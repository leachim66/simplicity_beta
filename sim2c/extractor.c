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
typedef struct FUNCTION {
  FUNC type;
  struct ATTRIBUTES *attributes;
  int parameter_count;
} FUNCTION;
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
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
REGISTER FRAME *arguments ASM("r12");
REGISTER int argument_count ASM("ebx");
IMPORT void invalid_arguments_error(void);
IMPORT NODE *clone_object_and_attributes(NODE *node);
IMPORT void *update_start_p;
IMPORT void *node_p;
IMPORT void set_attribute_value(ATTRIBUTES *attributes, int idx, void *attr);
REGISTER FUNC func ASM("r14");
REGISTER FRAME *frame ASM("r15");
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
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *undefined;
IMPORT NODE *create_future(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_continuation(void);
IMPORT NODE *create_cell(void);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT NODE *create_cell_with_contents(NODE *contents);
IMPORT NODE *empty_string;
IMPORT NODE *zero;
IMPORT void too_few_arguments_error(void);
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT void define_single_assign_static(
  const char *namespace, const char *name,
  NODE_GETTER getter, NODE **var_p
);
IMPORT void use_read_only(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_GETTER *get_value_or_future
);
IMPORT void use_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER *getter, int *id
);
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void assign_variable(NODE **dest, NODE **var_p);
IMPORT void register_collector(FUNC collector);


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
static NODE_GETTER get__A;
static NODE_GETTER get_value_or_future__A;
static NODE_GETTER get__ANY_CHARACTER;
static NODE_GETTER get_value_or_future__ANY_CHARACTER;
static NODE_GETTER get__ATTRIBUTE_KIND;
static NODE_GETTER get_value_or_future__ATTRIBUTE_KIND;
static NODE_GETTER get__BODY;
static NODE_GETTER get_value_or_future__BODY;
static NODE_GETTER get__BR;
static NODE_GETTER get_value_or_future__BR;
static NODE_GETTER get__CONTINUATION_PARAMETER;
static NODE_GETTER get_value_or_future__CONTINUATION_PARAMETER;
static NODE_GETTER get__DD;
static NODE_GETTER get_value_or_future__DD;
static NODE_GETTER get__DIV;
static NODE_GETTER get_value_or_future__DIV;
static NODE_GETTER get__DL;
static NODE_GETTER get_value_or_future__DL;
static NODE_GETTER get__DT;
static NODE_GETTER get_value_or_future__DT;
static NODE_GETTER get__DYNAMIC_MULTI;
static NODE_GETTER get_value_or_future__DYNAMIC_MULTI;
static NODE_GETTER get__DYNAMIC_SINGLE;
static NODE_GETTER get_value_or_future__DYNAMIC_SINGLE;
static NODE_GETTER get__Error;
static NODE_GETTER get_value_or_future__Error;
static NODE_GETTER get__H1;
static NODE_GETTER get_value_or_future__H1;
static NODE_GETTER get__H2;
static NODE_GETTER get_value_or_future__H2;
static NODE_GETTER get__HEAD;
static NODE_GETTER get_value_or_future__HEAD;
static NODE_GETTER get__HTML;
static NODE_GETTER get_value_or_future__HTML;
static NODE_GETTER get__IDENTIFIER;
static NODE_GETTER get_value_or_future__IDENTIFIER;
static NODE_GETTER get__METHOD_KIND;
static NODE_GETTER get_value_or_future__METHOD_KIND;
static NODE_GETTER get__MYSELF_PARAMETER;
static NODE_GETTER get_value_or_future__MYSELF_PARAMETER;
static NODE_GETTER get__NAME;
static NODE_GETTER get_value_or_future__NAME;
static NODE_GETTER get__NONE;
static NODE_GETTER get_value_or_future__NONE;
static NODE_GETTER get__P;
static NODE_GETTER get_value_or_future__P;
static NODE_GETTER get__PRE;
static NODE_GETTER get_value_or_future__PRE;
static NODE_GETTER get__SORT;
static NODE_GETTER get_value_or_future__SORT;
static NODE_GETTER get__STATIC_MULTI;
static NODE_GETTER get_value_or_future__STATIC_MULTI;
static NODE_GETTER get__STYLE;
static NODE_GETTER get_value_or_future__STYLE;
static NODE_GETTER get__TABLE;
static NODE_GETTER get_value_or_future__TABLE;
static NODE_GETTER get__TD;
static NODE_GETTER get_value_or_future__TD;
static NODE_GETTER get__TEXT;
static NODE_GETTER get_value_or_future__TEXT;
static NODE_GETTER get__TR;
static NODE_GETTER get_value_or_future__TR;
static NODE_GETTER get__alt;
static NODE_GETTER get_value_or_future__alt;
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get_value_or_future__arguments_of;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static int poly_idx__attribute_of;
static NODE_GETTER get__attribute_of;
static int poly_idx__base_of;
static NODE_GETTER get__base_of;
static NODE_GETTER get__before;
static NODE_GETTER get_value_or_future__before;
static NODE_GETTER get__behind;
static NODE_GETTER get_value_or_future__behind;
static NODE_GETTER get__between;
static NODE_GETTER get_value_or_future__between;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__collect_output;
static NODE_GETTER get_value_or_future__collect_output;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static NODE_GETTER get__contains;
static NODE_GETTER get_value_or_future__contains;
static NODE_GETTER get__cut_into_fragments;
static NODE_GETTER get_value_or_future__cut_into_fragments;
static NODE_GETTER get__default_value;
static NODE_GETTER get_value_or_future__default_value;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get_value_or_future__default_value_of;
static NODE_GETTER get__directory;
static NODE_GETTER get_value_or_future__directory;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_print_missing;
static NODE_GETTER get_value_or_future__do_print_missing;
static NODE_GETTER get__do_print_summary;
static NODE_GETTER get_value_or_future__do_print_summary;
static NODE_GETTER get__do_print_warnings;
static NODE_GETTER get_value_or_future__do_print_warnings;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__empty_insert_order_set;
static NODE_GETTER get_value_or_future__empty_insert_order_set;
static NODE_GETTER get__empty_insert_order_table;
static NODE_GETTER get_value_or_future__empty_insert_order_table;
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
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__from_to;
static NODE_GETTER get_value_or_future__from_to;
static NODE_GETTER get__from_utf8;
static NODE_GETTER get_value_or_future__from_utf8;
static NODE_GETTER get__fullname_of;
static NODE_GETTER get_value_or_future__fullname_of;
static NODE_GETTER get__has_prefix;
static NODE_GETTER get_value_or_future__has_prefix;
static NODE_GETTER get__has_suffix;
static NODE_GETTER get_value_or_future__has_suffix;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get_value_or_future__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__is_a_body;
static NODE_GETTER get_value_or_future__is_a_body;
static NODE_GETTER get__is_a_c_body;
static NODE_GETTER get_value_or_future__is_a_c_body;
static NODE_GETTER get__is_a_constant;
static NODE_GETTER get_value_or_future__is_a_constant;
static NODE_GETTER get__is_a_definition;
static NODE_GETTER get_value_or_future__is_a_definition;
static NODE_GETTER get__is_a_directory;
static NODE_GETTER get_value_or_future__is_a_directory;
static NODE_GETTER get__is_a_polymorphic_function_constant;
static NODE_GETTER get_value_or_future__is_a_polymorphic_function_constant;
static NODE_GETTER get__is_a_remark;
static NODE_GETTER get_value_or_future__is_a_remark;
static NODE_GETTER get__is_a_setter;
static NODE_GETTER get_value_or_future__is_a_setter;
static NODE_GETTER get__is_a_unique_item_constant;
static NODE_GETTER get_value_or_future__is_a_unique_item_constant;
static NODE_GETTER get__is_an_assignment;
static NODE_GETTER get_value_or_future__is_an_assignment;
static NODE_GETTER get__is_an_expanded_item;
static NODE_GETTER get_value_or_future__is_an_expanded_item;
static NODE_GETTER get__is_an_identifier;
static NODE_GETTER get_value_or_future__is_an_identifier;
static NODE_GETTER get__is_an_optional_item;
static NODE_GETTER get_value_or_future__is_an_optional_item;
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
static int poly_idx__kind_of;
static NODE_GETTER get__kind_of;
static NODE_GETTER get__length_of;
static NODE_GETTER get_value_or_future__length_of;
static NODE_GETTER get__list;
static NODE_GETTER get_value_or_future__list;
static NODE_GETTER get__load;
static NODE_GETTER get_value_or_future__load;
static NODE_GETTER get__many;
static NODE_GETTER get_value_or_future__many;
static NODE_GETTER get__multi_dimensional_set;
static NODE_GETTER get_value_or_future__multi_dimensional_set;
static int poly_idx__name_of;
static NODE_GETTER get__name_of;
static NODE_GETTER get__namespace_of;
static NODE_GETTER get_value_or_future__namespace_of;
static NODE_GETTER get__newline;
static NODE_GETTER get_value_or_future__newline;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static NODE_GETTER get__not_followed_by;
static NODE_GETTER get_value_or_future__not_followed_by;
static NODE_GETTER get__optional;
static NODE_GETTER get_value_or_future__optional;
static NODE_GETTER get__output_arguments_of;
static NODE_GETTER get_value_or_future__output_arguments_of;
static NODE_GETTER get__pad_left;
static NODE_GETTER get_value_or_future__pad_left;
static NODE_GETTER get__parameter_kind_of;
static NODE_GETTER get_value_or_future__parameter_kind_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__parse_meta_instruction;
static NODE_GETTER get_value_or_future__parse_meta_instruction;
static NODE_GETTER get__parse_statement;
static NODE_GETTER get_value_or_future__parse_statement;
static NODE_GETTER get__pass;
static NODE_GETTER get_value_or_future__pass;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static int poly_idx__remark_lines_of;
static NODE_GETTER get__remark_lines_of;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static NODE_GETTER get__save;
static NODE_GETTER get_value_or_future__save;
static NODE_GETTER get__sequence;
static NODE_GETTER get_value_or_future__sequence;
static NODE_GETTER get__sim2c__WHITESPACE;
static NODE_GETTER get_value_or_future__sim2c__WHITESPACE;
static NODE_GETTER get__sim2c__defined_namespaces;
static NODE_SETTER set__sim2c__defined_namespaces;
static NODE_SETTER define__sim2c__defined_namespaces;
static NODE_GETTER get__sim2c__enumeration_count;
static NODE_SETTER set__sim2c__enumeration_count;
static NODE_SETTER define__sim2c__enumeration_count;
static NODE_GETTER get__sim2c__included_files;
static NODE_SETTER set__sim2c__included_files;
static NODE_SETTER define__sim2c__included_files;
static NODE_GETTER get__sim2c__linked_libraries;
static NODE_SETTER set__sim2c__linked_libraries;
static NODE_SETTER define__sim2c__linked_libraries;
static NODE_GETTER get__sim2c__module_name;
static NODE_SETTER define__sim2c__module_name;
static NODE_GETTER get__sim2c__namespace_mappings;
static NODE_SETTER set__sim2c__namespace_mappings;
static NODE_SETTER define__sim2c__namespace_mappings;
static NODE_GETTER get__sim2c__required_modules;
static NODE_SETTER set__sim2c__required_modules;
static NODE_SETTER define__sim2c__required_modules;
static NODE_GETTER get__sim2c__used_namespaces;
static NODE_SETTER set__sim2c__used_namespaces;
static NODE_SETTER define__sim2c__used_namespaces;
static NODE_GETTER get__some;
static NODE_GETTER get_value_or_future__some;
static NODE_GETTER get__source_of;
static NODE_GETTER get_value_or_future__source_of;
static NODE_GETTER get__split;
static NODE_GETTER get_value_or_future__split;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__less;
static NODE_GETTER get_value_or_future__std__less;
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
static NODE_GETTER get__std__true;
static NODE_GETTER get_value_or_future__std__true;
static NODE_GETTER get__std__value_of;
static NODE_GETTER get_value_or_future__std__value_of;
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
static NODE_GETTER get__to_lower_case;
static NODE_GETTER get_value_or_future__to_lower_case;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__to_upper_case;
static NODE_GETTER get_value_or_future__to_upper_case;
static NODE_GETTER get__tokenize;
static NODE_GETTER get_value_or_future__tokenize;
static NODE_GETTER get__trim;
static NODE_GETTER get_value_or_future__trim;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__truncate_behind;
static NODE_GETTER get_value_or_future__truncate_behind;
static NODE_GETTER get__truncate_from;
static NODE_GETTER get_value_or_future__truncate_from;
static NODE_GETTER get__truncate_until;
static NODE_GETTER get_value_or_future__truncate_until;
static NODE_GETTER get__types__key_order_set;
static NODE_GETTER get_value_or_future__types__key_order_set;
static NODE_GETTER get__types__key_order_table;
static NODE_GETTER get_value_or_future__types__key_order_table;
static NODE_GETTER get__types__object;
static NODE_GETTER get_value_or_future__types__object;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__until;
static NODE_GETTER get_value_or_future__until;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static NODE_GETTER get__used_namespaces;
static NODE_SETTER set__used_namespaces;
static int poly_idx__variable_kind_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get__without_prefix;
static NODE_GETTER get_value_or_future__without_prefix;
static NODE_GETTER get__without_suffix;
static NODE_GETTER get_value_or_future__without_suffix;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static NODE_GETTER get__writeln_to;
static NODE_GETTER get_value_or_future__writeln_to;
static struct {
  NODE *_filename_of;
  NODE *_used_namespaces_of;
  NODE *_derived_types_of;
  NODE *_methods_of;
  NODE *_types_of;
  NODE *_polymorphic_functions;
  NODE *_definitions;
  NODE *_short_descriptions;
  NODE *_topics;
  NODE *_missing_documentation_count;
  NODE *_FUNCTION;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_POLYMORPHIC_ATTRIBUTE;
  NODE *_INLINE_C_TYPE;
  NODE *_INLINE_C_OBJECT;
  NODE *_INLINE_C_FUNCTION;
  NODE *_UNIQUE_ITEM;
  NODE *_CONSTANT;
  NODE *_OTHER;
  NODE *_PARAMETER_COUNT_OR_MYSELF;
  NODE *_path_prefix;
  NODE *_create_page;
  NODE *_symbol_info;
  NODE *_extract_documentation_from_file;
  NODE *_extract_documentation_from_directory;
  NODE *_resolved_name;
  NODE *_add_derived_type;
  NODE *_mangled;
  NODE *_ordered_name;
  NODE *_link_bar;
  NODE *_TOPIC;
  NODE *_EXAMPLE;
  NODE *_to_paragraphs;
  NODE *_resolve_reference;
  NODE *_add_links;
  NODE *_create_info_page;
  NODE *_get_short_description;
  NODE *sim2c__extract_documentation;
} var;
static const char *var_names[] = {
  "filename_of",
  "used_namespaces_of",
  "derived_types_of",
  "methods_of",
  "types_of",
  "polymorphic_functions",
  "definitions",
  "short_descriptions",
  "topics",
  "missing_documentation_count",
  "FUNCTION",
  "POLYMORPHIC_FUNCTION",
  "POLYMORPHIC_ATTRIBUTE",
  "INLINE_C_TYPE",
  "INLINE_C_OBJECT",
  "INLINE_C_FUNCTION",
  "UNIQUE_ITEM",
  "CONSTANT",
  "OTHER",
  "PARAMETER_COUNT_OR_MYSELF",
  "path_prefix",
  "create_page",
  "symbol_info",
  "extract_documentation_from_file",
  "extract_documentation_from_directory",
  "resolved_name",
  "add_derived_type",
  "mangled",
  "ordered_name",
  "link_bar",
  "TOPIC",
  "EXAMPLE",
  "to_paragraphs",
  "resolve_reference",
  "add_links",
  "create_info_page",
  "get_short_description"
};
static int poly_idx__filename_of;
static void type__filename_of(void);
static int poly_idx__used_namespaces_of;
static void type__used_namespaces_of(void);
static int poly_idx__derived_types_of;
static void type__derived_types_of(void);
static int poly_idx__methods_of;
static void type__methods_of(void);
static int poly_idx__types_of;
static void type__types_of(void);
static NODE *unique__FUNCTION;
static NODE *unique__POLYMORPHIC_FUNCTION;
static NODE *unique__POLYMORPHIC_ATTRIBUTE;
static NODE *unique__INLINE_C_TYPE;
static NODE *unique__INLINE_C_OBJECT;
static NODE *unique__INLINE_C_FUNCTION;
static NODE *unique__UNIQUE_ITEM;
static NODE *unique__CONSTANT;
static NODE *unique__OTHER;
static NODE *func__22_1_create_page;
static void entry__22_1_create_page(void);
static FRAME_INFO frame__22_1_create_page = {3, {"filename", "body", "page"}};
static NODE *func__22_2;
static void entry__22_2(void);
static FRAME_INFO frame__22_2 = {1, {"body"}};
static NODE *func__22_3;
static void entry__22_3(void);
static FRAME_INFO frame__22_3 = {1, {"body"}};
static NODE *func__22_4;
static void entry__22_4(void);
static FRAME_INFO frame__22_4 = {0, {}};
static NODE *string__22_5;
static void cont__22_6(void);
static void cont__22_7(void);
static NODE *func__24_1_extract_documentation_from_file;
static void entry__24_1_extract_documentation_from_file(void);
static FRAME_INFO frame__24_1_extract_documentation_from_file = {7, {"filename", "return__1", "buf", "fragments", "trees", "first_idx", "local_method_names"}};
static NODE *string__24_2;
static NODE *string__24_3;
static void cont__24_4(void);
static void cont__24_5(void);
static void cont__24_6(void);
static void cont__24_7(void);
static void cont__24_8(void);
static void cont__24_9(void);
static NODE *func__24_10;
static void entry__24_10(void);
static FRAME_INFO frame__24_10 = {0, {}};
static NODE *string__24_11;
static void cont__24_12(void);
static void cont__24_13(void);
static void cont__24_14(void);
static void cont__24_15(void);
static NODE *func__24_16;
static void entry__24_16(void);
static FRAME_INFO frame__24_16 = {0, {}};
static NODE *string__24_17;
static void cont__24_18(void);
static void cont__24_19(void);
static void cont__24_20(void);
static void cont__24_21(void);
static void cont__24_22(void);
static NODE *func__24_23;
static void entry__24_23(void);
static FRAME_INFO frame__24_23 = {0, {}};
static NODE *string__24_24;
static void cont__24_25(void);
static NODE *string__24_26;
static void cont__24_27(void);
static NODE *string__24_28;
static void cont__24_29(void);
static void cont__24_30(void);
static void cont__24_31(void);
static NODE *func__24_32;
static void entry__24_32(void);
static FRAME_INFO frame__24_32 = {1, {"fragment"}};
static void cont__24_33(void);
static void cont__24_34(void);
static NODE *func__24_35;
static void entry__24_35(void);
static FRAME_INFO frame__24_35 = {3, {"done", "fragments", "first_idx"}};
static NODE *func__24_36;
static void entry__24_36(void);
static FRAME_INFO frame__24_36 = {4, {"idx", "fragment", "first_idx", "done"}};
static void cont__24_37(void);
static void cont__24_38(void);
static NODE *func__24_39;
static void entry__24_39(void);
static FRAME_INFO frame__24_39 = {2, {"first_idx", "idx"}};
static void cont__24_40(void);
static NODE *func__24_41;
static void entry__24_41(void);
static FRAME_INFO frame__24_41 = {4, {"first_idx", "idx", "fragment", "tree"}};
static void cont__24_42(void);
static void cont__24_43(void);
static NODE *func__24_44;
static void entry__24_44(void);
static FRAME_INFO frame__24_44 = {1, {"done"}};
static void cont__24_45(void);
static void cont__24_46(void);
static void cont__24_47(void);
static void cont__24_48(void);
static NODE *func__24_49;
static void entry__24_49(void);
static FRAME_INFO frame__24_49 = {2, {"fragment", "trees"}};
static void cont__24_50(void);
static void cont__24_51(void);
static void cont__24_52(void);
static void cont__24_53(void);
static NODE *func__24_54;
static void entry__24_54(void);
static FRAME_INFO frame__24_54 = {0, {}};
static NODE *string__24_55;
static void cont__24_56(void);
static void cont__24_57(void);
static NODE *func__24_58;
static void entry__24_58(void);
static FRAME_INFO frame__24_58 = {2, {"statement", "local_method_names"}};
static NODE *func__24_59;
static void entry__24_59(void);
static FRAME_INFO frame__24_59 = {1, {"statement"}};
static void cont__24_60(void);
static NODE *func__24_61;
static void entry__24_61(void);
static FRAME_INFO frame__24_61 = {0, {}};
static NODE *func__24_62;
static void entry__24_62(void);
static FRAME_INFO frame__24_62 = {1, {"statement"}};
static void cont__24_63(void);
static NODE *func__24_64;
static void entry__24_64(void);
static FRAME_INFO frame__24_64 = {0, {}};
static NODE *func__24_65;
static void entry__24_65(void);
static FRAME_INFO frame__24_65 = {2, {"statement", "local_method_names"}};
static void cont__24_66(void);
static NODE *func__24_67;
static void entry__24_67(void);
static FRAME_INFO frame__24_67 = {3, {"statement", "local_method_names", "destination"}};
static void cont__24_68(void);
static void cont__24_69(void);
static void cont__24_70(void);
static NODE *func__24_71;
static void entry__24_71(void);
static FRAME_INFO frame__24_71 = {4, {"destination", "statement", "local_method_names", "identifier"}};
static void cont__24_72(void);
static void cont__24_73(void);
static void cont__24_74(void);
static NODE *func__24_75;
static void entry__24_75(void);
static FRAME_INFO frame__24_75 = {4, {"statement", "local_method_names", "destination", "source"}};
static void cont__24_76(void);
static void cont__24_77(void);
static void cont__24_78(void);
static NODE *func__24_79;
static void entry__24_79(void);
static FRAME_INFO frame__24_79 = {2, {"local_method_names", "destination"}};
static void cont__24_80(void);
static void cont__24_81(void);
static void cont__24_82(void);
static void cont__24_83(void);
static NODE *func__24_84;
static void entry__24_84(void);
static FRAME_INFO frame__24_84 = {4, {"statement", "break", "filename", "local_method_names"}};
static NODE *func__24_85;
static void entry__24_85(void);
static FRAME_INFO frame__24_85 = {1, {"statement"}};
static void cont__24_86(void);
static NODE *func__24_87;
static void entry__24_87(void);
static FRAME_INFO frame__24_87 = {0, {}};
static NODE *func__24_88;
static void entry__24_88(void);
static FRAME_INFO frame__24_88 = {2, {"statement", "filename"}};
static void cont__24_89(void);
static NODE *func__24_90;
static void entry__24_90(void);
static FRAME_INFO frame__24_90 = {3, {"statement", "filename", "identifier"}};
static void cont__24_91(void);
static void cont__24_92(void);
static NODE *func__24_93;
static void entry__24_93(void);
static FRAME_INFO frame__24_93 = {4, {"identifier", "statement", "filename", "namespace"}};
static void cont__24_94(void);
static void cont__24_95(void);
static NODE *func__24_96;
static void entry__24_96(void);
static FRAME_INFO frame__24_96 = {5, {"identifier", "statement", "namespace", "filename", "name"}};
static void cont__24_97(void);
static void cont__24_98(void);
static NODE *func__24_99;
static void entry__24_99(void);
static FRAME_INFO frame__24_99 = {5, {"namespace", "statement", "name", "identifier", "filename"}};
static void cont__24_100(void);
static NODE *func__24_101;
static void entry__24_101(void);
static FRAME_INFO frame__24_101 = {6, {"statement", "namespace", "name", "identifier", "filename", "base"}};
static void cont__24_102(void);
static void cont__24_103(void);
static void cont__24_104(void);
static NODE *func__24_105;
static void entry__24_105(void);
static FRAME_INFO frame__24_105 = {1, {"base"}};
static void cont__24_106(void);
static NODE *func__24_107;
static void entry__24_107(void);
static FRAME_INFO frame__24_107 = {0, {}};
static void cont__24_108(void);
static void cont__24_109(void);
static void cont__24_110(void);
static void cont__24_111(void);
static NODE *func__24_112;
static void entry__24_112(void);
static FRAME_INFO frame__24_112 = {5, {"namespace", "name", "identifier", "statement", "filename"}};
static void cont__24_113(void);
static void cont__24_114(void);
static void cont__24_115(void);
static void cont__24_116(void);
static NODE *string__24_117;
static NODE *string__24_118;
static NODE *func__24_119;
static void entry__24_119(void);
static FRAME_INFO frame__24_119 = {4, {"statement", "filename", "break", "local_method_names"}};
static void cont__24_120(void);
static NODE *func__24_121;
static void entry__24_121(void);
static FRAME_INFO frame__24_121 = {6, {"statement", "filename", "break", "local_method_names", "destination", "info"}};
static void cont__24_122(void);
static void cont__24_123(void);
static void cont__24_124(void);
static NODE *func__24_125;
static void entry__24_125(void);
static FRAME_INFO frame__24_125 = {7, {"destination", "info", "statement", "break", "local_method_names", "identifier", "namespace"}};
static void cont__24_126(void);
static void cont__24_127(void);
static void cont__24_128(void);
static NODE *func__24_129;
static void entry__24_129(void);
static FRAME_INFO frame__24_129 = {10, {"identifier", "namespace", "info", "destination", "statement", "break", "local_method_names", "name", "iname", "source"}};
static void cont__24_130(void);
static void cont__24_131(void);
static void cont__24_132(void);
static void cont__24_133(void);
static void cont__24_134(void);
static void cont__24_135(void);
static void cont__24_136(void);
static NODE *func__24_137;
static void entry__24_137(void);
static FRAME_INFO frame__24_137 = {6, {"source", "name", "namespace", "iname", "info", "break"}};
static void cont__24_138(void);
static NODE *func__24_139;
static void entry__24_139(void);
static FRAME_INFO frame__24_139 = {6, {"name", "namespace", "iname", "info", "source", "break"}};
static void cont__24_140(void);
static void cont__24_141(void);
static NODE *func__24_142;
static void entry__24_142(void);
static FRAME_INFO frame__24_142 = {0, {}};
static NODE *func__24_143;
static void entry__24_143(void);
static FRAME_INFO frame__24_143 = {0, {}};
static void cont__24_144(void);
static void cont__24_145(void);
static NODE *func__24_146;
static void entry__24_146(void);
static FRAME_INFO frame__24_146 = {3, {"source", "info", "statement"}};
static void cont__24_147(void);
static NODE *func__24_148;
static void entry__24_148(void);
static FRAME_INFO frame__24_148 = {3, {"info", "source", "statement"}};
static void cont__24_149(void);
static void cont__24_150(void);
static void cont__24_151(void);
static NODE *func__24_152;
static void entry__24_152(void);
static FRAME_INFO frame__24_152 = {1, {"source"}};
static void cont__24_153(void);
static NODE *func__24_154;
static void entry__24_154(void);
static FRAME_INFO frame__24_154 = {1, {"statement"}};
static void cont__24_155(void);
static void cont__24_156(void);
static NODE *string__24_157;
static NODE *func__24_158;
static void entry__24_158(void);
static FRAME_INFO frame__24_158 = {2, {"source", "info"}};
static void cont__24_159(void);
static NODE *func__24_160;
static void entry__24_160(void);
static FRAME_INFO frame__24_160 = {1, {"info"}};
static NODE *func__24_161;
static void entry__24_161(void);
static FRAME_INFO frame__24_161 = {2, {"source", "info"}};
static void cont__24_162(void);
static NODE *func__24_163;
static void entry__24_163(void);
static FRAME_INFO frame__24_163 = {2, {"source", "info"}};
static void cont__24_164(void);
static void cont__24_165(void);
static NODE *func__24_166;
static void entry__24_166(void);
static FRAME_INFO frame__24_166 = {2, {"info", "source"}};
static void cont__24_167(void);
static NODE *func__24_168;
static void entry__24_168(void);
static FRAME_INFO frame__24_168 = {4, {"source", "iname", "info", "break"}};
static void cont__24_169(void);
static NODE *func__24_170;
static void entry__24_170(void);
static FRAME_INFO frame__24_170 = {3, {"iname", "info", "break"}};
static void cont__24_171(void);
static NODE *func__24_172;
static void entry__24_172(void);
static FRAME_INFO frame__24_172 = {2, {"source", "info"}};
static void cont__24_173(void);
static NODE *func__24_174;
static void entry__24_174(void);
static FRAME_INFO frame__24_174 = {1, {"info"}};
static void cont__24_175(void);
static void cont__24_176(void);
static NODE *func__24_177;
static void entry__24_177(void);
static FRAME_INFO frame__24_177 = {3, {"iname", "info", "previous_definition"}};
static void cont__24_178(void);
static void cont__24_179(void);
static NODE *func__24_180;
static void entry__24_180(void);
static FRAME_INFO frame__24_180 = {2, {"previous_definition", "info"}};
static void cont__24_181(void);
static void cont__24_182(void);
static NODE *func__24_183;
static void entry__24_183(void);
static FRAME_INFO frame__24_183 = {2, {"info", "previous_definition"}};
static void cont__24_184(void);
static void cont__24_185(void);
static void cont__24_186(void);
static void cont__24_187(void);
static void cont__24_188(void);
static void cont__24_189(void);
static NODE *func__24_190;
static void entry__24_190(void);
static FRAME_INFO frame__24_190 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__24_191(void);
static void cont__24_192(void);
static void cont__24_193(void);
static void cont__24_194(void);
static void cont__24_195(void);
static NODE *func__24_196;
static void entry__24_196(void);
static FRAME_INFO frame__24_196 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__24_197(void);
static void cont__24_198(void);
static NODE *func__24_199;
static void entry__24_199(void);
static FRAME_INFO frame__24_199 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__24_200(void);
static void cont__24_201(void);
static NODE *func__24_202;
static void entry__24_202(void);
static FRAME_INFO frame__24_202 = {1, {"attr"}};
static void cont__24_203(void);
static void cont__24_204(void);
static void cont__24_205(void);
static void cont__24_206(void);
static void cont__24_207(void);
static void cont__24_208(void);
static void cont__24_209(void);
static void cont__24_210(void);
static NODE *func__25_1_extract_documentation_from_directory;
static void entry__25_1_extract_documentation_from_directory(void);
static FRAME_INFO frame__25_1_extract_documentation_from_directory = {1, {"path"}};
static void cont__25_2(void);
static void cont__25_3(void);
static NODE *func__25_4;
static void entry__25_4(void);
static FRAME_INFO frame__25_4 = {2, {"entry", "name"}};
static void cont__25_5(void);
static NODE *func__25_6;
static void entry__25_6(void);
static FRAME_INFO frame__25_6 = {2, {"entry", "name"}};
static void cont__25_7(void);
static NODE *func__25_8;
static void entry__25_8(void);
static FRAME_INFO frame__25_8 = {1, {"name"}};
static NODE *func__25_9;
static void entry__25_9(void);
static FRAME_INFO frame__25_9 = {1, {"name"}};
static void cont__25_10(void);
static NODE *func__25_11;
static void entry__25_11(void);
static FRAME_INFO frame__25_11 = {1, {"name"}};
static NODE *func__26_1_resolved_name;
static void entry__26_1_resolved_name(void);
static FRAME_INFO frame__26_1_resolved_name = {2, {"attr", "name"}};
static void cont__26_2(void);
static void cont__26_3(void);
static void cont__26_4(void);
static NODE *func__26_5;
static void entry__26_5(void);
static FRAME_INFO frame__26_5 = {1, {"attr"}};
static void cont__26_6(void);
static NODE *func__26_7;
static void entry__26_7(void);
static FRAME_INFO frame__26_7 = {3, {"attr", "name", "resolved_namespace"}};
static void cont__26_8(void);
static NODE *func__26_9;
static void entry__26_9(void);
static FRAME_INFO frame__26_9 = {3, {"namespace", "name", "resolved_namespace"}};
static void cont__26_10(void);
static NODE *func__26_11;
static void entry__26_11(void);
static FRAME_INFO frame__26_11 = {3, {"resolved_namespace", "name", "namespace"}};
static void cont__26_12(void);
static NODE *func__26_13;
static void entry__26_13(void);
static FRAME_INFO frame__26_13 = {1, {"name"}};
static NODE *string__26_14;
static NODE *string__26_15;
static void cont__26_16(void);
static void cont__26_17(void);
static void cont__26_18(void);
static void cont__26_19(void);
static NODE *func__26_20;
static void entry__26_20(void);
static FRAME_INFO frame__26_20 = {1, {"name"}};
static NODE *string__26_21;
static void cont__26_22(void);
static void cont__26_23(void);
static NODE *string__26_24;
static void cont__26_25(void);
static NODE *func__27_1_add_derived_type;
static void entry__27_1_add_derived_type(void);
static FRAME_INFO frame__27_1_add_derived_type = {4, {"base", "name", "ibase", "definition"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static void cont__27_5(void);
static void cont__27_6(void);
static NODE *func__27_7;
static void entry__27_7(void);
static FRAME_INFO frame__27_7 = {3, {"definition", "name", "ibase"}};
static void cont__27_8(void);
static void cont__27_9(void);
static void cont__27_10(void);
static void cont__27_11(void);
static NODE *func__27_12;
static void entry__27_12(void);
static FRAME_INFO frame__27_12 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__27_13(void);
static void cont__27_14(void);
static NODE *func__27_15;
static void entry__27_15(void);
static FRAME_INFO frame__27_15 = {2, {"base_of_base", "ibase"}};
static void cont__27_16(void);
static void cont__27_17(void);
static NODE *func__28_1_mangled;
static void entry__28_1_mangled(void);
static FRAME_INFO frame__28_1_mangled = {1, {"name"}};
static void cont__28_2(void);
static NODE *string__28_3;
static void cont__28_4(void);
static void cont__28_5(void);
static NODE *func__29_1_ordered_name;
static void entry__29_1_ordered_name(void);
static FRAME_INFO frame__29_1_ordered_name = {2, {"namespace", "name"}};
static void cont__29_2(void);
static void cont__29_3(void);
static void cont__29_4(void);
static NODE *func__30_1_link_bar;
static void entry__30_1_link_bar(void);
static FRAME_INFO frame__30_1_link_bar = {0, {}};
static NODE *func__30_2;
static void entry__30_2(void);
static FRAME_INFO frame__30_2 = {0, {}};
static NODE *string__30_3;
static NODE *string__30_4;
static void cont__30_5(void);
static NODE *string__30_6;
static void cont__30_7(void);
static NODE *string__30_8;
static void cont__30_9(void);
static NODE *string__30_10;
static void cont__30_11(void);
static NODE *string__30_12;
static void cont__30_13(void);
static void cont__30_14(void);
static NODE *string__30_15;
static void cont__30_16(void);
static NODE *string__30_17;
static void cont__30_18(void);
static void cont__30_19(void);
static NODE *string__30_20;
static void cont__30_21(void);
static NODE *string__30_22;
static void cont__30_23(void);
static void cont__30_24(void);
static NODE *string__30_25;
static void cont__30_26(void);
static NODE *string__30_27;
static NODE *func__33_1_to_paragraphs;
static void entry__33_1_to_paragraphs(void);
static FRAME_INFO frame__33_1_to_paragraphs = {4, {"lines", "paragraphs", "text", "pre_mode"}};
static NODE *func__33_2;
static void entry__33_2(void);
static FRAME_INFO frame__33_2 = {4, {"line", "pre_mode", "text", "paragraphs"}};
static NODE *func__33_3;
static void entry__33_3(void);
static FRAME_INFO frame__33_3 = {3, {"line", "text", "paragraphs"}};
static void cont__33_4(void);
static NODE *func__33_5;
static void entry__33_5(void);
static FRAME_INFO frame__33_5 = {3, {"text", "paragraphs", "line"}};
static void cont__33_6(void);
static void cont__33_7(void);
static NODE *func__33_8;
static void entry__33_8(void);
static FRAME_INFO frame__33_8 = {2, {"text", "line"}};
static void cont__33_9(void);
static NODE *func__33_10;
static void entry__33_10(void);
static FRAME_INFO frame__33_10 = {4, {"line", "text", "paragraphs", "pre_mode"}};
static void cont__33_11(void);
static NODE *func__33_12;
static void entry__33_12(void);
static FRAME_INFO frame__33_12 = {2, {"text", "paragraphs"}};
static void cont__33_13(void);
static void cont__33_14(void);
static NODE *func__33_15;
static void entry__33_15(void);
static FRAME_INFO frame__33_15 = {2, {"paragraphs", "text"}};
static void cont__33_16(void);
static NODE *func__33_17;
static void entry__33_17(void);
static FRAME_INFO frame__33_17 = {3, {"text", "line", "pre_mode"}};
static void cont__33_18(void);
static NODE *func__33_19;
static void entry__33_19(void);
static FRAME_INFO frame__33_19 = {2, {"line", "pre_mode"}};
static void cont__33_20(void);
static NODE *func__33_21;
static void entry__33_21(void);
static FRAME_INFO frame__33_21 = {1, {"pre_mode"}};
static NODE *func__33_22;
static void entry__33_22(void);
static FRAME_INFO frame__33_22 = {1, {"text"}};
static void cont__33_23(void);
static void cont__33_24(void);
static void cont__33_25(void);
static void cont__33_26(void);
static void cont__33_27(void);
static void cont__33_28(void);
static void cont__33_29(void);
static NODE *func__33_30;
static void entry__33_30(void);
static FRAME_INFO frame__33_30 = {2, {"paragraphs", "text"}};
static void cont__33_31(void);
static void cont__33_32(void);
static NODE *func__34_1_resolve_reference;
static void entry__34_1_resolve_reference(void);
static FRAME_INFO frame__34_1_resolve_reference = {1, {"reference"}};
static void cont__34_2(void);
static NODE *func__34_3;
static void entry__34_3(void);
static FRAME_INFO frame__34_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__34_4(void);
static void cont__34_5(void);
static void cont__34_6(void);
static NODE *func__34_7;
static void entry__34_7(void);
static FRAME_INFO frame__34_7 = {1, {"type_name"}};
static NODE *string__34_8;
static void cont__34_9(void);
static void cont__34_10(void);
static void cont__34_11(void);
static NODE *func__34_12;
static void entry__34_12(void);
static FRAME_INFO frame__34_12 = {1, {"method_name"}};
static NODE *string__34_13;
static void cont__34_14(void);
static void cont__34_15(void);
static void cont__34_16(void);
static NODE *func__34_17;
static void entry__34_17(void);
static FRAME_INFO frame__34_17 = {1, {"reference"}};
static void cont__34_18(void);
static NODE *func__34_19;
static void entry__34_19(void);
static FRAME_INFO frame__34_19 = {1, {"reference"}};
static void cont__34_20(void);
static void cont__34_21(void);
static NODE *func__35_1_add_links;
static void entry__35_1_add_links(void);
static FRAME_INFO frame__35_1_add_links = {1, {"paragraph"}};
static void cont__35_2(void);
static void cont__35_3(void);
static void cont__35_4(void);
static NODE *func__35_5;
static void entry__35_5(void);
static FRAME_INFO frame__35_5 = {1, {"reference"}};
static void cont__35_6(void);
static void cont__35_7(void);
static void cont__35_8(void);
static void cont__35_9(void);
static NODE *string__35_10;
static NODE *string__35_11;
static NODE *string__35_12;
static void cont__35_13(void);
static void cont__35_14(void);
static void cont__35_15(void);
static NODE *func__36_1_create_info_page;
static void entry__36_1_create_info_page(void);
static FRAME_INFO frame__36_1_create_info_page = {3, {"function_name", "info", "resolve_and_check_reference"}};
static NODE *func__36_2_resolve_and_check_reference;
static void entry__36_2_resolve_and_check_reference(void);
static FRAME_INFO frame__36_2_resolve_and_check_reference = {3, {"reference", "function_name", "info"}};
static void cont__36_3(void);
static void cont__36_4(void);
static void cont__36_5(void);
static NODE *func__36_6;
static void entry__36_6(void);
static FRAME_INFO frame__36_6 = {3, {"function_name", "info", "reference"}};
static void cont__36_7(void);
static NODE *string__36_8;
static NODE *string__36_9;
static NODE *string__36_10;
static NODE *string__36_11;
static void cont__36_12(void);
static void cont__36_13(void);
static void cont__36_14(void);
static NODE *func__36_15;
static void entry__36_15(void);
static FRAME_INFO frame__36_15 = {3, {"function_name", "info", "resolve_and_check_reference"}};
static void cont__36_16(void);
static NODE *string__36_17;
static NODE *string__36_18;
static void cont__36_19(void);
static NODE *func__36_20;
static void entry__36_20(void);
static FRAME_INFO frame__36_20 = {13, {"function_name", "info", "resolve_and_check_reference", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "topic_list", "examples", "remark_lines", "function_basename"}};
static void cont__36_21(void);
static void cont__36_22(void);
static NODE *func__36_23;
static void entry__36_23(void);
static FRAME_INFO frame__36_23 = {3, {"function_name", "type", "method"}};
static void cont__36_24(void);
static void cont__36_25(void);
static void cont__36_26(void);
static void cont__36_27(void);
static NODE *string__36_28;
static void cont__36_29(void);
static NODE *func__36_30;
static void entry__36_30(void);
static FRAME_INFO frame__36_30 = {2, {"function_name", "info"}};
static void cont__36_31(void);
static void cont__36_32(void);
static NODE *func__36_33;
static void entry__36_33(void);
static FRAME_INFO frame__36_33 = {0, {}};
static NODE *string__36_34;
static NODE *func__36_35;
static void entry__36_35(void);
static FRAME_INFO frame__36_35 = {0, {}};
static NODE *string__36_36;
static NODE *func__36_37;
static void entry__36_37(void);
static FRAME_INFO frame__36_37 = {0, {}};
static NODE *string__36_38;
static void cont__36_39(void);
static void cont__36_40(void);
static void cont__36_41(void);
static NODE *func__36_42;
static void entry__36_42(void);
static FRAME_INFO frame__36_42 = {1, {"remark_lines"}};
static void cont__36_43(void);
static void cont__36_44(void);
static NODE *func__36_45;
static void entry__36_45(void);
static FRAME_INFO frame__36_45 = {2, {"function_name", "info"}};
static void cont__36_46(void);
static NODE *func__36_47;
static void entry__36_47(void);
static FRAME_INFO frame__36_47 = {2, {"function_name", "info"}};
static void cont__36_48(void);
static NODE *string__36_49;
static NODE *string__36_50;
static NODE *string__36_51;
static void cont__36_52(void);
static void cont__36_53(void);
static void cont__36_54(void);
static NODE *func__36_55;
static void entry__36_55(void);
static FRAME_INFO frame__36_55 = {12, {"remark_lines", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions", "paragraphs"}};
static void cont__36_56(void);
static NODE *func__36_57;
static void entry__36_57(void);
static FRAME_INFO frame__36_57 = {11, {"paragraph", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions"}};
static NODE *func__36_58;
static void entry__36_58(void);
static FRAME_INFO frame__36_58 = {2, {"paragraph", "parameters"}};
static void cont__36_59(void);
static NODE *string__36_60;
static void cont__36_61(void);
static void cont__36_62(void);
static NODE *func__36_63;
static void entry__36_63(void);
static FRAME_INFO frame__36_63 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__36_64(void);
static NODE *func__36_65;
static void entry__36_65(void);
static FRAME_INFO frame__36_65 = {1, {"parameter"}};
static void cont__36_66(void);
static NODE *func__36_67;
static void entry__36_67(void);
static FRAME_INFO frame__36_67 = {1, {"parameter"}};
static void cont__36_68(void);
static void cont__36_69(void);
static NODE *string__36_70;
static void cont__36_71(void);
static NODE *func__36_72;
static void entry__36_72(void);
static FRAME_INFO frame__36_72 = {1, {"parameter"}};
static void cont__36_73(void);
static NODE *func__36_74;
static void entry__36_74(void);
static FRAME_INFO frame__36_74 = {1, {"parameter"}};
static void cont__36_75(void);
static void cont__36_76(void);
static NODE *string__36_77;
static void cont__36_78(void);
static NODE *func__36_79;
static void entry__36_79(void);
static FRAME_INFO frame__36_79 = {1, {"parameter"}};
static void cont__36_80(void);
static NODE *func__36_81;
static void entry__36_81(void);
static FRAME_INFO frame__36_81 = {1, {"parameter"}};
static void cont__36_82(void);
static void cont__36_83(void);
static void cont__36_84(void);
static void cont__36_85(void);
static NODE *string__36_86;
static NODE *string__36_87;
static void cont__36_88(void);
static void cont__36_89(void);
static void cont__36_90(void);
static void cont__36_91(void);
static void cont__36_92(void);
static void cont__36_93(void);
static NODE *func__36_94;
static void entry__36_94(void);
static FRAME_INFO frame__36_94 = {2, {"paragraph", "return_values"}};
static void cont__36_95(void);
static NODE *string__36_96;
static void cont__36_97(void);
static void cont__36_98(void);
static NODE *func__36_99;
static void entry__36_99(void);
static FRAME_INFO frame__36_99 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__36_100(void);
static NODE *func__36_101;
static void entry__36_101(void);
static FRAME_INFO frame__36_101 = {1, {"return_value"}};
static void cont__36_102(void);
static NODE *func__36_103;
static void entry__36_103(void);
static FRAME_INFO frame__36_103 = {1, {"return_value"}};
static void cont__36_104(void);
static void cont__36_105(void);
static void cont__36_106(void);
static NODE *func__36_107;
static void entry__36_107(void);
static FRAME_INFO frame__36_107 = {1, {"return_value"}};
static void cont__36_108(void);
static NODE *func__36_109;
static void entry__36_109(void);
static FRAME_INFO frame__36_109 = {1, {"return_value"}};
static void cont__36_110(void);
static void cont__36_111(void);
static void cont__36_112(void);
static void cont__36_113(void);
static void cont__36_114(void);
static void cont__36_115(void);
static void cont__36_116(void);
static void cont__36_117(void);
static NODE *func__36_118;
static void entry__36_118(void);
static FRAME_INFO frame__36_118 = {2, {"paragraph", "references"}};
static NODE *string__36_119;
static void cont__36_120(void);
static NODE *func__36_121;
static void entry__36_121(void);
static FRAME_INFO frame__36_121 = {2, {"paragraph", "references"}};
static void cont__36_122(void);
static void cont__36_123(void);
static NODE *func__36_124;
static void entry__36_124(void);
static FRAME_INFO frame__36_124 = {2, {"reference", "references"}};
static void cont__36_125(void);
static void cont__36_126(void);
static NODE *func__36_127;
static void entry__36_127(void);
static FRAME_INFO frame__36_127 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__36_128(void);
static NODE *func__36_129;
static void entry__36_129(void);
static FRAME_INFO frame__36_129 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__36_130(void);
static void cont__36_131(void);
static NODE *func__36_132;
static void entry__36_132(void);
static FRAME_INFO frame__36_132 = {4, {"topic", "topic_list", "function_name", "topic_contents"}};
static void cont__36_133(void);
static void cont__36_134(void);
static void cont__36_135(void);
static void cont__36_136(void);
static void cont__36_137(void);
static void cont__36_138(void);
static NODE *func__36_139;
static void entry__36_139(void);
static FRAME_INFO frame__36_139 = {2, {"paragraph", "examples"}};
static void cont__36_140(void);
static NODE *func__36_141;
static void entry__36_141(void);
static FRAME_INFO frame__36_141 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__36_142(void);
static void cont__36_143(void);
static void cont__36_144(void);
static void cont__36_145(void);
static void cont__36_146(void);
static void cont__36_147(void);
static NODE *func__36_148;
static void entry__36_148(void);
static FRAME_INFO frame__36_148 = {2, {"paragraph", "technical_details"}};
static NODE *string__36_149;
static void cont__36_150(void);
static NODE *func__36_151;
static void entry__36_151(void);
static FRAME_INFO frame__36_151 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__36_152(void);
static void cont__36_153(void);
static void cont__36_154(void);
static NODE *func__36_155;
static void entry__36_155(void);
static FRAME_INFO frame__36_155 = {1, {"technical_details"}};
static NODE *func__36_156;
static void entry__36_156(void);
static FRAME_INFO frame__36_156 = {2, {"technical_details", "detail"}};
static void cont__36_157(void);
static NODE *func__36_158;
static void entry__36_158(void);
static FRAME_INFO frame__36_158 = {5, {"paragraph", "resolve_and_check_reference", "short_description", "technical_details", "descriptions"}};
static void cont__36_159(void);
static void cont__36_160(void);
static void cont__36_161(void);
static NODE *func__36_162;
static void entry__36_162(void);
static FRAME_INFO frame__36_162 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__36_163(void);
static void cont__36_164(void);
static void cont__36_165(void);
static void cont__36_166(void);
static void cont__36_167(void);
static void cont__36_168(void);
static void cont__36_169(void);
static void cont__36_170(void);
static NODE *func__36_171;
static void entry__36_171(void);
static FRAME_INFO frame__36_171 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__36_172(void);
static NODE *func__36_173;
static void entry__36_173(void);
static FRAME_INFO frame__36_173 = {2, {"technical_details", "paragraph"}};
static void cont__36_174(void);
static NODE *func__36_175;
static void entry__36_175(void);
static FRAME_INFO frame__36_175 = {2, {"descriptions", "paragraph"}};
static void cont__36_176(void);
static NODE *func__36_177;
static void entry__36_177(void);
static FRAME_INFO frame__36_177 = {2, {"short_description", "paragraph"}};
static void cont__36_178(void);
static void cont__36_179(void);
static void cont__36_180(void);
static NODE *func__36_181;
static void entry__36_181(void);
static FRAME_INFO frame__36_181 = {2, {"info", "parameters"}};
static void cont__36_182(void);
static NODE *func__36_183;
static void entry__36_183(void);
static FRAME_INFO frame__36_183 = {2, {"parameter", "parameters"}};
static void cont__36_184(void);
static void cont__36_185(void);
static NODE *func__36_186;
static void entry__36_186(void);
static FRAME_INFO frame__36_186 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__36_187(void);
static void cont__36_188(void);
static void cont__36_189(void);
static NODE *func__36_190;
static void entry__36_190(void);
static FRAME_INFO frame__36_190 = {2, {"parameter", "name"}};
static void cont__36_191(void);
static NODE *func__36_192;
static void entry__36_192(void);
static FRAME_INFO frame__36_192 = {2, {"parameter", "name"}};
static void cont__36_193(void);
static void cont__36_194(void);
static NODE *func__36_195;
static void entry__36_195(void);
static FRAME_INFO frame__36_195 = {2, {"name", "parameter"}};
static void cont__36_196(void);
static void cont__36_197(void);
static void cont__36_198(void);
static NODE *func__36_199;
static void entry__36_199(void);
static FRAME_INFO frame__36_199 = {1, {"name"}};
static void cont__36_200(void);
static NODE *func__36_201;
static void entry__36_201(void);
static FRAME_INFO frame__36_201 = {2, {"parameter", "name"}};
static void cont__36_202(void);
static NODE *func__36_203;
static void entry__36_203(void);
static FRAME_INFO frame__36_203 = {1, {"name"}};
static void cont__36_204(void);
static void cont__36_205(void);
static void cont__36_206(void);
static void cont__36_207(void);
static void cont__36_208(void);
static NODE *func__36_209;
static void entry__36_209(void);
static FRAME_INFO frame__36_209 = {1, {"parameter"}};
static void cont__36_210(void);
static void cont__36_211(void);
static void cont__36_212(void);
static NODE *func__36_213;
static void entry__36_213(void);
static FRAME_INFO frame__36_213 = {0, {}};
static void cont__36_214(void);
static void cont__36_215(void);
static void cont__36_216(void);
static NODE *func__36_217;
static void entry__36_217(void);
static FRAME_INFO frame__36_217 = {0, {}};
static void cont__36_218(void);
static void cont__36_219(void);
static NODE *func__36_220;
static void entry__36_220(void);
static FRAME_INFO frame__36_220 = {1, {"short_description"}};
static void cont__36_221(void);
static void cont__36_222(void);
static NODE *func__36_223;
static void entry__36_223(void);
static FRAME_INFO frame__36_223 = {1, {"parameters"}};
static NODE *string__36_224;
static void cont__36_225(void);
static NODE *func__36_226;
static void entry__36_226(void);
static FRAME_INFO frame__36_226 = {1, {"parameters"}};
static NODE *func__36_227;
static void entry__36_227(void);
static FRAME_INFO frame__36_227 = {1, {"parameter"}};
static void cont__36_228(void);
static void cont__36_229(void);
static NODE *func__36_230;
static void entry__36_230(void);
static FRAME_INFO frame__36_230 = {1, {"parameter"}};
static void cont__36_231(void);
static void cont__36_232(void);
static void cont__36_233(void);
static NODE *func__36_234;
static void entry__36_234(void);
static FRAME_INFO frame__36_234 = {1, {"return_values"}};
static void cont__36_235(void);
static NODE *func__36_236;
static void entry__36_236(void);
static FRAME_INFO frame__36_236 = {1, {"return_values"}};
static NODE *func__36_237;
static void entry__36_237(void);
static FRAME_INFO frame__36_237 = {1, {"return_value"}};
static void cont__36_238(void);
static void cont__36_239(void);
static NODE *func__36_240;
static void entry__36_240(void);
static FRAME_INFO frame__36_240 = {1, {"return_value"}};
static void cont__36_241(void);
static void cont__36_242(void);
static void cont__36_243(void);
static NODE *func__36_244;
static void entry__36_244(void);
static FRAME_INFO frame__36_244 = {1, {"descriptions"}};
static NODE *string__36_245;
static void cont__36_246(void);
static NODE *func__36_247;
static void entry__36_247(void);
static FRAME_INFO frame__36_247 = {1, {"description"}};
static void cont__36_248(void);
static void cont__36_249(void);
static NODE *func__36_250;
static void entry__36_250(void);
static FRAME_INFO frame__36_250 = {1, {"technical_details"}};
static NODE *string__36_251;
static void cont__36_252(void);
static NODE *func__36_253;
static void entry__36_253(void);
static FRAME_INFO frame__36_253 = {1, {"detail"}};
static void cont__36_254(void);
static void cont__36_255(void);
static NODE *func__36_256;
static void entry__36_256(void);
static FRAME_INFO frame__36_256 = {2, {"references", "resolve_and_check_reference"}};
static NODE *string__36_257;
static void cont__36_258(void);
static NODE *func__36_259;
static void entry__36_259(void);
static FRAME_INFO frame__36_259 = {2, {"references", "resolve_and_check_reference"}};
static NODE *func__36_260;
static void entry__36_260(void);
static FRAME_INFO frame__36_260 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__36_261(void);
static NODE *func__36_262;
static void entry__36_262(void);
static FRAME_INFO frame__36_262 = {1, {"reference"}};
static NODE *func__36_263;
static void entry__36_263(void);
static FRAME_INFO frame__36_263 = {1, {"reference"}};
static void cont__36_264(void);
static void cont__36_265(void);
static void cont__36_266(void);
static void cont__36_267(void);
static NODE *string__36_268;
static void cont__36_269(void);
static void cont__36_270(void);
static void cont__36_271(void);
static void cont__36_272(void);
static void cont__36_273(void);
static NODE *func__36_274;
static void entry__36_274(void);
static FRAME_INFO frame__36_274 = {2, {"info", "function_name"}};
static NODE *string__36_275;
static void cont__36_276(void);
static NODE *func__36_277;
static void entry__36_277(void);
static FRAME_INFO frame__36_277 = {2, {"info", "function_name"}};
static void cont__36_278(void);
static NODE *func__36_279;
static void entry__36_279(void);
static FRAME_INFO frame__36_279 = {3, {"name", "function_name", "method"}};
static void cont__36_280(void);
static NODE *func__36_281;
static void entry__36_281(void);
static FRAME_INFO frame__36_281 = {2, {"name", "method"}};
static NODE *func__36_282;
static void entry__36_282(void);
static FRAME_INFO frame__36_282 = {1, {"name"}};
static void cont__36_283(void);
static void cont__36_284(void);
static void cont__36_285(void);
static void cont__36_286(void);
static NODE *string__36_287;
static void cont__36_288(void);
static NODE *func__36_289;
static void entry__36_289(void);
static FRAME_INFO frame__36_289 = {1, {"method"}};
static void cont__36_290(void);
static void cont__36_291(void);
static void cont__36_292(void);
static void cont__36_293(void);
static void cont__36_294(void);
static NODE *func__36_295;
static void entry__36_295(void);
static FRAME_INFO frame__36_295 = {2, {"function_name", "polymorphic_function_name"}};
static void cont__36_296(void);
static NODE *string__36_297;
static void cont__36_298(void);
static void cont__36_299(void);
static void cont__36_300(void);
static void cont__36_301(void);
static void cont__36_302(void);
static void cont__36_303(void);
static void cont__36_304(void);
static NODE *func__36_305;
static void entry__36_305(void);
static FRAME_INFO frame__36_305 = {2, {"info", "function_name"}};
static NODE *string__36_306;
static void cont__36_307(void);
static NODE *func__36_308;
static void entry__36_308(void);
static FRAME_INFO frame__36_308 = {2, {"info", "function_name"}};
static void cont__36_309(void);
static NODE *func__36_310;
static void entry__36_310(void);
static FRAME_INFO frame__36_310 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__36_311;
static void entry__36_311(void);
static FRAME_INFO frame__36_311 = {2, {"method_name", "function_name"}};
static NODE *func__36_312;
static void entry__36_312(void);
static FRAME_INFO frame__36_312 = {1, {"method_name"}};
static void cont__36_313(void);
static void cont__36_314(void);
static void cont__36_315(void);
static void cont__36_316(void);
static void cont__36_317(void);
static NODE *func__36_318;
static void entry__36_318(void);
static FRAME_INFO frame__36_318 = {2, {"function_name", "method_name"}};
static void cont__36_319(void);
static void cont__36_320(void);
static void cont__36_321(void);
static void cont__36_322(void);
static void cont__36_323(void);
static void cont__36_324(void);
static void cont__36_325(void);
static void cont__36_326(void);
static NODE *func__36_327;
static void entry__36_327(void);
static FRAME_INFO frame__36_327 = {1, {"topic_list"}};
static NODE *string__36_328;
static void cont__36_329(void);
static NODE *func__36_330;
static void entry__36_330(void);
static FRAME_INFO frame__36_330 = {1, {"topic_list"}};
static NODE *func__36_331;
static void entry__36_331(void);
static FRAME_INFO frame__36_331 = {2, {"topic", "filename"}};
static void cont__36_332(void);
static NODE *string__36_333;
static void cont__36_334(void);
static void cont__36_335(void);
static void cont__36_336(void);
static NODE *func__36_337;
static void entry__36_337(void);
static FRAME_INFO frame__36_337 = {2, {"filename", "topic"}};
static NODE *func__36_338;
static void entry__36_338(void);
static FRAME_INFO frame__36_338 = {2, {"filename", "topic"}};
static void cont__36_339(void);
static void cont__36_340(void);
static NODE *func__36_341;
static void entry__36_341(void);
static FRAME_INFO frame__36_341 = {4, {"example", "function_basename", "title", "text"}};
static void cont__36_342(void);
static void cont__36_343(void);
static void cont__36_344(void);
static void cont__36_345(void);
static void cont__36_346(void);
static NODE *string__36_347;
static void cont__36_348(void);
static NODE *func__36_349;
static void entry__36_349(void);
static FRAME_INFO frame__36_349 = {2, {"text", "function_basename"}};
static void cont__36_350(void);
static void cont__36_351(void);
static void cont__36_352(void);
static void cont__36_353(void);
static NODE *func__36_354;
static void entry__36_354(void);
static FRAME_INFO frame__36_354 = {1, {"string_literal"}};
static void cont__36_355(void);
static NODE *string__36_356;
static void cont__36_357(void);
static void cont__36_358(void);
static void cont__36_359(void);
static void cont__36_360(void);
static NODE *string__36_361;
static void cont__36_362(void);
static void cont__36_363(void);
static void cont__36_364(void);
static NODE *string__36_365;
static NODE *string__36_366;
static void cont__36_367(void);
static NODE *func__37_1_get_short_description;
static void entry__37_1_get_short_description(void);
static FRAME_INFO frame__37_1_get_short_description = {4, {"name", "info", "remark_lines", "short_description"}};
static void cont__37_2(void);
static void cont__37_3(void);
static NODE *func__37_4;
static void entry__37_4(void);
static FRAME_INFO frame__37_4 = {1, {"remark_lines"}};
static void cont__37_5(void);
static void cont__37_6(void);
static void cont__37_7(void);
static NODE *func__37_8;
static void entry__37_8(void);
static FRAME_INFO frame__37_8 = {4, {"remark_lines", "short_description", "name", "info"}};
static NODE *func__37_9;
static void entry__37_9(void);
static FRAME_INFO frame__37_9 = {3, {"break", "remark_lines", "short_description"}};
static NODE *func__37_10;
static void entry__37_10(void);
static FRAME_INFO frame__37_10 = {3, {"line", "short_description", "break"}};
static void cont__37_11(void);
static NODE *func__37_12;
static void entry__37_12(void);
static FRAME_INFO frame__37_12 = {1, {"short_description"}};
static void cont__37_13(void);
static void cont__37_14(void);
static void cont__37_15(void);
static void cont__37_16(void);
static void cont__37_17(void);
static void cont__37_18(void);
static void cont__37_19(void);
static void cont__37_20(void);
static NODE *func__37_21;
static void entry__37_21(void);
static FRAME_INFO frame__37_21 = {1, {"short_description"}};
static void cont__37_22(void);
static void cont__37_23(void);
static void cont__37_24(void);
static NODE *func__37_25;
static void entry__37_25(void);
static FRAME_INFO frame__37_25 = {3, {"name", "info", "short_description"}};
static void cont__37_26(void);
static NODE *string__37_27;
static NODE *string__37_28;
static void cont__37_29(void);
static void cont__37_30(void);
static void cont__37_31(void);
static NODE *func__38_1_sim2c__extract_documentation;
static void entry__38_1_sim2c__extract_documentation(void);
static FRAME_INFO frame__38_1_sim2c__extract_documentation = {1, {"path"}};
static void cont__38_2(void);
static void cont__38_3(void);
static void cont__38_4(void);
static NODE *func__38_5;
static void entry__38_5(void);
static FRAME_INFO frame__38_5 = {3, {"iname", "info", "name"}};
static void cont__38_6(void);
static void cont__38_7(void);
static void cont__38_8(void);
static void cont__38_9(void);
static void cont__38_10(void);
static NODE *func__38_11;
static void entry__38_11(void);
static FRAME_INFO frame__38_11 = {5, {"info", "iname", "name", "base", "methods"}};
static void cont__38_12(void);
static void cont__38_13(void);
static NODE *func__38_14;
static void entry__38_14(void);
static FRAME_INFO frame__38_14 = {2, {"base", "iname"}};
static void cont__38_15(void);
static void cont__38_16(void);
static NODE *func__38_17;
static void entry__38_17(void);
static FRAME_INFO frame__38_17 = {6, {"method_name", "method_info", "name", "methods", "sd_name", "oname"}};
static void cont__38_18(void);
static NODE *func__38_19;
static void entry__38_19(void);
static FRAME_INFO frame__38_19 = {2, {"method_name", "method_info"}};
static void cont__38_20(void);
static void cont__38_21(void);
static void cont__38_22(void);
static NODE *string__38_23;
static void cont__38_24(void);
static void cont__38_25(void);
static void cont__38_26(void);
static void cont__38_27(void);
static void cont__38_28(void);
static void cont__38_29(void);
static void cont__38_30(void);
static void cont__38_31(void);
static void cont__38_32(void);
static void cont__38_33(void);
static void cont__38_34(void);
static void cont__38_35(void);
static void cont__38_36(void);
static void cont__38_37(void);
static void cont__38_38(void);
static NODE *string__38_39;
static NODE *func__38_40;
static void entry__38_40(void);
static FRAME_INFO frame__38_40 = {1, {"print_type_info"}};
static NODE *func__38_41_print_type_info;
static void entry__38_41_print_type_info(void);
static FRAME_INFO frame__38_41_print_type_info = {3, {"info", "indent", "print_type_info"}};
static NODE *func__38_42;
static void entry__38_42(void);
static FRAME_INFO frame__38_42 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__38_43(void);
static void cont__38_44(void);
static void cont__38_45(void);
static NODE *func__38_46;
static void entry__38_46(void);
static FRAME_INFO frame__38_46 = {2, {"indent", "qname"}};
static NODE *func__38_47;
static void entry__38_47(void);
static FRAME_INFO frame__38_47 = {2, {"indent", "qname"}};
static void cont__38_48(void);
static void cont__38_49(void);
static void cont__38_50(void);
static void cont__38_51(void);
static void cont__38_52(void);
static void cont__38_53(void);
static void cont__38_54(void);
static NODE *func__38_55;
static void entry__38_55(void);
static FRAME_INFO frame__38_55 = {1, {"remark_lines"}};
static void cont__38_56(void);
static void cont__38_57(void);
static void cont__38_58(void);
static NODE *func__38_59;
static void entry__38_59(void);
static FRAME_INFO frame__38_59 = {1, {"remark_lines"}};
static void cont__38_60(void);
static void cont__38_61(void);
static void cont__38_62(void);
static void cont__38_63(void);
static NODE *func__38_64;
static void entry__38_64(void);
static FRAME_INFO frame__38_64 = {3, {"name", "print_type_info", "indent"}};
static void cont__38_65(void);
static void cont__38_66(void);
static void cont__38_67(void);
static void cont__38_68(void);
static NODE *func__38_69;
static void entry__38_69(void);
static FRAME_INFO frame__38_69 = {1, {"print_type_info"}};
static NODE *func__38_70;
static void entry__38_70(void);
static FRAME_INFO frame__38_70 = {3, {"base", "info", "print_type_info"}};
static void cont__38_71(void);
static void cont__38_72(void);
static NODE *func__38_73;
static void entry__38_73(void);
static FRAME_INFO frame__38_73 = {1, {"info"}};
static void cont__38_74(void);
static void cont__38_75(void);
static void cont__38_76(void);
static NODE *func__38_77;
static void entry__38_77(void);
static FRAME_INFO frame__38_77 = {2, {"print_type_info", "info"}};
static void cont__38_78(void);
static NODE *string__38_79;
static NODE *func__38_80;
static void entry__38_80(void);
static FRAME_INFO frame__38_80 = {0, {}};
static void cont__38_81(void);
static NODE *string__38_82;
static NODE *string__38_83;
static void cont__38_84(void);
static void cont__38_85(void);
static NODE *func__38_86;
static void entry__38_86(void);
static FRAME_INFO frame__38_86 = {1, {"letter"}};
static NODE *string__38_87;
static void cont__38_88(void);
static void cont__38_89(void);
static void cont__38_90(void);
static NODE *func__38_91;
static void entry__38_91(void);
static FRAME_INFO frame__38_91 = {0, {}};
static NODE *string__38_92;
static void cont__38_93(void);
static void cont__38_94(void);
static NODE *func__38_95;
static void entry__38_95(void);
static FRAME_INFO frame__38_95 = {1, {"letter"}};
static NODE *func__38_96;
static void entry__38_96(void);
static FRAME_INFO frame__38_96 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__38_97(void);
static void cont__38_98(void);
static void cont__38_99(void);
static NODE *func__38_100;
static void entry__38_100(void);
static FRAME_INFO frame__38_100 = {2, {"letter", "iname"}};
static void cont__38_101(void);
static NODE *func__38_102;
static void entry__38_102(void);
static FRAME_INFO frame__38_102 = {1, {"letter"}};
static NODE *string__38_103;
static void cont__38_104(void);
static NODE *func__38_105;
static void entry__38_105(void);
static FRAME_INFO frame__38_105 = {1, {"letter"}};
static void cont__38_106(void);
static NODE *func__38_107;
static void entry__38_107(void);
static FRAME_INFO frame__38_107 = {1, {"letter"}};
static void cont__38_108(void);
static void cont__38_109(void);
static NODE *string__38_110;
static void cont__38_111(void);
static NODE *string__38_112;
static void cont__38_113(void);
static void cont__38_114(void);
static void cont__38_115(void);
static void cont__38_116(void);
static NODE *func__38_117;
static void entry__38_117(void);
static FRAME_INFO frame__38_117 = {1, {"remark_lines"}};
static void cont__38_118(void);
static void cont__38_119(void);
static void cont__38_120(void);
static NODE *func__38_121;
static void entry__38_121(void);
static FRAME_INFO frame__38_121 = {2, {"remark", "remark_lines"}};
static void cont__38_122(void);
static void cont__38_123(void);
static void cont__38_124(void);
static void cont__38_125(void);
static NODE *func__38_126;
static void entry__38_126(void);
static FRAME_INFO frame__38_126 = {0, {}};
static NODE *string__38_127;
static NODE *func__38_128;
static void entry__38_128(void);
static FRAME_INFO frame__38_128 = {0, {}};
static NODE *string__38_129;
static NODE *func__38_130;
static void entry__38_130(void);
static FRAME_INFO frame__38_130 = {0, {}};
static NODE *string__38_131;
static NODE *func__38_132;
static void entry__38_132(void);
static FRAME_INFO frame__38_132 = {0, {}};
static NODE *string__38_133;
static NODE *func__38_134;
static void entry__38_134(void);
static FRAME_INFO frame__38_134 = {0, {}};
static NODE *string__38_135;
static NODE *func__38_136;
static void entry__38_136(void);
static FRAME_INFO frame__38_136 = {0, {}};
static NODE *string__38_137;
static NODE *func__38_138;
static void entry__38_138(void);
static FRAME_INFO frame__38_138 = {0, {}};
static NODE *string__38_139;
static NODE *func__38_140;
static void entry__38_140(void);
static FRAME_INFO frame__38_140 = {0, {}};
static NODE *string__38_141;
static NODE *func__38_142;
static void entry__38_142(void);
static FRAME_INFO frame__38_142 = {0, {}};
static NODE *string__38_143;
static NODE *func__38_144;
static void entry__38_144(void);
static FRAME_INFO frame__38_144 = {0, {}};
static void cont__38_145(void);
static void cont__38_146(void);
static NODE *func__38_147;
static void entry__38_147(void);
static FRAME_INFO frame__38_147 = {2, {"remark", "kind_info"}};
static void cont__38_148(void);
static NODE *func__38_149;
static void entry__38_149(void);
static FRAME_INFO frame__38_149 = {2, {"remark", "kind_info"}};
static NODE *string__38_150;
static void cont__38_151(void);
static NODE *func__38_152;
static void entry__38_152(void);
static FRAME_INFO frame__38_152 = {2, {"remark", "kind_info"}};
static void cont__38_153(void);
static void cont__38_154(void);
static NODE *func__38_155;
static void entry__38_155(void);
static FRAME_INFO frame__38_155 = {1, {"name"}};
static void cont__38_156(void);
static void cont__38_157(void);
static NODE *func__38_158;
static void entry__38_158(void);
static FRAME_INFO frame__38_158 = {2, {"name", "remark"}};
static NODE *func__38_159;
static void entry__38_159(void);
static FRAME_INFO frame__38_159 = {2, {"name", "remark"}};
static NODE *string__38_160;
static NODE *string__38_161;
static void cont__38_162(void);
static void cont__38_163(void);
static void cont__38_164(void);
static NODE *func__38_165;
static void entry__38_165(void);
static FRAME_INFO frame__38_165 = {1, {"name"}};
static void cont__38_166(void);
static void cont__38_167(void);
static void cont__38_168(void);
static void cont__38_169(void);
static void cont__38_170(void);
static NODE *string__38_171;
static void cont__38_172(void);
static void cont__38_173(void);
static NODE *func__38_174;
static void entry__38_174(void);
static FRAME_INFO frame__38_174 = {3, {"iname", "info", "name"}};
static void cont__38_175(void);
static void cont__38_176(void);
static void cont__38_177(void);
static NODE *func__38_178;
static void entry__38_178(void);
static FRAME_INFO frame__38_178 = {2, {"info", "name"}};
static void cont__38_179(void);
static NODE *func__38_180;
static void entry__38_180(void);
static FRAME_INFO frame__38_180 = {3, {"method_name", "method_info", "name"}};
static void cont__38_181(void);
static void cont__38_182(void);
static NODE *string__38_183;
static NODE *func__38_184;
static void entry__38_184(void);
static FRAME_INFO frame__38_184 = {0, {}};
static void cont__38_185(void);
static void cont__38_186(void);
static void cont__38_187(void);
static NODE *func__38_188;
static void entry__38_188(void);
static FRAME_INFO frame__38_188 = {0, {}};
static NODE *func__38_189;
static void entry__38_189(void);
static FRAME_INFO frame__38_189 = {3, {"topic", "references", "filename"}};
static void cont__38_190(void);
static void cont__38_191(void);
static void cont__38_192(void);
static void cont__38_193(void);
static NODE *func__38_194;
static void entry__38_194(void);
static FRAME_INFO frame__38_194 = {2, {"filename", "topic"}};
static NODE *func__38_195;
static void entry__38_195(void);
static FRAME_INFO frame__38_195 = {2, {"filename", "topic"}};
static void cont__38_196(void);
static void cont__38_197(void);
static NODE *func__38_198;
static void entry__38_198(void);
static FRAME_INFO frame__38_198 = {3, {"topic", "references", "filename"}};
static void cont__38_199(void);
static void cont__38_200(void);
static void cont__38_201(void);
static void cont__38_202(void);
static NODE *func__38_203;
static void entry__38_203(void);
static FRAME_INFO frame__38_203 = {2, {"topic", "references"}};
static void cont__38_204(void);
static void cont__38_205(void);
static void cont__38_206(void);
static NODE *func__38_207;
static void entry__38_207(void);
static FRAME_INFO frame__38_207 = {1, {"references"}};
static NODE *func__38_208;
static void entry__38_208(void);
static FRAME_INFO frame__38_208 = {1, {"reference"}};
static NODE *func__38_209;
static void entry__38_209(void);
static FRAME_INFO frame__38_209 = {1, {"reference"}};
static NODE *func__38_210;
static void entry__38_210(void);
static FRAME_INFO frame__38_210 = {1, {"reference"}};
static void cont__38_211(void);
static void cont__38_212(void);
static void cont__38_213(void);
static void cont__38_214(void);
static void cont__38_215(void);
static void cont__38_216(void);
static void cont__38_217(void);
static NODE *string__38_218;
static NODE *func__38_219;
static void entry__38_219(void);
static FRAME_INFO frame__38_219 = {0, {}};
static NODE *string__38_220;
static void cont__38_221(void);
static NODE *func__38_222;
static void entry__38_222(void);
static FRAME_INFO frame__38_222 = {0, {}};
static void cont__38_223(void);
static void cont__38_224(void);
static NODE *func__38_225;
static void entry__38_225(void);
static FRAME_INFO frame__38_225 = {0, {}};
static void cont__38_226(void);
static void cont__38_227(void);
static NODE *func__38_228;
static void entry__38_228(void);
static FRAME_INFO frame__38_228 = {0, {}};
static void cont__38_229(void);
static void cont__38_230(void);
static NODE *func__38_231;
static void entry__38_231(void);
static FRAME_INFO frame__38_231 = {0, {}};
static void cont__38_232(void);
static void cont__38_233(void);
static NODE *func__38_234;
static void entry__38_234(void);
static FRAME_INFO frame__38_234 = {13, {"total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_methods", "total_inline_c_methods", "total_inline_c_types", "total_inline_c_objects", "total_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "other", "total_definitions"}};
static NODE *func__38_235;
static void entry__38_235(void);
static FRAME_INFO frame__38_235 = {14, {"iname", "info", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_inline_c_functions", "total_inline_c_types", "total_inline_c_objects", "total_unique_items", "total_constants", "other", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__38_236(void);
static NODE *func__38_237;
static void entry__38_237(void);
static FRAME_INFO frame__38_237 = {1, {"total_functions"}};
static void cont__38_238(void);
static NODE *func__38_239;
static void entry__38_239(void);
static FRAME_INFO frame__38_239 = {1, {"total_polymorphic_functions"}};
static void cont__38_240(void);
static NODE *func__38_241;
static void entry__38_241(void);
static FRAME_INFO frame__38_241 = {1, {"total_polymorphic_attributes"}};
static void cont__38_242(void);
static NODE *func__38_243;
static void entry__38_243(void);
static FRAME_INFO frame__38_243 = {1, {"total_inline_c_functions"}};
static void cont__38_244(void);
static NODE *func__38_245;
static void entry__38_245(void);
static FRAME_INFO frame__38_245 = {1, {"total_inline_c_types"}};
static void cont__38_246(void);
static NODE *func__38_247;
static void entry__38_247(void);
static FRAME_INFO frame__38_247 = {1, {"total_inline_c_objects"}};
static void cont__38_248(void);
static NODE *func__38_249;
static void entry__38_249(void);
static FRAME_INFO frame__38_249 = {1, {"total_unique_items"}};
static void cont__38_250(void);
static NODE *func__38_251;
static void entry__38_251(void);
static FRAME_INFO frame__38_251 = {1, {"total_constants"}};
static void cont__38_252(void);
static NODE *func__38_253;
static void entry__38_253(void);
static FRAME_INFO frame__38_253 = {1, {"other"}};
static void cont__38_254(void);
static void cont__38_255(void);
static void cont__38_256(void);
static NODE *func__38_257;
static void entry__38_257(void);
static FRAME_INFO frame__38_257 = {4, {"info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__38_258(void);
static NODE *func__38_259;
static void entry__38_259(void);
static FRAME_INFO frame__38_259 = {5, {"method_name", "method_info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__38_260(void);
static NODE *func__38_261;
static void entry__38_261(void);
static FRAME_INFO frame__38_261 = {1, {"total_methods"}};
static void cont__38_262(void);
static NODE *func__38_263;
static void entry__38_263(void);
static FRAME_INFO frame__38_263 = {1, {"total_inline_c_methods"}};
static void cont__38_264(void);
static NODE *func__38_265;
static void entry__38_265(void);
static FRAME_INFO frame__38_265 = {1, {"total_attributes"}};
static void cont__38_266(void);
static void cont__38_267(void);
static void cont__38_268(void);
static void cont__38_269(void);
static void cont__38_270(void);
static void cont__38_271(void);
static void cont__38_272(void);
static void cont__38_273(void);
static void cont__38_274(void);
static void cont__38_275(void);
static void cont__38_276(void);
static void cont__38_277(void);
static void cont__38_278(void);
static void cont__38_279(void);
static void cont__38_280(void);
static void cont__38_281(void);
static void cont__38_282(void);
static void cont__38_283(void);
static void cont__38_284(void);
static void cont__38_285(void);
static void cont__38_286(void);
static void cont__38_287(void);
static void cont__38_288(void);
static void cont__38_289(void);
static void cont__38_290(void);
static void cont__38_291(void);
static NODE *string__38_292;
static NODE *string__38_293;
static NODE *string__38_294;
static NODE *string__38_295;
static NODE *string__38_296;
static NODE *string__38_297;
static NODE *string__38_298;
static NODE *string__38_299;
static NODE *string__38_300;
static NODE *string__38_301;
static NODE *string__38_302;
static NODE *string__38_303;
static NODE *string__38_304;
static NODE *string__38_305;
static void cont__38_306(void);
static NODE *get__sim2c__extract_documentation(void) {
  return var.sim2c__extract_documentation;
}
static void cont__44_1(void);
static void cont__58_1(void);
static void cont__58_2(void);
static void cont__58_3(void);
static void cont__58_4(void);
static void cont__58_5(void);
static void cont__58_6(void);
static void cont__58_7(void);
static NODE *string__69_1;
static void cont__69_2(void);
static void cont__69_3(void);
static NODE *string__70_1;
static NODE *string__70_2;
static void cont__70_3(void);
static void cont__70_4(void);
static void cont__70_5(void);
static void cont__70_6(void);
static void cont__70_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__44_1, NULL, 63, 63, 15, 55},
  {cont__58_1, NULL, 63, 63, 7, 56},
  {cont__58_2, NULL, 64, 64, 12, 31},
  {cont__58_3, NULL, 64, 64, 12, 46},
  {cont__58_4, NULL, 64, 64, 7, 47},
  {cont__58_5, NULL, 62, 64, 5, 46},
  {cont__58_6, NULL, 58, 64, 1, 49},
  {cont__58_7, NULL, 377, 377, 8, 28},
  {cont__69_2, NULL, 377, 377, 1, 33},
  {cont__69_3, NULL, 378, 378, 10, 32},
  {cont__70_3, NULL, 378, 378, 40, 59},
  {cont__70_4, NULL, 378, 378, 40, 74},
  {cont__70_5, NULL, 378, 378, 35, 75},
  {cont__70_6, NULL, 378, 378, 1, 80},
  {cont__70_7, NULL, },
  {entry__22_4, NULL, 74, 152, 9, 11},
  {entry__22_3, NULL, 73, 152, 7, 12},
  {cont__22_6, &frame__22_3, 153, 153, 7, 15},
  {entry__22_2, NULL, 72, 153, 5, 15},
  {entry__22_1_create_page, NULL, 71, 153, 3, 16},
  {cont__22_7, &frame__22_1_create_page, 154, 154, 3, 20},
  {entry__24_10, NULL, 169, 169, 27, 52},
  {entry__24_16, NULL, 170, 170, 21, 63},
  {entry__24_23, NULL, 171, 171, 26, 71},
  {entry__24_32, NULL, 185, 185, 39, 56},
  {cont__24_33, &frame__24_32, 185, 185, 56, 56},
  {entry__24_39, NULL, 193, 193, 11, 42},
  {cont__24_40, &frame__24_39, 193, 193, 42, 42},
  {entry__24_41, NULL, 195, 195, 11, 26},
  {cont__24_42, &frame__24_41, 196, 196, 11, 48},
  {cont__24_43, &frame__24_41, 196, 196, 48, 48},
  {entry__24_44, NULL, 198, 198, 11, 14},
  {entry__24_36, NULL, 191, 191, 9, 27},
  {cont__24_37, &frame__24_36, 191, 191, 9, 30},
  {cont__24_38, &frame__24_36, 190, 198, 7, 15},
  {entry__24_35, NULL, 189, 198, 5, 16},
  {cont__24_45, &frame__24_35, 198, 198, 16, 16},
  {entry__24_49, NULL, 200, 200, 46, 70},
  {cont__24_50, &frame__24_49, 200, 200, 34, 70},
  {cont__24_51, &frame__24_49, 200, 200, 70, 70},
  {entry__24_54, NULL, 201, 201, 32, 54},
  {cont__24_56, &frame__24_54, 201, 201, 59, 59},
  {entry__24_61, NULL, 205, 205, 33, 36},
  {entry__24_59, NULL, 205, 205, 10, 30},
  {cont__24_60, &frame__24_59, 205, 205, 7, 36},
  {entry__24_64, NULL, 206, 206, 31, 34},
  {entry__24_62, NULL, 206, 206, 10, 28},
  {cont__24_63, &frame__24_62, 206, 206, 7, 34},
  {entry__24_79, NULL, 214, 214, 43, 68},
  {cont__24_80, &frame__24_79, 214, 214, 35, 69},
  {cont__24_81, &frame__24_79, 214, 214, 15, 70},
  {cont__24_82, &frame__24_79, 214, 214, 75, 75},
  {entry__24_75, NULL, 212, 212, 21, 43},
  {cont__24_76, &frame__24_75, 212, 212, 13, 46},
  {cont__24_77, &frame__24_75, 213, 213, 16, 56},
  {cont__24_78, &frame__24_75, 213, 214, 13, 75},
  {entry__24_71, NULL, 210, 210, 11, 48},
  {cont__24_72, &frame__24_71, 211, 211, 18, 41},
  {cont__24_73, &frame__24_71, 211, 211, 18, 52},
  {cont__24_74, &frame__24_71, 211, 214, 11, 76},
  {entry__24_67, NULL, 208, 208, 22, 51},
  {cont__24_68, &frame__24_67, 208, 208, 9, 54},
  {cont__24_69, &frame__24_67, 209, 209, 12, 38},
  {cont__24_70, &frame__24_67, 209, 214, 9, 77},
  {entry__24_65, NULL, 207, 207, 10, 35},
  {cont__24_66, &frame__24_65, 207, 214, 7, 78},
  {entry__24_58, NULL, 204, 214, 5, 79},
  {entry__24_87, NULL, 221, 221, 33, 36},
  {entry__24_85, NULL, 221, 221, 10, 30},
  {cont__24_86, &frame__24_85, 221, 221, 7, 36},
  {entry__24_105, NULL, 236, 236, 55, 68},
  {cont__24_106, &frame__24_105, 236, 236, 52, 68},
  {entry__24_107, NULL, 236, 236, 71, 82},
  {entry__24_101, NULL, 231, 231, 19, 42},
  {cont__24_102, &frame__24_101, 235, 235, 32, 51},
  {cont__24_103, &frame__24_101, 236, 236, 35, 49},
  {cont__24_104, &frame__24_101, 236, 236, 32, 83},
  {cont__24_108, &frame__24_101, 237, 237, 40, 65},
  {cont__24_109, &frame__24_101, 232, 232, 32, 59},
  {cont__24_110, &frame__24_101, 232, 232, 19, 60},
  {cont__24_111, &frame__24_101, 238, 238, 45, 45},
  {entry__24_99, NULL, 230, 230, 20, 39},
  {cont__24_100, &frame__24_99, 230, 238, 17, 45},
  {entry__24_112, NULL, 243, 243, 30, 49},
  {cont__24_113, &frame__24_112, 244, 244, 38, 63},
  {cont__24_114, &frame__24_112, 240, 240, 30, 57},
  {cont__24_115, &frame__24_112, 240, 240, 17, 58},
  {cont__24_116, &frame__24_112, 245, 245, 43, 43},
  {entry__24_96, NULL, 227, 227, 13, 37},
  {cont__24_97, &frame__24_96, 228, 228, 18, 35},
  {cont__24_98, &frame__24_96, 228, 245, 13, 44},
  {entry__24_93, NULL, 225, 225, 11, 45},
  {cont__24_94, &frame__24_93, 226, 226, 14, 33},
  {cont__24_95, &frame__24_93, 226, 245, 11, 45},
  {entry__24_90, NULL, 223, 223, 9, 44},
  {cont__24_91, &frame__24_90, 224, 224, 12, 32},
  {cont__24_92, &frame__24_90, 224, 245, 9, 46},
  {entry__24_88, NULL, 222, 222, 10, 28},
  {cont__24_89, &frame__24_88, 222, 245, 7, 47},
  {entry__24_142, NULL, 269, 269, 27, 50},
  {entry__24_143, NULL, 270, 270, 27, 49},
  {entry__24_139, NULL, 263, 263, 19, 56},
  {cont__24_140, &frame__24_139, 268, 268, 27, 44},
  {cont__24_141, &frame__24_139, 267, 270, 25, 48},
  {cont__24_144, &frame__24_139, 264, 264, 19, 37},
  {cont__24_145, &frame__24_139, 271, 271, 19, 23},
  {entry__24_137, NULL, 262, 262, 20, 60},
  {cont__24_138, &frame__24_137, 262, 271, 17, 23},
  {entry__24_152, NULL, 280, 280, 28, 50},
  {cont__24_153, &frame__24_152, 280, 280, 25, 50},
  {entry__24_154, NULL, 281, 281, 28, 53},
  {cont__24_155, &frame__24_154, 281, 281, 25, 53},
  {entry__24_148, NULL, 276, 276, 36, 56},
  {cont__24_149, &frame__24_148, 279, 279, 25, 50},
  {cont__24_150, &frame__24_148, 279, 279, 25, 59},
  {cont__24_151, &frame__24_148, 278, 281, 23, 52},
  {cont__24_156, &frame__24_148, 281, 281, 56, 56},
  {entry__24_146, NULL, 272, 272, 20, 35},
  {cont__24_147, &frame__24_146, 272, 281, 17, 56},
  {entry__24_160, NULL, 283, 283, 49, 49},
  {entry__24_158, NULL, 282, 282, 20, 37},
  {cont__24_159, &frame__24_158, 282, 283, 17, 49},
  {entry__24_166, NULL, 286, 286, 21, 50},
  {cont__24_167, &frame__24_166, 286, 286, 50, 50},
  {entry__24_163, NULL, 285, 285, 22, 41},
  {cont__24_164, &frame__24_163, 285, 285, 22, 52},
  {cont__24_165, &frame__24_163, 285, 286, 19, 50},
  {entry__24_161, NULL, 284, 284, 20, 42},
  {cont__24_162, &frame__24_161, 284, 286, 17, 51},
  {entry__24_170, NULL, 288, 288, 19, 37},
  {cont__24_171, &frame__24_170, 289, 289, 19, 23},
  {entry__24_168, NULL, 287, 287, 20, 51},
  {cont__24_169, &frame__24_168, 287, 289, 17, 23},
  {entry__24_174, NULL, 291, 291, 40, 40},
  {entry__24_172, NULL, 290, 290, 20, 39},
  {cont__24_173, &frame__24_172, 290, 291, 17, 40},
  {entry__24_183, NULL, 298, 298, 23, 66},
  {cont__24_184, &frame__24_183, 299, 299, 23, 82},
  {cont__24_185, &frame__24_183, 300, 300, 23, 70},
  {cont__24_186, &frame__24_183, 300, 300, 70, 70},
  {entry__24_180, NULL, 297, 297, 24, 51},
  {cont__24_181, &frame__24_180, 297, 297, 24, 68},
  {cont__24_182, &frame__24_180, 297, 300, 21, 70},
  {entry__24_177, NULL, 295, 295, 19, 57},
  {cont__24_178, &frame__24_177, 296, 296, 22, 51},
  {cont__24_179, &frame__24_177, 296, 300, 19, 71},
  {cont__24_187, &frame__24_177, 301, 301, 19, 37},
  {cont__24_188, &frame__24_177, 301, 301, 42, 42},
  {entry__24_202, NULL, 313, 313, 64, 64},
  {entry__24_199, NULL, 312, 312, 30, 47},
  {cont__24_200, &frame__24_199, 312, 312, 30, 58},
  {cont__24_201, &frame__24_199, 312, 313, 23, 64},
  {cont__24_203, &frame__24_199, 314, 314, 50, 67},
  {cont__24_204, &frame__24_199, 314, 314, 23, 80},
  {cont__24_205, &frame__24_199, 316, 316, 24, 44},
  {cont__24_206, &frame__24_199, 316, 316, 23, 55},
  {cont__24_207, &frame__24_199, 317, 317, 23, 41},
  {cont__24_208, &frame__24_199, 317, 317, 52, 52},
  {entry__24_196, NULL, 310, 310, 21, 45},
  {cont__24_197, &frame__24_196, 311, 311, 28, 56},
  {cont__24_198, &frame__24_196, 311, 317, 21, 52},
  {entry__24_190, NULL, 303, 303, 19, 50},
  {cont__24_191, &frame__24_190, 306, 306, 35, 52},
  {cont__24_192, &frame__24_190, 306, 306, 21, 65},
  {cont__24_193, &frame__24_190, 308, 308, 19, 37},
  {cont__24_194, &frame__24_190, 309, 309, 22, 36},
  {cont__24_195, &frame__24_190, 309, 317, 19, 53},
  {entry__24_129, NULL, 254, 254, 15, 39},
  {cont__24_130, &frame__24_129, 255, 255, 15, 49},
  {cont__24_131, &frame__24_129, 257, 257, 26, 45},
  {cont__24_132, &frame__24_129, 258, 258, 35, 63},
  {cont__24_133, &frame__24_129, 259, 259, 34, 59},
  {cont__24_134, &frame__24_129, 260, 260, 23, 45},
  {cont__24_135, &frame__24_129, 260, 260, 15, 48},
  {cont__24_136, &frame__24_129, 261, 291, 15, 41},
  {cont__24_175, &frame__24_129, 293, 293, 17, 46},
  {cont__24_176, &frame__24_129, 302, 302, 17, 43},
  {cont__24_189, &frame__24_129, 292, 317, 15, 55},
  {entry__24_125, NULL, 251, 251, 13, 50},
  {cont__24_126, &frame__24_125, 252, 252, 13, 47},
  {cont__24_127, &frame__24_125, 253, 253, 16, 35},
  {cont__24_128, &frame__24_125, 253, 317, 13, 56},
  {entry__24_121, NULL, 247, 247, 22, 51},
  {cont__24_122, &frame__24_121, 247, 247, 22, 54},
  {cont__24_123, &frame__24_121, 250, 250, 11, 37},
  {cont__24_124, &frame__24_121, 249, 317, 9, 58},
  {entry__24_119, NULL, 246, 246, 10, 35},
  {cont__24_120, &frame__24_119, 246, 317, 7, 59},
  {entry__24_84, NULL, 220, 317, 5, 60},
  {cont__24_209, &frame__24_84, 317, 317, 60, 60},
  {entry__24_1_extract_documentation_from_file, NULL, 167, 167, 10, 56},
  {cont__24_4, &frame__24_1_extract_documentation_from_file, 167, 167, 3, 56},
  {cont__24_5, &frame__24_1_extract_documentation_from_file, 168, 168, 8, 21},
  {cont__24_6, &frame__24_1_extract_documentation_from_file, 168, 168, 3, 31},
  {cont__24_7, &frame__24_1_extract_documentation_from_file, 169, 169, 6, 19},
  {cont__24_8, &frame__24_1_extract_documentation_from_file, 169, 169, 6, 24},
  {cont__24_9, &frame__24_1_extract_documentation_from_file, 169, 169, 3, 52},
  {cont__24_12, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 11},
  {cont__24_13, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 18},
  {cont__24_14, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 18},
  {cont__24_15, &frame__24_1_extract_documentation_from_file, 170, 170, 3, 63},
  {cont__24_18, &frame__24_1_extract_documentation_from_file, 171, 171, 11, 11},
  {cont__24_19, &frame__24_1_extract_documentation_from_file, 171, 171, 6, 12},
  {cont__24_20, &frame__24_1_extract_documentation_from_file, 171, 171, 6, 23},
  {cont__24_21, &frame__24_1_extract_documentation_from_file, 171, 171, 6, 23},
  {cont__24_22, &frame__24_1_extract_documentation_from_file, 171, 171, 3, 71},
  {cont__24_25, &frame__24_1_extract_documentation_from_file, 174, 174, 17, 48},
  {cont__24_27, &frame__24_1_extract_documentation_from_file, 174, 174, 50, 59},
  {cont__24_29, &frame__24_1_extract_documentation_from_file, 173, 175, 3, 69},
  {cont__24_30, &frame__24_1_extract_documentation_from_file, 184, 184, 3, 37},
  {cont__24_31, &frame__24_1_extract_documentation_from_file, 185, 185, 3, 56},
  {cont__24_34, &frame__24_1_extract_documentation_from_file, 188, 198, 3, 17},
  {cont__24_46, &frame__24_1_extract_documentation_from_file, 199, 199, 31, 31},
  {cont__24_47, &frame__24_1_extract_documentation_from_file, 199, 199, 3, 31},
  {cont__24_48, &frame__24_1_extract_documentation_from_file, 200, 200, 3, 70},
  {cont__24_52, &frame__24_1_extract_documentation_from_file, 201, 201, 6, 29},
  {cont__24_53, &frame__24_1_extract_documentation_from_file, 201, 201, 3, 59},
  {cont__24_57, &frame__24_1_extract_documentation_from_file, 203, 214, 3, 80},
  {cont__24_83, &frame__24_1_extract_documentation_from_file, 215, 317, 3, 61},
  {cont__24_210, &frame__24_1_extract_documentation_from_file, 317, 317, 61, 61},
  {entry__25_8, NULL, 323, 323, 32, 72},
  {entry__25_6, NULL, 323, 323, 10, 29},
  {cont__25_7, &frame__25_6, 323, 323, 7, 72},
  {entry__25_11, NULL, 324, 324, 36, 71},
  {entry__25_9, NULL, 324, 324, 10, 33},
  {cont__25_10, &frame__25_9, 324, 324, 7, 71},
  {entry__25_4, NULL, 321, 321, 5, 28},
  {cont__25_5, &frame__25_4, 322, 324, 5, 71},
  {entry__25_1_extract_documentation_from_directory, NULL, 320, 320, 22, 27},
  {cont__25_2, &frame__25_1_extract_documentation_from_directory, 320, 320, 12, 33},
  {cont__25_3, &frame__25_1_extract_documentation_from_directory, 320, 324, 3, 72},
  {entry__26_5, NULL, 328, 328, 40, 53},
  {cont__26_6, &frame__26_5, 328, 328, 37, 53},
  {entry__26_13, NULL, 333, 334, 17, 64},
  {cont__26_16, &frame__26_13, 333, 334, 11, 64},
  {entry__26_11, NULL, 332, 332, 12, 40},
  {cont__26_12, &frame__26_11, 332, 334, 9, 65},
  {cont__26_17, &frame__26_11, 335, 335, 37, 37},
  {entry__26_9, NULL, 331, 331, 10, 46},
  {cont__26_10, &frame__26_9, 331, 335, 7, 37},
  {entry__26_20, NULL, 337, 338, 13, 51},
  {cont__26_22, &frame__26_20, 337, 338, 7, 51},
  {entry__26_7, NULL, 330, 330, 14, 37},
  {cont__26_8, &frame__26_7, 330, 335, 5, 38},
  {cont__26_18, &frame__26_7, 336, 336, 12, 40},
  {cont__26_19, &frame__26_7, 336, 338, 5, 52},
  {cont__26_23, &frame__26_7, 339, 339, 8, 43},
  {cont__26_25, &frame__26_7, 339, 339, 5, 43},
  {entry__26_1_resolved_name, NULL, 327, 327, 3, 21},
  {cont__26_2, &frame__26_1_resolved_name, 328, 328, 6, 23},
  {cont__26_3, &frame__26_1_resolved_name, 328, 328, 6, 34},
  {cont__26_4, &frame__26_1_resolved_name, 328, 339, 3, 43},
  {entry__27_15, NULL, 349, 349, 35, 69},
  {entry__27_12, NULL, 348, 348, 7, 39},
  {cont__27_13, &frame__27_12, 349, 349, 10, 32},
  {cont__27_14, &frame__27_12, 349, 349, 7, 69},
  {entry__27_7, NULL, 345, 345, 6, 32},
  {cont__27_8, &frame__27_7, 345, 345, 5, 38},
  {cont__27_9, &frame__27_7, 346, 346, 12, 30},
  {cont__27_10, &frame__27_7, 346, 346, 12, 47},
  {cont__27_11, &frame__27_7, 346, 349, 5, 69},
  {cont__27_16, &frame__27_7, 350, 350, 5, 23},
  {cont__27_17, &frame__27_7, 350, 350, 34, 34},
  {entry__27_1_add_derived_type, NULL, 342, 342, 23, 40},
  {cont__27_2, &frame__27_1_add_derived_type, 342, 342, 42, 59},
  {cont__27_3, &frame__27_1_add_derived_type, 342, 342, 3, 60},
  {cont__27_4, &frame__27_1_add_derived_type, 343, 343, 3, 33},
  {cont__27_5, &frame__27_1_add_derived_type, 344, 344, 6, 26},
  {cont__27_6, &frame__27_1_add_derived_type, 344, 350, 3, 34},
  {entry__28_1_mangled, NULL, 352, 352, 38, 48},
  {cont__28_2, &frame__28_1_mangled, 352, 352, 50, 60},
  {cont__28_4, &frame__28_1_mangled, 352, 352, 21, 61},
  {cont__28_5, &frame__28_1_mangled, 352, 352, 18, 61},
  {entry__29_1_ordered_name, NULL, 357, 357, 7, 24},
  {cont__29_2, &frame__29_1_ordered_name, 359, 359, 7, 29},
  {cont__29_3, &frame__29_1_ordered_name, 356, 363, 5, 14},
  {cont__29_4, &frame__29_1_ordered_name, 355, 363, 3, 16},
  {entry__30_2, NULL, 367, 367, 7, 27},
  {cont__30_5, &frame__30_2, 367, 367, 5, 34},
  {cont__30_7, &frame__30_2, 368, 368, 5, 29},
  {cont__30_9, &frame__30_2, 369, 369, 7, 28},
  {cont__30_11, &frame__30_2, 369, 369, 5, 37},
  {cont__30_13, &frame__30_2, 370, 370, 5, 29},
  {cont__30_14, &frame__30_2, 371, 371, 7, 32},
  {cont__30_16, &frame__30_2, 371, 371, 5, 45},
  {cont__30_18, &frame__30_2, 372, 372, 5, 29},
  {cont__30_19, &frame__30_2, 373, 373, 7, 34},
  {cont__30_21, &frame__30_2, 373, 373, 5, 49},
  {cont__30_23, &frame__30_2, 374, 374, 5, 29},
  {cont__30_24, &frame__30_2, 375, 375, 7, 33},
  {cont__30_26, &frame__30_2, 375, 375, 5, 47},
  {entry__30_1_link_bar, NULL, 366, 375, 3, 47},
  {entry__33_5, NULL, 389, 389, 13, 22},
  {cont__33_6, &frame__33_5, 390, 390, 13, 33},
  {cont__33_7, &frame__33_5, 391, 391, 22, 22},
  {entry__33_8, NULL, 393, 393, 13, 33},
  {cont__33_9, &frame__33_8, 393, 393, 33, 33},
  {entry__33_3, NULL, 388, 388, 11, 35},
  {cont__33_4, &frame__33_3, 387, 393, 9, 34},
  {entry__33_15, NULL, 398, 398, 15, 35},
  {cont__33_16, &frame__33_15, 399, 399, 22, 22},
  {entry__33_12, NULL, 397, 397, 16, 25},
  {cont__33_13, &frame__33_12, 397, 397, 16, 25},
  {cont__33_14, &frame__33_12, 397, 399, 13, 22},
  {entry__33_21, NULL, 403, 403, 60, 60},
  {entry__33_19, NULL, 403, 403, 20, 44},
  {cont__33_20, &frame__33_19, 403, 403, 17, 60},
  {entry__33_22, NULL, 405, 405, 17, 30},
  {cont__33_23, &frame__33_22, 405, 405, 30, 30},
  {entry__33_17, NULL, 402, 402, 15, 24},
  {cont__33_18, &frame__33_17, 401, 405, 13, 31},
  {cont__33_24, &frame__33_17, 406, 406, 26, 34},
  {cont__33_25, &frame__33_17, 406, 406, 13, 34},
  {cont__33_26, &frame__33_17, 406, 406, 34, 34},
  {entry__33_10, NULL, 396, 396, 11, 20},
  {cont__33_11, &frame__33_10, 395, 406, 9, 35},
  {entry__33_2, NULL, 385, 406, 5, 37},
  {entry__33_30, NULL, 407, 407, 18, 38},
  {cont__33_31, &frame__33_30, 407, 407, 38, 38},
  {entry__33_1_to_paragraphs, NULL, 384, 406, 3, 38},
  {cont__33_27, &frame__33_1_to_paragraphs, 407, 407, 6, 15},
  {cont__33_28, &frame__33_1_to_paragraphs, 407, 407, 6, 15},
  {cont__33_29, &frame__33_1_to_paragraphs, 407, 407, 3, 38},
  {cont__33_32, &frame__33_1_to_paragraphs, 408, 408, 3, 15},
  {entry__34_7, NULL, 415, 415, 41, 67},
  {cont__34_9, &frame__34_7, 415, 415, 67, 67},
  {entry__34_12, NULL, 416, 416, 43, 69},
  {cont__34_14, &frame__34_12, 416, 416, 69, 69},
  {entry__34_3, NULL, 413, 413, 7, 40},
  {cont__34_4, &frame__34_3, 414, 414, 7, 42},
  {cont__34_5, &frame__34_3, 415, 415, 14, 38},
  {cont__34_6, &frame__34_3, 415, 415, 7, 67},
  {cont__34_10, &frame__34_3, 416, 416, 14, 40},
  {cont__34_11, &frame__34_3, 416, 416, 7, 69},
  {cont__34_15, &frame__34_3, 417, 417, 7, 50},
  {cont__34_16, &frame__34_3, 417, 417, 50, 50},
  {entry__34_19, NULL, 419, 419, 41, 65},
  {cont__34_20, &frame__34_19, 419, 419, 65, 65},
  {entry__34_17, NULL, 419, 419, 14, 38},
  {cont__34_18, &frame__34_17, 419, 419, 7, 65},
  {entry__34_1_resolve_reference, NULL, 412, 412, 5, 28},
  {cont__34_2, &frame__34_1_resolve_reference, 411, 419, 3, 66},
  {cont__34_21, &frame__34_1_resolve_reference, },
  {entry__35_5, NULL, 427, 427, 29, 29},
  {cont__35_6, &frame__35_5, 427, 427, 9, 29},
  {cont__35_7, &frame__35_5, 428, 428, 9, 36},
  {cont__35_8, &frame__35_5, 429, 429, 30, 46},
  {cont__35_9, &frame__35_5, 429, 429, 12, 54},
  {cont__35_13, &frame__35_5, 429, 429, 9, 54},
  {entry__35_1_add_links, NULL, 425, 425, 33, 47},
  {cont__35_2, &frame__35_1_add_links, 425, 425, 24, 48},
  {cont__35_3, &frame__35_1_add_links, 425, 425, 7, 53},
  {cont__35_4, &frame__35_1_add_links, 424, 429, 5, 54},
  {cont__35_14, &frame__35_1_add_links, 422, 429, 3, 56},
  {cont__35_15, &frame__35_1_add_links, 429, 429, 57, 57},
  {entry__36_6, NULL, 437, 437, 24, 40},
  {cont__36_7, &frame__36_6, 435, 438, 13, 55},
  {cont__36_12, &frame__36_6, 435, 438, 7, 55},
  {entry__36_2_resolve_and_check_reference, NULL, 433, 433, 5, 32},
  {cont__36_3, &frame__36_2_resolve_and_check_reference, 434, 434, 8, 36},
  {cont__36_4, &frame__36_2_resolve_and_check_reference, 434, 434, 8, 49},
  {cont__36_5, &frame__36_2_resolve_and_check_reference, 434, 438, 5, 56},
  {cont__36_13, &frame__36_2_resolve_and_check_reference, },
  {entry__36_23, NULL, 445, 445, 11, 42},
  {cont__36_24, &frame__36_23, 446, 446, 11, 44},
  {cont__36_25, &frame__36_23, 452, 452, 15, 26},
  {cont__36_26, &frame__36_23, 456, 456, 15, 28},
  {cont__36_27, &frame__36_23, 448, 457, 13, 21},
  {cont__36_29, &frame__36_23, 447, 457, 11, 23},
  {entry__36_33, NULL, 462, 462, 27, 65},
  {entry__36_35, NULL, 463, 463, 29, 69},
  {entry__36_37, NULL, 464, 464, 28, 67},
  {entry__36_30, NULL, 459, 459, 11, 26},
  {cont__36_31, &frame__36_30, 461, 461, 16, 37},
  {cont__36_32, &frame__36_30, 461, 464, 11, 67},
  {entry__36_42, NULL, 475, 475, 39, 59},
  {cont__36_43, &frame__36_42, 475, 475, 39, 59},
  {entry__36_47, NULL, 480, 480, 28, 44},
  {cont__36_48, &frame__36_47, 478, 480, 18, 48},
  {cont__36_52, &frame__36_47, 478, 480, 11, 48},
  {entry__36_45, NULL, 476, 476, 9, 40},
  {cont__36_46, &frame__36_45, 477, 480, 9, 49},
  {entry__36_67, NULL, 498, 498, 58, 58},
  {cont__36_68, &frame__36_67, 498, 498, 39, 59},
  {cont__36_69, &frame__36_67, 498, 498, 21, 74},
  {cont__36_71, &frame__36_67, 498, 498, 74, 74},
  {entry__36_65, NULL, 497, 497, 22, 47},
  {cont__36_66, &frame__36_65, 497, 498, 19, 74},
  {entry__36_74, NULL, 501, 501, 49, 49},
  {cont__36_75, &frame__36_74, 501, 501, 30, 50},
  {cont__36_76, &frame__36_74, 500, 501, 21, 79},
  {cont__36_78, &frame__36_74, 501, 501, 80, 80},
  {entry__36_72, NULL, 499, 499, 22, 47},
  {cont__36_73, &frame__36_72, 499, 501, 19, 80},
  {entry__36_81, NULL, 505, 505, 26, 47},
  {cont__36_82, &frame__36_81, 505, 505, 26, 53},
  {cont__36_83, &frame__36_81, 507, 507, 26, 47},
  {cont__36_84, &frame__36_81, 507, 507, 26, 53},
  {cont__36_85, &frame__36_81, 503, 508, 21, 28},
  {cont__36_88, &frame__36_81, 508, 508, 29, 29},
  {entry__36_79, NULL, 502, 502, 22, 45},
  {cont__36_80, &frame__36_79, 502, 508, 19, 29},
  {entry__36_63, NULL, 495, 495, 17, 68},
  {cont__36_64, &frame__36_63, 496, 508, 17, 30},
  {cont__36_89, &frame__36_63, 509, 509, 31, 52},
  {cont__36_90, &frame__36_63, 509, 509, 17, 58},
  {cont__36_91, &frame__36_63, 510, 510, 34, 56},
  {cont__36_92, &frame__36_63, 510, 510, 17, 56},
  {cont__36_93, &frame__36_63, 510, 510, 56, 56},
  {entry__36_58, NULL, 492, 492, 19, 53},
  {cont__36_59, &frame__36_58, 488, 493, 17, 20},
  {cont__36_61, &frame__36_58, 486, 493, 15, 21},
  {cont__36_62, &frame__36_58, 485, 510, 13, 57},
  {entry__36_103, NULL, 524, 524, 64, 64},
  {cont__36_104, &frame__36_103, 524, 524, 42, 65},
  {cont__36_105, &frame__36_103, 524, 524, 21, 80},
  {cont__36_106, &frame__36_103, 524, 524, 80, 80},
  {entry__36_101, NULL, 523, 523, 22, 50},
  {cont__36_102, &frame__36_101, 523, 524, 19, 80},
  {entry__36_109, NULL, 528, 528, 47, 47},
  {cont__36_110, &frame__36_109, 528, 528, 25, 48},
  {cont__36_111, &frame__36_109, 526, 529, 21, 52},
  {cont__36_112, &frame__36_109, 529, 529, 53, 53},
  {entry__36_107, NULL, 525, 525, 22, 50},
  {cont__36_108, &frame__36_107, 525, 529, 19, 53},
  {entry__36_99, NULL, 521, 521, 17, 71},
  {cont__36_100, &frame__36_99, 522, 529, 17, 54},
  {cont__36_113, &frame__36_99, 530, 530, 31, 52},
  {cont__36_114, &frame__36_99, 530, 530, 17, 58},
  {cont__36_115, &frame__36_99, 531, 531, 37, 62},
  {cont__36_116, &frame__36_99, 531, 531, 17, 62},
  {cont__36_117, &frame__36_99, 531, 531, 62, 62},
  {entry__36_94, NULL, 518, 518, 19, 53},
  {cont__36_95, &frame__36_94, 514, 519, 17, 20},
  {cont__36_97, &frame__36_94, 512, 519, 15, 21},
  {cont__36_98, &frame__36_94, 511, 531, 13, 63},
  {entry__36_124, NULL, 534, 534, 34, 47},
  {cont__36_125, &frame__36_124, 534, 534, 17, 47},
  {cont__36_126, &frame__36_124, 534, 534, 47, 47},
  {entry__36_121, NULL, 533, 533, 30, 51},
  {cont__36_122, &frame__36_121, 533, 533, 24, 56},
  {cont__36_123, &frame__36_121, 533, 534, 15, 47},
  {entry__36_118, NULL, 532, 532, 16, 49},
  {cont__36_120, &frame__36_118, 532, 534, 13, 48},
  {entry__36_132, NULL, 537, 537, 17, 27},
  {cont__36_133, &frame__36_132, 538, 538, 17, 38},
  {cont__36_134, &frame__36_132, 541, 541, 33, 45},
  {cont__36_135, &frame__36_132, 540, 541, 17, 66},
  {cont__36_136, &frame__36_132, 543, 543, 17, 46},
  {cont__36_137, &frame__36_132, 544, 544, 17, 30},
  {cont__36_138, &frame__36_132, 544, 544, 45, 45},
  {entry__36_129, NULL, 536, 536, 30, 51},
  {cont__36_130, &frame__36_129, 536, 536, 24, 56},
  {cont__36_131, &frame__36_129, 536, 544, 15, 45},
  {entry__36_127, NULL, 535, 535, 16, 43},
  {cont__36_128, &frame__36_127, 535, 544, 13, 46},
  {entry__36_141, NULL, 546, 546, 23, 44},
  {cont__36_142, &frame__36_141, 546, 546, 15, 50},
  {cont__36_143, &frame__36_141, 547, 547, 22, 43},
  {cont__36_144, &frame__36_141, 547, 547, 15, 49},
  {cont__36_145, &frame__36_141, 548, 548, 30, 41},
  {cont__36_146, &frame__36_141, 548, 548, 15, 41},
  {cont__36_147, &frame__36_141, 548, 548, 41, 41},
  {entry__36_139, NULL, 545, 545, 16, 45},
  {cont__36_140, &frame__36_139, 545, 548, 13, 41},
  {entry__36_155, NULL, 553, 553, 47, 47},
  {entry__36_156, NULL, 555, 555, 19, 49},
  {cont__36_157, &frame__36_156, 555, 555, 49, 49},
  {entry__36_151, NULL, 550, 550, 24, 45},
  {cont__36_152, &frame__36_151, 550, 550, 15, 51},
  {cont__36_153, &frame__36_151, 552, 552, 17, 28},
  {cont__36_154, &frame__36_151, 551, 555, 15, 50},
  {entry__36_148, NULL, 549, 549, 16, 58},
  {cont__36_150, &frame__36_148, 549, 555, 13, 51},
  {entry__36_162, NULL, 562, 562, 41, 41},
  {cont__36_163, &frame__36_162, 562, 562, 21, 41},
  {cont__36_164, &frame__36_162, 563, 563, 21, 58},
  {cont__36_165, &frame__36_162, 564, 564, 42, 58},
  {cont__36_166, &frame__36_162, 564, 564, 24, 66},
  {cont__36_167, &frame__36_162, 564, 564, 21, 66},
  {entry__36_173, NULL, 569, 569, 23, 55},
  {cont__36_174, &frame__36_173, 569, 569, 55, 55},
  {entry__36_175, NULL, 571, 571, 23, 50},
  {cont__36_176, &frame__36_175, 571, 571, 50, 50},
  {entry__36_171, NULL, 568, 568, 21, 48},
  {cont__36_172, &frame__36_171, 567, 571, 19, 51},
  {entry__36_177, NULL, 573, 573, 46, 46},
  {entry__36_158, NULL, 560, 560, 45, 59},
  {cont__36_159, &frame__36_158, 560, 560, 36, 60},
  {cont__36_160, &frame__36_158, 560, 560, 19, 65},
  {cont__36_161, &frame__36_158, 559, 564, 17, 66},
  {cont__36_168, &frame__36_158, 557, 564, 15, 68},
  {cont__36_169, &frame__36_158, 566, 566, 17, 44},
  {cont__36_170, &frame__36_158, 565, 573, 15, 47},
  {entry__36_57, NULL, 484, 573, 11, 49},
  {entry__36_55, NULL, 482, 482, 9, 46},
  {cont__36_56, &frame__36_55, 483, 573, 9, 50},
  {entry__36_195, NULL, 589, 589, 25, 51},
  {cont__36_196, &frame__36_195, 589, 589, 25, 61},
  {cont__36_197, &frame__36_195, 586, 590, 23, 27},
  {cont__36_198, &frame__36_195, 590, 590, 28, 28},
  {entry__36_199, NULL, 592, 592, 23, 48},
  {cont__36_200, &frame__36_199, 592, 592, 48, 48},
  {entry__36_192, NULL, 585, 585, 21, 47},
  {cont__36_193, &frame__36_192, 585, 585, 21, 58},
  {cont__36_194, &frame__36_192, 584, 592, 19, 49},
  {entry__36_190, NULL, 583, 583, 20, 48},
  {cont__36_191, &frame__36_190, 583, 592, 17, 50},
  {entry__36_203, NULL, 594, 594, 19, 58},
  {cont__36_204, &frame__36_203, 594, 594, 58, 58},
  {entry__36_201, NULL, 593, 593, 20, 48},
  {cont__36_202, &frame__36_201, 593, 594, 17, 58},
  {entry__36_209, NULL, 599, 599, 22, 47},
  {cont__36_210, &frame__36_209, 599, 599, 22, 61},
  {cont__36_211, &frame__36_209, 599, 599, 22, 64},
  {cont__36_212, &frame__36_209, 599, 599, 19, 64},
  {entry__36_213, NULL, 600, 600, 19, 23},
  {entry__36_186, NULL, 581, 581, 30, 53},
  {cont__36_187, &frame__36_186, 581, 581, 22, 54},
  {cont__36_188, &frame__36_186, 581, 581, 15, 75},
  {cont__36_189, &frame__36_186, 582, 594, 15, 59},
  {cont__36_205, &frame__36_186, 598, 598, 23, 48},
  {cont__36_206, &frame__36_186, 598, 598, 23, 57},
  {cont__36_207, &frame__36_186, 598, 598, 19, 58},
  {cont__36_208, &frame__36_186, 596, 600, 15, 24},
  {cont__36_214, &frame__36_186, 602, 602, 32, 49},
  {cont__36_215, &frame__36_186, 602, 602, 15, 49},
  {cont__36_216, &frame__36_186, 602, 602, 49, 49},
  {entry__36_217, NULL, 579, 579, 15, 18},
  {entry__36_183, NULL, 577, 577, 13, 40},
  {cont__36_184, &frame__36_183, 578, 578, 13, 52},
  {cont__36_185, &frame__36_183, 576, 602, 11, 50},
  {entry__36_181, NULL, 575, 575, 18, 36},
  {cont__36_182, &frame__36_181, 575, 602, 9, 51},
  {entry__36_220, NULL, 603, 603, 40, 58},
  {entry__36_230, NULL, 609, 609, 19, 42},
  {cont__36_231, &frame__36_230, 609, 609, 17, 42},
  {entry__36_227, NULL, 608, 608, 16, 32},
  {cont__36_228, &frame__36_227, 608, 608, 13, 32},
  {cont__36_229, &frame__36_227, 609, 609, 13, 42},
  {entry__36_226, NULL, 607, 609, 11, 42},
  {entry__36_223, NULL, 605, 605, 9, 23},
  {cont__36_225, &frame__36_223, 606, 609, 9, 43},
  {entry__36_240, NULL, 615, 615, 19, 45},
  {cont__36_241, &frame__36_240, 615, 615, 17, 45},
  {entry__36_237, NULL, 614, 614, 16, 35},
  {cont__36_238, &frame__36_237, 614, 614, 13, 35},
  {cont__36_239, &frame__36_237, 615, 615, 13, 45},
  {entry__36_236, NULL, 613, 615, 11, 45},
  {entry__36_234, NULL, 611, 611, 9, 20},
  {cont__36_235, &frame__36_234, 612, 615, 9, 46},
  {entry__36_247, NULL, 618, 618, 46, 58},
  {entry__36_244, NULL, 617, 617, 9, 24},
  {cont__36_246, &frame__36_244, 618, 618, 9, 58},
  {entry__36_253, NULL, 621, 621, 46, 53},
  {entry__36_250, NULL, 620, 620, 9, 30},
  {cont__36_252, &frame__36_250, 621, 621, 9, 53},
  {entry__36_263, NULL, 628, 628, 33, 49},
  {cont__36_264, &frame__36_263, 628, 628, 30, 56},
  {cont__36_265, &frame__36_263, 628, 628, 21, 56},
  {cont__36_266, &frame__36_263, 628, 628, 19, 66},
  {entry__36_262, NULL, 628, 628, 15, 66},
  {cont__36_267, &frame__36_262, 629, 629, 15, 25},
  {cont__36_269, &frame__36_262, 630, 630, 18, 46},
  {cont__36_270, &frame__36_262, 630, 630, 15, 46},
  {entry__36_260, NULL, 626, 626, 13, 50},
  {cont__36_261, &frame__36_260, 627, 630, 13, 46},
  {entry__36_259, NULL, 625, 630, 11, 47},
  {entry__36_256, NULL, 623, 623, 9, 21},
  {cont__36_258, &frame__36_256, 624, 630, 9, 48},
  {entry__36_282, NULL, 637, 637, 33, 44},
  {cont__36_283, &frame__36_282, 637, 637, 30, 51},
  {cont__36_284, &frame__36_282, 637, 637, 21, 51},
  {cont__36_285, &frame__36_282, 637, 637, 19, 56},
  {entry__36_289, NULL, 639, 639, 33, 46},
  {cont__36_290, &frame__36_289, 639, 639, 30, 53},
  {cont__36_291, &frame__36_289, 639, 639, 21, 53},
  {cont__36_292, &frame__36_289, 639, 639, 19, 60},
  {entry__36_281, NULL, 637, 637, 15, 56},
  {cont__36_286, &frame__36_281, 638, 638, 15, 33},
  {cont__36_288, &frame__36_281, 639, 639, 15, 60},
  {entry__36_279, NULL, 635, 635, 13, 50},
  {cont__36_280, &frame__36_279, 636, 639, 13, 60},
  {entry__36_277, NULL, 634, 634, 20, 33},
  {cont__36_278, &frame__36_277, 634, 639, 11, 61},
  {entry__36_274, NULL, 632, 632, 9, 27},
  {cont__36_276, &frame__36_274, 633, 639, 9, 62},
  {entry__36_295, NULL, 642, 642, 9, 61},
  {cont__36_296, &frame__36_295, 643, 643, 9, 23},
  {cont__36_298, &frame__36_295, 644, 644, 23, 55},
  {cont__36_299, &frame__36_295, 644, 644, 20, 62},
  {cont__36_300, &frame__36_295, 644, 644, 11, 62},
  {cont__36_301, &frame__36_295, 644, 645, 9, 35},
  {entry__36_312, NULL, 652, 652, 33, 51},
  {cont__36_313, &frame__36_312, 652, 652, 30, 58},
  {cont__36_314, &frame__36_312, 652, 652, 21, 58},
  {cont__36_315, &frame__36_312, 652, 652, 19, 70},
  {entry__36_318, NULL, 658, 658, 24, 44},
  {cont__36_319, &frame__36_318, 658, 658, 51, 69},
  {cont__36_320, &frame__36_318, 658, 658, 21, 76},
  {cont__36_321, &frame__36_318, 656, 658, 19, 75},
  {cont__36_322, &frame__36_318, 655, 661, 17, 29},
  {entry__36_311, NULL, 652, 652, 15, 70},
  {cont__36_316, &frame__36_311, 653, 653, 15, 25},
  {cont__36_317, &frame__36_311, 654, 661, 15, 30},
  {entry__36_310, NULL, 651, 661, 13, 31},
  {entry__36_308, NULL, 650, 650, 20, 35},
  {cont__36_309, &frame__36_308, 650, 661, 11, 32},
  {entry__36_305, NULL, 648, 648, 9, 44},
  {cont__36_307, &frame__36_305, 649, 661, 9, 33},
  {entry__36_338, NULL, 671, 671, 23, 39},
  {cont__36_339, &frame__36_338, 671, 671, 21, 45},
  {entry__36_337, NULL, 671, 671, 17, 45},
  {entry__36_331, NULL, 670, 670, 42, 60},
  {cont__36_332, &frame__36_331, 670, 670, 62, 70},
  {cont__36_334, &frame__36_331, 670, 670, 30, 71},
  {cont__36_335, &frame__36_331, 670, 670, 13, 80},
  {cont__36_336, &frame__36_331, 671, 671, 13, 45},
  {entry__36_330, NULL, 669, 671, 11, 45},
  {entry__36_327, NULL, 667, 667, 9, 19},
  {cont__36_329, &frame__36_327, 668, 671, 9, 46},
  {entry__36_354, NULL, 687, 687, 19, 35},
  {entry__36_349, NULL, 684, 684, 24, 48},
  {cont__36_350, &frame__36_349, 684, 684, 24, 63},
  {cont__36_351, &frame__36_349, 684, 684, 19, 64},
  {cont__36_352, &frame__36_349, 682, 685, 17, 25},
  {cont__36_353, &frame__36_349, 681, 687, 15, 35},
  {cont__36_355, &frame__36_349, 688, 688, 35, 69},
  {cont__36_357, &frame__36_349, 688, 688, 15, 69},
  {cont__36_358, &frame__36_349, 679, 688, 13, 68},
  {cont__36_359, &frame__36_349, 678, 688, 11, 70},
  {entry__36_341, NULL, 674, 674, 9, 30},
  {cont__36_342, &frame__36_341, 675, 675, 9, 36},
  {cont__36_343, &frame__36_341, 676, 676, 9, 16},
  {cont__36_344, &frame__36_341, 677, 677, 45, 56},
  {cont__36_345, &frame__36_341, 677, 677, 23, 56},
  {cont__36_346, &frame__36_341, 677, 677, 13, 56},
  {cont__36_348, &frame__36_341, 677, 688, 9, 71},
  {entry__36_20, NULL, 442, 442, 7, 14},
  {cont__36_21, &frame__36_20, 444, 444, 9, 36},
  {cont__36_22, &frame__36_20, 443, 464, 7, 69},
  {cont__36_39, &frame__36_20, 474, 474, 7, 41},
  {cont__36_40, &frame__36_20, 475, 475, 10, 34},
  {cont__36_41, &frame__36_20, 475, 475, 10, 59},
  {cont__36_44, &frame__36_20, 475, 480, 7, 50},
  {cont__36_53, &frame__36_20, 481, 481, 10, 32},
  {cont__36_54, &frame__36_20, 481, 573, 7, 51},
  {cont__36_178, &frame__36_20, 574, 574, 10, 22},
  {cont__36_179, &frame__36_20, 574, 574, 10, 34},
  {cont__36_180, &frame__36_20, 574, 602, 7, 52},
  {cont__36_218, &frame__36_20, 603, 603, 10, 37},
  {cont__36_219, &frame__36_20, 603, 603, 7, 58},
  {cont__36_221, &frame__36_20, 604, 604, 14, 32},
  {cont__36_222, &frame__36_20, 604, 609, 7, 44},
  {cont__36_232, &frame__36_20, 610, 610, 14, 35},
  {cont__36_233, &frame__36_20, 610, 615, 7, 47},
  {cont__36_242, &frame__36_20, 616, 616, 14, 34},
  {cont__36_243, &frame__36_20, 616, 618, 7, 58},
  {cont__36_248, &frame__36_20, 619, 619, 10, 37},
  {cont__36_249, &frame__36_20, 619, 621, 7, 53},
  {cont__36_254, &frame__36_20, 622, 622, 14, 32},
  {cont__36_255, &frame__36_20, 622, 630, 7, 49},
  {cont__36_271, &frame__36_20, 631, 631, 14, 27},
  {cont__36_272, &frame__36_20, 631, 631, 14, 36},
  {cont__36_273, &frame__36_20, 631, 639, 7, 63},
  {cont__36_293, &frame__36_20, 641, 641, 10, 37},
  {cont__36_294, &frame__36_20, 641, 645, 7, 36},
  {cont__36_302, &frame__36_20, 647, 647, 10, 22},
  {cont__36_303, &frame__36_20, 647, 647, 10, 39},
  {cont__36_304, &frame__36_20, 647, 661, 7, 34},
  {cont__36_323, &frame__36_20, 664, 664, 9, 42},
  {cont__36_324, &frame__36_20, 663, 664, 7, 64},
  {cont__36_325, &frame__36_20, 666, 666, 14, 32},
  {cont__36_326, &frame__36_20, 666, 671, 7, 47},
  {cont__36_340, &frame__36_20, 673, 688, 7, 72},
  {cont__36_360, &frame__36_20, 690, 690, 9, 26},
  {cont__36_362, &frame__36_20, 691, 691, 24, 40},
  {cont__36_363, &frame__36_20, 691, 691, 24, 69},
  {cont__36_364, &frame__36_20, 691, 691, 9, 76},
  {cont__36_367, &frame__36_20, 689, 691, 7, 76},
  {entry__36_15, NULL, 441, 441, 25, 45},
  {cont__36_16, &frame__36_15, 441, 441, 17, 52},
  {cont__36_19, &frame__36_15, 441, 691, 5, 77},
  {entry__36_1_create_info_page, NULL, 440, 440, 6, 29},
  {cont__36_14, &frame__36_1_create_info_page, 440, 691, 3, 78},
  {entry__37_4, NULL, 696, 696, 37, 57},
  {cont__37_5, &frame__37_4, 696, 696, 33, 58},
  {cont__37_6, &frame__37_4, 696, 696, 33, 58},
  {entry__37_12, NULL, 698, 698, 24, 46},
  {cont__37_13, &frame__37_12, 698, 698, 24, 46},
  {cont__37_14, &frame__37_12, 698, 698, 24, 46},
  {entry__37_10, NULL, 698, 698, 10, 19},
  {cont__37_11, &frame__37_10, 698, 698, 10, 46},
  {cont__37_15, &frame__37_10, 698, 698, 7, 52},
  {cont__37_16, &frame__37_10, 699, 699, 33, 41},
  {cont__37_17, &frame__37_10, 699, 699, 7, 41},
  {cont__37_18, &frame__37_10, 699, 699, 41, 41},
  {entry__37_9, NULL, 697, 699, 20, 41},
  {cont__37_19, &frame__37_9, 699, 699, 41, 41},
  {entry__37_21, NULL, 700, 700, 29, 56},
  {cont__37_22, &frame__37_21, 700, 700, 29, 61},
  {cont__37_23, &frame__37_21, 700, 700, 29, 61},
  {entry__37_25, NULL, 704, 704, 24, 40},
  {cont__37_26, &frame__37_25, 701, 706, 14, 28},
  {cont__37_29, &frame__37_25, 701, 706, 7, 28},
  {entry__37_8, NULL, 697, 699, 5, 41},
  {cont__37_20, &frame__37_8, 700, 700, 8, 61},
  {cont__37_24, &frame__37_8, 700, 706, 5, 29},
  {entry__37_1_get_short_description, NULL, 694, 694, 3, 37},
  {cont__37_2, &frame__37_1_get_short_description, 696, 696, 6, 28},
  {cont__37_3, &frame__37_1_get_short_description, 696, 696, 6, 58},
  {cont__37_7, &frame__37_1_get_short_description, 696, 706, 3, 30},
  {cont__37_30, &frame__37_1_get_short_description, 707, 707, 3, 30},
  {cont__37_31, &frame__37_1_get_short_description, 708, 708, 3, 22},
  {entry__38_14, NULL, 721, 721, 27, 53},
  {entry__38_19, NULL, 725, 725, 24, 48},
  {cont__38_20, &frame__38_19, 725, 725, 11, 62},
  {cont__38_21, &frame__38_19, 725, 725, 62, 62},
  {entry__38_17, NULL, 724, 724, 16, 42},
  {cont__38_18, &frame__38_17, 724, 725, 9, 62},
  {cont__38_22, &frame__38_17, 726, 726, 9, 45},
  {cont__38_24, &frame__38_17, 727, 727, 9, 79},
  {cont__38_25, &frame__38_17, 727, 727, 9, 36},
  {cont__38_26, &frame__38_17, 729, 729, 24, 48},
  {cont__38_27, &frame__38_17, 729, 729, 50, 74},
  {cont__38_28, &frame__38_17, 728, 729, 9, 75},
  {cont__38_29, &frame__38_17, 730, 730, 10, 27},
  {cont__38_30, &frame__38_17, 730, 730, 10, 36},
  {cont__38_31, &frame__38_17, 730, 730, 9, 42},
  {cont__38_32, &frame__38_17, 730, 730, 9, 27},
  {cont__38_33, &frame__38_17, 731, 731, 9, 29},
  {cont__38_34, &frame__38_17, 731, 731, 41, 41},
  {entry__38_11, NULL, 720, 720, 7, 25},
  {cont__38_12, &frame__38_11, 721, 721, 10, 24},
  {cont__38_13, &frame__38_11, 721, 721, 7, 53},
  {cont__38_15, &frame__38_11, 723, 723, 16, 31},
  {cont__38_16, &frame__38_11, 723, 731, 7, 41},
  {cont__38_35, &frame__38_11, 732, 732, 8, 25},
  {cont__38_36, &frame__38_11, 732, 732, 7, 25},
  {cont__38_37, &frame__38_11, 732, 732, 44, 44},
  {entry__38_5, NULL, 716, 716, 5, 23},
  {cont__38_6, &frame__38_5, 717, 717, 5, 62},
  {cont__38_7, &frame__38_5, 717, 717, 5, 29},
  {cont__38_8, &frame__38_5, 719, 719, 8, 20},
  {cont__38_9, &frame__38_5, 719, 719, 8, 37},
  {cont__38_10, &frame__38_5, 719, 732, 5, 44},
  {entry__38_47, NULL, 745, 745, 18, 50},
  {cont__38_48, &frame__38_47, 745, 745, 13, 50},
  {cont__38_49, &frame__38_47, 746, 746, 27, 39},
  {cont__38_50, &frame__38_47, 746, 746, 24, 46},
  {cont__38_51, &frame__38_47, 746, 746, 15, 46},
  {cont__38_52, &frame__38_47, 746, 746, 13, 52},
  {entry__38_46, NULL, 744, 746, 11, 52},
  {entry__38_55, NULL, 747, 747, 43, 63},
  {cont__38_56, &frame__38_55, 747, 747, 39, 64},
  {cont__38_57, &frame__38_55, 747, 747, 39, 64},
  {entry__38_59, NULL, 748, 748, 14, 39},
  {cont__38_60, &frame__38_59, 748, 748, 14, 42},
  {cont__38_61, &frame__38_59, 748, 748, 11, 42},
  {entry__38_64, NULL, 750, 750, 27, 43},
  {cont__38_65, &frame__38_64, 750, 750, 45, 52},
  {cont__38_66, &frame__38_64, 750, 750, 11, 52},
  {entry__38_42, NULL, 741, 741, 9, 28},
  {cont__38_43, &frame__38_42, 742, 742, 9, 43},
  {cont__38_44, &frame__38_42, 743, 743, 12, 27},
  {cont__38_45, &frame__38_42, 743, 746, 9, 53},
  {cont__38_53, &frame__38_42, 747, 747, 12, 34},
  {cont__38_54, &frame__38_42, 747, 747, 12, 64},
  {cont__38_58, &frame__38_42, 747, 748, 9, 42},
  {cont__38_62, &frame__38_42, 749, 749, 18, 39},
  {cont__38_63, &frame__38_42, 749, 750, 9, 52},
  {entry__38_41_print_type_info, NULL, 740, 750, 7, 53},
  {entry__38_73, NULL, 756, 756, 46, 58},
  {cont__38_74, &frame__38_73, 756, 756, 46, 71},
  {cont__38_75, &frame__38_73, 756, 756, 46, 71},
  {entry__38_77, NULL, 757, 757, 11, 30},
  {entry__38_70, NULL, 756, 756, 12, 24},
  {cont__38_71, &frame__38_70, 756, 756, 12, 41},
  {cont__38_72, &frame__38_70, 756, 756, 12, 71},
  {cont__38_76, &frame__38_70, 756, 757, 9, 30},
  {entry__38_69, NULL, 755, 757, 7, 31},
  {entry__38_40, NULL, 752, 752, 5, 12},
  {cont__38_67, &frame__38_40, 753, 753, 5, 19},
  {cont__38_68, &frame__38_40, 754, 757, 5, 32},
  {entry__38_86, NULL, 765, 765, 20, 31},
  {cont__38_88, &frame__38_86, 765, 765, 11, 31},
  {cont__38_89, &frame__38_86, 765, 765, 33, 52},
  {cont__38_90, &frame__38_86, 765, 765, 9, 52},
  {entry__38_91, NULL, 767, 767, 9, 16},
  {entry__38_107, NULL, 777, 777, 22, 41},
  {cont__38_108, &frame__38_107, 777, 777, 17, 41},
  {cont__38_109, &frame__38_107, 778, 778, 19, 35},
  {cont__38_111, &frame__38_107, 778, 778, 17, 66},
  {entry__38_105, NULL, 776, 776, 18, 30},
  {cont__38_106, &frame__38_105, 776, 778, 15, 66},
  {entry__38_102, NULL, 775, 775, 16, 28},
  {cont__38_104, &frame__38_102, 775, 778, 13, 67},
  {entry__38_100, NULL, 773, 773, 11, 26},
  {cont__38_101, &frame__38_100, 774, 778, 11, 68},
  {entry__38_117, NULL, 782, 782, 43, 63},
  {cont__38_118, &frame__38_117, 782, 782, 39, 64},
  {cont__38_119, &frame__38_117, 782, 782, 39, 64},
  {entry__38_121, NULL, 783, 783, 19, 44},
  {cont__38_122, &frame__38_121, 783, 783, 11, 47},
  {cont__38_123, &frame__38_121, 783, 783, 47, 47},
  {entry__38_126, NULL, 788, 788, 22, 34},
  {entry__38_128, NULL, 789, 789, 34, 58},
  {entry__38_130, NULL, 790, 790, 35, 60},
  {entry__38_132, NULL, 791, 791, 27, 44},
  {entry__38_134, NULL, 792, 792, 29, 48},
  {entry__38_136, NULL, 793, 793, 31, 52},
  {entry__38_138, NULL, 794, 794, 25, 40},
  {entry__38_140, NULL, 795, 795, 22, 34},
  {entry__38_142, NULL, 796, 796, 19, 28},
  {entry__38_144, NULL, 797, 797, 13, 24},
  {entry__38_149, NULL, 802, 802, 15, 55},
  {cont__38_151, &frame__38_149, 802, 802, 55, 55},
  {entry__38_152, NULL, 804, 804, 31, 31},
  {entry__38_147, NULL, 801, 801, 13, 29},
  {cont__38_148, &frame__38_147, 800, 804, 11, 32},
  {entry__38_155, NULL, 805, 805, 33, 47},
  {cont__38_156, &frame__38_155, 805, 805, 33, 47},
  {entry__38_165, NULL, 808, 808, 31, 42},
  {cont__38_166, &frame__38_165, 808, 808, 28, 49},
  {cont__38_167, &frame__38_165, 808, 808, 19, 49},
  {cont__38_168, &frame__38_165, 808, 808, 51, 68},
  {cont__38_169, &frame__38_165, 808, 808, 17, 68},
  {entry__38_159, NULL, 807, 807, 16, 32},
  {cont__38_162, &frame__38_159, 807, 807, 34, 50},
  {cont__38_163, &frame__38_159, 807, 807, 13, 50},
  {cont__38_164, &frame__38_159, 808, 808, 13, 68},
  {cont__38_170, &frame__38_159, 809, 809, 16, 33},
  {cont__38_172, &frame__38_159, 809, 809, 13, 40},
  {entry__38_158, NULL, 806, 809, 11, 40},
  {entry__38_96, NULL, 772, 772, 12, 19},
  {cont__38_97, &frame__38_96, 772, 772, 12, 29},
  {cont__38_98, &frame__38_96, 772, 772, 12, 29},
  {cont__38_99, &frame__38_96, 772, 778, 9, 69},
  {cont__38_113, &frame__38_96, 780, 780, 9, 27},
  {cont__38_114, &frame__38_96, 781, 781, 9, 43},
  {cont__38_115, &frame__38_96, 782, 782, 12, 34},
  {cont__38_116, &frame__38_96, 782, 782, 12, 64},
  {cont__38_120, &frame__38_96, 782, 783, 9, 47},
  {cont__38_124, &frame__38_96, 787, 787, 13, 25},
  {cont__38_125, &frame__38_96, 785, 797, 9, 25},
  {cont__38_145, &frame__38_96, 799, 799, 12, 31},
  {cont__38_146, &frame__38_96, 799, 804, 9, 33},
  {cont__38_153, &frame__38_96, 805, 805, 12, 28},
  {cont__38_154, &frame__38_96, 805, 805, 12, 47},
  {cont__38_157, &frame__38_96, 805, 809, 9, 41},
  {entry__38_95, NULL, 771, 809, 7, 42},
  {entry__38_80, NULL, 760, 760, 5, 12},
  {cont__38_81, &frame__38_80, 761, 761, 8, 21},
  {cont__38_84, &frame__38_80, 761, 761, 5, 36},
  {cont__38_85, &frame__38_80, 762, 767, 5, 17},
  {cont__38_93, &frame__38_80, 768, 768, 5, 6},
  {cont__38_94, &frame__38_80, 769, 809, 5, 43},
  {entry__38_180, NULL, 816, 816, 26, 53},
  {cont__38_181, &frame__38_180, 816, 816, 9, 65},
  {entry__38_178, NULL, 815, 815, 16, 31},
  {cont__38_179, &frame__38_178, 815, 816, 7, 65},
  {entry__38_174, NULL, 812, 812, 5, 23},
  {cont__38_175, &frame__38_174, 813, 813, 5, 30},
  {cont__38_176, &frame__38_174, 814, 814, 10, 22},
  {cont__38_177, &frame__38_174, 814, 816, 5, 66},
  {entry__38_195, NULL, 824, 824, 19, 35},
  {cont__38_196, &frame__38_195, 824, 824, 17, 41},
  {entry__38_194, NULL, 824, 824, 13, 41},
  {entry__38_189, NULL, 823, 823, 38, 56},
  {cont__38_190, &frame__38_189, 823, 823, 58, 66},
  {cont__38_191, &frame__38_189, 823, 823, 26, 67},
  {cont__38_192, &frame__38_189, 823, 823, 9, 76},
  {cont__38_193, &frame__38_189, 824, 824, 9, 41},
  {entry__38_188, NULL, 822, 824, 7, 41},
  {entry__38_184, NULL, 819, 819, 5, 12},
  {cont__38_185, &frame__38_184, 820, 820, 8, 21},
  {cont__38_186, &frame__38_184, 820, 820, 5, 35},
  {cont__38_187, &frame__38_184, 821, 824, 5, 42},
  {entry__38_210, NULL, 833, 833, 35, 51},
  {cont__38_211, &frame__38_210, 833, 833, 28, 60},
  {cont__38_212, &frame__38_210, 833, 833, 19, 60},
  {cont__38_213, &frame__38_210, 833, 833, 17, 70},
  {entry__38_209, NULL, 833, 833, 13, 70},
  {cont__38_214, &frame__38_209, 834, 834, 13, 23},
  {cont__38_215, &frame__38_209, 835, 835, 16, 44},
  {cont__38_216, &frame__38_209, 835, 835, 13, 44},
  {entry__38_208, NULL, 832, 835, 11, 44},
  {entry__38_207, NULL, 831, 835, 9, 45},
  {entry__38_203, NULL, 828, 828, 7, 14},
  {cont__38_204, &frame__38_203, 829, 829, 10, 23},
  {cont__38_205, &frame__38_203, 829, 829, 7, 29},
  {cont__38_206, &frame__38_203, 830, 835, 7, 46},
  {entry__38_198, NULL, 826, 826, 27, 45},
  {cont__38_199, &frame__38_198, 826, 826, 47, 55},
  {cont__38_200, &frame__38_198, 826, 826, 5, 56},
  {cont__38_201, &frame__38_198, 827, 827, 17, 39},
  {cont__38_202, &frame__38_198, 827, 835, 5, 47},
  {entry__38_222, NULL, 838, 838, 10, 31},
  {cont__38_223, &frame__38_222, 838, 838, 8, 40},
  {entry__38_225, NULL, 839, 839, 10, 35},
  {cont__38_226, &frame__38_225, 839, 839, 8, 48},
  {entry__38_228, NULL, 840, 840, 10, 37},
  {cont__38_229, &frame__38_228, 840, 840, 8, 52},
  {entry__38_231, NULL, 841, 841, 10, 36},
  {cont__38_232, &frame__38_231, 841, 841, 8, 50},
  {entry__38_219, NULL, 837, 837, 5, 19},
  {cont__38_221, &frame__38_219, 838, 838, 5, 40},
  {cont__38_224, &frame__38_219, 839, 839, 5, 48},
  {cont__38_227, &frame__38_219, 840, 840, 5, 52},
  {cont__38_230, &frame__38_219, 841, 841, 5, 50},
  {entry__38_237, NULL, 859, 859, 19, 38},
  {cont__38_238, &frame__38_237, 859, 859, 38, 38},
  {entry__38_239, NULL, 860, 860, 31, 62},
  {cont__38_240, &frame__38_239, 860, 860, 62, 62},
  {entry__38_241, NULL, 861, 861, 32, 64},
  {cont__38_242, &frame__38_241, 861, 861, 64, 64},
  {entry__38_243, NULL, 862, 862, 28, 56},
  {cont__38_244, &frame__38_243, 862, 862, 56, 56},
  {entry__38_245, NULL, 863, 863, 24, 48},
  {cont__38_246, &frame__38_245, 863, 863, 48, 48},
  {entry__38_247, NULL, 864, 864, 26, 52},
  {cont__38_248, &frame__38_247, 864, 864, 52, 52},
  {entry__38_249, NULL, 865, 865, 22, 44},
  {cont__38_250, &frame__38_249, 865, 865, 44, 44},
  {entry__38_251, NULL, 866, 866, 19, 38},
  {cont__38_252, &frame__38_251, 866, 866, 38, 38},
  {entry__38_253, NULL, 867, 867, 11, 20},
  {cont__38_254, &frame__38_253, 867, 867, 20, 20},
  {entry__38_261, NULL, 871, 871, 23, 40},
  {cont__38_262, &frame__38_261, 871, 871, 40, 40},
  {entry__38_263, NULL, 872, 872, 32, 58},
  {cont__38_264, &frame__38_263, 872, 872, 58, 58},
  {entry__38_265, NULL, 873, 873, 15, 35},
  {cont__38_266, &frame__38_265, 873, 873, 35, 35},
  {entry__38_259, NULL, 870, 870, 16, 35},
  {cont__38_260, &frame__38_259, 870, 873, 11, 35},
  {entry__38_257, NULL, 869, 869, 18, 33},
  {cont__38_258, &frame__38_257, 869, 873, 9, 36},
  {entry__38_235, NULL, 858, 858, 12, 24},
  {cont__38_236, &frame__38_235, 858, 867, 7, 20},
  {cont__38_255, &frame__38_235, 868, 868, 12, 24},
  {cont__38_256, &frame__38_235, 868, 873, 7, 37},
  {entry__38_234, NULL, 857, 873, 5, 38},
  {cont__38_267, &frame__38_234, },
  {cont__38_268, &frame__38_234, },
  {cont__38_269, &frame__38_234, },
  {cont__38_270, &frame__38_234, },
  {cont__38_271, &frame__38_234, },
  {cont__38_272, &frame__38_234, },
  {cont__38_273, &frame__38_234, },
  {cont__38_274, &frame__38_234, },
  {cont__38_275, &frame__38_234, },
  {cont__38_276, &frame__38_234, 875, 887, 5, 24},
  {cont__38_277, &frame__38_234, 890, 890, 32, 60},
  {cont__38_278, &frame__38_234, 892, 892, 32, 58},
  {cont__38_279, &frame__38_234, 893, 893, 32, 70},
  {cont__38_280, &frame__38_234, 894, 894, 32, 71},
  {cont__38_281, &frame__38_234, 895, 895, 32, 56},
  {cont__38_282, &frame__38_234, 896, 896, 32, 65},
  {cont__38_283, &frame__38_234, 897, 897, 32, 59},
  {cont__38_284, &frame__38_234, 898, 898, 32, 67},
  {cont__38_285, &frame__38_234, 899, 899, 32, 63},
  {cont__38_286, &frame__38_234, 900, 900, 32, 65},
  {cont__38_287, &frame__38_234, 901, 901, 32, 61},
  {cont__38_288, &frame__38_234, 902, 902, 32, 58},
  {cont__38_289, &frame__38_234, 903, 903, 32, 48},
  {cont__38_290, &frame__38_234, 905, 905, 32, 70},
  {cont__38_291, &frame__38_234, 889, 905, 12, 71},
  {cont__38_306, &frame__38_234, 889, 905, 5, 71},
  {entry__38_1_sim2c__extract_documentation, NULL, 712, 712, 42, 42},
  {cont__38_2, &frame__38_1_sim2c__extract_documentation, 712, 712, 3, 43},
  {cont__38_3, &frame__38_1_sim2c__extract_documentation, 713, 713, 3, 43},
  {cont__38_4, &frame__38_1_sim2c__extract_documentation, 715, 732, 3, 45},
  {cont__38_38, &frame__38_1_sim2c__extract_documentation, 734, 757, 3, 33},
  {cont__38_78, &frame__38_1_sim2c__extract_documentation, 759, 809, 3, 44},
  {cont__38_173, &frame__38_1_sim2c__extract_documentation, 811, 816, 3, 67},
  {cont__38_182, &frame__38_1_sim2c__extract_documentation, 818, 824, 3, 43},
  {cont__38_197, &frame__38_1_sim2c__extract_documentation, 825, 835, 3, 48},
  {cont__38_217, &frame__38_1_sim2c__extract_documentation, 836, 841, 3, 50},
  {cont__38_233, &frame__38_1_sim2c__extract_documentation, 843, 905, 3, 72}
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__filename_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__filename_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__filename_of, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}
static void type__used_namespaces_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__used_namespaces_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__used_namespaces_of, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}
static void type__derived_types_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__derived_types_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__derived_types_of, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}
static void type__methods_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__methods_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__methods_of, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}
static void type__types_of(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__types_of);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__types_of, attr);
      arguments = node_p;
      argument_count = 1;
      arguments->slots[0] = temp;
    } else {
      arguments = node_p;
      arguments->slots[0] = RETRIEVE_ATTRIBUTE_VALUE(myself);
    }
    func = frame->cont;
    frame->cont = invalid_continuation;
  } else {
    func = myself->type;
  }
}
static NODE *character__35;
static NODE *character__122;
static NODE *character__47;
static NODE *number__80;
static NODE *character__63;
static NODE *character__44;
static NODE *character__58;
static NODE *number__0;
static NODE *number__3;
static NODE *character__60;
static NODE *character__34;
static NODE *number__5;
static NODE *character__36;
static NODE *character__91;
static NODE *character__32;
static NODE *character__61;
static NODE *character__97;
static NODE *number__1;
static NODE *number__2;
static NODE *character__42;
static NODE *character__62;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  "html",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "extractor",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("extractor.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__extractor(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 6);
  // 36: $$polymorphic_functions
  // 37:   multi_dimensional_set(types::key_order_table types::key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__types__key_order_table();
  arguments->slots[1] = get__types__key_order_set();
  result_count = 1;
  myself = get__multi_dimensional_set();
  func = myself->type;
  frame->cont = cont__44_1;
}
static void cont__44_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 39: $$definitions empty_key_order_table
  var._definitions = get__empty_key_order_table();
  // 41: $$short_descriptions empty_table
  var._short_descriptions = get__empty_table();
  // 44: $$topics empty_key_order_table
  var._topics = get__empty_key_order_table();
  // 46: $$missing_documentation_count 0
  var._missing_documentation_count = number__0;
  // 63: ... sim2c::WHITESPACE, '=', sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__sim2c__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__sim2c__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__58_1;
}
static void cont__58_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 63: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__58_2;
}
static void cont__58_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 64: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__58_3;
}
static void cont__58_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 64: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__58_4;
}
static void cont__58_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 64: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__58_5;
}
static void cont__58_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 62: sequence
  // 63:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 64:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__58_6;
}
static void cont__58_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 58: $PARAMETER_COUNT_OR_MYSELF
  // 59:   alt
  // 60:     '*'
  // 61:     '?'
  // 62:     sequence
  // 63:       alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 64:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__58_7;
}
static void cont__58_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 66: $$path_prefix undefined
  var._path_prefix = get__undefined();
  // 156: types::object $symbol_info
  // 157:   .kind_of OTHER
  // 158:   .name_of undefined
  // 159:   .base_of undefined
  // 160:   .parameters_of undefined
  // 161:   .remark_lines_of undefined
  // 162:   .derived_types_of empty_key_order_set
  // 163:   .methods_of empty_key_order_table
  // 164:   .types_of empty_key_order_set
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._OTHER);
    set_attribute_value(temp->attributes, poly_idx__name_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__parameters_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, get__empty_key_order_set());
    set_attribute_value(temp->attributes, poly_idx__methods_of, get__empty_key_order_table());
    set_attribute_value(temp->attributes, poly_idx__types_of, get__empty_key_order_set());
    initialize_future(var._symbol_info, temp);

  }
  // 377: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_328;
  arguments->slots[1] = string__69_1;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__69_2;
}
static void cont__69_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 377: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__69_3;
}
static void cont__69_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 378: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__70_1;
  arguments->slots[1] = string__70_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__70_3;
}
static void cont__70_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 378: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__70_4;
}
static void cont__70_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 378: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__70_5;
}
static void cont__70_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 378: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__70_6;
}
static void cont__70_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 378: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__70_7;
}
static void cont__70_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXAMPLE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_1_create_page(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // filename: 0
  // body: 1
  // page: 2
  frame->slots[2] /* page */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 71: ... :
  // 72:   HTML:
  // 73:     HEAD:
  // 74:       STYLE "
  // 75:         body {
  // 76:           background-color: white;
  // 77:           font-family: Times New Roman, Times;
  // 78:           font-size: 12pt;
  // 79:           color: #222;
  // 80:         }
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__22_2, 0);
  // 71: collect_output $page:
  // 72:   HTML:
  // 73:     HEAD:
  // 74:       STYLE "
  // 75:         body {
  // 76:           background-color: white;
  // 77:           font-family: Times New Roman, Times;
  // 78:           font-size: 12pt;
  // 79:           color: #222;
  // 80:         }
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void entry__22_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: HEAD:
  // 74:   STYLE "
  // 75:     body {
  // 76:       background-color: white;
  // 77:       font-family: Times New Roman, Times;
  // 78:       font-size: 12pt;
  // 79:       color: #222;
  // 80:     }
  // 81:     h1 {
  // 82:       font-family: Arial, Helvetica;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__22_4;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void entry__22_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: STYLE "
  // 75:   body {
  // 76:     background-color: white;
  // 77:     font-family: Times New Roman, Times;
  // 78:     font-size: 12pt;
  // 79:     color: #222;
  // 80:   }
  // 81:   h1 {
  // 82:     font-family: Arial, Helvetica;
  // 83:     font-size: 20pt;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__22_5;
  result_count = frame->caller_result_count;
  myself = get__STYLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 153: BODY body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__BODY();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 72: ... :
  // 73:   HEAD:
  // 74:     STYLE "
  // 75:       body {
  // 76:         background-color: white;
  // 77:         font-family: Times New Roman, Times;
  // 78:         font-size: 12pt;
  // 79:         color: #222;
  // 80:       }
  // 81:       h1 {
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__22_3, 0);
  // 72: HTML:
  // 73:   HEAD:
  // 74:     STYLE "
  // 75:       body {
  // 76:         background-color: white;
  // 77:         font-family: Times New Roman, Times;
  // 78:         font-size: 12pt;
  // 79:         color: #222;
  // 80:       }
  // 81:       h1 {
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* page */, arguments->slots[0]);
  // 154: save filename page
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[2] /* page */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_1_extract_documentation_from_file(void) {
  allocate_initialized_frame_gc(2, 11);
  // slot allocations:
  // filename: 0
  // return__1: 1
  // buf: 2
  // fragments: 3
  // trees: 4
  // first_idx: 5
  // local_method_names: 6
  frame->slots[1] /* return__1 */ = create_continuation();
  frame->slots[2] /* buf */ = create_future();
  define__sim2c__module_name(create_future());
  define__sim2c__required_modules(undefined);
  define__sim2c__used_namespaces(undefined);
  define__sim2c__defined_namespaces(undefined);
  define__sim2c__namespace_mappings(undefined);
  define__sim2c__included_files(undefined);
  define__sim2c__linked_libraries(undefined);
  define__sim2c__enumeration_count(undefined);
  frame->slots[3] /* fragments */ = create_cell();
  frame->slots[4] /* trees */ = create_cell();
  frame->slots[5] /* first_idx */ = create_cell();
  frame->slots[6] /* local_method_names */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 167: ... "extracting documentation from @(filename)@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__24_2;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__24_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 167: ewrite "extracting documentation from @(filename)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 168: ... load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 168: $buf load(filename).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void cont__24_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* buf */, arguments->slots[0]);
  // 169: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__24_8;
}
static void cont__24_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 169: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_9;
}
static void cont__24_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 169: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__24_10;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_12;
}
static void entry__24_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_11;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 170: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__24_13;
}
static void cont__24_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 170: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__24_14;
}
static void cont__24_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 170: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_15;
}
static void cont__24_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 170: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__24_16;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_18;
}
static void entry__24_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_17;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 171: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__24_19;
}
static void cont__24_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 171: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__24_20;
}
static void cont__24_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 171: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_21;
}
static void cont__24_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 171: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__24_22;
}
static void cont__24_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 171: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__24_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_25;
}
static void entry__24_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 174: ... filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__24_26;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__24_27;
}
static void cont__24_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 174: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__24_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_29;
}
static void cont__24_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 173: %sim2c::module_name
  // 174:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 175:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__24_30;
}
static void cont__24_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 177: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 178: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 179: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 180: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 181: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 182: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 183: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 184: $$fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__24_31;
}
static void cont__24_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 185: update_each &fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = func__24_32;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__24_34;
}
static void entry__24_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 185: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__24_33;
}
static void cont__24_33(void) {
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
static void cont__24_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 186: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 187: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 188: ... : (-> done)
  // 189:   for_each fragments: (idx fragment)
  // 190:     case
  // 191:       source_of(fragment)(1)
  // 192:       '#':
  // 193:         !first_idx idx+1 # ignore remark
  // 194:       '<':
  // 195:         !first_idx idx+1
  // 196:         parse_meta_instruction $_tree fragment
  // 197:       :
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_35, 0);
  // 188: do: (-> done)
  // 189:   for_each fragments: (idx fragment)
  // 190:     case
  // 191:       source_of(fragment)(1)
  // 192:       '#':
  // 193:         !first_idx idx+1 # ignore remark
  // 194:       '<':
  // 195:         !first_idx idx+1
  // 196:         parse_meta_instruction $_tree fragment
  // 197:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__24_46;
}
static void entry__24_35(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // done: 0
  // fragments: 1
  // first_idx: 2
  frame->slots[0] /* done */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[3]; /* fragments */
  frame->slots[2] = myself->closure.frame->slots[5]; /* first_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: ... : (idx fragment)
  // 190:   case
  // 191:     source_of(fragment)(1)
  // 192:     '#':
  // 193:       !first_idx idx+1 # ignore remark
  // 194:     '<':
  // 195:       !first_idx idx+1
  // 196:       parse_meta_instruction $_tree fragment
  // 197:     :
  // 198:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__24_36, 2);
  // 189: for_each fragments: (idx fragment)
  // 190:   case
  // 191:     source_of(fragment)(1)
  // 192:     '#':
  // 193:       !first_idx idx+1 # ignore remark
  // 194:     '<':
  // 195:       !first_idx idx+1
  // 196:       parse_meta_instruction $_tree fragment
  // 197:     :
  // 198:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_45;
}
static void entry__24_39(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // first_idx: 0
  // idx: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 193: !first_idx idx+1 # ignore remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__24_40;
}
static void cont__24_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_41(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // first_idx: 0
  // idx: 1
  // fragment: 2
  // tree: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[1] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[2] = myself->closure.frame->slots[1]; /* fragment */
  frame->slots[3] /* tree */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__24_42;
}
static void cont__24_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 196: parse_meta_instruction $_tree fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__24_43;
}
static void cont__24_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* tree */, arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_44(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_36(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // idx: 0
  // fragment: 1
  // first_idx: 2
  // done: 3
  frame->slots[2] = myself->closure.frame->slots[2]; /* first_idx */
  frame->slots[3] = myself->closure.frame->slots[0]; /* done */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 191: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__24_37;
}
static void cont__24_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 191: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__24_38;
}
static void cont__24_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 192: ... :
  // 193:   !first_idx idx+1 # ignore remark
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_39, 0);
  // 194: ... :
  // 195:   !first_idx idx+1
  // 196:   parse_meta_instruction $_tree fragment
  frame->slots[7] /* temp__4 */ = create_closure(entry__24_41, 0);
  // 197: :
  // 198:   done
  frame->slots[8] /* temp__5 */ = create_closure(entry__24_44, 0);
  // 190: case
  // 191:   source_of(fragment)(1)
  // 192:   '#':
  // 193:     !first_idx idx+1 # ignore remark
  // 194:   '<':
  // 195:     !first_idx idx+1
  // 196:     parse_meta_instruction $_tree fragment
  // 197:   :
  // 198:     done
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__35;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = character__60;
  arguments->slots[4] = frame->slots[7] /* temp__4 */;
  arguments->slots[5] = frame->slots[8] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_45(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__24_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 199: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__24_47;
}
static void cont__24_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 199: range &fragments first_idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__24_48;
}
static void cont__24_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 200: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_49, 1);
  // 200: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_52;
}
static void entry__24_49(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 200: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__24_50;
}
static void cont__24_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 200: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__24_51;
}
static void cont__24_51(void) {
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
static void cont__24_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 201: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__24_53;
}
static void cont__24_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 201: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__24_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_57;
}
static void entry__24_54(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 201: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 201: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_55;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__24_56;
}
static void cont__24_56(void) {
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
static void cont__24_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 203: ... : (statement)
  // 204:   cond
  // 205:     -> statement.is_a_remark: pass
  // 206:     -> statement.is_c_code: pass
  // 207:     -> statement.is_an_assignment:
  // 208:       $destination output_arguments_of(statement)(1)
  // 209:       if destination.is_a_definition:
  // 210:         $identifier identifier_of(destination)
  // 211:         unless namespace_of(identifier).is_defined:
  // 212:           $source arguments_of(statement)(1)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_58, 1);
  // 203: for_each trees: (statement)
  // 204:   cond
  // 205:     -> statement.is_a_remark: pass
  // 206:     -> statement.is_c_code: pass
  // 207:     -> statement.is_an_assignment:
  // 208:       $destination output_arguments_of(statement)(1)
  // 209:       if destination.is_a_definition:
  // 210:         $identifier identifier_of(destination)
  // 211:         unless namespace_of(identifier).is_defined:
  // 212:           $source arguments_of(statement)(1)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_83;
}
static void entry__24_79(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // local_method_names: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* local_method_names */
  frame->slots[1] = myself->closure.frame->slots[2]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 214: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__24_80;
}
static void cont__24_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 214: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__24_81;
}
static void cont__24_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 214: !local_method_names(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__24_82;
}
static void cont__24_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* local_method_names */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_75(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  // destination: 2
  // source: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[2]; /* local_method_names */
  frame->slots[2] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[3] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__24_76;
}
static void cont__24_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 212: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__24_77;
}
static void cont__24_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 213: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__24_78;
}
static void cont__24_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_79, 0);
  // 213: if source.is_a_polymorphic_function_constant:
  // 214:   !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_71(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // destination: 0
  // statement: 1
  // local_method_names: 2
  // identifier: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* local_method_names */
  frame->slots[3] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 210: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__24_72;
}
static void cont__24_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 211: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_73;
}
static void cont__24_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 211: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_74;
}
static void cont__24_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 211: ... :
  // 212:   $source arguments_of(statement)(1)
  // 213:   if source.is_a_polymorphic_function_constant:
  // 214:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_75, 0);
  // 211: unless namespace_of(identifier).is_defined:
  // 212:   $source arguments_of(statement)(1)
  // 213:   if source.is_a_polymorphic_function_constant:
  // 214:     !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_67(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  // destination: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* local_method_names */
  frame->slots[2] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__24_68;
}
static void cont__24_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 208: $destination output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__24_69;
}
static void cont__24_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 209: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__24_70;
}
static void cont__24_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   $identifier identifier_of(destination)
  // 211:   unless namespace_of(identifier).is_defined:
  // 212:     $source arguments_of(statement)(1)
  // 213:     if source.is_a_polymorphic_function_constant:
  // 214:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_71, 0);
  // 209: if destination.is_a_definition:
  // 210:   $identifier identifier_of(destination)
  // 211:   unless namespace_of(identifier).is_defined:
  // 212:     $source arguments_of(statement)(1)
  // 213:     if source.is_a_polymorphic_function_constant:
  // 214:       !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_64(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 206: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_61(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__24_60;
}
static void cont__24_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 205: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__24_61;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_62(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 206: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__24_63;
}
static void cont__24_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 206: -> statement.is_c_code: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__24_64;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_65(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* local_method_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__24_66;
}
static void cont__24_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 207: ... :
  // 208:   $destination output_arguments_of(statement)(1)
  // 209:   if destination.is_a_definition:
  // 210:     $identifier identifier_of(destination)
  // 211:     unless namespace_of(identifier).is_defined:
  // 212:       $source arguments_of(statement)(1)
  // 213:       if source.is_a_polymorphic_function_constant:
  // 214:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_67, 0);
  // 207: -> statement.is_an_assignment:
  // 208:   $destination output_arguments_of(statement)(1)
  // 209:   if destination.is_a_definition:
  // 210:     $identifier identifier_of(destination)
  // 211:     unless namespace_of(identifier).is_defined:
  // 212:       $source arguments_of(statement)(1)
  // 213:       if source.is_a_polymorphic_function_constant:
  // 214:         !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_58(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 205: -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__24_59, 0);
  // 206: -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_62, 0);
  // 207: -> statement.is_an_assignment:
  // 208:   $destination output_arguments_of(statement)(1)
  // 209:   if destination.is_a_definition:
  // 210:     $identifier identifier_of(destination)
  // 211:     unless namespace_of(identifier).is_defined:
  // 212:       $source arguments_of(statement)(1)
  // 213:       if source.is_a_polymorphic_function_constant:
  // 214:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_65, 0);
  // 204: cond
  // 205:   -> statement.is_a_remark: pass
  // 206:   -> statement.is_c_code: pass
  // 207:   -> statement.is_an_assignment:
  // 208:     $destination output_arguments_of(statement)(1)
  // 209:     if destination.is_a_definition:
  // 210:       $identifier identifier_of(destination)
  // 211:       unless namespace_of(identifier).is_defined:
  // 212:         $source arguments_of(statement)(1)
  // 213:         if source.is_a_polymorphic_function_constant:
  // ...
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
static void cont__24_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 215: ... :
  // 216:   (
  // 217:     statement
  // 218:     -> break
  // 219:   )
  // 220:   cond
  // 221:     -> statement.is_a_remark: pass
  // 222:     -> statement.is_c_code:
  // 223:       $identifier identifier_of(statement)
  // 224:       if identifier.is_defined:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_84, 1);
  // 215: for_each trees:
  // 216:   (
  // 217:     statement
  // 218:     -> break
  // 219:   )
  // 220:   cond
  // 221:     -> statement.is_a_remark: pass
  // 222:     -> statement.is_c_code:
  // 223:       $identifier identifier_of(statement)
  // 224:       if identifier.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_210;
}
static void entry__24_84(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // statement: 0
  // break: 1
  // filename: 2
  // local_method_names: 3
  frame->slots[1] /* break */ = create_continuation();
  frame->slots[2] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[3] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 221: -> statement.is_a_remark: pass
  frame->slots[4] /* temp__1 */ = create_closure(entry__24_85, 0);
  // 222: -> statement.is_c_code:
  // 223:   $identifier identifier_of(statement)
  // 224:   if identifier.is_defined:
  // 225:     $namespace namespace_of(identifier)
  // 226:     if namespace.is_defined:
  // 227:       $name name_of(identifier)
  // 228:       case kind_of(statement)
  // 229:         "type":
  // 230:           if namespace.is_defined:
  // 231:             $base base_of(statement)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_88, 0);
  // 246: -> statement.is_an_assignment:
  // 247:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 248:   $$info symbol_info(.filename_of filename)
  // 249:   if
  // 250:     destination.is_a_definition:
  // 251:       $identifier identifier_of(destination)
  // 252:       $namespace namespace_of(identifier)
  // 253:       if namespace.is_defined:
  // 254:         $name name_of(identifier)
  // 255:         $iname ordered_name(namespace name)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_119, 0);
  // 220: cond
  // 221:   -> statement.is_a_remark: pass
  // 222:   -> statement.is_c_code:
  // 223:     $identifier identifier_of(statement)
  // 224:     if identifier.is_defined:
  // 225:       $namespace namespace_of(identifier)
  // 226:       if namespace.is_defined:
  // 227:         $name name_of(identifier)
  // 228:         case kind_of(statement)
  // 229:           "type":
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__24_209;
}
static void entry__24_199(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // attr: 0
  // iname: 1
  // attr_name: 2
  // info: 3
  // definition: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[4]; /* attr_name */
  frame->slots[3] = myself->closure.frame->slots[3]; /* info */
  frame->slots[4] /* definition */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 312: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_200;
}
static void cont__24_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 312: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_201;
}
static void cont__24_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 312: ... :
  // 313:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__24_202, 0);
  // 312: unless namespace_of(attr).is_defined:
  // 313:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__24_203;
}
static void entry__24_202(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: !attr.used_namespaces_of used_namespaces
  frame->slots[1] /* temp__1 */ = get__used_namespaces();
  // 313: !attr.used_namespaces_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* attr */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_namespaces_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* attr */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_203(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 314: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_204;
}
static void cont__24_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 314: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__24_205;
}
static void cont__24_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 315: !definition.kind_of INLINE_C_TYPE
  frame->slots[5] /* temp__1 */ = var._INLINE_C_TYPE;
  // 315: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 316: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 316: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__24_206;
}
static void cont__24_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 316: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__24_207;
}
static void cont__24_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 316: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 317: !definitions(iname) definition
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* definition */;
  // 317: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_208;
}
static void cont__24_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_196(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // attr: 0
  // local_method_names: 1
  // iname: 2
  // info: 3
  // attr_name: 4
  frame->slots[0] = myself->closure.frame->slots[4]; /* attr */
  frame->slots[1] = myself->closure.frame->slots[2]; /* local_method_names */
  frame->slots[2] = myself->closure.frame->slots[1]; /* iname */
  frame->slots[3] = myself->closure.frame->slots[3]; /* info */
  frame->slots[4] /* attr_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 310: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_197;
}
static void cont__24_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 311: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__24_198;
}
static void cont__24_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 311: ... :
  // 312:   unless namespace_of(attr).is_defined:
  // 313:     !attr.used_namespaces_of used_namespaces
  // 314:   $$definition default_value(definitions(iname) symbol_info)
  // 315:   !definition.kind_of INLINE_C_TYPE
  // 316:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 317:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_199, 0);
  // 311: unless local_method_names(attr_name):
  // 312:   unless namespace_of(attr).is_defined:
  // 313:     !attr.used_namespaces_of used_namespaces
  // 314:   $$definition default_value(definitions(iname) symbol_info)
  // 315:   !definition.kind_of INLINE_C_TYPE
  // 316:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 317:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_190(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // destination: 0
  // iname: 1
  // local_method_names: 2
  // info: 3
  // attr: 4
  // type: 5
  frame->slots[0] = myself->closure.frame->slots[3]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[6]; /* local_method_names */
  frame->slots[3] = myself->closure.frame->slots[2]; /* info */
  frame->slots[4] /* attr */ = create_cell();
  frame->slots[5] /* type */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 303: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__24_191;
}
static void cont__24_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 306: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_192;
}
static void cont__24_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 306: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__24_193;
}
static void cont__24_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 305: $type
  // 306:   default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 308: !definitions(iname) type
  frame->slots[6] /* temp__1 */ = frame->slots[5] /* type */;
  // 308: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_194;
}
static void cont__24_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 309: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_195;
}
static void cont__24_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 309: ... :
  // 310:   $attr_name attr.to_string
  // 311:   unless local_method_names(attr_name):
  // 312:     unless namespace_of(attr).is_defined:
  // 313:       !attr.used_namespaces_of used_namespaces
  // 314:     $$definition default_value(definitions(iname) symbol_info)
  // 315:     !definition.kind_of INLINE_C_TYPE
  // 316:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 317:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_196, 0);
  // 309: if attr.is_defined:
  // 310:   $attr_name attr.to_string
  // 311:   unless local_method_names(attr_name):
  // 312:     unless namespace_of(attr).is_defined:
  // 313:       !attr.used_namespaces_of used_namespaces
  // 314:     $$definition default_value(definitions(iname) symbol_info)
  // 315:     !definition.kind_of INLINE_C_TYPE
  // 316:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 317:     !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_129(void) {
  allocate_initialized_frame_gc(7, 16);
  // slot allocations:
  // identifier: 0
  // namespace: 1
  // info: 2
  // destination: 3
  // statement: 4
  // break: 5
  // local_method_names: 6
  // name: 7
  // iname: 8
  // source: 9
  frame->slots[0] = myself->closure.frame->slots[5]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[6]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[4] = myself->closure.frame->slots[2]; /* statement */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  frame->slots[6] = myself->closure.frame->slots[4]; /* local_method_names */
  frame->slots[7] /* name */ = create_future();
  frame->slots[8] /* iname */ = create_future();
  frame->slots[9] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__24_130;
}
static void cont__24_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* name */, arguments->slots[0]);
  // 255: $iname ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[7] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__24_131;
}
static void cont__24_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* iname */, arguments->slots[0]);
  // 257: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_132;
}
static void cont__24_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 258: ... variable_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__24_133;
}
static void cont__24_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 259: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_134;
}
static void cont__24_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 256: !info
  // 257:   .name_of identifier.to_string
  // 258:   .variable_kind_of variable_kind_of(destination)
  // 259:   .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[10] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, frame->slots[11] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[12] /* temp__3 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 260: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__24_135;
}
static void cont__24_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 260: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__24_136;
}
static void cont__24_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* source */, arguments->slots[0]);
  // 262: -> source.is_a_polymorphic_function_constant:
  // 263:   !polymorphic_functions(name namespace) true
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_setter
  // 269:           -> POLYMORPHIC_ATTRIBUTE
  // 270:           -> POLYMORPHIC_FUNCTION
  // 271:   break
  frame->slots[10] /* temp__1 */ = create_closure(entry__24_137, 0);
  // 272: -> source.is_a_body:
  // 273:   !info
  // 274:     .base_of "types::function"
  // 275:     .kind_of FUNCTION
  // 276:     .parameters_of parameters_of(source)
  // 277:     .remark_lines_of
  // 278:       if
  // 279:         remark_lines_of(statement).is_empty
  // 280:         -> remark_lines_of(source)
  // 281:         -> remark_lines_of(statement)
  frame->slots[11] /* temp__2 */ = create_closure(entry__24_146, 0);
  // 282: -> source.is_a_c_body:
  // 283:   !info.kind_of INLINE_C_FUNCTION
  frame->slots[12] /* temp__3 */ = create_closure(entry__24_158, 0);
  // 284: -> source.is_an_identifier:
  // 285:   if namespace_of(source).is_defined:
  // 286:     !info.base_of source.to_string
  frame->slots[13] /* temp__4 */ = create_closure(entry__24_161, 0);
  // 287: -> source.is_a_unique_item_constant:
  // 288:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 289:   break
  frame->slots[14] /* temp__5 */ = create_closure(entry__24_168, 0);
  // 290: -> source.is_a_constant:
  // 291:   !info.kind_of CONSTANT
  frame->slots[15] /* temp__6 */ = create_closure(entry__24_172, 0);
  // 261: cond
  // 262:   -> source.is_a_polymorphic_function_constant:
  // 263:     !polymorphic_functions(name namespace) true
  // 264:     !definitions(iname)
  // 265:       info
  // 266:         .kind_of
  // 267:           if
  // 268:             source.is_a_setter
  // 269:             -> POLYMORPHIC_ATTRIBUTE
  // 270:             -> POLYMORPHIC_FUNCTION
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  arguments->slots[2] = frame->slots[12] /* temp__3 */;
  arguments->slots[3] = frame->slots[13] /* temp__4 */;
  arguments->slots[4] = frame->slots[14] /* temp__5 */;
  arguments->slots[5] = frame->slots[15] /* temp__6 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__24_175;
}
static void entry__24_174(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 291: !info.kind_of CONSTANT
  frame->slots[1] /* temp__1 */ = var._CONSTANT;
  // 291: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_170(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // iname: 0
  // info: 1
  // break: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* iname */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[3]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 288: !definitions(iname) info(.kind_of UNIQUE_ITEM)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._UNIQUE_ITEM);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 288: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_171;
}
static void cont__24_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 289: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_166(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // info: 0
  // source: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 286: !info.base_of source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_167;
}
static void cont__24_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 286: !info.base_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_163(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_164;
}
static void cont__24_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 285: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_165;
}
static void cont__24_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 285: ... :
  // 286:   !info.base_of source.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_166, 0);
  // 285: if namespace_of(source).is_defined:
  // 286:   !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_160(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 283: !info.kind_of INLINE_C_FUNCTION
  frame->slots[1] /* temp__1 */ = var._INLINE_C_FUNCTION;
  // 283: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[1] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_148(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // info: 0
  // source: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* source */
  frame->slots[2] = myself->closure.frame->slots[2]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 276: ... parameters_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__24_149;
}
static void cont__24_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 279: remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_150;
}
static void cont__24_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 279: remark_lines_of(statement).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__24_151;
}
static void cont__24_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 280: -> remark_lines_of(source)
  frame->slots[7] /* temp__5 */ = create_closure(entry__24_152, 0);
  // 281: -> remark_lines_of(statement)
  frame->slots[8] /* temp__6 */ = create_closure(entry__24_154, 0);
  // 278: if
  // 279:   remark_lines_of(statement).is_empty
  // 280:   -> remark_lines_of(source)
  // 281:   -> remark_lines_of(statement)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_156;
}
static void entry__24_152(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 280: ... remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_153;
}
static void cont__24_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 280: -> remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_154(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 281: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_155;
}
static void cont__24_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 281: -> remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 273: !info
  // 274:   .base_of "types::function"
  // 275:   .kind_of FUNCTION
  // 276:   .parameters_of parameters_of(source)
  // 277:   .remark_lines_of
  // 278:     if
  // 279:       remark_lines_of(statement).is_empty
  // 280:       -> remark_lines_of(source)
  // 281:       -> remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, string__24_157);
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._FUNCTION);
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[3] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_139(void) {
  allocate_initialized_frame_gc(6, 9);
  // slot allocations:
  // name: 0
  // namespace: 1
  // iname: 2
  // info: 3
  // source: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[3]; /* iname */
  frame->slots[3] = myself->closure.frame->slots[4]; /* info */
  frame->slots[4] = myself->closure.frame->slots[0]; /* source */
  frame->slots[5] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 263: !polymorphic_functions(name namespace) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 263: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__24_140;
}
static void cont__24_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 268: source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__24_141;
}
static void cont__24_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 267: if
  // 268:   source.is_a_setter
  // 269:   -> POLYMORPHIC_ATTRIBUTE
  // 270:   -> POLYMORPHIC_FUNCTION
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = func__24_142;
  arguments->slots[2] = func__24_143;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_144;
}
static void entry__24_142(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 269: -> POLYMORPHIC_ATTRIBUTE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_ATTRIBUTE;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_143(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 270: -> POLYMORPHIC_FUNCTION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 264: !definitions(iname)
  // 265:   info
  // 266:     .kind_of
  // 267:       if
  // 268:         source.is_a_setter
  // 269:         -> POLYMORPHIC_ATTRIBUTE
  // 270:         -> POLYMORPHIC_FUNCTION
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[6] /* temp__1 */);
    frame->slots[8] /* temp__3 */ = temp;

  }
  // 264: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_145;
}
static void cont__24_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 271: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_137(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // source: 0
  // name: 1
  // namespace: 2
  // iname: 3
  // info: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[7]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[4] = myself->closure.frame->slots[2]; /* info */
  frame->slots[5] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 262: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__24_138;
}
static void cont__24_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 262: ... :
  // 263:   !polymorphic_functions(name namespace) true
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_setter
  // 269:           -> POLYMORPHIC_ATTRIBUTE
  // 270:           -> POLYMORPHIC_FUNCTION
  // 271:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_139, 0);
  // 262: -> source.is_a_polymorphic_function_constant:
  // 263:   !polymorphic_functions(name namespace) true
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_setter
  // 269:           -> POLYMORPHIC_ATTRIBUTE
  // 270:           -> POLYMORPHIC_FUNCTION
  // 271:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_146(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // info: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[4]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__24_147;
}
static void cont__24_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 272: ... :
  // 273:   !info
  // 274:     .base_of "types::function"
  // 275:     .kind_of FUNCTION
  // 276:     .parameters_of parameters_of(source)
  // 277:     .remark_lines_of
  // 278:       if
  // 279:         remark_lines_of(statement).is_empty
  // 280:         -> remark_lines_of(source)
  // 281:         -> remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_148, 0);
  // 272: -> source.is_a_body:
  // 273:   !info
  // 274:     .base_of "types::function"
  // 275:     .kind_of FUNCTION
  // 276:     .parameters_of parameters_of(source)
  // 277:     .remark_lines_of
  // 278:       if
  // 279:         remark_lines_of(statement).is_empty
  // 280:         -> remark_lines_of(source)
  // 281:         -> remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_158(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 282: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__24_159;
}
static void cont__24_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 282: ... :
  // 283:   !info.kind_of INLINE_C_FUNCTION
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_160, 0);
  // 282: -> source.is_a_c_body:
  // 283:   !info.kind_of INLINE_C_FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_161(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__24_162;
}
static void cont__24_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 284: ... :
  // 285:   if namespace_of(source).is_defined:
  // 286:     !info.base_of source.to_string
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_163, 0);
  // 284: -> source.is_an_identifier:
  // 285:   if namespace_of(source).is_defined:
  // 286:     !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_168(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // source: 0
  // iname: 1
  // info: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[2]; /* info */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 287: ... source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__24_169;
}
static void cont__24_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 287: ... :
  // 288:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 289:   break
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_170, 0);
  // 287: -> source.is_a_unique_item_constant:
  // 288:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 289:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_172(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 290: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__24_173;
}
static void cont__24_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 290: ... :
  // 291:   !info.kind_of CONSTANT
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_174, 0);
  // 290: -> source.is_a_constant:
  // 291:   !info.kind_of CONSTANT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_175(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 293: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__24_176;
}
static void cont__24_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 294: ... :
  // 295:   $previous_definition definitions(iname)
  // 296:   if previous_definition.is_defined:
  // 297:     if kind_of(previous_definition) == INLINE_C_TYPE:
  // 298:       !info.types_of types_of(previous_definition)
  // 299:       !info.derived_types_of derived_types_of(previous_definition)
  // 300:       !info.methods_of methods_of(previous_definition)
  // 301:   !definitions(iname) info
  frame->slots[11] /* temp__2 */ = create_closure(entry__24_177, 0);
  // 302: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__24_189;
}
static void entry__24_177(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // iname: 0
  // info: 1
  // previous_definition: 2
  frame->slots[0] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] /* previous_definition */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 295: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_178;
}
static void cont__24_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 296: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_179;
}
static void cont__24_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 296: ... :
  // 297:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 298:     !info.types_of types_of(previous_definition)
  // 299:     !info.derived_types_of derived_types_of(previous_definition)
  // 300:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_180, 0);
  // 296: if previous_definition.is_defined:
  // 297:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 298:     !info.types_of types_of(previous_definition)
  // 299:     !info.derived_types_of derived_types_of(previous_definition)
  // 300:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_187;
}
static void entry__24_183(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // info: 0
  // previous_definition: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* previous_definition */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 298: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__24_184;
}
static void cont__24_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 298: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 299: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__24_185;
}
static void cont__24_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 300: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__24_186;
}
static void cont__24_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 300: !info.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_180(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // previous_definition: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* previous_definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__24_181;
}
static void cont__24_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 297: ... kind_of(previous_definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_182;
}
static void cont__24_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 297: ... :
  // 298:   !info.types_of types_of(previous_definition)
  // 299:   !info.derived_types_of derived_types_of(previous_definition)
  // 300:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_183, 0);
  // 297: if kind_of(previous_definition) == INLINE_C_TYPE:
  // 298:   !info.types_of types_of(previous_definition)
  // 299:   !info.derived_types_of derived_types_of(previous_definition)
  // 300:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_187(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 301: !definitions(iname) info
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* info */;
  // 301: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_188;
}
static void cont__24_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 302: ... :
  // 303:   $$attr attribute_of(destination)
  // 304:   
  // 305:   $type
  // 306:     default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  // 307:   
  // 308:   !definitions(iname) type
  // 309:   if attr.is_defined:
  // 310:     $attr_name attr.to_string
  // 311:     unless local_method_names(attr_name):
  // ...
  frame->slots[13] /* temp__4 */ = create_closure(entry__24_190, 0);
  // 292: case
  // 293:   attribute_kind_of(destination)
  // 294:   NONE:
  // 295:     $previous_definition definitions(iname)
  // 296:     if previous_definition.is_defined:
  // 297:       if kind_of(previous_definition) == INLINE_C_TYPE:
  // 298:         !info.types_of types_of(previous_definition)
  // 299:         !info.derived_types_of derived_types_of(previous_definition)
  // 300:         !info.methods_of methods_of(previous_definition)
  // 301:     !definitions(iname) info
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = get__NONE();
  arguments->slots[2] = frame->slots[11] /* temp__2 */;
  arguments->slots[3] = frame->slots[12] /* temp__3 */;
  arguments->slots[4] = frame->slots[13] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_125(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // destination: 0
  // info: 1
  // statement: 2
  // break: 3
  // local_method_names: 4
  // identifier: 5
  // namespace: 6
  frame->slots[0] = myself->closure.frame->slots[4]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[5]; /* info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[3] = myself->closure.frame->slots[2]; /* break */
  frame->slots[4] = myself->closure.frame->slots[3]; /* local_method_names */
  frame->slots[5] /* identifier */ = create_future();
  frame->slots[6] /* namespace */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 251: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__24_126;
}
static void cont__24_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* identifier */, arguments->slots[0]);
  // 252: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_127;
}
static void cont__24_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* namespace */, arguments->slots[0]);
  // 253: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_128;
}
static void cont__24_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 253: ... :
  // 254:   $name name_of(identifier)
  // 255:   $iname ordered_name(namespace name)
  // 256:   !info
  // 257:     .name_of identifier.to_string
  // 258:     .variable_kind_of variable_kind_of(destination)
  // 259:     .remark_lines_of remark_lines_of(statement)
  // 260:   $source arguments_of(statement)(1)
  // 261:   cond
  // 262:     -> source.is_a_polymorphic_function_constant:
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__24_129, 0);
  // 253: if namespace.is_defined:
  // 254:   $name name_of(identifier)
  // 255:   $iname ordered_name(namespace name)
  // 256:   !info
  // 257:     .name_of identifier.to_string
  // 258:     .variable_kind_of variable_kind_of(destination)
  // 259:     .remark_lines_of remark_lines_of(statement)
  // 260:   $source arguments_of(statement)(1)
  // 261:   cond
  // 262:     -> source.is_a_polymorphic_function_constant:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_121(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // statement: 0
  // filename: 1
  // break: 2
  // local_method_names: 3
  // destination: 4
  // info: 5
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[2] = myself->closure.frame->slots[2]; /* break */
  frame->slots[3] = myself->closure.frame->slots[3]; /* local_method_names */
  frame->slots[4] /* destination */ = create_future();
  frame->slots[5] /* info */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__24_122;
}
static void cont__24_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 247: ... output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__24_123;
}
static void cont__24_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 247: $destination output_arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 248: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 250: destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__24_124;
}
static void cont__24_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 250: ... :
  // 251:   $identifier identifier_of(destination)
  // 252:   $namespace namespace_of(identifier)
  // 253:   if namespace.is_defined:
  // 254:     $name name_of(identifier)
  // 255:     $iname ordered_name(namespace name)
  // 256:     !info
  // 257:       .name_of identifier.to_string
  // 258:       .variable_kind_of variable_kind_of(destination)
  // 259:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_125, 0);
  // 249: if
  // 250:   destination.is_a_definition:
  // 251:     $identifier identifier_of(destination)
  // 252:     $namespace namespace_of(identifier)
  // 253:     if namespace.is_defined:
  // 254:       $name name_of(identifier)
  // 255:       $iname ordered_name(namespace name)
  // 256:       !info
  // 257:         .name_of identifier.to_string
  // 258:         .variable_kind_of variable_kind_of(destination)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_101(void) {
  allocate_initialized_frame_gc(5, 13);
  // slot allocations:
  // statement: 0
  // namespace: 1
  // name: 2
  // identifier: 3
  // filename: 4
  // base: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[0]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[2]; /* name */
  frame->slots[3] = myself->closure.frame->slots[3]; /* identifier */
  frame->slots[4] = myself->closure.frame->slots[4]; /* filename */
  frame->slots[5] /* base */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 231: $base base_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__24_102;
}
static void cont__24_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* base */, arguments->slots[0]);
  // 235: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_103;
}
static void cont__24_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 236: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_104;
}
static void cont__24_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 236: ... -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__24_105, 0);
  // 236: ... if(base.is_defined (-> base.to_string) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = func__24_107;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_108;
}
static void entry__24_105(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* base */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: ... base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_106;
}
static void cont__24_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 236: ... -> base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_107(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 237: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_109;
}
static void cont__24_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 232: !definitions(ordered_name(namespace name))
  // 233:   symbol_info
  // 234:     .kind_of INLINE_C_TYPE
  // 235:     .name_of identifier.to_string
  // 236:     .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 237:     .remark_lines_of remark_lines_of(statement)
  // 238:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[6] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[10] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[4] /* filename */);
    frame->slots[11] /* temp__6 */ = temp;

  }
  // 232: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[2] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__24_110;
}
static void cont__24_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 232: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[11] /* temp__6 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_111;
}
static void cont__24_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_99(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // namespace: 0
  // statement: 1
  // name: 2
  // identifier: 3
  // filename: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[1]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[4]; /* name */
  frame->slots[3] = myself->closure.frame->slots[0]; /* identifier */
  frame->slots[4] = myself->closure.frame->slots[3]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 230: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_100;
}
static void cont__24_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 230: ... :
  // 231:   $base base_of(statement)
  // 232:   !definitions(ordered_name(namespace name))
  // 233:     symbol_info
  // 234:       .kind_of INLINE_C_TYPE
  // 235:       .name_of identifier.to_string
  // 236:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 237:       .remark_lines_of remark_lines_of(statement)
  // 238:       .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_101, 0);
  // 230: if namespace.is_defined:
  // 231:   $base base_of(statement)
  // 232:   !definitions(ordered_name(namespace name))
  // 233:     symbol_info
  // 234:       .kind_of INLINE_C_TYPE
  // 235:       .name_of identifier.to_string
  // 236:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 237:       .remark_lines_of remark_lines_of(statement)
  // 238:       .filename_of filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_112(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // namespace: 0
  // name: 1
  // identifier: 2
  // statement: 3
  // filename: 4
  frame->slots[0] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[4]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* identifier */
  frame->slots[3] = myself->closure.frame->slots[1]; /* statement */
  frame->slots[4] = myself->closure.frame->slots[3]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_113;
}
static void cont__24_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 244: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_114;
}
static void cont__24_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 240: !definitions(ordered_name(namespace name))
  // 241:   symbol_info
  // 242:     .kind_of INLINE_C_OBJECT
  // 243:     .name_of identifier.to_string
  // 244:     .remark_lines_of remark_lines_of(statement)
  // 245:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_OBJECT);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[4] /* filename */);
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 240: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__24_115;
}
static void cont__24_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 240: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_116;
}
static void cont__24_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_96(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // identifier: 0
  // statement: 1
  // namespace: 2
  // filename: 3
  // name: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[1]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[3]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[2]; /* filename */
  frame->slots[4] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 227: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__24_97;
}
static void cont__24_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 228: ... kind_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__24_98;
}
static void cont__24_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 229: ... :
  // 230:   if namespace.is_defined:
  // 231:     $base base_of(statement)
  // 232:     !definitions(ordered_name(namespace name))
  // 233:       symbol_info
  // 234:         .kind_of INLINE_C_TYPE
  // 235:         .name_of identifier.to_string
  // 236:         .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 237:         .remark_lines_of remark_lines_of(statement)
  // 238:         .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_99, 0);
  // 239: ... :
  // 240:   !definitions(ordered_name(namespace name))
  // 241:     symbol_info
  // 242:       .kind_of INLINE_C_OBJECT
  // 243:       .name_of identifier.to_string
  // 244:       .remark_lines_of remark_lines_of(statement)
  // 245:       .filename_of filename
  frame->slots[7] /* temp__3 */ = create_closure(entry__24_112, 0);
  // 228: case kind_of(statement)
  // 229:   "type":
  // 230:     if namespace.is_defined:
  // 231:       $base base_of(statement)
  // 232:       !definitions(ordered_name(namespace name))
  // 233:         symbol_info
  // 234:           .kind_of INLINE_C_TYPE
  // 235:           .name_of identifier.to_string
  // 236:           .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 237:           .remark_lines_of remark_lines_of(statement)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__24_117;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = string__24_118;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_93(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // identifier: 0
  // statement: 1
  // filename: 2
  // namespace: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[3] /* namespace */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_94;
}
static void cont__24_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 226: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_95;
}
static void cont__24_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 226: ... :
  // 227:   $name name_of(identifier)
  // 228:   case kind_of(statement)
  // 229:     "type":
  // 230:       if namespace.is_defined:
  // 231:         $base base_of(statement)
  // 232:         !definitions(ordered_name(namespace name))
  // 233:           symbol_info
  // 234:             .kind_of INLINE_C_TYPE
  // 235:             .name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_96, 0);
  // 226: if namespace.is_defined:
  // 227:   $name name_of(identifier)
  // 228:   case kind_of(statement)
  // 229:     "type":
  // 230:       if namespace.is_defined:
  // 231:         $base base_of(statement)
  // 232:         !definitions(ordered_name(namespace name))
  // 233:           symbol_info
  // 234:             .kind_of INLINE_C_TYPE
  // 235:             .name_of identifier.to_string
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
static void entry__24_90(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // filename: 1
  // identifier: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[2] /* identifier */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: $identifier identifier_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__24_91;
}
static void cont__24_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 224: ... identifier.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_92;
}
static void cont__24_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 224: ... :
  // 225:   $namespace namespace_of(identifier)
  // 226:   if namespace.is_defined:
  // 227:     $name name_of(identifier)
  // 228:     case kind_of(statement)
  // 229:       "type":
  // 230:         if namespace.is_defined:
  // 231:           $base base_of(statement)
  // 232:           !definitions(ordered_name(namespace name))
  // 233:             symbol_info
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_93, 0);
  // 224: if identifier.is_defined:
  // 225:   $namespace namespace_of(identifier)
  // 226:   if namespace.is_defined:
  // 227:     $name name_of(identifier)
  // 228:     case kind_of(statement)
  // 229:       "type":
  // 230:         if namespace.is_defined:
  // 231:           $base base_of(statement)
  // 232:           !definitions(ordered_name(namespace name))
  // 233:             symbol_info
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
static void entry__24_87(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_85(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 221: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__24_86;
}
static void cont__24_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 221: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__24_87;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_88(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // statement: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__24_89;
}
static void cont__24_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 222: ... :
  // 223:   $identifier identifier_of(statement)
  // 224:   if identifier.is_defined:
  // 225:     $namespace namespace_of(identifier)
  // 226:     if namespace.is_defined:
  // 227:       $name name_of(identifier)
  // 228:       case kind_of(statement)
  // 229:         "type":
  // 230:           if namespace.is_defined:
  // 231:             $base base_of(statement)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_90, 0);
  // 222: -> statement.is_c_code:
  // 223:   $identifier identifier_of(statement)
  // 224:   if identifier.is_defined:
  // 225:     $namespace namespace_of(identifier)
  // 226:     if namespace.is_defined:
  // 227:       $name name_of(identifier)
  // 228:       case kind_of(statement)
  // 229:         "type":
  // 230:           if namespace.is_defined:
  // 231:             $base base_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_119(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // statement: 0
  // filename: 1
  // break: 2
  // local_method_names: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[2]; /* filename */
  frame->slots[2] = myself->closure.frame->slots[1]; /* break */
  frame->slots[3] = myself->closure.frame->slots[3]; /* local_method_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 246: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__24_120;
}
static void cont__24_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 246: ... :
  // 247:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 248:   $$info symbol_info(.filename_of filename)
  // 249:   if
  // 250:     destination.is_a_definition:
  // 251:       $identifier identifier_of(destination)
  // 252:       $namespace namespace_of(identifier)
  // 253:       if namespace.is_defined:
  // 254:         $name name_of(identifier)
  // 255:         $iname ordered_name(namespace name)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_121, 0);
  // 246: -> statement.is_an_assignment:
  // 247:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 248:   $$info symbol_info(.filename_of filename)
  // 249:   if
  // 250:     destination.is_a_definition:
  // 251:       $identifier identifier_of(destination)
  // 252:       $namespace namespace_of(identifier)
  // 253:       if namespace.is_defined:
  // 254:         $name name_of(identifier)
  // 255:         $iname ordered_name(namespace name)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_209(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__24_210(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 324: ... extract_documentation_from_file name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 323: ... extract_documentation_from_directory name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_6(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* entry */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
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
  frame->cont = cont__25_7;
}
static void cont__25_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 323: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_8, 0);
  // 323: -> entry.is_a_directory: extract_documentation_from_directory name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 324: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__24_26;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void cont__25_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 324: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_11, 0);
  // 324: -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 321: $name fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 323: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__25_6, 0);
  // 324: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_9, 0);
  // 322: cond
  // 323:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 324:   -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_1_extract_documentation_from_directory(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 320: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 320: ... directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__25_3;
}
static void cont__25_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 320: for_each directory(--SORT path): (entry)
  // 321:   $name fullname_of(entry)
  // 322:   cond
  // 323:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 324:     -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__25_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: ... attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__26_6;
}
static void cont__26_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 328: ... -> attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_7(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // attr: 0
  // name: 1
  // resolved_namespace: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] /* resolved_namespace */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 329: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 330: ... used_namespaces_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = var._used_namespaces_of;
  func = myself->type;
  frame->cont = cont__26_8;
}
static void cont__26_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 330: ... : (namespace)
  // 331:   if polymorphic_functions(name namespace):
  // 332:     if resolved_namespace.is_defined:
  // 333:       Error "
  // 334:         The attribute "@(name)" cannot be uniquely resolved!
  // 335:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_9, 1);
  // 330: for_each used_namespaces_of(attr): (namespace)
  // 331:   if polymorphic_functions(name namespace):
  // 332:     if resolved_namespace.is_defined:
  // 333:       Error "
  // 334:         The attribute "@(name)" cannot be uniquely resolved!
  // 335:     !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__26_18;
}
static void entry__26_11(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // resolved_namespace: 0
  // name: 1
  // namespace: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* resolved_namespace */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 332: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_12;
}
static void cont__26_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 332: ... :
  // 333:   Error "
  // 334:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_13, 0);
  // 332: if resolved_namespace.is_defined:
  // 333:   Error "
  // 334:     The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__26_17;
}
static void entry__26_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... "
  // 334:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__26_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__26_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__26_16;
}
static void cont__26_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 333: Error "
  // 334:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: !resolved_namespace namespace
  ((CELL *)frame->slots[0])->contents /* resolved_namespace */ = frame->slots[2] /* namespace */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_9(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  // resolved_namespace: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* resolved_namespace */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 331: ... polymorphic_functions(name namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__26_10;
}
static void cont__26_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 331: ... :
  // 332:   if resolved_namespace.is_defined:
  // 333:     Error "
  // 334:       The attribute "@(name)" cannot be uniquely resolved!
  // 335:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_11, 0);
  // 331: if polymorphic_functions(name namespace):
  // 332:   if resolved_namespace.is_defined:
  // 333:     Error "
  // 334:       The attribute "@(name)" cannot be uniquely resolved!
  // 335:   !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 336: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_19;
}
static void cont__26_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 336: ... :
  // 337:   Error "
  // 338:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_20, 0);
  // 336: unless resolved_namespace.is_defined:
  // 337:   Error "
  // 338:     The attribute "@(name)" cannot be resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__26_23;
}
static void entry__26_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 337: ... "
  // 338:   The attribute "@(name)" cannot be resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__26_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__26_21;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__26_22;
}
static void cont__26_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 337: Error "
  // 338:   The attribute "@(name)" cannot be resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__26_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__26_24;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__26_25;
}
static void cont__26_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: -> string(resolved_namespace "::" name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_1_resolved_name(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // attr: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 327: $name name_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 328: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__26_3;
}
static void cont__26_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 328: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__26_4;
}
static void cont__26_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 328: ... -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__26_5, 0);
  // 328: ... :
  // 329:   $$resolved_namespace undefined
  // 330:   for_each used_namespaces_of(attr): (namespace)
  // 331:     if polymorphic_functions(name namespace):
  // 332:       if resolved_namespace.is_defined:
  // 333:         Error "
  // 334:           The attribute "@(name)" cannot be uniquely resolved!
  // 335:       !resolved_namespace namespace
  // 336:   unless resolved_namespace.is_defined:
  // 337:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__26_7, 0);
  // 328: if namespace_of(attr).is_defined (-> attr.to_string):
  // 329:   $$resolved_namespace undefined
  // 330:   for_each used_namespaces_of(attr): (namespace)
  // 331:     if polymorphic_functions(name namespace):
  // 332:       if resolved_namespace.is_defined:
  // 333:         Error "
  // 334:           The attribute "@(name)" cannot be uniquely resolved!
  // 335:       !resolved_namespace namespace
  // 336:   unless resolved_namespace.is_defined:
  // 337:     Error "
  // ...
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
static void entry__27_7(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // definition: 0
  // name: 1
  // ibase: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* ibase */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 345: !definition.derived_types_of(name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 345: ... definition.derived_types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__27_8;
}
static void cont__27_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 345: !definition.derived_types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__27_9;
}
static void cont__27_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 345: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 346: ... kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__27_10;
}
static void cont__27_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 346: ... kind_of(definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__27_11;
}
static void cont__27_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 346: ... :
  // 347:   !definition.kind_of INLINE_C_TYPE
  // 348:   $base_of_base base_of(definition)
  // 349:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__27_12, 0);
  // 346: unless kind_of(definition) == INLINE_C_TYPE:
  // 347:   !definition.kind_of INLINE_C_TYPE
  // 348:   $base_of_base base_of(definition)
  // 349:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__27_16;
}
static void entry__27_15(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // base_of_base: 0
  // ibase: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* base_of_base */
  frame->slots[1] = myself->closure.frame->slots[1]; /* ibase */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 349: ... add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base_of_base */;
  arguments->slots[1] = frame->slots[1] /* ibase */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_12(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // definition: 0
  // ibase: 1
  // base_of_base: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* definition */
  frame->slots[1] = myself->closure.frame->slots[2]; /* ibase */
  frame->slots[2] /* base_of_base */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: !definition.kind_of INLINE_C_TYPE
  frame->slots[3] /* temp__1 */ = var._INLINE_C_TYPE;
  // 347: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 348: $base_of_base base_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__27_13;
}
static void cont__27_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base_of_base */, arguments->slots[0]);
  // 349: ... base_of_base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base_of_base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_14;
}
static void cont__27_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 349: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_15, 0);
  // 349: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 350: !definitions(ibase) definition
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* definition */;
  // 350: !definitions(ibase)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__27_17;
}
static void cont__27_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_add_derived_type(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // base: 0
  // name: 1
  // ibase: 2
  // definition: 3
  frame->slots[2] /* ibase */ = create_future();
  frame->slots[3] /* definition */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 342: ... base .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 342: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 342: $ibase ordered_name(base .before. "::" base .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ibase */, arguments->slots[0]);
  // 343: $$definition definitions(ibase)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__27_5;
}
static void cont__27_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* definition */ = arguments->slots[0];
  // 344: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 344: ... :
  // 345:   !definition.derived_types_of(name) true
  // 346:   unless kind_of(definition) == INLINE_C_TYPE:
  // 347:     !definition.kind_of INLINE_C_TYPE
  // 348:     $base_of_base base_of(definition)
  // 349:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 350:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_7, 0);
  // 344: if definition.is_defined:
  // 345:   !definition.derived_types_of(name) true
  // 346:   unless kind_of(definition) == INLINE_C_TYPE:
  // 347:     !definition.kind_of INLINE_C_TYPE
  // 348:     $base_of_base base_of(definition)
  // 349:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 350:   !definitions(ibase) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_1_mangled(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 352: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__26_24;
  arguments->slots[1] = string__24_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 352: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__28_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 352: ... replace_all(name "::" = "__" '/' = "___")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 352: ... -> replace_all(name "::" = "__" '/' = "___")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_1_ordered_name(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 357: name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 359: namespace.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__29_3;
}
static void cont__29_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 356: string
  // 357:   name.to_lower_case
  // 358:   '/'
  // 359:   namespace.to_lower_case
  // 360:   '/'
  // 361:   name
  // 362:   '/'
  // 363:   namespace
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  arguments->slots[3] = character__47;
  arguments->slots[4] = frame->slots[1] /* name */;
  arguments->slots[5] = character__47;
  arguments->slots[6] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 355: ->
  // 356:   string
  // 357:     name.to_lower_case
  // 358:     '/'
  // 359:     namespace.to_lower_case
  // 360:     '/'
  // 361:     name
  // 362:     '/'
  // 363:     namespace
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... "href" = "index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_5;
}
static void cont__30_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 367: A "href" = "index.html" "Home"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_6;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_9;
}
static void cont__30_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 369: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_11;
}
static void cont__30_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 369: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_12;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__30_13;
}
static void cont__30_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 370: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_14;
}
static void cont__30_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 371: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_16;
}
static void cont__30_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 371: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_17;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__30_18;
}
static void cont__30_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 372: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_19;
}
static void cont__30_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 373: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_21;
}
static void cont__30_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 373: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_22;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__30_23;
}
static void cont__30_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 374: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_24;
}
static void cont__30_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 375: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_26;
}
static void cont__30_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 375: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_1_link_bar(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 366: P:
  // 367:   A "href" = "index.html" "Home"
  // 368:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 369:   A "href" = "manual.html" "Manual"
  // 370:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 371:   A "href" = "type_index.html" "Type Index"
  // 372:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 373:   A "href" = "symbol_index.html" "Symbol Index"
  // 374:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 375:   A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_1_to_paragraphs(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // lines: 0
  // paragraphs: 1
  // text: 2
  // pre_mode: 3
  frame->slots[1] /* paragraphs */ = create_cell();
  frame->slots[2] /* text */ = create_cell();
  frame->slots[3] /* pre_mode */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 381: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 382: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 383: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 384: ... : (line)
  // 385:   if
  // 386:     pre_mode:
  // 387:       if
  // 388:         line .has_prefix. EXAMPLE:
  // 389:           trim &text
  // 390:           push &paragraphs text
  // 391:           !text line
  // 392:         :
  // 393:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_2, 1);
  // 384: for_each lines: (line)
  // 385:   if
  // 386:     pre_mode:
  // 387:       if
  // 388:         line .has_prefix. EXAMPLE:
  // 389:           trim &text
  // 390:           push &paragraphs text
  // 391:           !text line
  // 392:         :
  // 393:           writeln_to &text line
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__33_27;
}
static void entry__33_15(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // paragraphs: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* paragraphs */
  frame->slots[1] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 398: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_16;
}
static void cont__33_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  // 399: !text ""
  ((CELL *)frame->slots[1])->contents /* text */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_12(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // text: 0
  // paragraphs: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* paragraphs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 397: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_13;
}
static void cont__33_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 397: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_14;
}
static void cont__33_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 397: ... :
  // 398:   push &paragraphs text
  // 399:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_15, 0);
  // 397: if text != "":
  // 398:   push &paragraphs text
  // 399:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_17(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // text: 0
  // line: 1
  // pre_mode: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[0]; /* line */
  frame->slots[2] = myself->closure.frame->slots[3]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 402: text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_18;
}
static void cont__33_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 402: ... :
  // 403:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_19, 0);
  // 404: :
  // 405:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_22, 0);
  // 401: if
  // 402:   text == "":
  // 403:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 404:   :
  // 405:     push &text ' '
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_24;
}
static void entry__33_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pre_mode: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: ... !pre_mode true
  ((CELL *)frame->slots[0])->contents /* pre_mode */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_19(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // line: 0
  // pre_mode: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* line */
  frame->slots[1] = myself->closure.frame->slots[2]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: ... line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_20;
}
static void cont__33_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 403: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_21, 0);
  // 403: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 405: push &text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_23;
}
static void cont__33_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 406: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_25;
}
static void cont__33_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 406: append &text line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__33_26;
}
static void cont__33_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_5(void) {
  allocate_initialized_frame_gc(3, 3);
  // slot allocations:
  // text: 0
  // paragraphs: 1
  // line: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[2]; /* paragraphs */
  frame->slots[2] = myself->closure.frame->slots[0]; /* line */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 389: trim &text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_6;
}
static void cont__33_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 390: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_7;
}
static void cont__33_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = arguments->slots[0];
  // 391: !text line
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[2] /* line */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_8(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // text: 0
  // line: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* text */
  frame->slots[1] = myself->closure.frame->slots[0]; /* line */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 393: writeln_to &text line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__33_9;
}
static void cont__33_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_3(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // line: 0
  // text: 1
  // paragraphs: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* line */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* paragraphs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 388: line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_4;
}
static void cont__33_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 388: ... :
  // 389:   trim &text
  // 390:   push &paragraphs text
  // 391:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_5, 0);
  // 392: :
  // 393:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_8, 0);
  // 387: if
  // 388:   line .has_prefix. EXAMPLE:
  // 389:     trim &text
  // 390:     push &paragraphs text
  // 391:     !text line
  // 392:   :
  // 393:     writeln_to &text line
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
static void entry__33_10(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // line: 0
  // text: 1
  // paragraphs: 2
  // pre_mode: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* line */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  frame->slots[2] = myself->closure.frame->slots[3]; /* paragraphs */
  frame->slots[3] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 396: line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_11;
}
static void cont__33_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 396: ... :
  // 397:   if text != "":
  // 398:     push &paragraphs text
  // 399:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_12, 0);
  // 400: :
  // 401:   if
  // 402:     text == "":
  // 403:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 404:     :
  // 405:       push &text ' '
  // 406:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_17, 0);
  // 395: if
  // 396:   line == "":
  // 397:     if text != "":
  // 398:       push &paragraphs text
  // 399:       !text ""
  // 400:   :
  // 401:     if
  // 402:       text == "":
  // 403:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 404:       :
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
static void entry__33_2(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // line: 0
  // pre_mode: 1
  // text: 2
  // paragraphs: 3
  frame->slots[1] = myself->closure.frame->slots[3]; /* pre_mode */
  frame->slots[2] = myself->closure.frame->slots[2]; /* text */
  frame->slots[3] = myself->closure.frame->slots[1]; /* paragraphs */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 386: ... :
  // 387:   if
  // 388:     line .has_prefix. EXAMPLE:
  // 389:       trim &text
  // 390:       push &paragraphs text
  // 391:       !text line
  // 392:     :
  // 393:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 394: :
  // 395:   if
  // 396:     line == "":
  // 397:       if text != "":
  // 398:         push &paragraphs text
  // 399:         !text ""
  // 400:     :
  // 401:       if
  // 402:         text == "":
  // 403:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_10, 0);
  // 385: if
  // 386:   pre_mode:
  // 387:     if
  // 388:       line .has_prefix. EXAMPLE:
  // 389:         trim &text
  // 390:         push &paragraphs text
  // 391:         !text line
  // 392:       :
  // 393:         writeln_to &text line
  // 394:   :
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* pre_mode */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 407: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_28;
}
static void cont__33_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 407: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__33_29;
}
static void cont__33_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 407: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_30, 0);
  // 407: if text != "": push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_32;
}
static void entry__33_30(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // paragraphs: 0
  // text: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* paragraphs */
  frame->slots[1] = myself->closure.frame->slots[2]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 407: ... push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_31;
}
static void cont__33_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 408: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_1_resolve_reference(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 412: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_2;
}
static void cont__34_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 412: ... :
  // 413:   $$type_name reference .before. '/'
  // 414:   $$method_name reference .behind. '/'
  // 415:   unless type_name .contains. "::": append "types::" &type_name
  // 416:   unless method_name .contains. "::": append "std::" &method_name
  // 417:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_3, 0);
  // 418: :
  // 419:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__34_17, 0);
  // 411: if
  // 412:   reference .contains. '/':
  // 413:     $$type_name reference .before. '/'
  // 414:     $$method_name reference .behind. '/'
  // 415:     unless type_name .contains. "::": append "types::" &type_name
  // 416:     unless method_name .contains. "::": append "std::" &method_name
  // 417:     !reference string(type_name '/' method_name)
  // 418:   :
  // 419:     unless reference .contains. "::": append "std::" &reference
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_21;
}
static void entry__34_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 419: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_20;
}
static void cont__34_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_3(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // reference: 0
  // type_name: 1
  // method_name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  frame->slots[1] /* type_name */ = create_cell();
  frame->slots[2] /* method_name */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 414: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_5;
}
static void cont__34_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 415: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_6;
}
static void cont__34_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 415: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_7, 0);
  // 415: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_10;
}
static void entry__34_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 415: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_8;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_9;
}
static void cont__34_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* type_name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void cont__34_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 416: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_12, 0);
  // 416: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_15;
}
static void entry__34_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_14;
}
static void cont__34_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* method_name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_16;
}
static void cont__34_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 419: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_18;
}
static void cont__34_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 419: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_19, 0);
  // 419: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_21(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__35_1_add_links(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // paragraph: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 425: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 425: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 425: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__35_4;
}
static void cont__35_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 424: =
  // 425:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 426:   : ($reference)
  // 427:     range &reference 2 -2
  // 428:     resolve_reference &reference
  // 429:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__35_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void entry__35_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 427: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 427: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__35_7;
}
static void cont__35_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 428: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__35_8;
}
static void cont__35_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 429: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__35_9;
}
static void cont__35_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 429: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__35_10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__35_11;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__35_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__35_13;
}
static void cont__35_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 429: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 422: replace_all
  // 423:   &paragraph
  // 424:   =
  // 425:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 426:     : ($reference)
  // 427:       range &reference 2 -2
  // 428:       resolve_reference &reference
  // 429:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void cont__35_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_20(void) {
  allocate_initialized_frame_gc(3, 17);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_and_check_reference: 2
  // short_description: 3
  // parameters: 4
  // return_values: 5
  // descriptions: 6
  // technical_details: 7
  // references: 8
  // topic_list: 9
  // examples: 10
  // remark_lines: 11
  // function_basename: 12
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* resolve_and_check_reference */
  frame->slots[3] /* short_description */ = create_cell();
  frame->slots[4] /* parameters */ = create_cell();
  frame->slots[5] /* return_values */ = create_cell();
  frame->slots[6] /* descriptions */ = create_cell();
  frame->slots[7] /* technical_details */ = create_cell();
  frame->slots[8] /* references */ = create_cell();
  frame->slots[9] /* topic_list */ = create_cell();
  frame->slots[10] /* examples */ = create_cell();
  frame->slots[11] /* remark_lines */ = create_future();
  frame->slots[12] /* function_basename */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 442: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__36_21;
}
static void cont__36_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__36_22;
}
static void cont__36_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 444: ... :
  // 445:   $type function_name .before. '/'
  // 446:   $method function_name .behind. '/'
  // 447:   H1
  // 448:     string
  // 449:       '['
  // 450:       type
  // 451:       "]("
  // 452:       type.mangled
  // 453:       ".html)/["
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_23, 0);
  // 458: :
  // 459:   H1 function_name
  // 460:   
  // 461:   case variable_kind_of(info)
  // 462:     STATIC_MULTI: H2 "(static multi-assignment variable)"
  // 463:     DYNAMIC_SINGLE: H2 "(dynamic single-assignment variable)"
  // 464:     DYNAMIC_MULTI: H2 "(dynamic multi-assignment variable)"
  frame->slots[15] /* temp__3 */ = create_closure(entry__36_30, 0);
  // 443: if
  // 444:   function_name .contains. '/':
  // 445:     $type function_name .before. '/'
  // 446:     $method function_name .behind. '/'
  // 447:     H1
  // 448:       string
  // 449:         '['
  // 450:         type
  // 451:         "]("
  // 452:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_39;
}
static void entry__36_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 462: ... H2 "(static multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_34;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 463: ... H2 "(dynamic single-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_36;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_37(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 464: ... H2 "(dynamic multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_38;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_23(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // function_name: 0
  // type: 1
  // method: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] /* type */ = create_future();
  frame->slots[2] /* method */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 445: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__36_24;
}
static void cont__36_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 446: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_25;
}
static void cont__36_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 452: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_26;
}
static void cont__36_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 456: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_27;
}
static void cont__36_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 448: string
  // 449:   '['
  // 450:   type
  // 451:   "]("
  // 452:   type.mangled
  // 453:   ".html)/["
  // 454:   method
  // 455:   "]("
  // 456:   method.mangled
  // 457:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__35_11;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__36_28;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__35_11;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__35_12;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_29;
}
static void cont__36_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 447: H1
  // 448:   string
  // 449:     '['
  // 450:     type
  // 451:     "]("
  // 452:     type.mangled
  // 453:     ".html)/["
  // 454:     method
  // 455:     "]("
  // 456:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_30(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // function_name: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 459: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_31;
}
static void cont__36_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__36_32;
}
static void cont__36_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 461: case variable_kind_of(info)
  // 462:   STATIC_MULTI: H2 "(static multi-assignment variable)"
  // 463:   DYNAMIC_SINGLE: H2 "(dynamic single-assignment variable)"
  // 464:   DYNAMIC_MULTI: H2 "(dynamic multi-assignment variable)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = func__36_33;
  arguments->slots[3] = get__DYNAMIC_SINGLE();
  arguments->slots[4] = func__36_35;
  arguments->slots[5] = get__DYNAMIC_MULTI();
  arguments->slots[6] = func__36_37;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 466: $$short_description undefined
  ((CELL *)frame->slots[3])->contents /* short_description */ = get__undefined();
  // 467: $$parameters empty_list
  ((CELL *)frame->slots[4])->contents /* parameters */ = get__empty_list();
  // 468: $$return_values empty_list
  ((CELL *)frame->slots[5])->contents /* return_values */ = get__empty_list();
  // 469: $$descriptions empty_list
  ((CELL *)frame->slots[6])->contents /* descriptions */ = get__empty_list();
  // 470: $$technical_details undefined
  ((CELL *)frame->slots[7])->contents /* technical_details */ = get__undefined();
  // 471: $$references empty_list
  ((CELL *)frame->slots[8])->contents /* references */ = get__empty_list();
  // 472: $$topic_list empty_list
  ((CELL *)frame->slots[9])->contents /* topic_list */ = get__empty_list();
  // 473: $$examples empty_list
  ((CELL *)frame->slots[10])->contents /* examples */ = get__empty_list();
  // 474: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__36_40;
}
static void cont__36_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* remark_lines */, arguments->slots[0]);
  // 475: ... remark_lines.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__36_41;
}
static void cont__36_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 475: ... remark_lines.is_empty
  frame->slots[15] /* temp__3 */ = create_closure(entry__36_42, 0);
  // 475: ... remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__36_44;
}
static void entry__36_42(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 475: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_43;
}
static void cont__36_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 475: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 475: ... :
  // 476:   inc &missing_documentation_count
  // 477:   if do_print_missing:
  // 478:     ewrite "
  // 479:       Missing documentation for @(function_name) @
  // 480:       (defined in "@(filename_of(info))")!
  frame->slots[16] /* temp__4 */ = create_closure(entry__36_45, 0);
  // 475: if remark_lines.is_undefined || remark_lines.is_empty:
  // 476:   inc &missing_documentation_count
  // 477:   if do_print_missing:
  // 478:     ewrite "
  // 479:       Missing documentation for @(function_name) @
  // 480:       (defined in "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_53;
}
static void entry__36_47(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // function_name: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 480: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__36_48;
}
static void cont__36_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 478: ... "
  // 479:   Missing documentation for @(function_name) @
  // 480:   (defined in "@(filename_of(info))")!
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__36_49;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__36_50;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__36_51;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_52;
}
static void cont__36_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 478: ewrite "
  // 479:   Missing documentation for @(function_name) @
  // 480:   (defined in "@(filename_of(info))")!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_45(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // function_name: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 476: inc &missing_documentation_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_46;
}
static void cont__36_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._missing_documentation_count = arguments->slots[0];
  // 477: ... :
  // 478:   ewrite "
  // 479:     Missing documentation for @(function_name) @
  // 480:     (defined in "@(filename_of(info))")!
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_47, 0);
  // 477: if do_print_missing:
  // 478:   ewrite "
  // 479:     Missing documentation for @(function_name) @
  // 480:     (defined in "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_missing();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 481: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_54;
}
static void cont__36_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 481: ... :
  // 482:   $paragraphs remark_lines.to_paragraphs
  // 483:   for_each paragraphs: ($paragraph)
  // 484:     cond
  // 485:       ->
  // 486:         has_prefix
  // 487:           paragraph
  // 488:           sequence
  // 489:             "Parameter"
  // 490:             sim2c::WHITESPACE
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_55, 0);
  // 481: if remark_lines.is_defined:
  // 482:   $paragraphs remark_lines.to_paragraphs
  // 483:   for_each paragraphs: ($paragraph)
  // 484:     cond
  // 485:       ->
  // 486:         has_prefix
  // 487:           paragraph
  // 488:           sequence
  // 489:             "Parameter"
  // 490:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_178;
}
static void entry__36_173(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // technical_details: 0
  // paragraph: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* technical_details */
  frame->slots[1] = myself->closure.frame->slots[1]; /* paragraph */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 569: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_174;
}
static void cont__36_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* technical_details */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_175(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // descriptions: 0
  // paragraph: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* descriptions */
  frame->slots[1] = myself->closure.frame->slots[1]; /* paragraph */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 571: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_176;
}
static void cont__36_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* descriptions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_171(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // technical_details: 0
  // paragraph: 1
  // descriptions: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* technical_details */
  frame->slots[1] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[2] = myself->closure.frame->slots[4]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 568: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_172;
}
static void cont__36_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 568: ... :
  // 569:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_173, 0);
  // 570: :
  // 571:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_175, 0);
  // 567: if
  // 568:   technical_details.is_defined:
  // 569:     push &technical_details paragraph
  // 570:   :
  // 571:     push &descriptions paragraph
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
static void entry__36_177(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // short_description: 0
  // paragraph: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* short_description */
  frame->slots[1] = myself->closure.frame->slots[0]; /* paragraph */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 573: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_155(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 553: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_156(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // technical_details: 0
  // detail: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  frame->slots[1] = myself->closure.frame->slots[2]; /* detail */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__36_157;
}
static void cont__36_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* technical_details */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_151(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // paragraph: 0
  // technical_details: 1
  // detail: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* technical_details */
  frame->slots[2] /* detail */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 550: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_152;
}
static void cont__36_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 550: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_153;
}
static void cont__36_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 552: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_154;
}
static void cont__36_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 552: ... :
  // 553:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_155, 0);
  // 554: :
  // 555:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_156, 0);
  // 551: if
  // 552:   detail == "":
  // 553:     !technical_details empty_list
  // 554:   :
  // 555:     !technical_details list(detail)
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
static void entry__36_141(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // paragraph: 0
  // examples: 1
  // title: 2
  // text: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* examples */
  frame->slots[2] /* title */ = create_future();
  frame->slots[3] /* text */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__36_142;
}
static void cont__36_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 546: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_143;
}
static void cont__36_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 547: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_144;
}
static void cont__36_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 547: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_145;
}
static void cont__36_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 548: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_146;
}
static void cont__36_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 548: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_147;
}
static void cont__36_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* examples */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_132(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // topic: 0
  // topic_list: 1
  // function_name: 2
  // topic_contents: 3
  frame->slots[1] = myself->closure.frame->slots[1]; /* topic_list */
  frame->slots[2] = myself->closure.frame->slots[2]; /* function_name */
  frame->slots[3] /* topic_contents */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* topic */ = create_cell_with_contents(arguments->slots[0]);
  // 537: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_133;
}
static void cont__36_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 538: push &topic_list topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* topic_list */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_134;
}
static void cont__36_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* topic_list */ = arguments->slots[0];
  // 541: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__36_135;
}
static void cont__36_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 540: $$topic_contents
  // 541:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__36_136;
}
static void cont__36_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 543: !topic_contents(function_name) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 543: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* function_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__36_137;
}
static void cont__36_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 544: !topics(topic) topic_contents
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  // 544: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__36_138;
}
static void cont__36_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._topics = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_129(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // paragraph: 0
  // topic_list: 1
  // function_name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* topic_list */
  frame->slots[2] = myself->closure.frame->slots[2]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 536: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_130;
}
static void cont__36_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 536: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__36_131;
}
static void cont__36_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 536: ... : ($topic)
  // 537:   trim &topic
  // 538:   push &topic_list topic
  // 539:   
  // 540:   $$topic_contents
  // 541:     default_value(topics(topic) empty_key_order_set)
  // 542:   
  // 543:   !topic_contents(function_name) true
  // 544:   !topics(topic) topic_contents
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_132, 1);
  // 536: for_each split(paragraph .behind. ':' ','): ($topic)
  // 537:   trim &topic
  // 538:   push &topic_list topic
  // 539:   
  // 540:   $$topic_contents
  // 541:     default_value(topics(topic) empty_key_order_set)
  // 542:   
  // 543:   !topic_contents(function_name) true
  // 544:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_124(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 534: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_125;
}
static void cont__36_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 534: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_126;
}
static void cont__36_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* references */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_121(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // paragraph: 0
  // references: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 533: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_122;
}
static void cont__36_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 533: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__36_123;
}
static void cont__36_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 533: ... : (reference)
  // 534:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_124, 1);
  // 533: for_each split(paragraph .behind. ':' ','): (reference)
  // 534:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_99(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // paragraph: 0
  // return_values: 1
  // return_value: 2
  // description: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* return_values */
  frame->slots[2] /* return_value */ = create_cell();
  frame->slots[3] /* description */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 521: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__36_100;
}
static void cont__36_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 523: -> return_value .has_suffix. '?':
  // 524:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_101, 0);
  // 525: -> return_value .has_suffix. '*':
  // 526:   !return_value
  // 527:     string
  // 528:       range(return_value 1 -2)
  // 529:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_107, 0);
  // 522: cond
  // 523:   -> return_value .has_suffix. '?':
  // 524:     !return_value string(range(return_value 1 -2) " (optional)")
  // 525:   -> return_value .has_suffix. '*':
  // 526:     !return_value
  // 527:       string
  // 528:         range(return_value 1 -2)
  // 529:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__36_113;
}
static void entry__36_109(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 528: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_110;
}
static void cont__36_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 528: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_111;
}
static void cont__36_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 526: !return_value
  // 527:   string
  // 528:     range(return_value 1 -2)
  // 529:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_77;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_112;
}
static void cont__36_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* return_value */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_103(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 524: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_104;
}
static void cont__36_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 524: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_105;
}
static void cont__36_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 524: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_70;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_106;
}
static void cont__36_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* return_value */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_101(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 523: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__36_102;
}
static void cont__36_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 523: ... :
  // 524:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_103, 0);
  // 523: -> return_value .has_suffix. '?':
  // 524:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_107(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 525: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__36_108;
}
static void cont__36_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 525: ... :
  // 526:   !return_value
  // 527:     string
  // 528:       range(return_value 1 -2)
  // 529:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_109, 0);
  // 525: -> return_value .has_suffix. '*':
  // 526:   !return_value
  // 527:     string
  // 528:       range(return_value 1 -2)
  // 529:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 530: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_114;
}
static void cont__36_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 530: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_115;
}
static void cont__36_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 531: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_116;
}
static void cont__36_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 531: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_117;
}
static void cont__36_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* return_values */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_63(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // paragraph: 0
  // parameters: 1
  // parameter: 2
  // description: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[2] /* parameter */ = create_cell();
  frame->slots[3] /* description */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 495: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__36_64;
}
static void cont__36_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 497: -> parameter .has_suffix. '?':
  // 498:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_65, 0);
  // 499: -> parameter .has_suffix. '*':
  // 500:   !parameter
  // 501:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_72, 0);
  // 502: -> parameter .contains. '=':
  // 503:   !parameter
  // 504:     string
  // 505:       (parameter .before. '=').trim
  // 506:       " (optional; default value: "
  // 507:       (parameter .behind. '=').trim
  // 508:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__36_79, 0);
  // 496: cond
  // 497:   -> parameter .has_suffix. '?':
  // 498:     !parameter string(range(parameter 1 -2) " (optional)")
  // 499:   -> parameter .has_suffix. '*':
  // 500:     !parameter
  // 501:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 502:   -> parameter .contains. '=':
  // 503:     !parameter
  // 504:       string
  // 505:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__36_89;
}
static void entry__36_81(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 505: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__36_82;
}
static void cont__36_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 505: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_83;
}
static void cont__36_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 507: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_84;
}
static void cont__36_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 507: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_85;
}
static void cont__36_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 503: !parameter
  // 504:   string
  // 505:     (parameter .before. '=').trim
  // 506:     " (optional; default value: "
  // 507:     (parameter .behind. '=').trim
  // 508:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_86;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__36_87;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_88;
}
static void cont__36_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameter */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_74(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 501: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_75;
}
static void cont__36_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 501: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_76;
}
static void cont__36_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 500: !parameter
  // 501:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_77;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_78;
}
static void cont__36_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameter */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_67(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 498: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_68;
}
static void cont__36_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 498: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_69;
}
static void cont__36_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 498: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_70;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_71;
}
static void cont__36_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* parameter */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_65(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 497: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__36_66;
}
static void cont__36_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 497: ... :
  // 498:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_67, 0);
  // 497: -> parameter .has_suffix. '?':
  // 498:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 499: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__36_73;
}
static void cont__36_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 499: ... :
  // 500:   !parameter
  // 501:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_74, 0);
  // 499: -> parameter .has_suffix. '*':
  // 500:   !parameter
  // 501:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_79(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 502: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__36_80;
}
static void cont__36_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 502: ... :
  // 503:   !parameter
  // 504:     string
  // 505:       (parameter .before. '=').trim
  // 506:       " (optional; default value: "
  // 507:       (parameter .behind. '=').trim
  // 508:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_81, 0);
  // 502: -> parameter .contains. '=':
  // 503:   !parameter
  // 504:     string
  // 505:       (parameter .before. '=').trim
  // 506:       " (optional; default value: "
  // 507:       (parameter .behind. '=').trim
  // 508:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 509: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_90;
}
static void cont__36_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 509: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__36_91;
}
static void cont__36_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 510: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_92;
}
static void cont__36_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 510: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_93;
}
static void cont__36_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* parameters */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_58(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // paragraph: 0
  // parameters: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 492: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__36_59;
}
static void cont__36_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 488: sequence
  // 489:   "Parameter"
  // 490:   sim2c::WHITESPACE
  // 491:   NAME
  // 492:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 493:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__36_60;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__36_61;
}
static void cont__36_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 486: has_prefix
  // 487:   paragraph
  // 488:   sequence
  // 489:     "Parameter"
  // 490:     sim2c::WHITESPACE
  // 491:     NAME
  // 492:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 493:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_62;
}
static void cont__36_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 494: :
  // 495:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 496:   cond
  // 497:     -> parameter .has_suffix. '?':
  // 498:       !parameter string(range(parameter 1 -2) " (optional)")
  // 499:     -> parameter .has_suffix. '*':
  // 500:       !parameter
  // 501:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 502:     -> parameter .contains. '=':
  // 503:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__36_63, 0);
  // 485: ->
  // 486:   has_prefix
  // 487:     paragraph
  // 488:     sequence
  // 489:       "Parameter"
  // 490:       sim2c::WHITESPACE
  // 491:       NAME
  // 492:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 493:       ':'
  // 494:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_94(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // paragraph: 0
  // return_values: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[2]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 518: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__36_95;
}
static void cont__36_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 514: sequence
  // 515:   "Returns"
  // 516:   sim2c::WHITESPACE
  // 517:   NAME
  // 518:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 519:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__36_96;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__36_97;
}
static void cont__36_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 512: has_prefix
  // 513:   paragraph
  // 514:   sequence
  // 515:     "Returns"
  // 516:     sim2c::WHITESPACE
  // 517:     NAME
  // 518:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 519:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_98;
}
static void cont__36_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 520: :
  // 521:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 522:   cond
  // 523:     -> return_value .has_suffix. '?':
  // 524:       !return_value string(range(return_value 1 -2) " (optional)")
  // 525:     -> return_value .has_suffix. '*':
  // 526:       !return_value
  // 527:         string
  // 528:           range(return_value 1 -2)
  // 529:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__36_99, 0);
  // 511: ->
  // 512:   has_prefix
  // 513:     paragraph
  // 514:     sequence
  // 515:       "Returns"
  // 516:       sim2c::WHITESPACE
  // 517:       NAME
  // 518:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 519:       ':'
  // 520:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_118(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // references: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[3]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 532: ... paragraph .has_prefix. "See also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__36_119;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_120;
}
static void cont__36_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 532: ... :
  // 533:   for_each split(paragraph .behind. ':' ','): (reference)
  // 534:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_121, 0);
  // 532: -> paragraph .has_prefix. "See also:":
  // 533:   for_each split(paragraph .behind. ':' ','): (reference)
  // 534:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_127(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // paragraph: 0
  // topic_list: 1
  // function_name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[4]; /* topic_list */
  frame->slots[2] = myself->closure.frame->slots[5]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 535: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_128;
}
static void cont__36_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 535: ... :
  // 536:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 537:     trim &topic
  // 538:     push &topic_list topic
  // 539:     
  // 540:     $$topic_contents
  // 541:       default_value(topics(topic) empty_key_order_set)
  // 542:     
  // 543:     !topic_contents(function_name) true
  // 544:     !topics(topic) topic_contents
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_129, 0);
  // 535: -> paragraph .has_prefix. TOPIC:
  // 536:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 537:     trim &topic
  // 538:     push &topic_list topic
  // 539:     
  // 540:     $$topic_contents
  // 541:       default_value(topics(topic) empty_key_order_set)
  // 542:     
  // 543:     !topic_contents(function_name) true
  // 544:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_139(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // examples: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[6]; /* examples */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_140;
}
static void cont__36_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 545: ... :
  // 546:   $title (paragraph .before. ':').trim
  // 547:   $text (paragraph .behind. ':').trim
  // 548:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_141, 0);
  // 545: -> paragraph .has_prefix. EXAMPLE:
  // 546:   $title (paragraph .before. ':').trim
  // 547:   $text (paragraph .behind. ':').trim
  // 548:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_148(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // technical_details: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[7]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 549: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__36_149;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__36_150;
}
static void cont__36_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 549: ... :
  // 550:   $detail (paragraph .behind. ':').trim
  // 551:   if
  // 552:     detail == "":
  // 553:       !technical_details empty_list
  // 554:     :
  // 555:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_151, 0);
  // 549: -> paragraph .has_prefix. "Technical Details:":
  // 550:   $detail (paragraph .behind. ':').trim
  // 551:   if
  // 552:     detail == "":
  // 553:       !technical_details empty_list
  // 554:     :
  // 555:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_158(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // paragraph: 0
  // resolve_and_check_reference: 1
  // short_description: 2
  // technical_details: 3
  // descriptions: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[8]; /* resolve_and_check_reference */
  frame->slots[2] = myself->closure.frame->slots[9]; /* short_description */
  frame->slots[3] = myself->closure.frame->slots[7]; /* technical_details */
  frame->slots[4] = myself->closure.frame->slots[10]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 560: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_159;
}
static void cont__36_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 560: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__36_160;
}
static void cont__36_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 560: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_161;
}
static void cont__36_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 561: : ($reference)
  // 562:   range &reference 2 -2
  // 563:   resolve_and_check_reference &reference
  // 564:   -> "[@(reference)](@(reference.mangled).html)"
  frame->slots[9] /* temp__5 */ = create_closure(entry__36_162, 1);
  // 559: =
  // 560:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 561:   : ($reference)
  // 562:     range &reference 2 -2
  // 563:     resolve_and_check_reference &reference
  // 564:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_168;
}
static void entry__36_162(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // reference: 0
  // resolve_and_check_reference: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_and_check_reference */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 562: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_163;
}
static void cont__36_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 562: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_164;
}
static void cont__36_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 563: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__36_165;
}
static void cont__36_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 564: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_166;
}
static void cont__36_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 564: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__35_10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__35_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__35_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_167;
}
static void cont__36_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 564: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 557: replace_all
  // 558:   &paragraph
  // 559:   =
  // 560:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 561:     : ($reference)
  // 562:       range &reference 2 -2
  // 563:       resolve_and_check_reference &reference
  // 564:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_169;
}
static void cont__36_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 566: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_170;
}
static void cont__36_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 566: ... :
  // 567:   if
  // 568:     technical_details.is_defined:
  // 569:       push &technical_details paragraph
  // 570:     :
  // 571:       push &descriptions paragraph
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_171, 0);
  // 572: :
  // 573:   !short_description paragraph
  frame->slots[7] /* temp__3 */ = create_closure(entry__36_177, 0);
  // 565: if
  // 566:   short_description.is_defined:
  // 567:     if
  // 568:       technical_details.is_defined:
  // 569:         push &technical_details paragraph
  // 570:       :
  // 571:         push &descriptions paragraph
  // 572:   :
  // 573:     !short_description paragraph
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
static void entry__36_57(void) {
  allocate_initialized_frame_gc(11, 18);
  // slot allocations:
  // paragraph: 0
  // parameters: 1
  // return_values: 2
  // references: 3
  // topic_list: 4
  // function_name: 5
  // examples: 6
  // technical_details: 7
  // resolve_and_check_reference: 8
  // short_description: 9
  // descriptions: 10
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return_values */
  frame->slots[3] = myself->closure.frame->slots[3]; /* references */
  frame->slots[4] = myself->closure.frame->slots[4]; /* topic_list */
  frame->slots[5] = myself->closure.frame->slots[5]; /* function_name */
  frame->slots[6] = myself->closure.frame->slots[6]; /* examples */
  frame->slots[7] = myself->closure.frame->slots[7]; /* technical_details */
  frame->slots[8] = myself->closure.frame->slots[8]; /* resolve_and_check_reference */
  frame->slots[9] = myself->closure.frame->slots[9]; /* short_description */
  frame->slots[10] = myself->closure.frame->slots[10]; /* descriptions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 485: ->
  // 486:   has_prefix
  // 487:     paragraph
  // 488:     sequence
  // 489:       "Parameter"
  // 490:       sim2c::WHITESPACE
  // 491:       NAME
  // 492:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 493:       ':'
  // 494:   :
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__36_58, 0);
  // 511: ->
  // 512:   has_prefix
  // 513:     paragraph
  // 514:     sequence
  // 515:       "Returns"
  // 516:       sim2c::WHITESPACE
  // 517:       NAME
  // 518:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 519:       ':'
  // 520:   :
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__36_94, 0);
  // 532: -> paragraph .has_prefix. "See also:":
  // 533:   for_each split(paragraph .behind. ':' ','): (reference)
  // 534:     push &references reference.trim
  frame->slots[13] /* temp__3 */ = create_closure(entry__36_118, 0);
  // 535: -> paragraph .has_prefix. TOPIC:
  // 536:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 537:     trim &topic
  // 538:     push &topic_list topic
  // 539:     
  // 540:     $$topic_contents
  // 541:       default_value(topics(topic) empty_key_order_set)
  // 542:     
  // 543:     !topic_contents(function_name) true
  // 544:     !topics(topic) topic_contents
  frame->slots[14] /* temp__4 */ = create_closure(entry__36_127, 0);
  // 545: -> paragraph .has_prefix. EXAMPLE:
  // 546:   $title (paragraph .before. ':').trim
  // 547:   $text (paragraph .behind. ':').trim
  // 548:   push &examples title = text
  frame->slots[15] /* temp__5 */ = create_closure(entry__36_139, 0);
  // 549: -> paragraph .has_prefix. "Technical Details:":
  // 550:   $detail (paragraph .behind. ':').trim
  // 551:   if
  // 552:     detail == "":
  // 553:       !technical_details empty_list
  // 554:     :
  // 555:       !technical_details list(detail)
  frame->slots[16] /* temp__6 */ = create_closure(entry__36_148, 0);
  // 556: :
  // 557:   replace_all
  // 558:     &paragraph
  // 559:     =
  // 560:       '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 561:       : ($reference)
  // 562:         range &reference 2 -2
  // 563:         resolve_and_check_reference &reference
  // 564:         -> "[@(reference)](@(reference.mangled).html)"
  // 565:   if
  // ...
  frame->slots[17] /* temp__7 */ = create_closure(entry__36_158, 0);
  // 484: cond
  // 485:   ->
  // 486:     has_prefix
  // 487:       paragraph
  // 488:       sequence
  // 489:         "Parameter"
  // 490:         sim2c::WHITESPACE
  // 491:         NAME
  // 492:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 493:         ':'
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  arguments->slots[3] = frame->slots[14] /* temp__4 */;
  arguments->slots[4] = frame->slots[15] /* temp__5 */;
  arguments->slots[5] = frame->slots[16] /* temp__6 */;
  arguments->slots[6] = frame->slots[17] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_55(void) {
  allocate_initialized_frame_gc(11, 13);
  // slot allocations:
  // remark_lines: 0
  // parameters: 1
  // return_values: 2
  // references: 3
  // topic_list: 4
  // function_name: 5
  // examples: 6
  // technical_details: 7
  // resolve_and_check_reference: 8
  // short_description: 9
  // descriptions: 10
  // paragraphs: 11
  frame->slots[0] = myself->closure.frame->slots[11]; /* remark_lines */
  frame->slots[1] = myself->closure.frame->slots[4]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[5]; /* return_values */
  frame->slots[3] = myself->closure.frame->slots[8]; /* references */
  frame->slots[4] = myself->closure.frame->slots[9]; /* topic_list */
  frame->slots[5] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[6] = myself->closure.frame->slots[10]; /* examples */
  frame->slots[7] = myself->closure.frame->slots[7]; /* technical_details */
  frame->slots[8] = myself->closure.frame->slots[2]; /* resolve_and_check_reference */
  frame->slots[9] = myself->closure.frame->slots[3]; /* short_description */
  frame->slots[10] = myself->closure.frame->slots[6]; /* descriptions */
  frame->slots[11] /* paragraphs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 482: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__36_56;
}
static void cont__36_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* paragraphs */, arguments->slots[0]);
  // 483: ... : ($paragraph)
  // 484:   cond
  // 485:     ->
  // 486:       has_prefix
  // 487:         paragraph
  // 488:         sequence
  // 489:           "Parameter"
  // 490:           sim2c::WHITESPACE
  // 491:           NAME
  // 492:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[12] /* temp__1 */ = create_closure(entry__36_57, 1);
  // 483: for_each paragraphs: ($paragraph)
  // 484:   cond
  // 485:     ->
  // 486:       has_prefix
  // 487:         paragraph
  // 488:         sequence
  // 489:           "Parameter"
  // 490:           sim2c::WHITESPACE
  // 491:           NAME
  // 492:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* paragraphs */;
  arguments->slots[1] = frame->slots[12] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_179;
}
static void cont__36_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 574: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_180;
}
static void cont__36_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 574: ... :
  // 575:   for_each parameters_of(info): (parameter)
  // 576:     case
  // 577:       parameter_kind_of(parameter)
  // 578:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 579:         pass
  // 580:       :
  // 581:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:         cond
  // 583:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__36_181, 0);
  // 574: if kind_of(info) == FUNCTION:
  // 575:   for_each parameters_of(info): (parameter)
  // 576:     case
  // 577:       parameter_kind_of(parameter)
  // 578:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 579:         pass
  // 580:       :
  // 581:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:         cond
  // 583:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_218;
}
static void entry__36_186(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  // name: 2
  // description: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[2] /* name */ = create_cell();
  frame->slots[3] /* description */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 581: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__36_187;
}
static void cont__36_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 581: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__36_188;
}
static void cont__36_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 581: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__36_189;
}
static void cont__36_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 583: -> parameter.is_an_optional_item:
  // 584:   if
  // 585:     default_value_of(parameter).is_defined:
  // 586:       write_to
  // 587:         &name
  // 588:         " (optional; default value: "
  // 589:         default_value_of(parameter).to_string
  // 590:         ")"
  // 591:     :
  // 592:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__36_190, 0);
  // 593: -> parameter.is_an_expanded_item:
  // 594:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_201, 0);
  // 582: cond
  // 583:   -> parameter.is_an_optional_item:
  // 584:     if
  // 585:       default_value_of(parameter).is_defined:
  // 586:         write_to
  // 587:           &name
  // 588:           " (optional; default value: "
  // 589:           default_value_of(parameter).to_string
  // 590:           ")"
  // 591:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__36_205;
}
static void entry__36_203(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 594: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__36_77;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_204;
}
static void cont__36_204(void) {
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
static void entry__36_195(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // parameter: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 589: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__36_196;
}
static void cont__36_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 589: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__36_197;
}
static void cont__36_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 586: write_to
  // 587:   &name
  // 588:   " (optional; default value: "
  // 589:   default_value_of(parameter).to_string
  // 590:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__36_86;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__36_87;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__36_198;
}
static void cont__36_198(void) {
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
static void entry__36_199(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 592: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__36_70;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__36_200;
}
static void cont__36_200(void) {
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
static void entry__36_192(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // parameter: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 585: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__36_193;
}
static void cont__36_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 585: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_194;
}
static void cont__36_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 585: ... :
  // 586:   write_to
  // 587:     &name
  // 588:     " (optional; default value: "
  // 589:     default_value_of(parameter).to_string
  // 590:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_195, 0);
  // 591: :
  // 592:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__36_199, 0);
  // 584: if
  // 585:   default_value_of(parameter).is_defined:
  // 586:     write_to
  // 587:       &name
  // 588:       " (optional; default value: "
  // 589:       default_value_of(parameter).to_string
  // 590:       ")"
  // 591:   :
  // 592:     append &name " (optional)"
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
static void entry__36_190(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // parameter: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 583: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__36_191;
}
static void cont__36_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 583: ... :
  // 584:   if
  // 585:     default_value_of(parameter).is_defined:
  // 586:       write_to
  // 587:         &name
  // 588:         " (optional; default value: "
  // 589:         default_value_of(parameter).to_string
  // 590:         ")"
  // 591:     :
  // 592:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_192, 0);
  // 583: -> parameter.is_an_optional_item:
  // 584:   if
  // 585:     default_value_of(parameter).is_defined:
  // 586:       write_to
  // 587:         &name
  // 588:         " (optional; default value: "
  // 589:         default_value_of(parameter).to_string
  // 590:         ")"
  // 591:     :
  // 592:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_201(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // parameter: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__36_202;
}
static void cont__36_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 593: ... :
  // 594:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_203, 0);
  // 593: -> parameter.is_an_expanded_item:
  // 594:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_205(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__36_206;
}
static void cont__36_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 598: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_207;
}
static void cont__36_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 598: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__36_208;
}
static void cont__36_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 599: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__36_209, 0);
  // 596: $description
  // 597:   if
  // 598:     not(remark_lines_of(parameter).is_empty)
  // 599:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 600:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__36_213;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_214;
}
static void entry__36_209(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 599: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__36_210;
}
static void cont__36_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 599: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__36_211;
}
static void cont__36_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 599: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__36_212;
}
static void cont__36_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 599: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_213(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 600: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 602: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_215;
}
static void cont__36_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 602: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__36_216;
}
static void cont__36_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* parameters */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_217(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 579: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_183(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 577: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__36_184;
}
static void cont__36_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 578: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_185;
}
static void cont__36_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 580: :
  // 581:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:   cond
  // 583:     -> parameter.is_an_optional_item:
  // 584:       if
  // 585:         default_value_of(parameter).is_defined:
  // 586:           write_to
  // 587:             &name
  // 588:             " (optional; default value: "
  // 589:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_186, 0);
  // 576: case
  // 577:   parameter_kind_of(parameter)
  // 578:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 579:     pass
  // 580:   :
  // 581:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:     cond
  // 583:       -> parameter.is_an_optional_item:
  // 584:         if
  // 585:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__36_217;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_181(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // parameters: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[4]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__36_182;
}
static void cont__36_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 575: ... : (parameter)
  // 576:   case
  // 577:     parameter_kind_of(parameter)
  // 578:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 579:       pass
  // 580:     :
  // 581:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:       cond
  // 583:         -> parameter.is_an_optional_item:
  // 584:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_183, 1);
  // 575: for_each parameters_of(info): (parameter)
  // 576:   case
  // 577:     parameter_kind_of(parameter)
  // 578:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 579:       pass
  // 580:     :
  // 581:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 582:       cond
  // 583:         -> parameter.is_an_optional_item:
  // 584:           if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 603: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_219;
}
static void cont__36_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 603: ... : P short_description
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_220, 0);
  // 603: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_221;
}
static void entry__36_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 604: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_222;
}
static void cont__36_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 604: ... :
  // 605:   H2 "Parameters"
  // 606:   DL:
  // 607:     for_each parameters: (parameter)
  // 608:       DT key_of(parameter)
  // 609:       DD: P std::value_of(parameter)
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_223, 0);
  // 604: unless parameters.is_empty:
  // 605:   H2 "Parameters"
  // 606:   DL:
  // 607:     for_each parameters: (parameter)
  // 608:       DT key_of(parameter)
  // 609:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_232;
}
static void entry__36_230(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 609: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__36_231;
}
static void cont__36_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 609: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_227(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 608: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__36_228;
}
static void cont__36_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 608: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__36_229;
}
static void cont__36_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 609: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_230, 0);
  // 609: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_226(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 607: for_each parameters: (parameter)
  // 608:   DT key_of(parameter)
  // 609:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__36_227;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_223(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 605: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_224;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_225;
}
static void cont__36_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 606: ... :
  // 607:   for_each parameters: (parameter)
  // 608:     DT key_of(parameter)
  // 609:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_226, 0);
  // 606: DL:
  // 607:   for_each parameters: (parameter)
  // 608:     DT key_of(parameter)
  // 609:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 610: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_233;
}
static void cont__36_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 610: ... :
  // 611:   H2 "Returns"
  // 612:   DL:
  // 613:     for_each return_values: (return_value)
  // 614:       DT key_of(return_value)
  // 615:       DD: P std::value_of(return_value)
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_234, 0);
  // 610: unless return_values.is_empty:
  // 611:   H2 "Returns"
  // 612:   DL:
  // 613:     for_each return_values: (return_value)
  // 614:       DT key_of(return_value)
  // 615:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_242;
}
static void entry__36_240(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 615: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__36_241;
}
static void cont__36_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 615: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_237(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 614: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__36_238;
}
static void cont__36_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 614: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__36_239;
}
static void cont__36_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 615: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_240, 0);
  // 615: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_236(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 613: for_each return_values: (return_value)
  // 614:   DT key_of(return_value)
  // 615:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__36_237;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_234(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 611: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_96;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_235;
}
static void cont__36_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 612: ... :
  // 613:   for_each return_values: (return_value)
  // 614:     DT key_of(return_value)
  // 615:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_236, 0);
  // 612: DL:
  // 613:   for_each return_values: (return_value)
  // 614:     DT key_of(return_value)
  // 615:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_242(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 616: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_243;
}
static void cont__36_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   H2 "Description"
  // 618:   for_each descriptions: (description) P description
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_244, 0);
  // 616: unless descriptions.is_empty:
  // 617:   H2 "Description"
  // 618:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_248;
}
static void entry__36_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 618: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_244(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 617: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_245;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_246;
}
static void cont__36_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__36_247;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_248(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_249;
}
static void cont__36_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 619: ... :
  // 620:   H2 "Technical Details"
  // 621:   for_each technical_details: (detail) P detail
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_250, 0);
  // 619: if technical_details.is_defined:
  // 620:   H2 "Technical Details"
  // 621:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_254;
}
static void entry__36_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 621: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_250(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 620: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_251;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_252;
}
static void cont__36_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 621: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__36_253;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_254(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 622: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_255;
}
static void cont__36_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 622: ... :
  // 623:   H2 "See also"
  // 624:   TABLE:
  // 625:     for_each references: ($reference)
  // 626:       resolve_and_check_reference &reference
  // 627:       TR:
  // 628:         TD: A "href" = "@(reference.mangled).html" reference
  // 629:         TD "&nbsp;"
  // 630:         TD short_descriptions(reference)
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_256, 0);
  // 622: unless references.is_empty:
  // 623:   H2 "See also"
  // 624:   TABLE:
  // 625:     for_each references: ($reference)
  // 626:       resolve_and_check_reference &reference
  // 627:       TR:
  // 628:         TD: A "href" = "@(reference.mangled).html" reference
  // 629:         TD "&nbsp;"
  // 630:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_271;
}
static void entry__36_262(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 628: ... : A "href" = "@(reference.mangled).html" reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_263, 0);
  // 628: TD: A "href" = "@(reference.mangled).html" reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_267;
}
static void entry__36_263(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 628: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_264;
}
static void cont__36_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 628: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_265;
}
static void cont__36_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 628: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_266;
}
static void cont__36_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 628: ... A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_267(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_269;
}
static void cont__36_269(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 630: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__36_270;
}
static void cont__36_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 630: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_260(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // resolve_and_check_reference: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_and_check_reference */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 626: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__36_261;
}
static void cont__36_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 627: ... :
  // 628:   TD: A "href" = "@(reference.mangled).html" reference
  // 629:   TD "&nbsp;"
  // 630:   TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_262, 0);
  // 627: TR:
  // 628:   TD: A "href" = "@(reference.mangled).html" reference
  // 629:   TD "&nbsp;"
  // 630:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_259(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // references: 0
  // resolve_and_check_reference: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* references */
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_and_check_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: ... : ($reference)
  // 626:   resolve_and_check_reference &reference
  // 627:   TR:
  // 628:     TD: A "href" = "@(reference.mangled).html" reference
  // 629:     TD "&nbsp;"
  // 630:     TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_260, 1);
  // 625: for_each references: ($reference)
  // 626:   resolve_and_check_reference &reference
  // 627:   TR:
  // 628:     TD: A "href" = "@(reference.mangled).html" reference
  // 629:     TD "&nbsp;"
  // 630:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_256(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // references: 0
  // resolve_and_check_reference: 1
  frame->slots[0] = myself->closure.frame->slots[8]; /* references */
  frame->slots[1] = myself->closure.frame->slots[2]; /* resolve_and_check_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 623: H2 "See also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_257;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_258;
}
static void cont__36_258(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 624: ... :
  // 625:   for_each references: ($reference)
  // 626:     resolve_and_check_reference &reference
  // 627:     TR:
  // 628:       TD: A "href" = "@(reference.mangled).html" reference
  // 629:       TD "&nbsp;"
  // 630:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_259, 0);
  // 624: TABLE:
  // 625:   for_each references: ($reference)
  // 626:     resolve_and_check_reference &reference
  // 627:     TR:
  // 628:       TD: A "href" = "@(reference.mangled).html" reference
  // 629:       TD "&nbsp;"
  // 630:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_271(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 631: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__36_272;
}
static void cont__36_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 631: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_273;
}
static void cont__36_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 631: ... :
  // 632:   H2 "Implemented by"
  // 633:   TABLE:
  // 634:     for_each types_of(info): (name)
  // 635:       $method string(name '/' function_name)
  // 636:       TR:
  // 637:         TD: A "href" = "@(name.mangled).html" name
  // 638:         TD "&nbsp;as&nbsp;"
  // 639:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[15] /* temp__3 */ = create_closure(entry__36_274, 0);
  // 631: unless types_of(info).is_empty:
  // 632:   H2 "Implemented by"
  // 633:   TABLE:
  // 634:     for_each types_of(info): (name)
  // 635:       $method string(name '/' function_name)
  // 636:       TR:
  // 637:         TD: A "href" = "@(name.mangled).html" name
  // 638:         TD "&nbsp;as&nbsp;"
  // 639:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_293;
}
static void entry__36_289(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 639: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_290;
}
static void cont__36_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 639: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_291;
}
static void cont__36_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 639: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_292;
}
static void cont__36_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 639: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_281(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // method: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 637: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_282, 0);
  // 637: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_286;
}
static void entry__36_282(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 637: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_283;
}
static void cont__36_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 637: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_284;
}
static void cont__36_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 637: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_285;
}
static void cont__36_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 637: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_286(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 638: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_287;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_288;
}
static void cont__36_288(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_289, 0);
  // 639: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_279(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // function_name: 1
  // method: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_name */
  frame->slots[2] /* method */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 635: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_280;
}
static void cont__36_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 636: ... :
  // 637:   TD: A "href" = "@(name.mangled).html" name
  // 638:   TD "&nbsp;as&nbsp;"
  // 639:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_281, 0);
  // 636: TR:
  // 637:   TD: A "href" = "@(name.mangled).html" name
  // 638:   TD "&nbsp;as&nbsp;"
  // 639:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_277(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 634: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__36_278;
}
static void cont__36_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 634: ... : (name)
  // 635:   $method string(name '/' function_name)
  // 636:   TR:
  // 637:     TD: A "href" = "@(name.mangled).html" name
  // 638:     TD "&nbsp;as&nbsp;"
  // 639:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_279, 1);
  // 634: for_each types_of(info): (name)
  // 635:   $method string(name '/' function_name)
  // 636:   TR:
  // 637:     TD: A "href" = "@(name.mangled).html" name
  // 638:     TD "&nbsp;as&nbsp;"
  // 639:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_274(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // info: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 632: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_275;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_276;
}
static void cont__36_276(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 633: ... :
  // 634:   for_each types_of(info): (name)
  // 635:     $method string(name '/' function_name)
  // 636:     TR:
  // 637:       TD: A "href" = "@(name.mangled).html" name
  // 638:       TD "&nbsp;as&nbsp;"
  // 639:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_277, 0);
  // 633: TABLE:
  // 634:   for_each types_of(info): (name)
  // 635:     $method string(name '/' function_name)
  // 636:     TR:
  // 637:       TD: A "href" = "@(name.mangled).html" name
  // 638:       TD "&nbsp;as&nbsp;"
  // 639:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_293(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 641: ... function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__36_294;
}
static void cont__36_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 641: ... :
  // 642:   $polymorphic_function_name function_name .behind. '/'
  // 643:   H2 "Implements"
  // 644:   A "href" = "@(polymorphic_function_name.mangled).html"
  // 645:     polymorphic_function_name
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_295, 0);
  // 641: if function_name .contains. '/':
  // 642:   $polymorphic_function_name function_name .behind. '/'
  // 643:   H2 "Implements"
  // 644:   A "href" = "@(polymorphic_function_name.mangled).html"
  // 645:     polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_302;
}
static void entry__36_295(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // function_name: 0
  // polymorphic_function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] /* polymorphic_function_name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 642: $polymorphic_function_name function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_296;
}
static void cont__36_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* polymorphic_function_name */, arguments->slots[0]);
  // 643: H2 "Implements"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_297;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_298;
}
static void cont__36_298(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: ... polymorphic_function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* polymorphic_function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_299;
}
static void cont__36_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 644: ... "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_300;
}
static void cont__36_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 644: ... "href" = "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_301;
}
static void cont__36_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 644: A "href" = "@(polymorphic_function_name.mangled).html"
  // 645:   polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* polymorphic_function_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_302(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_303;
}
static void cont__36_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 647: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_304;
}
static void cont__36_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 647: ... :
  // 648:   H2 "Supported Polymorphic Functions"
  // 649:   TABLE:
  // 650:     for_each methods_of(info): (method_name _method_info)
  // 651:       TR:
  // 652:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:         TD "&nbsp;"
  // 654:         TD:
  // 655:           A
  // 656:             =
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__36_305, 0);
  // 647: if kind_of(info) == INLINE_C_TYPE:
  // 648:   H2 "Supported Polymorphic Functions"
  // 649:   TABLE:
  // 650:     for_each methods_of(info): (method_name _method_info)
  // 651:       TR:
  // 652:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:         TD "&nbsp;"
  // 654:         TD:
  // 655:           A
  // 656:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_323;
}
static void entry__36_318(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // function_name: 0
  // method_name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 658: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_319;
}
static void cont__36_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 658: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_320;
}
static void cont__36_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 658: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__28_3;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_321;
}
static void cont__36_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 656: =
  // 657:   "href"
  // 658:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_322;
}
static void cont__36_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 655: A
  // 656:   =
  // 657:     "href"
  // 658:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:   function_name
  // 660:   '/'
  // 661:   method_name
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = character__47;
  arguments->slots[3] = frame->slots[1] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_311(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // method_name: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_312, 0);
  // 652: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_316;
}
static void entry__36_312(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 652: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_313;
}
static void cont__36_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 652: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_314;
}
static void cont__36_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 652: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_315;
}
static void cont__36_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 652: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_316(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_317;
}
static void cont__36_317(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: ... :
  // 655:   A
  // 656:     =
  // 657:       "href"
  // 658:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:     function_name
  // 660:     '/'
  // 661:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_318, 0);
  // 654: TD:
  // 655:   A
  // 656:     =
  // 657:       "href"
  // 658:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:     function_name
  // 660:     '/'
  // 661:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_310(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // function_name: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* function_name */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 651: ... :
  // 652:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:   TD "&nbsp;"
  // 654:   TD:
  // 655:     A
  // 656:       =
  // 657:         "href"
  // 658:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:       function_name
  // 660:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_311, 0);
  // 651: TR:
  // 652:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:   TD "&nbsp;"
  // 654:   TD:
  // 655:     A
  // 656:       =
  // 657:         "href"
  // 658:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:       function_name
  // 660:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_308(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__36_309;
}
static void cont__36_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 650: ... : (method_name _method_info)
  // 651:   TR:
  // 652:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:     TD "&nbsp;"
  // 654:     TD:
  // 655:       A
  // 656:         =
  // 657:           "href"
  // 658:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_310, 2);
  // 650: for_each methods_of(info): (method_name _method_info)
  // 651:   TR:
  // 652:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:     TD "&nbsp;"
  // 654:     TD:
  // 655:       A
  // 656:         =
  // 657:           "href"
  // 658:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 659:         function_name
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_305(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // info: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 648: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_306;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_307;
}
static void cont__36_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 649: ... :
  // 650:   for_each methods_of(info): (method_name _method_info)
  // 651:     TR:
  // 652:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:       TD "&nbsp;"
  // 654:       TD:
  // 655:         A
  // 656:           =
  // 657:             "href"
  // 658:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_308, 0);
  // 649: TABLE:
  // 650:   for_each methods_of(info): (method_name _method_info)
  // 651:     TR:
  // 652:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 653:       TD "&nbsp;"
  // 654:       TD:
  // 655:         A
  // 656:           =
  // 657:             "href"
  // 658:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_323(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__36_324;
}
static void cont__36_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 663: $function_basename
  // 664:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__36_325;
}
static void cont__36_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* function_basename */, arguments->slots[0]);
  // 666: ... topic_list.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* topic_list */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_326;
}
static void cont__36_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 666: ... :
  // 667:   H2 "Topics"
  // 668:   TABLE:
  // 669:     for_each topic_list: (topic)
  // 670:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 671:       TR: TD: A "href" = filename topic
  frame->slots[14] /* temp__2 */ = create_closure(entry__36_327, 0);
  // 666: unless topic_list.is_empty:
  // 667:   H2 "Topics"
  // 668:   TABLE:
  // 669:     for_each topic_list: (topic)
  // 670:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 671:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_340;
}
static void entry__36_338(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // topic: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* topic */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_339;
}
static void cont__36_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 671: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_337(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // topic: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* topic */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_338, 0);
  // 671: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_331(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // topic: 0
  // filename: 1
  frame->slots[1] /* filename */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 670: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__36_332;
}
static void cont__36_332(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 670: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__36_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_334;
}
static void cont__36_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 670: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_335;
}
static void cont__36_335(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 670: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_336;
}
static void cont__36_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* filename */, arguments->slots[0]);
  // 671: ... : TD: A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_337, 0);
  // 671: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_330(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: for_each topic_list: (topic)
  // 670:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 671:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic_list */;
  arguments->slots[1] = func__36_331;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_327(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 667: H2 "Topics"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_328;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_329;
}
static void cont__36_329(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 668: ... :
  // 669:   for_each topic_list: (topic)
  // 670:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 671:     TR: TD: A "href" = filename topic
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_330, 0);
  // 668: TABLE:
  // 669:   for_each topic_list: (topic)
  // 670:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 671:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_340(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 673: ... : (example)
  // 674:   $title key_of(example)
  // 675:   $text std::value_of(example)
  // 676:   H2 title
  // 677:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 678:     PRE
  // 679:       replace_all
  // 680:         text
  // 681:         =
  // 682:           sequence
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__36_341, 1);
  // 673: for_each examples: (example)
  // 674:   $title key_of(example)
  // 675:   $text std::value_of(example)
  // 676:   H2 title
  // 677:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 678:     PRE
  // 679:       replace_all
  // 680:         text
  // 681:         =
  // 682:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* examples */;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_360;
}
static void entry__36_349(void) {
  allocate_initialized_frame_gc(2, 10);
  // slot allocations:
  // text: 0
  // function_basename: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* text */
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_basename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__36_350;
}
static void cont__36_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 684: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_351;
}
static void cont__36_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 684: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__36_352;
}
static void cont__36_352(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 682: sequence
  // 683:   '@quot;'
  // 684:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__36_353;
}
static void cont__36_353(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 681: =
  // 682:   sequence
  // 683:     '@quot;'
  // 684:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:     '@quot;'
  // 686:   : (string_literal)
  // 687:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__36_354;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_355;
}
static void entry__36_354(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 687: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 688: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__36_356;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__36_356;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_357;
}
static void cont__36_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 688: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_358;
}
static void cont__36_358(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 679: replace_all
  // 680:   text
  // 681:   =
  // 682:     sequence
  // 683:       '@quot;'
  // 684:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:       '@quot;'
  // 686:     : (string_literal)
  // 687:       -> string_literal
  // 688:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_359;
}
static void cont__36_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 678: PRE
  // 679:   replace_all
  // 680:     text
  // 681:     =
  // 682:       sequence
  // 683:         '@quot;'
  // 684:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:         '@quot;'
  // 686:       : (string_literal)
  // 687:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_341(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // example: 0
  // function_basename: 1
  // title: 2
  // text: 3
  frame->slots[1] = myself->closure.frame->slots[12]; /* function_basename */
  frame->slots[2] /* title */ = create_future();
  frame->slots[3] /* text */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 674: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__36_342;
}
static void cont__36_342(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 675: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__36_343;
}
static void cont__36_343(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 676: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__36_344;
}
static void cont__36_344(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__36_345;
}
static void cont__36_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 677: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__36_346;
}
static void cont__36_346(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 677: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_347;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_348;
}
static void cont__36_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 677: ... :
  // 678:   PRE
  // 679:     replace_all
  // 680:       text
  // 681:       =
  // 682:         sequence
  // 683:           '@quot;'
  // 684:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:           '@quot;'
  // 686:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__36_349, 0);
  // 677: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 678:   PRE
  // 679:     replace_all
  // 680:       text
  // 681:       =
  // 682:         sequence
  // 683:           '@quot;'
  // 684:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 685:           '@quot;'
  // 686:         : (string_literal)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_360(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 690: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_347;
  arguments->slots[1] = string__36_361;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_362;
}
static void cont__36_362(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 691: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__36_363;
}
static void cont__36_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 691: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__36_364;
}
static void cont__36_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 691: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__36_365;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  arguments->slots[2] = string__36_366;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_367;
}
static void cont__36_367(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 689: DIV
  // 690:   "class" = "footer"
  // 691:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_15(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_and_check_reference: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* resolve_and_check_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 441: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_16;
}
static void cont__36_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 441: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__36_17;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_19;
}
static void cont__36_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 441: ... :
  // 442:   link_bar
  // 443:   if
  // 444:     function_name .contains. '/':
  // 445:       $type function_name .before. '/'
  // 446:       $method function_name .behind. '/'
  // 447:       H1
  // 448:         string
  // 449:           '['
  // 450:           type
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_20, 0);
  // 441: create_page "html/@(function_name.mangled).html":
  // 442:   link_bar
  // 443:   if
  // 444:     function_name .contains. '/':
  // 445:       $type function_name .before. '/'
  // 446:       $method function_name .behind. '/'
  // 447:       H1
  // 448:         string
  // 449:           '['
  // 450:           type
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_1_create_info_page(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_and_check_reference: 2
  frame->slots[2] /* resolve_and_check_reference */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 432: ... : (&reference)
  // 433:   resolve_reference &reference
  // 434:   if short_descriptions(reference).is_undefined:
  // 435:     Error "
  // 436:       The documentation for "@(function_name)"
  // 437:       (defined in "@(filename_of(info))")
  // 438:       references the undefined symbol "@(reference)"!
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_2_resolve_and_check_reference, 1);
  // 432: $resolve_and_check_reference: (&reference)
  // 433:   resolve_reference &reference
  // 434:   if short_descriptions(reference).is_undefined:
  // 435:     Error "
  // 436:       The documentation for "@(function_name)"
  // 437:       (defined in "@(filename_of(info))")
  // 438:       references the undefined symbol "@(reference)"!
  initialize_future(frame->slots[2] /* resolve_and_check_reference */, frame->slots[3] /* temp__1 */);
  // 440: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_14;
}
static void entry__36_2_resolve_and_check_reference(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // reference: 0
  // function_name: 1
  // info: 2
  frame->slots[1] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 433: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__36_3;
}
static void cont__36_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 434: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 434: ... short_descriptions(reference).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__36_5;
}
static void cont__36_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 434: ... :
  // 435:   Error "
  // 436:     The documentation for "@(function_name)"
  // 437:     (defined in "@(filename_of(info))")
  // 438:     references the undefined symbol "@(reference)"!
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_6, 0);
  // 434: if short_descriptions(reference).is_undefined:
  // 435:   Error "
  // 436:     The documentation for "@(function_name)"
  // 437:     (defined in "@(filename_of(info))")
  // 438:     references the undefined symbol "@(reference)"!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_13;
}
static void entry__36_6(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // function_name: 0
  // info: 1
  // reference: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 437: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__36_7;
}
static void cont__36_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 435: ... "
  // 436:   The documentation for "@(function_name)"
  // 437:   (defined in "@(filename_of(info))")
  // 438:   references the undefined symbol "@(reference)"!
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__36_8;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__36_9;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__36_10;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* reference */;
  arguments->slots[6] = string__36_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_12;
}
static void cont__36_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 435: Error "
  // 436:   The documentation for "@(function_name)"
  // 437:   (defined in "@(filename_of(info))")
  // 438:   references the undefined symbol "@(reference)"!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_13(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   create_page "html/@(function_name.mangled).html":
  // 442:     link_bar
  // 443:     if
  // 444:       function_name .contains. '/':
  // 445:         $type function_name .before. '/'
  // 446:         $method function_name .behind. '/'
  // 447:         H1
  // 448:           string
  // 449:             '['
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_15, 0);
  // 440: if function_name.is_defined:
  // 441:   create_page "html/@(function_name.mangled).html":
  // 442:     link_bar
  // 443:     if
  // 444:       function_name .contains. '/':
  // 445:         $type function_name .before. '/'
  // 446:         $method function_name .behind. '/'
  // 447:         H1
  // 448:           string
  // 449:             '['
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
static void entry__37_1_get_short_description(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // name: 0
  // info: 1
  // remark_lines: 2
  // short_description: 3
  frame->slots[2] /* remark_lines */ = create_future();
  frame->slots[3] /* short_description */ = create_cell();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 694: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__37_2;
}
static void cont__37_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* remark_lines */, arguments->slots[0]);
  // 695: $$short_description ""
  ((CELL *)frame->slots[3])->contents /* short_description */ = empty_string;
  // 696: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_3;
}
static void cont__37_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 696: ... not(remark_lines.is_empty)
  frame->slots[6] /* temp__3 */ = create_closure(entry__37_4, 0);
  // 696: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__37_7;
}
static void entry__37_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 696: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_5;
}
static void cont__37_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 696: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__37_6;
}
static void cont__37_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 696: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 696: ... :
  // 697:   do: (-> break) for_each remark_lines: (line)
  // 698:     if line == "" && short_description != "" break
  // 699:     append &short_description line.trim
  // 700:   if do_print_warnings && length_of(short_description) > 80:
  // 701:     ewrite "
  // 702:       
  // 703:       The short description for "@(name)"
  // 704:       (defined in "@(filename_of(info))")
  // 705:       is quite long:
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__37_8, 0);
  // 696: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 697:   do: (-> break) for_each remark_lines: (line)
  // 698:     if line == "" && short_description != "" break
  // 699:     append &short_description line.trim
  // 700:   if do_print_warnings && length_of(short_description) > 80:
  // 701:     ewrite "
  // 702:       
  // 703:       The short description for "@(name)"
  // 704:       (defined in "@(filename_of(info))")
  // 705:       is quite long:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_30;
}
static void entry__37_25(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // short_description: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* info */
  frame->slots[2] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__37_26;
}
static void cont__37_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 701: ... "
  // 702:   
  // 703:   The short description for "@(name)"
  // 704:   (defined in "@(filename_of(info))")
  // 705:   is quite long:
  // 706:   @(short_description)
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__37_27;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__36_9;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__37_28;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* short_description */;
  arguments->slots[6] = string__24_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_29;
}
static void cont__37_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 701: ewrite "
  // 702:   
  // 703:   The short description for "@(name)"
  // 704:   (defined in "@(filename_of(info))")
  // 705:   is quite long:
  // 706:   @(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_8(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // remark_lines: 0
  // short_description: 1
  // name: 2
  // info: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* remark_lines */
  frame->slots[1] = myself->closure.frame->slots[3]; /* short_description */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  frame->slots[3] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: ... : (-> break) for_each remark_lines: (line)
  // 698:   if line == "" && short_description != "" break
  // 699:   append &short_description line.trim
  frame->slots[4] /* temp__1 */ = create_closure(entry__37_9, 0);
  // 697: do: (-> break) for_each remark_lines: (line)
  // 698:   if line == "" && short_description != "" break
  // 699:   append &short_description line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__37_20;
}
static void entry__37_9(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // break: 0
  // remark_lines: 1
  // short_description: 2
  frame->slots[0] /* break */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* remark_lines */
  frame->slots[2] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: ... : (line)
  // 698:   if line == "" && short_description != "" break
  // 699:   append &short_description line.trim
  frame->slots[3] /* temp__1 */ = create_closure(entry__37_10, 1);
  // 697: ... for_each remark_lines: (line)
  // 698:   if line == "" && short_description != "" break
  // 699:   append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__37_19;
}
static void entry__37_10(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // line: 0
  // short_description: 1
  // break: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* short_description */
  frame->slots[2] = myself->closure.frame->slots[0]; /* break */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 698: ... line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__37_11;
}
static void cont__37_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 698: ... short_description != ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_12, 0);
  // 698: ... line == "" && short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__37_15;
}
static void entry__37_12(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 698: ... short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__37_13;
}
static void cont__37_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 698: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__37_14;
}
static void cont__37_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 698: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 698: if line == "" && short_description != "" break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_16;
}
static void cont__37_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 699: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_17;
}
static void cont__37_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 699: append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__37_18;
}
static void cont__37_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* short_description */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__37_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 700: ... length_of(short_description) > 80
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_21, 0);
  // 700: ... do_print_warnings && length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__37_24;
}
static void entry__37_21(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: ... length_of(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__37_22;
}
static void cont__37_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 700: ... length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__37_23;
}
static void cont__37_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 700: ... length_of(short_description) > 80
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 700: ... :
  // 701:   ewrite "
  // 702:     
  // 703:     The short description for "@(name)"
  // 704:     (defined in "@(filename_of(info))")
  // 705:     is quite long:
  // 706:     @(short_description)
  frame->slots[6] /* temp__3 */ = create_closure(entry__37_25, 0);
  // 700: if do_print_warnings && length_of(short_description) > 80:
  // 701:   ewrite "
  // 702:     
  // 703:     The short description for "@(name)"
  // 704:     (defined in "@(filename_of(info))")
  // 705:     is quite long:
  // 706:     @(short_description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 707: add_links &short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = var._add_links;
  func = myself->type;
  frame->cont = cont__37_31;
}
static void cont__37_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* short_description */ = arguments->slots[0];
  // 708: -> short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_234(void) {
  allocate_initialized_frame_gc(0, 28);
  // slot allocations:
  // total_functions: 0
  // total_polymorphic_functions: 1
  // total_polymorphic_attributes: 2
  // total_methods: 3
  // total_inline_c_methods: 4
  // total_inline_c_types: 5
  // total_inline_c_objects: 6
  // total_attributes: 7
  // total_inline_c_functions: 8
  // total_unique_items: 9
  // total_constants: 10
  // other: 11
  // total_definitions: 12
  frame->slots[0] /* total_functions */ = create_cell();
  frame->slots[1] /* total_polymorphic_functions */ = create_cell();
  frame->slots[2] /* total_polymorphic_attributes */ = create_cell();
  frame->slots[3] /* total_methods */ = create_cell();
  frame->slots[4] /* total_inline_c_methods */ = create_cell();
  frame->slots[5] /* total_inline_c_types */ = create_cell();
  frame->slots[6] /* total_inline_c_objects */ = create_cell();
  frame->slots[7] /* total_attributes */ = create_cell();
  frame->slots[8] /* total_inline_c_functions */ = create_cell();
  frame->slots[9] /* total_unique_items */ = create_cell();
  frame->slots[10] /* total_constants */ = create_cell();
  frame->slots[11] /* other */ = create_cell();
  frame->slots[12] /* total_definitions */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 844: $$total_functions 0
  ((CELL *)frame->slots[0])->contents /* total_functions */ = number__0;
  // 845: $$total_polymorphic_functions 0
  ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */ = number__0;
  // 846: $$total_polymorphic_attributes 0
  ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */ = number__0;
  // 847: $$total_methods 0
  ((CELL *)frame->slots[3])->contents /* total_methods */ = number__0;
  // 848: $$total_inline_c_methods 0
  ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */ = number__0;
  // 849: $$total_inline_c_types 0
  ((CELL *)frame->slots[5])->contents /* total_inline_c_types */ = number__0;
  // 850: $$total_inline_c_objects 0
  ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */ = number__0;
  // 851: $$total_attributes 0
  ((CELL *)frame->slots[7])->contents /* total_attributes */ = number__0;
  // 852: $$total_inline_c_functions 0
  ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */ = number__0;
  // 853: $$total_unique_items 0
  ((CELL *)frame->slots[9])->contents /* total_unique_items */ = number__0;
  // 854: $$total_constants 0
  ((CELL *)frame->slots[10])->contents /* total_constants */ = number__0;
  // 855: $$other 0
  ((CELL *)frame->slots[11])->contents /* other */ = number__0;
  // 857: ... : (_iname info)
  // 858:   case kind_of(info)
  // 859:     FUNCTION: inc &total_functions
  // 860:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 861:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 862:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 863:     INLINE_C_TYPE: inc &total_inline_c_types
  // 864:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 865:     UNIQUE_ITEM: inc &total_unique_items
  // 866:     CONSTANT: inc &total_constants
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__38_235, 2);
  // 857: for_each definitions: (_iname info)
  // 858:   case kind_of(info)
  // 859:     FUNCTION: inc &total_functions
  // 860:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 861:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 862:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 863:     INLINE_C_TYPE: inc &total_inline_c_types
  // 864:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 865:     UNIQUE_ITEM: inc &total_unique_items
  // 866:     CONSTANT: inc &total_constants
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_267;
}
static void entry__38_261(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_methods: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 871: ... inc &total_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_262;
}
static void cont__38_262(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_methods */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_263(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_methods: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_inline_c_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 872: ... inc &total_inline_c_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_264;
}
static void cont__38_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_265(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 873: ... inc &total_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_266;
}
static void cont__38_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_attributes */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_259(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // total_methods: 2
  // total_inline_c_methods: 3
  // total_attributes: 4
  frame->slots[2] = myself->closure.frame->slots[1]; /* total_methods */
  frame->slots[3] = myself->closure.frame->slots[2]; /* total_inline_c_methods */
  frame->slots[4] = myself->closure.frame->slots[3]; /* total_attributes */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 870: ... kind_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_260;
}
static void cont__38_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 871: ... : inc &total_methods
  frame->slots[6] /* temp__2 */ = create_closure(entry__38_261, 0);
  // 872: ... : inc &total_inline_c_methods
  frame->slots[7] /* temp__3 */ = create_closure(entry__38_263, 0);
  // 873: : inc &total_attributes
  frame->slots[8] /* temp__4 */ = create_closure(entry__38_265, 0);
  // 870: case kind_of(method_info)
  // 871:   FUNCTION: inc &total_methods
  // 872:   INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 873:   : inc &total_attributes
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = var._INLINE_C_FUNCTION;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  arguments->slots[5] = frame->slots[8] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_257(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // info: 0
  // total_methods: 1
  // total_inline_c_methods: 2
  // total_attributes: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[11]; /* total_methods */
  frame->slots[2] = myself->closure.frame->slots[12]; /* total_inline_c_methods */
  frame->slots[3] = myself->closure.frame->slots[13]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 869: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__38_258;
}
static void cont__38_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 869: ... : (method_name method_info)
  // 870:   case kind_of(method_info)
  // 871:     FUNCTION: inc &total_methods
  // 872:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 873:     : inc &total_attributes
  frame->slots[5] /* temp__2 */ = create_closure(entry__38_259, 2);
  // 869: for_each methods_of(info): (method_name method_info)
  // 870:   case kind_of(method_info)
  // 871:     FUNCTION: inc &total_methods
  // 872:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 873:     : inc &total_attributes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_235(void) {
  allocate_initialized_frame_gc(14, 24);
  // slot allocations:
  // iname: 0
  // info: 1
  // total_functions: 2
  // total_polymorphic_functions: 3
  // total_polymorphic_attributes: 4
  // total_inline_c_functions: 5
  // total_inline_c_types: 6
  // total_inline_c_objects: 7
  // total_unique_items: 8
  // total_constants: 9
  // other: 10
  // total_methods: 11
  // total_inline_c_methods: 12
  // total_attributes: 13
  frame->slots[2] = myself->closure.frame->slots[0]; /* total_functions */
  frame->slots[3] = myself->closure.frame->slots[1]; /* total_polymorphic_functions */
  frame->slots[4] = myself->closure.frame->slots[2]; /* total_polymorphic_attributes */
  frame->slots[5] = myself->closure.frame->slots[8]; /* total_inline_c_functions */
  frame->slots[6] = myself->closure.frame->slots[5]; /* total_inline_c_types */
  frame->slots[7] = myself->closure.frame->slots[6]; /* total_inline_c_objects */
  frame->slots[8] = myself->closure.frame->slots[9]; /* total_unique_items */
  frame->slots[9] = myself->closure.frame->slots[10]; /* total_constants */
  frame->slots[10] = myself->closure.frame->slots[11]; /* other */
  frame->slots[11] = myself->closure.frame->slots[3]; /* total_methods */
  frame->slots[12] = myself->closure.frame->slots[4]; /* total_inline_c_methods */
  frame->slots[13] = myself->closure.frame->slots[7]; /* total_attributes */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 858: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_236;
}
static void cont__38_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 859: ... : inc &total_functions
  frame->slots[15] /* temp__2 */ = create_closure(entry__38_237, 0);
  // 860: ... : inc &total_polymorphic_functions
  frame->slots[16] /* temp__3 */ = create_closure(entry__38_239, 0);
  // 861: ... : inc &total_polymorphic_attributes
  frame->slots[17] /* temp__4 */ = create_closure(entry__38_241, 0);
  // 862: ... : inc &total_inline_c_functions
  frame->slots[18] /* temp__5 */ = create_closure(entry__38_243, 0);
  // 863: ... : inc &total_inline_c_types
  frame->slots[19] /* temp__6 */ = create_closure(entry__38_245, 0);
  // 864: ... : inc &total_inline_c_objects
  frame->slots[20] /* temp__7 */ = create_closure(entry__38_247, 0);
  // 865: ... : inc &total_unique_items
  frame->slots[21] /* temp__8 */ = create_closure(entry__38_249, 0);
  // 866: ... : inc &total_constants
  frame->slots[22] /* temp__9 */ = create_closure(entry__38_251, 0);
  // 867: : inc &other
  frame->slots[23] /* temp__10 */ = create_closure(entry__38_253, 0);
  // 858: case kind_of(info)
  // 859:   FUNCTION: inc &total_functions
  // 860:   POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 861:   POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 862:   INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 863:   INLINE_C_TYPE: inc &total_inline_c_types
  // 864:   INLINE_C_OBJECT: inc &total_inline_c_objects
  // 865:   UNIQUE_ITEM: inc &total_unique_items
  // 866:   CONSTANT: inc &total_constants
  // 867:   : inc &other
  argument_count = 18;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = frame->slots[15] /* temp__2 */;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = frame->slots[16] /* temp__3 */;
  arguments->slots[5] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[6] = frame->slots[17] /* temp__4 */;
  arguments->slots[7] = var._INLINE_C_FUNCTION;
  arguments->slots[8] = frame->slots[18] /* temp__5 */;
  arguments->slots[9] = var._INLINE_C_TYPE;
  arguments->slots[10] = frame->slots[19] /* temp__6 */;
  arguments->slots[11] = var._INLINE_C_OBJECT;
  arguments->slots[12] = frame->slots[20] /* temp__7 */;
  arguments->slots[13] = var._UNIQUE_ITEM;
  arguments->slots[14] = frame->slots[21] /* temp__8 */;
  arguments->slots[15] = var._CONSTANT;
  arguments->slots[16] = frame->slots[22] /* temp__9 */;
  arguments->slots[17] = frame->slots[23] /* temp__10 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__38_255;
}
static void entry__38_237(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_functions: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: ... inc &total_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_238;
}
static void cont__38_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_functions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_239(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_functions: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_polymorphic_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 860: ... inc &total_polymorphic_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_240;
}
static void cont__38_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_241(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_polymorphic_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: ... inc &total_polymorphic_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_242;
}
static void cont__38_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_243(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_functions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* total_inline_c_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 862: ... inc &total_inline_c_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_244;
}
static void cont__38_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_245(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_types: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* total_inline_c_types */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: ... inc &total_inline_c_types
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_246;
}
static void cont__38_246(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_inline_c_types */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_objects: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* total_inline_c_objects */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: ... inc &total_inline_c_objects
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_248;
}
static void cont__38_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_inline_c_objects */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_249(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_unique_items: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* total_unique_items */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 865: ... inc &total_unique_items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_250;
}
static void cont__38_250(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_unique_items */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_251(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_constants: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* total_constants */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: ... inc &total_constants
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_constants */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_252;
}
static void cont__38_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_constants */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // other: 0
  frame->slots[0] = myself->closure.frame->slots[10]; /* other */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 867: ... inc &other
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* other */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__38_254;
}
static void cont__38_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* other */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_255(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 868: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_256;
}
static void cont__38_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 868: ... :
  // 869:   for_each methods_of(info): (method_name method_info)
  // 870:     case kind_of(method_info)
  // 871:       FUNCTION: inc &total_methods
  // 872:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 873:       : inc &total_attributes
  frame->slots[15] /* temp__2 */ = create_closure(entry__38_257, 0);
  // 868: case kind_of(info) INLINE_C_TYPE:
  // 869:   for_each methods_of(info): (method_name method_info)
  // 870:     case kind_of(method_info)
  // 871:       FUNCTION: inc &total_methods
  // 872:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 873:       : inc &total_attributes
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  arguments->slots[2] = frame->slots[15] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_267(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_268;
}
static void cont__38_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[21] /* temp__9 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_269;
}
static void cont__38_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__8 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_270;
}
static void cont__38_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__7 */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_271;
}
static void cont__38_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__6 */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_272;
}
static void cont__38_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__5 */;
  arguments->slots[1] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_273;
}
static void cont__38_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_274;
}
static void cont__38_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_275;
}
static void cont__38_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_276;
}
static void cont__38_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 875: $total_definitions
  // 876:   +
  // 877:     total_functions
  // 878:     total_polymorphic_functions
  // 879:     total_polymorphic_attributes
  // 880:     total_methods
  // 881:     total_inline_c_methods
  // 882:     total_inline_c_types
  // 883:     total_inline_c_objects
  // 884:     total_attributes
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_277;
}
static void cont__38_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* total_definitions */, arguments->slots[0]);
  // 890: ... pad_left(total_definitions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* total_definitions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_278;
}
static void cont__38_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 892: ... pad_left(total_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_279;
}
static void cont__38_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 893: ... pad_left(total_polymorphic_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_280;
}
static void cont__38_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 894: ... pad_left(total_polymorphic_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_281;
}
static void cont__38_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  // 895: ... pad_left(total_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_282;
}
static void cont__38_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  // 896: ... pad_left(total_inline_c_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_283;
}
static void cont__38_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  // 897: ... pad_left(total_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_284;
}
static void cont__38_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  // 898: ... pad_left(total_inline_c_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_285;
}
static void cont__38_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  // 899: ... pad_left(total_inline_c_types 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_286;
}
static void cont__38_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__10 */ = arguments->slots[0];
  // 900: ... pad_left(total_inline_c_objects 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_287;
}
static void cont__38_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__11 */ = arguments->slots[0];
  // 901: ... pad_left(total_unique_items 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_288;
}
static void cont__38_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__12 */ = arguments->slots[0];
  // 902: ... pad_left(total_constants 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_289;
}
static void cont__38_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__13 */ = arguments->slots[0];
  // 903: ... pad_left(other 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* other */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_290;
}
static void cont__38_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__14 */ = arguments->slots[0];
  // 905: ... pad_left(missing_documentation_count 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__38_291;
}
static void cont__38_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__15 */ = arguments->slots[0];
  // 889: ... "
  // 890:   total definitions:     @(pad_left(total_definitions 5))
  // 891:   
  // 892:   functions:             @(pad_left(total_functions 5))
  // 893:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 894:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 895:   method definitions:    @(pad_left(total_methods 5))
  // 896:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 897:   attribute definitions: @(pad_left(total_attributes 5))
  // 898:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 29;
  arguments = node_p;
  arguments->slots[0] = string__38_292;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = string__38_293;
  arguments->slots[3] = frame->slots[15] /* temp__3 */;
  arguments->slots[4] = string__38_294;
  arguments->slots[5] = frame->slots[16] /* temp__4 */;
  arguments->slots[6] = string__38_295;
  arguments->slots[7] = frame->slots[17] /* temp__5 */;
  arguments->slots[8] = string__38_296;
  arguments->slots[9] = frame->slots[18] /* temp__6 */;
  arguments->slots[10] = string__38_297;
  arguments->slots[11] = frame->slots[19] /* temp__7 */;
  arguments->slots[12] = string__38_298;
  arguments->slots[13] = frame->slots[20] /* temp__8 */;
  arguments->slots[14] = string__38_299;
  arguments->slots[15] = frame->slots[21] /* temp__9 */;
  arguments->slots[16] = string__38_300;
  arguments->slots[17] = frame->slots[22] /* temp__10 */;
  arguments->slots[18] = string__38_301;
  arguments->slots[19] = frame->slots[23] /* temp__11 */;
  arguments->slots[20] = string__38_302;
  arguments->slots[21] = frame->slots[24] /* temp__12 */;
  arguments->slots[22] = string__38_303;
  arguments->slots[23] = frame->slots[25] /* temp__13 */;
  arguments->slots[24] = string__38_304;
  arguments->slots[25] = frame->slots[26] /* temp__14 */;
  arguments->slots[26] = string__38_305;
  arguments->slots[27] = frame->slots[27] /* temp__15 */;
  arguments->slots[28] = string__24_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_306;
}
static void cont__38_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 889: ewrite "
  // 890:   total definitions:     @(pad_left(total_definitions 5))
  // 891:   
  // 892:   functions:             @(pad_left(total_functions 5))
  // 893:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 894:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 895:   method definitions:    @(pad_left(total_methods 5))
  // 896:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 897:   attribute definitions: @(pad_left(total_attributes 5))
  // 898:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_1_sim2c__extract_documentation(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
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
  frame->cont = cont__38_2;
}
static void cont__38_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 712: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 713: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__38_4;
}
static void cont__38_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 715: for_each definitions: (iname info)
  // 716:   $name name_of(info)
  // 717:   !short_descriptions(name) get_short_description(name info)
  // 718:   
  // 719:   if kind_of(info) == INLINE_C_TYPE:
  // 720:     $base base_of(info)
  // 721:     if base.is_defined: add_derived_type base iname
  // 722:     $$methods empty_key_order_table
  // 723:     for_each methods_of(info): ($method_name method_info)
  // 724:       unless method_name .contains. "::":
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__38_5;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_38;
}
static void entry__38_11(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // info: 0
  // iname: 1
  // name: 2
  // base: 3
  // methods: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[2]; /* name */
  frame->slots[3] /* base */ = create_future();
  frame->slots[4] /* methods */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 720: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__38_12;
}
static void cont__38_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base */, arguments->slots[0]);
  // 721: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_13;
}
static void cont__38_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 721: ... : add_derived_type base iname
  frame->slots[6] /* temp__2 */ = create_closure(entry__38_14, 0);
  // 721: if base.is_defined: add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_15;
}
static void entry__38_14(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // base: 0
  // iname: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* base */
  frame->slots[1] = myself->closure.frame->slots[1]; /* iname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 721: ... add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* iname */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 722: $$methods empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* methods */ = get__empty_key_order_table();
  // 723: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__38_16;
}
static void cont__38_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 723: ... : ($method_name method_info)
  // 724:   unless method_name .contains. "::":
  // 725:     !method_name attribute_of(method_info).resolved_name
  // 726:   $sd_name string(name "/" method_name)
  // 727:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 728:   $oname
  // 729:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 730:   !definitions(oname).types_of(name) true
  // 731:   !methods(method_name) method_info
  frame->slots[6] /* temp__2 */ = create_closure(entry__38_17, 2);
  // 723: for_each methods_of(info): ($method_name method_info)
  // 724:   unless method_name .contains. "::":
  // 725:     !method_name attribute_of(method_info).resolved_name
  // 726:   $sd_name string(name "/" method_name)
  // 727:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 728:   $oname
  // 729:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 730:   !definitions(oname).types_of(name) true
  // 731:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_35;
}
static void entry__38_17(void) {
  allocate_initialized_frame_gc(4, 9);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // name: 2
  // methods: 3
  // sd_name: 4
  // oname: 5
  frame->slots[2] = myself->closure.frame->slots[2]; /* name */
  frame->slots[3] = myself->closure.frame->slots[4]; /* methods */
  frame->slots[4] /* sd_name */ = create_future();
  frame->slots[5] /* oname */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* method_name */ = create_cell_with_contents(arguments->slots[0]);
  // 724: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__38_18;
}
static void cont__38_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 724: ... :
  // 725:   !method_name attribute_of(method_info).resolved_name
  frame->slots[7] /* temp__2 */ = create_closure(entry__38_19, 0);
  // 724: unless method_name .contains. "::":
  // 725:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__38_22;
}
static void entry__38_19(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* method_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__38_20;
}
static void cont__38_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 725: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__38_21;
}
static void cont__38_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* method_name */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 726: $sd_name string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__38_23;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__38_24;
}
static void cont__38_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* sd_name */, arguments->slots[0]);
  // 727: !short_descriptions(sd_name) get_short_description(sd_name method_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__38_25;
}
static void cont__38_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 727: !short_descriptions(sd_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__38_26;
}
static void cont__38_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 729: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__38_27;
}
static void cont__38_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 729: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__38_28;
}
static void cont__38_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 728: $oname
  // 729:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__38_29;
}
static void cont__38_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* oname */, arguments->slots[0]);
  // 730: !definitions(oname).types_of(name) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 730: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__38_30;
}
static void cont__38_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 730: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__38_31;
}
static void cont__38_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 730: !definitions(oname).types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[8] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__38_32;
}
static void cont__38_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 730: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[7] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[8] /* temp__3 */);
    frame->slots[7] /* temp__2 */ = temp;

  }
  // 730: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__38_33;
}
static void cont__38_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 731: !methods(method_name) method_info
  frame->slots[6] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 731: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__38_34;
}
static void cont__38_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* methods */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 732: !definitions(iname).methods_of methods
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* methods */;
  // 732: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__38_36;
}
static void cont__38_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 732: !definitions(iname).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[5] /* temp__1 */);
    frame->slots[6] /* temp__2 */ = temp;

  }
  // 732: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__38_37;
}
static void cont__38_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_5(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // iname: 0
  // info: 1
  // name: 2
  frame->slots[2] /* name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 716: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__38_6;
}
static void cont__38_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 717: !short_descriptions(name) get_short_description(name info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__38_7;
}
static void cont__38_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 717: !short_descriptions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__38_8;
}
static void cont__38_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 719: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_9;
}
static void cont__38_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 719: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_10;
}
static void cont__38_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 719: ... :
  // 720:   $base base_of(info)
  // 721:   if base.is_defined: add_derived_type base iname
  // 722:   $$methods empty_key_order_table
  // 723:   for_each methods_of(info): ($method_name method_info)
  // 724:     unless method_name .contains. "::":
  // 725:       !method_name attribute_of(method_info).resolved_name
  // 726:     $sd_name string(name "/" method_name)
  // 727:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 728:     $oname
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_11, 0);
  // 719: if kind_of(info) == INLINE_C_TYPE:
  // 720:   $base base_of(info)
  // 721:   if base.is_defined: add_derived_type base iname
  // 722:   $$methods empty_key_order_table
  // 723:   for_each methods_of(info): ($method_name method_info)
  // 724:     unless method_name .contains. "::":
  // 725:       !method_name attribute_of(method_info).resolved_name
  // 726:     $sd_name string(name "/" method_name)
  // 727:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 728:     $oname
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 734: create_page "html/type_index.html":
  // 735:   $print_type_info:
  // 736:     (
  // 737:       info
  // 738:       indent = 0
  // 739:     )
  // 740:     TR:
  // 741:       $qname name_of(info)
  // 742:       $remark_lines remark_lines_of(info)
  // 743:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_39;
  arguments->slots[1] = func__38_40;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__38_78;
}
static void entry__38_77(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // print_type_info: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* print_type_info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 757: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_70(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // base: 0
  // info: 1
  // print_type_info: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 756: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_71;
}
static void cont__38_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 756: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_72;
}
static void cont__38_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 756: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__38_73, 0);
  // 756: ... kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_76;
}
static void entry__38_73(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 756: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__38_74;
}
static void cont__38_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 756: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__38_75;
}
static void cont__38_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 756: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 756: ... :
  // 757:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__38_77, 0);
  // 756: if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 757:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_69(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 755: ... : (_base info)
  // 756:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 757:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_70, 2);
  // 755: for_each definitions: (_base info)
  // 756:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 757:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_40(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 735: ... :
  // 736:   (
  // 737:     info
  // 738:     indent = 0
  // 739:   )
  // 740:   TR:
  // 741:     $qname name_of(info)
  // 742:     $remark_lines remark_lines_of(info)
  // 743:     if qname.is_defined:
  // 744:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_41_print_type_info, -1);
  // 735: $print_type_info:
  // 736:   (
  // 737:     info
  // 738:     indent = 0
  // 739:   )
  // 740:   TR:
  // 741:     $qname name_of(info)
  // 742:     $remark_lines remark_lines_of(info)
  // 743:     if qname.is_defined:
  // 744:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 752: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__38_67;
}
static void entry__38_64(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // name: 0
  // print_type_info: 1
  // indent: 2
  frame->slots[1] = myself->closure.frame->slots[2]; /* print_type_info */
  frame->slots[2] = myself->closure.frame->slots[1]; /* indent */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 750: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__38_65;
}
static void cont__38_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 750: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__38_66;
}
static void cont__38_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 750: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_42(void) {
  allocate_initialized_frame_gc(3, 9);
  // slot allocations:
  // info: 0
  // indent: 1
  // print_type_info: 2
  // qname: 3
  // remark_lines: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[2] = myself->closure.frame->slots[2]; /* print_type_info */
  frame->slots[3] /* qname */ = create_future();
  frame->slots[4] /* remark_lines */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 741: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__38_43;
}
static void cont__38_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 742: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__38_44;
}
static void cont__38_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 743: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_45;
}
static void cont__38_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 743: ... :
  // 744:   TD:
  // 745:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__38_46, 0);
  // 743: if qname.is_defined:
  // 744:   TD:
  // 745:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_53;
}
static void entry__38_47(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // indent: 0
  // qname: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* indent */
  frame->slots[1] = myself->closure.frame->slots[1]; /* qname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 745: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__38_48;
}
static void cont__38_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 745: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__38_49;
}
static void cont__38_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 746: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__38_50;
}
static void cont__38_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 746: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_51;
}
static void cont__38_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 746: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_52;
}
static void cont__38_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 746: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_46(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // indent: 0
  // qname: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* indent */
  frame->slots[1] = myself->closure.frame->slots[3]; /* qname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... :
  // 745:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_47, 0);
  // 744: TD:
  // 745:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 747: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_54;
}
static void cont__38_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 747: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__38_55, 0);
  // 747: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_58;
}
static void entry__38_55(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 747: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__38_56;
}
static void cont__38_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 747: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__38_57;
}
static void cont__38_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 747: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 747: ... :
  // 748:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__38_59, 0);
  // 747: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 748:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_62;
}
static void entry__38_59(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 748: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__38_60;
}
static void cont__38_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 748: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__38_61;
}
static void cont__38_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 748: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_62(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 749: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__38_63;
}
static void cont__38_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 749: ... : (name)
  // 750:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__38_64, 1);
  // 749: for_each derived_types_of(info): (name)
  // 750:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_41_print_type_info(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // info: 0
  // indent: 1
  // print_type_info: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  if (argument_count > 2) {
    too_many_arguments_error();
    return;
  }
  switch(argument_count) {
    default: frame->slots[1] /* indent */ = arguments->slots[1];
    case 1:;
  }
  switch(argument_count) {
    case 1: frame->slots[1] /* indent */ = number__0;
  }
  // 740: ... :
  // 741:   $qname name_of(info)
  // 742:   $remark_lines remark_lines_of(info)
  // 743:   if qname.is_defined:
  // 744:     TD:
  // 745:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:       A "href" = "@(qname.mangled).html" qname
  // 747:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 748:     TD remark_lines.to_paragraphs(1)
  // 749:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_42, 0);
  // 740: TR:
  // 741:   $qname name_of(info)
  // 742:   $remark_lines remark_lines_of(info)
  // 743:   if qname.is_defined:
  // 744:     TD:
  // 745:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 746:       A "href" = "@(qname.mangled).html" qname
  // 747:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 748:     TD remark_lines.to_paragraphs(1)
  // 749:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_17;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__38_68;
}
static void cont__38_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 754: ... :
  // 755:   for_each definitions: (_base info)
  // 756:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 757:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_69, 0);
  // 754: TABLE:
  // 755:   for_each definitions: (_base info)
  // 756:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 757:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 759: create_page "html/symbol_index.html":
  // 760:   link_bar
  // 761:   H1 "id" = "index" "Symbol Index"
  // 762:   from_to
  // 763:     'a'
  // 764:     'z': (letter)
  // 765:       A "href" = "#@(letter)" letter.to_upper_case
  // 766:     :
  // 767:       TEXT " "
  // 768:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_79;
  arguments->slots[1] = func__38_80;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__38_173;
}
static void entry__38_159(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // remark: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* remark */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 807: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_160;
  arguments->slots[1] = string__38_161;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_162;
}
static void cont__38_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 807: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__38_163;
}
static void cont__38_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 807: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__38_164;
}
static void cont__38_164(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 808: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_165, 0);
  // 808: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__38_170;
}
static void entry__38_165(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 808: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__38_166;
}
static void cont__38_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 808: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_167;
}
static void cont__38_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 808: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_168;
}
static void cont__38_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 808: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__38_169;
}
static void cont__38_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 808: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_170(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 809: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_347;
  arguments->slots[1] = string__38_171;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_172;
}
static void cont__38_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 809: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_158(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // remark: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  frame->slots[1] = myself->closure.frame->slots[3]; /* remark */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 806: ... :
  // 807:   TD "align" = "right" name .until. "::"
  // 808:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 809:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_159, 0);
  // 806: TR:
  // 807:   TD "align" = "right" name .until. "::"
  // 808:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 809:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_96(void) {
  allocate_initialized_frame_gc(3, 11);
  // slot allocations:
  // iname: 0
  // info: 1
  // letter: 2
  // remark: 3
  // name: 4
  // remark_lines: 5
  // kind_info: 6
  frame->slots[2] = myself->closure.frame->slots[0]; /* letter */
  frame->slots[3] /* remark */ = create_cell();
  frame->slots[4] /* name */ = create_future();
  frame->slots[5] /* remark_lines */ = create_future();
  frame->slots[6] /* kind_info */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 772: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__38_97;
}
static void cont__38_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 772: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_98;
}
static void cont__38_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 772: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_99;
}
static void cont__38_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 772: ... :
  // 773:   !letter iname(1)
  // 774:   TR:
  // 775:     TD "colspan" = 3:
  // 776:       H2 "id" = letter:
  // 777:         TEXT letter.to_upper_case
  // 778:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__38_100, 0);
  // 772: if iname(1) != letter:
  // 773:   !letter iname(1)
  // 774:   TR:
  // 775:     TD "colspan" = 3:
  // 776:       H2 "id" = letter:
  // 777:         TEXT letter.to_upper_case
  // 778:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_113;
}
static void entry__38_107(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 777: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__38_108;
}
static void cont__38_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 777: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__38_109;
}
static void cont__38_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__38_110;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_111;
}
static void cont__38_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 778: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__38_112;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_105(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 776: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_82;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_106;
}
static void cont__38_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 776: ... :
  // 777:   TEXT letter.to_upper_case
  // 778:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__38_107, 0);
  // 776: H2 "id" = letter:
  // 777:   TEXT letter.to_upper_case
  // 778:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_102(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 775: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_103;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_104;
}
static void cont__38_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 775: ... :
  // 776:   H2 "id" = letter:
  // 777:     TEXT letter.to_upper_case
  // 778:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__38_105, 0);
  // 775: TD "colspan" = 3:
  // 776:   H2 "id" = letter:
  // 777:     TEXT letter.to_upper_case
  // 778:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_100(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // letter: 0
  // iname: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* letter */
  frame->slots[1] = myself->closure.frame->slots[0]; /* iname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 773: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__38_101;
}
static void cont__38_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 774: ... :
  // 775:   TD "colspan" = 3:
  // 776:     H2 "id" = letter:
  // 777:       TEXT letter.to_upper_case
  // 778:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_102, 0);
  // 774: TR:
  // 775:   TD "colspan" = 3:
  // 776:     H2 "id" = letter:
  // 777:       TEXT letter.to_upper_case
  // 778:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 779: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 780: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__38_114;
}
static void cont__38_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 781: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__38_115;
}
static void cont__38_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 782: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_116;
}
static void cont__38_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 782: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__38_117, 0);
  // 782: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_120;
}
static void entry__38_117(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 782: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__38_118;
}
static void cont__38_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 782: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__38_119;
}
static void cont__38_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 782: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 782: ... :
  // 783:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__38_121, 0);
  // 782: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 783:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_124;
}
static void entry__38_121(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // remark: 0
  // remark_lines: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* remark */
  frame->slots[1] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__38_122;
}
static void cont__38_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 783: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__38_123;
}
static void cont__38_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* remark */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_125;
}
static void cont__38_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 785: $kind_info
  // 786:   case
  // 787:     kind_of(info)
  // 788:     FUNCTION -> "function"
  // 789:     POLYMORPHIC_FUNCTION -> "polymorphic function"
  // 790:     POLYMORPHIC_ATTRIBUTE -> "polymorphic attribute"
  // 791:     INLINE_C_TYPE -> "inline-C type"
  // 792:     INLINE_C_OBJECT -> "inline-C object"
  // 793:     INLINE_C_FUNCTION -> "inline-C function"
  // 794:     UNIQUE_ITEM -> "unique item"
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__38_126;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = func__38_128;
  arguments->slots[5] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[6] = func__38_130;
  arguments->slots[7] = var._INLINE_C_TYPE;
  arguments->slots[8] = func__38_132;
  arguments->slots[9] = var._INLINE_C_OBJECT;
  arguments->slots[10] = func__38_134;
  arguments->slots[11] = var._INLINE_C_FUNCTION;
  arguments->slots[12] = func__38_136;
  arguments->slots[13] = var._UNIQUE_ITEM;
  arguments->slots[14] = func__38_138;
  arguments->slots[15] = var._CONSTANT;
  arguments->slots[16] = func__38_140;
  arguments->slots[17] = var._OTHER;
  arguments->slots[18] = func__38_142;
  arguments->slots[19] = func__38_144;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__38_145;
}
static void entry__38_126(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 788: ... -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_127;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_128(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 789: ... -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_129;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_130(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 790: ... -> "polymorphic attribute"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_131;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_132(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 791: ... -> "inline-C type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_133;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_134(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 792: ... -> "inline-C object"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_135;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_136(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 793: ... -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_137;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_138(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 794: ... -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_139;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_140(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 795: ... -> "constant"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_141;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_142(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 796: ... -> "other"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_143;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_144(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 797: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 799: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_146;
}
static void cont__38_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 799: ... :
  // 800:   if
  // 801:     remark.is_defined:
  // 802:       !remark string(remark " (" kind_info ")")
  // 803:     :
  // 804:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__38_147, 0);
  // 799: if kind_info.is_defined:
  // 800:   if
  // 801:     remark.is_defined:
  // 802:       !remark string(remark " (" kind_info ")")
  // 803:     :
  // 804:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_153;
}
static void entry__38_149(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // remark: 0
  // kind_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* remark */
  frame->slots[1] = myself->closure.frame->slots[1]; /* kind_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 802: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__38_150;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__36_87;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__38_151;
}
static void cont__38_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* remark */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_152(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // remark: 0
  // kind_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* remark */
  frame->slots[1] = myself->closure.frame->slots[1]; /* kind_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 804: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__38_147(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // remark: 0
  // kind_info: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* remark */
  frame->slots[1] = myself->closure.frame->slots[6]; /* kind_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 801: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_148;
}
static void cont__38_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 801: ... :
  // 802:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__38_149, 0);
  // 803: :
  // 804:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__38_152, 0);
  // 800: if
  // 801:   remark.is_defined:
  // 802:     !remark string(remark " (" kind_info ")")
  // 803:   :
  // 804:     !remark kind_info
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
static void cont__38_153(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 805: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_154;
}
static void cont__38_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 805: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__38_155, 0);
  // 805: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_157;
}
static void entry__38_155(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 805: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_156;
}
static void cont__38_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 805: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 805: ... :
  // 806:   TR:
  // 807:     TD "align" = "right" name .until. "::"
  // 808:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 809:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__38_158, 0);
  // 805: if remark.is_defined && name.is_defined:
  // 806:   TR:
  // 807:     TD "align" = "right" name .until. "::"
  // 808:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 809:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_95(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 770: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 771: ... : (iname info)
  // 772:   if iname(1) != letter:
  // 773:     !letter iname(1)
  // 774:     TR:
  // 775:       TD "colspan" = 3:
  // 776:         H2 "id" = letter:
  // 777:           TEXT letter.to_upper_case
  // 778:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 779:   $$remark undefined
  // 780:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_96, 2);
  // 771: for_each definitions: (iname info)
  // 772:   if iname(1) != letter:
  // 773:     !letter iname(1)
  // 774:     TR:
  // 775:       TD "colspan" = 3:
  // 776:         H2 "id" = letter:
  // 777:           TEXT letter.to_upper_case
  // 778:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 779:   $$remark undefined
  // 780:   $name name_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_80(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__38_81;
}
static void cont__38_81(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_82;
  arguments->slots[1] = string__38_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_84;
}
static void cont__38_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 761: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_22;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__38_85;
}
static void cont__38_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: from_to
  // 763:   'a'
  // 764:   'z': (letter)
  // 765:     A "href" = "#@(letter)" letter.to_upper_case
  // 766:   :
  // 767:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__38_86;
  arguments->slots[3] = func__38_91;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__38_93;
}
static void entry__38_86(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 765: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_87;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_88;
}
static void cont__38_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 765: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_89;
}
static void cont__38_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 765: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__38_90;
}
static void cont__38_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 765: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_91(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 767: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_92;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_93(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__38_94;
}
static void cont__38_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 769: TABLE:
  // 770:   $$letter undefined
  // 771:   for_each definitions: (iname info)
  // 772:     if iname(1) != letter:
  // 773:       !letter iname(1)
  // 774:       TR:
  // 775:         TD "colspan" = 3:
  // 776:           H2 "id" = letter:
  // 777:             TEXT letter.to_upper_case
  // 778:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_95;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_173(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 811: for_each definitions: (_iname info)
  // 812:   $name name_of(info)
  // 813:   create_info_page name info
  // 814:   case kind_of(info) INLINE_C_TYPE:
  // 815:     for_each methods_of(info): (method_name method_info)
  // 816:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__38_174;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_182;
}
static void entry__38_180(void) {
  allocate_initialized_frame_gc(3, 4);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // name: 2
  frame->slots[2] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 816: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__38_23;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__38_181;
}
static void cont__38_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 816: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_178(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 815: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__38_179;
}
static void cont__38_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 815: ... : (method_name method_info)
  // 816:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__38_180, 2);
  // 815: for_each methods_of(info): (method_name method_info)
  // 816:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_174(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // iname: 0
  // info: 1
  // name: 2
  frame->slots[2] /* name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 812: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__38_175;
}
static void cont__38_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 813: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__38_176;
}
static void cont__38_176(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__38_177;
}
static void cont__38_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 814: ... :
  // 815:   for_each methods_of(info): (method_name method_info)
  // 816:     create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__38_178, 0);
  // 814: case kind_of(info) INLINE_C_TYPE:
  // 815:   for_each methods_of(info): (method_name method_info)
  // 816:     create_info_page string(name "/" method_name) method_info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_182(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 818: create_page "html/topic_index.html":
  // 819:   link_bar
  // 820:   H1 "id" = "index" "Topic Index"
  // 821:   TABLE:
  // 822:     for_each topics: (topic _references)
  // 823:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 824:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_183;
  arguments->slots[1] = func__38_184;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__38_197;
}
static void entry__38_195(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // topic: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[1]; /* topic */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 824: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_196;
}
static void cont__38_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 824: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_194(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // filename: 0
  // topic: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* filename */
  frame->slots[1] = myself->closure.frame->slots[0]; /* topic */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 824: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_195, 0);
  // 824: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_189(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // topic: 0
  // references: 1
  // filename: 2
  frame->slots[2] /* filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 823: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__38_190;
}
static void cont__38_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 823: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__36_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_191;
}
static void cont__38_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 823: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__38_192;
}
static void cont__38_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 823: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__38_193;
}
static void cont__38_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 824: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_194, 0);
  // 824: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_188(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 822: for_each topics: (topic _references)
  // 823:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 824:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__38_189;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_184(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 819: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__38_185;
}
static void cont__38_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 820: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_82;
  arguments->slots[1] = string__38_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_186;
}
static void cont__38_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 820: H1 "id" = "index" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_27;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__38_187;
}
static void cont__38_187(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 821: TABLE:
  // 822:   for_each topics: (topic _references)
  // 823:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 824:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_188;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_197(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 825: for_each topics: (topic references)
  // 826:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 827:   create_page "html/@(filename).html":
  // 828:     link_bar
  // 829:     H1 "id" = "index" topic
  // 830:     TABLE:
  // 831:       for_each references: (reference)
  // 832:         TR:
  // 833:           TD: A "href" = string(reference.mangled ".html") reference
  // 834:           TD "&nbsp;"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__38_198;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_217;
}
static void entry__38_209(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 833: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_210, 0);
  // 833: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__38_214;
}
static void entry__38_210(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 833: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__38_211;
}
static void cont__38_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 833: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__36_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__38_212;
}
static void cont__38_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 833: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_213;
}
static void cont__38_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 833: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_214(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 834: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__38_215;
}
static void cont__38_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 835: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__38_216;
}
static void cont__38_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 835: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_208(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 832: ... :
  // 833:   TD: A "href" = string(reference.mangled ".html") reference
  // 834:   TD "&nbsp;"
  // 835:   TD short_descriptions(reference)
  frame->slots[1] /* temp__1 */ = create_closure(entry__38_209, 0);
  // 832: TR:
  // 833:   TD: A "href" = string(reference.mangled ".html") reference
  // 834:   TD "&nbsp;"
  // 835:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_207(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 831: for_each references: (reference)
  // 832:   TR:
  // 833:     TD: A "href" = string(reference.mangled ".html") reference
  // 834:     TD "&nbsp;"
  // 835:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__38_208;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_203(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // topic: 0
  // references: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic */
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 828: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__38_204;
}
static void cont__38_204(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 829: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_82;
  arguments->slots[1] = string__38_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_205;
}
static void cont__38_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 829: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__38_206;
}
static void cont__38_206(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 830: ... :
  // 831:   for_each references: (reference)
  // 832:     TR:
  // 833:       TD: A "href" = string(reference.mangled ".html") reference
  // 834:       TD "&nbsp;"
  // 835:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__38_207, 0);
  // 830: TABLE:
  // 831:   for_each references: (reference)
  // 832:     TR:
  // 833:       TD: A "href" = string(reference.mangled ".html") reference
  // 834:       TD "&nbsp;"
  // 835:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_198(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // topic: 0
  // references: 1
  // filename: 2
  frame->slots[2] /* filename */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 826: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__38_199;
}
static void cont__38_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 826: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__36_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_200;
}
static void cont__38_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 826: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__38_201;
}
static void cont__38_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 827: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__36_17;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__36_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_202;
}
static void cont__38_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 827: ... :
  // 828:   link_bar
  // 829:   H1 "id" = "index" topic
  // 830:   TABLE:
  // 831:     for_each references: (reference)
  // 832:       TR:
  // 833:         TD: A "href" = string(reference.mangled ".html") reference
  // 834:         TD "&nbsp;"
  // 835:         TD short_descriptions(reference)
  frame->slots[4] /* temp__2 */ = create_closure(entry__38_203, 0);
  // 827: create_page "html/@(filename).html":
  // 828:   link_bar
  // 829:   H1 "id" = "index" topic
  // 830:   TABLE:
  // 831:     for_each references: (reference)
  // 832:       TR:
  // 833:         TD: A "href" = string(reference.mangled ".html") reference
  // 834:         TD "&nbsp;"
  // 835:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 836: create_page "html/index.html":
  // 837:   H1 "Simplicity"
  // 838:   P: A "href" = "manual.html" "Manual"
  // 839:   P: A "href" = "type_index.html" "Type Index"
  // 840:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 841:   P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__38_218;
  arguments->slots[1] = func__38_219;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__38_233;
}
static void entry__38_231(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 841: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_232;
}
static void cont__38_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 841: ... A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_219(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 837: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__38_220;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__38_221;
}
static void cont__38_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 838: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_222;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__38_224;
}
static void entry__38_222(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 838: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_223;
}
static void cont__38_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 838: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_12;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_224(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 839: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_225;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__38_227;
}
static void entry__38_225(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 839: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_226;
}
static void cont__38_226(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 839: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_17;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_227(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 840: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_228;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__38_230;
}
static void entry__38_228(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 840: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__38_229;
}
static void cont__38_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 840: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_22;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_230(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 841: P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__38_231;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_233(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 843: if do_print_summary:
  // 844:   $$total_functions 0
  // 845:   $$total_polymorphic_functions 0
  // 846:   $$total_polymorphic_attributes 0
  // 847:   $$total_methods 0
  // 848:   $$total_inline_c_methods 0
  // 849:   $$total_inline_c_types 0
  // 850:   $$total_inline_c_objects 0
  // 851:   $$total_attributes 0
  // 852:   $$total_inline_c_functions 0
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_summary();
  arguments->slots[1] = func__38_234;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
EXPORT void collect__extractor(void) {
  var._filename_of = collect_node(var._filename_of);
  var._used_namespaces_of = collect_node(var._used_namespaces_of);
  var._derived_types_of = collect_node(var._derived_types_of);
  var._methods_of = collect_node(var._methods_of);
  var._types_of = collect_node(var._types_of);
  var._polymorphic_functions = collect_node(var._polymorphic_functions);
  var._definitions = collect_node(var._definitions);
  var._short_descriptions = collect_node(var._short_descriptions);
  var._topics = collect_node(var._topics);
  var._missing_documentation_count = collect_node(var._missing_documentation_count);
  var._FUNCTION = collect_node(var._FUNCTION);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._POLYMORPHIC_ATTRIBUTE = collect_node(var._POLYMORPHIC_ATTRIBUTE);
  var._INLINE_C_TYPE = collect_node(var._INLINE_C_TYPE);
  var._INLINE_C_OBJECT = collect_node(var._INLINE_C_OBJECT);
  var._INLINE_C_FUNCTION = collect_node(var._INLINE_C_FUNCTION);
  var._UNIQUE_ITEM = collect_node(var._UNIQUE_ITEM);
  var._CONSTANT = collect_node(var._CONSTANT);
  var._OTHER = collect_node(var._OTHER);
  var._PARAMETER_COUNT_OR_MYSELF = collect_node(var._PARAMETER_COUNT_OR_MYSELF);
  var._path_prefix = collect_node(var._path_prefix);
  var._create_page = collect_node(var._create_page);
  var._symbol_info = collect_node(var._symbol_info);
  var._extract_documentation_from_file = collect_node(var._extract_documentation_from_file);
  var._extract_documentation_from_directory = collect_node(var._extract_documentation_from_directory);
  var._resolved_name = collect_node(var._resolved_name);
  var._add_derived_type = collect_node(var._add_derived_type);
  var._mangled = collect_node(var._mangled);
  var._ordered_name = collect_node(var._ordered_name);
  var._link_bar = collect_node(var._link_bar);
  var._TOPIC = collect_node(var._TOPIC);
  var._EXAMPLE = collect_node(var._EXAMPLE);
  var._to_paragraphs = collect_node(var._to_paragraphs);
  var._resolve_reference = collect_node(var._resolve_reference);
  var._add_links = collect_node(var._add_links);
  var._create_info_page = collect_node(var._create_info_page);
  var._get_short_description = collect_node(var._get_short_description);
  var.sim2c__extract_documentation = collect_node(var.sim2c__extract_documentation);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__extractor(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  register_polymorphic_function_with_setter("_extractor::filename_of", &poly_idx__filename_of);
  register_polymorphic_function_with_setter("_extractor::used_namespaces_of", &poly_idx__used_namespaces_of);
  register_polymorphic_function_with_setter("_extractor::derived_types_of", &poly_idx__derived_types_of);
  register_polymorphic_function_with_setter("_extractor::methods_of", &poly_idx__methods_of);
  register_polymorphic_function_with_setter("_extractor::types_of", &poly_idx__types_of);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__extractor(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__35 = from_uchar32(35);
  character__122 = from_uchar32(122);
  character__47 = from_uchar32(47);
  number__80 = from_uint32(80U);
  character__63 = from_uchar32(63);
  character__44 = from_uchar32(44);
  character__58 = from_uchar32(58);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  character__60 = from_uchar32(60);
  character__34 = from_uchar32(34);
  number__5 = from_uint32(5U);
  character__36 = from_uchar32(36);
  character__91 = from_uchar32(91);
  character__32 = from_uchar32(32);
  character__61 = from_uchar32(61);
  character__97 = from_uchar32(97);
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  character__42 = from_uchar32(42);
  character__62 = from_uchar32(62);
  unique__FUNCTION = register_unique_item("FUNCTION");
  unique__POLYMORPHIC_FUNCTION = register_unique_item("POLYMORPHIC_FUNCTION");
  unique__POLYMORPHIC_ATTRIBUTE = register_unique_item("POLYMORPHIC_ATTRIBUTE");
  unique__INLINE_C_TYPE = register_unique_item("INLINE_C_TYPE");
  unique__INLINE_C_OBJECT = register_unique_item("INLINE_C_OBJECT");
  unique__INLINE_C_FUNCTION = register_unique_item("INLINE_C_FUNCTION");
  unique__UNIQUE_ITEM = register_unique_item("UNIQUE_ITEM");
  unique__CONSTANT = register_unique_item("CONSTANT");
  unique__OTHER = register_unique_item("OTHER");
  string__22_5 = from_latin_1_string("body {\012  background-color: white;\012  font-family: Times New Roman, Times;\012  font-size: 12pt;\012  color: #222;\012}\012h1 {\012  font-family: Arial, Helvetica;\012  font-size: 20pt;\012  color: #333;\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012h2 {\012  font-family: Arial, Helvetica;\012  font-size: 16pt;\012  color: #222;\012  margin-top: 5pt;\012  margin-bottom: 5pt;\012}\012h3 {\012  font-family: Arial, Helvetica;\012  font-size: 14pt;\012  color: #222;\012  margin-top: 3pt;\012  margin-bottom: 3pt;\012}\012h4 {\012  font-family: Arial, Helvetica;\012  font-size: 13pt;\012  color: #222;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012dt {\012  font-style: italic;\012  margin-bottom: 4pt;\012}\012dd {\012  padding-left: 0pt;\012  margin-left: 16pt;\012  margin-top: 0pt;\012  margin-bottom: 0pt;\012}\012p {\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012a {\012  text-decoration: none;\012}\012div.Example {\012  background-color: #ffc;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.Output {\012  background-color: #cff;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.footer {\012  padding-top: 10pt;\012  font-size: 10pt;\012}\012pre {\012  font-family: Courier New, Courier;\012  font-size: 12pt;\012  padding-top: 0pt;\012  padding-bottom: 0pt;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012td.remark {\012  padding-left: 10pt;\012}\012", 1234);
  func__22_4 = create_function(entry__22_4, 0);
  func__22_1_create_page = create_function(entry__22_1_create_page, 2);
  string__24_2 = from_latin_1_string("extracting documentation from ", 30);
  string__24_3 = from_latin_1_string("\012", 1);
  string__24_11 = from_latin_1_string("Empty source text!", 18);
  func__24_10 = create_function(entry__24_10, 0);
  string__24_17 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__24_16 = create_function(entry__24_16, 0);
  string__24_24 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__24_23 = create_function(entry__24_23, 0);
  string__24_26 = from_latin_1_string(".sim", 4);
  string__24_28 = from_latin_1_string("__", 2);
  func__24_32 = create_function(entry__24_32, 1);
  string__24_55 = from_latin_1_string("std", 3);
  func__24_54 = create_function(entry__24_54, 0);
  func__24_61 = create_function(entry__24_61, 0);
  func__24_64 = create_function(entry__24_64, 0);
  func__24_87 = create_function(entry__24_87, 0);
  func__24_107 = create_function(entry__24_107, 0);
  string__24_117 = from_latin_1_string("type", 4);
  string__24_118 = from_latin_1_string("object", 6);
  func__24_142 = create_function(entry__24_142, 0);
  func__24_143 = create_function(entry__24_143, 0);
  string__24_157 = from_latin_1_string("types::function", 15);
  func__24_1_extract_documentation_from_file = create_function(entry__24_1_extract_documentation_from_file, 1);
  func__25_4 = create_function(entry__25_4, 1);
  func__25_1_extract_documentation_from_directory = create_function(entry__25_1_extract_documentation_from_directory, 1);
  string__26_14 = from_latin_1_string("The attribute \042", 15);
  string__26_15 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__26_21 = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__26_24 = from_latin_1_string("::", 2);
  func__26_1_resolved_name = create_function(entry__26_1_resolved_name, 1);
  func__27_1_add_derived_type = create_function(entry__27_1_add_derived_type, 2);
  string__28_3 = from_latin_1_string("___", 3);
  func__28_1_mangled = create_function(entry__28_1_mangled, 1);
  func__29_1_ordered_name = create_function(entry__29_1_ordered_name, 2);
  string__30_3 = from_latin_1_string("href", 4);
  string__30_4 = from_latin_1_string("index.html", 10);
  string__30_6 = from_latin_1_string("Home", 4);
  string__30_8 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__30_10 = from_latin_1_string("manual.html", 11);
  string__30_12 = from_latin_1_string("Manual", 6);
  string__30_15 = from_latin_1_string("type_index.html", 15);
  string__30_17 = from_latin_1_string("Type Index", 10);
  string__30_20 = from_latin_1_string("symbol_index.html", 17);
  string__30_22 = from_latin_1_string("Symbol Index", 12);
  string__30_25 = from_latin_1_string("topic_index.html", 16);
  string__30_27 = from_latin_1_string("Topic Index", 11);
  func__30_2 = create_function(entry__30_2, 0);
  func__30_1_link_bar = create_function(entry__30_1_link_bar, 0);
  func__33_1_to_paragraphs = create_function(entry__33_1_to_paragraphs, 1);
  string__34_8 = from_latin_1_string("types::", 7);
  string__34_13 = from_latin_1_string("std::", 5);
  func__34_1_resolve_reference = create_function(entry__34_1_resolve_reference, 1);
  string__35_10 = from_latin_1_string("[", 1);
  string__35_11 = from_latin_1_string("](", 2);
  string__35_12 = from_latin_1_string(".html)", 6);
  func__35_5 = create_function(entry__35_5, 1);
  func__35_1_add_links = create_function(entry__35_1_add_links, 1);
  string__36_8 = from_latin_1_string("The documentation for \042", 23);
  string__36_9 = from_latin_1_string("\042\012(defined in \042", 15);
  string__36_10 = from_latin_1_string("\042)\012references the undefined symbol \042", 36);
  string__36_11 = from_latin_1_string("\042!\012", 3);
  string__36_17 = from_latin_1_string("html/", 5);
  string__36_18 = from_latin_1_string(".html", 5);
  string__36_28 = from_latin_1_string(".html)/[", 8);
  string__36_34 = from_latin_1_string("(static multi-assignment variable)", 34);
  func__36_33 = create_function(entry__36_33, 0);
  string__36_36 = from_latin_1_string("(dynamic single-assignment variable)", 36);
  func__36_35 = create_function(entry__36_35, 0);
  string__36_38 = from_latin_1_string("(dynamic multi-assignment variable)", 35);
  func__36_37 = create_function(entry__36_37, 0);
  string__36_49 = from_latin_1_string("Missing documentation for ", 26);
  string__36_50 = from_latin_1_string(" (defined in \042", 14);
  string__36_51 = from_latin_1_string("\042)!\012", 4);
  string__36_60 = from_latin_1_string("Parameter", 9);
  string__36_70 = from_latin_1_string(" (optional)", 11);
  string__36_77 = from_latin_1_string(" (zero or more arguments)", 25);
  string__36_86 = from_latin_1_string(" (optional; default value: ", 27);
  string__36_87 = from_latin_1_string(")", 1);
  string__36_96 = from_latin_1_string("Returns", 7);
  string__36_119 = from_latin_1_string("See also:", 9);
  string__36_149 = from_latin_1_string("Technical Details:", 18);
  func__36_213 = create_function(entry__36_213, 0);
  func__36_217 = create_function(entry__36_217, 0);
  string__36_224 = from_latin_1_string("Parameters", 10);
  func__36_227 = create_function(entry__36_227, 1);
  func__36_237 = create_function(entry__36_237, 1);
  string__36_245 = from_latin_1_string("Description", 11);
  func__36_247 = create_function(entry__36_247, 1);
  string__36_251 = from_latin_1_string("Technical Details", 17);
  func__36_253 = create_function(entry__36_253, 1);
  string__36_257 = from_latin_1_string("See also", 8);
  string__36_268 = from_latin_1_string("&nbsp;", 6);
  string__36_275 = from_latin_1_string("Implemented by", 14);
  string__36_287 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__36_297 = from_latin_1_string("Implements", 10);
  string__36_306 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__36_328 = from_latin_1_string("Topics", 6);
  string__36_333 = from_latin_1_string("_", 1);
  func__36_331 = create_function(entry__36_331, 1);
  string__36_347 = from_latin_1_string("class", 5);
  func__36_354 = create_function(entry__36_354, 1);
  string__36_356 = from_latin_1_string("**", 2);
  string__36_361 = from_latin_1_string("footer", 6);
  string__36_365 = from_latin_1_string("(defined in ", 12);
  string__36_366 = from_latin_1_string(")\012", 2);
  func__36_1_create_info_page = create_function(entry__36_1_create_info_page, 2);
  string__37_27 = from_latin_1_string("\012The short description for \042", 28);
  string__37_28 = from_latin_1_string("\042)\012is quite long:\012", 18);
  func__37_1_get_short_description = create_function(entry__37_1_get_short_description, 2);
  string__38_23 = from_latin_1_string("/", 1);
  func__38_5 = create_function(entry__38_5, 2);
  string__38_39 = from_latin_1_string("html/type_index.html", 20);
  func__38_40 = create_function(entry__38_40, 0);
  string__38_79 = from_latin_1_string("html/symbol_index.html", 22);
  string__38_82 = from_latin_1_string("id", 2);
  string__38_83 = from_latin_1_string("index", 5);
  string__38_87 = from_latin_1_string("#", 1);
  func__38_86 = create_function(entry__38_86, 1);
  string__38_92 = from_latin_1_string(" ", 1);
  func__38_91 = create_function(entry__38_91, 0);
  string__38_103 = from_latin_1_string("colspan", 7);
  string__38_110 = from_latin_1_string("#index", 6);
  string__38_112 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__38_127 = from_latin_1_string("function", 8);
  func__38_126 = create_function(entry__38_126, 0);
  string__38_129 = from_latin_1_string("polymorphic function", 20);
  func__38_128 = create_function(entry__38_128, 0);
  string__38_131 = from_latin_1_string("polymorphic attribute", 21);
  func__38_130 = create_function(entry__38_130, 0);
  string__38_133 = from_latin_1_string("inline-C type", 13);
  func__38_132 = create_function(entry__38_132, 0);
  string__38_135 = from_latin_1_string("inline-C object", 15);
  func__38_134 = create_function(entry__38_134, 0);
  string__38_137 = from_latin_1_string("inline-C function", 17);
  func__38_136 = create_function(entry__38_136, 0);
  string__38_139 = from_latin_1_string("unique item", 11);
  func__38_138 = create_function(entry__38_138, 0);
  string__38_141 = from_latin_1_string("constant", 8);
  func__38_140 = create_function(entry__38_140, 0);
  string__38_143 = from_latin_1_string("other", 5);
  func__38_142 = create_function(entry__38_142, 0);
  func__38_144 = create_function(entry__38_144, 0);
  string__38_150 = from_latin_1_string(" (", 2);
  string__38_160 = from_latin_1_string("align", 5);
  string__38_161 = from_latin_1_string("right", 5);
  string__38_171 = from_latin_1_string("remark", 6);
  func__38_95 = create_function(entry__38_95, 0);
  func__38_80 = create_function(entry__38_80, 0);
  func__38_174 = create_function(entry__38_174, 2);
  string__38_183 = from_latin_1_string("html/topic_index.html", 21);
  func__38_189 = create_function(entry__38_189, 2);
  func__38_188 = create_function(entry__38_188, 0);
  func__38_184 = create_function(entry__38_184, 0);
  func__38_208 = create_function(entry__38_208, 1);
  func__38_198 = create_function(entry__38_198, 2);
  string__38_218 = from_latin_1_string("html/index.html", 15);
  string__38_220 = from_latin_1_string("Simplicity", 10);
  func__38_222 = create_function(entry__38_222, 0);
  func__38_225 = create_function(entry__38_225, 0);
  func__38_228 = create_function(entry__38_228, 0);
  func__38_231 = create_function(entry__38_231, 0);
  func__38_219 = create_function(entry__38_219, 0);
  string__38_292 = from_latin_1_string("total definitions:     ", 23);
  string__38_293 = from_latin_1_string("\012\012functions:             ", 25);
  string__38_294 = from_latin_1_string("\012polymorphic functions: ", 24);
  string__38_295 = from_latin_1_string("\012polymorphic attributes:", 24);
  string__38_296 = from_latin_1_string("\012method definitions:    ", 24);
  string__38_297 = from_latin_1_string("\012inline C methods:      ", 24);
  string__38_298 = from_latin_1_string("\012attribute definitions: ", 24);
  string__38_299 = from_latin_1_string("\012inline C functions:    ", 24);
  string__38_300 = from_latin_1_string("\012inline C types:        ", 24);
  string__38_301 = from_latin_1_string("\012inline C objects:      ", 24);
  string__38_302 = from_latin_1_string("\012unique items:          ", 24);
  string__38_303 = from_latin_1_string("\012other constants:       ", 24);
  string__38_304 = from_latin_1_string("\012other:                 ", 24);
  string__38_305 = from_latin_1_string("\012\012missing documentation: ", 25);
  func__38_234 = create_function(entry__38_234, 0);
  func__38_1_sim2c__extract_documentation = create_function(entry__38_1_sim2c__extract_documentation, 1);
  string__69_1 = from_latin_1_string("Topic", 5);
  string__70_1 = from_latin_1_string("Example", 7);
  string__70_2 = from_latin_1_string("Output", 6);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__extractor(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  assign_value(&var._FUNCTION, unique__FUNCTION);
  assign_value(&var._POLYMORPHIC_FUNCTION, unique__POLYMORPHIC_FUNCTION);
  assign_value(&var._POLYMORPHIC_ATTRIBUTE, unique__POLYMORPHIC_ATTRIBUTE);
  assign_value(&var._INLINE_C_TYPE, unique__INLINE_C_TYPE);
  assign_value(&var._INLINE_C_OBJECT, unique__INLINE_C_OBJECT);
  assign_value(&var._INLINE_C_FUNCTION, unique__INLINE_C_FUNCTION);
  assign_value(&var._UNIQUE_ITEM, unique__UNIQUE_ITEM);
  assign_value(&var._CONSTANT, unique__CONSTANT);
  assign_value(&var._OTHER, unique__OTHER);
  var._PARAMETER_COUNT_OR_MYSELF = create_future();
  var._symbol_info = create_future();
  var._TOPIC = create_future();
  var._EXAMPLE = create_future();
  define_single_assign_static("sim2c", "extract_documentation", get__sim2c__extract_documentation, &var.sim2c__extract_documentation);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__extractor(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "A", &get__A, &get_value_or_future__A);
  use_read_only(NULL, "ANY_CHARACTER", &get__ANY_CHARACTER, &get_value_or_future__ANY_CHARACTER);
  use_read_only(NULL, "ATTRIBUTE_KIND", &get__ATTRIBUTE_KIND, &get_value_or_future__ATTRIBUTE_KIND);
  use_read_only(NULL, "BODY", &get__BODY, &get_value_or_future__BODY);
  use_read_only(NULL, "BR", &get__BR, &get_value_or_future__BR);
  use_read_only(NULL, "CONTINUATION_PARAMETER", &get__CONTINUATION_PARAMETER, &get_value_or_future__CONTINUATION_PARAMETER);
  use_read_only(NULL, "DD", &get__DD, &get_value_or_future__DD);
  use_read_only(NULL, "DIV", &get__DIV, &get_value_or_future__DIV);
  use_read_only(NULL, "DL", &get__DL, &get_value_or_future__DL);
  use_read_only(NULL, "DT", &get__DT, &get_value_or_future__DT);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "H1", &get__H1, &get_value_or_future__H1);
  use_read_only(NULL, "H2", &get__H2, &get_value_or_future__H2);
  use_read_only(NULL, "HEAD", &get__HEAD, &get_value_or_future__HEAD);
  use_read_only(NULL, "HTML", &get__HTML, &get_value_or_future__HTML);
  use_read_only(NULL, "IDENTIFIER", &get__IDENTIFIER, &get_value_or_future__IDENTIFIER);
  use_read_only(NULL, "METHOD_KIND", &get__METHOD_KIND, &get_value_or_future__METHOD_KIND);
  use_read_only(NULL, "MYSELF_PARAMETER", &get__MYSELF_PARAMETER, &get_value_or_future__MYSELF_PARAMETER);
  use_read_only(NULL, "NAME", &get__NAME, &get_value_or_future__NAME);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "P", &get__P, &get_value_or_future__P);
  use_read_only(NULL, "PRE", &get__PRE, &get_value_or_future__PRE);
  use_read_only(NULL, "SORT", &get__SORT, &get_value_or_future__SORT);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STYLE", &get__STYLE, &get_value_or_future__STYLE);
  use_read_only(NULL, "TABLE", &get__TABLE, &get_value_or_future__TABLE);
  use_read_only(NULL, "TD", &get__TD, &get_value_or_future__TD);
  use_read_only(NULL, "TEXT", &get__TEXT, &get_value_or_future__TEXT);
  use_read_only(NULL, "TR", &get__TR, &get_value_or_future__TR);
  use_read_only(NULL, "alt", &get__alt, &get_value_or_future__alt);
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_read_only(NULL, "arguments_of", &get__arguments_of, &get_value_or_future__arguments_of);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_polymorphic_function(NULL, "attribute_of", &get__attribute_of, &poly_idx__attribute_of);
  use_polymorphic_function(NULL, "base_of", &get__base_of, &poly_idx__base_of);
  use_read_only(NULL, "before", &get__before, &get_value_or_future__before);
  use_read_only(NULL, "behind", &get__behind, &get_value_or_future__behind);
  use_read_only(NULL, "between", &get__between, &get_value_or_future__between);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "collect_output", &get__collect_output, &get_value_or_future__collect_output);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_read_only(NULL, "contains", &get__contains, &get_value_or_future__contains);
  use_read_only(NULL, "cut_into_fragments", &get__cut_into_fragments, &get_value_or_future__cut_into_fragments);
  use_read_only(NULL, "default_value", &get__default_value, &get_value_or_future__default_value);
  use_read_only(NULL, "default_value_of", &get__default_value_of, &get_value_or_future__default_value_of);
  use_read_only(NULL, "directory", &get__directory, &get_value_or_future__directory);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_print_missing", &get__do_print_missing, &get_value_or_future__do_print_missing);
  use_read_only(NULL, "do_print_summary", &get__do_print_summary, &get_value_or_future__do_print_summary);
  use_read_only(NULL, "do_print_warnings", &get__do_print_warnings, &get_value_or_future__do_print_warnings);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "empty_insert_order_set", &get__empty_insert_order_set, &get_value_or_future__empty_insert_order_set);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_key_order_set", &get__empty_key_order_set, &get_value_or_future__empty_key_order_set);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "empty_table", &get__empty_table, &get_value_or_future__empty_table);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_read_only(NULL, "fullname_of", &get__fullname_of, &get_value_or_future__fullname_of);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "has_suffix", &get__has_suffix, &get_value_or_future__has_suffix);
  use_read_only(NULL, "identifier_of", &get__identifier_of, &get_value_or_future__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_only(NULL, "is_a_body", &get__is_a_body, &get_value_or_future__is_a_body);
  use_read_only(NULL, "is_a_c_body", &get__is_a_c_body, &get_value_or_future__is_a_c_body);
  use_read_only(NULL, "is_a_constant", &get__is_a_constant, &get_value_or_future__is_a_constant);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_read_only(NULL, "is_a_directory", &get__is_a_directory, &get_value_or_future__is_a_directory);
  use_read_only(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &get_value_or_future__is_a_polymorphic_function_constant);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
  use_read_only(NULL, "is_a_setter", &get__is_a_setter, &get_value_or_future__is_a_setter);
  use_read_only(NULL, "is_a_unique_item_constant", &get__is_a_unique_item_constant, &get_value_or_future__is_a_unique_item_constant);
  use_read_only(NULL, "is_an_assignment", &get__is_an_assignment, &get_value_or_future__is_an_assignment);
  use_read_only(NULL, "is_an_expanded_item", &get__is_an_expanded_item, &get_value_or_future__is_an_expanded_item);
  use_read_only(NULL, "is_an_identifier", &get__is_an_identifier, &get_value_or_future__is_an_identifier);
  use_read_only(NULL, "is_an_optional_item", &get__is_an_optional_item, &get_value_or_future__is_an_optional_item);
  use_read_only(NULL, "is_c_code", &get__is_c_code, &get_value_or_future__is_c_code);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "key_of", &get__key_of, &get_value_or_future__key_of);
  use_polymorphic_function(NULL, "kind_of", &get__kind_of, &poly_idx__kind_of);
  use_read_only(NULL, "length_of", &get__length_of, &get_value_or_future__length_of);
  use_read_only(NULL, "list", &get__list, &get_value_or_future__list);
  use_read_only(NULL, "load", &get__load, &get_value_or_future__load);
  use_read_only(NULL, "many", &get__many, &get_value_or_future__many);
  use_read_only(NULL, "multi_dimensional_set", &get__multi_dimensional_set, &get_value_or_future__multi_dimensional_set);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_read_only(NULL, "namespace_of", &get__namespace_of, &get_value_or_future__namespace_of);
  use_read_only(NULL, "newline", &get__newline, &get_value_or_future__newline);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_read_only(NULL, "not_followed_by", &get__not_followed_by, &get_value_or_future__not_followed_by);
  use_read_only(NULL, "optional", &get__optional, &get_value_or_future__optional);
  use_read_only(NULL, "output_arguments_of", &get__output_arguments_of, &get_value_or_future__output_arguments_of);
  use_read_only(NULL, "pad_left", &get__pad_left, &get_value_or_future__pad_left);
  use_read_only(NULL, "parameter_kind_of", &get__parameter_kind_of, &get_value_or_future__parameter_kind_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "parse_meta_instruction", &get__parse_meta_instruction, &get_value_or_future__parse_meta_instruction);
  use_read_only(NULL, "parse_statement", &get__parse_statement, &get_value_or_future__parse_statement);
  use_read_only(NULL, "pass", &get__pass, &get_value_or_future__pass);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_polymorphic_function(NULL, "remark_lines_of", &get__remark_lines_of, &poly_idx__remark_lines_of);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_read_only(NULL, "save", &get__save, &get_value_or_future__save);
  use_read_only(NULL, "sequence", &get__sequence, &get_value_or_future__sequence);
  use_read_only("sim2c", "WHITESPACE", &get__sim2c__WHITESPACE, &get_value_or_future__sim2c__WHITESPACE);
  use_multi_assign_dynamic("sim2c", "defined_namespaces", &get__sim2c__defined_namespaces, &set__sim2c__defined_namespaces, &define__sim2c__defined_namespaces);
  use_multi_assign_dynamic("sim2c", "enumeration_count", &get__sim2c__enumeration_count, &set__sim2c__enumeration_count, &define__sim2c__enumeration_count);
  use_multi_assign_dynamic("sim2c", "included_files", &get__sim2c__included_files, &set__sim2c__included_files, &define__sim2c__included_files);
  use_multi_assign_dynamic("sim2c", "linked_libraries", &get__sim2c__linked_libraries, &set__sim2c__linked_libraries, &define__sim2c__linked_libraries);
  use_single_assign_dynamic("sim2c", "module_name", &get__sim2c__module_name, &define__sim2c__module_name);
  use_multi_assign_dynamic("sim2c", "namespace_mappings", &get__sim2c__namespace_mappings, &set__sim2c__namespace_mappings, &define__sim2c__namespace_mappings);
  use_multi_assign_dynamic("sim2c", "required_modules", &get__sim2c__required_modules, &set__sim2c__required_modules, &define__sim2c__required_modules);
  use_multi_assign_dynamic("sim2c", "used_namespaces", &get__sim2c__used_namespaces, &set__sim2c__used_namespaces, &define__sim2c__used_namespaces);
  use_read_only(NULL, "some", &get__some, &get_value_or_future__some);
  use_read_only(NULL, "source_of", &get__source_of, &get_value_or_future__source_of);
  use_read_only(NULL, "split", &get__split, &get_value_or_future__split);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "less", &get__std__less, &get_value_or_future__std__less);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only("std", "true", &get__std__true, &get_value_or_future__std__true);
  use_read_only("std", "value_of", &get__std__value_of, &get_value_or_future__std__value_of);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
  use_read_only(NULL, "to_lower_case", &get__to_lower_case, &get_value_or_future__to_lower_case);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "to_upper_case", &get__to_upper_case, &get_value_or_future__to_upper_case);
  use_read_only(NULL, "tokenize", &get__tokenize, &get_value_or_future__tokenize);
  use_read_only(NULL, "trim", &get__trim, &get_value_or_future__trim);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only(NULL, "truncate_behind", &get__truncate_behind, &get_value_or_future__truncate_behind);
  use_read_only(NULL, "truncate_from", &get__truncate_from, &get_value_or_future__truncate_from);
  use_read_only(NULL, "truncate_until", &get__truncate_until, &get_value_or_future__truncate_until);
  use_read_only("types", "key_order_set", &get__types__key_order_set, &get_value_or_future__types__key_order_set);
  use_read_only("types", "key_order_table", &get__types__key_order_table, &get_value_or_future__types__key_order_table);
  use_read_only("types", "object", &get__types__object, &get_value_or_future__types__object);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "until", &get__until, &get_value_or_future__until);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_write(NULL, "used_namespaces", &get__used_namespaces, &set__used_namespaces);
  use_polymorphic_function(NULL, "variable_kind_of", &get__variable_kind_of, &poly_idx__variable_kind_of);
  use_read_only(NULL, "without_prefix", &get__without_prefix, &get_value_or_future__without_prefix);
  use_read_only(NULL, "without_suffix", &get__without_suffix, &get_value_or_future__without_suffix);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  use_read_only(NULL, "writeln_to", &get__writeln_to, &get_value_or_future__writeln_to);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__extractor(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var._filename_of, create_function(type__filename_of, -1));
  assign_value(&var._used_namespaces_of, create_function(type__used_namespaces_of, -1));
  assign_value(&var._derived_types_of, create_function(type__derived_types_of, -1));
  assign_value(&var._methods_of, create_function(type__methods_of, -1));
  assign_value(&var._types_of, create_function(type__types_of, -1));
  assign_variable(&var._create_page, &func__22_1_create_page);
  assign_variable(&var._extract_documentation_from_file, &func__24_1_extract_documentation_from_file);
  assign_variable(&var._extract_documentation_from_directory, &func__25_1_extract_documentation_from_directory);
  assign_variable(&var._resolved_name, &func__26_1_resolved_name);
  assign_variable(&var._add_derived_type, &func__27_1_add_derived_type);
  assign_variable(&var._mangled, &func__28_1_mangled);
  assign_variable(&var._ordered_name, &func__29_1_ordered_name);
  assign_variable(&var._link_bar, &func__30_1_link_bar);
  assign_variable(&var._to_paragraphs, &func__33_1_to_paragraphs);
  assign_variable(&var._resolve_reference, &func__34_1_resolve_reference);
  assign_variable(&var._add_links, &func__35_1_add_links);
  assign_variable(&var._create_info_page, &func__36_1_create_info_page);
  assign_variable(&var._get_short_description, &func__37_1_get_short_description);
  assign_variable(&var.sim2c__extract_documentation, &func__38_1_sim2c__extract_documentation);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
