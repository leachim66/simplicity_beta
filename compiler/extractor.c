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
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define REGISTER register
#else
  #define REGISTER IMPORT
#endif
typedef struct FRAME {
  FUNC cont;
  struct FRAME *caller_frame;
  long caller_result_count;
  long slot_count;
  NODE *slots[0];
} FRAME;
#if defined(__GNUC__) && !defined(__clang__) && defined(__x86_64)
  #define ASM(x) asm(x)
#else
  #define ASM(x)
#endif
REGISTER FRAME *arguments ASM("r12");
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
REGISTER int argument_count ASM("ebx");
IMPORT void too_few_arguments_error(void);
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
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
IMPORT void too_many_arguments_error(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void set_module(const char *name);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void register_polymorphic_function_with_setter(const char *name, int *id_p);
IMPORT NODE *register_unique_item(const char *name);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
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
static NODE_GETTER get__STATIC_SINGLE;
static NODE_GETTER get_value_or_future__STATIC_SINGLE;
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
static NODE_GETTER get__compiler__WHITESPACE;
static NODE_GETTER get_value_or_future__compiler__WHITESPACE;
static NODE_GETTER get__compiler__defined_namespaces;
static NODE_SETTER set__compiler__defined_namespaces;
static NODE_SETTER define__compiler__defined_namespaces;
static NODE_GETTER get__compiler__dependent_data;
static NODE_SETTER set__compiler__dependent_data;
static NODE_SETTER define__compiler__dependent_data;
static NODE_GETTER get__compiler__enumeration_count;
static NODE_SETTER set__compiler__enumeration_count;
static NODE_SETTER define__compiler__enumeration_count;
static NODE_GETTER get__compiler__included_files;
static NODE_SETTER set__compiler__included_files;
static NODE_SETTER define__compiler__included_files;
static NODE_GETTER get__compiler__linked_libraries;
static NODE_SETTER set__compiler__linked_libraries;
static NODE_SETTER define__compiler__linked_libraries;
static NODE_GETTER get__compiler__module_name;
static NODE_SETTER define__compiler__module_name;
static NODE_GETTER get__compiler__namespace_mappings;
static NODE_SETTER set__compiler__namespace_mappings;
static NODE_SETTER define__compiler__namespace_mappings;
static NODE_GETTER get__compiler__required_modules;
static NODE_SETTER set__compiler__required_modules;
static NODE_SETTER define__compiler__required_modules;
static NODE_GETTER get__compiler__used_namespaces;
static NODE_SETTER set__compiler__used_namespaces;
static NODE_SETTER define__compiler__used_namespaces;
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
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__find_first;
static NODE_GETTER get_value_or_future__find_first;
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
static NODE_GETTER get__verbose;
static NODE_GETTER get_value_or_future__verbose;
static NODE_GETTER get__without_prefix;
static NODE_GETTER get_value_or_future__without_prefix;
static NODE_GETTER get__without_suffix;
static NODE_GETTER get_value_or_future__without_suffix;
static NODE_GETTER get__write;
static NODE_GETTER get_value_or_future__write;
static NODE_GETTER get__write_to;
static NODE_GETTER get_value_or_future__write_to;
static NODE_GETTER get__writeln;
static NODE_GETTER get_value_or_future__writeln;
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
  NODE *_extract_remark_lines;
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
  NODE *compiler__extract_exports;
  NODE *compiler__extract_documentation;
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
  "extract_remark_lines",
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
static NODE *func__create_page_1;
static void entry__create_page_1(void);
static FRAME_INFO frame__create_page_1 = {3, {"filename", "body", "page"}};
static NODE *func__create_page_2;
static void entry__create_page_2(void);
static FRAME_INFO frame__create_page_2 = {1, {"body"}};
static NODE *func__create_page_3;
static void entry__create_page_3(void);
static FRAME_INFO frame__create_page_3 = {1, {"body"}};
static NODE *func__create_page_4;
static void entry__create_page_4(void);
static FRAME_INFO frame__create_page_4 = {0, {}};
static NODE *string__38ea9d2e8a7087ec;
static void cont__create_page_6(void);
static void cont__create_page_7(void);
static NODE *func__extract_remark_lines_1;
static void entry__extract_remark_lines_1(void);
static FRAME_INFO frame__extract_remark_lines_1 = {1, {"node"}};
static void cont__extract_remark_lines_2(void);
static void cont__extract_remark_lines_3(void);
static void cont__extract_remark_lines_4(void);
static NODE *func__extract_remark_lines_5;
static void entry__extract_remark_lines_5(void);
static FRAME_INFO frame__extract_remark_lines_5 = {1, {"node"}};
static void cont__extract_remark_lines_6(void);
static void cont__extract_remark_lines_7(void);
static void cont__extract_remark_lines_8(void);
static NODE *func__extract_remark_lines_9;
static void entry__extract_remark_lines_9(void);
static FRAME_INFO frame__extract_remark_lines_9 = {1, {"node"}};
static void cont__extract_remark_lines_10(void);
static NODE *func__extract_remark_lines_11;
static void entry__extract_remark_lines_11(void);
static FRAME_INFO frame__extract_remark_lines_11 = {3, {"node", "arguments", "first_idx"}};
static void cont__extract_remark_lines_12(void);
static void cont__extract_remark_lines_13(void);
static NODE *func__extract_remark_lines_14;
static void entry__extract_remark_lines_14(void);
static FRAME_INFO frame__extract_remark_lines_14 = {0, {}};
static NODE *func__extract_remark_lines_15;
static void entry__extract_remark_lines_15(void);
static FRAME_INFO frame__extract_remark_lines_15 = {0, {}};
static void cont__extract_remark_lines_16(void);
static void cont__extract_remark_lines_17(void);
static void cont__extract_remark_lines_18(void);
static void cont__extract_remark_lines_19(void);
static void cont__extract_remark_lines_20(void);
static NODE *func__extract_remark_lines_21;
static void entry__extract_remark_lines_21(void);
static FRAME_INFO frame__extract_remark_lines_21 = {2, {"arguments", "first_idx"}};
static void cont__extract_remark_lines_22(void);
static void cont__extract_remark_lines_23(void);
static NODE *func__extract_remark_lines_24;
static void entry__extract_remark_lines_24(void);
static FRAME_INFO frame__extract_remark_lines_24 = {1, {"arguments"}};
static void cont__extract_remark_lines_25(void);
static void cont__extract_remark_lines_26(void);
static void cont__extract_remark_lines_27(void);
static NODE *func__extract_documentation_from_file_1;
static void entry__extract_documentation_from_file_1(void);
static FRAME_INFO frame__extract_documentation_from_file_1 = {7, {"filename", "return__1", "buf", "fragments", "trees", "first_idx", "local_method_names"}};
static NODE *func__extract_documentation_from_file_2;
static void entry__extract_documentation_from_file_2(void);
static FRAME_INFO frame__extract_documentation_from_file_2 = {1, {"filename"}};
static NODE *string__f68a3e9b60626ed6;
static void cont__extract_documentation_from_file_4(void);
static void cont__extract_documentation_from_file_5(void);
static void cont__extract_documentation_from_file_6(void);
static void cont__extract_documentation_from_file_7(void);
static void cont__extract_documentation_from_file_8(void);
static void cont__extract_documentation_from_file_9(void);
static NODE *func__extract_documentation_from_file_10;
static void entry__extract_documentation_from_file_10(void);
static FRAME_INFO frame__extract_documentation_from_file_10 = {0, {}};
static NODE *string__1cbf9967f0b4797a;
static void cont__extract_documentation_from_file_12(void);
static void cont__extract_documentation_from_file_13(void);
static void cont__extract_documentation_from_file_14(void);
static void cont__extract_documentation_from_file_15(void);
static NODE *func__extract_documentation_from_file_16;
static void entry__extract_documentation_from_file_16(void);
static FRAME_INFO frame__extract_documentation_from_file_16 = {0, {}};
static NODE *string__cdb2cfe249b97e8f;
static void cont__extract_documentation_from_file_18(void);
static void cont__extract_documentation_from_file_19(void);
static void cont__extract_documentation_from_file_20(void);
static void cont__extract_documentation_from_file_21(void);
static void cont__extract_documentation_from_file_22(void);
static NODE *func__extract_documentation_from_file_23;
static void entry__extract_documentation_from_file_23(void);
static FRAME_INFO frame__extract_documentation_from_file_23 = {0, {}};
static NODE *string__f5ba012e5873af55;
static void cont__extract_documentation_from_file_25(void);
static NODE *string__9e0aed8b5d287d54;
static void cont__extract_documentation_from_file_27(void);
static NODE *string__2d7981f4e5f02b9a;
static void cont__extract_documentation_from_file_29(void);
static void cont__extract_documentation_from_file_30(void);
static void cont__extract_documentation_from_file_31(void);
static NODE *func__extract_documentation_from_file_32;
static void entry__extract_documentation_from_file_32(void);
static FRAME_INFO frame__extract_documentation_from_file_32 = {1, {"fragment"}};
static void cont__extract_documentation_from_file_33(void);
static void cont__extract_documentation_from_file_34(void);
static NODE *func__extract_documentation_from_file_35;
static void entry__extract_documentation_from_file_35(void);
static FRAME_INFO frame__extract_documentation_from_file_35 = {3, {"done", "fragments", "first_idx"}};
static NODE *func__extract_documentation_from_file_36;
static void entry__extract_documentation_from_file_36(void);
static FRAME_INFO frame__extract_documentation_from_file_36 = {4, {"idx", "fragment", "first_idx", "done"}};
static void cont__extract_documentation_from_file_37(void);
static void cont__extract_documentation_from_file_38(void);
static NODE *func__extract_documentation_from_file_39;
static void entry__extract_documentation_from_file_39(void);
static FRAME_INFO frame__extract_documentation_from_file_39 = {4, {"first_idx", "idx", "fragment", "tree"}};
static void cont__extract_documentation_from_file_40(void);
static void cont__extract_documentation_from_file_41(void);
static NODE *func__extract_documentation_from_file_42;
static void entry__extract_documentation_from_file_42(void);
static FRAME_INFO frame__extract_documentation_from_file_42 = {1, {"done"}};
static NODE *func__extract_documentation_from_file_43;
static void entry__extract_documentation_from_file_43(void);
static FRAME_INFO frame__extract_documentation_from_file_43 = {0, {}};
static void cont__extract_documentation_from_file_44(void);
static void cont__extract_documentation_from_file_45(void);
static void cont__extract_documentation_from_file_46(void);
static void cont__extract_documentation_from_file_47(void);
static NODE *func__extract_documentation_from_file_48;
static void entry__extract_documentation_from_file_48(void);
static FRAME_INFO frame__extract_documentation_from_file_48 = {2, {"fragment", "trees"}};
static void cont__extract_documentation_from_file_49(void);
static void cont__extract_documentation_from_file_50(void);
static void cont__extract_documentation_from_file_51(void);
static void cont__extract_documentation_from_file_52(void);
static NODE *func__extract_documentation_from_file_53;
static void entry__extract_documentation_from_file_53(void);
static FRAME_INFO frame__extract_documentation_from_file_53 = {0, {}};
static NODE *string__fa724815d896ba8;
static void cont__extract_documentation_from_file_55(void);
static void cont__extract_documentation_from_file_56(void);
static NODE *func__extract_documentation_from_file_57;
static void entry__extract_documentation_from_file_57(void);
static FRAME_INFO frame__extract_documentation_from_file_57 = {2, {"statement", "local_method_names"}};
static NODE *func__extract_documentation_from_file_58;
static void entry__extract_documentation_from_file_58(void);
static FRAME_INFO frame__extract_documentation_from_file_58 = {1, {"statement"}};
static void cont__extract_documentation_from_file_59(void);
static NODE *func__extract_documentation_from_file_60;
static void entry__extract_documentation_from_file_60(void);
static FRAME_INFO frame__extract_documentation_from_file_60 = {0, {}};
static NODE *func__extract_documentation_from_file_61;
static void entry__extract_documentation_from_file_61(void);
static FRAME_INFO frame__extract_documentation_from_file_61 = {1, {"statement"}};
static void cont__extract_documentation_from_file_62(void);
static NODE *func__extract_documentation_from_file_63;
static void entry__extract_documentation_from_file_63(void);
static FRAME_INFO frame__extract_documentation_from_file_63 = {0, {}};
static NODE *func__extract_documentation_from_file_64;
static void entry__extract_documentation_from_file_64(void);
static FRAME_INFO frame__extract_documentation_from_file_64 = {2, {"statement", "local_method_names"}};
static void cont__extract_documentation_from_file_65(void);
static NODE *func__extract_documentation_from_file_66;
static void entry__extract_documentation_from_file_66(void);
static FRAME_INFO frame__extract_documentation_from_file_66 = {3, {"statement", "local_method_names", "destination"}};
static void cont__extract_documentation_from_file_67(void);
static void cont__extract_documentation_from_file_68(void);
static void cont__extract_documentation_from_file_69(void);
static NODE *func__extract_documentation_from_file_70;
static void entry__extract_documentation_from_file_70(void);
static FRAME_INFO frame__extract_documentation_from_file_70 = {4, {"destination", "statement", "local_method_names", "identifier"}};
static void cont__extract_documentation_from_file_71(void);
static void cont__extract_documentation_from_file_72(void);
static void cont__extract_documentation_from_file_73(void);
static NODE *func__extract_documentation_from_file_74;
static void entry__extract_documentation_from_file_74(void);
static FRAME_INFO frame__extract_documentation_from_file_74 = {4, {"statement", "local_method_names", "destination", "source"}};
static void cont__extract_documentation_from_file_75(void);
static void cont__extract_documentation_from_file_76(void);
static void cont__extract_documentation_from_file_77(void);
static NODE *func__extract_documentation_from_file_78;
static void entry__extract_documentation_from_file_78(void);
static FRAME_INFO frame__extract_documentation_from_file_78 = {2, {"local_method_names", "destination"}};
static void cont__extract_documentation_from_file_79(void);
static void cont__extract_documentation_from_file_80(void);
static void cont__extract_documentation_from_file_81(void);
static void cont__extract_documentation_from_file_82(void);
static NODE *func__extract_documentation_from_file_83;
static void entry__extract_documentation_from_file_83(void);
static FRAME_INFO frame__extract_documentation_from_file_83 = {4, {"statement", "break", "filename", "local_method_names"}};
static NODE *func__extract_documentation_from_file_84;
static void entry__extract_documentation_from_file_84(void);
static FRAME_INFO frame__extract_documentation_from_file_84 = {1, {"statement"}};
static void cont__extract_documentation_from_file_85(void);
static NODE *func__extract_documentation_from_file_86;
static void entry__extract_documentation_from_file_86(void);
static FRAME_INFO frame__extract_documentation_from_file_86 = {2, {"statement", "remark_lines"}};
static void cont__extract_documentation_from_file_87(void);
static NODE *string__781f541a81a2a2ed;
static void cont__extract_documentation_from_file_89(void);
static NODE *func__extract_documentation_from_file_90;
static void entry__extract_documentation_from_file_90(void);
static FRAME_INFO frame__extract_documentation_from_file_90 = {2, {"remark_lines", "paragraphs"}};
static void cont__extract_documentation_from_file_91(void);
static NODE *func__extract_documentation_from_file_92;
static void entry__extract_documentation_from_file_92(void);
static FRAME_INFO frame__extract_documentation_from_file_92 = {2, {"done", "paragraphs"}};
static NODE *func__extract_documentation_from_file_93;
static void entry__extract_documentation_from_file_93(void);
static FRAME_INFO frame__extract_documentation_from_file_93 = {4, {"idx", "paragraph", "paragraphs", "done"}};
static void cont__extract_documentation_from_file_94(void);
static NODE *func__extract_documentation_from_file_95;
static void entry__extract_documentation_from_file_95(void);
static FRAME_INFO frame__extract_documentation_from_file_95 = {5, {"paragraph", "paragraphs", "idx", "done", "topic"}};
static void cont__extract_documentation_from_file_96(void);
static void cont__extract_documentation_from_file_97(void);
static void cont__extract_documentation_from_file_98(void);
static void cont__extract_documentation_from_file_99(void);
static void cont__extract_documentation_from_file_100(void);
static void cont__extract_documentation_from_file_101(void);
static void cont__extract_documentation_from_file_102(void);
static NODE *func__extract_documentation_from_file_103;
static void entry__extract_documentation_from_file_103(void);
static FRAME_INFO frame__extract_documentation_from_file_103 = {2, {"statement", "filename"}};
static void cont__extract_documentation_from_file_104(void);
static NODE *func__extract_documentation_from_file_105;
static void entry__extract_documentation_from_file_105(void);
static FRAME_INFO frame__extract_documentation_from_file_105 = {3, {"statement", "filename", "identifier"}};
static void cont__extract_documentation_from_file_106(void);
static void cont__extract_documentation_from_file_107(void);
static NODE *func__extract_documentation_from_file_108;
static void entry__extract_documentation_from_file_108(void);
static FRAME_INFO frame__extract_documentation_from_file_108 = {4, {"identifier", "statement", "filename", "namespace"}};
static void cont__extract_documentation_from_file_109(void);
static void cont__extract_documentation_from_file_110(void);
static NODE *func__extract_documentation_from_file_111;
static void entry__extract_documentation_from_file_111(void);
static FRAME_INFO frame__extract_documentation_from_file_111 = {5, {"identifier", "statement", "namespace", "filename", "name"}};
static void cont__extract_documentation_from_file_112(void);
static void cont__extract_documentation_from_file_113(void);
static NODE *func__extract_documentation_from_file_114;
static void entry__extract_documentation_from_file_114(void);
static FRAME_INFO frame__extract_documentation_from_file_114 = {5, {"namespace", "statement", "name", "identifier", "filename"}};
static void cont__extract_documentation_from_file_115(void);
static NODE *func__extract_documentation_from_file_116;
static void entry__extract_documentation_from_file_116(void);
static FRAME_INFO frame__extract_documentation_from_file_116 = {6, {"statement", "namespace", "name", "identifier", "filename", "base"}};
static void cont__extract_documentation_from_file_117(void);
static void cont__extract_documentation_from_file_118(void);
static void cont__extract_documentation_from_file_119(void);
static NODE *func__extract_documentation_from_file_120;
static void entry__extract_documentation_from_file_120(void);
static FRAME_INFO frame__extract_documentation_from_file_120 = {1, {"base"}};
static void cont__extract_documentation_from_file_121(void);
static NODE *func__extract_documentation_from_file_122;
static void entry__extract_documentation_from_file_122(void);
static FRAME_INFO frame__extract_documentation_from_file_122 = {0, {}};
static void cont__extract_documentation_from_file_123(void);
static void cont__extract_documentation_from_file_124(void);
static void cont__extract_documentation_from_file_125(void);
static void cont__extract_documentation_from_file_126(void);
static NODE *func__extract_documentation_from_file_127;
static void entry__extract_documentation_from_file_127(void);
static FRAME_INFO frame__extract_documentation_from_file_127 = {5, {"namespace", "name", "identifier", "statement", "filename"}};
static void cont__extract_documentation_from_file_128(void);
static void cont__extract_documentation_from_file_129(void);
static void cont__extract_documentation_from_file_130(void);
static void cont__extract_documentation_from_file_131(void);
static NODE *string__2a0aef0b5de07d5c;
static NODE *string__4c1f570701a272a3;
static NODE *func__extract_documentation_from_file_134;
static void entry__extract_documentation_from_file_134(void);
static FRAME_INFO frame__extract_documentation_from_file_134 = {4, {"statement", "filename", "break", "local_method_names"}};
static void cont__extract_documentation_from_file_135(void);
static NODE *func__extract_documentation_from_file_136;
static void entry__extract_documentation_from_file_136(void);
static FRAME_INFO frame__extract_documentation_from_file_136 = {6, {"statement", "filename", "break", "local_method_names", "destination", "info"}};
static void cont__extract_documentation_from_file_137(void);
static void cont__extract_documentation_from_file_138(void);
static void cont__extract_documentation_from_file_139(void);
static NODE *func__extract_documentation_from_file_140;
static void entry__extract_documentation_from_file_140(void);
static FRAME_INFO frame__extract_documentation_from_file_140 = {7, {"destination", "info", "statement", "break", "local_method_names", "identifier", "namespace"}};
static void cont__extract_documentation_from_file_141(void);
static void cont__extract_documentation_from_file_142(void);
static void cont__extract_documentation_from_file_143(void);
static NODE *func__extract_documentation_from_file_144;
static void entry__extract_documentation_from_file_144(void);
static FRAME_INFO frame__extract_documentation_from_file_144 = {11, {"identifier", "namespace", "info", "destination", "statement", "break", "local_method_names", "name", "iname", "is_not_a_remark", "source"}};
static NODE *func__extract_documentation_from_file_145;
static void entry__extract_documentation_from_file_145(void);
static FRAME_INFO frame__extract_documentation_from_file_145 = {1, {"node"}};
static void cont__extract_documentation_from_file_146(void);
static void cont__extract_documentation_from_file_147(void);
static void cont__extract_documentation_from_file_148(void);
static void cont__extract_documentation_from_file_149(void);
static void cont__extract_documentation_from_file_150(void);
static void cont__extract_documentation_from_file_151(void);
static void cont__extract_documentation_from_file_152(void);
static void cont__extract_documentation_from_file_153(void);
static void cont__extract_documentation_from_file_154(void);
static void cont__extract_documentation_from_file_155(void);
static void cont__extract_documentation_from_file_156(void);
static NODE *func__extract_documentation_from_file_157;
static void entry__extract_documentation_from_file_157(void);
static FRAME_INFO frame__extract_documentation_from_file_157 = {6, {"source", "name", "namespace", "iname", "info", "break"}};
static void cont__extract_documentation_from_file_158(void);
static NODE *func__extract_documentation_from_file_159;
static void entry__extract_documentation_from_file_159(void);
static FRAME_INFO frame__extract_documentation_from_file_159 = {6, {"name", "namespace", "iname", "info", "source", "break"}};
static void cont__extract_documentation_from_file_160(void);
static void cont__extract_documentation_from_file_161(void);
static NODE *func__extract_documentation_from_file_162;
static void entry__extract_documentation_from_file_162(void);
static FRAME_INFO frame__extract_documentation_from_file_162 = {0, {}};
static NODE *func__extract_documentation_from_file_163;
static void entry__extract_documentation_from_file_163(void);
static FRAME_INFO frame__extract_documentation_from_file_163 = {0, {}};
static void cont__extract_documentation_from_file_164(void);
static void cont__extract_documentation_from_file_165(void);
static NODE *func__extract_documentation_from_file_166;
static void entry__extract_documentation_from_file_166(void);
static FRAME_INFO frame__extract_documentation_from_file_166 = {3, {"source", "info", "statement"}};
static void cont__extract_documentation_from_file_167(void);
static NODE *func__extract_documentation_from_file_168;
static void entry__extract_documentation_from_file_168(void);
static FRAME_INFO frame__extract_documentation_from_file_168 = {3, {"info", "source", "statement"}};
static void cont__extract_documentation_from_file_169(void);
static void cont__extract_documentation_from_file_170(void);
static NODE *string__f7c371b7c3c668a7;
static NODE *func__extract_documentation_from_file_172;
static void entry__extract_documentation_from_file_172(void);
static FRAME_INFO frame__extract_documentation_from_file_172 = {2, {"source", "info"}};
static void cont__extract_documentation_from_file_173(void);
static NODE *func__extract_documentation_from_file_174;
static void entry__extract_documentation_from_file_174(void);
static FRAME_INFO frame__extract_documentation_from_file_174 = {1, {"info"}};
static NODE *func__extract_documentation_from_file_175;
static void entry__extract_documentation_from_file_175(void);
static FRAME_INFO frame__extract_documentation_from_file_175 = {2, {"source", "info"}};
static void cont__extract_documentation_from_file_176(void);
static NODE *func__extract_documentation_from_file_177;
static void entry__extract_documentation_from_file_177(void);
static FRAME_INFO frame__extract_documentation_from_file_177 = {2, {"source", "info"}};
static void cont__extract_documentation_from_file_178(void);
static void cont__extract_documentation_from_file_179(void);
static NODE *func__extract_documentation_from_file_180;
static void entry__extract_documentation_from_file_180(void);
static FRAME_INFO frame__extract_documentation_from_file_180 = {2, {"info", "source"}};
static void cont__extract_documentation_from_file_181(void);
static NODE *func__extract_documentation_from_file_182;
static void entry__extract_documentation_from_file_182(void);
static FRAME_INFO frame__extract_documentation_from_file_182 = {4, {"source", "iname", "info", "break"}};
static void cont__extract_documentation_from_file_183(void);
static NODE *func__extract_documentation_from_file_184;
static void entry__extract_documentation_from_file_184(void);
static FRAME_INFO frame__extract_documentation_from_file_184 = {3, {"iname", "info", "break"}};
static void cont__extract_documentation_from_file_185(void);
static NODE *func__extract_documentation_from_file_186;
static void entry__extract_documentation_from_file_186(void);
static FRAME_INFO frame__extract_documentation_from_file_186 = {2, {"source", "info"}};
static void cont__extract_documentation_from_file_187(void);
static NODE *func__extract_documentation_from_file_188;
static void entry__extract_documentation_from_file_188(void);
static FRAME_INFO frame__extract_documentation_from_file_188 = {1, {"info"}};
static void cont__extract_documentation_from_file_189(void);
static void cont__extract_documentation_from_file_190(void);
static NODE *func__extract_documentation_from_file_191;
static void entry__extract_documentation_from_file_191(void);
static FRAME_INFO frame__extract_documentation_from_file_191 = {3, {"iname", "info", "previous_definition"}};
static void cont__extract_documentation_from_file_192(void);
static void cont__extract_documentation_from_file_193(void);
static NODE *func__extract_documentation_from_file_194;
static void entry__extract_documentation_from_file_194(void);
static FRAME_INFO frame__extract_documentation_from_file_194 = {2, {"previous_definition", "info"}};
static void cont__extract_documentation_from_file_195(void);
static void cont__extract_documentation_from_file_196(void);
static NODE *func__extract_documentation_from_file_197;
static void entry__extract_documentation_from_file_197(void);
static FRAME_INFO frame__extract_documentation_from_file_197 = {2, {"info", "previous_definition"}};
static void cont__extract_documentation_from_file_198(void);
static void cont__extract_documentation_from_file_199(void);
static void cont__extract_documentation_from_file_200(void);
static void cont__extract_documentation_from_file_201(void);
static void cont__extract_documentation_from_file_202(void);
static void cont__extract_documentation_from_file_203(void);
static NODE *func__extract_documentation_from_file_204;
static void entry__extract_documentation_from_file_204(void);
static FRAME_INFO frame__extract_documentation_from_file_204 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__extract_documentation_from_file_205(void);
static void cont__extract_documentation_from_file_206(void);
static void cont__extract_documentation_from_file_207(void);
static void cont__extract_documentation_from_file_208(void);
static void cont__extract_documentation_from_file_209(void);
static NODE *func__extract_documentation_from_file_210;
static void entry__extract_documentation_from_file_210(void);
static FRAME_INFO frame__extract_documentation_from_file_210 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__extract_documentation_from_file_211(void);
static void cont__extract_documentation_from_file_212(void);
static NODE *func__extract_documentation_from_file_213;
static void entry__extract_documentation_from_file_213(void);
static FRAME_INFO frame__extract_documentation_from_file_213 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__extract_documentation_from_file_214(void);
static void cont__extract_documentation_from_file_215(void);
static NODE *func__extract_documentation_from_file_216;
static void entry__extract_documentation_from_file_216(void);
static FRAME_INFO frame__extract_documentation_from_file_216 = {1, {"attr"}};
static void cont__extract_documentation_from_file_217(void);
static void cont__extract_documentation_from_file_218(void);
static void cont__extract_documentation_from_file_219(void);
static void cont__extract_documentation_from_file_220(void);
static void cont__extract_documentation_from_file_221(void);
static void cont__extract_documentation_from_file_222(void);
static void cont__extract_documentation_from_file_223(void);
static void cont__extract_documentation_from_file_224(void);
static NODE *func__extract_documentation_from_directory_1;
static void entry__extract_documentation_from_directory_1(void);
static FRAME_INFO frame__extract_documentation_from_directory_1 = {1, {"path"}};
static void cont__extract_documentation_from_directory_2(void);
static void cont__extract_documentation_from_directory_3(void);
static NODE *func__extract_documentation_from_directory_4;
static void entry__extract_documentation_from_directory_4(void);
static FRAME_INFO frame__extract_documentation_from_directory_4 = {2, {"entry", "name"}};
static void cont__extract_documentation_from_directory_5(void);
static NODE *func__extract_documentation_from_directory_6;
static void entry__extract_documentation_from_directory_6(void);
static FRAME_INFO frame__extract_documentation_from_directory_6 = {2, {"entry", "name"}};
static void cont__extract_documentation_from_directory_7(void);
static NODE *func__extract_documentation_from_directory_8;
static void entry__extract_documentation_from_directory_8(void);
static FRAME_INFO frame__extract_documentation_from_directory_8 = {1, {"name"}};
static NODE *func__extract_documentation_from_directory_9;
static void entry__extract_documentation_from_directory_9(void);
static FRAME_INFO frame__extract_documentation_from_directory_9 = {1, {"name"}};
static void cont__extract_documentation_from_directory_10(void);
static NODE *func__extract_documentation_from_directory_11;
static void entry__extract_documentation_from_directory_11(void);
static FRAME_INFO frame__extract_documentation_from_directory_11 = {1, {"name"}};
static NODE *func__resolved_name_1;
static void entry__resolved_name_1(void);
static FRAME_INFO frame__resolved_name_1 = {2, {"attr", "name"}};
static void cont__resolved_name_2(void);
static void cont__resolved_name_3(void);
static void cont__resolved_name_4(void);
static NODE *func__resolved_name_5;
static void entry__resolved_name_5(void);
static FRAME_INFO frame__resolved_name_5 = {1, {"attr"}};
static void cont__resolved_name_6(void);
static NODE *func__resolved_name_7;
static void entry__resolved_name_7(void);
static FRAME_INFO frame__resolved_name_7 = {3, {"attr", "name", "resolved_namespace"}};
static void cont__resolved_name_8(void);
static NODE *func__resolved_name_9;
static void entry__resolved_name_9(void);
static FRAME_INFO frame__resolved_name_9 = {3, {"namespace", "name", "resolved_namespace"}};
static void cont__resolved_name_10(void);
static NODE *func__resolved_name_11;
static void entry__resolved_name_11(void);
static FRAME_INFO frame__resolved_name_11 = {3, {"resolved_namespace", "name", "namespace"}};
static void cont__resolved_name_12(void);
static NODE *func__resolved_name_13;
static void entry__resolved_name_13(void);
static FRAME_INFO frame__resolved_name_13 = {1, {"name"}};
static NODE *string__7f3103e18f358a6f;
static NODE *string__abd8bded937d2ca5;
static void cont__resolved_name_16(void);
static void cont__resolved_name_17(void);
static void cont__resolved_name_18(void);
static void cont__resolved_name_19(void);
static NODE *func__resolved_name_20;
static void entry__resolved_name_20(void);
static FRAME_INFO frame__resolved_name_20 = {1, {"name"}};
static NODE *string__8906d104d2e53fac;
static void cont__resolved_name_22(void);
static void cont__resolved_name_23(void);
static NODE *string__2d7981f4e6d82bff;
static void cont__resolved_name_25(void);
static NODE *func__add_derived_type_1;
static void entry__add_derived_type_1(void);
static FRAME_INFO frame__add_derived_type_1 = {4, {"base", "name", "ibase", "definition"}};
static void cont__add_derived_type_2(void);
static void cont__add_derived_type_3(void);
static void cont__add_derived_type_4(void);
static void cont__add_derived_type_5(void);
static void cont__add_derived_type_6(void);
static NODE *func__add_derived_type_7;
static void entry__add_derived_type_7(void);
static FRAME_INFO frame__add_derived_type_7 = {3, {"definition", "name", "ibase"}};
static void cont__add_derived_type_8(void);
static void cont__add_derived_type_9(void);
static void cont__add_derived_type_10(void);
static void cont__add_derived_type_11(void);
static NODE *func__add_derived_type_12;
static void entry__add_derived_type_12(void);
static FRAME_INFO frame__add_derived_type_12 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__add_derived_type_13(void);
static void cont__add_derived_type_14(void);
static NODE *func__add_derived_type_15;
static void entry__add_derived_type_15(void);
static FRAME_INFO frame__add_derived_type_15 = {2, {"base_of_base", "ibase"}};
static void cont__add_derived_type_16(void);
static void cont__add_derived_type_17(void);
static NODE *func__mangled_1;
static void entry__mangled_1(void);
static FRAME_INFO frame__mangled_1 = {1, {"name"}};
static void cont__mangled_2(void);
static NODE *string__fa72f815cd16b93;
static void cont__mangled_4(void);
static void cont__mangled_5(void);
static NODE *func__ordered_name_1;
static void entry__ordered_name_1(void);
static FRAME_INFO frame__ordered_name_1 = {2, {"namespace", "name"}};
static void cont__ordered_name_2(void);
static void cont__ordered_name_3(void);
static void cont__ordered_name_4(void);
static NODE *func__link_bar_1;
static void entry__link_bar_1(void);
static FRAME_INFO frame__link_bar_1 = {0, {}};
static NODE *func__link_bar_2;
static void entry__link_bar_2(void);
static FRAME_INFO frame__link_bar_2 = {0, {}};
static NODE *string__120aedcb5d487d5f;
static NODE *string__25705d17a847956d;
static void cont__link_bar_5(void);
static NODE *string__520aea8b5d087d5c;
static void cont__link_bar_7(void);
static NODE *string__57442216b13fc418;
static void cont__link_bar_9(void);
static NODE *string__d0d93c5da16549ef;
static void cont__link_bar_11(void);
static NODE *string__441f531601b242bb;
static void cont__link_bar_13(void);
static void cont__link_bar_14(void);
static NODE *string__cf81eefc97d2b8ee;
static void cont__link_bar_16(void);
static NODE *string__2971b13bbf01e7f9;
static void cont__link_bar_18(void);
static void cont__link_bar_19(void);
static NODE *string__bc0556bbe81c68c5;
static void cont__link_bar_21(void);
static NODE *string__d6ed116d58489777;
static void cont__link_bar_23(void);
static void cont__link_bar_24(void);
static NODE *string__b982567928221cc5;
static void cont__link_bar_26(void);
static NODE *string__5691f96d534696f2;
static NODE *func__to_paragraphs_1;
static void entry__to_paragraphs_1(void);
static FRAME_INFO frame__to_paragraphs_1 = {4, {"lines", "paragraphs", "text", "pre_mode"}};
static NODE *func__to_paragraphs_2;
static void entry__to_paragraphs_2(void);
static FRAME_INFO frame__to_paragraphs_2 = {4, {"line", "pre_mode", "text", "paragraphs"}};
static NODE *func__to_paragraphs_3;
static void entry__to_paragraphs_3(void);
static FRAME_INFO frame__to_paragraphs_3 = {3, {"line", "text", "paragraphs"}};
static void cont__to_paragraphs_4(void);
static NODE *func__to_paragraphs_5;
static void entry__to_paragraphs_5(void);
static FRAME_INFO frame__to_paragraphs_5 = {3, {"text", "paragraphs", "line"}};
static void cont__to_paragraphs_6(void);
static void cont__to_paragraphs_7(void);
static NODE *func__to_paragraphs_8;
static void entry__to_paragraphs_8(void);
static FRAME_INFO frame__to_paragraphs_8 = {2, {"text", "line"}};
static void cont__to_paragraphs_9(void);
static NODE *func__to_paragraphs_10;
static void entry__to_paragraphs_10(void);
static FRAME_INFO frame__to_paragraphs_10 = {4, {"line", "text", "paragraphs", "pre_mode"}};
static void cont__to_paragraphs_11(void);
static NODE *func__to_paragraphs_12;
static void entry__to_paragraphs_12(void);
static FRAME_INFO frame__to_paragraphs_12 = {2, {"text", "paragraphs"}};
static void cont__to_paragraphs_13(void);
static void cont__to_paragraphs_14(void);
static NODE *func__to_paragraphs_15;
static void entry__to_paragraphs_15(void);
static FRAME_INFO frame__to_paragraphs_15 = {2, {"paragraphs", "text"}};
static void cont__to_paragraphs_16(void);
static NODE *func__to_paragraphs_17;
static void entry__to_paragraphs_17(void);
static FRAME_INFO frame__to_paragraphs_17 = {3, {"text", "line", "pre_mode"}};
static void cont__to_paragraphs_18(void);
static NODE *func__to_paragraphs_19;
static void entry__to_paragraphs_19(void);
static FRAME_INFO frame__to_paragraphs_19 = {2, {"line", "pre_mode"}};
static void cont__to_paragraphs_20(void);
static NODE *func__to_paragraphs_21;
static void entry__to_paragraphs_21(void);
static FRAME_INFO frame__to_paragraphs_21 = {1, {"pre_mode"}};
static NODE *func__to_paragraphs_22;
static void entry__to_paragraphs_22(void);
static FRAME_INFO frame__to_paragraphs_22 = {1, {"text"}};
static void cont__to_paragraphs_23(void);
static void cont__to_paragraphs_24(void);
static void cont__to_paragraphs_25(void);
static void cont__to_paragraphs_26(void);
static void cont__to_paragraphs_27(void);
static void cont__to_paragraphs_28(void);
static void cont__to_paragraphs_29(void);
static NODE *func__to_paragraphs_30;
static void entry__to_paragraphs_30(void);
static FRAME_INFO frame__to_paragraphs_30 = {2, {"paragraphs", "text"}};
static void cont__to_paragraphs_31(void);
static void cont__to_paragraphs_32(void);
static NODE *func__resolve_reference_1;
static void entry__resolve_reference_1(void);
static FRAME_INFO frame__resolve_reference_1 = {1, {"reference"}};
static void cont__resolve_reference_2(void);
static NODE *func__resolve_reference_3;
static void entry__resolve_reference_3(void);
static FRAME_INFO frame__resolve_reference_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__resolve_reference_4(void);
static void cont__resolve_reference_5(void);
static void cont__resolve_reference_6(void);
static NODE *func__resolve_reference_7;
static void entry__resolve_reference_7(void);
static FRAME_INFO frame__resolve_reference_7 = {1, {"type_name"}};
static NODE *string__b854091e176bc0c0;
static void cont__resolve_reference_9(void);
static void cont__resolve_reference_10(void);
static void cont__resolve_reference_11(void);
static NODE *func__resolve_reference_12;
static void entry__resolve_reference_12(void);
static FRAME_INFO frame__resolve_reference_12 = {1, {"method_name"}};
static NODE *string__625aea03e819206d;
static void cont__resolve_reference_14(void);
static void cont__resolve_reference_15(void);
static void cont__resolve_reference_16(void);
static NODE *func__resolve_reference_17;
static void entry__resolve_reference_17(void);
static FRAME_INFO frame__resolve_reference_17 = {1, {"reference"}};
static void cont__resolve_reference_18(void);
static NODE *func__resolve_reference_19;
static void entry__resolve_reference_19(void);
static FRAME_INFO frame__resolve_reference_19 = {1, {"reference"}};
static void cont__resolve_reference_20(void);
static void cont__resolve_reference_21(void);
static NODE *func__add_links_1;
static void entry__add_links_1(void);
static FRAME_INFO frame__add_links_1 = {1, {"paragraph"}};
static void cont__add_links_2(void);
static void cont__add_links_3(void);
static void cont__add_links_4(void);
static NODE *func__add_links_5;
static void entry__add_links_5(void);
static FRAME_INFO frame__add_links_5 = {1, {"reference"}};
static void cont__add_links_6(void);
static void cont__add_links_7(void);
static void cont__add_links_8(void);
static void cont__add_links_9(void);
static NODE *string__578a5af303e9cba;
static NODE *string__2d7981f4e5e02bed;
static NODE *string__701f552781dad2fe;
static void cont__add_links_13(void);
static void cont__add_links_14(void);
static void cont__add_links_15(void);
static NODE *func__create_info_page_1;
static void entry__create_info_page_1(void);
static FRAME_INFO frame__create_info_page_1 = {3, {"function_name", "info", "resolve_and_check_reference"}};
static NODE *func__create_info_page_2;
static void entry__create_info_page_2(void);
static FRAME_INFO frame__create_info_page_2 = {3, {"reference", "function_name", "info"}};
static void cont__create_info_page_3(void);
static void cont__create_info_page_4(void);
static void cont__create_info_page_5(void);
static NODE *func__create_info_page_6;
static void entry__create_info_page_6(void);
static FRAME_INFO frame__create_info_page_6 = {3, {"function_name", "info", "reference"}};
static void cont__create_info_page_7(void);
static NODE *string__3da288aac4394c18;
static NODE *string__740195f292b901ee;
static NODE *string__e4c238e2b0c78735;
static NODE *string__fa730c15f216bc6;
static void cont__create_info_page_12(void);
static void cont__create_info_page_13(void);
static void cont__create_info_page_14(void);
static NODE *func__create_info_page_15;
static void entry__create_info_page_15(void);
static FRAME_INFO frame__create_info_page_15 = {3, {"function_name", "info", "resolve_and_check_reference"}};
static void cont__create_info_page_16(void);
static NODE *string__625ae843eaa89078;
static NODE *string__5a5aee03eaa4f03b;
static void cont__create_info_page_19(void);
static NODE *func__create_info_page_20;
static void entry__create_info_page_20(void);
static FRAME_INFO frame__create_info_page_20 = {13, {"function_name", "info", "resolve_and_check_reference", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "topic_list", "examples", "remark_lines", "function_basename"}};
static void cont__create_info_page_21(void);
static void cont__create_info_page_22(void);
static NODE *func__create_info_page_23;
static void entry__create_info_page_23(void);
static FRAME_INFO frame__create_info_page_23 = {3, {"function_name", "type", "method"}};
static void cont__create_info_page_24(void);
static void cont__create_info_page_25(void);
static void cont__create_info_page_26(void);
static void cont__create_info_page_27(void);
static NODE *string__76b4bf9c06ad49bb;
static void cont__create_info_page_29(void);
static NODE *func__create_info_page_30;
static void entry__create_info_page_30(void);
static FRAME_INFO frame__create_info_page_30 = {2, {"function_name", "info"}};
static void cont__create_info_page_31(void);
static void cont__create_info_page_32(void);
static NODE *func__create_info_page_33;
static void entry__create_info_page_33(void);
static FRAME_INFO frame__create_info_page_33 = {0, {}};
static NODE *string__4ce0cf0d4ae053bd;
static NODE *func__create_info_page_35;
static void entry__create_info_page_35(void);
static FRAME_INFO frame__create_info_page_35 = {0, {}};
static NODE *string__c674570cd5378184;
static NODE *func__create_info_page_37;
static void entry__create_info_page_37(void);
static FRAME_INFO frame__create_info_page_37 = {0, {}};
static NODE *string__f7a1838e683da008;
static void cont__create_info_page_39(void);
static void cont__create_info_page_40(void);
static void cont__create_info_page_41(void);
static NODE *func__create_info_page_42;
static void entry__create_info_page_42(void);
static FRAME_INFO frame__create_info_page_42 = {1, {"remark_lines"}};
static void cont__create_info_page_43(void);
static void cont__create_info_page_44(void);
static NODE *func__create_info_page_45;
static void entry__create_info_page_45(void);
static FRAME_INFO frame__create_info_page_45 = {2, {"function_name", "info"}};
static void cont__create_info_page_46(void);
static NODE *func__create_info_page_47;
static void entry__create_info_page_47(void);
static FRAME_INFO frame__create_info_page_47 = {2, {"function_name", "info"}};
static void cont__create_info_page_48(void);
static NODE *string__6cb12e827f50f616;
static NODE *string__f3159560bf5212b5;
static NODE *string__860afb0b5f687d33;
static void cont__create_info_page_52(void);
static void cont__create_info_page_53(void);
static void cont__create_info_page_54(void);
static NODE *func__create_info_page_55;
static void entry__create_info_page_55(void);
static FRAME_INFO frame__create_info_page_55 = {12, {"remark_lines", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions", "paragraphs"}};
static void cont__create_info_page_56(void);
static NODE *func__create_info_page_57;
static void entry__create_info_page_57(void);
static FRAME_INFO frame__create_info_page_57 = {11, {"paragraph", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_and_check_reference", "short_description", "descriptions"}};
static NODE *func__create_info_page_58;
static void entry__create_info_page_58(void);
static FRAME_INFO frame__create_info_page_58 = {2, {"paragraph", "parameters"}};
static void cont__create_info_page_59(void);
static NODE *string__64f823ac322ba4f7;
static void cont__create_info_page_61(void);
static void cont__create_info_page_62(void);
static NODE *func__create_info_page_63;
static void entry__create_info_page_63(void);
static FRAME_INFO frame__create_info_page_63 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__create_info_page_64(void);
static NODE *func__create_info_page_65;
static void entry__create_info_page_65(void);
static FRAME_INFO frame__create_info_page_65 = {1, {"parameter"}};
static void cont__create_info_page_66(void);
static NODE *func__create_info_page_67;
static void entry__create_info_page_67(void);
static FRAME_INFO frame__create_info_page_67 = {1, {"parameter"}};
static void cont__create_info_page_68(void);
static void cont__create_info_page_69(void);
static NODE *string__9c8f711f20695919;
static void cont__create_info_page_71(void);
static NODE *func__create_info_page_72;
static void entry__create_info_page_72(void);
static FRAME_INFO frame__create_info_page_72 = {1, {"parameter"}};
static void cont__create_info_page_73(void);
static NODE *func__create_info_page_74;
static void entry__create_info_page_74(void);
static FRAME_INFO frame__create_info_page_74 = {1, {"parameter"}};
static void cont__create_info_page_75(void);
static void cont__create_info_page_76(void);
static NODE *string__b78062cac7fbaabb;
static void cont__create_info_page_78(void);
static NODE *func__create_info_page_79;
static void entry__create_info_page_79(void);
static FRAME_INFO frame__create_info_page_79 = {1, {"parameter"}};
static void cont__create_info_page_80(void);
static NODE *func__create_info_page_81;
static void entry__create_info_page_81(void);
static FRAME_INFO frame__create_info_page_81 = {1, {"parameter"}};
static void cont__create_info_page_82(void);
static void cont__create_info_page_83(void);
static void cont__create_info_page_84(void);
static void cont__create_info_page_85(void);
static NODE *string__c050e39b840a7454;
static NODE *string__578a5af303e9cc8;
static void cont__create_info_page_88(void);
static void cont__create_info_page_89(void);
static void cont__create_info_page_90(void);
static void cont__create_info_page_91(void);
static void cont__create_info_page_92(void);
static void cont__create_info_page_93(void);
static NODE *func__create_info_page_94;
static void entry__create_info_page_94(void);
static FRAME_INFO frame__create_info_page_94 = {2, {"paragraph", "return_values"}};
static void cont__create_info_page_95(void);
static NODE *string__98cc095015cb8089;
static void cont__create_info_page_97(void);
static void cont__create_info_page_98(void);
static NODE *func__create_info_page_99;
static void entry__create_info_page_99(void);
static FRAME_INFO frame__create_info_page_99 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__create_info_page_100(void);
static NODE *func__create_info_page_101;
static void entry__create_info_page_101(void);
static FRAME_INFO frame__create_info_page_101 = {1, {"return_value"}};
static void cont__create_info_page_102(void);
static NODE *func__create_info_page_103;
static void entry__create_info_page_103(void);
static FRAME_INFO frame__create_info_page_103 = {1, {"return_value"}};
static void cont__create_info_page_104(void);
static void cont__create_info_page_105(void);
static void cont__create_info_page_106(void);
static NODE *func__create_info_page_107;
static void entry__create_info_page_107(void);
static FRAME_INFO frame__create_info_page_107 = {1, {"return_value"}};
static void cont__create_info_page_108(void);
static NODE *func__create_info_page_109;
static void entry__create_info_page_109(void);
static FRAME_INFO frame__create_info_page_109 = {1, {"return_value"}};
static void cont__create_info_page_110(void);
static void cont__create_info_page_111(void);
static void cont__create_info_page_112(void);
static void cont__create_info_page_113(void);
static void cont__create_info_page_114(void);
static void cont__create_info_page_115(void);
static void cont__create_info_page_116(void);
static void cont__create_info_page_117(void);
static NODE *func__create_info_page_118;
static void entry__create_info_page_118(void);
static FRAME_INFO frame__create_info_page_118 = {2, {"paragraph", "references"}};
static NODE *string__76a4224cb17b643f;
static void cont__create_info_page_120(void);
static NODE *func__create_info_page_121;
static void entry__create_info_page_121(void);
static FRAME_INFO frame__create_info_page_121 = {2, {"paragraph", "references"}};
static void cont__create_info_page_122(void);
static void cont__create_info_page_123(void);
static NODE *func__create_info_page_124;
static void entry__create_info_page_124(void);
static FRAME_INFO frame__create_info_page_124 = {2, {"reference", "references"}};
static void cont__create_info_page_125(void);
static void cont__create_info_page_126(void);
static NODE *func__create_info_page_127;
static void entry__create_info_page_127(void);
static FRAME_INFO frame__create_info_page_127 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__create_info_page_128(void);
static NODE *func__create_info_page_129;
static void entry__create_info_page_129(void);
static FRAME_INFO frame__create_info_page_129 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__create_info_page_130(void);
static void cont__create_info_page_131(void);
static NODE *func__create_info_page_132;
static void entry__create_info_page_132(void);
static FRAME_INFO frame__create_info_page_132 = {4, {"topic", "topic_list", "function_name", "topic_contents"}};
static void cont__create_info_page_133(void);
static void cont__create_info_page_134(void);
static void cont__create_info_page_135(void);
static void cont__create_info_page_136(void);
static void cont__create_info_page_137(void);
static void cont__create_info_page_138(void);
static NODE *func__create_info_page_139;
static void entry__create_info_page_139(void);
static FRAME_INFO frame__create_info_page_139 = {2, {"paragraph", "examples"}};
static void cont__create_info_page_140(void);
static NODE *func__create_info_page_141;
static void entry__create_info_page_141(void);
static FRAME_INFO frame__create_info_page_141 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__create_info_page_142(void);
static void cont__create_info_page_143(void);
static void cont__create_info_page_144(void);
static void cont__create_info_page_145(void);
static void cont__create_info_page_146(void);
static void cont__create_info_page_147(void);
static NODE *func__create_info_page_148;
static void entry__create_info_page_148(void);
static FRAME_INFO frame__create_info_page_148 = {2, {"paragraph", "technical_details"}};
static NODE *string__8f3750dfc2ad5d0a;
static void cont__create_info_page_150(void);
static NODE *func__create_info_page_151;
static void entry__create_info_page_151(void);
static FRAME_INFO frame__create_info_page_151 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__create_info_page_152(void);
static void cont__create_info_page_153(void);
static void cont__create_info_page_154(void);
static NODE *func__create_info_page_155;
static void entry__create_info_page_155(void);
static FRAME_INFO frame__create_info_page_155 = {1, {"technical_details"}};
static NODE *func__create_info_page_156;
static void entry__create_info_page_156(void);
static FRAME_INFO frame__create_info_page_156 = {2, {"technical_details", "detail"}};
static void cont__create_info_page_157(void);
static NODE *func__create_info_page_158;
static void entry__create_info_page_158(void);
static FRAME_INFO frame__create_info_page_158 = {5, {"paragraph", "resolve_and_check_reference", "short_description", "technical_details", "descriptions"}};
static void cont__create_info_page_159(void);
static void cont__create_info_page_160(void);
static void cont__create_info_page_161(void);
static NODE *func__create_info_page_162;
static void entry__create_info_page_162(void);
static FRAME_INFO frame__create_info_page_162 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__create_info_page_163(void);
static void cont__create_info_page_164(void);
static void cont__create_info_page_165(void);
static void cont__create_info_page_166(void);
static void cont__create_info_page_167(void);
static void cont__create_info_page_168(void);
static void cont__create_info_page_169(void);
static void cont__create_info_page_170(void);
static NODE *func__create_info_page_171;
static void entry__create_info_page_171(void);
static FRAME_INFO frame__create_info_page_171 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__create_info_page_172(void);
static NODE *func__create_info_page_173;
static void entry__create_info_page_173(void);
static FRAME_INFO frame__create_info_page_173 = {2, {"technical_details", "paragraph"}};
static void cont__create_info_page_174(void);
static NODE *func__create_info_page_175;
static void entry__create_info_page_175(void);
static FRAME_INFO frame__create_info_page_175 = {2, {"descriptions", "paragraph"}};
static void cont__create_info_page_176(void);
static NODE *func__create_info_page_177;
static void entry__create_info_page_177(void);
static FRAME_INFO frame__create_info_page_177 = {2, {"short_description", "paragraph"}};
static void cont__create_info_page_178(void);
static void cont__create_info_page_179(void);
static void cont__create_info_page_180(void);
static NODE *func__create_info_page_181;
static void entry__create_info_page_181(void);
static FRAME_INFO frame__create_info_page_181 = {2, {"info", "parameters"}};
static void cont__create_info_page_182(void);
static NODE *func__create_info_page_183;
static void entry__create_info_page_183(void);
static FRAME_INFO frame__create_info_page_183 = {2, {"parameter", "parameters"}};
static void cont__create_info_page_184(void);
static void cont__create_info_page_185(void);
static NODE *func__create_info_page_186;
static void entry__create_info_page_186(void);
static FRAME_INFO frame__create_info_page_186 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__create_info_page_187(void);
static void cont__create_info_page_188(void);
static void cont__create_info_page_189(void);
static NODE *func__create_info_page_190;
static void entry__create_info_page_190(void);
static FRAME_INFO frame__create_info_page_190 = {2, {"parameter", "name"}};
static void cont__create_info_page_191(void);
static NODE *func__create_info_page_192;
static void entry__create_info_page_192(void);
static FRAME_INFO frame__create_info_page_192 = {2, {"parameter", "name"}};
static void cont__create_info_page_193(void);
static void cont__create_info_page_194(void);
static NODE *func__create_info_page_195;
static void entry__create_info_page_195(void);
static FRAME_INFO frame__create_info_page_195 = {2, {"name", "parameter"}};
static void cont__create_info_page_196(void);
static void cont__create_info_page_197(void);
static void cont__create_info_page_198(void);
static NODE *func__create_info_page_199;
static void entry__create_info_page_199(void);
static FRAME_INFO frame__create_info_page_199 = {1, {"name"}};
static void cont__create_info_page_200(void);
static NODE *func__create_info_page_201;
static void entry__create_info_page_201(void);
static FRAME_INFO frame__create_info_page_201 = {2, {"parameter", "name"}};
static void cont__create_info_page_202(void);
static NODE *func__create_info_page_203;
static void entry__create_info_page_203(void);
static FRAME_INFO frame__create_info_page_203 = {1, {"name"}};
static void cont__create_info_page_204(void);
static void cont__create_info_page_205(void);
static void cont__create_info_page_206(void);
static void cont__create_info_page_207(void);
static void cont__create_info_page_208(void);
static NODE *func__create_info_page_209;
static void entry__create_info_page_209(void);
static FRAME_INFO frame__create_info_page_209 = {1, {"parameter"}};
static void cont__create_info_page_210(void);
static void cont__create_info_page_211(void);
static void cont__create_info_page_212(void);
static NODE *func__create_info_page_213;
static void entry__create_info_page_213(void);
static FRAME_INFO frame__create_info_page_213 = {0, {}};
static void cont__create_info_page_214(void);
static void cont__create_info_page_215(void);
static void cont__create_info_page_216(void);
static NODE *func__create_info_page_217;
static void entry__create_info_page_217(void);
static FRAME_INFO frame__create_info_page_217 = {0, {}};
static void cont__create_info_page_218(void);
static void cont__create_info_page_219(void);
static NODE *func__create_info_page_220;
static void entry__create_info_page_220(void);
static FRAME_INFO frame__create_info_page_220 = {1, {"short_description"}};
static void cont__create_info_page_221(void);
static void cont__create_info_page_222(void);
static NODE *func__create_info_page_223;
static void entry__create_info_page_223(void);
static FRAME_INFO frame__create_info_page_223 = {1, {"parameters"}};
static NODE *string__1d61915d27bb27b2;
static void cont__create_info_page_225(void);
static NODE *func__create_info_page_226;
static void entry__create_info_page_226(void);
static FRAME_INFO frame__create_info_page_226 = {1, {"parameters"}};
static NODE *func__create_info_page_227;
static void entry__create_info_page_227(void);
static FRAME_INFO frame__create_info_page_227 = {1, {"parameter"}};
static void cont__create_info_page_228(void);
static void cont__create_info_page_229(void);
static NODE *func__create_info_page_230;
static void entry__create_info_page_230(void);
static FRAME_INFO frame__create_info_page_230 = {1, {"parameter"}};
static void cont__create_info_page_231(void);
static void cont__create_info_page_232(void);
static void cont__create_info_page_233(void);
static NODE *func__create_info_page_234;
static void entry__create_info_page_234(void);
static FRAME_INFO frame__create_info_page_234 = {1, {"return_values"}};
static void cont__create_info_page_235(void);
static NODE *func__create_info_page_236;
static void entry__create_info_page_236(void);
static FRAME_INFO frame__create_info_page_236 = {1, {"return_values"}};
static NODE *func__create_info_page_237;
static void entry__create_info_page_237(void);
static FRAME_INFO frame__create_info_page_237 = {1, {"return_value"}};
static void cont__create_info_page_238(void);
static void cont__create_info_page_239(void);
static NODE *func__create_info_page_240;
static void entry__create_info_page_240(void);
static FRAME_INFO frame__create_info_page_240 = {1, {"return_value"}};
static void cont__create_info_page_241(void);
static void cont__create_info_page_242(void);
static void cont__create_info_page_243(void);
static NODE *func__create_info_page_244;
static void entry__create_info_page_244(void);
static FRAME_INFO frame__create_info_page_244 = {1, {"descriptions"}};
static NODE *string__a8951b1f3c70ab27;
static void cont__create_info_page_246(void);
static NODE *func__create_info_page_247;
static void entry__create_info_page_247(void);
static FRAME_INFO frame__create_info_page_247 = {1, {"description"}};
static void cont__create_info_page_248(void);
static void cont__create_info_page_249(void);
static NODE *func__create_info_page_250;
static void entry__create_info_page_250(void);
static FRAME_INFO frame__create_info_page_250 = {1, {"technical_details"}};
static NODE *string__aba611e6ea1bf855;
static void cont__create_info_page_252(void);
static NODE *func__create_info_page_253;
static void entry__create_info_page_253(void);
static FRAME_INFO frame__create_info_page_253 = {1, {"detail"}};
static void cont__create_info_page_254(void);
static void cont__create_info_page_255(void);
static NODE *func__create_info_page_256;
static void entry__create_info_page_256(void);
static FRAME_INFO frame__create_info_page_256 = {2, {"references", "resolve_and_check_reference"}};
static NODE *string__6c80aed48449962f;
static void cont__create_info_page_258(void);
static NODE *func__create_info_page_259;
static void entry__create_info_page_259(void);
static FRAME_INFO frame__create_info_page_259 = {2, {"references", "resolve_and_check_reference"}};
static NODE *func__create_info_page_260;
static void entry__create_info_page_260(void);
static FRAME_INFO frame__create_info_page_260 = {2, {"reference", "resolve_and_check_reference"}};
static void cont__create_info_page_261(void);
static NODE *func__create_info_page_262;
static void entry__create_info_page_262(void);
static FRAME_INFO frame__create_info_page_262 = {1, {"reference"}};
static NODE *func__create_info_page_263;
static void entry__create_info_page_263(void);
static FRAME_INFO frame__create_info_page_263 = {1, {"reference"}};
static void cont__create_info_page_264(void);
static void cont__create_info_page_265(void);
static void cont__create_info_page_266(void);
static void cont__create_info_page_267(void);
static NODE *string__5c1f52a3813ab2ec;
static void cont__create_info_page_269(void);
static void cont__create_info_page_270(void);
static void cont__create_info_page_271(void);
static void cont__create_info_page_272(void);
static void cont__create_info_page_273(void);
static NODE *func__create_info_page_274;
static void entry__create_info_page_274(void);
static FRAME_INFO frame__create_info_page_274 = {2, {"info", "function_name"}};
static NODE *string__9db99ab8b96e438c;
static void cont__create_info_page_276(void);
static NODE *func__create_info_page_277;
static void entry__create_info_page_277(void);
static FRAME_INFO frame__create_info_page_277 = {2, {"info", "function_name"}};
static void cont__create_info_page_278(void);
static NODE *func__create_info_page_279;
static void entry__create_info_page_279(void);
static FRAME_INFO frame__create_info_page_279 = {3, {"name", "function_name", "method"}};
static void cont__create_info_page_280(void);
static NODE *func__create_info_page_281;
static void entry__create_info_page_281(void);
static FRAME_INFO frame__create_info_page_281 = {2, {"name", "method"}};
static NODE *func__create_info_page_282;
static void entry__create_info_page_282(void);
static FRAME_INFO frame__create_info_page_282 = {1, {"name"}};
static void cont__create_info_page_283(void);
static void cont__create_info_page_284(void);
static void cont__create_info_page_285(void);
static void cont__create_info_page_286(void);
static NODE *string__664d2661efdaf349;
static void cont__create_info_page_288(void);
static NODE *func__create_info_page_289;
static void entry__create_info_page_289(void);
static FRAME_INFO frame__create_info_page_289 = {1, {"method"}};
static void cont__create_info_page_290(void);
static void cont__create_info_page_291(void);
static void cont__create_info_page_292(void);
static void cont__create_info_page_293(void);
static void cont__create_info_page_294(void);
static NODE *func__create_info_page_295;
static void entry__create_info_page_295(void);
static FRAME_INFO frame__create_info_page_295 = {2, {"function_name", "polymorphic_function_name"}};
static void cont__create_info_page_296(void);
static NODE *string__3f555b992b8ba7f2;
static void cont__create_info_page_298(void);
static void cont__create_info_page_299(void);
static void cont__create_info_page_300(void);
static void cont__create_info_page_301(void);
static void cont__create_info_page_302(void);
static void cont__create_info_page_303(void);
static void cont__create_info_page_304(void);
static NODE *func__create_info_page_305;
static void entry__create_info_page_305(void);
static FRAME_INFO frame__create_info_page_305 = {2, {"info", "function_name"}};
static NODE *string__ef7adaf915740b94;
static void cont__create_info_page_307(void);
static NODE *func__create_info_page_308;
static void entry__create_info_page_308(void);
static FRAME_INFO frame__create_info_page_308 = {2, {"info", "function_name"}};
static void cont__create_info_page_309(void);
static NODE *func__create_info_page_310;
static void entry__create_info_page_310(void);
static FRAME_INFO frame__create_info_page_310 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__create_info_page_311;
static void entry__create_info_page_311(void);
static FRAME_INFO frame__create_info_page_311 = {2, {"method_name", "function_name"}};
static NODE *func__create_info_page_312;
static void entry__create_info_page_312(void);
static FRAME_INFO frame__create_info_page_312 = {1, {"method_name"}};
static void cont__create_info_page_313(void);
static void cont__create_info_page_314(void);
static void cont__create_info_page_315(void);
static void cont__create_info_page_316(void);
static void cont__create_info_page_317(void);
static NODE *func__create_info_page_318;
static void entry__create_info_page_318(void);
static FRAME_INFO frame__create_info_page_318 = {2, {"function_name", "method_name"}};
static void cont__create_info_page_319(void);
static void cont__create_info_page_320(void);
static void cont__create_info_page_321(void);
static void cont__create_info_page_322(void);
static void cont__create_info_page_323(void);
static void cont__create_info_page_324(void);
static void cont__create_info_page_325(void);
static void cont__create_info_page_326(void);
static NODE *func__create_info_page_327;
static void entry__create_info_page_327(void);
static FRAME_INFO frame__create_info_page_327 = {1, {"topic_list"}};
static NODE *string__781f541a81a2a2a4;
static void cont__create_info_page_329(void);
static NODE *func__create_info_page_330;
static void entry__create_info_page_330(void);
static FRAME_INFO frame__create_info_page_330 = {1, {"topic_list"}};
static NODE *func__create_info_page_331;
static void entry__create_info_page_331(void);
static FRAME_INFO frame__create_info_page_331 = {2, {"topic", "filename"}};
static void cont__create_info_page_332(void);
static NODE *string__578a5af303e9cbe;
static void cont__create_info_page_334(void);
static void cont__create_info_page_335(void);
static void cont__create_info_page_336(void);
static NODE *func__create_info_page_337;
static void entry__create_info_page_337(void);
static FRAME_INFO frame__create_info_page_337 = {2, {"filename", "topic"}};
static NODE *func__create_info_page_338;
static void entry__create_info_page_338(void);
static FRAME_INFO frame__create_info_page_338 = {2, {"filename", "topic"}};
static void cont__create_info_page_339(void);
static void cont__create_info_page_340(void);
static NODE *func__create_info_page_341;
static void entry__create_info_page_341(void);
static FRAME_INFO frame__create_info_page_341 = {4, {"example", "function_basename", "title", "text"}};
static void cont__create_info_page_342(void);
static void cont__create_info_page_343(void);
static void cont__create_info_page_344(void);
static void cont__create_info_page_345(void);
static void cont__create_info_page_346(void);
static NODE *string__525aeb43ea502024;
static void cont__create_info_page_348(void);
static NODE *func__create_info_page_349;
static void entry__create_info_page_349(void);
static FRAME_INFO frame__create_info_page_349 = {2, {"text", "function_basename"}};
static void cont__create_info_page_350(void);
static void cont__create_info_page_351(void);
static void cont__create_info_page_352(void);
static void cont__create_info_page_353(void);
static NODE *func__create_info_page_354;
static void entry__create_info_page_354(void);
static FRAME_INFO frame__create_info_page_354 = {1, {"string_literal"}};
static void cont__create_info_page_355(void);
static NODE *string__2d7981f4e6582bef;
static void cont__create_info_page_357(void);
static void cont__create_info_page_358(void);
static void cont__create_info_page_359(void);
static void cont__create_info_page_360(void);
static NODE *string__461f53438192a2a5;
static void cont__create_info_page_362(void);
static void cont__create_info_page_363(void);
static void cont__create_info_page_364(void);
static NODE *string__ae5520fdce447e8;
static NODE *string__2d7981f4e6402bcf;
static void cont__create_info_page_367(void);
static NODE *func__get_short_description_1;
static void entry__get_short_description_1(void);
static FRAME_INFO frame__get_short_description_1 = {4, {"name", "info", "remark_lines", "short_description"}};
static void cont__get_short_description_2(void);
static void cont__get_short_description_3(void);
static NODE *func__get_short_description_4;
static void entry__get_short_description_4(void);
static FRAME_INFO frame__get_short_description_4 = {4, {"remark_lines", "short_description", "name", "info"}};
static NODE *func__get_short_description_5;
static void entry__get_short_description_5(void);
static FRAME_INFO frame__get_short_description_5 = {3, {"break", "remark_lines", "short_description"}};
static NODE *func__get_short_description_6;
static void entry__get_short_description_6(void);
static FRAME_INFO frame__get_short_description_6 = {3, {"line", "short_description", "break"}};
static void cont__get_short_description_7(void);
static NODE *func__get_short_description_8;
static void entry__get_short_description_8(void);
static FRAME_INFO frame__get_short_description_8 = {1, {"short_description"}};
static void cont__get_short_description_9(void);
static void cont__get_short_description_10(void);
static void cont__get_short_description_11(void);
static void cont__get_short_description_12(void);
static void cont__get_short_description_13(void);
static void cont__get_short_description_14(void);
static void cont__get_short_description_15(void);
static void cont__get_short_description_16(void);
static NODE *func__get_short_description_17;
static void entry__get_short_description_17(void);
static FRAME_INFO frame__get_short_description_17 = {1, {"short_description"}};
static void cont__get_short_description_18(void);
static void cont__get_short_description_19(void);
static void cont__get_short_description_20(void);
static NODE *func__get_short_description_21;
static void entry__get_short_description_21(void);
static FRAME_INFO frame__get_short_description_21 = {3, {"name", "info", "short_description"}};
static void cont__get_short_description_22(void);
static NODE *string__10bb152df59cfc0e;
static NODE *string__8eef7e8eb4c1beaf;
static NODE *string__578a5af303e9ceb;
static void cont__get_short_description_26(void);
static void cont__get_short_description_27(void);
static void cont__get_short_description_28(void);
static NODE *func__compiler__extract_exports_1;
static void entry__compiler__extract_exports_1(void);
static FRAME_INFO frame__compiler__extract_exports_1 = {1, {"paths"}};
static void cont__compiler__extract_exports_2(void);
static void cont__compiler__extract_exports_3(void);
static void cont__compiler__extract_exports_4(void);
static NODE *func__compiler__extract_exports_5;
static void entry__compiler__extract_exports_5(void);
static FRAME_INFO frame__compiler__extract_exports_5 = {1, {"path"}};
static void cont__compiler__extract_exports_6(void);
static NODE *func__compiler__extract_exports_7;
static void entry__compiler__extract_exports_7(void);
static FRAME_INFO frame__compiler__extract_exports_7 = {3, {"iname", "info", "name"}};
static void cont__compiler__extract_exports_8(void);
static void cont__compiler__extract_exports_9(void);
static NODE *func__compiler__extract_exports_10;
static void entry__compiler__extract_exports_10(void);
static FRAME_INFO frame__compiler__extract_exports_10 = {2, {"name", "info"}};
static void cont__compiler__extract_exports_11(void);
static void cont__compiler__extract_exports_12(void);
static NODE *func__compiler__extract_exports_13;
static void entry__compiler__extract_exports_13(void);
static FRAME_INFO frame__compiler__extract_exports_13 = {1, {"info"}};
static void cont__compiler__extract_exports_14(void);
static NODE *func__compiler__extract_exports_15;
static void entry__compiler__extract_exports_15(void);
static FRAME_INFO frame__compiler__extract_exports_15 = {0, {}};
static NODE *func__compiler__extract_exports_16;
static void entry__compiler__extract_exports_16(void);
static FRAME_INFO frame__compiler__extract_exports_16 = {0, {}};
static NODE *string__2d7981f4e6282be1;
static NODE *func__compiler__extract_exports_18;
static void entry__compiler__extract_exports_18(void);
static FRAME_INFO frame__compiler__extract_exports_18 = {0, {}};
static NODE *func__compiler__extract_exports_19;
static void entry__compiler__extract_exports_19(void);
static FRAME_INFO frame__compiler__extract_exports_19 = {0, {}};
static NODE *string__2d7981f4e6202be0;
static NODE *func__compiler__extract_exports_21;
static void entry__compiler__extract_exports_21(void);
static FRAME_INFO frame__compiler__extract_exports_21 = {0, {}};
static NODE *string__fa732415f216be5;
static NODE *func__compiler__extract_exports_23;
static void entry__compiler__extract_exports_23(void);
static FRAME_INFO frame__compiler__extract_exports_23 = {0, {}};
static NODE *string__2d7981f4e6482bec;
static NODE *func__compiler__extract_exports_25;
static void entry__compiler__extract_exports_25(void);
static FRAME_INFO frame__compiler__extract_exports_25 = {0, {}};
static void cont__compiler__extract_exports_26(void);
static void cont__compiler__extract_exports_27(void);
static void cont__compiler__extract_exports_28(void);
static NODE *func__compiler__extract_exports_29;
static void entry__compiler__extract_exports_29(void);
static FRAME_INFO frame__compiler__extract_exports_29 = {4, {"method_name", "method_info", "iname", "obj_name"}};
static void cont__compiler__extract_exports_30(void);
static void cont__compiler__extract_exports_31(void);
static void cont__compiler__extract_exports_32(void);
static void cont__compiler__extract_exports_33(void);
static NODE *get__compiler__extract_exports(void) {
  return var.compiler__extract_exports;
}
static NODE *func__compiler__extract_documentation_1;
static void entry__compiler__extract_documentation_1(void);
static FRAME_INFO frame__compiler__extract_documentation_1 = {1, {"paths"}};
static void cont__compiler__extract_documentation_2(void);
static void cont__compiler__extract_documentation_3(void);
static void cont__compiler__extract_documentation_4(void);
static NODE *func__compiler__extract_documentation_5;
static void entry__compiler__extract_documentation_5(void);
static FRAME_INFO frame__compiler__extract_documentation_5 = {1, {"path"}};
static void cont__compiler__extract_documentation_6(void);
static NODE *func__compiler__extract_documentation_7;
static void entry__compiler__extract_documentation_7(void);
static FRAME_INFO frame__compiler__extract_documentation_7 = {3, {"iname", "info", "name"}};
static void cont__compiler__extract_documentation_8(void);
static void cont__compiler__extract_documentation_9(void);
static NODE *func__compiler__extract_documentation_10;
static void entry__compiler__extract_documentation_10(void);
static FRAME_INFO frame__compiler__extract_documentation_10 = {1, {"iname"}};
static NODE *string__8f47f24352a780c2;
static void cont__compiler__extract_documentation_12(void);
static void cont__compiler__extract_documentation_13(void);
static void cont__compiler__extract_documentation_14(void);
static void cont__compiler__extract_documentation_15(void);
static void cont__compiler__extract_documentation_16(void);
static void cont__compiler__extract_documentation_17(void);
static NODE *func__compiler__extract_documentation_18;
static void entry__compiler__extract_documentation_18(void);
static FRAME_INFO frame__compiler__extract_documentation_18 = {5, {"info", "iname", "name", "base", "methods"}};
static void cont__compiler__extract_documentation_19(void);
static void cont__compiler__extract_documentation_20(void);
static NODE *func__compiler__extract_documentation_21;
static void entry__compiler__extract_documentation_21(void);
static FRAME_INFO frame__compiler__extract_documentation_21 = {2, {"base", "iname"}};
static void cont__compiler__extract_documentation_22(void);
static void cont__compiler__extract_documentation_23(void);
static NODE *func__compiler__extract_documentation_24;
static void entry__compiler__extract_documentation_24(void);
static FRAME_INFO frame__compiler__extract_documentation_24 = {6, {"method_name", "method_info", "name", "methods", "sd_name", "oname"}};
static void cont__compiler__extract_documentation_25(void);
static NODE *func__compiler__extract_documentation_26;
static void entry__compiler__extract_documentation_26(void);
static FRAME_INFO frame__compiler__extract_documentation_26 = {2, {"method_name", "method_info"}};
static void cont__compiler__extract_documentation_27(void);
static void cont__compiler__extract_documentation_28(void);
static void cont__compiler__extract_documentation_29(void);
static NODE *string__578a5af303e9cce;
static void cont__compiler__extract_documentation_31(void);
static void cont__compiler__extract_documentation_32(void);
static void cont__compiler__extract_documentation_33(void);
static void cont__compiler__extract_documentation_34(void);
static void cont__compiler__extract_documentation_35(void);
static void cont__compiler__extract_documentation_36(void);
static void cont__compiler__extract_documentation_37(void);
static void cont__compiler__extract_documentation_38(void);
static void cont__compiler__extract_documentation_39(void);
static void cont__compiler__extract_documentation_40(void);
static void cont__compiler__extract_documentation_41(void);
static void cont__compiler__extract_documentation_42(void);
static void cont__compiler__extract_documentation_43(void);
static void cont__compiler__extract_documentation_44(void);
static void cont__compiler__extract_documentation_45(void);
static NODE *string__5042403361ea61f3;
static NODE *func__compiler__extract_documentation_47;
static void entry__compiler__extract_documentation_47(void);
static FRAME_INFO frame__compiler__extract_documentation_47 = {1, {"print_type_info"}};
static NODE *func__compiler__extract_documentation_48;
static void entry__compiler__extract_documentation_48(void);
static FRAME_INFO frame__compiler__extract_documentation_48 = {3, {"info", "indent", "print_type_info"}};
static NODE *func__compiler__extract_documentation_49;
static void entry__compiler__extract_documentation_49(void);
static FRAME_INFO frame__compiler__extract_documentation_49 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__compiler__extract_documentation_50(void);
static void cont__compiler__extract_documentation_51(void);
static void cont__compiler__extract_documentation_52(void);
static NODE *func__compiler__extract_documentation_53;
static void entry__compiler__extract_documentation_53(void);
static FRAME_INFO frame__compiler__extract_documentation_53 = {2, {"indent", "qname"}};
static NODE *func__compiler__extract_documentation_54;
static void entry__compiler__extract_documentation_54(void);
static FRAME_INFO frame__compiler__extract_documentation_54 = {2, {"indent", "qname"}};
static void cont__compiler__extract_documentation_55(void);
static void cont__compiler__extract_documentation_56(void);
static void cont__compiler__extract_documentation_57(void);
static void cont__compiler__extract_documentation_58(void);
static void cont__compiler__extract_documentation_59(void);
static void cont__compiler__extract_documentation_60(void);
static void cont__compiler__extract_documentation_61(void);
static NODE *func__compiler__extract_documentation_62;
static void entry__compiler__extract_documentation_62(void);
static FRAME_INFO frame__compiler__extract_documentation_62 = {1, {"remark_lines"}};
static void cont__compiler__extract_documentation_63(void);
static void cont__compiler__extract_documentation_64(void);
static void cont__compiler__extract_documentation_65(void);
static NODE *func__compiler__extract_documentation_66;
static void entry__compiler__extract_documentation_66(void);
static FRAME_INFO frame__compiler__extract_documentation_66 = {1, {"remark_lines"}};
static void cont__compiler__extract_documentation_67(void);
static void cont__compiler__extract_documentation_68(void);
static void cont__compiler__extract_documentation_69(void);
static void cont__compiler__extract_documentation_70(void);
static NODE *func__compiler__extract_documentation_71;
static void entry__compiler__extract_documentation_71(void);
static FRAME_INFO frame__compiler__extract_documentation_71 = {3, {"name", "print_type_info", "indent"}};
static void cont__compiler__extract_documentation_72(void);
static void cont__compiler__extract_documentation_73(void);
static void cont__compiler__extract_documentation_74(void);
static void cont__compiler__extract_documentation_75(void);
static NODE *func__compiler__extract_documentation_76;
static void entry__compiler__extract_documentation_76(void);
static FRAME_INFO frame__compiler__extract_documentation_76 = {1, {"print_type_info"}};
static NODE *func__compiler__extract_documentation_77;
static void entry__compiler__extract_documentation_77(void);
static FRAME_INFO frame__compiler__extract_documentation_77 = {3, {"base", "info", "print_type_info"}};
static void cont__compiler__extract_documentation_78(void);
static void cont__compiler__extract_documentation_79(void);
static NODE *func__compiler__extract_documentation_80;
static void entry__compiler__extract_documentation_80(void);
static FRAME_INFO frame__compiler__extract_documentation_80 = {1, {"info"}};
static void cont__compiler__extract_documentation_81(void);
static void cont__compiler__extract_documentation_82(void);
static void cont__compiler__extract_documentation_83(void);
static NODE *func__compiler__extract_documentation_84;
static void entry__compiler__extract_documentation_84(void);
static FRAME_INFO frame__compiler__extract_documentation_84 = {2, {"print_type_info", "info"}};
static void cont__compiler__extract_documentation_85(void);
static NODE *string__323311dc18f7db38;
static NODE *func__compiler__extract_documentation_87;
static void entry__compiler__extract_documentation_87(void);
static FRAME_INFO frame__compiler__extract_documentation_87 = {0, {}};
static void cont__compiler__extract_documentation_88(void);
static NODE *string__2d7981f4e4402ba1;
static NODE *string__565aea03eae0802f;
static void cont__compiler__extract_documentation_91(void);
static void cont__compiler__extract_documentation_92(void);
static NODE *func__compiler__extract_documentation_93;
static void entry__compiler__extract_documentation_93(void);
static FRAME_INFO frame__compiler__extract_documentation_93 = {1, {"letter"}};
static NODE *string__578a5af303e9cc2;
static void cont__compiler__extract_documentation_95(void);
static void cont__compiler__extract_documentation_96(void);
static void cont__compiler__extract_documentation_97(void);
static NODE *func__compiler__extract_documentation_98;
static void entry__compiler__extract_documentation_98(void);
static FRAME_INFO frame__compiler__extract_documentation_98 = {0, {}};
static NODE *string__578a5af303e9cc1;
static void cont__compiler__extract_documentation_100(void);
static void cont__compiler__extract_documentation_101(void);
static NODE *func__compiler__extract_documentation_102;
static void entry__compiler__extract_documentation_102(void);
static FRAME_INFO frame__compiler__extract_documentation_102 = {1, {"letter"}};
static NODE *func__compiler__extract_documentation_103;
static void entry__compiler__extract_documentation_103(void);
static FRAME_INFO frame__compiler__extract_documentation_103 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__compiler__extract_documentation_104(void);
static void cont__compiler__extract_documentation_105(void);
static void cont__compiler__extract_documentation_106(void);
static NODE *func__compiler__extract_documentation_107;
static void entry__compiler__extract_documentation_107(void);
static FRAME_INFO frame__compiler__extract_documentation_107 = {2, {"letter", "iname"}};
static void cont__compiler__extract_documentation_108(void);
static NODE *func__compiler__extract_documentation_109;
static void entry__compiler__extract_documentation_109(void);
static FRAME_INFO frame__compiler__extract_documentation_109 = {1, {"letter"}};
static NODE *string__940809d515b20094;
static void cont__compiler__extract_documentation_111(void);
static NODE *func__compiler__extract_documentation_112;
static void entry__compiler__extract_documentation_112(void);
static FRAME_INFO frame__compiler__extract_documentation_112 = {1, {"letter"}};
static void cont__compiler__extract_documentation_113(void);
static NODE *func__compiler__extract_documentation_114;
static void entry__compiler__extract_documentation_114(void);
static FRAME_INFO frame__compiler__extract_documentation_114 = {1, {"letter"}};
static void cont__compiler__extract_documentation_115(void);
static void cont__compiler__extract_documentation_116(void);
static NODE *string__441f57610192c2af;
static void cont__compiler__extract_documentation_118(void);
static NODE *string__c50d368eedcf3ba9;
static void cont__compiler__extract_documentation_120(void);
static void cont__compiler__extract_documentation_121(void);
static void cont__compiler__extract_documentation_122(void);
static void cont__compiler__extract_documentation_123(void);
static NODE *func__compiler__extract_documentation_124;
static void entry__compiler__extract_documentation_124(void);
static FRAME_INFO frame__compiler__extract_documentation_124 = {1, {"remark_lines"}};
static void cont__compiler__extract_documentation_125(void);
static void cont__compiler__extract_documentation_126(void);
static void cont__compiler__extract_documentation_127(void);
static NODE *func__compiler__extract_documentation_128;
static void entry__compiler__extract_documentation_128(void);
static FRAME_INFO frame__compiler__extract_documentation_128 = {2, {"remark", "remark_lines"}};
static void cont__compiler__extract_documentation_129(void);
static void cont__compiler__extract_documentation_130(void);
static void cont__compiler__extract_documentation_131(void);
static void cont__compiler__extract_documentation_132(void);
static NODE *func__compiler__extract_documentation_133;
static void entry__compiler__extract_documentation_133(void);
static FRAME_INFO frame__compiler__extract_documentation_133 = {0, {}};
static NODE *string__46c0af9104ada08e;
static NODE *func__compiler__extract_documentation_135;
static void entry__compiler__extract_documentation_135(void);
static FRAME_INFO frame__compiler__extract_documentation_135 = {0, {}};
static NODE *string__ed9727706924ddb4;
static NODE *func__compiler__extract_documentation_137;
static void entry__compiler__extract_documentation_137(void);
static FRAME_INFO frame__compiler__extract_documentation_137 = {0, {}};
static NODE *string__2deb4fae6a76bcfc;
static NODE *func__compiler__extract_documentation_139;
static void entry__compiler__extract_documentation_139(void);
static FRAME_INFO frame__compiler__extract_documentation_139 = {0, {}};
static NODE *string__eb5e9ee1bad4562d;
static NODE *func__compiler__extract_documentation_141;
static void entry__compiler__extract_documentation_141(void);
static FRAME_INFO frame__compiler__extract_documentation_141 = {0, {}};
static NODE *string__81158b7754be081a;
static NODE *func__compiler__extract_documentation_143;
static void entry__compiler__extract_documentation_143(void);
static FRAME_INFO frame__compiler__extract_documentation_143 = {0, {}};
static NODE *string__1de01e2461abc9b;
static NODE *func__compiler__extract_documentation_145;
static void entry__compiler__extract_documentation_145(void);
static FRAME_INFO frame__compiler__extract_documentation_145 = {0, {}};
static NODE *string__d28944592625a968;
static NODE *func__compiler__extract_documentation_147;
static void entry__compiler__extract_documentation_147(void);
static FRAME_INFO frame__compiler__extract_documentation_147 = {0, {}};
static NODE *string__46a8ad9104a4a034;
static NODE *func__compiler__extract_documentation_149;
static void entry__compiler__extract_documentation_149(void);
static FRAME_INFO frame__compiler__extract_documentation_149 = {0, {}};
static NODE *string__625ae903eae0e025;
static NODE *func__compiler__extract_documentation_151;
static void entry__compiler__extract_documentation_151(void);
static FRAME_INFO frame__compiler__extract_documentation_151 = {0, {}};
static void cont__compiler__extract_documentation_152(void);
static void cont__compiler__extract_documentation_153(void);
static NODE *func__compiler__extract_documentation_154;
static void entry__compiler__extract_documentation_154(void);
static FRAME_INFO frame__compiler__extract_documentation_154 = {2, {"remark", "kind_info"}};
static void cont__compiler__extract_documentation_155(void);
static NODE *func__compiler__extract_documentation_156;
static void entry__compiler__extract_documentation_156(void);
static FRAME_INFO frame__compiler__extract_documentation_156 = {2, {"remark", "kind_info"}};
static NODE *string__2d7981f4e6082bed;
static void cont__compiler__extract_documentation_158(void);
static NODE *func__compiler__extract_documentation_159;
static void entry__compiler__extract_documentation_159(void);
static FRAME_INFO frame__compiler__extract_documentation_159 = {2, {"remark", "kind_info"}};
static void cont__compiler__extract_documentation_160(void);
static void cont__compiler__extract_documentation_161(void);
static NODE *func__compiler__extract_documentation_162;
static void entry__compiler__extract_documentation_162(void);
static FRAME_INFO frame__compiler__extract_documentation_162 = {1, {"name"}};
static void cont__compiler__extract_documentation_163(void);
static void cont__compiler__extract_documentation_164(void);
static NODE *func__compiler__extract_documentation_165;
static void entry__compiler__extract_documentation_165(void);
static FRAME_INFO frame__compiler__extract_documentation_165 = {2, {"name", "remark"}};
static NODE *func__compiler__extract_documentation_166;
static void entry__compiler__extract_documentation_166(void);
static FRAME_INFO frame__compiler__extract_documentation_166 = {2, {"name", "remark"}};
static NODE *string__525ae943eaf00039;
static NODE *string__585aeac3ea893023;
static void cont__compiler__extract_documentation_169(void);
static void cont__compiler__extract_documentation_170(void);
static void cont__compiler__extract_documentation_171(void);
static NODE *func__compiler__extract_documentation_172;
static void entry__compiler__extract_documentation_172(void);
static FRAME_INFO frame__compiler__extract_documentation_172 = {1, {"name"}};
static void cont__compiler__extract_documentation_173(void);
static void cont__compiler__extract_documentation_174(void);
static void cont__compiler__extract_documentation_175(void);
static void cont__compiler__extract_documentation_176(void);
static void cont__compiler__extract_documentation_177(void);
static NODE *string__421f5609812a02bc;
static void cont__compiler__extract_documentation_179(void);
static void cont__compiler__extract_documentation_180(void);
static NODE *func__compiler__extract_documentation_181;
static void entry__compiler__extract_documentation_181(void);
static FRAME_INFO frame__compiler__extract_documentation_181 = {3, {"iname", "info", "name"}};
static void cont__compiler__extract_documentation_182(void);
static void cont__compiler__extract_documentation_183(void);
static void cont__compiler__extract_documentation_184(void);
static NODE *func__compiler__extract_documentation_185;
static void entry__compiler__extract_documentation_185(void);
static FRAME_INFO frame__compiler__extract_documentation_185 = {2, {"info", "name"}};
static void cont__compiler__extract_documentation_186(void);
static NODE *func__compiler__extract_documentation_187;
static void entry__compiler__extract_documentation_187(void);
static FRAME_INFO frame__compiler__extract_documentation_187 = {3, {"method_name", "method_info", "name"}};
static void cont__compiler__extract_documentation_188(void);
static void cont__compiler__extract_documentation_189(void);
static NODE *string__37b4111ed8c9af38;
static NODE *func__compiler__extract_documentation_191;
static void entry__compiler__extract_documentation_191(void);
static FRAME_INFO frame__compiler__extract_documentation_191 = {0, {}};
static void cont__compiler__extract_documentation_192(void);
static void cont__compiler__extract_documentation_193(void);
static void cont__compiler__extract_documentation_194(void);
static NODE *func__compiler__extract_documentation_195;
static void entry__compiler__extract_documentation_195(void);
static FRAME_INFO frame__compiler__extract_documentation_195 = {0, {}};
static NODE *func__compiler__extract_documentation_196;
static void entry__compiler__extract_documentation_196(void);
static FRAME_INFO frame__compiler__extract_documentation_196 = {3, {"topic", "references", "filename"}};
static void cont__compiler__extract_documentation_197(void);
static void cont__compiler__extract_documentation_198(void);
static void cont__compiler__extract_documentation_199(void);
static void cont__compiler__extract_documentation_200(void);
static NODE *func__compiler__extract_documentation_201;
static void entry__compiler__extract_documentation_201(void);
static FRAME_INFO frame__compiler__extract_documentation_201 = {2, {"filename", "topic"}};
static NODE *func__compiler__extract_documentation_202;
static void entry__compiler__extract_documentation_202(void);
static FRAME_INFO frame__compiler__extract_documentation_202 = {2, {"filename", "topic"}};
static void cont__compiler__extract_documentation_203(void);
static void cont__compiler__extract_documentation_204(void);
static NODE *func__compiler__extract_documentation_205;
static void entry__compiler__extract_documentation_205(void);
static FRAME_INFO frame__compiler__extract_documentation_205 = {3, {"topic", "references", "filename"}};
static void cont__compiler__extract_documentation_206(void);
static void cont__compiler__extract_documentation_207(void);
static void cont__compiler__extract_documentation_208(void);
static void cont__compiler__extract_documentation_209(void);
static NODE *func__compiler__extract_documentation_210;
static void entry__compiler__extract_documentation_210(void);
static FRAME_INFO frame__compiler__extract_documentation_210 = {3, {"topic", "references", "paragraphs"}};
static void cont__compiler__extract_documentation_211(void);
static void cont__compiler__extract_documentation_212(void);
static void cont__compiler__extract_documentation_213(void);
static void cont__compiler__extract_documentation_214(void);
static void cont__compiler__extract_documentation_215(void);
static NODE *func__compiler__extract_documentation_216;
static void entry__compiler__extract_documentation_216(void);
static FRAME_INFO frame__compiler__extract_documentation_216 = {1, {"paragraphs"}};
static NODE *func__compiler__extract_documentation_217;
static void entry__compiler__extract_documentation_217(void);
static FRAME_INFO frame__compiler__extract_documentation_217 = {1, {"paragraph"}};
static void cont__compiler__extract_documentation_218(void);
static void cont__compiler__extract_documentation_219(void);
static NODE *func__compiler__extract_documentation_220;
static void entry__compiler__extract_documentation_220(void);
static FRAME_INFO frame__compiler__extract_documentation_220 = {1, {"references"}};
static NODE *func__compiler__extract_documentation_221;
static void entry__compiler__extract_documentation_221(void);
static FRAME_INFO frame__compiler__extract_documentation_221 = {1, {"reference"}};
static NODE *func__compiler__extract_documentation_222;
static void entry__compiler__extract_documentation_222(void);
static FRAME_INFO frame__compiler__extract_documentation_222 = {1, {"reference"}};
static NODE *func__compiler__extract_documentation_223;
static void entry__compiler__extract_documentation_223(void);
static FRAME_INFO frame__compiler__extract_documentation_223 = {1, {"reference"}};
static void cont__compiler__extract_documentation_224(void);
static void cont__compiler__extract_documentation_225(void);
static void cont__compiler__extract_documentation_226(void);
static void cont__compiler__extract_documentation_227(void);
static void cont__compiler__extract_documentation_228(void);
static void cont__compiler__extract_documentation_229(void);
static void cont__compiler__extract_documentation_230(void);
static NODE *string__c901ef2c97c0c8f2;
static NODE *func__compiler__extract_documentation_232;
static void entry__compiler__extract_documentation_232(void);
static FRAME_INFO frame__compiler__extract_documentation_232 = {0, {}};
static NODE *string__33258a5daf8be458;
static void cont__compiler__extract_documentation_234(void);
static NODE *func__compiler__extract_documentation_235;
static void entry__compiler__extract_documentation_235(void);
static FRAME_INFO frame__compiler__extract_documentation_235 = {0, {}};
static void cont__compiler__extract_documentation_236(void);
static void cont__compiler__extract_documentation_237(void);
static NODE *func__compiler__extract_documentation_238;
static void entry__compiler__extract_documentation_238(void);
static FRAME_INFO frame__compiler__extract_documentation_238 = {0, {}};
static void cont__compiler__extract_documentation_239(void);
static void cont__compiler__extract_documentation_240(void);
static NODE *func__compiler__extract_documentation_241;
static void entry__compiler__extract_documentation_241(void);
static FRAME_INFO frame__compiler__extract_documentation_241 = {0, {}};
static void cont__compiler__extract_documentation_242(void);
static void cont__compiler__extract_documentation_243(void);
static NODE *func__compiler__extract_documentation_244;
static void entry__compiler__extract_documentation_244(void);
static FRAME_INFO frame__compiler__extract_documentation_244 = {0, {}};
static void cont__compiler__extract_documentation_245(void);
static void cont__compiler__extract_documentation_246(void);
static NODE *func__compiler__extract_documentation_247;
static void entry__compiler__extract_documentation_247(void);
static FRAME_INFO frame__compiler__extract_documentation_247 = {13, {"total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_methods", "total_inline_c_methods", "total_inline_c_types", "total_inline_c_objects", "total_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "other", "total_definitions"}};
static NODE *func__compiler__extract_documentation_248;
static void entry__compiler__extract_documentation_248(void);
static FRAME_INFO frame__compiler__extract_documentation_248 = {14, {"iname", "info", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_inline_c_functions", "total_inline_c_types", "total_inline_c_objects", "total_unique_items", "total_constants", "other", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__compiler__extract_documentation_249(void);
static NODE *func__compiler__extract_documentation_250;
static void entry__compiler__extract_documentation_250(void);
static FRAME_INFO frame__compiler__extract_documentation_250 = {1, {"total_functions"}};
static void cont__compiler__extract_documentation_251(void);
static NODE *func__compiler__extract_documentation_252;
static void entry__compiler__extract_documentation_252(void);
static FRAME_INFO frame__compiler__extract_documentation_252 = {1, {"total_polymorphic_functions"}};
static void cont__compiler__extract_documentation_253(void);
static NODE *func__compiler__extract_documentation_254;
static void entry__compiler__extract_documentation_254(void);
static FRAME_INFO frame__compiler__extract_documentation_254 = {1, {"total_polymorphic_attributes"}};
static void cont__compiler__extract_documentation_255(void);
static NODE *func__compiler__extract_documentation_256;
static void entry__compiler__extract_documentation_256(void);
static FRAME_INFO frame__compiler__extract_documentation_256 = {1, {"total_inline_c_functions"}};
static void cont__compiler__extract_documentation_257(void);
static NODE *func__compiler__extract_documentation_258;
static void entry__compiler__extract_documentation_258(void);
static FRAME_INFO frame__compiler__extract_documentation_258 = {1, {"total_inline_c_types"}};
static void cont__compiler__extract_documentation_259(void);
static NODE *func__compiler__extract_documentation_260;
static void entry__compiler__extract_documentation_260(void);
static FRAME_INFO frame__compiler__extract_documentation_260 = {1, {"total_inline_c_objects"}};
static void cont__compiler__extract_documentation_261(void);
static NODE *func__compiler__extract_documentation_262;
static void entry__compiler__extract_documentation_262(void);
static FRAME_INFO frame__compiler__extract_documentation_262 = {1, {"total_unique_items"}};
static void cont__compiler__extract_documentation_263(void);
static NODE *func__compiler__extract_documentation_264;
static void entry__compiler__extract_documentation_264(void);
static FRAME_INFO frame__compiler__extract_documentation_264 = {1, {"total_constants"}};
static void cont__compiler__extract_documentation_265(void);
static NODE *func__compiler__extract_documentation_266;
static void entry__compiler__extract_documentation_266(void);
static FRAME_INFO frame__compiler__extract_documentation_266 = {1, {"other"}};
static void cont__compiler__extract_documentation_267(void);
static void cont__compiler__extract_documentation_268(void);
static void cont__compiler__extract_documentation_269(void);
static NODE *func__compiler__extract_documentation_270;
static void entry__compiler__extract_documentation_270(void);
static FRAME_INFO frame__compiler__extract_documentation_270 = {4, {"info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__compiler__extract_documentation_271(void);
static NODE *func__compiler__extract_documentation_272;
static void entry__compiler__extract_documentation_272(void);
static FRAME_INFO frame__compiler__extract_documentation_272 = {5, {"method_name", "method_info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__compiler__extract_documentation_273(void);
static NODE *func__compiler__extract_documentation_274;
static void entry__compiler__extract_documentation_274(void);
static FRAME_INFO frame__compiler__extract_documentation_274 = {1, {"total_methods"}};
static void cont__compiler__extract_documentation_275(void);
static NODE *func__compiler__extract_documentation_276;
static void entry__compiler__extract_documentation_276(void);
static FRAME_INFO frame__compiler__extract_documentation_276 = {1, {"total_inline_c_methods"}};
static void cont__compiler__extract_documentation_277(void);
static NODE *func__compiler__extract_documentation_278;
static void entry__compiler__extract_documentation_278(void);
static FRAME_INFO frame__compiler__extract_documentation_278 = {1, {"total_attributes"}};
static void cont__compiler__extract_documentation_279(void);
static void cont__compiler__extract_documentation_280(void);
static void cont__compiler__extract_documentation_281(void);
static void cont__compiler__extract_documentation_282(void);
static void cont__compiler__extract_documentation_283(void);
static void cont__compiler__extract_documentation_284(void);
static void cont__compiler__extract_documentation_285(void);
static void cont__compiler__extract_documentation_286(void);
static void cont__compiler__extract_documentation_287(void);
static void cont__compiler__extract_documentation_288(void);
static void cont__compiler__extract_documentation_289(void);
static void cont__compiler__extract_documentation_290(void);
static void cont__compiler__extract_documentation_291(void);
static void cont__compiler__extract_documentation_292(void);
static void cont__compiler__extract_documentation_293(void);
static void cont__compiler__extract_documentation_294(void);
static void cont__compiler__extract_documentation_295(void);
static void cont__compiler__extract_documentation_296(void);
static void cont__compiler__extract_documentation_297(void);
static void cont__compiler__extract_documentation_298(void);
static void cont__compiler__extract_documentation_299(void);
static void cont__compiler__extract_documentation_300(void);
static void cont__compiler__extract_documentation_301(void);
static void cont__compiler__extract_documentation_302(void);
static void cont__compiler__extract_documentation_303(void);
static void cont__compiler__extract_documentation_304(void);
static NODE *string__f5d1f6a5c0048246;
static NODE *string__c40b62b5c2e5a063;
static NODE *string__3441ee1e4106d8f4;
static NODE *string__c035e39bd94f7acf;
static NODE *string__effbd005c6cabd2e;
static NODE *string__2b2b0af8abbb8aa7;
static NODE *string__90c6182ac0816ddd;
static NODE *string__effbd3d1268e2925;
static NODE *string__67c3eb38f5b380c4;
static NODE *string__6a2b6a88bb878aa4;
static NODE *string__ff41420da974d0d3;
static NODE *string__e400cbf53b9db9ae;
static NODE *string__4dc16ebc881e822d;
static NODE *string__e1857d0a4bd566c9;
static void cont__compiler__extract_documentation_319(void);
static NODE *get__compiler__extract_documentation(void) {
  return var.compiler__extract_documentation;
}
static void cont__47_1(void);
static void cont__62_1(void);
static void cont__62_2(void);
static void cont__62_3(void);
static void cont__62_4(void);
static void cont__62_5(void);
static void cont__62_6(void);
static void cont__62_7(void);
static NODE *string__545aef03ea835034;
static void cont__74_2(void);
static void cont__74_3(void);
static NODE *string__a89009de95dad09f;
static NODE *string__701f5257011302a3;
static void cont__75_3(void);
static void cont__75_4(void);
static void cont__75_5(void);
static void cont__75_6(void);
static void cont__75_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__47_1, NULL, 63, 63, 15, 61},
  {cont__62_1, NULL, 63, 63, 7, 62},
  {cont__62_2, NULL, 64, 64, 12, 31},
  {cont__62_3, NULL, 64, 64, 12, 46},
  {cont__62_4, NULL, 64, 64, 7, 47},
  {cont__62_5, NULL, },
  {cont__62_6, NULL, 58, 64, 1, 49},
  {cont__62_7, NULL, 409, 409, 8, 28},
  {cont__74_2, NULL, 409, 409, 1, 33},
  {cont__74_3, NULL, 410, 410, 10, 32},
  {cont__75_3, NULL, 410, 410, 40, 59},
  {cont__75_4, NULL, 410, 410, 40, 74},
  {cont__75_5, NULL, 410, 410, 35, 75},
  {cont__75_6, NULL, 410, 410, 1, 80},
  {cont__75_7, NULL, },
  {entry__create_page_4, NULL, 74, 152, 9, 11},
  {entry__create_page_3, NULL, 73, 152, 7, 12},
  {cont__create_page_6, &frame__create_page_3, 153, 153, 7, 15},
  {entry__create_page_2, NULL, 72, 153, 5, 15},
  {entry__create_page_1, NULL, 71, 153, 3, 16},
  {cont__create_page_7, &frame__create_page_1, 154, 154, 3, 20},
  {entry__extract_remark_lines_5, NULL, 168, 168, 44, 61},
  {cont__extract_remark_lines_6, &frame__extract_remark_lines_5, 168, 168, 44, 70},
  {cont__extract_remark_lines_7, &frame__extract_remark_lines_5, 168, 168, 44, 70},
  {entry__extract_remark_lines_9, NULL, 169, 169, 8, 28},
  {cont__extract_remark_lines_10, &frame__extract_remark_lines_9, 169, 169, 5, 28},
  {entry__extract_remark_lines_14, NULL, 176, 176, 11, 14},
  {entry__extract_remark_lines_15, NULL, 177, 177, 11, 14},
  {entry__extract_remark_lines_21, NULL, 181, 181, 28, 47},
  {cont__extract_remark_lines_22, &frame__extract_remark_lines_21, 181, 181, 12, 48},
  {cont__extract_remark_lines_23, &frame__extract_remark_lines_21, 181, 181, 9, 48},
  {entry__extract_remark_lines_24, NULL, 182, 182, 39, 39},
  {cont__extract_remark_lines_25, &frame__extract_remark_lines_24, 182, 182, 28, 40},
  {cont__extract_remark_lines_26, &frame__extract_remark_lines_24, 182, 182, 12, 41},
  {cont__extract_remark_lines_27, &frame__extract_remark_lines_24, 182, 182, 9, 41},
  {entry__extract_remark_lines_11, NULL, 171, 171, 7, 35},
  {cont__extract_remark_lines_12, &frame__extract_remark_lines_11, 175, 175, 11, 31},
  {cont__extract_remark_lines_13, &frame__extract_remark_lines_11, 173, 177, 7, 15},
  {cont__extract_remark_lines_16, &frame__extract_remark_lines_11, 180, 180, 29, 48},
  {cont__extract_remark_lines_17, &frame__extract_remark_lines_11, 180, 180, 13, 49},
  {cont__extract_remark_lines_18, &frame__extract_remark_lines_11, 180, 180, 13, 58},
  {cont__extract_remark_lines_19, &frame__extract_remark_lines_11, 180, 180, 9, 59},
  {cont__extract_remark_lines_20, &frame__extract_remark_lines_11, 179, 182, 7, 41},
  {entry__extract_remark_lines_1, NULL, 168, 168, 9, 29},
  {cont__extract_remark_lines_2, &frame__extract_remark_lines_1, 168, 168, 9, 38},
  {cont__extract_remark_lines_3, &frame__extract_remark_lines_1, 168, 168, 5, 39},
  {cont__extract_remark_lines_4, &frame__extract_remark_lines_1, 168, 168, 5, 70},
  {cont__extract_remark_lines_8, &frame__extract_remark_lines_1, 167, 182, 3, 43},
  {entry__extract_documentation_from_file_2, NULL, 185, 185, 24, 66},
  {cont__extract_documentation_from_file_4, &frame__extract_documentation_from_file_2, 185, 185, 15, 66},
  {entry__extract_documentation_from_file_10, NULL, 187, 187, 27, 52},
  {entry__extract_documentation_from_file_16, NULL, 188, 188, 21, 63},
  {entry__extract_documentation_from_file_23, NULL, 189, 189, 26, 71},
  {entry__extract_documentation_from_file_32, NULL, 204, 204, 39, 56},
  {cont__extract_documentation_from_file_33, &frame__extract_documentation_from_file_32, 204, 204, 56, 56},
  {entry__extract_documentation_from_file_39, NULL, 213, 213, 11, 26},
  {cont__extract_documentation_from_file_40, &frame__extract_documentation_from_file_39, 214, 214, 11, 48},
  {cont__extract_documentation_from_file_41, &frame__extract_documentation_from_file_39, 214, 214, 48, 48},
  {entry__extract_documentation_from_file_42, NULL, 216, 216, 11, 14},
  {entry__extract_documentation_from_file_43, NULL, 211, 211, 11, 14},
  {entry__extract_documentation_from_file_36, NULL, 209, 209, 12, 30},
  {cont__extract_documentation_from_file_37, &frame__extract_documentation_from_file_36, 209, 209, 12, 33},
  {cont__extract_documentation_from_file_38, &frame__extract_documentation_from_file_36, 209, 216, 7, 15},
  {entry__extract_documentation_from_file_35, NULL, 208, 216, 5, 16},
  {cont__extract_documentation_from_file_44, &frame__extract_documentation_from_file_35, 216, 216, 16, 16},
  {entry__extract_documentation_from_file_48, NULL, 218, 218, 46, 70},
  {cont__extract_documentation_from_file_49, &frame__extract_documentation_from_file_48, 218, 218, 34, 70},
  {cont__extract_documentation_from_file_50, &frame__extract_documentation_from_file_48, 218, 218, 70, 70},
  {entry__extract_documentation_from_file_53, NULL, 219, 219, 32, 54},
  {cont__extract_documentation_from_file_55, &frame__extract_documentation_from_file_53, 219, 219, 59, 59},
  {entry__extract_documentation_from_file_60, NULL, 223, 223, 33, 36},
  {entry__extract_documentation_from_file_58, NULL, 223, 223, 10, 30},
  {cont__extract_documentation_from_file_59, &frame__extract_documentation_from_file_58, 223, 223, 7, 36},
  {entry__extract_documentation_from_file_63, NULL, 224, 224, 31, 34},
  {entry__extract_documentation_from_file_61, NULL, 224, 224, 10, 28},
  {cont__extract_documentation_from_file_62, &frame__extract_documentation_from_file_61, 224, 224, 7, 34},
  {entry__extract_documentation_from_file_78, NULL, 232, 232, 43, 68},
  {cont__extract_documentation_from_file_79, &frame__extract_documentation_from_file_78, 232, 232, 35, 69},
  {cont__extract_documentation_from_file_80, &frame__extract_documentation_from_file_78, 232, 232, 15, 70},
  {cont__extract_documentation_from_file_81, &frame__extract_documentation_from_file_78, 232, 232, 75, 75},
  {entry__extract_documentation_from_file_74, NULL, 230, 230, 21, 43},
  {cont__extract_documentation_from_file_75, &frame__extract_documentation_from_file_74, 230, 230, 13, 46},
  {cont__extract_documentation_from_file_76, &frame__extract_documentation_from_file_74, 231, 231, 16, 56},
  {cont__extract_documentation_from_file_77, &frame__extract_documentation_from_file_74, 231, 232, 13, 75},
  {entry__extract_documentation_from_file_70, NULL, 228, 228, 11, 48},
  {cont__extract_documentation_from_file_71, &frame__extract_documentation_from_file_70, 229, 229, 18, 41},
  {cont__extract_documentation_from_file_72, &frame__extract_documentation_from_file_70, 229, 229, 18, 52},
  {cont__extract_documentation_from_file_73, &frame__extract_documentation_from_file_70, 229, 232, 11, 76},
  {entry__extract_documentation_from_file_66, NULL, 226, 226, 22, 44},
  {cont__extract_documentation_from_file_67, &frame__extract_documentation_from_file_66, 226, 226, 9, 47},
  {cont__extract_documentation_from_file_68, &frame__extract_documentation_from_file_66, 227, 227, 12, 38},
  {cont__extract_documentation_from_file_69, &frame__extract_documentation_from_file_66, 227, 232, 9, 77},
  {entry__extract_documentation_from_file_64, NULL, 225, 225, 10, 35},
  {cont__extract_documentation_from_file_65, &frame__extract_documentation_from_file_64, 225, 232, 7, 78},
  {entry__extract_documentation_from_file_57, NULL, 222, 232, 5, 79},
  {entry__extract_documentation_from_file_95, NULL, 246, 246, 29, 55},
  {cont__extract_documentation_from_file_96, &frame__extract_documentation_from_file_95, 246, 246, 17, 56},
  {cont__extract_documentation_from_file_97, &frame__extract_documentation_from_file_95, 247, 247, 60, 64},
  {cont__extract_documentation_from_file_98, &frame__extract_documentation_from_file_95, 247, 247, 67, 67},
  {cont__extract_documentation_from_file_99, &frame__extract_documentation_from_file_95, 247, 247, 17, 68},
  {cont__extract_documentation_from_file_100, &frame__extract_documentation_from_file_95, 247, 247, 17, 41},
  {cont__extract_documentation_from_file_101, &frame__extract_documentation_from_file_95, 248, 248, 17, 20},
  {entry__extract_documentation_from_file_93, NULL, 245, 245, 18, 48},
  {cont__extract_documentation_from_file_94, &frame__extract_documentation_from_file_93, 245, 248, 15, 20},
  {entry__extract_documentation_from_file_92, NULL, 244, 248, 13, 21},
  {cont__extract_documentation_from_file_102, &frame__extract_documentation_from_file_92, 248, 248, 21, 21},
  {entry__extract_documentation_from_file_90, NULL, 242, 242, 11, 48},
  {cont__extract_documentation_from_file_91, &frame__extract_documentation_from_file_90, 243, 248, 11, 22},
  {entry__extract_documentation_from_file_86, NULL, 240, 240, 9, 48},
  {cont__extract_documentation_from_file_87, &frame__extract_documentation_from_file_86, 241, 241, 12, 51},
  {cont__extract_documentation_from_file_89, &frame__extract_documentation_from_file_86, 241, 248, 9, 23},
  {entry__extract_documentation_from_file_84, NULL, 239, 239, 10, 30},
  {cont__extract_documentation_from_file_85, &frame__extract_documentation_from_file_84, 239, 248, 7, 24},
  {entry__extract_documentation_from_file_120, NULL, 266, 266, 30, 43},
  {cont__extract_documentation_from_file_121, &frame__extract_documentation_from_file_120, 266, 266, 27, 43},
  {entry__extract_documentation_from_file_122, NULL, 267, 267, 27, 38},
  {entry__extract_documentation_from_file_116, NULL, 258, 258, 19, 42},
  {cont__extract_documentation_from_file_117, &frame__extract_documentation_from_file_116, 262, 262, 32, 51},
  {cont__extract_documentation_from_file_118, &frame__extract_documentation_from_file_116, 265, 265, 27, 41},
  {cont__extract_documentation_from_file_119, &frame__extract_documentation_from_file_116, 266, 266, 27, 43},
  {cont__extract_documentation_from_file_123, &frame__extract_documentation_from_file_116, 268, 268, 40, 65},
  {cont__extract_documentation_from_file_124, &frame__extract_documentation_from_file_116, 259, 259, 32, 59},
  {cont__extract_documentation_from_file_125, &frame__extract_documentation_from_file_116, 259, 259, 19, 60},
  {cont__extract_documentation_from_file_126, &frame__extract_documentation_from_file_116, 269, 269, 45, 45},
  {entry__extract_documentation_from_file_114, NULL, 257, 257, 20, 39},
  {cont__extract_documentation_from_file_115, &frame__extract_documentation_from_file_114, 257, 269, 17, 45},
  {entry__extract_documentation_from_file_127, NULL, 274, 274, 30, 49},
  {cont__extract_documentation_from_file_128, &frame__extract_documentation_from_file_127, 275, 275, 38, 63},
  {cont__extract_documentation_from_file_129, &frame__extract_documentation_from_file_127, 271, 271, 30, 57},
  {cont__extract_documentation_from_file_130, &frame__extract_documentation_from_file_127, 271, 271, 17, 58},
  {cont__extract_documentation_from_file_131, &frame__extract_documentation_from_file_127, 276, 276, 43, 43},
  {entry__extract_documentation_from_file_111, NULL, 254, 254, 13, 37},
  {cont__extract_documentation_from_file_112, &frame__extract_documentation_from_file_111, 255, 255, 18, 35},
  {cont__extract_documentation_from_file_113, &frame__extract_documentation_from_file_111, 255, 276, 13, 44},
  {entry__extract_documentation_from_file_108, NULL, 252, 252, 11, 45},
  {cont__extract_documentation_from_file_109, &frame__extract_documentation_from_file_108, 253, 253, 14, 33},
  {cont__extract_documentation_from_file_110, &frame__extract_documentation_from_file_108, 253, 276, 11, 45},
  {entry__extract_documentation_from_file_105, NULL, 250, 250, 9, 44},
  {cont__extract_documentation_from_file_106, &frame__extract_documentation_from_file_105, 251, 251, 12, 32},
  {cont__extract_documentation_from_file_107, &frame__extract_documentation_from_file_105, 251, 276, 9, 46},
  {entry__extract_documentation_from_file_103, NULL, 249, 249, 10, 28},
  {cont__extract_documentation_from_file_104, &frame__extract_documentation_from_file_103, 249, 276, 7, 47},
  {entry__extract_documentation_from_file_145, NULL, 291, 291, 45, 60},
  {cont__extract_documentation_from_file_146, &frame__extract_documentation_from_file_145, 291, 291, 41, 61},
  {cont__extract_documentation_from_file_147, &frame__extract_documentation_from_file_145, 291, 291, 38, 61},
  {entry__extract_documentation_from_file_162, NULL, 304, 304, 25, 48},
  {entry__extract_documentation_from_file_163, NULL, 305, 305, 25, 47},
  {entry__extract_documentation_from_file_159, NULL, 298, 298, 17, 54},
  {cont__extract_documentation_from_file_160, &frame__extract_documentation_from_file_159, 303, 303, 25, 42},
  {cont__extract_documentation_from_file_161, &frame__extract_documentation_from_file_159, },
  {cont__extract_documentation_from_file_164, &frame__extract_documentation_from_file_159, 299, 299, 17, 35},
  {cont__extract_documentation_from_file_165, &frame__extract_documentation_from_file_159, 306, 306, 17, 21},
  {entry__extract_documentation_from_file_157, NULL, 297, 297, 18, 58},
  {cont__extract_documentation_from_file_158, &frame__extract_documentation_from_file_157, 297, 306, 15, 21},
  {entry__extract_documentation_from_file_168, NULL, 311, 311, 34, 54},
  {cont__extract_documentation_from_file_169, &frame__extract_documentation_from_file_168, 312, 312, 36, 66},
  {cont__extract_documentation_from_file_170, &frame__extract_documentation_from_file_168, 312, 312, 67, 67},
  {entry__extract_documentation_from_file_166, NULL, 307, 307, 18, 33},
  {cont__extract_documentation_from_file_167, &frame__extract_documentation_from_file_166, 307, 312, 15, 67},
  {entry__extract_documentation_from_file_174, NULL, 313, 313, 68, 68},
  {entry__extract_documentation_from_file_172, NULL, 313, 313, 18, 35},
  {cont__extract_documentation_from_file_173, &frame__extract_documentation_from_file_172, 313, 313, 15, 68},
  {entry__extract_documentation_from_file_180, NULL, 316, 316, 19, 48},
  {cont__extract_documentation_from_file_181, &frame__extract_documentation_from_file_180, 316, 316, 48, 48},
  {entry__extract_documentation_from_file_177, NULL, 315, 315, 20, 39},
  {cont__extract_documentation_from_file_178, &frame__extract_documentation_from_file_177, 315, 315, 20, 50},
  {cont__extract_documentation_from_file_179, &frame__extract_documentation_from_file_177, 315, 316, 17, 48},
  {entry__extract_documentation_from_file_175, NULL, 314, 314, 18, 40},
  {cont__extract_documentation_from_file_176, &frame__extract_documentation_from_file_175, 314, 316, 15, 49},
  {entry__extract_documentation_from_file_184, NULL, 318, 318, 17, 35},
  {cont__extract_documentation_from_file_185, &frame__extract_documentation_from_file_184, 319, 319, 17, 21},
  {entry__extract_documentation_from_file_182, NULL, 317, 317, 18, 49},
  {cont__extract_documentation_from_file_183, &frame__extract_documentation_from_file_182, 317, 319, 15, 21},
  {entry__extract_documentation_from_file_188, NULL, 320, 320, 61, 61},
  {entry__extract_documentation_from_file_186, NULL, 320, 320, 18, 37},
  {cont__extract_documentation_from_file_187, &frame__extract_documentation_from_file_186, 320, 320, 15, 61},
  {entry__extract_documentation_from_file_197, NULL, 326, 326, 21, 64},
  {cont__extract_documentation_from_file_198, &frame__extract_documentation_from_file_197, 327, 327, 21, 80},
  {cont__extract_documentation_from_file_199, &frame__extract_documentation_from_file_197, 328, 328, 21, 68},
  {cont__extract_documentation_from_file_200, &frame__extract_documentation_from_file_197, 328, 328, 68, 68},
  {entry__extract_documentation_from_file_194, NULL, 325, 325, 22, 49},
  {cont__extract_documentation_from_file_195, &frame__extract_documentation_from_file_194, 325, 325, 22, 66},
  {cont__extract_documentation_from_file_196, &frame__extract_documentation_from_file_194, 325, 328, 19, 68},
  {entry__extract_documentation_from_file_191, NULL, 323, 323, 17, 55},
  {cont__extract_documentation_from_file_192, &frame__extract_documentation_from_file_191, 324, 324, 20, 49},
  {cont__extract_documentation_from_file_193, &frame__extract_documentation_from_file_191, 324, 328, 17, 69},
  {cont__extract_documentation_from_file_201, &frame__extract_documentation_from_file_191, 329, 329, 17, 35},
  {cont__extract_documentation_from_file_202, &frame__extract_documentation_from_file_191, 329, 329, 40, 40},
  {entry__extract_documentation_from_file_216, NULL, 342, 342, 62, 62},
  {entry__extract_documentation_from_file_213, NULL, 341, 341, 28, 45},
  {cont__extract_documentation_from_file_214, &frame__extract_documentation_from_file_213, 341, 341, 28, 56},
  {cont__extract_documentation_from_file_215, &frame__extract_documentation_from_file_213, 341, 342, 21, 62},
  {cont__extract_documentation_from_file_217, &frame__extract_documentation_from_file_213, 343, 343, 48, 65},
  {cont__extract_documentation_from_file_218, &frame__extract_documentation_from_file_213, 343, 343, 21, 78},
  {cont__extract_documentation_from_file_219, &frame__extract_documentation_from_file_213, 345, 345, 22, 42},
  {cont__extract_documentation_from_file_220, &frame__extract_documentation_from_file_213, 345, 345, 21, 53},
  {cont__extract_documentation_from_file_221, &frame__extract_documentation_from_file_213, 346, 346, 21, 39},
  {cont__extract_documentation_from_file_222, &frame__extract_documentation_from_file_213, 346, 346, 50, 50},
  {entry__extract_documentation_from_file_210, NULL, 339, 339, 19, 43},
  {cont__extract_documentation_from_file_211, &frame__extract_documentation_from_file_210, 340, 340, 26, 54},
  {cont__extract_documentation_from_file_212, &frame__extract_documentation_from_file_210, 340, 346, 19, 50},
  {entry__extract_documentation_from_file_204, NULL, 331, 331, 17, 48},
  {cont__extract_documentation_from_file_205, &frame__extract_documentation_from_file_204, 334, 334, 33, 50},
  {cont__extract_documentation_from_file_206, &frame__extract_documentation_from_file_204, 334, 334, 19, 63},
  {cont__extract_documentation_from_file_207, &frame__extract_documentation_from_file_204, 337, 337, 17, 35},
  {cont__extract_documentation_from_file_208, &frame__extract_documentation_from_file_204, 338, 338, 20, 34},
  {cont__extract_documentation_from_file_209, &frame__extract_documentation_from_file_204, 338, 346, 17, 51},
  {entry__extract_documentation_from_file_144, NULL, 284, 284, 13, 37},
  {cont__extract_documentation_from_file_148, &frame__extract_documentation_from_file_144, 285, 285, 13, 47},
  {cont__extract_documentation_from_file_149, &frame__extract_documentation_from_file_144, 287, 287, 24, 43},
  {cont__extract_documentation_from_file_150, &frame__extract_documentation_from_file_144, 288, 288, 33, 61},
  {cont__extract_documentation_from_file_151, &frame__extract_documentation_from_file_144, 289, 289, 32, 62},
  {cont__extract_documentation_from_file_152, &frame__extract_documentation_from_file_144, 294, 294, 32, 54},
  {cont__extract_documentation_from_file_153, &frame__extract_documentation_from_file_144, 294, 294, 59, 59},
  {cont__extract_documentation_from_file_154, &frame__extract_documentation_from_file_144, 294, 294, 26, 60},
  {cont__extract_documentation_from_file_155, &frame__extract_documentation_from_file_144, 293, 294, 13, 77},
  {cont__extract_documentation_from_file_156, &frame__extract_documentation_from_file_144, 296, 320, 13, 61},
  {cont__extract_documentation_from_file_189, &frame__extract_documentation_from_file_144, 321, 321, 18, 47},
  {cont__extract_documentation_from_file_190, &frame__extract_documentation_from_file_144, 330, 330, 15, 41},
  {cont__extract_documentation_from_file_203, &frame__extract_documentation_from_file_144, 321, 346, 13, 53},
  {entry__extract_documentation_from_file_140, NULL, 281, 281, 11, 48},
  {cont__extract_documentation_from_file_141, &frame__extract_documentation_from_file_140, 282, 282, 11, 45},
  {cont__extract_documentation_from_file_142, &frame__extract_documentation_from_file_140, 283, 283, 14, 33},
  {cont__extract_documentation_from_file_143, &frame__extract_documentation_from_file_140, 283, 346, 11, 54},
  {entry__extract_documentation_from_file_136, NULL, 278, 278, 22, 44},
  {cont__extract_documentation_from_file_137, &frame__extract_documentation_from_file_136, 278, 278, 22, 47},
  {cont__extract_documentation_from_file_138, &frame__extract_documentation_from_file_136, 280, 280, 12, 38},
  {cont__extract_documentation_from_file_139, &frame__extract_documentation_from_file_136, 280, 346, 9, 55},
  {entry__extract_documentation_from_file_134, NULL, 277, 277, 10, 35},
  {cont__extract_documentation_from_file_135, &frame__extract_documentation_from_file_134, 277, 346, 7, 56},
  {entry__extract_documentation_from_file_83, NULL, 238, 346, 5, 57},
  {cont__extract_documentation_from_file_223, &frame__extract_documentation_from_file_83, 346, 346, 57, 57},
  {entry__extract_documentation_from_file_1, NULL, 185, 185, 3, 66},
  {cont__extract_documentation_from_file_5, &frame__extract_documentation_from_file_1, 186, 186, 8, 21},
  {cont__extract_documentation_from_file_6, &frame__extract_documentation_from_file_1, 186, 186, 3, 31},
  {cont__extract_documentation_from_file_7, &frame__extract_documentation_from_file_1, 187, 187, 6, 19},
  {cont__extract_documentation_from_file_8, &frame__extract_documentation_from_file_1, 187, 187, 6, 24},
  {cont__extract_documentation_from_file_9, &frame__extract_documentation_from_file_1, 187, 187, 3, 52},
  {cont__extract_documentation_from_file_12, &frame__extract_documentation_from_file_1, 188, 188, 6, 11},
  {cont__extract_documentation_from_file_13, &frame__extract_documentation_from_file_1, 188, 188, 6, 18},
  {cont__extract_documentation_from_file_14, &frame__extract_documentation_from_file_1, 188, 188, 6, 18},
  {cont__extract_documentation_from_file_15, &frame__extract_documentation_from_file_1, 188, 188, 3, 63},
  {cont__extract_documentation_from_file_18, &frame__extract_documentation_from_file_1, 189, 189, 11, 11},
  {cont__extract_documentation_from_file_19, &frame__extract_documentation_from_file_1, 189, 189, 6, 12},
  {cont__extract_documentation_from_file_20, &frame__extract_documentation_from_file_1, 189, 189, 6, 23},
  {cont__extract_documentation_from_file_21, &frame__extract_documentation_from_file_1, 189, 189, 6, 23},
  {cont__extract_documentation_from_file_22, &frame__extract_documentation_from_file_1, 189, 189, 3, 71},
  {cont__extract_documentation_from_file_25, &frame__extract_documentation_from_file_1, 192, 192, 17, 48},
  {cont__extract_documentation_from_file_27, &frame__extract_documentation_from_file_1, 192, 192, 50, 59},
  {cont__extract_documentation_from_file_29, &frame__extract_documentation_from_file_1, 191, 193, 3, 69},
  {cont__extract_documentation_from_file_30, &frame__extract_documentation_from_file_1, 203, 203, 3, 37},
  {cont__extract_documentation_from_file_31, &frame__extract_documentation_from_file_1, 204, 204, 3, 56},
  {cont__extract_documentation_from_file_34, &frame__extract_documentation_from_file_1, 207, 216, 3, 17},
  {cont__extract_documentation_from_file_45, &frame__extract_documentation_from_file_1, 217, 217, 31, 31},
  {cont__extract_documentation_from_file_46, &frame__extract_documentation_from_file_1, 217, 217, 3, 31},
  {cont__extract_documentation_from_file_47, &frame__extract_documentation_from_file_1, 218, 218, 3, 70},
  {cont__extract_documentation_from_file_51, &frame__extract_documentation_from_file_1, 219, 219, 6, 29},
  {cont__extract_documentation_from_file_52, &frame__extract_documentation_from_file_1, 219, 219, 3, 59},
  {cont__extract_documentation_from_file_56, &frame__extract_documentation_from_file_1, 221, 232, 3, 80},
  {cont__extract_documentation_from_file_82, &frame__extract_documentation_from_file_1, 233, 346, 3, 58},
  {cont__extract_documentation_from_file_224, &frame__extract_documentation_from_file_1, 346, 346, 58, 58},
  {entry__extract_documentation_from_directory_8, NULL, 352, 352, 32, 72},
  {entry__extract_documentation_from_directory_6, NULL, 352, 352, 10, 29},
  {cont__extract_documentation_from_directory_7, &frame__extract_documentation_from_directory_6, 352, 352, 7, 72},
  {entry__extract_documentation_from_directory_11, NULL, 353, 353, 36, 71},
  {entry__extract_documentation_from_directory_9, NULL, 353, 353, 10, 33},
  {cont__extract_documentation_from_directory_10, &frame__extract_documentation_from_directory_9, 353, 353, 7, 71},
  {entry__extract_documentation_from_directory_4, NULL, 350, 350, 5, 28},
  {cont__extract_documentation_from_directory_5, &frame__extract_documentation_from_directory_4, 351, 353, 5, 71},
  {entry__extract_documentation_from_directory_1, NULL, 349, 349, 22, 27},
  {cont__extract_documentation_from_directory_2, &frame__extract_documentation_from_directory_1, 349, 349, 12, 33},
  {cont__extract_documentation_from_directory_3, &frame__extract_documentation_from_directory_1, 349, 353, 3, 72},
  {entry__resolved_name_5, NULL, 359, 359, 8, 21},
  {cont__resolved_name_6, &frame__resolved_name_5, 359, 359, 5, 21},
  {entry__resolved_name_13, NULL, 365, 366, 19, 66},
  {cont__resolved_name_16, &frame__resolved_name_13, 365, 366, 13, 66},
  {entry__resolved_name_11, NULL, 364, 364, 14, 42},
  {cont__resolved_name_12, &frame__resolved_name_11, 364, 366, 11, 67},
  {cont__resolved_name_17, &frame__resolved_name_11, 367, 367, 39, 39},
  {entry__resolved_name_9, NULL, 363, 363, 12, 48},
  {cont__resolved_name_10, &frame__resolved_name_9, 363, 367, 9, 39},
  {entry__resolved_name_20, NULL, 369, 370, 15, 53},
  {cont__resolved_name_22, &frame__resolved_name_20, 369, 370, 9, 53},
  {entry__resolved_name_7, NULL, 362, 362, 16, 39},
  {cont__resolved_name_8, &frame__resolved_name_7, 362, 367, 7, 40},
  {cont__resolved_name_18, &frame__resolved_name_7, 368, 368, 14, 42},
  {cont__resolved_name_19, &frame__resolved_name_7, 368, 370, 7, 54},
  {cont__resolved_name_23, &frame__resolved_name_7, 371, 371, 10, 45},
  {cont__resolved_name_25, &frame__resolved_name_7, 371, 371, 7, 45},
  {entry__resolved_name_1, NULL, 356, 356, 3, 21},
  {cont__resolved_name_2, &frame__resolved_name_1, 358, 358, 5, 22},
  {cont__resolved_name_3, &frame__resolved_name_1, 358, 358, 5, 33},
  {cont__resolved_name_4, &frame__resolved_name_1, 357, 371, 3, 46},
  {entry__add_derived_type_15, NULL, 381, 381, 35, 69},
  {entry__add_derived_type_12, NULL, 380, 380, 7, 39},
  {cont__add_derived_type_13, &frame__add_derived_type_12, 381, 381, 10, 32},
  {cont__add_derived_type_14, &frame__add_derived_type_12, 381, 381, 7, 69},
  {entry__add_derived_type_7, NULL, 377, 377, 6, 32},
  {cont__add_derived_type_8, &frame__add_derived_type_7, 377, 377, 5, 38},
  {cont__add_derived_type_9, &frame__add_derived_type_7, 378, 378, 12, 30},
  {cont__add_derived_type_10, &frame__add_derived_type_7, 378, 378, 12, 47},
  {cont__add_derived_type_11, &frame__add_derived_type_7, 378, 381, 5, 69},
  {cont__add_derived_type_16, &frame__add_derived_type_7, 382, 382, 5, 23},
  {cont__add_derived_type_17, &frame__add_derived_type_7, 382, 382, 34, 34},
  {entry__add_derived_type_1, NULL, 374, 374, 23, 40},
  {cont__add_derived_type_2, &frame__add_derived_type_1, 374, 374, 42, 59},
  {cont__add_derived_type_3, &frame__add_derived_type_1, 374, 374, 3, 60},
  {cont__add_derived_type_4, &frame__add_derived_type_1, 375, 375, 3, 33},
  {cont__add_derived_type_5, &frame__add_derived_type_1, 376, 376, 6, 26},
  {cont__add_derived_type_6, &frame__add_derived_type_1, 376, 382, 3, 34},
  {entry__mangled_1, NULL, 384, 384, 38, 48},
  {cont__mangled_2, &frame__mangled_1, 384, 384, 50, 60},
  {cont__mangled_4, &frame__mangled_1, 384, 384, 21, 61},
  {cont__mangled_5, &frame__mangled_1, 384, 384, 18, 61},
  {entry__ordered_name_1, NULL, 389, 389, 7, 24},
  {cont__ordered_name_2, &frame__ordered_name_1, 391, 391, 7, 29},
  {cont__ordered_name_3, &frame__ordered_name_1, },
  {cont__ordered_name_4, &frame__ordered_name_1, 387, 395, 3, 16},
  {entry__link_bar_2, NULL, 399, 399, 7, 27},
  {cont__link_bar_5, &frame__link_bar_2, 399, 399, 5, 34},
  {cont__link_bar_7, &frame__link_bar_2, 400, 400, 5, 29},
  {cont__link_bar_9, &frame__link_bar_2, 401, 401, 7, 28},
  {cont__link_bar_11, &frame__link_bar_2, 401, 401, 5, 37},
  {cont__link_bar_13, &frame__link_bar_2, 402, 402, 5, 29},
  {cont__link_bar_14, &frame__link_bar_2, 403, 403, 7, 32},
  {cont__link_bar_16, &frame__link_bar_2, 403, 403, 5, 45},
  {cont__link_bar_18, &frame__link_bar_2, 404, 404, 5, 29},
  {cont__link_bar_19, &frame__link_bar_2, 405, 405, 7, 34},
  {cont__link_bar_21, &frame__link_bar_2, 405, 405, 5, 49},
  {cont__link_bar_23, &frame__link_bar_2, 406, 406, 5, 29},
  {cont__link_bar_24, &frame__link_bar_2, 407, 407, 7, 34},
  {cont__link_bar_26, &frame__link_bar_2, 407, 407, 5, 49},
  {entry__link_bar_1, NULL, 398, 407, 3, 49},
  {entry__to_paragraphs_5, NULL, 421, 421, 13, 22},
  {cont__to_paragraphs_6, &frame__to_paragraphs_5, 422, 422, 13, 33},
  {cont__to_paragraphs_7, &frame__to_paragraphs_5, 423, 423, 22, 22},
  {entry__to_paragraphs_8, NULL, 425, 425, 13, 33},
  {cont__to_paragraphs_9, &frame__to_paragraphs_8, 425, 425, 33, 33},
  {entry__to_paragraphs_3, NULL, 420, 420, 11, 35},
  {cont__to_paragraphs_4, &frame__to_paragraphs_3, 419, 425, 9, 34},
  {entry__to_paragraphs_15, NULL, 430, 430, 15, 35},
  {cont__to_paragraphs_16, &frame__to_paragraphs_15, 431, 431, 22, 22},
  {entry__to_paragraphs_12, NULL, 429, 429, 16, 25},
  {cont__to_paragraphs_13, &frame__to_paragraphs_12, 429, 429, 16, 25},
  {cont__to_paragraphs_14, &frame__to_paragraphs_12, 429, 431, 13, 22},
  {entry__to_paragraphs_21, NULL, 435, 435, 60, 60},
  {entry__to_paragraphs_19, NULL, 435, 435, 20, 44},
  {cont__to_paragraphs_20, &frame__to_paragraphs_19, 435, 435, 17, 60},
  {entry__to_paragraphs_22, NULL, 437, 437, 17, 30},
  {cont__to_paragraphs_23, &frame__to_paragraphs_22, 437, 437, 30, 30},
  {entry__to_paragraphs_17, NULL, 434, 434, 15, 24},
  {cont__to_paragraphs_18, &frame__to_paragraphs_17, 433, 437, 13, 31},
  {cont__to_paragraphs_24, &frame__to_paragraphs_17, 438, 438, 26, 34},
  {cont__to_paragraphs_25, &frame__to_paragraphs_17, 438, 438, 13, 34},
  {cont__to_paragraphs_26, &frame__to_paragraphs_17, 438, 438, 34, 34},
  {entry__to_paragraphs_10, NULL, 428, 428, 11, 20},
  {cont__to_paragraphs_11, &frame__to_paragraphs_10, 427, 438, 9, 35},
  {entry__to_paragraphs_2, NULL, 417, 438, 5, 37},
  {entry__to_paragraphs_30, NULL, 439, 439, 18, 38},
  {cont__to_paragraphs_31, &frame__to_paragraphs_30, 439, 439, 38, 38},
  {entry__to_paragraphs_1, NULL, 416, 438, 3, 38},
  {cont__to_paragraphs_27, &frame__to_paragraphs_1, 439, 439, 6, 15},
  {cont__to_paragraphs_28, &frame__to_paragraphs_1, 439, 439, 6, 15},
  {cont__to_paragraphs_29, &frame__to_paragraphs_1, 439, 439, 3, 38},
  {cont__to_paragraphs_32, &frame__to_paragraphs_1, 440, 440, 3, 15},
  {entry__resolve_reference_7, NULL, 447, 447, 41, 67},
  {cont__resolve_reference_9, &frame__resolve_reference_7, 447, 447, 67, 67},
  {entry__resolve_reference_12, NULL, 448, 448, 43, 69},
  {cont__resolve_reference_14, &frame__resolve_reference_12, 448, 448, 69, 69},
  {entry__resolve_reference_3, NULL, 445, 445, 7, 40},
  {cont__resolve_reference_4, &frame__resolve_reference_3, 446, 446, 7, 42},
  {cont__resolve_reference_5, &frame__resolve_reference_3, 447, 447, 14, 38},
  {cont__resolve_reference_6, &frame__resolve_reference_3, 447, 447, 7, 67},
  {cont__resolve_reference_10, &frame__resolve_reference_3, 448, 448, 14, 40},
  {cont__resolve_reference_11, &frame__resolve_reference_3, 448, 448, 7, 69},
  {cont__resolve_reference_15, &frame__resolve_reference_3, 449, 449, 7, 50},
  {cont__resolve_reference_16, &frame__resolve_reference_3, 449, 449, 50, 50},
  {entry__resolve_reference_19, NULL, 451, 451, 41, 65},
  {cont__resolve_reference_20, &frame__resolve_reference_19, 451, 451, 65, 65},
  {entry__resolve_reference_17, NULL, 451, 451, 14, 38},
  {cont__resolve_reference_18, &frame__resolve_reference_17, 451, 451, 7, 65},
  {entry__resolve_reference_1, NULL, 444, 444, 5, 28},
  {cont__resolve_reference_2, &frame__resolve_reference_1, 443, 451, 3, 66},
  {cont__resolve_reference_21, &frame__resolve_reference_1, },
  {entry__add_links_5, NULL, 459, 459, 29, 29},
  {cont__add_links_6, &frame__add_links_5, 459, 459, 9, 29},
  {cont__add_links_7, &frame__add_links_5, 460, 460, 9, 36},
  {cont__add_links_8, &frame__add_links_5, 461, 461, 30, 46},
  {cont__add_links_9, &frame__add_links_5, 461, 461, 12, 54},
  {cont__add_links_13, &frame__add_links_5, 461, 461, 9, 54},
  {entry__add_links_1, NULL, 457, 457, 33, 47},
  {cont__add_links_2, &frame__add_links_1, 457, 457, 24, 48},
  {cont__add_links_3, &frame__add_links_1, 457, 457, 7, 53},
  {cont__add_links_4, &frame__add_links_1, 456, 461, 5, 55},
  {cont__add_links_14, &frame__add_links_1, 454, 461, 3, 56},
  {cont__add_links_15, &frame__add_links_1, 461, 461, 57, 57},
  {entry__create_info_page_6, NULL, 469, 469, 24, 40},
  {cont__create_info_page_7, &frame__create_info_page_6, 467, 470, 13, 60},
  {cont__create_info_page_12, &frame__create_info_page_6, 467, 470, 7, 60},
  {entry__create_info_page_2, NULL, 465, 465, 5, 32},
  {cont__create_info_page_3, &frame__create_info_page_2, 466, 466, 8, 36},
  {cont__create_info_page_4, &frame__create_info_page_2, 466, 466, 8, 49},
  {cont__create_info_page_5, &frame__create_info_page_2, 466, 470, 5, 61},
  {cont__create_info_page_13, &frame__create_info_page_2, },
  {entry__create_info_page_23, NULL, 477, 477, 11, 42},
  {cont__create_info_page_24, &frame__create_info_page_23, 478, 478, 11, 44},
  {cont__create_info_page_25, &frame__create_info_page_23, 484, 484, 15, 26},
  {cont__create_info_page_26, &frame__create_info_page_23, 488, 488, 15, 28},
  {cont__create_info_page_27, &frame__create_info_page_23, },
  {cont__create_info_page_29, &frame__create_info_page_23, 479, 489, 11, 23},
  {entry__create_info_page_33, NULL, 494, 494, 15, 53},
  {entry__create_info_page_35, NULL, 496, 496, 15, 55},
  {entry__create_info_page_37, NULL, 498, 498, 15, 54},
  {entry__create_info_page_30, NULL, 491, 491, 11, 26},
  {cont__create_info_page_31, &frame__create_info_page_30, 492, 492, 16, 37},
  {cont__create_info_page_32, &frame__create_info_page_30, 492, 498, 11, 55},
  {entry__create_info_page_42, NULL, 508, 508, 39, 59},
  {cont__create_info_page_43, &frame__create_info_page_42, 508, 508, 39, 59},
  {entry__create_info_page_47, NULL, 513, 513, 16, 32},
  {cont__create_info_page_48, &frame__create_info_page_47, 511, 513, 18, 36},
  {cont__create_info_page_52, &frame__create_info_page_47, 511, 513, 11, 36},
  {entry__create_info_page_45, NULL, 509, 509, 9, 40},
  {cont__create_info_page_46, &frame__create_info_page_45, 510, 513, 9, 37},
  {entry__create_info_page_67, NULL, 531, 531, 58, 58},
  {cont__create_info_page_68, &frame__create_info_page_67, 531, 531, 39, 59},
  {cont__create_info_page_69, &frame__create_info_page_67, 531, 531, 21, 74},
  {cont__create_info_page_71, &frame__create_info_page_67, 531, 531, 74, 74},
  {entry__create_info_page_65, NULL, 530, 530, 22, 47},
  {cont__create_info_page_66, &frame__create_info_page_65, 530, 531, 19, 74},
  {entry__create_info_page_74, NULL, 534, 534, 49, 49},
  {cont__create_info_page_75, &frame__create_info_page_74, 534, 534, 30, 50},
  {cont__create_info_page_76, &frame__create_info_page_74, 533, 534, 21, 79},
  {cont__create_info_page_78, &frame__create_info_page_74, 534, 534, 80, 80},
  {entry__create_info_page_72, NULL, 532, 532, 22, 47},
  {cont__create_info_page_73, &frame__create_info_page_72, 532, 534, 19, 80},
  {entry__create_info_page_81, NULL, 538, 538, 26, 47},
  {cont__create_info_page_82, &frame__create_info_page_81, 538, 538, 26, 53},
  {cont__create_info_page_83, &frame__create_info_page_81, 540, 540, 26, 47},
  {cont__create_info_page_84, &frame__create_info_page_81, 540, 540, 26, 53},
  {cont__create_info_page_85, &frame__create_info_page_81, 536, 541, 21, 28},
  {cont__create_info_page_88, &frame__create_info_page_81, 541, 541, 29, 29},
  {entry__create_info_page_79, NULL, 535, 535, 22, 45},
  {cont__create_info_page_80, &frame__create_info_page_79, 535, 541, 19, 29},
  {entry__create_info_page_63, NULL, 528, 528, 17, 71},
  {cont__create_info_page_64, &frame__create_info_page_63, 529, 541, 17, 30},
  {cont__create_info_page_89, &frame__create_info_page_63, 542, 542, 31, 52},
  {cont__create_info_page_90, &frame__create_info_page_63, 542, 542, 17, 58},
  {cont__create_info_page_91, &frame__create_info_page_63, 543, 543, 34, 56},
  {cont__create_info_page_92, &frame__create_info_page_63, 543, 543, 17, 56},
  {cont__create_info_page_93, &frame__create_info_page_63, 543, 543, 56, 56},
  {entry__create_info_page_58, NULL, 525, 525, 19, 53},
  {cont__create_info_page_59, &frame__create_info_page_58, },
  {cont__create_info_page_61, &frame__create_info_page_58, },
  {cont__create_info_page_62, &frame__create_info_page_58, 518, 543, 13, 57},
  {entry__create_info_page_103, NULL, 557, 557, 64, 64},
  {cont__create_info_page_104, &frame__create_info_page_103, 557, 557, 42, 65},
  {cont__create_info_page_105, &frame__create_info_page_103, 557, 557, 21, 80},
  {cont__create_info_page_106, &frame__create_info_page_103, 557, 557, 80, 80},
  {entry__create_info_page_101, NULL, 556, 556, 22, 50},
  {cont__create_info_page_102, &frame__create_info_page_101, 556, 557, 19, 80},
  {entry__create_info_page_109, NULL, 561, 561, 47, 47},
  {cont__create_info_page_110, &frame__create_info_page_109, 561, 561, 25, 48},
  {cont__create_info_page_111, &frame__create_info_page_109, 559, 562, 21, 52},
  {cont__create_info_page_112, &frame__create_info_page_109, 562, 562, 53, 53},
  {entry__create_info_page_107, NULL, 558, 558, 22, 50},
  {cont__create_info_page_108, &frame__create_info_page_107, 558, 562, 19, 53},
  {entry__create_info_page_99, NULL, 554, 554, 17, 74},
  {cont__create_info_page_100, &frame__create_info_page_99, 555, 562, 17, 54},
  {cont__create_info_page_113, &frame__create_info_page_99, 563, 563, 31, 52},
  {cont__create_info_page_114, &frame__create_info_page_99, 563, 563, 17, 58},
  {cont__create_info_page_115, &frame__create_info_page_99, 564, 564, 37, 62},
  {cont__create_info_page_116, &frame__create_info_page_99, 564, 564, 17, 62},
  {cont__create_info_page_117, &frame__create_info_page_99, 564, 564, 62, 62},
  {entry__create_info_page_94, NULL, 551, 551, 19, 53},
  {cont__create_info_page_95, &frame__create_info_page_94, },
  {cont__create_info_page_97, &frame__create_info_page_94, },
  {cont__create_info_page_98, &frame__create_info_page_94, 544, 564, 13, 63},
  {entry__create_info_page_124, NULL, 567, 567, 34, 47},
  {cont__create_info_page_125, &frame__create_info_page_124, 567, 567, 17, 47},
  {cont__create_info_page_126, &frame__create_info_page_124, 567, 567, 47, 47},
  {entry__create_info_page_121, NULL, 566, 566, 30, 51},
  {cont__create_info_page_122, &frame__create_info_page_121, 566, 566, 24, 56},
  {cont__create_info_page_123, &frame__create_info_page_121, 566, 567, 15, 47},
  {entry__create_info_page_118, NULL, 565, 565, 16, 49},
  {cont__create_info_page_120, &frame__create_info_page_118, 565, 567, 13, 48},
  {entry__create_info_page_132, NULL, 570, 570, 17, 27},
  {cont__create_info_page_133, &frame__create_info_page_132, 571, 571, 17, 38},
  {cont__create_info_page_134, &frame__create_info_page_132, 574, 574, 33, 45},
  {cont__create_info_page_135, &frame__create_info_page_132, 573, 574, 17, 66},
  {cont__create_info_page_136, &frame__create_info_page_132, 576, 576, 17, 46},
  {cont__create_info_page_137, &frame__create_info_page_132, 577, 577, 17, 30},
  {cont__create_info_page_138, &frame__create_info_page_132, 577, 577, 45, 45},
  {entry__create_info_page_129, NULL, 569, 569, 30, 51},
  {cont__create_info_page_130, &frame__create_info_page_129, 569, 569, 24, 56},
  {cont__create_info_page_131, &frame__create_info_page_129, 569, 577, 15, 45},
  {entry__create_info_page_127, NULL, 568, 568, 16, 43},
  {cont__create_info_page_128, &frame__create_info_page_127, 568, 577, 13, 46},
  {entry__create_info_page_141, NULL, 579, 579, 23, 44},
  {cont__create_info_page_142, &frame__create_info_page_141, 579, 579, 15, 50},
  {cont__create_info_page_143, &frame__create_info_page_141, 580, 580, 22, 43},
  {cont__create_info_page_144, &frame__create_info_page_141, 580, 580, 15, 49},
  {cont__create_info_page_145, &frame__create_info_page_141, 581, 581, 30, 41},
  {cont__create_info_page_146, &frame__create_info_page_141, 581, 581, 15, 41},
  {cont__create_info_page_147, &frame__create_info_page_141, 581, 581, 41, 41},
  {entry__create_info_page_139, NULL, 578, 578, 16, 45},
  {cont__create_info_page_140, &frame__create_info_page_139, 578, 581, 13, 41},
  {entry__create_info_page_155, NULL, 586, 586, 47, 47},
  {entry__create_info_page_156, NULL, 588, 588, 19, 49},
  {cont__create_info_page_157, &frame__create_info_page_156, 588, 588, 49, 49},
  {entry__create_info_page_151, NULL, 583, 583, 24, 45},
  {cont__create_info_page_152, &frame__create_info_page_151, 583, 583, 15, 51},
  {cont__create_info_page_153, &frame__create_info_page_151, 585, 585, 17, 28},
  {cont__create_info_page_154, &frame__create_info_page_151, 584, 588, 15, 50},
  {entry__create_info_page_148, NULL, 582, 582, 16, 58},
  {cont__create_info_page_150, &frame__create_info_page_148, 582, 588, 13, 51},
  {entry__create_info_page_162, NULL, 595, 595, 41, 41},
  {cont__create_info_page_163, &frame__create_info_page_162, 595, 595, 21, 41},
  {cont__create_info_page_164, &frame__create_info_page_162, 596, 596, 21, 58},
  {cont__create_info_page_165, &frame__create_info_page_162, 597, 597, 42, 58},
  {cont__create_info_page_166, &frame__create_info_page_162, 597, 597, 24, 66},
  {cont__create_info_page_167, &frame__create_info_page_162, 597, 597, 21, 66},
  {entry__create_info_page_173, NULL, 602, 602, 23, 55},
  {cont__create_info_page_174, &frame__create_info_page_173, 602, 602, 55, 55},
  {entry__create_info_page_175, NULL, 604, 604, 23, 50},
  {cont__create_info_page_176, &frame__create_info_page_175, 604, 604, 50, 50},
  {entry__create_info_page_171, NULL, 601, 601, 21, 48},
  {cont__create_info_page_172, &frame__create_info_page_171, 600, 604, 19, 51},
  {entry__create_info_page_177, NULL, 606, 606, 46, 46},
  {entry__create_info_page_158, NULL, 593, 593, 45, 59},
  {cont__create_info_page_159, &frame__create_info_page_158, 593, 593, 36, 60},
  {cont__create_info_page_160, &frame__create_info_page_158, 593, 593, 19, 65},
  {cont__create_info_page_161, &frame__create_info_page_158, 592, 597, 17, 67},
  {cont__create_info_page_168, &frame__create_info_page_158, 590, 597, 15, 68},
  {cont__create_info_page_169, &frame__create_info_page_158, 599, 599, 17, 44},
  {cont__create_info_page_170, &frame__create_info_page_158, 598, 606, 15, 47},
  {entry__create_info_page_57, NULL, 517, 606, 11, 49},
  {entry__create_info_page_55, NULL, 515, 515, 9, 46},
  {cont__create_info_page_56, &frame__create_info_page_55, 516, 606, 9, 50},
  {entry__create_info_page_195, NULL, 622, 622, 25, 51},
  {cont__create_info_page_196, &frame__create_info_page_195, 622, 622, 25, 61},
  {cont__create_info_page_197, &frame__create_info_page_195, 619, 623, 23, 27},
  {cont__create_info_page_198, &frame__create_info_page_195, 623, 623, 28, 28},
  {entry__create_info_page_199, NULL, 625, 625, 23, 48},
  {cont__create_info_page_200, &frame__create_info_page_199, 625, 625, 48, 48},
  {entry__create_info_page_192, NULL, 618, 618, 21, 47},
  {cont__create_info_page_193, &frame__create_info_page_192, 618, 618, 21, 58},
  {cont__create_info_page_194, &frame__create_info_page_192, 617, 625, 19, 49},
  {entry__create_info_page_190, NULL, 616, 616, 20, 48},
  {cont__create_info_page_191, &frame__create_info_page_190, 616, 625, 17, 50},
  {entry__create_info_page_203, NULL, 627, 627, 19, 58},
  {cont__create_info_page_204, &frame__create_info_page_203, 627, 627, 58, 58},
  {entry__create_info_page_201, NULL, 626, 626, 20, 48},
  {cont__create_info_page_202, &frame__create_info_page_201, 626, 627, 17, 58},
  {entry__create_info_page_209, NULL, 632, 632, 22, 47},
  {cont__create_info_page_210, &frame__create_info_page_209, 632, 632, 22, 61},
  {cont__create_info_page_211, &frame__create_info_page_209, 632, 632, 22, 64},
  {cont__create_info_page_212, &frame__create_info_page_209, 632, 632, 19, 64},
  {entry__create_info_page_213, NULL, 633, 633, 19, 23},
  {entry__create_info_page_186, NULL, 614, 614, 30, 53},
  {cont__create_info_page_187, &frame__create_info_page_186, 614, 614, 22, 54},
  {cont__create_info_page_188, &frame__create_info_page_186, 614, 614, 15, 75},
  {cont__create_info_page_189, &frame__create_info_page_186, 615, 627, 15, 59},
  {cont__create_info_page_205, &frame__create_info_page_186, 631, 631, 23, 48},
  {cont__create_info_page_206, &frame__create_info_page_186, 631, 631, 23, 57},
  {cont__create_info_page_207, &frame__create_info_page_186, 631, 631, 19, 58},
  {cont__create_info_page_208, &frame__create_info_page_186, 629, 633, 15, 24},
  {cont__create_info_page_214, &frame__create_info_page_186, 635, 635, 32, 49},
  {cont__create_info_page_215, &frame__create_info_page_186, 635, 635, 15, 49},
  {cont__create_info_page_216, &frame__create_info_page_186, 635, 635, 49, 49},
  {entry__create_info_page_217, NULL, 612, 612, 15, 18},
  {entry__create_info_page_183, NULL, 610, 610, 13, 40},
  {cont__create_info_page_184, &frame__create_info_page_183, 611, 611, 13, 52},
  {cont__create_info_page_185, &frame__create_info_page_183, 609, 635, 11, 50},
  {entry__create_info_page_181, NULL, 608, 608, 18, 36},
  {cont__create_info_page_182, &frame__create_info_page_181, 608, 635, 9, 51},
  {entry__create_info_page_220, NULL, 636, 636, 40, 58},
  {entry__create_info_page_230, NULL, 642, 642, 19, 42},
  {cont__create_info_page_231, &frame__create_info_page_230, 642, 642, 17, 42},
  {entry__create_info_page_227, NULL, 641, 641, 16, 32},
  {cont__create_info_page_228, &frame__create_info_page_227, 641, 641, 13, 32},
  {cont__create_info_page_229, &frame__create_info_page_227, 642, 642, 13, 42},
  {entry__create_info_page_226, NULL, 640, 642, 11, 42},
  {entry__create_info_page_223, NULL, 638, 638, 9, 23},
  {cont__create_info_page_225, &frame__create_info_page_223, 639, 642, 9, 43},
  {entry__create_info_page_240, NULL, 648, 648, 19, 45},
  {cont__create_info_page_241, &frame__create_info_page_240, 648, 648, 17, 45},
  {entry__create_info_page_237, NULL, 647, 647, 16, 35},
  {cont__create_info_page_238, &frame__create_info_page_237, 647, 647, 13, 35},
  {cont__create_info_page_239, &frame__create_info_page_237, 648, 648, 13, 45},
  {entry__create_info_page_236, NULL, 646, 648, 11, 45},
  {entry__create_info_page_234, NULL, 644, 644, 9, 20},
  {cont__create_info_page_235, &frame__create_info_page_234, 645, 648, 9, 46},
  {entry__create_info_page_247, NULL, 651, 651, 46, 58},
  {entry__create_info_page_244, NULL, 650, 650, 9, 24},
  {cont__create_info_page_246, &frame__create_info_page_244, 651, 651, 9, 58},
  {entry__create_info_page_253, NULL, 654, 654, 46, 53},
  {entry__create_info_page_250, NULL, 653, 653, 9, 30},
  {cont__create_info_page_252, &frame__create_info_page_250, 654, 654, 9, 53},
  {entry__create_info_page_263, NULL, 661, 661, 33, 49},
  {cont__create_info_page_264, &frame__create_info_page_263, 661, 661, 30, 56},
  {cont__create_info_page_265, &frame__create_info_page_263, 661, 661, 21, 56},
  {cont__create_info_page_266, &frame__create_info_page_263, 661, 661, 19, 66},
  {entry__create_info_page_262, NULL, 661, 661, 15, 66},
  {cont__create_info_page_267, &frame__create_info_page_262, 662, 662, 15, 25},
  {cont__create_info_page_269, &frame__create_info_page_262, 663, 663, 18, 46},
  {cont__create_info_page_270, &frame__create_info_page_262, 663, 663, 15, 46},
  {entry__create_info_page_260, NULL, 659, 659, 13, 50},
  {cont__create_info_page_261, &frame__create_info_page_260, 660, 663, 13, 46},
  {entry__create_info_page_259, NULL, 658, 663, 11, 47},
  {entry__create_info_page_256, NULL, 656, 656, 9, 21},
  {cont__create_info_page_258, &frame__create_info_page_256, 657, 663, 9, 48},
  {entry__create_info_page_282, NULL, 670, 670, 33, 44},
  {cont__create_info_page_283, &frame__create_info_page_282, 670, 670, 30, 51},
  {cont__create_info_page_284, &frame__create_info_page_282, 670, 670, 21, 51},
  {cont__create_info_page_285, &frame__create_info_page_282, 670, 670, 19, 56},
  {entry__create_info_page_289, NULL, 672, 672, 33, 46},
  {cont__create_info_page_290, &frame__create_info_page_289, 672, 672, 30, 53},
  {cont__create_info_page_291, &frame__create_info_page_289, 672, 672, 21, 53},
  {cont__create_info_page_292, &frame__create_info_page_289, 672, 672, 19, 60},
  {entry__create_info_page_281, NULL, 670, 670, 15, 56},
  {cont__create_info_page_286, &frame__create_info_page_281, 671, 671, 15, 33},
  {cont__create_info_page_288, &frame__create_info_page_281, 672, 672, 15, 60},
  {entry__create_info_page_279, NULL, 668, 668, 13, 50},
  {cont__create_info_page_280, &frame__create_info_page_279, 669, 672, 13, 60},
  {entry__create_info_page_277, NULL, 667, 667, 20, 33},
  {cont__create_info_page_278, &frame__create_info_page_277, 667, 672, 11, 61},
  {entry__create_info_page_274, NULL, 665, 665, 9, 27},
  {cont__create_info_page_276, &frame__create_info_page_274, 666, 672, 9, 62},
  {entry__create_info_page_295, NULL, 674, 674, 9, 61},
  {cont__create_info_page_296, &frame__create_info_page_295, 675, 675, 9, 23},
  {cont__create_info_page_298, &frame__create_info_page_295, 677, 677, 23, 55},
  {cont__create_info_page_299, &frame__create_info_page_295, 677, 677, 20, 62},
  {cont__create_info_page_300, &frame__create_info_page_295, 677, 677, 11, 62},
  {cont__create_info_page_301, &frame__create_info_page_295, 676, 678, 9, 35},
  {entry__create_info_page_312, NULL, 684, 684, 33, 51},
  {cont__create_info_page_313, &frame__create_info_page_312, 684, 684, 30, 58},
  {cont__create_info_page_314, &frame__create_info_page_312, 684, 684, 21, 58},
  {cont__create_info_page_315, &frame__create_info_page_312, 684, 684, 19, 70},
  {entry__create_info_page_318, NULL, 690, 690, 24, 44},
  {cont__create_info_page_319, &frame__create_info_page_318, 690, 690, 51, 69},
  {cont__create_info_page_320, &frame__create_info_page_318, 690, 690, 21, 76},
  {cont__create_info_page_321, &frame__create_info_page_318, 688, 690, 19, 76},
  {cont__create_info_page_322, &frame__create_info_page_318, 687, 693, 17, 29},
  {entry__create_info_page_311, NULL, 684, 684, 15, 70},
  {cont__create_info_page_316, &frame__create_info_page_311, 685, 685, 15, 25},
  {cont__create_info_page_317, &frame__create_info_page_311, 686, 693, 15, 30},
  {entry__create_info_page_310, NULL, 683, 693, 13, 31},
  {entry__create_info_page_308, NULL, 682, 682, 20, 35},
  {cont__create_info_page_309, &frame__create_info_page_308, 682, 693, 11, 32},
  {entry__create_info_page_305, NULL, 680, 680, 9, 44},
  {cont__create_info_page_307, &frame__create_info_page_305, 681, 693, 9, 33},
  {entry__create_info_page_338, NULL, 703, 703, 23, 39},
  {cont__create_info_page_339, &frame__create_info_page_338, 703, 703, 21, 45},
  {entry__create_info_page_337, NULL, 703, 703, 17, 45},
  {entry__create_info_page_331, NULL, 702, 702, 42, 60},
  {cont__create_info_page_332, &frame__create_info_page_331, 702, 702, 62, 70},
  {cont__create_info_page_334, &frame__create_info_page_331, 702, 702, 30, 71},
  {cont__create_info_page_335, &frame__create_info_page_331, 702, 702, 13, 80},
  {cont__create_info_page_336, &frame__create_info_page_331, 703, 703, 13, 45},
  {entry__create_info_page_330, NULL, 701, 703, 11, 45},
  {entry__create_info_page_327, NULL, 699, 699, 9, 19},
  {cont__create_info_page_329, &frame__create_info_page_327, 700, 703, 9, 46},
  {entry__create_info_page_354, NULL, 718, 718, 19, 35},
  {entry__create_info_page_349, NULL, 715, 715, 24, 48},
  {cont__create_info_page_350, &frame__create_info_page_349, 715, 715, 24, 63},
  {cont__create_info_page_351, &frame__create_info_page_349, 715, 715, 19, 64},
  {cont__create_info_page_352, &frame__create_info_page_349, },
  {cont__create_info_page_353, &frame__create_info_page_349, 712, 718, 15, 36},
  {cont__create_info_page_355, &frame__create_info_page_349, 719, 719, 35, 69},
  {cont__create_info_page_357, &frame__create_info_page_349, 719, 719, 15, 69},
  {cont__create_info_page_358, &frame__create_info_page_349, },
  {cont__create_info_page_359, &frame__create_info_page_349, 709, 719, 11, 70},
  {entry__create_info_page_341, NULL, 705, 705, 9, 30},
  {cont__create_info_page_342, &frame__create_info_page_341, 706, 706, 9, 36},
  {cont__create_info_page_343, &frame__create_info_page_341, 707, 707, 9, 16},
  {cont__create_info_page_344, &frame__create_info_page_341, 708, 708, 45, 56},
  {cont__create_info_page_345, &frame__create_info_page_341, 708, 708, 23, 56},
  {cont__create_info_page_346, &frame__create_info_page_341, 708, 708, 13, 56},
  {cont__create_info_page_348, &frame__create_info_page_341, 708, 719, 9, 71},
  {entry__create_info_page_20, NULL, 474, 474, 7, 14},
  {cont__create_info_page_21, &frame__create_info_page_20, 476, 476, 9, 36},
  {cont__create_info_page_22, &frame__create_info_page_20, 475, 498, 7, 57},
  {cont__create_info_page_39, &frame__create_info_page_20, 507, 507, 7, 41},
  {cont__create_info_page_40, &frame__create_info_page_20, 508, 508, 10, 34},
  {cont__create_info_page_41, &frame__create_info_page_20, 508, 508, 10, 59},
  {cont__create_info_page_44, &frame__create_info_page_20, 508, 513, 7, 38},
  {cont__create_info_page_53, &frame__create_info_page_20, 514, 514, 10, 32},
  {cont__create_info_page_54, &frame__create_info_page_20, 514, 606, 7, 51},
  {cont__create_info_page_178, &frame__create_info_page_20, 607, 607, 10, 22},
  {cont__create_info_page_179, &frame__create_info_page_20, 607, 607, 10, 34},
  {cont__create_info_page_180, &frame__create_info_page_20, 607, 635, 7, 52},
  {cont__create_info_page_218, &frame__create_info_page_20, 636, 636, 10, 37},
  {cont__create_info_page_219, &frame__create_info_page_20, 636, 636, 7, 58},
  {cont__create_info_page_221, &frame__create_info_page_20, 637, 637, 14, 32},
  {cont__create_info_page_222, &frame__create_info_page_20, 637, 642, 7, 44},
  {cont__create_info_page_232, &frame__create_info_page_20, 643, 643, 14, 35},
  {cont__create_info_page_233, &frame__create_info_page_20, 643, 648, 7, 47},
  {cont__create_info_page_242, &frame__create_info_page_20, 649, 649, 14, 34},
  {cont__create_info_page_243, &frame__create_info_page_20, 649, 651, 7, 58},
  {cont__create_info_page_248, &frame__create_info_page_20, 652, 652, 10, 37},
  {cont__create_info_page_249, &frame__create_info_page_20, 652, 654, 7, 53},
  {cont__create_info_page_254, &frame__create_info_page_20, 655, 655, 14, 32},
  {cont__create_info_page_255, &frame__create_info_page_20, 655, 663, 7, 49},
  {cont__create_info_page_271, &frame__create_info_page_20, 664, 664, 14, 27},
  {cont__create_info_page_272, &frame__create_info_page_20, 664, 664, 14, 36},
  {cont__create_info_page_273, &frame__create_info_page_20, 664, 672, 7, 63},
  {cont__create_info_page_293, &frame__create_info_page_20, 673, 673, 10, 37},
  {cont__create_info_page_294, &frame__create_info_page_20, 673, 678, 7, 36},
  {cont__create_info_page_302, &frame__create_info_page_20, 679, 679, 10, 22},
  {cont__create_info_page_303, &frame__create_info_page_20, 679, 679, 10, 39},
  {cont__create_info_page_304, &frame__create_info_page_20, 679, 693, 7, 34},
  {cont__create_info_page_323, &frame__create_info_page_20, 696, 696, 9, 42},
  {cont__create_info_page_324, &frame__create_info_page_20, 695, 696, 7, 64},
  {cont__create_info_page_325, &frame__create_info_page_20, 698, 698, 14, 32},
  {cont__create_info_page_326, &frame__create_info_page_20, 698, 703, 7, 47},
  {cont__create_info_page_340, &frame__create_info_page_20, 704, 719, 7, 72},
  {cont__create_info_page_360, &frame__create_info_page_20, 721, 721, 9, 26},
  {cont__create_info_page_362, &frame__create_info_page_20, 722, 722, 24, 40},
  {cont__create_info_page_363, &frame__create_info_page_20, 722, 722, 24, 69},
  {cont__create_info_page_364, &frame__create_info_page_20, 722, 722, 9, 76},
  {cont__create_info_page_367, &frame__create_info_page_20, 720, 722, 7, 76},
  {entry__create_info_page_15, NULL, 473, 473, 25, 45},
  {cont__create_info_page_16, &frame__create_info_page_15, 473, 473, 17, 52},
  {cont__create_info_page_19, &frame__create_info_page_15, 473, 722, 5, 77},
  {entry__create_info_page_1, NULL, 472, 472, 6, 29},
  {cont__create_info_page_14, &frame__create_info_page_1, 472, 722, 3, 78},
  {entry__get_short_description_8, NULL, 730, 730, 26, 48},
  {cont__get_short_description_9, &frame__get_short_description_8, 730, 730, 26, 48},
  {cont__get_short_description_10, &frame__get_short_description_8, 730, 730, 26, 48},
  {entry__get_short_description_6, NULL, 730, 730, 12, 21},
  {cont__get_short_description_7, &frame__get_short_description_6, 730, 730, 12, 48},
  {cont__get_short_description_11, &frame__get_short_description_6, 730, 730, 9, 54},
  {cont__get_short_description_12, &frame__get_short_description_6, 731, 731, 35, 43},
  {cont__get_short_description_13, &frame__get_short_description_6, 731, 731, 9, 43},
  {cont__get_short_description_14, &frame__get_short_description_6, 731, 731, 43, 43},
  {entry__get_short_description_5, NULL, 729, 731, 7, 43},
  {cont__get_short_description_15, &frame__get_short_description_5, 731, 731, 43, 43},
  {entry__get_short_description_17, NULL, 732, 732, 29, 56},
  {cont__get_short_description_18, &frame__get_short_description_17, 732, 732, 29, 61},
  {cont__get_short_description_19, &frame__get_short_description_17, 732, 732, 29, 61},
  {entry__get_short_description_21, NULL, 736, 736, 24, 40},
  {cont__get_short_description_22, &frame__get_short_description_21, 733, 738, 14, 28},
  {cont__get_short_description_26, &frame__get_short_description_21, 733, 738, 7, 28},
  {entry__get_short_description_4, NULL, 728, 731, 5, 44},
  {cont__get_short_description_16, &frame__get_short_description_4, 732, 732, 8, 61},
  {cont__get_short_description_20, &frame__get_short_description_4, 732, 738, 5, 29},
  {entry__get_short_description_1, NULL, 725, 725, 3, 37},
  {cont__get_short_description_2, &frame__get_short_description_1, 727, 727, 10, 30},
  {cont__get_short_description_3, &frame__get_short_description_1, 727, 738, 3, 30},
  {cont__get_short_description_27, &frame__get_short_description_1, 739, 739, 3, 30},
  {cont__get_short_description_28, &frame__get_short_description_1, 740, 740, 3, 22},
  {entry__compiler__extract_exports_5, NULL, 744, 744, 26, 66},
  {entry__compiler__extract_exports_15, NULL, 757, 757, 15, 23},
  {entry__compiler__extract_exports_16, NULL, 759, 759, 15, 24},
  {entry__compiler__extract_exports_18, NULL, 761, 761, 15, 23},
  {entry__compiler__extract_exports_19, NULL, 763, 763, 15, 24},
  {entry__compiler__extract_exports_13, NULL, 755, 755, 16, 37},
  {cont__compiler__extract_exports_14, &frame__compiler__extract_exports_13, 755, 763, 11, 25},
  {entry__compiler__extract_exports_21, NULL, 751, 751, 11, 21},
  {entry__compiler__extract_exports_23, NULL, 753, 753, 11, 20},
  {entry__compiler__extract_exports_25, NULL, 765, 765, 11, 19},
  {entry__compiler__extract_exports_10, NULL, 748, 748, 7, 20},
  {cont__compiler__extract_exports_11, &frame__compiler__extract_exports_10, 749, 749, 12, 24},
  {cont__compiler__extract_exports_12, &frame__compiler__extract_exports_10, 749, 765, 7, 20},
  {cont__compiler__extract_exports_26, &frame__compiler__extract_exports_10, 766, 766, 7, 13},
  {entry__compiler__extract_exports_29, NULL, 768, 768, 42, 42},
  {cont__compiler__extract_exports_30, &frame__compiler__extract_exports_29, 768, 768, 24, 43},
  {cont__compiler__extract_exports_31, &frame__compiler__extract_exports_29, 768, 768, 50, 73},
  {cont__compiler__extract_exports_32, &frame__compiler__extract_exports_29, 768, 768, 7, 74},
  {cont__compiler__extract_exports_33, &frame__compiler__extract_exports_29, 769, 769, 7, 38},
  {entry__compiler__extract_exports_7, NULL, 746, 746, 5, 23},
  {cont__compiler__extract_exports_8, &frame__compiler__extract_exports_7, 747, 747, 8, 22},
  {cont__compiler__extract_exports_9, &frame__compiler__extract_exports_7, 747, 766, 5, 13},
  {cont__compiler__extract_exports_27, &frame__compiler__extract_exports_7, 767, 767, 14, 29},
  {cont__compiler__extract_exports_28, &frame__compiler__extract_exports_7, 767, 769, 5, 38},
  {entry__compiler__extract_exports_1, NULL, 743, 743, 32, 39},
  {cont__compiler__extract_exports_2, &frame__compiler__extract_exports_1, 743, 743, 46, 46},
  {cont__compiler__extract_exports_3, &frame__compiler__extract_exports_1, 743, 743, 3, 47},
  {cont__compiler__extract_exports_4, &frame__compiler__extract_exports_1, 744, 744, 3, 66},
  {cont__compiler__extract_exports_6, &frame__compiler__extract_exports_1, 745, 769, 3, 39},
  {entry__compiler__extract_documentation_5, NULL, 773, 773, 26, 66},
  {entry__compiler__extract_documentation_10, NULL, 777, 780, 13, 63},
  {cont__compiler__extract_documentation_12, &frame__compiler__extract_documentation_10, 777, 780, 7, 63},
  {entry__compiler__extract_documentation_21, NULL, 784, 784, 27, 53},
  {entry__compiler__extract_documentation_26, NULL, 788, 788, 24, 48},
  {cont__compiler__extract_documentation_27, &frame__compiler__extract_documentation_26, 788, 788, 11, 62},
  {cont__compiler__extract_documentation_28, &frame__compiler__extract_documentation_26, 788, 788, 62, 62},
  {entry__compiler__extract_documentation_24, NULL, 787, 787, 16, 42},
  {cont__compiler__extract_documentation_25, &frame__compiler__extract_documentation_24, 787, 788, 9, 62},
  {cont__compiler__extract_documentation_29, &frame__compiler__extract_documentation_24, 789, 789, 9, 45},
  {cont__compiler__extract_documentation_31, &frame__compiler__extract_documentation_24, 790, 790, 9, 79},
  {cont__compiler__extract_documentation_32, &frame__compiler__extract_documentation_24, 790, 790, 9, 36},
  {cont__compiler__extract_documentation_33, &frame__compiler__extract_documentation_24, 791, 791, 29, 53},
  {cont__compiler__extract_documentation_34, &frame__compiler__extract_documentation_24, 791, 791, 55, 79},
  {cont__compiler__extract_documentation_35, &frame__compiler__extract_documentation_24, 791, 791, 9, 80},
  {cont__compiler__extract_documentation_36, &frame__compiler__extract_documentation_24, 792, 792, 10, 27},
  {cont__compiler__extract_documentation_37, &frame__compiler__extract_documentation_24, 792, 792, 10, 36},
  {cont__compiler__extract_documentation_38, &frame__compiler__extract_documentation_24, 792, 792, 9, 42},
  {cont__compiler__extract_documentation_39, &frame__compiler__extract_documentation_24, 792, 792, 9, 27},
  {cont__compiler__extract_documentation_40, &frame__compiler__extract_documentation_24, 793, 793, 9, 29},
  {cont__compiler__extract_documentation_41, &frame__compiler__extract_documentation_24, 793, 793, 41, 41},
  {entry__compiler__extract_documentation_18, NULL, 783, 783, 7, 25},
  {cont__compiler__extract_documentation_19, &frame__compiler__extract_documentation_18, 784, 784, 10, 24},
  {cont__compiler__extract_documentation_20, &frame__compiler__extract_documentation_18, 784, 784, 7, 53},
  {cont__compiler__extract_documentation_22, &frame__compiler__extract_documentation_18, 786, 786, 16, 31},
  {cont__compiler__extract_documentation_23, &frame__compiler__extract_documentation_18, 786, 793, 7, 41},
  {cont__compiler__extract_documentation_42, &frame__compiler__extract_documentation_18, 794, 794, 8, 25},
  {cont__compiler__extract_documentation_43, &frame__compiler__extract_documentation_18, 794, 794, 7, 25},
  {cont__compiler__extract_documentation_44, &frame__compiler__extract_documentation_18, 794, 794, 44, 44},
  {entry__compiler__extract_documentation_7, NULL, 775, 775, 5, 23},
  {cont__compiler__extract_documentation_8, &frame__compiler__extract_documentation_7, 776, 776, 8, 24},
  {cont__compiler__extract_documentation_9, &frame__compiler__extract_documentation_7, 776, 780, 5, 64},
  {cont__compiler__extract_documentation_13, &frame__compiler__extract_documentation_7, 781, 781, 5, 62},
  {cont__compiler__extract_documentation_14, &frame__compiler__extract_documentation_7, 781, 781, 5, 29},
  {cont__compiler__extract_documentation_15, &frame__compiler__extract_documentation_7, 782, 782, 8, 20},
  {cont__compiler__extract_documentation_16, &frame__compiler__extract_documentation_7, 782, 782, 8, 37},
  {cont__compiler__extract_documentation_17, &frame__compiler__extract_documentation_7, 782, 794, 5, 44},
  {entry__compiler__extract_documentation_54, NULL, 806, 806, 18, 50},
  {cont__compiler__extract_documentation_55, &frame__compiler__extract_documentation_54, 806, 806, 13, 50},
  {cont__compiler__extract_documentation_56, &frame__compiler__extract_documentation_54, 807, 807, 27, 39},
  {cont__compiler__extract_documentation_57, &frame__compiler__extract_documentation_54, 807, 807, 24, 46},
  {cont__compiler__extract_documentation_58, &frame__compiler__extract_documentation_54, 807, 807, 15, 46},
  {cont__compiler__extract_documentation_59, &frame__compiler__extract_documentation_54, 807, 807, 13, 52},
  {entry__compiler__extract_documentation_53, NULL, 805, 807, 11, 52},
  {entry__compiler__extract_documentation_62, NULL, 808, 808, 43, 63},
  {cont__compiler__extract_documentation_63, &frame__compiler__extract_documentation_62, 808, 808, 39, 64},
  {cont__compiler__extract_documentation_64, &frame__compiler__extract_documentation_62, 808, 808, 39, 64},
  {entry__compiler__extract_documentation_66, NULL, 809, 809, 14, 39},
  {cont__compiler__extract_documentation_67, &frame__compiler__extract_documentation_66, 809, 809, 14, 42},
  {cont__compiler__extract_documentation_68, &frame__compiler__extract_documentation_66, 809, 809, 11, 42},
  {entry__compiler__extract_documentation_71, NULL, 811, 811, 27, 43},
  {cont__compiler__extract_documentation_72, &frame__compiler__extract_documentation_71, 811, 811, 45, 52},
  {cont__compiler__extract_documentation_73, &frame__compiler__extract_documentation_71, 811, 811, 11, 52},
  {entry__compiler__extract_documentation_49, NULL, 802, 802, 9, 28},
  {cont__compiler__extract_documentation_50, &frame__compiler__extract_documentation_49, 803, 803, 9, 43},
  {cont__compiler__extract_documentation_51, &frame__compiler__extract_documentation_49, 804, 804, 12, 27},
  {cont__compiler__extract_documentation_52, &frame__compiler__extract_documentation_49, 804, 807, 9, 53},
  {cont__compiler__extract_documentation_60, &frame__compiler__extract_documentation_49, 808, 808, 12, 34},
  {cont__compiler__extract_documentation_61, &frame__compiler__extract_documentation_49, 808, 808, 12, 64},
  {cont__compiler__extract_documentation_65, &frame__compiler__extract_documentation_49, 808, 809, 9, 42},
  {cont__compiler__extract_documentation_69, &frame__compiler__extract_documentation_49, 810, 810, 18, 39},
  {cont__compiler__extract_documentation_70, &frame__compiler__extract_documentation_49, 810, 811, 9, 52},
  {entry__compiler__extract_documentation_48, NULL, 801, 811, 7, 53},
  {entry__compiler__extract_documentation_80, NULL, 817, 817, 46, 58},
  {cont__compiler__extract_documentation_81, &frame__compiler__extract_documentation_80, 817, 817, 46, 71},
  {cont__compiler__extract_documentation_82, &frame__compiler__extract_documentation_80, 817, 817, 46, 71},
  {entry__compiler__extract_documentation_84, NULL, 818, 818, 11, 30},
  {entry__compiler__extract_documentation_77, NULL, 817, 817, 12, 24},
  {cont__compiler__extract_documentation_78, &frame__compiler__extract_documentation_77, 817, 817, 12, 41},
  {cont__compiler__extract_documentation_79, &frame__compiler__extract_documentation_77, 817, 817, 12, 71},
  {cont__compiler__extract_documentation_83, &frame__compiler__extract_documentation_77, 817, 818, 9, 30},
  {entry__compiler__extract_documentation_76, NULL, 816, 818, 7, 31},
  {entry__compiler__extract_documentation_47, NULL, 813, 813, 5, 12},
  {cont__compiler__extract_documentation_74, &frame__compiler__extract_documentation_47, 814, 814, 5, 19},
  {cont__compiler__extract_documentation_75, &frame__compiler__extract_documentation_47, 815, 818, 5, 32},
  {entry__compiler__extract_documentation_93, NULL, 825, 825, 20, 31},
  {cont__compiler__extract_documentation_95, &frame__compiler__extract_documentation_93, 825, 825, 11, 31},
  {cont__compiler__extract_documentation_96, &frame__compiler__extract_documentation_93, 825, 825, 33, 52},
  {cont__compiler__extract_documentation_97, &frame__compiler__extract_documentation_93, 825, 825, 9, 52},
  {entry__compiler__extract_documentation_98, NULL, 827, 827, 9, 16},
  {entry__compiler__extract_documentation_114, NULL, 837, 837, 22, 41},
  {cont__compiler__extract_documentation_115, &frame__compiler__extract_documentation_114, 837, 837, 17, 41},
  {cont__compiler__extract_documentation_116, &frame__compiler__extract_documentation_114, 838, 838, 19, 35},
  {cont__compiler__extract_documentation_118, &frame__compiler__extract_documentation_114, 838, 838, 17, 66},
  {entry__compiler__extract_documentation_112, NULL, 836, 836, 18, 30},
  {cont__compiler__extract_documentation_113, &frame__compiler__extract_documentation_112, 836, 838, 15, 66},
  {entry__compiler__extract_documentation_109, NULL, 835, 835, 16, 28},
  {cont__compiler__extract_documentation_111, &frame__compiler__extract_documentation_109, 835, 838, 13, 67},
  {entry__compiler__extract_documentation_107, NULL, 833, 833, 11, 26},
  {cont__compiler__extract_documentation_108, &frame__compiler__extract_documentation_107, 834, 838, 11, 68},
  {entry__compiler__extract_documentation_124, NULL, 842, 842, 43, 63},
  {cont__compiler__extract_documentation_125, &frame__compiler__extract_documentation_124, 842, 842, 39, 64},
  {cont__compiler__extract_documentation_126, &frame__compiler__extract_documentation_124, 842, 842, 39, 64},
  {entry__compiler__extract_documentation_128, NULL, 843, 843, 19, 44},
  {cont__compiler__extract_documentation_129, &frame__compiler__extract_documentation_128, 843, 843, 11, 47},
  {cont__compiler__extract_documentation_130, &frame__compiler__extract_documentation_128, 843, 843, 47, 47},
  {entry__compiler__extract_documentation_133, NULL, 849, 849, 13, 25},
  {entry__compiler__extract_documentation_135, NULL, 851, 851, 13, 37},
  {entry__compiler__extract_documentation_137, NULL, 853, 853, 13, 38},
  {entry__compiler__extract_documentation_139, NULL, 855, 855, 13, 30},
  {entry__compiler__extract_documentation_141, NULL, 857, 857, 13, 32},
  {entry__compiler__extract_documentation_143, NULL, 859, 859, 13, 34},
  {entry__compiler__extract_documentation_145, NULL, 861, 861, 13, 28},
  {entry__compiler__extract_documentation_147, NULL, 863, 863, 13, 25},
  {entry__compiler__extract_documentation_149, NULL, 865, 865, 13, 22},
  {entry__compiler__extract_documentation_151, NULL, 866, 866, 13, 24},
  {entry__compiler__extract_documentation_156, NULL, 871, 871, 15, 55},
  {cont__compiler__extract_documentation_158, &frame__compiler__extract_documentation_156, 871, 871, 55, 55},
  {entry__compiler__extract_documentation_159, NULL, 873, 873, 31, 31},
  {entry__compiler__extract_documentation_154, NULL, 870, 870, 13, 29},
  {cont__compiler__extract_documentation_155, &frame__compiler__extract_documentation_154, 869, 873, 11, 32},
  {entry__compiler__extract_documentation_162, NULL, 874, 874, 33, 47},
  {cont__compiler__extract_documentation_163, &frame__compiler__extract_documentation_162, 874, 874, 33, 47},
  {entry__compiler__extract_documentation_172, NULL, 877, 877, 31, 42},
  {cont__compiler__extract_documentation_173, &frame__compiler__extract_documentation_172, 877, 877, 28, 49},
  {cont__compiler__extract_documentation_174, &frame__compiler__extract_documentation_172, 877, 877, 19, 49},
  {cont__compiler__extract_documentation_175, &frame__compiler__extract_documentation_172, 877, 877, 51, 68},
  {cont__compiler__extract_documentation_176, &frame__compiler__extract_documentation_172, 877, 877, 17, 68},
  {entry__compiler__extract_documentation_166, NULL, 876, 876, 16, 32},
  {cont__compiler__extract_documentation_169, &frame__compiler__extract_documentation_166, 876, 876, 34, 50},
  {cont__compiler__extract_documentation_170, &frame__compiler__extract_documentation_166, 876, 876, 13, 50},
  {cont__compiler__extract_documentation_171, &frame__compiler__extract_documentation_166, 877, 877, 13, 68},
  {cont__compiler__extract_documentation_177, &frame__compiler__extract_documentation_166, 878, 878, 16, 33},
  {cont__compiler__extract_documentation_179, &frame__compiler__extract_documentation_166, 878, 878, 13, 40},
  {entry__compiler__extract_documentation_165, NULL, 875, 878, 11, 40},
  {entry__compiler__extract_documentation_103, NULL, 832, 832, 12, 19},
  {cont__compiler__extract_documentation_104, &frame__compiler__extract_documentation_103, 832, 832, 12, 29},
  {cont__compiler__extract_documentation_105, &frame__compiler__extract_documentation_103, 832, 832, 12, 29},
  {cont__compiler__extract_documentation_106, &frame__compiler__extract_documentation_103, 832, 838, 9, 69},
  {cont__compiler__extract_documentation_120, &frame__compiler__extract_documentation_103, 840, 840, 9, 27},
  {cont__compiler__extract_documentation_121, &frame__compiler__extract_documentation_103, 841, 841, 9, 43},
  {cont__compiler__extract_documentation_122, &frame__compiler__extract_documentation_103, 842, 842, 12, 34},
  {cont__compiler__extract_documentation_123, &frame__compiler__extract_documentation_103, 842, 842, 12, 64},
  {cont__compiler__extract_documentation_127, &frame__compiler__extract_documentation_103, 842, 843, 9, 47},
  {cont__compiler__extract_documentation_131, &frame__compiler__extract_documentation_103, 847, 847, 13, 25},
  {cont__compiler__extract_documentation_132, &frame__compiler__extract_documentation_103, 845, 866, 9, 25},
  {cont__compiler__extract_documentation_152, &frame__compiler__extract_documentation_103, 868, 868, 12, 31},
  {cont__compiler__extract_documentation_153, &frame__compiler__extract_documentation_103, 868, 873, 9, 33},
  {cont__compiler__extract_documentation_160, &frame__compiler__extract_documentation_103, 874, 874, 12, 28},
  {cont__compiler__extract_documentation_161, &frame__compiler__extract_documentation_103, 874, 874, 12, 47},
  {cont__compiler__extract_documentation_164, &frame__compiler__extract_documentation_103, 874, 878, 9, 41},
  {entry__compiler__extract_documentation_102, NULL, 831, 878, 7, 42},
  {entry__compiler__extract_documentation_87, NULL, 820, 820, 5, 12},
  {cont__compiler__extract_documentation_88, &frame__compiler__extract_documentation_87, 821, 821, 8, 21},
  {cont__compiler__extract_documentation_91, &frame__compiler__extract_documentation_87, 821, 821, 5, 36},
  {cont__compiler__extract_documentation_92, &frame__compiler__extract_documentation_87, 822, 827, 5, 17},
  {cont__compiler__extract_documentation_100, &frame__compiler__extract_documentation_87, 828, 828, 5, 6},
  {cont__compiler__extract_documentation_101, &frame__compiler__extract_documentation_87, 829, 878, 5, 43},
  {entry__compiler__extract_documentation_187, NULL, 884, 884, 26, 53},
  {cont__compiler__extract_documentation_188, &frame__compiler__extract_documentation_187, 884, 884, 9, 65},
  {entry__compiler__extract_documentation_185, NULL, 883, 883, 16, 31},
  {cont__compiler__extract_documentation_186, &frame__compiler__extract_documentation_185, 883, 884, 7, 65},
  {entry__compiler__extract_documentation_181, NULL, 880, 880, 5, 23},
  {cont__compiler__extract_documentation_182, &frame__compiler__extract_documentation_181, 881, 881, 5, 30},
  {cont__compiler__extract_documentation_183, &frame__compiler__extract_documentation_181, 882, 882, 10, 22},
  {cont__compiler__extract_documentation_184, &frame__compiler__extract_documentation_181, 882, 884, 5, 66},
  {entry__compiler__extract_documentation_202, NULL, 891, 891, 19, 35},
  {cont__compiler__extract_documentation_203, &frame__compiler__extract_documentation_202, 891, 891, 17, 41},
  {entry__compiler__extract_documentation_201, NULL, 891, 891, 13, 41},
  {entry__compiler__extract_documentation_196, NULL, 890, 890, 38, 56},
  {cont__compiler__extract_documentation_197, &frame__compiler__extract_documentation_196, 890, 890, 58, 66},
  {cont__compiler__extract_documentation_198, &frame__compiler__extract_documentation_196, 890, 890, 26, 67},
  {cont__compiler__extract_documentation_199, &frame__compiler__extract_documentation_196, 890, 890, 9, 76},
  {cont__compiler__extract_documentation_200, &frame__compiler__extract_documentation_196, 891, 891, 9, 41},
  {entry__compiler__extract_documentation_195, NULL, 889, 891, 7, 41},
  {entry__compiler__extract_documentation_191, NULL, 886, 886, 5, 12},
  {cont__compiler__extract_documentation_192, &frame__compiler__extract_documentation_191, 887, 887, 8, 21},
  {cont__compiler__extract_documentation_193, &frame__compiler__extract_documentation_191, 887, 887, 5, 36},
  {cont__compiler__extract_documentation_194, &frame__compiler__extract_documentation_191, 888, 891, 5, 42},
  {entry__compiler__extract_documentation_217, NULL, 899, 899, 44, 62},
  {cont__compiler__extract_documentation_218, &frame__compiler__extract_documentation_217, 899, 899, 42, 62},
  {entry__compiler__extract_documentation_216, NULL, 899, 899, 9, 62},
  {entry__compiler__extract_documentation_223, NULL, 903, 903, 35, 51},
  {cont__compiler__extract_documentation_224, &frame__compiler__extract_documentation_223, 903, 903, 28, 60},
  {cont__compiler__extract_documentation_225, &frame__compiler__extract_documentation_223, 903, 903, 19, 60},
  {cont__compiler__extract_documentation_226, &frame__compiler__extract_documentation_223, 903, 903, 17, 70},
  {entry__compiler__extract_documentation_222, NULL, 903, 903, 13, 70},
  {cont__compiler__extract_documentation_227, &frame__compiler__extract_documentation_222, 904, 904, 13, 23},
  {cont__compiler__extract_documentation_228, &frame__compiler__extract_documentation_222, 905, 905, 16, 44},
  {cont__compiler__extract_documentation_229, &frame__compiler__extract_documentation_222, 905, 905, 13, 44},
  {entry__compiler__extract_documentation_221, NULL, 902, 905, 11, 44},
  {entry__compiler__extract_documentation_220, NULL, 901, 905, 9, 45},
  {entry__compiler__extract_documentation_210, NULL, 895, 895, 7, 14},
  {cont__compiler__extract_documentation_211, &frame__compiler__extract_documentation_210, 896, 896, 10, 23},
  {cont__compiler__extract_documentation_212, &frame__compiler__extract_documentation_210, 896, 896, 7, 29},
  {cont__compiler__extract_documentation_213, &frame__compiler__extract_documentation_210, 897, 897, 7, 42},
  {cont__compiler__extract_documentation_214, &frame__compiler__extract_documentation_210, 898, 898, 10, 30},
  {cont__compiler__extract_documentation_215, &frame__compiler__extract_documentation_210, 898, 899, 7, 62},
  {cont__compiler__extract_documentation_219, &frame__compiler__extract_documentation_210, 900, 905, 7, 46},
  {entry__compiler__extract_documentation_205, NULL, 893, 893, 27, 45},
  {cont__compiler__extract_documentation_206, &frame__compiler__extract_documentation_205, 893, 893, 47, 55},
  {cont__compiler__extract_documentation_207, &frame__compiler__extract_documentation_205, 893, 893, 5, 56},
  {cont__compiler__extract_documentation_208, &frame__compiler__extract_documentation_205, 894, 894, 17, 39},
  {cont__compiler__extract_documentation_209, &frame__compiler__extract_documentation_205, 894, 905, 5, 47},
  {entry__compiler__extract_documentation_235, NULL, 908, 908, 10, 31},
  {cont__compiler__extract_documentation_236, &frame__compiler__extract_documentation_235, 908, 908, 8, 40},
  {entry__compiler__extract_documentation_238, NULL, 909, 909, 10, 35},
  {cont__compiler__extract_documentation_239, &frame__compiler__extract_documentation_238, 909, 909, 8, 48},
  {entry__compiler__extract_documentation_241, NULL, 910, 910, 10, 37},
  {cont__compiler__extract_documentation_242, &frame__compiler__extract_documentation_241, 910, 910, 8, 52},
  {entry__compiler__extract_documentation_244, NULL, 911, 911, 10, 37},
  {cont__compiler__extract_documentation_245, &frame__compiler__extract_documentation_244, 911, 911, 8, 52},
  {entry__compiler__extract_documentation_232, NULL, 907, 907, 5, 19},
  {cont__compiler__extract_documentation_234, &frame__compiler__extract_documentation_232, 908, 908, 5, 40},
  {cont__compiler__extract_documentation_237, &frame__compiler__extract_documentation_232, 909, 909, 5, 48},
  {cont__compiler__extract_documentation_240, &frame__compiler__extract_documentation_232, 910, 910, 5, 52},
  {cont__compiler__extract_documentation_243, &frame__compiler__extract_documentation_232, 911, 911, 5, 52},
  {entry__compiler__extract_documentation_250, NULL, 928, 928, 11, 30},
  {cont__compiler__extract_documentation_251, &frame__compiler__extract_documentation_250, 928, 928, 30, 30},
  {entry__compiler__extract_documentation_252, NULL, 930, 930, 11, 42},
  {cont__compiler__extract_documentation_253, &frame__compiler__extract_documentation_252, 930, 930, 42, 42},
  {entry__compiler__extract_documentation_254, NULL, 932, 932, 11, 43},
  {cont__compiler__extract_documentation_255, &frame__compiler__extract_documentation_254, 932, 932, 43, 43},
  {entry__compiler__extract_documentation_256, NULL, 934, 934, 11, 39},
  {cont__compiler__extract_documentation_257, &frame__compiler__extract_documentation_256, 934, 934, 39, 39},
  {entry__compiler__extract_documentation_258, NULL, 936, 936, 11, 35},
  {cont__compiler__extract_documentation_259, &frame__compiler__extract_documentation_258, 936, 936, 35, 35},
  {entry__compiler__extract_documentation_260, NULL, 938, 938, 11, 37},
  {cont__compiler__extract_documentation_261, &frame__compiler__extract_documentation_260, 938, 938, 37, 37},
  {entry__compiler__extract_documentation_262, NULL, 940, 940, 11, 33},
  {cont__compiler__extract_documentation_263, &frame__compiler__extract_documentation_262, 940, 940, 33, 33},
  {entry__compiler__extract_documentation_264, NULL, 942, 942, 11, 30},
  {cont__compiler__extract_documentation_265, &frame__compiler__extract_documentation_264, 942, 942, 30, 30},
  {entry__compiler__extract_documentation_266, NULL, 944, 944, 11, 20},
  {cont__compiler__extract_documentation_267, &frame__compiler__extract_documentation_266, 944, 944, 20, 20},
  {entry__compiler__extract_documentation_274, NULL, 949, 949, 15, 32},
  {cont__compiler__extract_documentation_275, &frame__compiler__extract_documentation_274, 949, 949, 32, 32},
  {entry__compiler__extract_documentation_276, NULL, 951, 951, 15, 41},
  {cont__compiler__extract_documentation_277, &frame__compiler__extract_documentation_276, 951, 951, 41, 41},
  {entry__compiler__extract_documentation_278, NULL, 953, 953, 15, 35},
  {cont__compiler__extract_documentation_279, &frame__compiler__extract_documentation_278, 953, 953, 35, 35},
  {entry__compiler__extract_documentation_272, NULL, 947, 947, 16, 35},
  {cont__compiler__extract_documentation_273, &frame__compiler__extract_documentation_272, 947, 953, 11, 36},
  {entry__compiler__extract_documentation_270, NULL, 946, 946, 18, 33},
  {cont__compiler__extract_documentation_271, &frame__compiler__extract_documentation_270, 946, 953, 9, 37},
  {entry__compiler__extract_documentation_248, NULL, 926, 926, 12, 24},
  {cont__compiler__extract_documentation_249, &frame__compiler__extract_documentation_248, 926, 944, 7, 21},
  {cont__compiler__extract_documentation_268, &frame__compiler__extract_documentation_248, 945, 945, 12, 24},
  {cont__compiler__extract_documentation_269, &frame__compiler__extract_documentation_248, 945, 953, 7, 38},
  {entry__compiler__extract_documentation_247, NULL, 925, 953, 5, 39},
  {cont__compiler__extract_documentation_280, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_281, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_282, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_283, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_284, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_285, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_286, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_287, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_288, &frame__compiler__extract_documentation_247, },
  {cont__compiler__extract_documentation_289, &frame__compiler__extract_documentation_247, 955, 967, 5, 24},
  {cont__compiler__extract_documentation_290, &frame__compiler__extract_documentation_247, 970, 970, 32, 60},
  {cont__compiler__extract_documentation_291, &frame__compiler__extract_documentation_247, 972, 972, 32, 58},
  {cont__compiler__extract_documentation_292, &frame__compiler__extract_documentation_247, 973, 973, 32, 70},
  {cont__compiler__extract_documentation_293, &frame__compiler__extract_documentation_247, 974, 974, 32, 71},
  {cont__compiler__extract_documentation_294, &frame__compiler__extract_documentation_247, 975, 975, 32, 56},
  {cont__compiler__extract_documentation_295, &frame__compiler__extract_documentation_247, 976, 976, 32, 65},
  {cont__compiler__extract_documentation_296, &frame__compiler__extract_documentation_247, 977, 977, 32, 59},
  {cont__compiler__extract_documentation_297, &frame__compiler__extract_documentation_247, 978, 978, 32, 67},
  {cont__compiler__extract_documentation_298, &frame__compiler__extract_documentation_247, 979, 979, 32, 63},
  {cont__compiler__extract_documentation_299, &frame__compiler__extract_documentation_247, 980, 980, 32, 65},
  {cont__compiler__extract_documentation_300, &frame__compiler__extract_documentation_247, 981, 981, 32, 61},
  {cont__compiler__extract_documentation_301, &frame__compiler__extract_documentation_247, 982, 982, 32, 58},
  {cont__compiler__extract_documentation_302, &frame__compiler__extract_documentation_247, 983, 983, 32, 48},
  {cont__compiler__extract_documentation_303, &frame__compiler__extract_documentation_247, 985, 985, 32, 70},
  {cont__compiler__extract_documentation_304, &frame__compiler__extract_documentation_247, 969, 985, 12, 71},
  {cont__compiler__extract_documentation_319, &frame__compiler__extract_documentation_247, 969, 985, 5, 71},
  {entry__compiler__extract_documentation_1, NULL, 772, 772, 32, 39},
  {cont__compiler__extract_documentation_2, &frame__compiler__extract_documentation_1, 772, 772, 46, 46},
  {cont__compiler__extract_documentation_3, &frame__compiler__extract_documentation_1, 772, 772, 3, 47},
  {cont__compiler__extract_documentation_4, &frame__compiler__extract_documentation_1, 773, 773, 3, 66},
  {cont__compiler__extract_documentation_6, &frame__compiler__extract_documentation_1, 774, 794, 3, 45},
  {cont__compiler__extract_documentation_45, &frame__compiler__extract_documentation_1, 795, 818, 3, 33},
  {cont__compiler__extract_documentation_85, &frame__compiler__extract_documentation_1, 819, 878, 3, 44},
  {cont__compiler__extract_documentation_180, &frame__compiler__extract_documentation_1, 879, 884, 3, 67},
  {cont__compiler__extract_documentation_189, &frame__compiler__extract_documentation_1, 885, 891, 3, 43},
  {cont__compiler__extract_documentation_204, &frame__compiler__extract_documentation_1, 892, 905, 3, 48},
  {cont__compiler__extract_documentation_230, &frame__compiler__extract_documentation_1, 906, 911, 3, 52},
  {cont__compiler__extract_documentation_246, &frame__compiler__extract_documentation_1, 912, 985, 3, 72}
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
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
static NODE *character__37;
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
  "compiler",
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
  frame->cont = cont__47_1;
}
static void cont__47_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 39: $$definitions empty_key_order_table
  var._definitions = get__empty_key_order_table();
  // 41: $$short_descriptions empty_table
  // 42:   # is also used to check whether a symbol is defined or not
  var._short_descriptions = get__empty_table();
  // 44: $$topics empty_key_order_table
  var._topics = get__empty_key_order_table();
  // 45: $$topics_paragraphs empty_table
  var._topics_paragraphs = get__empty_table();
  // 46: $$missing_documentation_count 0
  var._missing_documentation_count = number__0;
  // 63: ... compiler::WHITESPACE, '=', compiler::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__compiler__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__compiler__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__62_1;
}
static void cont__62_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 63: alt('=' compiler::WHITESPACE, '=', compiler::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__62_2;
}
static void cont__62_2(void) {
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
  frame->cont = cont__62_3;
}
static void cont__62_3(void) {
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
  frame->cont = cont__62_4;
}
static void cont__62_4(void) {
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
  frame->cont = cont__62_5;
}
static void cont__62_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__62_6;
}
static void cont__62_6(void) {
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
  // 63:       alt('=' compiler::WHITESPACE, '=', compiler::WHITESPACE)
  // 64:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__62_7;
}
static void cont__62_7(void) {
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
  // 161:   .remark_lines_of empty_list
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
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__empty_list());
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, get__empty_key_order_set());
    set_attribute_value(temp->attributes, poly_idx__methods_of, get__empty_key_order_table());
    set_attribute_value(temp->attributes, poly_idx__types_of, get__empty_key_order_set());
    initialize_future(var._symbol_info, temp);

  }
  // 409: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__781f541a81a2a2a4;
  arguments->slots[1] = string__545aef03ea835034;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__74_2;
}
static void cont__74_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 409: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__74_3;
}
static void cont__74_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 410: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__a89009de95dad09f;
  arguments->slots[1] = string__701f5257011302a3;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__75_3;
}
static void cont__75_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 410: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__75_4;
}
static void cont__75_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 410: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__75_5;
}
static void cont__75_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 410: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__75_6;
}
static void cont__75_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 410: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__75_7;
}
static void cont__75_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXAMPLE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_page_1(void) {
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
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_page_2, 0);
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
  frame->cont = cont__create_page_7;
}
static void entry__create_page_3(void) {
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
  arguments->slots[0] = func__create_page_4;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__create_page_6;
}
static void entry__create_page_4(void) {
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
  arguments->slots[0] = string__38ea9d2e8a7087ec;
  result_count = frame->caller_result_count;
  myself = get__STYLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_page_6(void) {
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
static void entry__create_page_2(void) {
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
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_page_3, 0);
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
static void cont__create_page_7(void) {
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
static void entry__extract_remark_lines_21(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // arguments: 0
  // first_idx: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  frame->slots[1] = myself->closure.frame->slots[2]; /* first_idx */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: ... arguments(first_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* first_idx */;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__extract_remark_lines_22;
}
static void cont__extract_remark_lines_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 181: ... remark_lines_of(arguments(first_idx))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_23;
}
static void cont__extract_remark_lines_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 181: -> remark_lines_of(arguments(first_idx))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_remark_lines_24(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // arguments: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* arguments */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 182: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_25;
}
static void cont__extract_remark_lines_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 182: ... arguments(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = frame->slots[0] /* arguments */;
  func = myself->type;
  frame->cont = cont__extract_remark_lines_26;
}
static void cont__extract_remark_lines_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 182: ... remark_lines_of(arguments(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_27;
}
static void cont__extract_remark_lines_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 182: -> remark_lines_of(arguments(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_remark_lines_9(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_10;
}
static void cont__extract_remark_lines_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 169: -> remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_remark_lines_11(void) {
  allocate_initialized_frame_gc(1, 9);
  // slot allocations:
  // node: 0
  // arguments: 1
  // first_idx: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  frame->slots[1] /* arguments */ = create_future();
  frame->slots[2] /* first_idx */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 171: $arguments arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_12;
}
static void cont__extract_remark_lines_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* arguments */, arguments->slots[0]);
  // 175: node.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_13;
}
static void cont__extract_remark_lines_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 173: $first_idx
  // 174:   if
  // 175:     node.is_an_assignment
  // 176:     -> 2
  // 177:     -> 1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = func__extract_remark_lines_14;
  arguments->slots[2] = func__extract_remark_lines_15;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_16;
}
static void entry__extract_remark_lines_14(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: -> 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_remark_lines_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 177: -> 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_remark_lines_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* first_idx */, arguments->slots[0]);
  // 180: ... arguments(first_idx)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* first_idx */;
  result_count = 1;
  myself = frame->slots[1] /* arguments */;
  func = myself->type;
  frame->cont = cont__extract_remark_lines_17;
}
static void cont__extract_remark_lines_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 180: ... remark_lines_of(arguments(first_idx))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_18;
}
static void cont__extract_remark_lines_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 180: ... remark_lines_of(arguments(first_idx)).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_19;
}
static void cont__extract_remark_lines_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 180: not(remark_lines_of(arguments(first_idx)).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_20;
}
static void cont__extract_remark_lines_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 181: -> remark_lines_of(arguments(first_idx))
  frame->slots[7] /* temp__5 */ = create_closure(entry__extract_remark_lines_21, 0);
  // 182: -> remark_lines_of(arguments(-1))
  frame->slots[8] /* temp__6 */ = create_closure(entry__extract_remark_lines_24, 0);
  // 179: if
  // 180:   not(remark_lines_of(arguments(first_idx)).is_empty)
  // 181:   -> remark_lines_of(arguments(first_idx))
  // 182:   -> remark_lines_of(arguments(-1))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  arguments->slots[2] = frame->slots[8] /* temp__6 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_remark_lines_1(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 168: ... remark_lines_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_2;
}
static void cont__extract_remark_lines_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 168: ... remark_lines_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_3;
}
static void cont__extract_remark_lines_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 168: not(remark_lines_of(node).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_4;
}
static void cont__extract_remark_lines_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 168: ... arguments_of(node).is_empty
  frame->slots[5] /* temp__5 */ = create_closure(entry__extract_remark_lines_5, 0);
  // 168: not(remark_lines_of(node).is_empty) || arguments_of(node).is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_8;
}
static void entry__extract_remark_lines_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* node */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 168: ... arguments_of(node)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_6;
}
static void cont__extract_remark_lines_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 168: ... arguments_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__extract_remark_lines_7;
}
static void cont__extract_remark_lines_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 168: ... arguments_of(node).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_remark_lines_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 169: -> remark_lines_of(node)
  frame->slots[6] /* temp__6 */ = create_closure(entry__extract_remark_lines_9, 0);
  // 170: :
  // 171:   $arguments arguments_of(node)
  // 172:   
  // 173:   $first_idx
  // 174:     if
  // 175:       node.is_an_assignment
  // 176:       -> 2
  // 177:       -> 1
  // 178:   
  // 179:   if
  // ...
  frame->slots[7] /* temp__7 */ = create_closure(entry__extract_remark_lines_11, 0);
  // 167: if
  // 168:   not(remark_lines_of(node).is_empty) || arguments_of(node).is_empty
  // 169:   -> remark_lines_of(node)
  // 170:   :
  // 171:     $arguments arguments_of(node)
  // 172:     
  // 173:     $first_idx
  // 174:       if
  // 175:         node.is_an_assignment
  // 176:         -> 2
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  arguments->slots[2] = frame->slots[7] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_1(void) {
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
  define__compiler__module_name(create_future());
  define__compiler__required_modules(undefined);
  define__compiler__used_namespaces(undefined);
  define__compiler__defined_namespaces(undefined);
  define__compiler__namespace_mappings(undefined);
  define__compiler__included_files(undefined);
  define__compiler__linked_libraries(undefined);
  define__compiler__enumeration_count(undefined);
  define__compiler__dependent_data(undefined);
  frame->slots[3] /* fragments */ = create_cell();
  frame->slots[4] /* trees */ = create_cell();
  frame->slots[5] /* first_idx */ = create_cell();
  frame->slots[6] /* local_method_names */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 185: ... : ewriteln "extracting documentation from @(filename)"
  frame->slots[7] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_2, 0);
  // 185: if verbose: ewriteln "extracting documentation from @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__verbose();
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_5;
}
static void entry__extract_documentation_from_file_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // filename: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 185: ... "extracting documentation from @(filename)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__f68a3e9b60626ed6;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_4;
}
static void cont__extract_documentation_from_file_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: ... ewriteln "extracting documentation from @(filename)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 186: ... load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_6;
}
static void cont__extract_documentation_from_file_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 186: $buf load(filename).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_7;
}
static void cont__extract_documentation_from_file_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* buf */, arguments->slots[0]);
  // 187: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_8;
}
static void cont__extract_documentation_from_file_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 187: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_9;
}
static void cont__extract_documentation_from_file_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 187: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_10;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_12;
}
static void entry__extract_documentation_from_file_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1cbf9967f0b4797a;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 188: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_13;
}
static void cont__extract_documentation_from_file_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 188: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_14;
}
static void cont__extract_documentation_from_file_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 188: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_15;
}
static void cont__extract_documentation_from_file_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 188: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_16;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_18;
}
static void entry__extract_documentation_from_file_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 188: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cdb2cfe249b97e8f;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 189: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_19;
}
static void cont__extract_documentation_from_file_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 189: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_20;
}
static void cont__extract_documentation_from_file_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 189: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_21;
}
static void cont__extract_documentation_from_file_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 189: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_22;
}
static void cont__extract_documentation_from_file_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 189: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_25;
}
static void entry__extract_documentation_from_file_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 189: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f5ba012e5873af55;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 192: ... filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_27;
}
static void cont__extract_documentation_from_file_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 192: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_29;
}
static void cont__extract_documentation_from_file_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 191: %compiler::module_name
  // 192:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 193:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_30;
}
static void cont__extract_documentation_from_file_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__compiler__module_name(), arguments->slots[0]);
  // 195: %%compiler::required_modules empty_insert_order_table
  set__compiler__required_modules(get__empty_insert_order_table());
  // 196: %%compiler::used_namespaces empty_insert_order_set
  set__compiler__used_namespaces(get__empty_insert_order_set());
  // 197: %%compiler::defined_namespaces empty_insert_order_set
  set__compiler__defined_namespaces(get__empty_insert_order_set());
  // 198: %%compiler::namespace_mappings empty_insert_order_table
  set__compiler__namespace_mappings(get__empty_insert_order_table());
  // 199: %%compiler::included_files empty_insert_order_set
  set__compiler__included_files(get__empty_insert_order_set());
  // 200: %%compiler::linked_libraries empty_insert_order_set
  set__compiler__linked_libraries(get__empty_insert_order_set());
  // 201: %%compiler::enumeration_count 0
  set__compiler__enumeration_count(number__0);
  // 202: %%compiler::dependent_data empty_insert_order_set
  set__compiler__dependent_data(get__empty_insert_order_set());
  // 203: $$fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_31;
}
static void cont__extract_documentation_from_file_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 204: update_each &fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = func__extract_documentation_from_file_32;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_34;
}
static void entry__extract_documentation_from_file_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 204: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_33;
}
static void cont__extract_documentation_from_file_33(void) {
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
static void cont__extract_documentation_from_file_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 205: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 206: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 207: ... : (-> done)
  // 208:   for_each fragments: (idx fragment)
  // 209:     case source_of(fragment)(1)
  // 210:       '#':
  // 211:         pass
  // 212:       '<':
  // 213:         !first_idx idx+1
  // 214:         parse_meta_instruction $_tree fragment
  // 215:       :
  // 216:         done
  frame->slots[7] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_35, 0);
  // 207: do: (-> done)
  // 208:   for_each fragments: (idx fragment)
  // 209:     case source_of(fragment)(1)
  // 210:       '#':
  // 211:         pass
  // 212:       '<':
  // 213:         !first_idx idx+1
  // 214:         parse_meta_instruction $_tree fragment
  // 215:       :
  // 216:         done
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_45;
}
static void entry__extract_documentation_from_file_35(void) {
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
  // 208: ... : (idx fragment)
  // 209:   case source_of(fragment)(1)
  // 210:     '#':
  // 211:       pass
  // 212:     '<':
  // 213:       !first_idx idx+1
  // 214:       parse_meta_instruction $_tree fragment
  // 215:     :
  // 216:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_36, 2);
  // 208: for_each fragments: (idx fragment)
  // 209:   case source_of(fragment)(1)
  // 210:     '#':
  // 211:       pass
  // 212:     '<':
  // 213:       !first_idx idx+1
  // 214:       parse_meta_instruction $_tree fragment
  // 215:     :
  // 216:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_44;
}
static void entry__extract_documentation_from_file_39(void) {
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
  // 213: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_40;
}
static void cont__extract_documentation_from_file_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 214: parse_meta_instruction $_tree fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_41;
}
static void cont__extract_documentation_from_file_41(void) {
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
static void entry__extract_documentation_from_file_42(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 216: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_43(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_36(void) {
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
  // 209: ... source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_37;
}
static void cont__extract_documentation_from_file_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 209: ... source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_38;
}
static void cont__extract_documentation_from_file_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 212: ... :
  // 213:   !first_idx idx+1
  // 214:   parse_meta_instruction $_tree fragment
  frame->slots[6] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_39, 0);
  // 215: :
  // 216:   done
  frame->slots[7] /* temp__4 */ = create_closure(entry__extract_documentation_from_file_42, 0);
  // 209: case source_of(fragment)(1)
  // 210:   '#':
  // 211:     pass
  // 212:   '<':
  // 213:     !first_idx idx+1
  // 214:     parse_meta_instruction $_tree fragment
  // 215:   :
  // 216:     done
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__35;
  arguments->slots[2] = func__extract_documentation_from_file_43;
  arguments->slots[3] = character__60;
  arguments->slots[4] = frame->slots[6] /* temp__3 */;
  arguments->slots[5] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_44(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 217: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_46;
}
static void cont__extract_documentation_from_file_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 217: range &fragments first_idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_47;
}
static void cont__extract_documentation_from_file_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 218: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_48, 1);
  // 218: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_51;
}
static void entry__extract_documentation_from_file_48(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 218: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_49;
}
static void cont__extract_documentation_from_file_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 218: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_50;
}
static void cont__extract_documentation_from_file_50(void) {
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
static void cont__extract_documentation_from_file_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 219: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_52;
}
static void cont__extract_documentation_from_file_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 219: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_53;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_56;
}
static void entry__extract_documentation_from_file_53(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 219: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa724815d896ba8;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_55;
}
static void cont__extract_documentation_from_file_55(void) {
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
static void cont__extract_documentation_from_file_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 220: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 221: ... : (statement)
  // 222:   cond
  // 223:     -> statement.is_a_remark: pass
  // 224:     -> statement.is_c_code: pass
  // 225:     -> statement.is_an_assignment:
  // 226:       $destination arguments_of(statement)(1)
  // 227:       if destination.is_a_definition:
  // 228:         $identifier identifier_of(destination)
  // 229:         unless namespace_of(identifier).is_defined:
  // 230:           $source arguments_of(statement)(2)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_57, 1);
  // 221: for_each trees: (statement)
  // 222:   cond
  // 223:     -> statement.is_a_remark: pass
  // 224:     -> statement.is_c_code: pass
  // 225:     -> statement.is_an_assignment:
  // 226:       $destination arguments_of(statement)(1)
  // 227:       if destination.is_a_definition:
  // 228:         $identifier identifier_of(destination)
  // 229:         unless namespace_of(identifier).is_defined:
  // 230:           $source arguments_of(statement)(2)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_82;
}
static void entry__extract_documentation_from_file_78(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // local_method_names: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* local_method_names */
  frame->slots[1] = myself->closure.frame->slots[2]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 232: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_79;
}
static void cont__extract_documentation_from_file_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 232: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_80;
}
static void cont__extract_documentation_from_file_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 232: !local_method_names(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_81;
}
static void cont__extract_documentation_from_file_81(void) {
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
static void entry__extract_documentation_from_file_74(void) {
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
  // 230: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_75;
}
static void cont__extract_documentation_from_file_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 230: $source arguments_of(statement)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_76;
}
static void cont__extract_documentation_from_file_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 231: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_77;
}
static void cont__extract_documentation_from_file_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 231: ... :
  // 232:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_78, 0);
  // 231: if source.is_a_polymorphic_function_constant:
  // 232:   !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_70(void) {
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
  // 228: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_71;
}
static void cont__extract_documentation_from_file_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 229: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_72;
}
static void cont__extract_documentation_from_file_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 229: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_73;
}
static void cont__extract_documentation_from_file_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 229: ... :
  // 230:   $source arguments_of(statement)(2)
  // 231:   if source.is_a_polymorphic_function_constant:
  // 232:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_74, 0);
  // 229: unless namespace_of(identifier).is_defined:
  // 230:   $source arguments_of(statement)(2)
  // 231:   if source.is_a_polymorphic_function_constant:
  // 232:     !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_66(void) {
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
  // 226: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_67;
}
static void cont__extract_documentation_from_file_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 226: $destination arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_68;
}
static void cont__extract_documentation_from_file_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 227: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_69;
}
static void cont__extract_documentation_from_file_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 227: ... :
  // 228:   $identifier identifier_of(destination)
  // 229:   unless namespace_of(identifier).is_defined:
  // 230:     $source arguments_of(statement)(2)
  // 231:     if source.is_a_polymorphic_function_constant:
  // 232:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_70, 0);
  // 227: if destination.is_a_definition:
  // 228:   $identifier identifier_of(destination)
  // 229:   unless namespace_of(identifier).is_defined:
  // 230:     $source arguments_of(statement)(2)
  // 231:     if source.is_a_polymorphic_function_constant:
  // 232:       !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_63(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_60(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_58(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 223: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_59;
}
static void cont__extract_documentation_from_file_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 223: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_60;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_61(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_62;
}
static void cont__extract_documentation_from_file_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: -> statement.is_c_code: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_file_63;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_64(void) {
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
  // 225: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_65;
}
static void cont__extract_documentation_from_file_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 225: ... :
  // 226:   $destination arguments_of(statement)(1)
  // 227:   if destination.is_a_definition:
  // 228:     $identifier identifier_of(destination)
  // 229:     unless namespace_of(identifier).is_defined:
  // 230:       $source arguments_of(statement)(2)
  // 231:       if source.is_a_polymorphic_function_constant:
  // 232:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_66, 0);
  // 225: -> statement.is_an_assignment:
  // 226:   $destination arguments_of(statement)(1)
  // 227:   if destination.is_a_definition:
  // 228:     $identifier identifier_of(destination)
  // 229:     unless namespace_of(identifier).is_defined:
  // 230:       $source arguments_of(statement)(2)
  // 231:       if source.is_a_polymorphic_function_constant:
  // 232:         !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_57(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 223: -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_58, 0);
  // 224: -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_61, 0);
  // 225: -> statement.is_an_assignment:
  // 226:   $destination arguments_of(statement)(1)
  // 227:   if destination.is_a_definition:
  // 228:     $identifier identifier_of(destination)
  // 229:     unless namespace_of(identifier).is_defined:
  // 230:       $source arguments_of(statement)(2)
  // 231:       if source.is_a_polymorphic_function_constant:
  // 232:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_64, 0);
  // 222: cond
  // 223:   -> statement.is_a_remark: pass
  // 224:   -> statement.is_c_code: pass
  // 225:   -> statement.is_an_assignment:
  // 226:     $destination arguments_of(statement)(1)
  // 227:     if destination.is_a_definition:
  // 228:       $identifier identifier_of(destination)
  // 229:       unless namespace_of(identifier).is_defined:
  // 230:         $source arguments_of(statement)(2)
  // 231:         if source.is_a_polymorphic_function_constant:
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
static void cont__extract_documentation_from_file_82(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 233: ... :
  // 234:   (
  // 235:     statement
  // 236:     -> break
  // 237:   )
  // 238:   cond
  // 239:     -> statement.is_a_remark:
  // 240:       $remark_lines remark_lines_of(statement)
  // 241:       if any_of(remark_lines has_prefix "Topic:"):
  // 242:         $paragraphs remark_lines.to_paragraphs
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_83, 1);
  // 233: for_each trees:
  // 234:   (
  // 235:     statement
  // 236:     -> break
  // 237:   )
  // 238:   cond
  // 239:     -> statement.is_a_remark:
  // 240:       $remark_lines remark_lines_of(statement)
  // 241:       if any_of(remark_lines has_prefix "Topic:"):
  // 242:         $paragraphs remark_lines.to_paragraphs
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_224;
}
static void entry__extract_documentation_from_file_83(void) {
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
  // 239: -> statement.is_a_remark:
  // 240:   $remark_lines remark_lines_of(statement)
  // 241:   if any_of(remark_lines has_prefix "Topic:"):
  // 242:     $paragraphs remark_lines.to_paragraphs
  // 243:     do: (-> done)
  // 244:       for_each paragraphs: (idx paragraph)
  // 245:         if paragraph .has_prefix. "Topic:":
  // 246:           $topic trim(paragraph .behind. "Topic:")
  // 247:           !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:           done
  frame->slots[4] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_84, 0);
  // 249: -> statement.is_c_code:
  // 250:   $identifier identifier_of(statement)
  // 251:   if identifier.is_defined:
  // 252:     $namespace namespace_of(identifier)
  // 253:     if namespace.is_defined:
  // 254:       $name name_of(identifier)
  // 255:       case kind_of(statement)
  // 256:         "type":
  // 257:           if namespace.is_defined:
  // 258:             $base base_of(statement)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_103, 0);
  // 277: -> statement.is_an_assignment:
  // 278:   $destination arguments_of(statement)(1)(.base_of undefined)
  // 279:   $$info symbol_info(.filename_of filename)
  // 280:   if destination.is_a_definition:
  // 281:     $identifier identifier_of(destination)
  // 282:     $namespace namespace_of(identifier)
  // 283:     if namespace.is_defined:
  // 284:       $name name_of(identifier)
  // 285:       $iname ordered_name(namespace name)
  // 286:       !info
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_134, 0);
  // 238: cond
  // 239:   -> statement.is_a_remark:
  // 240:     $remark_lines remark_lines_of(statement)
  // 241:     if any_of(remark_lines has_prefix "Topic:"):
  // 242:       $paragraphs remark_lines.to_paragraphs
  // 243:       do: (-> done)
  // 244:         for_each paragraphs: (idx paragraph)
  // 245:           if paragraph .has_prefix. "Topic:":
  // 246:             $topic trim(paragraph .behind. "Topic:")
  // 247:             !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_223;
}
static void entry__extract_documentation_from_file_213(void) {
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
  // 341: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_214;
}
static void cont__extract_documentation_from_file_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 341: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_215;
}
static void cont__extract_documentation_from_file_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 341: ... :
  // 342:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_216, 0);
  // 341: unless namespace_of(attr).is_defined:
  // 342:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_217;
}
static void entry__extract_documentation_from_file_216(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 342: !attr.used_namespaces_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* attr */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_namespaces_of, get__used_namespaces());
    ((CELL *)frame->slots[0])->contents /* attr */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 343: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_218;
}
static void cont__extract_documentation_from_file_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 343: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_219;
}
static void cont__extract_documentation_from_file_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 344: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 345: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 345: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_220;
}
static void cont__extract_documentation_from_file_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 345: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_221;
}
static void cont__extract_documentation_from_file_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 345: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 346: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_222;
}
static void cont__extract_documentation_from_file_222(void) {
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
static void entry__extract_documentation_from_file_210(void) {
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
  // 339: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_211;
}
static void cont__extract_documentation_from_file_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 340: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_212;
}
static void cont__extract_documentation_from_file_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 340: ... :
  // 341:   unless namespace_of(attr).is_defined:
  // 342:     !attr.used_namespaces_of used_namespaces
  // 343:   $$definition default_value(definitions(iname) symbol_info)
  // 344:   !definition.kind_of INLINE_C_TYPE
  // 345:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 346:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_213, 0);
  // 340: unless local_method_names(attr_name):
  // 341:   unless namespace_of(attr).is_defined:
  // 342:     !attr.used_namespaces_of used_namespaces
  // 343:   $$definition default_value(definitions(iname) symbol_info)
  // 344:   !definition.kind_of INLINE_C_TYPE
  // 345:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 346:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_204(void) {
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
  // 331: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_205;
}
static void cont__extract_documentation_from_file_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 334: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_206;
}
static void cont__extract_documentation_from_file_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 334: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_207;
}
static void cont__extract_documentation_from_file_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 333: $type
  // 334:   default_value(definitions(iname) symbol_info)
  // 335:     .kind_of INLINE_C_TYPE
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 337: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* type */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_208;
}
static void cont__extract_documentation_from_file_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 338: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_209;
}
static void cont__extract_documentation_from_file_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 338: ... :
  // 339:   $attr_name attr.to_string
  // 340:   unless local_method_names(attr_name):
  // 341:     unless namespace_of(attr).is_defined:
  // 342:       !attr.used_namespaces_of used_namespaces
  // 343:     $$definition default_value(definitions(iname) symbol_info)
  // 344:     !definition.kind_of INLINE_C_TYPE
  // 345:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 346:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_210, 0);
  // 338: if attr.is_defined:
  // 339:   $attr_name attr.to_string
  // 340:   unless local_method_names(attr_name):
  // 341:     unless namespace_of(attr).is_defined:
  // 342:       !attr.used_namespaces_of used_namespaces
  // 343:     $$definition default_value(definitions(iname) symbol_info)
  // 344:     !definition.kind_of INLINE_C_TYPE
  // 345:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 346:     !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_144(void) {
  allocate_initialized_frame_gc(7, 17);
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
  // is_not_a_remark: 9
  // source: 10
  frame->slots[0] = myself->closure.frame->slots[5]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[6]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[4] = myself->closure.frame->slots[2]; /* statement */
  frame->slots[5] = myself->closure.frame->slots[3]; /* break */
  frame->slots[6] = myself->closure.frame->slots[4]; /* local_method_names */
  // _define $is_not_a_remark 
  // : (node)
  //   is_a_remark !temp__2 node
  //   not !temp__1 temp__2
  //   -> temp__1
  frame->slots[9] /* is_not_a_remark */ = func__extract_documentation_from_file_145;
  frame->slots[7] /* name */ = create_future();
  frame->slots[8] /* iname */ = create_future();
  frame->slots[10] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_148;
}
static void entry__extract_documentation_from_file_145(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // node: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 291: ... node.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* node */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_146;
}
static void cont__extract_documentation_from_file_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 291: ... not(node.is_a_remark)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_147;
}
static void cont__extract_documentation_from_file_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 291: ... -> not(node.is_a_remark)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* name */, arguments->slots[0]);
  // 285: $iname ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[7] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_149;
}
static void cont__extract_documentation_from_file_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* iname */, arguments->slots[0]);
  // 287: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_150;
}
static void cont__extract_documentation_from_file_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 288: ... variable_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_151;
}
static void cont__extract_documentation_from_file_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 289: ... extract_remark_lines(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = var._extract_remark_lines;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_152;
}
static void cont__extract_documentation_from_file_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 286: !info
  // 287:   .name_of identifier.to_string
  // 288:   .variable_kind_of variable_kind_of(destination)
  // 289:   .remark_lines_of extract_remark_lines(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[11] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, frame->slots[12] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[13] /* temp__3 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 294: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_153;
}
static void cont__extract_documentation_from_file_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 294: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_154;
}
static void cont__extract_documentation_from_file_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 294: ... range(arguments_of(statement) 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_155;
}
static void cont__extract_documentation_from_file_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 293: $source
  // 294:   find_first(range(arguments_of(statement) 2 -1) is_not_a_remark)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[9] /* is_not_a_remark */;
  result_count = 1;
  myself = get__find_first();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_156;
}
static void cont__extract_documentation_from_file_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* source */, arguments->slots[0]);
  // 297: -> source.is_a_polymorphic_function_constant:
  // 298:   !polymorphic_functions(name namespace) true
  // 299:   !definitions(iname)
  // 300:     info
  // 301:       .kind_of
  // 302:         if
  // 303:           source.is_a_setter
  // 304:           -> POLYMORPHIC_ATTRIBUTE
  // 305:           -> POLYMORPHIC_FUNCTION
  // 306:   break
  frame->slots[11] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_157, 0);
  // 307: -> source.is_a_body:
  // 308:   !info
  // 309:     .base_of "types::function"
  // 310:     .kind_of FUNCTION
  // 311:     .parameters_of parameters_of(source)
  // 312:     .remark_lines_of extract_remark_lines(statement)
  frame->slots[12] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_166, 0);
  // 313: -> source.is_a_c_body: !info.kind_of INLINE_C_FUNCTION
  frame->slots[13] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_172, 0);
  // 314: -> source.is_an_identifier:
  // 315:   if namespace_of(source).is_defined:
  // 316:     !info.base_of source.to_string
  frame->slots[14] /* temp__4 */ = create_closure(entry__extract_documentation_from_file_175, 0);
  // 317: -> source.is_a_unique_item_constant:
  // 318:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 319:   break
  frame->slots[15] /* temp__5 */ = create_closure(entry__extract_documentation_from_file_182, 0);
  // 320: -> source.is_a_constant: !info.kind_of CONSTANT
  frame->slots[16] /* temp__6 */ = create_closure(entry__extract_documentation_from_file_186, 0);
  // 296: cond
  // 297:   -> source.is_a_polymorphic_function_constant:
  // 298:     !polymorphic_functions(name namespace) true
  // 299:     !definitions(iname)
  // 300:       info
  // 301:         .kind_of
  // 302:           if
  // 303:             source.is_a_setter
  // 304:             -> POLYMORPHIC_ATTRIBUTE
  // 305:             -> POLYMORPHIC_FUNCTION
  // ...
  argument_count = 6;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  arguments->slots[3] = frame->slots[14] /* temp__4 */;
  arguments->slots[4] = frame->slots[15] /* temp__5 */;
  arguments->slots[5] = frame->slots[16] /* temp__6 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_189;
}
static void entry__extract_documentation_from_file_188(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: ... !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._CONSTANT);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_184(void) {
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
  // 318: !definitions(iname) info(.kind_of UNIQUE_ITEM)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._UNIQUE_ITEM);
    frame->slots[3] /* temp__1 */ = temp;

  }
  // 318: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_185;
}
static void cont__extract_documentation_from_file_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 319: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[2] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_180(void) {
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
  // 316: !info.base_of source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_181;
}
static void cont__extract_documentation_from_file_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 316: !info.base_of
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
static void entry__extract_documentation_from_file_177(void) {
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
  // 315: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_178;
}
static void cont__extract_documentation_from_file_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 315: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_179;
}
static void cont__extract_documentation_from_file_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   !info.base_of source.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_180, 0);
  // 315: if namespace_of(source).is_defined:
  // 316:   !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_174(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: ... !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_FUNCTION);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_168(void) {
  allocate_initialized_frame_gc(3, 5);
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
  // 311: ... parameters_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_169;
}
static void cont__extract_documentation_from_file_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 312: ... extract_remark_lines(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = var._extract_remark_lines;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_170;
}
static void cont__extract_documentation_from_file_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 308: !info
  // 309:   .base_of "types::function"
  // 310:   .kind_of FUNCTION
  // 311:   .parameters_of parameters_of(source)
  // 312:   .remark_lines_of extract_remark_lines(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, string__f7c371b7c3c668a7);
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
static void entry__extract_documentation_from_file_159(void) {
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
  // 298: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = get__true();
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_160;
}
static void cont__extract_documentation_from_file_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 303: source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_161;
}
static void cont__extract_documentation_from_file_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = func__extract_documentation_from_file_162;
  arguments->slots[2] = func__extract_documentation_from_file_163;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_164;
}
static void entry__extract_documentation_from_file_162(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: -> POLYMORPHIC_ATTRIBUTE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_ATTRIBUTE;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_163(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: -> POLYMORPHIC_FUNCTION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 299: !definitions(iname)
  // 300:   info
  // 301:     .kind_of
  // 302:       if
  // 303:         source.is_a_setter
  // 304:         -> POLYMORPHIC_ATTRIBUTE
  // 305:         -> POLYMORPHIC_FUNCTION
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[6] /* temp__1 */);
    frame->slots[8] /* temp__3 */ = temp;

  }
  // 299: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[8] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_165;
}
static void cont__extract_documentation_from_file_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 306: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_157(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // source: 0
  // name: 1
  // namespace: 2
  // iname: 3
  // info: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[7]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[4] = myself->closure.frame->slots[2]; /* info */
  frame->slots[5] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_158;
}
static void cont__extract_documentation_from_file_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 297: ... :
  // 298:   !polymorphic_functions(name namespace) true
  // 299:   !definitions(iname)
  // 300:     info
  // 301:       .kind_of
  // 302:         if
  // 303:           source.is_a_setter
  // 304:           -> POLYMORPHIC_ATTRIBUTE
  // 305:           -> POLYMORPHIC_FUNCTION
  // 306:   break
  frame->slots[7] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_159, 0);
  // 297: -> source.is_a_polymorphic_function_constant:
  // 298:   !polymorphic_functions(name namespace) true
  // 299:   !definitions(iname)
  // 300:     info
  // 301:       .kind_of
  // 302:         if
  // 303:           source.is_a_setter
  // 304:           -> POLYMORPHIC_ATTRIBUTE
  // 305:           -> POLYMORPHIC_FUNCTION
  // 306:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_166(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // info: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[4]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 307: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_167;
}
static void cont__extract_documentation_from_file_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 307: ... :
  // 308:   !info
  // 309:     .base_of "types::function"
  // 310:     .kind_of FUNCTION
  // 311:     .parameters_of parameters_of(source)
  // 312:     .remark_lines_of extract_remark_lines(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_168, 0);
  // 307: -> source.is_a_body:
  // 308:   !info
  // 309:     .base_of "types::function"
  // 310:     .kind_of FUNCTION
  // 311:     .parameters_of parameters_of(source)
  // 312:     .remark_lines_of extract_remark_lines(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_172(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 313: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_173;
}
static void cont__extract_documentation_from_file_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 313: ... : !info.kind_of INLINE_C_FUNCTION
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_174, 0);
  // 313: -> source.is_a_c_body: !info.kind_of INLINE_C_FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_175(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_176;
}
static void cont__extract_documentation_from_file_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 314: ... :
  // 315:   if namespace_of(source).is_defined:
  // 316:     !info.base_of source.to_string
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_177, 0);
  // 314: -> source.is_an_identifier:
  // 315:   if namespace_of(source).is_defined:
  // 316:     !info.base_of source.to_string
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_182(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // source: 0
  // iname: 1
  // info: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[2]; /* info */
  frame->slots[3] = myself->closure.frame->slots[5]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 317: ... source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_183;
}
static void cont__extract_documentation_from_file_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 317: ... :
  // 318:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 319:   break
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_184, 0);
  // 317: -> source.is_a_unique_item_constant:
  // 318:   !definitions(iname) info(.kind_of UNIQUE_ITEM)
  // 319:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_186(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // source: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[10]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 320: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_187;
}
static void cont__extract_documentation_from_file_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 320: ... : !info.kind_of CONSTANT
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_188, 0);
  // 320: -> source.is_a_constant: !info.kind_of CONSTANT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_189(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 321: ... attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_190;
}
static void cont__extract_documentation_from_file_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 322: ... :
  // 323:   $previous_definition definitions(iname)
  // 324:   if previous_definition.is_defined:
  // 325:     if kind_of(previous_definition) == INLINE_C_TYPE:
  // 326:       !info.types_of types_of(previous_definition)
  // 327:       !info.derived_types_of derived_types_of(previous_definition)
  // 328:       !info.methods_of methods_of(previous_definition)
  // 329:   !definitions(iname) info
  frame->slots[12] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_191, 0);
  // 330: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_203;
}
static void entry__extract_documentation_from_file_191(void) {
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
  // 323: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_192;
}
static void cont__extract_documentation_from_file_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 324: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_193;
}
static void cont__extract_documentation_from_file_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 324: ... :
  // 325:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 326:     !info.types_of types_of(previous_definition)
  // 327:     !info.derived_types_of derived_types_of(previous_definition)
  // 328:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_194, 0);
  // 324: if previous_definition.is_defined:
  // 325:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 326:     !info.types_of types_of(previous_definition)
  // 327:     !info.derived_types_of derived_types_of(previous_definition)
  // 328:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_201;
}
static void entry__extract_documentation_from_file_197(void) {
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
  // 326: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_198;
}
static void cont__extract_documentation_from_file_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 326: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 327: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_199;
}
static void cont__extract_documentation_from_file_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 327: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 328: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_200;
}
static void cont__extract_documentation_from_file_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 328: !info.methods_of
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
static void entry__extract_documentation_from_file_194(void) {
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
  // 325: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_195;
}
static void cont__extract_documentation_from_file_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 325: ... kind_of(previous_definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_196;
}
static void cont__extract_documentation_from_file_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 325: ... :
  // 326:   !info.types_of types_of(previous_definition)
  // 327:   !info.derived_types_of derived_types_of(previous_definition)
  // 328:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_197, 0);
  // 325: if kind_of(previous_definition) == INLINE_C_TYPE:
  // 326:   !info.types_of types_of(previous_definition)
  // 327:   !info.derived_types_of derived_types_of(previous_definition)
  // 328:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_201(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 329: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* info */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_202;
}
static void cont__extract_documentation_from_file_202(void) {
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
static void cont__extract_documentation_from_file_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 330: ... :
  // 331:   $$attr attribute_of(destination)
  // 332:   
  // 333:   $type
  // 334:     default_value(definitions(iname) symbol_info)
  // 335:       .kind_of INLINE_C_TYPE
  // 336:   
  // 337:   !definitions(iname) type
  // 338:   if attr.is_defined:
  // 339:     $attr_name attr.to_string
  // ...
  frame->slots[14] /* temp__4 */ = create_closure(entry__extract_documentation_from_file_204, 0);
  // 321: case attribute_kind_of(destination)
  // 322:   NONE:
  // 323:     $previous_definition definitions(iname)
  // 324:     if previous_definition.is_defined:
  // 325:       if kind_of(previous_definition) == INLINE_C_TYPE:
  // 326:         !info.types_of types_of(previous_definition)
  // 327:         !info.derived_types_of derived_types_of(previous_definition)
  // 328:         !info.methods_of methods_of(previous_definition)
  // 329:     !definitions(iname) info
  // 330:   ATTRIBUTE_KIND, METHOD_KIND:
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = get__NONE();
  arguments->slots[2] = frame->slots[12] /* temp__2 */;
  arguments->slots[3] = frame->slots[13] /* temp__3 */;
  arguments->slots[4] = frame->slots[14] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_140(void) {
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
  // 281: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_141;
}
static void cont__extract_documentation_from_file_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* identifier */, arguments->slots[0]);
  // 282: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_142;
}
static void cont__extract_documentation_from_file_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* namespace */, arguments->slots[0]);
  // 283: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_143;
}
static void cont__extract_documentation_from_file_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 283: ... :
  // 284:   $name name_of(identifier)
  // 285:   $iname ordered_name(namespace name)
  // 286:   !info
  // 287:     .name_of identifier.to_string
  // 288:     .variable_kind_of variable_kind_of(destination)
  // 289:     .remark_lines_of extract_remark_lines(statement)
  // 290:   
  // 291:   $is_not_a_remark: (node) -> not(node.is_a_remark)
  // 292:   
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_144, 0);
  // 283: if namespace.is_defined:
  // 284:   $name name_of(identifier)
  // 285:   $iname ordered_name(namespace name)
  // 286:   !info
  // 287:     .name_of identifier.to_string
  // 288:     .variable_kind_of variable_kind_of(destination)
  // 289:     .remark_lines_of extract_remark_lines(statement)
  // 290:   
  // 291:   $is_not_a_remark: (node) -> not(node.is_a_remark)
  // 292:   
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
static void entry__extract_documentation_from_file_136(void) {
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
  // 278: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_137;
}
static void cont__extract_documentation_from_file_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 278: ... arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_138;
}
static void cont__extract_documentation_from_file_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 278: $destination arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 279: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 280: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_139;
}
static void cont__extract_documentation_from_file_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 280: ... :
  // 281:   $identifier identifier_of(destination)
  // 282:   $namespace namespace_of(identifier)
  // 283:   if namespace.is_defined:
  // 284:     $name name_of(identifier)
  // 285:     $iname ordered_name(namespace name)
  // 286:     !info
  // 287:       .name_of identifier.to_string
  // 288:       .variable_kind_of variable_kind_of(destination)
  // 289:       .remark_lines_of extract_remark_lines(statement)
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_140, 0);
  // 280: if destination.is_a_definition:
  // 281:   $identifier identifier_of(destination)
  // 282:   $namespace namespace_of(identifier)
  // 283:   if namespace.is_defined:
  // 284:     $name name_of(identifier)
  // 285:     $iname ordered_name(namespace name)
  // 286:     !info
  // 287:       .name_of identifier.to_string
  // 288:       .variable_kind_of variable_kind_of(destination)
  // 289:       .remark_lines_of extract_remark_lines(statement)
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
static void entry__extract_documentation_from_file_116(void) {
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
  // 258: $base base_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_117;
}
static void cont__extract_documentation_from_file_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* base */, arguments->slots[0]);
  // 262: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_118;
}
static void cont__extract_documentation_from_file_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 265: base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_119;
}
static void cont__extract_documentation_from_file_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 266: -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__extract_documentation_from_file_120, 0);
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = func__extract_documentation_from_file_122;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_123;
}
static void entry__extract_documentation_from_file_120(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* base */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 266: ... base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_121;
}
static void cont__extract_documentation_from_file_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 266: -> base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_122(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 268: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_124;
}
static void cont__extract_documentation_from_file_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 259: !definitions(ordered_name(namespace name))
  // 260:   symbol_info
  // 261:     .kind_of INLINE_C_TYPE
  // 262:     .name_of identifier.to_string
  // 263:     .base_of
  // 264:       if
  // 265:         base.is_defined
  // 266:         -> base.to_string
  // 267:         -> undefined
  // 268:     .remark_lines_of remark_lines_of(statement)
  // ...
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
  // 259: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[2] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_125;
}
static void cont__extract_documentation_from_file_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 259: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[11] /* temp__6 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_126;
}
static void cont__extract_documentation_from_file_126(void) {
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
static void entry__extract_documentation_from_file_114(void) {
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
  // 257: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_115;
}
static void cont__extract_documentation_from_file_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 257: ... :
  // 258:   $base base_of(statement)
  // 259:   !definitions(ordered_name(namespace name))
  // 260:     symbol_info
  // 261:       .kind_of INLINE_C_TYPE
  // 262:       .name_of identifier.to_string
  // 263:       .base_of
  // 264:         if
  // 265:           base.is_defined
  // 266:           -> base.to_string
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_116, 0);
  // 257: if namespace.is_defined:
  // 258:   $base base_of(statement)
  // 259:   !definitions(ordered_name(namespace name))
  // 260:     symbol_info
  // 261:       .kind_of INLINE_C_TYPE
  // 262:       .name_of identifier.to_string
  // 263:       .base_of
  // 264:         if
  // 265:           base.is_defined
  // 266:           -> base.to_string
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_127(void) {
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
  // 274: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_128;
}
static void cont__extract_documentation_from_file_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 275: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_129;
}
static void cont__extract_documentation_from_file_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 271: !definitions(ordered_name(namespace name))
  // 272:   symbol_info
  // 273:     .kind_of INLINE_C_OBJECT
  // 274:     .name_of identifier.to_string
  // 275:     .remark_lines_of remark_lines_of(statement)
  // 276:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_OBJECT);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[4] /* filename */);
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 271: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_130;
}
static void cont__extract_documentation_from_file_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 271: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_131;
}
static void cont__extract_documentation_from_file_131(void) {
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
static void entry__extract_documentation_from_file_111(void) {
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
  // 254: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_112;
}
static void cont__extract_documentation_from_file_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 255: ... kind_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_113;
}
static void cont__extract_documentation_from_file_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 256: ... :
  // 257:   if namespace.is_defined:
  // 258:     $base base_of(statement)
  // 259:     !definitions(ordered_name(namespace name))
  // 260:       symbol_info
  // 261:         .kind_of INLINE_C_TYPE
  // 262:         .name_of identifier.to_string
  // 263:         .base_of
  // 264:           if
  // 265:             base.is_defined
  // ...
  frame->slots[6] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_114, 0);
  // 270: ... :
  // 271:   !definitions(ordered_name(namespace name))
  // 272:     symbol_info
  // 273:       .kind_of INLINE_C_OBJECT
  // 274:       .name_of identifier.to_string
  // 275:       .remark_lines_of remark_lines_of(statement)
  // 276:       .filename_of filename
  frame->slots[7] /* temp__3 */ = create_closure(entry__extract_documentation_from_file_127, 0);
  // 255: case kind_of(statement)
  // 256:   "type":
  // 257:     if namespace.is_defined:
  // 258:       $base base_of(statement)
  // 259:       !definitions(ordered_name(namespace name))
  // 260:         symbol_info
  // 261:           .kind_of INLINE_C_TYPE
  // 262:           .name_of identifier.to_string
  // 263:           .base_of
  // 264:             if
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = string__2a0aef0b5de07d5c;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  arguments->slots[3] = string__4c1f570701a272a3;
  arguments->slots[4] = frame->slots[7] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_108(void) {
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
  // 252: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_109;
}
static void cont__extract_documentation_from_file_109(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 253: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_110;
}
static void cont__extract_documentation_from_file_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 253: ... :
  // 254:   $name name_of(identifier)
  // 255:   case kind_of(statement)
  // 256:     "type":
  // 257:       if namespace.is_defined:
  // 258:         $base base_of(statement)
  // 259:         !definitions(ordered_name(namespace name))
  // 260:           symbol_info
  // 261:             .kind_of INLINE_C_TYPE
  // 262:             .name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_111, 0);
  // 253: if namespace.is_defined:
  // 254:   $name name_of(identifier)
  // 255:   case kind_of(statement)
  // 256:     "type":
  // 257:       if namespace.is_defined:
  // 258:         $base base_of(statement)
  // 259:         !definitions(ordered_name(namespace name))
  // 260:           symbol_info
  // 261:             .kind_of INLINE_C_TYPE
  // 262:             .name_of identifier.to_string
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
static void entry__extract_documentation_from_file_105(void) {
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
  // 250: $identifier identifier_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_106;
}
static void cont__extract_documentation_from_file_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 251: ... identifier.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_107;
}
static void cont__extract_documentation_from_file_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 251: ... :
  // 252:   $namespace namespace_of(identifier)
  // 253:   if namespace.is_defined:
  // 254:     $name name_of(identifier)
  // 255:     case kind_of(statement)
  // 256:       "type":
  // 257:         if namespace.is_defined:
  // 258:           $base base_of(statement)
  // 259:           !definitions(ordered_name(namespace name))
  // 260:             symbol_info
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_108, 0);
  // 251: if identifier.is_defined:
  // 252:   $namespace namespace_of(identifier)
  // 253:   if namespace.is_defined:
  // 254:     $name name_of(identifier)
  // 255:     case kind_of(statement)
  // 256:       "type":
  // 257:         if namespace.is_defined:
  // 258:           $base base_of(statement)
  // 259:           !definitions(ordered_name(namespace name))
  // 260:             symbol_info
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
static void entry__extract_documentation_from_file_92(void) {
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
  // 244: ... : (idx paragraph)
  // 245:   if paragraph .has_prefix. "Topic:":
  // 246:     $topic trim(paragraph .behind. "Topic:")
  // 247:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:     done
  frame->slots[2] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_93, 2);
  // 244: for_each paragraphs: (idx paragraph)
  // 245:   if paragraph .has_prefix. "Topic:":
  // 246:     $topic trim(paragraph .behind. "Topic:")
  // 247:     !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:     done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraphs */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_102;
}
static void entry__extract_documentation_from_file_95(void) {
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
  // 246: ... paragraph .behind. "Topic:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraph */;
  arguments->slots[1] = string__781f541a81a2a2ed;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_96;
}
static void cont__extract_documentation_from_file_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 246: $topic trim(paragraph .behind. "Topic:")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_97;
}
static void cont__extract_documentation_from_file_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* topic */, arguments->slots[0]);
  // 247: ... idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_98;
}
static void cont__extract_documentation_from_file_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 247: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_99;
}
static void cont__extract_documentation_from_file_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 247: !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraphs */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  arguments->slots[2] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_100;
}
static void cont__extract_documentation_from_file_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 247: !topics_paragraphs(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* topic */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = var._topics_paragraphs;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_101;
}
static void cont__extract_documentation_from_file_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._topics_paragraphs = arguments->slots[0];
  // 248: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_93(void) {
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
  // 245: ... paragraph .has_prefix. "Topic:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* paragraph */;
  arguments->slots[1] = string__781f541a81a2a2ed;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_94;
}
static void cont__extract_documentation_from_file_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 245: ... :
  // 246:   $topic trim(paragraph .behind. "Topic:")
  // 247:   !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:   done
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_95, 0);
  // 245: if paragraph .has_prefix. "Topic:":
  // 246:   $topic trim(paragraph .behind. "Topic:")
  // 247:   !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:   done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__extract_documentation_from_file_102(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_90(void) {
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
  // 242: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_91;
}
static void cont__extract_documentation_from_file_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* paragraphs */, arguments->slots[0]);
  // 243: ... : (-> done)
  // 244:   for_each paragraphs: (idx paragraph)
  // 245:     if paragraph .has_prefix. "Topic:":
  // 246:       $topic trim(paragraph .behind. "Topic:")
  // 247:       !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:       done
  frame->slots[2] /* temp__1 */ = create_closure(entry__extract_documentation_from_file_92, 0);
  // 243: do: (-> done)
  // 244:   for_each paragraphs: (idx paragraph)
  // 245:     if paragraph .has_prefix. "Topic:":
  // 246:       $topic trim(paragraph .behind. "Topic:")
  // 247:       !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:       done
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__do();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_86(void) {
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
  // 240: $remark_lines remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_87;
}
static void cont__extract_documentation_from_file_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* remark_lines */, arguments->slots[0]);
  // 241: ... any_of(remark_lines has_prefix "Topic:")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = get__has_prefix();
  arguments->slots[2] = string__781f541a81a2a2ed;
  result_count = 1;
  myself = get__any_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_89;
}
static void cont__extract_documentation_from_file_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 241: ... :
  // 242:   $paragraphs remark_lines.to_paragraphs
  // 243:   do: (-> done)
  // 244:     for_each paragraphs: (idx paragraph)
  // 245:       if paragraph .has_prefix. "Topic:":
  // 246:         $topic trim(paragraph .behind. "Topic:")
  // 247:         !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:         done
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_90, 0);
  // 241: if any_of(remark_lines has_prefix "Topic:"):
  // 242:   $paragraphs remark_lines.to_paragraphs
  // 243:   do: (-> done)
  // 244:     for_each paragraphs: (idx paragraph)
  // 245:       if paragraph .has_prefix. "Topic:":
  // 246:         $topic trim(paragraph .behind. "Topic:")
  // 247:         !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:         done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_file_84(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_85;
}
static void cont__extract_documentation_from_file_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 239: ... :
  // 240:   $remark_lines remark_lines_of(statement)
  // 241:   if any_of(remark_lines has_prefix "Topic:"):
  // 242:     $paragraphs remark_lines.to_paragraphs
  // 243:     do: (-> done)
  // 244:       for_each paragraphs: (idx paragraph)
  // 245:         if paragraph .has_prefix. "Topic:":
  // 246:           $topic trim(paragraph .behind. "Topic:")
  // 247:           !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:           done
  frame->slots[2] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_86, 0);
  // 239: -> statement.is_a_remark:
  // 240:   $remark_lines remark_lines_of(statement)
  // 241:   if any_of(remark_lines has_prefix "Topic:"):
  // 242:     $paragraphs remark_lines.to_paragraphs
  // 243:     do: (-> done)
  // 244:       for_each paragraphs: (idx paragraph)
  // 245:         if paragraph .has_prefix. "Topic:":
  // 246:           $topic trim(paragraph .behind. "Topic:")
  // 247:           !topics_paragraphs(topic) range(paragraphs idx+1 -1)
  // 248:           done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_103(void) {
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
  // 249: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_104;
}
static void cont__extract_documentation_from_file_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 249: ... :
  // 250:   $identifier identifier_of(statement)
  // 251:   if identifier.is_defined:
  // 252:     $namespace namespace_of(identifier)
  // 253:     if namespace.is_defined:
  // 254:       $name name_of(identifier)
  // 255:       case kind_of(statement)
  // 256:         "type":
  // 257:           if namespace.is_defined:
  // 258:             $base base_of(statement)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_105, 0);
  // 249: -> statement.is_c_code:
  // 250:   $identifier identifier_of(statement)
  // 251:   if identifier.is_defined:
  // 252:     $namespace namespace_of(identifier)
  // 253:     if namespace.is_defined:
  // 254:       $name name_of(identifier)
  // 255:       case kind_of(statement)
  // 256:         "type":
  // 257:           if namespace.is_defined:
  // 258:             $base base_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_file_134(void) {
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
  // 277: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_file_135;
}
static void cont__extract_documentation_from_file_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 277: ... :
  // 278:   $destination arguments_of(statement)(1)(.base_of undefined)
  // 279:   $$info symbol_info(.filename_of filename)
  // 280:   if destination.is_a_definition:
  // 281:     $identifier identifier_of(destination)
  // 282:     $namespace namespace_of(identifier)
  // 283:     if namespace.is_defined:
  // 284:       $name name_of(identifier)
  // 285:       $iname ordered_name(namespace name)
  // 286:       !info
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__extract_documentation_from_file_136, 0);
  // 277: -> statement.is_an_assignment:
  // 278:   $destination arguments_of(statement)(1)(.base_of undefined)
  // 279:   $$info symbol_info(.filename_of filename)
  // 280:   if destination.is_a_definition:
  // 281:     $identifier identifier_of(destination)
  // 282:     $namespace namespace_of(identifier)
  // 283:     if namespace.is_defined:
  // 284:       $name name_of(identifier)
  // 285:       $iname ordered_name(namespace name)
  // 286:       !info
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_223(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__extract_documentation_from_file_224(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_directory_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: ... extract_documentation_from_file name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_directory_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: ... extract_documentation_from_directory name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_directory_6(void) {
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
  // 352: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_directory_7;
}
static void cont__extract_documentation_from_directory_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 352: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_directory_8, 0);
  // 352: -> entry.is_a_directory: extract_documentation_from_directory name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_directory_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 353: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__9e0aed8b5d287d54;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_directory_10;
}
static void cont__extract_documentation_from_directory_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 353: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__extract_documentation_from_directory_11, 0);
  // 353: -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__extract_documentation_from_directory_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 350: $name fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_directory_5;
}
static void cont__extract_documentation_from_directory_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 352: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__extract_documentation_from_directory_6, 0);
  // 353: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__extract_documentation_from_directory_9, 0);
  // 351: cond
  // 352:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 353:   -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__extract_documentation_from_directory_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 349: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_directory_2;
}
static void cont__extract_documentation_from_directory_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 349: ... directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__extract_documentation_from_directory_3;
}
static void cont__extract_documentation_from_directory_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 349: for_each directory(--SORT path): (entry)
  // 350:   $name fullname_of(entry)
  // 351:   cond
  // 352:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 353:     -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__extract_documentation_from_directory_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__resolved_name_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 359: ... attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__resolved_name_6;
}
static void cont__resolved_name_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 359: -> attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__resolved_name_7(void) {
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
  // 361: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 362: ... used_namespaces_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = var._used_namespaces_of;
  func = myself->type;
  frame->cont = cont__resolved_name_8;
}
static void cont__resolved_name_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 362: ... : (namespace)
  // 363:   if polymorphic_functions(name namespace):
  // 364:     if resolved_namespace.is_defined:
  // 365:       Error "
  // 366:         The attribute "@(name)" cannot be uniquely resolved!
  // 367:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolved_name_9, 1);
  // 362: for_each used_namespaces_of(attr): (namespace)
  // 363:   if polymorphic_functions(name namespace):
  // 364:     if resolved_namespace.is_defined:
  // 365:       Error "
  // 366:         The attribute "@(name)" cannot be uniquely resolved!
  // 367:     !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__resolved_name_18;
}
static void entry__resolved_name_11(void) {
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
  // 364: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__resolved_name_12;
}
static void cont__resolved_name_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 364: ... :
  // 365:   Error "
  // 366:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolved_name_13, 0);
  // 364: if resolved_namespace.is_defined:
  // 365:   Error "
  // 366:     The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__resolved_name_17;
}
static void entry__resolved_name_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 365: ... "
  // 366:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7f3103e18f358a6f;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__abd8bded937d2ca5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__resolved_name_16;
}
static void cont__resolved_name_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 365: Error "
  // 366:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolved_name_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 367: !resolved_namespace namespace
  ((CELL *)frame->slots[0])->contents /* resolved_namespace */ = frame->slots[2] /* namespace */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__resolved_name_9(void) {
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
  // 363: ... polymorphic_functions(name namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__resolved_name_10;
}
static void cont__resolved_name_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 363: ... :
  // 364:   if resolved_namespace.is_defined:
  // 365:     Error "
  // 366:       The attribute "@(name)" cannot be uniquely resolved!
  // 367:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolved_name_11, 0);
  // 363: if polymorphic_functions(name namespace):
  // 364:   if resolved_namespace.is_defined:
  // 365:     Error "
  // 366:       The attribute "@(name)" cannot be uniquely resolved!
  // 367:   !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolved_name_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 368: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__resolved_name_19;
}
static void cont__resolved_name_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 368: ... :
  // 369:   Error "
  // 370:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolved_name_20, 0);
  // 368: unless resolved_namespace.is_defined:
  // 369:   Error "
  // 370:     The attribute "@(name)" cannot be resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__resolved_name_23;
}
static void entry__resolved_name_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 369: ... "
  // 370:   The attribute "@(name)" cannot be resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__7f3103e18f358a6f;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__8906d104d2e53fac;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__resolved_name_22;
}
static void cont__resolved_name_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 369: Error "
  // 370:   The attribute "@(name)" cannot be resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolved_name_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 371: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__resolved_name_25;
}
static void cont__resolved_name_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 371: -> string(resolved_namespace "::" name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__resolved_name_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // attr: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 356: $name name_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__resolved_name_2;
}
static void cont__resolved_name_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 358: namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__resolved_name_3;
}
static void cont__resolved_name_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 358: namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__resolved_name_4;
}
static void cont__resolved_name_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 359: -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__resolved_name_5, 0);
  // 360: :
  // 361:   $$resolved_namespace undefined
  // 362:   for_each used_namespaces_of(attr): (namespace)
  // 363:     if polymorphic_functions(name namespace):
  // 364:       if resolved_namespace.is_defined:
  // 365:         Error "
  // 366:           The attribute "@(name)" cannot be uniquely resolved!
  // 367:       !resolved_namespace namespace
  // 368:   unless resolved_namespace.is_defined:
  // 369:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__resolved_name_7, 0);
  // 357: if
  // 358:   namespace_of(attr).is_defined
  // 359:   -> attr.to_string
  // 360:   :
  // 361:     $$resolved_namespace undefined
  // 362:     for_each used_namespaces_of(attr): (namespace)
  // 363:       if polymorphic_functions(name namespace):
  // 364:         if resolved_namespace.is_defined:
  // 365:           Error "
  // 366:             The attribute "@(name)" cannot be uniquely resolved!
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
static void entry__add_derived_type_7(void) {
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
  // 377: ... definition.derived_types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__add_derived_type_8;
}
static void cont__add_derived_type_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 377: !definition.derived_types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__add_derived_type_9;
}
static void cont__add_derived_type_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 377: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 378: ... kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__add_derived_type_10;
}
static void cont__add_derived_type_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 378: ... kind_of(definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__add_derived_type_11;
}
static void cont__add_derived_type_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 378: ... :
  // 379:   !definition.kind_of INLINE_C_TYPE
  // 380:   $base_of_base base_of(definition)
  // 381:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__add_derived_type_12, 0);
  // 378: unless kind_of(definition) == INLINE_C_TYPE:
  // 379:   !definition.kind_of INLINE_C_TYPE
  // 380:   $base_of_base base_of(definition)
  // 381:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__add_derived_type_16;
}
static void entry__add_derived_type_15(void) {
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
  // 381: ... add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base_of_base */;
  arguments->slots[1] = frame->slots[1] /* ibase */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__add_derived_type_12(void) {
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
  // 379: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 380: $base_of_base base_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__add_derived_type_13;
}
static void cont__add_derived_type_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base_of_base */, arguments->slots[0]);
  // 381: ... base_of_base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base_of_base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__add_derived_type_14;
}
static void cont__add_derived_type_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 381: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__add_derived_type_15, 0);
  // 381: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__add_derived_type_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 382: !definitions(ibase)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__add_derived_type_17;
}
static void cont__add_derived_type_17(void) {
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
static void entry__add_derived_type_1(void) {
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
  // 374: ... base .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__add_derived_type_2;
}
static void cont__add_derived_type_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 374: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__add_derived_type_3;
}
static void cont__add_derived_type_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 374: $ibase ordered_name(base .before. "::" base .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__add_derived_type_4;
}
static void cont__add_derived_type_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ibase */, arguments->slots[0]);
  // 375: $$definition definitions(ibase)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__add_derived_type_5;
}
static void cont__add_derived_type_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* definition */ = arguments->slots[0];
  // 376: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__add_derived_type_6;
}
static void cont__add_derived_type_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 376: ... :
  // 377:   !definition.derived_types_of(name) true
  // 378:   unless kind_of(definition) == INLINE_C_TYPE:
  // 379:     !definition.kind_of INLINE_C_TYPE
  // 380:     $base_of_base base_of(definition)
  // 381:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 382:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__add_derived_type_7, 0);
  // 376: if definition.is_defined:
  // 377:   !definition.derived_types_of(name) true
  // 378:   unless kind_of(definition) == INLINE_C_TYPE:
  // 379:     !definition.kind_of INLINE_C_TYPE
  // 380:     $base_of_base base_of(definition)
  // 381:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 382:   !definitions(ibase) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__mangled_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 384: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6d82bff;
  arguments->slots[1] = string__2d7981f4e5f02b9a;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__mangled_2;
}
static void cont__mangled_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 384: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__fa72f815cd16b93;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__mangled_4;
}
static void cont__mangled_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 384: ... replace_all(name "::" = "__" '/' = "___")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__mangled_5;
}
static void cont__mangled_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 384: ... -> replace_all(name "::" = "__" '/' = "___")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__ordered_name_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 389: name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__ordered_name_2;
}
static void cont__ordered_name_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 391: namespace.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__ordered_name_3;
}
static void cont__ordered_name_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
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
  frame->cont = cont__ordered_name_4;
}
static void cont__ordered_name_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 387: ->
  // 388:   string
  // 389:     name.to_lower_case
  // 390:     '/'
  // 391:     namespace.to_lower_case
  // 392:     '/'
  // 393:     name
  // 394:     '/'
  // 395:     namespace
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__link_bar_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 399: ... "href" = "index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__25705d17a847956d;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__link_bar_5;
}
static void cont__link_bar_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 399: A "href" = "index.html" "Home"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__520aea8b5d087d5c;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__link_bar_7;
}
static void cont__link_bar_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 400: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57442216b13fc418;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__link_bar_9;
}
static void cont__link_bar_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 401: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__d0d93c5da16549ef;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__link_bar_11;
}
static void cont__link_bar_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 401: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__441f531601b242bb;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__link_bar_13;
}
static void cont__link_bar_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 402: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57442216b13fc418;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__link_bar_14;
}
static void cont__link_bar_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 403: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__cf81eefc97d2b8ee;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__link_bar_16;
}
static void cont__link_bar_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 403: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__2971b13bbf01e7f9;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__link_bar_18;
}
static void cont__link_bar_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 404: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57442216b13fc418;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__link_bar_19;
}
static void cont__link_bar_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 405: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__bc0556bbe81c68c5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__link_bar_21;
}
static void cont__link_bar_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 405: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__d6ed116d58489777;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__link_bar_23;
}
static void cont__link_bar_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 406: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__57442216b13fc418;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__link_bar_24;
}
static void cont__link_bar_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 407: ... "href" = "topics_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__b982567928221cc5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__link_bar_26;
}
static void cont__link_bar_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 407: A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__5691f96d534696f2;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__link_bar_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 398: P:
  // 399:   A "href" = "index.html" "Home"
  // 400:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 401:   A "href" = "manual.html" "Manual"
  // 402:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 403:   A "href" = "type_index.html" "Type Index"
  // 404:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 405:   A "href" = "symbol_index.html" "Symbol Index"
  // 406:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 407:   A "href" = "topics_index.html" "Topics Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__link_bar_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__to_paragraphs_1(void) {
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
  // 413: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 414: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 415: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 416: ... : (line)
  // 417:   if
  // 418:     pre_mode:
  // 419:       if
  // 420:         line .has_prefix. EXAMPLE:
  // 421:           trim &text
  // 422:           push &paragraphs text
  // 423:           !text line
  // 424:         :
  // 425:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__to_paragraphs_2, 1);
  // 416: for_each lines: (line)
  // 417:   if
  // 418:     pre_mode:
  // 419:       if
  // 420:         line .has_prefix. EXAMPLE:
  // 421:           trim &text
  // 422:           push &paragraphs text
  // 423:           !text line
  // 424:         :
  // 425:           writeln_to &text line
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__to_paragraphs_27;
}
static void entry__to_paragraphs_15(void) {
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
  // 430: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__to_paragraphs_16;
}
static void cont__to_paragraphs_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  // 431: !text ""
  ((CELL *)frame->slots[1])->contents /* text */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__to_paragraphs_12(void) {
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
  // 429: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__to_paragraphs_13;
}
static void cont__to_paragraphs_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 429: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__to_paragraphs_14;
}
static void cont__to_paragraphs_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 429: ... :
  // 430:   push &paragraphs text
  // 431:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__to_paragraphs_15, 0);
  // 429: if text != "":
  // 430:   push &paragraphs text
  // 431:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__to_paragraphs_17(void) {
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
  // 434: text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__to_paragraphs_18;
}
static void cont__to_paragraphs_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 434: ... :
  // 435:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__to_paragraphs_19, 0);
  // 436: :
  // 437:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__to_paragraphs_22, 0);
  // 433: if
  // 434:   text == "":
  // 435:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 436:   :
  // 437:     push &text ' '
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__to_paragraphs_24;
}
static void entry__to_paragraphs_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pre_mode: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 435: ... !pre_mode true
  ((CELL *)frame->slots[0])->contents /* pre_mode */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__to_paragraphs_19(void) {
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
  // 435: ... line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__to_paragraphs_20;
}
static void cont__to_paragraphs_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 435: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__to_paragraphs_21, 0);
  // 435: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__to_paragraphs_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 437: push &text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__to_paragraphs_23;
}
static void cont__to_paragraphs_23(void) {
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
static void cont__to_paragraphs_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 438: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__to_paragraphs_25;
}
static void cont__to_paragraphs_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 438: append &text line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__to_paragraphs_26;
}
static void cont__to_paragraphs_26(void) {
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
static void entry__to_paragraphs_5(void) {
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
  // 421: trim &text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__to_paragraphs_6;
}
static void cont__to_paragraphs_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 422: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__to_paragraphs_7;
}
static void cont__to_paragraphs_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = arguments->slots[0];
  // 423: !text line
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[2] /* line */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__to_paragraphs_8(void) {
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
  // 425: writeln_to &text line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__to_paragraphs_9;
}
static void cont__to_paragraphs_9(void) {
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
static void entry__to_paragraphs_3(void) {
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
  // 420: line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__to_paragraphs_4;
}
static void cont__to_paragraphs_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 420: ... :
  // 421:   trim &text
  // 422:   push &paragraphs text
  // 423:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__to_paragraphs_5, 0);
  // 424: :
  // 425:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__to_paragraphs_8, 0);
  // 419: if
  // 420:   line .has_prefix. EXAMPLE:
  // 421:     trim &text
  // 422:     push &paragraphs text
  // 423:     !text line
  // 424:   :
  // 425:     writeln_to &text line
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
static void entry__to_paragraphs_10(void) {
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
  // 428: line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__to_paragraphs_11;
}
static void cont__to_paragraphs_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 428: ... :
  // 429:   if text != "":
  // 430:     push &paragraphs text
  // 431:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__to_paragraphs_12, 0);
  // 432: :
  // 433:   if
  // 434:     text == "":
  // 435:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 436:     :
  // 437:       push &text ' '
  // 438:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__to_paragraphs_17, 0);
  // 427: if
  // 428:   line == "":
  // 429:     if text != "":
  // 430:       push &paragraphs text
  // 431:       !text ""
  // 432:   :
  // 433:     if
  // 434:       text == "":
  // 435:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 436:       :
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
static void entry__to_paragraphs_2(void) {
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
  // 418: ... :
  // 419:   if
  // 420:     line .has_prefix. EXAMPLE:
  // 421:       trim &text
  // 422:       push &paragraphs text
  // 423:       !text line
  // 424:     :
  // 425:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__to_paragraphs_3, 0);
  // 426: :
  // 427:   if
  // 428:     line == "":
  // 429:       if text != "":
  // 430:         push &paragraphs text
  // 431:         !text ""
  // 432:     :
  // 433:       if
  // 434:         text == "":
  // 435:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__to_paragraphs_10, 0);
  // 417: if
  // 418:   pre_mode:
  // 419:     if
  // 420:       line .has_prefix. EXAMPLE:
  // 421:         trim &text
  // 422:         push &paragraphs text
  // 423:         !text line
  // 424:       :
  // 425:         writeln_to &text line
  // 426:   :
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
static void cont__to_paragraphs_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 439: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__to_paragraphs_28;
}
static void cont__to_paragraphs_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 439: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__to_paragraphs_29;
}
static void cont__to_paragraphs_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 439: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__to_paragraphs_30, 0);
  // 439: if text != "": push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__to_paragraphs_32;
}
static void entry__to_paragraphs_30(void) {
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
  // 439: ... push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__to_paragraphs_31;
}
static void cont__to_paragraphs_31(void) {
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
static void cont__to_paragraphs_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 440: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__resolve_reference_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 444: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__resolve_reference_2;
}
static void cont__resolve_reference_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 444: ... :
  // 445:   $$type_name reference .before. '/'
  // 446:   $$method_name reference .behind. '/'
  // 447:   unless type_name .contains. "::": append "types::" &type_name
  // 448:   unless method_name .contains. "::": append "std::" &method_name
  // 449:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_reference_3, 0);
  // 450: :
  // 451:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__resolve_reference_17, 0);
  // 443: if
  // 444:   reference .contains. '/':
  // 445:     $$type_name reference .before. '/'
  // 446:     $$method_name reference .behind. '/'
  // 447:     unless type_name .contains. "::": append "types::" &type_name
  // 448:     unless method_name .contains. "::": append "std::" &method_name
  // 449:     !reference string(type_name '/' method_name)
  // 450:   :
  // 451:     unless reference .contains. "::": append "std::" &reference
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
  frame->cont = cont__resolve_reference_21;
}
static void entry__resolve_reference_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 451: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__625aea03e819206d;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__resolve_reference_20;
}
static void cont__resolve_reference_20(void) {
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
static void entry__resolve_reference_3(void) {
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
  // 445: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__resolve_reference_4;
}
static void cont__resolve_reference_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 446: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__resolve_reference_5;
}
static void cont__resolve_reference_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 447: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__resolve_reference_6;
}
static void cont__resolve_reference_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 447: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolve_reference_7, 0);
  // 447: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__resolve_reference_10;
}
static void entry__resolve_reference_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 447: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__b854091e176bc0c0;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__resolve_reference_9;
}
static void cont__resolve_reference_9(void) {
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
static void cont__resolve_reference_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 448: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__resolve_reference_11;
}
static void cont__resolve_reference_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 448: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__resolve_reference_12, 0);
  // 448: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__resolve_reference_15;
}
static void entry__resolve_reference_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 448: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__625aea03e819206d;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__resolve_reference_14;
}
static void cont__resolve_reference_14(void) {
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
static void cont__resolve_reference_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 449: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__resolve_reference_16;
}
static void cont__resolve_reference_16(void) {
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
static void entry__resolve_reference_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 451: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__resolve_reference_18;
}
static void cont__resolve_reference_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 451: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__resolve_reference_19, 0);
  // 451: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__resolve_reference_21(void) {
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
static void entry__add_links_1(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // paragraph: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 457: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__add_links_2;
}
static void cont__add_links_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 457: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__add_links_3;
}
static void cont__add_links_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 457: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__add_links_4;
}
static void cont__add_links_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 456: =
  // 457:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 458:   : ($reference)
  // 459:     range &reference 2 -2
  // 460:     resolve_reference &reference
  // 461:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__add_links_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__add_links_14;
}
static void entry__add_links_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 459: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__add_links_6;
}
static void cont__add_links_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 459: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__add_links_7;
}
static void cont__add_links_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 460: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__add_links_8;
}
static void cont__add_links_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 461: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__add_links_9;
}
static void cont__add_links_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 461: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cba;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__2d7981f4e5e02bed;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__701f552781dad2fe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__add_links_13;
}
static void cont__add_links_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 461: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__add_links_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 454: replace_all
  // 455:   &paragraph
  // 456:   =
  // 457:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 458:     : ($reference)
  // 459:       range &reference 2 -2
  // 460:       resolve_reference &reference
  // 461:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__add_links_15;
}
static void cont__add_links_15(void) {
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
static void entry__create_info_page_20(void) {
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
  // 474: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__create_info_page_21;
}
static void cont__create_info_page_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 476: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__create_info_page_22;
}
static void cont__create_info_page_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 476: ... :
  // 477:   $type function_name .before. '/'
  // 478:   $method function_name .behind. '/'
  // 479:   H1
  // 480:     string
  // 481:       '['
  // 482:       type
  // 483:       "]("
  // 484:       type.mangled
  // 485:       ".html)/["
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_23, 0);
  // 490: :
  // 491:   H1 function_name
  // 492:   case variable_kind_of(info)
  // 493:     STATIC_MULTI:
  // 494:       H2 "(static multi-assignment variable)"
  // 495:     DYNAMIC_SINGLE:
  // 496:       H2 "(dynamic single-assignment variable)"
  // 497:     DYNAMIC_MULTI:
  // 498:       H2 "(dynamic multi-assignment variable)"
  frame->slots[15] /* temp__3 */ = create_closure(entry__create_info_page_30, 0);
  // 475: if
  // 476:   function_name .contains. '/':
  // 477:     $type function_name .before. '/'
  // 478:     $method function_name .behind. '/'
  // 479:     H1
  // 480:       string
  // 481:         '['
  // 482:         type
  // 483:         "]("
  // 484:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_39;
}
static void entry__create_info_page_33(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 494: H2 "(static multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4ce0cf0d4ae053bd;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_35(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 496: H2 "(dynamic single-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__c674570cd5378184;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_37(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 498: H2 "(dynamic multi-assignment variable)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__f7a1838e683da008;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_23(void) {
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
  // 477: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__create_info_page_24;
}
static void cont__create_info_page_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 478: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_25;
}
static void cont__create_info_page_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 484: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_26;
}
static void cont__create_info_page_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 488: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_27;
}
static void cont__create_info_page_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__2d7981f4e5e02bed;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__76b4bf9c06ad49bb;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__2d7981f4e5e02bed;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__701f552781dad2fe;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_29;
}
static void cont__create_info_page_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 479: H1
  // 480:   string
  // 481:     '['
  // 482:     type
  // 483:     "]("
  // 484:     type.mangled
  // 485:     ".html)/["
  // 486:     method
  // 487:     "]("
  // 488:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_30(void) {
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
  // 491: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__create_info_page_31;
}
static void cont__create_info_page_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 492: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__create_info_page_32;
}
static void cont__create_info_page_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 492: case variable_kind_of(info)
  // 493:   STATIC_MULTI:
  // 494:     H2 "(static multi-assignment variable)"
  // 495:   DYNAMIC_SINGLE:
  // 496:     H2 "(dynamic single-assignment variable)"
  // 497:   DYNAMIC_MULTI:
  // 498:     H2 "(dynamic multi-assignment variable)"
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = get__STATIC_MULTI();
  arguments->slots[2] = func__create_info_page_33;
  arguments->slots[3] = get__DYNAMIC_SINGLE();
  arguments->slots[4] = func__create_info_page_35;
  arguments->slots[5] = get__DYNAMIC_MULTI();
  arguments->slots[6] = func__create_info_page_37;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 499: $$short_description undefined
  ((CELL *)frame->slots[3])->contents /* short_description */ = get__undefined();
  // 500: $$parameters empty_list
  ((CELL *)frame->slots[4])->contents /* parameters */ = get__empty_list();
  // 501: $$return_values empty_list
  ((CELL *)frame->slots[5])->contents /* return_values */ = get__empty_list();
  // 502: $$descriptions empty_list
  ((CELL *)frame->slots[6])->contents /* descriptions */ = get__empty_list();
  // 503: $$technical_details undefined
  ((CELL *)frame->slots[7])->contents /* technical_details */ = get__undefined();
  // 504: $$references empty_list
  ((CELL *)frame->slots[8])->contents /* references */ = get__empty_list();
  // 505: $$topic_list empty_list
  ((CELL *)frame->slots[9])->contents /* topic_list */ = get__empty_list();
  // 506: $$examples empty_list
  ((CELL *)frame->slots[10])->contents /* examples */ = get__empty_list();
  // 507: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__create_info_page_40;
}
static void cont__create_info_page_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* remark_lines */, arguments->slots[0]);
  // 508: ... remark_lines.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__create_info_page_41;
}
static void cont__create_info_page_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 508: ... remark_lines.is_empty
  frame->slots[15] /* temp__3 */ = create_closure(entry__create_info_page_42, 0);
  // 508: ... remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__create_info_page_44;
}
static void entry__create_info_page_42(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 508: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_43;
}
static void cont__create_info_page_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 508: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 508: ... :
  // 509:   inc &missing_documentation_count
  // 510:   if do_print_missing:
  // 511:     ewrite "
  // 512:       Missing documentation for @(function_name) (defined in @
  // 513:       "@(filename_of(info))")!
  frame->slots[16] /* temp__4 */ = create_closure(entry__create_info_page_45, 0);
  // 508: if remark_lines.is_undefined || remark_lines.is_empty:
  // 509:   inc &missing_documentation_count
  // 510:   if do_print_missing:
  // 511:     ewrite "
  // 512:       Missing documentation for @(function_name) (defined in @
  // 513:       "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[16] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_53;
}
static void entry__create_info_page_47(void) {
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
  // 513: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__create_info_page_48;
}
static void cont__create_info_page_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 511: ... "
  // 512:   Missing documentation for @(function_name) (defined in @
  // 513:   "@(filename_of(info))")!
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__6cb12e827f50f616;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__f3159560bf5212b5;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__860afb0b5f687d33;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_52;
}
static void cont__create_info_page_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 511: ewrite "
  // 512:   Missing documentation for @(function_name) (defined in @
  // 513:   "@(filename_of(info))")!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_45(void) {
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
  // 509: inc &missing_documentation_count
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__create_info_page_46;
}
static void cont__create_info_page_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._missing_documentation_count = arguments->slots[0];
  // 510: ... :
  // 511:   ewrite "
  // 512:     Missing documentation for @(function_name) (defined in @
  // 513:     "@(filename_of(info))")!
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_47, 0);
  // 510: if do_print_missing:
  // 511:   ewrite "
  // 512:     Missing documentation for @(function_name) (defined in @
  // 513:     "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_missing();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 514: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_54;
}
static void cont__create_info_page_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 514: ... :
  // 515:   $paragraphs remark_lines.to_paragraphs
  // 516:   for_each paragraphs: ($paragraph)
  // 517:     cond
  // 518:       ->
  // 519:         has_prefix
  // 520:           paragraph
  // 521:           sequence
  // 522:             "Parameter"
  // 523:             compiler::WHITESPACE
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_55, 0);
  // 514: if remark_lines.is_defined:
  // 515:   $paragraphs remark_lines.to_paragraphs
  // 516:   for_each paragraphs: ($paragraph)
  // 517:     cond
  // 518:       ->
  // 519:         has_prefix
  // 520:           paragraph
  // 521:           sequence
  // 522:             "Parameter"
  // 523:             compiler::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_178;
}
static void entry__create_info_page_173(void) {
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
  // 602: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_174;
}
static void cont__create_info_page_174(void) {
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
static void entry__create_info_page_175(void) {
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
  // 604: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_176;
}
static void cont__create_info_page_176(void) {
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
static void entry__create_info_page_171(void) {
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
  // 601: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_172;
}
static void cont__create_info_page_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 601: ... :
  // 602:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_info_page_173, 0);
  // 603: :
  // 604:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_info_page_175, 0);
  // 600: if
  // 601:   technical_details.is_defined:
  // 602:     push &technical_details paragraph
  // 603:   :
  // 604:     push &descriptions paragraph
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
static void entry__create_info_page_177(void) {
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
  // 606: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_155(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 586: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_156(void) {
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
  // 588: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__create_info_page_157;
}
static void cont__create_info_page_157(void) {
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
static void entry__create_info_page_151(void) {
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
  // 583: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_152;
}
static void cont__create_info_page_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 583: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_153;
}
static void cont__create_info_page_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 585: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_info_page_154;
}
static void cont__create_info_page_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 585: ... :
  // 586:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_info_page_155, 0);
  // 587: :
  // 588:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_info_page_156, 0);
  // 584: if
  // 585:   detail == "":
  // 586:     !technical_details empty_list
  // 587:   :
  // 588:     !technical_details list(detail)
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
static void entry__create_info_page_141(void) {
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
  // 579: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__create_info_page_142;
}
static void cont__create_info_page_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 579: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_143;
}
static void cont__create_info_page_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 580: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_144;
}
static void cont__create_info_page_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 580: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_145;
}
static void cont__create_info_page_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 581: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_146;
}
static void cont__create_info_page_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 581: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_147;
}
static void cont__create_info_page_147(void) {
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
static void entry__create_info_page_132(void) {
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
  // 570: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_133;
}
static void cont__create_info_page_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 571: push &topic_list topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* topic_list */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_134;
}
static void cont__create_info_page_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* topic_list */ = arguments->slots[0];
  // 574: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__create_info_page_135;
}
static void cont__create_info_page_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 573: $$topic_contents
  // 574:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__create_info_page_136;
}
static void cont__create_info_page_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 576: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* function_name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__create_info_page_137;
}
static void cont__create_info_page_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 577: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__create_info_page_138;
}
static void cont__create_info_page_138(void) {
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
static void entry__create_info_page_129(void) {
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
  // 569: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_130;
}
static void cont__create_info_page_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 569: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__create_info_page_131;
}
static void cont__create_info_page_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 569: ... : ($topic)
  // 570:   trim &topic
  // 571:   push &topic_list topic
  // 572:   
  // 573:   $$topic_contents
  // 574:     default_value(topics(topic) empty_key_order_set)
  // 575:   
  // 576:   !topic_contents(function_name) true
  // 577:   !topics(topic) topic_contents
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_info_page_132, 1);
  // 569: for_each split(paragraph .behind. ':' ','): ($topic)
  // 570:   trim &topic
  // 571:   push &topic_list topic
  // 572:   
  // 573:   $$topic_contents
  // 574:     default_value(topics(topic) empty_key_order_set)
  // 575:   
  // 576:   !topic_contents(function_name) true
  // 577:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_124(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 567: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_125;
}
static void cont__create_info_page_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 567: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_126;
}
static void cont__create_info_page_126(void) {
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
static void entry__create_info_page_121(void) {
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
  // 566: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_122;
}
static void cont__create_info_page_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 566: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__create_info_page_123;
}
static void cont__create_info_page_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 566: ... : (reference)
  // 567:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__create_info_page_124, 1);
  // 566: for_each split(paragraph .behind. ':' ','): (reference)
  // 567:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_99(void) {
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
  // 554: $$return_value between(paragraph compiler::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__compiler__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__create_info_page_100;
}
static void cont__create_info_page_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 556: -> return_value .has_suffix. '?':
  // 557:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__create_info_page_101, 0);
  // 558: -> return_value .has_suffix. '*':
  // 559:   !return_value
  // 560:     string
  // 561:       range(return_value 1 -2)
  // 562:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__create_info_page_107, 0);
  // 555: cond
  // 556:   -> return_value .has_suffix. '?':
  // 557:     !return_value string(range(return_value 1 -2) " (optional)")
  // 558:   -> return_value .has_suffix. '*':
  // 559:     !return_value
  // 560:       string
  // 561:         range(return_value 1 -2)
  // 562:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__create_info_page_113;
}
static void entry__create_info_page_109(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 561: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_info_page_110;
}
static void cont__create_info_page_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 561: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_info_page_111;
}
static void cont__create_info_page_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 559: !return_value
  // 560:   string
  // 561:     range(return_value 1 -2)
  // 562:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__b78062cac7fbaabb;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_112;
}
static void cont__create_info_page_112(void) {
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
static void entry__create_info_page_103(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 557: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_info_page_104;
}
static void cont__create_info_page_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 557: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_info_page_105;
}
static void cont__create_info_page_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 557: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__9c8f711f20695919;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_106;
}
static void cont__create_info_page_106(void) {
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
static void entry__create_info_page_101(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 556: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__create_info_page_102;
}
static void cont__create_info_page_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 556: ... :
  // 557:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__create_info_page_103, 0);
  // 556: -> return_value .has_suffix. '?':
  // 557:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_107(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 558: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__create_info_page_108;
}
static void cont__create_info_page_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 558: ... :
  // 559:   !return_value
  // 560:     string
  // 561:       range(return_value 1 -2)
  // 562:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__create_info_page_109, 0);
  // 558: -> return_value .has_suffix. '*':
  // 559:   !return_value
  // 560:     string
  // 561:       range(return_value 1 -2)
  // 562:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 563: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_114;
}
static void cont__create_info_page_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 563: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_115;
}
static void cont__create_info_page_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 564: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_116;
}
static void cont__create_info_page_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 564: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_117;
}
static void cont__create_info_page_117(void) {
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
static void entry__create_info_page_63(void) {
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
  // 528: $$parameter between(paragraph compiler::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__compiler__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__create_info_page_64;
}
static void cont__create_info_page_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 530: -> parameter .has_suffix. '?':
  // 531:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__create_info_page_65, 0);
  // 532: -> parameter .has_suffix. '*':
  // 533:   !parameter
  // 534:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__create_info_page_72, 0);
  // 535: -> parameter .contains. '=':
  // 536:   !parameter
  // 537:     string
  // 538:       (parameter .before. '=').trim
  // 539:       " (optional; default value: "
  // 540:       (parameter .behind. '=').trim
  // 541:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__create_info_page_79, 0);
  // 529: cond
  // 530:   -> parameter .has_suffix. '?':
  // 531:     !parameter string(range(parameter 1 -2) " (optional)")
  // 532:   -> parameter .has_suffix. '*':
  // 533:     !parameter
  // 534:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 535:   -> parameter .contains. '=':
  // 536:     !parameter
  // 537:       string
  // 538:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__create_info_page_89;
}
static void entry__create_info_page_81(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 538: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__create_info_page_82;
}
static void cont__create_info_page_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 538: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_83;
}
static void cont__create_info_page_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 540: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_84;
}
static void cont__create_info_page_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 540: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_85;
}
static void cont__create_info_page_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 536: !parameter
  // 537:   string
  // 538:     (parameter .before. '=').trim
  // 539:     " (optional; default value: "
  // 540:     (parameter .behind. '=').trim
  // 541:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__c050e39b840a7454;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__578a5af303e9cc8;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_88;
}
static void cont__create_info_page_88(void) {
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
static void entry__create_info_page_74(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 534: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_info_page_75;
}
static void cont__create_info_page_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 534: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_info_page_76;
}
static void cont__create_info_page_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 533: !parameter
  // 534:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__b78062cac7fbaabb;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_78;
}
static void cont__create_info_page_78(void) {
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
static void entry__create_info_page_67(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 531: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_info_page_68;
}
static void cont__create_info_page_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 531: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_info_page_69;
}
static void cont__create_info_page_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 531: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__9c8f711f20695919;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_71;
}
static void cont__create_info_page_71(void) {
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
static void entry__create_info_page_65(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 530: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__create_info_page_66;
}
static void cont__create_info_page_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 530: ... :
  // 531:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__create_info_page_67, 0);
  // 530: -> parameter .has_suffix. '?':
  // 531:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 532: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__create_info_page_73;
}
static void cont__create_info_page_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 532: ... :
  // 533:   !parameter
  // 534:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__create_info_page_74, 0);
  // 532: -> parameter .has_suffix. '*':
  // 533:   !parameter
  // 534:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_79(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 535: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__create_info_page_80;
}
static void cont__create_info_page_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 535: ... :
  // 536:   !parameter
  // 537:     string
  // 538:       (parameter .before. '=').trim
  // 539:       " (optional; default value: "
  // 540:       (parameter .behind. '=').trim
  // 541:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__create_info_page_81, 0);
  // 535: -> parameter .contains. '=':
  // 536:   !parameter
  // 537:     string
  // 538:       (parameter .before. '=').trim
  // 539:       " (optional; default value: "
  // 540:       (parameter .behind. '=').trim
  // 541:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_89(void) {
  if (argument_count != 0) {
    invalid_results_error();
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
  frame->cont = cont__create_info_page_90;
}
static void cont__create_info_page_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 542: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__create_info_page_91;
}
static void cont__create_info_page_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 543: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_92;
}
static void cont__create_info_page_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 543: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_93;
}
static void cont__create_info_page_93(void) {
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
static void entry__create_info_page_58(void) {
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
  // 525: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__create_info_page_59;
}
static void cont__create_info_page_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__64f823ac322ba4f7;
  arguments->slots[1] = get__compiler__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_61;
}
static void cont__create_info_page_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_62;
}
static void cont__create_info_page_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 527: :
  // 528:   $$parameter between(paragraph compiler::WHITESPACE ':')
  // 529:   cond
  // 530:     -> parameter .has_suffix. '?':
  // 531:       !parameter string(range(parameter 1 -2) " (optional)")
  // 532:     -> parameter .has_suffix. '*':
  // 533:       !parameter
  // 534:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 535:     -> parameter .contains. '=':
  // 536:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__create_info_page_63, 0);
  // 518: ->
  // 519:   has_prefix
  // 520:     paragraph
  // 521:     sequence
  // 522:       "Parameter"
  // 523:       compiler::WHITESPACE
  // 524:       NAME
  // 525:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 526:       ':'
  // 527:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_94(void) {
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
  // 551: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__create_info_page_95;
}
static void cont__create_info_page_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__98cc095015cb8089;
  arguments->slots[1] = get__compiler__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_97;
}
static void cont__create_info_page_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_98;
}
static void cont__create_info_page_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 553: :
  // 554:   $$return_value between(paragraph compiler::WHITESPACE ':')
  // 555:   cond
  // 556:     -> return_value .has_suffix. '?':
  // 557:       !return_value string(range(return_value 1 -2) " (optional)")
  // 558:     -> return_value .has_suffix. '*':
  // 559:       !return_value
  // 560:         string
  // 561:           range(return_value 1 -2)
  // 562:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__create_info_page_99, 0);
  // 544: ->
  // 545:   has_prefix
  // 546:     paragraph
  // 547:     sequence
  // 548:       "Returns"
  // 549:       compiler::WHITESPACE
  // 550:       NAME
  // 551:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 552:       ':'
  // 553:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_118(void) {
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
  // 565: ... paragraph .has_prefix. "See also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__76a4224cb17b643f;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_120;
}
static void cont__create_info_page_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 565: ... :
  // 566:   for_each split(paragraph .behind. ':' ','): (reference)
  // 567:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_121, 0);
  // 565: -> paragraph .has_prefix. "See also:":
  // 566:   for_each split(paragraph .behind. ':' ','): (reference)
  // 567:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_127(void) {
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
  // 568: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_128;
}
static void cont__create_info_page_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 568: ... :
  // 569:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 570:     trim &topic
  // 571:     push &topic_list topic
  // 572:     
  // 573:     $$topic_contents
  // 574:       default_value(topics(topic) empty_key_order_set)
  // 575:     
  // 576:     !topic_contents(function_name) true
  // 577:     !topics(topic) topic_contents
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_info_page_129, 0);
  // 568: -> paragraph .has_prefix. TOPIC:
  // 569:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 570:     trim &topic
  // 571:     push &topic_list topic
  // 572:     
  // 573:     $$topic_contents
  // 574:       default_value(topics(topic) empty_key_order_set)
  // 575:     
  // 576:     !topic_contents(function_name) true
  // 577:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_139(void) {
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
  // 578: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_140;
}
static void cont__create_info_page_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 578: ... :
  // 579:   $title (paragraph .before. ':').trim
  // 580:   $text (paragraph .behind. ':').trim
  // 581:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_141, 0);
  // 578: -> paragraph .has_prefix. EXAMPLE:
  // 579:   $title (paragraph .before. ':').trim
  // 580:   $text (paragraph .behind. ':').trim
  // 581:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_148(void) {
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
  // 582: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__8f3750dfc2ad5d0a;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_150;
}
static void cont__create_info_page_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 582: ... :
  // 583:   $detail (paragraph .behind. ':').trim
  // 584:   if
  // 585:     detail == "":
  // 586:       !technical_details empty_list
  // 587:     :
  // 588:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_151, 0);
  // 582: -> paragraph .has_prefix. "Technical Details:":
  // 583:   $detail (paragraph .behind. ':').trim
  // 584:   if
  // 585:     detail == "":
  // 586:       !technical_details empty_list
  // 587:     :
  // 588:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_158(void) {
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
  // 593: ... '/', IDENTIFIER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__IDENTIFIER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_159;
}
static void cont__create_info_page_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 593: ... optional('/', IDENTIFIER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__create_info_page_160;
}
static void cont__create_info_page_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 593: '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__IDENTIFIER();
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_161;
}
static void cont__create_info_page_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 594: : ($reference)
  // 595:   range &reference 2 -2
  // 596:   resolve_and_check_reference &reference
  // 597:   -> "[@(reference)](@(reference.mangled).html)"
  frame->slots[9] /* temp__5 */ = create_closure(entry__create_info_page_162, 1);
  // 592: =
  // 593:   '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 594:   : ($reference)
  // 595:     range &reference 2 -2
  // 596:     resolve_and_check_reference &reference
  // 597:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_168;
}
static void entry__create_info_page_162(void) {
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
  // 595: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__create_info_page_163;
}
static void cont__create_info_page_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 595: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__create_info_page_164;
}
static void cont__create_info_page_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 596: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__create_info_page_165;
}
static void cont__create_info_page_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 597: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_166;
}
static void cont__create_info_page_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 597: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cba;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__2d7981f4e5e02bed;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__701f552781dad2fe;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_167;
}
static void cont__create_info_page_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 597: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 590: replace_all
  // 591:   &paragraph
  // 592:   =
  // 593:     '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 594:     : ($reference)
  // 595:       range &reference 2 -2
  // 596:       resolve_and_check_reference &reference
  // 597:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__create_info_page_169;
}
static void cont__create_info_page_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 599: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_170;
}
static void cont__create_info_page_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 599: ... :
  // 600:   if
  // 601:     technical_details.is_defined:
  // 602:       push &technical_details paragraph
  // 603:     :
  // 604:       push &descriptions paragraph
  frame->slots[6] /* temp__2 */ = create_closure(entry__create_info_page_171, 0);
  // 605: :
  // 606:   !short_description paragraph
  frame->slots[7] /* temp__3 */ = create_closure(entry__create_info_page_177, 0);
  // 598: if
  // 599:   short_description.is_defined:
  // 600:     if
  // 601:       technical_details.is_defined:
  // 602:         push &technical_details paragraph
  // 603:       :
  // 604:         push &descriptions paragraph
  // 605:   :
  // 606:     !short_description paragraph
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
static void entry__create_info_page_57(void) {
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
  // 518: ->
  // 519:   has_prefix
  // 520:     paragraph
  // 521:     sequence
  // 522:       "Parameter"
  // 523:       compiler::WHITESPACE
  // 524:       NAME
  // 525:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 526:       ':'
  // 527:   :
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__create_info_page_58, 0);
  // 544: ->
  // 545:   has_prefix
  // 546:     paragraph
  // 547:     sequence
  // 548:       "Returns"
  // 549:       compiler::WHITESPACE
  // 550:       NAME
  // 551:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 552:       ':'
  // 553:   :
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__create_info_page_94, 0);
  // 565: -> paragraph .has_prefix. "See also:":
  // 566:   for_each split(paragraph .behind. ':' ','): (reference)
  // 567:     push &references reference.trim
  frame->slots[13] /* temp__3 */ = create_closure(entry__create_info_page_118, 0);
  // 568: -> paragraph .has_prefix. TOPIC:
  // 569:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 570:     trim &topic
  // 571:     push &topic_list topic
  // 572:     
  // 573:     $$topic_contents
  // 574:       default_value(topics(topic) empty_key_order_set)
  // 575:     
  // 576:     !topic_contents(function_name) true
  // 577:     !topics(topic) topic_contents
  frame->slots[14] /* temp__4 */ = create_closure(entry__create_info_page_127, 0);
  // 578: -> paragraph .has_prefix. EXAMPLE:
  // 579:   $title (paragraph .before. ':').trim
  // 580:   $text (paragraph .behind. ':').trim
  // 581:   push &examples title = text
  frame->slots[15] /* temp__5 */ = create_closure(entry__create_info_page_139, 0);
  // 582: -> paragraph .has_prefix. "Technical Details:":
  // 583:   $detail (paragraph .behind. ':').trim
  // 584:   if
  // 585:     detail == "":
  // 586:       !technical_details empty_list
  // 587:     :
  // 588:       !technical_details list(detail)
  frame->slots[16] /* temp__6 */ = create_closure(entry__create_info_page_148, 0);
  // 589: :
  // 590:   replace_all
  // 591:     &paragraph
  // 592:     =
  // 593:       '<', IDENTIFIER, optional('/', IDENTIFIER), '>'
  // 594:       : ($reference)
  // 595:         range &reference 2 -2
  // 596:         resolve_and_check_reference &reference
  // 597:         -> "[@(reference)](@(reference.mangled).html)"
  // 598:   if
  // ...
  frame->slots[17] /* temp__7 */ = create_closure(entry__create_info_page_158, 0);
  // 517: cond
  // 518:   ->
  // 519:     has_prefix
  // 520:       paragraph
  // 521:       sequence
  // 522:         "Parameter"
  // 523:         compiler::WHITESPACE
  // 524:         NAME
  // 525:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 526:         ':'
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
static void entry__create_info_page_55(void) {
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
  // 515: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__create_info_page_56;
}
static void cont__create_info_page_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* paragraphs */, arguments->slots[0]);
  // 516: ... : ($paragraph)
  // 517:   cond
  // 518:     ->
  // 519:       has_prefix
  // 520:         paragraph
  // 521:         sequence
  // 522:           "Parameter"
  // 523:           compiler::WHITESPACE
  // 524:           NAME
  // 525:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[12] /* temp__1 */ = create_closure(entry__create_info_page_57, 1);
  // 516: for_each paragraphs: ($paragraph)
  // 517:   cond
  // 518:     ->
  // 519:       has_prefix
  // 520:         paragraph
  // 521:         sequence
  // 522:           "Parameter"
  // 523:           compiler::WHITESPACE
  // 524:           NAME
  // 525:           optional(PARAMETER_COUNT_OR_MYSELF)
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
static void cont__create_info_page_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 607: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__create_info_page_179;
}
static void cont__create_info_page_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 607: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_info_page_180;
}
static void cont__create_info_page_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 607: ... :
  // 608:   for_each parameters_of(info): (parameter)
  // 609:     case
  // 610:       parameter_kind_of(parameter)
  // 611:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 612:         pass
  // 613:       :
  // 614:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:         cond
  // 616:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__create_info_page_181, 0);
  // 607: if kind_of(info) == FUNCTION:
  // 608:   for_each parameters_of(info): (parameter)
  // 609:     case
  // 610:       parameter_kind_of(parameter)
  // 611:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 612:         pass
  // 613:       :
  // 614:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:         cond
  // 616:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_218;
}
static void entry__create_info_page_186(void) {
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
  // 614: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__create_info_page_187;
}
static void cont__create_info_page_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 614: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__create_info_page_188;
}
static void cont__create_info_page_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 614: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_189;
}
static void cont__create_info_page_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 616: -> parameter.is_an_optional_item:
  // 617:   if
  // 618:     default_value_of(parameter).is_defined:
  // 619:       write_to
  // 620:         &name
  // 621:         " (optional; default value: "
  // 622:         default_value_of(parameter).to_string
  // 623:         ")"
  // 624:     :
  // 625:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__create_info_page_190, 0);
  // 626: -> parameter.is_an_expanded_item:
  // 627:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__create_info_page_201, 0);
  // 615: cond
  // 616:   -> parameter.is_an_optional_item:
  // 617:     if
  // 618:       default_value_of(parameter).is_defined:
  // 619:         write_to
  // 620:           &name
  // 621:           " (optional; default value: "
  // 622:           default_value_of(parameter).to_string
  // 623:           ")"
  // 624:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__create_info_page_205;
}
static void entry__create_info_page_203(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 627: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__b78062cac7fbaabb;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__create_info_page_204;
}
static void cont__create_info_page_204(void) {
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
static void entry__create_info_page_195(void) {
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
  // 622: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__create_info_page_196;
}
static void cont__create_info_page_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 622: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__create_info_page_197;
}
static void cont__create_info_page_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 619: write_to
  // 620:   &name
  // 621:   " (optional; default value: "
  // 622:   default_value_of(parameter).to_string
  // 623:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__c050e39b840a7454;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__578a5af303e9cc8;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__create_info_page_198;
}
static void cont__create_info_page_198(void) {
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
static void entry__create_info_page_199(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__9c8f711f20695919;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__create_info_page_200;
}
static void cont__create_info_page_200(void) {
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
static void entry__create_info_page_192(void) {
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
  // 618: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__create_info_page_193;
}
static void cont__create_info_page_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 618: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_194;
}
static void cont__create_info_page_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 618: ... :
  // 619:   write_to
  // 620:     &name
  // 621:     " (optional; default value: "
  // 622:     default_value_of(parameter).to_string
  // 623:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__create_info_page_195, 0);
  // 624: :
  // 625:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__create_info_page_199, 0);
  // 617: if
  // 618:   default_value_of(parameter).is_defined:
  // 619:     write_to
  // 620:       &name
  // 621:       " (optional; default value: "
  // 622:       default_value_of(parameter).to_string
  // 623:       ")"
  // 624:   :
  // 625:     append &name " (optional)"
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
static void entry__create_info_page_190(void) {
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
  // 616: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__create_info_page_191;
}
static void cont__create_info_page_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   if
  // 618:     default_value_of(parameter).is_defined:
  // 619:       write_to
  // 620:         &name
  // 621:         " (optional; default value: "
  // 622:         default_value_of(parameter).to_string
  // 623:         ")"
  // 624:     :
  // 625:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_192, 0);
  // 616: -> parameter.is_an_optional_item:
  // 617:   if
  // 618:     default_value_of(parameter).is_defined:
  // 619:       write_to
  // 620:         &name
  // 621:         " (optional; default value: "
  // 622:         default_value_of(parameter).to_string
  // 623:         ")"
  // 624:     :
  // 625:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_201(void) {
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
  // 626: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__create_info_page_202;
}
static void cont__create_info_page_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 626: ... :
  // 627:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_203, 0);
  // 626: -> parameter.is_an_expanded_item:
  // 627:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_205(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 631: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__create_info_page_206;
}
static void cont__create_info_page_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 631: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_207;
}
static void cont__create_info_page_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 631: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__create_info_page_208;
}
static void cont__create_info_page_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 632: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__create_info_page_209, 0);
  // 629: $description
  // 630:   if
  // 631:     not(remark_lines_of(parameter).is_empty)
  // 632:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 633:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__create_info_page_213;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_214;
}
static void entry__create_info_page_209(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 632: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__create_info_page_210;
}
static void cont__create_info_page_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 632: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__create_info_page_211;
}
static void cont__create_info_page_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 632: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__create_info_page_212;
}
static void cont__create_info_page_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 632: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__create_info_page_213(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 633: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 635: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_215;
}
static void cont__create_info_page_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 635: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__create_info_page_216;
}
static void cont__create_info_page_216(void) {
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
static void entry__create_info_page_217(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 612: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_183(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 610: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__create_info_page_184;
}
static void cont__create_info_page_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 611: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_185;
}
static void cont__create_info_page_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 613: :
  // 614:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:   cond
  // 616:     -> parameter.is_an_optional_item:
  // 617:       if
  // 618:         default_value_of(parameter).is_defined:
  // 619:           write_to
  // 620:             &name
  // 621:             " (optional; default value: "
  // 622:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__create_info_page_186, 0);
  // 609: case
  // 610:   parameter_kind_of(parameter)
  // 611:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 612:     pass
  // 613:   :
  // 614:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:     cond
  // 616:       -> parameter.is_an_optional_item:
  // 617:         if
  // 618:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__create_info_page_217;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_181(void) {
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
  // 608: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__create_info_page_182;
}
static void cont__create_info_page_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 608: ... : (parameter)
  // 609:   case
  // 610:     parameter_kind_of(parameter)
  // 611:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 612:       pass
  // 613:     :
  // 614:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:       cond
  // 616:         -> parameter.is_an_optional_item:
  // 617:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_183, 1);
  // 608: for_each parameters_of(info): (parameter)
  // 609:   case
  // 610:     parameter_kind_of(parameter)
  // 611:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 612:       pass
  // 613:     :
  // 614:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 615:       cond
  // 616:         -> parameter.is_an_optional_item:
  // 617:           if
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
static void cont__create_info_page_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 636: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_219;
}
static void cont__create_info_page_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 636: ... : P short_description
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_220, 0);
  // 636: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_221;
}
static void entry__create_info_page_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 636: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_222;
}
static void cont__create_info_page_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 637: ... :
  // 638:   H2 "Parameters"
  // 639:   DL:
  // 640:     for_each parameters: (parameter)
  // 641:       DT key_of(parameter)
  // 642:       DD: P std::value_of(parameter)
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_223, 0);
  // 637: unless parameters.is_empty:
  // 638:   H2 "Parameters"
  // 639:   DL:
  // 640:     for_each parameters: (parameter)
  // 641:       DT key_of(parameter)
  // 642:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_232;
}
static void entry__create_info_page_230(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 642: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__create_info_page_231;
}
static void cont__create_info_page_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 642: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_227(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 641: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__create_info_page_228;
}
static void cont__create_info_page_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 641: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__create_info_page_229;
}
static void cont__create_info_page_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_230, 0);
  // 642: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_226(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: for_each parameters: (parameter)
  // 641:   DT key_of(parameter)
  // 642:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__create_info_page_227;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_223(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1d61915d27bb27b2;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_225;
}
static void cont__create_info_page_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 639: ... :
  // 640:   for_each parameters: (parameter)
  // 641:     DT key_of(parameter)
  // 642:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_226, 0);
  // 639: DL:
  // 640:   for_each parameters: (parameter)
  // 641:     DT key_of(parameter)
  // 642:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_233;
}
static void cont__create_info_page_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 643: ... :
  // 644:   H2 "Returns"
  // 645:   DL:
  // 646:     for_each return_values: (return_value)
  // 647:       DT key_of(return_value)
  // 648:       DD: P std::value_of(return_value)
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_234, 0);
  // 643: unless return_values.is_empty:
  // 644:   H2 "Returns"
  // 645:   DL:
  // 646:     for_each return_values: (return_value)
  // 647:       DT key_of(return_value)
  // 648:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_242;
}
static void entry__create_info_page_240(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 648: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__create_info_page_241;
}
static void cont__create_info_page_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 648: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_237(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 647: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__create_info_page_238;
}
static void cont__create_info_page_238(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 647: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__create_info_page_239;
}
static void cont__create_info_page_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 648: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_240, 0);
  // 648: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_236(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 646: for_each return_values: (return_value)
  // 647:   DT key_of(return_value)
  // 648:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__create_info_page_237;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_234(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 644: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__98cc095015cb8089;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_235;
}
static void cont__create_info_page_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 645: ... :
  // 646:   for_each return_values: (return_value)
  // 647:     DT key_of(return_value)
  // 648:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_236, 0);
  // 645: DL:
  // 646:   for_each return_values: (return_value)
  // 647:     DT key_of(return_value)
  // 648:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_242(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 649: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_243;
}
static void cont__create_info_page_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 649: ... :
  // 650:   H2 "Description"
  // 651:   for_each descriptions: (description) P description
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_244, 0);
  // 649: unless descriptions.is_empty:
  // 650:   H2 "Description"
  // 651:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_248;
}
static void entry__create_info_page_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 651: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_244(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__a8951b1f3c70ab27;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_246;
}
static void cont__create_info_page_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 651: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__create_info_page_247;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_248(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 652: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_249;
}
static void cont__create_info_page_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 652: ... :
  // 653:   H2 "Technical Details"
  // 654:   for_each technical_details: (detail) P detail
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_250, 0);
  // 652: if technical_details.is_defined:
  // 653:   H2 "Technical Details"
  // 654:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_254;
}
static void entry__create_info_page_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 654: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_250(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 653: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__aba611e6ea1bf855;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_252;
}
static void cont__create_info_page_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 654: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__create_info_page_253;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_254(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 655: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_255;
}
static void cont__create_info_page_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 655: ... :
  // 656:   H2 "See also"
  // 657:   TABLE:
  // 658:     for_each references: ($reference)
  // 659:       resolve_and_check_reference &reference
  // 660:       TR:
  // 661:         TD: A "href" = "@(reference.mangled).html" reference
  // 662:         TD "&nbsp;"
  // 663:         TD short_descriptions(reference)
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_256, 0);
  // 655: unless references.is_empty:
  // 656:   H2 "See also"
  // 657:   TABLE:
  // 658:     for_each references: ($reference)
  // 659:       resolve_and_check_reference &reference
  // 660:       TR:
  // 661:         TD: A "href" = "@(reference.mangled).html" reference
  // 662:         TD "&nbsp;"
  // 663:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_271;
}
static void entry__create_info_page_262(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 661: ... : A "href" = "@(reference.mangled).html" reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_263, 0);
  // 661: TD: A "href" = "@(reference.mangled).html" reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_267;
}
static void entry__create_info_page_263(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 661: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_264;
}
static void cont__create_info_page_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 661: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_265;
}
static void cont__create_info_page_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 661: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_266;
}
static void cont__create_info_page_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 661: ... A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_267(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 662: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c1f52a3813ab2ec;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_269;
}
static void cont__create_info_page_269(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__create_info_page_270;
}
static void cont__create_info_page_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 663: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_260(void) {
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
  // 659: resolve_and_check_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_and_check_reference */;
  func = myself->type;
  frame->cont = cont__create_info_page_261;
}
static void cont__create_info_page_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 660: ... :
  // 661:   TD: A "href" = "@(reference.mangled).html" reference
  // 662:   TD "&nbsp;"
  // 663:   TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_262, 0);
  // 660: TR:
  // 661:   TD: A "href" = "@(reference.mangled).html" reference
  // 662:   TD "&nbsp;"
  // 663:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_259(void) {
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
  // 658: ... : ($reference)
  // 659:   resolve_and_check_reference &reference
  // 660:   TR:
  // 661:     TD: A "href" = "@(reference.mangled).html" reference
  // 662:     TD "&nbsp;"
  // 663:     TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_260, 1);
  // 658: for_each references: ($reference)
  // 659:   resolve_and_check_reference &reference
  // 660:   TR:
  // 661:     TD: A "href" = "@(reference.mangled).html" reference
  // 662:     TD "&nbsp;"
  // 663:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_256(void) {
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
  // 656: H2 "See also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6c80aed48449962f;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_258;
}
static void cont__create_info_page_258(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: ... :
  // 658:   for_each references: ($reference)
  // 659:     resolve_and_check_reference &reference
  // 660:     TR:
  // 661:       TD: A "href" = "@(reference.mangled).html" reference
  // 662:       TD "&nbsp;"
  // 663:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_259, 0);
  // 657: TABLE:
  // 658:   for_each references: ($reference)
  // 659:     resolve_and_check_reference &reference
  // 660:     TR:
  // 661:       TD: A "href" = "@(reference.mangled).html" reference
  // 662:       TD "&nbsp;"
  // 663:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_271(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__create_info_page_272;
}
static void cont__create_info_page_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 664: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_273;
}
static void cont__create_info_page_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 664: ... :
  // 665:   H2 "Implemented by"
  // 666:   TABLE:
  // 667:     for_each types_of(info): (name)
  // 668:       $method string(name '/' function_name)
  // 669:       TR:
  // 670:         TD: A "href" = "@(name.mangled).html" name
  // 671:         TD "&nbsp;as&nbsp;"
  // 672:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[15] /* temp__3 */ = create_closure(entry__create_info_page_274, 0);
  // 664: unless types_of(info).is_empty:
  // 665:   H2 "Implemented by"
  // 666:   TABLE:
  // 667:     for_each types_of(info): (name)
  // 668:       $method string(name '/' function_name)
  // 669:       TR:
  // 670:         TD: A "href" = "@(name.mangled).html" name
  // 671:         TD "&nbsp;as&nbsp;"
  // 672:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_293;
}
static void entry__create_info_page_289(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 672: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_290;
}
static void cont__create_info_page_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 672: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_291;
}
static void cont__create_info_page_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 672: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_292;
}
static void cont__create_info_page_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 672: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_281(void) {
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
  // 670: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_282, 0);
  // 670: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_286;
}
static void entry__create_info_page_282(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 670: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_283;
}
static void cont__create_info_page_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 670: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_284;
}
static void cont__create_info_page_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 670: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_285;
}
static void cont__create_info_page_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 670: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_286(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 671: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__664d2661efdaf349;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_288;
}
static void cont__create_info_page_288(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 672: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_289, 0);
  // 672: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_279(void) {
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
  // 668: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_280;
}
static void cont__create_info_page_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 669: ... :
  // 670:   TD: A "href" = "@(name.mangled).html" name
  // 671:   TD "&nbsp;as&nbsp;"
  // 672:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_info_page_281, 0);
  // 669: TR:
  // 670:   TD: A "href" = "@(name.mangled).html" name
  // 671:   TD "&nbsp;as&nbsp;"
  // 672:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_277(void) {
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
  // 667: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__create_info_page_278;
}
static void cont__create_info_page_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 667: ... : (name)
  // 668:   $method string(name '/' function_name)
  // 669:   TR:
  // 670:     TD: A "href" = "@(name.mangled).html" name
  // 671:     TD "&nbsp;as&nbsp;"
  // 672:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_279, 1);
  // 667: for_each types_of(info): (name)
  // 668:   $method string(name '/' function_name)
  // 669:   TR:
  // 670:     TD: A "href" = "@(name.mangled).html" name
  // 671:     TD "&nbsp;as&nbsp;"
  // 672:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_274(void) {
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
  // 665: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9db99ab8b96e438c;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_276;
}
static void cont__create_info_page_276(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 666: ... :
  // 667:   for_each types_of(info): (name)
  // 668:     $method string(name '/' function_name)
  // 669:     TR:
  // 670:       TD: A "href" = "@(name.mangled).html" name
  // 671:       TD "&nbsp;as&nbsp;"
  // 672:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_277, 0);
  // 666: TABLE:
  // 667:   for_each types_of(info): (name)
  // 668:     $method string(name '/' function_name)
  // 669:     TR:
  // 670:       TD: A "href" = "@(name.mangled).html" name
  // 671:       TD "&nbsp;as&nbsp;"
  // 672:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_293(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 673: ... function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__create_info_page_294;
}
static void cont__create_info_page_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 673: ... :
  // 674:   $polymorphic_function_name function_name .behind. '/'
  // 675:   H2 "Implements"
  // 676:   A
  // 677:     "href" = "@(polymorphic_function_name.mangled).html"
  // 678:     polymorphic_function_name
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_295, 0);
  // 673: if function_name .contains. '/':
  // 674:   $polymorphic_function_name function_name .behind. '/'
  // 675:   H2 "Implements"
  // 676:   A
  // 677:     "href" = "@(polymorphic_function_name.mangled).html"
  // 678:     polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_302;
}
static void entry__create_info_page_295(void) {
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
  // 674: $polymorphic_function_name function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__create_info_page_296;
}
static void cont__create_info_page_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* polymorphic_function_name */, arguments->slots[0]);
  // 675: H2 "Implements"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__3f555b992b8ba7f2;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_298;
}
static void cont__create_info_page_298(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... polymorphic_function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* polymorphic_function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_299;
}
static void cont__create_info_page_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 677: ... "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_300;
}
static void cont__create_info_page_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 677: "href" = "@(polymorphic_function_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_301;
}
static void cont__create_info_page_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 676: A
  // 677:   "href" = "@(polymorphic_function_name.mangled).html"
  // 678:   polymorphic_function_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* polymorphic_function_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_302(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 679: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__create_info_page_303;
}
static void cont__create_info_page_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 679: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__create_info_page_304;
}
static void cont__create_info_page_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 679: ... :
  // 680:   H2 "Supported Polymorphic Functions"
  // 681:   TABLE:
  // 682:     for_each methods_of(info): (method_name _method_info)
  // 683:       TR:
  // 684:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:         TD "&nbsp;"
  // 686:         TD:
  // 687:           A
  // 688:             =
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__create_info_page_305, 0);
  // 679: if kind_of(info) == INLINE_C_TYPE:
  // 680:   H2 "Supported Polymorphic Functions"
  // 681:   TABLE:
  // 682:     for_each methods_of(info): (method_name _method_info)
  // 683:       TR:
  // 684:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:         TD "&nbsp;"
  // 686:         TD:
  // 687:           A
  // 688:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_323;
}
static void entry__create_info_page_318(void) {
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
  // 690: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_319;
}
static void cont__create_info_page_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 690: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_320;
}
static void cont__create_info_page_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 690: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__fa72f815cd16b93;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_321;
}
static void cont__create_info_page_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 688: =
  // 689:   "href"
  // 690:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_322;
}
static void cont__create_info_page_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 687: A
  // 688:   =
  // 689:     "href"
  // 690:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:   function_name
  // 692:   '/'
  // 693:   method_name
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
static void entry__create_info_page_311(void) {
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
  // 684: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_312, 0);
  // 684: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_316;
}
static void entry__create_info_page_312(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_313;
}
static void cont__create_info_page_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 684: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_314;
}
static void cont__create_info_page_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 684: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_315;
}
static void cont__create_info_page_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 684: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_316(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 685: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c1f52a3813ab2ec;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__create_info_page_317;
}
static void cont__create_info_page_317(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 686: ... :
  // 687:   A
  // 688:     =
  // 689:       "href"
  // 690:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:     function_name
  // 692:     '/'
  // 693:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_318, 0);
  // 686: TD:
  // 687:   A
  // 688:     =
  // 689:       "href"
  // 690:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:     function_name
  // 692:     '/'
  // 693:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_310(void) {
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
  // 683: ... :
  // 684:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:   TD "&nbsp;"
  // 686:   TD:
  // 687:     A
  // 688:       =
  // 689:         "href"
  // 690:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:       function_name
  // 692:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_info_page_311, 0);
  // 683: TR:
  // 684:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:   TD "&nbsp;"
  // 686:   TD:
  // 687:     A
  // 688:       =
  // 689:         "href"
  // 690:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:       function_name
  // 692:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_308(void) {
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
  // 682: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__create_info_page_309;
}
static void cont__create_info_page_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 682: ... : (method_name _method_info)
  // 683:   TR:
  // 684:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:     TD "&nbsp;"
  // 686:     TD:
  // 687:       A
  // 688:         =
  // 689:           "href"
  // 690:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__create_info_page_310, 2);
  // 682: for_each methods_of(info): (method_name _method_info)
  // 683:   TR:
  // 684:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:     TD "&nbsp;"
  // 686:     TD:
  // 687:       A
  // 688:         =
  // 689:           "href"
  // 690:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 691:         function_name
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
static void entry__create_info_page_305(void) {
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
  // 680: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ef7adaf915740b94;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_307;
}
static void cont__create_info_page_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 681: ... :
  // 682:   for_each methods_of(info): (method_name _method_info)
  // 683:     TR:
  // 684:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:       TD "&nbsp;"
  // 686:       TD:
  // 687:         A
  // 688:           =
  // 689:             "href"
  // 690:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_308, 0);
  // 681: TABLE:
  // 682:   for_each methods_of(info): (method_name _method_info)
  // 683:     TR:
  // 684:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 685:       TD "&nbsp;"
  // 686:       TD:
  // 687:         A
  // 688:           =
  // 689:             "href"
  // 690:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_323(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 696: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__create_info_page_324;
}
static void cont__create_info_page_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 695: $function_basename
  // 696:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__create_info_page_325;
}
static void cont__create_info_page_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* function_basename */, arguments->slots[0]);
  // 698: ... topic_list.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* topic_list */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__create_info_page_326;
}
static void cont__create_info_page_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 698: ... :
  // 699:   H2 "Topics"
  // 700:   TABLE:
  // 701:     for_each topic_list: (topic)
  // 702:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 703:       TR: TD: A "href" = filename topic
  frame->slots[14] /* temp__2 */ = create_closure(entry__create_info_page_327, 0);
  // 698: unless topic_list.is_empty:
  // 699:   H2 "Topics"
  // 700:   TABLE:
  // 701:     for_each topic_list: (topic)
  // 702:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 703:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__create_info_page_340;
}
static void entry__create_info_page_338(void) {
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
  // 703: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_339;
}
static void cont__create_info_page_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 703: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_337(void) {
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
  // 703: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_338, 0);
  // 703: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_331(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // topic: 0
  // filename: 1
  frame->slots[1] /* filename */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 702: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__create_info_page_332;
}
static void cont__create_info_page_332(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 702: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__578a5af303e9cbe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_334;
}
static void cont__create_info_page_334(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 702: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__create_info_page_335;
}
static void cont__create_info_page_335(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 702: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_336;
}
static void cont__create_info_page_336(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* filename */, arguments->slots[0]);
  // 703: ... : TD: A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__create_info_page_337, 0);
  // 703: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_330(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 701: for_each topic_list: (topic)
  // 702:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 703:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic_list */;
  arguments->slots[1] = func__create_info_page_331;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_327(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 699: H2 "Topics"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__781f541a81a2a2a4;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_329;
}
static void cont__create_info_page_329(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 700: ... :
  // 701:   for_each topic_list: (topic)
  // 702:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 703:     TR: TD: A "href" = filename topic
  frame->slots[1] /* temp__1 */ = create_closure(entry__create_info_page_330, 0);
  // 700: TABLE:
  // 701:   for_each topic_list: (topic)
  // 702:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 703:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_340(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 704: ... : (example)
  // 705:   $title key_of(example)
  // 706:   $text std::value_of(example)
  // 707:   H2 title
  // 708:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 709:     PRE
  // 710:       replace_all
  // 711:         text
  // 712:         =
  // 713:           sequence
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__create_info_page_341, 1);
  // 704: for_each examples: (example)
  // 705:   $title key_of(example)
  // 706:   $text std::value_of(example)
  // 707:   H2 title
  // 708:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 709:     PRE
  // 710:       replace_all
  // 711:         text
  // 712:         =
  // 713:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* examples */;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__create_info_page_360;
}
static void entry__create_info_page_349(void) {
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
  // 715: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__create_info_page_350;
}
static void cont__create_info_page_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 715: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_351;
}
static void cont__create_info_page_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 715: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__create_info_page_352;
}
static void cont__create_info_page_352(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__create_info_page_353;
}
static void cont__create_info_page_353(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 712: =
  // 713:   sequence
  // 714:     '@quot;'
  // 715:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 716:     '@quot;'
  // 717:   : (string_literal)
  // 718:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__create_info_page_354;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_355;
}
static void entry__create_info_page_354(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 718: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__create_info_page_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 719: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6582bef;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__2d7981f4e6582bef;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__create_info_page_357;
}
static void cont__create_info_page_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 719: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_358;
}
static void cont__create_info_page_358(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__create_info_page_359;
}
static void cont__create_info_page_359(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 709: PRE
  // 710:   replace_all
  // 711:     text
  // 712:     =
  // 713:       sequence
  // 714:         '@quot;'
  // 715:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 716:         '@quot;'
  // 717:       : (string_literal)
  // 718:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_341(void) {
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
  // 705: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__create_info_page_342;
}
static void cont__create_info_page_342(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 706: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__create_info_page_343;
}
static void cont__create_info_page_343(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 707: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__create_info_page_344;
}
static void cont__create_info_page_344(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__create_info_page_345;
}
static void cont__create_info_page_345(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 708: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__create_info_page_346;
}
static void cont__create_info_page_346(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 708: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__525aeb43ea502024;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_348;
}
static void cont__create_info_page_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 708: ... :
  // 709:   PRE
  // 710:     replace_all
  // 711:       text
  // 712:       =
  // 713:         sequence
  // 714:           '@quot;'
  // 715:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 716:           '@quot;'
  // 717:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__create_info_page_349, 0);
  // 708: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 709:   PRE
  // 710:     replace_all
  // 711:       text
  // 712:       =
  // 713:         sequence
  // 714:           '@quot;'
  // 715:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 716:           '@quot;'
  // 717:         : (string_literal)
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
static void cont__create_info_page_360(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 721: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__525aeb43ea502024;
  arguments->slots[1] = string__461f53438192a2a5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__create_info_page_362;
}
static void cont__create_info_page_362(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 722: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__create_info_page_363;
}
static void cont__create_info_page_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 722: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__create_info_page_364;
}
static void cont__create_info_page_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 722: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__ae5520fdce447e8;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  arguments->slots[2] = string__2d7981f4e6402bcf;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_367;
}
static void cont__create_info_page_367(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 720: DIV
  // 721:   "class" = "footer"
  // 722:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__create_info_page_15(void) {
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
  // 473: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__create_info_page_16;
}
static void cont__create_info_page_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 473: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__625ae843eaa89078;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_19;
}
static void cont__create_info_page_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 473: ... :
  // 474:   link_bar
  // 475:   if
  // 476:     function_name .contains. '/':
  // 477:       $type function_name .before. '/'
  // 478:       $method function_name .behind. '/'
  // 479:       H1
  // 480:         string
  // 481:           '['
  // 482:           type
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_info_page_20, 0);
  // 473: create_page "html/@(function_name.mangled).html":
  // 474:   link_bar
  // 475:   if
  // 476:     function_name .contains. '/':
  // 477:       $type function_name .before. '/'
  // 478:       $method function_name .behind. '/'
  // 479:       H1
  // 480:         string
  // 481:           '['
  // 482:           type
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
static void entry__create_info_page_1(void) {
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
  // 464: ... : (&reference)
  // 465:   resolve_reference &reference
  // 466:   if short_descriptions(reference).is_undefined:
  // 467:     Error "
  // 468:       The documentation for "@(function_name)"
  // 469:       (defined in "@(filename_of(info))")
  // 470:       references the undefined symbol "@(reference)@quot;!
  frame->slots[3] /* temp__1 */ = create_closure(entry__create_info_page_2, 1);
  // 464: $resolve_and_check_reference: (&reference)
  // 465:   resolve_reference &reference
  // 466:   if short_descriptions(reference).is_undefined:
  // 467:     Error "
  // 468:       The documentation for "@(function_name)"
  // 469:       (defined in "@(filename_of(info))")
  // 470:       references the undefined symbol "@(reference)@quot;!
  initialize_future(frame->slots[2] /* resolve_and_check_reference */, frame->slots[3] /* temp__1 */);
  // 472: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__create_info_page_14;
}
static void entry__create_info_page_2(void) {
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
  // 465: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__create_info_page_3;
}
static void cont__create_info_page_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 466: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__create_info_page_4;
}
static void cont__create_info_page_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 466: ... short_descriptions(reference).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__create_info_page_5;
}
static void cont__create_info_page_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 466: ... :
  // 467:   Error "
  // 468:     The documentation for "@(function_name)"
  // 469:     (defined in "@(filename_of(info))")
  // 470:     references the undefined symbol "@(reference)@quot;!
  frame->slots[5] /* temp__3 */ = create_closure(entry__create_info_page_6, 0);
  // 466: if short_descriptions(reference).is_undefined:
  // 467:   Error "
  // 468:     The documentation for "@(function_name)"
  // 469:     (defined in "@(filename_of(info))")
  // 470:     references the undefined symbol "@(reference)@quot;!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__create_info_page_13;
}
static void entry__create_info_page_6(void) {
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
  // 469: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__create_info_page_7;
}
static void cont__create_info_page_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 467: ... "
  // 468:   The documentation for "@(function_name)"
  // 469:   (defined in "@(filename_of(info))")
  // 470:   references the undefined symbol "@(reference)@quot;!
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__3da288aac4394c18;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__740195f292b901ee;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__e4c238e2b0c78735;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* reference */;
  arguments->slots[6] = string__fa730c15f216bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__create_info_page_12;
}
static void cont__create_info_page_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 467: Error "
  // 468:   The documentation for "@(function_name)"
  // 469:   (defined in "@(filename_of(info))")
  // 470:   references the undefined symbol "@(reference)@quot;!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__create_info_page_13(void) {
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
static void cont__create_info_page_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 472: ... :
  // 473:   create_page "html/@(function_name.mangled).html":
  // 474:     link_bar
  // 475:     if
  // 476:       function_name .contains. '/':
  // 477:         $type function_name .before. '/'
  // 478:         $method function_name .behind. '/'
  // 479:         H1
  // 480:           string
  // 481:             '['
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__create_info_page_15, 0);
  // 472: if function_name.is_defined:
  // 473:   create_page "html/@(function_name.mangled).html":
  // 474:     link_bar
  // 475:     if
  // 476:       function_name .contains. '/':
  // 477:         $type function_name .before. '/'
  // 478:         $method function_name .behind. '/'
  // 479:         H1
  // 480:           string
  // 481:             '['
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
static void entry__get_short_description_1(void) {
  allocate_initialized_frame_gc(2, 6);
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
  // 725: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__get_short_description_2;
}
static void cont__get_short_description_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* remark_lines */, arguments->slots[0]);
  // 726: $$short_description ""
  ((CELL *)frame->slots[3])->contents /* short_description */ = empty_string;
  // 727: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__get_short_description_3;
}
static void cont__get_short_description_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 727: ... :
  // 728:   do: (-> break)
  // 729:     for_each remark_lines: (line)
  // 730:       if line == "" && short_description != "" break
  // 731:       append &short_description line.trim
  // 732:   if do_print_warnings && length_of(short_description) > 80:
  // 733:     ewrite "
  // 734:       
  // 735:       The short description for "@(name)"
  // 736:       (defined in "@(filename_of(info))")
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__get_short_description_4, 0);
  // 727: unless remark_lines.is_empty:
  // 728:   do: (-> break)
  // 729:     for_each remark_lines: (line)
  // 730:       if line == "" && short_description != "" break
  // 731:       append &short_description line.trim
  // 732:   if do_print_warnings && length_of(short_description) > 80:
  // 733:     ewrite "
  // 734:       
  // 735:       The short description for "@(name)"
  // 736:       (defined in "@(filename_of(info))")
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__get_short_description_27;
}
static void entry__get_short_description_21(void) {
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
  // 736: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__get_short_description_22;
}
static void cont__get_short_description_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 733: ... "
  // 734:   
  // 735:   The short description for "@(name)"
  // 736:   (defined in "@(filename_of(info))")
  // 737:   is quite long:
  // 738:   @(short_description)
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__10bb152df59cfc0e;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__740195f292b901ee;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__8eef7e8eb4c1beaf;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* short_description */;
  arguments->slots[6] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__get_short_description_26;
}
static void cont__get_short_description_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 733: ewrite "
  // 734:   
  // 735:   The short description for "@(name)"
  // 736:   (defined in "@(filename_of(info))")
  // 737:   is quite long:
  // 738:   @(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__get_short_description_4(void) {
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
  // 728: ... : (-> break)
  // 729:   for_each remark_lines: (line)
  // 730:     if line == "" && short_description != "" break
  // 731:     append &short_description line.trim
  frame->slots[4] /* temp__1 */ = create_closure(entry__get_short_description_5, 0);
  // 728: do: (-> break)
  // 729:   for_each remark_lines: (line)
  // 730:     if line == "" && short_description != "" break
  // 731:     append &short_description line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__get_short_description_16;
}
static void entry__get_short_description_5(void) {
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
  // 729: ... : (line)
  // 730:   if line == "" && short_description != "" break
  // 731:   append &short_description line.trim
  frame->slots[3] /* temp__1 */ = create_closure(entry__get_short_description_6, 1);
  // 729: for_each remark_lines: (line)
  // 730:   if line == "" && short_description != "" break
  // 731:   append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__get_short_description_15;
}
static void entry__get_short_description_6(void) {
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
  // 730: ... line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__get_short_description_7;
}
static void cont__get_short_description_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 730: ... short_description != ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__get_short_description_8, 0);
  // 730: ... line == "" && short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__get_short_description_11;
}
static void entry__get_short_description_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 730: ... short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__get_short_description_9;
}
static void cont__get_short_description_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 730: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__get_short_description_10;
}
static void cont__get_short_description_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 730: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__get_short_description_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 730: if line == "" && short_description != "" break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__get_short_description_12;
}
static void cont__get_short_description_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 731: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__get_short_description_13;
}
static void cont__get_short_description_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 731: append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__get_short_description_14;
}
static void cont__get_short_description_14(void) {
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
static void cont__get_short_description_15(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__get_short_description_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 732: ... length_of(short_description) > 80
  frame->slots[5] /* temp__2 */ = create_closure(entry__get_short_description_17, 0);
  // 732: ... do_print_warnings && length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__get_short_description_20;
}
static void entry__get_short_description_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 732: ... length_of(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__get_short_description_18;
}
static void cont__get_short_description_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 732: ... length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__get_short_description_19;
}
static void cont__get_short_description_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 732: ... length_of(short_description) > 80
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__get_short_description_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 732: ... :
  // 733:   ewrite "
  // 734:     
  // 735:     The short description for "@(name)"
  // 736:     (defined in "@(filename_of(info))")
  // 737:     is quite long:
  // 738:     @(short_description)
  frame->slots[6] /* temp__3 */ = create_closure(entry__get_short_description_21, 0);
  // 732: if do_print_warnings && length_of(short_description) > 80:
  // 733:   ewrite "
  // 734:     
  // 735:     The short description for "@(name)"
  // 736:     (defined in "@(filename_of(info))")
  // 737:     is quite long:
  // 738:     @(short_description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__get_short_description_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 739: add_links &short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = var._add_links;
  func = myself->type;
  frame->cont = cont__get_short_description_28;
}
static void cont__get_short_description_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* short_description */ = arguments->slots[0];
  // 740: -> short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_exports_29(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // iname: 2
  // obj_name: 3
  frame->slots[2] = myself->closure.frame->slots[0]; /* iname */
  frame->slots[3] /* obj_name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 768: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_30;
}
static void cont__compiler__extract_exports_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 768: ... behind(iname '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_31;
}
static void cont__compiler__extract_exports_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 768: ... between(iname '/' '/' 2)
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = character__47;
  arguments->slots[3] = number__2;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_32;
}
static void cont__compiler__extract_exports_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 768: $obj_name string(behind(iname '/' -1) "::" between(iname '/' '/' 2))
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_33;
}
static void cont__compiler__extract_exports_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* obj_name */, arguments->slots[0]);
  // 769: writeln obj_name '/' method_name
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* obj_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_7(void) {
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
  // 746: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_8;
}
static void cont__compiler__extract_exports_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 747: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_9;
}
static void cont__compiler__extract_exports_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 747: ... :
  // 748:   write name ' '
  // 749:   case kind_of(info)
  // 750:     POLYMORPHIC_ATTRIBUTE:
  // 751:       write "(!)"
  // 752:     POLYMORPHIC_FUNCTION:
  // 753:       write "()"
  // 754:     OTHER:
  // 755:       case variable_kind_of(info)
  // 756:         STATIC_SINGLE:
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_exports_10, 0);
  // 747: if name.is_defined:
  // 748:   write name ' '
  // 749:   case kind_of(info)
  // 750:     POLYMORPHIC_ATTRIBUTE:
  // 751:       write "(!)"
  // 752:     POLYMORPHIC_FUNCTION:
  // 753:       write "()"
  // 754:     OTHER:
  // 755:       case variable_kind_of(info)
  // 756:         STATIC_SINGLE:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_27;
}
static void entry__compiler__extract_exports_10(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 748: write name ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__32;
  result_count = 0;
  myself = get__write();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_11;
}
static void cont__compiler__extract_exports_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 749: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_12;
}
static void cont__compiler__extract_exports_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 754: ... :
  // 755:   case variable_kind_of(info)
  // 756:     STATIC_SINGLE:
  // 757:       write '$'
  // 758:     STATIC_MULTI:
  // 759:       write "$$"
  // 760:     DYNAMIC_SINGLE:
  // 761:       write '%'
  // 762:     DYNAMIC_MULTI:
  // 763:       write "%%"
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__extract_exports_13, 0);
  // 749: case kind_of(info)
  // 750:   POLYMORPHIC_ATTRIBUTE:
  // 751:     write "(!)"
  // 752:   POLYMORPHIC_FUNCTION:
  // 753:     write "()"
  // 754:   OTHER:
  // 755:     case variable_kind_of(info)
  // 756:       STATIC_SINGLE:
  // 757:         write '$'
  // 758:       STATIC_MULTI:
  // ...
  argument_count = 8;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[2] = func__compiler__extract_exports_21;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = func__compiler__extract_exports_23;
  arguments->slots[5] = var._OTHER;
  arguments->slots[6] = frame->slots[3] /* temp__2 */;
  arguments->slots[7] = func__compiler__extract_exports_25;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_26;
}
static void entry__compiler__extract_exports_15(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 757: write '$'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__36;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 759: write "$$"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6282be1;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_18(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 761: write '%'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__37;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_19(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 763: write "%%"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6202be0;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 755: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_14;
}
static void cont__compiler__extract_exports_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 755: case variable_kind_of(info)
  // 756:   STATIC_SINGLE:
  // 757:     write '$'
  // 758:   STATIC_MULTI:
  // 759:     write "$$"
  // 760:   DYNAMIC_SINGLE:
  // 761:     write '%'
  // 762:   DYNAMIC_MULTI:
  // 763:     write "%%"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  arguments->slots[2] = func__compiler__extract_exports_15;
  arguments->slots[3] = get__STATIC_MULTI();
  arguments->slots[4] = func__compiler__extract_exports_16;
  arguments->slots[5] = get__DYNAMIC_SINGLE();
  arguments->slots[6] = func__compiler__extract_exports_18;
  arguments->slots[7] = get__DYNAMIC_MULTI();
  arguments->slots[8] = func__compiler__extract_exports_19;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_21(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 751: write "(!)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__fa732415f216be5;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 753: write "()"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e6482bec;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_25(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: write '$'
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__36;
  result_count = frame->caller_result_count;
  myself = get__write();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_exports_26(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 766: writeln
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__writeln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_exports_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 767: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_28;
}
static void cont__compiler__extract_exports_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 767: ... : (method_name _method_info)
  // 768:   $obj_name string(behind(iname '/' -1) "::" between(iname '/' '/' 2))
  // 769:   writeln obj_name '/' method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_exports_29, 2);
  // 767: for_each methods_of(info): (method_name _method_info)
  // 768:   $obj_name string(behind(iname '/' -1) "::" between(iname '/' '/' 2))
  // 769:   writeln obj_name '/' method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_exports_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // paths: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 743: ... paths(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* paths */;
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_2;
}
static void cont__compiler__extract_exports_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 743: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_3;
}
static void cont__compiler__extract_exports_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 743: !path_prefix truncate_behind(paths(1) '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_4;
}
static void cont__compiler__extract_exports_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 744: for_each paths: (path) extract_documentation_from_directory path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = func__compiler__extract_exports_5;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_exports_6;
}
static void entry__compiler__extract_exports_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 744: ... extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_exports_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: for_each definitions: (iname info)
  // 746:   $name name_of(info)
  // 747:   if name.is_defined:
  // 748:     write name ' '
  // 749:     case kind_of(info)
  // 750:       POLYMORPHIC_ATTRIBUTE:
  // 751:         write "(!)"
  // 752:       POLYMORPHIC_FUNCTION:
  // 753:         write "()"
  // 754:       OTHER:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__compiler__extract_exports_7;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_247(void) {
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
  // 913: $$total_functions 0
  ((CELL *)frame->slots[0])->contents /* total_functions */ = number__0;
  // 914: $$total_polymorphic_functions 0
  ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */ = number__0;
  // 915: $$total_polymorphic_attributes 0
  ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */ = number__0;
  // 916: $$total_methods 0
  ((CELL *)frame->slots[3])->contents /* total_methods */ = number__0;
  // 917: $$total_inline_c_methods 0
  ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */ = number__0;
  // 918: $$total_inline_c_types 0
  ((CELL *)frame->slots[5])->contents /* total_inline_c_types */ = number__0;
  // 919: $$total_inline_c_objects 0
  ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */ = number__0;
  // 920: $$total_attributes 0
  ((CELL *)frame->slots[7])->contents /* total_attributes */ = number__0;
  // 921: $$total_inline_c_functions 0
  ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */ = number__0;
  // 922: $$total_unique_items 0
  ((CELL *)frame->slots[9])->contents /* total_unique_items */ = number__0;
  // 923: $$total_constants 0
  ((CELL *)frame->slots[10])->contents /* total_constants */ = number__0;
  // 924: $$other 0
  ((CELL *)frame->slots[11])->contents /* other */ = number__0;
  // 925: ... : (_iname info)
  // 926:   case kind_of(info)
  // 927:     FUNCTION:
  // 928:       inc &total_functions
  // 929:     POLYMORPHIC_FUNCTION:
  // 930:       inc &total_polymorphic_functions
  // 931:     POLYMORPHIC_ATTRIBUTE:
  // 932:       inc &total_polymorphic_attributes
  // 933:     INLINE_C_FUNCTION:
  // 934:       inc &total_inline_c_functions
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_248, 2);
  // 925: for_each definitions: (_iname info)
  // 926:   case kind_of(info)
  // 927:     FUNCTION:
  // 928:       inc &total_functions
  // 929:     POLYMORPHIC_FUNCTION:
  // 930:       inc &total_polymorphic_functions
  // 931:     POLYMORPHIC_ATTRIBUTE:
  // 932:       inc &total_polymorphic_attributes
  // 933:     INLINE_C_FUNCTION:
  // 934:       inc &total_inline_c_functions
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_280;
}
static void entry__compiler__extract_documentation_274(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_methods: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 949: inc &total_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_275;
}
static void cont__compiler__extract_documentation_275(void) {
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
static void entry__compiler__extract_documentation_276(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_methods: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_inline_c_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 951: inc &total_inline_c_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_277;
}
static void cont__compiler__extract_documentation_277(void) {
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
static void entry__compiler__extract_documentation_278(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 953: inc &total_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_279;
}
static void cont__compiler__extract_documentation_279(void) {
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
static void entry__compiler__extract_documentation_272(void) {
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
  // 947: ... kind_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_273;
}
static void cont__compiler__extract_documentation_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 948: ... :
  // 949:   inc &total_methods
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_274, 0);
  // 950: ... :
  // 951:   inc &total_inline_c_methods
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_276, 0);
  // 952: :
  // 953:   inc &total_attributes
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_278, 0);
  // 947: case kind_of(method_info)
  // 948:   FUNCTION:
  // 949:     inc &total_methods
  // 950:   INLINE_C_FUNCTION:
  // 951:     inc &total_inline_c_methods
  // 952:   :
  // 953:     inc &total_attributes
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
static void entry__compiler__extract_documentation_270(void) {
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
  // 946: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_271;
}
static void cont__compiler__extract_documentation_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 946: ... : (_method_name method_info)
  // 947:   case kind_of(method_info)
  // 948:     FUNCTION:
  // 949:       inc &total_methods
  // 950:     INLINE_C_FUNCTION:
  // 951:       inc &total_inline_c_methods
  // 952:     :
  // 953:       inc &total_attributes
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_272, 2);
  // 946: for_each methods_of(info): (_method_name method_info)
  // 947:   case kind_of(method_info)
  // 948:     FUNCTION:
  // 949:       inc &total_methods
  // 950:     INLINE_C_FUNCTION:
  // 951:       inc &total_inline_c_methods
  // 952:     :
  // 953:       inc &total_attributes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_248(void) {
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
  // 926: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_249;
}
static void cont__compiler__extract_documentation_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 927: ... :
  // 928:   inc &total_functions
  frame->slots[15] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_250, 0);
  // 929: ... :
  // 930:   inc &total_polymorphic_functions
  frame->slots[16] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_252, 0);
  // 931: ... :
  // 932:   inc &total_polymorphic_attributes
  frame->slots[17] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_254, 0);
  // 933: ... :
  // 934:   inc &total_inline_c_functions
  frame->slots[18] /* temp__5 */ = create_closure(entry__compiler__extract_documentation_256, 0);
  // 935: ... :
  // 936:   inc &total_inline_c_types
  frame->slots[19] /* temp__6 */ = create_closure(entry__compiler__extract_documentation_258, 0);
  // 937: ... :
  // 938:   inc &total_inline_c_objects
  frame->slots[20] /* temp__7 */ = create_closure(entry__compiler__extract_documentation_260, 0);
  // 939: ... :
  // 940:   inc &total_unique_items
  frame->slots[21] /* temp__8 */ = create_closure(entry__compiler__extract_documentation_262, 0);
  // 941: ... :
  // 942:   inc &total_constants
  frame->slots[22] /* temp__9 */ = create_closure(entry__compiler__extract_documentation_264, 0);
  // 943: :
  // 944:   inc &other
  frame->slots[23] /* temp__10 */ = create_closure(entry__compiler__extract_documentation_266, 0);
  // 926: case kind_of(info)
  // 927:   FUNCTION:
  // 928:     inc &total_functions
  // 929:   POLYMORPHIC_FUNCTION:
  // 930:     inc &total_polymorphic_functions
  // 931:   POLYMORPHIC_ATTRIBUTE:
  // 932:     inc &total_polymorphic_attributes
  // 933:   INLINE_C_FUNCTION:
  // 934:     inc &total_inline_c_functions
  // 935:   INLINE_C_TYPE:
  // ...
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
  frame->cont = cont__compiler__extract_documentation_268;
}
static void entry__compiler__extract_documentation_250(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_functions: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 928: inc &total_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_251;
}
static void cont__compiler__extract_documentation_251(void) {
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
static void entry__compiler__extract_documentation_252(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_functions: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_polymorphic_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 930: inc &total_polymorphic_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_253;
}
static void cont__compiler__extract_documentation_253(void) {
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
static void entry__compiler__extract_documentation_254(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_polymorphic_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 932: inc &total_polymorphic_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_255;
}
static void cont__compiler__extract_documentation_255(void) {
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
static void entry__compiler__extract_documentation_256(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_functions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* total_inline_c_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 934: inc &total_inline_c_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_257;
}
static void cont__compiler__extract_documentation_257(void) {
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
static void entry__compiler__extract_documentation_258(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_types: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* total_inline_c_types */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 936: inc &total_inline_c_types
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_259;
}
static void cont__compiler__extract_documentation_259(void) {
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
static void entry__compiler__extract_documentation_260(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_objects: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* total_inline_c_objects */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 938: inc &total_inline_c_objects
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_261;
}
static void cont__compiler__extract_documentation_261(void) {
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
static void entry__compiler__extract_documentation_262(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_unique_items: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* total_unique_items */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 940: inc &total_unique_items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_263;
}
static void cont__compiler__extract_documentation_263(void) {
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
static void entry__compiler__extract_documentation_264(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_constants: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* total_constants */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 942: inc &total_constants
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_constants */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_265;
}
static void cont__compiler__extract_documentation_265(void) {
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
static void entry__compiler__extract_documentation_266(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // other: 0
  frame->slots[0] = myself->closure.frame->slots[10]; /* other */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 944: inc &other
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* other */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_267;
}
static void cont__compiler__extract_documentation_267(void) {
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
static void cont__compiler__extract_documentation_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 945: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_269;
}
static void cont__compiler__extract_documentation_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 945: ... :
  // 946:   for_each methods_of(info): (_method_name method_info)
  // 947:     case kind_of(method_info)
  // 948:       FUNCTION:
  // 949:         inc &total_methods
  // 950:       INLINE_C_FUNCTION:
  // 951:         inc &total_inline_c_methods
  // 952:       :
  // 953:         inc &total_attributes
  frame->slots[15] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_270, 0);
  // 945: case kind_of(info) INLINE_C_TYPE:
  // 946:   for_each methods_of(info): (_method_name method_info)
  // 947:     case kind_of(method_info)
  // 948:       FUNCTION:
  // 949:         inc &total_methods
  // 950:       INLINE_C_FUNCTION:
  // 951:         inc &total_inline_c_methods
  // 952:       :
  // 953:         inc &total_attributes
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
static void cont__compiler__extract_documentation_280(void) {
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
  frame->cont = cont__compiler__extract_documentation_281;
}
static void cont__compiler__extract_documentation_281(void) {
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
  frame->cont = cont__compiler__extract_documentation_282;
}
static void cont__compiler__extract_documentation_282(void) {
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
  frame->cont = cont__compiler__extract_documentation_283;
}
static void cont__compiler__extract_documentation_283(void) {
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
  frame->cont = cont__compiler__extract_documentation_284;
}
static void cont__compiler__extract_documentation_284(void) {
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
  frame->cont = cont__compiler__extract_documentation_285;
}
static void cont__compiler__extract_documentation_285(void) {
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
  frame->cont = cont__compiler__extract_documentation_286;
}
static void cont__compiler__extract_documentation_286(void) {
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
  frame->cont = cont__compiler__extract_documentation_287;
}
static void cont__compiler__extract_documentation_287(void) {
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
  frame->cont = cont__compiler__extract_documentation_288;
}
static void cont__compiler__extract_documentation_288(void) {
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
  frame->cont = cont__compiler__extract_documentation_289;
}
static void cont__compiler__extract_documentation_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 955: $total_definitions
  // 956:   +
  // 957:     total_functions
  // 958:     total_polymorphic_functions
  // 959:     total_polymorphic_attributes
  // 960:     total_methods
  // 961:     total_inline_c_methods
  // 962:     total_inline_c_types
  // 963:     total_inline_c_objects
  // 964:     total_attributes
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_290;
}
static void cont__compiler__extract_documentation_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* total_definitions */, arguments->slots[0]);
  // 970: ... pad_left(total_definitions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* total_definitions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_291;
}
static void cont__compiler__extract_documentation_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 972: ... pad_left(total_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_292;
}
static void cont__compiler__extract_documentation_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 973: ... pad_left(total_polymorphic_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_293;
}
static void cont__compiler__extract_documentation_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 974: ... pad_left(total_polymorphic_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_294;
}
static void cont__compiler__extract_documentation_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  // 975: ... pad_left(total_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_295;
}
static void cont__compiler__extract_documentation_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  // 976: ... pad_left(total_inline_c_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_296;
}
static void cont__compiler__extract_documentation_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  // 977: ... pad_left(total_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_297;
}
static void cont__compiler__extract_documentation_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  // 978: ... pad_left(total_inline_c_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_298;
}
static void cont__compiler__extract_documentation_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  // 979: ... pad_left(total_inline_c_types 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_299;
}
static void cont__compiler__extract_documentation_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__10 */ = arguments->slots[0];
  // 980: ... pad_left(total_inline_c_objects 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_300;
}
static void cont__compiler__extract_documentation_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__11 */ = arguments->slots[0];
  // 981: ... pad_left(total_unique_items 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_301;
}
static void cont__compiler__extract_documentation_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__12 */ = arguments->slots[0];
  // 982: ... pad_left(total_constants 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_302;
}
static void cont__compiler__extract_documentation_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__13 */ = arguments->slots[0];
  // 983: ... pad_left(other 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* other */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_303;
}
static void cont__compiler__extract_documentation_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__14 */ = arguments->slots[0];
  // 985: ... pad_left(missing_documentation_count 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._missing_documentation_count;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_304;
}
static void cont__compiler__extract_documentation_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__15 */ = arguments->slots[0];
  // 969: ... "
  // 970:   total definitions:     @(pad_left(total_definitions 5))
  // 971:   
  // 972:   functions:             @(pad_left(total_functions 5))
  // 973:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 974:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 975:   method definitions:    @(pad_left(total_methods 5))
  // 976:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 977:   attribute definitions: @(pad_left(total_attributes 5))
  // 978:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 29;
  arguments = node_p;
  arguments->slots[0] = string__f5d1f6a5c0048246;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = string__c40b62b5c2e5a063;
  arguments->slots[3] = frame->slots[15] /* temp__3 */;
  arguments->slots[4] = string__3441ee1e4106d8f4;
  arguments->slots[5] = frame->slots[16] /* temp__4 */;
  arguments->slots[6] = string__c035e39bd94f7acf;
  arguments->slots[7] = frame->slots[17] /* temp__5 */;
  arguments->slots[8] = string__effbd005c6cabd2e;
  arguments->slots[9] = frame->slots[18] /* temp__6 */;
  arguments->slots[10] = string__2b2b0af8abbb8aa7;
  arguments->slots[11] = frame->slots[19] /* temp__7 */;
  arguments->slots[12] = string__90c6182ac0816ddd;
  arguments->slots[13] = frame->slots[20] /* temp__8 */;
  arguments->slots[14] = string__effbd3d1268e2925;
  arguments->slots[15] = frame->slots[21] /* temp__9 */;
  arguments->slots[16] = string__67c3eb38f5b380c4;
  arguments->slots[17] = frame->slots[22] /* temp__10 */;
  arguments->slots[18] = string__6a2b6a88bb878aa4;
  arguments->slots[19] = frame->slots[23] /* temp__11 */;
  arguments->slots[20] = string__ff41420da974d0d3;
  arguments->slots[21] = frame->slots[24] /* temp__12 */;
  arguments->slots[22] = string__e400cbf53b9db9ae;
  arguments->slots[23] = frame->slots[25] /* temp__13 */;
  arguments->slots[24] = string__4dc16ebc881e822d;
  arguments->slots[25] = frame->slots[26] /* temp__14 */;
  arguments->slots[26] = string__e1857d0a4bd566c9;
  arguments->slots[27] = frame->slots[27] /* temp__15 */;
  arguments->slots[28] = string__578a5af303e9ceb;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_319;
}
static void cont__compiler__extract_documentation_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 969: ewrite "
  // 970:   total definitions:     @(pad_left(total_definitions 5))
  // 971:   
  // 972:   functions:             @(pad_left(total_functions 5))
  // 973:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 974:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 975:   method definitions:    @(pad_left(total_methods 5))
  // 976:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 977:   attribute definitions: @(pad_left(total_attributes 5))
  // 978:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // paths: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 772: ... paths(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* paths */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_2;
}
static void cont__compiler__extract_documentation_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 772: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_3;
}
static void cont__compiler__extract_documentation_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 772: !path_prefix truncate_behind(paths(1) '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_4;
}
static void cont__compiler__extract_documentation_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 773: for_each paths: (path) extract_documentation_from_directory path
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paths */;
  arguments->slots[1] = func__compiler__extract_documentation_5;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_6;
}
static void entry__compiler__extract_documentation_5(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 773: ... extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 774: for_each definitions: (iname info)
  // 775:   $name name_of(info)
  // 776:   if name.is_undefined:
  // 777:     Error "
  // 778:       Incomplete definition encountered:
  // 779:       
  // 780:       There is no name for the definition of "@(iname)@quot;!
  // 781:   !short_descriptions(name) get_short_description(name info)
  // 782:   if kind_of(info) == INLINE_C_TYPE:
  // 783:     $base base_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__compiler__extract_documentation_7;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_45;
}
static void entry__compiler__extract_documentation_18(void) {
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
  // 783: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_19;
}
static void cont__compiler__extract_documentation_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base */, arguments->slots[0]);
  // 784: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_20;
}
static void cont__compiler__extract_documentation_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 784: ... : add_derived_type base iname
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_21, 0);
  // 784: if base.is_defined: add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_22;
}
static void entry__compiler__extract_documentation_21(void) {
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
  // 784: ... add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* iname */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 785: $$methods empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* methods */ = get__empty_key_order_table();
  // 786: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_23;
}
static void cont__compiler__extract_documentation_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 786: ... : ($method_name method_info)
  // 787:   unless method_name .contains. "::":
  // 788:     !method_name attribute_of(method_info).resolved_name
  // 789:   $sd_name string(name "/" method_name)
  // 790:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 791:   $oname ordered_name(method_name .before. "::" method_name .behind. "::")
  // 792:   !definitions(oname).types_of(name) true
  // 793:   !methods(method_name) method_info
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_24, 2);
  // 786: for_each methods_of(info): ($method_name method_info)
  // 787:   unless method_name .contains. "::":
  // 788:     !method_name attribute_of(method_info).resolved_name
  // 789:   $sd_name string(name "/" method_name)
  // 790:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 791:   $oname ordered_name(method_name .before. "::" method_name .behind. "::")
  // 792:   !definitions(oname).types_of(name) true
  // 793:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_42;
}
static void entry__compiler__extract_documentation_24(void) {
  allocate_initialized_frame_gc(4, 8);
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
  // 787: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_25;
}
static void cont__compiler__extract_documentation_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 787: ... :
  // 788:   !method_name attribute_of(method_info).resolved_name
  frame->slots[7] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_26, 0);
  // 787: unless method_name .contains. "::":
  // 788:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_29;
}
static void entry__compiler__extract_documentation_26(void) {
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
  // 788: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_27;
}
static void cont__compiler__extract_documentation_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 788: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_28;
}
static void cont__compiler__extract_documentation_28(void) {
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
static void cont__compiler__extract_documentation_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 789: $sd_name string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__578a5af303e9cce;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_31;
}
static void cont__compiler__extract_documentation_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* sd_name */, arguments->slots[0]);
  // 790: !short_descriptions(sd_name) get_short_description(sd_name method_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_32;
}
static void cont__compiler__extract_documentation_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 790: !short_descriptions(sd_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_33;
}
static void cont__compiler__extract_documentation_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 791: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_34;
}
static void cont__compiler__extract_documentation_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 791: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_35;
}
static void cont__compiler__extract_documentation_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 791: $oname ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_36;
}
static void cont__compiler__extract_documentation_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* oname */, arguments->slots[0]);
  // 792: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_37;
}
static void cont__compiler__extract_documentation_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 792: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_38;
}
static void cont__compiler__extract_documentation_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 792: !definitions(oname).types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_39;
}
static void cont__compiler__extract_documentation_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 792: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[7] /* temp__2 */);
    frame->slots[6] /* temp__1 */ = temp;

  }
  // 792: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_40;
}
static void cont__compiler__extract_documentation_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 793: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_41;
}
static void cont__compiler__extract_documentation_41(void) {
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
static void cont__compiler__extract_documentation_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_43;
}
static void cont__compiler__extract_documentation_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 794: !definitions(iname).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, ((CELL *)frame->slots[4])->contents /* methods */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 794: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_44;
}
static void cont__compiler__extract_documentation_44(void) {
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
static void entry__compiler__extract_documentation_7(void) {
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
  // 775: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_8;
}
static void cont__compiler__extract_documentation_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 776: ... name.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_9;
}
static void cont__compiler__extract_documentation_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 776: ... :
  // 777:   Error "
  // 778:     Incomplete definition encountered:
  // 779:     
  // 780:     There is no name for the definition of "@(iname)@quot;!
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_10, 0);
  // 776: if name.is_undefined:
  // 777:   Error "
  // 778:     Incomplete definition encountered:
  // 779:     
  // 780:     There is no name for the definition of "@(iname)@quot;!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_13;
}
static void entry__compiler__extract_documentation_10(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // iname: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* iname */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 777: ... "
  // 778:   Incomplete definition encountered:
  // 779:   
  // 780:   There is no name for the definition of "@(iname)@quot;!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8f47f24352a780c2;
  arguments->slots[1] = frame->slots[0] /* iname */;
  arguments->slots[2] = string__fa730c15f216bc6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_12;
}
static void cont__compiler__extract_documentation_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 777: Error "
  // 778:   Incomplete definition encountered:
  // 779:   
  // 780:   There is no name for the definition of "@(iname)@quot;!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 781: !short_descriptions(name) get_short_description(name info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_14;
}
static void cont__compiler__extract_documentation_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 781: !short_descriptions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_15;
}
static void cont__compiler__extract_documentation_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 782: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_16;
}
static void cont__compiler__extract_documentation_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 782: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_17;
}
static void cont__compiler__extract_documentation_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 782: ... :
  // 783:   $base base_of(info)
  // 784:   if base.is_defined: add_derived_type base iname
  // 785:   $$methods empty_key_order_table
  // 786:   for_each methods_of(info): ($method_name method_info)
  // 787:     unless method_name .contains. "::":
  // 788:       !method_name attribute_of(method_info).resolved_name
  // 789:     $sd_name string(name "/" method_name)
  // 790:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 791:     $oname ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_18, 0);
  // 782: if kind_of(info) == INLINE_C_TYPE:
  // 783:   $base base_of(info)
  // 784:   if base.is_defined: add_derived_type base iname
  // 785:   $$methods empty_key_order_table
  // 786:   for_each methods_of(info): ($method_name method_info)
  // 787:     unless method_name .contains. "::":
  // 788:       !method_name attribute_of(method_info).resolved_name
  // 789:     $sd_name string(name "/" method_name)
  // 790:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 791:     $oname ordered_name(method_name .before. "::" method_name .behind. "::")
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
static void cont__compiler__extract_documentation_45(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 795: create_page "html/type_index.html":
  // 796:   $print_type_info:
  // 797:     (
  // 798:       info
  // 799:       indent = 0
  // 800:     )
  // 801:     TR:
  // 802:       $qname name_of(info)
  // 803:       $remark_lines remark_lines_of(info)
  // 804:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__5042403361ea61f3;
  arguments->slots[1] = func__compiler__extract_documentation_47;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_85;
}
static void entry__compiler__extract_documentation_84(void) {
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
  // 818: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_77(void) {
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
  // 817: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_78;
}
static void cont__compiler__extract_documentation_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 817: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_79;
}
static void cont__compiler__extract_documentation_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 817: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_80, 0);
  // 817: ... kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_83;
}
static void entry__compiler__extract_documentation_80(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 817: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_81;
}
static void cont__compiler__extract_documentation_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 817: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_82;
}
static void cont__compiler__extract_documentation_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 817: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__extract_documentation_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 817: ... :
  // 818:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__extract_documentation_84, 0);
  // 817: if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 818:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_76(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 816: ... : (_base info)
  // 817:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 818:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_77, 2);
  // 816: for_each definitions: (_base info)
  // 817:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 818:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_47(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 796: ... :
  // 797:   (
  // 798:     info
  // 799:     indent = 0
  // 800:   )
  // 801:   TR:
  // 802:     $qname name_of(info)
  // 803:     $remark_lines remark_lines_of(info)
  // 804:     if qname.is_defined:
  // 805:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_48, -1);
  // 796: $print_type_info:
  // 797:   (
  // 798:     info
  // 799:     indent = 0
  // 800:   )
  // 801:   TR:
  // 802:     $qname name_of(info)
  // 803:     $remark_lines remark_lines_of(info)
  // 804:     if qname.is_defined:
  // 805:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 813: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_74;
}
static void entry__compiler__extract_documentation_71(void) {
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
  // 811: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_72;
}
static void cont__compiler__extract_documentation_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 811: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_73;
}
static void cont__compiler__extract_documentation_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 811: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_49(void) {
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
  // 802: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_50;
}
static void cont__compiler__extract_documentation_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 803: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_51;
}
static void cont__compiler__extract_documentation_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 804: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_52;
}
static void cont__compiler__extract_documentation_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 804: ... :
  // 805:   TD:
  // 806:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_53, 0);
  // 804: if qname.is_defined:
  // 805:   TD:
  // 806:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_60;
}
static void entry__compiler__extract_documentation_54(void) {
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
  // 806: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__57442216b13fc418;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_55;
}
static void cont__compiler__extract_documentation_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 806: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_56;
}
static void cont__compiler__extract_documentation_56(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 807: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_57;
}
static void cont__compiler__extract_documentation_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 807: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_58;
}
static void cont__compiler__extract_documentation_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 807: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_59;
}
static void cont__compiler__extract_documentation_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 807: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_53(void) {
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
  // 805: ... :
  // 806:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_54, 0);
  // 805: TD:
  // 806:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_60(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 808: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_61;
}
static void cont__compiler__extract_documentation_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 808: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_62, 0);
  // 808: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_65;
}
static void entry__compiler__extract_documentation_62(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 808: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_63;
}
static void cont__compiler__extract_documentation_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 808: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_64;
}
static void cont__compiler__extract_documentation_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 808: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__extract_documentation_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 808: ... :
  // 809:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_66, 0);
  // 808: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 809:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_69;
}
static void entry__compiler__extract_documentation_66(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 809: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_67;
}
static void cont__compiler__extract_documentation_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 809: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_68;
}
static void cont__compiler__extract_documentation_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 809: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 810: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_70;
}
static void cont__compiler__extract_documentation_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 810: ... : (name)
  // 811:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_71, 1);
  // 810: for_each derived_types_of(info): (name)
  // 811:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_48(void) {
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
  // 801: ... :
  // 802:   $qname name_of(info)
  // 803:   $remark_lines remark_lines_of(info)
  // 804:   if qname.is_defined:
  // 805:     TD:
  // 806:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:       A "href" = "@(qname.mangled).html" qname
  // 808:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 809:     TD remark_lines.to_paragraphs(1)
  // 810:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_49, 0);
  // 801: TR:
  // 802:   $qname name_of(info)
  // 803:   $remark_lines remark_lines_of(info)
  // 804:   if qname.is_defined:
  // 805:     TD:
  // 806:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 807:       A "href" = "@(qname.mangled).html" qname
  // 808:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 809:     TD remark_lines.to_paragraphs(1)
  // 810:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_74(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2971b13bbf01e7f9;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_75;
}
static void cont__compiler__extract_documentation_75(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 815: ... :
  // 816:   for_each definitions: (_base info)
  // 817:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 818:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_76, 0);
  // 815: TABLE:
  // 816:   for_each definitions: (_base info)
  // 817:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 818:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 819: create_page "html/symbol_index.html":
  // 820:   link_bar
  // 821:   H1 "id" = "index" "Symbol Index"
  // 822:   from_to
  // 823:     'a'
  // 824:     'z': (letter)
  // 825:       A "href" = "#@(letter)" letter.to_upper_case
  // 826:     :
  // 827:       TEXT " "
  // 828:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__323311dc18f7db38;
  arguments->slots[1] = func__compiler__extract_documentation_87;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_180;
}
static void entry__compiler__extract_documentation_166(void) {
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
  // 876: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__525ae943eaf00039;
  arguments->slots[1] = string__585aeac3ea893023;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_169;
}
static void cont__compiler__extract_documentation_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 876: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_170;
}
static void cont__compiler__extract_documentation_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 876: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_171;
}
static void cont__compiler__extract_documentation_171(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 877: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_172, 0);
  // 877: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_177;
}
static void entry__compiler__extract_documentation_172(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 877: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_173;
}
static void cont__compiler__extract_documentation_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 877: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_174;
}
static void cont__compiler__extract_documentation_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 877: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_175;
}
static void cont__compiler__extract_documentation_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 877: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__2d7981f4e6d82bff;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_176;
}
static void cont__compiler__extract_documentation_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 877: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_177(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 878: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__525aeb43ea502024;
  arguments->slots[1] = string__421f5609812a02bc;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_179;
}
static void cont__compiler__extract_documentation_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 878: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_165(void) {
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
  // 875: ... :
  // 876:   TD "align" = "right" name .until. "::"
  // 877:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 878:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_166, 0);
  // 875: TR:
  // 876:   TD "align" = "right" name .until. "::"
  // 877:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 878:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_103(void) {
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
  // 832: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_104;
}
static void cont__compiler__extract_documentation_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 832: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_105;
}
static void cont__compiler__extract_documentation_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 832: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_106;
}
static void cont__compiler__extract_documentation_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 832: ... :
  // 833:   !letter iname(1)
  // 834:   TR:
  // 835:     TD "colspan" = 3:
  // 836:       H2 "id" = letter:
  // 837:         TEXT letter.to_upper_case
  // 838:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_107, 0);
  // 832: if iname(1) != letter:
  // 833:   !letter iname(1)
  // 834:   TR:
  // 835:     TD "colspan" = 3:
  // 836:       H2 "id" = letter:
  // 837:         TEXT letter.to_upper_case
  // 838:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_120;
}
static void entry__compiler__extract_documentation_114(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 837: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_115;
}
static void cont__compiler__extract_documentation_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 837: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_116;
}
static void cont__compiler__extract_documentation_116(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 838: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__441f57610192c2af;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_118;
}
static void cont__compiler__extract_documentation_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 838: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__c50d368eedcf3ba9;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_112(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 836: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4402ba1;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_113;
}
static void cont__compiler__extract_documentation_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 836: ... :
  // 837:   TEXT letter.to_upper_case
  // 838:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_114, 0);
  // 836: H2 "id" = letter:
  // 837:   TEXT letter.to_upper_case
  // 838:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_109(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 835: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__940809d515b20094;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_111;
}
static void cont__compiler__extract_documentation_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 835: ... :
  // 836:   H2 "id" = letter:
  // 837:     TEXT letter.to_upper_case
  // 838:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_112, 0);
  // 835: TD "colspan" = 3:
  // 836:   H2 "id" = letter:
  // 837:     TEXT letter.to_upper_case
  // 838:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_107(void) {
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
  // 833: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_108;
}
static void cont__compiler__extract_documentation_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 834: ... :
  // 835:   TD "colspan" = 3:
  // 836:     H2 "id" = letter:
  // 837:       TEXT letter.to_upper_case
  // 838:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_109, 0);
  // 834: TR:
  // 835:   TD "colspan" = 3:
  // 836:     H2 "id" = letter:
  // 837:       TEXT letter.to_upper_case
  // 838:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_120(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 839: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 840: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_121;
}
static void cont__compiler__extract_documentation_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 841: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_122;
}
static void cont__compiler__extract_documentation_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 842: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_123;
}
static void cont__compiler__extract_documentation_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 842: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_124, 0);
  // 842: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_127;
}
static void entry__compiler__extract_documentation_124(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 842: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_125;
}
static void cont__compiler__extract_documentation_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 842: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_126;
}
static void cont__compiler__extract_documentation_126(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 842: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__extract_documentation_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 842: ... :
  // 843:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_128, 0);
  // 842: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 843:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_131;
}
static void entry__compiler__extract_documentation_128(void) {
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
  // 843: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_129;
}
static void cont__compiler__extract_documentation_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 843: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_130;
}
static void cont__compiler__extract_documentation_130(void) {
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
static void cont__compiler__extract_documentation_131(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 847: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_132;
}
static void cont__compiler__extract_documentation_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 845: $kind_info
  // 846:   case
  // 847:     kind_of(info)
  // 848:     FUNCTION
  // 849:     -> "function"
  // 850:     POLYMORPHIC_FUNCTION
  // 851:     -> "polymorphic function"
  // 852:     POLYMORPHIC_ATTRIBUTE
  // 853:     -> "polymorphic attribute"
  // 854:     INLINE_C_TYPE
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__compiler__extract_documentation_133;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = func__compiler__extract_documentation_135;
  arguments->slots[5] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[6] = func__compiler__extract_documentation_137;
  arguments->slots[7] = var._INLINE_C_TYPE;
  arguments->slots[8] = func__compiler__extract_documentation_139;
  arguments->slots[9] = var._INLINE_C_OBJECT;
  arguments->slots[10] = func__compiler__extract_documentation_141;
  arguments->slots[11] = var._INLINE_C_FUNCTION;
  arguments->slots[12] = func__compiler__extract_documentation_143;
  arguments->slots[13] = var._UNIQUE_ITEM;
  arguments->slots[14] = func__compiler__extract_documentation_145;
  arguments->slots[15] = var._CONSTANT;
  arguments->slots[16] = func__compiler__extract_documentation_147;
  arguments->slots[17] = var._OTHER;
  arguments->slots[18] = func__compiler__extract_documentation_149;
  arguments->slots[19] = func__compiler__extract_documentation_151;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_152;
}
static void entry__compiler__extract_documentation_133(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 849: -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__46c0af9104ada08e;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_135(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 851: -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ed9727706924ddb4;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_137(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 853: -> "polymorphic attribute"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2deb4fae6a76bcfc;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_139(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 855: -> "inline-C type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__eb5e9ee1bad4562d;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_141(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 857: -> "inline-C object"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__81158b7754be081a;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_143(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 859: -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1de01e2461abc9b;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_145(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 861: -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__d28944592625a968;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_147(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: -> "constant"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__46a8ad9104a4a034;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_149(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 865: -> "other"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__625ae903eae0e025;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_151(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 866: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__extract_documentation_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 868: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_153;
}
static void cont__compiler__extract_documentation_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 868: ... :
  // 869:   if
  // 870:     remark.is_defined:
  // 871:       !remark string(remark " (" kind_info ")")
  // 872:     :
  // 873:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_154, 0);
  // 868: if kind_info.is_defined:
  // 869:   if
  // 870:     remark.is_defined:
  // 871:       !remark string(remark " (" kind_info ")")
  // 872:     :
  // 873:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_160;
}
static void entry__compiler__extract_documentation_156(void) {
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
  // 871: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__2d7981f4e6082bed;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__578a5af303e9cc8;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_158;
}
static void cont__compiler__extract_documentation_158(void) {
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
static void entry__compiler__extract_documentation_159(void) {
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
  // 873: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__extract_documentation_154(void) {
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
  // 870: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_155;
}
static void cont__compiler__extract_documentation_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 870: ... :
  // 871:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_156, 0);
  // 872: :
  // 873:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_159, 0);
  // 869: if
  // 870:   remark.is_defined:
  // 871:     !remark string(remark " (" kind_info ")")
  // 872:   :
  // 873:     !remark kind_info
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
static void cont__compiler__extract_documentation_160(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 874: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_161;
}
static void cont__compiler__extract_documentation_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 874: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__compiler__extract_documentation_162, 0);
  // 874: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_164;
}
static void entry__compiler__extract_documentation_162(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 874: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_163;
}
static void cont__compiler__extract_documentation_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 874: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__extract_documentation_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 874: ... :
  // 875:   TR:
  // 876:     TD "align" = "right" name .until. "::"
  // 877:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 878:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__compiler__extract_documentation_165, 0);
  // 874: if remark.is_defined && name.is_defined:
  // 875:   TR:
  // 876:     TD "align" = "right" name .until. "::"
  // 877:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 878:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_102(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 830: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 831: ... : (iname info)
  // 832:   if iname(1) != letter:
  // 833:     !letter iname(1)
  // 834:     TR:
  // 835:       TD "colspan" = 3:
  // 836:         H2 "id" = letter:
  // 837:           TEXT letter.to_upper_case
  // 838:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 839:   $$remark undefined
  // 840:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_103, 2);
  // 831: for_each definitions: (iname info)
  // 832:   if iname(1) != letter:
  // 833:     !letter iname(1)
  // 834:     TR:
  // 835:       TD "colspan" = 3:
  // 836:         H2 "id" = letter:
  // 837:           TEXT letter.to_upper_case
  // 838:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 839:   $$remark undefined
  // 840:   $name name_of(info)
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
static void entry__compiler__extract_documentation_87(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 820: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_88;
}
static void cont__compiler__extract_documentation_88(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 821: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4402ba1;
  arguments->slots[1] = string__565aea03eae0802f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_91;
}
static void cont__compiler__extract_documentation_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 821: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__d6ed116d58489777;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_92;
}
static void cont__compiler__extract_documentation_92(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 822: from_to
  // 823:   'a'
  // 824:   'z': (letter)
  // 825:     A "href" = "#@(letter)" letter.to_upper_case
  // 826:   :
  // 827:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__compiler__extract_documentation_93;
  arguments->slots[3] = func__compiler__extract_documentation_98;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_100;
}
static void entry__compiler__extract_documentation_93(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 825: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc2;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_95;
}
static void cont__compiler__extract_documentation_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 825: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_96;
}
static void cont__compiler__extract_documentation_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 825: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_97;
}
static void cont__compiler__extract_documentation_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 825: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_98(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 827: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__578a5af303e9cc1;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_100(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 828: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_101;
}
static void cont__compiler__extract_documentation_101(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 829: TABLE:
  // 830:   $$letter undefined
  // 831:   for_each definitions: (iname info)
  // 832:     if iname(1) != letter:
  // 833:       !letter iname(1)
  // 834:       TR:
  // 835:         TD "colspan" = 3:
  // 836:           H2 "id" = letter:
  // 837:             TEXT letter.to_upper_case
  // 838:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_102;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_180(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 879: for_each definitions: (_iname info)
  // 880:   $name name_of(info)
  // 881:   create_info_page name info
  // 882:   case kind_of(info) INLINE_C_TYPE:
  // 883:     for_each methods_of(info): (method_name method_info)
  // 884:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__compiler__extract_documentation_181;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_189;
}
static void entry__compiler__extract_documentation_187(void) {
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
  // 884: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__578a5af303e9cce;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_188;
}
static void cont__compiler__extract_documentation_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 884: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_185(void) {
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
  // 883: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_186;
}
static void cont__compiler__extract_documentation_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 883: ... : (method_name method_info)
  // 884:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_187, 2);
  // 883: for_each methods_of(info): (method_name method_info)
  // 884:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_181(void) {
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
  // 880: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_182;
}
static void cont__compiler__extract_documentation_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 881: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_183;
}
static void cont__compiler__extract_documentation_183(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 882: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_184;
}
static void cont__compiler__extract_documentation_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 882: ... :
  // 883:   for_each methods_of(info): (method_name method_info)
  // 884:     create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_185, 0);
  // 882: case kind_of(info) INLINE_C_TYPE:
  // 883:   for_each methods_of(info): (method_name method_info)
  // 884:     create_info_page string(name "/" method_name) method_info
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
static void cont__compiler__extract_documentation_189(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 885: create_page "html/topics_index.html":
  // 886:   link_bar
  // 887:   H1 "id" = "index" "Topics Index"
  // 888:   TABLE:
  // 889:     for_each topics: (topic _references)
  // 890:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 891:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__37b4111ed8c9af38;
  arguments->slots[1] = func__compiler__extract_documentation_191;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_204;
}
static void entry__compiler__extract_documentation_202(void) {
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
  // 891: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_203;
}
static void cont__compiler__extract_documentation_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 891: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_201(void) {
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
  // 891: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_202, 0);
  // 891: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_196(void) {
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
  // 890: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_197;
}
static void cont__compiler__extract_documentation_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 890: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__578a5af303e9cbe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_198;
}
static void cont__compiler__extract_documentation_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 890: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_199;
}
static void cont__compiler__extract_documentation_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 890: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_200;
}
static void cont__compiler__extract_documentation_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 891: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_201, 0);
  // 891: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_195(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 889: for_each topics: (topic _references)
  // 890:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 891:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__compiler__extract_documentation_196;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_191(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 886: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_192;
}
static void cont__compiler__extract_documentation_192(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 887: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4402ba1;
  arguments->slots[1] = string__565aea03eae0802f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_193;
}
static void cont__compiler__extract_documentation_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 887: H1 "id" = "index" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__5691f96d534696f2;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_194;
}
static void cont__compiler__extract_documentation_194(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 888: TABLE:
  // 889:   for_each topics: (topic _references)
  // 890:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 891:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_195;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_204(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 892: for_each topics: (topic references)
  // 893:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 894:   create_page "html/@(filename).html":
  // 895:     link_bar
  // 896:     H1 "id" = "index" topic
  // 897:     $paragraphs topics_paragraphs(topic)
  // 898:     if paragraphs.is_defined:
  // 899:       for_each paragraphs: (paragraph) P paragraph.add_links
  // 900:     TABLE:
  // 901:       for_each references: (reference)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__compiler__extract_documentation_205;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_230;
}
static void entry__compiler__extract_documentation_222(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 903: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_223, 0);
  // 903: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_227;
}
static void entry__compiler__extract_documentation_223(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 903: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_224;
}
static void cont__compiler__extract_documentation_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 903: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_225;
}
static void cont__compiler__extract_documentation_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 903: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_226;
}
static void cont__compiler__extract_documentation_226(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 903: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_227(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 904: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__5c1f52a3813ab2ec;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_228;
}
static void cont__compiler__extract_documentation_228(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 905: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_229;
}
static void cont__compiler__extract_documentation_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 905: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_221(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 902: ... :
  // 903:   TD: A "href" = string(reference.mangled ".html") reference
  // 904:   TD "&nbsp;"
  // 905:   TD short_descriptions(reference)
  frame->slots[1] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_222, 0);
  // 902: TR:
  // 903:   TD: A "href" = string(reference.mangled ".html") reference
  // 904:   TD "&nbsp;"
  // 905:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_220(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 901: for_each references: (reference)
  // 902:   TR:
  // 903:     TD: A "href" = string(reference.mangled ".html") reference
  // 904:     TD "&nbsp;"
  // 905:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__compiler__extract_documentation_221;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_210(void) {
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
  // 895: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_211;
}
static void cont__compiler__extract_documentation_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 896: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2d7981f4e4402ba1;
  arguments->slots[1] = string__565aea03eae0802f;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_212;
}
static void cont__compiler__extract_documentation_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 896: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_213;
}
static void cont__compiler__extract_documentation_213(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 897: $paragraphs topics_paragraphs(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = var._topics_paragraphs;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_214;
}
static void cont__compiler__extract_documentation_214(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* paragraphs */, arguments->slots[0]);
  // 898: ... paragraphs.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* paragraphs */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_215;
}
static void cont__compiler__extract_documentation_215(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 898: ... :
  // 899:   for_each paragraphs: (paragraph) P paragraph.add_links
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_216, 0);
  // 898: if paragraphs.is_defined:
  // 899:   for_each paragraphs: (paragraph) P paragraph.add_links
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_219;
}
static void entry__compiler__extract_documentation_217(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // paragraph: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 899: ... paragraph.add_links
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraph */;
  result_count = 1;
  myself = var._add_links;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_218;
}
static void cont__compiler__extract_documentation_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 899: ... P paragraph.add_links
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_216(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // paragraphs: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* paragraphs */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 899: for_each paragraphs: (paragraph) P paragraph.add_links
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* paragraphs */;
  arguments->slots[1] = func__compiler__extract_documentation_217;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_219(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 900: ... :
  // 901:   for_each references: (reference)
  // 902:     TR:
  // 903:       TD: A "href" = string(reference.mangled ".html") reference
  // 904:       TD "&nbsp;"
  // 905:       TD short_descriptions(reference)
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__extract_documentation_220, 0);
  // 900: TABLE:
  // 901:   for_each references: (reference)
  // 902:     TR:
  // 903:       TD: A "href" = string(reference.mangled ".html") reference
  // 904:       TD "&nbsp;"
  // 905:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_205(void) {
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
  // 893: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_206;
}
static void cont__compiler__extract_documentation_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 893: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__578a5af303e9cbe;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_207;
}
static void cont__compiler__extract_documentation_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 893: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_208;
}
static void cont__compiler__extract_documentation_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 894: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__625ae843eaa89078;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__5a5aee03eaa4f03b;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_209;
}
static void cont__compiler__extract_documentation_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 894: ... :
  // 895:   link_bar
  // 896:   H1 "id" = "index" topic
  // 897:   $paragraphs topics_paragraphs(topic)
  // 898:   if paragraphs.is_defined:
  // 899:     for_each paragraphs: (paragraph) P paragraph.add_links
  // 900:   TABLE:
  // 901:     for_each references: (reference)
  // 902:       TR:
  // 903:         TD: A "href" = string(reference.mangled ".html") reference
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__extract_documentation_210, 0);
  // 894: create_page "html/@(filename).html":
  // 895:   link_bar
  // 896:   H1 "id" = "index" topic
  // 897:   $paragraphs topics_paragraphs(topic)
  // 898:   if paragraphs.is_defined:
  // 899:     for_each paragraphs: (paragraph) P paragraph.add_links
  // 900:   TABLE:
  // 901:     for_each references: (reference)
  // 902:       TR:
  // 903:         TD: A "href" = string(reference.mangled ".html") reference
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
static void cont__compiler__extract_documentation_230(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 906: create_page "html/index.html":
  // 907:   H1 "Simplicity"
  // 908:   P: A "href" = "manual.html" "Manual"
  // 909:   P: A "href" = "type_index.html" "Type Index"
  // 910:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 911:   P: A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__c901ef2c97c0c8f2;
  arguments->slots[1] = func__compiler__extract_documentation_232;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_246;
}
static void entry__compiler__extract_documentation_244(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 911: ... "href" = "topics_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__b982567928221cc5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_245;
}
static void cont__compiler__extract_documentation_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 911: ... A "href" = "topics_index.html" "Topics Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__5691f96d534696f2;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__extract_documentation_232(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 907: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33258a5daf8be458;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_234;
}
static void cont__compiler__extract_documentation_234(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 908: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_235;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_237;
}
static void entry__compiler__extract_documentation_235(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 908: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__d0d93c5da16549ef;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_236;
}
static void cont__compiler__extract_documentation_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 908: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__441f531601b242bb;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_237(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 909: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_238;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_240;
}
static void entry__compiler__extract_documentation_238(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 909: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__cf81eefc97d2b8ee;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_239;
}
static void cont__compiler__extract_documentation_239(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 909: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__2971b13bbf01e7f9;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_240(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 910: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_241;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_243;
}
static void entry__compiler__extract_documentation_241(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 910: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__120aedcb5d487d5f;
  arguments->slots[1] = string__bc0556bbe81c68c5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__compiler__extract_documentation_242;
}
static void cont__compiler__extract_documentation_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 910: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__d6ed116d58489777;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_243(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 911: P: A "href" = "topics_index.html" "Topics Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__compiler__extract_documentation_244;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__extract_documentation_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 912: if do_print_summary:
  // 913:   $$total_functions 0
  // 914:   $$total_polymorphic_functions 0
  // 915:   $$total_polymorphic_attributes 0
  // 916:   $$total_methods 0
  // 917:   $$total_inline_c_methods 0
  // 918:   $$total_inline_c_types 0
  // 919:   $$total_inline_c_objects 0
  // 920:   $$total_attributes 0
  // 921:   $$total_inline_c_functions 0
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_summary();
  arguments->slots[1] = func__compiler__extract_documentation_247;
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
  var._extract_remark_lines = collect_node(var._extract_remark_lines);
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
  var.compiler__extract_exports = collect_node(var.compiler__extract_exports);
  var.compiler__extract_documentation = collect_node(var.compiler__extract_documentation);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__extractor(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__extractor(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("extractor");
  character__35 = from_uchar32(35);
  character__122 = from_uchar32(122);
  character__47 = from_uchar32(47);
  number__80 = from_uint32(80U);
  character__63 = from_uchar32(63);
  character__44 = from_uchar32(44);
  character__58 = from_uchar32(58);
  number__0 = from_uint32(0U);
  number__3 = from_uint32(3U);
  character__37 = from_uchar32(37);
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
  register_polymorphic_function_with_setter("_extractor::filename_of", &poly_idx__filename_of);
  register_polymorphic_function_with_setter("_extractor::used_namespaces_of", &poly_idx__used_namespaces_of);
  register_polymorphic_function_with_setter("_extractor::derived_types_of", &poly_idx__derived_types_of);
  register_polymorphic_function_with_setter("_extractor::methods_of", &poly_idx__methods_of);
  register_polymorphic_function_with_setter("_extractor::types_of", &poly_idx__types_of);
  unique__FUNCTION = register_unique_item("FUNCTION");
  unique__POLYMORPHIC_FUNCTION = register_unique_item("POLYMORPHIC_FUNCTION");
  unique__POLYMORPHIC_ATTRIBUTE = register_unique_item("POLYMORPHIC_ATTRIBUTE");
  unique__INLINE_C_TYPE = register_unique_item("INLINE_C_TYPE");
  unique__INLINE_C_OBJECT = register_unique_item("INLINE_C_OBJECT");
  unique__INLINE_C_FUNCTION = register_unique_item("INLINE_C_FUNCTION");
  unique__UNIQUE_ITEM = register_unique_item("UNIQUE_ITEM");
  unique__CONSTANT = register_unique_item("CONSTANT");
  unique__OTHER = register_unique_item("OTHER");
  string__38ea9d2e8a7087ec = from_latin_1_string(
    "body {\n"
    "  background-color: white;\n"
    "  font-family: Times New Roman, Times;\n"
    "  font-size: 12pt;\n"
    "  color: #222;\n"
    "}\n"
    "h1 {\n"
    "  font-family: Arial, Helvetica;\n"
    "  font-size: 20pt;\n"
    "  color: #333;\n"
    "  margin-top: 0pt;\n"
    "  margin-bottom: 8pt;\n"
    "}\n"
    "h2 {\n"
    "  font-family: Arial, Helvetica;\n"
    "  font-size: 16pt;\n"
    "  color: #222;\n"
    "  margin-top: 5pt;\n"
    "  margin-bottom: 5pt;\n"
    "}\n"
    "h3 {\n"
    "  font-family: Arial, Helvetica;\n"
    "  font-size: 14pt;\n"
    "  color: #222;\n"
    "  margin-top: 3pt;\n"
    "  margin-bottom: 3pt;\n"
    "}\n"
    "h4 {\n"
    "  font-family: Arial, Helvetica;\n"
    "  font-size: 13pt;\n"
    "  color: #222;\n"
    "  margin-top: 2pt;\n"
    "  margin-bottom: 2pt;\n"
    "}\n"
    "dt {\n"
    "  font-style: italic;\n"
    "  margin-bottom: 4pt;\n"
    "}\n"
    "dd {\n"
    "  padding-left: 0pt;\n"
    "  margin-left: 16pt;\n"
    "  margin-top: 0pt;\n"
    "  margin-bottom: 0pt;\n"
    "}\n"
    "p {\n"
    "  margin-top: 0pt;\n"
    "  margin-bottom: 8pt;\n"
    "}\n"
    "a {\n"
    "  text-decoration: none;\n"
    "}\n"
    "div.Example {\n"
    "  background-color: #ffc;\n"
    "  border: solid 1pt;\n"
    "  margin-top: 6pt;\n"
    "  margin-bottom: 8pt;\n"
    "}\n"
    "div.Output {\n"
    "  background-color: #cff;\n"
    "  border: solid 1pt;\n"
    "  margin-top: 6pt;\n"
    "  margin-bottom: 8pt;\n"
    "}\n"
    "div.footer {\n"
    "  padding-top: 10pt;\n"
    "  font-size: 10pt;\n"
    "}\n"
    "pre {\n"
    "  font-family: Courier New, Courier;\n"
    "  font-size: 12pt;\n"
    "  padding-top: 0pt;\n"
    "  padding-bottom: 0pt;\n"
    "  margin-top: 2pt;\n"
    "  margin-bottom: 2pt;\n"
    "}\n"
    "td.remark {\n"
    "  padding-left: 10pt;\n"
    "}\n",
    1234);
  func__create_page_4 = create_function(entry__create_page_4, 0);
  func__create_page_1 = create_function(entry__create_page_1, 2);
  func__extract_remark_lines_14 = create_function(entry__extract_remark_lines_14, 0);
  func__extract_remark_lines_15 = create_function(entry__extract_remark_lines_15, 0);
  func__extract_remark_lines_1 = create_function(entry__extract_remark_lines_1, 1);
  string__f68a3e9b60626ed6 = from_latin_1_string("extracting documentation from ", 30);
  string__1cbf9967f0b4797a = from_latin_1_string("Empty source text!", 18);
  func__extract_documentation_from_file_10 = create_function(entry__extract_documentation_from_file_10, 0);
  string__cdb2cfe249b97e8f = from_latin_1_string("Whitespace at start of source text!", 35);
  func__extract_documentation_from_file_16 = create_function(entry__extract_documentation_from_file_16, 0);
  string__f5ba012e5873af55 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__extract_documentation_from_file_23 = create_function(entry__extract_documentation_from_file_23, 0);
  string__9e0aed8b5d287d54 = from_latin_1_string(".sim", 4);
  string__2d7981f4e5f02b9a = from_latin_1_string("__", 2);
  func__extract_documentation_from_file_32 = create_function(entry__extract_documentation_from_file_32, 1);
  func__extract_documentation_from_file_43 = create_function(entry__extract_documentation_from_file_43, 0);
  string__fa724815d896ba8 = from_latin_1_string("std", 3);
  func__extract_documentation_from_file_53 = create_function(entry__extract_documentation_from_file_53, 0);
  func__extract_documentation_from_file_60 = create_function(entry__extract_documentation_from_file_60, 0);
  func__extract_documentation_from_file_63 = create_function(entry__extract_documentation_from_file_63, 0);
  string__781f541a81a2a2ed = from_latin_1_string("Topic:", 6);
  func__extract_documentation_from_file_122 = create_function(entry__extract_documentation_from_file_122, 0);
  string__2a0aef0b5de07d5c = from_latin_1_string("type", 4);
  string__4c1f570701a272a3 = from_latin_1_string("object", 6);
  func__extract_documentation_from_file_145 = create_function(entry__extract_documentation_from_file_145, 1);
  func__extract_documentation_from_file_162 = create_function(entry__extract_documentation_from_file_162, 0);
  func__extract_documentation_from_file_163 = create_function(entry__extract_documentation_from_file_163, 0);
  string__f7c371b7c3c668a7 = from_latin_1_string("types::function", 15);
  func__extract_documentation_from_file_1 = create_function(entry__extract_documentation_from_file_1, 1);
  func__extract_documentation_from_directory_4 = create_function(entry__extract_documentation_from_directory_4, 1);
  func__extract_documentation_from_directory_1 = create_function(entry__extract_documentation_from_directory_1, 1);
  string__7f3103e18f358a6f = from_latin_1_string("The attribute \042", 15);
  string__abd8bded937d2ca5 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__8906d104d2e53fac = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__2d7981f4e6d82bff = from_latin_1_string("::", 2);
  func__resolved_name_1 = create_function(entry__resolved_name_1, 1);
  func__add_derived_type_1 = create_function(entry__add_derived_type_1, 2);
  string__fa72f815cd16b93 = from_latin_1_string("___", 3);
  func__mangled_1 = create_function(entry__mangled_1, 1);
  func__ordered_name_1 = create_function(entry__ordered_name_1, 2);
  string__120aedcb5d487d5f = from_latin_1_string("href", 4);
  string__25705d17a847956d = from_latin_1_string("index.html", 10);
  string__520aea8b5d087d5c = from_latin_1_string("Home", 4);
  string__57442216b13fc418 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__d0d93c5da16549ef = from_latin_1_string("manual.html", 11);
  string__441f531601b242bb = from_latin_1_string("Manual", 6);
  string__cf81eefc97d2b8ee = from_latin_1_string("type_index.html", 15);
  string__2971b13bbf01e7f9 = from_latin_1_string("Type Index", 10);
  string__bc0556bbe81c68c5 = from_latin_1_string("symbol_index.html", 17);
  string__d6ed116d58489777 = from_latin_1_string("Symbol Index", 12);
  string__b982567928221cc5 = from_latin_1_string("topics_index.html", 17);
  string__5691f96d534696f2 = from_latin_1_string("Topics Index", 12);
  func__link_bar_2 = create_function(entry__link_bar_2, 0);
  func__link_bar_1 = create_function(entry__link_bar_1, 0);
  func__to_paragraphs_1 = create_function(entry__to_paragraphs_1, 1);
  string__b854091e176bc0c0 = from_latin_1_string("types::", 7);
  string__625aea03e819206d = from_latin_1_string("std::", 5);
  func__resolve_reference_1 = create_function(entry__resolve_reference_1, 1);
  string__578a5af303e9cba = from_latin_1_string("[", 1);
  string__2d7981f4e5e02bed = from_latin_1_string("](", 2);
  string__701f552781dad2fe = from_latin_1_string(".html)", 6);
  func__add_links_5 = create_function(entry__add_links_5, 1);
  func__add_links_1 = create_function(entry__add_links_1, 1);
  string__3da288aac4394c18 = from_latin_1_string("The documentation for \042", 23);
  string__740195f292b901ee = from_latin_1_string(
    "\042\n"
    "(defined in \042",
    15);
  string__e4c238e2b0c78735 = from_latin_1_string(
    "\042)\n"
    "references the undefined symbol \042",
    36);
  string__fa730c15f216bc6 = from_latin_1_string("\042!\012", 3);
  string__625ae843eaa89078 = from_latin_1_string("html/", 5);
  string__5a5aee03eaa4f03b = from_latin_1_string(".html", 5);
  string__76b4bf9c06ad49bb = from_latin_1_string(".html)/[", 8);
  string__4ce0cf0d4ae053bd = from_latin_1_string("(static multi-assignment variable)", 34);
  func__create_info_page_33 = create_function(entry__create_info_page_33, 0);
  string__c674570cd5378184 = from_latin_1_string("(dynamic single-assignment variable)", 36);
  func__create_info_page_35 = create_function(entry__create_info_page_35, 0);
  string__f7a1838e683da008 = from_latin_1_string("(dynamic multi-assignment variable)", 35);
  func__create_info_page_37 = create_function(entry__create_info_page_37, 0);
  string__6cb12e827f50f616 = from_latin_1_string("Missing documentation for ", 26);
  string__f3159560bf5212b5 = from_latin_1_string(" (defined in \042", 14);
  string__860afb0b5f687d33 = from_latin_1_string("\042)!\012", 4);
  string__64f823ac322ba4f7 = from_latin_1_string("Parameter", 9);
  string__9c8f711f20695919 = from_latin_1_string(" (optional)", 11);
  string__b78062cac7fbaabb = from_latin_1_string(" (zero or more arguments)", 25);
  string__c050e39b840a7454 = from_latin_1_string(" (optional; default value: ", 27);
  string__578a5af303e9cc8 = from_latin_1_string(")", 1);
  string__98cc095015cb8089 = from_latin_1_string("Returns", 7);
  string__76a4224cb17b643f = from_latin_1_string("See also:", 9);
  string__8f3750dfc2ad5d0a = from_latin_1_string("Technical Details:", 18);
  func__create_info_page_213 = create_function(entry__create_info_page_213, 0);
  func__create_info_page_217 = create_function(entry__create_info_page_217, 0);
  string__1d61915d27bb27b2 = from_latin_1_string("Parameters", 10);
  func__create_info_page_227 = create_function(entry__create_info_page_227, 1);
  func__create_info_page_237 = create_function(entry__create_info_page_237, 1);
  string__a8951b1f3c70ab27 = from_latin_1_string("Description", 11);
  func__create_info_page_247 = create_function(entry__create_info_page_247, 1);
  string__aba611e6ea1bf855 = from_latin_1_string("Technical Details", 17);
  func__create_info_page_253 = create_function(entry__create_info_page_253, 1);
  string__6c80aed48449962f = from_latin_1_string("See also", 8);
  string__5c1f52a3813ab2ec = from_latin_1_string("&nbsp;", 6);
  string__9db99ab8b96e438c = from_latin_1_string("Implemented by", 14);
  string__664d2661efdaf349 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__3f555b992b8ba7f2 = from_latin_1_string("Implements", 10);
  string__ef7adaf915740b94 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__781f541a81a2a2a4 = from_latin_1_string("Topics", 6);
  string__578a5af303e9cbe = from_latin_1_string("_", 1);
  func__create_info_page_331 = create_function(entry__create_info_page_331, 1);
  string__525aeb43ea502024 = from_latin_1_string("class", 5);
  func__create_info_page_354 = create_function(entry__create_info_page_354, 1);
  string__2d7981f4e6582bef = from_latin_1_string("**", 2);
  string__461f53438192a2a5 = from_latin_1_string("footer", 6);
  string__ae5520fdce447e8 = from_latin_1_string("(defined in ", 12);
  string__2d7981f4e6402bcf = from_latin_1_string(")\012", 2);
  func__create_info_page_1 = create_function(entry__create_info_page_1, 2);
  string__10bb152df59cfc0e = from_latin_1_string(
    "\n"
    "The short description for \042",
    28);
  string__8eef7e8eb4c1beaf = from_latin_1_string(
    "\042)\n"
    "is quite long:\n",
    18);
  string__578a5af303e9ceb = from_latin_1_string("\012", 1);
  func__get_short_description_1 = create_function(entry__get_short_description_1, 2);
  func__compiler__extract_exports_5 = create_function(entry__compiler__extract_exports_5, 1);
  func__compiler__extract_exports_15 = create_function(entry__compiler__extract_exports_15, 0);
  string__2d7981f4e6282be1 = from_latin_1_string("$$", 2);
  func__compiler__extract_exports_16 = create_function(entry__compiler__extract_exports_16, 0);
  func__compiler__extract_exports_18 = create_function(entry__compiler__extract_exports_18, 0);
  string__2d7981f4e6202be0 = from_latin_1_string("%%", 2);
  func__compiler__extract_exports_19 = create_function(entry__compiler__extract_exports_19, 0);
  string__fa732415f216be5 = from_latin_1_string("(!)", 3);
  func__compiler__extract_exports_21 = create_function(entry__compiler__extract_exports_21, 0);
  string__2d7981f4e6482bec = from_latin_1_string("()", 2);
  func__compiler__extract_exports_23 = create_function(entry__compiler__extract_exports_23, 0);
  func__compiler__extract_exports_25 = create_function(entry__compiler__extract_exports_25, 0);
  func__compiler__extract_exports_7 = create_function(entry__compiler__extract_exports_7, 2);
  func__compiler__extract_exports_1 = create_function(entry__compiler__extract_exports_1, 1);
  func__compiler__extract_documentation_5 = create_function(entry__compiler__extract_documentation_5, 1);
  string__8f47f24352a780c2 = from_latin_1_string(
    "Incomplete definition encountered:\n"
    "\n"
    "There is no name for the definition of \042",
    76);
  string__578a5af303e9cce = from_latin_1_string("/", 1);
  func__compiler__extract_documentation_7 = create_function(entry__compiler__extract_documentation_7, 2);
  string__5042403361ea61f3 = from_latin_1_string("html/type_index.html", 20);
  func__compiler__extract_documentation_47 = create_function(entry__compiler__extract_documentation_47, 0);
  string__323311dc18f7db38 = from_latin_1_string("html/symbol_index.html", 22);
  string__2d7981f4e4402ba1 = from_latin_1_string("id", 2);
  string__565aea03eae0802f = from_latin_1_string("index", 5);
  string__578a5af303e9cc2 = from_latin_1_string("#", 1);
  func__compiler__extract_documentation_93 = create_function(entry__compiler__extract_documentation_93, 1);
  string__578a5af303e9cc1 = from_latin_1_string(" ", 1);
  func__compiler__extract_documentation_98 = create_function(entry__compiler__extract_documentation_98, 0);
  string__940809d515b20094 = from_latin_1_string("colspan", 7);
  string__441f57610192c2af = from_latin_1_string("#index", 6);
  string__c50d368eedcf3ba9 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__46c0af9104ada08e = from_latin_1_string("function", 8);
  func__compiler__extract_documentation_133 = create_function(entry__compiler__extract_documentation_133, 0);
  string__ed9727706924ddb4 = from_latin_1_string("polymorphic function", 20);
  func__compiler__extract_documentation_135 = create_function(entry__compiler__extract_documentation_135, 0);
  string__2deb4fae6a76bcfc = from_latin_1_string("polymorphic attribute", 21);
  func__compiler__extract_documentation_137 = create_function(entry__compiler__extract_documentation_137, 0);
  string__eb5e9ee1bad4562d = from_latin_1_string("inline-C type", 13);
  func__compiler__extract_documentation_139 = create_function(entry__compiler__extract_documentation_139, 0);
  string__81158b7754be081a = from_latin_1_string("inline-C object", 15);
  func__compiler__extract_documentation_141 = create_function(entry__compiler__extract_documentation_141, 0);
  string__1de01e2461abc9b = from_latin_1_string("inline-C function", 17);
  func__compiler__extract_documentation_143 = create_function(entry__compiler__extract_documentation_143, 0);
  string__d28944592625a968 = from_latin_1_string("unique item", 11);
  func__compiler__extract_documentation_145 = create_function(entry__compiler__extract_documentation_145, 0);
  string__46a8ad9104a4a034 = from_latin_1_string("constant", 8);
  func__compiler__extract_documentation_147 = create_function(entry__compiler__extract_documentation_147, 0);
  string__625ae903eae0e025 = from_latin_1_string("other", 5);
  func__compiler__extract_documentation_149 = create_function(entry__compiler__extract_documentation_149, 0);
  func__compiler__extract_documentation_151 = create_function(entry__compiler__extract_documentation_151, 0);
  string__2d7981f4e6082bed = from_latin_1_string(" (", 2);
  string__525ae943eaf00039 = from_latin_1_string("align", 5);
  string__585aeac3ea893023 = from_latin_1_string("right", 5);
  string__421f5609812a02bc = from_latin_1_string("remark", 6);
  func__compiler__extract_documentation_102 = create_function(entry__compiler__extract_documentation_102, 0);
  func__compiler__extract_documentation_87 = create_function(entry__compiler__extract_documentation_87, 0);
  func__compiler__extract_documentation_181 = create_function(entry__compiler__extract_documentation_181, 2);
  string__37b4111ed8c9af38 = from_latin_1_string("html/topics_index.html", 22);
  func__compiler__extract_documentation_196 = create_function(entry__compiler__extract_documentation_196, 2);
  func__compiler__extract_documentation_195 = create_function(entry__compiler__extract_documentation_195, 0);
  func__compiler__extract_documentation_191 = create_function(entry__compiler__extract_documentation_191, 0);
  func__compiler__extract_documentation_217 = create_function(entry__compiler__extract_documentation_217, 1);
  func__compiler__extract_documentation_221 = create_function(entry__compiler__extract_documentation_221, 1);
  func__compiler__extract_documentation_205 = create_function(entry__compiler__extract_documentation_205, 2);
  string__c901ef2c97c0c8f2 = from_latin_1_string("html/index.html", 15);
  string__33258a5daf8be458 = from_latin_1_string("Simplicity", 10);
  func__compiler__extract_documentation_235 = create_function(entry__compiler__extract_documentation_235, 0);
  func__compiler__extract_documentation_238 = create_function(entry__compiler__extract_documentation_238, 0);
  func__compiler__extract_documentation_241 = create_function(entry__compiler__extract_documentation_241, 0);
  func__compiler__extract_documentation_244 = create_function(entry__compiler__extract_documentation_244, 0);
  func__compiler__extract_documentation_232 = create_function(entry__compiler__extract_documentation_232, 0);
  string__f5d1f6a5c0048246 = from_latin_1_string("total definitions:     ", 23);
  string__c40b62b5c2e5a063 = from_latin_1_string(
    "\n"
    "\n"
    "functions:             ",
    25);
  string__3441ee1e4106d8f4 = from_latin_1_string(
    "\n"
    "polymorphic functions: ",
    24);
  string__c035e39bd94f7acf = from_latin_1_string(
    "\n"
    "polymorphic attributes:",
    24);
  string__effbd005c6cabd2e = from_latin_1_string(
    "\n"
    "method definitions:    ",
    24);
  string__2b2b0af8abbb8aa7 = from_latin_1_string(
    "\n"
    "inline C methods:      ",
    24);
  string__90c6182ac0816ddd = from_latin_1_string(
    "\n"
    "attribute definitions: ",
    24);
  string__effbd3d1268e2925 = from_latin_1_string(
    "\n"
    "inline C functions:    ",
    24);
  string__67c3eb38f5b380c4 = from_latin_1_string(
    "\n"
    "inline C types:        ",
    24);
  string__6a2b6a88bb878aa4 = from_latin_1_string(
    "\n"
    "inline C objects:      ",
    24);
  string__ff41420da974d0d3 = from_latin_1_string(
    "\n"
    "unique items:          ",
    24);
  string__e400cbf53b9db9ae = from_latin_1_string(
    "\n"
    "other constants:       ",
    24);
  string__4dc16ebc881e822d = from_latin_1_string(
    "\n"
    "other:                 ",
    24);
  string__e1857d0a4bd566c9 = from_latin_1_string(
    "\n"
    "\n"
    "missing documentation: ",
    25);
  func__compiler__extract_documentation_247 = create_function(entry__compiler__extract_documentation_247, 0);
  func__compiler__extract_documentation_1 = create_function(entry__compiler__extract_documentation_1, 1);
  string__545aef03ea835034 = from_latin_1_string("Topic", 5);
  string__a89009de95dad09f = from_latin_1_string("Example", 7);
  string__701f5257011302a3 = from_latin_1_string("Output", 6);
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
  var.compiler__extract_exports = create_future();
  define_single_assign_static("compiler", "extract_exports", get__compiler__extract_exports, &var.compiler__extract_exports);
  var.compiler__extract_documentation = create_future();
  define_single_assign_static("compiler", "extract_documentation", get__compiler__extract_documentation, &var.compiler__extract_documentation);
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
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
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
  use_read_only("compiler", "WHITESPACE", &get__compiler__WHITESPACE, &get_value_or_future__compiler__WHITESPACE);
  use_multi_assign_dynamic("compiler", "defined_namespaces", &get__compiler__defined_namespaces, &set__compiler__defined_namespaces, &define__compiler__defined_namespaces);
  use_multi_assign_dynamic("compiler", "dependent_data", &get__compiler__dependent_data, &set__compiler__dependent_data, &define__compiler__dependent_data);
  use_multi_assign_dynamic("compiler", "enumeration_count", &get__compiler__enumeration_count, &set__compiler__enumeration_count, &define__compiler__enumeration_count);
  use_multi_assign_dynamic("compiler", "included_files", &get__compiler__included_files, &set__compiler__included_files, &define__compiler__included_files);
  use_multi_assign_dynamic("compiler", "linked_libraries", &get__compiler__linked_libraries, &set__compiler__linked_libraries, &define__compiler__linked_libraries);
  use_single_assign_dynamic("compiler", "module_name", &get__compiler__module_name, &define__compiler__module_name);
  use_multi_assign_dynamic("compiler", "namespace_mappings", &get__compiler__namespace_mappings, &set__compiler__namespace_mappings, &define__compiler__namespace_mappings);
  use_multi_assign_dynamic("compiler", "required_modules", &get__compiler__required_modules, &set__compiler__required_modules, &define__compiler__required_modules);
  use_multi_assign_dynamic("compiler", "used_namespaces", &get__compiler__used_namespaces, &set__compiler__used_namespaces, &define__compiler__used_namespaces);
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
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "find_first", &get__find_first, &get_value_or_future__find_first);
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
  use_read_only(NULL, "verbose", &get__verbose, &get_value_or_future__verbose);
  use_read_only(NULL, "without_prefix", &get__without_prefix, &get_value_or_future__without_prefix);
  use_read_only(NULL, "without_suffix", &get__without_suffix, &get_value_or_future__without_suffix);
  use_read_only(NULL, "write", &get__write, &get_value_or_future__write);
  use_read_only(NULL, "write_to", &get__write_to, &get_value_or_future__write_to);
  use_read_only(NULL, "writeln", &get__writeln, &get_value_or_future__writeln);
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
  assign_variable(&var._create_page, &func__create_page_1);
  assign_variable(&var._extract_remark_lines, &func__extract_remark_lines_1);
  assign_variable(&var._extract_documentation_from_file, &func__extract_documentation_from_file_1);
  assign_variable(&var._extract_documentation_from_directory, &func__extract_documentation_from_directory_1);
  assign_variable(&var._resolved_name, &func__resolved_name_1);
  assign_variable(&var._add_derived_type, &func__add_derived_type_1);
  assign_variable(&var._mangled, &func__mangled_1);
  assign_variable(&var._ordered_name, &func__ordered_name_1);
  assign_variable(&var._link_bar, &func__link_bar_1);
  assign_variable(&var._to_paragraphs, &func__to_paragraphs_1);
  assign_variable(&var._resolve_reference, &func__resolve_reference_1);
  assign_variable(&var._add_links, &func__add_links_1);
  assign_variable(&var._create_info_page, &func__create_info_page_1);
  assign_variable(&var._get_short_description, &func__get_short_description_1);
  initialize_future(var.compiler__extract_exports, func__compiler__extract_exports_1);
  initialize_future(var.compiler__extract_documentation, func__compiler__extract_documentation_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
