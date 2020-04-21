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
static NODE_GETTER get__any_of;
static NODE_GETTER get_value_or_future__any_of;
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
  NODE *_topics_paragraphs;
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
  "topics_paragraphs",
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
static NODE *func__23_1_create_page;
static void entry__23_1_create_page(void);
static FRAME_INFO frame__23_1_create_page = {3, {"filename", "body", "page"}};
static NODE *func__23_2;
static void entry__23_2(void);
static FRAME_INFO frame__23_2 = {1, {"body"}};
static NODE *func__23_3;
static void entry__23_3(void);
static FRAME_INFO frame__23_3 = {1, {"body"}};
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {0, {}};
static NODE *string__23_5;
static void cont__23_6(void);
static void cont__23_7(void);
static NODE *func__25_1_extract_documentation_from_file;
static void entry__25_1_extract_documentation_from_file(void);
static FRAME_INFO frame__25_1_extract_documentation_from_file = {7, {"filename", "return__1", "buf", "fragments", "trees", "first_idx", "local_method_names"}};
static NODE *string__25_2;
static NODE *string__25_3;
static void cont__25_4(void);
static void cont__25_5(void);
static void cont__25_6(void);
static void cont__25_7(void);
static void cont__25_8(void);
static void cont__25_9(void);
static NODE *func__25_10;
static void entry__25_10(void);
static FRAME_INFO frame__25_10 = {0, {}};
static NODE *string__25_11;
static void cont__25_12(void);
static void cont__25_13(void);
static void cont__25_14(void);
static void cont__25_15(void);
static NODE *func__25_16;
static void entry__25_16(void);
static FRAME_INFO frame__25_16 = {0, {}};
static NODE *string__25_17;
static void cont__25_18(void);
static void cont__25_19(void);
static void cont__25_20(void);
static void cont__25_21(void);
static void cont__25_22(void);
static NODE *func__25_23;
static void entry__25_23(void);
static FRAME_INFO frame__25_23 = {0, {}};
static NODE *string__25_24;
static void cont__25_25(void);
static NODE *string__25_26;
static void cont__25_27(void);
static NODE *string__25_28;
static void cont__25_29(void);
static void cont__25_30(void);
static void cont__25_31(void);
static NODE *func__25_32;
static void entry__25_32(void);
static FRAME_INFO frame__25_32 = {1, {"fragment"}};
static void cont__25_33(void);
static void cont__25_34(void);
static NODE *func__25_35;
static void entry__25_35(void);
static FRAME_INFO frame__25_35 = {3, {"done", "fragments", "first_idx"}};
static NODE *func__25_36;
static void entry__25_36(void);
static FRAME_INFO frame__25_36 = {4, {"idx", "fragment", "first_idx", "done"}};
static void cont__25_37(void);
static void cont__25_38(void);
static NODE *func__25_39;
static void entry__25_39(void);
static FRAME_INFO frame__25_39 = {4, {"first_idx", "idx", "fragment", "tree"}};
static void cont__25_40(void);
static void cont__25_41(void);
static NODE *func__25_42;
static void entry__25_42(void);
static FRAME_INFO frame__25_42 = {1, {"done"}};
static NODE *func__25_43;
static void entry__25_43(void);
static FRAME_INFO frame__25_43 = {0, {}};
static void cont__25_44(void);
static void cont__25_45(void);
static void cont__25_46(void);
static void cont__25_47(void);
static NODE *func__25_48;
static void entry__25_48(void);
static FRAME_INFO frame__25_48 = {2, {"fragment", "trees"}};
static void cont__25_49(void);
static void cont__25_50(void);
static void cont__25_51(void);
static void cont__25_52(void);
static NODE *func__25_53;
static void entry__25_53(void);
static FRAME_INFO frame__25_53 = {0, {}};
static NODE *string__25_54;
static void cont__25_55(void);
static void cont__25_56(void);
static NODE *func__25_57;
static void entry__25_57(void);
static FRAME_INFO frame__25_57 = {2, {"statement", "local_method_names"}};
static NODE *func__25_58;
static void entry__25_58(void);
static FRAME_INFO frame__25_58 = {1, {"statement"}};
static void cont__25_59(void);
static NODE *func__25_60;
static void entry__25_60(void);
static FRAME_INFO frame__25_60 = {0, {}};
static NODE *func__25_61;
static void entry__25_61(void);
static FRAME_INFO frame__25_61 = {1, {"statement"}};
static void cont__25_62(void);
static NODE *func__25_63;
static void entry__25_63(void);
static FRAME_INFO frame__25_63 = {0, {}};
static NODE *func__25_64;
static void entry__25_64(void);
static FRAME_INFO frame__25_64 = {2, {"statement", "local_method_names"}};
static void cont__25_65(void);
static NODE *func__25_66;
static void entry__25_66(void);
static FRAME_INFO frame__25_66 = {3, {"statement", "local_method_names", "destination"}};
static void cont__25_67(void);
static void cont__25_68(void);
static void cont__25_69(void);
static NODE *func__25_70;
static void entry__25_70(void);
static FRAME_INFO frame__25_70 = {4, {"destination", "statement", "local_method_names", "identifier"}};
static void cont__25_71(void);
static void cont__25_72(void);
static void cont__25_73(void);
static NODE *func__25_74;
static void entry__25_74(void);
static FRAME_INFO frame__25_74 = {4, {"statement", "local_method_names", "destination", "source"}};
static void cont__25_75(void);
static void cont__25_76(void);
static void cont__25_77(void);
static NODE *func__25_78;
static void entry__25_78(void);
static FRAME_INFO frame__25_78 = {2, {"local_method_names", "destination"}};
static void cont__25_79(void);
static void cont__25_80(void);
static void cont__25_81(void);
static void cont__25_82(void);
static NODE *func__25_83;
static void entry__25_83(void);
static FRAME_INFO frame__25_83 = {4, {"statement", "break", "filename", "local_method_names"}};
static NODE *func__25_84;
static void entry__25_84(void);
static FRAME_INFO frame__25_84 = {1, {"statement"}};
static void cont__25_85(void);
static NODE *func__25_86;
static void entry__25_86(void);
static FRAME_INFO frame__25_86 = {2, {"statement", "remark_lines"}};
static void cont__25_87(void);
static NODE *string__25_88;
static void cont__25_89(void);
static NODE *func__25_90;
static void entry__25_90(void);
static FRAME_INFO frame__25_90 = {2, {"remark_lines", "paragraphs"}};
static void cont__25_91(void);
static NODE *func__25_92;
static void entry__25_92(void);
static FRAME_INFO frame__25_92 = {2, {"done", "paragraphs"}};
static NODE *func__25_93;
static void entry__25_93(void);
static FRAME_INFO frame__25_93 = {4, {"idx", "paragraph", "paragraphs", "done"}};
static void cont__25_94(void);
static NODE *func__25_95;
static void entry__25_95(void);
static FRAME_INFO frame__25_95 = {5, {"paragraph", "paragraphs", "idx", "done", "topic"}};
static void cont__25_96(void);
static void cont__25_97(void);
static void cont__25_98(void);
static void cont__25_99(void);
static void cont__25_100(void);
static void cont__25_101(void);
static void cont__25_102(void);
static NODE *func__25_103;
static void entry__25_103(void);
static FRAME_INFO frame__25_103 = {2, {"statement", "filename"}};
static void cont__25_104(void);
static NODE *func__25_105;
static void entry__25_105(void);
static FRAME_INFO frame__25_105 = {3, {"statement", "filename", "identifier"}};
static void cont__25_106(void);
static void cont__25_107(void);
static NODE *func__25_108;
static void entry__25_108(void);
static FRAME_INFO frame__25_108 = {4, {"identifier", "statement", "filename", "namespace"}};
static void cont__25_109(void);
static void cont__25_110(void);
static NODE *func__25_111;
static void entry__25_111(void);
static FRAME_INFO frame__25_111 = {5, {"identifier", "statement", "namespace", "filename", "name"}};
static void cont__25_112(void);
static void cont__25_113(void);
static NODE *func__25_114;
static void entry__25_114(void);
static FRAME_INFO frame__25_114 = {5, {"namespace", "statement", "name", "identifier", "filename"}};
static void cont__25_115(void);
static NODE *func__25_116;
static void entry__25_116(void);
static FRAME_INFO frame__25_116 = {6, {"statement", "namespace", "name", "identifier", "filename", "base"}};
static void cont__25_117(void);
static void cont__25_118(void);
static void cont__25_119(void);
static NODE *func__25_120;
static void entry__25_120(void);
static FRAME_INFO frame__25_120 = {1, {"base"}};
static void cont__25_121(void);
static NODE *func__25_122;
static void entry__25_122(void);
static FRAME_INFO frame__25_122 = {0, {}};
static void cont__25_123(void);
static void cont__25_124(void);
static void cont__25_125(void);
static void cont__25_126(void);
static NODE *func__25_127;
static void entry__25_127(void);
static FRAME_INFO frame__25_127 = {5, {"namespace", "name", "identifier", "statement", "filename"}};
static void cont__25_128(void);
static void cont__25_129(void);
static void cont__25_130(void);
static void cont__25_131(void);
static NODE *string__25_132;
static NODE *string__25_133;
static NODE *func__25_134;
static void entry__25_134(void);
static FRAME_INFO frame__25_134 = {4, {"statement", "filename", "break", "local_method_names"}};
static void cont__25_135(void);
static NODE *func__25_136;
static void entry__25_136(void);
static FRAME_INFO frame__25_136 = {6, {"statement", "filename", "break", "local_method_names", "destination", "info"}};
static void cont__25_137(void);
static void cont__25_138(void);
static void cont__25_139(void);
static NODE *func__25_140;
static void entry__25_140(void);
static FRAME_INFO frame__25_140 = {7, {"destination", "info", "statement", "break", "local_method_names", "identifier", "namespace"}};
static void cont__25_141(void);
static void cont__25_142(void);
static void cont__25_143(void);
static NODE *func__25_144;
static void entry__25_144(void);
static FRAME_INFO frame__25_144 = {10, {"identifier", "namespace", "info", "destination", "statement", "break", "local_method_names", "name", "iname", "source"}};
static void cont__25_145(void);
static void cont__25_146(void);
static void cont__25_147(void);
static void cont__25_148(void);
static void cont__25_149(void);
static void cont__25_150(void);
static void cont__25_151(void);
static NODE *func__25_152;
static void entry__25_152(void);
static FRAME_INFO frame__25_152 = {6, {"source", "name", "namespace", "iname", "info", "break"}};
static void cont__25_153(void);
static NODE *func__25_154;
static void entry__25_154(void);
static FRAME_INFO frame__25_154 = {6, {"name", "namespace", "iname", "info", "source", "break"}};
static void cont__25_155(void);
static void cont__25_156(void);
static NODE *func__25_157;
static void entry__25_157(void);
static FRAME_INFO frame__25_157 = {0, {}};
static NODE *func__25_158;
static void entry__25_158(void);
static FRAME_INFO frame__25_158 = {0, {}};
static void cont__25_159(void);
static void cont__25_160(void);
static NODE *func__25_161;
static void entry__25_161(void);
static FRAME_INFO frame__25_161 = {3, {"source", "info", "statement"}};
static void cont__25_162(void);
static NODE *func__25_163;
static void entry__25_163(void);
static FRAME_INFO frame__25_163 = {3, {"info", "source", "statement"}};
static void cont__25_164(void);
static void cont__25_165(void);
static void cont__25_166(void);
static NODE *func__25_167;
static void entry__25_167(void);
static FRAME_INFO frame__25_167 = {1, {"source"}};
static void cont__25_168(void);
static NODE *func__25_169;
static void entry__25_169(void);
static FRAME_INFO frame__25_169 = {1, {"statement"}};
static void cont__25_170(void);
static void cont__25_171(void);
static NODE *string__25_172;
static NODE *func__25_173;
static void entry__25_173(void);
static FRAME_INFO frame__25_173 = {2, {"source", "info"}};
static void cont__25_174(void);
static NODE *func__25_175;
static void entry__25_175(void);
static FRAME_INFO frame__25_175 = {1, {"info"}};
static NODE *func__25_176;
static void entry__25_176(void);
static FRAME_INFO frame__25_176 = {2, {"source", "info"}};
static void cont__25_177(void);
static NODE *func__25_178;
static void entry__25_178(void);
static FRAME_INFO frame__25_178 = {2, {"source", "info"}};
static void cont__25_179(void);
static void cont__25_180(void);
static NODE *func__25_181;
static void entry__25_181(void);
static FRAME_INFO frame__25_181 = {2, {"info", "source"}};
static void cont__25_182(void);
static NODE *func__25_183;
static void entry__25_183(void);
static FRAME_INFO frame__25_183 = {4, {"source", "iname", "info", "break"}};
static void cont__25_184(void);
static NODE *func__25_185;
static void entry__25_185(void);
static FRAME_INFO frame__25_185 = {3, {"iname", "info", "break"}};
static void cont__25_186(void);
static NODE *func__25_187;
static void entry__25_187(void);
static FRAME_INFO frame__25_187 = {2, {"source", "info"}};
static void cont__25_188(void);
static NODE *func__25_189;
static void entry__25_189(void);
static FRAME_INFO frame__25_189 = {1, {"info"}};
static void cont__25_190(void);
static void cont__25_191(void);
static NODE *func__25_192;
static void entry__25_192(void);
static FRAME_INFO frame__25_192 = {3, {"iname", "info", "previous_definition"}};
static void cont__25_193(void);
static void cont__25_194(void);
static NODE *func__25_195;
static void entry__25_195(void);
static FRAME_INFO frame__25_195 = {2, {"previous_definition", "info"}};
static void cont__25_196(void);
static void cont__25_197(void);
static NODE *func__25_198;
static void entry__25_198(void);
static FRAME_INFO frame__25_198 = {2, {"info", "previous_definition"}};
static void cont__25_199(void);
static void cont__25_200(void);
static void cont__25_201(void);
static void cont__25_202(void);
static void cont__25_203(void);
static void cont__25_204(void);
static NODE *func__25_205;
static void entry__25_205(void);
static FRAME_INFO frame__25_205 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__25_206(void);
static void cont__25_207(void);
static void cont__25_208(void);
static void cont__25_209(void);
static void cont__25_210(void);
static NODE *func__25_211;
static void entry__25_211(void);
static FRAME_INFO frame__25_211 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__25_212(void);
static void cont__25_213(void);
static NODE *func__25_214;
static void entry__25_214(void);
static FRAME_INFO frame__25_214 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__25_215(void);
static void cont__25_216(void);
static NODE *func__25_217;
static void entry__25_217(void);
static FRAME_INFO frame__25_217 = {1, {"attr"}};
static void cont__25_218(void);
static void cont__25_219(void);
static void cont__25_220(void);
static void cont__25_221(void);
static void cont__25_222(void);
static void cont__25_223(void);
static void cont__25_224(void);
static void cont__25_225(void);
static NODE *func__26_1_extract_documentation_from_directory;
static void entry__26_1_extract_documentation_from_directory(void);
static FRAME_INFO frame__26_1_extract_documentation_from_directory = {1, {"path"}};
static void cont__26_2(void);
static void cont__26_3(void);
static NODE *func__26_4;
static void entry__26_4(void);
static FRAME_INFO frame__26_4 = {2, {"entry", "name"}};
static void cont__26_5(void);
static NODE *func__26_6;
static void entry__26_6(void);
static FRAME_INFO frame__26_6 = {2, {"entry", "name"}};
static void cont__26_7(void);
static NODE *func__26_8;
static void entry__26_8(void);
static FRAME_INFO frame__26_8 = {1, {"name"}};
static NODE *func__26_9;
static void entry__26_9(void);
static FRAME_INFO frame__26_9 = {1, {"name"}};
static void cont__26_10(void);
static NODE *func__26_11;
static void entry__26_11(void);
static FRAME_INFO frame__26_11 = {1, {"name"}};
static NODE *func__27_1_resolved_name;
static void entry__27_1_resolved_name(void);
static FRAME_INFO frame__27_1_resolved_name = {2, {"attr", "name"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static NODE *func__27_5;
static void entry__27_5(void);
static FRAME_INFO frame__27_5 = {1, {"attr"}};
static void cont__27_6(void);
static NODE *func__27_7;
static void entry__27_7(void);
static FRAME_INFO frame__27_7 = {3, {"attr", "name", "resolved_namespace"}};
static void cont__27_8(void);
static NODE *func__27_9;
static void entry__27_9(void);
static FRAME_INFO frame__27_9 = {3, {"namespace", "name", "resolved_namespace"}};
static void cont__27_10(void);
static NODE *func__27_11;
static void entry__27_11(void);
static FRAME_INFO frame__27_11 = {3, {"resolved_namespace", "name", "namespace"}};
static void cont__27_12(void);
static NODE *func__27_13;
static void entry__27_13(void);
static FRAME_INFO frame__27_13 = {1, {"name"}};
static NODE *string__27_14;
static NODE *string__27_15;
static void cont__27_16(void);
static void cont__27_17(void);
static void cont__27_18(void);
static void cont__27_19(void);
static NODE *func__27_20;
static void entry__27_20(void);
static FRAME_INFO frame__27_20 = {1, {"name"}};
static NODE *string__27_21;
static void cont__27_22(void);
static void cont__27_23(void);
static NODE *string__27_24;
static void cont__27_25(void);
static NODE *func__28_1_add_derived_type;
static void entry__28_1_add_derived_type(void);
static FRAME_INFO frame__28_1_add_derived_type = {4, {"base", "name", "ibase", "definition"}};
static void cont__28_2(void);
static void cont__28_3(void);
static void cont__28_4(void);
static void cont__28_5(void);
static void cont__28_6(void);
static NODE *func__28_7;
static void entry__28_7(void);
static FRAME_INFO frame__28_7 = {3, {"definition", "name", "ibase"}};
static void cont__28_8(void);
static void cont__28_9(void);
static void cont__28_10(void);
static void cont__28_11(void);
static NODE *func__28_12;
static void entry__28_12(void);
static FRAME_INFO frame__28_12 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__28_13(void);
static void cont__28_14(void);
static NODE *func__28_15;
static void entry__28_15(void);
static FRAME_INFO frame__28_15 = {2, {"base_of_base", "ibase"}};
static void cont__28_16(void);
static void cont__28_17(void);
static NODE *func__29_1_mangled;
static void entry__29_1_mangled(void);
static FRAME_INFO frame__29_1_mangled = {1, {"name"}};
static void cont__29_2(void);
static NODE *string__29_3;
static void cont__29_4(void);
static void cont__29_5(void);
static NODE *func__30_1_ordered_name;
static void entry__30_1_ordered_name(void);
static FRAME_INFO frame__30_1_ordered_name = {2, {"namespace", "name"}};
static void cont__30_2(void);
static void cont__30_3(void);
static void cont__30_4(void);
static NODE *func__31_1_link_bar;
static void entry__31_1_link_bar(void);
static FRAME_INFO frame__31_1_link_bar = {0, {}};
static NODE *func__31_2;
static void entry__31_2(void);
static FRAME_INFO frame__31_2 = {0, {}};
static NODE *string__31_3;
static NODE *string__31_4;
static void cont__31_5(void);
static NODE *string__31_6;
static void cont__31_7(void);
static NODE *string__31_8;
static void cont__31_9(void);
static NODE *string__31_10;
static void cont__31_11(void);
static NODE *string__31_12;
static void cont__31_13(void);
static void cont__31_14(void);
static NODE *string__31_15;
static void cont__31_16(void);
static NODE *string__31_17;
static void cont__31_18(void);
static void cont__31_19(void);
static NODE *string__31_20;
static void cont__31_21(void);
static NODE *string__31_22;
static void cont__31_23(void);
static void cont__31_24(void);
static NODE *string__31_25;
static void cont__31_26(void);
static NODE *string__31_27;
static NODE *func__34_1_to_paragraphs;
static void entry__34_1_to_paragraphs(void);
static FRAME_INFO frame__34_1_to_paragraphs = {4, {"lines", "paragraphs", "text", "pre_mode"}};
static NODE *func__34_2;
static void entry__34_2(void);
static FRAME_INFO frame__34_2 = {4, {"line", "pre_mode", "text", "paragraphs"}};
static NODE *func__34_3;
static void entry__34_3(void);
static FRAME_INFO frame__34_3 = {3, {"line", "text", "paragraphs"}};
static void cont__34_4(void);
static NODE *func__34_5;
static void entry__34_5(void);
static FRAME_INFO frame__34_5 = {3, {"text", "paragraphs", "line"}};
static void cont__34_6(void);
static void cont__34_7(void);
static NODE *func__34_8;
static void entry__34_8(void);
static FRAME_INFO frame__34_8 = {2, {"text", "line"}};
static void cont__34_9(void);
static NODE *func__34_10;
static void entry__34_10(void);
static FRAME_INFO frame__34_10 = {4, {"line", "text", "paragraphs", "pre_mode"}};
static void cont__34_11(void);
static NODE *func__34_12;
static void entry__34_12(void);
static FRAME_INFO frame__34_12 = {2, {"text", "paragraphs"}};
static void cont__34_13(void);
static void cont__34_14(void);
static NODE *func__34_15;
static void entry__34_15(void);
static FRAME_INFO frame__34_15 = {2, {"paragraphs", "text"}};
static void cont__34_16(void);
static NODE *func__34_17;
static void entry__34_17(void);
static FRAME_INFO frame__34_17 = {3, {"text", "line", "pre_mode"}};
static void cont__34_18(void);
static NODE *func__34_19;
static void entry__34_19(void);
static FRAME_INFO frame__34_19 = {2, {"line", "pre_mode"}};
static void cont__34_20(void);
static NODE *func__34_21;
static void entry__34_21(void);
static FRAME_INFO frame__34_21 = {1, {"pre_mode"}};
static NODE *func__34_22;
static void entry__34_22(void);
static FRAME_INFO frame__34_22 = {1, {"text"}};
static void cont__34_23(void);
static void cont__34_24(void);
static void cont__34_25(void);
static void cont__34_26(void);
static void cont__34_27(void);
static void cont__34_28(void);
static void cont__34_29(void);
static NODE *func__34_30;
static void entry__34_30(void);
static FRAME_INFO frame__34_30 = {2, {"paragraphs", "text"}};
static void cont__34_31(void);
static void cont__34_32(void);
static NODE *func__35_1_resolve_reference;
static void entry__35_1_resolve_reference(void);
static FRAME_INFO frame__35_1_resolve_reference = {1, {"reference"}};
static void cont__35_2(void);
static NODE *func__35_3;
static void entry__35_3(void);
static FRAME_INFO frame__35_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__35_4(void);
static void cont__35_5(void);
static void cont__35_6(void);
static NODE *func__35_7;
static void entry__35_7(void);
static FRAME_INFO frame__35_7 = {1, {"type_name"}};
static NODE *string__35_8;
static void cont__35_9(void);
static void cont__35_10(void);
static void cont__35_11(void);
static NODE *func__35_12;
static void entry__35_12(void);
static FRAME_INFO frame__35_12 = {1, {"method_name"}};
static NODE *string__35_13;
static void cont__35_14(void);
static void cont__35_15(void);
static void cont__35_16(void);
static NODE *func__35_17;
static void entry__35_17(void);
static FRAME_INFO frame__35_17 = {1, {"reference"}};
static void cont__35_18(void);
static NODE *func__35_19;
static void entry__35_19(void);
static FRAME_INFO frame__35_19 = {1, {"reference"}};
static void cont__35_20(void);
static void cont__35_21(void);
static NODE *func__36_1_add_links;
static void entry__36_1_add_links(void);
static FRAME_INFO frame__36_1_add_links = {1, {"paragraph"}};
static void cont__36_2(void);
static void cont__36_3(void);
static void cont__36_4(void);
static NODE *func__36_5;
static void entry__36_5(void);
static FRAME_INFO frame__36_5 = {1, {"reference"}};
static void cont__36_6(void);
static void cont__36_7(void);
static void cont__36_8(void);
static void cont__36_9(void);
static NODE *string__36_10;
static NODE *string__36_11;
static NODE *string__36_12;
static void cont__36_13(void);
static void cont__36_14(void);
static void cont__36_15(void);
static NODE *func__37_1_create_info_page;
static void entry__37_1_create_info_page(void);
static FRAME_INFO frame__37_1_create_info_page = {3, {"function_name", "info", "resolve_and_check_reference"}};
static NODE *func__37_2_resolve_and_check_reference;
static void entry__37_2_resolve_and_check_reference(void);
static FRAME_INFO frame__37_2_resolve_and_check_reference = {3, {"reference", "function_name", "info"}};
static void cont__37_3(void);
static void cont__37_4(void);
static void cont__37_5(void);
static NODE *func__37_6;
static void entry__37_6(void);
static FRAME_INFO frame__37_6 = {3, {"function_name", "info", "reference"}};
static void cont__37_7(void);
static NODE *string__37_8;
static NODE *string__37_9;
static NODE *string__37_10;
static NODE *string__37_11;
static void cont__37_12(void);
static void cont__37_13(void);
static void cont__37_14(void);
static NODE *func__37_15;
static void entry__37_15(void);
static FRAME_INFO frame__37_15 = {3, {"function_name", "info", "resolve_and_check_reference"}};
static void cont__37_16(void);
static NODE *string__37_17;
static NODE *string__37_18;
static void cont__37_19(void);
static NODE *func__37_20;
static void entry__37_20(void);
static FRAME_INFO frame__37_20 = {13, {"function_name", "info", "resolve_and_check_reference", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "topic_list", "examples", "remark_lines", "function_basename"}};
static void cont__37_21(void);
static void cont__37_22(void);
static NODE *func__37_23;
static void entry__37_23(void);
static FRAME_INFO frame__37_23 = {3, {"function_name", "type", "method"}};
static void cont__37_24(void);
static void cont__37_25(void);
static void cont__37_26(void);
static void cont__37_27(void);
static NODE *string__37_28;
static void cont__37_29(void);
static NODE *func__37_30;
static void entry__37_30(void);
static FRAME_INFO frame__37_30 = {2, {"function_name", "info"}};
static void cont__37_31(void);
static void cont__37_32(void);
static NODE *func__37_33;
static void entry__37_33(void);
static FRAME_INFO frame__37_33 = {0, {}};
static NODE *string__37_34;
static NODE *func__37_35;
static void entry__37_35(void);
static FRAME_INFO frame__37_35 = {0, {}};
static NODE *string__37_36;
static NODE *func__37_37;
static void entry__37_37(void);
static FRAME_INFO frame__37_37 = {0, {}};
static NODE *string__37_38;
static void cont__37_39(void);
static void cont__37_40(void);
static void cont__37_41(void);
static NODE *func__37_42;
static void entry__37_42(void);
static FRAME_INFO frame__37_42 = {1, {"remark_lines"}};
static void cont__37_43(void);
static void cont__37_44(void);
static NODE *func__37_45;
static void entry__37_45(void);
static FRAME_INFO frame__37_45 = {2, {"function_name", "info"}};
static void cont__37_46(void);
static NODE *func__37_47;
static void entry__37_47(void);
static FRAME_INFO frame__37_47 = {2, {"function_name", "info"}};
static void cont__37_48(void);
static NODE *string__37_49;
static NODE *string__37_50;
static NODE *string__37_51;
static void cont__37_52(void);
static void cont__37_53(void);
static void cont__37_54(void);
static NODE *func__37_55;
static void entry__37_55(void);
static FRAME_INFO frame__37_55 = {12, {"remark_lines", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions", "paragraphs"}};
static void cont__37_56(void);
static NODE *func__37_57;
static void entry__37_57(void);
static FRAME_INFO frame__37_57 = {11, {"paragraph", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions"}};
static NODE *func__37_58;
static void entry__37_58(void);
static FRAME_INFO frame__37_58 = {2, {"paragraph", "parameters"}};
static void cont__37_59(void);
static NODE *string__37_60;
static void cont__37_61(void);
static void cont__37_62(void);
static NODE *func__37_63;
static void entry__37_63(void);
static FRAME_INFO frame__37_63 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__37_64(void);
static NODE *func__37_65;
static void entry__37_65(void);
static FRAME_INFO frame__37_65 = {1, {"parameter"}};
static void cont__37_66(void);
static NODE *func__37_67;
static void entry__37_67(void);
static FRAME_INFO frame__37_67 = {1, {"parameter"}};
static void cont__37_68(void);
static void cont__37_69(void);
static NODE *string__37_70;
static void cont__37_71(void);
static NODE *func__37_72;
static void entry__37_72(void);
static FRAME_INFO frame__37_72 = {1, {"parameter"}};
static void cont__37_73(void);
static NODE *func__37_74;
static void entry__37_74(void);
static FRAME_INFO frame__37_74 = {1, {"parameter"}};
static void cont__37_75(void);
static void cont__37_76(void);
static NODE *string__37_77;
static void cont__37_78(void);
static NODE *func__37_79;
static void entry__37_79(void);
static FRAME_INFO frame__37_79 = {1, {"parameter"}};
static void cont__37_80(void);
static NODE *func__37_81;
static void entry__37_81(void);
static FRAME_INFO frame__37_81 = {1, {"parameter"}};
static void cont__37_82(void);
static void cont__37_83(void);
static void cont__37_84(void);
static void cont__37_85(void);
static NODE *string__37_86;
static NODE *string__37_87;
static void cont__37_88(void);
static void cont__37_89(void);
static void cont__37_90(void);
static void cont__37_91(void);
static void cont__37_92(void);
static void cont__37_93(void);
static NODE *func__37_94;
static void entry__37_94(void);
static FRAME_INFO frame__37_94 = {2, {"paragraph", "return_values"}};
static void cont__37_95(void);
static NODE *string__37_96;
static void cont__37_97(void);
static void cont__37_98(void);
static NODE *func__37_99;
static void entry__37_99(void);
static FRAME_INFO frame__37_99 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__37_100(void);
static NODE *func__37_101;
static void entry__37_101(void);
static FRAME_INFO frame__37_101 = {1, {"return_value"}};
static void cont__37_102(void);
static NODE *func__37_103;
static void entry__37_103(void);
static FRAME_INFO frame__37_103 = {1, {"return_value"}};
static void cont__37_104(void);
static void cont__37_105(void);
static void cont__37_106(void);
static NODE *func__37_107;
static void entry__37_107(void);
static FRAME_INFO frame__37_107 = {1, {"return_value"}};
static void cont__37_108(void);
static NODE *func__37_109;
static void entry__37_109(void);
static FRAME_INFO frame__37_109 = {1, {"return_value"}};
static void cont__37_110(void);
static void cont__37_111(void);
static void cont__37_112(void);
static void cont__37_113(void);
static void cont__37_114(void);
static void cont__37_115(void);
static void cont__37_116(void);
static void cont__37_117(void);
static NODE *func__37_118;
static void entry__37_118(void);
static FRAME_INFO frame__37_118 = {2, {"paragraph", "references"}};
static NODE *string__37_119;
static void cont__37_120(void);
static NODE *func__37_121;
static void entry__37_121(void);
static FRAME_INFO frame__37_121 = {2, {"paragraph", "references"}};
static void cont__37_122(void);
static void cont__37_123(void);
static NODE *func__37_124;
static void entry__37_124(void);
static FRAME_INFO frame__37_124 = {2, {"reference", "references"}};
static void cont__37_125(void);
static void cont__37_126(void);
static NODE *func__37_127;
static void entry__37_127(void);
static FRAME_INFO frame__37_127 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__37_128(void);
static NODE *func__37_129;
static void entry__37_129(void);
static FRAME_INFO frame__37_129 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__37_130(void);
static void cont__37_131(void);
static NODE *func__37_132;
static void entry__37_132(void);
static FRAME_INFO frame__37_132 = {4, {"topic", "topic_list", "function_name", "topic_contents"}};
static void cont__37_133(void);
static void cont__37_134(void);
static void cont__37_135(void);
static void cont__37_136(void);
static void cont__37_137(void);
static void cont__37_138(void);
static NODE *func__37_139;
static void entry__37_139(void);
static FRAME_INFO frame__37_139 = {2, {"paragraph", "examples"}};
static void cont__37_140(void);
static NODE *func__37_141;
static void entry__37_141(void);
static FRAME_INFO frame__37_141 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__37_142(void);
static void cont__37_143(void);
static void cont__37_144(void);
static void cont__37_145(void);
static void cont__37_146(void);
static void cont__37_147(void);
static NODE *func__37_148;
static void entry__37_148(void);
static FRAME_INFO frame__37_148 = {2, {"paragraph", "technical_details"}};
static NODE *string__37_149;
static void cont__37_150(void);
static NODE *func__37_151;
static void entry__37_151(void);
static FRAME_INFO frame__37_151 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__37_152(void);
static void cont__37_153(void);
static void cont__37_154(void);
static NODE *func__37_155;
static void entry__37_155(void);
static FRAME_INFO frame__37_155 = {1, {"technical_details"}};
static NODE *func__37_156;
static void entry__37_156(void);
static FRAME_INFO frame__37_156 = {2, {"technical_details", "detail"}};
static void cont__37_157(void);
static NODE *func__37_158;
static void entry__37_158(void);
static FRAME_INFO frame__37_158 = {5, {"paragraph", "resolve_and_check_reference", "short_description", "technical_details", "descriptions"}};
static void cont__37_159(void);
static void cont__37_160(void);
static void cont__37_161(void);
static NODE *func__37_162;
static void entry__37_162(void);
static FRAME_INFO frame__37_162 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__37_163(void);
static void cont__37_164(void);
static void cont__37_165(void);
static void cont__37_166(void);
static void cont__37_167(void);
static void cont__37_168(void);
static void cont__37_169(void);
static void cont__37_170(void);
static NODE *func__37_171;
static void entry__37_171(void);
static FRAME_INFO frame__37_171 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__37_172(void);
static NODE *func__37_173;
static void entry__37_173(void);
static FRAME_INFO frame__37_173 = {2, {"technical_details", "paragraph"}};
static void cont__37_174(void);
static NODE *func__37_175;
static void entry__37_175(void);
static FRAME_INFO frame__37_175 = {2, {"descriptions", "paragraph"}};
static void cont__37_176(void);
static NODE *func__37_177;
static void entry__37_177(void);
static FRAME_INFO frame__37_177 = {2, {"short_description", "paragraph"}};
static void cont__37_178(void);
static void cont__37_179(void);
static void cont__37_180(void);
static NODE *func__37_181;
static void entry__37_181(void);
static FRAME_INFO frame__37_181 = {2, {"info", "parameters"}};
static void cont__37_182(void);
static NODE *func__37_183;
static void entry__37_183(void);
static FRAME_INFO frame__37_183 = {2, {"parameter", "parameters"}};
static void cont__37_184(void);
static void cont__37_185(void);
static NODE *func__37_186;
static void entry__37_186(void);
static FRAME_INFO frame__37_186 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__37_187(void);
static void cont__37_188(void);
static void cont__37_189(void);
static NODE *func__37_190;
static void entry__37_190(void);
static FRAME_INFO frame__37_190 = {2, {"parameter", "name"}};
static void cont__37_191(void);
static NODE *func__37_192;
static void entry__37_192(void);
static FRAME_INFO frame__37_192 = {2, {"parameter", "name"}};
static void cont__37_193(void);
static void cont__37_194(void);
static NODE *func__37_195;
static void entry__37_195(void);
static FRAME_INFO frame__37_195 = {2, {"name", "parameter"}};
static void cont__37_196(void);
static void cont__37_197(void);
static void cont__37_198(void);
static NODE *func__37_199;
static void entry__37_199(void);
static FRAME_INFO frame__37_199 = {1, {"name"}};
static void cont__37_200(void);
static NODE *func__37_201;
static void entry__37_201(void);
static FRAME_INFO frame__37_201 = {2, {"parameter", "name"}};
static void cont__37_202(void);
static NODE *func__37_203;
static void entry__37_203(void);
static FRAME_INFO frame__37_203 = {1, {"name"}};
static void cont__37_204(void);
static void cont__37_205(void);
static void cont__37_206(void);
static void cont__37_207(void);
static void cont__37_208(void);
static NODE *func__37_209;
static void entry__37_209(void);
static FRAME_INFO frame__37_209 = {1, {"parameter"}};
static void cont__37_210(void);
static void cont__37_211(void);
static void cont__37_212(void);
static NODE *func__37_213;
static void entry__37_213(void);
static FRAME_INFO frame__37_213 = {0, {}};
static void cont__37_214(void);
static void cont__37_215(void);
static void cont__37_216(void);
static NODE *func__37_217;
static void entry__37_217(void);
static FRAME_INFO frame__37_217 = {0, {}};
static void cont__37_218(void);
static void cont__37_219(void);
static NODE *func__37_220;
static void entry__37_220(void);
static FRAME_INFO frame__37_220 = {1, {"short_description"}};
static void cont__37_221(void);
static void cont__37_222(void);
static NODE *func__37_223;
static void entry__37_223(void);
static FRAME_INFO frame__37_223 = {1, {"parameters"}};
static NODE *string__37_224;
static void cont__37_225(void);
static NODE *func__37_226;
static void entry__37_226(void);
static FRAME_INFO frame__37_226 = {1, {"parameters"}};
static NODE *func__37_227;
static void entry__37_227(void);
static FRAME_INFO frame__37_227 = {1, {"parameter"}};
static void cont__37_228(void);
static void cont__37_229(void);
static NODE *func__37_230;
static void entry__37_230(void);
static FRAME_INFO frame__37_230 = {1, {"parameter"}};
static void cont__37_231(void);
static void cont__37_232(void);
static void cont__37_233(void);
static NODE *func__37_234;
static void entry__37_234(void);
static FRAME_INFO frame__37_234 = {1, {"return_values"}};
static void cont__37_235(void);
static NODE *func__37_236;
static void entry__37_236(void);
static FRAME_INFO frame__37_236 = {1, {"return_values"}};
static NODE *func__37_237;
static void entry__37_237(void);
static FRAME_INFO frame__37_237 = {1, {"return_value"}};
static void cont__37_238(void);
static void cont__37_239(void);
static NODE *func__37_240;
static void entry__37_240(void);
static FRAME_INFO frame__37_240 = {1, {"return_value"}};
static void cont__37_241(void);
static void cont__37_242(void);
static void cont__37_243(void);
static NODE *func__37_244;
static void entry__37_244(void);
static FRAME_INFO frame__37_244 = {1, {"descriptions"}};
static NODE *string__37_245;
static void cont__37_246(void);
static NODE *func__37_247;
static void entry__37_247(void);
static FRAME_INFO frame__37_247 = {1, {"description"}};
static void cont__37_248(void);
static void cont__37_249(void);
static NODE *func__37_250;
static void entry__37_250(void);
static FRAME_INFO frame__37_250 = {1, {"technical_details"}};
static NODE *string__37_251;
static void cont__37_252(void);
static NODE *func__37_253;
static void entry__37_253(void);
static FRAME_INFO frame__37_253 = {1, {"detail"}};
static void cont__37_254(void);
static void cont__37_255(void);
static NODE *func__37_256;
static void entry__37_256(void);
static FRAME_INFO frame__37_256 = {2, {"references", "resolve_and_check_reference"}};
static NODE *string__37_257;
static void cont__37_258(void);
static NODE *func__37_259;
static void entry__37_259(void);
static FRAME_INFO frame__37_259 = {2, {"references", "resolve_and_check_reference"}};
static NODE *func__37_260;
static void entry__37_260(void);
static FRAME_INFO frame__37_260 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__37_261(void);
static NODE *func__37_262;
static void entry__37_262(void);
static FRAME_INFO frame__37_262 = {1, {"reference"}};
static NODE *func__37_263;
static void entry__37_263(void);
static FRAME_INFO frame__37_263 = {1, {"reference"}};
static void cont__37_264(void);
static void cont__37_265(void);
static void cont__37_266(void);
static void cont__37_267(void);
static NODE *string__37_268;
static void cont__37_269(void);
static void cont__37_270(void);
static void cont__37_271(void);
static void cont__37_272(void);
static void cont__37_273(void);
static NODE *func__37_274;
static void entry__37_274(void);
static FRAME_INFO frame__37_274 = {2, {"info", "function_name"}};
static NODE *string__37_275;
static void cont__37_276(void);
static NODE *func__37_277;
static void entry__37_277(void);
static FRAME_INFO frame__37_277 = {2, {"info", "function_name"}};
static void cont__37_278(void);
static NODE *func__37_279;
static void entry__37_279(void);
static FRAME_INFO frame__37_279 = {3, {"name", "function_name", "method"}};
static void cont__37_280(void);
static NODE *func__37_281;
static void entry__37_281(void);
static FRAME_INFO frame__37_281 = {2, {"name", "method"}};
static NODE *func__37_282;
static void entry__37_282(void);
static FRAME_INFO frame__37_282 = {1, {"name"}};
static void cont__37_283(void);
static void cont__37_284(void);
static void cont__37_285(void);
static void cont__37_286(void);
static NODE *string__37_287;
static void cont__37_288(void);
static NODE *func__37_289;
static void entry__37_289(void);
static FRAME_INFO frame__37_289 = {1, {"method"}};
static void cont__37_290(void);
static void cont__37_291(void);
static void cont__37_292(void);
static void cont__37_293(void);
static void cont__37_294(void);
static NODE *func__37_295;
static void entry__37_295(void);
static FRAME_INFO frame__37_295 = {2, {"function_name", "polymorphic_function_name"}};
static void cont__37_296(void);
static NODE *string__37_297;
static void cont__37_298(void);
static void cont__37_299(void);
static void cont__37_300(void);
static void cont__37_301(void);
static void cont__37_302(void);
static void cont__37_303(void);
static void cont__37_304(void);
static NODE *func__37_305;
static void entry__37_305(void);
static FRAME_INFO frame__37_305 = {2, {"info", "function_name"}};
static NODE *string__37_306;
static void cont__37_307(void);
static NODE *func__37_308;
static void entry__37_308(void);
static FRAME_INFO frame__37_308 = {2, {"info", "function_name"}};
static void cont__37_309(void);
static NODE *func__37_310;
static void entry__37_310(void);
static FRAME_INFO frame__37_310 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__37_311;
static void entry__37_311(void);
static FRAME_INFO frame__37_311 = {2, {"method_name", "function_name"}};
static NODE *func__37_312;
static void entry__37_312(void);
static FRAME_INFO frame__37_312 = {1, {"method_name"}};
static void cont__37_313(void);
static void cont__37_314(void);
static void cont__37_315(void);
static void cont__37_316(void);
static void cont__37_317(void);
static NODE *func__37_318;
static void entry__37_318(void);
static FRAME_INFO frame__37_318 = {2, {"function_name", "method_name"}};
static void cont__37_319(void);
static void cont__37_320(void);
static void cont__37_321(void);
static void cont__37_322(void);
static void cont__37_323(void);
static void cont__37_324(void);
static void cont__37_325(void);
static void cont__37_326(void);
static NODE *func__37_327;
static void entry__37_327(void);
static FRAME_INFO frame__37_327 = {1, {"topic_list"}};
static NODE *string__37_328;
static void cont__37_329(void);
static NODE *func__37_330;
static void entry__37_330(void);
static FRAME_INFO frame__37_330 = {1, {"topic_list"}};
static NODE *func__37_331;
static void entry__37_331(void);
static FRAME_INFO frame__37_331 = {2, {"topic", "filename"}};
static void cont__37_332(void);
static NODE *string__37_333;
static void cont__37_334(void);
static void cont__37_335(void);
static void cont__37_336(void);
static NODE *func__37_337;
static void entry__37_337(void);
static FRAME_INFO frame__37_337 = {2, {"filename", "topic"}};
static NODE *func__37_338;
static void entry__37_338(void);
static FRAME_INFO frame__37_338 = {2, {"filename", "topic"}};
static void cont__37_339(void);
static void cont__37_340(void);
static NODE *func__37_341;
static void entry__37_341(void);
static FRAME_INFO frame__37_341 = {4, {"example", "function_basename", "title", "text"}};
static void cont__37_342(void);
static void cont__37_343(void);
static void cont__37_344(void);
static void cont__37_345(void);
static void cont__37_346(void);
static NODE *string__37_347;
static void cont__37_348(void);
static NODE *func__37_349;
static void entry__37_349(void);
static FRAME_INFO frame__37_349 = {2, {"text", "function_basename"}};
static void cont__37_350(void);
static void cont__37_351(void);
static void cont__37_352(void);
static void cont__37_353(void);
static NODE *func__37_354;
static void entry__37_354(void);
static FRAME_INFO frame__37_354 = {1, {"string_literal"}};
static void cont__37_355(void);
static NODE *string__37_356;
static void cont__37_357(void);
static void cont__37_358(void);
static void cont__37_359(void);
static void cont__37_360(void);
static NODE *string__37_361;
static void cont__37_362(void);
static void cont__37_363(void);
static void cont__37_364(void);
static NODE *string__37_365;
static NODE *string__37_366;
static void cont__37_367(void);
static NODE *func__38_1_get_short_description;
static void entry__38_1_get_short_description(void);
static FRAME_INFO frame__38_1_get_short_description = {4, {"name", "info", "remark_lines", "short_description"}};
static void cont__38_2(void);
static void cont__38_3(void);
static NODE *func__38_4;
static void entry__38_4(void);
static FRAME_INFO frame__38_4 = {1, {"remark_lines"}};
static void cont__38_5(void);
static void cont__38_6(void);
static void cont__38_7(void);
static NODE *func__38_8;
static void entry__38_8(void);
static FRAME_INFO frame__38_8 = {4, {"remark_lines", "short_description", "name", "info"}};
static NODE *func__38_9;
static void entry__38_9(void);
static FRAME_INFO frame__38_9 = {3, {"break", "remark_lines", "short_description"}};
static NODE *func__38_10;
static void entry__38_10(void);
static FRAME_INFO frame__38_10 = {3, {"line", "short_description", "break"}};
static void cont__38_11(void);
static NODE *func__38_12;
static void entry__38_12(void);
static FRAME_INFO frame__38_12 = {1, {"short_description"}};
static void cont__38_13(void);
static void cont__38_14(void);
static void cont__38_15(void);
static void cont__38_16(void);
static void cont__38_17(void);
static void cont__38_18(void);
static void cont__38_19(void);
static void cont__38_20(void);
static NODE *func__38_21;
static void entry__38_21(void);
static FRAME_INFO frame__38_21 = {1, {"short_description"}};
static void cont__38_22(void);
static void cont__38_23(void);
static void cont__38_24(void);
static NODE *func__38_25;
static void entry__38_25(void);
static FRAME_INFO frame__38_25 = {3, {"name", "info", "short_description"}};
static void cont__38_26(void);
static NODE *string__38_27;
static NODE *string__38_28;
static void cont__38_29(void);
static void cont__38_30(void);
static void cont__38_31(void);
static NODE *func__39_1_sim2c__extract_documentation;
static void entry__39_1_sim2c__extract_documentation(void);
static FRAME_INFO frame__39_1_sim2c__extract_documentation = {1, {"path"}};
static void cont__39_2(void);
static void cont__39_3(void);
static void cont__39_4(void);
static NODE *func__39_5;
static void entry__39_5(void);
static FRAME_INFO frame__39_5 = {3, {"iname", "info", "name"}};
static void cont__39_6(void);
static void cont__39_7(void);
static void cont__39_8(void);
static void cont__39_9(void);
static void cont__39_10(void);
static NODE *func__39_11;
static void entry__39_11(void);
static FRAME_INFO frame__39_11 = {5, {"info", "iname", "name", "base", "methods"}};
static void cont__39_12(void);
static void cont__39_13(void);
static NODE *func__39_14;
static void entry__39_14(void);
static FRAME_INFO frame__39_14 = {2, {"base", "iname"}};
static void cont__39_15(void);
static void cont__39_16(void);
static NODE *func__39_17;
static void entry__39_17(void);
static FRAME_INFO frame__39_17 = {6, {"method_name", "method_info", "name", "methods", "sd_name", "oname"}};
static void cont__39_18(void);
static NODE *func__39_19;
static void entry__39_19(void);
static FRAME_INFO frame__39_19 = {2, {"method_name", "method_info"}};
static void cont__39_20(void);
static void cont__39_21(void);
static void cont__39_22(void);
static NODE *string__39_23;
static void cont__39_24(void);
static void cont__39_25(void);
static void cont__39_26(void);
static void cont__39_27(void);
static void cont__39_28(void);
static void cont__39_29(void);
static void cont__39_30(void);
static void cont__39_31(void);
static void cont__39_32(void);
static void cont__39_33(void);
static void cont__39_34(void);
static void cont__39_35(void);
static void cont__39_36(void);
static void cont__39_37(void);
static void cont__39_38(void);
static NODE *string__39_39;
static NODE *func__39_40;
static void entry__39_40(void);
static FRAME_INFO frame__39_40 = {1, {"print_type_info"}};
static NODE *func__39_41_print_type_info;
static void entry__39_41_print_type_info(void);
static FRAME_INFO frame__39_41_print_type_info = {3, {"info", "indent", "print_type_info"}};
static NODE *func__39_42;
static void entry__39_42(void);
static FRAME_INFO frame__39_42 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__39_43(void);
static void cont__39_44(void);
static void cont__39_45(void);
static NODE *func__39_46;
static void entry__39_46(void);
static FRAME_INFO frame__39_46 = {2, {"indent", "qname"}};
static NODE *func__39_47;
static void entry__39_47(void);
static FRAME_INFO frame__39_47 = {2, {"indent", "qname"}};
static void cont__39_48(void);
static void cont__39_49(void);
static void cont__39_50(void);
static void cont__39_51(void);
static void cont__39_52(void);
static void cont__39_53(void);
static void cont__39_54(void);
static NODE *func__39_55;
static void entry__39_55(void);
static FRAME_INFO frame__39_55 = {1, {"remark_lines"}};
static void cont__39_56(void);
static void cont__39_57(void);
static void cont__39_58(void);
static NODE *func__39_59;
static void entry__39_59(void);
static FRAME_INFO frame__39_59 = {1, {"remark_lines"}};
static void cont__39_60(void);
static void cont__39_61(void);
static void cont__39_62(void);
static void cont__39_63(void);
static NODE *func__39_64;
static void entry__39_64(void);
static FRAME_INFO frame__39_64 = {3, {"name", "print_type_info", "indent"}};
static void cont__39_65(void);
static void cont__39_66(void);
static void cont__39_67(void);
static void cont__39_68(void);
static NODE *func__39_69;
static void entry__39_69(void);
static FRAME_INFO frame__39_69 = {1, {"print_type_info"}};
static NODE *func__39_70;
static void entry__39_70(void);
static FRAME_INFO frame__39_70 = {3, {"base", "info", "print_type_info"}};
static void cont__39_71(void);
static void cont__39_72(void);
static NODE *func__39_73;
static void entry__39_73(void);
static FRAME_INFO frame__39_73 = {1, {"info"}};
static void cont__39_74(void);
static void cont__39_75(void);
static void cont__39_76(void);
static NODE *func__39_77;
static void entry__39_77(void);
static FRAME_INFO frame__39_77 = {2, {"print_type_info", "info"}};
static void cont__39_78(void);
static NODE *string__39_79;
static NODE *func__39_80;
static void entry__39_80(void);
static FRAME_INFO frame__39_80 = {0, {}};
static void cont__39_81(void);
static NODE *string__39_82;
static NODE *string__39_83;
static void cont__39_84(void);
static void cont__39_85(void);
static NODE *func__39_86;
static void entry__39_86(void);
static FRAME_INFO frame__39_86 = {1, {"letter"}};
static NODE *string__39_87;
static void cont__39_88(void);
static void cont__39_89(void);
static void cont__39_90(void);
static NODE *func__39_91;
static void entry__39_91(void);
static FRAME_INFO frame__39_91 = {0, {}};
static NODE *string__39_92;
static void cont__39_93(void);
static void cont__39_94(void);
static NODE *func__39_95;
static void entry__39_95(void);
static FRAME_INFO frame__39_95 = {1, {"letter"}};
static NODE *func__39_96;
static void entry__39_96(void);
static FRAME_INFO frame__39_96 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__39_97(void);
static void cont__39_98(void);
static void cont__39_99(void);
static NODE *func__39_100;
static void entry__39_100(void);
static FRAME_INFO frame__39_100 = {2, {"letter", "iname"}};
static void cont__39_101(void);
static NODE *func__39_102;
static void entry__39_102(void);
static FRAME_INFO frame__39_102 = {1, {"letter"}};
static NODE *string__39_103;
static void cont__39_104(void);
static NODE *func__39_105;
static void entry__39_105(void);
static FRAME_INFO frame__39_105 = {1, {"letter"}};
static void cont__39_106(void);
static NODE *func__39_107;
static void entry__39_107(void);
static FRAME_INFO frame__39_107 = {1, {"letter"}};
static void cont__39_108(void);
static void cont__39_109(void);
static NODE *string__39_110;
static void cont__39_111(void);
static NODE *string__39_112;
static void cont__39_113(void);
static void cont__39_114(void);
static void cont__39_115(void);
static void cont__39_116(void);
static NODE *func__39_117;
static void entry__39_117(void);
static FRAME_INFO frame__39_117 = {1, {"remark_lines"}};
static void cont__39_118(void);
static void cont__39_119(void);
static void cont__39_120(void);
static NODE *func__39_121;
static void entry__39_121(void);
static FRAME_INFO frame__39_121 = {2, {"remark", "remark_lines"}};
static void cont__39_122(void);
static void cont__39_123(void);
static void cont__39_124(void);
static void cont__39_125(void);
static NODE *func__39_126;
static void entry__39_126(void);
static FRAME_INFO frame__39_126 = {0, {}};
static NODE *string__39_127;
static NODE *func__39_128;
static void entry__39_128(void);
static FRAME_INFO frame__39_128 = {0, {}};
static NODE *string__39_129;
static NODE *func__39_130;
static void entry__39_130(void);
static FRAME_INFO frame__39_130 = {0, {}};
static NODE *string__39_131;
static NODE *func__39_132;
static void entry__39_132(void);
static FRAME_INFO frame__39_132 = {0, {}};
static NODE *string__39_133;
static NODE *func__39_134;
static void entry__39_134(void);
static FRAME_INFO frame__39_134 = {0, {}};
static NODE *string__39_135;
static NODE *func__39_136;
static void entry__39_136(void);
static FRAME_INFO frame__39_136 = {0, {}};
static NODE *string__39_137;
static NODE *func__39_138;
static void entry__39_138(void);
static FRAME_INFO frame__39_138 = {0, {}};
static NODE *string__39_139;
static NODE *func__39_140;
static void entry__39_140(void);
static FRAME_INFO frame__39_140 = {0, {}};
static NODE *string__39_141;
static NODE *func__39_142;
static void entry__39_142(void);
static FRAME_INFO frame__39_142 = {0, {}};
static NODE *string__39_143;
static NODE *func__39_144;
static void entry__39_144(void);
static FRAME_INFO frame__39_144 = {0, {}};
static void cont__39_145(void);
static void cont__39_146(void);
static NODE *func__39_147;
static void entry__39_147(void);
static FRAME_INFO frame__39_147 = {2, {"remark", "kind_info"}};
static void cont__39_148(void);
static NODE *func__39_149;
static void entry__39_149(void);
static FRAME_INFO frame__39_149 = {2, {"remark", "kind_info"}};
static NODE *string__39_150;
static void cont__39_151(void);
static NODE *func__39_152;
static void entry__39_152(void);
static FRAME_INFO frame__39_152 = {2, {"remark", "kind_info"}};
static void cont__39_153(void);
static void cont__39_154(void);
static NODE *func__39_155;
static void entry__39_155(void);
static FRAME_INFO frame__39_155 = {1, {"name"}};
static void cont__39_156(void);
static void cont__39_157(void);
static NODE *func__39_158;
static void entry__39_158(void);
static FRAME_INFO frame__39_158 = {2, {"name", "remark"}};
static NODE *func__39_159;
static void entry__39_159(void);
static FRAME_INFO frame__39_159 = {2, {"name", "remark"}};
static NODE *string__39_160;
static NODE *string__39_161;
static void cont__39_162(void);
static void cont__39_163(void);
static void cont__39_164(void);
static NODE *func__39_165;
static void entry__39_165(void);
static FRAME_INFO frame__39_165 = {1, {"name"}};
static void cont__39_166(void);
static void cont__39_167(void);
static void cont__39_168(void);
static void cont__39_169(void);
static void cont__39_170(void);
static NODE *string__39_171;
static void cont__39_172(void);
static void cont__39_173(void);
static NODE *func__39_174;
static void entry__39_174(void);
static FRAME_INFO frame__39_174 = {3, {"iname", "info", "name"}};
static void cont__39_175(void);
static void cont__39_176(void);
static void cont__39_177(void);
static NODE *func__39_178;
static void entry__39_178(void);
static FRAME_INFO frame__39_178 = {2, {"info", "name"}};
static void cont__39_179(void);
static NODE *func__39_180;
static void entry__39_180(void);
static FRAME_INFO frame__39_180 = {3, {"method_name", "method_info", "name"}};
static void cont__39_181(void);
static void cont__39_182(void);
static NODE *string__39_183;
static NODE *func__39_184;
static void entry__39_184(void);
static FRAME_INFO frame__39_184 = {0, {}};
static void cont__39_185(void);
static void cont__39_186(void);
static void cont__39_187(void);
static NODE *func__39_188;
static void entry__39_188(void);
static FRAME_INFO frame__39_188 = {0, {}};
static NODE *func__39_189;
static void entry__39_189(void);
static FRAME_INFO frame__39_189 = {3, {"topic", "references", "filename"}};
static void cont__39_190(void);
static void cont__39_191(void);
static void cont__39_192(void);
static void cont__39_193(void);
static NODE *func__39_194;
static void entry__39_194(void);
static FRAME_INFO frame__39_194 = {2, {"filename", "topic"}};
static NODE *func__39_195;
static void entry__39_195(void);
static FRAME_INFO frame__39_195 = {2, {"filename", "topic"}};
static void cont__39_196(void);
static void cont__39_197(void);
static NODE *func__39_198;
static void entry__39_198(void);
static FRAME_INFO frame__39_198 = {3, {"topic", "references", "filename"}};
static void cont__39_199(void);
static void cont__39_200(void);
static void cont__39_201(void);
static void cont__39_202(void);
static NODE *func__39_203;
static void entry__39_203(void);
static FRAME_INFO frame__39_203 = {3, {"topic", "references", "paragraphs"}};
static void cont__39_204(void);
static void cont__39_205(void);
static void cont__39_206(void);
static void cont__39_207(void);
static void cont__39_208(void);
static NODE *func__39_209;
static void entry__39_209(void);
static FRAME_INFO frame__39_209 = {1, {"paragraphs"}};
static NODE *func__39_210;
static void entry__39_210(void);
static FRAME_INFO frame__39_210 = {1, {"paragraph"}};
static void cont__39_211(void);
static void cont__39_212(void);
static NODE *func__39_213;
static void entry__39_213(void);
static FRAME_INFO frame__39_213 = {1, {"references"}};
static NODE *func__39_214;
static void entry__39_214(void);
static FRAME_INFO frame__39_214 = {1, {"reference"}};
static NODE *func__39_215;
static void entry__39_215(void);
static FRAME_INFO frame__39_215 = {1, {"reference"}};
static NODE *func__39_216;
static void entry__39_216(void);
static FRAME_INFO frame__39_216 = {1, {"reference"}};
static void cont__39_217(void);
static void cont__39_218(void);
static void cont__39_219(void);
static void cont__39_220(void);
static void cont__39_221(void);
static void cont__39_222(void);
static void cont__39_223(void);
static NODE *string__39_224;
static NODE *func__39_225;
static void entry__39_225(void);
static FRAME_INFO frame__39_225 = {0, {}};
static NODE *string__39_226;
static void cont__39_227(void);
static NODE *func__39_228;
static void entry__39_228(void);
static FRAME_INFO frame__39_228 = {0, {}};
static void cont__39_229(void);
static void cont__39_230(void);
static NODE *func__39_231;
static void entry__39_231(void);
static FRAME_INFO frame__39_231 = {0, {}};
static void cont__39_232(void);
static void cont__39_233(void);
static NODE *func__39_234;
static void entry__39_234(void);
static FRAME_INFO frame__39_234 = {0, {}};
static void cont__39_235(void);
static void cont__39_236(void);
static NODE *func__39_237;
static void entry__39_237(void);
static FRAME_INFO frame__39_237 = {0, {}};
static void cont__39_238(void);
static void cont__39_239(void);
static NODE *func__39_240;
static void entry__39_240(void);
static FRAME_INFO frame__39_240 = {13, {"total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_methods", "total_inline_c_methods", "total_inline_c_types", "total_inline_c_objects", "total_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "other", "total_definitions"}};
static NODE *func__39_241;
static void entry__39_241(void);
static FRAME_INFO frame__39_241 = {14, {"iname", "info", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_inline_c_functions", "total_inline_c_types", "total_inline_c_objects", "total_unique_items", "total_constants", "other", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__39_242(void);
static NODE *func__39_243;
static void entry__39_243(void);
static FRAME_INFO frame__39_243 = {1, {"total_functions"}};
static void cont__39_244(void);
static NODE *func__39_245;
static void entry__39_245(void);
static FRAME_INFO frame__39_245 = {1, {"total_polymorphic_functions"}};
static void cont__39_246(void);
static NODE *func__39_247;
static void entry__39_247(void);
static FRAME_INFO frame__39_247 = {1, {"total_polymorphic_attributes"}};
static void cont__39_248(void);
static NODE *func__39_249;
static void entry__39_249(void);
static FRAME_INFO frame__39_249 = {1, {"total_inline_c_functions"}};
static void cont__39_250(void);
static NODE *func__39_251;
static void entry__39_251(void);
static FRAME_INFO frame__39_251 = {1, {"total_inline_c_types"}};
static void cont__39_252(void);
static NODE *func__39_253;
static void entry__39_253(void);
static FRAME_INFO frame__39_253 = {1, {"total_inline_c_objects"}};
static void cont__39_254(void);
static NODE *func__39_255;
static void entry__39_255(void);
static FRAME_INFO frame__39_255 = {1, {"total_unique_items"}};
static void cont__39_256(void);
static NODE *func__39_257;
static void entry__39_257(void);
static FRAME_INFO frame__39_257 = {1, {"total_constants"}};
static void cont__39_258(void);
static NODE *func__39_259;
static void entry__39_259(void);
static FRAME_INFO frame__39_259 = {1, {"other"}};
static void cont__39_260(void);
static void cont__39_261(void);
static void cont__39_262(void);
static NODE *func__39_263;
static void entry__39_263(void);
static FRAME_INFO frame__39_263 = {4, {"info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__39_264(void);
static NODE *func__39_265;
static void entry__39_265(void);
static FRAME_INFO frame__39_265 = {5, {"method_name", "method_info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__39_266(void);
static NODE *func__39_267;
static void entry__39_267(void);
static FRAME_INFO frame__39_267 = {1, {"total_methods"}};
static void cont__39_268(void);
static NODE *func__39_269;
static void entry__39_269(void);
static FRAME_INFO frame__39_269 = {1, {"total_inline_c_methods"}};
static void cont__39_270(void);
static NODE *func__39_271;
static void entry__39_271(void);
static FRAME_INFO frame__39_271 = {1, {"total_attributes"}};
static void cont__39_272(void);
static void cont__39_273(void);
static void cont__39_274(void);
static void cont__39_275(void);
static void cont__39_276(void);
static void cont__39_277(void);
static void cont__39_278(void);
static void cont__39_279(void);
static void cont__39_280(void);
static void cont__39_281(void);
static void cont__39_282(void);
static void cont__39_283(void);
static void cont__39_284(void);
static void cont__39_285(void);
static void cont__39_286(void);
static void cont__39_287(void);
static void cont__39_288(void);
static void cont__39_289(void);
static void cont__39_290(void);
static void cont__39_291(void);
static void cont__39_292(void);
static void cont__39_293(void);
static void cont__39_294(void);
static void cont__39_295(void);
static void cont__39_296(void);
static void cont__39_297(void);
static NODE *string__39_298;
static NODE *string__39_299;
static NODE *string__39_300;
static NODE *string__39_301;
static NODE *string__39_302;
static NODE *string__39_303;
static NODE *string__39_304;
static NODE *string__39_305;
static NODE *string__39_306;
static NODE *string__39_307;
static NODE *string__39_308;
static NODE *string__39_309;
static NODE *string__39_310;
static NODE *string__39_311;
static void cont__39_312(void);
static NODE *get__sim2c__extract_documentation(void) {
  return var.sim2c__extract_documentation;
}
static void cont__45_1(void);
static void cont__60_1(void);
static void cont__60_2(void);
static void cont__60_3(void);
static void cont__60_4(void);
static void cont__60_5(void);
static void cont__60_6(void);
static void cont__60_7(void);
static NODE *string__71_1;
static void cont__71_2(void);
static void cont__71_3(void);
static NODE *string__72_1;
static NODE *string__72_2;
static void cont__72_3(void);
static void cont__72_4(void);
static void cont__72_5(void);
static void cont__72_6(void);
static void cont__72_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__45_1, NULL, 64, 64, 15, 55},
  {cont__60_1, NULL, 64, 64, 7, 56},
  {cont__60_2, NULL, 65, 65, 12, 31},
  {cont__60_3, NULL, 65, 65, 12, 46},
  {cont__60_4, NULL, 65, 65, 7, 47},
  {cont__60_5, NULL, 63, 65, 5, 46},
  {cont__60_6, NULL, 59, 65, 1, 49},
  {cont__60_7, NULL, 386, 386, 8, 28},
  {cont__71_2, NULL, 386, 386, 1, 33},
  {cont__71_3, NULL, 387, 387, 10, 32},
  {cont__72_3, NULL, 387, 387, 40, 59},
  {cont__72_4, NULL, 387, 387, 40, 74},
  {cont__72_5, NULL, 387, 387, 35, 75},
  {cont__72_6, NULL, 387, 387, 1, 80},
  {cont__72_7, NULL, },
  {entry__23_4, NULL, 75, 153, 9, 11},
  {entry__23_3, NULL, 74, 153, 7, 12},
  {cont__23_6, &frame__23_3, 154, 154, 7, 15},
  {entry__23_2, NULL, 73, 154, 5, 15},
  {entry__23_1_create_page, NULL, 72, 154, 3, 16},
  {cont__23_7, &frame__23_1_create_page, 155, 155, 3, 20},
  {entry__25_10, NULL, 170, 170, 27, 52},
  {entry__25_16, NULL, 171, 171, 21, 63},
  {entry__25_23, NULL, 172, 172, 26, 71},
  {entry__25_32, NULL, 186, 186, 39, 56},
  {cont__25_33, &frame__25_32, 186, 186, 56, 56},
  {entry__25_39, NULL, 196, 196, 11, 26},
  {cont__25_40, &frame__25_39, 197, 197, 11, 48},
  {cont__25_41, &frame__25_39, 197, 197, 48, 48},
  {entry__25_42, NULL, 199, 199, 11, 14},
  {entry__25_43, NULL, 194, 194, 11, 14},
  {entry__25_36, NULL, 192, 192, 9, 27},
  {cont__25_37, &frame__25_36, 192, 192, 9, 30},
  {cont__25_38, &frame__25_36, 191, 199, 7, 15},
  {entry__25_35, NULL, 190, 199, 5, 16},
  {cont__25_44, &frame__25_35, 199, 199, 16, 16},
  {entry__25_48, NULL, 201, 201, 46, 70},
  {cont__25_49, &frame__25_48, 201, 201, 34, 70},
  {cont__25_50, &frame__25_48, 201, 201, 70, 70},
  {entry__25_53, NULL, 202, 202, 32, 54},
  {cont__25_55, &frame__25_53, 202, 202, 59, 59},
  {entry__25_60, NULL, 206, 206, 33, 36},
  {entry__25_58, NULL, 206, 206, 10, 30},
  {cont__25_59, &frame__25_58, 206, 206, 7, 36},
  {entry__25_63, NULL, 207, 207, 31, 34},
  {entry__25_61, NULL, 207, 207, 10, 28},
  {cont__25_62, &frame__25_61, 207, 207, 7, 34},
  {entry__25_78, NULL, 215, 215, 43, 68},
  {cont__25_79, &frame__25_78, 215, 215, 35, 69},
  {cont__25_80, &frame__25_78, 215, 215, 15, 70},
  {cont__25_81, &frame__25_78, 215, 215, 75, 75},
  {entry__25_74, NULL, 213, 213, 21, 43},
  {cont__25_75, &frame__25_74, 213, 213, 13, 46},
  {cont__25_76, &frame__25_74, 214, 214, 16, 56},
  {cont__25_77, &frame__25_74, 214, 215, 13, 75},
  {entry__25_70, NULL, 211, 211, 11, 48},
  {cont__25_71, &frame__25_70, 212, 212, 18, 41},
  {cont__25_72, &frame__25_70, 212, 212, 18, 52},
  {cont__25_73, &frame__25_70, 212, 215, 11, 76},
  {entry__25_66, NULL, 209, 209, 22, 51},
  {cont__25_67, &frame__25_66, 209, 209, 9, 54},
  {cont__25_68, &frame__25_66, 210, 210, 12, 38},
  {cont__25_69, &frame__25_66, 210, 215, 9, 77},
  {entry__25_64, NULL, 208, 208, 10, 35},
  {cont__25_65, &frame__25_64, 208, 215, 7, 78},
  {entry__25_57, NULL, 205, 215, 5, 79},
  {entry__25_95, NULL, 228, 228, 27, 53},
  {cont__25_96, &frame__25_95, 228, 228, 15, 54},
  {cont__25_97, &frame__25_95, 229, 229, 58, 62},
  {cont__25_98, &frame__25_95, 229, 229, 65, 65},
  {cont__25_99, &frame__25_95, 229, 229, 15, 66},
  {cont__25_100, &frame__25_95, 229, 229, 15, 39},
  {cont__25_101, &frame__25_95, 230, 230, 15, 18},
  {entry__25_93, NULL, 227, 227, 16, 46},
  {cont__25_94, &frame__25_93, 227, 230, 13, 18},
  {entry__25_92, NULL, 226, 230, 25, 19},
  {cont__25_102, &frame__25_92, 230, 230, 19, 19},
  {entry__25_90, NULL, 225, 225, 11, 48},
  {cont__25_91, &frame__25_90, 226, 230, 11, 19},
  {entry__25_86, NULL, 223, 223, 9, 48},
  {cont__25_87, &frame__25_86, 224, 224, 12, 51},
  {cont__25_89, &frame__25_86, 224, 230, 9, 20},
  {entry__25_84, NULL, 222, 222, 10, 30},
  {cont__25_85, &frame__25_84, 222, 230, 7, 21},
  {entry__25_120, NULL, 245, 245, 55, 68},
  {cont__25_121, &frame__25_120, 245, 245, 52, 68},
  {entry__25_122, NULL, 245, 245, 71, 82},
  {entry__25_116, NULL, 240, 240, 19, 42},
  {cont__25_117, &frame__25_116, 244, 244, 32, 51},
  {cont__25_118, &frame__25_116, 245, 245, 35, 49},
  {cont__25_119, &frame__25_116, 245, 245, 32, 83},
  {cont__25_123, &frame__25_116, 246, 246, 40, 65},
  {cont__25_124, &frame__25_116, 241, 241, 32, 59},
  {cont__25_125, &frame__25_116, 241, 241, 19, 60},
  {cont__25_126, &frame__25_116, 247, 247, 45, 45},
  {entry__25_114, NULL, 239, 239, 20, 39},
  {cont__25_115, &frame__25_114, 239, 247, 17, 45},
  {entry__25_127, NULL, 252, 252, 30, 49},
  {cont__25_128, &frame__25_127, 253, 253, 38, 63},
  {cont__25_129, &frame__25_127, 249, 249, 30, 57},
  {cont__25_130, &frame__25_127, 249, 249, 17, 58},
  {cont__25_131, &frame__25_127, 254, 254, 43, 43},
  {entry__25_111, NULL, 236, 236, 13, 37},
  {cont__25_112, &frame__25_111, 237, 237, 18, 35},
  {cont__25_113, &frame__25_111, 237, 254, 13, 44},
  {entry__25_108, NULL, 234, 234, 11, 45},
  {cont__25_109, &frame__25_108, 235, 235, 14, 33},
  {cont__25_110, &frame__25_108, 235, 254, 11, 45},
  {entry__25_105, NULL, 232, 232, 9, 44},
  {cont__25_106, &frame__25_105, 233, 233, 12, 32},
  {cont__25_107, &frame__25_105, 233, 254, 9, 46},
  {entry__25_103, NULL, 231, 231, 10, 28},
  {cont__25_104, &frame__25_103, 231, 254, 7, 47},
  {entry__25_157, NULL, 278, 278, 27, 50},
  {entry__25_158, NULL, 279, 279, 27, 49},
  {entry__25_154, NULL, 272, 272, 19, 56},
  {cont__25_155, &frame__25_154, 277, 277, 27, 44},
  {cont__25_156, &frame__25_154, 276, 279, 25, 48},
  {cont__25_159, &frame__25_154, 273, 273, 19, 37},
  {cont__25_160, &frame__25_154, 280, 280, 19, 23},
  {entry__25_152, NULL, 271, 271, 20, 60},
  {cont__25_153, &frame__25_152, 271, 280, 17, 23},
  {entry__25_167, NULL, 289, 289, 28, 50},
  {cont__25_168, &frame__25_167, 289, 289, 25, 50},
  {entry__25_169, NULL, 290, 290, 28, 53},
  {cont__25_170, &frame__25_169, 290, 290, 25, 53},
  {entry__25_163, NULL, 285, 285, 36, 56},
  {cont__25_164, &frame__25_163, 288, 288, 25, 50},
  {cont__25_165, &frame__25_163, 288, 288, 25, 59},
  {cont__25_166, &frame__25_163, 287, 290, 23, 52},
  {cont__25_171, &frame__25_163, 290, 290, 56, 56},
  {entry__25_161, NULL, 281, 281, 20, 35},
  {cont__25_162, &frame__25_161, 281, 290, 17, 56},
  {entry__25_175, NULL, 292, 292, 49, 49},
  {entry__25_173, NULL, 291, 291, 20, 37},
  {cont__25_174, &frame__25_173, 291, 292, 17, 49},
  {entry__25_181, NULL, 295, 295, 21, 50},
  {cont__25_182, &frame__25_181, 295, 295, 50, 50},
  {entry__25_178, NULL, 294, 294, 22, 41},
  {cont__25_179, &frame__25_178, 294, 294, 22, 52},
  {cont__25_180, &frame__25_178, 294, 295, 19, 50},
  {entry__25_176, NULL, 293, 293, 20, 42},
  {cont__25_177, &frame__25_176, 293, 295, 17, 51},
  {entry__25_185, NULL, 297, 297, 19, 37},
  {cont__25_186, &frame__25_185, 298, 298, 19, 23},
  {entry__25_183, NULL, 296, 296, 20, 51},
  {cont__25_184, &frame__25_183, 296, 298, 17, 23},
  {entry__25_189, NULL, 300, 300, 40, 40},
  {entry__25_187, NULL, 299, 299, 20, 39},
  {cont__25_188, &frame__25_187, 299, 300, 17, 40},
  {entry__25_198, NULL, 307, 307, 23, 66},
  {cont__25_199, &frame__25_198, 308, 308, 23, 82},
  {cont__25_200, &frame__25_198, 309, 309, 23, 70},
  {cont__25_201, &frame__25_198, 309, 309, 70, 70},
  {entry__25_195, NULL, 306, 306, 24, 51},
  {cont__25_196, &frame__25_195, 306, 306, 24, 68},
  {cont__25_197, &frame__25_195, 306, 309, 21, 70},
  {entry__25_192, NULL, 304, 304, 19, 57},
  {cont__25_193, &frame__25_192, 305, 305, 22, 51},
  {cont__25_194, &frame__25_192, 305, 309, 19, 71},
  {cont__25_202, &frame__25_192, 310, 310, 19, 37},
  {cont__25_203, &frame__25_192, 310, 310, 42, 42},
  {entry__25_217, NULL, 322, 322, 64, 64},
  {entry__25_214, NULL, 321, 321, 30, 47},
  {cont__25_215, &frame__25_214, 321, 321, 30, 58},
  {cont__25_216, &frame__25_214, 321, 322, 23, 64},
  {cont__25_218, &frame__25_214, 323, 323, 50, 67},
  {cont__25_219, &frame__25_214, 323, 323, 23, 80},
  {cont__25_220, &frame__25_214, 325, 325, 24, 44},
  {cont__25_221, &frame__25_214, 325, 325, 23, 55},
  {cont__25_222, &frame__25_214, 326, 326, 23, 41},
  {cont__25_223, &frame__25_214, 326, 326, 52, 52},
  {entry__25_211, NULL, 319, 319, 21, 45},
  {cont__25_212, &frame__25_211, 320, 320, 28, 56},
  {cont__25_213, &frame__25_211, 320, 326, 21, 52},
  {entry__25_205, NULL, 312, 312, 19, 50},
  {cont__25_206, &frame__25_205, 315, 315, 35, 52},
  {cont__25_207, &frame__25_205, 315, 315, 21, 65},
  {cont__25_208, &frame__25_205, 317, 317, 19, 37},
  {cont__25_209, &frame__25_205, 318, 318, 22, 36},
  {cont__25_210, &frame__25_205, 318, 326, 19, 53},
  {entry__25_144, NULL, 263, 263, 15, 39},
  {cont__25_145, &frame__25_144, 264, 264, 15, 49},
  {cont__25_146, &frame__25_144, 266, 266, 26, 45},
  {cont__25_147, &frame__25_144, 267, 267, 35, 63},
  {cont__25_148, &frame__25_144, 268, 268, 34, 59},
  {cont__25_149, &frame__25_144, 269, 269, 23, 45},
  {cont__25_150, &frame__25_144, 269, 269, 15, 48},
  {cont__25_151, &frame__25_144, 270, 300, 15, 41},
  {cont__25_190, &frame__25_144, 302, 302, 17, 46},
  {cont__25_191, &frame__25_144, 311, 311, 17, 43},
  {cont__25_204, &frame__25_144, 301, 326, 15, 55},
  {entry__25_140, NULL, 260, 260, 13, 50},
  {cont__25_141, &frame__25_140, 261, 261, 13, 47},
  {cont__25_142, &frame__25_140, 262, 262, 16, 35},
  {cont__25_143, &frame__25_140, 262, 326, 13, 56},
  {entry__25_136, NULL, 256, 256, 22, 51},
  {cont__25_137, &frame__25_136, 256, 256, 22, 54},
  {cont__25_138, &frame__25_136, 259, 259, 11, 37},
  {cont__25_139, &frame__25_136, 258, 326, 9, 58},
  {entry__25_134, NULL, 255, 255, 10, 35},
  {cont__25_135, &frame__25_134, 255, 326, 7, 59},
  {entry__25_83, NULL, 221, 326, 5, 60},
  {cont__25_224, &frame__25_83, 326, 326, 60, 60},
  {entry__25_1_extract_documentation_from_file, NULL, 168, 168, 10, 56},
  {cont__25_4, &frame__25_1_extract_documentation_from_file, 168, 168, 3, 56},
  {cont__25_5, &frame__25_1_extract_documentation_from_file, 169, 169, 8, 21},
  {cont__25_6, &frame__25_1_extract_documentation_from_file, 169, 169, 3, 31},
  {cont__25_7, &frame__25_1_extract_documentation_from_file, 170, 170, 6, 19},
  {cont__25_8, &frame__25_1_extract_documentation_from_file, 170, 170, 6, 24},
  {cont__25_9, &frame__25_1_extract_documentation_from_file, 170, 170, 3, 52},
  {cont__25_12, &frame__25_1_extract_documentation_from_file, 171, 171, 6, 11},
  {cont__25_13, &frame__25_1_extract_documentation_from_file, 171, 171, 6, 18},
  {cont__25_14, &frame__25_1_extract_documentation_from_file, 171, 171, 6, 18},
  {cont__25_15, &frame__25_1_extract_documentation_from_file, 171, 171, 3, 63},
  {cont__25_18, &frame__25_1_extract_documentation_from_file, 172, 172, 11, 11},
  {cont__25_19, &frame__25_1_extract_documentation_from_file, 172, 172, 6, 12},
  {cont__25_20, &frame__25_1_extract_documentation_from_file, 172, 172, 6, 23},
  {cont__25_21, &frame__25_1_extract_documentation_from_file, 172, 172, 6, 23},
  {cont__25_22, &frame__25_1_extract_documentation_from_file, 172, 172, 3, 71},
  {cont__25_25, &frame__25_1_extract_documentation_from_file, 175, 175, 17, 48},
  {cont__25_27, &frame__25_1_extract_documentation_from_file, 175, 175, 50, 59},
  {cont__25_29, &frame__25_1_extract_documentation_from_file, 174, 176, 3, 69},
  {cont__25_30, &frame__25_1_extract_documentation_from_file, 185, 185, 3, 37},
  {cont__25_31, &frame__25_1_extract_documentation_from_file, 186, 186, 3, 56},
  {cont__25_34, &frame__25_1_extract_documentation_from_file, 189, 199, 3, 17},
  {cont__25_45, &frame__25_1_extract_documentation_from_file, 200, 200, 31, 31},
  {cont__25_46, &frame__25_1_extract_documentation_from_file, 200, 200, 3, 31},
  {cont__25_47, &frame__25_1_extract_documentation_from_file, 201, 201, 3, 70},
  {cont__25_51, &frame__25_1_extract_documentation_from_file, 202, 202, 6, 29},
  {cont__25_52, &frame__25_1_extract_documentation_from_file, 202, 202, 3, 59},
  {cont__25_56, &frame__25_1_extract_documentation_from_file, 204, 215, 3, 80},
  {cont__25_82, &frame__25_1_extract_documentation_from_file, 216, 326, 3, 61},
  {cont__25_225, &frame__25_1_extract_documentation_from_file, 326, 326, 61, 61},
  {entry__26_8, NULL, 332, 332, 32, 72},
  {entry__26_6, NULL, 332, 332, 10, 29},
  {cont__26_7, &frame__26_6, 332, 332, 7, 72},
  {entry__26_11, NULL, 333, 333, 36, 71},
  {entry__26_9, NULL, 333, 333, 10, 33},
  {cont__26_10, &frame__26_9, 333, 333, 7, 71},
  {entry__26_4, NULL, 330, 330, 5, 28},
  {cont__26_5, &frame__26_4, 331, 333, 5, 71},
  {entry__26_1_extract_documentation_from_directory, NULL, 329, 329, 22, 27},
  {cont__26_2, &frame__26_1_extract_documentation_from_directory, 329, 329, 12, 33},
  {cont__26_3, &frame__26_1_extract_documentation_from_directory, 329, 333, 3, 72},
  {entry__27_5, NULL, 337, 337, 40, 53},
  {cont__27_6, &frame__27_5, 337, 337, 37, 53},
  {entry__27_13, NULL, 342, 343, 17, 64},
  {cont__27_16, &frame__27_13, 342, 343, 11, 64},
  {entry__27_11, NULL, 341, 341, 12, 40},
  {cont__27_12, &frame__27_11, 341, 343, 9, 65},
  {cont__27_17, &frame__27_11, 344, 344, 37, 37},
  {entry__27_9, NULL, 340, 340, 10, 46},
  {cont__27_10, &frame__27_9, 340, 344, 7, 37},
  {entry__27_20, NULL, 346, 347, 13, 51},
  {cont__27_22, &frame__27_20, 346, 347, 7, 51},
  {entry__27_7, NULL, 339, 339, 14, 37},
  {cont__27_8, &frame__27_7, 339, 344, 5, 38},
  {cont__27_18, &frame__27_7, 345, 345, 12, 40},
  {cont__27_19, &frame__27_7, 345, 347, 5, 52},
  {cont__27_23, &frame__27_7, 348, 348, 8, 43},
  {cont__27_25, &frame__27_7, 348, 348, 5, 43},
  {entry__27_1_resolved_name, NULL, 336, 336, 3, 21},
  {cont__27_2, &frame__27_1_resolved_name, 337, 337, 6, 23},
  {cont__27_3, &frame__27_1_resolved_name, 337, 337, 6, 34},
  {cont__27_4, &frame__27_1_resolved_name, 337, 348, 3, 43},
  {entry__28_15, NULL, 358, 358, 35, 69},
  {entry__28_12, NULL, 357, 357, 7, 39},
  {cont__28_13, &frame__28_12, 358, 358, 10, 32},
  {cont__28_14, &frame__28_12, 358, 358, 7, 69},
  {entry__28_7, NULL, 354, 354, 6, 32},
  {cont__28_8, &frame__28_7, 354, 354, 5, 38},
  {cont__28_9, &frame__28_7, 355, 355, 12, 30},
  {cont__28_10, &frame__28_7, 355, 355, 12, 47},
  {cont__28_11, &frame__28_7, 355, 358, 5, 69},
  {cont__28_16, &frame__28_7, 359, 359, 5, 23},
  {cont__28_17, &frame__28_7, 359, 359, 34, 34},
  {entry__28_1_add_derived_type, NULL, 351, 351, 23, 40},
  {cont__28_2, &frame__28_1_add_derived_type, 351, 351, 42, 59},
  {cont__28_3, &frame__28_1_add_derived_type, 351, 351, 3, 60},
  {cont__28_4, &frame__28_1_add_derived_type, 352, 352, 3, 33},
  {cont__28_5, &frame__28_1_add_derived_type, 353, 353, 6, 26},
  {cont__28_6, &frame__28_1_add_derived_type, 353, 359, 3, 34},
  {entry__29_1_mangled, NULL, 361, 361, 38, 48},
  {cont__29_2, &frame__29_1_mangled, 361, 361, 50, 60},
  {cont__29_4, &frame__29_1_mangled, 361, 361, 21, 61},
  {cont__29_5, &frame__29_1_mangled, 361, 361, 18, 61},
  {entry__30_1_ordered_name, NULL, 366, 366, 7, 24},
  {cont__30_2, &frame__30_1_ordered_name, 368, 368, 7, 29},
  {cont__30_3, &frame__30_1_ordered_name, 365, 372, 5, 14},
  {cont__30_4, &frame__30_1_ordered_name, 364, 372, 3, 16},
  {entry__31_2, NULL, 376, 376, 7, 27},
  {cont__31_5, &frame__31_2, 376, 376, 5, 34},
  {cont__31_7, &frame__31_2, 377, 377, 5, 29},
  {cont__31_9, &frame__31_2, 378, 378, 7, 28},
  {cont__31_11, &frame__31_2, 378, 378, 5, 37},
  {cont__31_13, &frame__31_2, 379, 379, 5, 29},
  {cont__31_14, &frame__31_2, 380, 380, 7, 32},
  {cont__31_16, &frame__31_2, 380, 380, 5, 45},
  {cont__31_18, &frame__31_2, 381, 381, 5, 29},
  {cont__31_19, &frame__31_2, 382, 382, 7, 34},
  {cont__31_21, &frame__31_2, 382, 382, 5, 49},
  {cont__31_23, &frame__31_2, 383, 383, 5, 29},
  {cont__31_24, &frame__31_2, 384, 384, 7, 34},
  {cont__31_26, &frame__31_2, 384, 384, 5, 49},
  {entry__31_1_link_bar, NULL, 375, 384, 3, 49},
  {entry__34_5, NULL, 398, 398, 13, 22},
  {cont__34_6, &frame__34_5, 399, 399, 13, 33},
  {cont__34_7, &frame__34_5, 400, 400, 22, 22},
  {entry__34_8, NULL, 402, 402, 13, 33},
  {cont__34_9, &frame__34_8, 402, 402, 33, 33},
  {entry__34_3, NULL, 397, 397, 11, 35},
  {cont__34_4, &frame__34_3, 396, 402, 9, 34},
  {entry__34_15, NULL, 407, 407, 15, 35},
  {cont__34_16, &frame__34_15, 408, 408, 22, 22},
  {entry__34_12, NULL, 406, 406, 16, 25},
  {cont__34_13, &frame__34_12, 406, 406, 16, 25},
  {cont__34_14, &frame__34_12, 406, 408, 13, 22},
  {entry__34_21, NULL, 412, 412, 60, 60},
  {entry__34_19, NULL, 412, 412, 20, 44},
  {cont__34_20, &frame__34_19, 412, 412, 17, 60},
  {entry__34_22, NULL, 414, 414, 17, 30},
  {cont__34_23, &frame__34_22, 414, 414, 30, 30},
  {entry__34_17, NULL, 411, 411, 15, 24},
  {cont__34_18, &frame__34_17, 410, 414, 13, 31},
  {cont__34_24, &frame__34_17, 415, 415, 26, 34},
  {cont__34_25, &frame__34_17, 415, 415, 13, 34},
  {cont__34_26, &frame__34_17, 415, 415, 34, 34},
  {entry__34_10, NULL, 405, 405, 11, 20},
  {cont__34_11, &frame__34_10, 404, 415, 9, 35},
  {entry__34_2, NULL, 394, 415, 5, 37},
  {entry__34_30, NULL, 416, 416, 18, 38},
  {cont__34_31, &frame__34_30, 416, 416, 38, 38},
  {entry__34_1_to_paragraphs, NULL, 393, 415, 3, 38},
  {cont__34_27, &frame__34_1_to_paragraphs, 416, 416, 6, 15},
  {cont__34_28, &frame__34_1_to_paragraphs, 416, 416, 6, 15},
  {cont__34_29, &frame__34_1_to_paragraphs, 416, 416, 3, 38},
  {cont__34_32, &frame__34_1_to_paragraphs, 417, 417, 3, 15},
  {entry__35_7, NULL, 424, 424, 41, 67},
  {cont__35_9, &frame__35_7, 424, 424, 67, 67},
  {entry__35_12, NULL, 425, 425, 43, 69},
  {cont__35_14, &frame__35_12, 425, 425, 69, 69},
  {entry__35_3, NULL, 422, 422, 7, 40},
  {cont__35_4, &frame__35_3, 423, 423, 7, 42},
  {cont__35_5, &frame__35_3, 424, 424, 14, 38},
  {cont__35_6, &frame__35_3, 424, 424, 7, 67},
  {cont__35_10, &frame__35_3, 425, 425, 14, 40},
  {cont__35_11, &frame__35_3, 425, 425, 7, 69},
  {cont__35_15, &frame__35_3, 426, 426, 7, 50},
  {cont__35_16, &frame__35_3, 426, 426, 50, 50},
  {entry__35_19, NULL, 428, 428, 41, 65},
  {cont__35_20, &frame__35_19, 428, 428, 65, 65},
  {entry__35_17, NULL, 428, 428, 14, 38},
  {cont__35_18, &frame__35_17, 428, 428, 7, 65},
  {entry__35_1_resolve_reference, NULL, 421, 421, 5, 28},
  {cont__35_2, &frame__35_1_resolve_reference, 420, 428, 3, 66},
  {cont__35_21, &frame__35_1_resolve_reference, },
  {entry__36_5, NULL, 436, 436, 29, 29},
  {cont__36_6, &frame__36_5, 436, 436, 9, 29},
  {cont__36_7, &frame__36_5, 437, 437, 9, 36},
  {cont__36_8, &frame__36_5, 438, 438, 30, 46},
  {cont__36_9, &frame__36_5, 438, 438, 12, 54},
  {cont__36_13, &frame__36_5, 438, 438, 9, 54},
  {entry__36_1_add_links, NULL, 434, 434, 33, 47},
  {cont__36_2, &frame__36_1_add_links, 434, 434, 24, 48},
  {cont__36_3, &frame__36_1_add_links, 434, 434, 7, 53},
  {cont__36_4, &frame__36_1_add_links, 433, 438, 5, 54},
  {cont__36_14, &frame__36_1_add_links, 431, 438, 3, 56},
  {cont__36_15, &frame__36_1_add_links, 438, 438, 57, 57},
  {entry__37_6, NULL, 446, 446, 24, 40},
  {cont__37_7, &frame__37_6, 444, 447, 13, 55},
  {cont__37_12, &frame__37_6, 444, 447, 7, 55},
  {entry__37_2_resolve_and_check_reference, NULL, 442, 442, 5, 32},
  {cont__37_3, &frame__37_2_resolve_and_check_reference, 443, 443, 8, 36},
  {cont__37_4, &frame__37_2_resolve_and_check_reference, 443, 443, 8, 49},
  {cont__37_5, &frame__37_2_resolve_and_check_reference, 443, 447, 5, 56},
  {cont__37_13, &frame__37_2_resolve_and_check_reference, },
  {entry__37_23, NULL, 454, 454, 11, 42},
  {cont__37_24, &frame__37_23, 455, 455, 11, 44},
  {cont__37_25, &frame__37_23, 461, 461, 15, 26},
  {cont__37_26, &frame__37_23, 465, 465, 15, 28},
  {cont__37_27, &frame__37_23, 457, 466, 13, 21},
  {cont__37_29, &frame__37_23, 456, 466, 11, 23},
  {entry__37_33, NULL, 471, 471, 27, 65},
  {entry__37_35, NULL, 472, 472, 29, 69},
  {entry__37_37, NULL, 473, 473, 28, 67},
  {entry__37_30, NULL, 468, 468, 11, 26},
  {cont__37_31, &frame__37_30, 470, 470, 16, 37},
  {cont__37_32, &frame__37_30, 470, 473, 11, 67},
  {entry__37_42, NULL, 484, 484, 39, 59},
  {cont__37_43, &frame__37_42, 484, 484, 39, 59},
  {entry__37_47, NULL, 489, 489, 28, 44},
  {cont__37_48, &frame__37_47, 487, 489, 18, 48},
  {cont__37_52, &frame__37_47, 487, 489, 11, 48},
  {entry__37_45, NULL, 485, 485, 9, 40},
  {cont__37_46, &frame__37_45, 486, 489, 9, 49},
  {entry__37_67, NULL, 507, 507, 58, 58},
  {cont__37_68, &frame__37_67, 507, 507, 39, 59},
  {cont__37_69, &frame__37_67, 507, 507, 21, 74},
  {cont__37_71, &frame__37_67, 507, 507, 74, 74},
  {entry__37_65, NULL, 506, 506, 22, 47},
  {cont__37_66, &frame__37_65, 506, 507, 19, 74},
  {entry__37_74, NULL, 510, 510, 49, 49},
  {cont__37_75, &frame__37_74, 510, 510, 30, 50},
  {cont__37_76, &frame__37_74, 509, 510, 21, 79},
  {cont__37_78, &frame__37_74, 510, 510, 80, 80},
  {entry__37_72, NULL, 508, 508, 22, 47},
  {cont__37_73, &frame__37_72, 508, 510, 19, 80},
  {entry__37_81, NULL, 514, 514, 26, 47},
  {cont__37_82, &frame__37_81, 514, 514, 26, 53},
  {cont__37_83, &frame__37_81, 516, 516, 26, 47},
  {cont__37_84, &frame__37_81, 516, 516, 26, 53},
  {cont__37_85, &frame__37_81, 512, 517, 21, 28},
  {cont__37_88, &frame__37_81, 517, 517, 29, 29},
  {entry__37_79, NULL, 511, 511, 22, 45},
  {cont__37_80, &frame__37_79, 511, 517, 19, 29},
  {entry__37_63, NULL, 504, 504, 17, 68},
  {cont__37_64, &frame__37_63, 505, 517, 17, 30},
  {cont__37_89, &frame__37_63, 518, 518, 31, 52},
  {cont__37_90, &frame__37_63, 518, 518, 17, 58},
  {cont__37_91, &frame__37_63, 519, 519, 34, 56},
  {cont__37_92, &frame__37_63, 519, 519, 17, 56},
  {cont__37_93, &frame__37_63, 519, 519, 56, 56},
  {entry__37_58, NULL, 501, 501, 19, 53},
  {cont__37_59, &frame__37_58, 497, 502, 17, 20},
  {cont__37_61, &frame__37_58, 495, 502, 15, 21},
  {cont__37_62, &frame__37_58, 494, 519, 13, 57},
  {entry__37_103, NULL, 533, 533, 64, 64},
  {cont__37_104, &frame__37_103, 533, 533, 42, 65},
  {cont__37_105, &frame__37_103, 533, 533, 21, 80},
  {cont__37_106, &frame__37_103, 533, 533, 80, 80},
  {entry__37_101, NULL, 532, 532, 22, 50},
  {cont__37_102, &frame__37_101, 532, 533, 19, 80},
  {entry__37_109, NULL, 537, 537, 47, 47},
  {cont__37_110, &frame__37_109, 537, 537, 25, 48},
  {cont__37_111, &frame__37_109, 535, 538, 21, 52},
  {cont__37_112, &frame__37_109, 538, 538, 53, 53},
  {entry__37_107, NULL, 534, 534, 22, 50},
  {cont__37_108, &frame__37_107, 534, 538, 19, 53},
  {entry__37_99, NULL, 530, 530, 17, 71},
  {cont__37_100, &frame__37_99, 531, 538, 17, 54},
  {cont__37_113, &frame__37_99, 539, 539, 31, 52},
  {cont__37_114, &frame__37_99, 539, 539, 17, 58},
  {cont__37_115, &frame__37_99, 540, 540, 37, 62},
  {cont__37_116, &frame__37_99, 540, 540, 17, 62},
  {cont__37_117, &frame__37_99, 540, 540, 62, 62},
  {entry__37_94, NULL, 527, 527, 19, 53},
  {cont__37_95, &frame__37_94, 523, 528, 17, 20},
  {cont__37_97, &frame__37_94, 521, 528, 15, 21},
  {cont__37_98, &frame__37_94, 520, 540, 13, 63},
  {entry__37_124, NULL, 543, 543, 34, 47},
  {cont__37_125, &frame__37_124, 543, 543, 17, 47},
  {cont__37_126, &frame__37_124, 543, 543, 47, 47},
  {entry__37_121, NULL, 542, 542, 30, 51},
  {cont__37_122, &frame__37_121, 542, 542, 24, 56},
  {cont__37_123, &frame__37_121, 542, 543, 15, 47},
  {entry__37_118, NULL, 541, 541, 16, 49},
  {cont__37_120, &frame__37_118, 541, 543, 13, 48},
  {entry__37_132, NULL, 546, 546, 17, 27},
  {cont__37_133, &frame__37_132, 547, 547, 17, 38},
  {cont__37_134, &frame__37_132, 550, 550, 33, 45},
  {cont__37_135, &frame__37_132, 549, 550, 17, 66},
  {cont__37_136, &frame__37_132, 552, 552, 17, 46},
  {cont__37_137, &frame__37_132, 553, 553, 17, 30},
  {cont__37_138, &frame__37_132, 553, 553, 45, 45},
  {entry__37_129, NULL, 545, 545, 30, 51},
  {cont__37_130, &frame__37_129, 545, 545, 24, 56},
  {cont__37_131, &frame__37_129, 545, 553, 15, 45},
  {entry__37_127, NULL, 544, 544, 16, 43},
  {cont__37_128, &frame__37_127, 544, 553, 13, 46},
  {entry__37_141, NULL, 555, 555, 23, 44},
  {cont__37_142, &frame__37_141, 555, 555, 15, 50},
  {cont__37_143, &frame__37_141, 556, 556, 22, 43},
  {cont__37_144, &frame__37_141, 556, 556, 15, 49},
  {cont__37_145, &frame__37_141, 557, 557, 30, 41},
  {cont__37_146, &frame__37_141, 557, 557, 15, 41},
  {cont__37_147, &frame__37_141, 557, 557, 41, 41},
  {entry__37_139, NULL, 554, 554, 16, 45},
  {cont__37_140, &frame__37_139, 554, 557, 13, 41},
  {entry__37_155, NULL, 562, 562, 47, 47},
  {entry__37_156, NULL, 564, 564, 19, 49},
  {cont__37_157, &frame__37_156, 564, 564, 49, 49},
  {entry__37_151, NULL, 559, 559, 24, 45},
  {cont__37_152, &frame__37_151, 559, 559, 15, 51},
  {cont__37_153, &frame__37_151, 561, 561, 17, 28},
  {cont__37_154, &frame__37_151, 560, 564, 15, 50},
  {entry__37_148, NULL, 558, 558, 16, 58},
  {cont__37_150, &frame__37_148, 558, 564, 13, 51},
  {entry__37_162, NULL, 571, 571, 41, 41},
  {cont__37_163, &frame__37_162, 571, 571, 21, 41},
  {cont__37_164, &frame__37_162, 572, 572, 21, 58},
  {cont__37_165, &frame__37_162, 573, 573, 42, 58},
  {cont__37_166, &frame__37_162, 573, 573, 24, 66},
  {cont__37_167, &frame__37_162, 573, 573, 21, 66},
  {entry__37_173, NULL, 578, 578, 23, 55},
  {cont__37_174, &frame__37_173, 578, 578, 55, 55},
  {entry__37_175, NULL, 580, 580, 23, 50},
  {cont__37_176, &frame__37_175, 580, 580, 50, 50},
  {entry__37_171, NULL, 577, 577, 21, 48},
  {cont__37_172, &frame__37_171, 576, 580, 19, 51},
  {entry__37_177, NULL, 582, 582, 46, 46},
  {entry__37_158, NULL, 569, 569, 45, 59},
  {cont__37_159, &frame__37_158, 569, 569, 36, 60},
  {cont__37_160, &frame__37_158, 569, 569, 19, 65},
  {cont__37_161, &frame__37_158, 568, 573, 17, 66},
  {cont__37_168, &frame__37_158, 566, 573, 15, 68},
  {cont__37_169, &frame__37_158, 575, 575, 17, 44},
  {cont__37_170, &frame__37_158, 574, 582, 15, 47},
  {entry__37_57, NULL, 493, 582, 11, 49},
  {entry__37_55, NULL, 491, 491, 9, 46},
  {cont__37_56, &frame__37_55, 492, 582, 9, 50},
  {entry__37_195, NULL, 598, 598, 25, 51},
  {cont__37_196, &frame__37_195, 598, 598, 25, 61},
  {cont__37_197, &frame__37_195, 595, 599, 23, 27},
  {cont__37_198, &frame__37_195, 599, 599, 28, 28},
  {entry__37_199, NULL, 601, 601, 23, 48},
  {cont__37_200, &frame__37_199, 601, 601, 48, 48},
  {entry__37_192, NULL, 594, 594, 21, 47},
  {cont__37_193, &frame__37_192, 594, 594, 21, 58},
  {cont__37_194, &frame__37_192, 593, 601, 19, 49},
  {entry__37_190, NULL, 592, 592, 20, 48},
  {cont__37_191, &frame__37_190, 592, 601, 17, 50},
  {entry__37_203, NULL, 603, 603, 19, 58},
  {cont__37_204, &frame__37_203, 603, 603, 58, 58},
  {entry__37_201, NULL, 602, 602, 20, 48},
  {cont__37_202, &frame__37_201, 602, 603, 17, 58},
  {entry__37_209, NULL, 608, 608, 22, 47},
  {cont__37_210, &frame__37_209, 608, 608, 22, 61},
  {cont__37_211, &frame__37_209, 608, 608, 22, 64},
  {cont__37_212, &frame__37_209, 608, 608, 19, 64},
  {entry__37_213, NULL, 609, 609, 19, 23},
  {entry__37_186, NULL, 590, 590, 30, 53},
  {cont__37_187, &frame__37_186, 590, 590, 22, 54},
  {cont__37_188, &frame__37_186, 590, 590, 15, 75},
  {cont__37_189, &frame__37_186, 591, 603, 15, 59},
  {cont__37_205, &frame__37_186, 607, 607, 23, 48},
  {cont__37_206, &frame__37_186, 607, 607, 23, 57},
  {cont__37_207, &frame__37_186, 607, 607, 19, 58},
  {cont__37_208, &frame__37_186, 605, 609, 15, 24},
  {cont__37_214, &frame__37_186, 611, 611, 32, 49},
  {cont__37_215, &frame__37_186, 611, 611, 15, 49},
  {cont__37_216, &frame__37_186, 611, 611, 49, 49},
  {entry__37_217, NULL, 588, 588, 15, 18},
  {entry__37_183, NULL, 586, 586, 13, 40},
  {cont__37_184, &frame__37_183, 587, 587, 13, 52},
  {cont__37_185, &frame__37_183, 585, 611, 11, 50},
  {entry__37_181, NULL, 584, 584, 18, 36},
  {cont__37_182, &frame__37_181, 584, 611, 9, 51},
  {entry__37_220, NULL, 612, 612, 40, 58},
  {entry__37_230, NULL, 618, 618, 19, 42},
  {cont__37_231, &frame__37_230, 618, 618, 17, 42},
  {entry__37_227, NULL, 617, 617, 16, 32},
  {cont__37_228, &frame__37_227, 617, 617, 13, 32},
  {cont__37_229, &frame__37_227, 618, 618, 13, 42},
  {entry__37_226, NULL, 616, 618, 11, 42},
  {entry__37_223, NULL, 614, 614, 9, 23},
  {cont__37_225, &frame__37_223, 615, 618, 9, 43},
  {entry__37_240, NULL, 624, 624, 19, 45},
  {cont__37_241, &frame__37_240, 624, 624, 17, 45},
  {entry__37_237, NULL, 623, 623, 16, 35},
  {cont__37_238, &frame__37_237, 623, 623, 13, 35},
  {cont__37_239, &frame__37_237, 624, 624, 13, 45},
  {entry__37_236, NULL, 622, 624, 11, 45},
  {entry__37_234, NULL, 620, 620, 9, 20},
  {cont__37_235, &frame__37_234, 621, 624, 9, 46},
  {entry__37_247, NULL, 627, 627, 46, 58},
  {entry__37_244, NULL, 626, 626, 9, 24},
  {cont__37_246, &frame__37_244, 627, 627, 9, 58},
  {entry__37_253, NULL, 630, 630, 46, 53},
  {entry__37_250, NULL, 629, 629, 9, 30},
  {cont__37_252, &frame__37_250, 630, 630, 9, 53},
  {entry__37_263, NULL, 637, 637, 33, 49},
  {cont__37_264, &frame__37_263, 637, 637, 30, 56},
  {cont__37_265, &frame__37_263, 637, 637, 21, 56},
  {cont__37_266, &frame__37_263, 637, 637, 19, 66},
  {entry__37_262, NULL, 637, 637, 15, 66},
  {cont__37_267, &frame__37_262, 638, 638, 15, 25},
  {cont__37_269, &frame__37_262, 639, 639, 18, 46},
  {cont__37_270, &frame__37_262, 639, 639, 15, 46},
  {entry__37_260, NULL, 635, 635, 13, 50},
  {cont__37_261, &frame__37_260, 636, 639, 13, 46},
  {entry__37_259, NULL, 634, 639, 11, 47},
  {entry__37_256, NULL, 632, 632, 9, 21},
  {cont__37_258, &frame__37_256, 633, 639, 9, 48},
  {entry__37_282, NULL, 646, 646, 33, 44},
  {cont__37_283, &frame__37_282, 646, 646, 30, 51},
  {cont__37_284, &frame__37_282, 646, 646, 21, 51},
  {cont__37_285, &frame__37_282, 646, 646, 19, 56},
  {entry__37_289, NULL, 648, 648, 33, 46},
  {cont__37_290, &frame__37_289, 648, 648, 30, 53},
  {cont__37_291, &frame__37_289, 648, 648, 21, 53},
  {cont__37_292, &frame__37_289, 648, 648, 19, 60},
  {entry__37_281, NULL, 646, 646, 15, 56},
  {cont__37_286, &frame__37_281, 647, 647, 15, 33},
  {cont__37_288, &frame__37_281, 648, 648, 15, 60},
  {entry__37_279, NULL, 644, 644, 13, 50},
  {cont__37_280, &frame__37_279, 645, 648, 13, 60},
  {entry__37_277, NULL, 643, 643, 20, 33},
  {cont__37_278, &frame__37_277, 643, 648, 11, 61},
  {entry__37_274, NULL, 641, 641, 9, 27},
  {cont__37_276, &frame__37_274, 642, 648, 9, 62},
  {entry__37_295, NULL, 651, 651, 9, 61},
  {cont__37_296, &frame__37_295, 652, 652, 9, 23},
  {cont__37_298, &frame__37_295, 653, 653, 23, 55},
  {cont__37_299, &frame__37_295, 653, 653, 20, 62},
  {cont__37_300, &frame__37_295, 653, 653, 11, 62},
  {cont__37_301, &frame__37_295, 653, 654, 9, 35},
  {entry__37_312, NULL, 661, 661, 33, 51},
  {cont__37_313, &frame__37_312, 661, 661, 30, 58},
  {cont__37_314, &frame__37_312, 661, 661, 21, 58},
  {cont__37_315, &frame__37_312, 661, 661, 19, 70},
  {entry__37_318, NULL, 667, 667, 24, 44},
  {cont__37_319, &frame__37_318, 667, 667, 51, 69},
  {cont__37_320, &frame__37_318, 667, 667, 21, 76},
  {cont__37_321, &frame__37_318, 665, 667, 19, 75},
  {cont__37_322, &frame__37_318, 664, 670, 17, 29},
  {entry__37_311, NULL, 661, 661, 15, 70},
  {cont__37_316, &frame__37_311, 662, 662, 15, 25},
  {cont__37_317, &frame__37_311, 663, 670, 15, 30},
  {entry__37_310, NULL, 660, 670, 13, 31},
  {entry__37_308, NULL, 659, 659, 20, 35},
  {cont__37_309, &frame__37_308, 659, 670, 11, 32},
  {entry__37_305, NULL, 657, 657, 9, 44},
  {cont__37_307, &frame__37_305, 658, 670, 9, 33},
  {entry__37_338, NULL, 680, 680, 23, 39},
  {cont__37_339, &frame__37_338, 680, 680, 21, 45},
  {entry__37_337, NULL, 680, 680, 17, 45},
  {entry__37_331, NULL, 679, 679, 42, 60},
  {cont__37_332, &frame__37_331, 679, 679, 62, 70},
  {cont__37_334, &frame__37_331, 679, 679, 30, 71},
  {cont__37_335, &frame__37_331, 679, 679, 13, 80},
  {cont__37_336, &frame__37_331, 680, 680, 13, 45},
  {entry__37_330, NULL, 678, 680, 11, 45},
  {entry__37_327, NULL, 676, 676, 9, 19},
  {cont__37_329, &frame__37_327, 677, 680, 9, 46},
  {entry__37_354, NULL, 696, 696, 19, 35},
  {entry__37_349, NULL, 693, 693, 24, 48},
  {cont__37_350, &frame__37_349, 693, 693, 24, 63},
  {cont__37_351, &frame__37_349, 693, 693, 19, 64},
  {cont__37_352, &frame__37_349, 691, 694, 17, 25},
  {cont__37_353, &frame__37_349, 690, 696, 15, 35},
  {cont__37_355, &frame__37_349, 697, 697, 35, 69},
  {cont__37_357, &frame__37_349, 697, 697, 15, 69},
  {cont__37_358, &frame__37_349, 688, 697, 13, 68},
  {cont__37_359, &frame__37_349, 687, 697, 11, 70},
  {entry__37_341, NULL, 683, 683, 9, 30},
  {cont__37_342, &frame__37_341, 684, 684, 9, 36},
  {cont__37_343, &frame__37_341, 685, 685, 9, 16},
  {cont__37_344, &frame__37_341, 686, 686, 45, 56},
  {cont__37_345, &frame__37_341, 686, 686, 23, 56},
  {cont__37_346, &frame__37_341, 686, 686, 13, 56},
  {cont__37_348, &frame__37_341, 686, 697, 9, 71},
  {entry__37_20, NULL, 451, 451, 7, 14},
  {cont__37_21, &frame__37_20, 453, 453, 9, 36},
  {cont__37_22, &frame__37_20, 452, 473, 7, 69},
  {cont__37_39, &frame__37_20, 483, 483, 7, 41},
  {cont__37_40, &frame__37_20, 484, 484, 10, 34},
  {cont__37_41, &frame__37_20, 484, 484, 10, 59},
  {cont__37_44, &frame__37_20, 484, 489, 7, 50},
  {cont__37_53, &frame__37_20, 490, 490, 10, 32},
  {cont__37_54, &frame__37_20, 490, 582, 7, 51},
  {cont__37_178, &frame__37_20, 583, 583, 10, 22},
  {cont__37_179, &frame__37_20, 583, 583, 10, 34},
  {cont__37_180, &frame__37_20, 583, 611, 7, 52},
  {cont__37_218, &frame__37_20, 612, 612, 10, 37},
  {cont__37_219, &frame__37_20, 612, 612, 7, 58},
  {cont__37_221, &frame__37_20, 613, 613, 14, 32},
  {cont__37_222, &frame__37_20, 613, 618, 7, 44},
  {cont__37_232, &frame__37_20, 619, 619, 14, 35},
  {cont__37_233, &frame__37_20, 619, 624, 7, 47},
  {cont__37_242, &frame__37_20, 625, 625, 14, 34},
  {cont__37_243, &frame__37_20, 625, 627, 7, 58},
  {cont__37_248, &frame__37_20, 628, 628, 10, 37},
  {cont__37_249, &frame__37_20, 628, 630, 7, 53},
  {cont__37_254, &frame__37_20, 631, 631, 14, 32},
  {cont__37_255, &frame__37_20, 631, 639, 7, 49},
  {cont__37_271, &frame__37_20, 640, 640, 14, 27},
  {cont__37_272, &frame__37_20, 640, 640, 14, 36},
  {cont__37_273, &frame__37_20, 640, 648, 7, 63},
  {cont__37_293, &frame__37_20, 650, 650, 10, 37},
  {cont__37_294, &frame__37_20, 650, 654, 7, 36},
  {cont__37_302, &frame__37_20, 656, 656, 10, 22},
  {cont__37_303, &frame__37_20, 656, 656, 10, 39},
  {cont__37_304, &frame__37_20, 656, 670, 7, 34},
  {cont__37_323, &frame__37_20, 673, 673, 9, 42},
  {cont__37_324, &frame__37_20, 672, 673, 7, 64},
  {cont__37_325, &frame__37_20, 675, 675, 14, 32},
  {cont__37_326, &frame__37_20, 675, 680, 7, 47},
  {cont__37_340, &frame__37_20, 682, 697, 7, 72},
  {cont__37_360, &frame__37_20, 699, 699, 9, 26},
  {cont__37_362, &frame__37_20, 700, 700, 24, 40},
  {cont__37_363, &frame__37_20, 700, 700, 24, 69},
  {cont__37_364, &frame__37_20, 700, 700, 9, 76},
  {cont__37_367, &frame__37_20, 698, 700, 7, 76},
  {entry__37_15, NULL, 450, 450, 25, 45},
  {cont__37_16, &frame__37_15, 450, 450, 17, 52},
  {cont__37_19, &frame__37_15, 450, 700, 5, 77},
  {entry__37_1_create_info_page, NULL, 449, 449, 6, 29},
  {cont__37_14, &frame__37_1_create_info_page, 449, 700, 3, 78},
  {entry__38_4, NULL, 705, 705, 37, 57},
  {cont__38_5, &frame__38_4, 705, 705, 33, 58},
  {cont__38_6, &frame__38_4, 705, 705, 33, 58},
  {entry__38_12, NULL, 707, 707, 24, 46},
  {cont__38_13, &frame__38_12, 707, 707, 24, 46},
  {cont__38_14, &frame__38_12, 707, 707, 24, 46},
  {entry__38_10, NULL, 707, 707, 10, 19},
  {cont__38_11, &frame__38_10, 707, 707, 10, 46},
  {cont__38_15, &frame__38_10, 707, 707, 7, 52},
  {cont__38_16, &frame__38_10, 708, 708, 33, 41},
  {cont__38_17, &frame__38_10, 708, 708, 7, 41},
  {cont__38_18, &frame__38_10, 708, 708, 41, 41},
  {entry__38_9, NULL, 706, 708, 20, 41},
  {cont__38_19, &frame__38_9, 708, 708, 41, 41},
  {entry__38_21, NULL, 709, 709, 29, 56},
  {cont__38_22, &frame__38_21, 709, 709, 29, 61},
  {cont__38_23, &frame__38_21, 709, 709, 29, 61},
  {entry__38_25, NULL, 713, 713, 24, 40},
  {cont__38_26, &frame__38_25, 710, 715, 14, 28},
  {cont__38_29, &frame__38_25, 710, 715, 7, 28},
  {entry__38_8, NULL, 706, 708, 5, 41},
  {cont__38_20, &frame__38_8, 709, 709, 8, 61},
  {cont__38_24, &frame__38_8, 709, 715, 5, 29},
  {entry__38_1_get_short_description, NULL, 703, 703, 3, 37},
  {cont__38_2, &frame__38_1_get_short_description, 705, 705, 6, 28},
  {cont__38_3, &frame__38_1_get_short_description, 705, 705, 6, 58},
  {cont__38_7, &frame__38_1_get_short_description, 705, 715, 3, 30},
  {cont__38_30, &frame__38_1_get_short_description, 716, 716, 3, 30},
  {cont__38_31, &frame__38_1_get_short_description, 717, 717, 3, 22},
  {entry__39_14, NULL, 730, 730, 27, 53},
  {entry__39_19, NULL, 734, 734, 24, 48},
  {cont__39_20, &frame__39_19, 734, 734, 11, 62},
  {cont__39_21, &frame__39_19, 734, 734, 62, 62},
  {entry__39_17, NULL, 733, 733, 16, 42},
  {cont__39_18, &frame__39_17, 733, 734, 9, 62},
  {cont__39_22, &frame__39_17, 735, 735, 9, 45},
  {cont__39_24, &frame__39_17, 736, 736, 9, 79},
  {cont__39_25, &frame__39_17, 736, 736, 9, 36},
  {cont__39_26, &frame__39_17, 738, 738, 24, 48},
  {cont__39_27, &frame__39_17, 738, 738, 50, 74},
  {cont__39_28, &frame__39_17, 737, 738, 9, 75},
  {cont__39_29, &frame__39_17, 739, 739, 10, 27},
  {cont__39_30, &frame__39_17, 739, 739, 10, 36},
  {cont__39_31, &frame__39_17, 739, 739, 9, 42},
  {cont__39_32, &frame__39_17, 739, 739, 9, 27},
  {cont__39_33, &frame__39_17, 740, 740, 9, 29},
  {cont__39_34, &frame__39_17, 740, 740, 41, 41},
  {entry__39_11, NULL, 729, 729, 7, 25},
  {cont__39_12, &frame__39_11, 730, 730, 10, 24},
  {cont__39_13, &frame__39_11, 730, 730, 7, 53},
  {cont__39_15, &frame__39_11, 732, 732, 16, 31},
  {cont__39_16, &frame__39_11, 732, 740, 7, 41},
  {cont__39_35, &frame__39_11, 741, 741, 8, 25},
  {cont__39_36, &frame__39_11, 741, 741, 7, 25},
  {cont__39_37, &frame__39_11, 741, 741, 44, 44},
  {entry__39_5, NULL, 725, 725, 5, 23},
  {cont__39_6, &frame__39_5, 726, 726, 5, 62},
  {cont__39_7, &frame__39_5, 726, 726, 5, 29},
  {cont__39_8, &frame__39_5, 728, 728, 8, 20},
  {cont__39_9, &frame__39_5, 728, 728, 8, 37},
  {cont__39_10, &frame__39_5, 728, 741, 5, 44},
  {entry__39_47, NULL, 754, 754, 18, 50},
  {cont__39_48, &frame__39_47, 754, 754, 13, 50},
  {cont__39_49, &frame__39_47, 755, 755, 27, 39},
  {cont__39_50, &frame__39_47, 755, 755, 24, 46},
  {cont__39_51, &frame__39_47, 755, 755, 15, 46},
  {cont__39_52, &frame__39_47, 755, 755, 13, 52},
  {entry__39_46, NULL, 753, 755, 11, 52},
  {entry__39_55, NULL, 756, 756, 43, 63},
  {cont__39_56, &frame__39_55, 756, 756, 39, 64},
  {cont__39_57, &frame__39_55, 756, 756, 39, 64},
  {entry__39_59, NULL, 757, 757, 14, 39},
  {cont__39_60, &frame__39_59, 757, 757, 14, 42},
  {cont__39_61, &frame__39_59, 757, 757, 11, 42},
  {entry__39_64, NULL, 759, 759, 27, 43},
  {cont__39_65, &frame__39_64, 759, 759, 45, 52},
  {cont__39_66, &frame__39_64, 759, 759, 11, 52},
  {entry__39_42, NULL, 750, 750, 9, 28},
  {cont__39_43, &frame__39_42, 751, 751, 9, 43},
  {cont__39_44, &frame__39_42, 752, 752, 12, 27},
  {cont__39_45, &frame__39_42, 752, 755, 9, 53},
  {cont__39_53, &frame__39_42, 756, 756, 12, 34},
  {cont__39_54, &frame__39_42, 756, 756, 12, 64},
  {cont__39_58, &frame__39_42, 756, 757, 9, 42},
  {cont__39_62, &frame__39_42, 758, 758, 18, 39},
  {cont__39_63, &frame__39_42, 758, 759, 9, 52},
  {entry__39_41_print_type_info, NULL, 749, 759, 7, 53},
  {entry__39_73, NULL, 765, 765, 46, 58},
  {cont__39_74, &frame__39_73, 765, 765, 46, 71},
  {cont__39_75, &frame__39_73, 765, 765, 46, 71},
  {entry__39_77, NULL, 766, 766, 11, 30},
  {entry__39_70, NULL, 765, 765, 12, 24},
  {cont__39_71, &frame__39_70, 765, 765, 12, 41},
  {cont__39_72, &frame__39_70, 765, 765, 12, 71},
  {cont__39_76, &frame__39_70, 765, 766, 9, 30},
  {entry__39_69, NULL, 764, 766, 7, 31},
  {entry__39_40, NULL, 761, 761, 5, 12},
  {cont__39_67, &frame__39_40, 762, 762, 5, 19},
  {cont__39_68, &frame__39_40, 763, 766, 5, 32},
  {entry__39_86, NULL, 774, 774, 20, 31},
  {cont__39_88, &frame__39_86, 774, 774, 11, 31},
  {cont__39_89, &frame__39_86, 774, 774, 33, 52},
  {cont__39_90, &frame__39_86, 774, 774, 9, 52},
  {entry__39_91, NULL, 776, 776, 9, 16},
  {entry__39_107, NULL, 786, 786, 22, 41},
  {cont__39_108, &frame__39_107, 786, 786, 17, 41},
  {cont__39_109, &frame__39_107, 787, 787, 19, 35},
  {cont__39_111, &frame__39_107, 787, 787, 17, 66},
  {entry__39_105, NULL, 785, 785, 18, 30},
  {cont__39_106, &frame__39_105, 785, 787, 15, 66},
  {entry__39_102, NULL, 784, 784, 16, 28},
  {cont__39_104, &frame__39_102, 784, 787, 13, 67},
  {entry__39_100, NULL, 782, 782, 11, 26},
  {cont__39_101, &frame__39_100, 783, 787, 11, 68},
  {entry__39_117, NULL, 791, 791, 43, 63},
  {cont__39_118, &frame__39_117, 791, 791, 39, 64},
  {cont__39_119, &frame__39_117, 791, 791, 39, 64},
  {entry__39_121, NULL, 792, 792, 19, 44},
  {cont__39_122, &frame__39_121, 792, 792, 11, 47},
  {cont__39_123, &frame__39_121, 792, 792, 47, 47},
  {entry__39_126, NULL, 797, 797, 22, 34},
  {entry__39_128, NULL, 798, 798, 34, 58},
  {entry__39_130, NULL, 799, 799, 35, 60},
  {entry__39_132, NULL, 800, 800, 27, 44},
  {entry__39_134, NULL, 801, 801, 29, 48},
  {entry__39_136, NULL, 802, 802, 31, 52},
  {entry__39_138, NULL, 803, 803, 25, 40},
  {entry__39_140, NULL, 804, 804, 22, 34},
  {entry__39_142, NULL, 805, 805, 19, 28},
  {entry__39_144, NULL, 806, 806, 13, 24},
  {entry__39_149, NULL, 811, 811, 15, 55},
  {cont__39_151, &frame__39_149, 811, 811, 55, 55},
  {entry__39_152, NULL, 813, 813, 31, 31},
  {entry__39_147, NULL, 810, 810, 13, 29},
  {cont__39_148, &frame__39_147, 809, 813, 11, 32},
  {entry__39_155, NULL, 814, 814, 33, 47},
  {cont__39_156, &frame__39_155, 814, 814, 33, 47},
  {entry__39_165, NULL, 817, 817, 31, 42},
  {cont__39_166, &frame__39_165, 817, 817, 28, 49},
  {cont__39_167, &frame__39_165, 817, 817, 19, 49},
  {cont__39_168, &frame__39_165, 817, 817, 51, 68},
  {cont__39_169, &frame__39_165, 817, 817, 17, 68},
  {entry__39_159, NULL, 816, 816, 16, 32},
  {cont__39_162, &frame__39_159, 816, 816, 34, 50},
  {cont__39_163, &frame__39_159, 816, 816, 13, 50},
  {cont__39_164, &frame__39_159, 817, 817, 13, 68},
  {cont__39_170, &frame__39_159, 818, 818, 16, 33},
  {cont__39_172, &frame__39_159, 818, 818, 13, 40},
  {entry__39_158, NULL, 815, 818, 11, 40},
  {entry__39_96, NULL, 781, 781, 12, 19},
  {cont__39_97, &frame__39_96, 781, 781, 12, 29},
  {cont__39_98, &frame__39_96, 781, 781, 12, 29},
  {cont__39_99, &frame__39_96, 781, 787, 9, 69},
  {cont__39_113, &frame__39_96, 789, 789, 9, 27},
  {cont__39_114, &frame__39_96, 790, 790, 9, 43},
  {cont__39_115, &frame__39_96, 791, 791, 12, 34},
  {cont__39_116, &frame__39_96, 791, 791, 12, 64},
  {cont__39_120, &frame__39_96, 791, 792, 9, 47},
  {cont__39_124, &frame__39_96, 796, 796, 13, 25},
  {cont__39_125, &frame__39_96, 794, 806, 9, 25},
  {cont__39_145, &frame__39_96, 808, 808, 12, 31},
  {cont__39_146, &frame__39_96, 808, 813, 9, 33},
  {cont__39_153, &frame__39_96, 814, 814, 12, 28},
  {cont__39_154, &frame__39_96, 814, 814, 12, 47},
  {cont__39_157, &frame__39_96, 814, 818, 9, 41},
  {entry__39_95, NULL, 780, 818, 7, 42},
  {entry__39_80, NULL, 769, 769, 5, 12},
  {cont__39_81, &frame__39_80, 770, 770, 8, 21},
  {cont__39_84, &frame__39_80, 770, 770, 5, 36},
  {cont__39_85, &frame__39_80, 771, 776, 5, 17},
  {cont__39_93, &frame__39_80, 777, 777, 5, 6},
  {cont__39_94, &frame__39_80, 778, 818, 5, 43},
  {entry__39_180, NULL, 825, 825, 26, 53},
  {cont__39_181, &frame__39_180, 825, 825, 9, 65},
  {entry__39_178, NULL, 824, 824, 16, 31},
  {cont__39_179, &frame__39_178, 824, 825, 7, 65},
  {entry__39_174, NULL, 821, 821, 5, 23},
  {cont__39_175, &frame__39_174, 822, 822, 5, 30},
  {cont__39_176, &frame__39_174, 823, 823, 10, 22},
  {cont__39_177, &frame__39_174, 823, 825, 5, 66},
  {entry__39_195, NULL, 833, 833, 19, 35},
  {cont__39_196, &frame__39_195, 833, 833, 17, 41},
  {entry__39_194, NULL, 833, 833, 13, 41},
  {entry__39_189, NULL, 832, 832, 38, 56},
  {cont__39_190, &frame__39_189, 832, 832, 58, 66},
  {cont__39_191, &frame__39_189, 832, 832, 26, 67},
  {cont__39_192, &frame__39_189, 832, 832, 9, 76},
  {cont__39_193, &frame__39_189, 833, 833, 9, 41},
  {entry__39_188, NULL, 831, 833, 7, 41},
  {entry__39_184, NULL, 828, 828, 5, 12},
  {cont__39_185, &frame__39_184, 829, 829, 8, 21},
  {cont__39_186, &frame__39_184, 829, 829, 5, 36},
  {cont__39_187, &frame__39_184, 830, 833, 5, 42},
  {entry__39_210, NULL, 841, 841, 44, 62},
  {cont__39_211, &frame__39_210, 841, 841, 42, 62},
  {entry__39_209, NULL, 841, 841, 9, 62},
  {entry__39_216, NULL, 845, 845, 35, 51},
  {cont__39_217, &frame__39_216, 845, 845, 28, 60},
  {cont__39_218, &frame__39_216, 845, 845, 19, 60},
  {cont__39_219, &frame__39_216, 845, 845, 17, 70},
  {entry__39_215, NULL, 845, 845, 13, 70},
  {cont__39_220, &frame__39_215, 846, 846, 13, 23},
  {cont__39_221, &frame__39_215, 847, 847, 16, 44},
  {cont__39_222, &frame__39_215, 847, 847, 13, 44},
  {entry__39_214, NULL, 844, 847, 11, 44},
  {entry__39_213, NULL, 843, 847, 9, 45},
  {entry__39_203, NULL, 837, 837, 7, 14},
  {cont__39_204, &frame__39_203, 838, 838, 10, 23},
  {cont__39_205, &frame__39_203, 838, 838, 7, 29},
  {cont__39_206, &frame__39_203, 839, 839, 7, 42},
  {cont__39_207, &frame__39_203, 840, 840, 10, 30},
  {cont__39_208, &frame__39_203, 840, 841, 7, 62},
  {cont__39_212, &frame__39_203, 842, 847, 7, 46},
  {entry__39_198, NULL, 835, 835, 27, 45},
  {cont__39_199, &frame__39_198, 835, 835, 47, 55},
  {cont__39_200, &frame__39_198, 835, 835, 5, 56},
  {cont__39_201, &frame__39_198, 836, 836, 17, 39},
  {cont__39_202, &frame__39_198, 836, 847, 5, 47},
  {entry__39_228, NULL, 850, 850, 10, 31},
  {cont__39_229, &frame__39_228, 850, 850, 8, 40},
  {entry__39_231, NULL, 851, 851, 10, 35},
  {cont__39_232, &frame__39_231, 851, 851, 8, 48},
  {entry__39_234, NULL, 852, 852, 10, 37},
  {cont__39_235, &frame__39_234, 852, 852, 8, 52},
  {entry__39_237, NULL, 853, 853, 10, 37},
  {cont__39_238, &frame__39_237, 853, 853, 8, 52},
  {entry__39_225, NULL, 849, 849, 5, 19},
  {cont__39_227, &frame__39_225, 850, 850, 5, 40},
  {cont__39_230, &frame__39_225, 851, 851, 5, 48},
  {cont__39_233, &frame__39_225, 852, 852, 5, 52},
  {cont__39_236, &frame__39_225, 853, 853, 5, 52},
  {entry__39_243, NULL, 871, 871, 19, 38},
  {cont__39_244, &frame__39_243, 871, 871, 38, 38},
  {entry__39_245, NULL, 872, 872, 31, 62},
  {cont__39_246, &frame__39_245, 872, 872, 62, 62},
  {entry__39_247, NULL, 873, 873, 32, 64},
  {cont__39_248, &frame__39_247, 873, 873, 64, 64},
  {entry__39_249, NULL, 874, 874, 28, 56},
  {cont__39_250, &frame__39_249, 874, 874, 56, 56},
  {entry__39_251, NULL, 875, 875, 24, 48},
  {cont__39_252, &frame__39_251, 875, 875, 48, 48},
  {entry__39_253, NULL, 876, 876, 26, 52},
  {cont__39_254, &frame__39_253, 876, 876, 52, 52},
  {entry__39_255, NULL, 877, 877, 22, 44},
  {cont__39_256, &frame__39_255, 877, 877, 44, 44},
  {entry__39_257, NULL, 878, 878, 19, 38},
  {cont__39_258, &frame__39_257, 878, 878, 38, 38},
  {entry__39_259, NULL, 879, 879, 11, 20},
  {cont__39_260, &frame__39_259, 879, 879, 20, 20},
  {entry__39_267, NULL, 883, 883, 23, 40},
  {cont__39_268, &frame__39_267, 883, 883, 40, 40},
  {entry__39_269, NULL, 884, 884, 32, 58},
  {cont__39_270, &frame__39_269, 884, 884, 58, 58},
  {entry__39_271, NULL, 885, 885, 15, 35},
  {cont__39_272, &frame__39_271, 885, 885, 35, 35},
  {entry__39_265, NULL, 882, 882, 16, 35},
  {cont__39_266, &frame__39_265, 882, 885, 11, 35},
  {entry__39_263, NULL, 881, 881, 18, 33},
  {cont__39_264, &frame__39_263, 881, 885, 9, 36},
  {entry__39_241, NULL, 870, 870, 12, 24},
  {cont__39_242, &frame__39_241, 870, 879, 7, 20},
  {cont__39_261, &frame__39_241, 880, 880, 12, 24},
  {cont__39_262, &frame__39_241, 880, 885, 7, 37},
  {entry__39_240, NULL, 869, 885, 5, 38},
  {cont__39_273, &frame__39_240, },
  {cont__39_274, &frame__39_240, },
  {cont__39_275, &frame__39_240, },
  {cont__39_276, &frame__39_240, },
  {cont__39_277, &frame__39_240, },
  {cont__39_278, &frame__39_240, },
  {cont__39_279, &frame__39_240, },
  {cont__39_280, &frame__39_240, },
  {cont__39_281, &frame__39_240, },
  {cont__39_282, &frame__39_240, 887, 899, 5, 24},
  {cont__39_283, &frame__39_240, 902, 902, 32, 60},
  {cont__39_284, &frame__39_240, 904, 904, 32, 58},
  {cont__39_285, &frame__39_240, 905, 905, 32, 70},
  {cont__39_286, &frame__39_240, 906, 906, 32, 71},
  {cont__39_287, &frame__39_240, 907, 907, 32, 56},
  {cont__39_288, &frame__39_240, 908, 908, 32, 65},
  {cont__39_289, &frame__39_240, 909, 909, 32, 59},
  {cont__39_290, &frame__39_240, 910, 910, 32, 67},
  {cont__39_291, &frame__39_240, 911, 911, 32, 63},
  {cont__39_292, &frame__39_240, 912, 912, 32, 65},
  {cont__39_293, &frame__39_240, 913, 913, 32, 61},
  {cont__39_294, &frame__39_240, 914, 914, 32, 58},
  {cont__39_295, &frame__39_240, 915, 915, 32, 48},
  {cont__39_296, &frame__39_240, 917, 917, 32, 70},
  {cont__39_297, &frame__39_240, 901, 917, 12, 71},
  {cont__39_312, &frame__39_240, 901, 917, 5, 71},
  {entry__39_1_sim2c__extract_documentation, NULL, 721, 721, 42, 42},
  {cont__39_2, &frame__39_1_sim2c__extract_documentation, 721, 721, 3, 43},
  {cont__39_3, &frame__39_1_sim2c__extract_documentation, 722, 722, 3, 43},
  {cont__39_4, &frame__39_1_sim2c__extract_documentation, 724, 741, 3, 45},
  {cont__39_38, &frame__39_1_sim2c__extract_documentation, 743, 766, 3, 33},
  {cont__39_78, &frame__39_1_sim2c__extract_documentation, 768, 818, 3, 44},
  {cont__39_173, &frame__39_1_sim2c__extract_documentation, 820, 825, 3, 67},
  {cont__39_182, &frame__39_1_sim2c__extract_documentation, 827, 833, 3, 43},
  {cont__39_197, &frame__39_1_sim2c__extract_documentation, 834, 847, 3, 48},
  {cont__39_223, &frame__39_1_sim2c__extract_documentation, 848, 853, 3, 52},
  {cont__39_239, &frame__39_1_sim2c__extract_documentation, 855, 917, 3, 72}
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
  frame->cont = cont__45_1;
}
static void cont__45_1(void) {
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
  // 45: $$topics_paragraphs empty_table
  var._topics_paragraphs = get__empty_table();
  // 47: $$missing_documentation_count 0
  var._missing_documentation_count = number__0;
  // 64: ... sim2c::WHITESPACE, '=', sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__sim2c__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__sim2c__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__60_1;
}
static void cont__60_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 64: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__60_2;
}
static void cont__60_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 65: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__60_3;
}
static void cont__60_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 65: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__60_4;
}
static void cont__60_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 65: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__60_5;
}
static void cont__60_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 63: sequence
  // 64:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 65:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__60_6;
}
static void cont__60_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 59: $PARAMETER_COUNT_OR_MYSELF
  // 60:   alt
  // 61:     '*'
  // 62:     '?'
  // 63:     sequence
  // 64:       alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 65:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__60_7;
}
static void cont__60_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 67: $$path_prefix undefined
  var._path_prefix = get__undefined();
  // 157: types::object $symbol_info
  // 158:   .kind_of OTHER
  // 159:   .name_of undefined
  // 160:   .base_of undefined
  // 161:   .parameters_of undefined
  // 162:   .remark_lines_of undefined
  // 163:   .derived_types_of empty_key_order_set
  // 164:   .methods_of empty_key_order_table
  // 165:   .types_of empty_key_order_set
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
  // 386: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37_328;
  arguments->slots[1] = string__71_1;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__71_2;
}
static void cont__71_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 386: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__71_3;
}
static void cont__71_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 387: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__72_1;
  arguments->slots[1] = string__72_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__72_3;
}
static void cont__72_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 387: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__72_4;
}
static void cont__72_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 387: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__72_5;
}
static void cont__72_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 387: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__72_6;
}
static void cont__72_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 387: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__72_7;
}
static void cont__72_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXAMPLE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1_create_page(void) {
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
  // 72: ... :
  // 73:   HTML:
  // 74:     HEAD:
  // 75:       STYLE "
  // 76:         body {
  // 77:           background-color: white;
  // 78:           font-family: Times New Roman, Times;
  // 79:           font-size: 12pt;
  // 80:           color: #222;
  // 81:         }
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__23_2, 0);
  // 72: collect_output $page:
  // 73:   HTML:
  // 74:     HEAD:
  // 75:       STYLE "
  // 76:         body {
  // 77:           background-color: white;
  // 78:           font-family: Times New Roman, Times;
  // 79:           font-size: 12pt;
  // 80:           color: #222;
  // 81:         }
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void entry__23_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: HEAD:
  // 75:   STYLE "
  // 76:     body {
  // 77:       background-color: white;
  // 78:       font-family: Times New Roman, Times;
  // 79:       font-size: 12pt;
  // 80:       color: #222;
  // 81:     }
  // 82:     h1 {
  // 83:       font-family: Arial, Helvetica;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__23_4;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__23_6;
}
static void entry__23_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 75: STYLE "
  // 76:   body {
  // 77:     background-color: white;
  // 78:     font-family: Times New Roman, Times;
  // 79:     font-size: 12pt;
  // 80:     color: #222;
  // 81:   }
  // 82:   h1 {
  // 83:     font-family: Arial, Helvetica;
  // 84:     font-size: 20pt;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__23_5;
  result_count = frame->caller_result_count;
  myself = get__STYLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__23_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 154: BODY body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__BODY();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: ... :
  // 74:   HEAD:
  // 75:     STYLE "
  // 76:       body {
  // 77:         background-color: white;
  // 78:         font-family: Times New Roman, Times;
  // 79:         font-size: 12pt;
  // 80:         color: #222;
  // 81:       }
  // 82:       h1 {
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__23_3, 0);
  // 73: HTML:
  // 74:   HEAD:
  // 75:     STYLE "
  // 76:       body {
  // 77:         background-color: white;
  // 78:         font-family: Times New Roman, Times;
  // 79:         font-size: 12pt;
  // 80:         color: #222;
  // 81:       }
  // 82:       h1 {
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__23_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* page */, arguments->slots[0]);
  // 155: save filename page
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[2] /* page */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_1_extract_documentation_from_file(void) {
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
  // 168: ... "extracting documentation from @(filename)@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__25_2;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__25_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 168: ewrite "extracting documentation from @(filename)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 169: ... load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__25_6;
}
static void cont__25_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 169: $buf load(filename).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__25_7;
}
static void cont__25_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* buf */, arguments->slots[0]);
  // 170: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__25_8;
}
static void cont__25_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 170: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_9;
}
static void cont__25_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 170: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__25_10;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_12;
}
static void entry__25_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 170: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_11;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 171: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 171: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 171: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__25_15;
}
static void cont__25_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 171: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__25_16;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_18;
}
static void entry__25_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_17;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_19;
}
static void cont__25_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 172: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__25_20;
}
static void cont__25_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 172: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_21;
}
static void cont__25_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 172: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__25_22;
}
static void cont__25_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 172: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__25_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_25;
}
static void entry__25_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 172: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__25_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ... filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__25_26;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__25_27;
}
static void cont__25_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 175: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__25_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__25_29;
}
static void cont__25_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 174: %sim2c::module_name
  // 175:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 176:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__25_30;
}
static void cont__25_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 178: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 179: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 180: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 181: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 182: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 183: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 184: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 185: $$fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__25_31;
}
static void cont__25_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 186: update_each &fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = func__25_32;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__25_34;
}
static void entry__25_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 186: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__25_33;
}
static void cont__25_33(void) {
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
static void cont__25_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 187: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 188: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 189: ... : (-> done)
  // 190:   for_each fragments: (idx fragment)
  // 191:     case
  // 192:       source_of(fragment)(1)
  // 193:       '#':
  // 194:         pass
  // 195:       '<':
  // 196:         !first_idx idx+1
  // 197:         parse_meta_instruction $_tree fragment
  // 198:       :
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__25_35, 0);
  // 189: do: (-> done)
  // 190:   for_each fragments: (idx fragment)
  // 191:     case
  // 192:       source_of(fragment)(1)
  // 193:       '#':
  // 194:         pass
  // 195:       '<':
  // 196:         !first_idx idx+1
  // 197:         parse_meta_instruction $_tree fragment
  // 198:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__25_45;
}
static void entry__25_35(void) {
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
  // 190: ... : (idx fragment)
  // 191:   case
  // 192:     source_of(fragment)(1)
  // 193:     '#':
  // 194:       pass
  // 195:     '<':
  // 196:       !first_idx idx+1
  // 197:       parse_meta_instruction $_tree fragment
  // 198:     :
  // 199:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__25_36, 2);
  // 190: for_each fragments: (idx fragment)
  // 191:   case
  // 192:     source_of(fragment)(1)
  // 193:     '#':
  // 194:       pass
  // 195:     '<':
  // 196:       !first_idx idx+1
  // 197:       parse_meta_instruction $_tree fragment
  // 198:     :
  // 199:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__25_44;
}
static void entry__25_39(void) {
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
  // 196: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__25_40;
}
static void cont__25_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 197: parse_meta_instruction $_tree fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__25_41;
}
static void cont__25_41(void) {
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
static void entry__25_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_43(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_36(void) {
  allocate_initialized_frame_gc(4, 8);
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
  // 192: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__25_37;
}
static void cont__25_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 192: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__25_38;
}
static void cont__25_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 195: ... :
  // 196:   !first_idx idx+1
  // 197:   parse_meta_instruction $_tree fragment
  frame->slots[6] /* temp__3 */ = create_closure(entry__25_39, 0);
  // 198: :
  // 199:   done
  frame->slots[7] /* temp__4 */ = create_closure(entry__25_42, 0);
  // 191: case
  // 192:   source_of(fragment)(1)
  // 193:   '#':
  // 194:     pass
  // 195:   '<':
  // 196:     !first_idx idx+1
  // 197:     parse_meta_instruction $_tree fragment
  // 198:   :
  // 199:     done
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__35;
  arguments->slots[2] = func__25_43;
  arguments->slots[3] = character__60;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_44(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__25_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 200: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_46;
}
static void cont__25_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 200: range &fragments first_idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__25_47;
}
static void cont__25_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 201: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__25_48, 1);
  // 201: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__25_51;
}
static void entry__25_48(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 201: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__25_49;
}
static void cont__25_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 201: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__25_50;
}
static void cont__25_50(void) {
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
static void cont__25_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__25_52;
}
static void cont__25_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 202: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__25_53;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_56;
}
static void entry__25_53(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 202: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 202: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_54;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__25_55;
}
static void cont__25_55(void) {
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
static void cont__25_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 203: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 204: ... : (statement)
  // 205:   cond
  // 206:     -> statement.is_a_remark: pass
  // 207:     -> statement.is_c_code: pass
  // 208:     -> statement.is_an_assignment:
  // 209:       $destination output_arguments_of(statement)(1)
  // 210:       if destination.is_a_definition:
  // 211:         $identifier identifier_of(destination)
  // 212:         unless namespace_of(identifier).is_defined:
  // 213:           $source arguments_of(statement)(1)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__25_57, 1);
  // 204: for_each trees: (statement)
  // 205:   cond
  // 206:     -> statement.is_a_remark: pass
  // 207:     -> statement.is_c_code: pass
  // 208:     -> statement.is_an_assignment:
  // 209:       $destination output_arguments_of(statement)(1)
  // 210:       if destination.is_a_definition:
  // 211:         $identifier identifier_of(destination)
  // 212:         unless namespace_of(identifier).is_defined:
  // 213:           $source arguments_of(statement)(1)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__25_82;
}
static void entry__25_78(void) {
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
  // 215: !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 215: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__25_79;
}
static void cont__25_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 215: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__25_80;
}
static void cont__25_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 215: !local_method_names(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__25_81;
}
static void cont__25_81(void) {
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
static void entry__25_74(void) {
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
  // 213: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__25_75;
}
static void cont__25_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 213: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__25_76;
}
static void cont__25_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 214: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__25_77;
}
static void cont__25_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 214: ... :
  // 215:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_78, 0);
  // 214: if source.is_a_polymorphic_function_constant:
  // 215:   !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_70(void) {
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
  // 211: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__25_71;
}
static void cont__25_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 212: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__25_72;
}
static void cont__25_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 212: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_73;
}
static void cont__25_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 212: ... :
  // 213:   $source arguments_of(statement)(1)
  // 214:   if source.is_a_polymorphic_function_constant:
  // 215:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__25_74, 0);
  // 212: unless namespace_of(identifier).is_defined:
  // 213:   $source arguments_of(statement)(1)
  // 214:   if source.is_a_polymorphic_function_constant:
  // 215:     !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_66(void) {
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
  // 209: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__25_67;
}
static void cont__25_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 209: $destination output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__25_68;
}
static void cont__25_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 210: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__25_69;
}
static void cont__25_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 210: ... :
  // 211:   $identifier identifier_of(destination)
  // 212:   unless namespace_of(identifier).is_defined:
  // 213:     $source arguments_of(statement)(1)
  // 214:     if source.is_a_polymorphic_function_constant:
  // 215:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_70, 0);
  // 210: if destination.is_a_definition:
  // 211:   $identifier identifier_of(destination)
  // 212:   unless namespace_of(identifier).is_defined:
  // 213:     $source arguments_of(statement)(1)
  // 214:     if source.is_a_polymorphic_function_constant:
  // 215:       !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_60(void) {
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
static void entry__25_58(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 206: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__25_59;
}
static void cont__25_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 206: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__25_60;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_61(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__25_62;
}
static void cont__25_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 207: -> statement.is_c_code: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__25_63;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_64(void) {
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
  // 208: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__25_65;
}
static void cont__25_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 208: ... :
  // 209:   $destination output_arguments_of(statement)(1)
  // 210:   if destination.is_a_definition:
  // 211:     $identifier identifier_of(destination)
  // 212:     unless namespace_of(identifier).is_defined:
  // 213:       $source arguments_of(statement)(1)
  // 214:       if source.is_a_polymorphic_function_constant:
  // 215:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_66, 0);
  // 208: -> statement.is_an_assignment:
  // 209:   $destination output_arguments_of(statement)(1)
  // 210:   if destination.is_a_definition:
  // 211:     $identifier identifier_of(destination)
  // 212:     unless namespace_of(identifier).is_defined:
  // 213:       $source arguments_of(statement)(1)
  // 214:       if source.is_a_polymorphic_function_constant:
  // 215:         !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_57(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 206: -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__25_58, 0);
  // 207: -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_61, 0);
  // 208: -> statement.is_an_assignment:
  // 209:   $destination output_arguments_of(statement)(1)
  // 210:   if destination.is_a_definition:
  // 211:     $identifier identifier_of(destination)
  // 212:     unless namespace_of(identifier).is_defined:
  // 213:       $source arguments_of(statement)(1)
  // 214:       if source.is_a_polymorphic_function_constant:
  // 215:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__25_64, 0);
  // 205: cond
  // 206:   -> statement.is_a_remark: pass
  // 207:   -> statement.is_c_code: pass
  // 208:   -> statement.is_an_assignment:
  // 209:     $destination output_arguments_of(statement)(1)
  // 210:     if destination.is_a_definition:
  // 211:       $identifier identifier_of(destination)
  // 212:       unless namespace_of(identifier).is_defined:
  // 213:         $source arguments_of(statement)(1)
  // 214:         if source.is_a_polymorphic_function_constant:
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
static void cont__25_82(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 216: ... :
  // 217:   (
  // 218:     statement
  // 219:     -> break
  // 220:   )
  // 221:   cond
  // 222:     -> statement.is_a_remark:
  // 223:       $remark_lines remark_lines_of(statement)
  // 224:       if any_of(remark_lines has_prefix "Topic:"):
  // 225:         $paragraphs remark_lines.to_paragraphs
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__25_83, 1);
  // 216: for_each trees:
  // 217:   (
  // 218:     statement
  // 219:     -> break
  // 220:   )
  // 221:   cond
  // 222:     -> statement.is_a_remark:
  // 223:       $remark_lines remark_lines_of(statement)
  // 224:       if any_of(remark_lines has_prefix "Topic:"):
  // 225:         $paragraphs remark_lines.to_paragraphs
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__25_225;
}
static void entry__25_83(void) {
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
  // 222: -> statement.is_a_remark:
  // 223:   $remark_lines remark_lines_of(statement)
  // 224:   if any_of(remark_lines has_prefix "Topic:"):
  // 225:     $paragraphs remark_lines.to_paragraphs
  // 226:     do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:       if paragraph .has_prefix. "Topic:":
  // 228:         $topic trim(paragraph .behind. "Topic:")
  // 229:         !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:         done
  frame->slots[4] /* temp__1 */ = create_closure(entry__25_84, 0);
  // 231: -> statement.is_c_code:
  // 232:   $identifier identifier_of(statement)
  // 233:   if identifier.is_defined:
  // 234:     $namespace namespace_of(identifier)
  // 235:     if namespace.is_defined:
  // 236:       $name name_of(identifier)
  // 237:       case kind_of(statement)
  // 238:         "type":
  // 239:           if namespace.is_defined:
  // 240:             $base base_of(statement)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_103, 0);
  // 255: -> statement.is_an_assignment:
  // 256:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 257:   $$info symbol_info(.filename_of filename)
  // 258:   if
  // 259:     destination.is_a_definition:
  // 260:       $identifier identifier_of(destination)
  // 261:       $namespace namespace_of(identifier)
  // 262:       if namespace.is_defined:
  // 263:         $name name_of(identifier)
  // 264:         $iname ordered_name(namespace name)
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__25_134, 0);
  // 221: cond
  // 222:   -> statement.is_a_remark:
  // 223:     $remark_lines remark_lines_of(statement)
  // 224:     if any_of(remark_lines has_prefix "Topic:"):
  // 225:       $paragraphs remark_lines.to_paragraphs
  // 226:       do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:         if paragraph .has_prefix. "Topic:":
  // 228:           $topic trim(paragraph .behind. "Topic:")
  // 229:           !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:           done
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__25_224;
}
static void entry__25_214(void) {
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
  // 321: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__25_215;
}
static void cont__25_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 321: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_216;
}
static void cont__25_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 321: ... :
  // 322:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__25_217, 0);
  // 321: unless namespace_of(attr).is_defined:
  // 322:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_218;
}
static void entry__25_217(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 322: !attr.used_namespaces_of used_namespaces
  frame->slots[1] /* temp__1 */ = get__used_namespaces();
  // 322: !attr.used_namespaces_of
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
static void cont__25_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 323: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_219;
}
static void cont__25_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 323: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__25_220;
}
static void cont__25_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 324: !definition.kind_of INLINE_C_TYPE
  frame->slots[5] /* temp__1 */ = var._INLINE_C_TYPE;
  // 324: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 325: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 325: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__25_221;
}
static void cont__25_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 325: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__25_222;
}
static void cont__25_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 325: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 326: !definitions(iname) definition
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* definition */;
  // 326: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_223;
}
static void cont__25_223(void) {
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
static void entry__25_211(void) {
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
  // 319: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_212;
}
static void cont__25_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 320: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__25_213;
}
static void cont__25_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 320: ... :
  // 321:   unless namespace_of(attr).is_defined:
  // 322:     !attr.used_namespaces_of used_namespaces
  // 323:   $$definition default_value(definitions(iname) symbol_info)
  // 324:   !definition.kind_of INLINE_C_TYPE
  // 325:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 326:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__25_214, 0);
  // 320: unless local_method_names(attr_name):
  // 321:   unless namespace_of(attr).is_defined:
  // 322:     !attr.used_namespaces_of used_namespaces
  // 323:   $$definition default_value(definitions(iname) symbol_info)
  // 324:   !definition.kind_of INLINE_C_TYPE
  // 325:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 326:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_205(void) {
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
  // 312: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__25_206;
}
static void cont__25_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 315: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_207;
}
static void cont__25_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 315: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__25_208;
}
static void cont__25_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 314: $type
  // 315:   default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 317: !definitions(iname) type
  frame->slots[6] /* temp__1 */ = frame->slots[5] /* type */;
  // 317: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_209;
}
static void cont__25_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 318: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_210;
}
static void cont__25_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 318: ... :
  // 319:   $attr_name attr.to_string
  // 320:   unless local_method_names(attr_name):
  // 321:     unless namespace_of(attr).is_defined:
  // 322:       !attr.used_namespaces_of used_namespaces
  // 323:     $$definition default_value(definitions(iname) symbol_info)
  // 324:     !definition.kind_of INLINE_C_TYPE
  // 325:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 326:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__25_211, 0);
  // 318: if attr.is_defined:
  // 319:   $attr_name attr.to_string
  // 320:   unless local_method_names(attr_name):
  // 321:     unless namespace_of(attr).is_defined:
  // 322:       !attr.used_namespaces_of used_namespaces
  // 323:     $$definition default_value(definitions(iname) symbol_info)
  // 324:     !definition.kind_of INLINE_C_TYPE
  // 325:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 326:     !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_144(void) {
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
  // 263: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__25_145;
}
static void cont__25_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* name */, arguments->slots[0]);
  // 264: $iname ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[7] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__25_146;
}
static void cont__25_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* iname */, arguments->slots[0]);
  // 266: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_147;
}
static void cont__25_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 267: ... variable_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__25_148;
}
static void cont__25_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__2 */ = arguments->slots[0];
  // 268: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_149;
}
static void cont__25_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 265: !info
  // 266:   .name_of identifier.to_string
  // 267:   .variable_kind_of variable_kind_of(destination)
  // 268:   .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[10] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, frame->slots[11] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[12] /* temp__3 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 269: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__25_150;
}
static void cont__25_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 269: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__25_151;
}
static void cont__25_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* source */, arguments->slots[0]);
  // 271: -> source.is_a_polymorphic_function_constant:
  // 272:   !polymorphic_functions(name namespace) true
  // 273:   !definitions(iname)
  // 274:     info
  // 275:       .kind_of
  // 276:         if
  // 277:           source.is_a_setter
  // 278:           -> POLYMORPHIC_ATTRIBUTE
  // 279:           -> POLYMORPHIC_FUNCTION
  // 280:   break
  frame->slots[10] /* temp__1 */ = create_closure(entry__25_152, 0);
  // 281: -> source.is_a_body:
  // 282:   !info
  // 283:     .base_of "types::function"
  // 284:     .kind_of FUNCTION
  // 285:     .parameters_of parameters_of(source)
  // 286:     .remark_lines_of
  // 287:       if
  // 288:         remark_lines_of(statement).is_empty
  // 289:         -> remark_lines_of(source)
  // 290:         -> remark_lines_of(statement)
  frame->slots[11] /* temp__2 */ = create_closure(entry__25_161, 0);
  // 291: -> source.is_a_c_body:
  // 292:   !info.kind_of INLINE_C_FUNCTION
  frame->slots[12] /* temp__3 */ = create_closure(entry__25_173, 0);
  // 293: -> source.is_an_identifier:
  // 294:   if namespace_of(source).is_defined:
  // 295:     !info.base_of source.to_string
  frame->slots[13] /* temp__4 */ = create_closure(entry__25_176, 0);
  // 296: -> source.is_a_unique_item_constant:
  // 297:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 298:   break
  frame->slots[14] /* temp__5 */ = create_closure(entry__25_183, 0);
  // 299: -> source.is_a_constant:
  // 300:   !info.kind_of CONSTANT
  frame->slots[15] /* temp__6 */ = create_closure(entry__25_187, 0);
  // 270: cond
  // 271:   -> source.is_a_polymorphic_function_constant:
  // 272:     !polymorphic_functions(name namespace) true
  // 273:     !definitions(iname)
  // 274:       info
  // 275:         .kind_of
  // 276:           if
  // 277:             source.is_a_setter
  // 278:             -> POLYMORPHIC_ATTRIBUTE
  // 279:             -> POLYMORPHIC_FUNCTION
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
  frame->cont = cont__25_190;
}
static void entry__25_189(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 300: !info.kind_of CONSTANT
  frame->slots[1] /* temp__1 */ = var._CONSTANT;
  // 300: !info.kind_of
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
static void entry__25_185(void) {
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
  // 297: !definitions(iname) info(.kind_of UNIQUE_ITEM)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._UNIQUE_ITEM);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 297: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_186;
}
static void cont__25_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 298: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_181(void) {
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
  // 295: !info.base_of source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_182;
}
static void cont__25_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 295: !info.base_of
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
static void entry__25_178(void) {
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
  // 294: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__25_179;
}
static void cont__25_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 294: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_180;
}
static void cont__25_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 294: ... :
  // 295:   !info.base_of source.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__25_181, 0);
  // 294: if namespace_of(source).is_defined:
  // 295:   !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_175(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: !info.kind_of INLINE_C_FUNCTION
  frame->slots[1] /* temp__1 */ = var._INLINE_C_FUNCTION;
  // 292: !info.kind_of
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
static void entry__25_163(void) {
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
  // 285: ... parameters_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__25_164;
}
static void cont__25_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 288: remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_165;
}
static void cont__25_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 288: remark_lines_of(statement).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__25_166;
}
static void cont__25_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 289: -> remark_lines_of(source)
  frame->slots[7] /* temp__5 */ = create_closure(entry__25_167, 0);
  // 290: -> remark_lines_of(statement)
  frame->slots[8] /* temp__6 */ = create_closure(entry__25_169, 0);
  // 287: if
  // 288:   remark_lines_of(statement).is_empty
  // 289:   -> remark_lines_of(source)
  // 290:   -> remark_lines_of(statement)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = frame->slots[8] /* temp__6 */;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_171;
}
static void entry__25_167(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: ... remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_168;
}
static void cont__25_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 289: -> remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_169(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 290: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_170;
}
static void cont__25_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 290: -> remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 282: !info
  // 283:   .base_of "types::function"
  // 284:   .kind_of FUNCTION
  // 285:   .parameters_of parameters_of(source)
  // 286:   .remark_lines_of
  // 287:     if
  // 288:       remark_lines_of(statement).is_empty
  // 289:       -> remark_lines_of(source)
  // 290:       -> remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, string__25_172);
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
static void entry__25_154(void) {
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
  // 272: !polymorphic_functions(name namespace) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 272: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__25_155;
}
static void cont__25_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 277: source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__25_156;
}
static void cont__25_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 276: if
  // 277:   source.is_a_setter
  // 278:   -> POLYMORPHIC_ATTRIBUTE
  // 279:   -> POLYMORPHIC_FUNCTION
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = func__25_157;
  arguments->slots[2] = func__25_158;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_159;
}
static void entry__25_157(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: -> POLYMORPHIC_ATTRIBUTE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_ATTRIBUTE;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_158(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 279: -> POLYMORPHIC_FUNCTION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 273: !definitions(iname)
  // 274:   info
  // 275:     .kind_of
  // 276:       if
  // 277:         source.is_a_setter
  // 278:         -> POLYMORPHIC_ATTRIBUTE
  // 279:         -> POLYMORPHIC_FUNCTION
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[6] /* temp__1 */);
    frame->slots[8] /* temp__3 */ = temp;

  }
  // 273: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_160;
}
static void cont__25_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 280: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_152(void) {
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
  // 271: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__25_153;
}
static void cont__25_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 271: ... :
  // 272:   !polymorphic_functions(name namespace) true
  // 273:   !definitions(iname)
  // 274:     info
  // 275:       .kind_of
  // 276:         if
  // 277:           source.is_a_setter
  // 278:           -> POLYMORPHIC_ATTRIBUTE
  // 279:           -> POLYMORPHIC_FUNCTION
  // 280:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__25_154, 0);
  // 271: -> source.is_a_polymorphic_function_constant:
  // 272:   !polymorphic_functions(name namespace) true
  // 273:   !definitions(iname)
  // 274:     info
  // 275:       .kind_of
  // 276:         if
  // 277:           source.is_a_setter
  // 278:           -> POLYMORPHIC_ATTRIBUTE
  // 279:           -> POLYMORPHIC_FUNCTION
  // 280:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_161(void) {
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
  // 281: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__25_162;
}
static void cont__25_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 281: ... :
  // 282:   !info
  // 283:     .base_of "types::function"
  // 284:     .kind_of FUNCTION
  // 285:     .parameters_of parameters_of(source)
  // 286:     .remark_lines_of
  // 287:       if
  // 288:         remark_lines_of(statement).is_empty
  // 289:         -> remark_lines_of(source)
  // 290:         -> remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_163, 0);
  // 281: -> source.is_a_body:
  // 282:   !info
  // 283:     .base_of "types::function"
  // 284:     .kind_of FUNCTION
  // 285:     .parameters_of parameters_of(source)
  // 286:     .remark_lines_of
  // 287:       if
  // 288:         remark_lines_of(statement).is_empty
  // 289:         -> remark_lines_of(source)
  // 290:         -> remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_173(void) {
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
  // 291: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__25_174;
}
static void cont__25_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 291: ... :
  // 292:   !info.kind_of INLINE_C_FUNCTION
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_175, 0);
  // 291: -> source.is_a_c_body:
  // 292:   !info.kind_of INLINE_C_FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_176(void) {
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
  // 293: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__25_177;
}
static void cont__25_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   if namespace_of(source).is_defined:
  // 295:     !info.base_of source.to_string
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_178, 0);
  // 293: -> source.is_an_identifier:
  // 294:   if namespace_of(source).is_defined:
  // 295:     !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_183(void) {
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
  // 296: ... source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__25_184;
}
static void cont__25_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 296: ... :
  // 297:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 298:   break
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_185, 0);
  // 296: -> source.is_a_unique_item_constant:
  // 297:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 298:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_187(void) {
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
  // 299: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__25_188;
}
static void cont__25_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 299: ... :
  // 300:   !info.kind_of CONSTANT
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_189, 0);
  // 299: -> source.is_a_constant:
  // 300:   !info.kind_of CONSTANT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_190(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 302: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__25_191;
}
static void cont__25_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 303: ... :
  // 304:   $previous_definition definitions(iname)
  // 305:   if previous_definition.is_defined:
  // 306:     if kind_of(previous_definition) == INLINE_C_TYPE:
  // 307:       !info.types_of types_of(previous_definition)
  // 308:       !info.derived_types_of derived_types_of(previous_definition)
  // 309:       !info.methods_of methods_of(previous_definition)
  // 310:   !definitions(iname) info
  frame->slots[11] /* temp__2 */ = create_closure(entry__25_192, 0);
  // 311: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__25_204;
}
static void entry__25_192(void) {
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
  // 304: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_193;
}
static void cont__25_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 305: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_194;
}
static void cont__25_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 307:     !info.types_of types_of(previous_definition)
  // 308:     !info.derived_types_of derived_types_of(previous_definition)
  // 309:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_195, 0);
  // 305: if previous_definition.is_defined:
  // 306:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 307:     !info.types_of types_of(previous_definition)
  // 308:     !info.derived_types_of derived_types_of(previous_definition)
  // 309:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_202;
}
static void entry__25_198(void) {
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
  // 307: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__25_199;
}
static void cont__25_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 307: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 308: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__25_200;
}
static void cont__25_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 308: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 309: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__25_201;
}
static void cont__25_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 309: !info.methods_of
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
static void entry__25_195(void) {
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
  // 306: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__25_196;
}
static void cont__25_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 306: ... kind_of(previous_definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_197;
}
static void cont__25_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 306: ... :
  // 307:   !info.types_of types_of(previous_definition)
  // 308:   !info.derived_types_of derived_types_of(previous_definition)
  // 309:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__25_198, 0);
  // 306: if kind_of(previous_definition) == INLINE_C_TYPE:
  // 307:   !info.types_of types_of(previous_definition)
  // 308:   !info.derived_types_of derived_types_of(previous_definition)
  // 309:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_202(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 310: !definitions(iname) info
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* info */;
  // 310: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_203;
}
static void cont__25_203(void) {
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
static void cont__25_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 311: ... :
  // 312:   $$attr attribute_of(destination)
  // 313:   
  // 314:   $type
  // 315:     default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  // 316:   
  // 317:   !definitions(iname) type
  // 318:   if attr.is_defined:
  // 319:     $attr_name attr.to_string
  // 320:     unless local_method_names(attr_name):
  // ...
  frame->slots[13] /* temp__4 */ = create_closure(entry__25_205, 0);
  // 301: case
  // 302:   attribute_kind_of(destination)
  // 303:   NONE:
  // 304:     $previous_definition definitions(iname)
  // 305:     if previous_definition.is_defined:
  // 306:       if kind_of(previous_definition) == INLINE_C_TYPE:
  // 307:         !info.types_of types_of(previous_definition)
  // 308:         !info.derived_types_of derived_types_of(previous_definition)
  // 309:         !info.methods_of methods_of(previous_definition)
  // 310:     !definitions(iname) info
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
static void entry__25_140(void) {
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
  // 260: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__25_141;
}
static void cont__25_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* identifier */, arguments->slots[0]);
  // 261: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__25_142;
}
static void cont__25_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* namespace */, arguments->slots[0]);
  // 262: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_143;
}
static void cont__25_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 262: ... :
  // 263:   $name name_of(identifier)
  // 264:   $iname ordered_name(namespace name)
  // 265:   !info
  // 266:     .name_of identifier.to_string
  // 267:     .variable_kind_of variable_kind_of(destination)
  // 268:     .remark_lines_of remark_lines_of(statement)
  // 269:   $source arguments_of(statement)(1)
  // 270:   cond
  // 271:     -> source.is_a_polymorphic_function_constant:
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__25_144, 0);
  // 262: if namespace.is_defined:
  // 263:   $name name_of(identifier)
  // 264:   $iname ordered_name(namespace name)
  // 265:   !info
  // 266:     .name_of identifier.to_string
  // 267:     .variable_kind_of variable_kind_of(destination)
  // 268:     .remark_lines_of remark_lines_of(statement)
  // 269:   $source arguments_of(statement)(1)
  // 270:   cond
  // 271:     -> source.is_a_polymorphic_function_constant:
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
static void entry__25_136(void) {
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
  // 256: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__25_137;
}
static void cont__25_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 256: ... output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__25_138;
}
static void cont__25_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 256: $destination output_arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 257: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 259: destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__25_139;
}
static void cont__25_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 259: ... :
  // 260:   $identifier identifier_of(destination)
  // 261:   $namespace namespace_of(identifier)
  // 262:   if namespace.is_defined:
  // 263:     $name name_of(identifier)
  // 264:     $iname ordered_name(namespace name)
  // 265:     !info
  // 266:       .name_of identifier.to_string
  // 267:       .variable_kind_of variable_kind_of(destination)
  // 268:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__25_140, 0);
  // 258: if
  // 259:   destination.is_a_definition:
  // 260:     $identifier identifier_of(destination)
  // 261:     $namespace namespace_of(identifier)
  // 262:     if namespace.is_defined:
  // 263:       $name name_of(identifier)
  // 264:       $iname ordered_name(namespace name)
  // 265:       !info
  // 266:         .name_of identifier.to_string
  // 267:         .variable_kind_of variable_kind_of(destination)
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
static void entry__25_116(void) {
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
  // 240: $base base_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__25_117;
}
static void cont__25_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* base */, arguments->slots[0]);
  // 244: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_118;
}
static void cont__25_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 245: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_119;
}
static void cont__25_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 245: ... -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__25_120, 0);
  // 245: ... if(base.is_defined (-> base.to_string) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = func__25_122;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__25_123;
}
static void entry__25_120(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* base */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: ... base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_121;
}
static void cont__25_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 245: ... -> base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_122(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 245: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 246: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_124;
}
static void cont__25_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 241: !definitions(ordered_name(namespace name))
  // 242:   symbol_info
  // 243:     .kind_of INLINE_C_TYPE
  // 244:     .name_of identifier.to_string
  // 245:     .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 246:     .remark_lines_of remark_lines_of(statement)
  // 247:     .filename_of filename
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
  // 241: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[2] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__25_125;
}
static void cont__25_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 241: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[11] /* temp__6 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_126;
}
static void cont__25_126(void) {
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
static void entry__25_114(void) {
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
  // 239: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_115;
}
static void cont__25_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 239: ... :
  // 240:   $base base_of(statement)
  // 241:   !definitions(ordered_name(namespace name))
  // 242:     symbol_info
  // 243:       .kind_of INLINE_C_TYPE
  // 244:       .name_of identifier.to_string
  // 245:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 246:       .remark_lines_of remark_lines_of(statement)
  // 247:       .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__25_116, 0);
  // 239: if namespace.is_defined:
  // 240:   $base base_of(statement)
  // 241:   !definitions(ordered_name(namespace name))
  // 242:     symbol_info
  // 243:       .kind_of INLINE_C_TYPE
  // 244:       .name_of identifier.to_string
  // 245:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 246:       .remark_lines_of remark_lines_of(statement)
  // 247:       .filename_of filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_127(void) {
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
  // 252: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__25_128;
}
static void cont__25_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 253: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_129;
}
static void cont__25_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 249: !definitions(ordered_name(namespace name))
  // 250:   symbol_info
  // 251:     .kind_of INLINE_C_OBJECT
  // 252:     .name_of identifier.to_string
  // 253:     .remark_lines_of remark_lines_of(statement)
  // 254:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_OBJECT);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[4] /* filename */);
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 249: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__25_130;
}
static void cont__25_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 249: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_131;
}
static void cont__25_131(void) {
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
static void entry__25_111(void) {
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
  // 236: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__25_112;
}
static void cont__25_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 237: ... kind_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__25_113;
}
static void cont__25_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 238: ... :
  // 239:   if namespace.is_defined:
  // 240:     $base base_of(statement)
  // 241:     !definitions(ordered_name(namespace name))
  // 242:       symbol_info
  // 243:         .kind_of INLINE_C_TYPE
  // 244:         .name_of identifier.to_string
  // 245:         .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 246:         .remark_lines_of remark_lines_of(statement)
  // 247:         .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__25_114, 0);
  // 248: ... :
  // 249:   !definitions(ordered_name(namespace name))
  // 250:     symbol_info
  // 251:       .kind_of INLINE_C_OBJECT
  // 252:       .name_of identifier.to_string
  // 253:       .remark_lines_of remark_lines_of(statement)
  // 254:       .filename_of filename
  frame->slots[7] /* temp__3 */ = create_closure(entry__25_127, 0);
  // 237: case kind_of(statement)
  // 238:   "type":
  // 239:     if namespace.is_defined:
  // 240:       $base base_of(statement)
  // 241:       !definitions(ordered_name(namespace name))
  // 242:         symbol_info
  // 243:           .kind_of INLINE_C_TYPE
  // 244:           .name_of identifier.to_string
  // 245:           .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 246:           .remark_lines_of remark_lines_of(statement)
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__25_132;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = string__25_133;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_108(void) {
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
  // 234: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__25_109;
}
static void cont__25_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 235: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_110;
}
static void cont__25_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 235: ... :
  // 236:   $name name_of(identifier)
  // 237:   case kind_of(statement)
  // 238:     "type":
  // 239:       if namespace.is_defined:
  // 240:         $base base_of(statement)
  // 241:         !definitions(ordered_name(namespace name))
  // 242:           symbol_info
  // 243:             .kind_of INLINE_C_TYPE
  // 244:             .name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_111, 0);
  // 235: if namespace.is_defined:
  // 236:   $name name_of(identifier)
  // 237:   case kind_of(statement)
  // 238:     "type":
  // 239:       if namespace.is_defined:
  // 240:         $base base_of(statement)
  // 241:         !definitions(ordered_name(namespace name))
  // 242:           symbol_info
  // 243:             .kind_of INLINE_C_TYPE
  // 244:             .name_of identifier.to_string
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
static void entry__25_105(void) {
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
  // 232: $identifier identifier_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__25_106;
}
static void cont__25_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 233: ... identifier.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_107;
}
static void cont__25_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 233: ... :
  // 234:   $namespace namespace_of(identifier)
  // 235:   if namespace.is_defined:
  // 236:     $name name_of(identifier)
  // 237:     case kind_of(statement)
  // 238:       "type":
  // 239:         if namespace.is_defined:
  // 240:           $base base_of(statement)
  // 241:           !definitions(ordered_name(namespace name))
  // 242:             symbol_info
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_108, 0);
  // 233: if identifier.is_defined:
  // 234:   $namespace namespace_of(identifier)
  // 235:   if namespace.is_defined:
  // 236:     $name name_of(identifier)
  // 237:     case kind_of(statement)
  // 238:       "type":
  // 239:         if namespace.is_defined:
  // 240:           $base base_of(statement)
  // 241:           !definitions(ordered_name(namespace name))
  // 242:             symbol_info
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
static void entry__25_92(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // done: 0
  // paragraphs: 1
  frame->slots[0] /* done */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[1]; /* paragraphs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 226: ... : (idx paragraph)
  // 227:   if paragraph .has_prefix. "Topic:":
  // 228:     $topic trim(paragraph .behind. "Topic:")
  // 229:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:     done
  frame->slots[2] /* temp__1 */ = create_closure(entry__25_93, 2);
  // 226: ... for_each paragraphs: (idx paragraph)
  // 227:   if paragraph .has_prefix. "Topic:":
  // 228:     $topic trim(paragraph .behind. "Topic:")
  // 229:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:     done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraphs */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__25_102;
}
static void entry__25_95(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // paragraph: 0
  // paragraphs: 1
  // idx: 2
  // done: 3
  // topic: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[2]; /* paragraphs */
  frame->slots[2] = myself->closure.frame->slots[0]; /* idx */
  frame->slots[3] = myself->closure.frame->slots[3]; /* done */
  frame->slots[4] /* topic */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 228: ... paragraph .behind. "Topic:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraph */;
  arguments->slots[1] = string__25_88;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__25_96;
}
static void cont__25_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 228: $topic trim(paragraph .behind. "Topic:")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__25_97;
}
static void cont__25_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* topic */, arguments->slots[0]);
  // 229: ... idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__25_98;
}
static void cont__25_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 229: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__25_99;
}
static void cont__25_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 229: !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraphs */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__25_100;
}
static void cont__25_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 229: !topics_paragraphs(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* topic */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = var._topics_paragraphs;
  func = myself->type;
  frame->cont = cont__25_101;
}
static void cont__25_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._topics_paragraphs = arguments->slots[0];
  // 230: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_93(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // idx: 0
  // paragraph: 1
  // paragraphs: 2
  // done: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* paragraphs */
  frame->slots[3] = myself->closure.frame->slots[0]; /* done */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 227: ... paragraph .has_prefix. "Topic:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraph */;
  arguments->slots[1] = string__25_88;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__25_94;
}
static void cont__25_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 227: ... :
  // 228:   $topic trim(paragraph .behind. "Topic:")
  // 229:   !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:   done
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_95, 0);
  // 227: if paragraph .has_prefix. "Topic:":
  // 228:   $topic trim(paragraph .behind. "Topic:")
  // 229:   !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:   done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_102(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__25_90(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  // paragraphs: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* remark_lines */
  frame->slots[1] /* paragraphs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 225: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__25_91;
}
static void cont__25_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* paragraphs */, arguments->slots[0]);
  // 226: ... : (-> done) for_each paragraphs: (idx paragraph)
  // 227:   if paragraph .has_prefix. "Topic:":
  // 228:     $topic trim(paragraph .behind. "Topic:")
  // 229:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:     done
  frame->slots[2] /* temp__1 */ = create_closure(entry__25_92, 0);
  // 226: do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:   if paragraph .has_prefix. "Topic:":
  // 228:     $topic trim(paragraph .behind. "Topic:")
  // 229:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:     done
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_86(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // statement: 0
  // remark_lines: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] /* remark_lines */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: $remark_lines remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__25_87;
}
static void cont__25_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* remark_lines */, arguments->slots[0]);
  // 224: ... any_of(remark_lines has_prefix "Topic:")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = get__has_prefix();
  arguments->slots[2] = string__25_88;
  result_count = 1;
  myself = get__any_of();
  func = myself->type;
  frame->cont = cont__25_89;
}
static void cont__25_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 224: ... :
  // 225:   $paragraphs remark_lines.to_paragraphs
  // 226:   do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:     if paragraph .has_prefix. "Topic:":
  // 228:       $topic trim(paragraph .behind. "Topic:")
  // 229:       !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:       done
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_90, 0);
  // 224: if any_of(remark_lines has_prefix "Topic:"):
  // 225:   $paragraphs remark_lines.to_paragraphs
  // 226:   do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:     if paragraph .has_prefix. "Topic:":
  // 228:       $topic trim(paragraph .behind. "Topic:")
  // 229:       !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_84(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 222: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__25_85;
}
static void cont__25_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 222: ... :
  // 223:   $remark_lines remark_lines_of(statement)
  // 224:   if any_of(remark_lines has_prefix "Topic:"):
  // 225:     $paragraphs remark_lines.to_paragraphs
  // 226:     do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:       if paragraph .has_prefix. "Topic:":
  // 228:         $topic trim(paragraph .behind. "Topic:")
  // 229:         !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:         done
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_86, 0);
  // 222: -> statement.is_a_remark:
  // 223:   $remark_lines remark_lines_of(statement)
  // 224:   if any_of(remark_lines has_prefix "Topic:"):
  // 225:     $paragraphs remark_lines.to_paragraphs
  // 226:     do: (-> done) for_each paragraphs: (idx paragraph)
  // 227:       if paragraph .has_prefix. "Topic:":
  // 228:         $topic trim(paragraph .behind. "Topic:")
  // 229:         !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 230:         done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_103(void) {
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
  // 231: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__25_104;
}
static void cont__25_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 231: ... :
  // 232:   $identifier identifier_of(statement)
  // 233:   if identifier.is_defined:
  // 234:     $namespace namespace_of(identifier)
  // 235:     if namespace.is_defined:
  // 236:       $name name_of(identifier)
  // 237:       case kind_of(statement)
  // 238:         "type":
  // 239:           if namespace.is_defined:
  // 240:             $base base_of(statement)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_105, 0);
  // 231: -> statement.is_c_code:
  // 232:   $identifier identifier_of(statement)
  // 233:   if identifier.is_defined:
  // 234:     $namespace namespace_of(identifier)
  // 235:     if namespace.is_defined:
  // 236:       $name name_of(identifier)
  // 237:       case kind_of(statement)
  // 238:         "type":
  // 239:           if namespace.is_defined:
  // 240:             $base base_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__25_134(void) {
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
  // 255: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__25_135;
}
static void cont__25_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 255: ... :
  // 256:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 257:   $$info symbol_info(.filename_of filename)
  // 258:   if
  // 259:     destination.is_a_definition:
  // 260:       $identifier identifier_of(destination)
  // 261:       $namespace namespace_of(identifier)
  // 262:       if namespace.is_defined:
  // 263:         $name name_of(identifier)
  // 264:         $iname ordered_name(namespace name)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_136, 0);
  // 255: -> statement.is_an_assignment:
  // 256:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 257:   $$info symbol_info(.filename_of filename)
  // 258:   if
  // 259:     destination.is_a_definition:
  // 260:       $identifier identifier_of(destination)
  // 261:       $namespace namespace_of(identifier)
  // 262:       if namespace.is_defined:
  // 263:         $name name_of(identifier)
  // 264:         $iname ordered_name(namespace name)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__25_224(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__25_225(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__26_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... extract_documentation_from_file name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 332: ... extract_documentation_from_directory name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_6(void) {
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
  // 332: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__26_7;
}
static void cont__26_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 332: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__26_8, 0);
  // 332: -> entry.is_a_directory: extract_documentation_from_directory name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 333: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__25_26;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__26_10;
}
static void cont__26_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 333: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__26_11, 0);
  // 333: -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__26_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 330: $name fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 332: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__26_6, 0);
  // 333: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__26_9, 0);
  // 331: cond
  // 332:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 333:   -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_1_extract_documentation_from_directory(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 329: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__26_2;
}
static void cont__26_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 329: ... directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__26_3;
}
static void cont__26_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 329: for_each directory(--SORT path): (entry)
  // 330:   $name fullname_of(entry)
  // 331:   cond
  // 332:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 333:     -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__26_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__27_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 337: ... attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__27_6;
}
static void cont__27_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 337: ... -> attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_7(void) {
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
  // 338: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 339: ... used_namespaces_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = var._used_namespaces_of;
  func = myself->type;
  frame->cont = cont__27_8;
}
static void cont__27_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 339: ... : (namespace)
  // 340:   if polymorphic_functions(name namespace):
  // 341:     if resolved_namespace.is_defined:
  // 342:       Error "
  // 343:         The attribute "@(name)" cannot be uniquely resolved!
  // 344:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_9, 1);
  // 339: for_each used_namespaces_of(attr): (namespace)
  // 340:   if polymorphic_functions(name namespace):
  // 341:     if resolved_namespace.is_defined:
  // 342:       Error "
  // 343:         The attribute "@(name)" cannot be uniquely resolved!
  // 344:     !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__27_18;
}
static void entry__27_11(void) {
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
  // 341: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_12;
}
static void cont__27_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   Error "
  // 343:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_13, 0);
  // 341: if resolved_namespace.is_defined:
  // 342:   Error "
  // 343:     The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__27_17;
}
static void entry__27_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: ... "
  // 343:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__27_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__27_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__27_16;
}
static void cont__27_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 342: Error "
  // 343:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 344: !resolved_namespace namespace
  ((CELL *)frame->slots[0])->contents /* resolved_namespace */ = frame->slots[2] /* namespace */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_9(void) {
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
  // 340: ... polymorphic_functions(name namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__27_10;
}
static void cont__27_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   if resolved_namespace.is_defined:
  // 342:     Error "
  // 343:       The attribute "@(name)" cannot be uniquely resolved!
  // 344:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_11, 0);
  // 340: if polymorphic_functions(name namespace):
  // 341:   if resolved_namespace.is_defined:
  // 342:     Error "
  // 343:       The attribute "@(name)" cannot be uniquely resolved!
  // 344:   !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 345: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_19;
}
static void cont__27_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 345: ... :
  // 346:   Error "
  // 347:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_20, 0);
  // 345: unless resolved_namespace.is_defined:
  // 346:   Error "
  // 347:     The attribute "@(name)" cannot be resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__27_23;
}
static void entry__27_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 346: ... "
  // 347:   The attribute "@(name)" cannot be resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__27_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__27_21;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__27_22;
}
static void cont__27_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 346: Error "
  // 347:   The attribute "@(name)" cannot be resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__27_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 348: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__27_24;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__27_25;
}
static void cont__27_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 348: -> string(resolved_namespace "::" name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_resolved_name(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // attr: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 336: $name name_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 337: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 337: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 337: ... -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__27_5, 0);
  // 337: ... :
  // 338:   $$resolved_namespace undefined
  // 339:   for_each used_namespaces_of(attr): (namespace)
  // 340:     if polymorphic_functions(name namespace):
  // 341:       if resolved_namespace.is_defined:
  // 342:         Error "
  // 343:           The attribute "@(name)" cannot be uniquely resolved!
  // 344:       !resolved_namespace namespace
  // 345:   unless resolved_namespace.is_defined:
  // 346:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__27_7, 0);
  // 337: if namespace_of(attr).is_defined (-> attr.to_string):
  // 338:   $$resolved_namespace undefined
  // 339:   for_each used_namespaces_of(attr): (namespace)
  // 340:     if polymorphic_functions(name namespace):
  // 341:       if resolved_namespace.is_defined:
  // 342:         Error "
  // 343:           The attribute "@(name)" cannot be uniquely resolved!
  // 344:       !resolved_namespace namespace
  // 345:   unless resolved_namespace.is_defined:
  // 346:     Error "
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
static void entry__28_7(void) {
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
  // 354: !definition.derived_types_of(name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 354: ... definition.derived_types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__28_8;
}
static void cont__28_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 354: !definition.derived_types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 354: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 355: ... kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__28_10;
}
static void cont__28_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 355: ... kind_of(definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 355: ... :
  // 356:   !definition.kind_of INLINE_C_TYPE
  // 357:   $base_of_base base_of(definition)
  // 358:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_12, 0);
  // 355: unless kind_of(definition) == INLINE_C_TYPE:
  // 356:   !definition.kind_of INLINE_C_TYPE
  // 357:   $base_of_base base_of(definition)
  // 358:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__28_16;
}
static void entry__28_15(void) {
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
  // 358: ... add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base_of_base */;
  arguments->slots[1] = frame->slots[1] /* ibase */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_12(void) {
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
  // 356: !definition.kind_of INLINE_C_TYPE
  frame->slots[3] /* temp__1 */ = var._INLINE_C_TYPE;
  // 356: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 357: $base_of_base base_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void cont__28_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base_of_base */, arguments->slots[0]);
  // 358: ... base_of_base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base_of_base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_14;
}
static void cont__28_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 358: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__28_15, 0);
  // 358: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__28_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 359: !definitions(ibase) definition
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* definition */;
  // 359: !definitions(ibase)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__28_17;
}
static void cont__28_17(void) {
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
static void entry__28_1_add_derived_type(void) {
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
  // 351: ... base .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__28_2;
}
static void cont__28_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 351: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__28_3;
}
static void cont__28_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 351: $ibase ordered_name(base .before. "::" base .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ibase */, arguments->slots[0]);
  // 352: $$definition definitions(ibase)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* definition */ = arguments->slots[0];
  // 353: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__28_6;
}
static void cont__28_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 353: ... :
  // 354:   !definition.derived_types_of(name) true
  // 355:   unless kind_of(definition) == INLINE_C_TYPE:
  // 356:     !definition.kind_of INLINE_C_TYPE
  // 357:     $base_of_base base_of(definition)
  // 358:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 359:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_7, 0);
  // 353: if definition.is_defined:
  // 354:   !definition.derived_types_of(name) true
  // 355:   unless kind_of(definition) == INLINE_C_TYPE:
  // 356:     !definition.kind_of INLINE_C_TYPE
  // 357:     $base_of_base base_of(definition)
  // 358:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 359:   !definitions(ibase) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_1_mangled(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 361: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__27_24;
  arguments->slots[1] = string__25_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 361: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__29_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 361: ... replace_all(name "::" = "__" '/' = "___")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__29_5;
}
static void cont__29_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 361: ... -> replace_all(name "::" = "__" '/' = "___")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_1_ordered_name(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 366: name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_2;
}
static void cont__30_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 368: namespace.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_3;
}
static void cont__30_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 365: string
  // 366:   name.to_lower_case
  // 367:   '/'
  // 368:   namespace.to_lower_case
  // 369:   '/'
  // 370:   name
  // 371:   '/'
  // 372:   namespace
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
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 364: ->
  // 365:   string
  // 366:     name.to_lower_case
  // 367:     '/'
  // 368:     namespace.to_lower_case
  // 369:     '/'
  // 370:     name
  // 371:     '/'
  // 372:     namespace
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__31_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 376: ... "href" = "index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__31_5;
}
static void cont__31_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 376: A "href" = "index.html" "Home"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_6;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__31_7;
}
static void cont__31_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 377: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__31_9;
}
static void cont__31_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 378: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__31_11;
}
static void cont__31_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 378: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_12;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__31_13;
}
static void cont__31_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 379: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__31_14;
}
static void cont__31_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__31_16;
}
static void cont__31_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 380: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_17;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__31_18;
}
static void cont__31_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 381: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__31_19;
}
static void cont__31_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 382: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__31_21;
}
static void cont__31_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 382: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_22;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__31_23;
}
static void cont__31_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 383: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__31_24;
}
static void cont__31_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 384: ... "href" = "topics_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__31_26;
}
static void cont__31_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 384: A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__31_1_link_bar(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 375: P:
  // 376:   A "href" = "index.html" "Home"
  // 377:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 378:   A "href" = "manual.html" "Manual"
  // 379:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 380:   A "href" = "type_index.html" "Type Index"
  // 381:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 382:   A "href" = "symbol_index.html" "Symbol Index"
  // 383:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 384:   A "href" = "topics_index.html" "Topics Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__31_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_1_to_paragraphs(void) {
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
  // 390: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 391: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 392: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 393: ... : (line)
  // 394:   if
  // 395:     pre_mode:
  // 396:       if
  // 397:         line .has_prefix. EXAMPLE:
  // 398:           trim &text
  // 399:           push &paragraphs text
  // 400:           !text line
  // 401:         :
  // 402:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_2, 1);
  // 393: for_each lines: (line)
  // 394:   if
  // 395:     pre_mode:
  // 396:       if
  // 397:         line .has_prefix. EXAMPLE:
  // 398:           trim &text
  // 399:           push &paragraphs text
  // 400:           !text line
  // 401:         :
  // 402:           writeln_to &text line
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_27;
}
static void entry__34_15(void) {
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
  // 407: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_16;
}
static void cont__34_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  // 408: !text ""
  ((CELL *)frame->slots[1])->contents /* text */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_12(void) {
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
  // 406: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_13;
}
static void cont__34_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 406: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_14;
}
static void cont__34_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 406: ... :
  // 407:   push &paragraphs text
  // 408:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_15, 0);
  // 406: if text != "":
  // 407:   push &paragraphs text
  // 408:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_17(void) {
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
  // 411: text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_18;
}
static void cont__34_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 411: ... :
  // 412:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_19, 0);
  // 413: :
  // 414:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_22, 0);
  // 410: if
  // 411:   text == "":
  // 412:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 413:   :
  // 414:     push &text ' '
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_24;
}
static void entry__34_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pre_mode: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: ... !pre_mode true
  ((CELL *)frame->slots[0])->contents /* pre_mode */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_19(void) {
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
  // 412: ... line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_20;
}
static void cont__34_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 412: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_21, 0);
  // 412: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 414: push &text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_23;
}
static void cont__34_23(void) {
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
static void cont__34_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 415: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_25;
}
static void cont__34_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 415: append &text line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_26;
}
static void cont__34_26(void) {
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
static void entry__34_5(void) {
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
  // 398: trim &text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_6;
}
static void cont__34_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 399: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = arguments->slots[0];
  // 400: !text line
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[2] /* line */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_8(void) {
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
  // 402: writeln_to &text line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__34_9;
}
static void cont__34_9(void) {
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
static void entry__34_3(void) {
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
  // 397: line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 397: ... :
  // 398:   trim &text
  // 399:   push &paragraphs text
  // 400:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_5, 0);
  // 401: :
  // 402:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_8, 0);
  // 396: if
  // 397:   line .has_prefix. EXAMPLE:
  // 398:     trim &text
  // 399:     push &paragraphs text
  // 400:     !text line
  // 401:   :
  // 402:     writeln_to &text line
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
static void entry__34_10(void) {
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
  // 405: line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void cont__34_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 405: ... :
  // 406:   if text != "":
  // 407:     push &paragraphs text
  // 408:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_12, 0);
  // 409: :
  // 410:   if
  // 411:     text == "":
  // 412:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 413:     :
  // 414:       push &text ' '
  // 415:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__34_17, 0);
  // 404: if
  // 405:   line == "":
  // 406:     if text != "":
  // 407:       push &paragraphs text
  // 408:       !text ""
  // 409:   :
  // 410:     if
  // 411:       text == "":
  // 412:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 413:       :
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
static void entry__34_2(void) {
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
  // 395: ... :
  // 396:   if
  // 397:     line .has_prefix. EXAMPLE:
  // 398:       trim &text
  // 399:       push &paragraphs text
  // 400:       !text line
  // 401:     :
  // 402:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_3, 0);
  // 403: :
  // 404:   if
  // 405:     line == "":
  // 406:       if text != "":
  // 407:         push &paragraphs text
  // 408:         !text ""
  // 409:     :
  // 410:       if
  // 411:         text == "":
  // 412:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_10, 0);
  // 394: if
  // 395:   pre_mode:
  // 396:     if
  // 397:       line .has_prefix. EXAMPLE:
  // 398:         trim &text
  // 399:         push &paragraphs text
  // 400:         !text line
  // 401:       :
  // 402:         writeln_to &text line
  // 403:   :
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
static void cont__34_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 416: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_28;
}
static void cont__34_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 416: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_29;
}
static void cont__34_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 416: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__34_30, 0);
  // 416: if text != "": push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_32;
}
static void entry__34_30(void) {
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
  // 416: ... push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_31;
}
static void cont__34_31(void) {
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
static void cont__34_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 417: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__35_1_resolve_reference(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 421: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 421: ... :
  // 422:   $$type_name reference .before. '/'
  // 423:   $$method_name reference .behind. '/'
  // 424:   unless type_name .contains. "::": append "types::" &type_name
  // 425:   unless method_name .contains. "::": append "std::" &method_name
  // 426:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__35_3, 0);
  // 427: :
  // 428:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__35_17, 0);
  // 420: if
  // 421:   reference .contains. '/':
  // 422:     $$type_name reference .before. '/'
  // 423:     $$method_name reference .behind. '/'
  // 424:     unless type_name .contains. "::": append "types::" &type_name
  // 425:     unless method_name .contains. "::": append "std::" &method_name
  // 426:     !reference string(type_name '/' method_name)
  // 427:   :
  // 428:     unless reference .contains. "::": append "std::" &reference
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
  frame->cont = cont__35_21;
}
static void entry__35_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 428: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__35_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void cont__35_20(void) {
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
static void entry__35_3(void) {
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
  // 422: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__35_4;
}
static void cont__35_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 423: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__35_5;
}
static void cont__35_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 424: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 424: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__35_7, 0);
  // 424: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__35_10;
}
static void entry__35_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 424: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__35_8;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_9;
}
static void cont__35_9(void) {
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
static void cont__35_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 425: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__35_11;
}
static void cont__35_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 425: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__35_12, 0);
  // 425: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void entry__35_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__35_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void cont__35_14(void) {
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
static void cont__35_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 426: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__35_16;
}
static void cont__35_16(void) {
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
static void entry__35_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 428: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 428: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__35_19, 0);
  // 428: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__35_21(void) {
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
static void entry__36_1_add_links(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // paragraph: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 434: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_2;
}
static void cont__36_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 434: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__36_3;
}
static void cont__36_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 434: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 433: =
  // 434:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 435:   : ($reference)
  // 436:     range &reference 2 -2
  // 437:     resolve_reference &reference
  // 438:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__36_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_14;
}
static void entry__36_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 436: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 436: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__36_7;
}
static void cont__36_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 437: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 438: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_9;
}
static void cont__36_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 438: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__36_10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__36_11;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__36_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_13;
}
static void cont__36_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 438: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 431: replace_all
  // 432:   &paragraph
  // 433:   =
  // 434:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 435:     : ($reference)
  // 436:       range &reference 2 -2
  // 437:       resolve_reference &reference
  // 438:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_15;
}
static void cont__36_15(void) {
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
static void entry__37_20(void) {
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
  // 451: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__37_21;
}
static void cont__37_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 453: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__37_22;
}
static void cont__37_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 453: ... :
  // 454:   $type function_name .before. '/'
  // 455:   $method function_name .behind. '/'
  // 456:   H1
  // 457:     string
  // 458:       '['
  // 459:       type
  // 460:       "]("
  // 461:       type.mangled
  // 462:       ".html)/["
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_23, 0);
  // 467: :
  // 468:   H1 function_name
  // 469:   
  // 470:   case variable_kind_of(info)
  // 471:     STATIC_MULTI: H2 "(static multi-assignment variable)"
  // 472:     DYNAMIC_SINGLE: H2 "(dynamic single-assignment variable)"
  // 473:     DYNAMIC_MULTI: H2 "(dynamic multi-assignment variable)"
  frame->slots[15] /* temp__3 */ = create_closure(entry__37_30, 0);
  // 452: if
  // 453:   function_name .contains. '/':
  // 454:     $type function_name .before. '/'
  // 455:     $method function_name .behind. '/'
  // 456:     H1
  // 457:       string
  // 458:         '['
  // 459:         type
  // 460:         "]("
  // 461:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_39;
}
static void entry__37_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 471: ... H2 "(static multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_34;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 472: ... H2 "(dynamic single-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_36;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_37(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 473: ... H2 "(dynamic multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_38;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_23(void) {
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
  // 454: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__37_24;
}
static void cont__37_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 455: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_25;
}
static void cont__37_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 461: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_26;
}
static void cont__37_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 465: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_27;
}
static void cont__37_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 457: string
  // 458:   '['
  // 459:   type
  // 460:   "]("
  // 461:   type.mangled
  // 462:   ".html)/["
  // 463:   method
  // 464:   "]("
  // 465:   method.mangled
  // 466:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__36_11;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__37_28;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__36_11;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__36_12;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_29;
}
static void cont__37_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 456: H1
  // 457:   string
  // 458:     '['
  // 459:     type
  // 460:     "]("
  // 461:     type.mangled
  // 462:     ".html)/["
  // 463:     method
  // 464:     "]("
  // 465:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_30(void) {
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
  // 468: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__37_31;
}
static void cont__37_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 470: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__37_32;
}
static void cont__37_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 470: case variable_kind_of(info)
  // 471:   STATIC_MULTI: H2 "(static multi-assignment variable)"
  // 472:   DYNAMIC_SINGLE: H2 "(dynamic single-assignment variable)"
  // 473:   DYNAMIC_MULTI: H2 "(dynamic multi-assignment variable)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = func__37_33;
  arguments->slots[3] = get__DYNAMIC_SINGLE();
  arguments->slots[4] = func__37_35;
  arguments->slots[5] = get__DYNAMIC_MULTI();
  arguments->slots[6] = func__37_37;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 475: $$short_description undefined
  ((CELL *)frame->slots[3])->contents /* short_description */ = get__undefined();
  // 476: $$parameters empty_list
  ((CELL *)frame->slots[4])->contents /* parameters */ = get__empty_list();
  // 477: $$return_values empty_list
  ((CELL *)frame->slots[5])->contents /* return_values */ = get__empty_list();
  // 478: $$descriptions empty_list
  ((CELL *)frame->slots[6])->contents /* descriptions */ = get__empty_list();
  // 479: $$technical_details undefined
  ((CELL *)frame->slots[7])->contents /* technical_details */ = get__undefined();
  // 480: $$references empty_list
  ((CELL *)frame->slots[8])->contents /* references */ = get__empty_list();
  // 481: $$topic_list empty_list
  ((CELL *)frame->slots[9])->contents /* topic_list */ = get__empty_list();
  // 482: $$examples empty_list
  ((CELL *)frame->slots[10])->contents /* examples */ = get__empty_list();
  // 483: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__37_40;
}
static void cont__37_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* remark_lines */, arguments->slots[0]);
  // 484: ... remark_lines.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_41;
}
static void cont__37_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 484: ... remark_lines.is_empty
  frame->slots[15] /* temp__3 */ = create_closure(entry__37_42, 0);
  // 484: ... remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__37_44;
}
static void entry__37_42(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 484: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_43;
}
static void cont__37_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 484: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 484: ... :
  // 485:   inc &missing_documentation_count
  // 486:   if do_print_missing:
  // 487:     ewrite "
  // 488:       Missing documentation for @(function_name) @
  // 489:       (defined in "@(filename_of(info))")!
  frame->slots[16] /* temp__4 */ = create_closure(entry__37_45, 0);
  // 484: if remark_lines.is_undefined || remark_lines.is_empty:
  // 485:   inc &missing_documentation_count
  // 486:   if do_print_missing:
  // 487:     ewrite "
  // 488:       Missing documentation for @(function_name) @
  // 489:       (defined in "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_53;
}
static void entry__37_47(void) {
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
  // 489: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__37_48;
}
static void cont__37_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 487: ... "
  // 488:   Missing documentation for @(function_name) @
  // 489:   (defined in "@(filename_of(info))")!
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__37_49;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__37_50;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__37_51;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_52;
}
static void cont__37_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 487: ewrite "
  // 488:   Missing documentation for @(function_name) @
  // 489:   (defined in "@(filename_of(info))")!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_45(void) {
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
  // 485: inc &missing_documentation_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__37_46;
}
static void cont__37_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._missing_documentation_count = arguments->slots[0];
  // 486: ... :
  // 487:   ewrite "
  // 488:     Missing documentation for @(function_name) @
  // 489:     (defined in "@(filename_of(info))")!
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_47, 0);
  // 486: if do_print_missing:
  // 487:   ewrite "
  // 488:     Missing documentation for @(function_name) @
  // 489:     (defined in "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_missing();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 490: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_54;
}
static void cont__37_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 490: ... :
  // 491:   $paragraphs remark_lines.to_paragraphs
  // 492:   for_each paragraphs: ($paragraph)
  // 493:     cond
  // 494:       ->
  // 495:         has_prefix
  // 496:           paragraph
  // 497:           sequence
  // 498:             "Parameter"
  // 499:             sim2c::WHITESPACE
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_55, 0);
  // 490: if remark_lines.is_defined:
  // 491:   $paragraphs remark_lines.to_paragraphs
  // 492:   for_each paragraphs: ($paragraph)
  // 493:     cond
  // 494:       ->
  // 495:         has_prefix
  // 496:           paragraph
  // 497:           sequence
  // 498:             "Parameter"
  // 499:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_178;
}
static void entry__37_173(void) {
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
  // 578: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_174;
}
static void cont__37_174(void) {
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
static void entry__37_175(void) {
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
  // 580: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_176;
}
static void cont__37_176(void) {
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
static void entry__37_171(void) {
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
  // 577: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_172;
}
static void cont__37_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 577: ... :
  // 578:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__37_173, 0);
  // 579: :
  // 580:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_175, 0);
  // 576: if
  // 577:   technical_details.is_defined:
  // 578:     push &technical_details paragraph
  // 579:   :
  // 580:     push &descriptions paragraph
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
static void entry__37_177(void) {
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
  // 582: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_155(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_156(void) {
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
  // 564: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__37_157;
}
static void cont__37_157(void) {
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
static void entry__37_151(void) {
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
  // 559: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_152;
}
static void cont__37_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 559: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_153;
}
static void cont__37_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 561: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__37_154;
}
static void cont__37_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 561: ... :
  // 562:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__37_155, 0);
  // 563: :
  // 564:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_156, 0);
  // 560: if
  // 561:   detail == "":
  // 562:     !technical_details empty_list
  // 563:   :
  // 564:     !technical_details list(detail)
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
static void entry__37_141(void) {
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
  // 555: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__37_142;
}
static void cont__37_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 555: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_143;
}
static void cont__37_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 556: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_144;
}
static void cont__37_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 556: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_145;
}
static void cont__37_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 557: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_146;
}
static void cont__37_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 557: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_147;
}
static void cont__37_147(void) {
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
static void entry__37_132(void) {
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
  // 546: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_133;
}
static void cont__37_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 547: push &topic_list topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* topic_list */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_134;
}
static void cont__37_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* topic_list */ = arguments->slots[0];
  // 550: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__37_135;
}
static void cont__37_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 549: $$topic_contents
  // 550:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__37_136;
}
static void cont__37_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 552: !topic_contents(function_name) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 552: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* function_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__37_137;
}
static void cont__37_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 553: !topics(topic) topic_contents
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  // 553: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__37_138;
}
static void cont__37_138(void) {
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
static void entry__37_129(void) {
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
  // 545: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_130;
}
static void cont__37_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 545: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__37_131;
}
static void cont__37_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 545: ... : ($topic)
  // 546:   trim &topic
  // 547:   push &topic_list topic
  // 548:   
  // 549:   $$topic_contents
  // 550:     default_value(topics(topic) empty_key_order_set)
  // 551:   
  // 552:   !topic_contents(function_name) true
  // 553:   !topics(topic) topic_contents
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_132, 1);
  // 545: for_each split(paragraph .behind. ':' ','): ($topic)
  // 546:   trim &topic
  // 547:   push &topic_list topic
  // 548:   
  // 549:   $$topic_contents
  // 550:     default_value(topics(topic) empty_key_order_set)
  // 551:   
  // 552:   !topic_contents(function_name) true
  // 553:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_124(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 543: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_125;
}
static void cont__37_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 543: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_126;
}
static void cont__37_126(void) {
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
static void entry__37_121(void) {
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
  // 542: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_122;
}
static void cont__37_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 542: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__37_123;
}
static void cont__37_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 542: ... : (reference)
  // 543:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__37_124, 1);
  // 542: for_each split(paragraph .behind. ':' ','): (reference)
  // 543:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_99(void) {
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
  // 530: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__37_100;
}
static void cont__37_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 532: -> return_value .has_suffix. '?':
  // 533:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__37_101, 0);
  // 534: -> return_value .has_suffix. '*':
  // 535:   !return_value
  // 536:     string
  // 537:       range(return_value 1 -2)
  // 538:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_107, 0);
  // 531: cond
  // 532:   -> return_value .has_suffix. '?':
  // 533:     !return_value string(range(return_value 1 -2) " (optional)")
  // 534:   -> return_value .has_suffix. '*':
  // 535:     !return_value
  // 536:       string
  // 537:         range(return_value 1 -2)
  // 538:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__37_113;
}
static void entry__37_109(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_110;
}
static void cont__37_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 537: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_111;
}
static void cont__37_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 535: !return_value
  // 536:   string
  // 537:     range(return_value 1 -2)
  // 538:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__37_77;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_112;
}
static void cont__37_112(void) {
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
static void entry__37_103(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 533: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_104;
}
static void cont__37_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 533: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_105;
}
static void cont__37_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 533: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__37_70;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_106;
}
static void cont__37_106(void) {
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
static void entry__37_101(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 532: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__37_102;
}
static void cont__37_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 532: ... :
  // 533:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__37_103, 0);
  // 532: -> return_value .has_suffix. '?':
  // 533:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_107(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 534: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__37_108;
}
static void cont__37_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 534: ... :
  // 535:   !return_value
  // 536:     string
  // 537:       range(return_value 1 -2)
  // 538:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__37_109, 0);
  // 534: -> return_value .has_suffix. '*':
  // 535:   !return_value
  // 536:     string
  // 537:       range(return_value 1 -2)
  // 538:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 539: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_114;
}
static void cont__37_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 539: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_115;
}
static void cont__37_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 540: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_116;
}
static void cont__37_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 540: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_117;
}
static void cont__37_117(void) {
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
static void entry__37_63(void) {
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
  // 504: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__37_64;
}
static void cont__37_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 506: -> parameter .has_suffix. '?':
  // 507:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__37_65, 0);
  // 508: -> parameter .has_suffix. '*':
  // 509:   !parameter
  // 510:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_72, 0);
  // 511: -> parameter .contains. '=':
  // 512:   !parameter
  // 513:     string
  // 514:       (parameter .before. '=').trim
  // 515:       " (optional; default value: "
  // 516:       (parameter .behind. '=').trim
  // 517:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__37_79, 0);
  // 505: cond
  // 506:   -> parameter .has_suffix. '?':
  // 507:     !parameter string(range(parameter 1 -2) " (optional)")
  // 508:   -> parameter .has_suffix. '*':
  // 509:     !parameter
  // 510:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 511:   -> parameter .contains. '=':
  // 512:     !parameter
  // 513:       string
  // 514:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__37_89;
}
static void entry__37_81(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 514: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__37_82;
}
static void cont__37_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 514: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_83;
}
static void cont__37_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 516: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_84;
}
static void cont__37_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 516: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_85;
}
static void cont__37_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 512: !parameter
  // 513:   string
  // 514:     (parameter .before. '=').trim
  // 515:     " (optional; default value: "
  // 516:     (parameter .behind. '=').trim
  // 517:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__37_86;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__37_87;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_88;
}
static void cont__37_88(void) {
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
static void entry__37_74(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 510: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_75;
}
static void cont__37_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 510: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_76;
}
static void cont__37_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 509: !parameter
  // 510:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__37_77;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_78;
}
static void cont__37_78(void) {
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
static void entry__37_67(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 507: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_68;
}
static void cont__37_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 507: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_69;
}
static void cont__37_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 507: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__37_70;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_71;
}
static void cont__37_71(void) {
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
static void entry__37_65(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 506: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__37_66;
}
static void cont__37_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 506: ... :
  // 507:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__37_67, 0);
  // 506: -> parameter .has_suffix. '?':
  // 507:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 508: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__37_73;
}
static void cont__37_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 508: ... :
  // 509:   !parameter
  // 510:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__37_74, 0);
  // 508: -> parameter .has_suffix. '*':
  // 509:   !parameter
  // 510:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_79(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 511: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__37_80;
}
static void cont__37_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 511: ... :
  // 512:   !parameter
  // 513:     string
  // 514:       (parameter .before. '=').trim
  // 515:       " (optional; default value: "
  // 516:       (parameter .behind. '=').trim
  // 517:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__37_81, 0);
  // 511: -> parameter .contains. '=':
  // 512:   !parameter
  // 513:     string
  // 514:       (parameter .before. '=').trim
  // 515:       " (optional; default value: "
  // 516:       (parameter .behind. '=').trim
  // 517:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 518: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_90;
}
static void cont__37_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 518: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__37_91;
}
static void cont__37_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 519: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_92;
}
static void cont__37_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 519: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_93;
}
static void cont__37_93(void) {
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
static void entry__37_58(void) {
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
  // 501: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__37_59;
}
static void cont__37_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 497: sequence
  // 498:   "Parameter"
  // 499:   sim2c::WHITESPACE
  // 500:   NAME
  // 501:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 502:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__37_60;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__37_61;
}
static void cont__37_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 495: has_prefix
  // 496:   paragraph
  // 497:   sequence
  // 498:     "Parameter"
  // 499:     sim2c::WHITESPACE
  // 500:     NAME
  // 501:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 502:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_62;
}
static void cont__37_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 503: :
  // 504:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 505:   cond
  // 506:     -> parameter .has_suffix. '?':
  // 507:       !parameter string(range(parameter 1 -2) " (optional)")
  // 508:     -> parameter .has_suffix. '*':
  // 509:       !parameter
  // 510:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 511:     -> parameter .contains. '=':
  // 512:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__37_63, 0);
  // 494: ->
  // 495:   has_prefix
  // 496:     paragraph
  // 497:     sequence
  // 498:       "Parameter"
  // 499:       sim2c::WHITESPACE
  // 500:       NAME
  // 501:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 502:       ':'
  // 503:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_94(void) {
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
  // 527: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__37_95;
}
static void cont__37_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 523: sequence
  // 524:   "Returns"
  // 525:   sim2c::WHITESPACE
  // 526:   NAME
  // 527:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 528:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__37_96;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__37_97;
}
static void cont__37_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 521: has_prefix
  // 522:   paragraph
  // 523:   sequence
  // 524:     "Returns"
  // 525:     sim2c::WHITESPACE
  // 526:     NAME
  // 527:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 528:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_98;
}
static void cont__37_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 529: :
  // 530:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 531:   cond
  // 532:     -> return_value .has_suffix. '?':
  // 533:       !return_value string(range(return_value 1 -2) " (optional)")
  // 534:     -> return_value .has_suffix. '*':
  // 535:       !return_value
  // 536:         string
  // 537:           range(return_value 1 -2)
  // 538:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__37_99, 0);
  // 520: ->
  // 521:   has_prefix
  // 522:     paragraph
  // 523:     sequence
  // 524:       "Returns"
  // 525:       sim2c::WHITESPACE
  // 526:       NAME
  // 527:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 528:       ':'
  // 529:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_118(void) {
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
  // 541: ... paragraph .has_prefix. "See also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__37_119;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_120;
}
static void cont__37_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 541: ... :
  // 542:   for_each split(paragraph .behind. ':' ','): (reference)
  // 543:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_121, 0);
  // 541: -> paragraph .has_prefix. "See also:":
  // 542:   for_each split(paragraph .behind. ':' ','): (reference)
  // 543:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_127(void) {
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
  // 544: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_128;
}
static void cont__37_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 544: ... :
  // 545:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 546:     trim &topic
  // 547:     push &topic_list topic
  // 548:     
  // 549:     $$topic_contents
  // 550:       default_value(topics(topic) empty_key_order_set)
  // 551:     
  // 552:     !topic_contents(function_name) true
  // 553:     !topics(topic) topic_contents
  frame->slots[4] /* temp__2 */ = create_closure(entry__37_129, 0);
  // 544: -> paragraph .has_prefix. TOPIC:
  // 545:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 546:     trim &topic
  // 547:     push &topic_list topic
  // 548:     
  // 549:     $$topic_contents
  // 550:       default_value(topics(topic) empty_key_order_set)
  // 551:     
  // 552:     !topic_contents(function_name) true
  // 553:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_139(void) {
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
  // 554: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_140;
}
static void cont__37_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 554: ... :
  // 555:   $title (paragraph .before. ':').trim
  // 556:   $text (paragraph .behind. ':').trim
  // 557:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_141, 0);
  // 554: -> paragraph .has_prefix. EXAMPLE:
  // 555:   $title (paragraph .before. ':').trim
  // 556:   $text (paragraph .behind. ':').trim
  // 557:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_148(void) {
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
  // 558: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__37_149;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__37_150;
}
static void cont__37_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 558: ... :
  // 559:   $detail (paragraph .behind. ':').trim
  // 560:   if
  // 561:     detail == "":
  // 562:       !technical_details empty_list
  // 563:     :
  // 564:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_151, 0);
  // 558: -> paragraph .has_prefix. "Technical Details:":
  // 559:   $detail (paragraph .behind. ':').trim
  // 560:   if
  // 561:     detail == "":
  // 562:       !technical_details empty_list
  // 563:     :
  // 564:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_158(void) {
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
  // 569: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__37_159;
}
static void cont__37_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 569: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__37_160;
}
static void cont__37_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 569: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__37_161;
}
static void cont__37_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 570: : ($reference)
  // 571:   range &reference 2 -2
  // 572:   resolve_and_check_reference &reference
  // 573:   -> "[@(reference)](@(reference.mangled).html)"
  frame->slots[9] /* temp__5 */ = create_closure(entry__37_162, 1);
  // 568: =
  // 569:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 570:   : ($reference)
  // 571:     range &reference 2 -2
  // 572:     resolve_and_check_reference &reference
  // 573:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_168;
}
static void entry__37_162(void) {
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
  // 571: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__37_163;
}
static void cont__37_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 571: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__37_164;
}
static void cont__37_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 572: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__37_165;
}
static void cont__37_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 573: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_166;
}
static void cont__37_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 573: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__36_10;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__36_11;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__36_12;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_167;
}
static void cont__37_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 573: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 566: replace_all
  // 567:   &paragraph
  // 568:   =
  // 569:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 570:     : ($reference)
  // 571:       range &reference 2 -2
  // 572:       resolve_and_check_reference &reference
  // 573:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__37_169;
}
static void cont__37_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 575: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_170;
}
static void cont__37_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 575: ... :
  // 576:   if
  // 577:     technical_details.is_defined:
  // 578:       push &technical_details paragraph
  // 579:     :
  // 580:       push &descriptions paragraph
  frame->slots[6] /* temp__2 */ = create_closure(entry__37_171, 0);
  // 581: :
  // 582:   !short_description paragraph
  frame->slots[7] /* temp__3 */ = create_closure(entry__37_177, 0);
  // 574: if
  // 575:   short_description.is_defined:
  // 576:     if
  // 577:       technical_details.is_defined:
  // 578:         push &technical_details paragraph
  // 579:       :
  // 580:         push &descriptions paragraph
  // 581:   :
  // 582:     !short_description paragraph
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
static void entry__37_57(void) {
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
  // 494: ->
  // 495:   has_prefix
  // 496:     paragraph
  // 497:     sequence
  // 498:       "Parameter"
  // 499:       sim2c::WHITESPACE
  // 500:       NAME
  // 501:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 502:       ':'
  // 503:   :
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__37_58, 0);
  // 520: ->
  // 521:   has_prefix
  // 522:     paragraph
  // 523:     sequence
  // 524:       "Returns"
  // 525:       sim2c::WHITESPACE
  // 526:       NAME
  // 527:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 528:       ':'
  // 529:   :
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__37_94, 0);
  // 541: -> paragraph .has_prefix. "See also:":
  // 542:   for_each split(paragraph .behind. ':' ','): (reference)
  // 543:     push &references reference.trim
  frame->slots[13] /* temp__3 */ = create_closure(entry__37_118, 0);
  // 544: -> paragraph .has_prefix. TOPIC:
  // 545:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 546:     trim &topic
  // 547:     push &topic_list topic
  // 548:     
  // 549:     $$topic_contents
  // 550:       default_value(topics(topic) empty_key_order_set)
  // 551:     
  // 552:     !topic_contents(function_name) true
  // 553:     !topics(topic) topic_contents
  frame->slots[14] /* temp__4 */ = create_closure(entry__37_127, 0);
  // 554: -> paragraph .has_prefix. EXAMPLE:
  // 555:   $title (paragraph .before. ':').trim
  // 556:   $text (paragraph .behind. ':').trim
  // 557:   push &examples title = text
  frame->slots[15] /* temp__5 */ = create_closure(entry__37_139, 0);
  // 558: -> paragraph .has_prefix. "Technical Details:":
  // 559:   $detail (paragraph .behind. ':').trim
  // 560:   if
  // 561:     detail == "":
  // 562:       !technical_details empty_list
  // 563:     :
  // 564:       !technical_details list(detail)
  frame->slots[16] /* temp__6 */ = create_closure(entry__37_148, 0);
  // 565: :
  // 566:   replace_all
  // 567:     &paragraph
  // 568:     =
  // 569:       '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 570:       : ($reference)
  // 571:         range &reference 2 -2
  // 572:         resolve_and_check_reference &reference
  // 573:         -> "[@(reference)](@(reference.mangled).html)"
  // 574:   if
  // ...
  frame->slots[17] /* temp__7 */ = create_closure(entry__37_158, 0);
  // 493: cond
  // 494:   ->
  // 495:     has_prefix
  // 496:       paragraph
  // 497:       sequence
  // 498:         "Parameter"
  // 499:         sim2c::WHITESPACE
  // 500:         NAME
  // 501:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 502:         ':'
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
static void entry__37_55(void) {
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
  // 491: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__37_56;
}
static void cont__37_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* paragraphs */, arguments->slots[0]);
  // 492: ... : ($paragraph)
  // 493:   cond
  // 494:     ->
  // 495:       has_prefix
  // 496:         paragraph
  // 497:         sequence
  // 498:           "Parameter"
  // 499:           sim2c::WHITESPACE
  // 500:           NAME
  // 501:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[12] /* temp__1 */ = create_closure(entry__37_57, 1);
  // 492: for_each paragraphs: ($paragraph)
  // 493:   cond
  // 494:     ->
  // 495:       has_prefix
  // 496:         paragraph
  // 497:         sequence
  // 498:           "Parameter"
  // 499:           sim2c::WHITESPACE
  // 500:           NAME
  // 501:           optional(PARAMETER_COUNT_OR_MYSELF)
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
static void cont__37_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 583: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__37_179;
}
static void cont__37_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 583: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__37_180;
}
static void cont__37_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 583: ... :
  // 584:   for_each parameters_of(info): (parameter)
  // 585:     case
  // 586:       parameter_kind_of(parameter)
  // 587:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 588:         pass
  // 589:       :
  // 590:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:         cond
  // 592:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__37_181, 0);
  // 583: if kind_of(info) == FUNCTION:
  // 584:   for_each parameters_of(info): (parameter)
  // 585:     case
  // 586:       parameter_kind_of(parameter)
  // 587:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 588:         pass
  // 589:       :
  // 590:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:         cond
  // 592:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_218;
}
static void entry__37_186(void) {
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
  // 590: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__37_187;
}
static void cont__37_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 590: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__37_188;
}
static void cont__37_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 590: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__37_189;
}
static void cont__37_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 592: -> parameter.is_an_optional_item:
  // 593:   if
  // 594:     default_value_of(parameter).is_defined:
  // 595:       write_to
  // 596:         &name
  // 597:         " (optional; default value: "
  // 598:         default_value_of(parameter).to_string
  // 599:         ")"
  // 600:     :
  // 601:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__37_190, 0);
  // 602: -> parameter.is_an_expanded_item:
  // 603:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__37_201, 0);
  // 591: cond
  // 592:   -> parameter.is_an_optional_item:
  // 593:     if
  // 594:       default_value_of(parameter).is_defined:
  // 595:         write_to
  // 596:           &name
  // 597:           " (optional; default value: "
  // 598:           default_value_of(parameter).to_string
  // 599:           ")"
  // 600:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__37_205;
}
static void entry__37_203(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__37_77;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__37_204;
}
static void cont__37_204(void) {
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
static void entry__37_195(void) {
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
  // 598: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__37_196;
}
static void cont__37_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 598: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__37_197;
}
static void cont__37_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 595: write_to
  // 596:   &name
  // 597:   " (optional; default value: "
  // 598:   default_value_of(parameter).to_string
  // 599:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__37_86;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__37_87;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__37_198;
}
static void cont__37_198(void) {
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
static void entry__37_199(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 601: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__37_70;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__37_200;
}
static void cont__37_200(void) {
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
static void entry__37_192(void) {
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
  // 594: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__37_193;
}
static void cont__37_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 594: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_194;
}
static void cont__37_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 594: ... :
  // 595:   write_to
  // 596:     &name
  // 597:     " (optional; default value: "
  // 598:     default_value_of(parameter).to_string
  // 599:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__37_195, 0);
  // 600: :
  // 601:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__37_199, 0);
  // 593: if
  // 594:   default_value_of(parameter).is_defined:
  // 595:     write_to
  // 596:       &name
  // 597:       " (optional; default value: "
  // 598:       default_value_of(parameter).to_string
  // 599:       ")"
  // 600:   :
  // 601:     append &name " (optional)"
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
static void entry__37_190(void) {
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
  // 592: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__37_191;
}
static void cont__37_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 592: ... :
  // 593:   if
  // 594:     default_value_of(parameter).is_defined:
  // 595:       write_to
  // 596:         &name
  // 597:         " (optional; default value: "
  // 598:         default_value_of(parameter).to_string
  // 599:         ")"
  // 600:     :
  // 601:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_192, 0);
  // 592: -> parameter.is_an_optional_item:
  // 593:   if
  // 594:     default_value_of(parameter).is_defined:
  // 595:       write_to
  // 596:         &name
  // 597:         " (optional; default value: "
  // 598:         default_value_of(parameter).to_string
  // 599:         ")"
  // 600:     :
  // 601:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_201(void) {
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
  // 602: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__37_202;
}
static void cont__37_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 602: ... :
  // 603:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_203, 0);
  // 602: -> parameter.is_an_expanded_item:
  // 603:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_205(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 607: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__37_206;
}
static void cont__37_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 607: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_207;
}
static void cont__37_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 607: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__37_208;
}
static void cont__37_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 608: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__37_209, 0);
  // 605: $description
  // 606:   if
  // 607:     not(remark_lines_of(parameter).is_empty)
  // 608:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 609:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__37_213;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_214;
}
static void entry__37_209(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__37_210;
}
static void cont__37_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 608: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__37_211;
}
static void cont__37_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 608: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__37_212;
}
static void cont__37_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 608: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__37_213(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 609: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 611: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_215;
}
static void cont__37_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 611: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__37_216;
}
static void cont__37_216(void) {
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
static void entry__37_217(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 588: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_183(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 586: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__37_184;
}
static void cont__37_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 587: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__37_185;
}
static void cont__37_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 589: :
  // 590:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:   cond
  // 592:     -> parameter.is_an_optional_item:
  // 593:       if
  // 594:         default_value_of(parameter).is_defined:
  // 595:           write_to
  // 596:             &name
  // 597:             " (optional; default value: "
  // 598:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__37_186, 0);
  // 585: case
  // 586:   parameter_kind_of(parameter)
  // 587:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 588:     pass
  // 589:   :
  // 590:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:     cond
  // 592:       -> parameter.is_an_optional_item:
  // 593:         if
  // 594:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__37_217;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_181(void) {
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
  // 584: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__37_182;
}
static void cont__37_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 584: ... : (parameter)
  // 585:   case
  // 586:     parameter_kind_of(parameter)
  // 587:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 588:       pass
  // 589:     :
  // 590:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:       cond
  // 592:         -> parameter.is_an_optional_item:
  // 593:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_183, 1);
  // 584: for_each parameters_of(info): (parameter)
  // 585:   case
  // 586:     parameter_kind_of(parameter)
  // 587:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 588:       pass
  // 589:     :
  // 590:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 591:       cond
  // 592:         -> parameter.is_an_optional_item:
  // 593:           if
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
static void cont__37_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 612: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_219;
}
static void cont__37_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 612: ... : P short_description
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_220, 0);
  // 612: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_221;
}
static void entry__37_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 612: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 613: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_222;
}
static void cont__37_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 613: ... :
  // 614:   H2 "Parameters"
  // 615:   DL:
  // 616:     for_each parameters: (parameter)
  // 617:       DT key_of(parameter)
  // 618:       DD: P std::value_of(parameter)
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_223, 0);
  // 613: unless parameters.is_empty:
  // 614:   H2 "Parameters"
  // 615:   DL:
  // 616:     for_each parameters: (parameter)
  // 617:       DT key_of(parameter)
  // 618:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_232;
}
static void entry__37_230(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 618: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__37_231;
}
static void cont__37_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 618: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_227(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 617: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__37_228;
}
static void cont__37_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 617: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__37_229;
}
static void cont__37_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_230, 0);
  // 618: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_226(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 616: for_each parameters: (parameter)
  // 617:   DT key_of(parameter)
  // 618:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__37_227;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_223(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 614: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_224;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_225;
}
static void cont__37_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 615: ... :
  // 616:   for_each parameters: (parameter)
  // 617:     DT key_of(parameter)
  // 618:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_226, 0);
  // 615: DL:
  // 616:   for_each parameters: (parameter)
  // 617:     DT key_of(parameter)
  // 618:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_233;
}
static void cont__37_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 619: ... :
  // 620:   H2 "Returns"
  // 621:   DL:
  // 622:     for_each return_values: (return_value)
  // 623:       DT key_of(return_value)
  // 624:       DD: P std::value_of(return_value)
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_234, 0);
  // 619: unless return_values.is_empty:
  // 620:   H2 "Returns"
  // 621:   DL:
  // 622:     for_each return_values: (return_value)
  // 623:       DT key_of(return_value)
  // 624:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_242;
}
static void entry__37_240(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 624: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__37_241;
}
static void cont__37_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 624: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_237(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 623: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__37_238;
}
static void cont__37_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 623: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__37_239;
}
static void cont__37_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 624: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_240, 0);
  // 624: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_236(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 622: for_each return_values: (return_value)
  // 623:   DT key_of(return_value)
  // 624:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__37_237;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_234(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 620: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_96;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_235;
}
static void cont__37_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 621: ... :
  // 622:   for_each return_values: (return_value)
  // 623:     DT key_of(return_value)
  // 624:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_236, 0);
  // 621: DL:
  // 622:   for_each return_values: (return_value)
  // 623:     DT key_of(return_value)
  // 624:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_242(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 625: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_243;
}
static void cont__37_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 625: ... :
  // 626:   H2 "Description"
  // 627:   for_each descriptions: (description) P description
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_244, 0);
  // 625: unless descriptions.is_empty:
  // 626:   H2 "Description"
  // 627:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_248;
}
static void entry__37_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 627: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_244(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 626: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_245;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_246;
}
static void cont__37_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 627: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__37_247;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_248(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 628: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_249;
}
static void cont__37_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 628: ... :
  // 629:   H2 "Technical Details"
  // 630:   for_each technical_details: (detail) P detail
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_250, 0);
  // 628: if technical_details.is_defined:
  // 629:   H2 "Technical Details"
  // 630:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_254;
}
static void entry__37_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 630: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_250(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 629: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_251;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_252;
}
static void cont__37_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 630: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__37_253;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_254(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 631: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_255;
}
static void cont__37_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 631: ... :
  // 632:   H2 "See also"
  // 633:   TABLE:
  // 634:     for_each references: ($reference)
  // 635:       resolve_and_check_reference &reference
  // 636:       TR:
  // 637:         TD: A "href" = "@(reference.mangled).html" reference
  // 638:         TD "&nbsp;"
  // 639:         TD short_descriptions(reference)
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_256, 0);
  // 631: unless references.is_empty:
  // 632:   H2 "See also"
  // 633:   TABLE:
  // 634:     for_each references: ($reference)
  // 635:       resolve_and_check_reference &reference
  // 636:       TR:
  // 637:         TD: A "href" = "@(reference.mangled).html" reference
  // 638:         TD "&nbsp;"
  // 639:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_271;
}
static void entry__37_262(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 637: ... : A "href" = "@(reference.mangled).html" reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_263, 0);
  // 637: TD: A "href" = "@(reference.mangled).html" reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_267;
}
static void entry__37_263(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 637: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_264;
}
static void cont__37_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 637: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_265;
}
static void cont__37_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 637: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_266;
}
static void cont__37_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 637: ... A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_267(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 638: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_269;
}
static void cont__37_269(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__37_270;
}
static void cont__37_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 639: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_260(void) {
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
  // 635: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__37_261;
}
static void cont__37_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 636: ... :
  // 637:   TD: A "href" = "@(reference.mangled).html" reference
  // 638:   TD "&nbsp;"
  // 639:   TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_262, 0);
  // 636: TR:
  // 637:   TD: A "href" = "@(reference.mangled).html" reference
  // 638:   TD "&nbsp;"
  // 639:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_259(void) {
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
  // 634: ... : ($reference)
  // 635:   resolve_and_check_reference &reference
  // 636:   TR:
  // 637:     TD: A "href" = "@(reference.mangled).html" reference
  // 638:     TD "&nbsp;"
  // 639:     TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_260, 1);
  // 634: for_each references: ($reference)
  // 635:   resolve_and_check_reference &reference
  // 636:   TR:
  // 637:     TD: A "href" = "@(reference.mangled).html" reference
  // 638:     TD "&nbsp;"
  // 639:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_256(void) {
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
  // 632: H2 "See also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_257;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_258;
}
static void cont__37_258(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 633: ... :
  // 634:   for_each references: ($reference)
  // 635:     resolve_and_check_reference &reference
  // 636:     TR:
  // 637:       TD: A "href" = "@(reference.mangled).html" reference
  // 638:       TD "&nbsp;"
  // 639:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_259, 0);
  // 633: TABLE:
  // 634:   for_each references: ($reference)
  // 635:     resolve_and_check_reference &reference
  // 636:     TR:
  // 637:       TD: A "href" = "@(reference.mangled).html" reference
  // 638:       TD "&nbsp;"
  // 639:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_271(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 640: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__37_272;
}
static void cont__37_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 640: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_273;
}
static void cont__37_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 640: ... :
  // 641:   H2 "Implemented by"
  // 642:   TABLE:
  // 643:     for_each types_of(info): (name)
  // 644:       $method string(name '/' function_name)
  // 645:       TR:
  // 646:         TD: A "href" = "@(name.mangled).html" name
  // 647:         TD "&nbsp;as&nbsp;"
  // 648:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[15] /* temp__3 */ = create_closure(entry__37_274, 0);
  // 640: unless types_of(info).is_empty:
  // 641:   H2 "Implemented by"
  // 642:   TABLE:
  // 643:     for_each types_of(info): (name)
  // 644:       $method string(name '/' function_name)
  // 645:       TR:
  // 646:         TD: A "href" = "@(name.mangled).html" name
  // 647:         TD "&nbsp;as&nbsp;"
  // 648:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_293;
}
static void entry__37_289(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 648: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_290;
}
static void cont__37_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 648: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_291;
}
static void cont__37_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 648: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_292;
}
static void cont__37_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 648: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_281(void) {
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
  // 646: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_282, 0);
  // 646: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_286;
}
static void entry__37_282(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_283;
}
static void cont__37_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 646: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_284;
}
static void cont__37_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 646: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_285;
}
static void cont__37_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 646: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_286(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_287;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_288;
}
static void cont__37_288(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 648: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_289, 0);
  // 648: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_279(void) {
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
  // 644: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_280;
}
static void cont__37_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 645: ... :
  // 646:   TD: A "href" = "@(name.mangled).html" name
  // 647:   TD "&nbsp;as&nbsp;"
  // 648:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__37_281, 0);
  // 645: TR:
  // 646:   TD: A "href" = "@(name.mangled).html" name
  // 647:   TD "&nbsp;as&nbsp;"
  // 648:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_277(void) {
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
  // 643: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__37_278;
}
static void cont__37_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 643: ... : (name)
  // 644:   $method string(name '/' function_name)
  // 645:   TR:
  // 646:     TD: A "href" = "@(name.mangled).html" name
  // 647:     TD "&nbsp;as&nbsp;"
  // 648:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_279, 1);
  // 643: for_each types_of(info): (name)
  // 644:   $method string(name '/' function_name)
  // 645:   TR:
  // 646:     TD: A "href" = "@(name.mangled).html" name
  // 647:     TD "&nbsp;as&nbsp;"
  // 648:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_274(void) {
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
  // 641: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_275;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_276;
}
static void cont__37_276(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: ... :
  // 643:   for_each types_of(info): (name)
  // 644:     $method string(name '/' function_name)
  // 645:     TR:
  // 646:       TD: A "href" = "@(name.mangled).html" name
  // 647:       TD "&nbsp;as&nbsp;"
  // 648:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_277, 0);
  // 642: TABLE:
  // 643:   for_each types_of(info): (name)
  // 644:     $method string(name '/' function_name)
  // 645:     TR:
  // 646:       TD: A "href" = "@(name.mangled).html" name
  // 647:       TD "&nbsp;as&nbsp;"
  // 648:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_293(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: ... function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__37_294;
}
static void cont__37_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 650: ... :
  // 651:   $polymorphic_function_name function_name .behind. '/'
  // 652:   H2 "Implements"
  // 653:   A "href" = "@(polymorphic_function_name.mangled).html"
  // 654:     polymorphic_function_name
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_295, 0);
  // 650: if function_name .contains. '/':
  // 651:   $polymorphic_function_name function_name .behind. '/'
  // 652:   H2 "Implements"
  // 653:   A "href" = "@(polymorphic_function_name.mangled).html"
  // 654:     polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_302;
}
static void entry__37_295(void) {
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
  // 651: $polymorphic_function_name function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__37_296;
}
static void cont__37_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* polymorphic_function_name */, arguments->slots[0]);
  // 652: H2 "Implements"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_297;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_298;
}
static void cont__37_298(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 653: ... polymorphic_function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* polymorphic_function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_299;
}
static void cont__37_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 653: ... "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_300;
}
static void cont__37_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 653: ... "href" = "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_301;
}
static void cont__37_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 653: A "href" = "@(polymorphic_function_name.mangled).html"
  // 654:   polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* polymorphic_function_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_302(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 656: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__37_303;
}
static void cont__37_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 656: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__37_304;
}
static void cont__37_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 656: ... :
  // 657:   H2 "Supported Polymorphic Functions"
  // 658:   TABLE:
  // 659:     for_each methods_of(info): (method_name _method_info)
  // 660:       TR:
  // 661:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:         TD "&nbsp;"
  // 663:         TD:
  // 664:           A
  // 665:             =
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__37_305, 0);
  // 656: if kind_of(info) == INLINE_C_TYPE:
  // 657:   H2 "Supported Polymorphic Functions"
  // 658:   TABLE:
  // 659:     for_each methods_of(info): (method_name _method_info)
  // 660:       TR:
  // 661:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:         TD "&nbsp;"
  // 663:         TD:
  // 664:           A
  // 665:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_323;
}
static void entry__37_318(void) {
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
  // 667: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_319;
}
static void cont__37_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 667: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_320;
}
static void cont__37_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 667: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__29_3;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_321;
}
static void cont__37_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 665: =
  // 666:   "href"
  // 667:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_322;
}
static void cont__37_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 664: A
  // 665:   =
  // 666:     "href"
  // 667:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:   function_name
  // 669:   '/'
  // 670:   method_name
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
static void entry__37_311(void) {
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
  // 661: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_312, 0);
  // 661: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_316;
}
static void entry__37_312(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 661: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_313;
}
static void cont__37_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 661: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_314;
}
static void cont__37_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 661: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_315;
}
static void cont__37_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 661: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_316(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 662: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__37_317;
}
static void cont__37_317(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: ... :
  // 664:   A
  // 665:     =
  // 666:       "href"
  // 667:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:     function_name
  // 669:     '/'
  // 670:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_318, 0);
  // 663: TD:
  // 664:   A
  // 665:     =
  // 666:       "href"
  // 667:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:     function_name
  // 669:     '/'
  // 670:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_310(void) {
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
  // 660: ... :
  // 661:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:   TD "&nbsp;"
  // 663:   TD:
  // 664:     A
  // 665:       =
  // 666:         "href"
  // 667:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:       function_name
  // 669:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__37_311, 0);
  // 660: TR:
  // 661:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:   TD "&nbsp;"
  // 663:   TD:
  // 664:     A
  // 665:       =
  // 666:         "href"
  // 667:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:       function_name
  // 669:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_308(void) {
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
  // 659: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__37_309;
}
static void cont__37_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 659: ... : (method_name _method_info)
  // 660:   TR:
  // 661:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:     TD "&nbsp;"
  // 663:     TD:
  // 664:       A
  // 665:         =
  // 666:           "href"
  // 667:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__37_310, 2);
  // 659: for_each methods_of(info): (method_name _method_info)
  // 660:   TR:
  // 661:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:     TD "&nbsp;"
  // 663:     TD:
  // 664:       A
  // 665:         =
  // 666:           "href"
  // 667:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 668:         function_name
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
static void entry__37_305(void) {
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
  // 657: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_306;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_307;
}
static void cont__37_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 658: ... :
  // 659:   for_each methods_of(info): (method_name _method_info)
  // 660:     TR:
  // 661:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:       TD "&nbsp;"
  // 663:       TD:
  // 664:         A
  // 665:           =
  // 666:             "href"
  // 667:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_308, 0);
  // 658: TABLE:
  // 659:   for_each methods_of(info): (method_name _method_info)
  // 660:     TR:
  // 661:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 662:       TD "&nbsp;"
  // 663:       TD:
  // 664:         A
  // 665:           =
  // 666:             "href"
  // 667:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_323(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 673: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__37_324;
}
static void cont__37_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 672: $function_basename
  // 673:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__37_325;
}
static void cont__37_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* function_basename */, arguments->slots[0]);
  // 675: ... topic_list.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* topic_list */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__37_326;
}
static void cont__37_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 675: ... :
  // 676:   H2 "Topics"
  // 677:   TABLE:
  // 678:     for_each topic_list: (topic)
  // 679:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 680:       TR: TD: A "href" = filename topic
  frame->slots[14] /* temp__2 */ = create_closure(entry__37_327, 0);
  // 675: unless topic_list.is_empty:
  // 676:   H2 "Topics"
  // 677:   TABLE:
  // 678:     for_each topic_list: (topic)
  // 679:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 680:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__37_340;
}
static void entry__37_338(void) {
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
  // 680: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_339;
}
static void cont__37_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 680: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_337(void) {
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
  // 680: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_338, 0);
  // 680: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_331(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // topic: 0
  // filename: 1
  frame->slots[1] /* filename */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 679: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__37_332;
}
static void cont__37_332(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 679: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__37_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_334;
}
static void cont__37_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 679: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__37_335;
}
static void cont__37_335(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 679: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_336;
}
static void cont__37_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* filename */, arguments->slots[0]);
  // 680: ... : TD: A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__37_337, 0);
  // 680: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_330(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: for_each topic_list: (topic)
  // 679:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 680:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic_list */;
  arguments->slots[1] = func__37_331;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_327(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 676: H2 "Topics"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_328;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_329;
}
static void cont__37_329(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... :
  // 678:   for_each topic_list: (topic)
  // 679:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 680:     TR: TD: A "href" = filename topic
  frame->slots[1] /* temp__1 */ = create_closure(entry__37_330, 0);
  // 677: TABLE:
  // 678:   for_each topic_list: (topic)
  // 679:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 680:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_340(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 682: ... : (example)
  // 683:   $title key_of(example)
  // 684:   $text std::value_of(example)
  // 685:   H2 title
  // 686:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 687:     PRE
  // 688:       replace_all
  // 689:         text
  // 690:         =
  // 691:           sequence
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__37_341, 1);
  // 682: for_each examples: (example)
  // 683:   $title key_of(example)
  // 684:   $text std::value_of(example)
  // 685:   H2 title
  // 686:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 687:     PRE
  // 688:       replace_all
  // 689:         text
  // 690:         =
  // 691:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* examples */;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__37_360;
}
static void entry__37_349(void) {
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
  // 693: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__37_350;
}
static void cont__37_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 693: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__37_351;
}
static void cont__37_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 693: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__37_352;
}
static void cont__37_352(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 691: sequence
  // 692:   '@quot;'
  // 693:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__37_353;
}
static void cont__37_353(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 690: =
  // 691:   sequence
  // 692:     '@quot;'
  // 693:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:     '@quot;'
  // 695:   : (string_literal)
  // 696:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__37_354;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_355;
}
static void entry__37_354(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 696: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__37_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 697: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__37_356;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__37_356;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__37_357;
}
static void cont__37_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 697: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_358;
}
static void cont__37_358(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 688: replace_all
  // 689:   text
  // 690:   =
  // 691:     sequence
  // 692:       '@quot;'
  // 693:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:       '@quot;'
  // 695:     : (string_literal)
  // 696:       -> string_literal
  // 697:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__37_359;
}
static void cont__37_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 687: PRE
  // 688:   replace_all
  // 689:     text
  // 690:     =
  // 691:       sequence
  // 692:         '@quot;'
  // 693:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:         '@quot;'
  // 695:       : (string_literal)
  // 696:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_341(void) {
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
  // 683: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__37_342;
}
static void cont__37_342(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 684: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__37_343;
}
static void cont__37_343(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 685: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__37_344;
}
static void cont__37_344(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 686: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__37_345;
}
static void cont__37_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 686: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__37_346;
}
static void cont__37_346(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 686: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37_347;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_348;
}
static void cont__37_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 686: ... :
  // 687:   PRE
  // 688:     replace_all
  // 689:       text
  // 690:       =
  // 691:         sequence
  // 692:           '@quot;'
  // 693:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:           '@quot;'
  // 695:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__37_349, 0);
  // 686: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 687:   PRE
  // 688:     replace_all
  // 689:       text
  // 690:       =
  // 691:         sequence
  // 692:           '@quot;'
  // 693:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 694:           '@quot;'
  // 695:         : (string_literal)
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
static void cont__37_360(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 699: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37_347;
  arguments->slots[1] = string__37_361;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__37_362;
}
static void cont__37_362(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 700: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__37_363;
}
static void cont__37_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 700: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__37_364;
}
static void cont__37_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 700: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__37_365;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  arguments->slots[2] = string__37_366;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_367;
}
static void cont__37_367(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 698: DIV
  // 699:   "class" = "footer"
  // 700:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__37_15(void) {
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
  // 450: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__37_16;
}
static void cont__37_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 450: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__37_17;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_19;
}
static void cont__37_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 450: ... :
  // 451:   link_bar
  // 452:   if
  // 453:     function_name .contains. '/':
  // 454:       $type function_name .before. '/'
  // 455:       $method function_name .behind. '/'
  // 456:       H1
  // 457:         string
  // 458:           '['
  // 459:           type
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_20, 0);
  // 450: create_page "html/@(function_name.mangled).html":
  // 451:   link_bar
  // 452:   if
  // 453:     function_name .contains. '/':
  // 454:       $type function_name .before. '/'
  // 455:       $method function_name .behind. '/'
  // 456:       H1
  // 457:         string
  // 458:           '['
  // 459:           type
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
static void entry__37_1_create_info_page(void) {
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
  // 441: ... : (&reference)
  // 442:   resolve_reference &reference
  // 443:   if short_descriptions(reference).is_undefined:
  // 444:     Error "
  // 445:       The documentation for "@(function_name)"
  // 446:       (defined in "@(filename_of(info))")
  // 447:       references the undefined symbol "@(reference)"!
  frame->slots[3] /* temp__1 */ = create_closure(entry__37_2_resolve_and_check_reference, 1);
  // 441: $resolve_and_check_reference: (&reference)
  // 442:   resolve_reference &reference
  // 443:   if short_descriptions(reference).is_undefined:
  // 444:     Error "
  // 445:       The documentation for "@(function_name)"
  // 446:       (defined in "@(filename_of(info))")
  // 447:       references the undefined symbol "@(reference)"!
  initialize_future(frame->slots[2] /* resolve_and_check_reference */, frame->slots[3] /* temp__1 */);
  // 449: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__37_14;
}
static void entry__37_2_resolve_and_check_reference(void) {
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
  // 442: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__37_3;
}
static void cont__37_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 443: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__37_4;
}
static void cont__37_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 443: ... short_descriptions(reference).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__37_5;
}
static void cont__37_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 443: ... :
  // 444:   Error "
  // 445:     The documentation for "@(function_name)"
  // 446:     (defined in "@(filename_of(info))")
  // 447:     references the undefined symbol "@(reference)"!
  frame->slots[5] /* temp__3 */ = create_closure(entry__37_6, 0);
  // 443: if short_descriptions(reference).is_undefined:
  // 444:   Error "
  // 445:     The documentation for "@(function_name)"
  // 446:     (defined in "@(filename_of(info))")
  // 447:     references the undefined symbol "@(reference)"!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__37_13;
}
static void entry__37_6(void) {
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
  // 446: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__37_7;
}
static void cont__37_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 444: ... "
  // 445:   The documentation for "@(function_name)"
  // 446:   (defined in "@(filename_of(info))")
  // 447:   references the undefined symbol "@(reference)"!
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__37_8;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__37_9;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__37_10;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* reference */;
  arguments->slots[6] = string__37_11;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__37_12;
}
static void cont__37_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 444: Error "
  // 445:   The documentation for "@(function_name)"
  // 446:   (defined in "@(filename_of(info))")
  // 447:   references the undefined symbol "@(reference)"!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__37_13(void) {
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
static void cont__37_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 449: ... :
  // 450:   create_page "html/@(function_name.mangled).html":
  // 451:     link_bar
  // 452:     if
  // 453:       function_name .contains. '/':
  // 454:         $type function_name .before. '/'
  // 455:         $method function_name .behind. '/'
  // 456:         H1
  // 457:           string
  // 458:             '['
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__37_15, 0);
  // 449: if function_name.is_defined:
  // 450:   create_page "html/@(function_name.mangled).html":
  // 451:     link_bar
  // 452:     if
  // 453:       function_name .contains. '/':
  // 454:         $type function_name .before. '/'
  // 455:         $method function_name .behind. '/'
  // 456:         H1
  // 457:           string
  // 458:             '['
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
static void entry__38_1_get_short_description(void) {
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
  // 703: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__38_2;
}
static void cont__38_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* remark_lines */, arguments->slots[0]);
  // 704: $$short_description ""
  ((CELL *)frame->slots[3])->contents /* short_description */ = empty_string;
  // 705: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__38_3;
}
static void cont__38_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 705: ... not(remark_lines.is_empty)
  frame->slots[6] /* temp__3 */ = create_closure(entry__38_4, 0);
  // 705: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_7;
}
static void entry__38_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 705: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__38_5;
}
static void cont__38_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 705: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__38_6;
}
static void cont__38_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 705: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 705: ... :
  // 706:   do: (-> break) for_each remark_lines: (line)
  // 707:     if line == "" && short_description != "" break
  // 708:     append &short_description line.trim
  // 709:   if do_print_warnings && length_of(short_description) > 80:
  // 710:     ewrite "
  // 711:       
  // 712:       The short description for "@(name)"
  // 713:       (defined in "@(filename_of(info))")
  // 714:       is quite long:
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__38_8, 0);
  // 705: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 706:   do: (-> break) for_each remark_lines: (line)
  // 707:     if line == "" && short_description != "" break
  // 708:     append &short_description line.trim
  // 709:   if do_print_warnings && length_of(short_description) > 80:
  // 710:     ewrite "
  // 711:       
  // 712:       The short description for "@(name)"
  // 713:       (defined in "@(filename_of(info))")
  // 714:       is quite long:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_30;
}
static void entry__38_25(void) {
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
  // 713: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__38_26;
}
static void cont__38_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 710: ... "
  // 711:   
  // 712:   The short description for "@(name)"
  // 713:   (defined in "@(filename_of(info))")
  // 714:   is quite long:
  // 715:   @(short_description)
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__38_27;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__37_9;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__38_28;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* short_description */;
  arguments->slots[6] = string__25_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__38_29;
}
static void cont__38_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 710: ewrite "
  // 711:   
  // 712:   The short description for "@(name)"
  // 713:   (defined in "@(filename_of(info))")
  // 714:   is quite long:
  // 715:   @(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__38_8(void) {
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
  // 706: ... : (-> break) for_each remark_lines: (line)
  // 707:   if line == "" && short_description != "" break
  // 708:   append &short_description line.trim
  frame->slots[4] /* temp__1 */ = create_closure(entry__38_9, 0);
  // 706: do: (-> break) for_each remark_lines: (line)
  // 707:   if line == "" && short_description != "" break
  // 708:   append &short_description line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__38_20;
}
static void entry__38_9(void) {
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
  // 706: ... : (line)
  // 707:   if line == "" && short_description != "" break
  // 708:   append &short_description line.trim
  frame->slots[3] /* temp__1 */ = create_closure(entry__38_10, 1);
  // 706: ... for_each remark_lines: (line)
  // 707:   if line == "" && short_description != "" break
  // 708:   append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__38_19;
}
static void entry__38_10(void) {
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
  // 707: ... line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_11;
}
static void cont__38_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 707: ... short_description != ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__38_12, 0);
  // 707: ... line == "" && short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_15;
}
static void entry__38_12(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: ... short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__38_13;
}
static void cont__38_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 707: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__38_14;
}
static void cont__38_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 707: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 707: if line == "" && short_description != "" break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__38_16;
}
static void cont__38_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__38_17;
}
static void cont__38_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 708: append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__38_18;
}
static void cont__38_18(void) {
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
static void cont__38_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__38_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 709: ... length_of(short_description) > 80
  frame->slots[5] /* temp__2 */ = create_closure(entry__38_21, 0);
  // 709: ... do_print_warnings && length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__38_24;
}
static void entry__38_21(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 709: ... length_of(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__38_22;
}
static void cont__38_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 709: ... length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__38_23;
}
static void cont__38_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 709: ... length_of(short_description) > 80
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__38_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 709: ... :
  // 710:   ewrite "
  // 711:     
  // 712:     The short description for "@(name)"
  // 713:     (defined in "@(filename_of(info))")
  // 714:     is quite long:
  // 715:     @(short_description)
  frame->slots[6] /* temp__3 */ = create_closure(entry__38_25, 0);
  // 709: if do_print_warnings && length_of(short_description) > 80:
  // 710:   ewrite "
  // 711:     
  // 712:     The short description for "@(name)"
  // 713:     (defined in "@(filename_of(info))")
  // 714:     is quite long:
  // 715:     @(short_description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__38_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 716: add_links &short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = var._add_links;
  func = myself->type;
  frame->cont = cont__38_31;
}
static void cont__38_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* short_description */ = arguments->slots[0];
  // 717: -> short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_240(void) {
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
  // 856: $$total_functions 0
  ((CELL *)frame->slots[0])->contents /* total_functions */ = number__0;
  // 857: $$total_polymorphic_functions 0
  ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */ = number__0;
  // 858: $$total_polymorphic_attributes 0
  ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */ = number__0;
  // 859: $$total_methods 0
  ((CELL *)frame->slots[3])->contents /* total_methods */ = number__0;
  // 860: $$total_inline_c_methods 0
  ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */ = number__0;
  // 861: $$total_inline_c_types 0
  ((CELL *)frame->slots[5])->contents /* total_inline_c_types */ = number__0;
  // 862: $$total_inline_c_objects 0
  ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */ = number__0;
  // 863: $$total_attributes 0
  ((CELL *)frame->slots[7])->contents /* total_attributes */ = number__0;
  // 864: $$total_inline_c_functions 0
  ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */ = number__0;
  // 865: $$total_unique_items 0
  ((CELL *)frame->slots[9])->contents /* total_unique_items */ = number__0;
  // 866: $$total_constants 0
  ((CELL *)frame->slots[10])->contents /* total_constants */ = number__0;
  // 867: $$other 0
  ((CELL *)frame->slots[11])->contents /* other */ = number__0;
  // 869: ... : (_iname info)
  // 870:   case kind_of(info)
  // 871:     FUNCTION: inc &total_functions
  // 872:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 873:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 874:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 875:     INLINE_C_TYPE: inc &total_inline_c_types
  // 876:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 877:     UNIQUE_ITEM: inc &total_unique_items
  // 878:     CONSTANT: inc &total_constants
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__39_241, 2);
  // 869: for_each definitions: (_iname info)
  // 870:   case kind_of(info)
  // 871:     FUNCTION: inc &total_functions
  // 872:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 873:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 874:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 875:     INLINE_C_TYPE: inc &total_inline_c_types
  // 876:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 877:     UNIQUE_ITEM: inc &total_unique_items
  // 878:     CONSTANT: inc &total_constants
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_273;
}
static void entry__39_267(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_methods: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 883: ... inc &total_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_268;
}
static void cont__39_268(void) {
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
static void entry__39_269(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_methods: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_inline_c_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 884: ... inc &total_inline_c_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_270;
}
static void cont__39_270(void) {
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
static void entry__39_271(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 885: ... inc &total_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_272;
}
static void cont__39_272(void) {
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
static void entry__39_265(void) {
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
  // 882: ... kind_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_266;
}
static void cont__39_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 883: ... : inc &total_methods
  frame->slots[6] /* temp__2 */ = create_closure(entry__39_267, 0);
  // 884: ... : inc &total_inline_c_methods
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_269, 0);
  // 885: : inc &total_attributes
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_271, 0);
  // 882: case kind_of(method_info)
  // 883:   FUNCTION: inc &total_methods
  // 884:   INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 885:   : inc &total_attributes
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
static void entry__39_263(void) {
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
  // 881: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__39_264;
}
static void cont__39_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 881: ... : (method_name method_info)
  // 882:   case kind_of(method_info)
  // 883:     FUNCTION: inc &total_methods
  // 884:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 885:     : inc &total_attributes
  frame->slots[5] /* temp__2 */ = create_closure(entry__39_265, 2);
  // 881: for_each methods_of(info): (method_name method_info)
  // 882:   case kind_of(method_info)
  // 883:     FUNCTION: inc &total_methods
  // 884:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 885:     : inc &total_attributes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_241(void) {
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
  // 870: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_242;
}
static void cont__39_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 871: ... : inc &total_functions
  frame->slots[15] /* temp__2 */ = create_closure(entry__39_243, 0);
  // 872: ... : inc &total_polymorphic_functions
  frame->slots[16] /* temp__3 */ = create_closure(entry__39_245, 0);
  // 873: ... : inc &total_polymorphic_attributes
  frame->slots[17] /* temp__4 */ = create_closure(entry__39_247, 0);
  // 874: ... : inc &total_inline_c_functions
  frame->slots[18] /* temp__5 */ = create_closure(entry__39_249, 0);
  // 875: ... : inc &total_inline_c_types
  frame->slots[19] /* temp__6 */ = create_closure(entry__39_251, 0);
  // 876: ... : inc &total_inline_c_objects
  frame->slots[20] /* temp__7 */ = create_closure(entry__39_253, 0);
  // 877: ... : inc &total_unique_items
  frame->slots[21] /* temp__8 */ = create_closure(entry__39_255, 0);
  // 878: ... : inc &total_constants
  frame->slots[22] /* temp__9 */ = create_closure(entry__39_257, 0);
  // 879: : inc &other
  frame->slots[23] /* temp__10 */ = create_closure(entry__39_259, 0);
  // 870: case kind_of(info)
  // 871:   FUNCTION: inc &total_functions
  // 872:   POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 873:   POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 874:   INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 875:   INLINE_C_TYPE: inc &total_inline_c_types
  // 876:   INLINE_C_OBJECT: inc &total_inline_c_objects
  // 877:   UNIQUE_ITEM: inc &total_unique_items
  // 878:   CONSTANT: inc &total_constants
  // 879:   : inc &other
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
  frame->cont = cont__39_261;
}
static void entry__39_243(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_functions: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 871: ... inc &total_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_244;
}
static void cont__39_244(void) {
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
static void entry__39_245(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_functions: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_polymorphic_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 872: ... inc &total_polymorphic_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_246;
}
static void cont__39_246(void) {
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
static void entry__39_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_polymorphic_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 873: ... inc &total_polymorphic_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_248;
}
static void cont__39_248(void) {
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
static void entry__39_249(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_functions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* total_inline_c_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 874: ... inc &total_inline_c_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_250;
}
static void cont__39_250(void) {
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
static void entry__39_251(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_types: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* total_inline_c_types */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 875: ... inc &total_inline_c_types
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_252;
}
static void cont__39_252(void) {
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
static void entry__39_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_objects: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* total_inline_c_objects */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 876: ... inc &total_inline_c_objects
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_254;
}
static void cont__39_254(void) {
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
static void entry__39_255(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_unique_items: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* total_unique_items */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... inc &total_unique_items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_256;
}
static void cont__39_256(void) {
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
static void entry__39_257(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_constants: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* total_constants */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 878: ... inc &total_constants
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_constants */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_258;
}
static void cont__39_258(void) {
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
static void entry__39_259(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // other: 0
  frame->slots[0] = myself->closure.frame->slots[10]; /* other */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 879: ... inc &other
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* other */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__39_260;
}
static void cont__39_260(void) {
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
static void cont__39_261(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 880: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_262;
}
static void cont__39_262(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 880: ... :
  // 881:   for_each methods_of(info): (method_name method_info)
  // 882:     case kind_of(method_info)
  // 883:       FUNCTION: inc &total_methods
  // 884:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 885:       : inc &total_attributes
  frame->slots[15] /* temp__2 */ = create_closure(entry__39_263, 0);
  // 880: case kind_of(info) INLINE_C_TYPE:
  // 881:   for_each methods_of(info): (method_name method_info)
  // 882:     case kind_of(method_info)
  // 883:       FUNCTION: inc &total_methods
  // 884:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 885:       : inc &total_attributes
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
static void cont__39_273(void) {
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
  frame->cont = cont__39_274;
}
static void cont__39_274(void) {
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
  frame->cont = cont__39_275;
}
static void cont__39_275(void) {
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
  frame->cont = cont__39_276;
}
static void cont__39_276(void) {
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
  frame->cont = cont__39_277;
}
static void cont__39_277(void) {
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
  frame->cont = cont__39_278;
}
static void cont__39_278(void) {
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
  frame->cont = cont__39_279;
}
static void cont__39_279(void) {
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
  frame->cont = cont__39_280;
}
static void cont__39_280(void) {
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
  frame->cont = cont__39_281;
}
static void cont__39_281(void) {
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
  frame->cont = cont__39_282;
}
static void cont__39_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 887: $total_definitions
  // 888:   +
  // 889:     total_functions
  // 890:     total_polymorphic_functions
  // 891:     total_polymorphic_attributes
  // 892:     total_methods
  // 893:     total_inline_c_methods
  // 894:     total_inline_c_types
  // 895:     total_inline_c_objects
  // 896:     total_attributes
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__39_283;
}
static void cont__39_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* total_definitions */, arguments->slots[0]);
  // 902: ... pad_left(total_definitions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* total_definitions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_284;
}
static void cont__39_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 904: ... pad_left(total_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_285;
}
static void cont__39_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 905: ... pad_left(total_polymorphic_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_286;
}
static void cont__39_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 906: ... pad_left(total_polymorphic_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_287;
}
static void cont__39_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  // 907: ... pad_left(total_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_288;
}
static void cont__39_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  // 908: ... pad_left(total_inline_c_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_289;
}
static void cont__39_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  // 909: ... pad_left(total_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_290;
}
static void cont__39_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  // 910: ... pad_left(total_inline_c_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_291;
}
static void cont__39_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  // 911: ... pad_left(total_inline_c_types 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_292;
}
static void cont__39_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__10 */ = arguments->slots[0];
  // 912: ... pad_left(total_inline_c_objects 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_293;
}
static void cont__39_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__11 */ = arguments->slots[0];
  // 913: ... pad_left(total_unique_items 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_294;
}
static void cont__39_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__12 */ = arguments->slots[0];
  // 914: ... pad_left(total_constants 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_295;
}
static void cont__39_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__13 */ = arguments->slots[0];
  // 915: ... pad_left(other 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* other */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_296;
}
static void cont__39_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__14 */ = arguments->slots[0];
  // 917: ... pad_left(missing_documentation_count 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__39_297;
}
static void cont__39_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__15 */ = arguments->slots[0];
  // 901: ... "
  // 902:   total definitions:     @(pad_left(total_definitions 5))
  // 903:   
  // 904:   functions:             @(pad_left(total_functions 5))
  // 905:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 906:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 907:   method definitions:    @(pad_left(total_methods 5))
  // 908:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 909:   attribute definitions: @(pad_left(total_attributes 5))
  // 910:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 29;
  arguments = node_p;
  arguments->slots[0] = string__39_298;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = string__39_299;
  arguments->slots[3] = frame->slots[15] /* temp__3 */;
  arguments->slots[4] = string__39_300;
  arguments->slots[5] = frame->slots[16] /* temp__4 */;
  arguments->slots[6] = string__39_301;
  arguments->slots[7] = frame->slots[17] /* temp__5 */;
  arguments->slots[8] = string__39_302;
  arguments->slots[9] = frame->slots[18] /* temp__6 */;
  arguments->slots[10] = string__39_303;
  arguments->slots[11] = frame->slots[19] /* temp__7 */;
  arguments->slots[12] = string__39_304;
  arguments->slots[13] = frame->slots[20] /* temp__8 */;
  arguments->slots[14] = string__39_305;
  arguments->slots[15] = frame->slots[21] /* temp__9 */;
  arguments->slots[16] = string__39_306;
  arguments->slots[17] = frame->slots[22] /* temp__10 */;
  arguments->slots[18] = string__39_307;
  arguments->slots[19] = frame->slots[23] /* temp__11 */;
  arguments->slots[20] = string__39_308;
  arguments->slots[21] = frame->slots[24] /* temp__12 */;
  arguments->slots[22] = string__39_309;
  arguments->slots[23] = frame->slots[25] /* temp__13 */;
  arguments->slots[24] = string__39_310;
  arguments->slots[25] = frame->slots[26] /* temp__14 */;
  arguments->slots[26] = string__39_311;
  arguments->slots[27] = frame->slots[27] /* temp__15 */;
  arguments->slots[28] = string__25_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__39_312;
}
static void cont__39_312(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 901: ewrite "
  // 902:   total definitions:     @(pad_left(total_definitions 5))
  // 903:   
  // 904:   functions:             @(pad_left(total_functions 5))
  // 905:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 906:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 907:   method definitions:    @(pad_left(total_methods 5))
  // 908:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 909:   attribute definitions: @(pad_left(total_attributes 5))
  // 910:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_1_sim2c__extract_documentation(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 721: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__39_2;
}
static void cont__39_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 721: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__39_3;
}
static void cont__39_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 722: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__39_4;
}
static void cont__39_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: for_each definitions: (iname info)
  // 725:   $name name_of(info)
  // 726:   !short_descriptions(name) get_short_description(name info)
  // 727:   
  // 728:   if kind_of(info) == INLINE_C_TYPE:
  // 729:     $base base_of(info)
  // 730:     if base.is_defined: add_derived_type base iname
  // 731:     $$methods empty_key_order_table
  // 732:     for_each methods_of(info): ($method_name method_info)
  // 733:       unless method_name .contains. "::":
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__39_5;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_38;
}
static void entry__39_11(void) {
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
  // 729: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__39_12;
}
static void cont__39_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base */, arguments->slots[0]);
  // 730: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_13;
}
static void cont__39_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 730: ... : add_derived_type base iname
  frame->slots[6] /* temp__2 */ = create_closure(entry__39_14, 0);
  // 730: if base.is_defined: add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_15;
}
static void entry__39_14(void) {
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
  // 730: ... add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* iname */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 731: $$methods empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* methods */ = get__empty_key_order_table();
  // 732: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__39_16;
}
static void cont__39_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 732: ... : ($method_name method_info)
  // 733:   unless method_name .contains. "::":
  // 734:     !method_name attribute_of(method_info).resolved_name
  // 735:   $sd_name string(name "/" method_name)
  // 736:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 737:   $oname
  // 738:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 739:   !definitions(oname).types_of(name) true
  // 740:   !methods(method_name) method_info
  frame->slots[6] /* temp__2 */ = create_closure(entry__39_17, 2);
  // 732: for_each methods_of(info): ($method_name method_info)
  // 733:   unless method_name .contains. "::":
  // 734:     !method_name attribute_of(method_info).resolved_name
  // 735:   $sd_name string(name "/" method_name)
  // 736:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 737:   $oname
  // 738:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 739:   !definitions(oname).types_of(name) true
  // 740:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_35;
}
static void entry__39_17(void) {
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
  // 733: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__39_18;
}
static void cont__39_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 733: ... :
  // 734:   !method_name attribute_of(method_info).resolved_name
  frame->slots[7] /* temp__2 */ = create_closure(entry__39_19, 0);
  // 733: unless method_name .contains. "::":
  // 734:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__39_22;
}
static void entry__39_19(void) {
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
  // 734: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__39_20;
}
static void cont__39_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 734: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__39_21;
}
static void cont__39_21(void) {
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
static void cont__39_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 735: $sd_name string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__39_23;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__39_24;
}
static void cont__39_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* sd_name */, arguments->slots[0]);
  // 736: !short_descriptions(sd_name) get_short_description(sd_name method_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__39_25;
}
static void cont__39_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 736: !short_descriptions(sd_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__39_26;
}
static void cont__39_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 738: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__39_27;
}
static void cont__39_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 738: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__39_28;
}
static void cont__39_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 737: $oname
  // 738:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__39_29;
}
static void cont__39_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* oname */, arguments->slots[0]);
  // 739: !definitions(oname).types_of(name) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 739: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__39_30;
}
static void cont__39_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 739: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__39_31;
}
static void cont__39_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 739: !definitions(oname).types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[8] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__39_32;
}
static void cont__39_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 739: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[7] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[8] /* temp__3 */);
    frame->slots[7] /* temp__2 */ = temp;

  }
  // 739: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__39_33;
}
static void cont__39_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 740: !methods(method_name) method_info
  frame->slots[6] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 740: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__39_34;
}
static void cont__39_34(void) {
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
static void cont__39_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 741: !definitions(iname).methods_of methods
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* methods */;
  // 741: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__39_36;
}
static void cont__39_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 741: !definitions(iname).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[5] /* temp__1 */);
    frame->slots[6] /* temp__2 */ = temp;

  }
  // 741: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__39_37;
}
static void cont__39_37(void) {
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
static void entry__39_5(void) {
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
  // 725: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__39_6;
}
static void cont__39_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 726: !short_descriptions(name) get_short_description(name info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__39_7;
}
static void cont__39_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 726: !short_descriptions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__39_8;
}
static void cont__39_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 728: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_9;
}
static void cont__39_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 728: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__39_10;
}
static void cont__39_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 728: ... :
  // 729:   $base base_of(info)
  // 730:   if base.is_defined: add_derived_type base iname
  // 731:   $$methods empty_key_order_table
  // 732:   for_each methods_of(info): ($method_name method_info)
  // 733:     unless method_name .contains. "::":
  // 734:       !method_name attribute_of(method_info).resolved_name
  // 735:     $sd_name string(name "/" method_name)
  // 736:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 737:     $oname
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__39_11, 0);
  // 728: if kind_of(info) == INLINE_C_TYPE:
  // 729:   $base base_of(info)
  // 730:   if base.is_defined: add_derived_type base iname
  // 731:   $$methods empty_key_order_table
  // 732:   for_each methods_of(info): ($method_name method_info)
  // 733:     unless method_name .contains. "::":
  // 734:       !method_name attribute_of(method_info).resolved_name
  // 735:     $sd_name string(name "/" method_name)
  // 736:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 737:     $oname
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
static void cont__39_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: create_page "html/type_index.html":
  // 744:   $print_type_info:
  // 745:     (
  // 746:       info
  // 747:       indent = 0
  // 748:     )
  // 749:     TR:
  // 750:       $qname name_of(info)
  // 751:       $remark_lines remark_lines_of(info)
  // 752:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_39;
  arguments->slots[1] = func__39_40;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__39_78;
}
static void entry__39_77(void) {
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
  // 766: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_70(void) {
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
  // 765: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_71;
}
static void cont__39_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 765: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__39_72;
}
static void cont__39_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 765: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__39_73, 0);
  // 765: ... kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__39_76;
}
static void entry__39_73(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__39_74;
}
static void cont__39_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 765: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__39_75;
}
static void cont__39_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 765: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 765: ... :
  // 766:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__39_77, 0);
  // 765: if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 766:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_69(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 764: ... : (_base info)
  // 765:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 766:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_70, 2);
  // 764: for_each definitions: (_base info)
  // 765:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 766:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_40(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... :
  // 745:   (
  // 746:     info
  // 747:     indent = 0
  // 748:   )
  // 749:   TR:
  // 750:     $qname name_of(info)
  // 751:     $remark_lines remark_lines_of(info)
  // 752:     if qname.is_defined:
  // 753:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_41_print_type_info, -1);
  // 744: $print_type_info:
  // 745:   (
  // 746:     info
  // 747:     indent = 0
  // 748:   )
  // 749:   TR:
  // 750:     $qname name_of(info)
  // 751:     $remark_lines remark_lines_of(info)
  // 752:     if qname.is_defined:
  // 753:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 761: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__39_67;
}
static void entry__39_64(void) {
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
  // 759: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__39_65;
}
static void cont__39_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 759: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__39_66;
}
static void cont__39_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 759: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_42(void) {
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
  // 750: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__39_43;
}
static void cont__39_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 751: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__39_44;
}
static void cont__39_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 752: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_45;
}
static void cont__39_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 752: ... :
  // 753:   TD:
  // 754:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__39_46, 0);
  // 752: if qname.is_defined:
  // 753:   TD:
  // 754:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_53;
}
static void entry__39_47(void) {
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
  // 754: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_8;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__39_48;
}
static void cont__39_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 754: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__39_49;
}
static void cont__39_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 755: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__39_50;
}
static void cont__39_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 755: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__39_51;
}
static void cont__39_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 755: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_52;
}
static void cont__39_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 755: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_46(void) {
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
  // 753: ... :
  // 754:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_47, 0);
  // 753: TD:
  // 754:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 756: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_54;
}
static void cont__39_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 756: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__39_55, 0);
  // 756: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__39_58;
}
static void entry__39_55(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 756: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__39_56;
}
static void cont__39_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 756: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__39_57;
}
static void cont__39_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 756: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 756: ... :
  // 757:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__39_59, 0);
  // 756: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 757:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_62;
}
static void entry__39_59(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 757: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__39_60;
}
static void cont__39_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 757: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__39_61;
}
static void cont__39_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 757: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_62(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 758: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__39_63;
}
static void cont__39_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 758: ... : (name)
  // 759:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__39_64, 1);
  // 758: for_each derived_types_of(info): (name)
  // 759:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_41_print_type_info(void) {
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
  // 749: ... :
  // 750:   $qname name_of(info)
  // 751:   $remark_lines remark_lines_of(info)
  // 752:   if qname.is_defined:
  // 753:     TD:
  // 754:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:       A "href" = "@(qname.mangled).html" qname
  // 756:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 757:     TD remark_lines.to_paragraphs(1)
  // 758:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_42, 0);
  // 749: TR:
  // 750:   $qname name_of(info)
  // 751:   $remark_lines remark_lines_of(info)
  // 752:   if qname.is_defined:
  // 753:     TD:
  // 754:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 755:       A "href" = "@(qname.mangled).html" qname
  // 756:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 757:     TD remark_lines.to_paragraphs(1)
  // 758:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__31_17;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__39_68;
}
static void cont__39_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: ... :
  // 764:   for_each definitions: (_base info)
  // 765:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 766:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_69, 0);
  // 763: TABLE:
  // 764:   for_each definitions: (_base info)
  // 765:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 766:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: create_page "html/symbol_index.html":
  // 769:   link_bar
  // 770:   H1 "id" = "index" "Symbol Index"
  // 771:   from_to
  // 772:     'a'
  // 773:     'z': (letter)
  // 774:       A "href" = "#@(letter)" letter.to_upper_case
  // 775:     :
  // 776:       TEXT " "
  // 777:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_79;
  arguments->slots[1] = func__39_80;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__39_173;
}
static void entry__39_159(void) {
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
  // 816: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_160;
  arguments->slots[1] = string__39_161;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_162;
}
static void cont__39_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 816: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__39_163;
}
static void cont__39_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 816: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__39_164;
}
static void cont__39_164(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 817: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_165, 0);
  // 817: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__39_170;
}
static void entry__39_165(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 817: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__39_166;
}
static void cont__39_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 817: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__39_167;
}
static void cont__39_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 817: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_168;
}
static void cont__39_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 817: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__27_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__39_169;
}
static void cont__39_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 817: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_170(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 818: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37_347;
  arguments->slots[1] = string__39_171;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_172;
}
static void cont__39_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 818: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_158(void) {
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
  // 815: ... :
  // 816:   TD "align" = "right" name .until. "::"
  // 817:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 818:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_159, 0);
  // 815: TR:
  // 816:   TD "align" = "right" name .until. "::"
  // 817:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 818:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_96(void) {
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
  // 781: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__39_97;
}
static void cont__39_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 781: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__39_98;
}
static void cont__39_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 781: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__39_99;
}
static void cont__39_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 781: ... :
  // 782:   !letter iname(1)
  // 783:   TR:
  // 784:     TD "colspan" = 3:
  // 785:       H2 "id" = letter:
  // 786:         TEXT letter.to_upper_case
  // 787:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__39_100, 0);
  // 781: if iname(1) != letter:
  // 782:   !letter iname(1)
  // 783:   TR:
  // 784:     TD "colspan" = 3:
  // 785:       H2 "id" = letter:
  // 786:         TEXT letter.to_upper_case
  // 787:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_113;
}
static void entry__39_107(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 786: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__39_108;
}
static void cont__39_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 786: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__39_109;
}
static void cont__39_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 787: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__39_110;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_111;
}
static void cont__39_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 787: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__39_112;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_105(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_82;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_106;
}
static void cont__39_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 785: ... :
  // 786:   TEXT letter.to_upper_case
  // 787:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__39_107, 0);
  // 785: H2 "id" = letter:
  // 786:   TEXT letter.to_upper_case
  // 787:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_102(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_103;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_104;
}
static void cont__39_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 784: ... :
  // 785:   H2 "id" = letter:
  // 786:     TEXT letter.to_upper_case
  // 787:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__39_105, 0);
  // 784: TD "colspan" = 3:
  // 785:   H2 "id" = letter:
  // 786:     TEXT letter.to_upper_case
  // 787:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_100(void) {
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
  // 782: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__39_101;
}
static void cont__39_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 783: ... :
  // 784:   TD "colspan" = 3:
  // 785:     H2 "id" = letter:
  // 786:       TEXT letter.to_upper_case
  // 787:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_102, 0);
  // 783: TR:
  // 784:   TD "colspan" = 3:
  // 785:     H2 "id" = letter:
  // 786:       TEXT letter.to_upper_case
  // 787:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 788: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 789: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__39_114;
}
static void cont__39_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 790: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__39_115;
}
static void cont__39_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 791: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_116;
}
static void cont__39_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 791: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__39_117, 0);
  // 791: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__39_120;
}
static void entry__39_117(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 791: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__39_118;
}
static void cont__39_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 791: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__39_119;
}
static void cont__39_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 791: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 791: ... :
  // 792:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__39_121, 0);
  // 791: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 792:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_124;
}
static void entry__39_121(void) {
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
  // 792: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__39_122;
}
static void cont__39_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 792: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__39_123;
}
static void cont__39_123(void) {
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
static void cont__39_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 796: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_125;
}
static void cont__39_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 794: $kind_info
  // 795:   case
  // 796:     kind_of(info)
  // 797:     FUNCTION -> "function"
  // 798:     POLYMORPHIC_FUNCTION -> "polymorphic function"
  // 799:     POLYMORPHIC_ATTRIBUTE -> "polymorphic attribute"
  // 800:     INLINE_C_TYPE -> "inline-C type"
  // 801:     INLINE_C_OBJECT -> "inline-C object"
  // 802:     INLINE_C_FUNCTION -> "inline-C function"
  // 803:     UNIQUE_ITEM -> "unique item"
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__39_126;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = func__39_128;
  arguments->slots[5] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[6] = func__39_130;
  arguments->slots[7] = var._INLINE_C_TYPE;
  arguments->slots[8] = func__39_132;
  arguments->slots[9] = var._INLINE_C_OBJECT;
  arguments->slots[10] = func__39_134;
  arguments->slots[11] = var._INLINE_C_FUNCTION;
  arguments->slots[12] = func__39_136;
  arguments->slots[13] = var._UNIQUE_ITEM;
  arguments->slots[14] = func__39_138;
  arguments->slots[15] = var._CONSTANT;
  arguments->slots[16] = func__39_140;
  arguments->slots[17] = var._OTHER;
  arguments->slots[18] = func__39_142;
  arguments->slots[19] = func__39_144;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__39_145;
}
static void entry__39_126(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 797: ... -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_127;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_128(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 798: ... -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_129;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_130(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 799: ... -> "polymorphic attribute"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_131;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_132(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 800: ... -> "inline-C type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_133;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_134(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 801: ... -> "inline-C object"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_135;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_136(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 802: ... -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_137;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_138(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 803: ... -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_139;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_140(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 804: ... -> "constant"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_141;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_142(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 805: ... -> "other"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_143;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_144(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 806: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 808: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_146;
}
static void cont__39_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 808: ... :
  // 809:   if
  // 810:     remark.is_defined:
  // 811:       !remark string(remark " (" kind_info ")")
  // 812:     :
  // 813:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__39_147, 0);
  // 808: if kind_info.is_defined:
  // 809:   if
  // 810:     remark.is_defined:
  // 811:       !remark string(remark " (" kind_info ")")
  // 812:     :
  // 813:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_153;
}
static void entry__39_149(void) {
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
  // 811: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__39_150;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__37_87;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__39_151;
}
static void cont__39_151(void) {
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
static void entry__39_152(void) {
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
  // 813: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__39_147(void) {
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
  // 810: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_148;
}
static void cont__39_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 810: ... :
  // 811:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__39_149, 0);
  // 812: :
  // 813:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__39_152, 0);
  // 809: if
  // 810:   remark.is_defined:
  // 811:     !remark string(remark " (" kind_info ")")
  // 812:   :
  // 813:     !remark kind_info
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
static void cont__39_153(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_154;
}
static void cont__39_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 814: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__39_155, 0);
  // 814: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__39_157;
}
static void entry__39_155(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 814: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_156;
}
static void cont__39_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 814: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__39_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 814: ... :
  // 815:   TR:
  // 816:     TD "align" = "right" name .until. "::"
  // 817:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 818:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__39_158, 0);
  // 814: if remark.is_defined && name.is_defined:
  // 815:   TR:
  // 816:     TD "align" = "right" name .until. "::"
  // 817:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 818:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_95(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 779: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 780: ... : (iname info)
  // 781:   if iname(1) != letter:
  // 782:     !letter iname(1)
  // 783:     TR:
  // 784:       TD "colspan" = 3:
  // 785:         H2 "id" = letter:
  // 786:           TEXT letter.to_upper_case
  // 787:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 788:   $$remark undefined
  // 789:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_96, 2);
  // 780: for_each definitions: (iname info)
  // 781:   if iname(1) != letter:
  // 782:     !letter iname(1)
  // 783:     TR:
  // 784:       TD "colspan" = 3:
  // 785:         H2 "id" = letter:
  // 786:           TEXT letter.to_upper_case
  // 787:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 788:   $$remark undefined
  // 789:   $name name_of(info)
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
static void entry__39_80(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 769: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__39_81;
}
static void cont__39_81(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 770: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_82;
  arguments->slots[1] = string__39_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_84;
}
static void cont__39_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 770: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_22;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__39_85;
}
static void cont__39_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: from_to
  // 772:   'a'
  // 773:   'z': (letter)
  // 774:     A "href" = "#@(letter)" letter.to_upper_case
  // 775:   :
  // 776:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__39_86;
  arguments->slots[3] = func__39_91;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__39_93;
}
static void entry__39_86(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 774: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_87;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__39_88;
}
static void cont__39_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 774: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_89;
}
static void cont__39_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 774: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__39_90;
}
static void cont__39_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 774: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_91(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 776: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_92;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_93(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 777: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__39_94;
}
static void cont__39_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 778: TABLE:
  // 779:   $$letter undefined
  // 780:   for_each definitions: (iname info)
  // 781:     if iname(1) != letter:
  // 782:       !letter iname(1)
  // 783:       TR:
  // 784:         TD "colspan" = 3:
  // 785:           H2 "id" = letter:
  // 786:             TEXT letter.to_upper_case
  // 787:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_95;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_173(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 820: for_each definitions: (_iname info)
  // 821:   $name name_of(info)
  // 822:   create_info_page name info
  // 823:   case kind_of(info) INLINE_C_TYPE:
  // 824:     for_each methods_of(info): (method_name method_info)
  // 825:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__39_174;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_182;
}
static void entry__39_180(void) {
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
  // 825: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__39_23;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__39_181;
}
static void cont__39_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 825: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_178(void) {
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
  // 824: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__39_179;
}
static void cont__39_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 824: ... : (method_name method_info)
  // 825:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__39_180, 2);
  // 824: for_each methods_of(info): (method_name method_info)
  // 825:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_174(void) {
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
  // 821: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__39_175;
}
static void cont__39_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 822: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__39_176;
}
static void cont__39_176(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 823: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__39_177;
}
static void cont__39_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 823: ... :
  // 824:   for_each methods_of(info): (method_name method_info)
  // 825:     create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_178, 0);
  // 823: case kind_of(info) INLINE_C_TYPE:
  // 824:   for_each methods_of(info): (method_name method_info)
  // 825:     create_info_page string(name "/" method_name) method_info
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
static void cont__39_182(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 827: create_page "html/topics_index.html":
  // 828:   link_bar
  // 829:   H1 "id" = "index" "Topics Index"
  // 830:   TABLE:
  // 831:     for_each topics: (topic _references)
  // 832:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 833:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_183;
  arguments->slots[1] = func__39_184;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__39_197;
}
static void entry__39_195(void) {
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
  // 833: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_196;
}
static void cont__39_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 833: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_194(void) {
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
  // 833: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__39_195, 0);
  // 833: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_189(void) {
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
  // 832: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__39_190;
}
static void cont__39_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 832: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__37_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_191;
}
static void cont__39_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 832: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__39_192;
}
static void cont__39_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 832: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__39_193;
}
static void cont__39_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 833: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_194, 0);
  // 833: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_188(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 831: for_each topics: (topic _references)
  // 832:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 833:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__39_189;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_184(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
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
  frame->cont = cont__39_185;
}
static void cont__39_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 829: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_82;
  arguments->slots[1] = string__39_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_186;
}
static void cont__39_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 829: H1 "id" = "index" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_27;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__39_187;
}
static void cont__39_187(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 830: TABLE:
  // 831:   for_each topics: (topic _references)
  // 832:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 833:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_188;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_197(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 834: for_each topics: (topic references)
  // 835:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 836:   create_page "html/@(filename).html":
  // 837:     link_bar
  // 838:     H1 "id" = "index" topic
  // 839:     $paragraphs topics_paragraphs(topic)
  // 840:     if paragraphs.is_defined:
  // 841:       for_each paragraphs: (paragraph) P paragraph.add_links
  // 842:     TABLE:
  // 843:       for_each references: (reference)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__39_198;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__39_223;
}
static void entry__39_215(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 845: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_216, 0);
  // 845: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__39_220;
}
static void entry__39_216(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 845: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__39_217;
}
static void cont__39_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 845: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__37_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__39_218;
}
static void cont__39_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 845: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_219;
}
static void cont__39_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 845: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_220(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 846: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__37_268;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__39_221;
}
static void cont__39_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 847: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__39_222;
}
static void cont__39_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 847: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_214(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 844: ... :
  // 845:   TD: A "href" = string(reference.mangled ".html") reference
  // 846:   TD "&nbsp;"
  // 847:   TD short_descriptions(reference)
  frame->slots[1] /* temp__1 */ = create_closure(entry__39_215, 0);
  // 844: TR:
  // 845:   TD: A "href" = string(reference.mangled ".html") reference
  // 846:   TD "&nbsp;"
  // 847:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_213(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 843: for_each references: (reference)
  // 844:   TR:
  // 845:     TD: A "href" = string(reference.mangled ".html") reference
  // 846:     TD "&nbsp;"
  // 847:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__39_214;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_203(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // topic: 0
  // references: 1
  // paragraphs: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic */
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  frame->slots[2] /* paragraphs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 837: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__39_204;
}
static void cont__39_204(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 838: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_82;
  arguments->slots[1] = string__39_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_205;
}
static void cont__39_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 838: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__39_206;
}
static void cont__39_206(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 839: $paragraphs topics_paragraphs(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = var._topics_paragraphs;
  func = myself->type;
  frame->cont = cont__39_207;
}
static void cont__39_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* paragraphs */, arguments->slots[0]);
  // 840: ... paragraphs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* paragraphs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__39_208;
}
static void cont__39_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 840: ... :
  // 841:   for_each paragraphs: (paragraph) P paragraph.add_links
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_209, 0);
  // 840: if paragraphs.is_defined:
  // 841:   for_each paragraphs: (paragraph) P paragraph.add_links
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__39_212;
}
static void entry__39_210(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // paragraph: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 841: ... paragraph.add_links
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraph */;
  result_count = 1;
  myself = var._add_links;
  func = myself->type;
  frame->cont = cont__39_211;
}
static void cont__39_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 841: ... P paragraph.add_links
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_209(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // paragraphs: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* paragraphs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 841: for_each paragraphs: (paragraph) P paragraph.add_links
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraphs */;
  arguments->slots[1] = func__39_210;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_212(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 842: ... :
  // 843:   for_each references: (reference)
  // 844:     TR:
  // 845:       TD: A "href" = string(reference.mangled ".html") reference
  // 846:       TD "&nbsp;"
  // 847:       TD short_descriptions(reference)
  frame->slots[3] /* temp__1 */ = create_closure(entry__39_213, 0);
  // 842: TABLE:
  // 843:   for_each references: (reference)
  // 844:     TR:
  // 845:       TD: A "href" = string(reference.mangled ".html") reference
  // 846:       TD "&nbsp;"
  // 847:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_198(void) {
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
  // 835: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__39_199;
}
static void cont__39_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 835: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__37_333;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_200;
}
static void cont__39_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 835: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__39_201;
}
static void cont__39_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 836: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__37_17;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__37_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__39_202;
}
static void cont__39_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 836: ... :
  // 837:   link_bar
  // 838:   H1 "id" = "index" topic
  // 839:   $paragraphs topics_paragraphs(topic)
  // 840:   if paragraphs.is_defined:
  // 841:     for_each paragraphs: (paragraph) P paragraph.add_links
  // 842:   TABLE:
  // 843:     for_each references: (reference)
  // 844:       TR:
  // 845:         TD: A "href" = string(reference.mangled ".html") reference
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__39_203, 0);
  // 836: create_page "html/@(filename).html":
  // 837:   link_bar
  // 838:   H1 "id" = "index" topic
  // 839:   $paragraphs topics_paragraphs(topic)
  // 840:   if paragraphs.is_defined:
  // 841:     for_each paragraphs: (paragraph) P paragraph.add_links
  // 842:   TABLE:
  // 843:     for_each references: (reference)
  // 844:       TR:
  // 845:         TD: A "href" = string(reference.mangled ".html") reference
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_223(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 848: create_page "html/index.html":
  // 849:   H1 "Simplicity"
  // 850:   P: A "href" = "manual.html" "Manual"
  // 851:   P: A "href" = "type_index.html" "Type Index"
  // 852:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 853:   P: A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__39_224;
  arguments->slots[1] = func__39_225;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__39_239;
}
static void entry__39_237(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 853: ... "href" = "topics_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_238;
}
static void cont__39_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 853: ... A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__39_225(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 849: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__39_226;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__39_227;
}
static void cont__39_227(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 850: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_228;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__39_230;
}
static void entry__39_228(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 850: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_229;
}
static void cont__39_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 850: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_12;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_230(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 851: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_231;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__39_233;
}
static void entry__39_231(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 851: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_232;
}
static void cont__39_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 851: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_17;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_233(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 852: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_234;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__39_236;
}
static void entry__39_234(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 852: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__31_3;
  arguments->slots[1] = string__31_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__39_235;
}
static void cont__39_235(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 852: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__31_22;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_236(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 853: P: A "href" = "topics_index.html" "Topics Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__39_237;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__39_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 855: if do_print_summary:
  // 856:   $$total_functions 0
  // 857:   $$total_polymorphic_functions 0
  // 858:   $$total_polymorphic_attributes 0
  // 859:   $$total_methods 0
  // 860:   $$total_inline_c_methods 0
  // 861:   $$total_inline_c_types 0
  // 862:   $$total_inline_c_objects 0
  // 863:   $$total_attributes 0
  // 864:   $$total_inline_c_functions 0
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_summary();
  arguments->slots[1] = func__39_240;
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
  var._topics_paragraphs = collect_node(var._topics_paragraphs);
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
  string__23_5 = from_latin_1_string("body {\012  background-color: white;\012  font-family: Times New Roman, Times;\012  font-size: 12pt;\012  color: #222;\012}\012h1 {\012  font-family: Arial, Helvetica;\012  font-size: 20pt;\012  color: #333;\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012h2 {\012  font-family: Arial, Helvetica;\012  font-size: 16pt;\012  color: #222;\012  margin-top: 5pt;\012  margin-bottom: 5pt;\012}\012h3 {\012  font-family: Arial, Helvetica;\012  font-size: 14pt;\012  color: #222;\012  margin-top: 3pt;\012  margin-bottom: 3pt;\012}\012h4 {\012  font-family: Arial, Helvetica;\012  font-size: 13pt;\012  color: #222;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012dt {\012  font-style: italic;\012  margin-bottom: 4pt;\012}\012dd {\012  padding-left: 0pt;\012  margin-left: 16pt;\012  margin-top: 0pt;\012  margin-bottom: 0pt;\012}\012p {\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012a {\012  text-decoration: none;\012}\012div.Example {\012  background-color: #ffc;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.Output {\012  background-color: #cff;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.footer {\012  padding-top: 10pt;\012  font-size: 10pt;\012}\012pre {\012  font-family: Courier New, Courier;\012  font-size: 12pt;\012  padding-top: 0pt;\012  padding-bottom: 0pt;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012td.remark {\012  padding-left: 10pt;\012}\012", 1234);
  func__23_4 = create_function(entry__23_4, 0);
  func__23_1_create_page = create_function(entry__23_1_create_page, 2);
  string__25_2 = from_latin_1_string("extracting documentation from ", 30);
  string__25_3 = from_latin_1_string("\012", 1);
  string__25_11 = from_latin_1_string("Empty source text!", 18);
  func__25_10 = create_function(entry__25_10, 0);
  string__25_17 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__25_16 = create_function(entry__25_16, 0);
  string__25_24 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__25_23 = create_function(entry__25_23, 0);
  string__25_26 = from_latin_1_string(".sim", 4);
  string__25_28 = from_latin_1_string("__", 2);
  func__25_32 = create_function(entry__25_32, 1);
  func__25_43 = create_function(entry__25_43, 0);
  string__25_54 = from_latin_1_string("std", 3);
  func__25_53 = create_function(entry__25_53, 0);
  func__25_60 = create_function(entry__25_60, 0);
  func__25_63 = create_function(entry__25_63, 0);
  string__25_88 = from_latin_1_string("Topic:", 6);
  func__25_122 = create_function(entry__25_122, 0);
  string__25_132 = from_latin_1_string("type", 4);
  string__25_133 = from_latin_1_string("object", 6);
  func__25_157 = create_function(entry__25_157, 0);
  func__25_158 = create_function(entry__25_158, 0);
  string__25_172 = from_latin_1_string("types::function", 15);
  func__25_1_extract_documentation_from_file = create_function(entry__25_1_extract_documentation_from_file, 1);
  func__26_4 = create_function(entry__26_4, 1);
  func__26_1_extract_documentation_from_directory = create_function(entry__26_1_extract_documentation_from_directory, 1);
  string__27_14 = from_latin_1_string("The attribute \042", 15);
  string__27_15 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__27_21 = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__27_24 = from_latin_1_string("::", 2);
  func__27_1_resolved_name = create_function(entry__27_1_resolved_name, 1);
  func__28_1_add_derived_type = create_function(entry__28_1_add_derived_type, 2);
  string__29_3 = from_latin_1_string("___", 3);
  func__29_1_mangled = create_function(entry__29_1_mangled, 1);
  func__30_1_ordered_name = create_function(entry__30_1_ordered_name, 2);
  string__31_3 = from_latin_1_string("href", 4);
  string__31_4 = from_latin_1_string("index.html", 10);
  string__31_6 = from_latin_1_string("Home", 4);
  string__31_8 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__31_10 = from_latin_1_string("manual.html", 11);
  string__31_12 = from_latin_1_string("Manual", 6);
  string__31_15 = from_latin_1_string("type_index.html", 15);
  string__31_17 = from_latin_1_string("Type Index", 10);
  string__31_20 = from_latin_1_string("symbol_index.html", 17);
  string__31_22 = from_latin_1_string("Symbol Index", 12);
  string__31_25 = from_latin_1_string("topics_index.html", 17);
  string__31_27 = from_latin_1_string("Topics Index", 12);
  func__31_2 = create_function(entry__31_2, 0);
  func__31_1_link_bar = create_function(entry__31_1_link_bar, 0);
  func__34_1_to_paragraphs = create_function(entry__34_1_to_paragraphs, 1);
  string__35_8 = from_latin_1_string("types::", 7);
  string__35_13 = from_latin_1_string("std::", 5);
  func__35_1_resolve_reference = create_function(entry__35_1_resolve_reference, 1);
  string__36_10 = from_latin_1_string("[", 1);
  string__36_11 = from_latin_1_string("](", 2);
  string__36_12 = from_latin_1_string(".html)", 6);
  func__36_5 = create_function(entry__36_5, 1);
  func__36_1_add_links = create_function(entry__36_1_add_links, 1);
  string__37_8 = from_latin_1_string("The documentation for \042", 23);
  string__37_9 = from_latin_1_string("\042\012(defined in \042", 15);
  string__37_10 = from_latin_1_string("\042)\012references the undefined symbol \042", 36);
  string__37_11 = from_latin_1_string("\042!\012", 3);
  string__37_17 = from_latin_1_string("html/", 5);
  string__37_18 = from_latin_1_string(".html", 5);
  string__37_28 = from_latin_1_string(".html)/[", 8);
  string__37_34 = from_latin_1_string("(static multi-assignment variable)", 34);
  func__37_33 = create_function(entry__37_33, 0);
  string__37_36 = from_latin_1_string("(dynamic single-assignment variable)", 36);
  func__37_35 = create_function(entry__37_35, 0);
  string__37_38 = from_latin_1_string("(dynamic multi-assignment variable)", 35);
  func__37_37 = create_function(entry__37_37, 0);
  string__37_49 = from_latin_1_string("Missing documentation for ", 26);
  string__37_50 = from_latin_1_string(" (defined in \042", 14);
  string__37_51 = from_latin_1_string("\042)!\012", 4);
  string__37_60 = from_latin_1_string("Parameter", 9);
  string__37_70 = from_latin_1_string(" (optional)", 11);
  string__37_77 = from_latin_1_string(" (zero or more arguments)", 25);
  string__37_86 = from_latin_1_string(" (optional; default value: ", 27);
  string__37_87 = from_latin_1_string(")", 1);
  string__37_96 = from_latin_1_string("Returns", 7);
  string__37_119 = from_latin_1_string("See also:", 9);
  string__37_149 = from_latin_1_string("Technical Details:", 18);
  func__37_213 = create_function(entry__37_213, 0);
  func__37_217 = create_function(entry__37_217, 0);
  string__37_224 = from_latin_1_string("Parameters", 10);
  func__37_227 = create_function(entry__37_227, 1);
  func__37_237 = create_function(entry__37_237, 1);
  string__37_245 = from_latin_1_string("Description", 11);
  func__37_247 = create_function(entry__37_247, 1);
  string__37_251 = from_latin_1_string("Technical Details", 17);
  func__37_253 = create_function(entry__37_253, 1);
  string__37_257 = from_latin_1_string("See also", 8);
  string__37_268 = from_latin_1_string("&nbsp;", 6);
  string__37_275 = from_latin_1_string("Implemented by", 14);
  string__37_287 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__37_297 = from_latin_1_string("Implements", 10);
  string__37_306 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__37_328 = from_latin_1_string("Topics", 6);
  string__37_333 = from_latin_1_string("_", 1);
  func__37_331 = create_function(entry__37_331, 1);
  string__37_347 = from_latin_1_string("class", 5);
  func__37_354 = create_function(entry__37_354, 1);
  string__37_356 = from_latin_1_string("**", 2);
  string__37_361 = from_latin_1_string("footer", 6);
  string__37_365 = from_latin_1_string("(defined in ", 12);
  string__37_366 = from_latin_1_string(")\012", 2);
  func__37_1_create_info_page = create_function(entry__37_1_create_info_page, 2);
  string__38_27 = from_latin_1_string("\012The short description for \042", 28);
  string__38_28 = from_latin_1_string("\042)\012is quite long:\012", 18);
  func__38_1_get_short_description = create_function(entry__38_1_get_short_description, 2);
  string__39_23 = from_latin_1_string("/", 1);
  func__39_5 = create_function(entry__39_5, 2);
  string__39_39 = from_latin_1_string("html/type_index.html", 20);
  func__39_40 = create_function(entry__39_40, 0);
  string__39_79 = from_latin_1_string("html/symbol_index.html", 22);
  string__39_82 = from_latin_1_string("id", 2);
  string__39_83 = from_latin_1_string("index", 5);
  string__39_87 = from_latin_1_string("#", 1);
  func__39_86 = create_function(entry__39_86, 1);
  string__39_92 = from_latin_1_string(" ", 1);
  func__39_91 = create_function(entry__39_91, 0);
  string__39_103 = from_latin_1_string("colspan", 7);
  string__39_110 = from_latin_1_string("#index", 6);
  string__39_112 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__39_127 = from_latin_1_string("function", 8);
  func__39_126 = create_function(entry__39_126, 0);
  string__39_129 = from_latin_1_string("polymorphic function", 20);
  func__39_128 = create_function(entry__39_128, 0);
  string__39_131 = from_latin_1_string("polymorphic attribute", 21);
  func__39_130 = create_function(entry__39_130, 0);
  string__39_133 = from_latin_1_string("inline-C type", 13);
  func__39_132 = create_function(entry__39_132, 0);
  string__39_135 = from_latin_1_string("inline-C object", 15);
  func__39_134 = create_function(entry__39_134, 0);
  string__39_137 = from_latin_1_string("inline-C function", 17);
  func__39_136 = create_function(entry__39_136, 0);
  string__39_139 = from_latin_1_string("unique item", 11);
  func__39_138 = create_function(entry__39_138, 0);
  string__39_141 = from_latin_1_string("constant", 8);
  func__39_140 = create_function(entry__39_140, 0);
  string__39_143 = from_latin_1_string("other", 5);
  func__39_142 = create_function(entry__39_142, 0);
  func__39_144 = create_function(entry__39_144, 0);
  string__39_150 = from_latin_1_string(" (", 2);
  string__39_160 = from_latin_1_string("align", 5);
  string__39_161 = from_latin_1_string("right", 5);
  string__39_171 = from_latin_1_string("remark", 6);
  func__39_95 = create_function(entry__39_95, 0);
  func__39_80 = create_function(entry__39_80, 0);
  func__39_174 = create_function(entry__39_174, 2);
  string__39_183 = from_latin_1_string("html/topics_index.html", 22);
  func__39_189 = create_function(entry__39_189, 2);
  func__39_188 = create_function(entry__39_188, 0);
  func__39_184 = create_function(entry__39_184, 0);
  func__39_210 = create_function(entry__39_210, 1);
  func__39_214 = create_function(entry__39_214, 1);
  func__39_198 = create_function(entry__39_198, 2);
  string__39_224 = from_latin_1_string("html/index.html", 15);
  string__39_226 = from_latin_1_string("Simplicity", 10);
  func__39_228 = create_function(entry__39_228, 0);
  func__39_231 = create_function(entry__39_231, 0);
  func__39_234 = create_function(entry__39_234, 0);
  func__39_237 = create_function(entry__39_237, 0);
  func__39_225 = create_function(entry__39_225, 0);
  string__39_298 = from_latin_1_string("total definitions:     ", 23);
  string__39_299 = from_latin_1_string("\012\012functions:             ", 25);
  string__39_300 = from_latin_1_string("\012polymorphic functions: ", 24);
  string__39_301 = from_latin_1_string("\012polymorphic attributes:", 24);
  string__39_302 = from_latin_1_string("\012method definitions:    ", 24);
  string__39_303 = from_latin_1_string("\012inline C methods:      ", 24);
  string__39_304 = from_latin_1_string("\012attribute definitions: ", 24);
  string__39_305 = from_latin_1_string("\012inline C functions:    ", 24);
  string__39_306 = from_latin_1_string("\012inline C types:        ", 24);
  string__39_307 = from_latin_1_string("\012inline C objects:      ", 24);
  string__39_308 = from_latin_1_string("\012unique items:          ", 24);
  string__39_309 = from_latin_1_string("\012other constants:       ", 24);
  string__39_310 = from_latin_1_string("\012other:                 ", 24);
  string__39_311 = from_latin_1_string("\012\012missing documentation: ", 25);
  func__39_240 = create_function(entry__39_240, 0);
  func__39_1_sim2c__extract_documentation = create_function(entry__39_1_sim2c__extract_documentation, 1);
  string__71_1 = from_latin_1_string("Topic", 5);
  string__72_1 = from_latin_1_string("Example", 7);
  string__72_2 = from_latin_1_string("Output", 6);
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
  use_read_only(NULL, "any_of", &get__any_of, &get_value_or_future__any_of);
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
  assign_variable(&var._create_page, &func__23_1_create_page);
  assign_variable(&var._extract_documentation_from_file, &func__25_1_extract_documentation_from_file);
  assign_variable(&var._extract_documentation_from_directory, &func__26_1_extract_documentation_from_directory);
  assign_variable(&var._resolved_name, &func__27_1_resolved_name);
  assign_variable(&var._add_derived_type, &func__28_1_add_derived_type);
  assign_variable(&var._mangled, &func__29_1_mangled);
  assign_variable(&var._ordered_name, &func__30_1_ordered_name);
  assign_variable(&var._link_bar, &func__31_1_link_bar);
  assign_variable(&var._to_paragraphs, &func__34_1_to_paragraphs);
  assign_variable(&var._resolve_reference, &func__35_1_resolve_reference);
  assign_variable(&var._add_links, &func__36_1_add_links);
  assign_variable(&var._create_info_page, &func__37_1_create_info_page);
  assign_variable(&var._get_short_description, &func__38_1_get_short_description);
  assign_variable(&var.sim2c__extract_documentation, &func__39_1_sim2c__extract_documentation);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
