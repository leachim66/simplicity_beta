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
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void initialize_phase_3(void);
IMPORT void resolve_symbols(void);
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
  NODE *_REVISION;
  NODE *_VERSION;
  NODE *_cc;
  NODE *_mkdir;
  NODE *_SIMLIBPATH;
  NODE *_SIMDATAPATH;
  NODE *_default_paths;
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
  NODE *_additional_libraries;
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
  "default_paths",
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
  "additional_libraries",
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
static NODE *func__sim2c__show_compiler_debug_info_1;
static void entry__sim2c__show_compiler_debug_info_1(void);
static FRAME_INFO frame__sim2c__show_compiler_debug_info_1 = {1, {"args"}};
static NODE *func__sim2c__show_compiler_debug_info_2;
static void entry__sim2c__show_compiler_debug_info_2(void);
static FRAME_INFO frame__sim2c__show_compiler_debug_info_2 = {1, {"args"}};
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
static NODE *func__resolve_filename_1;
static void entry__resolve_filename_1(void);
static FRAME_INFO frame__resolve_filename_1 = {3, {"filename", "libname", "libpath"}};
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
static NODE *func__add_module_infos_1;
static void entry__add_module_infos_1(void);
static FRAME_INFO frame__add_module_infos_1 = {7, {"path", "mod_path", "return", "entries", "filenames", "directories", "modules"}};
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
static NODE *func__lookup_1;
static void entry__lookup_1(void);
static FRAME_INFO frame__lookup_1 = {3, {"mod_filename", "mod_name", "info"}};
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
static NODE *func__CC_1;
static void entry__CC_1(void);
static FRAME_INFO frame__CC_1 = {1, {"args"}};
static NODE *func__CC_2;
static void entry__CC_2(void);
static FRAME_INFO frame__CC_2 = {1, {"args"}};
static void cont__CC_3(void);
static void cont__CC_4(void);
static void cont__CC_5(void);
static NODE *func__compile_c_1;
static void entry__compile_c_1(void);
static FRAME_INFO frame__compile_c_1 = {2, {"c_filename", "o_filename"}};
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
static NODE *func__compile_meta_module_1;
static void entry__compile_meta_module_1(void);
static FRAME_INFO frame__compile_meta_module_1 = {3, {"mod_filename", "mod_name", "meta_level"}};
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
static NODE *func__build_dependencies_1;
static void entry__build_dependencies_1(void);
static FRAME_INFO frame__build_dependencies_1 = {5, {"mod_filename", "mod_name", "c_buf", "do_compile_c", "return"}};
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
static NODE *func__compile_module_1;
static void entry__compile_module_1(void);
static FRAME_INFO frame__compile_module_1 = {6, {"mod_filename", "mod_name", "return", "compile_submodule", "mod_info", "o_filename"}};
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
static FRAME_INFO frame__compile_module_91 = {3, {"compile_submodule", "mod_name", "mod_filename"}};
static void cont__compile_module_92(void);
static void cont__compile_module_93(void);
static void cont__compile_module_94(void);
static void cont__compile_module_95(void);
static NODE *func__compile_module_96;
static void entry__compile_module_96(void);
static FRAME_INFO frame__compile_module_96 = {1, {"mod_filename"}};
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
static NODE *func__compile_modules_1;
static void entry__compile_modules_1(void);
static FRAME_INFO frame__compile_modules_1 = {4, {"path", "mod_path", "directories", "modules"}};
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
static NODE *func__show_file_list_1;
static void entry__show_file_list_1(void);
static FRAME_INFO frame__show_file_list_1 = {0, {}};
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
static NODE *func__library_paths_and_file_list_1;
static void entry__library_paths_and_file_list_1(void);
static FRAME_INFO frame__library_paths_and_file_list_1 = {4, {"library_paths", "object_files", "library_files", "paths"}};
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
static NODE *func__create_imports_1;
static void entry__create_imports_1(void);
static FRAME_INFO frame__create_imports_1 = {5, {"source", "already_checked", "collect_declarations", "imports", "first_part"}};
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
static NODE *func__compile_exe_1;
static void entry__compile_exe_1(void);
static FRAME_INFO frame__compile_exe_1 = {4, {"body", "return__1", "mod_filename", "mod_name"}};
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
static NODE *func__dump_source_or_check_1;
static void entry__dump_source_or_check_1(void);
static FRAME_INFO frame__dump_source_or_check_1 = {0, {}};
static NODE *func__dump_source_or_check_2;
static void entry__dump_source_or_check_2(void);
static FRAME_INFO frame__dump_source_or_check_2 = {3, {"mod_filename", "mod_name", "return__1"}};
static void cont__dump_source_or_check_3(void);
static void cont__dump_source_or_check_4(void);
static NODE *func__print_c_1;
static void entry__print_c_1(void);
static FRAME_INFO frame__print_c_1 = {0, {}};
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
static NODE *func__list_dependencies_1;
static void entry__list_dependencies_1(void);
static FRAME_INFO frame__list_dependencies_1 = {1, {"prefix_path"}};
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
static NODE *func__build_codeblocks_project_1;
static void entry__build_codeblocks_project_1(void);
static FRAME_INFO frame__build_codeblocks_project_1 = {0, {}};
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
static NODE *string__ae2cb2959270f10e;
static NODE *string__3a69827feeaedc87;
static NODE *string__65fb167cf21c35a9;
static void cont__build_codeblocks_project_32(void);
static void cont__build_codeblocks_project_33(void);
static NODE *func__build_codeblocks_project_34;
static void entry__build_codeblocks_project_34(void);
static FRAME_INFO frame__build_codeblocks_project_34 = {2, {"filename", "buf"}};
static NODE *string__86909867946dc27b;
static NODE *string__ca5af8c3e83c305d;
static void cont__build_codeblocks_project_37(void);
static void cont__build_codeblocks_project_38(void);
static void cont__build_codeblocks_project_39(void);
static void cont__build_codeblocks_project_40(void);
static void cont__build_codeblocks_project_41(void);
static void cont__build_codeblocks_project_42(void);
static NODE *string__4f8ac82e5b683b6f;
static NODE *string__6ec73fb9d26dad91;
static NODE *string__62c73cb6d2cd6da9;
static NODE *string__e224568f04fadefb;
static NODE *string__29a08e6f8046de11;
static NODE *string__97a58959c957d32c;
static NODE *string__629c968402fadffb;
static NODE *string__517e18f604196bbc;
static void cont__build_codeblocks_project_51(void);
static void cont__build_codeblocks_project_52(void);
static NODE *func__build_codeblocks_project_53;
static void entry__build_codeblocks_project_53(void);
static FRAME_INFO frame__build_codeblocks_project_53 = {4, {"filename", "prefix_path", "buf", "path_prefix"}};
static void cont__build_codeblocks_project_54(void);
static void cont__build_codeblocks_project_55(void);
static void cont__build_codeblocks_project_56(void);
static NODE *string__5ce0e5ba1304a164;
static NODE *string__48b865872b902196;
static void cont__build_codeblocks_project_59(void);
static void cont__build_codeblocks_project_60(void);
static void cont__build_codeblocks_project_61(void);
static NODE *string__1d1cedd7cdd611c4;
static void cont__build_codeblocks_project_63(void);
static NODE *func__build_library_1;
static void entry__build_library_1(void);
static FRAME_INFO frame__build_library_1 = {1, {"return__1"}};
static NODE *string__421f52c90112c2b9;
static void cont__build_library_3(void);
static NODE *func__build_library_4;
static void entry__build_library_4(void);
static FRAME_INFO frame__build_library_4 = {0, {}};
static NODE *string__c84d9037a41e8f73;
static void cont__build_library_6(void);
static NODE *func__build_library_7;
static void entry__build_library_7(void);
static FRAME_INFO frame__build_library_7 = {1, {"doc_libraries"}};
static void cont__build_library_8(void);
static NODE *func__build_library_9;
static void entry__build_library_9(void);
static FRAME_INFO frame__build_library_9 = {2, {"library", "doc_libraries"}};
static void cont__build_library_10(void);
static void cont__build_library_11(void);
static void cont__build_library_12(void);
static NODE *func__build_library_13;
static void entry__build_library_13(void);
static FRAME_INFO frame__build_library_13 = {5, {"version", "version_filename", "so_version", "base_filename", "lib_filename"}};
static NODE *string__84ca78485aeb98e;
static void cont__build_library_15(void);
static void cont__build_library_16(void);
static NODE *func__build_library_17;
static void entry__build_library_17(void);
static FRAME_INFO frame__build_library_17 = {2, {"version", "version_filename"}};
static void cont__build_library_18(void);
static void cont__build_library_19(void);
static void cont__build_library_20(void);
static void cont__build_library_21(void);
static void cont__build_library_22(void);
static void cont__build_library_23(void);
static void cont__build_library_24(void);
static void cont__build_library_25(void);
static void cont__build_library_26(void);
static NODE *func__build_library_27;
static void entry__build_library_27(void);
static FRAME_INFO frame__build_library_27 = {2, {"base_filename", "version"}};
static void cont__build_library_28(void);
static NODE *string__94340f9615d2e0d7;
static void cont__build_library_30(void);
static NODE *func__build_library_31;
static void entry__build_library_31(void);
static FRAME_INFO frame__build_library_31 = {2, {"base_filename", "version"}};
static NODE *string__9e0ae84b5d007d55;
static void cont__build_library_33(void);
static void cont__build_library_34(void);
static NODE *func__build_library_35;
static void entry__build_library_35(void);
static FRAME_INFO frame__build_library_35 = {2, {"base_filename", "version"}};
static NODE *string__6a1f556781f212b5;
static void cont__build_library_37(void);
static void cont__build_library_38(void);
static NODE *func__build_library_39;
static void entry__build_library_39(void);
static FRAME_INFO frame__build_library_39 = {2, {"base_filename", "version"}};
static void cont__build_library_40(void);
static void cont__build_library_41(void);
static NODE *string__561f538101f3c2b9;
static NODE *string__7c1f538281f242b9;
static void cont__build_library_44(void);
static NODE *func__build_library_45;
static void entry__build_library_45(void);
static FRAME_INFO frame__build_library_45 = {1, {"lib_filename"}};
static NODE *string__822587b3f48532f5;
static void cont__build_library_47(void);
static void cont__build_library_48(void);
static void cont__build_library_49(void);
static void cont__build_library_50(void);
static NODE *func__build_library_51;
static void entry__build_library_51(void);
static FRAME_INFO frame__build_library_51 = {2, {"lib_filename", "info"}};
static void cont__build_library_52(void);
static void cont__build_library_53(void);
static NODE *func__build_library_54;
static void entry__build_library_54(void);
static FRAME_INFO frame__build_library_54 = {1, {"info"}};
static void cont__build_library_55(void);
static void cont__build_library_56(void);
static void cont__build_library_57(void);
static NODE *func__build_library_58;
static void entry__build_library_58(void);
static FRAME_INFO frame__build_library_58 = {0, {}};
static void cont__build_library_59(void);
static NODE *func__build_library_60;
static void entry__build_library_60(void);
static FRAME_INFO frame__build_library_60 = {3, {"base_filename", "so_version", "lib_filename"}};
static NODE *func__build_library_61;
static void entry__build_library_61(void);
static FRAME_INFO frame__build_library_61 = {0, {}};
static NODE *string__b9aef2a4efc3a1a8;
static void cont__build_library_63(void);
static void cont__build_library_64(void);
static void cont__build_library_65(void);
static NODE *func__build_library_66;
static void entry__build_library_66(void);
static FRAME_INFO frame__build_library_66 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__f5937b2655b3cd24;
static void cont__build_library_68(void);
static void cont__build_library_69(void);
static NODE *string__b130095b1592409e;
static void cont__build_library_71(void);
static NODE *func__build_library_72;
static void entry__build_library_72(void);
static FRAME_INFO frame__build_library_72 = {1, {"err"}};
static void cont__build_library_73(void);
static NODE *func__build_library_74;
static void entry__build_library_74(void);
static FRAME_INFO frame__build_library_74 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__build_library_75(void);
static NODE *string__7e1f542601d292fa;
static void cont__build_library_77(void);
static void cont__build_library_78(void);
static NODE *func__build_library_79;
static void entry__build_library_79(void);
static FRAME_INFO frame__build_library_79 = {1, {"err"}};
static void cont__build_library_80(void);
static NODE *func__build_library_81;
static void entry__build_library_81(void);
static FRAME_INFO frame__build_library_81 = {6, {"base_filename", "so_version", "lib_filename", "out", "err", "success"}};
static NODE *string__33820b08e3b95a2a;
static void cont__build_library_83(void);
static void cont__build_library_84(void);
static void cont__build_library_85(void);
static NODE *string__c6d9125d36413a91;
static void cont__build_library_87(void);
static NODE *func__build_library_88;
static void entry__build_library_88(void);
static FRAME_INFO frame__build_library_88 = {1, {"err"}};
static void cont__build_library_89(void);
static NODE *func__build_library_90;
static void entry__build_library_90(void);
static FRAME_INFO frame__build_library_90 = {4, {"lib_filename", "out", "err", "success"}};
static void cont__build_library_91(void);
static void cont__build_library_92(void);
static NODE *func__build_library_93;
static void entry__build_library_93(void);
static FRAME_INFO frame__build_library_93 = {1, {"err"}};
static void cont__build_library_94(void);
static void cont__build_library_95(void);
static NODE *func__maybe_compile_c_file_1;
static void entry__maybe_compile_c_file_1(void);
static FRAME_INFO frame__maybe_compile_c_file_1 = {5, {"filename", "c_filename", "o_filename", "c_info", "o_info"}};
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
static NODE *func__format_number_1;
static void entry__format_number_1(void);
static FRAME_INFO frame__format_number_1 = {4, {"val", "n", "m", "ac"}};
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
static FRAME_INFO frame__format_number_11 = {3, {"val", "n", "i"}};
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
static NODE *func__sim2c__write_timing_info_1;
static void entry__sim2c__write_timing_info_1(void);
static FRAME_INFO frame__sim2c__write_timing_info_1 = {3, {"description", "filename", "new_t"}};
static void cont__sim2c__write_timing_info_2(void);
static void cont__sim2c__write_timing_info_3(void);
static NODE *func__sim2c__write_timing_info_4;
static void entry__sim2c__write_timing_info_4(void);
static FRAME_INFO frame__sim2c__write_timing_info_4 = {3, {"filename", "description", "new_t"}};
static void cont__sim2c__write_timing_info_5(void);
static void cont__sim2c__write_timing_info_6(void);
static void cont__sim2c__write_timing_info_7(void);
static void cont__sim2c__write_timing_info_8(void);
static void cont__sim2c__write_timing_info_9(void);
static void cont__sim2c__write_timing_info_10(void);
static void cont__sim2c__write_timing_info_11(void);
static NODE *string__2d7981f4e6082bb6;
static NODE *func__sim2c__write_timing_info_13;
static void entry__sim2c__write_timing_info_13(void);
static FRAME_INFO frame__sim2c__write_timing_info_13 = {2, {"description", "new_t"}};
static void cont__sim2c__write_timing_info_14(void);
static void cont__sim2c__write_timing_info_15(void);
static NODE *string__2d7981f4e6d82be5;
static void cont__sim2c__write_timing_info_17(void);
static void cont__sim2c__write_timing_info_18(void);
static NODE *get__sim2c__write_timing_info(void) {
  return var.sim2c__write_timing_info;
}
static NODE *func__build_executable_1;
static void entry__build_executable_1(void);
static FRAME_INFO frame__build_executable_1 = {0, {}};
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
static void cont__98_2(void);
static void cont__99_1(void);
static void cont__100_1(void);
static void cont__101_1(void);
static NODE *string__578a5af303e9ccf;
static void cont__102_2(void);
static void cont__103_1(void);
static void cont__104_1(void);
static void cont__104_2(void);
static NODE *string__5c5aea03ea80c025;
static void cont__105_2(void);
static NODE *string__55d5804f0e895069;
static void cont__106_2(void);
static NODE *string__2058710183abbfe4;
static void cont__107_2(void);
static void cont__108_1(void);
static NODE *string__1057e106f655c41;
static void cont__108_3(void);
static void cont__108_4(void);
static void cont__108_5(void);
static void cont__109_1(void);
static NODE *func__109_2;
static void entry__109_2(void);
static FRAME_INFO frame__109_2 = {0, {}};
static void cont__109_3(void);
static void cont__109_4(void);
static void cont__109_5(void);
static NODE *func__109_6;
static void entry__109_6(void);
static FRAME_INFO frame__109_6 = {0, {}};
static void cont__109_7(void);
static NODE *func__109_8;
static void entry__109_8(void);
static FRAME_INFO frame__109_8 = {0, {}};
static void cont__109_9(void);
static void cont__110_1(void);
static NODE *func__110_2;
static void entry__110_2(void);
static FRAME_INFO frame__110_2 = {0, {}};
static void cont__110_3(void);
static void cont__110_4(void);
static void cont__110_5(void);
static NODE *func__110_6;
static void entry__110_6(void);
static FRAME_INFO frame__110_6 = {0, {}};
static void cont__110_7(void);
static NODE *func__110_8;
static void entry__110_8(void);
static FRAME_INFO frame__110_8 = {0, {}};
static void cont__110_9(void);
static NODE *string__545aefc3ea81102f;
static void cont__112_2(void);
static void cont__112_3(void);
static void cont__112_4(void);
static void cont__112_5(void);
static NODE *string__fa720015d496ba0;
static void cont__112_7(void);
static NODE *string__fa725815d616ba2;
static void cont__112_9(void);
static void cont__112_10(void);
static void cont__112_11(void);
static NODE *func__114_1;
static void entry__114_1(void);
static FRAME_INFO frame__114_1 = {2, {"platform", "priority"}};
static void cont__114_2(void);
static NODE *func__114_3;
static void entry__114_3(void);
static FRAME_INFO frame__114_3 = {3, {"break", "platform", "priority"}};
static NODE *func__114_4;
static void entry__114_4(void);
static FRAME_INFO frame__114_4 = {4, {"platform", "break", "priority", "plat"}};
static void cont__114_5(void);
static void cont__114_6(void);
static void cont__114_7(void);
static void cont__114_8(void);
static void cont__114_9(void);
static void cont__114_10(void);
static void cont__114_11(void);
static void cont__114_12(void);
static void cont__114_13(void);
static void cont__141_1(void);
static void cont__141_2(void);
static void cont__141_3(void);
static void cont__142_1(void);
static NODE *func__142_2;
static void entry__142_2(void);
static FRAME_INFO frame__142_2 = {0, {}};
static void cont__142_3(void);
static NODE *func__142_4;
static void entry__142_4(void);
static FRAME_INFO frame__142_4 = {0, {}};
static NODE *string__8d3c5e4b22d2f22b;
static void cont__142_6(void);
static void cont__142_7(void);
static NODE *func__142_8;
static void entry__142_8(void);
static FRAME_INFO frame__142_8 = {0, {}};
static NODE *func__142_9;
static void entry__142_9(void);
static FRAME_INFO frame__142_9 = {0, {}};
static NODE *string__2b680b9e2e4fa558;
static NODE *string__8d1eb0934cb703aa;
static NODE *func__142_12;
static void entry__142_12(void);
static FRAME_INFO frame__142_12 = {0, {}};
static NODE *string__1124317d33023452;
static NODE *string__d3c3199b9e37dd88;
static NODE *func__142_15;
static void entry__142_15(void);
static FRAME_INFO frame__142_15 = {0, {}};
static NODE *string__2eb9522bce550419;
static NODE *string__31ed31d8e6f28138;
static NODE *func__142_18;
static void entry__142_18(void);
static FRAME_INFO frame__142_18 = {0, {}};
static NODE *string__23efc30ce16df2e;
static NODE *string__c565f1870e113429;
static NODE *func__142_21;
static void entry__142_21(void);
static FRAME_INFO frame__142_21 = {0, {}};
static NODE *string__ae4408db97d25099;
static NODE *string__2623b8ba9cf2f994;
static NODE *func__142_24;
static void entry__142_24(void);
static FRAME_INFO frame__142_24 = {0, {}};
static NODE *string__a7e97d93a221bbf6;
static NODE *string__fa3ca2557b3c0271;
static NODE *func__142_27;
static void entry__142_27(void);
static FRAME_INFO frame__142_27 = {0, {}};
static NODE *string__c95e7978381b7632;
static NODE *string__4cca41e5ff59895a;
static NODE *func__142_30;
static void entry__142_30(void);
static FRAME_INFO frame__142_30 = {0, {}};
static NODE *string__6e5ae943eae03031;
static NODE *string__22ca0f65643a26b5;
static NODE *func__142_33;
static void entry__142_33(void);
static FRAME_INFO frame__142_33 = {0, {}};
static NODE *string__7c90ae5f04ed72b3;
static NODE *string__ea6d59fa9dcad709;
static NODE *func__142_36;
static void entry__142_36(void);
static FRAME_INFO frame__142_36 = {0, {}};
static NODE *string__94300f9615cbf09d;
static NODE *string__aa7c4ea56fedf95b;
static NODE *func__142_39;
static void entry__142_39(void);
static FRAME_INFO frame__142_39 = {0, {}};
static NODE *string__a8480d98152a1083;
static NODE *string__10671df6f7523277;
static NODE *func__142_42;
static void entry__142_42(void);
static FRAME_INFO frame__142_42 = {0, {}};
static NODE *string__b65c0e101523e09f;
static NODE *string__2ba4a5a9cdae43b8;
static NODE *func__142_45;
static void entry__142_45(void);
static FRAME_INFO frame__142_45 = {0, {}};
static NODE *string__405aeb83ea605030;
static NODE *string__977692d258cc57f;
static NODE *func__142_48;
static void entry__142_48(void);
static FRAME_INFO frame__142_48 = {0, {}};
static NODE *string__d13d99340b731341;
static NODE *string__d30c0a59c3d26b04;
static NODE *func__142_51;
static void entry__142_51(void);
static FRAME_INFO frame__142_51 = {0, {}};
static NODE *string__2b7008daa973b572;
static NODE *string__99c92c9b20cfd38;
static NODE *func__142_54;
static void entry__142_54(void);
static FRAME_INFO frame__142_54 = {0, {}};
static NODE *string__7f0dce6ce0a2268e;
static NODE *string__140146cb87bc0040;
static NODE *func__142_57;
static void entry__142_57(void);
static FRAME_INFO frame__142_57 = {0, {}};
static NODE *string__211e9dd763481194;
static NODE *string__1214925be130f2c;
static NODE *func__142_60;
static void entry__142_60(void);
static FRAME_INFO frame__142_60 = {0, {}};
static NODE *string__984c0f9015dae09e;
static NODE *string__6ce7f8f6c7e73eb4;
static NODE *func__142_63;
static void entry__142_63(void);
static FRAME_INFO frame__142_63 = {0, {}};
static NODE *string__749427e68da7a564;
static NODE *string__93608261e3431133;
static NODE *func__142_66;
static void entry__142_66(void);
static FRAME_INFO frame__142_66 = {0, {}};
static NODE *string__5a1f534901f312b4;
static NODE *string__b20e03a80d6db737;
static NODE *func__142_69;
static void entry__142_69(void);
static FRAME_INFO frame__142_69 = {0, {}};
static NODE *string__be440f9b95da309f;
static NODE *string__6f1f4f6107c9cdea;
static NODE *func__142_72;
static void entry__142_72(void);
static FRAME_INFO frame__142_72 = {0, {}};
static NODE *string__72b0ad9004bdc085;
static NODE *string__bb8770c27da8f42f;
static NODE *func__142_75;
static void entry__142_75(void);
static FRAME_INFO frame__142_75 = {0, {}};
static NODE *string__af5ae49d07a6e408;
static NODE *string__c8a7274dc08e5785;
static void cont__142_78(void);
static void cont__142_79(void);
static void cont__143_1(void);
static void cont__144_1(void);
static NODE *func__146_1;
static void entry__146_1(void);
static FRAME_INFO frame__146_1 = {0, {}};
static void cont__146_2(void);
static void cont__151_1(void);
static NODE *string__245aeb43eaacc03b;
static NODE *string__e381a5286a12b5a7;
static NODE *string__c9d1a7e66a0a17ac;
static NODE *string__1abcc193f1dac47a;
static NODE *string__d3e88c522110dabb;
static NODE *string__65a7cd1120033166;
static NODE *string__fa733015c516bfd;
static NODE *string__465ae703eb84c014;
static NODE *string__40ebeb253b72cf38;
static NODE *string__edf2e5a02a882fc3;
static void cont__152_11(void);
static void cont__153_1(void);
static NODE *string__fa721815d316baf;
static void cont__153_3(void);
static NODE *func__153_4;
static void entry__153_4(void);
static FRAME_INFO frame__153_4 = {0, {}};
static NODE *string__ecde9da404625e23;
static void cont__153_6(void);
static void cont__153_7(void);
static void cont__154_1(void);
static NODE *string__f41f598c8327d2e5;
static NODE *string__f41f598c830fd2e3;
static void cont__154_4(void);
static NODE *func__154_5;
static void entry__154_5(void);
static FRAME_INFO frame__154_5 = {0, {}};
static NODE *string__7e1f52a6019282e5;
static void cont__154_7(void);
static NODE *string__70d94c874a06872f;
static void cont__154_9(void);
static void cont__154_10(void);
static NODE *func__155_1;
static void entry__155_1(void);
static FRAME_INFO frame__155_1 = {1, {"path"}};
static NODE *string__2d7981f4e6602b8c;
static void cont__155_3(void);
static void cont__155_4(void);
static void cont__155_5(void);
static void cont__157_1(void);
static void cont__157_2(void);
static NODE *func__157_3;
static void entry__157_3(void);
static FRAME_INFO frame__157_3 = {1, {"option"}};
static void cont__157_4(void);
static void cont__157_5(void);
static void cont__159_1(void);
static void cont__159_2(void);
static NODE *func__159_3;
static void entry__159_3(void);
static FRAME_INFO frame__159_3 = {1, {"option"}};
static void cont__159_4(void);
static void cont__159_5(void);
static void cont__177_1(void);
static NODE *func__177_2;
static void entry__177_2(void);
static FRAME_INFO frame__177_2 = {0, {}};
static NODE *string__9b6a42533552c66c;
static NODE *string__79c06fde49ef2e97;
static void cont__177_5(void);
static void cont__177_6(void);
static NODE *func__192_1;
static void entry__192_1(void);
static FRAME_INFO frame__192_1 = {0, {}};
static void cont__192_2(void);
static void cont__192_3(void);
static NODE *func__193_1;
static void entry__193_1(void);
static FRAME_INFO frame__193_1 = {0, {}};
static NODE *func__193_2;
static void entry__193_2(void);
static FRAME_INFO frame__193_2 = {0, {}};
static NODE *func__193_3;
static void entry__193_3(void);
static FRAME_INFO frame__193_3 = {0, {}};
static NODE *func__193_4;
static void entry__193_4(void);
static FRAME_INFO frame__193_4 = {0, {}};
static void cont__193_5(void);
static void cont__193_6(void);
static void cont__193_7(void);
static NODE *func__193_8;
static void entry__193_8(void);
static FRAME_INFO frame__193_8 = {0, {}};
static NODE *func__193_9;
static void entry__193_9(void);
static FRAME_INFO frame__193_9 = {0, {}};
static NODE *func__193_10;
static void entry__193_10(void);
static FRAME_INFO frame__193_10 = {0, {}};
static NODE *func__193_11;
static void entry__193_11(void);
static FRAME_INFO frame__193_11 = {0, {}};
static void cont__193_12(void);
static void cont__193_13(void);
static void cont__194_1(void);
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
  {cont__98_2, NULL, 96, 96, 1, 30},
  {cont__99_1, NULL, 97, 97, 1, 30},
  {cont__100_1, NULL, 98, 98, 1, 28},
  {cont__101_1, NULL, 100, 100, 1, 40},
  {cont__102_2, NULL, 102, 102, 1, 15},
  {cont__103_1, NULL, 104, 104, 12, 23},
  {cont__104_1, NULL, 104, 104, 1, 23},
  {cont__104_2, NULL, 105, 105, 1, 72},
  {cont__105_2, NULL, 106, 106, 1, 37},
  {cont__106_2, NULL, 107, 107, 1, 39},
  {cont__107_2, NULL, 109, 109, 28, 35},
  {cont__108_1, NULL, 109, 109, 37, 66},
  {cont__108_3, NULL, 109, 109, 21, 67},
  {cont__108_4, NULL, 109, 109, 1, 68},
  {cont__108_5, NULL, 113, 113, 5, 25},
  {cont__109_1, NULL, 113, 113, 5, 45},
  {cont__109_5, NULL, 111, 115, 1, 21},
  {cont__109_9, NULL, 119, 119, 5, 26},
  {cont__110_1, NULL, 119, 119, 5, 47},
  {cont__110_5, NULL, 117, 121, 1, 21},
  {cont__110_9, NULL, 127, 127, 5, 19},
  {cont__112_2, NULL, 128, 128, 5, 22},
  {cont__112_3, NULL, 129, 129, 5, 22},
  {cont__112_4, NULL, 130, 130, 5, 21},
  {cont__112_5, NULL, 131, 131, 5, 19},
  {cont__112_7, NULL, 132, 132, 5, 17},
  {cont__112_9, NULL, 133, 133, 5, 16},
  {cont__112_10, NULL, 125, 133, 1, 17},
  {cont__112_11, NULL, 136, 146, 1, 22},
  {cont__114_13, NULL, 173, 173, 42, 42},
  {cont__141_1, NULL, 173, 173, 9, 43},
  {cont__141_2, NULL, 173, 173, 1, 63},
  {cont__141_3, NULL, 175, 175, 3, 20},
  {cont__142_1, NULL, 174, 258, 1, 79},
  {cont__142_79, NULL, 260, 260, 1, 39},
  {cont__143_1, NULL, 261, 261, 1, 30},
  {cont__144_1, NULL, 263, 263, 1, 37},
  {cont__146_2, NULL, 272, 272, 1, 21},
  {cont__151_1, NULL, 274, 285, 1, 27},
  {cont__152_11, NULL, 287, 287, 4, 15},
  {cont__153_1, NULL, 287, 287, 4, 24},
  {cont__153_3, NULL, 287, 288, 1, 45},
  {cont__153_7, NULL, 290, 290, 6, 28},
  {cont__154_1, NULL, 291, 291, 3, 20},
  {cont__154_4, NULL, 290, 293, 1, 36},
  {cont__154_10, NULL, 295, 296, 1, 30},
  {cont__155_5, NULL, 299, 299, 16, 25},
  {cont__157_1, NULL, 299, 299, 10, 26},
  {cont__157_2, NULL, 299, 300, 1, 26},
  {cont__157_5, NULL, 303, 303, 16, 24},
  {cont__159_1, NULL, 303, 303, 10, 25},
  {cont__159_2, NULL, 303, 304, 1, 25},
  {cont__159_5, NULL, 645, 645, 4, 25},
  {cont__177_1, NULL, 645, 647, 1, 52},
  {cont__177_6, NULL, 1097, 1097, 1, 36},
  {cont__192_3, NULL, 1098, 1110, 1, 18},
  {cont__193_13, NULL, },
  {cont__194_1, NULL, },
  {entry__sim2c__show_compiler_debug_info_2, NULL, 266, 266, 36, 49},
  {entry__sim2c__show_compiler_debug_info_1, NULL, 266, 266, 3, 49},
  {entry__resolve_filename_13, NULL, 323, 323, 37, 80},
  {cont__resolve_filename_14, &frame__resolve_filename_13, 323, 323, 37, 61},
  {cont__resolve_filename_15, &frame__resolve_filename_13, 323, 323, 80, 80},
  {entry__resolve_filename_10, NULL, 322, 322, 13, 41},
  {cont__resolve_filename_11, &frame__resolve_filename_10, 323, 323, 16, 34},
  {cont__resolve_filename_12, &frame__resolve_filename_10, 323, 323, 13, 80},
  {entry__resolve_filename_8, NULL, 321, 321, 14, 33},
  {cont__resolve_filename_9, &frame__resolve_filename_8, 321, 323, 11, 80},
  {entry__resolve_filename_6, NULL, 320, 320, 18, 32},
  {cont__resolve_filename_7, &frame__resolve_filename_6, 320, 323, 9, 81},
  {entry__resolve_filename_4, NULL, 319, 319, 10, 26},
  {cont__resolve_filename_5, &frame__resolve_filename_4, 319, 323, 7, 82},
  {entry__resolve_filename_3, NULL, 318, 323, 5, 83},
  {entry__resolve_filename_20, NULL, 327, 328, 11, 57},
  {cont__resolve_filename_23, &frame__resolve_filename_20, 327, 328, 5, 57},
  {entry__resolve_filename_1, NULL, 316, 316, 6, 36},
  {cont__resolve_filename_2, &frame__resolve_filename_1, 316, 323, 3, 84},
  {cont__resolve_filename_16, &frame__resolve_filename_1, 324, 324, 3, 32},
  {cont__resolve_filename_17, &frame__resolve_filename_1, 325, 325, 3, 38},
  {cont__resolve_filename_18, &frame__resolve_filename_1, 326, 326, 6, 25},
  {cont__resolve_filename_19, &frame__resolve_filename_1, 326, 328, 3, 58},
  {cont__resolve_filename_24, &frame__resolve_filename_1, 329, 329, 21, 39},
  {cont__resolve_filename_25, &frame__resolve_filename_1, 329, 329, 6, 40},
  {cont__resolve_filename_26, &frame__resolve_filename_1, 329, 329, 3, 40},
  {entry__add_module_infos_10, NULL, 347, 347, 56, 77},
  {cont__add_module_infos_11, &frame__add_module_infos_10, 347, 347, 77, 77},
  {entry__add_module_infos_8, NULL, 347, 347, 35, 53},
  {cont__add_module_infos_9, &frame__add_module_infos_8, 347, 347, 32, 77},
  {entry__add_module_infos_6, NULL, 347, 347, 10, 29},
  {cont__add_module_infos_7, &frame__add_module_infos_6, 347, 347, 7, 77},
  {entry__add_module_infos_28, NULL, 353, 353, 41, 65},
  {cont__add_module_infos_29, &frame__add_module_infos_28, 353, 353, 41, 65},
  {entry__add_module_infos_31, NULL, 354, 354, 11, 38},
  {cont__add_module_infos_32, &frame__add_module_infos_31, 354, 354, 49, 49},
  {entry__add_module_infos_15, NULL, 349, 349, 48, 60},
  {cont__add_module_infos_17, &frame__add_module_infos_15, 349, 349, 48, 68},
  {cont__add_module_infos_18, &frame__add_module_infos_15, 349, 349, 9, 69},
  {cont__add_module_infos_19, &frame__add_module_infos_15, 350, 350, 9, 34},
  {cont__add_module_infos_20, &frame__add_module_infos_15, 351, 351, 22, 36},
  {cont__add_module_infos_21, &frame__add_module_infos_15, 351, 351, 38, 62},
  {cont__add_module_infos_22, &frame__add_module_infos_15, 351, 351, 22, 62},
  {cont__add_module_infos_23, &frame__add_module_infos_15, 351, 351, 22, 64},
  {cont__add_module_infos_24, &frame__add_module_infos_15, 351, 351, 9, 67},
  {cont__add_module_infos_25, &frame__add_module_infos_15, 352, 352, 9, 49},
  {cont__add_module_infos_26, &frame__add_module_infos_15, 353, 353, 12, 36},
  {cont__add_module_infos_27, &frame__add_module_infos_15, 353, 353, 12, 65},
  {cont__add_module_infos_30, &frame__add_module_infos_15, 353, 354, 9, 49},
  {cont__add_module_infos_33, &frame__add_module_infos_15, 355, 355, 9, 52},
  {cont__add_module_infos_34, &frame__add_module_infos_15, 356, 356, 9, 26},
  {cont__add_module_infos_35, &frame__add_module_infos_15, 357, 357, 9, 43},
  {cont__add_module_infos_36, &frame__add_module_infos_15, 358, 358, 9, 30},
  {cont__add_module_infos_37, &frame__add_module_infos_15, 358, 358, 52, 52},
  {entry__add_module_infos_12, NULL, 348, 348, 10, 33},
  {cont__add_module_infos_14, &frame__add_module_infos_12, 348, 358, 7, 52},
  {entry__add_module_infos_4, NULL, 345, 345, 5, 33},
  {cont__add_module_infos_5, &frame__add_module_infos_4, 346, 358, 5, 53},
  {entry__add_module_infos_49, NULL, 364, 364, 38, 60},
  {cont__add_module_infos_50, &frame__add_module_infos_49, 364, 364, 60, 60},
  {entry__add_module_infos_45, NULL, 363, 363, 11, 54},
  {cont__add_module_infos_47, &frame__add_module_infos_45, 364, 364, 14, 35},
  {cont__add_module_infos_48, &frame__add_module_infos_45, 364, 364, 11, 60},
  {entry__add_module_infos_57, NULL, 371, 372, 17, 57},
  {cont__add_module_infos_60, &frame__add_module_infos_57, 371, 372, 11, 57},
  {entry__add_module_infos_67, NULL, 376, 376, 11, 34},
  {cont__add_module_infos_68, &frame__add_module_infos_67, 377, 377, 11, 45},
  {cont__add_module_infos_69, &frame__add_module_infos_67, 377, 377, 45, 45},
  {entry__add_module_infos_64, NULL, 375, 375, 18, 31},
  {cont__add_module_infos_65, &frame__add_module_infos_64, 375, 375, 18, 31},
  {cont__add_module_infos_66, &frame__add_module_infos_64, 375, 377, 15, 45},
  {entry__add_module_infos_44, NULL, 366, 366, 9, 35},
  {cont__add_module_infos_51, &frame__add_module_infos_44, 367, 367, 35, 58},
  {cont__add_module_infos_52, &frame__add_module_infos_44, 367, 367, 9, 59},
  {cont__add_module_infos_53, &frame__add_module_infos_44, 368, 368, 9, 39},
  {cont__add_module_infos_54, &frame__add_module_infos_44, 369, 369, 9, 46},
  {cont__add_module_infos_55, &frame__add_module_infos_44, 370, 370, 16, 32},
  {cont__add_module_infos_56, &frame__add_module_infos_44, 370, 372, 9, 58},
  {cont__add_module_infos_61, &frame__add_module_infos_44, 373, 373, 9, 30},
  {cont__add_module_infos_62, &frame__add_module_infos_44, 374, 374, 9, 34},
  {cont__add_module_infos_63, &frame__add_module_infos_44, 375, 377, 9, 45},
  {cont__add_module_infos_70, &frame__add_module_infos_44, 378, 378, 10, 30},
  {cont__add_module_infos_71, &frame__add_module_infos_44, 378, 378, 9, 40},
  {cont__add_module_infos_72, &frame__add_module_infos_44, 378, 378, 9, 30},
  {cont__add_module_infos_73, &frame__add_module_infos_44, 378, 378, 46, 46},
  {entry__add_module_infos_41, NULL, 361, 361, 14, 44},
  {cont__add_module_infos_43, &frame__add_module_infos_41, 361, 378, 7, 46},
  {entry__add_module_infos_39, NULL, 360, 360, 8, 30},
  {cont__add_module_infos_40, &frame__add_module_infos_39, 360, 378, 5, 47},
  {entry__add_module_infos_77, NULL, 379, 379, 39, 64},
  {entry__add_module_infos_1, NULL, 340, 340, 22, 27},
  {cont__add_module_infos_2, &frame__add_module_infos_1, 340, 340, 3, 33},
  {cont__add_module_infos_3, &frame__add_module_infos_1, 344, 358, 3, 54},
  {cont__add_module_infos_38, &frame__add_module_infos_1, 359, 378, 3, 48},
  {cont__add_module_infos_74, &frame__add_module_infos_1, 379, 379, 6, 31},
  {cont__add_module_infos_75, &frame__add_module_infos_1, 379, 379, 6, 36},
  {cont__add_module_infos_76, &frame__add_module_infos_1, 379, 379, 3, 64},
  {cont__add_module_infos_78, &frame__add_module_infos_1, 379, 379, 64, 64},
  {entry__lookup_4, NULL, 390, 390, 23, 29},
  {entry__lookup_5, NULL, 391, 391, 47, 47},
  {cont__lookup_6, &frame__lookup_5, 391, 391, 22, 48},
  {cont__lookup_7, &frame__lookup_5, 391, 391, 70, 70},
  {cont__lookup_8, &frame__lookup_5, 391, 391, 50, 71},
  {cont__lookup_9, &frame__lookup_5, 391, 391, 5, 71},
  {cont__lookup_10, &frame__lookup_5, 392, 392, 8, 28},
  {cont__lookup_11, &frame__lookup_5, 392, 392, 5, 28},
  {entry__lookup_1, NULL, 389, 389, 3, 29},
  {cont__lookup_2, &frame__lookup_1, 390, 390, 6, 20},
  {cont__lookup_3, &frame__lookup_1, 390, 392, 3, 28},
  {entry__CC_2, NULL, 395, 395, 36, 47},
  {cont__CC_3, &frame__CC_2, 395, 395, 53, 62},
  {cont__CC_4, &frame__CC_2, 395, 395, 27, 62},
  {entry__CC_1, NULL, 395, 395, 3, 62},
  {cont__CC_5, &frame__CC_1, 396, 396, 3, 10},
  {entry__compile_c_2, NULL, 399, 399, 41, 60},
  {entry__compile_c_8, NULL, 404, 404, 11, 23},
  {cont__compile_c_9, &frame__compile_c_8, 402, 404, 13, 24},
  {cont__compile_c_12, &frame__compile_c_8, 402, 404, 7, 24},
  {entry__compile_c_4, NULL, 400, 400, 5, 83},
  {cont__compile_c_7, &frame__compile_c_4, 401, 404, 5, 25},
  {cont__compile_c_13, &frame__compile_c_4, 405, 405, 17, 17},
  {entry__compile_c_1, NULL, 399, 399, 10, 60},
  {cont__compile_c_3, &frame__compile_c_1, 399, 405, 3, 17},
  {entry__compile_meta_module_25, NULL, 432, 432, 45, 74},
  {cont__compile_meta_module_26, &frame__compile_meta_module_25, 432, 432, 9, 41},
  {cont__compile_meta_module_27, &frame__compile_meta_module_25, 432, 432, 9, 74},
  {cont__compile_meta_module_28, &frame__compile_meta_module_25, 432, 432, 9, 74},
  {entry__compile_meta_module_21, NULL, 431, 431, 43, 75},
  {cont__compile_meta_module_22, &frame__compile_meta_module_21, 431, 431, 9, 39},
  {cont__compile_meta_module_23, &frame__compile_meta_module_21, 431, 431, 9, 75},
  {cont__compile_meta_module_24, &frame__compile_meta_module_21, 432, 432, 9, 74},
  {cont__compile_meta_module_29, &frame__compile_meta_module_21, },
  {entry__compile_meta_module_19, NULL, 430, 430, 9, 32},
  {cont__compile_meta_module_20, &frame__compile_meta_module_19, },
  {cont__compile_meta_module_30, &frame__compile_meta_module_19, },
  {entry__compile_meta_module_17, NULL, 429, 429, 9, 29},
  {cont__compile_meta_module_18, &frame__compile_meta_module_17, },
  {cont__compile_meta_module_31, &frame__compile_meta_module_17, },
  {entry__compile_meta_module_41, NULL, 444, 444, 17, 47},
  {cont__compile_meta_module_42, &frame__compile_meta_module_41, 444, 444, 17, 67},
  {cont__compile_meta_module_43, &frame__compile_meta_module_41, 444, 444, 17, 67},
  {entry__compile_meta_module_45, NULL, 447, 447, 17, 21},
  {entry__compile_meta_module_38, NULL, 440, 440, 13, 42},
  {cont__compile_meta_module_39, &frame__compile_meta_module_38, 443, 443, 17, 38},
  {cont__compile_meta_module_40, &frame__compile_meta_module_38, 442, 444, 15, 66},
  {cont__compile_meta_module_44, &frame__compile_meta_module_38, 441, 447, 13, 22},
  {entry__compile_meta_module_58, NULL, 457, 457, 58, 58},
  {cont__compile_meta_module_59, &frame__compile_meta_module_58, 457, 457, 40, 59},
  {cont__compile_meta_module_60, &frame__compile_meta_module_58, 457, 457, 23, 60},
  {cont__compile_meta_module_61, &frame__compile_meta_module_58, 457, 457, 17, 60},
  {entry__compile_meta_module_63, NULL, 459, 459, 53, 77},
  {cont__compile_meta_module_64, &frame__compile_meta_module_63, 459, 459, 47, 77},
  {entry__compile_meta_module_62, NULL, 459, 459, 17, 77},
  {entry__compile_meta_module_55, NULL, 456, 456, 15, 40},
  {cont__compile_meta_module_57, &frame__compile_meta_module_55, 455, 459, 13, 78},
  {entry__compile_meta_module_37, NULL, 449, 449, 18, 41},
  {cont__compile_meta_module_47, &frame__compile_meta_module_37, 449, 449, 11, 47},
  {cont__compile_meta_module_48, &frame__compile_meta_module_37, 450, 450, 11, 26},
  {cont__compile_meta_module_49, &frame__compile_meta_module_37, 451, 451, 11, 20},
  {cont__compile_meta_module_50, &frame__compile_meta_module_37, 452, 452, 11, 50},
  {cont__compile_meta_module_51, &frame__compile_meta_module_37, 453, 453, 11, 44},
  {cont__compile_meta_module_52, &frame__compile_meta_module_37, 454, 454, 14, 30},
  {cont__compile_meta_module_54, &frame__compile_meta_module_37, 454, 459, 11, 79},
  {entry__compile_meta_module_36, NULL, 438, 459, 9, 80},
  {cont__compile_meta_module_65, &frame__compile_meta_module_36, 459, 459, 80, 80},
  {entry__compile_meta_module_33, NULL, 435, 435, 7, 55},
  {cont__compile_meta_module_34, &frame__compile_meta_module_33, 436, 436, 7, 38},
  {cont__compile_meta_module_35, &frame__compile_meta_module_33, 437, 459, 7, 81},
  {entry__compile_meta_module_74, NULL, 474, 474, 29, 41},
  {cont__compile_meta_module_75, &frame__compile_meta_module_74, 474, 474, 23, 41},
  {entry__compile_meta_module_67, NULL, 468, 468, 7, 36},
  {cont__compile_meta_module_68, &frame__compile_meta_module_67, 469, 469, 7, 22},
  {cont__compile_meta_module_69, &frame__compile_meta_module_67, 470, 470, 7, 31},
  {cont__compile_meta_module_70, &frame__compile_meta_module_67, 471, 471, 7, 32},
  {cont__compile_meta_module_71, &frame__compile_meta_module_67, 472, 472, 7, 43},
  {cont__compile_meta_module_72, &frame__compile_meta_module_67, 473, 473, 7, 32},
  {cont__compile_meta_module_73, &frame__compile_meta_module_67, 474, 474, 7, 41},
  {cont__compile_meta_module_76, &frame__compile_meta_module_67, 475, 475, 25, 35},
  {cont__compile_meta_module_77, &frame__compile_meta_module_67, 475, 475, 7, 35},
  {cont__compile_meta_module_78, &frame__compile_meta_module_67, 475, 475, 35, 35},
  {entry__compile_meta_module_2, NULL, 417, 417, 48, 48},
  {cont__compile_meta_module_3, &frame__compile_meta_module_2, 417, 417, 5, 49},
  {cont__compile_meta_module_4, &frame__compile_meta_module_2, 418, 418, 35, 57},
  {cont__compile_meta_module_5, &frame__compile_meta_module_2, 418, 418, 5, 58},
  {cont__compile_meta_module_6, &frame__compile_meta_module_2, 419, 419, 5, 42},
  {cont__compile_meta_module_7, &frame__compile_meta_module_2, 420, 420, 42, 64},
  {cont__compile_meta_module_8, &frame__compile_meta_module_2, 420, 420, 5, 70},
  {cont__compile_meta_module_10, &frame__compile_meta_module_2, 421, 421, 51, 62},
  {cont__compile_meta_module_11, &frame__compile_meta_module_2, 421, 421, 39, 63},
  {cont__compile_meta_module_12, &frame__compile_meta_module_2, 421, 421, 5, 71},
  {cont__compile_meta_module_13, &frame__compile_meta_module_2, 422, 422, 5, 34},
  {cont__compile_meta_module_14, &frame__compile_meta_module_2, 423, 423, 5, 32},
  {cont__compile_meta_module_15, &frame__compile_meta_module_2, 424, 424, 5, 38},
  {cont__compile_meta_module_16, &frame__compile_meta_module_2, 426, 432, 5, 75},
  {cont__compile_meta_module_32, &frame__compile_meta_module_2, 434, 459, 5, 82},
  {cont__compile_meta_module_66, &frame__compile_meta_module_2, 460, 475, 5, 35},
  {cont__compile_meta_module_79, &frame__compile_meta_module_2, 476, 476, 5, 19},
  {cont__compile_meta_module_80, &frame__compile_meta_module_2, 477, 477, 8, 21},
  {cont__compile_meta_module_81, &frame__compile_meta_module_2, 477, 477, 5, 21},
  {entry__compile_meta_module_1, NULL, 416, 477, 3, 21},
  {entry__build_dependencies_13, NULL, 502, 502, 43, 43},
  {cont__build_dependencies_14, &frame__build_dependencies_13, 502, 502, 15, 44},
  {cont__build_dependencies_15, &frame__build_dependencies_13, 504, 504, 48, 48},
  {cont__build_dependencies_16, &frame__build_dependencies_13, 504, 504, 24, 49},
  {cont__build_dependencies_17, &frame__build_dependencies_13, 504, 504, 17, 59},
  {cont__build_dependencies_18, &frame__build_dependencies_13, 505, 505, 44, 44},
  {cont__build_dependencies_19, &frame__build_dependencies_13, 505, 505, 24, 45},
  {cont__build_dependencies_20, &frame__build_dependencies_13, 505, 505, 17, 55},
  {cont__build_dependencies_21, &frame__build_dependencies_13, 503, 505, 15, 55},
  {entry__build_dependencies_11, NULL, 501, 501, 16, 26},
  {cont__build_dependencies_12, &frame__build_dependencies_11, 501, 505, 13, 56},
  {entry__build_dependencies_24, NULL, 511, 511, 17, 36},
  {entry__build_dependencies_23, NULL, },
  {cont__build_dependencies_25, &frame__build_dependencies_23, },
  {entry__build_dependencies_27, NULL, 513, 513, 32, 57},
  {cont__build_dependencies_28, &frame__build_dependencies_27, 513, 513, 17, 66},
  {entry__build_dependencies_30, NULL, 516, 516, 44, 71},
  {cont__build_dependencies_31, &frame__build_dependencies_30, 516, 516, 30, 72},
  {cont__build_dependencies_33, &frame__build_dependencies_30, 516, 516, 19, 73},
  {cont__build_dependencies_34, &frame__build_dependencies_30, 516, 516, 78, 78},
  {entry__build_dependencies_29, NULL, 515, 516, 17, 78},
  {entry__build_dependencies_22, NULL, },
  {cont__build_dependencies_26, &frame__build_dependencies_22, 507, 516, 13, 80},
  {entry__build_dependencies_9, NULL, 500, 500, 11, 36},
  {cont__build_dependencies_10, &frame__build_dependencies_9, 499, 516, 9, 82},
  {entry__build_dependencies_36, NULL, 518, 518, 37, 64},
  {cont__build_dependencies_37, &frame__build_dependencies_36, 518, 518, 26, 65},
  {cont__build_dependencies_38, &frame__build_dependencies_36, 518, 518, 70, 70},
  {entry__build_dependencies_35, NULL, 518, 518, 9, 70},
  {entry__build_dependencies_2, NULL, 491, 491, 12, 35},
  {cont__build_dependencies_3, &frame__build_dependencies_2, 491, 491, 5, 42},
  {cont__build_dependencies_4, &frame__build_dependencies_2, 492, 492, 5, 20},
  {cont__build_dependencies_5, &frame__build_dependencies_2, 493, 493, 5, 14},
  {cont__build_dependencies_6, &frame__build_dependencies_2, 494, 494, 5, 44},
  {cont__build_dependencies_7, &frame__build_dependencies_2, 495, 495, 5, 38},
  {cont__build_dependencies_8, &frame__build_dependencies_2, 496, 518, 5, 71},
  {entry__build_dependencies_1, NULL, 490, 518, 3, 72},
  {cont__build_dependencies_41, &frame__build_dependencies_1, 518, 518, 72, 72},
  {entry__compile_module_9, NULL, 540, 540, 28, 44},
  {cont__compile_module_10, &frame__compile_module_9, 540, 540, 28, 44},
  {entry__compile_module_12, NULL, 541, 541, 9, 72},
  {entry__compile_module_18, NULL, 546, 547, 15, 49},
  {cont__compile_module_20, &frame__compile_module_18, 546, 547, 9, 49},
  {entry__compile_module_23, NULL, 551, 551, 11, 40},
  {cont__compile_module_24, &frame__compile_module_23, 551, 551, 11, 60},
  {cont__compile_module_25, &frame__compile_module_23, 551, 551, 11, 60},
  {entry__compile_module_27, NULL, 553, 553, 11, 59},
  {cont__compile_module_28, &frame__compile_module_27, 553, 553, 59, 59},
  {entry__compile_module_3, NULL, 538, 538, 7, 45},
  {cont__compile_module_4, &frame__compile_module_3, 539, 539, 58, 58},
  {cont__compile_module_5, &frame__compile_module_3, 539, 539, 34, 59},
  {cont__compile_module_6, &frame__compile_module_3, 539, 539, 7, 75},
  {cont__compile_module_7, &frame__compile_module_3, 540, 540, 10, 23},
  {cont__compile_module_8, &frame__compile_module_3, 540, 540, 10, 44},
  {cont__compile_module_11, &frame__compile_module_3, 540, 541, 7, 72},
  {cont__compile_module_13, &frame__compile_module_3, 542, 542, 7, 53},
  {cont__compile_module_14, &frame__compile_module_3, 543, 543, 7, 38},
  {cont__compile_module_15, &frame__compile_module_3, 544, 544, 7, 34},
  {cont__compile_module_16, &frame__compile_module_3, 545, 545, 14, 32},
  {cont__compile_module_17, &frame__compile_module_3, 545, 547, 7, 50},
  {cont__compile_module_21, &frame__compile_module_3, 550, 550, 11, 40},
  {cont__compile_module_22, &frame__compile_module_3, 549, 551, 9, 59},
  {cont__compile_module_26, &frame__compile_module_3, 548, 553, 7, 60},
  {entry__compile_module_32, NULL, 556, 556, 22, 43},
  {cont__compile_module_33, &frame__compile_module_32, 556, 556, 48, 48},
  {entry__compile_module_37, NULL, 562, 562, 29, 56},
  {cont__compile_module_38, &frame__compile_module_37, 562, 562, 9, 56},
  {cont__compile_module_39, &frame__compile_module_37, 562, 562, 9, 56},
  {entry__compile_module_35, NULL, 561, 561, 9, 27},
  {cont__compile_module_36, &frame__compile_module_35, 562, 562, 9, 56},
  {cont__compile_module_40, &frame__compile_module_35, },
  {entry__compile_module_47, NULL, 565, 565, 21, 63},
  {entry__compile_module_50, NULL, 566, 566, 35, 53},
  {entry__compile_module_52, NULL, 567, 567, 32, 54},
  {entry__compile_module_56, NULL, 569, 569, 26, 56},
  {entry__compile_module_42, NULL, 564, 564, 50, 59},
  {cont__compile_module_44, &frame__compile_module_42, 564, 564, 61, 70},
  {cont__compile_module_45, &frame__compile_module_42, 564, 564, 9, 71},
  {cont__compile_module_46, &frame__compile_module_42, 565, 565, 9, 63},
  {cont__compile_module_49, &frame__compile_module_42, 566, 566, 9, 53},
  {cont__compile_module_51, &frame__compile_module_42, 567, 567, 9, 54},
  {cont__compile_module_53, &frame__compile_module_42, 568, 568, 25, 37},
  {cont__compile_module_54, &frame__compile_module_42, 568, 568, 9, 37},
  {cont__compile_module_55, &frame__compile_module_42, 569, 569, 9, 56},
  {cont__compile_module_57, &frame__compile_module_42, 569, 569, 56, 56},
  {entry__compile_module_62, NULL, 576, 576, 44, 71},
  {cont__compile_module_63, &frame__compile_module_62, 576, 576, 13, 40},
  {cont__compile_module_64, &frame__compile_module_62, 576, 576, 13, 71},
  {cont__compile_module_65, &frame__compile_module_62, 576, 576, 13, 71},
  {entry__compile_module_68, NULL, 578, 578, 30, 60},
  {entry__compile_module_67, NULL, 578, 578, 13, 60},
  {entry__compile_module_71, NULL, 583, 583, 17, 44},
  {cont__compile_module_72, &frame__compile_module_71, 583, 583, 17, 69},
  {cont__compile_module_73, &frame__compile_module_71, 583, 583, 17, 69},
  {entry__compile_module_75, NULL, 585, 585, 17, 68},
  {cont__compile_module_76, &frame__compile_module_75, 585, 585, 68, 68},
  {entry__compile_module_69, NULL, 582, 582, 17, 51},
  {cont__compile_module_70, &frame__compile_module_69, 581, 583, 15, 68},
  {cont__compile_module_74, &frame__compile_module_69, 580, 585, 13, 69},
  {entry__compile_module_58, NULL, 571, 571, 9, 30},
  {cont__compile_module_59, &frame__compile_module_58, 572, 572, 9, 32},
  {cont__compile_module_60, &frame__compile_module_58, 575, 575, 13, 31},
  {cont__compile_module_61, &frame__compile_module_58, 574, 576, 11, 70},
  {cont__compile_module_66, &frame__compile_module_58, 573, 585, 9, 71},
  {entry__compile_module_2, NULL, 537, 553, 5, 61},
  {cont__compile_module_29, &frame__compile_module_2, 554, 554, 5, 48},
  {cont__compile_module_30, &frame__compile_module_2, 555, 555, 5, 28},
  {cont__compile_module_31, &frame__compile_module_2, 556, 556, 5, 48},
  {cont__compile_module_34, &frame__compile_module_2, 557, 557, 5, 21},
  {cont__compile_module_41, &frame__compile_module_2, 558, 585, 5, 73},
  {cont__compile_module_77, &frame__compile_module_2, 586, 586, 5, 63},
  {entry__compile_module_80, NULL, 590, 591, 11, 56},
  {cont__compile_module_83, &frame__compile_module_80, 590, 591, 5, 56},
  {entry__compile_module_96, NULL, 598, 598, 51, 75},
  {cont__compile_module_97, &frame__compile_module_96, 598, 598, 32, 75},
  {cont__compile_module_98, &frame__compile_module_96, 598, 598, 75, 75},
  {entry__compile_module_91, NULL, 597, 597, 59, 59},
  {cont__compile_module_92, &frame__compile_module_91, 597, 597, 30, 60},
  {cont__compile_module_93, &frame__compile_module_91, 597, 597, 25, 61},
  {cont__compile_module_94, &frame__compile_module_91, 597, 597, 7, 61},
  {cont__compile_module_95, &frame__compile_module_91, 598, 598, 7, 75},
  {entry__compile_module_104, NULL, 605, 605, 37, 60},
  {cont__compile_module_105, &frame__compile_module_104, 605, 605, 37, 60},
  {entry__compile_module_107, NULL, 607, 607, 35, 35},
  {entry__compile_module_101, NULL, 604, 604, 11, 47},
  {cont__compile_module_102, &frame__compile_module_101, 605, 605, 14, 32},
  {cont__compile_module_103, &frame__compile_module_101, 605, 605, 14, 60},
  {cont__compile_module_106, &frame__compile_module_101, 605, 607, 11, 35},
  {entry__compile_module_109, NULL, 611, 611, 13, 37},
  {cont__compile_module_110, &frame__compile_module_109, 612, 612, 13, 32},
  {cont__compile_module_111, &frame__compile_module_109, 609, 612, 11, 32},
  {entry__compile_module_100, NULL, 603, 607, 9, 36},
  {cont__compile_module_108, &frame__compile_module_100, 608, 612, 9, 33},
  {entry__compile_module_118, NULL, 620, 620, 39, 62},
  {cont__compile_module_119, &frame__compile_module_118, 620, 620, 39, 62},
  {entry__compile_module_121, NULL, 622, 622, 37, 37},
  {entry__compile_module_115, NULL, 619, 619, 13, 77},
  {cont__compile_module_116, &frame__compile_module_115, 620, 620, 16, 34},
  {cont__compile_module_117, &frame__compile_module_115, 620, 620, 16, 62},
  {cont__compile_module_120, &frame__compile_module_115, 620, 622, 13, 37},
  {entry__compile_module_124, NULL, 624, 624, 32, 53},
  {cont__compile_module_125, &frame__compile_module_124, 624, 624, 13, 65},
  {cont__compile_module_126, &frame__compile_module_124, 625, 625, 13, 39},
  {cont__compile_module_127, &frame__compile_module_124, 626, 626, 13, 35},
  {cont__compile_module_128, &frame__compile_module_124, 626, 626, 38, 38},
  {entry__compile_module_114, NULL, 618, 622, 11, 38},
  {cont__compile_module_122, &frame__compile_module_114, 623, 623, 14, 37},
  {cont__compile_module_123, &frame__compile_module_114, 623, 626, 11, 38},
  {entry__compile_module_135, NULL, 631, 631, 40, 69},
  {cont__compile_module_137, &frame__compile_module_135, 631, 631, 69, 69},
  {entry__compile_module_134, NULL, 631, 631, 13, 69},
  {entry__compile_module_130, NULL, 628, 628, 11, 61},
  {cont__compile_module_131, &frame__compile_module_130, 629, 629, 11, 38},
  {cont__compile_module_132, &frame__compile_module_130, 630, 630, 14, 33},
  {cont__compile_module_133, &frame__compile_module_130, 630, 631, 11, 69},
  {cont__compile_module_138, &frame__compile_module_130, 632, 632, 11, 39},
  {cont__compile_module_139, &frame__compile_module_130, 632, 632, 39, 39},
  {entry__compile_module_113, NULL, 615, 626, 9, 39},
  {cont__compile_module_129, &frame__compile_module_113, 627, 632, 9, 39},
  {entry__compile_module_99, NULL, 600, 612, 7, 34},
  {cont__compile_module_112, &frame__compile_module_99, 613, 632, 7, 40},
  {entry__compile_module_1, NULL, 588, 588, 3, 40},
  {cont__compile_module_78, &frame__compile_module_1, 589, 589, 10, 28},
  {cont__compile_module_79, &frame__compile_module_1, 589, 591, 3, 57},
  {cont__compile_module_84, &frame__compile_module_1, 592, 592, 3, 39},
  {cont__compile_module_86, &frame__compile_module_1, 593, 593, 6, 24},
  {cont__compile_module_87, &frame__compile_module_1, 593, 593, 3, 31},
  {cont__compile_module_88, &frame__compile_module_1, 594, 594, 3, 22},
  {cont__compile_module_89, &frame__compile_module_1, 596, 596, 5, 21},
  {cont__compile_module_90, &frame__compile_module_1, 595, 632, 3, 42},
  {cont__compile_module_140, &frame__compile_module_1, 632, 632, 42, 42},
  {entry__compile_modules_4, NULL, 641, 641, 21, 41},
  {cont__compile_modules_5, &frame__compile_modules_4, 641, 641, 43, 67},
  {cont__compile_modules_6, &frame__compile_modules_4, 641, 641, 5, 67},
  {entry__compile_modules_8, NULL, 643, 643, 20, 40},
  {cont__compile_modules_9, &frame__compile_modules_8, 643, 643, 42, 66},
  {cont__compile_modules_10, &frame__compile_modules_8, 643, 643, 5, 66},
  {entry__compile_modules_1, NULL, 639, 639, 47, 66},
  {cont__compile_modules_2, &frame__compile_modules_1, 639, 639, 3, 66},
  {cont__compile_modules_3, &frame__compile_modules_1, 640, 641, 3, 67},
  {cont__compile_modules_7, &frame__compile_modules_1, 642, 643, 3, 66},
  {entry__show_file_list_6, NULL, 652, 652, 34, 58},
  {cont__show_file_list_8, &frame__show_file_list_6, 652, 652, 25, 58},
  {entry__show_file_list_2, NULL, 651, 651, 5, 40},
  {cont__show_file_list_4, &frame__show_file_list_2, 652, 652, 8, 22},
  {cont__show_file_list_5, &frame__show_file_list_2, 652, 652, 5, 58},
  {cont__show_file_list_9, &frame__show_file_list_2, 653, 653, 40, 57},
  {cont__show_file_list_10, &frame__show_file_list_2, 653, 653, 5, 57},
  {cont__show_file_list_12, &frame__show_file_list_2, 654, 654, 35, 54},
  {cont__show_file_list_13, &frame__show_file_list_2, 654, 654, 5, 54},
  {entry__show_file_list_1, NULL, 650, 654, 3, 54},
  {entry__library_paths_and_file_list_7, NULL, 663, 663, 60, 70},
  {cont__library_paths_and_file_list_9, &frame__library_paths_and_file_list_7, 663, 663, 40, 70},
  {cont__library_paths_and_file_list_10, &frame__library_paths_and_file_list_7, 663, 663, 70, 70},
  {entry__library_paths_and_file_list_5, NULL, 663, 663, 14, 30},
  {cont__library_paths_and_file_list_6, &frame__library_paths_and_file_list_5, 663, 663, 5, 70},
  {entry__library_paths_and_file_list_12, NULL, 664, 664, 54, 77},
  {cont__library_paths_and_file_list_13, &frame__library_paths_and_file_list_12, 664, 664, 27, 77},
  {entry__library_paths_and_file_list_16, NULL, 665, 665, 30, 54},
  {cont__library_paths_and_file_list_17, &frame__library_paths_and_file_list_16, 665, 665, 54, 54},
  {entry__library_paths_and_file_list_26, NULL, 674, 674, 31, 60},
  {cont__library_paths_and_file_list_29, &frame__library_paths_and_file_list_26, 674, 674, 28, 60},
  {entry__library_paths_and_file_list_30, NULL, 675, 675, 16, 38},
  {cont__library_paths_and_file_list_32, &frame__library_paths_and_file_list_30, 675, 675, 13, 38},
  {entry__library_paths_and_file_list_21, NULL, 673, 673, 13, 30},
  {cont__library_paths_and_file_list_22, &frame__library_paths_and_file_list_21, 674, 674, 13, 26},
  {cont__library_paths_and_file_list_25, &frame__library_paths_and_file_list_21, 672, 675, 11, 37},
  {cont__library_paths_and_file_list_33, &frame__library_paths_and_file_list_21, 671, 675, 9, 39},
  {entry__library_paths_and_file_list_36, NULL, 679, 679, 25, 44},
  {cont__library_paths_and_file_list_37, &frame__library_paths_and_file_list_36, 679, 679, 52, 71},
  {cont__library_paths_and_file_list_38, &frame__library_paths_and_file_list_36, 679, 679, 16, 73},
  {cont__library_paths_and_file_list_39, &frame__library_paths_and_file_list_36, 679, 680, 13, 26},
  {entry__library_paths_and_file_list_40, NULL, 681, 681, 16, 29},
  {cont__library_paths_and_file_list_41, &frame__library_paths_and_file_list_40, 681, 681, 13, 29},
  {entry__library_paths_and_file_list_34, NULL, 678, 678, 13, 34},
  {cont__library_paths_and_file_list_35, &frame__library_paths_and_file_list_34, 677, 681, 11, 28},
  {cont__library_paths_and_file_list_42, &frame__library_paths_and_file_list_34, 676, 681, 9, 30},
  {entry__library_paths_and_file_list_19, NULL, 670, 670, 9, 35},
  {cont__library_paths_and_file_list_20, &frame__library_paths_and_file_list_19, 669, 681, 7, 30},
  {cont__library_paths_and_file_list_43, &frame__library_paths_and_file_list_19, 667, 681, 5, 32},
  {cont__library_paths_and_file_list_44, &frame__library_paths_and_file_list_19, 681, 681, 33, 33},
  {entry__library_paths_and_file_list_1, NULL, 657, 657, 3, 16},
  {cont__library_paths_and_file_list_2, &frame__library_paths_and_file_list_1, 661, 661, 3, 39},
  {cont__library_paths_and_file_list_3, &frame__library_paths_and_file_list_1, 662, 662, 6, 21},
  {cont__library_paths_and_file_list_4, &frame__library_paths_and_file_list_1, 662, 663, 3, 70},
  {cont__library_paths_and_file_list_11, &frame__library_paths_and_file_list_1, 664, 664, 3, 77},
  {cont__library_paths_and_file_list_15, &frame__library_paths_and_file_list_1, 665, 665, 3, 54},
  {cont__library_paths_and_file_list_18, &frame__library_paths_and_file_list_1, 666, 681, 3, 33},
  {cont__library_paths_and_file_list_45, &frame__library_paths_and_file_list_1, 682, 682, 24, 57},
  {cont__library_paths_and_file_list_46, &frame__library_paths_and_file_list_1, 682, 682, 3, 57},
  {entry__create_imports_9, NULL, 692, 692, 51, 64},
  {cont__create_imports_10, &frame__create_imports_9, 692, 692, 51, 64},
  {entry__create_imports_7, NULL, 692, 692, 37, 46},
  {cont__create_imports_8, &frame__create_imports_7, 692, 692, 37, 64},
  {cont__create_imports_11, &frame__create_imports_7, 692, 692, 37, 64},
  {entry__create_imports_29, NULL, 703, 703, 25, 59},
  {cont__create_imports_31, &frame__create_imports_29, 703, 703, 21, 60},
  {cont__create_imports_32, &frame__create_imports_29, 703, 703, 21, 60},
  {entry__create_imports_25, NULL, 702, 702, 25, 58},
  {cont__create_imports_27, &frame__create_imports_25, 702, 702, 21, 59},
  {cont__create_imports_28, &frame__create_imports_25, 703, 703, 21, 60},
  {cont__create_imports_33, &frame__create_imports_25, },
  {entry__create_imports_38, NULL, 707, 707, 46, 80},
  {cont__create_imports_39, &frame__create_imports_38, 707, 707, 46, 80},
  {entry__create_imports_41, NULL, 709, 709, 44, 74},
  {cont__create_imports_42, &frame__create_imports_41, 709, 709, 23, 74},
  {entry__create_imports_35, NULL, 707, 707, 21, 34},
  {cont__create_imports_36, &frame__create_imports_35, 707, 707, 21, 41},
  {cont__create_imports_37, &frame__create_imports_35, 707, 707, 21, 80},
  {cont__create_imports_40, &frame__create_imports_35, 706, 709, 19, 75},
  {entry__create_imports_49, NULL, 712, 712, 60, 60},
  {cont__create_imports_50, &frame__create_imports_49, 712, 712, 44, 61},
  {cont__create_imports_51, &frame__create_imports_49, 712, 712, 23, 61},
  {entry__create_imports_46, NULL, 711, 711, 35, 62},
  {cont__create_imports_47, &frame__create_imports_46, 711, 711, 35, 67},
  {cont__create_imports_48, &frame__create_imports_46, 711, 712, 21, 61},
  {entry__create_imports_43, NULL, 710, 710, 22, 62},
  {cont__create_imports_45, &frame__create_imports_43, 710, 712, 19, 62},
  {entry__create_imports_52, NULL, 714, 714, 21, 52},
  {entry__create_imports_54, NULL, 715, 715, 31, 45},
  {entry__create_imports_21, NULL, 701, 701, 21, 34},
  {cont__create_imports_22, &frame__create_imports_21, 701, 701, 21, 41},
  {cont__create_imports_23, &frame__create_imports_21, 701, 701, 21, 41},
  {cont__create_imports_24, &frame__create_imports_21, 699, 703, 17, 61},
  {cont__create_imports_34, &frame__create_imports_21, 705, 714, 17, 53},
  {cont__create_imports_53, &frame__create_imports_21, 715, 715, 17, 45},
  {cont__create_imports_56, &frame__create_imports_21, 716, 716, 17, 33},
  {entry__create_imports_17, NULL, 696, 696, 15, 38},
  {cont__create_imports_18, &frame__create_imports_17, 697, 697, 15, 50},
  {cont__create_imports_19, &frame__create_imports_17, 698, 698, 18, 39},
  {cont__create_imports_20, &frame__create_imports_17, 698, 716, 15, 33},
  {entry__create_imports_13, NULL, 693, 693, 33, 37},
  {cont__create_imports_14, &frame__create_imports_13, 693, 693, 13, 38},
  {cont__create_imports_15, &frame__create_imports_13, 695, 695, 20, 42},
  {cont__create_imports_16, &frame__create_imports_13, 695, 716, 13, 34},
  {entry__create_imports_5, NULL, 692, 692, 18, 32},
  {cont__create_imports_6, &frame__create_imports_5, 692, 692, 18, 64},
  {cont__create_imports_12, &frame__create_imports_5, 692, 716, 11, 35},
  {entry__create_imports_59, NULL, 718, 718, 33, 42},
  {cont__create_imports_60, &frame__create_imports_59, 718, 718, 33, 42},
  {entry__create_imports_62, NULL, 718, 718, 50, 50},
  {entry__create_imports_57, NULL, 718, 718, 14, 28},
  {cont__create_imports_58, &frame__create_imports_57, 718, 718, 14, 42},
  {cont__create_imports_61, &frame__create_imports_57, 718, 718, 11, 50},
  {entry__create_imports_3, NULL, 691, 691, 9, 20},
  {cont__create_imports_4, &frame__create_imports_3, 690, 718, 7, 51},
  {entry__create_imports_2, NULL, 689, 718, 5, 52},
  {entry__create_imports_63, NULL, 720, 720, 28, 54},
  {entry__create_imports_74, NULL, 725, 725, 22, 59},
  {entry__create_imports_1, NULL, 720, 720, 3, 54},
  {cont__create_imports_64, &frame__create_imports_1, 721, 721, 3, 49},
  {cont__create_imports_66, &frame__create_imports_1, 722, 722, 3, 18},
  {cont__create_imports_67, &frame__create_imports_1, 723, 723, 3, 15},
  {cont__create_imports_68, &frame__create_imports_1, 724, 724, 22, 42},
  {cont__create_imports_69, &frame__create_imports_1, 724, 724, 22, 45},
  {cont__create_imports_70, &frame__create_imports_1, 724, 724, 48, 48},
  {cont__create_imports_71, &frame__create_imports_1, 724, 724, 9, 49},
  {cont__create_imports_72, &frame__create_imports_1, 724, 724, 3, 49},
  {cont__create_imports_73, &frame__create_imports_1, 725, 725, 3, 59},
  {entry__compile_exe_3, NULL, 728, 728, 32, 67},
  {entry__compile_exe_7, NULL, 730, 731, 5, 57},
  {entry__compile_exe_1, NULL, 728, 728, 6, 29},
  {cont__compile_exe_2, &frame__compile_exe_1, 728, 728, 3, 67},
  {cont__compile_exe_5, &frame__compile_exe_1, 729, 729, 10, 42},
  {cont__compile_exe_6, &frame__compile_exe_1, 729, 731, 3, 58},
  {cont__compile_exe_9, &frame__compile_exe_1, 733, 733, 3, 53},
  {cont__compile_exe_10, &frame__compile_exe_1, 734, 734, 46, 46},
  {cont__compile_exe_11, &frame__compile_exe_1, 734, 734, 3, 47},
  {cont__compile_exe_12, &frame__compile_exe_1, 735, 735, 3, 28},
  {cont__compile_exe_13, &frame__compile_exe_1, 735, 735, 28, 28},
  {entry__dump_source_or_check_2, NULL, 740, 740, 11, 29},
  {cont__dump_source_or_check_3, &frame__dump_source_or_check_2, 740, 740, 5, 29},
  {cont__dump_source_or_check_4, &frame__dump_source_or_check_2, 740, 740, 29, 29},
  {entry__dump_source_or_check_1, NULL, 738, 740, 3, 29},
  {entry__print_c_4, NULL, 744, 744, 41, 65},
  {cont__print_c_5, &frame__print_c_4, 744, 744, 34, 75},
  {cont__print_c_6, &frame__print_c_4, 744, 744, 75, 75},
  {entry__print_c_8, NULL, 746, 746, 48, 57},
  {cont__print_c_9, &frame__print_c_8, 746, 746, 59, 68},
  {cont__print_c_10, &frame__print_c_8, 746, 746, 7, 69},
  {cont__print_c_11, &frame__print_c_8, 747, 747, 13, 31},
  {cont__print_c_12, &frame__print_c_8, 747, 747, 7, 31},
  {cont__print_c_13, &frame__print_c_8, 747, 747, 31, 31},
  {entry__print_c_15, NULL, 748, 748, 28, 50},
  {entry__print_c_18, NULL, 750, 750, 24, 59},
  {entry__print_c_2, NULL, 744, 744, 8, 31},
  {cont__print_c_3, &frame__print_c_2, 744, 744, 5, 75},
  {cont__print_c_7, &frame__print_c_2, 745, 747, 5, 31},
  {cont__print_c_14, &frame__print_c_2, 748, 748, 5, 50},
  {cont__print_c_16, &frame__print_c_2, 749, 749, 5, 15},
  {cont__print_c_17, &frame__print_c_2, 750, 750, 5, 59},
  {entry__print_c_1, NULL, 743, 750, 3, 59},
  {entry__list_dependencies_5, NULL, 759, 759, 9, 43},
  {cont__list_dependencies_6, &frame__list_dependencies_5, 760, 760, 12, 28},
  {cont__list_dependencies_7, &frame__list_dependencies_5, 760, 760, 9, 34},
  {cont__list_dependencies_8, &frame__list_dependencies_5, 761, 761, 9, 21},
  {cont__list_dependencies_9, &frame__list_dependencies_5, 762, 762, 9, 64},
  {cont__list_dependencies_10, &frame__list_dependencies_5, 763, 763, 12, 23},
  {cont__list_dependencies_11, &frame__list_dependencies_5, 763, 763, 9, 29},
  {cont__list_dependencies_12, &frame__list_dependencies_5, 764, 764, 22, 22},
  {entry__list_dependencies_4, NULL, 758, 764, 7, 22},
  {cont__list_dependencies_13, &frame__list_dependencies_4, 764, 764, 22, 22},
  {entry__list_dependencies_3, NULL, 757, 764, 5, 23},
  {entry__list_dependencies_17, NULL, 768, 768, 19, 65},
  {entry__list_dependencies_16, NULL, 768, 768, 7, 65},
  {cont__list_dependencies_19, &frame__list_dependencies_16, 769, 769, 63, 63},
  {cont__list_dependencies_20, &frame__list_dependencies_16, 769, 769, 37, 64},
  {cont__list_dependencies_21, &frame__list_dependencies_16, 769, 769, 7, 64},
  {cont__list_dependencies_22, &frame__list_dependencies_16, 769, 769, 64, 64},
  {entry__list_dependencies_25, NULL, 772, 772, 21, 66},
  {entry__list_dependencies_24, NULL, 772, 772, 9, 66},
  {cont__list_dependencies_26, &frame__list_dependencies_24, 773, 773, 9, 44},
  {entry__list_dependencies_23, NULL, 771, 773, 7, 44},
  {cont__list_dependencies_27, &frame__list_dependencies_23, 774, 774, 7, 32},
  {cont__list_dependencies_29, &frame__list_dependencies_23, 775, 775, 7, 32},
  {cont__list_dependencies_31, &frame__list_dependencies_23, 776, 776, 7, 34},
  {entry__list_dependencies_35, NULL, 779, 779, 5, 40},
  {cont__list_dependencies_36, &frame__list_dependencies_35, 780, 780, 5, 32},
  {cont__list_dependencies_37, &frame__list_dependencies_35, 781, 781, 5, 20},
  {entry__list_dependencies_1, NULL, 753, 753, 3, 80},
  {cont__list_dependencies_2, &frame__list_dependencies_1, 754, 764, 3, 24},
  {cont__list_dependencies_14, &frame__list_dependencies_1, 766, 766, 5, 28},
  {cont__list_dependencies_15, &frame__list_dependencies_1, 765, 776, 3, 35},
  {cont__list_dependencies_33, &frame__list_dependencies_1, 777, 777, 3, 29},
  {cont__list_dependencies_34, &frame__list_dependencies_1, 778, 781, 3, 20},
  {entry__build_codeblocks_project_7, NULL, 788, 789, 14, 58},
  {cont__build_codeblocks_project_10, &frame__build_codeblocks_project_7, 788, 789, 7, 58},
  {entry__build_codeblocks_project_12, NULL, 790, 790, 17, 73},
  {entry__build_codeblocks_project_34, NULL, 822, 824, 21, 49},
  {cont__build_codeblocks_project_37, &frame__build_codeblocks_project_34, 822, 824, 7, 49},
  {cont__build_codeblocks_project_38, &frame__build_codeblocks_project_34, 824, 824, 50, 50},
  {entry__build_codeblocks_project_53, NULL, 844, 844, 7, 42},
  {cont__build_codeblocks_project_54, &frame__build_codeblocks_project_53, 845, 845, 7, 34},
  {cont__build_codeblocks_project_55, &frame__build_codeblocks_project_53, 850, 850, 44, 55},
  {cont__build_codeblocks_project_56, &frame__build_codeblocks_project_53, 846, 851, 21, 23},
  {cont__build_codeblocks_project_59, &frame__build_codeblocks_project_53, 846, 851, 7, 23},
  {cont__build_codeblocks_project_60, &frame__build_codeblocks_project_53, 851, 851, 24, 24},
  {entry__build_codeblocks_project_2, NULL, 785, 785, 5, 55},
  {cont__build_codeblocks_project_4, &frame__build_codeblocks_project_2, 786, 786, 5, 31},
  {cont__build_codeblocks_project_5, &frame__build_codeblocks_project_2, 787, 787, 8, 22},
  {cont__build_codeblocks_project_6, &frame__build_codeblocks_project_2, 787, 789, 5, 59},
  {cont__build_codeblocks_project_11, &frame__build_codeblocks_project_2, 790, 790, 5, 73},
  {cont__build_codeblocks_project_14, &frame__build_codeblocks_project_2, 791, 791, 5, 40},
  {cont__build_codeblocks_project_15, &frame__build_codeblocks_project_2, 792, 792, 5, 18},
  {cont__build_codeblocks_project_16, &frame__build_codeblocks_project_2, 793, 793, 49, 49},
  {cont__build_codeblocks_project_17, &frame__build_codeblocks_project_2, 793, 793, 15, 50},
  {cont__build_codeblocks_project_18, &frame__build_codeblocks_project_2, 793, 793, 5, 74},
  {cont__build_codeblocks_project_19, &frame__build_codeblocks_project_2, 794, 794, 5, 31},
  {cont__build_codeblocks_project_20, &frame__build_codeblocks_project_2, 795, 795, 30, 73},
  {cont__build_codeblocks_project_21, &frame__build_codeblocks_project_2, 795, 795, 5, 78},
  {cont__build_codeblocks_project_22, &frame__build_codeblocks_project_2, 796, 796, 5, 33},
  {cont__build_codeblocks_project_24, &frame__build_codeblocks_project_2, 797, 797, 5, 61},
  {cont__build_codeblocks_project_27, &frame__build_codeblocks_project_2, 798, 798, 5, 25},
  {cont__build_codeblocks_project_28, &frame__build_codeblocks_project_2, 800, 820, 19, 22},
  {cont__build_codeblocks_project_32, &frame__build_codeblocks_project_2, 800, 820, 5, 22},
  {cont__build_codeblocks_project_33, &frame__build_codeblocks_project_2, 821, 824, 5, 50},
  {cont__build_codeblocks_project_39, &frame__build_codeblocks_project_2, 835, 835, 42, 53},
  {cont__build_codeblocks_project_40, &frame__build_codeblocks_project_2, 838, 838, 42, 53},
  {cont__build_codeblocks_project_41, &frame__build_codeblocks_project_2, 841, 841, 42, 53},
  {cont__build_codeblocks_project_42, &frame__build_codeblocks_project_2, 825, 842, 19, 21},
  {cont__build_codeblocks_project_51, &frame__build_codeblocks_project_2, 825, 842, 5, 21},
  {cont__build_codeblocks_project_52, &frame__build_codeblocks_project_2, 843, 851, 5, 24},
  {cont__build_codeblocks_project_61, &frame__build_codeblocks_project_2, 852, 858, 5, 32},
  {cont__build_codeblocks_project_63, &frame__build_codeblocks_project_2, 859, 859, 5, 25},
  {entry__build_codeblocks_project_1, NULL, 784, 859, 3, 25},
  {entry__build_library_4, NULL, 862, 862, 26, 56},
  {entry__build_library_9, NULL, 868, 868, 29, 45},
  {cont__build_library_10, &frame__build_library_9, 868, 868, 9, 45},
  {cont__build_library_11, &frame__build_library_9, 868, 868, 45, 45},
  {entry__build_library_7, NULL, 866, 866, 7, 41},
  {cont__build_library_8, &frame__build_library_7, 867, 868, 7, 45},
  {cont__build_library_12, &frame__build_library_7, 869, 869, 7, 41},
  {entry__build_library_17, NULL, 874, 874, 29, 50},
  {cont__build_library_18, &frame__build_library_17, 874, 874, 29, 55},
  {cont__build_library_19, &frame__build_library_17, 874, 874, 9, 56},
  {cont__build_library_20, &frame__build_library_17, 874, 874, 56, 56},
  {entry__build_library_27, NULL, 882, 882, 53, 66},
  {cont__build_library_28, &frame__build_library_27, 882, 882, 14, 67},
  {cont__build_library_30, &frame__build_library_27, 882, 882, 11, 67},
  {entry__build_library_31, NULL, 884, 884, 53, 67},
  {cont__build_library_33, &frame__build_library_31, 884, 884, 14, 68},
  {cont__build_library_34, &frame__build_library_31, 884, 884, 11, 68},
  {entry__build_library_35, NULL, 886, 886, 53, 69},
  {cont__build_library_37, &frame__build_library_35, 886, 886, 14, 70},
  {cont__build_library_38, &frame__build_library_35, 886, 886, 11, 70},
  {entry__build_library_39, NULL, 887, 887, 53, 66},
  {cont__build_library_40, &frame__build_library_39, 887, 887, 14, 67},
  {cont__build_library_41, &frame__build_library_39, 887, 887, 11, 67},
  {entry__build_library_45, NULL, 889, 889, 19, 56},
  {entry__build_library_54, NULL, 896, 896, 38, 63},
  {cont__build_library_55, &frame__build_library_54, 896, 896, 13, 63},
  {cont__build_library_56, &frame__build_library_54, 896, 896, 13, 63},
  {entry__build_library_58, NULL, 898, 898, 25, 25},
  {entry__build_library_51, NULL, 892, 892, 9, 32},
  {cont__build_library_52, &frame__build_library_51, 895, 895, 13, 29},
  {cont__build_library_53, &frame__build_library_51, 894, 896, 11, 62},
  {cont__build_library_57, &frame__build_library_51, 893, 898, 9, 26},
  {entry__build_library_61, NULL, 900, 900, 21, 54},
  {entry__build_library_72, NULL, 911, 911, 35, 47},
  {cont__build_library_73, &frame__build_library_72, 911, 911, 29, 47},
  {entry__build_library_66, NULL, 907, 907, 15, 76},
  {cont__build_library_68, &frame__build_library_66, 908, 908, 15, 43},
  {cont__build_library_69, &frame__build_library_66, 904, 910, 13, 26},
  {cont__build_library_71, &frame__build_library_66, 911, 911, 13, 47},
  {entry__build_library_79, NULL, 920, 920, 35, 47},
  {cont__build_library_80, &frame__build_library_79, 920, 920, 29, 47},
  {entry__build_library_74, NULL, 916, 916, 15, 43},
  {cont__build_library_75, &frame__build_library_74, 917, 917, 15, 30},
  {cont__build_library_77, &frame__build_library_74, 913, 919, 13, 26},
  {cont__build_library_78, &frame__build_library_74, 920, 920, 13, 47},
  {entry__build_library_88, NULL, 931, 931, 35, 47},
  {cont__build_library_89, &frame__build_library_88, 931, 931, 29, 47},
  {entry__build_library_81, NULL, 925, 926, 15, 86},
  {cont__build_library_83, &frame__build_library_81, 927, 927, 15, 43},
  {cont__build_library_84, &frame__build_library_81, 928, 928, 15, 30},
  {cont__build_library_85, &frame__build_library_81, 922, 930, 13, 26},
  {cont__build_library_87, &frame__build_library_81, 931, 931, 13, 47},
  {entry__build_library_93, NULL, 939, 939, 35, 47},
  {cont__build_library_94, &frame__build_library_93, 939, 939, 29, 47},
  {entry__build_library_90, NULL, 936, 936, 15, 43},
  {cont__build_library_91, &frame__build_library_90, 933, 938, 13, 26},
  {cont__build_library_92, &frame__build_library_90, 939, 939, 13, 47},
  {entry__build_library_60, NULL, 900, 900, 9, 54},
  {cont__build_library_63, &frame__build_library_60, 902, 902, 11, 28},
  {cont__build_library_64, &frame__build_library_60, 903, 903, 11, 24},
  {cont__build_library_65, &frame__build_library_60, 901, 939, 9, 48},
  {entry__build_library_13, NULL, 872, 872, 7, 56},
  {cont__build_library_15, &frame__build_library_13, 873, 873, 10, 38},
  {cont__build_library_16, &frame__build_library_13, 873, 874, 7, 56},
  {cont__build_library_21, &frame__build_library_13, 875, 875, 7, 45},
  {cont__build_library_22, &frame__build_library_13, 876, 876, 56, 56},
  {cont__build_library_23, &frame__build_library_13, 876, 876, 7, 57},
  {cont__build_library_24, &frame__build_library_13, 880, 880, 11, 28},
  {cont__build_library_25, &frame__build_library_13, 881, 881, 11, 24},
  {cont__build_library_26, &frame__build_library_13, 878, 887, 7, 68},
  {cont__build_library_44, &frame__build_library_13, 889, 889, 7, 56},
  {cont__build_library_47, &frame__build_library_13, 890, 890, 63, 63},
  {cont__build_library_48, &frame__build_library_13, 890, 890, 37, 64},
  {cont__build_library_49, &frame__build_library_13, 890, 890, 7, 64},
  {cont__build_library_50, &frame__build_library_13, 891, 898, 7, 27},
  {cont__build_library_59, &frame__build_library_13, 899, 939, 7, 49},
  {entry__build_library_1, NULL, 862, 862, 6, 23},
  {cont__build_library_3, &frame__build_library_1, 862, 862, 3, 56},
  {cont__build_library_6, &frame__build_library_1, 864, 939, 3, 51},
  {cont__build_library_95, &frame__build_library_1, 939, 939, 51, 51},
  {entry__maybe_compile_c_file_6, NULL, 946, 947, 11, 42},
  {cont__maybe_compile_c_file_9, &frame__maybe_compile_c_file_6, 946, 947, 5, 42},
  {entry__maybe_compile_c_file_13, NULL, 952, 952, 38, 65},
  {cont__maybe_compile_c_file_14, &frame__maybe_compile_c_file_13, 952, 952, 7, 34},
  {cont__maybe_compile_c_file_15, &frame__maybe_compile_c_file_13, 952, 952, 7, 65},
  {cont__maybe_compile_c_file_16, &frame__maybe_compile_c_file_13, 952, 952, 7, 65},
  {entry__maybe_compile_c_file_19, NULL, 954, 954, 28, 65},
  {cont__maybe_compile_c_file_21, &frame__maybe_compile_c_file_19, 954, 954, 19, 65},
  {entry__maybe_compile_c_file_18, NULL, 954, 954, 7, 65},
  {cont__maybe_compile_c_file_22, &frame__maybe_compile_c_file_18, 955, 955, 7, 37},
  {entry__maybe_compile_c_file_1, NULL, 942, 942, 3, 35},
  {cont__maybe_compile_c_file_2, &frame__maybe_compile_c_file_1, 943, 943, 3, 35},
  {cont__maybe_compile_c_file_3, &frame__maybe_compile_c_file_1, 944, 944, 3, 26},
  {cont__maybe_compile_c_file_4, &frame__maybe_compile_c_file_1, 945, 945, 6, 24},
  {cont__maybe_compile_c_file_5, &frame__maybe_compile_c_file_1, 945, 947, 3, 43},
  {cont__maybe_compile_c_file_10, &frame__maybe_compile_c_file_1, 948, 948, 3, 26},
  {cont__maybe_compile_c_file_11, &frame__maybe_compile_c_file_1, 951, 951, 7, 25},
  {cont__maybe_compile_c_file_12, &frame__maybe_compile_c_file_1, 950, 952, 5, 64},
  {cont__maybe_compile_c_file_17, &frame__maybe_compile_c_file_1, 949, 955, 3, 38},
  {entry__format_number_11, NULL, 971, 971, 39, 41},
  {cont__format_number_12, &frame__format_number_11, 971, 971, 36, 41},
  {cont__format_number_13, &frame__format_number_11, 971, 971, 28, 43},
  {cont__format_number_15, &frame__format_number_11, 971, 971, 21, 48},
  {cont__format_number_16, &frame__format_number_11, 971, 971, 48, 48},
  {entry__format_number_6, NULL, 970, 970, 13, 26},
  {cont__format_number_7, &frame__format_number_6, 970, 970, 9, 28},
  {cont__format_number_8, &frame__format_number_6, 971, 971, 16, 18},
  {cont__format_number_9, &frame__format_number_6, 971, 971, 12, 18},
  {cont__format_number_10, &frame__format_number_6, 971, 971, 9, 48},
  {cont__format_number_17, &frame__format_number_6, 972, 972, 9, 13},
  {entry__format_number_4, NULL, 969, 969, 10, 19},
  {cont__format_number_5, &frame__format_number_4, 969, 972, 7, 13},
  {entry__format_number_3, NULL, 968, 972, 5, 14},
  {cont__format_number_18, &frame__format_number_3, 972, 972, 14, 14},
  {entry__format_number_21, NULL, 975, 975, 27, 30},
  {cont__format_number_22, &frame__format_number_21, 975, 975, 19, 31},
  {cont__format_number_24, &frame__format_number_21, 975, 975, 7, 31},
  {cont__format_number_25, &frame__format_number_21, 975, 975, 31, 31},
  {entry__format_number_28, NULL, 977, 977, 33, 36},
  {cont__format_number_29, &frame__format_number_28, 977, 977, 33, 38},
  {cont__format_number_30, &frame__format_number_28, 977, 977, 33, 39},
  {cont__format_number_31, &frame__format_number_28, 977, 977, 18, 39},
  {cont__format_number_32, &frame__format_number_28, 977, 977, 39, 39},
  {entry__format_number_26, NULL, 977, 977, 10, 15},
  {cont__format_number_27, &frame__format_number_26, 977, 977, 7, 39},
  {entry__format_number_1, NULL, 965, 965, 3, 16},
  {cont__format_number_2, &frame__format_number_1, 967, 972, 3, 15},
  {cont__format_number_19, &frame__format_number_1, 974, 974, 5, 10},
  {cont__format_number_20, &frame__format_number_1, 973, 977, 3, 40},
  {cont__format_number_33, &frame__format_number_1, 978, 978, 3, 8},
  {entry__sim2c__write_timing_info_4, NULL, 984, 984, 37, 37},
  {cont__sim2c__write_timing_info_5, &frame__sim2c__write_timing_info_4, 984, 984, 7, 37},
  {cont__sim2c__write_timing_info_6, &frame__sim2c__write_timing_info_4, 990, 990, 20, 41},
  {cont__sim2c__write_timing_info_7, &frame__sim2c__write_timing_info_4, 990, 990, 17, 41},
  {cont__sim2c__write_timing_info_8, &frame__sim2c__write_timing_info_4, 990, 990, 9, 42},
  {cont__sim2c__write_timing_info_9, &frame__sim2c__write_timing_info_4, 991, 991, 23, 29},
  {cont__sim2c__write_timing_info_10, &frame__sim2c__write_timing_info_4, 991, 991, 9, 34},
  {cont__sim2c__write_timing_info_11, &frame__sim2c__write_timing_info_4, 985, 992, 7, 12},
  {entry__sim2c__write_timing_info_13, NULL, 994, 994, 47, 53},
  {cont__sim2c__write_timing_info_14, &frame__sim2c__write_timing_info_13, 994, 994, 33, 58},
  {cont__sim2c__write_timing_info_15, &frame__sim2c__write_timing_info_13, 994, 994, 7, 63},
  {entry__sim2c__write_timing_info_1, NULL, 981, 981, 3, 23},
  {cont__sim2c__write_timing_info_2, &frame__sim2c__write_timing_info_1, 983, 983, 5, 23},
  {cont__sim2c__write_timing_info_3, &frame__sim2c__write_timing_info_1, 982, 994, 3, 64},
  {cont__sim2c__write_timing_info_17, &frame__sim2c__write_timing_info_1, 995, 995, 3, 19},
  {cont__sim2c__write_timing_info_18, &frame__sim2c__write_timing_info_1, 995, 995, 19, 19},
  {entry__build_executable_5, NULL, 1011, 1011, 12, 38},
  {cont__build_executable_7, &frame__build_executable_5, 1011, 1011, 9, 38},
  {entry__build_executable_8, NULL, 1012, 1012, 9, 23},
  {entry__build_executable_10, NULL, 1014, 1014, 17, 57},
  {entry__build_executable_20, NULL, 1025, 1025, 42, 69},
  {cont__build_executable_21, &frame__build_executable_20, 1025, 1025, 9, 38},
  {cont__build_executable_22, &frame__build_executable_20, 1025, 1025, 9, 69},
  {cont__build_executable_23, &frame__build_executable_20, 1025, 1025, 9, 69},
  {entry__build_executable_18, NULL, 1024, 1024, 9, 27},
  {cont__build_executable_19, &frame__build_executable_18, 1025, 1025, 9, 69},
  {cont__build_executable_24, &frame__build_executable_18, },
  {entry__build_executable_29, NULL, 1028, 1028, 21, 61},
  {entry__build_executable_32, NULL, 1029, 1029, 41, 59},
  {cont__build_executable_33, &frame__build_executable_32, 1029, 1029, 35, 64},
  {entry__build_executable_35, NULL, 1030, 1030, 32, 54},
  {entry__build_executable_39, NULL, 1032, 1032, 28, 64},
  {entry__build_executable_43, NULL, 1034, 1034, 28, 67},
  {entry__build_executable_26, NULL, 1027, 1027, 55, 67},
  {cont__build_executable_27, &frame__build_executable_26, 1027, 1027, 9, 67},
  {cont__build_executable_28, &frame__build_executable_26, 1028, 1028, 9, 61},
  {cont__build_executable_31, &frame__build_executable_26, 1029, 1029, 9, 64},
  {cont__build_executable_34, &frame__build_executable_26, 1030, 1030, 9, 54},
  {cont__build_executable_36, &frame__build_executable_26, 1031, 1031, 25, 37},
  {cont__build_executable_37, &frame__build_executable_26, 1031, 1031, 9, 37},
  {cont__build_executable_38, &frame__build_executable_26, 1032, 1032, 9, 64},
  {cont__build_executable_41, &frame__build_executable_26, 1033, 1033, 9, 39},
  {cont__build_executable_42, &frame__build_executable_26, 1034, 1034, 9, 67},
  {cont__build_executable_45, &frame__build_executable_26, 1034, 1034, 67, 67},
  {entry__build_executable_50, NULL, 1041, 1041, 44, 71},
  {cont__build_executable_51, &frame__build_executable_50, 1041, 1041, 13, 40},
  {cont__build_executable_52, &frame__build_executable_50, 1041, 1041, 13, 71},
  {cont__build_executable_53, &frame__build_executable_50, 1041, 1041, 13, 71},
  {entry__build_executable_55, NULL, 1043, 1043, 13, 43},
  {entry__build_executable_56, NULL, 1045, 1045, 13, 64},
  {cont__build_executable_57, &frame__build_executable_56, 1045, 1045, 64, 64},
  {entry__build_executable_46, NULL, 1036, 1036, 9, 30},
  {cont__build_executable_47, &frame__build_executable_46, 1037, 1037, 9, 32},
  {cont__build_executable_48, &frame__build_executable_46, 1040, 1040, 13, 31},
  {cont__build_executable_49, &frame__build_executable_46, 1039, 1041, 11, 70},
  {cont__build_executable_54, &frame__build_executable_46, 1038, 1045, 9, 65},
  {entry__build_executable_65, NULL, 1050, 1050, 11, 39},
  {entry__build_executable_60, NULL, 1049, 1049, 9, 62},
  {cont__build_executable_64, &frame__build_executable_60, 1048, 1050, 7, 40},
  {entry__build_executable_72, NULL, 1058, 1058, 38, 63},
  {cont__build_executable_73, &frame__build_executable_72, 1058, 1058, 13, 63},
  {cont__build_executable_74, &frame__build_executable_72, 1058, 1058, 13, 63},
  {entry__build_executable_70, NULL, 1057, 1057, 13, 45},
  {cont__build_executable_71, &frame__build_executable_70, 1056, 1058, 11, 62},
  {cont__build_executable_75, &frame__build_executable_70, 1056, 1058, 11, 62},
  {entry__build_executable_77, NULL, 1060, 1060, 23, 23},
  {entry__build_executable_67, NULL, 1052, 1052, 7, 30},
  {cont__build_executable_68, &frame__build_executable_67, 1055, 1055, 11, 27},
  {cont__build_executable_69, &frame__build_executable_67, 1054, 1058, 9, 63},
  {cont__build_executable_76, &frame__build_executable_67, 1053, 1060, 7, 24},
  {entry__build_executable_81, NULL, 1063, 1063, 28, 75},
  {cont__build_executable_83, &frame__build_executable_81, 1063, 1063, 75, 75},
  {entry__build_executable_86, NULL, 1066, 1066, 23, 58},
  {entry__build_executable_93, NULL, 1074, 1074, 33, 45},
  {cont__build_executable_94, &frame__build_executable_93, 1074, 1074, 27, 45},
  {entry__build_executable_85, NULL, 1066, 1066, 11, 58},
  {cont__build_executable_88, &frame__build_executable_85, 1067, 1073, 11, 24},
  {cont__build_executable_92, &frame__build_executable_85, 1074, 1074, 11, 45},
  {entry__build_executable_96, NULL, 1076, 1076, 23, 51},
  {entry__build_executable_101, NULL, 1081, 1081, 33, 55},
  {cont__build_executable_103, &frame__build_executable_101, 1081, 1081, 30, 55},
  {entry__build_executable_104, NULL, 1082, 1082, 18, 33},
  {cont__build_executable_105, &frame__build_executable_104, 1082, 1082, 15, 33},
  {entry__build_executable_108, NULL, 1085, 1085, 33, 45},
  {cont__build_executable_109, &frame__build_executable_108, 1085, 1085, 27, 45},
  {entry__build_executable_95, NULL, 1076, 1076, 11, 51},
  {cont__build_executable_98, &frame__build_executable_95, 1080, 1080, 15, 32},
  {cont__build_executable_99, &frame__build_executable_95, 1081, 1081, 15, 28},
  {cont__build_executable_100, &frame__build_executable_95, 1079, 1082, 13, 32},
  {cont__build_executable_106, &frame__build_executable_95, 1077, 1084, 11, 24},
  {cont__build_executable_107, &frame__build_executable_95, 1085, 1085, 11, 45},
  {entry__build_executable_79, NULL, 1062, 1062, 7, 52},
  {cont__build_executable_80, &frame__build_executable_79, 1063, 1063, 7, 75},
  {cont__build_executable_84, &frame__build_executable_79, 1064, 1085, 7, 46},
  {entry__build_executable_113, NULL, 1087, 1087, 24, 41},
  {cont__build_executable_114, &frame__build_executable_113, 1087, 1087, 24, 41},
  {entry__build_executable_118, NULL, 1091, 1091, 11, 25},
  {entry__build_executable_119, NULL, 1092, 1092, 14, 38},
  {cont__build_executable_120, &frame__build_executable_119, 1092, 1092, 11, 38},
  {entry__build_executable_116, NULL, 1090, 1090, 11, 39},
  {cont__build_executable_117, &frame__build_executable_116, 1089, 1092, 9, 37},
  {cont__build_executable_121, &frame__build_executable_116, 1088, 1095, 7, 44},
  {entry__build_executable_2, NULL, 1010, 1010, 9, 26},
  {cont__build_executable_3, &frame__build_executable_2, 1010, 1010, 9, 38},
  {cont__build_executable_4, &frame__build_executable_2, 1008, 1012, 5, 24},
  {cont__build_executable_9, &frame__build_executable_2, 1014, 1014, 5, 57},
  {cont__build_executable_12, &frame__build_executable_2, 1015, 1015, 5, 41},
  {cont__build_executable_13, &frame__build_executable_2, 1016, 1016, 5, 41},
  {cont__build_executable_14, &frame__build_executable_2, 1017, 1017, 5, 33},
  {cont__build_executable_15, &frame__build_executable_2, 1018, 1018, 5, 28},
  {cont__build_executable_16, &frame__build_executable_2, 1020, 1020, 5, 24},
  {cont__build_executable_17, &frame__build_executable_2, },
  {cont__build_executable_25, &frame__build_executable_2, 1021, 1045, 5, 67},
  {cont__build_executable_58, &frame__build_executable_2, 1046, 1046, 5, 50},
  {cont__build_executable_59, &frame__build_executable_2, 1047, 1050, 5, 41},
  {cont__build_executable_66, &frame__build_executable_2, 1051, 1060, 5, 25},
  {cont__build_executable_78, &frame__build_executable_2, 1061, 1085, 5, 47},
  {cont__build_executable_110, &frame__build_executable_2, 1086, 1086, 41, 41},
  {cont__build_executable_111, &frame__build_executable_2, 1086, 1086, 5, 42},
  {cont__build_executable_112, &frame__build_executable_2, 1087, 1087, 8, 41},
  {cont__build_executable_115, &frame__build_executable_2, 1087, 1095, 5, 45},
  {entry__build_executable_1, NULL, 1007, 1095, 3, 46},
  {entry__109_2, NULL, 113, 113, 30, 45},
  {cont__109_3, &frame__109_2, 113, 113, 30, 45},
  {cont__109_4, &frame__109_2, 113, 113, 30, 45},
  {entry__109_6, NULL, 114, 114, 8, 28},
  {cont__109_7, &frame__109_6, 114, 114, 5, 28},
  {entry__109_8, NULL, 115, 115, 5, 20},
  {entry__110_2, NULL, 119, 119, 31, 47},
  {cont__110_3, &frame__110_2, 119, 119, 31, 47},
  {cont__110_4, &frame__110_2, 119, 119, 31, 47},
  {entry__110_6, NULL, 120, 120, 8, 29},
  {cont__110_7, &frame__110_6, 120, 120, 5, 29},
  {entry__110_8, NULL, 121, 121, 5, 20},
  {entry__114_4, NULL, 141, 141, 7, 41},
  {cont__114_5, &frame__114_4, 142, 142, 10, 26},
  {cont__114_6, &frame__114_4, 142, 142, 7, 32},
  {cont__114_7, &frame__114_4, 143, 143, 7, 19},
  {cont__114_8, &frame__114_4, 144, 144, 7, 34},
  {cont__114_9, &frame__114_4, 145, 145, 10, 21},
  {cont__114_10, &frame__114_4, 145, 145, 7, 27},
  {cont__114_11, &frame__114_4, 146, 146, 20, 20},
  {entry__114_3, NULL, 140, 146, 5, 20},
  {cont__114_12, &frame__114_3, 146, 146, 20, 20},
  {entry__114_1, NULL, 137, 137, 3, 31},
  {cont__114_2, &frame__114_1, 139, 146, 3, 21},
  {entry__142_4, NULL, 176, 176, 41, 79},
  {entry__142_2, NULL, 176, 176, 8, 38},
  {cont__142_3, &frame__142_2, 176, 176, 5, 79},
  {cont__142_6, &frame__142_2, 177, 177, 5, 45},
  {cont__142_7, &frame__142_2, 177, 177, 45, 45},
  {entry__142_9, NULL, 183, 184, 7, 52},
  {entry__142_12, NULL, 186, 187, 7, 34},
  {entry__142_15, NULL, 189, 190, 7, 57},
  {entry__142_18, NULL, 192, 193, 7, 71},
  {entry__142_21, NULL, 195, 196, 7, 47},
  {entry__142_24, NULL, 198, 199, 7, 61},
  {entry__142_27, NULL, 201, 204, 9, 29},
  {entry__142_30, NULL, 208, 209, 7, 33},
  {entry__142_33, NULL, 211, 212, 7, 29},
  {entry__142_36, NULL, 214, 215, 7, 42},
  {entry__142_39, NULL, 217, 218, 7, 34},
  {entry__142_42, NULL, 220, 221, 7, 35},
  {entry__142_45, NULL, 223, 224, 7, 40},
  {entry__142_48, NULL, 226, 227, 9, 65},
  {entry__142_51, NULL, 231, 232, 7, 35},
  {entry__142_54, NULL, 234, 235, 7, 45},
  {entry__142_57, NULL, 237, 238, 9, 31},
  {entry__142_60, NULL, 242, 243, 7, 32},
  {entry__142_63, NULL, 245, 246, 7, 33},
  {entry__142_66, NULL, 248, 249, 7, 43},
  {entry__142_69, NULL, 251, 252, 7, 29},
  {entry__142_72, NULL, 254, 255, 7, 59},
  {entry__142_75, NULL, 257, 258, 7, 76},
  {entry__142_8, NULL, 179, 258, 5, 77},
  {cont__142_78, &frame__142_8, 258, 258, 78, 78},
  {entry__146_1, NULL, 263, 263, 37, 37},
  {entry__153_4, NULL, 288, 288, 3, 45},
  {cont__153_6, &frame__153_4, 288, 288, 45, 45},
  {entry__154_5, NULL, 292, 292, 5, 29},
  {cont__154_7, &frame__154_5, 293, 293, 5, 35},
  {cont__154_9, &frame__154_5, 293, 293, 35, 35},
  {entry__155_1, NULL, 296, 296, 20, 30},
  {cont__155_3, &frame__155_1, 296, 296, 3, 30},
  {cont__155_4, &frame__155_1, 296, 296, 30, 30},
  {entry__157_3, NULL, 300, 300, 3, 26},
  {cont__157_4, &frame__157_3, 300, 300, 26, 26},
  {entry__159_3, NULL, 304, 304, 3, 25},
  {cont__159_4, &frame__159_3, 304, 304, 25, 25},
  {entry__177_2, NULL, 646, 647, 9, 51},
  {cont__177_5, &frame__177_2, 646, 647, 3, 51},
  {entry__192_1, NULL, 1097, 1097, 20, 36},
  {cont__192_2, &frame__192_1, 1097, 1097, 36, 36},
  {entry__193_4, NULL, 1104, 1104, 7, 32},
  {entry__193_3, NULL, },
  {cont__193_5, &frame__193_3, },
  {entry__193_2, NULL, },
  {cont__193_6, &frame__193_2, },
  {entry__193_1, NULL, },
  {cont__193_7, &frame__193_1, 1099, 1105, 3, 24},
  {entry__193_8, NULL, 1106, 1106, 3, 23},
  {entry__193_9, NULL, 1107, 1107, 3, 43},
  {entry__193_10, NULL, 1108, 1108, 3, 57},
  {entry__193_11, NULL, 1109, 1109, 6, 29},
  {cont__193_12, &frame__193_11, 1109, 1109, 3, 43}
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
  frame->cont = cont__98_2;
}
static void cont__98_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 96: $MAJOR runtime_major_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_major_version();
  func = myself->type;
  frame->cont = cont__99_1;
}
static void cont__99_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MAJOR, arguments->slots[0]);
  // 97: $MINOR runtime_minor_version()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_minor_version();
  func = myself->type;
  frame->cont = cont__100_1;
}
static void cont__100_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._MINOR, arguments->slots[0]);
  // 98: $REVISION runtime_revision()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__runtime_revision();
  func = myself->type;
  frame->cont = cont__101_1;
}
static void cont__101_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._REVISION, arguments->slots[0]);
  // 100: $VERSION "@(MAJOR).@(MINOR).@(REVISION)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = var._MAJOR;
  arguments->slots[1] = string__578a5af303e9ccf;
  arguments->slots[2] = var._MINOR;
  arguments->slots[3] = string__578a5af303e9ccf;
  arguments->slots[4] = var._REVISION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__102_2;
}
static void cont__102_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._VERSION, arguments->slots[0]);
  // 102: version VERSION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._VERSION;
  result_count = 0;
  myself = get__version();
  func = myself->type;
  frame->cont = cont__103_1;
}
static void cont__103_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 104: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__104_1;
}
static void cont__104_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 104: extern $cc c_compiler()
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__104_2;
}
static void cont__104_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._cc, arguments->slots[0]);
  // 105: extern $mkdir "mkdir" # would be nice to have one in the system library!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c5aea03ea80c025;
  result_count = 1;
  myself = get__extern();
  func = myself->type;
  frame->cont = cont__105_2;
}
static void cont__105_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._mkdir, arguments->slots[0]);
  // 106: $SIMLIBPATH environment("SIMLIBPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__55d5804f0e895069;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__106_2;
}
static void cont__106_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMLIBPATH, arguments->slots[0]);
  // 107: $SIMDATAPATH environment("SIMDATAPATH")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2058710183abbfe4;
  result_count = 1;
  myself = get__environment();
  func = myself->type;
  frame->cont = cont__107_2;
}
static void cont__107_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._SIMDATAPATH, arguments->slots[0]);
  // 109: ... PREFIX()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__PREFIX();
  func = myself->type;
  frame->cont = cont__108_1;
}
static void cont__108_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 109: ... "/share/simplicity-@(VERSION)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1057e106f655c41;
  arguments->slots[1] = var._VERSION;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__108_3;
}
static void cont__108_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 109: ... string(PREFIX() "/share/simplicity-@(VERSION)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__108_4;
}
static void cont__108_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 109: $default_paths list(string(PREFIX() "/share/simplicity-@(VERSION)"))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__108_5;
}
static void cont__108_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._default_paths, arguments->slots[0]);
  // 113: SIMLIBPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__109_1;
}
static void cont__109_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 113: SIMLIBPATH.is_defined && SIMLIBPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = func__109_2;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__109_5;
}
static void entry__109_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 113: ... SIMLIBPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__109_3;
}
static void cont__109_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 113: ... SIMLIBPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__109_4;
}
static void cont__109_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 113: ... SIMLIBPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__109_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 111: $simlibpaths
  // 112:   if
  // 113:     SIMLIBPATH.is_defined && SIMLIBPATH != ""
  // 114:     -> split(SIMLIBPATH ':')
  // 115:     -> default_paths
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__109_6;
  arguments->slots[2] = func__109_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__109_9;
}
static void entry__109_6(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: ... split(SIMLIBPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMLIBPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__109_7;
}
static void cont__109_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 114: -> split(SIMLIBPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__109_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 115: -> default_paths
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._default_paths;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__109_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simlibpaths, arguments->slots[0]);
  // 119: SIMDATAPATH.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__110_1;
}
static void cont__110_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 119: SIMDATAPATH.is_defined && SIMDATAPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = func__110_2;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__110_5;
}
static void entry__110_2(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 119: ... SIMDATAPATH != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__110_3;
}
static void cont__110_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 119: ... SIMDATAPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__110_4;
}
static void cont__110_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 119: ... SIMDATAPATH != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__110_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 117: $simdatapaths
  // 118:   if
  // 119:     SIMDATAPATH.is_defined && SIMDATAPATH != ""
  // 120:     -> split(SIMDATAPATH ':')
  // 121:     -> default_paths
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__110_6;
  arguments->slots[2] = func__110_8;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__110_9;
}
static void entry__110_6(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 120: ... split(SIMDATAPATH ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._SIMDATAPATH;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__110_7;
}
static void cont__110_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 120: -> split(SIMDATAPATH ':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__110_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: -> default_paths
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._default_paths;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__110_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._simdatapaths, arguments->slots[0]);
  // 127: "bsd" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa720c15db16ba8;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_2;
}
static void cont__112_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 128: "cygwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__561f538101f3c2b9;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_3;
}
static void cont__112_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 129: "darwin" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c1f538281f242b9;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_4;
}
static void cont__112_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 130: "linux" = "posix"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__545aefc3ea81102f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_5;
}
static void cont__112_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 131: "posix" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__545aefc3ea81102f;
  arguments->slots[1] = string__fa720015d496ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_7;
}
static void cont__112_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 132: "win" = "all"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa725815d616ba2;
  arguments->slots[1] = string__fa720015d496ba0;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_9;
}
static void cont__112_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 133: "all" = NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa720015d496ba0;
  arguments->slots[1] = var._NONE;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__112_10;
}
static void cont__112_10(void) {
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
  frame->cont = cont__112_11;
}
static void cont__112_11(void) {
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
  arguments->slots[0] = func__114_1;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__114_13;
}
static void entry__114_3(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__114_4, 0);
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
  frame->cont = cont__114_12;
}
static void entry__114_4(void) {
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
  frame->cont = cont__114_5;
}
static void cont__114_5(void) {
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
  frame->cont = cont__114_6;
}
static void cont__114_6(void) {
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
  frame->cont = cont__114_7;
}
static void cont__114_7(void) {
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
  frame->cont = cont__114_8;
}
static void cont__114_8(void) {
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
  frame->cont = cont__114_9;
}
static void cont__114_9(void) {
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
  frame->cont = cont__114_10;
}
static void cont__114_10(void) {
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
  frame->cont = cont__114_11;
}
static void cont__114_11(void) {
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
static void cont__114_12(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__114_1(void) {
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
  frame->cont = cont__114_2;
}
static void cont__114_2(void) {
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
  frame->slots[2] /* temp__1 */ = create_closure(entry__114_3, 0);
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
static void cont__114_13(void) {
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
  // 172: $$additional_libraries undefined
  var._additional_libraries = get__undefined();
  // 173: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__141_1;
}
static void cont__141_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 173: ... truncate_until(program_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__program_name();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__141_2;
}
static void cont__141_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 173: $action truncate_until(program_name '/' -1) .truncate_from. '-'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__45;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__141_3;
}
static void cont__141_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._action, arguments->slots[0]);
  // 175: action == "simrun"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._action;
  arguments->slots[1] = string__421f52c90112c2b9;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__142_1;
}
static void cont__142_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 174: if
  // 175:   action == "simrun":
  // 176:     if command_line_arguments.is_empty: Error "Missing command line arguments!"
  // 177:     !input_filename command_line_arguments(1)
  // 178:   :
  // 179:     program_parameters
  // 180:       # the following options act on a single file only
  // 181:       
  // 182:       !sim2c::do_check_only
  // 183:       -> "check-only" "
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__142_2;
  arguments->slots[2] = func__142_8;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__142_79;
}
static void entry__142_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... command_line_arguments.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__command_line_arguments();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__142_3;
}
static void cont__142_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 176: if command_line_arguments.is_empty: Error "Missing command line arguments!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__142_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__142_6;
}
static void entry__142_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... Error "Missing command line arguments!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8d3c5e4b22d2f22b;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__142_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: !input_filename command_line_arguments(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__command_line_arguments();
  func = myself->type;
  frame->cont = cont__142_7;
}
static void cont__142_7(void) {
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
static void entry__142_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: program_parameters
  // 180:   # the following options act on a single file only
  // 181:   
  // 182:   !sim2c::do_check_only
  // 183:   -> "check-only" "
  // 184:     do not compile; just check for syntax errors
  // 185:   !sim2c::do_dump_trees
  // 186:   -> "dump-trees" "
  // 187:     dump abstract syntax trees
  // 188:   !sim2c::do_pretty_print
  // ...
  argument_count = 23;
  arguments = node_p;
  arguments->slots[0] = func__142_9;
  arguments->slots[1] = func__142_12;
  arguments->slots[2] = func__142_15;
  arguments->slots[3] = func__142_18;
  arguments->slots[4] = func__142_21;
  arguments->slots[5] = func__142_24;
  arguments->slots[6] = func__142_27;
  arguments->slots[7] = func__142_30;
  arguments->slots[8] = func__142_33;
  arguments->slots[9] = func__142_36;
  arguments->slots[10] = func__142_39;
  arguments->slots[11] = func__142_42;
  arguments->slots[12] = func__142_45;
  arguments->slots[13] = func__142_48;
  arguments->slots[14] = func__142_51;
  arguments->slots[15] = func__142_54;
  arguments->slots[16] = func__142_57;
  arguments->slots[17] = func__142_60;
  arguments->slots[18] = func__142_63;
  arguments->slots[19] = func__142_66;
  arguments->slots[20] = func__142_69;
  arguments->slots[21] = func__142_72;
  arguments->slots[22] = func__142_75;
  result_count = 23;
  myself = get__program_parameters();
  func = myself->type;
  frame->cont = cont__142_78;
}
static void entry__142_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: -> "check-only" "
  // 184:   do not compile; just check for syntax errors
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2b680b9e2e4fa558;
  arguments->slots[1] = string__8d1eb0934cb703aa;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_12(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 186: -> "dump-trees" "
  // 187:   dump abstract syntax trees
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__1124317d33023452;
  arguments->slots[1] = string__d3c3199b9e37dd88;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: -> "pretty-print" "
  // 190:   do not compile; just pretty print the source file
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2eb9522bce550419;
  arguments->slots[1] = string__31ed31d8e6f28138;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: -> "print-simplified-source" "
  // 193:   do not generate a C-file; just print the simplified source text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__23efc30ce16df2e;
  arguments->slots[1] = string__c565f1870e113429;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_21(void) {
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
static void entry__142_24(void) {
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
static void entry__142_27(void) {
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
static void entry__142_30(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: -> "brief" "
  // 209:   show brief error messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__6e5ae943eae03031;
  arguments->slots[1] = string__22ca0f65643a26b5;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: -> "warnings" "
  // 212:   show warning messages
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7c90ae5f04ed72b3;
  arguments->slots[1] = string__ea6d59fa9dcad709;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_36(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: -> "missing" "
  // 215:   inform about missing documentation
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__94300f9615cbf09d;
  arguments->slots[1] = string__aa7c4ea56fedf95b;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_39(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 217: -> "summary" "
  // 218:   show a statistical summary
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a8480d98152a1083;
  arguments->slots[1] = string__10671df6f7523277;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_42(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: -> "verbose" "
  // 221:   output verbose informations
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b65c0e101523e09f;
  arguments->slots[1] = string__2ba4a5a9cdae43b8;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_45(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: -> "debug" "
  // 224:   show C-compiler and linker calls
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__405aeb83ea605030;
  arguments->slots[1] = string__977692d258cc57f;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_48(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 226: -> "debug_compiler" "
  // 227:   show internal debug messages of the Simplicity compiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d13d99340b731341;
  arguments->slots[1] = string__d30c0a59c3d26b04;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_51(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: -> "codeblocks" "
  // 232:   create Code::Blocks project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2b7008daa973b572;
  arguments->slots[1] = string__99c92c9b20cfd38;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_54(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 234: -> "extract-documentation" "
  // 235:   extract documentation encoded as HTML
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7f0dce6ce0a2268e;
  arguments->slots[1] = string__140146cb87bc0040;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_57(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 237: -> "list-dependencies" "
  // 238:   list all dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__211e9dd763481194;
  arguments->slots[1] = string__1214925be130f2c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 242: -> "rebuild" "
  // 243:   rebuild all source files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__984c0f9015dae09e;
  arguments->slots[1] = string__6ce7f8f6c7e73eb4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: -> "omit-meta" "
  // 246:   do not rebuild meta files
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__749427e68da7a564;
  arguments->slots[1] = string__93608261e3431133;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_66(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 248: -> "static" "
  // 249:   create statically linked executable
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5a1f534901f312b4;
  arguments->slots[1] = string__b20e03a80d6db737;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_69(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: -> "profile" "
  // 252:   link with libprofiler
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__be440f9b95da309f;
  arguments->slots[1] = string__6f1f4f6107c9cdea;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_72(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: -> std::MANDATORY_PARAMETER "filename" "
  // 255:   the name of the source file or directory to compile
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__MANDATORY_PARAMETER();
  arguments->slots[1] = string__72b0ad9004bdc085;
  arguments->slots[2] = string__bb8770c27da8f42f;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__142_75(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 257: -> std::SOME_PARAMETERS "additional_libraries" "
  // 258:   the names of additional libraries (used for --extract-documentation)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__std__SOME_PARAMETERS();
  arguments->slots[1] = string__af5ae49d07a6e408;
  arguments->slots[2] = string__c8a7274dc08e5785;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__142_78(void) {
  if (argument_count != 23) {
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
  var._additional_libraries = arguments->slots[22];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__142_79(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: %main_filename fullname(input_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._input_filename;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__143_1;
}
static void cont__143_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_filename(), arguments->slots[0]);
  // 261: %main_info stat(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__144_1;
}
static void cont__144_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__main_info(), arguments->slots[0]);
  // 262: %do_build_static_executable do_build_static
  initialize_future(get__do_build_static_executable(), var._do_build_static);
  // 263: if do_show_debug_infos: !verbose true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__146_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__146_2;
}
static void entry__146_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 263: ... !verbose true
  set__verbose(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__146_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 271: %mode undefined # EXE or LIB
  initialize_maybe_future(get__mode(), get__undefined());
  // 272: $WHITESPACE many(' ')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__32;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__151_1;
}
static void cont__151_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._WHITESPACE, arguments->slots[0]);
  // 274: $$cc_options
  // 275:   list
  // 276:     "-Wall"
  // 277:     "-Wno-unused-function"
  // 278:     "-Wno-unused-variable"
  // 279:     "-Wno-parentheses"
  // 280:     "-Wno-switch"
  // 281:     "-Wno-trigraphs"
  // 282:     "-O1"
  // 283:     "-fPIC"
  // ...
  argument_count = 10;
  arguments = node_p;
  arguments->slots[0] = string__245aeb43eaacc03b;
  arguments->slots[1] = string__e381a5286a12b5a7;
  arguments->slots[2] = string__c9d1a7e66a0a17ac;
  arguments->slots[3] = string__1abcc193f1dac47a;
  arguments->slots[4] = string__d3e88c522110dabb;
  arguments->slots[5] = string__65a7cd1120033166;
  arguments->slots[6] = string__fa733015c516bfd;
  arguments->slots[7] = string__465ae703eb84c014;
  arguments->slots[8] = string__40ebeb253b72cf38;
  arguments->slots[9] = string__edf2e5a02a882fc3;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__152_11;
}
static void cont__152_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 287: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__153_1;
}
static void cont__153_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 287: ... c_compiler() == "gcc"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = string__fa721815d316baf;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__153_3;
}
static void cont__153_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 287: if c_compiler() == "gcc":
  // 288:   push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__153_4;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__153_7;
}
static void entry__153_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 288: push &cc_options "-Wno-maybe-uninitialized"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__ecde9da404625e23;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__153_6;
}
static void cont__153_6(void) {
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
static void cont__153_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 290: ... hardware_architecture()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__hardware_architecture();
  func = myself->type;
  frame->cont = cont__154_1;
}
static void cont__154_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 291: "x86_32", "x86_64"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f41f598c8327d2e5;
  arguments->slots[1] = string__f41f598c830fd2e3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__154_4;
}
static void cont__154_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 290: case hardware_architecture()
  // 291:   "x86_32", "x86_64":
  // 292:     push &cc_options "-msse2"
  // 293:     push &cc_options "-mfpmath=sse"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = func__154_5;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__154_10;
}
static void entry__154_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: push &cc_options "-msse2"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__7e1f52a6019282e5;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__154_7;
}
static void cont__154_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._cc_options = arguments->slots[0];
  // 293: push &cc_options "-mfpmath=sse"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = string__70d94c874a06872f;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__154_9;
}
static void cont__154_9(void) {
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
static void cont__154_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 295: for_each simdatapaths: (path)
  // 296:   push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._simdatapaths;
  arguments->slots[1] = func__155_1;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__155_5;
}
static void entry__155_1(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 296: ... "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6602b8c;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__155_3;
}
static void cont__155_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 296: push &cc_options "-I@(path)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cc_options;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
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
  var._cc_options = arguments->slots[0];
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
  // 298: $$cpp_options empty_list
  var._cpp_options = get__empty_list();
  // 299: ... CPPFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__CPPFLAGS();
  func = myself->type;
  frame->cont = cont__157_1;
}
static void cont__157_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 299: ... split(CPPFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__157_2;
}
static void cont__157_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 299: for_each split(CPPFLAGS()): (option)
  // 300:   push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__157_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__157_5;
}
static void entry__157_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 300: push &cpp_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._cpp_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__157_4;
}
static void cont__157_4(void) {
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
static void cont__157_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 302: $$ld_options empty_list
  var._ld_options = get__empty_list();
  // 303: ... LDFLAGS()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__LDFLAGS();
  func = myself->type;
  frame->cont = cont__159_1;
}
static void cont__159_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 303: ... split(LDFLAGS())
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__159_2;
}
static void cont__159_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 303: for_each split(LDFLAGS()): (option)
  // 304:   push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__159_3;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__159_5;
}
static void entry__159_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // option: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 304: push &ld_options option
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._ld_options;
  arguments->slots[1] = frame->slots[0] /* option */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__159_4;
}
static void cont__159_4(void) {
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
static void cont__159_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 306: %on_top_level true # set to false while building meta-files
  initialize_maybe_future(get__on_top_level(), get__true());
  // 307: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 308: %%libraries empty_insert_order_set # contains "-lsim-..."-entries
  set__libraries(get__empty_insert_order_set());
  // 309: %%do_link false
  set__do_link(get__false());
  // 310: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 311: $$c_sources empty_insert_order_set
  var._c_sources = get__empty_insert_order_set();
  // 312: $$dependencies empty_list
  var._dependencies = get__empty_list();
  // 313: $$resolved_libraries undefined
  var._resolved_libraries = get__undefined();
  // 645: ... main_info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__177_1;
}
static void cont__177_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 645: if main_info.is_undefined:
  // 646:   Error "
  // 647:     Source file "@(main_filename)" does not exist!@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = func__177_2;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__177_6;
}
static void entry__177_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: ... "
  // 647:   Source file "@(main_filename)" does not exist!@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9b6a42533552c66c;
  arguments->slots[1] = get__main_filename();
  arguments->slots[2] = string__79c06fde49ef2e97;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__177_5;
}
static void cont__177_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 646: Error "
  // 647:   Source file "@(main_filename)" does not exist!@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__177_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 957: $$t undefined
  var._t = get__undefined();
  // 1097: if do_time_passes: !t current_time()
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__192_1;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__192_3;
}
static void entry__192_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1097: ... !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__192_2;
}
static void cont__192_2(void) {
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
static void cont__192_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1098: cond
  // 1099:   ->
  // 1100:     ||
  // 1101:       do_check_only
  // 1102:       do_dump_trees
  // 1103:       do_pretty_print
  // 1104:       do_print_simplified_source
  // 1105:     dump_source_or_check
  // 1106:   -> do_print_c print_c
  // 1107:   -> do_list_dependencies list_dependencies
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = func__193_1;
  arguments->slots[1] = func__193_8;
  arguments->slots[2] = func__193_9;
  arguments->slots[3] = func__193_10;
  arguments->slots[4] = func__193_11;
  arguments->slots[5] = var._build_executable;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__193_13;
}
static void entry__193_1(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_check_only();
  arguments->slots[1] = func__193_2;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__193_7;
}
static void entry__193_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_dump_trees();
  arguments->slots[1] = func__193_3;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__193_6;
}
static void entry__193_3(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_pretty_print();
  arguments->slots[1] = func__193_4;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__193_5;
}
static void entry__193_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1104: do_print_simplified_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_simplified_source();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__193_5(void) {
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
static void cont__193_6(void) {
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
static void cont__193_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1099: ->
  // 1100:   ||
  // 1101:     do_check_only
  // 1102:     do_dump_trees
  // 1103:     do_pretty_print
  // 1104:     do_print_simplified_source
  // 1105:   dump_source_or_check
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._dump_source_or_check;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__193_8(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1106: -> do_print_c print_c
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_print_c;
  arguments->slots[1] = var._print_c;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__193_9(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1107: -> do_list_dependencies list_dependencies
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = var._list_dependencies;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__193_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1108: -> do_build_codeblocks_project build_codeblocks_project
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_build_codeblocks_project;
  arguments->slots[1] = var._build_codeblocks_project;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__193_11(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1109: ... main_info.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_info();
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__193_12;
}
static void cont__193_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 1109: -> main_info.is_a_directory build_library
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = var._build_library;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__193_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__std__terminate();
  func = myself->type;
  frame->cont = cont__194_1;
}
static void cont__194_1(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  terminate(0); // should never be reached
}
static void entry__sim2c__show_compiler_debug_info_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // args: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* args */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... ewriteln args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__sim2c__show_compiler_debug_info_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 266: ... : ewriteln args*
  frame->slots[1] /* temp__1 */ = create_closure(entry__sim2c__show_compiler_debug_info_2, 0);
  // 266: if do_show_compiler_debug_infos: ewriteln args*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_compiler_debug_infos();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolve_filename_1(void) {
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
  // 316: ... resolved_libraries.is_undefined
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
  // 316: if resolved_libraries.is_undefined:
  // 317:   !resolved_libraries empty_table
  // 318:   for_each simlibpaths: (path)
  // 319:     if file_exists(path):
  // 320:       for_each directory(path): (entry)
  // 321:         if entry.is_a_directory:
  // 322:           $name std::filename_of(entry)
  // 323:           if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 323: ... !resolved_libraries(name) fullname_of(entry)
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
  // 323: ... !resolved_libraries(name)
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
  // 322: $name std::filename_of(entry)
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
  // 323: ... name .matches. NAME
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
  // 323: ... : !resolved_libraries(name) fullname_of(entry)
  frame->slots[3] /* temp__2 */ = create_closure(entry__resolve_filename_13, 0);
  // 323: if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 321: ... entry.is_a_directory
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
  // 321: ... :
  // 322:   $name std::filename_of(entry)
  // 323:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_filename_10, 0);
  // 321: if entry.is_a_directory:
  // 322:   $name std::filename_of(entry)
  // 323:   if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 320: ... directory(path)
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
  // 320: for_each directory(path): (entry)
  // 321:   if entry.is_a_directory:
  // 322:     $name std::filename_of(entry)
  // 323:     if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 319: ... file_exists(path)
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
  // 319: ... :
  // 320:   for_each directory(path): (entry)
  // 321:     if entry.is_a_directory:
  // 322:       $name std::filename_of(entry)
  // 323:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_filename_6, 0);
  // 319: if file_exists(path):
  // 320:   for_each directory(path): (entry)
  // 321:     if entry.is_a_directory:
  // 322:       $name std::filename_of(entry)
  // 323:       if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 317: !resolved_libraries empty_table
  var._resolved_libraries = get__empty_table();
  // 318: for_each simlibpaths: (path)
  // 319:   if file_exists(path):
  // 320:     for_each directory(path): (entry)
  // 321:       if entry.is_a_directory:
  // 322:         $name std::filename_of(entry)
  // 323:         if name .matches. NAME: !resolved_libraries(name) fullname_of(entry)
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
  // 324: $libname filename .before. '/'
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
  // 325: $libpath resolved_libraries(libname)
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
  // 326: ... libpath.is_undefined
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
  // 326: ... :
  // 327:   Error "
  // 328:     Cannot resolve required library "@(libname)@quot;!@
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolve_filename_20, 0);
  // 326: if libpath.is_undefined:
  // 327:   Error "
  // 328:     Cannot resolve required library "@(libname)@quot;!@
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
  // 327: ... "
  // 328:   Cannot resolve required library "@(libname)@quot;!@
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
  // 327: Error "
  // 328:   Cannot resolve required library "@(libname)@quot;!@
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
  // 329: ... filename .from. '/'
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
  // 329: ... string(libpath filename .from. '/')
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
  // 329: -> string(libpath filename .from. '/')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__add_module_infos_1(void) {
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
  // 340: ... --SORT
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
  // 340: $entries directory(--SORT path)
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
  // 341: $$filenames empty_set
  ((CELL *)frame->slots[4])->contents /* filenames */ = get__empty_set();
  // 342: $$directories empty_list
  ((CELL *)frame->slots[5])->contents /* directories */ = get__empty_list();
  // 343: $$modules empty_key_order_set
  ((CELL *)frame->slots[6])->contents /* modules */ = get__empty_key_order_set();
  // 344: ... : (entry)
  // 345:   $name std::filename_of(entry)
  // 346:   cond
  // 347:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 348:     -> name .has_suffix. ".sim":
  // 349:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:       !filenames(submodule_name) true
  // 351:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:       $stored_level meta_levels(submodule_name)
  // 353:       if stored_level.is_undefined || meta_level > stored_level:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__add_module_infos_4, 1);
  // 344: for_each entries: (entry)
  // 345:   $name std::filename_of(entry)
  // 346:   cond
  // 347:     -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 348:     -> name .has_suffix. ".sim":
  // 349:       $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:       !filenames(submodule_name) true
  // 351:       $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:       $stored_level meta_levels(submodule_name)
  // 353:       if stored_level.is_undefined || meta_level > stored_level:
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
  // 349: ... some(".meta")
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
  // 349: ... some(".meta"), ".sim"
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
  // 349: $submodule_name name .without_suffix. (some(".meta"), ".sim")
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
  // 350: !filenames(submodule_name) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 350: !filenames(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* submodule_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
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
  // 351: ... length_of(name)
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
  // 351: ... length_of(submodule_name)
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
  // 351: ... length_of(name)-length_of(submodule_name)
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
  // 351: ... length_of(name)-length_of(submodule_name)-4
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
  // 351: $meta_level (length_of(name)-length_of(submodule_name)-4)/5
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
  // 352: $stored_level meta_levels(submodule_name)
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
  // 353: ... stored_level.is_undefined
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
  // 353: ... meta_level > stored_level
  frame->slots[11] /* temp__3 */ = create_closure(entry__add_module_infos_28, 0);
  // 353: ... stored_level.is_undefined || meta_level > stored_level
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
  // 353: ... meta_level > stored_level
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
  // 353: ... meta_level > stored_level
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
  // 353: ... :
  // 354:   !meta_levels(submodule_name) meta_level
  frame->slots[12] /* temp__4 */ = create_closure(entry__add_module_infos_31, 0);
  // 353: if stored_level.is_undefined || meta_level > stored_level:
  // 354:   !meta_levels(submodule_name) meta_level
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
  // 354: !meta_levels(submodule_name) meta_level
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* meta_level */;
  // 354: !meta_levels(submodule_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* submodule_name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
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
  // 355: $basename submodule_name .truncate_from. '-'
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
  // 356: !modules(basename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 356: !modules(basename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* basename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
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
  // 357: $mod_name string(mod_path basename)
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
  // 358: !module_info(mod_name) empty_key_order_table
  frame->slots[9] /* temp__1 */ = get__empty_key_order_table();
  // 358: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* mod_name */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
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
  // 347: ... push &directories name
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
  // 347: ... name .matches. NAME
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
  // 347: ... : push &directories name
  frame->slots[3] /* temp__2 */ = create_closure(entry__add_module_infos_10, 0);
  // 347: ... if name .matches. NAME: push &directories name
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
  // 347: ... entry.is_a_directory
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
  // 347: ... : if name .matches. NAME: push &directories name
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_8, 0);
  // 347: -> entry.is_a_directory: if name .matches. NAME: push &directories name
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
  // 348: ... name .has_suffix. ".sim"
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
  // 348: ... :
  // 349:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:   !filenames(submodule_name) true
  // 351:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:   $stored_level meta_levels(submodule_name)
  // 353:   if stored_level.is_undefined || meta_level > stored_level:
  // 354:     !meta_levels(submodule_name) meta_level
  // 355:   $basename submodule_name .truncate_from. '-'
  // 356:   !modules(basename) true
  // 357:   $mod_name string(mod_path basename)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__add_module_infos_15, 0);
  // 348: -> name .has_suffix. ".sim":
  // 349:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:   !filenames(submodule_name) true
  // 351:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:   $stored_level meta_levels(submodule_name)
  // 353:   if stored_level.is_undefined || meta_level > stored_level:
  // 354:     !meta_levels(submodule_name) meta_level
  // 355:   $basename submodule_name .truncate_from. '-'
  // 356:   !modules(basename) true
  // 357:   $mod_name string(mod_path basename)
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
  // 345: $name std::filename_of(entry)
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
  // 347: -> entry.is_a_directory: if name .matches. NAME: push &directories name
  frame->slots[6] /* temp__1 */ = create_closure(entry__add_module_infos_6, 0);
  // 348: -> name .has_suffix. ".sim":
  // 349:   $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:   !filenames(submodule_name) true
  // 351:   $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:   $stored_level meta_levels(submodule_name)
  // 353:   if stored_level.is_undefined || meta_level > stored_level:
  // 354:     !meta_levels(submodule_name) meta_level
  // 355:   $basename submodule_name .truncate_from. '-'
  // 356:   !modules(basename) true
  // 357:   $mod_name string(mod_path basename)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__add_module_infos_12, 0);
  // 346: cond
  // 347:   -> entry.is_a_directory: if name .matches. NAME: push &directories name
  // 348:   -> name .has_suffix. ".sim":
  // 349:     $submodule_name name .without_suffix. (some(".meta"), ".sim")
  // 350:     !filenames(submodule_name) true
  // 351:     $meta_level (length_of(name)-length_of(submodule_name)-4)/5
  // 352:     $stored_level meta_levels(submodule_name)
  // 353:     if stored_level.is_undefined || meta_level > stored_level:
  // 354:       !meta_levels(submodule_name) meta_level
  // 355:     $basename submodule_name .truncate_from. '-'
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
  // 359: ... : (filename)
  // 360:   if filename .contains. '-':
  // 361:     unless filename .has_suffix. "-common":
  // 362:       $maybe_push_common: (plat)
  // 363:         $common_name string(name "-" plat "-common")
  // 364:         if filenames(common_name): push &files common_name
  // 365:       
  // 366:       $name filename .before. '-'
  // 367:       $mod_name string(mod_path name .truncate_from. '-')
  // 368:       $platform filename .behind. '-'
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__add_module_infos_39, 1);
  // 359: for_each filenames: (filename)
  // 360:   if filename .contains. '-':
  // 361:     unless filename .has_suffix. "-common":
  // 362:       $maybe_push_common: (plat)
  // 363:         $common_name string(name "-" plat "-common")
  // 364:         if filenames(common_name): push &files common_name
  // 365:       
  // 366:       $name filename .before. '-'
  // 367:       $mod_name string(mod_path name .truncate_from. '-')
  // 368:       $platform filename .behind. '-'
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
  // 362: ... : (plat)
  // 363:   $common_name string(name "-" plat "-common")
  // 364:   if filenames(common_name): push &files common_name
  frame->slots[9] /* temp__1 */ = create_closure(entry__add_module_infos_45, 1);
  // 362: $maybe_push_common: (plat)
  // 363:   $common_name string(name "-" plat "-common")
  // 364:   if filenames(common_name): push &files common_name
  initialize_future(frame->slots[3] /* maybe_push_common */, frame->slots[9] /* temp__1 */);
  // 366: $name filename .before. '-'
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
  // 364: ... push &files common_name
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
  // 363: $common_name string(name "-" plat "-common")
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
  // 364: ... filenames(common_name)
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
  // 364: ... : push &files common_name
  frame->slots[6] /* temp__2 */ = create_closure(entry__add_module_infos_49, 0);
  // 364: if filenames(common_name): push &files common_name
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
  // 367: ... name .truncate_from. '-'
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
  // 367: $mod_name string(mod_path name .truncate_from. '-')
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
  // 368: $platform filename .behind. '-'
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
  // 369: $$parent supported_platforms(platform)
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
  // 370: ... parent.is_defined
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
  // 370: ... :
  // 371:   Error "
  // 372:     The platform "@(platform)" is not supported!@
  frame->slots[10] /* temp__2 */ = create_closure(entry__add_module_infos_57, 0);
  // 370: unless parent.is_defined:
  // 371:   Error "
  // 372:     The platform "@(platform)" is not supported!@
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
  // 371: ... "
  // 372:   The platform "@(platform)" is not supported!@
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
  // 371: Error "
  // 372:   The platform "@(platform)" is not supported!@
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
  // 373: $$files list(filename)
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
  // 374: maybe_push_common platform
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
  // 375: ... -> parent != NONE:
  // 376:   maybe_push_common parent
  // 377:   !parent supported_platforms(parent)
  frame->slots[9] /* temp__1 */ = create_closure(entry__add_module_infos_64, 0);
  // 375: while -> parent != NONE:
  // 376:   maybe_push_common parent
  // 377:   !parent supported_platforms(parent)
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
  // 376: maybe_push_common parent
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
  // 377: !parent supported_platforms(parent)
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
  // 375: ... parent != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parent */;
  arguments->slots[1] = var._NONE;
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
  // 375: ... parent != NONE
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
  // 375: ... :
  // 376:   maybe_push_common parent
  // 377:   !parent supported_platforms(parent)
  frame->slots[4] /* temp__3 */ = create_closure(entry__add_module_infos_67, 0);
  // 375: ... -> parent != NONE:
  // 376:   maybe_push_common parent
  // 377:   !parent supported_platforms(parent)
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
  // 378: !module_info(mod_name)(platform) files
  frame->slots[9] /* temp__1 */ = ((CELL *)frame->slots[8])->contents /* files */;
  // 378: ... module_info(mod_name)
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
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 378: !module_info(mod_name)(platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* platform */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__add_module_infos_72;
}
static void cont__add_module_infos_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__2 */ = arguments->slots[0];
  // 378: !module_info(mod_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* mod_name */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
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
  // 361: ... filename .has_suffix. "-common"
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
  // 361: ... :
  // 362:   $maybe_push_common: (plat)
  // 363:     $common_name string(name "-" plat "-common")
  // 364:     if filenames(common_name): push &files common_name
  // 365:   
  // 366:   $name filename .before. '-'
  // 367:   $mod_name string(mod_path name .truncate_from. '-')
  // 368:   $platform filename .behind. '-'
  // 369:   $$parent supported_platforms(platform)
  // 370:   unless parent.is_defined:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_44, 0);
  // 361: unless filename .has_suffix. "-common":
  // 362:   $maybe_push_common: (plat)
  // 363:     $common_name string(name "-" plat "-common")
  // 364:     if filenames(common_name): push &files common_name
  // 365:   
  // 366:   $name filename .before. '-'
  // 367:   $mod_name string(mod_path name .truncate_from. '-')
  // 368:   $platform filename .behind. '-'
  // 369:   $$parent supported_platforms(platform)
  // 370:   unless parent.is_defined:
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
  // 360: ... filename .contains. '-'
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
  // 360: ... :
  // 361:   unless filename .has_suffix. "-common":
  // 362:     $maybe_push_common: (plat)
  // 363:       $common_name string(name "-" plat "-common")
  // 364:       if filenames(common_name): push &files common_name
  // 365:     
  // 366:     $name filename .before. '-'
  // 367:     $mod_name string(mod_path name .truncate_from. '-')
  // 368:     $platform filename .behind. '-'
  // 369:     $$parent supported_platforms(platform)
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_module_infos_41, 0);
  // 360: if filename .contains. '-':
  // 361:   unless filename .has_suffix. "-common":
  // 362:     $maybe_push_common: (plat)
  // 363:       $common_name string(name "-" plat "-common")
  // 364:       if filenames(common_name): push &files common_name
  // 365:     
  // 366:     $name filename .before. '-'
  // 367:     $mod_name string(mod_path name .truncate_from. '-')
  // 368:     $platform filename .behind. '-'
  // 369:     $$parent supported_platforms(platform)
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
  // 379: ... parameter_count_of(return)
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
  // 379: ... parameter_count_of(return) == 2
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
  // 379: ... : return directories modules
  frame->slots[9] /* temp__3 */ = create_closure(entry__add_module_infos_77, 0);
  // 379: if parameter_count_of(return) == 2: return directories modules
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
  // 379: ... return directories modules
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
  // 390: ... -> info
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
  // 391: ... 1
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
  // 391: ... before(mod_filename '/' -1)
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
  // 391: ... 1
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
  // 391: ... until(mod_name '/' -1)
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
  // 391: add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 0;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__lookup_10;
}
static void cont__lookup_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 392: ... module_info(mod_name)
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
  // 392: -> module_info(mod_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__lookup_1(void) {
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
  // 389: $info module_info(mod_name)
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
  // 390: ... info.is_defined
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
  // 390: ... -> info
  frame->slots[4] /* temp__2 */ = create_closure(entry__lookup_4, 0);
  // 390: ... :
  // 391:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 392:   -> module_info(mod_name)
  frame->slots[5] /* temp__3 */ = create_closure(entry__lookup_5, 0);
  // 390: if info.is_defined (-> info):
  // 391:   add_module_infos before(mod_filename '/' -1) until(mod_name '/' -1)
  // 392:   -> module_info(mod_name)
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
static void entry__CC_1(void) {
  allocate_arguments();
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // args: 0
  frame->slots[0] /* args */ = from_arguments(0, argument_count-0);
  // 395: ... : ewriteln c_compiler() ' ' join(args)
  frame->slots[1] /* temp__1 */ = create_closure(entry__CC_2, 0);
  // 395: if do_show_debug_infos: ewriteln c_compiler() ' ' join(args)
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
  // 395: ... c_compiler()
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
  // 395: ... join(args)
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
  // 395: ... ewriteln c_compiler() ' ' join(args)
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
  // 396: cc args*
  argument_count = 0;
  arguments = node_p;
  unfold(frame->slots[0] /* args */);
  result_count = frame->caller_result_count;
  myself = var._cc;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_c_4(void) {
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
  // 400: CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._cpp_options);
  unfold(var._cc_options);
  arguments->slots[argument_count++] = string__2d7981f4e6602ba6;
  arguments->slots[argument_count++] = frame->slots[0] /* c_filename */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* o_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__compile_c_7;
}
static void cont__compile_c_7(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 400: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 400: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 400: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 401: ... :
  // 402:   Error "
  // 403:     Failed to compile @(c_filename)
  // 404:     @(err.from_utf8)
  frame->slots[5] /* temp__1 */ = create_closure(entry__compile_c_8, 0);
  // 401: unless success:
  // 402:   Error "
  // 403:     Failed to compile @(c_filename)
  // 404:     @(err.from_utf8)
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
  // 404: ... err.from_utf8
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
  // 402: ... "
  // 403:   Failed to compile @(c_filename)
  // 404:   @(err.from_utf8)
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
  // 402: Error "
  // 403:   Failed to compile @(c_filename)
  // 404:   @(err.from_utf8)
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
  // 405: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_c_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // c_filename: 0
  // o_filename: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 399: ... do_build_codeblocks_project || do_list_dependencies
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
  // 399: ... do_list_dependencies
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
  // 399: ... :
  // 400:   CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  // 401:   unless success:
  // 402:     Error "
  // 403:       Failed to compile @(c_filename)
  // 404:       @(err.from_utf8)
  // 405:   !do_link true
  frame->slots[3] /* temp__2 */ = create_closure(entry__compile_c_4, 0);
  // 399: unless do_build_codeblocks_project || do_list_dependencies:
  // 400:   CC $_out $err $success cpp_options* cc_options* "-c" c_filename "-o" o_filename
  // 401:   unless success:
  // 402:     Error "
  // 403:       Failed to compile @(c_filename)
  // 404:       @(err.from_utf8)
  // 405:   !do_link true
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
  // 417: ... 1
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
  // 417: $meta_path truncate_from(mod_filename '/' -1)
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
  // 418: ... dup(".meta" meta_level)
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
  // 418: $filename string(mod_filename dup(".meta" meta_level))
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
  // 419: $meta_filename string(filename ".sim")
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
  // 420: ... dup(".meta" meta_level)
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
  // 420: $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
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
  // 421: ... meta_level-1
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
  // 421: ... dup(".meta" meta_level-1)
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
  // 421: $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
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
  // 422: $meta_info stat(meta_filename)
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
  // 423: $sim_info stat(sim_filename)
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
  // 424: $meta_c_info stat(meta_c_filename)
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
  // 426: $$force_rebuild
  // 427:   ||
  // 428:     do_rebuild
  // 429:     sim_info.is_undefined
  // 430:     meta_c_info.is_undefined
  // 431:     modification_time_of(meta_info) > modification_time_of(meta_c_info)
  // 432:     modification_time_of(meta_c_info) > modification_time_of(sim_info)
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
  // 429: sim_info.is_undefined
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
  // 430: meta_c_info.is_undefined
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
  // 431: ... modification_time_of(meta_c_info)
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
  // 431: modification_time_of(meta_info)
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
  // 431: modification_time_of(meta_info) > modification_time_of(meta_c_info)
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
  // 432: modification_time_of(meta_c_info) > modification_time_of(sim_info)
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
  // 432: ... modification_time_of(sim_info)
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
  // 432: modification_time_of(meta_c_info)
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
  // 432: modification_time_of(meta_c_info) > modification_time_of(sim_info)
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
  // 432: modification_time_of(meta_c_info) > modification_time_of(sim_info)
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
  // 434: ... :
  // 435:   $modification_time modification_time_of(sim_info)
  // 436:   load $meta_c_buf meta_c_filename
  // 437:   do: (-> break)
  // 438:     for_each_line meta_c_buf: ($line)
  // 439:       $check: (data_filename)
  // 440:         $data_info stat(data_filename)
  // 441:         if
  // 442:           ||
  // 443:             data_info.is_undefined
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_meta_module_33, 0);
  // 434: unless force_rebuild:
  // 435:   $modification_time modification_time_of(sim_info)
  // 436:   load $meta_c_buf meta_c_filename
  // 437:   do: (-> break)
  // 438:     for_each_line meta_c_buf: ($line)
  // 439:       $check: (data_filename)
  // 440:         $data_info stat(data_filename)
  // 441:         if
  // 442:           ||
  // 443:             data_info.is_undefined
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
  // 438: ... : ($line)
  // 439:   $check: (data_filename)
  // 440:     $data_info stat(data_filename)
  // 441:     if
  // 442:       ||
  // 443:         data_info.is_undefined
  // 444:         modification_time_of(data_info) > modification_time
  // 445:       :
  // 446:         !force_rebuild true
  // 447:         break
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__compile_meta_module_37, 1);
  // 438: for_each_line meta_c_buf: ($line)
  // 439:   $check: (data_filename)
  // 440:     $data_info stat(data_filename)
  // 441:     if
  // 442:       ||
  // 443:         data_info.is_undefined
  // 444:         modification_time_of(data_info) > modification_time
  // 445:       :
  // 446:         !force_rebuild true
  // 447:         break
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
  // 459: ... string(path '/' argument)
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
  // 459: ... check string(path '/' argument)
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
  // 457: ... 1
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
  // 457: ... range(argument 2 -1)
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
  // 457: ... string(meta_path range(argument 2 -1))
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
  // 457: check string(meta_path range(argument 2 -1))
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
  // 459: ... : (path) check string(path '/' argument)
  frame->slots[2] /* temp__1 */ = create_closure(entry__compile_meta_module_63, 1);
  // 459: for_each simdatapaths: (path) check string(path '/' argument)
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
  // 456: argument .has_prefix. "./"
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
  // 456: ... :
  // 457:   check string(meta_path range(argument 2 -1))
  frame->slots[4] /* temp__2 */ = create_closure(entry__compile_meta_module_58, 0);
  // 458: :
  // 459:   for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[5] /* temp__3 */ = create_closure(entry__compile_meta_module_62, 0);
  // 455: if
  // 456:   argument .has_prefix. "./":
  // 457:     check string(meta_path range(argument 2 -1))
  // 458:   :
  // 459:     for_each simdatapaths: (path) check string(path '/' argument)
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
  // 439: ... : (data_filename)
  // 440:   $data_info stat(data_filename)
  // 441:   if
  // 442:     ||
  // 443:       data_info.is_undefined
  // 444:       modification_time_of(data_info) > modification_time
  // 445:     :
  // 446:       !force_rebuild true
  // 447:       break
  frame->slots[8] /* temp__1 */ = create_closure(entry__compile_meta_module_38, 1);
  // 439: $check: (data_filename)
  // 440:   $data_info stat(data_filename)
  // 441:   if
  // 442:     ||
  // 443:       data_info.is_undefined
  // 444:       modification_time_of(data_info) > modification_time
  // 445:     :
  // 446:       !force_rebuild true
  // 447:       break
  initialize_future(frame->slots[5] /* check */, frame->slots[8] /* temp__1 */);
  // 449: ... line .has_prefix. "/// "
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
  // 446: !force_rebuild true
  ((CELL *)frame->slots[0])->contents /* force_rebuild */ = get__true();
  // 447: break
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
  // 440: $data_info stat(data_filename)
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
  // 443: data_info.is_undefined
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
  // 444: modification_time_of(data_info) > modification_time
  frame->slots[7] /* temp__3 */ = create_closure(entry__compile_meta_module_41, 0);
  // 442: ||
  // 443:   data_info.is_undefined
  // 444:   modification_time_of(data_info) > modification_time
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
  // 444: modification_time_of(data_info)
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
  // 444: modification_time_of(data_info) > modification_time
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
  // 444: modification_time_of(data_info) > modification_time
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
  // 445: :
  // 446:   !force_rebuild true
  // 447:   break
  frame->slots[8] /* temp__4 */ = create_closure(entry__compile_meta_module_45, 0);
  // 441: if
  // 442:   ||
  // 443:     data_info.is_undefined
  // 444:     modification_time_of(data_info) > modification_time
  // 445:   :
  // 446:     !force_rebuild true
  // 447:     break
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
  // 449: unless line .has_prefix. "/// " break
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
  // 450: behind &line ' '
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
  // 451: trim &line
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
  // 452: $command line .truncate_from. WHITESPACE
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
  // 453: $argument line .behind. WHITESPACE
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
  // 454: ... command == "data"
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
  // 454: ... :
  // 455:   if
  // 456:     argument .has_prefix. "./":
  // 457:       check string(meta_path range(argument 2 -1))
  // 458:     :
  // 459:       for_each simdatapaths: (path) check string(path '/' argument)
  frame->slots[9] /* temp__2 */ = create_closure(entry__compile_meta_module_55, 0);
  // 454: if command == "data":
  // 455:   if
  // 456:     argument .has_prefix. "./":
  // 457:       check string(meta_path range(argument 2 -1))
  // 458:     :
  // 459:       for_each simdatapaths: (path) check string(path '/' argument)
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
  // 435: $modification_time modification_time_of(sim_info)
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
  // 436: load $meta_c_buf meta_c_filename
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
  // 437: ... : (-> break)
  // 438:   for_each_line meta_c_buf: ($line)
  // 439:     $check: (data_filename)
  // 440:       $data_info stat(data_filename)
  // 441:       if
  // 442:         ||
  // 443:           data_info.is_undefined
  // 444:           modification_time_of(data_info) > modification_time
  // 445:         :
  // 446:           !force_rebuild true
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_meta_module_36, 0);
  // 437: do: (-> break)
  // 438:   for_each_line meta_c_buf: ($line)
  // 439:     $check: (data_filename)
  // 440:       $data_info stat(data_filename)
  // 441:       if
  // 442:         ||
  // 443:           data_info.is_undefined
  // 444:           modification_time_of(data_info) > modification_time
  // 445:         :
  // 446:           !force_rebuild true
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
  // 460: ... :
  // 461:   %on_top_level false
  // 462:   %%objects empty_insert_order_set
  // 463:   %%libraries empty_insert_order_set
  // 464:   %%do_link false
  // 465:   %%last_modification_time undefined
  // 466:   %do_build_static_executable false
  // 467:   %main_filename meta_filename
  // 468:   %main_info stat(main_filename)
  // 469:   build_executable
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_meta_module_67, 0);
  // 460: if force_rebuild:
  // 461:   %on_top_level false
  // 462:   %%objects empty_insert_order_set
  // 463:   %%libraries empty_insert_order_set
  // 464:   %%do_link false
  // 465:   %%last_modification_time undefined
  // 466:   %do_build_static_executable false
  // 467:   %main_filename meta_filename
  // 468:   %main_info stat(main_filename)
  // 469:   build_executable
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
  // 461: %on_top_level false
  initialize_maybe_future(get__on_top_level(), get__false());
  // 462: %%objects empty_insert_order_set
  set__objects(get__empty_insert_order_set());
  // 463: %%libraries empty_insert_order_set
  set__libraries(get__empty_insert_order_set());
  // 464: %%do_link false
  set__do_link(get__false());
  // 465: %%last_modification_time undefined
  set__last_modification_time(get__undefined());
  // 466: %do_build_static_executable false
  initialize_maybe_future(get__do_build_static_executable(), get__false());
  // 467: %main_filename meta_filename
  initialize_maybe_future(get__main_filename(), frame->slots[1] /* meta_filename */);
  // 468: %main_info stat(main_filename)
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
  // 469: build_executable
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._build_executable;
  func = myself->type;
  frame->cont = cont__compile_meta_module_69;
}
static void cont__compile_meta_module_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 470: $orig_path current_path()
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
  // 471: change_directory meta_path
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
  // 472: std::call $out $err $success filename
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
  frame->slots[9] /* temp__1 */ = arguments->slots[0];
  frame->slots[10] /* temp__2 */ = arguments->slots[1];
  frame->slots[11] /* temp__3 */ = arguments->slots[2];
  // 472: ... out
  initialize_future(frame->slots[6] /* out */, frame->slots[9] /* temp__1 */);
  // 472: ... err
  initialize_future(frame->slots[7] /* err */, frame->slots[10] /* temp__2 */);
  // 472: ... success
  initialize_future(frame->slots[8] /* success */, frame->slots[11] /* temp__3 */);
  // 473: change_directory orig_path
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
  // 474: ... : Error err.from_utf8
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_meta_module_74, 0);
  // 474: unless success: Error err.from_utf8
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
  // 474: ... err.from_utf8
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
  // 474: ... Error err.from_utf8
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
  // 475: ... out.to_utf8
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
  // 475: save sim_filename out.to_utf8
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
  // 476: dec &meta_level
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
  // 477: ... meta_level > 0
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
  // 477: -> meta_level > 0
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compile_meta_module_1(void) {
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
  // 416: ... :
  // 417:   $meta_path truncate_from(mod_filename '/' -1)
  // 418:   $filename string(mod_filename dup(".meta" meta_level))
  // 419:   $meta_filename string(filename ".sim")
  // 420:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 421:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 422:   $meta_info stat(meta_filename)
  // 423:   $sim_info stat(sim_filename)
  // 424:   $meta_c_info stat(meta_c_filename)
  // 425:   
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_meta_module_2, 0);
  // 416: do_while:
  // 417:   $meta_path truncate_from(mod_filename '/' -1)
  // 418:   $filename string(mod_filename dup(".meta" meta_level))
  // 419:   $meta_filename string(filename ".sim")
  // 420:   $meta_c_filename string(mod_filename dup(".meta" meta_level) ".c")
  // 421:   $sim_filename string(mod_filename dup(".meta" meta_level-1) ".sim")
  // 422:   $meta_info stat(meta_filename)
  // 423:   $sim_info stat(sim_filename)
  // 424:   $meta_c_info stat(meta_c_filename)
  // 425:   
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do_while();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_dependencies_1(void) {
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
  // 490: ... : ($line)
  // 491:   unless line .has_prefix. "/// " return
  // 492:   behind &line ' '
  // 493:   trim &line
  // 494:   $command line .truncate_from. WHITESPACE
  // 495:   $argument line .behind. WHITESPACE
  // 496:   case
  // 497:     command
  // 498:     "require":
  // 499:       if
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_dependencies_2, 1);
  // 490: for_each_line c_buf: ($line)
  // 491:   unless line .has_prefix. "/// " return
  // 492:   behind &line ' '
  // 493:   trim &line
  // 494:   $command line .truncate_from. WHITESPACE
  // 495:   $argument line .behind. WHITESPACE
  // 496:   case
  // 497:     command
  // 498:     "require":
  // 499:       if
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
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 518: ... !libraries(argument .truncate_from. '/') true
  frame->slots[1] /* temp__1 */ = get__true();
  // 518: ... argument .truncate_from. '/'
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 518: ... !libraries(argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
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
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* argument */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 516: !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 516: ... argument .truncate_from. '/'
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
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 516: ... string("sim-" argument .truncate_from. '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__240aeb0b5d087d14;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 516: !libraries(string("sim-" argument .truncate_from. '/'))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
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
  // 513: ... resolve_filename(argument)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* argument */;
  result_count = 1;
  myself = var._resolve_filename;
  func = myself->type;
  frame->cont = cont__build_dependencies_28;
}
static void cont__build_dependencies_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 513: compile_module resolve_filename(argument) argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* argument */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
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
  // 515: ... :
  // 516:   !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_dependencies_30, 0);
  // 515: if do_compile_c:
  // 516:   !libraries(string("sim-" argument .truncate_from. '/')) true
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
  // 502: ... 1
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
  // 502: $req_name range(argument 3 -1)
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
  // 504: ... 1
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
  // 504: ... until(mod_filename '/' -1)
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
  // 504: string(until(mod_filename '/' -1) req_name)
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
  // 505: ... 1
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
  // 505: ... until(mod_name '/' -1)
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
  // 505: string(until(mod_name '/' -1) req_name)
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
  // 503: compile_module
  // 504:   string(until(mod_filename '/' -1) req_name)
  // 505:   string(until(mod_name '/' -1) req_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
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
  // 501: ... mode == EXE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__mode();
  arguments->slots[1] = var._EXE;
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
  // 501: ... :
  // 502:   $req_name range(argument 3 -1)
  // 503:   compile_module
  // 504:     string(until(mod_filename '/' -1) req_name)
  // 505:     string(until(mod_name '/' -1) req_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__build_dependencies_13, 0);
  // 501: if mode == EXE:
  // 502:   $req_name range(argument 3 -1)
  // 503:   compile_module
  // 504:     string(until(mod_filename '/' -1) req_name)
  // 505:     string(until(mod_name '/' -1) req_name)
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
  // 511: do_list_dependencies
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
  // 512: :
  // 513:   compile_module resolve_filename(argument) argument
  frame->slots[3] /* temp__2 */ = create_closure(entry__build_dependencies_27, 0);
  // 514: :
  // 515:   if do_compile_c:
  // 516:     !libraries(string("sim-" argument .truncate_from. '/')) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_dependencies_29, 0);
  // 507: if
  // 508:   ||
  // 509:     do_build_static_executable
  // 510:     do_build_codeblocks_project
  // 511:     do_list_dependencies
  // 512:   :
  // 513:     compile_module resolve_filename(argument) argument
  // 514:   :
  // 515:     if do_compile_c:
  // 516:       !libraries(string("sim-" argument .truncate_from. '/')) true
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
  // 500: argument .has_prefix. "./"
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
  // 500: ... :
  // 501:   if mode == EXE:
  // 502:     $req_name range(argument 3 -1)
  // 503:     compile_module
  // 504:       string(until(mod_filename '/' -1) req_name)
  // 505:       string(until(mod_name '/' -1) req_name)
  frame->slots[5] /* temp__2 */ = create_closure(entry__build_dependencies_11, 0);
  // 506: :
  // 507:   if
  // 508:     ||
  // 509:       do_build_static_executable
  // 510:       do_build_codeblocks_project
  // 511:       do_list_dependencies
  // 512:     :
  // 513:       compile_module resolve_filename(argument) argument
  // 514:     :
  // 515:       if do_compile_c:
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__build_dependencies_22, 0);
  // 499: if
  // 500:   argument .has_prefix. "./":
  // 501:     if mode == EXE:
  // 502:       $req_name range(argument 3 -1)
  // 503:       compile_module
  // 504:         string(until(mod_filename '/' -1) req_name)
  // 505:         string(until(mod_name '/' -1) req_name)
  // 506:   :
  // 507:     if
  // 508:       ||
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
  // 518: ... : !libraries(argument .truncate_from. '/') true
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_dependencies_36, 0);
  // 518: if do_compile_c: !libraries(argument .truncate_from. '/') true
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
  // 491: ... line .has_prefix. "/// "
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
  // 491: unless line .has_prefix. "/// " return
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
  // 492: behind &line ' '
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
  // 493: trim &line
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
  // 494: $command line .truncate_from. WHITESPACE
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
  // 495: $argument line .behind. WHITESPACE
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
  // 498: ... :
  // 499:   if
  // 500:     argument .has_prefix. "./":
  // 501:       if mode == EXE:
  // 502:         $req_name range(argument 3 -1)
  // 503:         compile_module
  // 504:           string(until(mod_filename '/' -1) req_name)
  // 505:           string(until(mod_name '/' -1) req_name)
  // 506:     :
  // 507:       if
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__build_dependencies_9, 0);
  // 517: ... :
  // 518:   if do_compile_c: !libraries(argument .truncate_from. '/') true
  frame->slots[8] /* temp__2 */ = create_closure(entry__build_dependencies_35, 0);
  // 496: case
  // 497:   command
  // 498:   "require":
  // 499:     if
  // 500:       argument .has_prefix. "./":
  // 501:         if mode == EXE:
  // 502:           $req_name range(argument 3 -1)
  // 503:           compile_module
  // 504:             string(until(mod_filename '/' -1) req_name)
  // 505:             string(until(mod_name '/' -1) req_name)
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
static void entry__compile_module_1(void) {
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
  // 529: ... :
  // 530:   (
  // 531:     submodule_names # no paths; no extensions
  // 532:     do_compile_c = true
  // 533:     suffix = "" # a hyphen followed by the platform name
  // 534:   )
  // 535:   $$modification_time undefined
  // 536:   $$sim_filenames empty_list
  // 537:   for_each submodule_names: (submodule_name)
  // 538:     $meta_level meta_levels(submodule_name)
  // ...
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_module_2, -1);
  // 529: $compile_submodule:
  // 530:   (
  // 531:     submodule_names # no paths; no extensions
  // 532:     do_compile_c = true
  // 533:     suffix = "" # a hyphen followed by the platform name
  // 534:   )
  // 535:   $$modification_time undefined
  // 536:   $$sim_filenames empty_list
  // 537:   for_each submodule_names: (submodule_name)
  // 538:     $meta_level meta_levels(submodule_name)
  // ...
  initialize_future(frame->slots[3] /* compile_submodule */, frame->slots[6] /* temp__1 */);
  // 588: lookup $mod_info mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 1;
  myself = var._lookup;
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
  // 535: $$modification_time undefined
  ((CELL *)frame->slots[6])->contents /* modification_time */ = get__undefined();
  // 536: $$sim_filenames empty_list
  ((CELL *)frame->slots[7])->contents /* sim_filenames */ = get__empty_list();
  // 537: ... : (submodule_name)
  // 538:   $meta_level meta_levels(submodule_name)
  // 539:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 540:   if meta_level > 0 && not(do_omit_meta):
  // 541:     compile_meta_module submodule_filename submodule_name meta_level
  // 542:   $sim_filename string(submodule_filename ".sim")
  // 543:   push &sim_filenames sim_filename
  // 544:   $sim_info stat(sim_filename)
  // 545:   unless sim_info.is_defined:
  // 546:     Error "
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_module_3, 1);
  // 537: for_each submodule_names: (submodule_name)
  // 538:   $meta_level meta_levels(submodule_name)
  // 539:   $submodule_filename string(until(mod_filename '/' -1) submodule_name)
  // 540:   if meta_level > 0 && not(do_omit_meta):
  // 541:     compile_meta_module submodule_filename submodule_name meta_level
  // 542:   $sim_filename string(submodule_filename ".sim")
  // 543:   push &sim_filenames sim_filename
  // 544:   $sim_info stat(sim_filename)
  // 545:   unless sim_info.is_defined:
  // 546:     Error "
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
  // 553: !modification_time modification_time_of(sim_info)
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
  // 538: $meta_level meta_levels(submodule_name)
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
  // 539: ... 1
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
  // 539: ... until(mod_filename '/' -1)
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
  // 539: $submodule_filename string(until(mod_filename '/' -1) submodule_name)
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
  // 540: ... meta_level > 0
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
  // 540: ... meta_level > 0 && not(do_omit_meta)
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
  // 540: ... not(do_omit_meta)
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
  // 540: ... not(do_omit_meta)
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
  // 540: ... :
  // 541:   compile_meta_module submodule_filename submodule_name meta_level
  frame->slots[10] /* temp__3 */ = create_closure(entry__compile_module_12, 0);
  // 540: if meta_level > 0 && not(do_omit_meta):
  // 541:   compile_meta_module submodule_filename submodule_name meta_level
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
  // 541: compile_meta_module submodule_filename submodule_name meta_level
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
static void cont__compile_module_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 542: $sim_filename string(submodule_filename ".sim")
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
  // 543: push &sim_filenames sim_filename
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
  // 544: $sim_info stat(sim_filename)
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
  // 545: ... sim_info.is_defined
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
  // 545: ... :
  // 546:   Error "
  // 547:     Failed to open file "@(sim_filename)"!@
  frame->slots[9] /* temp__2 */ = create_closure(entry__compile_module_18, 0);
  // 545: unless sim_info.is_defined:
  // 546:   Error "
  // 547:     Failed to open file "@(sim_filename)"!@
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
  // 546: ... "
  // 547:   Failed to open file "@(sim_filename)"!@
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
  // 546: Error "
  // 547:   Failed to open file "@(sim_filename)"!@
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
  // 550: modification_time.is_undefined
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
  // 551: modification_time_of(sim_info) > modification_time
  frame->slots[10] /* temp__3 */ = create_closure(entry__compile_module_23, 0);
  // 549: ||
  // 550:   modification_time.is_undefined
  // 551:   modification_time_of(sim_info) > modification_time
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
  // 551: modification_time_of(sim_info)
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
  // 551: modification_time_of(sim_info) > modification_time
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
  // 551: modification_time_of(sim_info) > modification_time
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
  // 552: :
  // 553:   !modification_time modification_time_of(sim_info)
  frame->slots[11] /* temp__4 */ = create_closure(entry__compile_module_27, 0);
  // 548: if
  // 549:   ||
  // 550:     modification_time.is_undefined
  // 551:     modification_time_of(sim_info) > modification_time
  // 552:   :
  // 553:     !modification_time modification_time_of(sim_info)
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
  // 554: $c_filename string(mod_filename suffix ".c")
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
  // 555: $c_info stat(c_filename)
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
  // 556: ... : !c_sources(c_filename) true
  frame->slots[11] /* temp__1 */ = create_closure(entry__compile_module_32, 0);
  // 556: if do_compile_c: !c_sources(c_filename) true
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
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // c_filename: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* c_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 556: ... !c_sources(c_filename) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 556: ... !c_sources(c_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
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
  // 557: $$c_buf undefined
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
  // 561: c_info.is_undefined
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
  // 562: modification_time > modification_time_of(c_info)
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
  // 562: ... modification_time_of(c_info)
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
  // 562: modification_time > modification_time_of(c_info)
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
  // 562: modification_time > modification_time_of(c_info)
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
  // 563: :
  // 564:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 565:   if verbose: ewriteln "build module " module_name suffix
  // 566:   collect_output $c_source: sim2c sim_filenames
  // 567:   collect_output !c_buf: create_imports c_source
  // 568:   save c_filename c_buf.to_utf8
  // 569:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[13] /* temp__3 */ = create_closure(entry__compile_module_42, 0);
  // 570: :
  // 571:   load !c_buf c_filename
  // 572:   $o_info stat(o_filename)
  // 573:   if
  // 574:     ||
  // 575:       o_info.is_undefined
  // 576:       modification_time_of(c_info) > modification_time_of(o_info)
  // 577:     :
  // 578:       if do_compile_c: compile_c c_filename o_filename
  // 579:     :
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__compile_module_58, 0);
  // 558: if
  // 559:   ||
  // 560:     do_rebuild
  // 561:     c_info.is_undefined
  // 562:     modification_time > modification_time_of(c_info)
  // 563:   :
  // 564:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 565:     if verbose: ewriteln "build module " module_name suffix
  // 566:     collect_output $c_source: sim2c sim_filenames
  // 567:     collect_output !c_buf: create_imports c_source
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
  // 585: !last_modification_time modification_time_of(o_info)
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
  // 578: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
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
  // 578: ... : compile_c c_filename o_filename
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_68, 0);
  // 578: if do_compile_c: compile_c c_filename o_filename
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
  // 582: last_modification_time.is_undefined
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
  // 583: modification_time_of(o_info) > last_modification_time
  frame->slots[3] /* temp__3 */ = create_closure(entry__compile_module_71, 0);
  // 581: ||
  // 582:   last_modification_time.is_undefined
  // 583:   modification_time_of(o_info) > last_modification_time
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
  // 583: modification_time_of(o_info)
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
  // 583: modification_time_of(o_info) > last_modification_time
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
  // 583: modification_time_of(o_info) > last_modification_time
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
  // 584: :
  // 585:   !last_modification_time modification_time_of(o_info)
  frame->slots[4] /* temp__4 */ = create_closure(entry__compile_module_75, 0);
  // 580: if
  // 581:   ||
  // 582:     last_modification_time.is_undefined
  // 583:     modification_time_of(o_info) > last_modification_time
  // 584:   :
  // 585:     !last_modification_time modification_time_of(o_info)
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
  define__sim2c__module_name(create_future());
  frame->slots[8] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 564: ... '/' = "__"
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
  // 564: ... '.' = "__"
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
  // 564: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
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
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 565: ... : ewriteln "build module " module_name suffix
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_47, 0);
  // 565: if verbose: ewriteln "build module " module_name suffix
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
  // 565: ... ewriteln "build module " module_name suffix
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
  // 566: ... : sim2c sim_filenames
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_50, 0);
  // 566: collect_output $c_source: sim2c sim_filenames
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
  // 566: ... sim2c sim_filenames
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
  // 567: ... : create_imports c_source
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_52, 0);
  // 567: collect_output !c_buf: create_imports c_source
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
  // 567: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_module_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* c_buf */ = arguments->slots[0];
  // 568: ... c_buf.to_utf8
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
  // 568: save c_filename c_buf.to_utf8
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
  // 569: ... : compile_c c_filename o_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__compile_module_56, 0);
  // 569: if do_compile_c: compile_c c_filename o_filename
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
  // 569: ... compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
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
  // 571: load !c_buf c_filename
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
  // 572: $o_info stat(o_filename)
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
  // 575: o_info.is_undefined
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
  // 576: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_62, 0);
  // 574: ||
  // 575:   o_info.is_undefined
  // 576:   modification_time_of(c_info) > modification_time_of(o_info)
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
  // 576: ... modification_time_of(o_info)
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
  // 576: modification_time_of(c_info)
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
  // 576: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 576: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 577: :
  // 578:   if do_compile_c: compile_c c_filename o_filename
  frame->slots[9] /* temp__4 */ = create_closure(entry__compile_module_67, 0);
  // 579: :
  // 580:   if
  // 581:     ||
  // 582:       last_modification_time.is_undefined
  // 583:       modification_time_of(o_info) > last_modification_time
  // 584:     :
  // 585:       !last_modification_time modification_time_of(o_info)
  frame->slots[10] /* temp__5 */ = create_closure(entry__compile_module_69, 0);
  // 573: if
  // 574:   ||
  // 575:     o_info.is_undefined
  // 576:     modification_time_of(c_info) > modification_time_of(o_info)
  // 577:   :
  // 578:     if do_compile_c: compile_c c_filename o_filename
  // 579:   :
  // 580:     if
  // 581:       ||
  // 582:         last_modification_time.is_undefined
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
  // 586: build_dependencies mod_filename mod_name c_buf do_compile_c
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
static void cont__compile_module_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* mod_info */, arguments->slots[0]);
  // 589: ... mod_info.is_defined
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
  // 589: ... :
  // 590:   Error "
  // 591:     No source file(s) for module "@(mod_name)" found!@
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_80, 0);
  // 589: unless mod_info.is_defined:
  // 590:   Error "
  // 591:     No source file(s) for module "@(mod_name)" found!@
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
  // 590: ... "
  // 591:   No source file(s) for module "@(mod_name)" found!@
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
  // 590: Error "
  // 591:   No source file(s) for module "@(mod_name)" found!@
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
  // 592: $o_filename append(mod_filename ".o")
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
  // 593: ... objects(o_filename)
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
  // 593: if objects(o_filename) return
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
  // 594: !objects(o_filename) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 594: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* o_filename */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
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
  // 596: mod_info.is_empty
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
  // 596: ... :
  // 597:   compile_submodule list(truncate_until(mod_name '/' -1))
  // 598:   if do_list_dependencies: push &dependencies string(mod_filename ".c")
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_91, 0);
  // 599: :
  // 600:   do:
  // 601:     $$best_platform undefined
  // 602:     $$best_priority 999
  // 603:     for_each mod_info: (platform _filenames)
  // 604:       $priority platform_priority(platform)
  // 605:       if priority.is_defined && priority < best_priority:
  // 606:         !best_platform platform
  // 607:         !best_priority priority
  // 608:     for_each mod_info: (platform filenames)
  // ...
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_99, 0);
  // 595: if
  // 596:   mod_info.is_empty:
  // 597:     compile_submodule list(truncate_until(mod_name '/' -1))
  // 598:     if do_list_dependencies: push &dependencies string(mod_filename ".c")
  // 599:   :
  // 600:     do:
  // 601:       $$best_platform undefined
  // 602:       $$best_priority 999
  // 603:       for_each mod_info: (platform _filenames)
  // 604:         $priority platform_priority(platform)
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
  // 628: $$dependency string(mod_filename "-" platform ".c")
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
  // 629: $platforms used_by(platform)
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
  // 630: ... platforms.is_defined
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
  // 630: ... :
  // 631:   for_each platforms: (plat) write_to &dependency " #" plat
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_134, 0);
  // 630: if platforms.is_defined:
  // 631:   for_each platforms: (plat) write_to &dependency " #" plat
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
  // 631: ... write_to &dependency " #" plat
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
  // 631: ... : (plat) write_to &dependency " #" plat
  frame->slots[2] /* temp__1 */ = create_closure(entry__compile_module_135, 1);
  // 631: for_each platforms: (plat) write_to &dependency " #" plat
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
  // 632: push &dependencies dependency
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
  // 614: $$used_by empty_table
  ((CELL *)frame->slots[2])->contents /* used_by */ = get__empty_table();
  // 615: ... : (supported_platform _parent_platform)
  // 616:   $$best_platform undefined
  // 617:   $$best_priority 999
  // 618:   for_each mod_info: (platform _filenames)
  // 619:     $priority platform_specific_priority(supported_platform platform)
  // 620:     if priority.is_defined && priority < best_priority:
  // 621:       !best_platform platform
  // 622:       !best_priority priority
  // 623:   if best_platform.is_defined:
  // 624:     $$ub default_value(used_by(best_platform) empty_list)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_114, 2);
  // 615: for_each supported_platforms: (supported_platform _parent_platform)
  // 616:   $$best_platform undefined
  // 617:   $$best_priority 999
  // 618:   for_each mod_info: (platform _filenames)
  // 619:     $priority platform_specific_priority(supported_platform platform)
  // 620:     if priority.is_defined && priority < best_priority:
  // 621:       !best_platform platform
  // 622:       !best_priority priority
  // 623:   if best_platform.is_defined:
  // 624:     $$ub default_value(used_by(best_platform) empty_list)
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
  // 624: ... used_by(best_platform)
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
  // 624: $$ub default_value(used_by(best_platform) empty_list)
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
  // 625: push &ub supported_platform
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
  // 626: !used_by(best_platform) ub
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* ub */;
  // 626: !used_by(best_platform)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* best_platform */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
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
  // 616: $$best_platform undefined
  ((CELL *)frame->slots[4])->contents /* best_platform */ = get__undefined();
  // 617: $$best_priority 999
  ((CELL *)frame->slots[5])->contents /* best_priority */ = number__999;
  // 618: ... : (platform _filenames)
  // 619:   $priority platform_specific_priority(supported_platform platform)
  // 620:   if priority.is_defined && priority < best_priority:
  // 621:     !best_platform platform
  // 622:     !best_priority priority
  frame->slots[6] /* temp__1 */ = create_closure(entry__compile_module_115, 2);
  // 618: for_each mod_info: (platform _filenames)
  // 619:   $priority platform_specific_priority(supported_platform platform)
  // 620:   if priority.is_defined && priority < best_priority:
  // 621:     !best_platform platform
  // 622:     !best_priority priority
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
  // 621: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 622: !best_priority priority
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
  // 619: $priority platform_specific_priority(supported_platform platform)
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
  // 620: ... priority.is_defined
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
  // 620: ... priority < best_priority
  frame->slots[8] /* temp__3 */ = create_closure(entry__compile_module_118, 0);
  // 620: ... priority.is_defined && priority < best_priority
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
  // 620: ... priority < best_priority
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
  // 620: ... priority < best_priority
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
  // 620: ... :
  // 621:   !best_platform platform
  // 622:   !best_priority priority
  frame->slots[9] /* temp__4 */ = create_closure(entry__compile_module_121, 0);
  // 620: if priority.is_defined && priority < best_priority:
  // 621:   !best_platform platform
  // 622:   !best_priority priority
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
  // 623: ... best_platform.is_defined
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
  // 623: ... :
  // 624:   $$ub default_value(used_by(best_platform) empty_list)
  // 625:   push &ub supported_platform
  // 626:   !used_by(best_platform) ub
  frame->slots[7] /* temp__2 */ = create_closure(entry__compile_module_124, 0);
  // 623: if best_platform.is_defined:
  // 624:   $$ub default_value(used_by(best_platform) empty_list)
  // 625:   push &ub supported_platform
  // 626:   !used_by(best_platform) ub
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
  // 627: ... : (platform _filenames)
  // 628:   $$dependency string(mod_filename "-" platform ".c")
  // 629:   $platforms used_by(platform)
  // 630:   if platforms.is_defined:
  // 631:     for_each platforms: (plat) write_to &dependency " #" plat
  // 632:   push &dependencies dependency
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_130, 2);
  // 627: for_each mod_info: (platform _filenames)
  // 628:   $$dependency string(mod_filename "-" platform ".c")
  // 629:   $platforms used_by(platform)
  // 630:   if platforms.is_defined:
  // 631:     for_each platforms: (plat) write_to &dependency " #" plat
  // 632:   push &dependencies dependency
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_info */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_module_96(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // mod_filename: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* mod_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 598: ... string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = string__2d7981f4e6782ba6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compile_module_97;
}
static void cont__compile_module_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 598: ... push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._dependencies;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compile_module_98;
}
static void cont__compile_module_98(void) {
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
static void entry__compile_module_91(void) {
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
  // 597: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compile_module_92;
}
static void cont__compile_module_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 597: ... truncate_until(mod_name '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* mod_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__compile_module_93;
}
static void cont__compile_module_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 597: ... list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__compile_module_94;
}
static void cont__compile_module_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 597: compile_submodule list(truncate_until(mod_name '/' -1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = frame->slots[0] /* compile_submodule */;
  func = myself->type;
  frame->cont = cont__compile_module_95;
}
static void cont__compile_module_95(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: ... : push &dependencies string(mod_filename ".c")
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_96, 0);
  // 598: if do_list_dependencies: push &dependencies string(mod_filename ".c")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._do_list_dependencies;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
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
  // 600: ... :
  // 601:   $$best_platform undefined
  // 602:   $$best_priority 999
  // 603:   for_each mod_info: (platform _filenames)
  // 604:     $priority platform_priority(platform)
  // 605:     if priority.is_defined && priority < best_priority:
  // 606:       !best_platform platform
  // 607:       !best_priority priority
  // 608:   for_each mod_info: (platform filenames)
  // 609:     compile_submodule
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_100, 0);
  // 600: do:
  // 601:   $$best_platform undefined
  // 602:   $$best_priority 999
  // 603:   for_each mod_info: (platform _filenames)
  // 604:     $priority platform_priority(platform)
  // 605:     if priority.is_defined && priority < best_priority:
  // 606:       !best_platform platform
  // 607:       !best_priority priority
  // 608:   for_each mod_info: (platform filenames)
  // 609:     compile_submodule
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
  // 611: platform == best_platform
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
  // 612: string("-" platform)
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
  // 609: compile_submodule
  // 610:   filenames
  // 611:   platform == best_platform
  // 612:   string("-" platform)
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
  // 601: $$best_platform undefined
  ((CELL *)frame->slots[2])->contents /* best_platform */ = get__undefined();
  // 602: $$best_priority 999
  ((CELL *)frame->slots[3])->contents /* best_priority */ = number__999;
  // 603: ... : (platform _filenames)
  // 604:   $priority platform_priority(platform)
  // 605:   if priority.is_defined && priority < best_priority:
  // 606:     !best_platform platform
  // 607:     !best_priority priority
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_module_101, 2);
  // 603: for_each mod_info: (platform _filenames)
  // 604:   $priority platform_priority(platform)
  // 605:   if priority.is_defined && priority < best_priority:
  // 606:     !best_platform platform
  // 607:     !best_priority priority
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
  // 606: !best_platform platform
  ((CELL *)frame->slots[0])->contents /* best_platform */ = frame->slots[1] /* platform */;
  // 607: !best_priority priority
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
  // 604: $priority platform_priority(platform)
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
  // 605: ... priority.is_defined
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
  // 605: ... priority < best_priority
  frame->slots[7] /* temp__3 */ = create_closure(entry__compile_module_104, 0);
  // 605: ... priority.is_defined && priority < best_priority
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
  // 605: ... priority < best_priority
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
  // 605: ... priority < best_priority
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
  // 605: ... :
  // 606:   !best_platform platform
  // 607:   !best_priority priority
  frame->slots[8] /* temp__4 */ = create_closure(entry__compile_module_107, 0);
  // 605: if priority.is_defined && priority < best_priority:
  // 606:   !best_platform platform
  // 607:   !best_priority priority
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
  // 608: ... : (platform filenames)
  // 609:   compile_submodule
  // 610:     filenames
  // 611:     platform == best_platform
  // 612:     string("-" platform)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_module_109, 2);
  // 608: for_each mod_info: (platform filenames)
  // 609:   compile_submodule
  // 610:     filenames
  // 611:     platform == best_platform
  // 612:     string("-" platform)
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
  // 613: ... :
  // 614:   $$used_by empty_table
  // 615:   for_each supported_platforms: (supported_platform _parent_platform)
  // 616:     $$best_platform undefined
  // 617:     $$best_priority 999
  // 618:     for_each mod_info: (platform _filenames)
  // 619:       $priority platform_specific_priority(supported_platform platform)
  // 620:       if priority.is_defined && priority < best_priority:
  // 621:         !best_platform platform
  // 622:         !best_priority priority
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compile_module_113, 0);
  // 613: if do_list_dependencies:
  // 614:   $$used_by empty_table
  // 615:   for_each supported_platforms: (supported_platform _parent_platform)
  // 616:     $$best_platform undefined
  // 617:     $$best_priority 999
  // 618:     for_each mod_info: (platform _filenames)
  // 619:       $priority platform_specific_priority(supported_platform platform)
  // 620:       if priority.is_defined && priority < best_priority:
  // 621:         !best_platform platform
  // 622:         !best_priority priority
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
  // 643: ... string(path '/' name)
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
  // 643: ... string(mod_path '/' name)
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
  // 643: compile_module string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_modules_1(void) {
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
  // 639: ... string(mod_path '/')
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
  // 639: add_module_infos $directories $modules path string(mod_path '/')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 2;
  myself = var._add_module_infos;
  func = myself->type;
  frame->cont = cont__compile_modules_3;
}
static void cont__compile_modules_3(void) {
  if (argument_count != 2) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  // 639: ... directories
  initialize_future(frame->slots[2] /* directories */, frame->slots[5] /* temp__2 */);
  // 639: ... modules
  initialize_future(frame->slots[3] /* modules */, frame->slots[6] /* temp__3 */);
  // 640: ... : (name)
  // 641:   compile_modules string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_modules_4, 1);
  // 640: for_each directories: (name)
  // 641:   compile_modules string(path '/' name) string(mod_path '/' name)
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
  // 641: ... string(path '/' name)
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
  // 641: ... string(mod_path '/' name)
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
  // 641: compile_modules string(path '/' name) string(mod_path '/' name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compile_modules_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: ... : (name)
  // 643:   compile_module string(path '/' name) string(mod_path '/' name)
  frame->slots[4] /* temp__1 */ = create_closure(entry__compile_modules_8, 1);
  // 642: for_each modules: (name)
  // 643:   compile_module string(path '/' name) string(mod_path '/' name)
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
  // 651: $path environment("LD_LIBRARY_PATH")
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
  // 652: ... path.is_defined
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
  // 652: ... : ewriteln "LD_LIBRARY_PATH=@(path)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__show_file_list_6, 0);
  // 652: if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
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
  // 652: ... "LD_LIBRARY_PATH=@(path)"
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
  // 652: ... ewriteln "LD_LIBRARY_PATH=@(path)"
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
  // 653: ... serialize(objects)
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
  // 653: ewriteln "included object files: " serialize(objects)
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
  // 654: ... serialize(libraries)
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
  // 654: ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d2a77fcc4263ea03;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__show_file_list_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: if do_show_debug_infos:
  // 651:   $path environment("LD_LIBRARY_PATH")
  // 652:   if path.is_defined: ewriteln "LD_LIBRARY_PATH=@(path)"
  // 653:   ewriteln "included object files: " serialize(objects)
  // 654:   ewriteln "needed libraries: " serialize(libraries)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_show_debug_infos();
  arguments->slots[1] = func__show_file_list_2;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__library_paths_and_file_list_1(void) {
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
  // 657: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__library_paths_and_file_list_2;
}
static void cont__library_paths_and_file_list_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: $$library_paths empty_list
  ((CELL *)frame->slots[0])->contents /* library_paths */ = get__empty_list();
  // 659: $$object_files empty_list
  ((CELL *)frame->slots[1])->contents /* object_files */ = get__empty_list();
  // 660: $$library_files empty_list
  ((CELL *)frame->slots[2])->contents /* library_files */ = get__empty_list();
  // 661: $paths environment("LD_LIBRARY_PATH")
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
  // 662: ... paths.is_defined
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
  // 662: ... :
  // 663:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__library_paths_and_file_list_5, 0);
  // 662: if paths.is_defined:
  // 663:   for_each paths .split. ':': (path) push &library_paths "-L@(path)"
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
  // 663: ... "-L@(path)"
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
  // 663: ... push &library_paths "-L@(path)"
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
  // 663: ... paths .split. ':'
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
  // 663: ... : (path) push &library_paths "-L@(path)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__library_paths_and_file_list_7, 1);
  // 663: for_each paths .split. ':': (path) push &library_paths "-L@(path)"
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
  // 664: ... : ewriteln "library paths: " serialize(library_paths)
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_12, 0);
  // 664: if do_show_debug_infos: ewriteln "library paths: " serialize(library_paths)
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
  // 664: ... serialize(library_paths)
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
  // 664: ... ewriteln "library paths: " serialize(library_paths)
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
  // 665: ... : (object) push &object_files object
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_16, 1);
  // 665: for_each objects: (object) push &object_files object
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
  // 665: ... push &object_files object
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
  // 666: ... : (library)
  // 667:   push
  // 668:     &library_files
  // 669:     if
  // 670:       library .has_prefix. "sim-"
  // 671:       ->
  // 672:         case
  // 673:           operating_system()
  // 674:           "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:           -> "-l@(library)-@(MAJOR)"
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__library_paths_and_file_list_19, 1);
  // 666: for_each libraries: (library)
  // 667:   push
  // 668:     &library_files
  // 669:     if
  // 670:       library .has_prefix. "sim-"
  // 671:       ->
  // 672:         case
  // 673:           operating_system()
  // 674:           "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:           -> "-l@(library)-@(MAJOR)"
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
  // 670: library .has_prefix. "sim-"
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
  // 671: ->
  // 672:   case
  // 673:     operating_system()
  // 674:     "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:     -> "-l@(library)-@(MAJOR)"
  frame->slots[4] /* temp__3 */ = create_closure(entry__library_paths_and_file_list_21, 0);
  // 676: ->
  // 677:   if
  // 678:     library .contains. '.'
  // 679:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 680:       # Linux only
  // 681:     -> "-l@(library)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_34, 0);
  // 669: if
  // 670:   library .has_prefix. "sim-"
  // 671:   ->
  // 672:     case
  // 673:       operating_system()
  // 674:       "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:       -> "-l@(library)-@(MAJOR)"
  // 676:   ->
  // 677:     if
  // 678:       library .contains. '.'
  // ...
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
  // 673: operating_system()
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
  // 674: "linux", "bsd"
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
  // 674: ... -> "-l:lib@(library).so.@(MAJOR)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_26, 0);
  // 675: -> "-l@(library)-@(MAJOR)"
  frame->slots[5] /* temp__5 */ = create_closure(entry__library_paths_and_file_list_30, 0);
  // 672: case
  // 673:   operating_system()
  // 674:   "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:   -> "-l@(library)-@(MAJOR)"
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
  // 674: ... "-l:lib@(library).so.@(MAJOR)"
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
  // 674: ... -> "-l:lib@(library).so.@(MAJOR)"
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
  // 675: ... "-l@(library)-@(MAJOR)"
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
  // 675: -> "-l@(library)-@(MAJOR)"
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
  // 671: ->
  // 672:   case
  // 673:     operating_system()
  // 674:     "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:     -> "-l@(library)-@(MAJOR)"
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
  // 678: library .contains. '.'
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
  // 679: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 680:   # Linux only
  frame->slots[3] /* temp__3 */ = create_closure(entry__library_paths_and_file_list_36, 0);
  // 681: -> "-l@(library)"
  frame->slots[4] /* temp__4 */ = create_closure(entry__library_paths_and_file_list_40, 0);
  // 677: if
  // 678:   library .contains. '.'
  // 679:   -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 680:     # Linux only
  // 681:   -> "-l@(library)"
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
  // 679: ... library .before. '.'
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
  // 679: ... library .behind. '.'
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
  // 679: ... "-l:lib@(library .before. '.').so.@(library .behind. '.')"
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
  // 679: -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 680:   # Linux only
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
  // 681: ... "-l@(library)"
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
  // 681: -> "-l@(library)"
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
  // 676: ->
  // 677:   if
  // 678:     library .contains. '.'
  // 679:     -> "-l:lib@(library .before. '.').so.@(library .behind. '.')"
  // 680:       # Linux only
  // 681:     -> "-l@(library)"
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
  // 667: push
  // 668:   &library_files
  // 669:   if
  // 670:     library .has_prefix. "sim-"
  // 671:     ->
  // 672:       case
  // 673:         operating_system()
  // 674:         "linux", "bsd" -> "-l:lib@(library).so.@(MAJOR)"
  // 675:         -> "-l@(library)-@(MAJOR)"
  // 676:     ->
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
  // 682: ... append(object_files library_files)
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
  // 682: append library_paths append(object_files library_files)
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
  // 725: ... write_timing_info "collecting imports"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__868d47f2e5ba5079;
  result_count = frame->caller_result_count;
  myself = get__write_timing_info();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_imports_1(void) {
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
  // 687: ... : (buf)
  // 688:   $$s undefined
  // 689:   for_each buf: (idx chr)
  // 690:     if
  // 691:       s.is_defined:
  // 692:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:           $symbol range(buf s idx-1)
  // 694:           !s undefined
  // 695:           unless already_checked(symbol):
  // 696:             !already_checked(symbol) true
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__create_imports_2, 1);
  // 687: $collect_declarations: (buf)
  // 688:   $$s undefined
  // 689:   for_each buf: (idx chr)
  // 690:     if
  // 691:       s.is_defined:
  // 692:         unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:           $symbol range(buf s idx-1)
  // 694:           !s undefined
  // 695:           unless already_checked(symbol):
  // 696:             !already_checked(symbol) true
  // ...
  initialize_future(frame->slots[2] /* collect_declarations */, frame->slots[5] /* temp__1 */);
  // 685: $$already_checked empty_set
  ((CELL *)frame->slots[1])->contents /* already_checked */ = get__empty_set();
  // 720: ... : collect_declarations source
  frame->slots[5] /* temp__1 */ = create_closure(entry__create_imports_63, 0);
  // 720: collect_output $imports: collect_declarations source
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
  // 718: ... !s idx
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
  // 701: declaration(1)
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
  // 701: declaration(1) != '#'
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
  // 701: declaration(1) != '#'
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
  // 699: $do_import
  // 700:   &&
  // 701:     declaration(1) != '#'
  // 702:     not(declaration .has_prefix. "typedef")
  // 703:     not(declaration .has_prefix. "REGISTER")
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
  // 702: ... declaration .has_prefix. "typedef"
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
  // 702: not(declaration .has_prefix. "typedef")
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
  // 703: not(declaration .has_prefix. "REGISTER")
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
  // 703: ... declaration .has_prefix. "REGISTER"
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
  // 703: not(declaration .has_prefix. "REGISTER")
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
  // 703: not(declaration .has_prefix. "REGISTER")
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
  // 706: ->
  // 707:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 708:   :
  // 709:     collect_declarations declaration .truncate_from. '{'
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_imports_35, 0);
  // 710: -> declaration .has_prefix. "typedef struct":
  // 711:   for_each_line between(declaration '{' '}').trim: (line)
  // 712:     collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_imports_43, 0);
  // 713: :
  // 714:   collect_declarations declaration
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_imports_52, 0);
  // 705: cond
  // 706:   ->
  // 707:     declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 708:     :
  // 709:       collect_declarations declaration .truncate_from. '{'
  // 710:   -> declaration .has_prefix. "typedef struct":
  // 711:     for_each_line between(declaration '{' '}').trim: (line)
  // 712:       collect_declarations until(line ' ' -1)
  // 713:   :
  // 714:     collect_declarations declaration
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
  // 712: ... 1
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
  // 712: ... until(line ' ' -1)
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
  // 712: collect_declarations until(line ' ' -1)
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
  // 711: ... between(declaration '{' '}')
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
  // 711: ... between(declaration '{' '}').trim
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
  // 711: ... : (line)
  // 712:   collect_declarations until(line ' ' -1)
  frame->slots[4] /* temp__3 */ = create_closure(entry__create_imports_49, 1);
  // 711: for_each_line between(declaration '{' '}').trim: (line)
  // 712:   collect_declarations until(line ' ' -1)
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
  // 709: ... declaration .truncate_from. '{'
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
  // 709: collect_declarations declaration .truncate_from. '{'
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
  // 707: declaration(1)
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
  // 707: declaration(1) == '#'
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
  // 707: ... declaration .has_prefix. "REGISTER"
  frame->slots[5] /* temp__4 */ = create_closure(entry__create_imports_38, 0);
  // 707: declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
  // 707: ... declaration .has_prefix. "REGISTER"
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
  // 707: ... declaration .has_prefix. "REGISTER"
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
  // 708: :
  // 709:   collect_declarations declaration .truncate_from. '{'
  frame->slots[6] /* temp__5 */ = create_closure(entry__create_imports_41, 0);
  // 706: ->
  // 707:   declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // 708:   :
  // 709:     collect_declarations declaration .truncate_from. '{'
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
  // 710: ... declaration .has_prefix. "typedef struct"
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
  // 710: ... :
  // 711:   for_each_line between(declaration '{' '}').trim: (line)
  // 712:     collect_declarations until(line ' ' -1)
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_imports_46, 0);
  // 710: -> declaration .has_prefix. "typedef struct":
  // 711:   for_each_line between(declaration '{' '}').trim: (line)
  // 712:     collect_declarations until(line ' ' -1)
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
  // 714: collect_declarations declaration
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
  // 715: if do_import: write "IMPORT "
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
  // 715: ... write "IMPORT "
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
  // 716: write declaration
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
  // 696: !already_checked(symbol) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 696: !already_checked(symbol)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* symbol */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
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
  // 697: $declaration runtime_symbols(symbol)
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
  // 698: ... declaration.is_defined
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
  // 698: ... :
  // 699:   $do_import
  // 700:     &&
  // 701:       declaration(1) != '#'
  // 702:       not(declaration .has_prefix. "typedef")
  // 703:       not(declaration .has_prefix. "REGISTER")
  // 704:   
  // 705:   cond
  // 706:     ->
  // 707:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__create_imports_21, 0);
  // 698: if declaration.is_defined:
  // 699:   $do_import
  // 700:     &&
  // 701:       declaration(1) != '#'
  // 702:       not(declaration .has_prefix. "typedef")
  // 703:       not(declaration .has_prefix. "REGISTER")
  // 704:   
  // 705:   cond
  // 706:     ->
  // 707:       declaration(1) == '#' || declaration .has_prefix. "REGISTER"
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
  // 693: ... idx-1
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
  // 693: $symbol range(buf s idx-1)
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
  // 694: !s undefined
  ((CELL *)frame->slots[1])->contents /* s */ = get__undefined();
  // 695: ... already_checked(symbol)
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
  // 695: ... :
  // 696:   !already_checked(symbol) true
  // 697:   $declaration runtime_symbols(symbol)
  // 698:   if declaration.is_defined:
  // 699:     $do_import
  // 700:       &&
  // 701:         declaration(1) != '#'
  // 702:         not(declaration .has_prefix. "typedef")
  // 703:         not(declaration .has_prefix. "REGISTER")
  // 704:     
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__create_imports_17, 0);
  // 695: unless already_checked(symbol):
  // 696:   !already_checked(symbol) true
  // 697:   $declaration runtime_symbols(symbol)
  // 698:   if declaration.is_defined:
  // 699:     $do_import
  // 700:       &&
  // 701:         declaration(1) != '#'
  // 702:         not(declaration .has_prefix. "typedef")
  // 703:         not(declaration .has_prefix. "REGISTER")
  // 704:     
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
  // 692: ... chr.is_a_letter
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
  // 692: ... chr == '_' || chr.is_a_digit
  frame->slots[8] /* temp__3 */ = create_closure(entry__create_imports_7, 0);
  // 692: ... chr.is_a_letter || chr == '_' || chr.is_a_digit
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
  // 692: ... chr == '_'
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
  // 692: ... chr.is_a_digit
  frame->slots[3] /* temp__3 */ = create_closure(entry__create_imports_9, 0);
  // 692: ... chr == '_' || chr.is_a_digit
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
  // 692: ... chr.is_a_digit
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
  // 692: ... chr.is_a_digit
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
  // 692: ... chr == '_' || chr.is_a_digit
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
  // 692: ... :
  // 693:   $symbol range(buf s idx-1)
  // 694:   !s undefined
  // 695:   unless already_checked(symbol):
  // 696:     !already_checked(symbol) true
  // 697:     $declaration runtime_symbols(symbol)
  // 698:     if declaration.is_defined:
  // 699:       $do_import
  // 700:         &&
  // 701:           declaration(1) != '#'
  // ...
  frame->slots[9] /* temp__4 */ = create_closure(entry__create_imports_13, 0);
  // 692: unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:   $symbol range(buf s idx-1)
  // 694:   !s undefined
  // 695:   unless already_checked(symbol):
  // 696:     !already_checked(symbol) true
  // 697:     $declaration runtime_symbols(symbol)
  // 698:     if declaration.is_defined:
  // 699:       $do_import
  // 700:         &&
  // 701:           declaration(1) != '#'
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
  // 718: ... chr.is_a_letter
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
  // 718: ... chr == '_'
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_imports_59, 0);
  // 718: ... chr.is_a_letter || chr == '_'
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
  // 718: ... chr == '_'
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
  // 718: ... chr == '_'
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
  // 718: ... : !s idx
  frame->slots[6] /* temp__4 */ = create_closure(entry__create_imports_62, 0);
  // 718: if chr.is_a_letter || chr == '_': !s idx
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
  // 691: s.is_defined
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
  // 691: ... :
  // 692:   unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:     $symbol range(buf s idx-1)
  // 694:     !s undefined
  // 695:     unless already_checked(symbol):
  // 696:       !already_checked(symbol) true
  // 697:       $declaration runtime_symbols(symbol)
  // 698:       if declaration.is_defined:
  // 699:         $do_import
  // 700:           &&
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__create_imports_5, 0);
  // 717: :
  // 718:   if chr.is_a_letter || chr == '_': !s idx
  frame->slots[8] /* temp__3 */ = create_closure(entry__create_imports_57, 0);
  // 690: if
  // 691:   s.is_defined:
  // 692:     unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:       $symbol range(buf s idx-1)
  // 694:       !s undefined
  // 695:       unless already_checked(symbol):
  // 696:         !already_checked(symbol) true
  // 697:         $declaration runtime_symbols(symbol)
  // 698:         if declaration.is_defined:
  // 699:           $do_import
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
  // 688: $$s undefined
  ((CELL *)frame->slots[3])->contents /* s */ = get__undefined();
  // 689: ... : (idx chr)
  // 690:   if
  // 691:     s.is_defined:
  // 692:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:         $symbol range(buf s idx-1)
  // 694:         !s undefined
  // 695:         unless already_checked(symbol):
  // 696:           !already_checked(symbol) true
  // 697:           $declaration runtime_symbols(symbol)
  // 698:           if declaration.is_defined:
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__create_imports_3, 2);
  // 689: for_each buf: (idx chr)
  // 690:   if
  // 691:     s.is_defined:
  // 692:       unless chr.is_a_letter || chr == '_' || chr.is_a_digit:
  // 693:         $symbol range(buf s idx-1)
  // 694:         !s undefined
  // 695:         unless already_checked(symbol):
  // 696:           !already_checked(symbol) true
  // 697:           $declaration runtime_symbols(symbol)
  // 698:           if declaration.is_defined:
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
  // 720: ... collect_declarations source
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
  // 721: $first_part source .before. "// INSERT HERE //"
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
  // 722: write first_part
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
  // 723: write imports
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
  // 724: ... length_of(first_part)
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
  // 724: ... length_of(first_part)+18
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
  // 724: ... 1
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
  // 724: ... range(source length_of(first_part)+18 -1)
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
  // 724: write range(source length_of(first_part)+18 -1)
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
  // 725: if do_time_passes: write_timing_info "collecting imports"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__create_imports_74;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compile_exe_1(void) {
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
  // 728: ... main_info.is_a_directory
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
  // 728: if main_info.is_a_directory: Error "Expected a source code file!"
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
  // 728: ... Error "Expected a source code file!"
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
  // 729: ... main_filename .has_suffix. ".sim"
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
  // 729: unless main_filename .has_suffix. ".sim":
  // 730:   Error "
  // 731:     Expected ".sim" file extension in source filename!@
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
  // 730: Error "
  // 731:   Expected ".sim" file extension in source filename!@
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
  // 733: $mod_filename main_filename .without_suffix. ".sim"
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
  // 734: ... 1
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
  // 734: $mod_name truncate_until(mod_filename '/' -1)
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
  // 735: body mod_filename mod_name
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
  // _define %sim2c::module_name mod_name
  define__sim2c__module_name(frame->slots[1] /* mod_name */);
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 739: %sim2c::module_name mod_name
  initialize_maybe_future(get__sim2c__module_name(), frame->slots[1] /* mod_name */);
  // 740: ... list(main_filename)
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
  // 740: sim2c list(main_filename)
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
static void entry__dump_source_or_check_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 738: compile_exe: (_mod_filename mod_name)
  // 739:   %sim2c::module_name mod_name
  // 740:   sim2c list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__dump_source_or_check_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
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
  // 750: ... write_timing_info "writing C-source"
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
  // 744: ... module_prefix.is_defined
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
  // 744: ... : append string(module_prefix '/') &mod_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__print_c_4, 0);
  // 744: if module_prefix.is_defined: append string(module_prefix '/') &mod_name
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
  // 744: ... string(module_prefix '/')
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
  // 744: ... append string(module_prefix '/') &mod_name
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
  // 745: ... :
  // 746:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 747:   sim2c list(main_filename)
  frame->slots[4] /* temp__1 */ = create_closure(entry__print_c_8, 0);
  // 745: collect_output $c_source:
  // 746:   %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 747:   sim2c list(main_filename)
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
  define__sim2c__module_name(create_future());
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 746: ... '/' = "__"
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
  // 746: ... '.' = "__"
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
  // 746: %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
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
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 747: ... list(main_filename)
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
  // 747: sim2c list(main_filename)
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
  // 748: ... : create_imports c_source
  frame->slots[4] /* temp__1 */ = create_closure(entry__print_c_15, 0);
  // 748: collect_output $c_buf: create_imports c_source
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
  // 748: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__print_c_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* c_buf */, arguments->slots[0]);
  // 749: write c_buf
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
  // 750: if do_time_passes: write_timing_info "writing C-source"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_time_passes();
  arguments->slots[1] = func__print_c_18;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__print_c_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: compile_exe: (_mod_filename $mod_name)
  // 744:   if module_prefix.is_defined: append string(module_prefix '/') &mod_name
  // 745:   collect_output $c_source:
  // 746:     %sim2c::module_name replace_all(mod_name '/' = "__" '.' = "__")
  // 747:     sim2c list(main_filename)
  // 748:   collect_output $c_buf: create_imports c_source
  // 749:   write c_buf
  // 750:   if do_time_passes: write_timing_info "writing C-source"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__print_c_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
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
  // 779: without_prefix &filename prefix_path
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
  // 780: without_prefix &filename '/'
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
  // 781: writeln filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__list_dependencies_1(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // prefix_path: 0
  frame->slots[0] /* prefix_path */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 753: !platform_specific_priority multi_dimensional_table(types::table types::table)
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
  // 754: for_each supported_platforms: (supported_platform _parent_platform)
  // 755:   $$platform supported_platform
  // 756:   $$priority 0
  // 757:   do: (-> break)
  // 758:     forever:
  // 759:       $plat supported_platforms(platform)
  // 760:       if plat.is_undefined break
  // 761:       inc &priority
  // 762:       !platform_specific_priority(supported_platform platform) priority
  // 763:       if plat == NONE break
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
  // 758: ... :
  // 759:   $plat supported_platforms(platform)
  // 760:   if plat.is_undefined break
  // 761:   inc &priority
  // 762:   !platform_specific_priority(supported_platform platform) priority
  // 763:   if plat == NONE break
  // 764:   !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__list_dependencies_5, 0);
  // 758: forever:
  // 759:   $plat supported_platforms(platform)
  // 760:   if plat.is_undefined break
  // 761:   inc &priority
  // 762:   !platform_specific_priority(supported_platform platform) priority
  // 763:   if plat == NONE break
  // 764:   !platform plat
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
  // 759: $plat supported_platforms(platform)
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
  // 760: ... plat.is_undefined
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
  // 760: if plat.is_undefined break
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
  // 761: inc &priority
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
  // 762: !platform_specific_priority(supported_platform platform) priority
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* priority */;
  // 762: !platform_specific_priority(supported_platform platform)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* supported_platform */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* platform */;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
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
  // 763: ... plat == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* plat */;
  arguments->slots[1] = var._NONE;
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
  // 763: if plat == NONE break
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
  // 764: !platform plat
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
  // 755: $$platform supported_platform
  ((CELL *)frame->slots[2])->contents /* platform */ = frame->slots[0] /* supported_platform */;
  // 756: $$priority 0
  ((CELL *)frame->slots[3])->contents /* priority */ = number__0;
  // 757: ... : (-> break)
  // 758:   forever:
  // 759:     $plat supported_platforms(platform)
  // 760:     if plat.is_undefined break
  // 761:     inc &priority
  // 762:     !platform_specific_priority(supported_platform platform) priority
  // 763:     if plat == NONE break
  // 764:     !platform plat
  frame->slots[4] /* temp__1 */ = create_closure(entry__list_dependencies_4, 0);
  // 757: do: (-> break)
  // 758:   forever:
  // 759:     $plat supported_platforms(platform)
  // 760:     if plat.is_undefined break
  // 761:     inc &priority
  // 762:     !platform_specific_priority(supported_platform platform) priority
  // 763:     if plat == NONE break
  // 764:     !platform plat
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
  // 766: main_info.is_a_directory
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
  // 765: if
  // 766:   main_info.is_a_directory:
  // 767:     %mode LIB
  // 768:     if verbose: ewriteln "list dependencies for " main_filename
  // 769:     compile_modules main_filename behind(main_filename '/' -1)
  // 770:   :
  // 771:     compile_exe: (mod_filename mod_name)
  // 772:       if verbose: ewriteln "list dependencies for " mod_filename
  // 773:       compile_module mod_filename mod_name
  // 774:     writeln "runtime/linker.c"
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
  // _define %mode LIB
  define__mode(var._LIB);
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 768: if verbose: ewriteln "list dependencies for " main_filename
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
  // 768: ... ewriteln "list dependencies for " main_filename
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
  // 769: ... 1
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
  // 769: ... behind(main_filename '/' -1)
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
  // 769: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = var._compile_modules;
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
  // 771: compile_exe: (mod_filename mod_name)
  // 772:   if verbose: ewriteln "list dependencies for " mod_filename
  // 773:   compile_module mod_filename mod_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__list_dependencies_24;
  result_count = 0;
  myself = var._compile_exe;
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
  // 772: ... : ewriteln "list dependencies for " mod_filename
  frame->slots[2] /* temp__1 */ = create_closure(entry__list_dependencies_25, 0);
  // 772: if verbose: ewriteln "list dependencies for " mod_filename
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
  // 772: ... ewriteln "list dependencies for " mod_filename
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
  // 773: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = frame->caller_result_count;
  myself = var._compile_module;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__list_dependencies_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 774: writeln "runtime/linker.c"
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
  // 775: writeln "runtime/memory.c"
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
  // 776: writeln "runtime/debugger.c"
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
  // 777: $prefix_path current_path()
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
  // 778: ... : ($filename)
  // 779:   without_prefix &filename prefix_path
  // 780:   without_prefix &filename '/'
  // 781:   writeln filename
  frame->slots[1] /* temp__1 */ = create_closure(entry__list_dependencies_35, 1);
  // 778: for_each dependencies: ($filename)
  // 779:   without_prefix &filename prefix_path
  // 780:   without_prefix &filename '/'
  // 781:   writeln filename
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
  // 785: $codeblocks_path string(mod_filename ".codeblocks")
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
  // 786: $info stat(codeblocks_path)
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
  // 787: ... info.is_defined
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
  // 787: ... :
  // 788:   ewrite "
  // 789:     The directory "@(codeblocks_path)" already exists!
  frame->slots[11] /* temp__2 */ = create_closure(entry__build_codeblocks_project_7, 0);
  // 787: if info.is_defined:
  // 788:   ewrite "
  // 789:     The directory "@(codeblocks_path)" already exists!
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
  // 788: ... "
  // 789:   The directory "@(codeblocks_path)" already exists!
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
  // 788: ewrite "
  // 789:   The directory "@(codeblocks_path)" already exists!
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
  // 790: ... : ewriteln "build Code::Blocks project in " codeblocks_path
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_12, 0);
  // 790: if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
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
  // 790: ... ewriteln "build Code::Blocks project in " codeblocks_path
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
  // 791: compile_module mod_filename mod_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  result_count = 0;
  myself = var._compile_module;
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_15;
}
static void cont__build_codeblocks_project_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 792: show_file_list
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._show_file_list;
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_16;
}
static void cont__build_codeblocks_project_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 793: ... 1
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
  // 793: ... truncate_until(main_filename '/' -1)
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
  // 793: $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
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
  // 794: $prefix_path current_path()
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
  // 795: ... codeblocks_path .without_prefix. prefix_path
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
  // 795: $depth count_occurrences(codeblocks_path .without_prefix. prefix_path '/')
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
  // 796: $path_prefix dup("../" depth)
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
  // 797: $cbp_filename string(codeblocks_path "/" basename ".cbp")
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
  // 798: mkdir codeblocks_path
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
  // 799: $$buf ""
  ((CELL *)frame->slots[9])->contents /* buf */ = empty_string;
  // 800: ... "
  // 801:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 802:   <CodeBlocks_project_file>
  // 803:     <FileVersion major="1" minor="6" />
  // 804:     <Project>
  // 805:       <Option title="@(basename)" />
  // 806:       <Option pch_mode="2" />
  // 807:       <Option compiler=c_compiler() />
  // 808:       <Build>
  // 809:         <Target title="debug">
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__ae2cb2959270f10e;
  arguments->slots[1] = frame->slots[4] /* basename */;
  arguments->slots[2] = string__3a69827feeaedc87;
  arguments->slots[3] = frame->slots[4] /* basename */;
  arguments->slots[4] = string__65fb167cf21c35a9;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_32;
}
static void cont__build_codeblocks_project_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 800: write_to &buf "
  // 801:   <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
  // 802:   <CodeBlocks_project_file>
  // 803:     <FileVersion major="1" minor="6" />
  // 804:     <Project>
  // 805:       <Option title="@(basename)" />
  // 806:       <Option pch_mode="2" />
  // 807:       <Option compiler=c_compiler() />
  // 808:       <Build>
  // 809:         <Target title="debug">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_33;
}
static void cont__build_codeblocks_project_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 821: ... : (filename)
  // 822:   write_to &buf "
  // 823:     @
  // 824:           <Add library="@(filename)" />
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_34, 1);
  // 821: for_each libraries: (filename)
  // 822:   write_to &buf "
  // 823:     @
  // 824:           <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__libraries();
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_39;
}
static void entry__build_codeblocks_project_34(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // buf: 1
  frame->slots[1] = myself->closure.frame->slots[9]; /* buf */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 822: ... "
  // 823:   @
  // 824:         <Add library="@(filename)" />
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__86909867946dc27b;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__ca5af8c3e83c305d;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_37;
}
static void cont__build_codeblocks_project_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 822: write_to &buf "
  // 823:   @
  // 824:         <Add library="@(filename)" />
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* buf */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_38;
}
static void cont__build_codeblocks_project_38(void) {
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
static void cont__build_codeblocks_project_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 835: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_40;
}
static void cont__build_codeblocks_project_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 838: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_41;
}
static void cont__build_codeblocks_project_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 841: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_42;
}
static void cont__build_codeblocks_project_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__4 */ = arguments->slots[0];
  // 825: ... "
  // 826:   @
  // 827:   
  // 828:       </Linker>
  // 829:       <Compiler>
  // 830:         <Add option="-Wall" />
  // 831:       </Compiler>
  // 832:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 833:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 834:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 17;
  arguments = node_p;
  arguments->slots[0] = string__4f8ac82e5b683b6f;
  arguments->slots[1] = frame->slots[7] /* path_prefix */;
  arguments->slots[2] = string__6ec73fb9d26dad91;
  arguments->slots[3] = frame->slots[7] /* path_prefix */;
  arguments->slots[4] = string__62c73cb6d2cd6da9;
  arguments->slots[5] = frame->slots[7] /* path_prefix */;
  arguments->slots[6] = string__e224568f04fadefb;
  arguments->slots[7] = frame->slots[11] /* temp__2 */;
  arguments->slots[8] = string__29a08e6f8046de11;
  arguments->slots[9] = frame->slots[7] /* path_prefix */;
  arguments->slots[10] = string__97a58959c957d32c;
  arguments->slots[11] = frame->slots[12] /* temp__3 */;
  arguments->slots[12] = string__29a08e6f8046de11;
  arguments->slots[13] = frame->slots[7] /* path_prefix */;
  arguments->slots[14] = string__629c968402fadffb;
  arguments->slots[15] = frame->slots[13] /* temp__4 */;
  arguments->slots[16] = string__517e18f604196bbc;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_51;
}
static void cont__build_codeblocks_project_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 825: write_to &buf "
  // 826:   @
  // 827:   
  // 828:       </Linker>
  // 829:       <Compiler>
  // 830:         <Add option="-Wall" />
  // 831:       </Compiler>
  // 832:       <Unit filename="@(path_prefix)runtime/common.h" />
  // 833:       <Unit filename="@(path_prefix)runtime/linker.h" />
  // 834:       <Unit filename="@(path_prefix)runtime/memory.c">
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_52;
}
static void cont__build_codeblocks_project_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 843: ... : ($filename)
  // 844:   without_prefix &filename prefix_path
  // 845:   without_prefix &filename '/'
  // 846:   write_to &buf "
  // 847:     @
  // 848:     
  // 849:         <Unit filename="@(path_prefix)@(filename)">
  // 850:           <Option compilerVar="@(c_compiler())" />
  // 851:         </Unit>
  frame->slots[10] /* temp__1 */ = create_closure(entry__build_codeblocks_project_53, 1);
  // 843: for_each c_sources: ($filename)
  // 844:   without_prefix &filename prefix_path
  // 845:   without_prefix &filename '/'
  // 846:   write_to &buf "
  // 847:     @
  // 848:     
  // 849:         <Unit filename="@(path_prefix)@(filename)">
  // 850:           <Option compilerVar="@(c_compiler())" />
  // 851:         </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._c_sources;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_61;
}
static void entry__build_codeblocks_project_53(void) {
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
  // 844: without_prefix &filename prefix_path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = frame->slots[1] /* prefix_path */;
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
  // 845: without_prefix &filename '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_55;
}
static void cont__build_codeblocks_project_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 850: ... c_compiler()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__c_compiler();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_56;
}
static void cont__build_codeblocks_project_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 846: ... "
  // 847:   @
  // 848:   
  // 849:       <Unit filename="@(path_prefix)@(filename)">
  // 850:         <Option compilerVar="@(c_compiler())" />
  // 851:       </Unit>
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = string__5ce0e5ba1304a164;
  arguments->slots[1] = frame->slots[3] /* path_prefix */;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[3] = string__48b865872b902196;
  arguments->slots[4] = frame->slots[5] /* temp__2 */;
  arguments->slots[5] = string__517e18f604196bbc;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_59;
}
static void cont__build_codeblocks_project_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 846: write_to &buf "
  // 847:   @
  // 848:   
  // 849:       <Unit filename="@(path_prefix)@(filename)">
  // 850:         <Option compilerVar="@(c_compiler())" />
  // 851:       </Unit>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* buf */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_60;
}
static void cont__build_codeblocks_project_60(void) {
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
static void cont__build_codeblocks_project_61(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 852: write_to &buf "
  // 853:       <Extensions>
  // 854:         <code_completion />
  // 855:         <debugger />
  // 856:       </Extensions>
  // 857:     </Project>
  // 858:   </CodeBlocks_project_file>
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* buf */;
  arguments->slots[1] = string__1d1cedd7cdd611c4;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__build_codeblocks_project_63;
}
static void cont__build_codeblocks_project_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[9])->contents /* buf */ = arguments->slots[0];
  // 859: save cbp_filename buf
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* cbp_filename */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* buf */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_codeblocks_project_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: compile_exe: (mod_filename mod_name)
  // 785:   $codeblocks_path string(mod_filename ".codeblocks")
  // 786:   $info stat(codeblocks_path)
  // 787:   if info.is_defined:
  // 788:     ewrite "
  // 789:       The directory "@(codeblocks_path)" already exists!
  // 790:   if verbose: ewriteln "build Code::Blocks project in " codeblocks_path
  // 791:   compile_module mod_filename mod_name
  // 792:   show_file_list
  // 793:   $basename truncate_until(main_filename '/' -1) .without_suffix. ".sim"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__build_codeblocks_project_2;
  result_count = frame->caller_result_count;
  myself = var._compile_exe;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_1(void) {
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
  // 862: ... action == "simrun"
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
  // 862: if action == "simrun": Error "Cannot run a directory!"
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
  // 862: ... Error "Cannot run a directory!"
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
  // 864: if
  // 865:   do_extract_documentation:
  // 866:     $$doc_libraries list(main_filename)
  // 867:     for_each additional_libraries: (library)
  // 868:       push &doc_libraries fullname(library)
  // 869:     extract_documentation doc_libraries
  // 870:   :
  // 871:     $$version ""
  // 872:     $version_filename string(main_filename "/VERSION")
  // 873:     if file_exists(version_filename):
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__do_extract_documentation();
  arguments->slots[1] = func__build_library_7;
  arguments->slots[2] = func__build_library_13;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_95;
}
static void entry__build_library_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 939: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_library_94;
}
static void cont__build_library_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 939: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_88(void) {
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
  frame->cont = cont__build_library_89;
}
static void cont__build_library_89(void) {
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
static void entry__build_library_79(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* err */
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
  frame->cont = cont__build_library_80;
}
static void cont__build_library_80(void) {
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
static void entry__build_library_72(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // err: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* err */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 911: ... err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* err */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__build_library_73;
}
static void cont__build_library_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 911: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_66(void) {
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
  // 907: "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
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
  frame->cont = cont__build_library_68;
}
static void cont__build_library_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 908: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_69;
}
static void cont__build_library_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 904: CC $_out $err $success
  // 905:   ld_options*
  // 906:   "-shared"
  // 907:   "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 908:   library_paths_and_file_list()*
  // 909:   "-o"
  // 910:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  arguments->slots[argument_count++] = frame->slots[6] /* temp__1 */;
  unfold(frame->slots[7] /* temp__2 */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[2] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_library_71;
}
static void cont__build_library_71(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  frame->slots[9] /* temp__4 */ = arguments->slots[1];
  frame->slots[10] /* temp__5 */ = arguments->slots[2];
  // 904: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[8] /* temp__3 */);
  // 904: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[9] /* temp__4 */);
  // 904: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[10] /* temp__5 */);
  // 911: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_library_72, 0);
  // 911: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* success */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_74(void) {
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
  // 916: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_75;
}
static void cont__build_library_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 917: "-lsim-@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__7e1f542601d292fa;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_77;
}
static void cont__build_library_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 913: CC $_out $err $success
  // 914:   ld_options*
  // 915:   "-shared"
  // 916:   library_paths_and_file_list()*
  // 917:   "-lsim-@(MAJOR)"
  // 918:   "-o"
  // 919:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__2 */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_library_78;
}
static void cont__build_library_78(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  frame->slots[7] /* temp__4 */ = arguments->slots[1];
  frame->slots[8] /* temp__5 */ = arguments->slots[2];
  // 913: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[6] /* temp__3 */);
  // 913: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[7] /* temp__4 */);
  // 913: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[8] /* temp__5 */);
  // 920: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__build_library_79, 0);
  // 920: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_81(void) {
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
  // 925: "
  // 926:   -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
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
  frame->cont = cont__build_library_83;
}
static void cont__build_library_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 927: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_84;
}
static void cont__build_library_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 928: "-lsim-@(MAJOR)"
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
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 922: CC $_out $err $success
  // 923:   ld_options*
  // 924:   "-dynamiclib"
  // 925:   "
  // 926:     -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
  // 927:   library_paths_and_file_list()*
  // 928:   "-lsim-@(MAJOR)"
  // 929:   "-o"
  // 930:   lib_filename
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
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_library_87;
}
static void cont__build_library_87(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__4 */ = arguments->slots[0];
  frame->slots[10] /* temp__5 */ = arguments->slots[1];
  frame->slots[11] /* temp__6 */ = arguments->slots[2];
  // 922: ... _out
  initialize_future(frame->slots[3] /* out */, frame->slots[9] /* temp__4 */);
  // 922: ... err
  initialize_future(frame->slots[4] /* err */, frame->slots[10] /* temp__5 */);
  // 922: ... success
  initialize_future(frame->slots[5] /* success */, frame->slots[11] /* temp__6 */);
  // 931: ... : Error err.from_utf8
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_library_88, 0);
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
static void entry__build_library_90(void) {
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
  // 936: library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_library_91;
}
static void cont__build_library_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 933: CC $_out $err $success
  // 934:   ld_options*
  // 935:   "-shared"
  // 936:   library_paths_and_file_list()*
  // 937:   "-o"
  // 938:   lib_filename
  argument_count = 0;
  arguments = node_p;
  unfold(var._ld_options);
  arguments->slots[argument_count++] = string__b130095b1592409e;
  unfold(frame->slots[4] /* temp__1 */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[0] /* lib_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_library_92;
}
static void cont__build_library_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  frame->slots[6] /* temp__3 */ = arguments->slots[1];
  frame->slots[7] /* temp__4 */ = arguments->slots[2];
  // 933: ... _out
  initialize_future(frame->slots[1] /* out */, frame->slots[5] /* temp__2 */);
  // 933: ... err
  initialize_future(frame->slots[2] /* err */, frame->slots[6] /* temp__3 */);
  // 933: ... success
  initialize_future(frame->slots[3] /* success */, frame->slots[7] /* temp__4 */);
  // 939: ... : Error err.from_utf8
  frame->slots[4] /* temp__1 */ = create_closure(entry__build_library_93, 0);
  // 939: unless success: Error err.from_utf8
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* success */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_60(void) {
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
  // 900: if verbose: ewriteln "linking dynamic library"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = func__build_library_61;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_63;
}
static void entry__build_library_61(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 900: ... ewriteln "linking dynamic library"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__b9aef2a4efc3a1a8;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_63(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 902: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_library_64;
}
static void cont__build_library_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 903: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_library_65;
}
static void cont__build_library_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 903: ... :
  // 904:   CC $_out $err $success
  // 905:     ld_options*
  // 906:     "-shared"
  // 907:     "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 908:     library_paths_and_file_list()*
  // 909:     "-o"
  // 910:     lib_filename
  // 911:   unless success: Error err.from_utf8
  frame->slots[5] /* temp__3 */ = create_closure(entry__build_library_66, 0);
  // 912: ... :
  // 913:   CC $_out $err $success
  // 914:     ld_options*
  // 915:     "-shared"
  // 916:     library_paths_and_file_list()*
  // 917:     "-lsim-@(MAJOR)"
  // 918:     "-o"
  // 919:     lib_filename
  // 920:   unless success: Error err.from_utf8
  frame->slots[6] /* temp__4 */ = create_closure(entry__build_library_74, 0);
  // 921: ... :
  // 922:   CC $_out $err $success
  // 923:     ld_options*
  // 924:     "-dynamiclib"
  // 925:     "
  // 926:       -Wl,-install_name,libsim-@(base_filename)@(so_version)-@(MAJOR).dylib@
  // 927:     library_paths_and_file_list()*
  // 928:     "-lsim-@(MAJOR)"
  // 929:     "-o"
  // 930:     lib_filename
  // ...
  frame->slots[7] /* temp__5 */ = create_closure(entry__build_library_81, 0);
  // 932: :
  // 933:   CC $_out $err $success
  // 934:     ld_options*
  // 935:     "-shared"
  // 936:     library_paths_and_file_list()*
  // 937:     "-o"
  // 938:     lib_filename
  // 939:   unless success: Error err.from_utf8
  frame->slots[8] /* temp__6 */ = create_closure(entry__build_library_90, 0);
  // 901: case
  // 902:   operating_system()
  // 903:   "linux", "bsd":
  // 904:     CC $_out $err $success
  // 905:       ld_options*
  // 906:       "-shared"
  // 907:       "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 908:       library_paths_and_file_list()*
  // 909:       "-o"
  // 910:       lib_filename
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
static void entry__build_library_7(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // doc_libraries: 0
  frame->slots[0] /* doc_libraries */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: $$doc_libraries list(main_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__build_library_8;
}
static void cont__build_library_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* doc_libraries */ = arguments->slots[0];
  // 867: ... : (library)
  // 868:   push &doc_libraries fullname(library)
  frame->slots[1] /* temp__1 */ = create_closure(entry__build_library_9, 1);
  // 867: for_each additional_libraries: (library)
  // 868:   push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._additional_libraries;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__build_library_12;
}
static void entry__build_library_9(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // library: 0
  // doc_libraries: 1
  frame->slots[1] = myself->closure.frame->slots[0]; /* doc_libraries */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 868: ... fullname(library)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* library */;
  result_count = 1;
  myself = get__fullname();
  func = myself->type;
  frame->cont = cont__build_library_10;
}
static void cont__build_library_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 868: push &doc_libraries fullname(library)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* doc_libraries */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__build_library_11;
}
static void cont__build_library_11(void) {
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
static void cont__build_library_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 869: extract_documentation doc_libraries
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* doc_libraries */;
  result_count = frame->caller_result_count;
  myself = get__extract_documentation();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_library_13(void) {
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
  // 871: $$version ""
  ((CELL *)frame->slots[0])->contents /* version */ = empty_string;
  // 872: $version_filename string(main_filename "/VERSION")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = string__84ca78485aeb98e;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_15;
}
static void cont__build_library_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* version_filename */, arguments->slots[0]);
  // 873: ... file_exists(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__file_exists();
  func = myself->type;
  frame->cont = cont__build_library_16;
}
static void cont__build_library_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 873: ... :
  // 874:   !version string('-' load(version_filename).trim)
  frame->slots[6] /* temp__2 */ = create_closure(entry__build_library_17, 0);
  // 873: if file_exists(version_filename):
  // 874:   !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_21;
}
static void entry__build_library_17(void) {
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
  // 874: ... load(version_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* version_filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__build_library_18;
}
static void cont__build_library_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 874: ... load(version_filename).trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__build_library_19;
}
static void cont__build_library_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 874: !version string('-' load(version_filename).trim)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__45;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_20;
}
static void cont__build_library_20(void) {
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
static void cont__build_library_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 875: $so_version version .truncate_from. '.'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* version */;
  arguments->slots[1] = character__46;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__build_library_22;
}
static void cont__build_library_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* so_version */, arguments->slots[0]);
  // 876: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_library_23;
}
static void cont__build_library_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 876: $base_filename truncate_until(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__build_library_24;
}
static void cont__build_library_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base_filename */, arguments->slots[0]);
  // 880: operating_system()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__operating_system();
  func = myself->type;
  frame->cont = cont__build_library_25;
}
static void cont__build_library_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 881: "linux", "bsd"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__585ae883ea60d02f;
  arguments->slots[1] = string__fa720c15db16ba8;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__build_library_26;
}
static void cont__build_library_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 882: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[7] /* temp__3 */ = create_closure(entry__build_library_27, 0);
  // 884: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  frame->slots[8] /* temp__4 */ = create_closure(entry__build_library_31, 0);
  // 886: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  frame->slots[9] /* temp__5 */ = create_closure(entry__build_library_35, 0);
  // 887: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  frame->slots[10] /* temp__6 */ = create_closure(entry__build_library_39, 0);
  // 878: $lib_filename
  // 879:   case
  // 880:     operating_system()
  // 881:     "linux", "bsd"
  // 882:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
  // 883:     "cygwin"
  // 884:     -> string("libsim-" base_filename version "-@(MAJOR).dll")
  // 885:     "darwin"
  // 886:     -> string("libsim-" base_filename version "-@(MAJOR).dylib")
  // 887:     -> string("libsim-" base_filename version ".so.@(MAJOR)")
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
  frame->cont = cont__build_library_44;
}
static void entry__build_library_27(void) {
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
  // 882: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9e0aed8b5d187d17;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_28;
}
static void cont__build_library_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 882: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_30;
}
static void cont__build_library_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 882: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_31(void) {
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
  // 884: ... "-@(MAJOR).dll"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__9e0ae84b5d007d55;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_33;
}
static void cont__build_library_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 884: ... string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_34;
}
static void cont__build_library_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 884: -> string("libsim-" base_filename version "-@(MAJOR).dll")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
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
  // 886: ... "-@(MAJOR).dylib"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9ccc;
  arguments->slots[1] = var._MAJOR;
  arguments->slots[2] = string__6a1f556781f212b5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_37;
}
static void cont__build_library_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 886: ... string("libsim-" base_filename version "-@(MAJOR).dylib")
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
  // 886: -> string("libsim-" base_filename version "-@(MAJOR).dylib")
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
  // 887: ... ".so.@(MAJOR)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9e0aed8b5d187d17;
  arguments->slots[1] = var._MAJOR;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__build_library_40;
}
static void cont__build_library_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 887: ... string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = string__94340f9615d2e0d7;
  arguments->slots[1] = frame->slots[0] /* base_filename */;
  arguments->slots[2] = ((CELL *)frame->slots[1])->contents /* version */;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__build_library_41;
}
static void cont__build_library_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 887: -> string("libsim-" base_filename version ".so.@(MAJOR)")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* lib_filename */, arguments->slots[0]);
  // 889: ... : ewriteln "build library " lib_filename
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_45, 0);
  // 889: if verbose: ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__build_library_47;
}
static void entry__build_library_45(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // lib_filename: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* lib_filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 889: ... ewriteln "build library " lib_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__822587b3f48532f5;
  arguments->slots[1] = frame->slots[0] /* lib_filename */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_47(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 890: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__build_library_48;
}
static void cont__build_library_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 890: ... behind(main_filename '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__build_library_49;
}
static void cont__build_library_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 890: compile_modules main_filename behind(main_filename '/' -1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__main_filename();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = var._compile_modules;
  func = myself->type;
  frame->cont = cont__build_library_50;
}
static void cont__build_library_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 891: ... :
  // 892:   $info stat(lib_filename)
  // 893:   if
  // 894:     ||
  // 895:       info.is_undefined
  // 896:       last_modification_time > modification_time_of(info)
  // 897:     :
  // 898:       !do_link true
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_51, 0);
  // 891: unless do_link:
  // 892:   $info stat(lib_filename)
  // 893:   if
  // 894:     ||
  // 895:       info.is_undefined
  // 896:       last_modification_time > modification_time_of(info)
  // 897:     :
  // 898:       !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_link();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__build_library_59;
}
static void entry__build_library_58(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 898: !do_link true
  set__do_link(get__true());
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__build_library_51(void) {
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
  // 892: $info stat(lib_filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lib_filename */;
  result_count = 1;
  myself = get__stat();
  func = myself->type;
  frame->cont = cont__build_library_52;
}
static void cont__build_library_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* info */, arguments->slots[0]);
  // 895: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__build_library_53;
}
static void cont__build_library_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 896: last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_library_54, 0);
  // 894: ||
  // 895:   info.is_undefined
  // 896:   last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__build_library_57;
}
static void entry__build_library_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 896: ... modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__modification_time_of();
  func = myself->type;
  frame->cont = cont__build_library_55;
}
static void cont__build_library_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 896: last_modification_time > modification_time_of(info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__last_modification_time();
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__build_library_56;
}
static void cont__build_library_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 896: last_modification_time > modification_time_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__build_library_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 893: if
  // 894:   ||
  // 895:     info.is_undefined
  // 896:     last_modification_time > modification_time_of(info)
  // 897:   :
  // 898:     !do_link true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = func__build_library_58;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_library_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 899: ... :
  // 900:   if verbose: ewriteln "linking dynamic library"
  // 901:   case
  // 902:     operating_system()
  // 903:     "linux", "bsd":
  // 904:       CC $_out $err $success
  // 905:         ld_options*
  // 906:         "-shared"
  // 907:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 908:         library_paths_and_file_list()*
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_library_60, 0);
  // 899: if do_link:
  // 900:   if verbose: ewriteln "linking dynamic library"
  // 901:   case
  // 902:     operating_system()
  // 903:     "linux", "bsd":
  // 904:       CC $_out $err $success
  // 905:         ld_options*
  // 906:         "-shared"
  // 907:         "-Wl,-soname,libsim-@(base_filename)@(so_version).so.@(MAJOR)"
  // 908:         library_paths_and_file_list()*
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
static void cont__build_library_95(void) {
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
  // 954: ... : ewriteln "compiling runtime module @(filename)"
  frame->slots[3] /* temp__1 */ = create_closure(entry__maybe_compile_c_file_19, 0);
  // 954: if verbose: ewriteln "compiling runtime module @(filename)"
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
  // 954: ... "compiling runtime module @(filename)"
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
  // 954: ... ewriteln "compiling runtime module @(filename)"
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
  // 955: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* c_filename */;
  arguments->slots[1] = frame->slots[2] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__maybe_compile_c_file_1(void) {
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
  // 942: $c_filename string(filename ".c")
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
  // 943: $o_filename string(filename ".o")
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
  // 944: $c_info stat(c_filename)
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
  // 945: ... c_info.is_undefined
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
  // 945: ... :
  // 946:   Error "
  // 947:     @quot;@(c_filename)" does not exist!
  frame->slots[6] /* temp__2 */ = create_closure(entry__maybe_compile_c_file_6, 0);
  // 945: if c_info.is_undefined:
  // 946:   Error "
  // 947:     @quot;@(c_filename)" does not exist!
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
  // 946: ... "
  // 947:   @quot;@(c_filename)" does not exist!
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
  // 946: Error "
  // 947:   @quot;@(c_filename)" does not exist!
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
  // 948: $o_info stat(o_filename)
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
  // 951: o_info.is_undefined
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
  // 952: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__maybe_compile_c_file_13, 0);
  // 950: ||
  // 951:   o_info.is_undefined
  // 952:   modification_time_of(c_info) > modification_time_of(o_info)
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
  // 952: ... modification_time_of(o_info)
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
  // 952: modification_time_of(c_info)
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
  // 952: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 952: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 953: :
  // 954:   if verbose: ewriteln "compiling runtime module @(filename)"
  // 955:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__maybe_compile_c_file_18, 0);
  // 949: if
  // 950:   ||
  // 951:     o_info.is_undefined
  // 952:     modification_time_of(c_info) > modification_time_of(o_info)
  // 953:   :
  // 954:     if verbose: ewriteln "compiling runtime module @(filename)"
  // 955:     compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__format_number_1(void) {
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
  // 965: to_string &val
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
  // 966: $$ac 0
  ((CELL *)frame->slots[3])->contents /* ac */ = number__0;
  // 967: ... : (-> break)
  // 968:   for_each val: (i chr)
  // 969:     if chr == '.':
  // 970:       !ac length_of(val)-i
  // 971:       if n > i-1: append dup(" " n-(i-1)) &val
  // 972:       break
  frame->slots[4] /* temp__1 */ = create_closure(entry__format_number_3, 0);
  // 967: do: (-> break)
  // 968:   for_each val: (i chr)
  // 969:     if chr == '.':
  // 970:       !ac length_of(val)-i
  // 971:       if n > i-1: append dup(" " n-(i-1)) &val
  // 972:       break
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
  // 968: ... : (i chr)
  // 969:   if chr == '.':
  // 970:     !ac length_of(val)-i
  // 971:     if n > i-1: append dup(" " n-(i-1)) &val
  // 972:     break
  frame->slots[4] /* temp__1 */ = create_closure(entry__format_number_4, 2);
  // 968: for_each val: (i chr)
  // 969:   if chr == '.':
  // 970:     !ac length_of(val)-i
  // 971:     if n > i-1: append dup(" " n-(i-1)) &val
  // 972:     break
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
  // 970: ... length_of(val)
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
  // 970: !ac length_of(val)-i
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
  // 971: ... i-1
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
  // 971: ... n > i-1
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
  // 971: ... : append dup(" " n-(i-1)) &val
  frame->slots[7] /* temp__3 */ = create_closure(entry__format_number_11, 0);
  // 971: if n > i-1: append dup(" " n-(i-1)) &val
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
  // 971: ... i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* i */;
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
  // 971: ... n-(i-1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* n */;
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
  // 971: ... dup(" " n-(i-1))
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
  // 971: ... append dup(" " n-(i-1)) &val
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* val */;
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
  ((CELL *)frame->slots[0])->contents /* val */ = arguments->slots[0];
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
  // 972: break
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
  // 969: ... chr == '.'
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
  // 969: ... :
  // 970:   !ac length_of(val)-i
  // 971:   if n > i-1: append dup(" " n-(i-1)) &val
  // 972:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__format_number_6, 0);
  // 969: if chr == '.':
  // 970:   !ac length_of(val)-i
  // 971:   if n > i-1: append dup(" " n-(i-1)) &val
  // 972:   break
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
  // 974: m > ac
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
  // 974: ... :
  // 975:   append &val dup("0" m-ac)
  frame->slots[5] /* temp__2 */ = create_closure(entry__format_number_21, 0);
  // 976: :
  // 977:   if ac > m: range &val 1 -(ac-m+1)
  frame->slots[6] /* temp__3 */ = create_closure(entry__format_number_26, 0);
  // 973: if
  // 974:   m > ac:
  // 975:     append &val dup("0" m-ac)
  // 976:   :
  // 977:     if ac > m: range &val 1 -(ac-m+1)
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
  // 977: ... ac-m
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
  // 977: ... ac-m+1
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
  // 977: ... ac-m+1)
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
  // 977: ... range &val 1 -(ac-m+1)
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
  // 975: ... m-ac
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
  // 975: ... dup("0" m-ac)
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
  // 975: append &val dup("0" m-ac)
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
  // 977: ... ac > m
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
  // 977: ... : range &val 1 -(ac-m+1)
  frame->slots[4] /* temp__2 */ = create_closure(entry__format_number_28, 0);
  // 977: if ac > m: range &val 1 -(ac-m+1)
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
  // 978: -> val
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* val */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__sim2c__write_timing_info_1(void) {
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
  // 981: $new_t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_2;
}
static void cont__sim2c__write_timing_info_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* new_t */, arguments->slots[0]);
  // 983: filename.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* filename */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_3;
}
static void cont__sim2c__write_timing_info_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 983: ... :
  // 984:   truncate_until &filename '/' -1
  // 985:   ewriteln
  // 986:     description
  // 987:     ' '
  // 988:     filename
  // 989:     ':'
  // 990:     dup(" " 12-length_of(description))
  // 991:     format_number(new_t-t 2 3)
  // 992:     " s"
  frame->slots[4] /* temp__2 */ = create_closure(entry__sim2c__write_timing_info_4, 0);
  // 993: :
  // 994:   ewriteln description ": " format_number(new_t-t 0 3) " s"
  frame->slots[5] /* temp__3 */ = create_closure(entry__sim2c__write_timing_info_13, 0);
  // 982: if
  // 983:   filename.is_defined:
  // 984:     truncate_until &filename '/' -1
  // 985:     ewriteln
  // 986:       description
  // 987:       ' '
  // 988:       filename
  // 989:       ':'
  // 990:       dup(" " 12-length_of(description))
  // 991:       format_number(new_t-t 2 3)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_17;
}
static void entry__sim2c__write_timing_info_4(void) {
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
  // 984: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_5;
}
static void cont__sim2c__write_timing_info_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 984: truncate_until &filename '/' -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* filename */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_6;
}
static void cont__sim2c__write_timing_info_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* filename */ = arguments->slots[0];
  // 990: ... length_of(description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_7;
}
static void cont__sim2c__write_timing_info_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 990: ... 12-length_of(description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__12;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_8;
}
static void cont__sim2c__write_timing_info_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 990: dup(" " 12-length_of(description))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_9;
}
static void cont__sim2c__write_timing_info_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 991: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_10;
}
static void cont__sim2c__write_timing_info_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__5 */ = arguments->slots[0];
  // 991: format_number(new_t-t 2 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__5 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_11;
}
static void cont__sim2c__write_timing_info_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 985: ewriteln
  // 986:   description
  // 987:   ' '
  // 988:   filename
  // 989:   ':'
  // 990:   dup(" " 12-length_of(description))
  // 991:   format_number(new_t-t 2 3)
  // 992:   " s"
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
static void entry__sim2c__write_timing_info_13(void) {
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
  // 994: ... new_t-t
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* new_t */;
  arguments->slots[1] = var._t;
  result_count = 1;
  myself = get__std__minus();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_14;
}
static void cont__sim2c__write_timing_info_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 994: ... format_number(new_t-t 0 3)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = number__0;
  arguments->slots[2] = number__3;
  result_count = 1;
  myself = var._format_number;
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_15;
}
static void cont__sim2c__write_timing_info_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 994: ewriteln description ": " format_number(new_t-t 0 3) " s"
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
static void cont__sim2c__write_timing_info_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 995: !t current_time()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = get__current_time();
  func = myself->type;
  frame->cont = cont__sim2c__write_timing_info_18;
}
static void cont__sim2c__write_timing_info_18(void) {
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
  // 1090: exe_filename .has_prefix. '/'
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
  // 1091: -> exe_filename
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_executable_118, 0);
  // 1092: -> string("./" exe_filename)
  frame->slots[5] /* temp__4 */ = create_closure(entry__build_executable_119, 0);
  // 1089: if
  // 1090:   exe_filename .has_prefix. '/'
  // 1091:   -> exe_filename
  // 1092:   -> string("./" exe_filename)
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
  // 1091: -> exe_filename
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
  // 1092: ... string("./" exe_filename)
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
  // 1092: -> string("./" exe_filename)
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
  // 1088: exec
  // 1089:   if
  // 1090:     exe_filename .has_prefix. '/'
  // 1091:     -> exe_filename
  // 1092:     -> string("./" exe_filename)
  // 1093:   zz*
  // 1094:   
  // 1095:   #range(command_line_arguments 2 -1)*
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
  // 1010: operating_system()
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
  // 1010: operating_system() == "cygwin"
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
  // 1011: -> string(mod_filename ".exe")
  frame->slots[11] /* temp__3 */ = create_closure(entry__build_executable_5, 0);
  // 1012: -> mod_filename
  frame->slots[12] /* temp__4 */ = create_closure(entry__build_executable_8, 0);
  // 1008: $exe_filename
  // 1009:   if
  // 1010:     operating_system() == "cygwin"
  // 1011:     -> string(mod_filename ".exe")
  // 1012:     -> mod_filename
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
  // 1011: ... string(mod_filename ".exe")
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
  // 1011: -> string(mod_filename ".exe")
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
  // 1012: -> mod_filename
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
  // 1014: ... : ewriteln "build executable " exe_filename
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_10, 0);
  // 1014: if verbose: ewriteln "build executable " exe_filename
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
  // 1014: ... ewriteln "build executable " exe_filename
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
  // 1015: $c_filename string(mod_filename ".c")
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
  // 1016: $o_filename string(mod_filename ".o")
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
  // 1017: $sim_info stat(main_filename)
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
  // 1018: $c_info stat(c_filename)
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
  // 1019: $$c_buf undefined
  ((CELL *)frame->slots[7])->contents /* c_buf */ = get__undefined();
  // 1020: !objects(o_filename) true
  frame->slots[9] /* temp__1 */ = get__true();
  // 1020: !objects(o_filename)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* o_filename */;
  arguments->slots[1] = frame->slots[9] /* temp__1 */;
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
  // 1024: c_info.is_undefined
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
  // 1025: modification_time_of(sim_info) > modification_time_of(c_info)
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
  // 1025: ... modification_time_of(c_info)
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
  // 1025: modification_time_of(sim_info)
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
  // 1025: modification_time_of(sim_info) > modification_time_of(c_info)
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
  // 1025: modification_time_of(sim_info) > modification_time_of(c_info)
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
  // 1026: :
  // 1027:   %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1028:   if verbose: ewriteln "build main module " module_name
  // 1029:   collect_output $c_source: sim2c list(main_filename) true
  // 1030:   collect_output !c_buf: create_imports c_source
  // 1031:   save c_filename c_buf.to_utf8
  // 1032:   if do_time_passes: write_timing_info "saving" c_filename
  // 1033:   compile_c c_filename o_filename
  // 1034:   if do_time_passes: write_timing_info "compiling" c_filename
  frame->slots[11] /* temp__3 */ = create_closure(entry__build_executable_26, 0);
  // 1035: :
  // 1036:   load !c_buf c_filename
  // 1037:   $o_info stat(o_filename)
  // 1038:   if
  // 1039:     ||
  // 1040:       o_info.is_undefined
  // 1041:       modification_time_of(c_info) > modification_time_of(o_info)
  // 1042:     :
  // 1043:       compile_c c_filename o_filename
  // 1044:     :
  // ...
  frame->slots[12] /* temp__4 */ = create_closure(entry__build_executable_46, 0);
  // 1021: if
  // 1022:   ||
  // 1023:     do_rebuild
  // 1024:     c_info.is_undefined
  // 1025:     modification_time_of(sim_info) > modification_time_of(c_info)
  // 1026:   :
  // 1027:     %sim2c::module_name mod_name .without_suffix. some(".meta")
  // 1028:     if verbose: ewriteln "build main module " module_name
  // 1029:     collect_output $c_source: sim2c list(main_filename) true
  // 1030:     collect_output !c_buf: create_imports c_source
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
  // 1043: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_filename */;
  arguments->slots[1] = frame->slots[1] /* o_filename */;
  result_count = frame->caller_result_count;
  myself = var._compile_c;
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
  // 1045: !last_modification_time modification_time_of(o_info)
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
  define__sim2c__module_name(create_future());
  frame->slots[5] /* c_source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1027: ... some(".meta")
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
  // 1027: %sim2c::module_name mod_name .without_suffix. some(".meta")
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
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 1028: if verbose: ewriteln "build main module " module_name
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
  // 1028: ... ewriteln "build main module " module_name
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
  // 1029: collect_output $c_source: sim2c list(main_filename) true
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
  // 1029: ... list(main_filename)
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
  // 1029: ... sim2c list(main_filename) true
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
  // 1030: ... : create_imports c_source
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_35, 0);
  // 1030: collect_output !c_buf: create_imports c_source
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
  // 1030: ... create_imports c_source
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* c_source */;
  result_count = frame->caller_result_count;
  myself = var._create_imports;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__build_executable_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* c_buf */ = arguments->slots[0];
  // 1031: ... c_buf.to_utf8
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
  // 1031: save c_filename c_buf.to_utf8
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
  // 1032: ... : write_timing_info "saving" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_39, 0);
  // 1032: if do_time_passes: write_timing_info "saving" c_filename
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
  // 1032: ... write_timing_info "saving" c_filename
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
  // 1033: compile_c c_filename o_filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* c_filename */;
  arguments->slots[1] = frame->slots[4] /* o_filename */;
  result_count = 0;
  myself = var._compile_c;
  func = myself->type;
  frame->cont = cont__build_executable_42;
}
static void cont__build_executable_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1034: ... : write_timing_info "compiling" c_filename
  frame->slots[6] /* temp__1 */ = create_closure(entry__build_executable_43, 0);
  // 1034: if do_time_passes: write_timing_info "compiling" c_filename
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
  // 1034: ... write_timing_info "compiling" c_filename
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
  // 1036: load !c_buf c_filename
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
  // 1037: $o_info stat(o_filename)
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
  // 1040: o_info.is_undefined
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
  // 1041: modification_time_of(c_info) > modification_time_of(o_info)
  frame->slots[7] /* temp__3 */ = create_closure(entry__build_executable_50, 0);
  // 1039: ||
  // 1040:   o_info.is_undefined
  // 1041:   modification_time_of(c_info) > modification_time_of(o_info)
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
  // 1041: ... modification_time_of(o_info)
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
  // 1041: modification_time_of(c_info)
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
  // 1041: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 1041: modification_time_of(c_info) > modification_time_of(o_info)
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
  // 1042: :
  // 1043:   compile_c c_filename o_filename
  frame->slots[8] /* temp__4 */ = create_closure(entry__build_executable_55, 0);
  // 1044: :
  // 1045:   !last_modification_time modification_time_of(o_info)
  frame->slots[9] /* temp__5 */ = create_closure(entry__build_executable_56, 0);
  // 1038: if
  // 1039:   ||
  // 1040:     o_info.is_undefined
  // 1041:     modification_time_of(c_info) > modification_time_of(o_info)
  // 1042:   :
  // 1043:     compile_c c_filename o_filename
  // 1044:   :
  // 1045:     !last_modification_time modification_time_of(o_info)
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
  // 1046: build_dependencies mod_filename mod_name c_buf
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* mod_filename */;
  arguments->slots[1] = frame->slots[1] /* mod_name */;
  arguments->slots[2] = ((CELL *)frame->slots[7])->contents /* c_buf */;
  result_count = 0;
  myself = var._build_dependencies;
  func = myself->type;
  frame->cont = cont__build_executable_59;
}
static void cont__build_executable_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 1047: if do_build_static_executable:
  // 1048:   for_each
  // 1049:     "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1050:       maybe_compile_c_file filename
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
  // 1050: maybe_compile_c_file filename
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = frame->caller_result_count;
  myself = var._maybe_compile_c_file;
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
  // 1049: "runtime/linker", "runtime/memory", "runtime/debugger"
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
  // 1048: for_each
  // 1049:   "runtime/linker", "runtime/memory", "runtime/debugger": (filename)
  // 1050:     maybe_compile_c_file filename
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
  // 1051: ... :
  // 1052:   $info stat(exe_filename)
  // 1053:   if
  // 1054:     ||
  // 1055:       info.is_undefined
  // 1056:       &&
  // 1057:         last_modification_time.is_defined
  // 1058:         last_modification_time > modification_time_of(info)
  // 1059:     :
  // 1060:       !do_link true
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_67, 0);
  // 1051: unless do_link:
  // 1052:   $info stat(exe_filename)
  // 1053:   if
  // 1054:     ||
  // 1055:       info.is_undefined
  // 1056:       &&
  // 1057:         last_modification_time.is_defined
  // 1058:         last_modification_time > modification_time_of(info)
  // 1059:     :
  // 1060:       !do_link true
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
  // 1060: !do_link true
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
  // 1052: $info stat(exe_filename)
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
  // 1055: info.is_undefined
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
  // 1056: &&
  // 1057:   last_modification_time.is_defined
  // 1058:   last_modification_time > modification_time_of(info)
  frame->slots[4] /* temp__3 */ = create_closure(entry__build_executable_70, 0);
  // 1054: ||
  // 1055:   info.is_undefined
  // 1056:   &&
  // 1057:     last_modification_time.is_defined
  // 1058:     last_modification_time > modification_time_of(info)
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
  // 1057: last_modification_time.is_defined
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
  // 1058: last_modification_time > modification_time_of(info)
  frame->slots[3] /* temp__3 */ = create_closure(entry__build_executable_72, 0);
  // 1056: &&
  // 1057:   last_modification_time.is_defined
  // 1058:   last_modification_time > modification_time_of(info)
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
  // 1058: ... modification_time_of(info)
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
  // 1058: last_modification_time > modification_time_of(info)
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
  // 1058: last_modification_time > modification_time_of(info)
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
  // 1056: &&
  // 1057:   last_modification_time.is_defined
  // 1058:   last_modification_time > modification_time_of(info)
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
  // 1053: if
  // 1054:   ||
  // 1055:     info.is_undefined
  // 1056:     &&
  // 1057:       last_modification_time.is_defined
  // 1058:       last_modification_time > modification_time_of(info)
  // 1059:   :
  // 1060:     !do_link true
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
  // 1061: ... :
  // 1062:   $$libs_and_files library_paths_and_file_list()
  // 1063:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1064:   if
  // 1065:     do_build_static_executable:
  // 1066:       if verbose: ewriteln "linking static executable"
  // 1067:       CC $_out $err $success
  // 1068:         "runtime/linker.o"
  // 1069:         "runtime/memory.o"
  // 1070:         "runtime/debugger.o"
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__build_executable_79, 0);
  // 1061: if do_link:
  // 1062:   $$libs_and_files library_paths_and_file_list()
  // 1063:   if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
  // 1064:   if
  // 1065:     do_build_static_executable:
  // 1066:       if verbose: ewriteln "linking static executable"
  // 1067:       CC $_out $err $success
  // 1068:         "runtime/linker.o"
  // 1069:         "runtime/memory.o"
  // 1070:         "runtime/debugger.o"
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
  // 1085: ... err.from_utf8
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
  // 1085: ... Error err.from_utf8
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
  // 1074: ... err.from_utf8
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
  // 1074: ... Error err.from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_85(void) {
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
  // 1066: if verbose: ewriteln "linking static executable"
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
  // 1066: ... ewriteln "linking static executable"
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
  // 1067: CC $_out $err $success
  // 1068:   "runtime/linker.o"
  // 1069:   "runtime/memory.o"
  // 1070:   "runtime/debugger.o"
  // 1071:   libs_and_files*
  // 1072:   "-o"
  // 1073:   exe_filename
  argument_count = 0;
  arguments = node_p;
  arguments->slots[argument_count++] = string__5aa0e0654e0a7d41;
  arguments->slots[argument_count++] = string__7490e2a4ce0a3d61;
  arguments->slots[argument_count++] = string__14e71717a54948bc;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_executable_92;
}
static void cont__build_executable_92(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  frame->slots[6] /* temp__2 */ = arguments->slots[1];
  frame->slots[7] /* temp__3 */ = arguments->slots[2];
  // 1067: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[5] /* temp__1 */);
  // 1067: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[6] /* temp__2 */);
  // 1067: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[7] /* temp__3 */);
  // 1074: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_executable_93, 0);
  // 1074: unless success: Error err.from_utf8
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
  // 1076: if verbose: ewriteln "linking executable"
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
  // 1076: ... ewriteln "linking executable"
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
  // 1080: operating_system()
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
  // 1081: "linux", "bsd"
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
  // 1079: case
  // 1080:   operating_system()
  // 1081:   "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1082:   -> "-lsim-@(MAJOR)"
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
  // 1081: ... "-l:libsim.so.@(MAJOR)"
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
  // 1081: ... -> "-l:libsim.so.@(MAJOR)"
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
  // 1082: ... "-lsim-@(MAJOR)"
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
  // 1082: -> "-lsim-@(MAJOR)"
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
  // 1077: CC $_out $err $success
  // 1078:   libs_and_files*
  // 1079:   case
  // 1080:     operating_system()
  // 1081:     "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1082:     -> "-lsim-@(MAJOR)"
  // 1083:   "-o"
  // 1084:   exe_filename
  argument_count = 0;
  arguments = node_p;
  unfold(((CELL *)frame->slots[0])->contents /* libs_and_files */);
  arguments->slots[argument_count++] = frame->slots[5] /* temp__1 */;
  arguments->slots[argument_count++] = string__2d7981f4e6602baa;
  arguments->slots[argument_count++] = frame->slots[1] /* exe_filename */;
  result_count = 3;
  myself = var._CC;
  func = myself->type;
  frame->cont = cont__build_executable_107;
}
static void cont__build_executable_107(void) {
  if (argument_count != 3) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  frame->slots[9] /* temp__5 */ = arguments->slots[1];
  frame->slots[10] /* temp__6 */ = arguments->slots[2];
  // 1077: ... _out
  initialize_future(frame->slots[2] /* out */, frame->slots[8] /* temp__4 */);
  // 1077: ... err
  initialize_future(frame->slots[3] /* err */, frame->slots[9] /* temp__5 */);
  // 1077: ... success
  initialize_future(frame->slots[4] /* success */, frame->slots[10] /* temp__6 */);
  // 1085: ... : Error err.from_utf8
  frame->slots[5] /* temp__1 */ = create_closure(entry__build_executable_108, 0);
  // 1085: unless success: Error err.from_utf8
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
  // 1062: $$libs_and_files library_paths_and_file_list()
  argument_count = 0;
  arguments = node_p;
  result_count = 1;
  myself = var._library_paths_and_file_list;
  func = myself->type;
  frame->cont = cont__build_executable_80;
}
static void cont__build_executable_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* libs_and_files */ = arguments->slots[0];
  // 1063: ... : push &libs_and_files "/usr/lib/libprofiler.so.0"
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_executable_81, 0);
  // 1063: if do_link_profiler: push &libs_and_files "/usr/lib/libprofiler.so.0"
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
  // 1063: ... push &libs_and_files "/usr/lib/libprofiler.so.0"
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
  // 1065: ... :
  // 1066:   if verbose: ewriteln "linking static executable"
  // 1067:   CC $_out $err $success
  // 1068:     "runtime/linker.o"
  // 1069:     "runtime/memory.o"
  // 1070:     "runtime/debugger.o"
  // 1071:     libs_and_files*
  // 1072:     "-o"
  // 1073:     exe_filename
  // 1074:   unless success: Error err.from_utf8
  frame->slots[2] /* temp__1 */ = create_closure(entry__build_executable_85, 0);
  // 1075: :
  // 1076:   if verbose: ewriteln "linking executable"
  // 1077:   CC $_out $err $success
  // 1078:     libs_and_files*
  // 1079:     case
  // 1080:       operating_system()
  // 1081:       "linux", "bsd" -> "-l:libsim.so.@(MAJOR)"
  // 1082:       -> "-lsim-@(MAJOR)"
  // 1083:     "-o"
  // 1084:     exe_filename
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__build_executable_95, 0);
  // 1064: if
  // 1065:   do_build_static_executable:
  // 1066:     if verbose: ewriteln "linking static executable"
  // 1067:     CC $_out $err $success
  // 1068:       "runtime/linker.o"
  // 1069:       "runtime/memory.o"
  // 1070:       "runtime/debugger.o"
  // 1071:       libs_and_files*
  // 1072:       "-o"
  // 1073:       exe_filename
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
  // 1086: ... 1
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
  // 1086: $zz range(command_line_arguments 2 -1)
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
  // 1087: ... on_top_level && action == "simrun"
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
  // 1087: ... action == "simrun"
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
  // 1087: ... action == "simrun"
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
  // 1087: ... :
  // 1088:   exec
  // 1089:     if
  // 1090:       exe_filename .has_prefix. '/'
  // 1091:       -> exe_filename
  // 1092:       -> string("./" exe_filename)
  // 1093:     zz*
  // 1094:     
  // 1095:     #range(command_line_arguments 2 -1)*
  frame->slots[10] /* temp__2 */ = create_closure(entry__build_executable_116, 0);
  // 1087: if on_top_level && action == "simrun":
  // 1088:   exec
  // 1089:     if
  // 1090:       exe_filename .has_prefix. '/'
  // 1091:       -> exe_filename
  // 1092:       -> string("./" exe_filename)
  // 1093:     zz*
  // 1094:     
  // 1095:     #range(command_line_arguments 2 -1)*
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__build_executable_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 1007: compile_exe: (mod_filename mod_name)
  // 1008:   $exe_filename
  // 1009:     if
  // 1010:       operating_system() == "cygwin"
  // 1011:       -> string(mod_filename ".exe")
  // 1012:       -> mod_filename
  // 1013:   
  // 1014:   if verbose: ewriteln "build executable " exe_filename
  // 1015:   $c_filename string(mod_filename ".c")
  // 1016:   $o_filename string(mod_filename ".o")
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__build_executable_2;
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
  var._default_paths = collect_node(var._default_paths);
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
  var._additional_libraries = collect_node(var._additional_libraries);
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
  define_namespace("std");
  define_namespace("types");
  define_namespace("sim2c");

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
  unique__NONE = register_unique_item("NONE");
  func__sim2c__show_compiler_debug_info_1 = create_function(entry__sim2c__show_compiler_debug_info_1, -1);
  unique__EXE = register_unique_item("EXE");
  unique__LIB = register_unique_item("LIB");
  func__resolve_filename_8 = create_function(entry__resolve_filename_8, 1);
  func__resolve_filename_4 = create_function(entry__resolve_filename_4, 1);
  func__resolve_filename_3 = create_function(entry__resolve_filename_3, 0);
  string__373a794ad67f2aca = from_latin_1_string("Cannot resolve required library \042", 33);
  string__2d7981f4e6182be4 = from_latin_1_string("\042!", 2);
  func__resolve_filename_1 = create_function(entry__resolve_filename_1, 1);
  string__9e0aed8b5d287d54 = from_latin_1_string(".sim", 4);
  string__505aea43ea6cf036 = from_latin_1_string(".meta", 5);
  string__a9300e9315c23094 = from_latin_1_string("-common", 7);
  string__578a5af303e9ccc = from_latin_1_string("-", 1);
  string__bf5121a1ba54e344 = from_latin_1_string("The platform \042", 14);
  string__b566882ea60ef100 = from_latin_1_string("\042 is not supported!", 19);
  func__add_module_infos_1 = create_function(entry__add_module_infos_1, 2);
  func__lookup_1 = create_function(entry__lookup_1, 2);
  func__CC_1 = create_function(entry__CC_1, -1);
  func__compile_c_2 = create_function(entry__compile_c_2, 0);
  string__2d7981f4e6602ba6 = from_latin_1_string("-c", 2);
  string__2d7981f4e6602baa = from_latin_1_string("-o", 2);
  string__ca9b4802029a5965 = from_latin_1_string("Failed to compile ", 18);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  func__compile_c_1 = create_function(entry__compile_c_1, 2);
  string__2d7981f4e6782ba6 = from_latin_1_string(".c", 2);
  string__9c0afa8b5f187d19 = from_latin_1_string("/// ", 4);
  string__a0ae90b5dc07d58 = from_latin_1_string("data", 4);
  string__2d7981f4e6782bea = from_latin_1_string("./", 2);
  func__compile_meta_module_1 = create_function(entry__compile_meta_module_1, 3);
  func__build_dependencies_24 = create_function(entry__build_dependencies_24, 0);
  func__build_dependencies_23 = create_function(entry__build_dependencies_23, 0);
  string__240aeb0b5d087d14 = from_latin_1_string("sim-", 4);
  string__984c0f90152bd09f = from_latin_1_string("require", 7);
  string__1a0aeb0b5d107d52 = from_latin_1_string("link", 4);
  func__build_dependencies_1 = create_function(entry__build_dependencies_1, -1);
  func__compile_module_9 = create_function(entry__compile_module_9, 0);
  string__52b1d7d50d05f753 = from_latin_1_string("Failed to open file \042", 21);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  string__a85eb307b04e1ec9 = from_latin_1_string("build module ", 13);
  string__1c48d17af91ab023 = from_latin_1_string("No source file(s) for module \042", 30);
  string__4594ae5504f56841 = from_latin_1_string("\042 found!", 8);
  string__2d7981f4e6782baa = from_latin_1_string(".o", 2);
  string__2d7981f4e6082be6 = from_latin_1_string(" #", 2);
  func__compile_module_1 = create_function(entry__compile_module_1, 2);
  func__compile_modules_1 = create_function(entry__compile_modules_1, 2);
  string__21dcb95c2a4f4c6f = from_latin_1_string("LD_LIBRARY_PATH", 15);
  string__cae1527a63790ed8 = from_latin_1_string("LD_LIBRARY_PATH=", 16);
  string__4c84a8f87d97d1a3 = from_latin_1_string("included object files: ", 23);
  string__d2a77fcc4263ea03 = from_latin_1_string("needed libraries: ", 18);
  func__show_file_list_2 = create_function(entry__show_file_list_2, 0);
  func__show_file_list_1 = create_function(entry__show_file_list_1, 0);
  string__2d7981f4e6602b89 = from_latin_1_string("-L", 2);
  string__47d536100241702d = from_latin_1_string("library paths: ", 15);
  string__585ae883ea60d02f = from_latin_1_string("linux", 5);
  string__fa720c15db16ba8 = from_latin_1_string("bsd", 3);
  string__ec1f556601f292b5 = from_latin_1_string("-l:lib", 6);
  string__9e0aed8b5d187d17 = from_latin_1_string(".so.", 4);
  string__2d7981f4e6602ba9 = from_latin_1_string("-l", 2);
  func__library_paths_and_file_list_1 = create_function(entry__library_paths_and_file_list_1, 0);
  string__b8540cde1593c09c = from_latin_1_string("typedef", 7);
  string__800a0c585ff0632 = from_latin_1_string("REGISTER", 8);
  string__ee0186bb316753e3 = from_latin_1_string("typedef struct", 14);
  string__eca001441419c0da = from_latin_1_string("IMPORT ", 7);
  func__create_imports_54 = create_function(entry__create_imports_54, 0);
  string__736c99bf90749400 = from_latin_1_string("// INSERT HERE //", 17);
  string__868d47f2e5ba5079 = from_latin_1_string("collecting imports", 18);
  func__create_imports_74 = create_function(entry__create_imports_74, 0);
  func__create_imports_1 = create_function(entry__create_imports_1, 1);
  string__ac6b0fa074ea65e7 = from_latin_1_string("Expected a source code file!", 28);
  func__compile_exe_3 = create_function(entry__compile_exe_3, 0);
  string__e365e96bee331e9c = from_latin_1_string("Expected \042.sim\042 file extension in source filename!", 50);
  func__compile_exe_7 = create_function(entry__compile_exe_7, 0);
  func__compile_exe_1 = create_function(entry__compile_exe_1, 1);
  func__dump_source_or_check_2 = create_function(entry__dump_source_or_check_2, 2);
  func__dump_source_or_check_1 = create_function(entry__dump_source_or_check_1, 0);
  string__b830f06b636224ab = from_latin_1_string("writing C-source", 16);
  func__print_c_18 = create_function(entry__print_c_18, 0);
  func__print_c_2 = create_function(entry__print_c_2, 2);
  func__print_c_1 = create_function(entry__print_c_1, 0);
  func__list_dependencies_3 = create_function(entry__list_dependencies_3, 2);
  string__7da4130a131d4ea3 = from_latin_1_string("list dependencies for ", 22);
  func__list_dependencies_17 = create_function(entry__list_dependencies_17, 0);
  func__list_dependencies_16 = create_function(entry__list_dependencies_16, 0);
  func__list_dependencies_24 = create_function(entry__list_dependencies_24, 2);
  string__5aa0e0654e0a7d4d = from_latin_1_string("runtime/linker.c", 16);
  string__7490e2a4ce0a3d6d = from_latin_1_string("runtime/memory.c", 16);
  string__14e71717a54948b0 = from_latin_1_string("runtime/debugger.c", 18);
  func__list_dependencies_23 = create_function(entry__list_dependencies_23, 0);
  func__list_dependencies_1 = create_function(entry__list_dependencies_1, 0);
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
  string__3a69827feeaedc87 = from_latin_1_string(
    "\042 />\n"
    "    <Option pch_mode=\0422\042 />\n"
    "    <Option compiler=c_compiler() />\n"
    "    <Build>\n"
    "      <Target title=\042debug\042>\n"
    "        <Option output=\042bin/debug/",
    145);
  string__65fb167cf21c35a9 = from_latin_1_string(
    "\042 prefix_auto=\0421\042 extension_auto=\0421\042 />\n"
    "        <Option object_output=\042obj/debug/\042 />\n"
    "        <Option type=\0421\042 />\n"
    "        <Option compiler=c_compiler() />\n"
    "        <Compiler>\n"
    "          <Add option=\042-g\042 />\n"
    "        </Compiler>\n"
    "      </Target>\n"
    "    </Build>\n"
    "    <Linker>\n",
    266);
  string__86909867946dc27b = from_latin_1_string("      <Add library=\042", 20);
  string__ca5af8c3e83c305d = from_latin_1_string("\042 />\012", 5);
  string__4f8ac82e5b683b6f = from_latin_1_string(
    "\n"
    "    </Linker>\n"
    "    <Compiler>\n"
    "      <Add option=\042-Wall\042 />\n"
    "    </Compiler>\n"
    "    <Unit filename=\042",
    95);
  string__6ec73fb9d26dad91 = from_latin_1_string(
    "runtime/common.h\042 />\n"
    "    <Unit filename=\042",
    41);
  string__62c73cb6d2cd6da9 = from_latin_1_string(
    "runtime/linker.h\042 />\n"
    "    <Unit filename=\042",
    41);
  string__e224568f04fadefb = from_latin_1_string(
    "runtime/memory.c\042>\n"
    "      <Option compilerVar=\042",
    46);
  string__29a08e6f8046de11 = from_latin_1_string(
    "\042 />\n"
    "    </Unit>\n"
    "    <Unit filename=\042",
    37);
  string__97a58959c957d32c = from_latin_1_string(
    "runtime/debugger.c\042>\n"
    "      <Option compilerVar=\042",
    48);
  string__629c968402fadffb = from_latin_1_string(
    "runtime/linker.c\042>\n"
    "      <Option compilerVar=\042",
    46);
  string__517e18f604196bbc = from_latin_1_string(
    "\042 />\n"
    "    </Unit>\n",
    17);
  string__5ce0e5ba1304a164 = from_latin_1_string(
    "\n"
    "    <Unit filename=\042",
    21);
  string__48b865872b902196 = from_latin_1_string(
    "\042>\n"
    "      <Option compilerVar=\042",
    30);
  string__1d1cedd7cdd611c4 = from_latin_1_string(
    "    <Extensions>\n"
    "      <code_completion />\n"
    "      <debugger />\n"
    "    </Extensions>\n"
    "  </Project>\n"
    "</CodeBlocks_project_file>\n",
    120);
  func__build_codeblocks_project_2 = create_function(entry__build_codeblocks_project_2, 2);
  func__build_codeblocks_project_1 = create_function(entry__build_codeblocks_project_1, 0);
  string__421f52c90112c2b9 = from_latin_1_string("simrun", 6);
  string__c84d9037a41e8f73 = from_latin_1_string("Cannot run a directory!", 23);
  func__build_library_4 = create_function(entry__build_library_4, 0);
  func__build_library_7 = create_function(entry__build_library_7, 0);
  string__84ca78485aeb98e = from_latin_1_string("/VERSION", 8);
  string__94340f9615d2e0d7 = from_latin_1_string("libsim-", 7);
  string__9e0ae84b5d007d55 = from_latin_1_string(".dll", 4);
  string__6a1f556781f212b5 = from_latin_1_string(".dylib", 6);
  string__561f538101f3c2b9 = from_latin_1_string("cygwin", 6);
  string__7c1f538281f242b9 = from_latin_1_string("darwin", 6);
  string__822587b3f48532f5 = from_latin_1_string("build library ", 14);
  func__build_library_58 = create_function(entry__build_library_58, 0);
  string__b9aef2a4efc3a1a8 = from_latin_1_string("linking dynamic library", 23);
  func__build_library_61 = create_function(entry__build_library_61, 0);
  string__f5937b2655b3cd24 = from_latin_1_string("-Wl,-soname,libsim-", 19);
  string__b130095b1592409e = from_latin_1_string("-shared", 7);
  string__7e1f542601d292fa = from_latin_1_string("-lsim-", 6);
  string__33820b08e3b95a2a = from_latin_1_string("-Wl,-install_name,libsim-", 25);
  string__c6d9125d36413a91 = from_latin_1_string("-dynamiclib", 11);
  func__build_library_13 = create_function(entry__build_library_13, 0);
  func__build_library_1 = create_function(entry__build_library_1, 0);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  string__7ef24f7974bbce09 = from_latin_1_string("\042 does not exist!\012", 18);
  string__74150357c2230d49 = from_latin_1_string("compiling runtime module ", 25);
  func__maybe_compile_c_file_1 = create_function(entry__maybe_compile_c_file_1, 1);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  string__578a5af303e9cd1 = from_latin_1_string("0", 1);
  func__format_number_1 = create_function(entry__format_number_1, -1);
  string__2d7981f4e6082bb6 = from_latin_1_string(" s", 2);
  string__2d7981f4e6d82be5 = from_latin_1_string(": ", 2);
  func__sim2c__write_timing_info_1 = create_function(entry__sim2c__write_timing_info_1, -1);
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
  func__build_executable_1 = create_function(entry__build_executable_1, 0);
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
  func__109_2 = create_function(entry__109_2, 0);
  func__109_6 = create_function(entry__109_6, 0);
  func__109_8 = create_function(entry__109_8, 0);
  func__110_2 = create_function(entry__110_2, 0);
  func__110_6 = create_function(entry__110_6, 0);
  func__110_8 = create_function(entry__110_8, 0);
  string__545aefc3ea81102f = from_latin_1_string("posix", 5);
  string__fa720015d496ba0 = from_latin_1_string("all", 3);
  string__fa725815d616ba2 = from_latin_1_string("win", 3);
  func__114_1 = create_function(entry__114_1, 0);
  string__8d3c5e4b22d2f22b = from_latin_1_string("Missing command line arguments!", 31);
  func__142_4 = create_function(entry__142_4, 0);
  func__142_2 = create_function(entry__142_2, 0);
  string__2b680b9e2e4fa558 = from_latin_1_string("check-only", 10);
  string__8d1eb0934cb703aa = from_latin_1_string("do not compile; just check for syntax errors\012", 45);
  func__142_9 = create_function(entry__142_9, 0);
  string__1124317d33023452 = from_latin_1_string("dump-trees", 10);
  string__d3c3199b9e37dd88 = from_latin_1_string("dump abstract syntax trees\012", 27);
  func__142_12 = create_function(entry__142_12, 0);
  string__2eb9522bce550419 = from_latin_1_string("pretty-print", 12);
  string__31ed31d8e6f28138 = from_latin_1_string("do not compile; just pretty print the source file\012", 50);
  func__142_15 = create_function(entry__142_15, 0);
  string__23efc30ce16df2e = from_latin_1_string("print-simplified-source", 23);
  string__c565f1870e113429 = from_latin_1_string("do not generate a C-file; just print the simplified source text\012", 64);
  func__142_18 = create_function(entry__142_18, 0);
  string__ae4408db97d25099 = from_latin_1_string("print-c", 7);
  string__2623b8ba9cf2f994 = from_latin_1_string("print C source code for a single module\012", 40);
  func__142_21 = create_function(entry__142_21, 0);
  string__a7e97d93a221bbf6 = from_latin_1_string("time-passes", 11);
  string__fa3ca2557b3c0271 = from_latin_1_string("print running time for the individual compiler passes\012", 54);
  func__142_24 = create_function(entry__142_24, 0);
  string__c95e7978381b7632 = from_latin_1_string("module-prefix", 13);
  string__4cca41e5ff59895a = from_latin_1_string(
    "needed to compile a single file within a subdirectory;\n"
    "if the subdirectories are nested use slashes to separate\n"
    "the directory names\n",
    132);
  func__142_27 = create_function(entry__142_27, 0);
  string__6e5ae943eae03031 = from_latin_1_string("brief", 5);
  string__22ca0f65643a26b5 = from_latin_1_string("show brief error messages\012", 26);
  func__142_30 = create_function(entry__142_30, 0);
  string__7c90ae5f04ed72b3 = from_latin_1_string("warnings", 8);
  string__ea6d59fa9dcad709 = from_latin_1_string("show warning messages\012", 22);
  func__142_33 = create_function(entry__142_33, 0);
  string__94300f9615cbf09d = from_latin_1_string("missing", 7);
  string__aa7c4ea56fedf95b = from_latin_1_string("inform about missing documentation\012", 35);
  func__142_36 = create_function(entry__142_36, 0);
  string__a8480d98152a1083 = from_latin_1_string("summary", 7);
  string__10671df6f7523277 = from_latin_1_string("show a statistical summary\012", 27);
  func__142_39 = create_function(entry__142_39, 0);
  string__b65c0e101523e09f = from_latin_1_string("verbose", 7);
  string__2ba4a5a9cdae43b8 = from_latin_1_string("output verbose informations\012", 28);
  func__142_42 = create_function(entry__142_42, 0);
  string__405aeb83ea605030 = from_latin_1_string("debug", 5);
  string__977692d258cc57f = from_latin_1_string("show C-compiler and linker calls\012", 33);
  func__142_45 = create_function(entry__142_45, 0);
  string__d13d99340b731341 = from_latin_1_string("debug_compiler", 14);
  string__d30c0a59c3d26b04 = from_latin_1_string("show internal debug messages of the Simplicity compiler\012", 56);
  func__142_48 = create_function(entry__142_48, 0);
  string__2b7008daa973b572 = from_latin_1_string("codeblocks", 10);
  string__99c92c9b20cfd38 = from_latin_1_string("create Code::Blocks project\012", 28);
  func__142_51 = create_function(entry__142_51, 0);
  string__7f0dce6ce0a2268e = from_latin_1_string("extract-documentation", 21);
  string__140146cb87bc0040 = from_latin_1_string("extract documentation encoded as HTML\012", 38);
  func__142_54 = create_function(entry__142_54, 0);
  string__211e9dd763481194 = from_latin_1_string("list-dependencies", 17);
  string__1214925be130f2c = from_latin_1_string("list all dependencies\012", 22);
  func__142_57 = create_function(entry__142_57, 0);
  string__984c0f9015dae09e = from_latin_1_string("rebuild", 7);
  string__6ce7f8f6c7e73eb4 = from_latin_1_string("rebuild all source files\012", 25);
  func__142_60 = create_function(entry__142_60, 0);
  string__749427e68da7a564 = from_latin_1_string("omit-meta", 9);
  string__93608261e3431133 = from_latin_1_string("do not rebuild meta files\012", 26);
  func__142_63 = create_function(entry__142_63, 0);
  string__5a1f534901f312b4 = from_latin_1_string("static", 6);
  string__b20e03a80d6db737 = from_latin_1_string("create statically linked executable\012", 36);
  func__142_66 = create_function(entry__142_66, 0);
  string__be440f9b95da309f = from_latin_1_string("profile", 7);
  string__6f1f4f6107c9cdea = from_latin_1_string("link with libprofiler\012", 22);
  func__142_69 = create_function(entry__142_69, 0);
  string__72b0ad9004bdc085 = from_latin_1_string("filename", 8);
  string__bb8770c27da8f42f = from_latin_1_string("the name of the source file or directory to compile\012", 52);
  func__142_72 = create_function(entry__142_72, 0);
  string__af5ae49d07a6e408 = from_latin_1_string("additional_libraries", 20);
  string__c8a7274dc08e5785 = from_latin_1_string("the names of additional libraries (used for --extract-documentation)\012", 69);
  func__142_75 = create_function(entry__142_75, 0);
  func__142_8 = create_function(entry__142_8, 0);
  func__146_1 = create_function(entry__146_1, 0);
  string__245aeb43eaacc03b = from_latin_1_string("-Wall", 5);
  string__e381a5286a12b5a7 = from_latin_1_string("-Wno-unused-function", 20);
  string__c9d1a7e66a0a17ac = from_latin_1_string("-Wno-unused-variable", 20);
  string__1abcc193f1dac47a = from_latin_1_string("-Wno-parentheses", 16);
  string__d3e88c522110dabb = from_latin_1_string("-Wno-switch", 11);
  string__65a7cd1120033166 = from_latin_1_string("-Wno-trigraphs", 14);
  string__fa733015c516bfd = from_latin_1_string("-O1", 3);
  string__465ae703eb84c014 = from_latin_1_string("-fPIC", 5);
  string__40ebeb253b72cf38 = from_latin_1_string("-fno-stack-protector", 20);
  string__edf2e5a02a882fc3 = from_latin_1_string("-falign-functions=16", 20);
  string__fa721815d316baf = from_latin_1_string("gcc", 3);
  string__ecde9da404625e23 = from_latin_1_string("-Wno-maybe-uninitialized", 24);
  func__153_4 = create_function(entry__153_4, 0);
  string__f41f598c8327d2e5 = from_latin_1_string("x86_32", 6);
  string__f41f598c830fd2e3 = from_latin_1_string("x86_64", 6);
  string__7e1f52a6019282e5 = from_latin_1_string("-msse2", 6);
  string__70d94c874a06872f = from_latin_1_string("-mfpmath=sse", 12);
  func__154_5 = create_function(entry__154_5, 0);
  string__2d7981f4e6602b8c = from_latin_1_string("-I", 2);
  func__155_1 = create_function(entry__155_1, 1);
  func__157_3 = create_function(entry__157_3, 1);
  func__159_3 = create_function(entry__159_3, 1);
  string__9b6a42533552c66c = from_latin_1_string("Source file \042", 13);
  string__79c06fde49ef2e97 = from_latin_1_string("\042 does not exist!", 17);
  func__177_2 = create_function(entry__177_2, 0);
  func__192_1 = create_function(entry__192_1, 0);
  func__193_4 = create_function(entry__193_4, 0);
  func__193_3 = create_function(entry__193_3, 0);
  func__193_2 = create_function(entry__193_2, 0);
  func__193_1 = create_function(entry__193_1, 0);
  func__193_8 = create_function(entry__193_8, 0);
  func__193_9 = create_function(entry__193_9, 0);
  func__193_10 = create_function(entry__193_10, 0);
  func__193_11 = create_function(entry__193_11, 0);

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
  var._default_paths = create_future();
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
  assign_variable(&var.sim2c__show_compiler_debug_info, &func__sim2c__show_compiler_debug_info_1);
  maybe_initialize_future(get__mode(), get__undefined());
  maybe_initialize_future(get__on_top_level(), get__true());
  assign_variable(&var._resolve_filename, &func__resolve_filename_1);
  assign_variable(&var._add_module_infos, &func__add_module_infos_1);
  assign_variable(&var._lookup, &func__lookup_1);
  assign_variable(&var._CC, &func__CC_1);
  assign_variable(&var._compile_c, &func__compile_c_1);
  assign_variable(&var._compile_meta_module, &func__compile_meta_module_1);
  assign_variable(&var._build_dependencies, &func__build_dependencies_1);
  assign_variable(&var._compile_module, &func__compile_module_1);
  assign_variable(&var._compile_modules, &func__compile_modules_1);
  assign_variable(&var._show_file_list, &func__show_file_list_1);
  assign_variable(&var._library_paths_and_file_list, &func__library_paths_and_file_list_1);
  assign_variable(&var._create_imports, &func__create_imports_1);
  assign_variable(&var._compile_exe, &func__compile_exe_1);
  assign_variable(&var._dump_source_or_check, &func__dump_source_or_check_1);
  assign_variable(&var._print_c, &func__print_c_1);
  assign_variable(&var._list_dependencies, &func__list_dependencies_1);
  assign_variable(&var._build_codeblocks_project, &func__build_codeblocks_project_1);
  assign_variable(&var._build_library, &func__build_library_1);
  assign_variable(&var._maybe_compile_c_file, &func__maybe_compile_c_file_1);
  assign_variable(&var._format_number, &func__format_number_1);
  assign_variable(&var.sim2c__write_timing_info, &func__sim2c__write_timing_info_1);
  assign_variable(&var._build_executable, &func__build_executable_1);
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