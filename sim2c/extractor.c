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
static NODE_GETTER get__POLYMORPHIC;
static NODE_GETTER get_value_or_future__POLYMORPHIC;
static NODE_GETTER get__PRE;
static NODE_GETTER get_value_or_future__PRE;
static NODE_GETTER get__SORT;
static NODE_GETTER get_value_or_future__SORT;
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
  NODE *_BORING;
  NODE *_FUNCTION;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_POLYMORPHIC_ATTRIBUTE;
  NODE *_INLINE_C_TYPE;
  NODE *_INLINE_C_OBJECT;
  NODE *_INLINE_C_FUNCTION;
  NODE *_UNIQUE_ITEM;
  NODE *_CONSTANT;
  NODE *_VARIABLE;
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
  "BORING",
  "FUNCTION",
  "POLYMORPHIC_FUNCTION",
  "POLYMORPHIC_ATTRIBUTE",
  "INLINE_C_TYPE",
  "INLINE_C_OBJECT",
  "INLINE_C_FUNCTION",
  "UNIQUE_ITEM",
  "CONSTANT",
  "VARIABLE",
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
static NODE *unique__BORING;
static NODE *unique__FUNCTION;
static NODE *unique__POLYMORPHIC_FUNCTION;
static NODE *unique__POLYMORPHIC_ATTRIBUTE;
static NODE *unique__INLINE_C_TYPE;
static NODE *unique__INLINE_C_OBJECT;
static NODE *unique__INLINE_C_FUNCTION;
static NODE *unique__UNIQUE_ITEM;
static NODE *unique__CONSTANT;
static NODE *unique__VARIABLE;
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
static FRAME_INFO frame__24_129 = {10, {"identifier", "namespace", "info", "statement", "break", "destination", "local_method_names", "name", "iname", "source"}};
static void cont__24_130(void);
static void cont__24_131(void);
static void cont__24_132(void);
static void cont__24_133(void);
static void cont__24_134(void);
static NODE *func__24_135;
static void entry__24_135(void);
static FRAME_INFO frame__24_135 = {7, {"source", "name", "namespace", "iname", "info", "statement", "break"}};
static void cont__24_136(void);
static NODE *func__24_137;
static void entry__24_137(void);
static FRAME_INFO frame__24_137 = {7, {"name", "namespace", "iname", "info", "source", "statement", "break"}};
static void cont__24_138(void);
static void cont__24_139(void);
static NODE *func__24_140;
static void entry__24_140(void);
static FRAME_INFO frame__24_140 = {0, {}};
static NODE *func__24_141;
static void entry__24_141(void);
static FRAME_INFO frame__24_141 = {0, {}};
static void cont__24_142(void);
static void cont__24_143(void);
static void cont__24_144(void);
static NODE *func__24_145;
static void entry__24_145(void);
static FRAME_INFO frame__24_145 = {2, {"source", "info"}};
static void cont__24_146(void);
static NODE *func__24_147;
static void entry__24_147(void);
static FRAME_INFO frame__24_147 = {2, {"info", "source"}};
static NODE *string__24_148;
static void cont__24_149(void);
static void cont__24_150(void);
static NODE *func__24_151;
static void entry__24_151(void);
static FRAME_INFO frame__24_151 = {3, {"source", "info", "statement"}};
static void cont__24_152(void);
static NODE *func__24_153;
static void entry__24_153(void);
static FRAME_INFO frame__24_153 = {2, {"info", "statement"}};
static void cont__24_154(void);
static NODE *func__24_155;
static void entry__24_155(void);
static FRAME_INFO frame__24_155 = {3, {"source", "info", "statement"}};
static void cont__24_156(void);
static NODE *func__24_157;
static void entry__24_157(void);
static FRAME_INFO frame__24_157 = {3, {"source", "info", "statement"}};
static void cont__24_158(void);
static void cont__24_159(void);
static NODE *func__24_160;
static void entry__24_160(void);
static FRAME_INFO frame__24_160 = {3, {"info", "source", "statement"}};
static void cont__24_161(void);
static void cont__24_162(void);
static NODE *func__24_163;
static void entry__24_163(void);
static FRAME_INFO frame__24_163 = {5, {"source", "iname", "info", "statement", "break"}};
static void cont__24_164(void);
static NODE *func__24_165;
static void entry__24_165(void);
static FRAME_INFO frame__24_165 = {5, {"iname", "info", "source", "statement", "break"}};
static void cont__24_166(void);
static NODE *func__24_167;
static void entry__24_167(void);
static FRAME_INFO frame__24_167 = {0, {}};
static NODE *func__24_168;
static void entry__24_168(void);
static FRAME_INFO frame__24_168 = {0, {}};
static void cont__24_169(void);
static void cont__24_170(void);
static void cont__24_171(void);
static void cont__24_172(void);
static void cont__24_173(void);
static NODE *func__24_174;
static void entry__24_174(void);
static FRAME_INFO frame__24_174 = {3, {"iname", "info", "previous_definition"}};
static void cont__24_175(void);
static void cont__24_176(void);
static NODE *func__24_177;
static void entry__24_177(void);
static FRAME_INFO frame__24_177 = {2, {"previous_definition", "info"}};
static void cont__24_178(void);
static void cont__24_179(void);
static NODE *func__24_180;
static void entry__24_180(void);
static FRAME_INFO frame__24_180 = {2, {"info", "previous_definition"}};
static void cont__24_181(void);
static void cont__24_182(void);
static void cont__24_183(void);
static void cont__24_184(void);
static void cont__24_185(void);
static void cont__24_186(void);
static NODE *func__24_187;
static void entry__24_187(void);
static FRAME_INFO frame__24_187 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__24_188(void);
static void cont__24_189(void);
static void cont__24_190(void);
static void cont__24_191(void);
static void cont__24_192(void);
static NODE *func__24_193;
static void entry__24_193(void);
static FRAME_INFO frame__24_193 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__24_194(void);
static void cont__24_195(void);
static NODE *func__24_196;
static void entry__24_196(void);
static FRAME_INFO frame__24_196 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__24_197(void);
static void cont__24_198(void);
static NODE *func__24_199;
static void entry__24_199(void);
static FRAME_INFO frame__24_199 = {1, {"attr"}};
static void cont__24_200(void);
static void cont__24_201(void);
static void cont__24_202(void);
static void cont__24_203(void);
static void cont__24_204(void);
static void cont__24_205(void);
static void cont__24_206(void);
static void cont__24_207(void);
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
static NODE *func__34_1_create_info_page;
static void entry__34_1_create_info_page(void);
static FRAME_INFO frame__34_1_create_info_page = {3, {"function_name", "info", "resolve_reference"}};
static NODE *func__34_2_resolve_reference;
static void entry__34_2_resolve_reference(void);
static FRAME_INFO frame__34_2_resolve_reference = {3, {"reference", "function_name", "info"}};
static void cont__34_3(void);
static NODE *func__34_4;
static void entry__34_4(void);
static FRAME_INFO frame__34_4 = {3, {"reference", "type_name", "method_name"}};
static void cont__34_5(void);
static void cont__34_6(void);
static void cont__34_7(void);
static NODE *func__34_8;
static void entry__34_8(void);
static FRAME_INFO frame__34_8 = {1, {"type_name"}};
static NODE *string__34_9;
static void cont__34_10(void);
static void cont__34_11(void);
static void cont__34_12(void);
static NODE *func__34_13;
static void entry__34_13(void);
static FRAME_INFO frame__34_13 = {1, {"method_name"}};
static NODE *string__34_14;
static void cont__34_15(void);
static void cont__34_16(void);
static void cont__34_17(void);
static NODE *func__34_18;
static void entry__34_18(void);
static FRAME_INFO frame__34_18 = {1, {"reference"}};
static void cont__34_19(void);
static NODE *func__34_20;
static void entry__34_20(void);
static FRAME_INFO frame__34_20 = {1, {"reference"}};
static void cont__34_21(void);
static void cont__34_22(void);
static void cont__34_23(void);
static void cont__34_24(void);
static NODE *func__34_25;
static void entry__34_25(void);
static FRAME_INFO frame__34_25 = {3, {"function_name", "info", "reference"}};
static void cont__34_26(void);
static NODE *string__34_27;
static NODE *string__34_28;
static NODE *string__34_29;
static NODE *string__34_30;
static void cont__34_31(void);
static void cont__34_32(void);
static void cont__34_33(void);
static NODE *func__34_34;
static void entry__34_34(void);
static FRAME_INFO frame__34_34 = {3, {"function_name", "info", "resolve_reference"}};
static void cont__34_35(void);
static NODE *string__34_36;
static NODE *string__34_37;
static void cont__34_38(void);
static NODE *func__34_39;
static void entry__34_39(void);
static FRAME_INFO frame__34_39 = {13, {"function_name", "info", "resolve_reference", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "topic_list", "examples", "remark_lines", "function_basename"}};
static void cont__34_40(void);
static void cont__34_41(void);
static NODE *func__34_42;
static void entry__34_42(void);
static FRAME_INFO frame__34_42 = {3, {"function_name", "type", "method"}};
static void cont__34_43(void);
static void cont__34_44(void);
static void cont__34_45(void);
static void cont__34_46(void);
static NODE *string__34_47;
static NODE *string__34_48;
static NODE *string__34_49;
static void cont__34_50(void);
static NODE *func__34_51;
static void entry__34_51(void);
static FRAME_INFO frame__34_51 = {1, {"function_name"}};
static void cont__34_52(void);
static void cont__34_53(void);
static NODE *func__34_54;
static void entry__34_54(void);
static FRAME_INFO frame__34_54 = {1, {"remark_lines"}};
static void cont__34_55(void);
static NODE *func__34_56;
static void entry__34_56(void);
static FRAME_INFO frame__34_56 = {1, {"remark_lines"}};
static void cont__34_57(void);
static void cont__34_58(void);
static void cont__34_59(void);
static NODE *func__34_60;
static void entry__34_60(void);
static FRAME_INFO frame__34_60 = {2, {"function_name", "info"}};
static void cont__34_61(void);
static NODE *string__34_62;
static NODE *string__34_63;
static NODE *string__34_64;
static void cont__34_65(void);
static void cont__34_66(void);
static void cont__34_67(void);
static NODE *func__34_68;
static void entry__34_68(void);
static FRAME_INFO frame__34_68 = {12, {"remark_lines", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_reference", "short_description", "descriptions", "paragraphs"}};
static void cont__34_69(void);
static NODE *func__34_70;
static void entry__34_70(void);
static FRAME_INFO frame__34_70 = {11, {"paragraph", "parameters", "return_values", "references", "topic_list", "function_name", "examples", "technical_details", "resolve_reference", "short_description", "descriptions"}};
static NODE *func__34_71;
static void entry__34_71(void);
static FRAME_INFO frame__34_71 = {2, {"paragraph", "parameters"}};
static void cont__34_72(void);
static NODE *string__34_73;
static void cont__34_74(void);
static void cont__34_75(void);
static NODE *func__34_76;
static void entry__34_76(void);
static FRAME_INFO frame__34_76 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__34_77(void);
static NODE *func__34_78;
static void entry__34_78(void);
static FRAME_INFO frame__34_78 = {1, {"parameter"}};
static void cont__34_79(void);
static NODE *func__34_80;
static void entry__34_80(void);
static FRAME_INFO frame__34_80 = {1, {"parameter"}};
static void cont__34_81(void);
static void cont__34_82(void);
static NODE *string__34_83;
static void cont__34_84(void);
static NODE *func__34_85;
static void entry__34_85(void);
static FRAME_INFO frame__34_85 = {1, {"parameter"}};
static void cont__34_86(void);
static NODE *func__34_87;
static void entry__34_87(void);
static FRAME_INFO frame__34_87 = {1, {"parameter"}};
static void cont__34_88(void);
static void cont__34_89(void);
static NODE *string__34_90;
static void cont__34_91(void);
static NODE *func__34_92;
static void entry__34_92(void);
static FRAME_INFO frame__34_92 = {1, {"parameter"}};
static void cont__34_93(void);
static NODE *func__34_94;
static void entry__34_94(void);
static FRAME_INFO frame__34_94 = {1, {"parameter"}};
static void cont__34_95(void);
static void cont__34_96(void);
static void cont__34_97(void);
static void cont__34_98(void);
static NODE *string__34_99;
static NODE *string__34_100;
static void cont__34_101(void);
static void cont__34_102(void);
static void cont__34_103(void);
static void cont__34_104(void);
static void cont__34_105(void);
static void cont__34_106(void);
static NODE *func__34_107;
static void entry__34_107(void);
static FRAME_INFO frame__34_107 = {2, {"paragraph", "return_values"}};
static void cont__34_108(void);
static NODE *string__34_109;
static void cont__34_110(void);
static void cont__34_111(void);
static NODE *func__34_112;
static void entry__34_112(void);
static FRAME_INFO frame__34_112 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__34_113(void);
static NODE *func__34_114;
static void entry__34_114(void);
static FRAME_INFO frame__34_114 = {1, {"return_value"}};
static void cont__34_115(void);
static NODE *func__34_116;
static void entry__34_116(void);
static FRAME_INFO frame__34_116 = {1, {"return_value"}};
static void cont__34_117(void);
static void cont__34_118(void);
static void cont__34_119(void);
static NODE *func__34_120;
static void entry__34_120(void);
static FRAME_INFO frame__34_120 = {1, {"return_value"}};
static void cont__34_121(void);
static NODE *func__34_122;
static void entry__34_122(void);
static FRAME_INFO frame__34_122 = {1, {"return_value"}};
static void cont__34_123(void);
static void cont__34_124(void);
static void cont__34_125(void);
static void cont__34_126(void);
static void cont__34_127(void);
static void cont__34_128(void);
static void cont__34_129(void);
static void cont__34_130(void);
static NODE *func__34_131;
static void entry__34_131(void);
static FRAME_INFO frame__34_131 = {2, {"paragraph", "references"}};
static NODE *string__34_132;
static void cont__34_133(void);
static NODE *func__34_134;
static void entry__34_134(void);
static FRAME_INFO frame__34_134 = {2, {"paragraph", "references"}};
static void cont__34_135(void);
static void cont__34_136(void);
static NODE *func__34_137;
static void entry__34_137(void);
static FRAME_INFO frame__34_137 = {2, {"reference", "references"}};
static void cont__34_138(void);
static void cont__34_139(void);
static NODE *func__34_140;
static void entry__34_140(void);
static FRAME_INFO frame__34_140 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__34_141(void);
static NODE *func__34_142;
static void entry__34_142(void);
static FRAME_INFO frame__34_142 = {3, {"paragraph", "topic_list", "function_name"}};
static void cont__34_143(void);
static void cont__34_144(void);
static NODE *func__34_145;
static void entry__34_145(void);
static FRAME_INFO frame__34_145 = {4, {"topic", "topic_list", "function_name", "topic_contents"}};
static void cont__34_146(void);
static void cont__34_147(void);
static void cont__34_148(void);
static void cont__34_149(void);
static void cont__34_150(void);
static void cont__34_151(void);
static NODE *func__34_152;
static void entry__34_152(void);
static FRAME_INFO frame__34_152 = {2, {"paragraph", "examples"}};
static void cont__34_153(void);
static NODE *func__34_154;
static void entry__34_154(void);
static FRAME_INFO frame__34_154 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__34_155(void);
static void cont__34_156(void);
static void cont__34_157(void);
static void cont__34_158(void);
static void cont__34_159(void);
static void cont__34_160(void);
static NODE *func__34_161;
static void entry__34_161(void);
static FRAME_INFO frame__34_161 = {2, {"paragraph", "technical_details"}};
static NODE *string__34_162;
static void cont__34_163(void);
static NODE *func__34_164;
static void entry__34_164(void);
static FRAME_INFO frame__34_164 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__34_165(void);
static void cont__34_166(void);
static void cont__34_167(void);
static NODE *func__34_168;
static void entry__34_168(void);
static FRAME_INFO frame__34_168 = {1, {"technical_details"}};
static NODE *func__34_169;
static void entry__34_169(void);
static FRAME_INFO frame__34_169 = {2, {"technical_details", "detail"}};
static void cont__34_170(void);
static NODE *func__34_171;
static void entry__34_171(void);
static FRAME_INFO frame__34_171 = {5, {"paragraph", "resolve_reference", "short_description", "technical_details", "descriptions"}};
static void cont__34_172(void);
static void cont__34_173(void);
static void cont__34_174(void);
static NODE *func__34_175;
static void entry__34_175(void);
static FRAME_INFO frame__34_175 = {2, {"reference", "resolve_reference"}};
static void cont__34_176(void);
static void cont__34_177(void);
static void cont__34_178(void);
static void cont__34_179(void);
static NODE *string__34_180;
static void cont__34_181(void);
static void cont__34_182(void);
static void cont__34_183(void);
static void cont__34_184(void);
static NODE *func__34_185;
static void entry__34_185(void);
static FRAME_INFO frame__34_185 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__34_186(void);
static NODE *func__34_187;
static void entry__34_187(void);
static FRAME_INFO frame__34_187 = {2, {"technical_details", "paragraph"}};
static void cont__34_188(void);
static NODE *func__34_189;
static void entry__34_189(void);
static FRAME_INFO frame__34_189 = {2, {"descriptions", "paragraph"}};
static void cont__34_190(void);
static NODE *func__34_191;
static void entry__34_191(void);
static FRAME_INFO frame__34_191 = {2, {"short_description", "paragraph"}};
static void cont__34_192(void);
static void cont__34_193(void);
static void cont__34_194(void);
static NODE *func__34_195;
static void entry__34_195(void);
static FRAME_INFO frame__34_195 = {2, {"info", "parameters"}};
static void cont__34_196(void);
static NODE *func__34_197;
static void entry__34_197(void);
static FRAME_INFO frame__34_197 = {2, {"parameter", "parameters"}};
static void cont__34_198(void);
static void cont__34_199(void);
static NODE *func__34_200;
static void entry__34_200(void);
static FRAME_INFO frame__34_200 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__34_201(void);
static void cont__34_202(void);
static void cont__34_203(void);
static NODE *func__34_204;
static void entry__34_204(void);
static FRAME_INFO frame__34_204 = {2, {"parameter", "name"}};
static void cont__34_205(void);
static NODE *func__34_206;
static void entry__34_206(void);
static FRAME_INFO frame__34_206 = {2, {"parameter", "name"}};
static void cont__34_207(void);
static void cont__34_208(void);
static NODE *func__34_209;
static void entry__34_209(void);
static FRAME_INFO frame__34_209 = {2, {"name", "parameter"}};
static void cont__34_210(void);
static void cont__34_211(void);
static void cont__34_212(void);
static NODE *func__34_213;
static void entry__34_213(void);
static FRAME_INFO frame__34_213 = {1, {"name"}};
static void cont__34_214(void);
static NODE *func__34_215;
static void entry__34_215(void);
static FRAME_INFO frame__34_215 = {2, {"parameter", "name"}};
static void cont__34_216(void);
static NODE *func__34_217;
static void entry__34_217(void);
static FRAME_INFO frame__34_217 = {1, {"name"}};
static void cont__34_218(void);
static void cont__34_219(void);
static void cont__34_220(void);
static void cont__34_221(void);
static void cont__34_222(void);
static NODE *func__34_223;
static void entry__34_223(void);
static FRAME_INFO frame__34_223 = {1, {"parameter"}};
static void cont__34_224(void);
static void cont__34_225(void);
static void cont__34_226(void);
static NODE *func__34_227;
static void entry__34_227(void);
static FRAME_INFO frame__34_227 = {0, {}};
static void cont__34_228(void);
static void cont__34_229(void);
static void cont__34_230(void);
static NODE *func__34_231;
static void entry__34_231(void);
static FRAME_INFO frame__34_231 = {0, {}};
static void cont__34_232(void);
static void cont__34_233(void);
static NODE *func__34_234;
static void entry__34_234(void);
static FRAME_INFO frame__34_234 = {1, {"short_description"}};
static void cont__34_235(void);
static void cont__34_236(void);
static NODE *func__34_237;
static void entry__34_237(void);
static FRAME_INFO frame__34_237 = {1, {"parameters"}};
static NODE *string__34_238;
static void cont__34_239(void);
static NODE *func__34_240;
static void entry__34_240(void);
static FRAME_INFO frame__34_240 = {1, {"parameters"}};
static NODE *func__34_241;
static void entry__34_241(void);
static FRAME_INFO frame__34_241 = {1, {"parameter"}};
static void cont__34_242(void);
static void cont__34_243(void);
static NODE *func__34_244;
static void entry__34_244(void);
static FRAME_INFO frame__34_244 = {1, {"parameter"}};
static void cont__34_245(void);
static void cont__34_246(void);
static void cont__34_247(void);
static NODE *func__34_248;
static void entry__34_248(void);
static FRAME_INFO frame__34_248 = {1, {"return_values"}};
static void cont__34_249(void);
static NODE *func__34_250;
static void entry__34_250(void);
static FRAME_INFO frame__34_250 = {1, {"return_values"}};
static NODE *func__34_251;
static void entry__34_251(void);
static FRAME_INFO frame__34_251 = {1, {"return_value"}};
static void cont__34_252(void);
static void cont__34_253(void);
static NODE *func__34_254;
static void entry__34_254(void);
static FRAME_INFO frame__34_254 = {1, {"return_value"}};
static void cont__34_255(void);
static void cont__34_256(void);
static void cont__34_257(void);
static NODE *func__34_258;
static void entry__34_258(void);
static FRAME_INFO frame__34_258 = {1, {"descriptions"}};
static NODE *string__34_259;
static void cont__34_260(void);
static NODE *func__34_261;
static void entry__34_261(void);
static FRAME_INFO frame__34_261 = {1, {"description"}};
static void cont__34_262(void);
static void cont__34_263(void);
static NODE *func__34_264;
static void entry__34_264(void);
static FRAME_INFO frame__34_264 = {1, {"technical_details"}};
static NODE *string__34_265;
static void cont__34_266(void);
static NODE *func__34_267;
static void entry__34_267(void);
static FRAME_INFO frame__34_267 = {1, {"detail"}};
static void cont__34_268(void);
static void cont__34_269(void);
static NODE *func__34_270;
static void entry__34_270(void);
static FRAME_INFO frame__34_270 = {2, {"references", "resolve_reference"}};
static NODE *string__34_271;
static void cont__34_272(void);
static NODE *func__34_273;
static void entry__34_273(void);
static FRAME_INFO frame__34_273 = {2, {"references", "resolve_reference"}};
static NODE *func__34_274;
static void entry__34_274(void);
static FRAME_INFO frame__34_274 = {2, {"reference", "resolve_reference"}};
static void cont__34_275(void);
static NODE *func__34_276;
static void entry__34_276(void);
static FRAME_INFO frame__34_276 = {1, {"reference"}};
static NODE *func__34_277;
static void entry__34_277(void);
static FRAME_INFO frame__34_277 = {1, {"reference"}};
static void cont__34_278(void);
static void cont__34_279(void);
static void cont__34_280(void);
static void cont__34_281(void);
static NODE *string__34_282;
static void cont__34_283(void);
static void cont__34_284(void);
static void cont__34_285(void);
static void cont__34_286(void);
static void cont__34_287(void);
static NODE *func__34_288;
static void entry__34_288(void);
static FRAME_INFO frame__34_288 = {2, {"info", "function_name"}};
static NODE *string__34_289;
static void cont__34_290(void);
static NODE *func__34_291;
static void entry__34_291(void);
static FRAME_INFO frame__34_291 = {2, {"info", "function_name"}};
static void cont__34_292(void);
static NODE *func__34_293;
static void entry__34_293(void);
static FRAME_INFO frame__34_293 = {3, {"name", "function_name", "method"}};
static void cont__34_294(void);
static NODE *func__34_295;
static void entry__34_295(void);
static FRAME_INFO frame__34_295 = {2, {"name", "method"}};
static NODE *func__34_296;
static void entry__34_296(void);
static FRAME_INFO frame__34_296 = {1, {"name"}};
static void cont__34_297(void);
static void cont__34_298(void);
static void cont__34_299(void);
static void cont__34_300(void);
static NODE *string__34_301;
static void cont__34_302(void);
static NODE *func__34_303;
static void entry__34_303(void);
static FRAME_INFO frame__34_303 = {1, {"method"}};
static void cont__34_304(void);
static void cont__34_305(void);
static void cont__34_306(void);
static void cont__34_307(void);
static void cont__34_308(void);
static void cont__34_309(void);
static NODE *func__34_310;
static void entry__34_310(void);
static FRAME_INFO frame__34_310 = {2, {"info", "function_name"}};
static NODE *string__34_311;
static void cont__34_312(void);
static NODE *func__34_313;
static void entry__34_313(void);
static FRAME_INFO frame__34_313 = {2, {"info", "function_name"}};
static void cont__34_314(void);
static NODE *func__34_315;
static void entry__34_315(void);
static FRAME_INFO frame__34_315 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__34_316;
static void entry__34_316(void);
static FRAME_INFO frame__34_316 = {2, {"method_name", "function_name"}};
static NODE *func__34_317;
static void entry__34_317(void);
static FRAME_INFO frame__34_317 = {1, {"method_name"}};
static void cont__34_318(void);
static void cont__34_319(void);
static void cont__34_320(void);
static void cont__34_321(void);
static void cont__34_322(void);
static NODE *func__34_323;
static void entry__34_323(void);
static FRAME_INFO frame__34_323 = {2, {"function_name", "method_name"}};
static void cont__34_324(void);
static void cont__34_325(void);
static void cont__34_326(void);
static void cont__34_327(void);
static void cont__34_328(void);
static void cont__34_329(void);
static void cont__34_330(void);
static void cont__34_331(void);
static NODE *func__34_332;
static void entry__34_332(void);
static FRAME_INFO frame__34_332 = {1, {"topic_list"}};
static NODE *string__34_333;
static void cont__34_334(void);
static NODE *func__34_335;
static void entry__34_335(void);
static FRAME_INFO frame__34_335 = {1, {"topic_list"}};
static NODE *func__34_336;
static void entry__34_336(void);
static FRAME_INFO frame__34_336 = {2, {"topic", "filename"}};
static void cont__34_337(void);
static NODE *string__34_338;
static void cont__34_339(void);
static void cont__34_340(void);
static void cont__34_341(void);
static NODE *func__34_342;
static void entry__34_342(void);
static FRAME_INFO frame__34_342 = {2, {"filename", "topic"}};
static NODE *func__34_343;
static void entry__34_343(void);
static FRAME_INFO frame__34_343 = {2, {"filename", "topic"}};
static void cont__34_344(void);
static void cont__34_345(void);
static NODE *func__34_346;
static void entry__34_346(void);
static FRAME_INFO frame__34_346 = {4, {"example", "function_basename", "title", "text"}};
static void cont__34_347(void);
static void cont__34_348(void);
static void cont__34_349(void);
static void cont__34_350(void);
static void cont__34_351(void);
static NODE *string__34_352;
static void cont__34_353(void);
static NODE *func__34_354;
static void entry__34_354(void);
static FRAME_INFO frame__34_354 = {2, {"text", "function_basename"}};
static void cont__34_355(void);
static void cont__34_356(void);
static void cont__34_357(void);
static void cont__34_358(void);
static NODE *func__34_359;
static void entry__34_359(void);
static FRAME_INFO frame__34_359 = {1, {"string_literal"}};
static void cont__34_360(void);
static NODE *string__34_361;
static void cont__34_362(void);
static void cont__34_363(void);
static void cont__34_364(void);
static void cont__34_365(void);
static NODE *string__34_366;
static void cont__34_367(void);
static void cont__34_368(void);
static void cont__34_369(void);
static NODE *string__34_370;
static NODE *string__34_371;
static void cont__34_372(void);
static NODE *func__35_1_get_short_description;
static void entry__35_1_get_short_description(void);
static FRAME_INFO frame__35_1_get_short_description = {4, {"name", "info", "remark_lines", "short_description"}};
static void cont__35_2(void);
static void cont__35_3(void);
static NODE *func__35_4;
static void entry__35_4(void);
static FRAME_INFO frame__35_4 = {1, {"remark_lines"}};
static void cont__35_5(void);
static void cont__35_6(void);
static void cont__35_7(void);
static NODE *func__35_8;
static void entry__35_8(void);
static FRAME_INFO frame__35_8 = {4, {"remark_lines", "short_description", "name", "info"}};
static NODE *func__35_9;
static void entry__35_9(void);
static FRAME_INFO frame__35_9 = {3, {"break", "remark_lines", "short_description"}};
static NODE *func__35_10;
static void entry__35_10(void);
static FRAME_INFO frame__35_10 = {3, {"line", "short_description", "break"}};
static void cont__35_11(void);
static NODE *func__35_12;
static void entry__35_12(void);
static FRAME_INFO frame__35_12 = {1, {"short_description"}};
static void cont__35_13(void);
static void cont__35_14(void);
static void cont__35_15(void);
static void cont__35_16(void);
static void cont__35_17(void);
static void cont__35_18(void);
static void cont__35_19(void);
static void cont__35_20(void);
static NODE *func__35_21;
static void entry__35_21(void);
static FRAME_INFO frame__35_21 = {1, {"short_description"}};
static void cont__35_22(void);
static void cont__35_23(void);
static void cont__35_24(void);
static NODE *func__35_25;
static void entry__35_25(void);
static FRAME_INFO frame__35_25 = {3, {"name", "info", "short_description"}};
static void cont__35_26(void);
static NODE *string__35_27;
static NODE *string__35_28;
static void cont__35_29(void);
static void cont__35_30(void);
static NODE *func__36_1_sim2c__extract_documentation;
static void entry__36_1_sim2c__extract_documentation(void);
static FRAME_INFO frame__36_1_sim2c__extract_documentation = {1, {"path"}};
static void cont__36_2(void);
static void cont__36_3(void);
static void cont__36_4(void);
static NODE *func__36_5;
static void entry__36_5(void);
static FRAME_INFO frame__36_5 = {3, {"iname", "info", "name"}};
static void cont__36_6(void);
static void cont__36_7(void);
static void cont__36_8(void);
static void cont__36_9(void);
static void cont__36_10(void);
static NODE *func__36_11;
static void entry__36_11(void);
static FRAME_INFO frame__36_11 = {5, {"info", "iname", "name", "base", "methods"}};
static void cont__36_12(void);
static void cont__36_13(void);
static NODE *func__36_14;
static void entry__36_14(void);
static FRAME_INFO frame__36_14 = {2, {"base", "iname"}};
static void cont__36_15(void);
static void cont__36_16(void);
static NODE *func__36_17;
static void entry__36_17(void);
static FRAME_INFO frame__36_17 = {6, {"method_name", "method_info", "name", "methods", "sd_name", "oname"}};
static void cont__36_18(void);
static NODE *func__36_19;
static void entry__36_19(void);
static FRAME_INFO frame__36_19 = {2, {"method_name", "method_info"}};
static void cont__36_20(void);
static void cont__36_21(void);
static void cont__36_22(void);
static NODE *string__36_23;
static void cont__36_24(void);
static void cont__36_25(void);
static void cont__36_26(void);
static void cont__36_27(void);
static void cont__36_28(void);
static void cont__36_29(void);
static void cont__36_30(void);
static void cont__36_31(void);
static void cont__36_32(void);
static void cont__36_33(void);
static void cont__36_34(void);
static void cont__36_35(void);
static void cont__36_36(void);
static void cont__36_37(void);
static void cont__36_38(void);
static NODE *string__36_39;
static NODE *func__36_40;
static void entry__36_40(void);
static FRAME_INFO frame__36_40 = {1, {"print_type_info"}};
static NODE *func__36_41_print_type_info;
static void entry__36_41_print_type_info(void);
static FRAME_INFO frame__36_41_print_type_info = {3, {"info", "indent", "print_type_info"}};
static NODE *func__36_42;
static void entry__36_42(void);
static FRAME_INFO frame__36_42 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__36_43(void);
static void cont__36_44(void);
static void cont__36_45(void);
static NODE *func__36_46;
static void entry__36_46(void);
static FRAME_INFO frame__36_46 = {2, {"indent", "qname"}};
static NODE *func__36_47;
static void entry__36_47(void);
static FRAME_INFO frame__36_47 = {2, {"indent", "qname"}};
static void cont__36_48(void);
static void cont__36_49(void);
static void cont__36_50(void);
static void cont__36_51(void);
static void cont__36_52(void);
static void cont__36_53(void);
static void cont__36_54(void);
static NODE *func__36_55;
static void entry__36_55(void);
static FRAME_INFO frame__36_55 = {1, {"remark_lines"}};
static void cont__36_56(void);
static void cont__36_57(void);
static void cont__36_58(void);
static NODE *func__36_59;
static void entry__36_59(void);
static FRAME_INFO frame__36_59 = {1, {"remark_lines"}};
static void cont__36_60(void);
static void cont__36_61(void);
static void cont__36_62(void);
static void cont__36_63(void);
static NODE *func__36_64;
static void entry__36_64(void);
static FRAME_INFO frame__36_64 = {3, {"name", "print_type_info", "indent"}};
static void cont__36_65(void);
static void cont__36_66(void);
static void cont__36_67(void);
static void cont__36_68(void);
static NODE *func__36_69;
static void entry__36_69(void);
static FRAME_INFO frame__36_69 = {1, {"print_type_info"}};
static NODE *func__36_70;
static void entry__36_70(void);
static FRAME_INFO frame__36_70 = {3, {"base", "info", "print_type_info"}};
static void cont__36_71(void);
static void cont__36_72(void);
static NODE *func__36_73;
static void entry__36_73(void);
static FRAME_INFO frame__36_73 = {1, {"info"}};
static void cont__36_74(void);
static void cont__36_75(void);
static void cont__36_76(void);
static NODE *func__36_77;
static void entry__36_77(void);
static FRAME_INFO frame__36_77 = {2, {"print_type_info", "info"}};
static void cont__36_78(void);
static NODE *string__36_79;
static NODE *func__36_80;
static void entry__36_80(void);
static FRAME_INFO frame__36_80 = {0, {}};
static void cont__36_81(void);
static NODE *string__36_82;
static NODE *string__36_83;
static void cont__36_84(void);
static void cont__36_85(void);
static NODE *func__36_86;
static void entry__36_86(void);
static FRAME_INFO frame__36_86 = {1, {"letter"}};
static NODE *string__36_87;
static void cont__36_88(void);
static void cont__36_89(void);
static void cont__36_90(void);
static NODE *func__36_91;
static void entry__36_91(void);
static FRAME_INFO frame__36_91 = {0, {}};
static NODE *string__36_92;
static void cont__36_93(void);
static void cont__36_94(void);
static NODE *func__36_95;
static void entry__36_95(void);
static FRAME_INFO frame__36_95 = {1, {"letter"}};
static NODE *func__36_96;
static void entry__36_96(void);
static FRAME_INFO frame__36_96 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__36_97(void);
static void cont__36_98(void);
static void cont__36_99(void);
static NODE *func__36_100;
static void entry__36_100(void);
static FRAME_INFO frame__36_100 = {2, {"letter", "iname"}};
static void cont__36_101(void);
static NODE *func__36_102;
static void entry__36_102(void);
static FRAME_INFO frame__36_102 = {1, {"letter"}};
static NODE *string__36_103;
static void cont__36_104(void);
static NODE *func__36_105;
static void entry__36_105(void);
static FRAME_INFO frame__36_105 = {1, {"letter"}};
static void cont__36_106(void);
static NODE *func__36_107;
static void entry__36_107(void);
static FRAME_INFO frame__36_107 = {1, {"letter"}};
static void cont__36_108(void);
static void cont__36_109(void);
static NODE *string__36_110;
static void cont__36_111(void);
static NODE *string__36_112;
static void cont__36_113(void);
static void cont__36_114(void);
static void cont__36_115(void);
static void cont__36_116(void);
static NODE *func__36_117;
static void entry__36_117(void);
static FRAME_INFO frame__36_117 = {1, {"remark_lines"}};
static void cont__36_118(void);
static void cont__36_119(void);
static void cont__36_120(void);
static NODE *func__36_121;
static void entry__36_121(void);
static FRAME_INFO frame__36_121 = {2, {"remark", "remark_lines"}};
static void cont__36_122(void);
static void cont__36_123(void);
static void cont__36_124(void);
static void cont__36_125(void);
static NODE *func__36_126;
static void entry__36_126(void);
static FRAME_INFO frame__36_126 = {0, {}};
static NODE *string__36_127;
static NODE *func__36_128;
static void entry__36_128(void);
static FRAME_INFO frame__36_128 = {0, {}};
static NODE *string__36_129;
static NODE *func__36_130;
static void entry__36_130(void);
static FRAME_INFO frame__36_130 = {0, {}};
static NODE *string__36_131;
static NODE *func__36_132;
static void entry__36_132(void);
static FRAME_INFO frame__36_132 = {0, {}};
static NODE *string__36_133;
static NODE *func__36_134;
static void entry__36_134(void);
static FRAME_INFO frame__36_134 = {0, {}};
static NODE *string__36_135;
static NODE *func__36_136;
static void entry__36_136(void);
static FRAME_INFO frame__36_136 = {0, {}};
static NODE *string__36_137;
static NODE *func__36_138;
static void entry__36_138(void);
static FRAME_INFO frame__36_138 = {0, {}};
static NODE *string__36_139;
static NODE *func__36_140;
static void entry__36_140(void);
static FRAME_INFO frame__36_140 = {0, {}};
static void cont__36_141(void);
static void cont__36_142(void);
static NODE *func__36_143;
static void entry__36_143(void);
static FRAME_INFO frame__36_143 = {2, {"remark", "kind_info"}};
static void cont__36_144(void);
static NODE *func__36_145;
static void entry__36_145(void);
static FRAME_INFO frame__36_145 = {2, {"remark", "kind_info"}};
static NODE *string__36_146;
static void cont__36_147(void);
static NODE *func__36_148;
static void entry__36_148(void);
static FRAME_INFO frame__36_148 = {2, {"remark", "kind_info"}};
static void cont__36_149(void);
static void cont__36_150(void);
static NODE *func__36_151;
static void entry__36_151(void);
static FRAME_INFO frame__36_151 = {1, {"name"}};
static void cont__36_152(void);
static void cont__36_153(void);
static NODE *func__36_154;
static void entry__36_154(void);
static FRAME_INFO frame__36_154 = {2, {"name", "remark"}};
static NODE *func__36_155;
static void entry__36_155(void);
static FRAME_INFO frame__36_155 = {2, {"name", "remark"}};
static NODE *string__36_156;
static NODE *string__36_157;
static void cont__36_158(void);
static void cont__36_159(void);
static void cont__36_160(void);
static NODE *func__36_161;
static void entry__36_161(void);
static FRAME_INFO frame__36_161 = {1, {"name"}};
static void cont__36_162(void);
static void cont__36_163(void);
static void cont__36_164(void);
static void cont__36_165(void);
static void cont__36_166(void);
static NODE *string__36_167;
static void cont__36_168(void);
static void cont__36_169(void);
static NODE *func__36_170;
static void entry__36_170(void);
static FRAME_INFO frame__36_170 = {3, {"iname", "info", "name"}};
static void cont__36_171(void);
static void cont__36_172(void);
static void cont__36_173(void);
static NODE *func__36_174;
static void entry__36_174(void);
static FRAME_INFO frame__36_174 = {2, {"info", "name"}};
static void cont__36_175(void);
static NODE *func__36_176;
static void entry__36_176(void);
static FRAME_INFO frame__36_176 = {3, {"method_name", "method_info", "name"}};
static void cont__36_177(void);
static void cont__36_178(void);
static NODE *string__36_179;
static NODE *func__36_180;
static void entry__36_180(void);
static FRAME_INFO frame__36_180 = {0, {}};
static void cont__36_181(void);
static void cont__36_182(void);
static void cont__36_183(void);
static NODE *func__36_184;
static void entry__36_184(void);
static FRAME_INFO frame__36_184 = {0, {}};
static NODE *func__36_185;
static void entry__36_185(void);
static FRAME_INFO frame__36_185 = {3, {"topic", "references", "filename"}};
static void cont__36_186(void);
static void cont__36_187(void);
static void cont__36_188(void);
static void cont__36_189(void);
static NODE *func__36_190;
static void entry__36_190(void);
static FRAME_INFO frame__36_190 = {2, {"filename", "topic"}};
static NODE *func__36_191;
static void entry__36_191(void);
static FRAME_INFO frame__36_191 = {2, {"filename", "topic"}};
static void cont__36_192(void);
static void cont__36_193(void);
static NODE *func__36_194;
static void entry__36_194(void);
static FRAME_INFO frame__36_194 = {3, {"topic", "references", "filename"}};
static void cont__36_195(void);
static void cont__36_196(void);
static void cont__36_197(void);
static void cont__36_198(void);
static NODE *func__36_199;
static void entry__36_199(void);
static FRAME_INFO frame__36_199 = {2, {"topic", "references"}};
static void cont__36_200(void);
static void cont__36_201(void);
static void cont__36_202(void);
static NODE *func__36_203;
static void entry__36_203(void);
static FRAME_INFO frame__36_203 = {1, {"references"}};
static NODE *func__36_204;
static void entry__36_204(void);
static FRAME_INFO frame__36_204 = {1, {"reference"}};
static NODE *func__36_205;
static void entry__36_205(void);
static FRAME_INFO frame__36_205 = {1, {"reference"}};
static NODE *func__36_206;
static void entry__36_206(void);
static FRAME_INFO frame__36_206 = {1, {"reference"}};
static void cont__36_207(void);
static void cont__36_208(void);
static void cont__36_209(void);
static void cont__36_210(void);
static void cont__36_211(void);
static void cont__36_212(void);
static void cont__36_213(void);
static NODE *string__36_214;
static NODE *func__36_215;
static void entry__36_215(void);
static FRAME_INFO frame__36_215 = {0, {}};
static NODE *string__36_216;
static void cont__36_217(void);
static NODE *func__36_218;
static void entry__36_218(void);
static FRAME_INFO frame__36_218 = {0, {}};
static void cont__36_219(void);
static void cont__36_220(void);
static NODE *func__36_221;
static void entry__36_221(void);
static FRAME_INFO frame__36_221 = {0, {}};
static void cont__36_222(void);
static void cont__36_223(void);
static NODE *func__36_224;
static void entry__36_224(void);
static FRAME_INFO frame__36_224 = {0, {}};
static void cont__36_225(void);
static void cont__36_226(void);
static NODE *func__36_227;
static void entry__36_227(void);
static FRAME_INFO frame__36_227 = {0, {}};
static void cont__36_228(void);
static void cont__36_229(void);
static NODE *func__36_230;
static void entry__36_230(void);
static FRAME_INFO frame__36_230 = {14, {"total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_methods", "total_inline_c_methods", "total_inline_c_types", "total_inline_c_objects", "total_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "total_variables", "other", "total_definitions"}};
static NODE *func__36_231;
static void entry__36_231(void);
static FRAME_INFO frame__36_231 = {15, {"iname", "info", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_inline_c_functions", "total_inline_c_types", "total_inline_c_objects", "total_unique_items", "total_constants", "total_variables", "other", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__36_232(void);
static NODE *func__36_233;
static void entry__36_233(void);
static FRAME_INFO frame__36_233 = {1, {"total_functions"}};
static void cont__36_234(void);
static NODE *func__36_235;
static void entry__36_235(void);
static FRAME_INFO frame__36_235 = {1, {"total_polymorphic_functions"}};
static void cont__36_236(void);
static NODE *func__36_237;
static void entry__36_237(void);
static FRAME_INFO frame__36_237 = {1, {"total_polymorphic_attributes"}};
static void cont__36_238(void);
static NODE *func__36_239;
static void entry__36_239(void);
static FRAME_INFO frame__36_239 = {1, {"total_inline_c_functions"}};
static void cont__36_240(void);
static NODE *func__36_241;
static void entry__36_241(void);
static FRAME_INFO frame__36_241 = {1, {"total_inline_c_types"}};
static void cont__36_242(void);
static NODE *func__36_243;
static void entry__36_243(void);
static FRAME_INFO frame__36_243 = {1, {"total_inline_c_objects"}};
static void cont__36_244(void);
static NODE *func__36_245;
static void entry__36_245(void);
static FRAME_INFO frame__36_245 = {1, {"total_unique_items"}};
static void cont__36_246(void);
static NODE *func__36_247;
static void entry__36_247(void);
static FRAME_INFO frame__36_247 = {1, {"total_constants"}};
static void cont__36_248(void);
static NODE *func__36_249;
static void entry__36_249(void);
static FRAME_INFO frame__36_249 = {1, {"total_variables"}};
static void cont__36_250(void);
static NODE *func__36_251;
static void entry__36_251(void);
static FRAME_INFO frame__36_251 = {1, {"other"}};
static void cont__36_252(void);
static void cont__36_253(void);
static void cont__36_254(void);
static NODE *func__36_255;
static void entry__36_255(void);
static FRAME_INFO frame__36_255 = {4, {"info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__36_256(void);
static NODE *func__36_257;
static void entry__36_257(void);
static FRAME_INFO frame__36_257 = {5, {"method_name", "method_info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__36_258(void);
static NODE *func__36_259;
static void entry__36_259(void);
static FRAME_INFO frame__36_259 = {1, {"total_methods"}};
static void cont__36_260(void);
static NODE *func__36_261;
static void entry__36_261(void);
static FRAME_INFO frame__36_261 = {1, {"total_inline_c_methods"}};
static void cont__36_262(void);
static NODE *func__36_263;
static void entry__36_263(void);
static FRAME_INFO frame__36_263 = {1, {"total_attributes"}};
static void cont__36_264(void);
static void cont__36_265(void);
static void cont__36_266(void);
static void cont__36_267(void);
static void cont__36_268(void);
static void cont__36_269(void);
static void cont__36_270(void);
static void cont__36_271(void);
static void cont__36_272(void);
static void cont__36_273(void);
static void cont__36_274(void);
static void cont__36_275(void);
static void cont__36_276(void);
static void cont__36_277(void);
static void cont__36_278(void);
static void cont__36_279(void);
static void cont__36_280(void);
static void cont__36_281(void);
static void cont__36_282(void);
static void cont__36_283(void);
static void cont__36_284(void);
static void cont__36_285(void);
static void cont__36_286(void);
static void cont__36_287(void);
static void cont__36_288(void);
static void cont__36_289(void);
static void cont__36_290(void);
static NODE *string__36_291;
static NODE *string__36_292;
static NODE *string__36_293;
static NODE *string__36_294;
static NODE *string__36_295;
static NODE *string__36_296;
static NODE *string__36_297;
static NODE *string__36_298;
static NODE *string__36_299;
static NODE *string__36_300;
static NODE *string__36_301;
static NODE *string__36_302;
static NODE *string__36_303;
static NODE *string__36_304;
static void cont__36_305(void);
static NODE *get__sim2c__extract_documentation(void) {
  return var.sim2c__extract_documentation;
}
static void cont__42_1(void);
static void cont__56_1(void);
static void cont__56_2(void);
static void cont__56_3(void);
static void cont__56_4(void);
static void cont__56_5(void);
static void cont__56_6(void);
static void cont__56_7(void);
static NODE *string__67_1;
static void cont__67_2(void);
static void cont__67_3(void);
static NODE *string__68_1;
static NODE *string__68_2;
static void cont__68_3(void);
static void cont__68_4(void);
static void cont__68_5(void);
static void cont__68_6(void);
static void cont__68_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__42_1, NULL, 62, 62, 15, 55},
  {cont__56_1, NULL, 62, 62, 7, 56},
  {cont__56_2, NULL, 63, 63, 12, 31},
  {cont__56_3, NULL, 63, 63, 12, 46},
  {cont__56_4, NULL, 63, 63, 7, 47},
  {cont__56_5, NULL, 61, 63, 5, 46},
  {cont__56_6, NULL, 57, 63, 1, 49},
  {cont__56_7, NULL, 373, 373, 8, 28},
  {cont__67_2, NULL, 373, 373, 1, 33},
  {cont__67_3, NULL, 374, 374, 10, 32},
  {cont__68_3, NULL, 374, 374, 40, 59},
  {cont__68_4, NULL, 374, 374, 40, 74},
  {cont__68_5, NULL, 374, 374, 35, 75},
  {cont__68_6, NULL, 374, 374, 1, 80},
  {cont__68_7, NULL, },
  {entry__22_4, NULL, 73, 151, 9, 11},
  {entry__22_3, NULL, 72, 151, 7, 12},
  {cont__22_6, &frame__22_3, 152, 152, 7, 15},
  {entry__22_2, NULL, 71, 152, 5, 15},
  {entry__22_1_create_page, NULL, 70, 152, 3, 16},
  {cont__22_7, &frame__22_1_create_page, 153, 153, 3, 20},
  {entry__24_10, NULL, 168, 168, 27, 52},
  {entry__24_16, NULL, 169, 169, 21, 63},
  {entry__24_23, NULL, 170, 170, 26, 71},
  {entry__24_32, NULL, 184, 184, 39, 56},
  {cont__24_33, &frame__24_32, 184, 184, 56, 56},
  {entry__24_39, NULL, 192, 192, 11, 42},
  {cont__24_40, &frame__24_39, 192, 192, 42, 42},
  {entry__24_41, NULL, 194, 194, 11, 26},
  {cont__24_42, &frame__24_41, 195, 195, 11, 48},
  {cont__24_43, &frame__24_41, 195, 195, 48, 48},
  {entry__24_44, NULL, 197, 197, 11, 14},
  {entry__24_36, NULL, 190, 190, 9, 27},
  {cont__24_37, &frame__24_36, 190, 190, 9, 30},
  {cont__24_38, &frame__24_36, 189, 197, 7, 15},
  {entry__24_35, NULL, 188, 197, 5, 16},
  {cont__24_45, &frame__24_35, 197, 197, 16, 16},
  {entry__24_49, NULL, 199, 199, 46, 70},
  {cont__24_50, &frame__24_49, 199, 199, 34, 70},
  {cont__24_51, &frame__24_49, 199, 199, 70, 70},
  {entry__24_54, NULL, 200, 200, 32, 54},
  {cont__24_56, &frame__24_54, 200, 200, 59, 59},
  {entry__24_61, NULL, 203, 203, 37, 40},
  {entry__24_59, NULL, 203, 203, 14, 34},
  {cont__24_60, &frame__24_59, 203, 203, 11, 40},
  {entry__24_64, NULL, 203, 203, 68, 71},
  {entry__24_62, NULL, 203, 203, 47, 65},
  {cont__24_63, &frame__24_62, 203, 203, 44, 71},
  {entry__24_79, NULL, 210, 210, 41, 66},
  {cont__24_80, &frame__24_79, 210, 210, 33, 67},
  {cont__24_81, &frame__24_79, 210, 210, 13, 68},
  {cont__24_82, &frame__24_79, 210, 210, 73, 73},
  {entry__24_75, NULL, 208, 208, 19, 41},
  {cont__24_76, &frame__24_75, 208, 208, 11, 44},
  {cont__24_77, &frame__24_75, 209, 209, 14, 54},
  {cont__24_78, &frame__24_75, 209, 210, 11, 73},
  {entry__24_71, NULL, 206, 206, 9, 46},
  {cont__24_72, &frame__24_71, 207, 207, 16, 39},
  {cont__24_73, &frame__24_71, 207, 207, 16, 50},
  {cont__24_74, &frame__24_71, 207, 210, 9, 74},
  {entry__24_67, NULL, 204, 204, 20, 49},
  {cont__24_68, &frame__24_67, 204, 204, 7, 52},
  {cont__24_69, &frame__24_67, 205, 205, 10, 36},
  {cont__24_70, &frame__24_67, 205, 210, 7, 75},
  {entry__24_65, NULL, 203, 203, 77, 102},
  {cont__24_66, &frame__24_65, 203, 210, 74, 76},
  {entry__24_58, NULL, 203, 210, 5, 76},
  {entry__24_87, NULL, 217, 217, 33, 36},
  {entry__24_85, NULL, 217, 217, 10, 30},
  {cont__24_86, &frame__24_85, 217, 217, 7, 36},
  {entry__24_105, NULL, 232, 232, 55, 68},
  {cont__24_106, &frame__24_105, 232, 232, 52, 68},
  {entry__24_107, NULL, 232, 232, 71, 82},
  {entry__24_101, NULL, 227, 227, 19, 42},
  {cont__24_102, &frame__24_101, 231, 231, 32, 51},
  {cont__24_103, &frame__24_101, 232, 232, 35, 49},
  {cont__24_104, &frame__24_101, 232, 232, 32, 83},
  {cont__24_108, &frame__24_101, 233, 233, 40, 65},
  {cont__24_109, &frame__24_101, 228, 228, 32, 59},
  {cont__24_110, &frame__24_101, 228, 228, 19, 60},
  {cont__24_111, &frame__24_101, 234, 234, 45, 45},
  {entry__24_99, NULL, 226, 226, 20, 39},
  {cont__24_100, &frame__24_99, 226, 234, 17, 45},
  {entry__24_112, NULL, 239, 239, 30, 49},
  {cont__24_113, &frame__24_112, 240, 240, 38, 63},
  {cont__24_114, &frame__24_112, 236, 236, 30, 57},
  {cont__24_115, &frame__24_112, 236, 236, 17, 58},
  {cont__24_116, &frame__24_112, 241, 241, 43, 43},
  {entry__24_96, NULL, 223, 223, 13, 37},
  {cont__24_97, &frame__24_96, 224, 224, 18, 35},
  {cont__24_98, &frame__24_96, 224, 241, 13, 44},
  {entry__24_93, NULL, 221, 221, 11, 45},
  {cont__24_94, &frame__24_93, 222, 222, 14, 33},
  {cont__24_95, &frame__24_93, 222, 241, 11, 45},
  {entry__24_90, NULL, 219, 219, 9, 44},
  {cont__24_91, &frame__24_90, 220, 220, 12, 32},
  {cont__24_92, &frame__24_90, 220, 241, 9, 46},
  {entry__24_88, NULL, 218, 218, 10, 28},
  {cont__24_89, &frame__24_88, 218, 241, 7, 47},
  {entry__24_140, NULL, 261, 261, 25, 48},
  {entry__24_141, NULL, 262, 262, 25, 47},
  {entry__24_137, NULL, 255, 255, 17, 54},
  {cont__24_138, &frame__24_137, 260, 260, 25, 42},
  {cont__24_139, &frame__24_137, 259, 262, 23, 46},
  {cont__24_142, &frame__24_137, 263, 263, 38, 63},
  {cont__24_143, &frame__24_137, 256, 256, 17, 35},
  {cont__24_144, &frame__24_137, 264, 264, 17, 21},
  {entry__24_135, NULL, 254, 254, 18, 58},
  {cont__24_136, &frame__24_135, 254, 264, 15, 21},
  {entry__24_147, NULL, 268, 268, 17, 57},
  {cont__24_149, &frame__24_147, 269, 269, 17, 61},
  {cont__24_150, &frame__24_147, 269, 269, 61, 61},
  {entry__24_145, NULL, 265, 265, 18, 33},
  {cont__24_146, &frame__24_145, 265, 269, 15, 61},
  {entry__24_153, NULL, 272, 272, 17, 64},
  {cont__24_154, &frame__24_153, 272, 272, 64, 64},
  {entry__24_151, NULL, 270, 270, 18, 35},
  {cont__24_152, &frame__24_151, 270, 272, 15, 64},
  {entry__24_160, NULL, 276, 276, 30, 45},
  {cont__24_161, &frame__24_160, 277, 277, 38, 63},
  {cont__24_162, &frame__24_160, 277, 277, 64, 64},
  {entry__24_157, NULL, 274, 274, 20, 39},
  {cont__24_158, &frame__24_157, 274, 274, 20, 50},
  {cont__24_159, &frame__24_157, 274, 277, 17, 64},
  {entry__24_155, NULL, 273, 273, 18, 40},
  {cont__24_156, &frame__24_155, 273, 277, 15, 65},
  {entry__24_167, NULL, 284, 284, 25, 38},
  {entry__24_168, NULL, 285, 285, 25, 35},
  {entry__24_165, NULL, 283, 283, 25, 56},
  {cont__24_166, &frame__24_165, 282, 285, 23, 34},
  {cont__24_169, &frame__24_165, 286, 286, 38, 63},
  {cont__24_170, &frame__24_165, 279, 279, 17, 35},
  {cont__24_171, &frame__24_165, 287, 287, 17, 21},
  {entry__24_163, NULL, 278, 278, 18, 37},
  {cont__24_164, &frame__24_163, 278, 287, 15, 21},
  {entry__24_180, NULL, 294, 294, 21, 64},
  {cont__24_181, &frame__24_180, 295, 295, 21, 80},
  {cont__24_182, &frame__24_180, 296, 296, 21, 68},
  {cont__24_183, &frame__24_180, 296, 296, 68, 68},
  {entry__24_177, NULL, 293, 293, 22, 49},
  {cont__24_178, &frame__24_177, 293, 293, 22, 66},
  {cont__24_179, &frame__24_177, 293, 296, 19, 68},
  {entry__24_174, NULL, 291, 291, 17, 55},
  {cont__24_175, &frame__24_174, 292, 292, 20, 49},
  {cont__24_176, &frame__24_174, 292, 296, 17, 69},
  {cont__24_184, &frame__24_174, 297, 297, 17, 35},
  {cont__24_185, &frame__24_174, 297, 297, 40, 40},
  {entry__24_199, NULL, 309, 309, 62, 62},
  {entry__24_196, NULL, 308, 308, 28, 45},
  {cont__24_197, &frame__24_196, 308, 308, 28, 56},
  {cont__24_198, &frame__24_196, 308, 309, 21, 62},
  {cont__24_200, &frame__24_196, 310, 310, 48, 65},
  {cont__24_201, &frame__24_196, 310, 310, 21, 78},
  {cont__24_202, &frame__24_196, 312, 312, 22, 42},
  {cont__24_203, &frame__24_196, 312, 312, 21, 53},
  {cont__24_204, &frame__24_196, 313, 313, 21, 39},
  {cont__24_205, &frame__24_196, 313, 313, 50, 50},
  {entry__24_193, NULL, 306, 306, 19, 43},
  {cont__24_194, &frame__24_193, 307, 307, 26, 54},
  {cont__24_195, &frame__24_193, 307, 313, 19, 50},
  {entry__24_187, NULL, 299, 299, 17, 48},
  {cont__24_188, &frame__24_187, 302, 302, 33, 50},
  {cont__24_189, &frame__24_187, 302, 302, 19, 63},
  {cont__24_190, &frame__24_187, 304, 304, 17, 35},
  {cont__24_191, &frame__24_187, 305, 305, 20, 34},
  {cont__24_192, &frame__24_187, 305, 313, 17, 51},
  {entry__24_129, NULL, 249, 249, 13, 37},
  {cont__24_130, &frame__24_129, 250, 250, 13, 47},
  {cont__24_131, &frame__24_129, 251, 251, 13, 46},
  {cont__24_132, &frame__24_129, 252, 252, 21, 43},
  {cont__24_133, &frame__24_129, 252, 252, 13, 46},
  {cont__24_134, &frame__24_129, 253, 287, 13, 22},
  {cont__24_172, &frame__24_129, 289, 289, 15, 44},
  {cont__24_173, &frame__24_129, 298, 298, 15, 41},
  {cont__24_186, &frame__24_129, 288, 313, 13, 53},
  {entry__24_125, NULL, 246, 246, 11, 48},
  {cont__24_126, &frame__24_125, 247, 247, 11, 45},
  {cont__24_127, &frame__24_125, 248, 248, 14, 33},
  {cont__24_128, &frame__24_125, 248, 313, 11, 54},
  {entry__24_121, NULL, 243, 243, 22, 51},
  {cont__24_122, &frame__24_121, 243, 243, 22, 54},
  {cont__24_123, &frame__24_121, 245, 245, 12, 38},
  {cont__24_124, &frame__24_121, 245, 313, 9, 55},
  {entry__24_119, NULL, 242, 242, 10, 35},
  {cont__24_120, &frame__24_119, 242, 313, 7, 56},
  {entry__24_84, NULL, 216, 313, 5, 57},
  {cont__24_206, &frame__24_84, 313, 313, 57, 57},
  {entry__24_1_extract_documentation_from_file, NULL, 166, 166, 10, 56},
  {cont__24_4, &frame__24_1_extract_documentation_from_file, 166, 166, 3, 56},
  {cont__24_5, &frame__24_1_extract_documentation_from_file, 167, 167, 8, 21},
  {cont__24_6, &frame__24_1_extract_documentation_from_file, 167, 167, 3, 31},
  {cont__24_7, &frame__24_1_extract_documentation_from_file, 168, 168, 6, 19},
  {cont__24_8, &frame__24_1_extract_documentation_from_file, 168, 168, 6, 24},
  {cont__24_9, &frame__24_1_extract_documentation_from_file, 168, 168, 3, 52},
  {cont__24_12, &frame__24_1_extract_documentation_from_file, 169, 169, 6, 11},
  {cont__24_13, &frame__24_1_extract_documentation_from_file, 169, 169, 6, 18},
  {cont__24_14, &frame__24_1_extract_documentation_from_file, 169, 169, 6, 18},
  {cont__24_15, &frame__24_1_extract_documentation_from_file, 169, 169, 3, 63},
  {cont__24_18, &frame__24_1_extract_documentation_from_file, 170, 170, 11, 11},
  {cont__24_19, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 12},
  {cont__24_20, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 23},
  {cont__24_21, &frame__24_1_extract_documentation_from_file, 170, 170, 6, 23},
  {cont__24_22, &frame__24_1_extract_documentation_from_file, 170, 170, 3, 71},
  {cont__24_25, &frame__24_1_extract_documentation_from_file, 173, 173, 17, 48},
  {cont__24_27, &frame__24_1_extract_documentation_from_file, 173, 173, 50, 59},
  {cont__24_29, &frame__24_1_extract_documentation_from_file, 172, 174, 3, 69},
  {cont__24_30, &frame__24_1_extract_documentation_from_file, 183, 183, 3, 37},
  {cont__24_31, &frame__24_1_extract_documentation_from_file, 184, 184, 3, 56},
  {cont__24_34, &frame__24_1_extract_documentation_from_file, 187, 197, 3, 17},
  {cont__24_46, &frame__24_1_extract_documentation_from_file, 198, 198, 31, 31},
  {cont__24_47, &frame__24_1_extract_documentation_from_file, 198, 198, 3, 31},
  {cont__24_48, &frame__24_1_extract_documentation_from_file, 199, 199, 3, 70},
  {cont__24_52, &frame__24_1_extract_documentation_from_file, 200, 200, 6, 29},
  {cont__24_53, &frame__24_1_extract_documentation_from_file, 200, 200, 3, 59},
  {cont__24_57, &frame__24_1_extract_documentation_from_file, 202, 210, 3, 77},
  {cont__24_83, &frame__24_1_extract_documentation_from_file, 211, 313, 3, 58},
  {cont__24_207, &frame__24_1_extract_documentation_from_file, 313, 313, 58, 58},
  {entry__25_8, NULL, 319, 319, 32, 72},
  {entry__25_6, NULL, 319, 319, 10, 29},
  {cont__25_7, &frame__25_6, 319, 319, 7, 72},
  {entry__25_11, NULL, 320, 320, 36, 71},
  {entry__25_9, NULL, 320, 320, 10, 33},
  {cont__25_10, &frame__25_9, 320, 320, 7, 71},
  {entry__25_4, NULL, 317, 317, 5, 28},
  {cont__25_5, &frame__25_4, 318, 320, 5, 71},
  {entry__25_1_extract_documentation_from_directory, NULL, 316, 316, 22, 27},
  {cont__25_2, &frame__25_1_extract_documentation_from_directory, 316, 316, 12, 33},
  {cont__25_3, &frame__25_1_extract_documentation_from_directory, 316, 320, 3, 72},
  {entry__26_5, NULL, 324, 324, 40, 53},
  {cont__26_6, &frame__26_5, 324, 324, 37, 53},
  {entry__26_13, NULL, 329, 330, 17, 64},
  {cont__26_16, &frame__26_13, 329, 330, 11, 64},
  {entry__26_11, NULL, 328, 328, 12, 40},
  {cont__26_12, &frame__26_11, 328, 330, 9, 65},
  {cont__26_17, &frame__26_11, 331, 331, 37, 37},
  {entry__26_9, NULL, 327, 327, 10, 46},
  {cont__26_10, &frame__26_9, 327, 331, 7, 37},
  {entry__26_20, NULL, 333, 334, 13, 51},
  {cont__26_22, &frame__26_20, 333, 334, 7, 51},
  {entry__26_7, NULL, 326, 326, 14, 37},
  {cont__26_8, &frame__26_7, 326, 331, 5, 38},
  {cont__26_18, &frame__26_7, 332, 332, 12, 40},
  {cont__26_19, &frame__26_7, 332, 334, 5, 52},
  {cont__26_23, &frame__26_7, 335, 335, 8, 43},
  {cont__26_25, &frame__26_7, 335, 335, 5, 43},
  {entry__26_1_resolved_name, NULL, 323, 323, 3, 21},
  {cont__26_2, &frame__26_1_resolved_name, 324, 324, 6, 23},
  {cont__26_3, &frame__26_1_resolved_name, 324, 324, 6, 34},
  {cont__26_4, &frame__26_1_resolved_name, 324, 335, 3, 43},
  {entry__27_15, NULL, 345, 345, 35, 69},
  {entry__27_12, NULL, 344, 344, 7, 39},
  {cont__27_13, &frame__27_12, 345, 345, 10, 32},
  {cont__27_14, &frame__27_12, 345, 345, 7, 69},
  {entry__27_7, NULL, 341, 341, 6, 32},
  {cont__27_8, &frame__27_7, 341, 341, 5, 38},
  {cont__27_9, &frame__27_7, 342, 342, 12, 30},
  {cont__27_10, &frame__27_7, 342, 342, 12, 47},
  {cont__27_11, &frame__27_7, 342, 345, 5, 69},
  {cont__27_16, &frame__27_7, 346, 346, 5, 23},
  {cont__27_17, &frame__27_7, 346, 346, 34, 34},
  {entry__27_1_add_derived_type, NULL, 338, 338, 23, 40},
  {cont__27_2, &frame__27_1_add_derived_type, 338, 338, 42, 59},
  {cont__27_3, &frame__27_1_add_derived_type, 338, 338, 3, 60},
  {cont__27_4, &frame__27_1_add_derived_type, 339, 339, 3, 33},
  {cont__27_5, &frame__27_1_add_derived_type, 340, 340, 6, 26},
  {cont__27_6, &frame__27_1_add_derived_type, 340, 346, 3, 34},
  {entry__28_1_mangled, NULL, 348, 348, 38, 48},
  {cont__28_2, &frame__28_1_mangled, 348, 348, 50, 60},
  {cont__28_4, &frame__28_1_mangled, 348, 348, 21, 61},
  {cont__28_5, &frame__28_1_mangled, 348, 348, 18, 61},
  {entry__29_1_ordered_name, NULL, 353, 353, 7, 24},
  {cont__29_2, &frame__29_1_ordered_name, 355, 355, 7, 29},
  {cont__29_3, &frame__29_1_ordered_name, 352, 359, 5, 14},
  {cont__29_4, &frame__29_1_ordered_name, 351, 359, 3, 16},
  {entry__30_2, NULL, 363, 363, 7, 27},
  {cont__30_5, &frame__30_2, 363, 363, 5, 34},
  {cont__30_7, &frame__30_2, 364, 364, 5, 29},
  {cont__30_9, &frame__30_2, 365, 365, 7, 28},
  {cont__30_11, &frame__30_2, 365, 365, 5, 37},
  {cont__30_13, &frame__30_2, 366, 366, 5, 29},
  {cont__30_14, &frame__30_2, 367, 367, 7, 32},
  {cont__30_16, &frame__30_2, 367, 367, 5, 45},
  {cont__30_18, &frame__30_2, 368, 368, 5, 29},
  {cont__30_19, &frame__30_2, 369, 369, 7, 34},
  {cont__30_21, &frame__30_2, 369, 369, 5, 49},
  {cont__30_23, &frame__30_2, 370, 370, 5, 29},
  {cont__30_24, &frame__30_2, 371, 371, 7, 33},
  {cont__30_26, &frame__30_2, 371, 371, 5, 47},
  {entry__30_1_link_bar, NULL, 362, 371, 3, 47},
  {entry__33_5, NULL, 385, 385, 13, 22},
  {cont__33_6, &frame__33_5, 386, 386, 13, 33},
  {cont__33_7, &frame__33_5, 387, 387, 22, 22},
  {entry__33_8, NULL, 389, 389, 13, 33},
  {cont__33_9, &frame__33_8, 389, 389, 33, 33},
  {entry__33_3, NULL, 384, 384, 11, 35},
  {cont__33_4, &frame__33_3, 383, 389, 9, 34},
  {entry__33_15, NULL, 394, 394, 15, 35},
  {cont__33_16, &frame__33_15, 395, 395, 22, 22},
  {entry__33_12, NULL, 393, 393, 16, 25},
  {cont__33_13, &frame__33_12, 393, 393, 16, 25},
  {cont__33_14, &frame__33_12, 393, 395, 13, 22},
  {entry__33_21, NULL, 399, 399, 60, 60},
  {entry__33_19, NULL, 399, 399, 20, 44},
  {cont__33_20, &frame__33_19, 399, 399, 17, 60},
  {entry__33_22, NULL, 401, 401, 17, 30},
  {cont__33_23, &frame__33_22, 401, 401, 30, 30},
  {entry__33_17, NULL, 398, 398, 15, 24},
  {cont__33_18, &frame__33_17, 397, 401, 13, 31},
  {cont__33_24, &frame__33_17, 402, 402, 26, 34},
  {cont__33_25, &frame__33_17, 402, 402, 13, 34},
  {cont__33_26, &frame__33_17, 402, 402, 34, 34},
  {entry__33_10, NULL, 392, 392, 11, 20},
  {cont__33_11, &frame__33_10, 391, 402, 9, 35},
  {entry__33_2, NULL, 381, 402, 5, 37},
  {entry__33_30, NULL, 403, 403, 18, 38},
  {cont__33_31, &frame__33_30, 403, 403, 38, 38},
  {entry__33_1_to_paragraphs, NULL, 380, 402, 3, 38},
  {cont__33_27, &frame__33_1_to_paragraphs, 403, 403, 6, 15},
  {cont__33_28, &frame__33_1_to_paragraphs, 403, 403, 6, 15},
  {cont__33_29, &frame__33_1_to_paragraphs, 403, 403, 3, 38},
  {cont__33_32, &frame__33_1_to_paragraphs, 404, 404, 3, 15},
  {entry__34_8, NULL, 412, 412, 43, 69},
  {cont__34_10, &frame__34_8, 412, 412, 69, 69},
  {entry__34_13, NULL, 413, 413, 45, 71},
  {cont__34_15, &frame__34_13, 413, 413, 71, 71},
  {entry__34_4, NULL, 410, 410, 9, 42},
  {cont__34_5, &frame__34_4, 411, 411, 9, 44},
  {cont__34_6, &frame__34_4, 412, 412, 16, 40},
  {cont__34_7, &frame__34_4, 412, 412, 9, 69},
  {cont__34_11, &frame__34_4, 413, 413, 16, 42},
  {cont__34_12, &frame__34_4, 413, 413, 9, 71},
  {cont__34_16, &frame__34_4, 414, 414, 9, 52},
  {cont__34_17, &frame__34_4, 414, 414, 52, 52},
  {entry__34_20, NULL, 416, 416, 43, 67},
  {cont__34_21, &frame__34_20, 416, 416, 67, 67},
  {entry__34_18, NULL, 416, 416, 16, 40},
  {cont__34_19, &frame__34_18, 416, 416, 9, 67},
  {entry__34_25, NULL, 421, 421, 24, 40},
  {cont__34_26, &frame__34_25, 419, 422, 13, 55},
  {cont__34_31, &frame__34_25, 419, 422, 7, 55},
  {entry__34_2_resolve_reference, NULL, 409, 409, 7, 30},
  {cont__34_3, &frame__34_2_resolve_reference, 408, 416, 5, 68},
  {cont__34_22, &frame__34_2_resolve_reference, 418, 418, 8, 36},
  {cont__34_23, &frame__34_2_resolve_reference, 418, 418, 8, 49},
  {cont__34_24, &frame__34_2_resolve_reference, 418, 422, 5, 56},
  {cont__34_32, &frame__34_2_resolve_reference, },
  {entry__34_42, NULL, 429, 429, 11, 42},
  {cont__34_43, &frame__34_42, 430, 430, 11, 44},
  {cont__34_44, &frame__34_42, 436, 436, 15, 26},
  {cont__34_45, &frame__34_42, 440, 440, 15, 28},
  {cont__34_46, &frame__34_42, 432, 441, 13, 21},
  {cont__34_50, &frame__34_42, 431, 441, 11, 23},
  {entry__34_51, NULL, 443, 443, 11, 26},
  {entry__34_56, NULL, 456, 456, 40, 60},
  {cont__34_57, &frame__34_56, 456, 456, 40, 60},
  {entry__34_54, NULL, 456, 456, 11, 35},
  {cont__34_55, &frame__34_54, 456, 456, 11, 60},
  {cont__34_58, &frame__34_54, 456, 456, 11, 60},
  {entry__34_60, NULL, 460, 460, 28, 44},
  {cont__34_61, &frame__34_60, 458, 460, 18, 48},
  {cont__34_65, &frame__34_60, 458, 460, 11, 48},
  {entry__34_80, NULL, 478, 478, 58, 58},
  {cont__34_81, &frame__34_80, 478, 478, 39, 59},
  {cont__34_82, &frame__34_80, 478, 478, 21, 74},
  {cont__34_84, &frame__34_80, 478, 478, 74, 74},
  {entry__34_78, NULL, 477, 477, 22, 47},
  {cont__34_79, &frame__34_78, 477, 478, 19, 74},
  {entry__34_87, NULL, 481, 481, 49, 49},
  {cont__34_88, &frame__34_87, 481, 481, 30, 50},
  {cont__34_89, &frame__34_87, 480, 481, 21, 79},
  {cont__34_91, &frame__34_87, 481, 481, 80, 80},
  {entry__34_85, NULL, 479, 479, 22, 47},
  {cont__34_86, &frame__34_85, 479, 481, 19, 80},
  {entry__34_94, NULL, 485, 485, 26, 47},
  {cont__34_95, &frame__34_94, 485, 485, 26, 53},
  {cont__34_96, &frame__34_94, 487, 487, 26, 47},
  {cont__34_97, &frame__34_94, 487, 487, 26, 53},
  {cont__34_98, &frame__34_94, 483, 488, 21, 28},
  {cont__34_101, &frame__34_94, 488, 488, 29, 29},
  {entry__34_92, NULL, 482, 482, 22, 45},
  {cont__34_93, &frame__34_92, 482, 488, 19, 29},
  {entry__34_76, NULL, 475, 475, 17, 68},
  {cont__34_77, &frame__34_76, 476, 488, 17, 30},
  {cont__34_102, &frame__34_76, 489, 489, 31, 52},
  {cont__34_103, &frame__34_76, 489, 489, 17, 58},
  {cont__34_104, &frame__34_76, 490, 490, 34, 56},
  {cont__34_105, &frame__34_76, 490, 490, 17, 56},
  {cont__34_106, &frame__34_76, 490, 490, 56, 56},
  {entry__34_71, NULL, 472, 472, 19, 53},
  {cont__34_72, &frame__34_71, 468, 473, 17, 20},
  {cont__34_74, &frame__34_71, 466, 473, 15, 21},
  {cont__34_75, &frame__34_71, 465, 490, 13, 57},
  {entry__34_116, NULL, 504, 504, 64, 64},
  {cont__34_117, &frame__34_116, 504, 504, 42, 65},
  {cont__34_118, &frame__34_116, 504, 504, 21, 80},
  {cont__34_119, &frame__34_116, 504, 504, 80, 80},
  {entry__34_114, NULL, 503, 503, 22, 50},
  {cont__34_115, &frame__34_114, 503, 504, 19, 80},
  {entry__34_122, NULL, 508, 508, 47, 47},
  {cont__34_123, &frame__34_122, 508, 508, 25, 48},
  {cont__34_124, &frame__34_122, 506, 509, 21, 52},
  {cont__34_125, &frame__34_122, 509, 509, 53, 53},
  {entry__34_120, NULL, 505, 505, 22, 50},
  {cont__34_121, &frame__34_120, 505, 509, 19, 53},
  {entry__34_112, NULL, 501, 501, 17, 71},
  {cont__34_113, &frame__34_112, 502, 509, 17, 54},
  {cont__34_126, &frame__34_112, 510, 510, 31, 52},
  {cont__34_127, &frame__34_112, 510, 510, 17, 58},
  {cont__34_128, &frame__34_112, 511, 511, 37, 62},
  {cont__34_129, &frame__34_112, 511, 511, 17, 62},
  {cont__34_130, &frame__34_112, 511, 511, 62, 62},
  {entry__34_107, NULL, 498, 498, 19, 53},
  {cont__34_108, &frame__34_107, 494, 499, 17, 20},
  {cont__34_110, &frame__34_107, 492, 499, 15, 21},
  {cont__34_111, &frame__34_107, 491, 511, 13, 63},
  {entry__34_137, NULL, 514, 514, 34, 47},
  {cont__34_138, &frame__34_137, 514, 514, 17, 47},
  {cont__34_139, &frame__34_137, 514, 514, 47, 47},
  {entry__34_134, NULL, 513, 513, 30, 51},
  {cont__34_135, &frame__34_134, 513, 513, 24, 56},
  {cont__34_136, &frame__34_134, 513, 514, 15, 47},
  {entry__34_131, NULL, 512, 512, 16, 49},
  {cont__34_133, &frame__34_131, 512, 514, 13, 48},
  {entry__34_145, NULL, 517, 517, 17, 27},
  {cont__34_146, &frame__34_145, 518, 518, 17, 38},
  {cont__34_147, &frame__34_145, 521, 521, 33, 45},
  {cont__34_148, &frame__34_145, 520, 521, 17, 66},
  {cont__34_149, &frame__34_145, 523, 523, 17, 46},
  {cont__34_150, &frame__34_145, 524, 524, 17, 30},
  {cont__34_151, &frame__34_145, 524, 524, 45, 45},
  {entry__34_142, NULL, 516, 516, 30, 51},
  {cont__34_143, &frame__34_142, 516, 516, 24, 56},
  {cont__34_144, &frame__34_142, 516, 524, 15, 45},
  {entry__34_140, NULL, 515, 515, 16, 43},
  {cont__34_141, &frame__34_140, 515, 524, 13, 46},
  {entry__34_154, NULL, 526, 526, 23, 44},
  {cont__34_155, &frame__34_154, 526, 526, 15, 50},
  {cont__34_156, &frame__34_154, 527, 527, 22, 43},
  {cont__34_157, &frame__34_154, 527, 527, 15, 49},
  {cont__34_158, &frame__34_154, 528, 528, 30, 41},
  {cont__34_159, &frame__34_154, 528, 528, 15, 41},
  {cont__34_160, &frame__34_154, 528, 528, 41, 41},
  {entry__34_152, NULL, 525, 525, 16, 45},
  {cont__34_153, &frame__34_152, 525, 528, 13, 41},
  {entry__34_168, NULL, 533, 533, 47, 47},
  {entry__34_169, NULL, 535, 535, 19, 49},
  {cont__34_170, &frame__34_169, 535, 535, 49, 49},
  {entry__34_164, NULL, 530, 530, 24, 45},
  {cont__34_165, &frame__34_164, 530, 530, 15, 51},
  {cont__34_166, &frame__34_164, 532, 532, 17, 28},
  {cont__34_167, &frame__34_164, 531, 535, 15, 50},
  {entry__34_161, NULL, 529, 529, 16, 58},
  {cont__34_163, &frame__34_161, 529, 535, 13, 51},
  {entry__34_175, NULL, 542, 542, 41, 41},
  {cont__34_176, &frame__34_175, 542, 542, 21, 41},
  {cont__34_177, &frame__34_175, 543, 543, 21, 48},
  {cont__34_178, &frame__34_175, 544, 544, 42, 58},
  {cont__34_179, &frame__34_175, 544, 544, 24, 66},
  {cont__34_181, &frame__34_175, 544, 544, 21, 66},
  {entry__34_187, NULL, 549, 549, 23, 55},
  {cont__34_188, &frame__34_187, 549, 549, 55, 55},
  {entry__34_189, NULL, 551, 551, 23, 50},
  {cont__34_190, &frame__34_189, 551, 551, 50, 50},
  {entry__34_185, NULL, 548, 548, 21, 48},
  {cont__34_186, &frame__34_185, 547, 551, 19, 51},
  {entry__34_191, NULL, 553, 553, 46, 46},
  {entry__34_171, NULL, 540, 540, 39, 47},
  {cont__34_172, &frame__34_171, 540, 540, 30, 48},
  {cont__34_173, &frame__34_171, 540, 540, 19, 53},
  {cont__34_174, &frame__34_171, 539, 544, 17, 66},
  {cont__34_182, &frame__34_171, 537, 544, 15, 68},
  {cont__34_183, &frame__34_171, 546, 546, 17, 44},
  {cont__34_184, &frame__34_171, 545, 553, 15, 47},
  {entry__34_70, NULL, 464, 553, 11, 49},
  {entry__34_68, NULL, 462, 462, 9, 46},
  {cont__34_69, &frame__34_68, 463, 553, 9, 50},
  {entry__34_209, NULL, 569, 569, 25, 51},
  {cont__34_210, &frame__34_209, 569, 569, 25, 61},
  {cont__34_211, &frame__34_209, 566, 570, 23, 27},
  {cont__34_212, &frame__34_209, 570, 570, 28, 28},
  {entry__34_213, NULL, 572, 572, 23, 48},
  {cont__34_214, &frame__34_213, 572, 572, 48, 48},
  {entry__34_206, NULL, 565, 565, 21, 47},
  {cont__34_207, &frame__34_206, 565, 565, 21, 58},
  {cont__34_208, &frame__34_206, 564, 572, 19, 49},
  {entry__34_204, NULL, 563, 563, 20, 48},
  {cont__34_205, &frame__34_204, 563, 572, 17, 50},
  {entry__34_217, NULL, 574, 574, 19, 58},
  {cont__34_218, &frame__34_217, 574, 574, 58, 58},
  {entry__34_215, NULL, 573, 573, 20, 48},
  {cont__34_216, &frame__34_215, 573, 574, 17, 58},
  {entry__34_223, NULL, 579, 579, 22, 47},
  {cont__34_224, &frame__34_223, 579, 579, 22, 61},
  {cont__34_225, &frame__34_223, 579, 579, 22, 64},
  {cont__34_226, &frame__34_223, 579, 579, 19, 64},
  {entry__34_227, NULL, 580, 580, 19, 23},
  {entry__34_200, NULL, 561, 561, 30, 53},
  {cont__34_201, &frame__34_200, 561, 561, 22, 54},
  {cont__34_202, &frame__34_200, 561, 561, 15, 75},
  {cont__34_203, &frame__34_200, 562, 574, 15, 59},
  {cont__34_219, &frame__34_200, 578, 578, 23, 48},
  {cont__34_220, &frame__34_200, 578, 578, 23, 57},
  {cont__34_221, &frame__34_200, 578, 578, 19, 58},
  {cont__34_222, &frame__34_200, 576, 580, 15, 24},
  {cont__34_228, &frame__34_200, 582, 582, 32, 49},
  {cont__34_229, &frame__34_200, 582, 582, 15, 49},
  {cont__34_230, &frame__34_200, 582, 582, 49, 49},
  {entry__34_231, NULL, 559, 559, 15, 18},
  {entry__34_197, NULL, 557, 557, 13, 40},
  {cont__34_198, &frame__34_197, 558, 558, 13, 52},
  {cont__34_199, &frame__34_197, 556, 582, 11, 50},
  {entry__34_195, NULL, 555, 555, 18, 36},
  {cont__34_196, &frame__34_195, 555, 582, 9, 51},
  {entry__34_234, NULL, 583, 583, 40, 58},
  {entry__34_244, NULL, 589, 589, 19, 42},
  {cont__34_245, &frame__34_244, 589, 589, 17, 42},
  {entry__34_241, NULL, 588, 588, 16, 32},
  {cont__34_242, &frame__34_241, 588, 588, 13, 32},
  {cont__34_243, &frame__34_241, 589, 589, 13, 42},
  {entry__34_240, NULL, 587, 589, 11, 42},
  {entry__34_237, NULL, 585, 585, 9, 23},
  {cont__34_239, &frame__34_237, 586, 589, 9, 43},
  {entry__34_254, NULL, 595, 595, 19, 45},
  {cont__34_255, &frame__34_254, 595, 595, 17, 45},
  {entry__34_251, NULL, 594, 594, 16, 35},
  {cont__34_252, &frame__34_251, 594, 594, 13, 35},
  {cont__34_253, &frame__34_251, 595, 595, 13, 45},
  {entry__34_250, NULL, 593, 595, 11, 45},
  {entry__34_248, NULL, 591, 591, 9, 20},
  {cont__34_249, &frame__34_248, 592, 595, 9, 46},
  {entry__34_261, NULL, 598, 598, 46, 58},
  {entry__34_258, NULL, 597, 597, 9, 24},
  {cont__34_260, &frame__34_258, 598, 598, 9, 58},
  {entry__34_267, NULL, 601, 601, 46, 53},
  {entry__34_264, NULL, 600, 600, 9, 30},
  {cont__34_266, &frame__34_264, 601, 601, 9, 53},
  {entry__34_277, NULL, 608, 608, 33, 49},
  {cont__34_278, &frame__34_277, 608, 608, 30, 56},
  {cont__34_279, &frame__34_277, 608, 608, 21, 56},
  {cont__34_280, &frame__34_277, 608, 608, 19, 66},
  {entry__34_276, NULL, 608, 608, 15, 66},
  {cont__34_281, &frame__34_276, 609, 609, 15, 25},
  {cont__34_283, &frame__34_276, 610, 610, 18, 46},
  {cont__34_284, &frame__34_276, 610, 610, 15, 46},
  {entry__34_274, NULL, 606, 606, 13, 40},
  {cont__34_275, &frame__34_274, 607, 610, 13, 46},
  {entry__34_273, NULL, 605, 610, 11, 47},
  {entry__34_270, NULL, 603, 603, 9, 21},
  {cont__34_272, &frame__34_270, 604, 610, 9, 48},
  {entry__34_296, NULL, 617, 617, 33, 44},
  {cont__34_297, &frame__34_296, 617, 617, 30, 51},
  {cont__34_298, &frame__34_296, 617, 617, 21, 51},
  {cont__34_299, &frame__34_296, 617, 617, 19, 56},
  {entry__34_303, NULL, 619, 619, 33, 46},
  {cont__34_304, &frame__34_303, 619, 619, 30, 53},
  {cont__34_305, &frame__34_303, 619, 619, 21, 53},
  {cont__34_306, &frame__34_303, 619, 619, 19, 60},
  {entry__34_295, NULL, 617, 617, 15, 56},
  {cont__34_300, &frame__34_295, 618, 618, 15, 33},
  {cont__34_302, &frame__34_295, 619, 619, 15, 60},
  {entry__34_293, NULL, 615, 615, 13, 50},
  {cont__34_294, &frame__34_293, 616, 619, 13, 60},
  {entry__34_291, NULL, 614, 614, 20, 33},
  {cont__34_292, &frame__34_291, 614, 619, 11, 61},
  {entry__34_288, NULL, 612, 612, 9, 27},
  {cont__34_290, &frame__34_288, 613, 619, 9, 62},
  {entry__34_317, NULL, 625, 625, 33, 51},
  {cont__34_318, &frame__34_317, 625, 625, 30, 58},
  {cont__34_319, &frame__34_317, 625, 625, 21, 58},
  {cont__34_320, &frame__34_317, 625, 625, 19, 70},
  {entry__34_323, NULL, 631, 631, 24, 44},
  {cont__34_324, &frame__34_323, 631, 631, 51, 69},
  {cont__34_325, &frame__34_323, 631, 631, 21, 76},
  {cont__34_326, &frame__34_323, 629, 631, 19, 75},
  {cont__34_327, &frame__34_323, 628, 634, 17, 29},
  {entry__34_316, NULL, 625, 625, 15, 70},
  {cont__34_321, &frame__34_316, 626, 626, 15, 25},
  {cont__34_322, &frame__34_316, 627, 634, 15, 30},
  {entry__34_315, NULL, 624, 634, 13, 31},
  {entry__34_313, NULL, 623, 623, 20, 35},
  {cont__34_314, &frame__34_313, 623, 634, 11, 32},
  {entry__34_310, NULL, 621, 621, 9, 44},
  {cont__34_312, &frame__34_310, 622, 634, 9, 33},
  {entry__34_343, NULL, 644, 644, 23, 39},
  {cont__34_344, &frame__34_343, 644, 644, 21, 45},
  {entry__34_342, NULL, 644, 644, 17, 45},
  {entry__34_336, NULL, 643, 643, 42, 60},
  {cont__34_337, &frame__34_336, 643, 643, 62, 70},
  {cont__34_339, &frame__34_336, 643, 643, 30, 71},
  {cont__34_340, &frame__34_336, 643, 643, 13, 80},
  {cont__34_341, &frame__34_336, 644, 644, 13, 45},
  {entry__34_335, NULL, 642, 644, 11, 45},
  {entry__34_332, NULL, 640, 640, 9, 19},
  {cont__34_334, &frame__34_332, 641, 644, 9, 46},
  {entry__34_359, NULL, 660, 660, 19, 35},
  {entry__34_354, NULL, 657, 657, 24, 48},
  {cont__34_355, &frame__34_354, 657, 657, 24, 63},
  {cont__34_356, &frame__34_354, 657, 657, 19, 64},
  {cont__34_357, &frame__34_354, 655, 658, 17, 25},
  {cont__34_358, &frame__34_354, 654, 660, 15, 35},
  {cont__34_360, &frame__34_354, 661, 661, 35, 69},
  {cont__34_362, &frame__34_354, 661, 661, 15, 69},
  {cont__34_363, &frame__34_354, 652, 661, 13, 68},
  {cont__34_364, &frame__34_354, 651, 661, 11, 70},
  {entry__34_346, NULL, 647, 647, 9, 30},
  {cont__34_347, &frame__34_346, 648, 648, 9, 36},
  {cont__34_348, &frame__34_346, 649, 649, 9, 16},
  {cont__34_349, &frame__34_346, 650, 650, 45, 56},
  {cont__34_350, &frame__34_346, 650, 650, 23, 56},
  {cont__34_351, &frame__34_346, 650, 650, 13, 56},
  {cont__34_353, &frame__34_346, 650, 661, 9, 71},
  {entry__34_39, NULL, 426, 426, 7, 14},
  {cont__34_40, &frame__34_39, 428, 428, 9, 36},
  {cont__34_41, &frame__34_39, 427, 443, 7, 27},
  {cont__34_52, &frame__34_39, 452, 452, 7, 41},
  {cont__34_53, &frame__34_39, 454, 456, 9, 59},
  {cont__34_59, &frame__34_39, 453, 460, 7, 50},
  {cont__34_66, &frame__34_39, 461, 461, 10, 32},
  {cont__34_67, &frame__34_39, 461, 553, 7, 51},
  {cont__34_192, &frame__34_39, 554, 554, 10, 22},
  {cont__34_193, &frame__34_39, 554, 554, 10, 34},
  {cont__34_194, &frame__34_39, 554, 582, 7, 52},
  {cont__34_232, &frame__34_39, 583, 583, 10, 37},
  {cont__34_233, &frame__34_39, 583, 583, 7, 58},
  {cont__34_235, &frame__34_39, 584, 584, 14, 32},
  {cont__34_236, &frame__34_39, 584, 589, 7, 44},
  {cont__34_246, &frame__34_39, 590, 590, 14, 35},
  {cont__34_247, &frame__34_39, 590, 595, 7, 47},
  {cont__34_256, &frame__34_39, 596, 596, 14, 34},
  {cont__34_257, &frame__34_39, 596, 598, 7, 58},
  {cont__34_262, &frame__34_39, 599, 599, 10, 37},
  {cont__34_263, &frame__34_39, 599, 601, 7, 53},
  {cont__34_268, &frame__34_39, 602, 602, 14, 32},
  {cont__34_269, &frame__34_39, 602, 610, 7, 49},
  {cont__34_285, &frame__34_39, 611, 611, 14, 27},
  {cont__34_286, &frame__34_39, 611, 611, 14, 36},
  {cont__34_287, &frame__34_39, 611, 619, 7, 63},
  {cont__34_307, &frame__34_39, 620, 620, 10, 22},
  {cont__34_308, &frame__34_39, 620, 620, 10, 39},
  {cont__34_309, &frame__34_39, 620, 634, 7, 34},
  {cont__34_328, &frame__34_39, 637, 637, 9, 42},
  {cont__34_329, &frame__34_39, 636, 637, 7, 64},
  {cont__34_330, &frame__34_39, 639, 639, 14, 32},
  {cont__34_331, &frame__34_39, 639, 644, 7, 47},
  {cont__34_345, &frame__34_39, 646, 661, 7, 72},
  {cont__34_365, &frame__34_39, 663, 663, 9, 26},
  {cont__34_367, &frame__34_39, 664, 664, 24, 40},
  {cont__34_368, &frame__34_39, 664, 664, 24, 69},
  {cont__34_369, &frame__34_39, 664, 664, 9, 76},
  {cont__34_372, &frame__34_39, 662, 664, 7, 76},
  {entry__34_34, NULL, 425, 425, 25, 45},
  {cont__34_35, &frame__34_34, 425, 425, 17, 52},
  {cont__34_38, &frame__34_34, 425, 664, 5, 77},
  {entry__34_1_create_info_page, NULL, 424, 424, 6, 29},
  {cont__34_33, &frame__34_1_create_info_page, 424, 664, 3, 78},
  {entry__35_4, NULL, 669, 669, 37, 57},
  {cont__35_5, &frame__35_4, 669, 669, 33, 58},
  {cont__35_6, &frame__35_4, 669, 669, 33, 58},
  {entry__35_12, NULL, 671, 671, 24, 46},
  {cont__35_13, &frame__35_12, 671, 671, 24, 46},
  {cont__35_14, &frame__35_12, 671, 671, 24, 46},
  {entry__35_10, NULL, 671, 671, 10, 19},
  {cont__35_11, &frame__35_10, 671, 671, 10, 46},
  {cont__35_15, &frame__35_10, 671, 671, 7, 52},
  {cont__35_16, &frame__35_10, 672, 672, 33, 41},
  {cont__35_17, &frame__35_10, 672, 672, 7, 41},
  {cont__35_18, &frame__35_10, 672, 672, 41, 41},
  {entry__35_9, NULL, 670, 672, 20, 41},
  {cont__35_19, &frame__35_9, 672, 672, 41, 41},
  {entry__35_21, NULL, 673, 673, 29, 56},
  {cont__35_22, &frame__35_21, 673, 673, 29, 61},
  {cont__35_23, &frame__35_21, 673, 673, 29, 61},
  {entry__35_25, NULL, 677, 677, 24, 40},
  {cont__35_26, &frame__35_25, 674, 679, 14, 28},
  {cont__35_29, &frame__35_25, 674, 679, 7, 28},
  {entry__35_8, NULL, 670, 672, 5, 41},
  {cont__35_20, &frame__35_8, 673, 673, 8, 61},
  {cont__35_24, &frame__35_8, 673, 679, 5, 29},
  {entry__35_1_get_short_description, NULL, 667, 667, 3, 37},
  {cont__35_2, &frame__35_1_get_short_description, 669, 669, 6, 28},
  {cont__35_3, &frame__35_1_get_short_description, 669, 669, 6, 58},
  {cont__35_7, &frame__35_1_get_short_description, 669, 679, 3, 30},
  {cont__35_30, &frame__35_1_get_short_description, 680, 680, 3, 22},
  {entry__36_14, NULL, 705, 705, 27, 53},
  {entry__36_19, NULL, 709, 709, 24, 48},
  {cont__36_20, &frame__36_19, 709, 709, 11, 62},
  {cont__36_21, &frame__36_19, 709, 709, 62, 62},
  {entry__36_17, NULL, 708, 708, 16, 42},
  {cont__36_18, &frame__36_17, 708, 709, 9, 62},
  {cont__36_22, &frame__36_17, 710, 710, 9, 45},
  {cont__36_24, &frame__36_17, 711, 711, 9, 79},
  {cont__36_25, &frame__36_17, 711, 711, 9, 36},
  {cont__36_26, &frame__36_17, 713, 713, 24, 48},
  {cont__36_27, &frame__36_17, 713, 713, 50, 74},
  {cont__36_28, &frame__36_17, 712, 713, 9, 75},
  {cont__36_29, &frame__36_17, 714, 714, 10, 27},
  {cont__36_30, &frame__36_17, 714, 714, 10, 36},
  {cont__36_31, &frame__36_17, 714, 714, 9, 42},
  {cont__36_32, &frame__36_17, 714, 714, 9, 27},
  {cont__36_33, &frame__36_17, 715, 715, 9, 29},
  {cont__36_34, &frame__36_17, 715, 715, 41, 41},
  {entry__36_11, NULL, 704, 704, 7, 25},
  {cont__36_12, &frame__36_11, 705, 705, 10, 24},
  {cont__36_13, &frame__36_11, 705, 705, 7, 53},
  {cont__36_15, &frame__36_11, 707, 707, 16, 31},
  {cont__36_16, &frame__36_11, 707, 715, 7, 41},
  {cont__36_35, &frame__36_11, 716, 716, 8, 25},
  {cont__36_36, &frame__36_11, 716, 716, 7, 25},
  {cont__36_37, &frame__36_11, 716, 716, 44, 44},
  {entry__36_5, NULL, 700, 700, 5, 23},
  {cont__36_6, &frame__36_5, 701, 701, 5, 62},
  {cont__36_7, &frame__36_5, 701, 701, 5, 29},
  {cont__36_8, &frame__36_5, 703, 703, 8, 20},
  {cont__36_9, &frame__36_5, 703, 703, 8, 37},
  {cont__36_10, &frame__36_5, 703, 716, 5, 44},
  {entry__36_47, NULL, 729, 729, 18, 50},
  {cont__36_48, &frame__36_47, 729, 729, 13, 50},
  {cont__36_49, &frame__36_47, 730, 730, 27, 39},
  {cont__36_50, &frame__36_47, 730, 730, 24, 46},
  {cont__36_51, &frame__36_47, 730, 730, 15, 46},
  {cont__36_52, &frame__36_47, 730, 730, 13, 52},
  {entry__36_46, NULL, 728, 730, 11, 52},
  {entry__36_55, NULL, 731, 731, 43, 63},
  {cont__36_56, &frame__36_55, 731, 731, 39, 64},
  {cont__36_57, &frame__36_55, 731, 731, 39, 64},
  {entry__36_59, NULL, 732, 732, 14, 39},
  {cont__36_60, &frame__36_59, 732, 732, 14, 42},
  {cont__36_61, &frame__36_59, 732, 732, 11, 42},
  {entry__36_64, NULL, 734, 734, 27, 43},
  {cont__36_65, &frame__36_64, 734, 734, 45, 52},
  {cont__36_66, &frame__36_64, 734, 734, 11, 52},
  {entry__36_42, NULL, 725, 725, 9, 28},
  {cont__36_43, &frame__36_42, 726, 726, 9, 43},
  {cont__36_44, &frame__36_42, 727, 727, 12, 27},
  {cont__36_45, &frame__36_42, 727, 730, 9, 53},
  {cont__36_53, &frame__36_42, 731, 731, 12, 34},
  {cont__36_54, &frame__36_42, 731, 731, 12, 64},
  {cont__36_58, &frame__36_42, 731, 732, 9, 42},
  {cont__36_62, &frame__36_42, 733, 733, 18, 39},
  {cont__36_63, &frame__36_42, 733, 734, 9, 52},
  {entry__36_41_print_type_info, NULL, 724, 734, 7, 53},
  {entry__36_73, NULL, 740, 740, 46, 58},
  {cont__36_74, &frame__36_73, 740, 740, 46, 71},
  {cont__36_75, &frame__36_73, 740, 740, 46, 71},
  {entry__36_77, NULL, 741, 741, 11, 30},
  {entry__36_70, NULL, 740, 740, 12, 24},
  {cont__36_71, &frame__36_70, 740, 740, 12, 41},
  {cont__36_72, &frame__36_70, 740, 740, 12, 71},
  {cont__36_76, &frame__36_70, 740, 741, 9, 30},
  {entry__36_69, NULL, 739, 741, 7, 31},
  {entry__36_40, NULL, 736, 736, 5, 12},
  {cont__36_67, &frame__36_40, 737, 737, 5, 19},
  {cont__36_68, &frame__36_40, 738, 741, 5, 32},
  {entry__36_86, NULL, 749, 749, 20, 31},
  {cont__36_88, &frame__36_86, 749, 749, 11, 31},
  {cont__36_89, &frame__36_86, 749, 749, 33, 52},
  {cont__36_90, &frame__36_86, 749, 749, 9, 52},
  {entry__36_91, NULL, 751, 751, 9, 16},
  {entry__36_107, NULL, 761, 761, 22, 41},
  {cont__36_108, &frame__36_107, 761, 761, 17, 41},
  {cont__36_109, &frame__36_107, 762, 762, 19, 35},
  {cont__36_111, &frame__36_107, 762, 762, 17, 66},
  {entry__36_105, NULL, 760, 760, 18, 30},
  {cont__36_106, &frame__36_105, 760, 762, 15, 66},
  {entry__36_102, NULL, 759, 759, 16, 28},
  {cont__36_104, &frame__36_102, 759, 762, 13, 67},
  {entry__36_100, NULL, 757, 757, 11, 26},
  {cont__36_101, &frame__36_100, 758, 762, 11, 68},
  {entry__36_117, NULL, 766, 766, 43, 63},
  {cont__36_118, &frame__36_117, 766, 766, 39, 64},
  {cont__36_119, &frame__36_117, 766, 766, 39, 64},
  {entry__36_121, NULL, 767, 767, 19, 44},
  {cont__36_122, &frame__36_121, 767, 767, 11, 47},
  {cont__36_123, &frame__36_121, 767, 767, 47, 47},
  {entry__36_126, NULL, 773, 773, 13, 25},
  {entry__36_128, NULL, 775, 775, 13, 34},
  {entry__36_130, NULL, 777, 777, 13, 37},
  {entry__36_132, NULL, 779, 779, 13, 28},
  {entry__36_134, NULL, 781, 781, 13, 25},
  {entry__36_136, NULL, 783, 783, 13, 29},
  {entry__36_138, NULL, 785, 785, 13, 31},
  {entry__36_140, NULL, 786, 786, 13, 24},
  {entry__36_145, NULL, 791, 791, 15, 55},
  {cont__36_147, &frame__36_145, 791, 791, 55, 55},
  {entry__36_148, NULL, 793, 793, 31, 31},
  {entry__36_143, NULL, 790, 790, 13, 29},
  {cont__36_144, &frame__36_143, 789, 793, 11, 32},
  {entry__36_151, NULL, 794, 794, 33, 47},
  {cont__36_152, &frame__36_151, 794, 794, 33, 47},
  {entry__36_161, NULL, 797, 797, 31, 42},
  {cont__36_162, &frame__36_161, 797, 797, 28, 49},
  {cont__36_163, &frame__36_161, 797, 797, 19, 49},
  {cont__36_164, &frame__36_161, 797, 797, 51, 68},
  {cont__36_165, &frame__36_161, 797, 797, 17, 68},
  {entry__36_155, NULL, 796, 796, 16, 32},
  {cont__36_158, &frame__36_155, 796, 796, 34, 50},
  {cont__36_159, &frame__36_155, 796, 796, 13, 50},
  {cont__36_160, &frame__36_155, 797, 797, 13, 68},
  {cont__36_166, &frame__36_155, 798, 798, 16, 33},
  {cont__36_168, &frame__36_155, 798, 798, 13, 40},
  {entry__36_154, NULL, 795, 798, 11, 40},
  {entry__36_96, NULL, 756, 756, 12, 19},
  {cont__36_97, &frame__36_96, 756, 756, 12, 29},
  {cont__36_98, &frame__36_96, 756, 756, 12, 29},
  {cont__36_99, &frame__36_96, 756, 762, 9, 69},
  {cont__36_113, &frame__36_96, 764, 764, 9, 27},
  {cont__36_114, &frame__36_96, 765, 765, 9, 43},
  {cont__36_115, &frame__36_96, 766, 766, 12, 34},
  {cont__36_116, &frame__36_96, 766, 766, 12, 64},
  {cont__36_120, &frame__36_96, 766, 767, 9, 47},
  {cont__36_124, &frame__36_96, 771, 771, 13, 25},
  {cont__36_125, &frame__36_96, 769, 786, 9, 25},
  {cont__36_141, &frame__36_96, 788, 788, 12, 31},
  {cont__36_142, &frame__36_96, 788, 793, 9, 33},
  {cont__36_149, &frame__36_96, 794, 794, 12, 28},
  {cont__36_150, &frame__36_96, 794, 794, 12, 47},
  {cont__36_153, &frame__36_96, 794, 798, 9, 41},
  {entry__36_95, NULL, 755, 798, 7, 42},
  {entry__36_80, NULL, 744, 744, 5, 12},
  {cont__36_81, &frame__36_80, 745, 745, 8, 21},
  {cont__36_84, &frame__36_80, 745, 745, 5, 36},
  {cont__36_85, &frame__36_80, 746, 751, 5, 17},
  {cont__36_93, &frame__36_80, 752, 752, 5, 6},
  {cont__36_94, &frame__36_80, 753, 798, 5, 43},
  {entry__36_176, NULL, 805, 805, 26, 53},
  {cont__36_177, &frame__36_176, 805, 805, 9, 65},
  {entry__36_174, NULL, 804, 804, 16, 31},
  {cont__36_175, &frame__36_174, 804, 805, 7, 65},
  {entry__36_170, NULL, 801, 801, 5, 23},
  {cont__36_171, &frame__36_170, 802, 802, 5, 30},
  {cont__36_172, &frame__36_170, 803, 803, 10, 22},
  {cont__36_173, &frame__36_170, 803, 805, 5, 66},
  {entry__36_191, NULL, 813, 813, 19, 35},
  {cont__36_192, &frame__36_191, 813, 813, 17, 41},
  {entry__36_190, NULL, 813, 813, 13, 41},
  {entry__36_185, NULL, 812, 812, 38, 56},
  {cont__36_186, &frame__36_185, 812, 812, 58, 66},
  {cont__36_187, &frame__36_185, 812, 812, 26, 67},
  {cont__36_188, &frame__36_185, 812, 812, 9, 76},
  {cont__36_189, &frame__36_185, 813, 813, 9, 41},
  {entry__36_184, NULL, 811, 813, 7, 41},
  {entry__36_180, NULL, 808, 808, 5, 12},
  {cont__36_181, &frame__36_180, 809, 809, 8, 21},
  {cont__36_182, &frame__36_180, 809, 809, 5, 35},
  {cont__36_183, &frame__36_180, 810, 813, 5, 42},
  {entry__36_206, NULL, 822, 822, 35, 51},
  {cont__36_207, &frame__36_206, 822, 822, 28, 60},
  {cont__36_208, &frame__36_206, 822, 822, 19, 60},
  {cont__36_209, &frame__36_206, 822, 822, 17, 70},
  {entry__36_205, NULL, 822, 822, 13, 70},
  {cont__36_210, &frame__36_205, 823, 823, 13, 23},
  {cont__36_211, &frame__36_205, 824, 824, 16, 44},
  {cont__36_212, &frame__36_205, 824, 824, 13, 44},
  {entry__36_204, NULL, 821, 824, 11, 44},
  {entry__36_203, NULL, 820, 824, 9, 45},
  {entry__36_199, NULL, 817, 817, 7, 14},
  {cont__36_200, &frame__36_199, 818, 818, 10, 23},
  {cont__36_201, &frame__36_199, 818, 818, 7, 29},
  {cont__36_202, &frame__36_199, 819, 824, 7, 46},
  {entry__36_194, NULL, 815, 815, 27, 45},
  {cont__36_195, &frame__36_194, 815, 815, 47, 55},
  {cont__36_196, &frame__36_194, 815, 815, 5, 56},
  {cont__36_197, &frame__36_194, 816, 816, 17, 39},
  {cont__36_198, &frame__36_194, 816, 824, 5, 47},
  {entry__36_218, NULL, 827, 827, 10, 31},
  {cont__36_219, &frame__36_218, 827, 827, 8, 40},
  {entry__36_221, NULL, 828, 828, 10, 35},
  {cont__36_222, &frame__36_221, 828, 828, 8, 48},
  {entry__36_224, NULL, 829, 829, 10, 37},
  {cont__36_225, &frame__36_224, 829, 829, 8, 52},
  {entry__36_227, NULL, 830, 830, 10, 36},
  {cont__36_228, &frame__36_227, 830, 830, 8, 50},
  {entry__36_215, NULL, 826, 826, 5, 19},
  {cont__36_217, &frame__36_215, 827, 827, 5, 40},
  {cont__36_220, &frame__36_215, 828, 828, 5, 48},
  {cont__36_223, &frame__36_215, 829, 829, 5, 52},
  {cont__36_226, &frame__36_215, 830, 830, 5, 50},
  {entry__36_233, NULL, 849, 849, 19, 38},
  {cont__36_234, &frame__36_233, 849, 849, 38, 38},
  {entry__36_235, NULL, 850, 850, 31, 62},
  {cont__36_236, &frame__36_235, 850, 850, 62, 62},
  {entry__36_237, NULL, 851, 851, 32, 64},
  {cont__36_238, &frame__36_237, 851, 851, 64, 64},
  {entry__36_239, NULL, 852, 852, 28, 56},
  {cont__36_240, &frame__36_239, 852, 852, 56, 56},
  {entry__36_241, NULL, 853, 853, 24, 48},
  {cont__36_242, &frame__36_241, 853, 853, 48, 48},
  {entry__36_243, NULL, 854, 854, 26, 52},
  {cont__36_244, &frame__36_243, 854, 854, 52, 52},
  {entry__36_245, NULL, 855, 855, 22, 44},
  {cont__36_246, &frame__36_245, 855, 855, 44, 44},
  {entry__36_247, NULL, 856, 856, 19, 38},
  {cont__36_248, &frame__36_247, 856, 856, 38, 38},
  {entry__36_249, NULL, 857, 857, 19, 38},
  {cont__36_250, &frame__36_249, 857, 857, 38, 38},
  {entry__36_251, NULL, 858, 858, 11, 20},
  {cont__36_252, &frame__36_251, 858, 858, 20, 20},
  {entry__36_259, NULL, 862, 862, 23, 40},
  {cont__36_260, &frame__36_259, 862, 862, 40, 40},
  {entry__36_261, NULL, 863, 863, 32, 58},
  {cont__36_262, &frame__36_261, 863, 863, 58, 58},
  {entry__36_263, NULL, 864, 864, 15, 35},
  {cont__36_264, &frame__36_263, 864, 864, 35, 35},
  {entry__36_257, NULL, 861, 861, 16, 35},
  {cont__36_258, &frame__36_257, 861, 864, 11, 35},
  {entry__36_255, NULL, 860, 860, 18, 33},
  {cont__36_256, &frame__36_255, 860, 864, 9, 36},
  {entry__36_231, NULL, 848, 848, 12, 24},
  {cont__36_232, &frame__36_231, 848, 858, 7, 20},
  {cont__36_253, &frame__36_231, 859, 859, 12, 24},
  {cont__36_254, &frame__36_231, 859, 864, 7, 37},
  {entry__36_230, NULL, 847, 864, 5, 38},
  {cont__36_265, &frame__36_230, },
  {cont__36_266, &frame__36_230, },
  {cont__36_267, &frame__36_230, },
  {cont__36_268, &frame__36_230, },
  {cont__36_269, &frame__36_230, },
  {cont__36_270, &frame__36_230, },
  {cont__36_271, &frame__36_230, },
  {cont__36_272, &frame__36_230, },
  {cont__36_273, &frame__36_230, },
  {cont__36_274, &frame__36_230, },
  {cont__36_275, &frame__36_230, 866, 879, 5, 24},
  {cont__36_276, &frame__36_230, 882, 882, 32, 60},
  {cont__36_277, &frame__36_230, 884, 884, 32, 58},
  {cont__36_278, &frame__36_230, 885, 885, 32, 70},
  {cont__36_279, &frame__36_230, 886, 886, 32, 71},
  {cont__36_280, &frame__36_230, 887, 887, 32, 56},
  {cont__36_281, &frame__36_230, 888, 888, 32, 65},
  {cont__36_282, &frame__36_230, 889, 889, 32, 59},
  {cont__36_283, &frame__36_230, 890, 890, 32, 67},
  {cont__36_284, &frame__36_230, 891, 891, 32, 63},
  {cont__36_285, &frame__36_230, 892, 892, 32, 65},
  {cont__36_286, &frame__36_230, 893, 893, 32, 61},
  {cont__36_287, &frame__36_230, 894, 894, 32, 58},
  {cont__36_288, &frame__36_230, 895, 895, 32, 58},
  {cont__36_289, &frame__36_230, 897, 897, 32, 48},
  {cont__36_290, &frame__36_230, 881, 897, 12, 49},
  {cont__36_305, &frame__36_230, 881, 897, 5, 49},
  {entry__36_1_sim2c__extract_documentation, NULL, 696, 696, 42, 42},
  {cont__36_2, &frame__36_1_sim2c__extract_documentation, 696, 696, 3, 43},
  {cont__36_3, &frame__36_1_sim2c__extract_documentation, 697, 697, 3, 43},
  {cont__36_4, &frame__36_1_sim2c__extract_documentation, 699, 716, 3, 45},
  {cont__36_38, &frame__36_1_sim2c__extract_documentation, 718, 741, 3, 33},
  {cont__36_78, &frame__36_1_sim2c__extract_documentation, 743, 798, 3, 44},
  {cont__36_169, &frame__36_1_sim2c__extract_documentation, 800, 805, 3, 67},
  {cont__36_178, &frame__36_1_sim2c__extract_documentation, 807, 813, 3, 43},
  {cont__36_193, &frame__36_1_sim2c__extract_documentation, 814, 824, 3, 48},
  {cont__36_213, &frame__36_1_sim2c__extract_documentation, 825, 830, 3, 50},
  {cont__36_229, &frame__36_1_sim2c__extract_documentation, 832, 897, 3, 50}
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
  frame->cont = cont__42_1;
}
static void cont__42_1(void) {
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
  // 62: ... sim2c::WHITESPACE, '=', sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__sim2c__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__sim2c__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__56_1;
}
static void cont__56_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 62: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__56_2;
}
static void cont__56_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 63: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__56_3;
}
static void cont__56_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 63: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__56_4;
}
static void cont__56_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 63: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__56_5;
}
static void cont__56_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 61: sequence
  // 62:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 63:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__56_6;
}
static void cont__56_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 57: $PARAMETER_COUNT_OR_MYSELF
  // 58:   alt
  // 59:     '*'
  // 60:     '?'
  // 61:     sequence
  // 62:       alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 63:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__56_7;
}
static void cont__56_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 65: $$path_prefix undefined
  var._path_prefix = get__undefined();
  // 155: types::object $symbol_info
  // 156:   .kind_of BORING
  // 157:   .name_of undefined
  // 158:   .base_of undefined
  // 159:   .parameters_of undefined
  // 160:   .remark_lines_of undefined
  // 161:   .derived_types_of empty_key_order_set
  // 162:   .methods_of empty_key_order_table
  // 163:   .types_of empty_key_order_set
  {
    NODE *temp = clone_object_and_attributes(get__types__object());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._BORING);
    set_attribute_value(temp->attributes, poly_idx__name_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__parameters_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, get__undefined());
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, get__empty_key_order_set());
    set_attribute_value(temp->attributes, poly_idx__methods_of, get__empty_key_order_table());
    set_attribute_value(temp->attributes, poly_idx__types_of, get__empty_key_order_set());
    initialize_future(var._symbol_info, temp);

  }
  // 373: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_333;
  arguments->slots[1] = string__67_1;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__67_2;
}
static void cont__67_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 373: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__67_3;
}
static void cont__67_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 374: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__68_1;
  arguments->slots[1] = string__68_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__68_3;
}
static void cont__68_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 374: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__68_4;
}
static void cont__68_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 374: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__68_5;
}
static void cont__68_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 374: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__68_6;
}
static void cont__68_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 374: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__68_7;
}
static void cont__68_7(void) {
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
  // 70: ... :
  // 71:   HTML:
  // 72:     HEAD:
  // 73:       STYLE "
  // 74:         body {
  // 75:           background-color: white;
  // 76:           font-family: Times New Roman, Times;
  // 77:           font-size: 12pt;
  // 78:           color: #222;
  // 79:         }
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__22_2, 0);
  // 70: collect_output $page:
  // 71:   HTML:
  // 72:     HEAD:
  // 73:       STYLE "
  // 74:         body {
  // 75:           background-color: white;
  // 76:           font-family: Times New Roman, Times;
  // 77:           font-size: 12pt;
  // 78:           color: #222;
  // 79:         }
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
  // 72: HEAD:
  // 73:   STYLE "
  // 74:     body {
  // 75:       background-color: white;
  // 76:       font-family: Times New Roman, Times;
  // 77:       font-size: 12pt;
  // 78:       color: #222;
  // 79:     }
  // 80:     h1 {
  // 81:       font-family: Arial, Helvetica;
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
  // 73: STYLE "
  // 74:   body {
  // 75:     background-color: white;
  // 76:     font-family: Times New Roman, Times;
  // 77:     font-size: 12pt;
  // 78:     color: #222;
  // 79:   }
  // 80:   h1 {
  // 81:     font-family: Arial, Helvetica;
  // 82:     font-size: 20pt;
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
  // 152: BODY body
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
  // 71: ... :
  // 72:   HEAD:
  // 73:     STYLE "
  // 74:       body {
  // 75:         background-color: white;
  // 76:         font-family: Times New Roman, Times;
  // 77:         font-size: 12pt;
  // 78:         color: #222;
  // 79:       }
  // 80:       h1 {
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__22_3, 0);
  // 71: HTML:
  // 72:   HEAD:
  // 73:     STYLE "
  // 74:       body {
  // 75:         background-color: white;
  // 76:         font-family: Times New Roman, Times;
  // 77:         font-size: 12pt;
  // 78:         color: #222;
  // 79:       }
  // 80:       h1 {
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
  // 153: save filename page
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
  // 166: ... "extracting documentation from @(filename)@nl;"
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
  // 166: ewrite "extracting documentation from @(filename)@nl;"
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
  // 167: ... load(filename)
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
  // 167: $buf load(filename).from_utf8
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
  // 168: ... length_of(buf)
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
  // 168: ... length_of(buf) == 0
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
  // 168: if length_of(buf) == 0: Error "Empty source text!"
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
  // 168: ... Error "Empty source text!"
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
  // 169: ... buf(1)
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
  // 169: ... buf(1) <= ' '
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
  // 169: ... buf(1) <= ' '
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
  // 169: if buf(1) <= ' ': Error "Whitespace at start of source text!"
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
  // 169: ... Error "Whitespace at start of source text!"
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
  // 170: ... 1
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
  // 170: ... buf(-1)
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
  // 170: ... buf(-1) != newline
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
  // 170: ... buf(-1) != newline
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
  // 170: if buf(-1) != newline: Error "Missing newline at end of source text!"
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
  // 170: ... Error "Missing newline at end of source text!"
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
  // 173: ... filename .without_suffix. ".sim"
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
  // 173: ... '/' = "__"
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
  // 172: %sim2c::module_name
  // 173:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 174:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
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
  // 176: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 177: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 178: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 179: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 180: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 181: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 182: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 183: $$fragments cut_into_fragments(buf)
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
  // 184: update_each &fragments: (&fragment) tokenize &fragment
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
  // 184: ... tokenize &fragment
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
  // 185: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 186: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 187: ... : (-> done)
  // 188:   for_each fragments: (idx fragment)
  // 189:     case
  // 190:       source_of(fragment)(1)
  // 191:       '#':
  // 192:         !first_idx idx+1 # ignore remark
  // 193:       '<':
  // 194:         !first_idx idx+1
  // 195:         parse_meta_instruction $_tree fragment
  // 196:       :
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_35, 0);
  // 187: do: (-> done)
  // 188:   for_each fragments: (idx fragment)
  // 189:     case
  // 190:       source_of(fragment)(1)
  // 191:       '#':
  // 192:         !first_idx idx+1 # ignore remark
  // 193:       '<':
  // 194:         !first_idx idx+1
  // 195:         parse_meta_instruction $_tree fragment
  // 196:       :
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
  // 188: ... : (idx fragment)
  // 189:   case
  // 190:     source_of(fragment)(1)
  // 191:     '#':
  // 192:       !first_idx idx+1 # ignore remark
  // 193:     '<':
  // 194:       !first_idx idx+1
  // 195:       parse_meta_instruction $_tree fragment
  // 196:     :
  // 197:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__24_36, 2);
  // 188: for_each fragments: (idx fragment)
  // 189:   case
  // 190:     source_of(fragment)(1)
  // 191:     '#':
  // 192:       !first_idx idx+1 # ignore remark
  // 193:     '<':
  // 194:       !first_idx idx+1
  // 195:       parse_meta_instruction $_tree fragment
  // 196:     :
  // 197:       done
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
  // 192: !first_idx idx+1 # ignore remark
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
  // 194: !first_idx idx+1
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
  // 195: parse_meta_instruction $_tree fragment
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
  // 197: done
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
  // 190: source_of(fragment)
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
  // 190: source_of(fragment)(1)
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
  // 191: ... :
  // 192:   !first_idx idx+1 # ignore remark
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_39, 0);
  // 193: ... :
  // 194:   !first_idx idx+1
  // 195:   parse_meta_instruction $_tree fragment
  frame->slots[7] /* temp__4 */ = create_closure(entry__24_41, 0);
  // 196: :
  // 197:   done
  frame->slots[8] /* temp__5 */ = create_closure(entry__24_44, 0);
  // 189: case
  // 190:   source_of(fragment)(1)
  // 191:   '#':
  // 192:     !first_idx idx+1 # ignore remark
  // 193:   '<':
  // 194:     !first_idx idx+1
  // 195:     parse_meta_instruction $_tree fragment
  // 196:   :
  // 197:     done
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
  // 198: ... 1
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
  // 198: range &fragments first_idx -1
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
  // 199: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_49, 1);
  // 199: for_each fragments: (fragment) push &trees parse_statement(fragment)
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
  // 199: ... parse_statement(fragment)
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
  // 199: ... push &trees parse_statement(fragment)
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
  // 200: ... used_namespaces.is_empty
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
  // 200: if used_namespaces.is_empty: !used_namespaces("std") true
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
  // 200: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 200: ... !used_namespaces("std")
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
  // 201: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 202: ... : (statement)
  // 203:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 204:     $destination output_arguments_of(statement)(1)
  // 205:     if destination.is_a_definition:
  // 206:       $identifier identifier_of(destination)
  // 207:       unless namespace_of(identifier).is_defined:
  // 208:         $source arguments_of(statement)(1)
  // 209:         if source.is_a_polymorphic_function_constant:
  // 210:           !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_58, 1);
  // 202: for_each trees: (statement)
  // 203:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 204:     $destination output_arguments_of(statement)(1)
  // 205:     if destination.is_a_definition:
  // 206:       $identifier identifier_of(destination)
  // 207:       unless namespace_of(identifier).is_defined:
  // 208:         $source arguments_of(statement)(1)
  // 209:         if source.is_a_polymorphic_function_constant:
  // 210:           !local_method_names(name_of(identifier_of(destination))) true
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
  // 210: !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 210: ... identifier_of(destination)
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
  // 210: ... name_of(identifier_of(destination))
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
  // 210: !local_method_names(name_of(identifier_of(destination)))
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
  // 208: ... arguments_of(statement)
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
  // 208: $source arguments_of(statement)(1)
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
  // 209: ... source.is_a_polymorphic_function_constant
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
  // 209: ... :
  // 210:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_79, 0);
  // 209: if source.is_a_polymorphic_function_constant:
  // 210:   !local_method_names(name_of(identifier_of(destination))) true
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
  // 206: $identifier identifier_of(destination)
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
  // 207: ... namespace_of(identifier)
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
  // 207: ... namespace_of(identifier).is_defined
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
  // 207: ... :
  // 208:   $source arguments_of(statement)(1)
  // 209:   if source.is_a_polymorphic_function_constant:
  // 210:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_75, 0);
  // 207: unless namespace_of(identifier).is_defined:
  // 208:   $source arguments_of(statement)(1)
  // 209:   if source.is_a_polymorphic_function_constant:
  // 210:     !local_method_names(name_of(identifier_of(destination))) true
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
  // 204: ... output_arguments_of(statement)
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
  // 204: $destination output_arguments_of(statement)(1)
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
  // 205: ... destination.is_a_definition
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
  // 205: ... :
  // 206:   $identifier identifier_of(destination)
  // 207:   unless namespace_of(identifier).is_defined:
  // 208:     $source arguments_of(statement)(1)
  // 209:     if source.is_a_polymorphic_function_constant:
  // 210:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_71, 0);
  // 205: if destination.is_a_definition:
  // 206:   $identifier identifier_of(destination)
  // 207:   unless namespace_of(identifier).is_defined:
  // 208:     $source arguments_of(statement)(1)
  // 209:     if source.is_a_polymorphic_function_constant:
  // 210:       !local_method_names(name_of(identifier_of(destination))) true
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
  // 203: ... pass
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
  // 203: ... pass
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
  // 203: ... statement.is_a_remark
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
  // 203: ... -> statement.is_a_remark: pass
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
  // 203: ... statement.is_c_code
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
  // 203: ... -> statement.is_c_code: pass
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
  // 203: ... statement.is_an_assignment
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
  // 203: ... :
  // 204:   $destination output_arguments_of(statement)(1)
  // 205:   if destination.is_a_definition:
  // 206:     $identifier identifier_of(destination)
  // 207:     unless namespace_of(identifier).is_defined:
  // 208:       $source arguments_of(statement)(1)
  // 209:       if source.is_a_polymorphic_function_constant:
  // 210:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_67, 0);
  // 203: ... -> statement.is_an_assignment:
  // 204:   $destination output_arguments_of(statement)(1)
  // 205:   if destination.is_a_definition:
  // 206:     $identifier identifier_of(destination)
  // 207:     unless namespace_of(identifier).is_defined:
  // 208:       $source arguments_of(statement)(1)
  // 209:       if source.is_a_polymorphic_function_constant:
  // 210:         !local_method_names(name_of(identifier_of(destination))) true
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
  // 203: ... -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__24_59, 0);
  // 203: ... -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_62, 0);
  // 203: ... -> statement.is_an_assignment:
  // 204:   $destination output_arguments_of(statement)(1)
  // 205:   if destination.is_a_definition:
  // 206:     $identifier identifier_of(destination)
  // 207:     unless namespace_of(identifier).is_defined:
  // 208:       $source arguments_of(statement)(1)
  // 209:       if source.is_a_polymorphic_function_constant:
  // 210:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_65, 0);
  // 203: cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 204:   $destination output_arguments_of(statement)(1)
  // 205:   if destination.is_a_definition:
  // 206:     $identifier identifier_of(destination)
  // 207:     unless namespace_of(identifier).is_defined:
  // 208:       $source arguments_of(statement)(1)
  // 209:       if source.is_a_polymorphic_function_constant:
  // 210:         !local_method_names(name_of(identifier_of(destination))) true
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
  // 211: ... :
  // 212:   (
  // 213:     statement
  // 214:     -> break
  // 215:   )
  // 216:   cond
  // 217:     -> statement.is_a_remark: pass
  // 218:     -> statement.is_c_code:
  // 219:       $identifier identifier_of(statement)
  // 220:       if identifier.is_defined:
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__24_84, 1);
  // 211: for_each trees:
  // 212:   (
  // 213:     statement
  // 214:     -> break
  // 215:   )
  // 216:   cond
  // 217:     -> statement.is_a_remark: pass
  // 218:     -> statement.is_c_code:
  // 219:       $identifier identifier_of(statement)
  // 220:       if identifier.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_207;
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
  // 217: -> statement.is_a_remark: pass
  frame->slots[4] /* temp__1 */ = create_closure(entry__24_85, 0);
  // 218: -> statement.is_c_code:
  // 219:   $identifier identifier_of(statement)
  // 220:   if identifier.is_defined:
  // 221:     $namespace namespace_of(identifier)
  // 222:     if namespace.is_defined:
  // 223:       $name name_of(identifier)
  // 224:       case kind_of(statement)
  // 225:         "type":
  // 226:           if namespace.is_defined:
  // 227:             $base base_of(statement)
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_88, 0);
  // 242: -> statement.is_an_assignment:
  // 243:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 244:   $$info symbol_info(.filename_of filename)
  // 245:   if destination.is_a_definition:
  // 246:     $identifier identifier_of(destination)
  // 247:     $namespace namespace_of(identifier)
  // 248:     if namespace.is_defined:
  // 249:       $name name_of(identifier)
  // 250:       $iname ordered_name(namespace name)
  // 251:       !info.name_of identifier.to_string
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__24_119, 0);
  // 216: cond
  // 217:   -> statement.is_a_remark: pass
  // 218:   -> statement.is_c_code:
  // 219:     $identifier identifier_of(statement)
  // 220:     if identifier.is_defined:
  // 221:       $namespace namespace_of(identifier)
  // 222:       if namespace.is_defined:
  // 223:         $name name_of(identifier)
  // 224:         case kind_of(statement)
  // 225:           "type":
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__24_206;
}
static void entry__24_196(void) {
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
  // 308: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_197;
}
static void cont__24_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 308: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_198;
}
static void cont__24_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 308: ... :
  // 309:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__24_199, 0);
  // 308: unless namespace_of(attr).is_defined:
  // 309:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__24_200;
}
static void entry__24_199(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: !attr.used_namespaces_of used_namespaces
  frame->slots[1] /* temp__1 */ = get__used_namespaces();
  // 309: !attr.used_namespaces_of
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
static void cont__24_200(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 310: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_201;
}
static void cont__24_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 310: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__24_202;
}
static void cont__24_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 311: !definition.kind_of INLINE_C_TYPE
  frame->slots[5] /* temp__1 */ = var._INLINE_C_TYPE;
  // 311: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 312: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 312: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__24_203;
}
static void cont__24_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 312: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__24_204;
}
static void cont__24_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 312: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 313: !definitions(iname) definition
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* definition */;
  // 313: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_205;
}
static void cont__24_205(void) {
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
static void entry__24_193(void) {
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
  // 306: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_194;
}
static void cont__24_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 307: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__24_195;
}
static void cont__24_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 307: ... :
  // 308:   unless namespace_of(attr).is_defined:
  // 309:     !attr.used_namespaces_of used_namespaces
  // 310:   $$definition default_value(definitions(iname) symbol_info)
  // 311:   !definition.kind_of INLINE_C_TYPE
  // 312:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 313:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_196, 0);
  // 307: unless local_method_names(attr_name):
  // 308:   unless namespace_of(attr).is_defined:
  // 309:     !attr.used_namespaces_of used_namespaces
  // 310:   $$definition default_value(definitions(iname) symbol_info)
  // 311:   !definition.kind_of INLINE_C_TYPE
  // 312:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 313:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_187(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // destination: 0
  // iname: 1
  // local_method_names: 2
  // info: 3
  // attr: 4
  // type: 5
  frame->slots[0] = myself->closure.frame->slots[5]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[6]; /* local_method_names */
  frame->slots[3] = myself->closure.frame->slots[2]; /* info */
  frame->slots[4] /* attr */ = create_cell();
  frame->slots[5] /* type */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__24_188;
}
static void cont__24_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 302: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_189;
}
static void cont__24_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 302: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__24_190;
}
static void cont__24_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 301: $type
  // 302:   default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 304: !definitions(iname) type
  frame->slots[6] /* temp__1 */ = frame->slots[5] /* type */;
  // 304: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_191;
}
static void cont__24_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 305: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_192;
}
static void cont__24_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   $attr_name attr.to_string
  // 307:   unless local_method_names(attr_name):
  // 308:     unless namespace_of(attr).is_defined:
  // 309:       !attr.used_namespaces_of used_namespaces
  // 310:     $$definition default_value(definitions(iname) symbol_info)
  // 311:     !definition.kind_of INLINE_C_TYPE
  // 312:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 313:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_193, 0);
  // 305: if attr.is_defined:
  // 306:   $attr_name attr.to_string
  // 307:   unless local_method_names(attr_name):
  // 308:     unless namespace_of(attr).is_defined:
  // 309:       !attr.used_namespaces_of used_namespaces
  // 310:     $$definition default_value(definitions(iname) symbol_info)
  // 311:     !definition.kind_of INLINE_C_TYPE
  // 312:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 313:     !definitions(iname) definition
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
  allocate_initialized_frame_gc(7, 15);
  // slot allocations:
  // identifier: 0
  // namespace: 1
  // info: 2
  // statement: 3
  // break: 4
  // destination: 5
  // local_method_names: 6
  // name: 7
  // iname: 8
  // source: 9
  frame->slots[0] = myself->closure.frame->slots[5]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[6]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[1]; /* info */
  frame->slots[3] = myself->closure.frame->slots[2]; /* statement */
  frame->slots[4] = myself->closure.frame->slots[3]; /* break */
  frame->slots[5] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[6] = myself->closure.frame->slots[4]; /* local_method_names */
  frame->slots[7] /* name */ = create_future();
  frame->slots[8] /* iname */ = create_future();
  frame->slots[9] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 249: $name name_of(identifier)
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
  // 250: $iname ordered_name(namespace name)
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
  // 251: !info.name_of identifier.to_string
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
  // 251: !info.name_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[10] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 252: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__24_133;
}
static void cont__24_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 252: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__24_134;
}
static void cont__24_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* source */, arguments->slots[0]);
  // 254: -> source.is_a_polymorphic_function_constant:
  // 255:   !polymorphic_functions(name namespace) true
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of
  // 259:         if
  // 260:           source.is_a_setter
  // 261:           -> POLYMORPHIC_ATTRIBUTE
  // 262:           -> POLYMORPHIC_FUNCTION
  // 263:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[10] /* temp__1 */ = create_closure(entry__24_135, 0);
  // 265: -> source.is_a_body:
  // 266:   !info.base_of "types::function"
  // 267:   !info.kind_of FUNCTION
  // 268:   !info.parameters_of parameters_of(source)
  // 269:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[11] /* temp__2 */ = create_closure(entry__24_145, 0);
  // 270: -> source.is_a_c_body:
  // 271:   !info.kind_of INLINE_C_FUNCTION
  // 272:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[12] /* temp__3 */ = create_closure(entry__24_151, 0);
  // 273: -> source.is_an_identifier:
  // 274:   if namespace_of(source).is_defined:
  // 275:     !info
  // 276:       .base_of source.to_string
  // 277:       .remark_lines_of remark_lines_of(statement)
  frame->slots[13] /* temp__4 */ = create_closure(entry__24_155, 0);
  // 278: -> source.is_a_constant:
  // 279:   !definitions(iname)
  // 280:     info
  // 281:       .kind_of
  // 282:         if
  // 283:           source.is_a_unique_item_constant
  // 284:           -> UNIQUE_ITEM
  // 285:           -> CONSTANT
  // 286:       .remark_lines_of remark_lines_of(statement)
  // 287:   break
  frame->slots[14] /* temp__5 */ = create_closure(entry__24_163, 0);
  // 253: cond
  // 254:   -> source.is_a_polymorphic_function_constant:
  // 255:     !polymorphic_functions(name namespace) true
  // 256:     !definitions(iname)
  // 257:       info
  // 258:         .kind_of
  // 259:           if
  // 260:             source.is_a_setter
  // 261:             -> POLYMORPHIC_ATTRIBUTE
  // 262:             -> POLYMORPHIC_FUNCTION
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__1 */;
  arguments->slots[1] = frame->slots[11] /* temp__2 */;
  arguments->slots[2] = frame->slots[12] /* temp__3 */;
  arguments->slots[3] = frame->slots[13] /* temp__4 */;
  arguments->slots[4] = frame->slots[14] /* temp__5 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__24_172;
}
static void entry__24_165(void) {
  allocate_initialized_frame_gc(5, 9);
  // slot allocations:
  // iname: 0
  // info: 1
  // source: 2
  // statement: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[1]; /* iname */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* source */
  frame->slots[3] = myself->closure.frame->slots[3]; /* statement */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 283: source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__24_166;
}
static void cont__24_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 282: if
  // 283:   source.is_a_unique_item_constant
  // 284:   -> UNIQUE_ITEM
  // 285:   -> CONSTANT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__24_167;
  arguments->slots[2] = func__24_168;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_169;
}
static void entry__24_167(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: -> UNIQUE_ITEM
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._UNIQUE_ITEM;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_168(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: -> CONSTANT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._CONSTANT;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 286: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_170;
}
static void cont__24_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 279: !definitions(iname)
  // 280:   info
  // 281:     .kind_of
  // 282:       if
  // 283:         source.is_a_unique_item_constant
  // 284:         -> UNIQUE_ITEM
  // 285:         -> CONSTANT
  // 286:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[7] /* temp__3 */);
    frame->slots[8] /* temp__4 */ = temp;

  }
  // 279: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
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
  // 287: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_160(void) {
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
  // 276: ... source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_161;
}
static void cont__24_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 277: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_162;
}
static void cont__24_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 275: !info
  // 276:   .base_of source.to_string
  // 277:   .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[3] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_157(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // source: 0
  // info: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 274: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_158;
}
static void cont__24_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 274: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_159;
}
static void cont__24_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 274: ... :
  // 275:   !info
  // 276:     .base_of source.to_string
  // 277:     .remark_lines_of remark_lines_of(statement)
  frame->slots[5] /* temp__3 */ = create_closure(entry__24_160, 0);
  // 274: if namespace_of(source).is_defined:
  // 275:   !info
  // 276:     .base_of source.to_string
  // 277:     .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_153(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // info: 0
  // statement: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 271: !info.kind_of INLINE_C_FUNCTION
  frame->slots[2] /* temp__1 */ = var._INLINE_C_FUNCTION;
  // 271: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 272: !info.remark_lines_of remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_154;
}
static void cont__24_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 272: !info.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_147(void) {
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
  // 266: !info.base_of "types::function"
  frame->slots[2] /* temp__1 */ = string__24_148;
  // 266: !info.base_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 267: !info.kind_of FUNCTION
  frame->slots[2] /* temp__1 */ = var._FUNCTION;
  // 267: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 268: !info.parameters_of parameters_of(source)
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 268: !info.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 269: !info.remark_lines_of remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 269: !info.remark_lines_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_137(void) {
  allocate_initialized_frame_gc(7, 11);
  // slot allocations:
  // name: 0
  // namespace: 1
  // iname: 2
  // info: 3
  // source: 4
  // statement: 5
  // break: 6
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[3]; /* iname */
  frame->slots[3] = myself->closure.frame->slots[4]; /* info */
  frame->slots[4] = myself->closure.frame->slots[0]; /* source */
  frame->slots[5] = myself->closure.frame->slots[5]; /* statement */
  frame->slots[6] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 255: !polymorphic_functions(name namespace) true
  frame->slots[7] /* temp__1 */ = get__true();
  // 255: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__24_138;
}
static void cont__24_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 260: source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__24_139;
}
static void cont__24_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 259: if
  // 260:   source.is_a_setter
  // 261:   -> POLYMORPHIC_ATTRIBUTE
  // 262:   -> POLYMORPHIC_FUNCTION
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = func__24_140;
  arguments->slots[2] = func__24_141;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_142;
}
static void entry__24_140(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 261: -> POLYMORPHIC_ATTRIBUTE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_ATTRIBUTE;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_141(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 262: -> POLYMORPHIC_FUNCTION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 263: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__24_143;
}
static void cont__24_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 256: !definitions(iname)
  // 257:   info
  // 258:     .kind_of
  // 259:       if
  // 260:         source.is_a_setter
  // 261:         -> POLYMORPHIC_ATTRIBUTE
  // 262:         -> POLYMORPHIC_FUNCTION
  // 263:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[7] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[9] /* temp__3 */);
    frame->slots[10] /* temp__4 */ = temp;

  }
  // 256: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_144;
}
static void cont__24_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 264: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[6] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_135(void) {
  allocate_initialized_frame_gc(7, 9);
  // slot allocations:
  // source: 0
  // name: 1
  // namespace: 2
  // iname: 3
  // info: 4
  // statement: 5
  // break: 6
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[7]; /* name */
  frame->slots[2] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[4] = myself->closure.frame->slots[2]; /* info */
  frame->slots[5] = myself->closure.frame->slots[3]; /* statement */
  frame->slots[6] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 254: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__24_136;
}
static void cont__24_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 254: ... :
  // 255:   !polymorphic_functions(name namespace) true
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of
  // 259:         if
  // 260:           source.is_a_setter
  // 261:           -> POLYMORPHIC_ATTRIBUTE
  // 262:           -> POLYMORPHIC_FUNCTION
  // 263:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__24_137, 0);
  // 254: -> source.is_a_polymorphic_function_constant:
  // 255:   !polymorphic_functions(name namespace) true
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of
  // 259:         if
  // 260:           source.is_a_setter
  // 261:           -> POLYMORPHIC_ATTRIBUTE
  // 262:           -> POLYMORPHIC_FUNCTION
  // 263:       .remark_lines_of remark_lines_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_145(void) {
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
  // 265: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__24_146;
}
static void cont__24_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   !info.base_of "types::function"
  // 267:   !info.kind_of FUNCTION
  // 268:   !info.parameters_of parameters_of(source)
  // 269:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_147, 0);
  // 265: -> source.is_a_body:
  // 266:   !info.base_of "types::function"
  // 267:   !info.kind_of FUNCTION
  // 268:   !info.parameters_of parameters_of(source)
  // 269:   !info.remark_lines_of remark_lines_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_151(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // info: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[3]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 270: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__24_152;
}
static void cont__24_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 270: ... :
  // 271:   !info.kind_of INLINE_C_FUNCTION
  // 272:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_153, 0);
  // 270: -> source.is_a_c_body:
  // 271:   !info.kind_of INLINE_C_FUNCTION
  // 272:   !info.remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_155(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // source: 0
  // info: 1
  // statement: 2
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[3]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__24_156;
}
static void cont__24_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 273: ... :
  // 274:   if namespace_of(source).is_defined:
  // 275:     !info
  // 276:       .base_of source.to_string
  // 277:       .remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_157, 0);
  // 273: -> source.is_an_identifier:
  // 274:   if namespace_of(source).is_defined:
  // 275:     !info
  // 276:       .base_of source.to_string
  // 277:       .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_163(void) {
  allocate_initialized_frame_gc(5, 7);
  // slot allocations:
  // source: 0
  // iname: 1
  // info: 2
  // statement: 3
  // break: 4
  frame->slots[0] = myself->closure.frame->slots[9]; /* source */
  frame->slots[1] = myself->closure.frame->slots[8]; /* iname */
  frame->slots[2] = myself->closure.frame->slots[2]; /* info */
  frame->slots[3] = myself->closure.frame->slots[3]; /* statement */
  frame->slots[4] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__24_164;
}
static void cont__24_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 278: ... :
  // 279:   !definitions(iname)
  // 280:     info
  // 281:       .kind_of
  // 282:         if
  // 283:           source.is_a_unique_item_constant
  // 284:           -> UNIQUE_ITEM
  // 285:           -> CONSTANT
  // 286:       .remark_lines_of remark_lines_of(statement)
  // 287:   break
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_165, 0);
  // 278: -> source.is_a_constant:
  // 279:   !definitions(iname)
  // 280:     info
  // 281:       .kind_of
  // 282:         if
  // 283:           source.is_a_unique_item_constant
  // 284:           -> UNIQUE_ITEM
  // 285:           -> CONSTANT
  // 286:       .remark_lines_of remark_lines_of(statement)
  // 287:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_172(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 289: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__24_173;
}
static void cont__24_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 290: ... :
  // 291:   $previous_definition definitions(iname)
  // 292:   if previous_definition.is_defined:
  // 293:     if kind_of(previous_definition) == INLINE_C_TYPE:
  // 294:       !info.types_of types_of(previous_definition)
  // 295:       !info.derived_types_of derived_types_of(previous_definition)
  // 296:       !info.methods_of methods_of(previous_definition)
  // 297:   !definitions(iname) info
  frame->slots[11] /* temp__2 */ = create_closure(entry__24_174, 0);
  // 298: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__24_186;
}
static void entry__24_174(void) {
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
  // 291: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_175;
}
static void cont__24_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 292: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_176;
}
static void cont__24_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 292: ... :
  // 293:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 294:     !info.types_of types_of(previous_definition)
  // 295:     !info.derived_types_of derived_types_of(previous_definition)
  // 296:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_177, 0);
  // 292: if previous_definition.is_defined:
  // 293:   if kind_of(previous_definition) == INLINE_C_TYPE:
  // 294:     !info.types_of types_of(previous_definition)
  // 295:     !info.derived_types_of derived_types_of(previous_definition)
  // 296:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_184;
}
static void entry__24_180(void) {
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
  // 294: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__24_181;
}
static void cont__24_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 294: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 295: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__24_182;
}
static void cont__24_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 295: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 296: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__24_183;
}
static void cont__24_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 296: !info.methods_of
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
static void entry__24_177(void) {
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
  // 293: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__24_178;
}
static void cont__24_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 293: ... kind_of(previous_definition) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__24_179;
}
static void cont__24_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   !info.types_of types_of(previous_definition)
  // 295:   !info.derived_types_of derived_types_of(previous_definition)
  // 296:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_180, 0);
  // 293: if kind_of(previous_definition) == INLINE_C_TYPE:
  // 294:   !info.types_of types_of(previous_definition)
  // 295:   !info.derived_types_of derived_types_of(previous_definition)
  // 296:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_184(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 297: !definitions(iname) info
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* info */;
  // 297: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__24_185;
}
static void cont__24_185(void) {
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
static void cont__24_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 298: ... :
  // 299:   $$attr attribute_of(destination)
  // 300:   
  // 301:   $type
  // 302:     default_value(definitions(iname) symbol_info)(.kind_of INLINE_C_TYPE)
  // 303:   
  // 304:   !definitions(iname) type
  // 305:   if attr.is_defined:
  // 306:     $attr_name attr.to_string
  // 307:     unless local_method_names(attr_name):
  // ...
  frame->slots[13] /* temp__4 */ = create_closure(entry__24_187, 0);
  // 288: case
  // 289:   attribute_kind_of(destination)
  // 290:   NONE:
  // 291:     $previous_definition definitions(iname)
  // 292:     if previous_definition.is_defined:
  // 293:       if kind_of(previous_definition) == INLINE_C_TYPE:
  // 294:         !info.types_of types_of(previous_definition)
  // 295:         !info.derived_types_of derived_types_of(previous_definition)
  // 296:         !info.methods_of methods_of(previous_definition)
  // 297:     !definitions(iname) info
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
  // 246: $identifier identifier_of(destination)
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
  // 247: $namespace namespace_of(identifier)
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
  // 248: ... namespace.is_defined
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
  // 248: ... :
  // 249:   $name name_of(identifier)
  // 250:   $iname ordered_name(namespace name)
  // 251:   !info.name_of identifier.to_string
  // 252:   $source arguments_of(statement)(1)
  // 253:   cond
  // 254:     -> source.is_a_polymorphic_function_constant:
  // 255:       !polymorphic_functions(name namespace) true
  // 256:       !definitions(iname)
  // 257:         info
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__24_129, 0);
  // 248: if namespace.is_defined:
  // 249:   $name name_of(identifier)
  // 250:   $iname ordered_name(namespace name)
  // 251:   !info.name_of identifier.to_string
  // 252:   $source arguments_of(statement)(1)
  // 253:   cond
  // 254:     -> source.is_a_polymorphic_function_constant:
  // 255:       !polymorphic_functions(name namespace) true
  // 256:       !definitions(iname)
  // 257:         info
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
  // 243: ... output_arguments_of(statement)
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
  // 243: ... output_arguments_of(statement)(1)
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
  // 243: $destination output_arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 244: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 245: ... destination.is_a_definition
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
  // 245: ... :
  // 246:   $identifier identifier_of(destination)
  // 247:   $namespace namespace_of(identifier)
  // 248:   if namespace.is_defined:
  // 249:     $name name_of(identifier)
  // 250:     $iname ordered_name(namespace name)
  // 251:     !info.name_of identifier.to_string
  // 252:     $source arguments_of(statement)(1)
  // 253:     cond
  // 254:       -> source.is_a_polymorphic_function_constant:
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__24_125, 0);
  // 245: if destination.is_a_definition:
  // 246:   $identifier identifier_of(destination)
  // 247:   $namespace namespace_of(identifier)
  // 248:   if namespace.is_defined:
  // 249:     $name name_of(identifier)
  // 250:     $iname ordered_name(namespace name)
  // 251:     !info.name_of identifier.to_string
  // 252:     $source arguments_of(statement)(1)
  // 253:     cond
  // 254:       -> source.is_a_polymorphic_function_constant:
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
  // 227: $base base_of(statement)
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
  // 231: ... identifier.to_string
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
  // 232: ... base.is_defined
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
  // 232: ... -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__24_105, 0);
  // 232: ... if(base.is_defined (-> base.to_string) -> undefined)
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
  // 232: ... base.to_string
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
  // 232: ... -> base.to_string
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
  // 232: ... -> undefined
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
  // 233: ... remark_lines_of(statement)
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
  // 228: !definitions(ordered_name(namespace name))
  // 229:   symbol_info
  // 230:     .kind_of INLINE_C_TYPE
  // 231:     .name_of identifier.to_string
  // 232:     .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 233:     .remark_lines_of remark_lines_of(statement)
  // 234:     .filename_of filename
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
  // 228: ... ordered_name(namespace name)
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
  // 228: !definitions(ordered_name(namespace name))
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
  // 226: ... namespace.is_defined
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
  // 226: ... :
  // 227:   $base base_of(statement)
  // 228:   !definitions(ordered_name(namespace name))
  // 229:     symbol_info
  // 230:       .kind_of INLINE_C_TYPE
  // 231:       .name_of identifier.to_string
  // 232:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 233:       .remark_lines_of remark_lines_of(statement)
  // 234:       .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_101, 0);
  // 226: if namespace.is_defined:
  // 227:   $base base_of(statement)
  // 228:   !definitions(ordered_name(namespace name))
  // 229:     symbol_info
  // 230:       .kind_of INLINE_C_TYPE
  // 231:       .name_of identifier.to_string
  // 232:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 233:       .remark_lines_of remark_lines_of(statement)
  // 234:       .filename_of filename
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
  // 239: ... identifier.to_string
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
  // 240: ... remark_lines_of(statement)
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
  // 236: !definitions(ordered_name(namespace name))
  // 237:   symbol_info
  // 238:     .kind_of INLINE_C_OBJECT
  // 239:     .name_of identifier.to_string
  // 240:     .remark_lines_of remark_lines_of(statement)
  // 241:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._INLINE_C_OBJECT);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[4] /* filename */);
    frame->slots[7] /* temp__3 */ = temp;

  }
  // 236: ... ordered_name(namespace name)
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
  // 236: !definitions(ordered_name(namespace name))
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
  // 223: $name name_of(identifier)
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
  // 224: ... kind_of(statement)
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
  // 225: ... :
  // 226:   if namespace.is_defined:
  // 227:     $base base_of(statement)
  // 228:     !definitions(ordered_name(namespace name))
  // 229:       symbol_info
  // 230:         .kind_of INLINE_C_TYPE
  // 231:         .name_of identifier.to_string
  // 232:         .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 233:         .remark_lines_of remark_lines_of(statement)
  // 234:         .filename_of filename
  frame->slots[6] /* temp__2 */ = create_closure(entry__24_99, 0);
  // 235: ... :
  // 236:   !definitions(ordered_name(namespace name))
  // 237:     symbol_info
  // 238:       .kind_of INLINE_C_OBJECT
  // 239:       .name_of identifier.to_string
  // 240:       .remark_lines_of remark_lines_of(statement)
  // 241:       .filename_of filename
  frame->slots[7] /* temp__3 */ = create_closure(entry__24_112, 0);
  // 224: case kind_of(statement)
  // 225:   "type":
  // 226:     if namespace.is_defined:
  // 227:       $base base_of(statement)
  // 228:       !definitions(ordered_name(namespace name))
  // 229:         symbol_info
  // 230:           .kind_of INLINE_C_TYPE
  // 231:           .name_of identifier.to_string
  // 232:           .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 233:           .remark_lines_of remark_lines_of(statement)
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
  // 221: $namespace namespace_of(identifier)
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
  // 222: ... namespace.is_defined
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
  // 222: ... :
  // 223:   $name name_of(identifier)
  // 224:   case kind_of(statement)
  // 225:     "type":
  // 226:       if namespace.is_defined:
  // 227:         $base base_of(statement)
  // 228:         !definitions(ordered_name(namespace name))
  // 229:           symbol_info
  // 230:             .kind_of INLINE_C_TYPE
  // 231:             .name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_96, 0);
  // 222: if namespace.is_defined:
  // 223:   $name name_of(identifier)
  // 224:   case kind_of(statement)
  // 225:     "type":
  // 226:       if namespace.is_defined:
  // 227:         $base base_of(statement)
  // 228:         !definitions(ordered_name(namespace name))
  // 229:           symbol_info
  // 230:             .kind_of INLINE_C_TYPE
  // 231:             .name_of identifier.to_string
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
  // 219: $identifier identifier_of(statement)
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
  // 220: ... identifier.is_defined
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
  // 220: ... :
  // 221:   $namespace namespace_of(identifier)
  // 222:   if namespace.is_defined:
  // 223:     $name name_of(identifier)
  // 224:     case kind_of(statement)
  // 225:       "type":
  // 226:         if namespace.is_defined:
  // 227:           $base base_of(statement)
  // 228:           !definitions(ordered_name(namespace name))
  // 229:             symbol_info
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_93, 0);
  // 220: if identifier.is_defined:
  // 221:   $namespace namespace_of(identifier)
  // 222:   if namespace.is_defined:
  // 223:     $name name_of(identifier)
  // 224:     case kind_of(statement)
  // 225:       "type":
  // 226:         if namespace.is_defined:
  // 227:           $base base_of(statement)
  // 228:           !definitions(ordered_name(namespace name))
  // 229:             symbol_info
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
  // 217: ... pass
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
  // 217: ... statement.is_a_remark
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
  // 217: -> statement.is_a_remark: pass
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
  // 218: ... statement.is_c_code
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
  // 218: ... :
  // 219:   $identifier identifier_of(statement)
  // 220:   if identifier.is_defined:
  // 221:     $namespace namespace_of(identifier)
  // 222:     if namespace.is_defined:
  // 223:       $name name_of(identifier)
  // 224:       case kind_of(statement)
  // 225:         "type":
  // 226:           if namespace.is_defined:
  // 227:             $base base_of(statement)
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__24_90, 0);
  // 218: -> statement.is_c_code:
  // 219:   $identifier identifier_of(statement)
  // 220:   if identifier.is_defined:
  // 221:     $namespace namespace_of(identifier)
  // 222:     if namespace.is_defined:
  // 223:       $name name_of(identifier)
  // 224:       case kind_of(statement)
  // 225:         "type":
  // 226:           if namespace.is_defined:
  // 227:             $base base_of(statement)
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
  // 242: ... statement.is_an_assignment
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
  // 242: ... :
  // 243:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 244:   $$info symbol_info(.filename_of filename)
  // 245:   if destination.is_a_definition:
  // 246:     $identifier identifier_of(destination)
  // 247:     $namespace namespace_of(identifier)
  // 248:     if namespace.is_defined:
  // 249:       $name name_of(identifier)
  // 250:       $iname ordered_name(namespace name)
  // 251:       !info.name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__24_121, 0);
  // 242: -> statement.is_an_assignment:
  // 243:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 244:   $$info symbol_info(.filename_of filename)
  // 245:   if destination.is_a_definition:
  // 246:     $identifier identifier_of(destination)
  // 247:     $namespace namespace_of(identifier)
  // 248:     if namespace.is_defined:
  // 249:       $name name_of(identifier)
  // 250:       $iname ordered_name(namespace name)
  // 251:       !info.name_of identifier.to_string
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__24_206(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__24_207(void) {
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
  // 320: ... extract_documentation_from_file name
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
  // 319: ... extract_documentation_from_directory name
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
  // 319: ... entry.is_a_directory
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
  // 319: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_8, 0);
  // 319: -> entry.is_a_directory: extract_documentation_from_directory name
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
  // 320: ... name .has_suffix. ".sim"
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
  // 320: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_11, 0);
  // 320: -> name .has_suffix. ".sim": extract_documentation_from_file name
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
  // 317: $name fullname_of(entry)
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
  // 319: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__25_6, 0);
  // 320: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__25_9, 0);
  // 318: cond
  // 319:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 320:   -> name .has_suffix. ".sim": extract_documentation_from_file name
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
  // 316: ... --SORT
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
  // 316: ... directory(--SORT path)
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
  // 316: for_each directory(--SORT path): (entry)
  // 317:   $name fullname_of(entry)
  // 318:   cond
  // 319:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 320:     -> name .has_suffix. ".sim": extract_documentation_from_file name
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
  // 324: ... attr.to_string
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
  // 324: ... -> attr.to_string
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
  // 325: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 326: ... used_namespaces_of(attr)
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
  // 326: ... : (namespace)
  // 327:   if polymorphic_functions(name namespace):
  // 328:     if resolved_namespace.is_defined:
  // 329:       Error "
  // 330:         The attribute "@(name)" cannot be uniquely resolved!
  // 331:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_9, 1);
  // 326: for_each used_namespaces_of(attr): (namespace)
  // 327:   if polymorphic_functions(name namespace):
  // 328:     if resolved_namespace.is_defined:
  // 329:       Error "
  // 330:         The attribute "@(name)" cannot be uniquely resolved!
  // 331:     !resolved_namespace namespace
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
  // 328: ... resolved_namespace.is_defined
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
  // 328: ... :
  // 329:   Error "
  // 330:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_13, 0);
  // 328: if resolved_namespace.is_defined:
  // 329:   Error "
  // 330:     The attribute "@(name)" cannot be uniquely resolved!
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
  // 329: ... "
  // 330:   The attribute "@(name)" cannot be uniquely resolved!
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
  // 329: Error "
  // 330:   The attribute "@(name)" cannot be uniquely resolved!
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
  // 331: !resolved_namespace namespace
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
  // 327: ... polymorphic_functions(name namespace)
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
  // 327: ... :
  // 328:   if resolved_namespace.is_defined:
  // 329:     Error "
  // 330:       The attribute "@(name)" cannot be uniquely resolved!
  // 331:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_11, 0);
  // 327: if polymorphic_functions(name namespace):
  // 328:   if resolved_namespace.is_defined:
  // 329:     Error "
  // 330:       The attribute "@(name)" cannot be uniquely resolved!
  // 331:   !resolved_namespace namespace
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
  // 332: ... resolved_namespace.is_defined
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
  // 332: ... :
  // 333:   Error "
  // 334:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__26_20, 0);
  // 332: unless resolved_namespace.is_defined:
  // 333:   Error "
  // 334:     The attribute "@(name)" cannot be resolved!
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
  // 333: ... "
  // 334:   The attribute "@(name)" cannot be resolved!
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
  // 333: Error "
  // 334:   The attribute "@(name)" cannot be resolved!
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
  // 335: ... string(resolved_namespace "::" name)
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
  // 335: -> string(resolved_namespace "::" name)
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
  // 323: $name name_of(attr)
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
  // 324: ... namespace_of(attr)
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
  // 324: ... namespace_of(attr).is_defined
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
  // 324: ... -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__26_5, 0);
  // 324: ... :
  // 325:   $$resolved_namespace undefined
  // 326:   for_each used_namespaces_of(attr): (namespace)
  // 327:     if polymorphic_functions(name namespace):
  // 328:       if resolved_namespace.is_defined:
  // 329:         Error "
  // 330:           The attribute "@(name)" cannot be uniquely resolved!
  // 331:       !resolved_namespace namespace
  // 332:   unless resolved_namespace.is_defined:
  // 333:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__26_7, 0);
  // 324: if namespace_of(attr).is_defined (-> attr.to_string):
  // 325:   $$resolved_namespace undefined
  // 326:   for_each used_namespaces_of(attr): (namespace)
  // 327:     if polymorphic_functions(name namespace):
  // 328:       if resolved_namespace.is_defined:
  // 329:         Error "
  // 330:           The attribute "@(name)" cannot be uniquely resolved!
  // 331:       !resolved_namespace namespace
  // 332:   unless resolved_namespace.is_defined:
  // 333:     Error "
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
  // 341: !definition.derived_types_of(name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 341: ... definition.derived_types_of
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
  // 341: !definition.derived_types_of(name)
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
  // 341: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 342: ... kind_of(definition)
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
  // 342: ... kind_of(definition) == INLINE_C_TYPE
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
  // 342: ... :
  // 343:   !definition.kind_of INLINE_C_TYPE
  // 344:   $base_of_base base_of(definition)
  // 345:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__27_12, 0);
  // 342: unless kind_of(definition) == INLINE_C_TYPE:
  // 343:   !definition.kind_of INLINE_C_TYPE
  // 344:   $base_of_base base_of(definition)
  // 345:   if base_of_base.is_defined: add_derived_type base_of_base ibase
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
  // 345: ... add_derived_type base_of_base ibase
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
  // 343: !definition.kind_of INLINE_C_TYPE
  frame->slots[3] /* temp__1 */ = var._INLINE_C_TYPE;
  // 343: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 344: $base_of_base base_of(definition)
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
  // 345: ... base_of_base.is_defined
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
  // 345: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__27_15, 0);
  // 345: if base_of_base.is_defined: add_derived_type base_of_base ibase
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
  // 346: !definitions(ibase) definition
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* definition */;
  // 346: !definitions(ibase)
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
  // 338: ... base .before. "::"
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
  // 338: ... base .behind. "::"
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
  // 338: $ibase ordered_name(base .before. "::" base .behind. "::")
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
  // 339: $$definition definitions(ibase)
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
  // 340: ... definition.is_defined
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
  // 340: ... :
  // 341:   !definition.derived_types_of(name) true
  // 342:   unless kind_of(definition) == INLINE_C_TYPE:
  // 343:     !definition.kind_of INLINE_C_TYPE
  // 344:     $base_of_base base_of(definition)
  // 345:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 346:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__27_7, 0);
  // 340: if definition.is_defined:
  // 341:   !definition.derived_types_of(name) true
  // 342:   unless kind_of(definition) == INLINE_C_TYPE:
  // 343:     !definition.kind_of INLINE_C_TYPE
  // 344:     $base_of_base base_of(definition)
  // 345:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 346:   !definitions(ibase) definition
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
  // 348: ... "::" = "__"
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
  // 348: ... '/' = "___"
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
  // 348: ... replace_all(name "::" = "__" '/' = "___")
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
  // 348: ... -> replace_all(name "::" = "__" '/' = "___")
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
  // 353: name.to_lower_case
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
  // 355: namespace.to_lower_case
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
  // 352: string
  // 353:   name.to_lower_case
  // 354:   '/'
  // 355:   namespace.to_lower_case
  // 356:   '/'
  // 357:   name
  // 358:   '/'
  // 359:   namespace
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
  // 351: ->
  // 352:   string
  // 353:     name.to_lower_case
  // 354:     '/'
  // 355:     namespace.to_lower_case
  // 356:     '/'
  // 357:     name
  // 358:     '/'
  // 359:     namespace
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
  // 363: ... "href" = "index.html"
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
  // 363: A "href" = "index.html" "Home"
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
  // 364: TEXT "&nbsp;&nbsp;&nbsp;"
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
  // 365: ... "href" = "manual.html"
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
  // 365: A "href" = "manual.html" "Manual"
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
  // 366: TEXT "&nbsp;&nbsp;&nbsp;"
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
  // 367: ... "href" = "type_index.html"
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
  // 367: A "href" = "type_index.html" "Type Index"
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
  // 368: TEXT "&nbsp;&nbsp;&nbsp;"
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
  // 369: ... "href" = "symbol_index.html"
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
  // 369: A "href" = "symbol_index.html" "Symbol Index"
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
  // 370: TEXT "&nbsp;&nbsp;&nbsp;"
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
  // 371: ... "href" = "topic_index.html"
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
  // 371: A "href" = "topic_index.html" "Topic Index"
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
  // 362: P:
  // 363:   A "href" = "index.html" "Home"
  // 364:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 365:   A "href" = "manual.html" "Manual"
  // 366:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 367:   A "href" = "type_index.html" "Type Index"
  // 368:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 369:   A "href" = "symbol_index.html" "Symbol Index"
  // 370:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 371:   A "href" = "topic_index.html" "Topic Index"
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
  // 377: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 378: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 379: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 380: ... : (line)
  // 381:   if
  // 382:     pre_mode:
  // 383:       if
  // 384:         line .has_prefix. EXAMPLE:
  // 385:           trim &text
  // 386:           push &paragraphs text
  // 387:           !text line
  // 388:         :
  // 389:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_2, 1);
  // 380: for_each lines: (line)
  // 381:   if
  // 382:     pre_mode:
  // 383:       if
  // 384:         line .has_prefix. EXAMPLE:
  // 385:           trim &text
  // 386:           push &paragraphs text
  // 387:           !text line
  // 388:         :
  // 389:           writeln_to &text line
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
  // 394: push &paragraphs text
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
  // 395: !text ""
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
  // 393: ... text != ""
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
  // 393: ... text != ""
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
  // 393: ... :
  // 394:   push &paragraphs text
  // 395:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_15, 0);
  // 393: if text != "":
  // 394:   push &paragraphs text
  // 395:   !text ""
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
  // 398: text == ""
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
  // 398: ... :
  // 399:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_19, 0);
  // 400: :
  // 401:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_22, 0);
  // 397: if
  // 398:   text == "":
  // 399:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 400:   :
  // 401:     push &text ' '
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
  // 399: ... !pre_mode true
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
  // 399: ... line .has_prefix. EXAMPLE
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
  // 399: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_21, 0);
  // 399: if line .has_prefix. EXAMPLE: !pre_mode true
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
  // 401: push &text ' '
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
  // 402: ... line.trim
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
  // 402: append &text line.trim
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
  // 385: trim &text
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
  // 386: push &paragraphs text
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
  // 387: !text line
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
  // 389: writeln_to &text line
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
  // 384: line .has_prefix. EXAMPLE
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
  // 384: ... :
  // 385:   trim &text
  // 386:   push &paragraphs text
  // 387:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_5, 0);
  // 388: :
  // 389:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_8, 0);
  // 383: if
  // 384:   line .has_prefix. EXAMPLE:
  // 385:     trim &text
  // 386:     push &paragraphs text
  // 387:     !text line
  // 388:   :
  // 389:     writeln_to &text line
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
  // 392: line == ""
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
  // 392: ... :
  // 393:   if text != "":
  // 394:     push &paragraphs text
  // 395:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_12, 0);
  // 396: :
  // 397:   if
  // 398:     text == "":
  // 399:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 400:     :
  // 401:       push &text ' '
  // 402:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_17, 0);
  // 391: if
  // 392:   line == "":
  // 393:     if text != "":
  // 394:       push &paragraphs text
  // 395:       !text ""
  // 396:   :
  // 397:     if
  // 398:       text == "":
  // 399:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 400:       :
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
  // 382: ... :
  // 383:   if
  // 384:     line .has_prefix. EXAMPLE:
  // 385:       trim &text
  // 386:       push &paragraphs text
  // 387:       !text line
  // 388:     :
  // 389:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_3, 0);
  // 390: :
  // 391:   if
  // 392:     line == "":
  // 393:       if text != "":
  // 394:         push &paragraphs text
  // 395:         !text ""
  // 396:     :
  // 397:       if
  // 398:         text == "":
  // 399:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_10, 0);
  // 381: if
  // 382:   pre_mode:
  // 383:     if
  // 384:       line .has_prefix. EXAMPLE:
  // 385:         trim &text
  // 386:         push &paragraphs text
  // 387:         !text line
  // 388:       :
  // 389:         writeln_to &text line
  // 390:   :
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
  // 403: ... text != ""
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
  // 403: ... text != ""
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
  // 403: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_30, 0);
  // 403: if text != "": push &paragraphs text
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
  // 403: ... push &paragraphs text
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
  // 404: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_39(void) {
  allocate_initialized_frame_gc(3, 17);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_reference: 2
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
  frame->slots[2] = myself->closure.frame->slots[2]; /* resolve_reference */
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
  // 426: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__34_40;
}
static void cont__34_40(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 428: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_41;
}
static void cont__34_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 428: ... :
  // 429:   $type function_name .before. '/'
  // 430:   $method function_name .behind. '/'
  // 431:   H1
  // 432:     string
  // 433:       '['
  // 434:       type
  // 435:       "]("
  // 436:       type.mangled
  // 437:       ".html)/["
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_42, 0);
  // 442: :
  // 443:   H1 function_name
  frame->slots[15] /* temp__3 */ = create_closure(entry__34_51, 0);
  // 427: if
  // 428:   function_name .contains. '/':
  // 429:     $type function_name .before. '/'
  // 430:     $method function_name .behind. '/'
  // 431:     H1
  // 432:       string
  // 433:         '['
  // 434:         type
  // 435:         "]("
  // 436:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_52;
}
static void entry__34_42(void) {
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
  // 429: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_43;
}
static void cont__34_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 430: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_44;
}
static void cont__34_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 436: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_45;
}
static void cont__34_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 440: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_46;
}
static void cont__34_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 432: string
  // 433:   '['
  // 434:   type
  // 435:   "]("
  // 436:   type.mangled
  // 437:   ".html)/["
  // 438:   method
  // 439:   "]("
  // 440:   method.mangled
  // 441:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__34_47;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__34_48;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__34_47;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__34_49;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_50;
}
static void cont__34_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 431: H1
  // 432:   string
  // 433:     '['
  // 434:     type
  // 435:     "]("
  // 436:     type.mangled
  // 437:     ".html)/["
  // 438:     method
  // 439:     "]("
  // 440:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_51(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // function_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 443: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 444: $$short_description undefined
  ((CELL *)frame->slots[3])->contents /* short_description */ = get__undefined();
  // 445: $$parameters empty_list
  ((CELL *)frame->slots[4])->contents /* parameters */ = get__empty_list();
  // 446: $$return_values empty_list
  ((CELL *)frame->slots[5])->contents /* return_values */ = get__empty_list();
  // 447: $$descriptions empty_list
  ((CELL *)frame->slots[6])->contents /* descriptions */ = get__empty_list();
  // 448: $$technical_details undefined
  ((CELL *)frame->slots[7])->contents /* technical_details */ = get__undefined();
  // 449: $$references empty_list
  ((CELL *)frame->slots[8])->contents /* references */ = get__empty_list();
  // 450: $$topic_list empty_list
  ((CELL *)frame->slots[9])->contents /* topic_list */ = get__empty_list();
  // 451: $$examples empty_list
  ((CELL *)frame->slots[10])->contents /* examples */ = get__empty_list();
  // 452: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__34_53;
}
static void cont__34_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* remark_lines */, arguments->slots[0]);
  // 456: remark_lines.is_undefined || remark_lines.is_empty
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_54, 0);
  // 454: &&
  // 455:   do_print_missing
  // 456:   remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_missing();
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_59;
}
static void entry__34_54(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 456: remark_lines.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_55;
}
static void cont__34_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 456: ... remark_lines.is_empty
  frame->slots[3] /* temp__3 */ = create_closure(entry__34_56, 0);
  // 456: remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__34_58;
}
static void entry__34_56(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 456: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_57;
}
static void cont__34_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 456: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 456: remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 457: :
  // 458:   ewrite "
  // 459:     Missing documentation for @(function_name) @
  // 460:     (defined in "@(filename_of(info))")!
  frame->slots[15] /* temp__3 */ = create_closure(entry__34_60, 0);
  // 453: if
  // 454:   &&
  // 455:     do_print_missing
  // 456:     remark_lines.is_undefined || remark_lines.is_empty
  // 457:   :
  // 458:     ewrite "
  // 459:       Missing documentation for @(function_name) @
  // 460:       (defined in "@(filename_of(info))")!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_66;
}
static void entry__34_60(void) {
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
  // 460: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__34_61;
}
static void cont__34_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 458: ... "
  // 459:   Missing documentation for @(function_name) @
  // 460:   (defined in "@(filename_of(info))")!
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_62;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__34_63;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__34_64;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_65;
}
static void cont__34_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 458: ewrite "
  // 459:   Missing documentation for @(function_name) @
  // 460:   (defined in "@(filename_of(info))")!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_67;
}
static void cont__34_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 461: ... :
  // 462:   $paragraphs remark_lines.to_paragraphs
  // 463:   for_each paragraphs: ($paragraph)
  // 464:     cond
  // 465:       ->
  // 466:         has_prefix
  // 467:           paragraph
  // 468:           sequence
  // 469:             "Parameter"
  // 470:             sim2c::WHITESPACE
  // ...
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_68, 0);
  // 461: if remark_lines.is_defined:
  // 462:   $paragraphs remark_lines.to_paragraphs
  // 463:   for_each paragraphs: ($paragraph)
  // 464:     cond
  // 465:       ->
  // 466:         has_prefix
  // 467:           paragraph
  // 468:           sequence
  // 469:             "Parameter"
  // 470:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_192;
}
static void entry__34_187(void) {
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
  // 549: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_188;
}
static void cont__34_188(void) {
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
static void entry__34_189(void) {
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
  // 551: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_190;
}
static void cont__34_190(void) {
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
static void entry__34_185(void) {
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
  // 548: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_186;
}
static void cont__34_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 548: ... :
  // 549:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_187, 0);
  // 550: :
  // 551:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_189, 0);
  // 547: if
  // 548:   technical_details.is_defined:
  // 549:     push &technical_details paragraph
  // 550:   :
  // 551:     push &descriptions paragraph
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
static void entry__34_191(void) {
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
  // 553: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_168(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 533: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_169(void) {
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
  // 535: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__34_170;
}
static void cont__34_170(void) {
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
static void entry__34_164(void) {
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
  // 530: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_165;
}
static void cont__34_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 530: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_166;
}
static void cont__34_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 532: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_167;
}
static void cont__34_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 532: ... :
  // 533:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_168, 0);
  // 534: :
  // 535:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_169, 0);
  // 531: if
  // 532:   detail == "":
  // 533:     !technical_details empty_list
  // 534:   :
  // 535:     !technical_details list(detail)
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
static void entry__34_154(void) {
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
  // 526: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_155;
}
static void cont__34_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 526: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_156;
}
static void cont__34_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 527: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_157;
}
static void cont__34_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 527: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_158;
}
static void cont__34_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 528: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_159;
}
static void cont__34_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 528: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_160;
}
static void cont__34_160(void) {
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
static void entry__34_145(void) {
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
  // 517: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_146;
}
static void cont__34_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 518: push &topic_list topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* topic_list */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_147;
}
static void cont__34_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* topic_list */ = arguments->slots[0];
  // 521: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__34_148;
}
static void cont__34_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 520: $$topic_contents
  // 521:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__34_149;
}
static void cont__34_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 523: !topic_contents(function_name) true
  frame->slots[4] /* temp__1 */ = get__true();
  // 523: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* function_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__34_150;
}
static void cont__34_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* topic_contents */ = arguments->slots[0];
  // 524: !topics(topic) topic_contents
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* topic_contents */;
  // 524: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__34_151;
}
static void cont__34_151(void) {
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
static void entry__34_142(void) {
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
  // 516: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_143;
}
static void cont__34_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 516: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__34_144;
}
static void cont__34_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 516: ... : ($topic)
  // 517:   trim &topic
  // 518:   push &topic_list topic
  // 519:   
  // 520:   $$topic_contents
  // 521:     default_value(topics(topic) empty_key_order_set)
  // 522:   
  // 523:   !topic_contents(function_name) true
  // 524:   !topics(topic) topic_contents
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_145, 1);
  // 516: for_each split(paragraph .behind. ':' ','): ($topic)
  // 517:   trim &topic
  // 518:   push &topic_list topic
  // 519:   
  // 520:   $$topic_contents
  // 521:     default_value(topics(topic) empty_key_order_set)
  // 522:   
  // 523:   !topic_contents(function_name) true
  // 524:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_137(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 514: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_138;
}
static void cont__34_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 514: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_139;
}
static void cont__34_139(void) {
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
static void entry__34_134(void) {
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
  // 513: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_135;
}
static void cont__34_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 513: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__34_136;
}
static void cont__34_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 513: ... : (reference)
  // 514:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_137, 1);
  // 513: for_each split(paragraph .behind. ':' ','): (reference)
  // 514:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_112(void) {
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
  // 501: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__34_113;
}
static void cont__34_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 503: -> return_value .has_suffix. '?':
  // 504:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_114, 0);
  // 505: -> return_value .has_suffix. '*':
  // 506:   !return_value
  // 507:     string
  // 508:       range(return_value 1 -2)
  // 509:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_120, 0);
  // 502: cond
  // 503:   -> return_value .has_suffix. '?':
  // 504:     !return_value string(range(return_value 1 -2) " (optional)")
  // 505:   -> return_value .has_suffix. '*':
  // 506:     !return_value
  // 507:       string
  // 508:         range(return_value 1 -2)
  // 509:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__34_126;
}
static void entry__34_122(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 508: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_123;
}
static void cont__34_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 508: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_124;
}
static void cont__34_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 506: !return_value
  // 507:   string
  // 508:     range(return_value 1 -2)
  // 509:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_90;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_125;
}
static void cont__34_125(void) {
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
static void entry__34_116(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 504: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_117;
}
static void cont__34_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 504: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_118;
}
static void cont__34_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 504: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_83;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_119;
}
static void cont__34_119(void) {
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
static void entry__34_114(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 503: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__34_115;
}
static void cont__34_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 503: ... :
  // 504:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_116, 0);
  // 503: -> return_value .has_suffix. '?':
  // 504:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_120(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 505: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__34_121;
}
static void cont__34_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 505: ... :
  // 506:   !return_value
  // 507:     string
  // 508:       range(return_value 1 -2)
  // 509:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_122, 0);
  // 505: -> return_value .has_suffix. '*':
  // 506:   !return_value
  // 507:     string
  // 508:       range(return_value 1 -2)
  // 509:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_126(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 510: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_127;
}
static void cont__34_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 510: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_128;
}
static void cont__34_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 511: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_129;
}
static void cont__34_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 511: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_130;
}
static void cont__34_130(void) {
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
static void entry__34_76(void) {
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
  // 475: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__34_77;
}
static void cont__34_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 477: -> parameter .has_suffix. '?':
  // 478:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_78, 0);
  // 479: -> parameter .has_suffix. '*':
  // 480:   !parameter
  // 481:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_85, 0);
  // 482: -> parameter .contains. '=':
  // 483:   !parameter
  // 484:     string
  // 485:       (parameter .before. '=').trim
  // 486:       " (optional; default value: "
  // 487:       (parameter .behind. '=').trim
  // 488:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__34_92, 0);
  // 476: cond
  // 477:   -> parameter .has_suffix. '?':
  // 478:     !parameter string(range(parameter 1 -2) " (optional)")
  // 479:   -> parameter .has_suffix. '*':
  // 480:     !parameter
  // 481:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 482:   -> parameter .contains. '=':
  // 483:     !parameter
  // 484:       string
  // 485:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__34_102;
}
static void entry__34_94(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 485: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_95;
}
static void cont__34_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 485: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_96;
}
static void cont__34_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 487: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_97;
}
static void cont__34_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 487: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_98;
}
static void cont__34_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 483: !parameter
  // 484:   string
  // 485:     (parameter .before. '=').trim
  // 486:     " (optional; default value: "
  // 487:     (parameter .behind. '=').trim
  // 488:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_99;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__34_100;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_101;
}
static void cont__34_101(void) {
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
static void entry__34_87(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 481: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_88;
}
static void cont__34_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 481: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_89;
}
static void cont__34_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 480: !parameter
  // 481:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_90;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_91;
}
static void cont__34_91(void) {
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
static void entry__34_80(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 478: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_81;
}
static void cont__34_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 478: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_82;
}
static void cont__34_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 478: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_83;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_84;
}
static void cont__34_84(void) {
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
static void entry__34_78(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 477: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__34_79;
}
static void cont__34_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 477: ... :
  // 478:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_80, 0);
  // 477: -> parameter .has_suffix. '?':
  // 478:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_85(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 479: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__34_86;
}
static void cont__34_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 479: ... :
  // 480:   !parameter
  // 481:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_87, 0);
  // 479: -> parameter .has_suffix. '*':
  // 480:   !parameter
  // 481:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_92(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 482: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_93;
}
static void cont__34_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 482: ... :
  // 483:   !parameter
  // 484:     string
  // 485:       (parameter .before. '=').trim
  // 486:       " (optional; default value: "
  // 487:       (parameter .behind. '=').trim
  // 488:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_94, 0);
  // 482: -> parameter .contains. '=':
  // 483:   !parameter
  // 484:     string
  // 485:       (parameter .before. '=').trim
  // 486:       " (optional; default value: "
  // 487:       (parameter .behind. '=').trim
  // 488:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_102(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 489: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_103;
}
static void cont__34_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 489: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__34_104;
}
static void cont__34_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 490: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_105;
}
static void cont__34_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 490: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_106;
}
static void cont__34_106(void) {
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
static void entry__34_71(void) {
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
  // 472: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__34_72;
}
static void cont__34_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 468: sequence
  // 469:   "Parameter"
  // 470:   sim2c::WHITESPACE
  // 471:   NAME
  // 472:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 473:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_73;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__34_74;
}
static void cont__34_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 466: has_prefix
  // 467:   paragraph
  // 468:   sequence
  // 469:     "Parameter"
  // 470:     sim2c::WHITESPACE
  // 471:     NAME
  // 472:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 473:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_75;
}
static void cont__34_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 474: :
  // 475:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 476:   cond
  // 477:     -> parameter .has_suffix. '?':
  // 478:       !parameter string(range(parameter 1 -2) " (optional)")
  // 479:     -> parameter .has_suffix. '*':
  // 480:       !parameter
  // 481:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 482:     -> parameter .contains. '=':
  // 483:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__34_76, 0);
  // 465: ->
  // 466:   has_prefix
  // 467:     paragraph
  // 468:     sequence
  // 469:       "Parameter"
  // 470:       sim2c::WHITESPACE
  // 471:       NAME
  // 472:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 473:       ':'
  // 474:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_107(void) {
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
  // 498: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__34_108;
}
static void cont__34_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 494: sequence
  // 495:   "Returns"
  // 496:   sim2c::WHITESPACE
  // 497:   NAME
  // 498:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 499:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_109;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__34_110;
}
static void cont__34_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 492: has_prefix
  // 493:   paragraph
  // 494:   sequence
  // 495:     "Returns"
  // 496:     sim2c::WHITESPACE
  // 497:     NAME
  // 498:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 499:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_111;
}
static void cont__34_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 500: :
  // 501:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 502:   cond
  // 503:     -> return_value .has_suffix. '?':
  // 504:       !return_value string(range(return_value 1 -2) " (optional)")
  // 505:     -> return_value .has_suffix. '*':
  // 506:       !return_value
  // 507:         string
  // 508:           range(return_value 1 -2)
  // 509:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__34_112, 0);
  // 491: ->
  // 492:   has_prefix
  // 493:     paragraph
  // 494:     sequence
  // 495:       "Returns"
  // 496:       sim2c::WHITESPACE
  // 497:       NAME
  // 498:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 499:       ':'
  // 500:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_131(void) {
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
  // 512: ... paragraph .has_prefix. "See also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__34_132;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_133;
}
static void cont__34_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 512: ... :
  // 513:   for_each split(paragraph .behind. ':' ','): (reference)
  // 514:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_134, 0);
  // 512: -> paragraph .has_prefix. "See also:":
  // 513:   for_each split(paragraph .behind. ':' ','): (reference)
  // 514:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_140(void) {
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
  // 515: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_141;
}
static void cont__34_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 515: ... :
  // 516:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 517:     trim &topic
  // 518:     push &topic_list topic
  // 519:     
  // 520:     $$topic_contents
  // 521:       default_value(topics(topic) empty_key_order_set)
  // 522:     
  // 523:     !topic_contents(function_name) true
  // 524:     !topics(topic) topic_contents
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_142, 0);
  // 515: -> paragraph .has_prefix. TOPIC:
  // 516:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 517:     trim &topic
  // 518:     push &topic_list topic
  // 519:     
  // 520:     $$topic_contents
  // 521:       default_value(topics(topic) empty_key_order_set)
  // 522:     
  // 523:     !topic_contents(function_name) true
  // 524:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_152(void) {
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
  // 525: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_153;
}
static void cont__34_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 525: ... :
  // 526:   $title (paragraph .before. ':').trim
  // 527:   $text (paragraph .behind. ':').trim
  // 528:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_154, 0);
  // 525: -> paragraph .has_prefix. EXAMPLE:
  // 526:   $title (paragraph .before. ':').trim
  // 527:   $text (paragraph .behind. ':').trim
  // 528:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_161(void) {
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
  // 529: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__34_162;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__34_163;
}
static void cont__34_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 529: ... :
  // 530:   $detail (paragraph .behind. ':').trim
  // 531:   if
  // 532:     detail == "":
  // 533:       !technical_details empty_list
  // 534:     :
  // 535:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_164, 0);
  // 529: -> paragraph .has_prefix. "Technical Details:":
  // 530:   $detail (paragraph .behind. ':').trim
  // 531:   if
  // 532:     detail == "":
  // 533:       !technical_details empty_list
  // 534:     :
  // 535:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_171(void) {
  allocate_initialized_frame_gc(5, 10);
  // slot allocations:
  // paragraph: 0
  // resolve_reference: 1
  // short_description: 2
  // technical_details: 3
  // descriptions: 4
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[8]; /* resolve_reference */
  frame->slots[2] = myself->closure.frame->slots[9]; /* short_description */
  frame->slots[3] = myself->closure.frame->slots[7]; /* technical_details */
  frame->slots[4] = myself->closure.frame->slots[10]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 540: ... '/', NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__34_172;
}
static void cont__34_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__4 */ = arguments->slots[0];
  // 540: ... optional('/', NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__34_173;
}
static void cont__34_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 540: '<', NAME, optional('/', NAME), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[7] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__34_174;
}
static void cont__34_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 541: : ($reference)
  // 542:   range &reference 2 -2
  // 543:   resolve_reference &reference
  // 544:   -> "[@(reference)](@(reference.mangled).html)"
  frame->slots[9] /* temp__5 */ = create_closure(entry__34_175, 1);
  // 539: =
  // 540:   '<', NAME, optional('/', NAME), '>'
  // 541:   : ($reference)
  // 542:     range &reference 2 -2
  // 543:     resolve_reference &reference
  // 544:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__5 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_182;
}
static void entry__34_175(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // reference: 0
  // resolve_reference: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_reference */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 542: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_176;
}
static void cont__34_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 542: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_177;
}
static void cont__34_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 543: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_reference */;
  func = myself->type;
  frame->cont = cont__34_178;
}
static void cont__34_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 544: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_179;
}
static void cont__34_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 544: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_180;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__34_47;
  arguments->slots[3] = frame->slots[3] /* temp__2 */;
  arguments->slots[4] = string__34_49;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_181;
}
static void cont__34_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 544: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 537: replace_all
  // 538:   &paragraph
  // 539:   =
  // 540:     '<', NAME, optional('/', NAME), '>'
  // 541:     : ($reference)
  // 542:       range &reference 2 -2
  // 543:       resolve_reference &reference
  // 544:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_183;
}
static void cont__34_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 546: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_184;
}
static void cont__34_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 546: ... :
  // 547:   if
  // 548:     technical_details.is_defined:
  // 549:       push &technical_details paragraph
  // 550:     :
  // 551:       push &descriptions paragraph
  frame->slots[6] /* temp__2 */ = create_closure(entry__34_185, 0);
  // 552: :
  // 553:   !short_description paragraph
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_191, 0);
  // 545: if
  // 546:   short_description.is_defined:
  // 547:     if
  // 548:       technical_details.is_defined:
  // 549:         push &technical_details paragraph
  // 550:       :
  // 551:         push &descriptions paragraph
  // 552:   :
  // 553:     !short_description paragraph
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
static void entry__34_70(void) {
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
  // resolve_reference: 8
  // short_description: 9
  // descriptions: 10
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return_values */
  frame->slots[3] = myself->closure.frame->slots[3]; /* references */
  frame->slots[4] = myself->closure.frame->slots[4]; /* topic_list */
  frame->slots[5] = myself->closure.frame->slots[5]; /* function_name */
  frame->slots[6] = myself->closure.frame->slots[6]; /* examples */
  frame->slots[7] = myself->closure.frame->slots[7]; /* technical_details */
  frame->slots[8] = myself->closure.frame->slots[8]; /* resolve_reference */
  frame->slots[9] = myself->closure.frame->slots[9]; /* short_description */
  frame->slots[10] = myself->closure.frame->slots[10]; /* descriptions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 465: ->
  // 466:   has_prefix
  // 467:     paragraph
  // 468:     sequence
  // 469:       "Parameter"
  // 470:       sim2c::WHITESPACE
  // 471:       NAME
  // 472:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 473:       ':'
  // 474:   :
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__34_71, 0);
  // 491: ->
  // 492:   has_prefix
  // 493:     paragraph
  // 494:     sequence
  // 495:       "Returns"
  // 496:       sim2c::WHITESPACE
  // 497:       NAME
  // 498:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 499:       ':'
  // 500:   :
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__34_107, 0);
  // 512: -> paragraph .has_prefix. "See also:":
  // 513:   for_each split(paragraph .behind. ':' ','): (reference)
  // 514:     push &references reference.trim
  frame->slots[13] /* temp__3 */ = create_closure(entry__34_131, 0);
  // 515: -> paragraph .has_prefix. TOPIC:
  // 516:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 517:     trim &topic
  // 518:     push &topic_list topic
  // 519:     
  // 520:     $$topic_contents
  // 521:       default_value(topics(topic) empty_key_order_set)
  // 522:     
  // 523:     !topic_contents(function_name) true
  // 524:     !topics(topic) topic_contents
  frame->slots[14] /* temp__4 */ = create_closure(entry__34_140, 0);
  // 525: -> paragraph .has_prefix. EXAMPLE:
  // 526:   $title (paragraph .before. ':').trim
  // 527:   $text (paragraph .behind. ':').trim
  // 528:   push &examples title = text
  frame->slots[15] /* temp__5 */ = create_closure(entry__34_152, 0);
  // 529: -> paragraph .has_prefix. "Technical Details:":
  // 530:   $detail (paragraph .behind. ':').trim
  // 531:   if
  // 532:     detail == "":
  // 533:       !technical_details empty_list
  // 534:     :
  // 535:       !technical_details list(detail)
  frame->slots[16] /* temp__6 */ = create_closure(entry__34_161, 0);
  // 536: :
  // 537:   replace_all
  // 538:     &paragraph
  // 539:     =
  // 540:       '<', NAME, optional('/', NAME), '>'
  // 541:       : ($reference)
  // 542:         range &reference 2 -2
  // 543:         resolve_reference &reference
  // 544:         -> "[@(reference)](@(reference.mangled).html)"
  // 545:   if
  // ...
  frame->slots[17] /* temp__7 */ = create_closure(entry__34_171, 0);
  // 464: cond
  // 465:   ->
  // 466:     has_prefix
  // 467:       paragraph
  // 468:       sequence
  // 469:         "Parameter"
  // 470:         sim2c::WHITESPACE
  // 471:         NAME
  // 472:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 473:         ':'
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
static void entry__34_68(void) {
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
  // resolve_reference: 8
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
  frame->slots[8] = myself->closure.frame->slots[2]; /* resolve_reference */
  frame->slots[9] = myself->closure.frame->slots[3]; /* short_description */
  frame->slots[10] = myself->closure.frame->slots[6]; /* descriptions */
  frame->slots[11] /* paragraphs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 462: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__34_69;
}
static void cont__34_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[11] /* paragraphs */, arguments->slots[0]);
  // 463: ... : ($paragraph)
  // 464:   cond
  // 465:     ->
  // 466:       has_prefix
  // 467:         paragraph
  // 468:         sequence
  // 469:           "Parameter"
  // 470:           sim2c::WHITESPACE
  // 471:           NAME
  // 472:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[12] /* temp__1 */ = create_closure(entry__34_70, 1);
  // 463: for_each paragraphs: ($paragraph)
  // 464:   cond
  // 465:     ->
  // 466:       has_prefix
  // 467:         paragraph
  // 468:         sequence
  // 469:           "Parameter"
  // 470:           sim2c::WHITESPACE
  // 471:           NAME
  // 472:           optional(PARAMETER_COUNT_OR_MYSELF)
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
static void cont__34_192(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 554: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_193;
}
static void cont__34_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 554: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_194;
}
static void cont__34_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 554: ... :
  // 555:   for_each parameters_of(info): (parameter)
  // 556:     case
  // 557:       parameter_kind_of(parameter)
  // 558:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 559:         pass
  // 560:       :
  // 561:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:         cond
  // 563:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__34_195, 0);
  // 554: if kind_of(info) == FUNCTION:
  // 555:   for_each parameters_of(info): (parameter)
  // 556:     case
  // 557:       parameter_kind_of(parameter)
  // 558:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 559:         pass
  // 560:       :
  // 561:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:         cond
  // 563:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_232;
}
static void entry__34_200(void) {
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
  // 561: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__34_201;
}
static void cont__34_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 561: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_202;
}
static void cont__34_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 561: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__34_203;
}
static void cont__34_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 563: -> parameter.is_an_optional_item:
  // 564:   if
  // 565:     default_value_of(parameter).is_defined:
  // 566:       write_to
  // 567:         &name
  // 568:         " (optional; default value: "
  // 569:         default_value_of(parameter).to_string
  // 570:         ")"
  // 571:     :
  // 572:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__34_204, 0);
  // 573: -> parameter.is_an_expanded_item:
  // 574:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_215, 0);
  // 562: cond
  // 563:   -> parameter.is_an_optional_item:
  // 564:     if
  // 565:       default_value_of(parameter).is_defined:
  // 566:         write_to
  // 567:           &name
  // 568:           " (optional; default value: "
  // 569:           default_value_of(parameter).to_string
  // 570:           ")"
  // 571:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__34_219;
}
static void entry__34_217(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 574: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__34_90;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_218;
}
static void cont__34_218(void) {
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
static void entry__34_209(void) {
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
  // 569: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__34_210;
}
static void cont__34_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 569: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__34_211;
}
static void cont__34_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 566: write_to
  // 567:   &name
  // 568:   " (optional; default value: "
  // 569:   default_value_of(parameter).to_string
  // 570:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__34_99;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__34_100;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__34_212;
}
static void cont__34_212(void) {
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
static void entry__34_213(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 572: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__34_83;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_214;
}
static void cont__34_214(void) {
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
static void entry__34_206(void) {
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
  // 565: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__34_207;
}
static void cont__34_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 565: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_208;
}
static void cont__34_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 565: ... :
  // 566:   write_to
  // 567:     &name
  // 568:     " (optional; default value: "
  // 569:     default_value_of(parameter).to_string
  // 570:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_209, 0);
  // 571: :
  // 572:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__34_213, 0);
  // 564: if
  // 565:   default_value_of(parameter).is_defined:
  // 566:     write_to
  // 567:       &name
  // 568:       " (optional; default value: "
  // 569:       default_value_of(parameter).to_string
  // 570:       ")"
  // 571:   :
  // 572:     append &name " (optional)"
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
static void entry__34_204(void) {
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
  // 563: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__34_205;
}
static void cont__34_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 563: ... :
  // 564:   if
  // 565:     default_value_of(parameter).is_defined:
  // 566:       write_to
  // 567:         &name
  // 568:         " (optional; default value: "
  // 569:         default_value_of(parameter).to_string
  // 570:         ")"
  // 571:     :
  // 572:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_206, 0);
  // 563: -> parameter.is_an_optional_item:
  // 564:   if
  // 565:     default_value_of(parameter).is_defined:
  // 566:       write_to
  // 567:         &name
  // 568:         " (optional; default value: "
  // 569:         default_value_of(parameter).to_string
  // 570:         ")"
  // 571:     :
  // 572:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_215(void) {
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
  // 573: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__34_216;
}
static void cont__34_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 573: ... :
  // 574:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_217, 0);
  // 573: -> parameter.is_an_expanded_item:
  // 574:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_219(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 578: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__34_220;
}
static void cont__34_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 578: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_221;
}
static void cont__34_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 578: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__34_222;
}
static void cont__34_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 579: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__34_223, 0);
  // 576: $description
  // 577:   if
  // 578:     not(remark_lines_of(parameter).is_empty)
  // 579:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 580:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__34_227;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_228;
}
static void entry__34_223(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 579: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__34_224;
}
static void cont__34_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 579: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__34_225;
}
static void cont__34_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 579: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__34_226;
}
static void cont__34_226(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 579: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_227(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 582: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_229;
}
static void cont__34_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 582: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__34_230;
}
static void cont__34_230(void) {
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
static void entry__34_231(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 559: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_197(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 557: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__34_198;
}
static void cont__34_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 558: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__34_199;
}
static void cont__34_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 560: :
  // 561:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:   cond
  // 563:     -> parameter.is_an_optional_item:
  // 564:       if
  // 565:         default_value_of(parameter).is_defined:
  // 566:           write_to
  // 567:             &name
  // 568:             " (optional; default value: "
  // 569:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_200, 0);
  // 556: case
  // 557:   parameter_kind_of(parameter)
  // 558:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 559:     pass
  // 560:   :
  // 561:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:     cond
  // 563:       -> parameter.is_an_optional_item:
  // 564:         if
  // 565:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__34_231;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_195(void) {
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
  // 555: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__34_196;
}
static void cont__34_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 555: ... : (parameter)
  // 556:   case
  // 557:     parameter_kind_of(parameter)
  // 558:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 559:       pass
  // 560:     :
  // 561:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:       cond
  // 563:         -> parameter.is_an_optional_item:
  // 564:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_197, 1);
  // 555: for_each parameters_of(info): (parameter)
  // 556:   case
  // 557:     parameter_kind_of(parameter)
  // 558:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 559:       pass
  // 560:     :
  // 561:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 562:       cond
  // 563:         -> parameter.is_an_optional_item:
  // 564:           if
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
static void cont__34_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 583: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_233;
}
static void cont__34_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 583: ... : P short_description
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_234, 0);
  // 583: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_235;
}
static void entry__34_234(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 583: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 584: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_236;
}
static void cont__34_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   H2 "Parameters"
  // 586:   DL:
  // 587:     for_each parameters: (parameter)
  // 588:       DT key_of(parameter)
  // 589:       DD: P std::value_of(parameter)
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_237, 0);
  // 584: unless parameters.is_empty:
  // 585:   H2 "Parameters"
  // 586:   DL:
  // 587:     for_each parameters: (parameter)
  // 588:       DT key_of(parameter)
  // 589:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_246;
}
static void entry__34_244(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 589: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__34_245;
}
static void cont__34_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 589: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_241(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 588: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__34_242;
}
static void cont__34_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 588: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__34_243;
}
static void cont__34_243(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 589: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_244, 0);
  // 589: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_240(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 587: for_each parameters: (parameter)
  // 588:   DT key_of(parameter)
  // 589:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__34_241;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_237(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 585: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_238;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_239;
}
static void cont__34_239(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 586: ... :
  // 587:   for_each parameters: (parameter)
  // 588:     DT key_of(parameter)
  // 589:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_240, 0);
  // 586: DL:
  // 587:   for_each parameters: (parameter)
  // 588:     DT key_of(parameter)
  // 589:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 590: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_247;
}
static void cont__34_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 590: ... :
  // 591:   H2 "Returns"
  // 592:   DL:
  // 593:     for_each return_values: (return_value)
  // 594:       DT key_of(return_value)
  // 595:       DD: P std::value_of(return_value)
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_248, 0);
  // 590: unless return_values.is_empty:
  // 591:   H2 "Returns"
  // 592:   DL:
  // 593:     for_each return_values: (return_value)
  // 594:       DT key_of(return_value)
  // 595:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_256;
}
static void entry__34_254(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 595: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__34_255;
}
static void cont__34_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 595: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_251(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 594: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__34_252;
}
static void cont__34_252(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 594: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__34_253;
}
static void cont__34_253(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 595: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_254, 0);
  // 595: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_250(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 593: for_each return_values: (return_value)
  // 594:   DT key_of(return_value)
  // 595:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__34_251;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_248(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 591: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_109;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_249;
}
static void cont__34_249(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 592: ... :
  // 593:   for_each return_values: (return_value)
  // 594:     DT key_of(return_value)
  // 595:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_250, 0);
  // 592: DL:
  // 593:   for_each return_values: (return_value)
  // 594:     DT key_of(return_value)
  // 595:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_256(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 596: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_257;
}
static void cont__34_257(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 596: ... :
  // 597:   H2 "Description"
  // 598:   for_each descriptions: (description) P description
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_258, 0);
  // 596: unless descriptions.is_empty:
  // 597:   H2 "Description"
  // 598:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_262;
}
static void entry__34_261(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 598: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_258(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 597: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_259;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_260;
}
static void cont__34_260(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__34_261;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_262(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 599: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_263;
}
static void cont__34_263(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 599: ... :
  // 600:   H2 "Technical Details"
  // 601:   for_each technical_details: (detail) P detail
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_264, 0);
  // 599: if technical_details.is_defined:
  // 600:   H2 "Technical Details"
  // 601:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_268;
}
static void entry__34_267(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 601: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_264(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 600: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_265;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_266;
}
static void cont__34_266(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 601: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__34_267;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 602: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_269;
}
static void cont__34_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 602: ... :
  // 603:   H2 "See also"
  // 604:   TABLE:
  // 605:     for_each references: ($reference)
  // 606:       resolve_reference &reference
  // 607:       TR:
  // 608:         TD: A "href" = "@(reference.mangled).html" reference
  // 609:         TD "&nbsp;"
  // 610:         TD short_descriptions(reference)
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_270, 0);
  // 602: unless references.is_empty:
  // 603:   H2 "See also"
  // 604:   TABLE:
  // 605:     for_each references: ($reference)
  // 606:       resolve_reference &reference
  // 607:       TR:
  // 608:         TD: A "href" = "@(reference.mangled).html" reference
  // 609:         TD "&nbsp;"
  // 610:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_285;
}
static void entry__34_276(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: ... : A "href" = "@(reference.mangled).html" reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_277, 0);
  // 608: TD: A "href" = "@(reference.mangled).html" reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_281;
}
static void entry__34_277(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 608: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_278;
}
static void cont__34_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 608: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_279;
}
static void cont__34_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 608: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_280;
}
static void cont__34_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 608: ... A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_281(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 609: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_282;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_283;
}
static void cont__34_283(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 610: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__34_284;
}
static void cont__34_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 610: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_274(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // resolve_reference: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_reference */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 606: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = frame->slots[1] /* resolve_reference */;
  func = myself->type;
  frame->cont = cont__34_275;
}
static void cont__34_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 607: ... :
  // 608:   TD: A "href" = "@(reference.mangled).html" reference
  // 609:   TD "&nbsp;"
  // 610:   TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_276, 0);
  // 607: TR:
  // 608:   TD: A "href" = "@(reference.mangled).html" reference
  // 609:   TD "&nbsp;"
  // 610:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_273(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // references: 0
  // resolve_reference: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* references */
  frame->slots[1] = myself->closure.frame->slots[1]; /* resolve_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 605: ... : ($reference)
  // 606:   resolve_reference &reference
  // 607:   TR:
  // 608:     TD: A "href" = "@(reference.mangled).html" reference
  // 609:     TD "&nbsp;"
  // 610:     TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_274, 1);
  // 605: for_each references: ($reference)
  // 606:   resolve_reference &reference
  // 607:   TR:
  // 608:     TD: A "href" = "@(reference.mangled).html" reference
  // 609:     TD "&nbsp;"
  // 610:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_270(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // references: 0
  // resolve_reference: 1
  frame->slots[0] = myself->closure.frame->slots[8]; /* references */
  frame->slots[1] = myself->closure.frame->slots[2]; /* resolve_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 603: H2 "See also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_271;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_272;
}
static void cont__34_272(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 604: ... :
  // 605:   for_each references: ($reference)
  // 606:     resolve_reference &reference
  // 607:     TR:
  // 608:       TD: A "href" = "@(reference.mangled).html" reference
  // 609:       TD "&nbsp;"
  // 610:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_273, 0);
  // 604: TABLE:
  // 605:   for_each references: ($reference)
  // 606:     resolve_reference &reference
  // 607:     TR:
  // 608:       TD: A "href" = "@(reference.mangled).html" reference
  // 609:       TD "&nbsp;"
  // 610:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_285(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 611: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__34_286;
}
static void cont__34_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 611: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_287;
}
static void cont__34_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 611: ... :
  // 612:   H2 "Implemented by"
  // 613:   TABLE:
  // 614:     for_each types_of(info): (name)
  // 615:       $method string(name '/' function_name)
  // 616:       TR:
  // 617:         TD: A "href" = "@(name.mangled).html" name
  // 618:         TD "&nbsp;as&nbsp;"
  // 619:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[15] /* temp__3 */ = create_closure(entry__34_288, 0);
  // 611: unless types_of(info).is_empty:
  // 612:   H2 "Implemented by"
  // 613:   TABLE:
  // 614:     for_each types_of(info): (name)
  // 615:       $method string(name '/' function_name)
  // 616:       TR:
  // 617:         TD: A "href" = "@(name.mangled).html" name
  // 618:         TD "&nbsp;as&nbsp;"
  // 619:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_307;
}
static void entry__34_303(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 619: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_304;
}
static void cont__34_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 619: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_305;
}
static void cont__34_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 619: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_306;
}
static void cont__34_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 619: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_295(void) {
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
  // 617: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_296, 0);
  // 617: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_300;
}
static void entry__34_296(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 617: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_297;
}
static void cont__34_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 617: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_298;
}
static void cont__34_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 617: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_299;
}
static void cont__34_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 617: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_300(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_301;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_302;
}
static void cont__34_302(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 619: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_303, 0);
  // 619: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_293(void) {
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
  // 615: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_294;
}
static void cont__34_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 616: ... :
  // 617:   TD: A "href" = "@(name.mangled).html" name
  // 618:   TD "&nbsp;as&nbsp;"
  // 619:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__34_295, 0);
  // 616: TR:
  // 617:   TD: A "href" = "@(name.mangled).html" name
  // 618:   TD "&nbsp;as&nbsp;"
  // 619:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_291(void) {
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
  // 614: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__34_292;
}
static void cont__34_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 614: ... : (name)
  // 615:   $method string(name '/' function_name)
  // 616:   TR:
  // 617:     TD: A "href" = "@(name.mangled).html" name
  // 618:     TD "&nbsp;as&nbsp;"
  // 619:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_293, 1);
  // 614: for_each types_of(info): (name)
  // 615:   $method string(name '/' function_name)
  // 616:   TR:
  // 617:     TD: A "href" = "@(name.mangled).html" name
  // 618:     TD "&nbsp;as&nbsp;"
  // 619:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_288(void) {
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
  // 612: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_289;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_290;
}
static void cont__34_290(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 613: ... :
  // 614:   for_each types_of(info): (name)
  // 615:     $method string(name '/' function_name)
  // 616:     TR:
  // 617:       TD: A "href" = "@(name.mangled).html" name
  // 618:       TD "&nbsp;as&nbsp;"
  // 619:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_291, 0);
  // 613: TABLE:
  // 614:   for_each types_of(info): (name)
  // 615:     $method string(name '/' function_name)
  // 616:     TR:
  // 617:       TD: A "href" = "@(name.mangled).html" name
  // 618:       TD "&nbsp;as&nbsp;"
  // 619:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 620: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_308;
}
static void cont__34_308(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 620: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_309;
}
static void cont__34_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 620: ... :
  // 621:   H2 "Supported Polymorphic Functions"
  // 622:   TABLE:
  // 623:     for_each methods_of(info): (method_name _method_info)
  // 624:       TR:
  // 625:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:         TD "&nbsp;"
  // 627:         TD:
  // 628:           A
  // 629:             =
  // ...
  frame->slots[15] /* temp__3 */ = create_closure(entry__34_310, 0);
  // 620: if kind_of(info) == INLINE_C_TYPE:
  // 621:   H2 "Supported Polymorphic Functions"
  // 622:   TABLE:
  // 623:     for_each methods_of(info): (method_name _method_info)
  // 624:       TR:
  // 625:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:         TD "&nbsp;"
  // 627:         TD:
  // 628:           A
  // 629:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_328;
}
static void entry__34_323(void) {
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
  // 631: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_324;
}
static void cont__34_324(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 631: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_325;
}
static void cont__34_325(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 631: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__28_3;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_326;
}
static void cont__34_326(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 629: =
  // 630:   "href"
  // 631:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_327;
}
static void cont__34_327(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 628: A
  // 629:   =
  // 630:     "href"
  // 631:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:   function_name
  // 633:   '/'
  // 634:   method_name
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
static void entry__34_316(void) {
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
  // 625: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_317, 0);
  // 625: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_321;
}
static void entry__34_317(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 625: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_318;
}
static void cont__34_318(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 625: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_319;
}
static void cont__34_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 625: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_320;
}
static void cont__34_320(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 625: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_321(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 626: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_282;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_322;
}
static void cont__34_322(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 627: ... :
  // 628:   A
  // 629:     =
  // 630:       "href"
  // 631:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:     function_name
  // 633:     '/'
  // 634:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_323, 0);
  // 627: TD:
  // 628:   A
  // 629:     =
  // 630:       "href"
  // 631:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:     function_name
  // 633:     '/'
  // 634:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_315(void) {
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
  // 624: ... :
  // 625:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:   TD "&nbsp;"
  // 627:   TD:
  // 628:     A
  // 629:       =
  // 630:         "href"
  // 631:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:       function_name
  // 633:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__34_316, 0);
  // 624: TR:
  // 625:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:   TD "&nbsp;"
  // 627:   TD:
  // 628:     A
  // 629:       =
  // 630:         "href"
  // 631:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:       function_name
  // 633:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_313(void) {
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
  // 623: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__34_314;
}
static void cont__34_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 623: ... : (method_name _method_info)
  // 624:   TR:
  // 625:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:     TD "&nbsp;"
  // 627:     TD:
  // 628:       A
  // 629:         =
  // 630:           "href"
  // 631:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_315, 2);
  // 623: for_each methods_of(info): (method_name _method_info)
  // 624:   TR:
  // 625:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:     TD "&nbsp;"
  // 627:     TD:
  // 628:       A
  // 629:         =
  // 630:           "href"
  // 631:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 632:         function_name
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
static void entry__34_310(void) {
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
  // 621: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_311;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_312;
}
static void cont__34_312(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 622: ... :
  // 623:   for_each methods_of(info): (method_name _method_info)
  // 624:     TR:
  // 625:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:       TD "&nbsp;"
  // 627:       TD:
  // 628:         A
  // 629:           =
  // 630:             "href"
  // 631:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_313, 0);
  // 622: TABLE:
  // 623:   for_each methods_of(info): (method_name _method_info)
  // 624:     TR:
  // 625:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 626:       TD "&nbsp;"
  // 627:       TD:
  // 628:         A
  // 629:           =
  // 630:             "href"
  // 631:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_328(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__34_329;
}
static void cont__34_329(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 636: $function_basename
  // 637:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__34_330;
}
static void cont__34_330(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* function_basename */, arguments->slots[0]);
  // 639: ... topic_list.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* topic_list */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_331;
}
static void cont__34_331(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 639: ... :
  // 640:   H2 "Topics"
  // 641:   TABLE:
  // 642:     for_each topic_list: (topic)
  // 643:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 644:       TR: TD: A "href" = filename topic
  frame->slots[14] /* temp__2 */ = create_closure(entry__34_332, 0);
  // 639: unless topic_list.is_empty:
  // 640:   H2 "Topics"
  // 641:   TABLE:
  // 642:     for_each topic_list: (topic)
  // 643:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 644:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_345;
}
static void entry__34_343(void) {
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
  // 644: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_344;
}
static void cont__34_344(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 644: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_342(void) {
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
  // 644: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_343, 0);
  // 644: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_336(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // topic: 0
  // filename: 1
  frame->slots[1] /* filename */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 643: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__34_337;
}
static void cont__34_337(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 643: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__34_338;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_339;
}
static void cont__34_339(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 643: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_340;
}
static void cont__34_340(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 643: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_341;
}
static void cont__34_341(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* filename */, arguments->slots[0]);
  // 644: ... : TD: A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_342, 0);
  // 644: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_335(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 642: for_each topic_list: (topic)
  // 643:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 644:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic_list */;
  arguments->slots[1] = func__34_336;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_332(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // topic_list: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* topic_list */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 640: H2 "Topics"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_333;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_334;
}
static void cont__34_334(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 641: ... :
  // 642:   for_each topic_list: (topic)
  // 643:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 644:     TR: TD: A "href" = filename topic
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_335, 0);
  // 641: TABLE:
  // 642:   for_each topic_list: (topic)
  // 643:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 644:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_345(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 646: ... : (example)
  // 647:   $title key_of(example)
  // 648:   $text std::value_of(example)
  // 649:   H2 title
  // 650:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 651:     PRE
  // 652:       replace_all
  // 653:         text
  // 654:         =
  // 655:           sequence
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__34_346, 1);
  // 646: for_each examples: (example)
  // 647:   $title key_of(example)
  // 648:   $text std::value_of(example)
  // 649:   H2 title
  // 650:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 651:     PRE
  // 652:       replace_all
  // 653:         text
  // 654:         =
  // 655:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* examples */;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_365;
}
static void entry__34_354(void) {
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
  // 657: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__34_355;
}
static void cont__34_355(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 657: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__34_356;
}
static void cont__34_356(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 657: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__34_357;
}
static void cont__34_357(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 655: sequence
  // 656:   '@quot;'
  // 657:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__34_358;
}
static void cont__34_358(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 654: =
  // 655:   sequence
  // 656:     '@quot;'
  // 657:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:     '@quot;'
  // 659:   : (string_literal)
  // 660:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__34_359;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_360;
}
static void entry__34_359(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 660: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_360(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 661: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__34_361;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__34_361;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_362;
}
static void cont__34_362(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 661: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_363;
}
static void cont__34_363(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 652: replace_all
  // 653:   text
  // 654:   =
  // 655:     sequence
  // 656:       '@quot;'
  // 657:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:       '@quot;'
  // 659:     : (string_literal)
  // 660:       -> string_literal
  // 661:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_364;
}
static void cont__34_364(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 651: PRE
  // 652:   replace_all
  // 653:     text
  // 654:     =
  // 655:       sequence
  // 656:         '@quot;'
  // 657:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:         '@quot;'
  // 659:       : (string_literal)
  // 660:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_346(void) {
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
  // 647: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__34_347;
}
static void cont__34_347(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 648: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__34_348;
}
static void cont__34_348(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 649: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__34_349;
}
static void cont__34_349(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__34_350;
}
static void cont__34_350(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 650: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__34_351;
}
static void cont__34_351(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 650: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_352;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_353;
}
static void cont__34_353(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 650: ... :
  // 651:   PRE
  // 652:     replace_all
  // 653:       text
  // 654:       =
  // 655:         sequence
  // 656:           '@quot;'
  // 657:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:           '@quot;'
  // 659:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__34_354, 0);
  // 650: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 651:   PRE
  // 652:     replace_all
  // 653:       text
  // 654:       =
  // 655:         sequence
  // 656:           '@quot;'
  // 657:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 658:           '@quot;'
  // 659:         : (string_literal)
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
static void cont__34_365(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_352;
  arguments->slots[1] = string__34_366;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_367;
}
static void cont__34_367(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 664: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__34_368;
}
static void cont__34_368(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 664: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__34_369;
}
static void cont__34_369(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 664: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__34_370;
  arguments->slots[1] = frame->slots[15] /* temp__3 */;
  arguments->slots[2] = string__34_371;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_372;
}
static void cont__34_372(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 662: DIV
  // 663:   "class" = "footer"
  // 664:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_34(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_reference: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* resolve_reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 425: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_35;
}
static void cont__34_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 425: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__34_36;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_38;
}
static void cont__34_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 425: ... :
  // 426:   link_bar
  // 427:   if
  // 428:     function_name .contains. '/':
  // 429:       $type function_name .before. '/'
  // 430:       $method function_name .behind. '/'
  // 431:       H1
  // 432:         string
  // 433:           '['
  // 434:           type
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_39, 0);
  // 425: create_page "html/@(function_name.mangled).html":
  // 426:   link_bar
  // 427:   if
  // 428:     function_name .contains. '/':
  // 429:       $type function_name .before. '/'
  // 430:       $method function_name .behind. '/'
  // 431:       H1
  // 432:         string
  // 433:           '['
  // 434:           type
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
static void entry__34_1_create_info_page(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // function_name: 0
  // info: 1
  // resolve_reference: 2
  frame->slots[2] /* resolve_reference */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 407: ... : (&reference)
  // 408:   if
  // 409:     reference .contains. '/':
  // 410:       $$type_name reference .before. '/'
  // 411:       $$method_name reference .behind. '/'
  // 412:       unless type_name .contains. "::": append "types::" &type_name
  // 413:       unless method_name .contains. "::": append "std::" &method_name
  // 414:       !reference string(type_name '/' method_name)
  // 415:     :
  // 416:       unless reference .contains. "::": append "std::" &reference
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__34_2_resolve_reference, 1);
  // 407: $resolve_reference: (&reference)
  // 408:   if
  // 409:     reference .contains. '/':
  // 410:       $$type_name reference .before. '/'
  // 411:       $$method_name reference .behind. '/'
  // 412:       unless type_name .contains. "::": append "types::" &type_name
  // 413:       unless method_name .contains. "::": append "std::" &method_name
  // 414:       !reference string(type_name '/' method_name)
  // 415:     :
  // 416:       unless reference .contains. "::": append "std::" &reference
  // ...
  initialize_future(frame->slots[2] /* resolve_reference */, frame->slots[3] /* temp__1 */);
  // 424: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_33;
}
static void entry__34_2_resolve_reference(void) {
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
  // 409: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_3;
}
static void cont__34_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 409: ... :
  // 410:   $$type_name reference .before. '/'
  // 411:   $$method_name reference .behind. '/'
  // 412:   unless type_name .contains. "::": append "types::" &type_name
  // 413:   unless method_name .contains. "::": append "std::" &method_name
  // 414:   !reference string(type_name '/' method_name)
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_4, 0);
  // 415: :
  // 416:   unless reference .contains. "::": append "std::" &reference
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_18, 0);
  // 408: if
  // 409:   reference .contains. '/':
  // 410:     $$type_name reference .before. '/'
  // 411:     $$method_name reference .behind. '/'
  // 412:     unless type_name .contains. "::": append "types::" &type_name
  // 413:     unless method_name .contains. "::": append "std::" &method_name
  // 414:     !reference string(type_name '/' method_name)
  // 415:   :
  // 416:     unless reference .contains. "::": append "std::" &reference
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_22;
}
static void entry__34_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_14;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_21;
}
static void cont__34_21(void) {
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
static void entry__34_4(void) {
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
  // 410: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_5;
}
static void cont__34_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 411: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_6;
}
static void cont__34_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 412: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 412: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_8, 0);
  // 412: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_11;
}
static void entry__34_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 412: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_9;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_10;
}
static void cont__34_10(void) {
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
static void cont__34_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 413: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_12;
}
static void cont__34_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 413: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_13, 0);
  // 413: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_16;
}
static void entry__34_13(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 413: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_14;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__34_15;
}
static void cont__34_15(void) {
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
static void cont__34_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 414: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_17;
}
static void cont__34_17(void) {
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
static void entry__34_18(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 416: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_19;
}
static void cont__34_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 416: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_20, 0);
  // 416: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 418: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__34_23;
}
static void cont__34_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 418: ... short_descriptions(reference).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_24;
}
static void cont__34_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 418: ... :
  // 419:   Error "
  // 420:     The documentation for "@(function_name)"
  // 421:     (defined in "@(filename_of(info))")
  // 422:     references the undefined symbol "@(reference)"!
  frame->slots[5] /* temp__3 */ = create_closure(entry__34_25, 0);
  // 418: if short_descriptions(reference).is_undefined:
  // 419:   Error "
  // 420:     The documentation for "@(function_name)"
  // 421:     (defined in "@(filename_of(info))")
  // 422:     references the undefined symbol "@(reference)"!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_32;
}
static void entry__34_25(void) {
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
  // 421: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__34_26;
}
static void cont__34_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 419: ... "
  // 420:   The documentation for "@(function_name)"
  // 421:   (defined in "@(filename_of(info))")
  // 422:   references the undefined symbol "@(reference)"!
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__34_27;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__34_28;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__34_29;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* reference */;
  arguments->slots[6] = string__34_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_31;
}
static void cont__34_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 419: Error "
  // 420:   The documentation for "@(function_name)"
  // 421:   (defined in "@(filename_of(info))")
  // 422:   references the undefined symbol "@(reference)"!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_32(void) {
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
static void cont__34_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 424: ... :
  // 425:   create_page "html/@(function_name.mangled).html":
  // 426:     link_bar
  // 427:     if
  // 428:       function_name .contains. '/':
  // 429:         $type function_name .before. '/'
  // 430:         $method function_name .behind. '/'
  // 431:         H1
  // 432:           string
  // 433:             '['
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_34, 0);
  // 424: if function_name.is_defined:
  // 425:   create_page "html/@(function_name.mangled).html":
  // 426:     link_bar
  // 427:     if
  // 428:       function_name .contains. '/':
  // 429:         $type function_name .before. '/'
  // 430:         $method function_name .behind. '/'
  // 431:         H1
  // 432:           string
  // 433:             '['
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
static void entry__35_1_get_short_description(void) {
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
  // 667: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__35_2;
}
static void cont__35_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* remark_lines */, arguments->slots[0]);
  // 668: $$short_description ""
  ((CELL *)frame->slots[3])->contents /* short_description */ = empty_string;
  // 669: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__35_3;
}
static void cont__35_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 669: ... not(remark_lines.is_empty)
  frame->slots[6] /* temp__3 */ = create_closure(entry__35_4, 0);
  // 669: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__35_7;
}
static void entry__35_4(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__35_5;
}
static void cont__35_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 669: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__35_6;
}
static void cont__35_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 669: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 669: ... :
  // 670:   do: (-> break) for_each remark_lines: (line)
  // 671:     if line == "" && short_description != "" break
  // 672:     append &short_description line.trim
  // 673:   if do_print_warnings && length_of(short_description) > 80:
  // 674:     ewrite "
  // 675:       
  // 676:       The short description for "@(name)"
  // 677:       (defined in "@(filename_of(info))")
  // 678:       is quite long:
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__35_8, 0);
  // 669: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 670:   do: (-> break) for_each remark_lines: (line)
  // 671:     if line == "" && short_description != "" break
  // 672:     append &short_description line.trim
  // 673:   if do_print_warnings && length_of(short_description) > 80:
  // 674:     ewrite "
  // 675:       
  // 676:       The short description for "@(name)"
  // 677:       (defined in "@(filename_of(info))")
  // 678:       is quite long:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__35_30;
}
static void entry__35_25(void) {
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
  // 677: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__35_26;
}
static void cont__35_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 674: ... "
  // 675:   
  // 676:   The short description for "@(name)"
  // 677:   (defined in "@(filename_of(info))")
  // 678:   is quite long:
  // 679:   @(short_description)
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = string__35_27;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__34_28;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__35_28;
  arguments->slots[5] = ((CELL *)frame->slots[2])->contents /* short_description */;
  arguments->slots[6] = string__24_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__35_29;
}
static void cont__35_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 674: ewrite "
  // 675:   
  // 676:   The short description for "@(name)"
  // 677:   (defined in "@(filename_of(info))")
  // 678:   is quite long:
  // 679:   @(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__35_8(void) {
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
  // 670: ... : (-> break) for_each remark_lines: (line)
  // 671:   if line == "" && short_description != "" break
  // 672:   append &short_description line.trim
  frame->slots[4] /* temp__1 */ = create_closure(entry__35_9, 0);
  // 670: do: (-> break) for_each remark_lines: (line)
  // 671:   if line == "" && short_description != "" break
  // 672:   append &short_description line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__35_20;
}
static void entry__35_9(void) {
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
  // 670: ... : (line)
  // 671:   if line == "" && short_description != "" break
  // 672:   append &short_description line.trim
  frame->slots[3] /* temp__1 */ = create_closure(entry__35_10, 1);
  // 670: ... for_each remark_lines: (line)
  // 671:   if line == "" && short_description != "" break
  // 672:   append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__35_19;
}
static void entry__35_10(void) {
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
  // 671: ... line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__35_11;
}
static void cont__35_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 671: ... short_description != ""
  frame->slots[5] /* temp__3 */ = create_closure(entry__35_12, 0);
  // 671: ... line == "" && short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__35_15;
}
static void entry__35_12(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 671: ... short_description != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__35_13;
}
static void cont__35_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 671: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__35_14;
}
static void cont__35_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 671: ... short_description != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 671: if line == "" && short_description != "" break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* break */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__35_16;
}
static void cont__35_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 672: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__35_17;
}
static void cont__35_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 672: append &short_description line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__35_18;
}
static void cont__35_18(void) {
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
static void cont__35_19(void) {
  myself = frame->slots[0] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__35_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 673: ... length_of(short_description) > 80
  frame->slots[5] /* temp__2 */ = create_closure(entry__35_21, 0);
  // 673: ... do_print_warnings && length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__35_24;
}
static void entry__35_21(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 673: ... length_of(short_description)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__35_22;
}
static void cont__35_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 673: ... length_of(short_description) > 80
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__80;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__35_23;
}
static void cont__35_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 673: ... length_of(short_description) > 80
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__35_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 673: ... :
  // 674:   ewrite "
  // 675:     
  // 676:     The short description for "@(name)"
  // 677:     (defined in "@(filename_of(info))")
  // 678:     is quite long:
  // 679:     @(short_description)
  frame->slots[6] /* temp__3 */ = create_closure(entry__35_25, 0);
  // 673: if do_print_warnings && length_of(short_description) > 80:
  // 674:   ewrite "
  // 675:     
  // 676:     The short description for "@(name)"
  // 677:     (defined in "@(filename_of(info))")
  // 678:     is quite long:
  // 679:     @(short_description)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__35_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 680: -> short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* short_description */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_230(void) {
  allocate_initialized_frame_gc(0, 29);
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
  // total_variables: 11
  // other: 12
  // total_definitions: 13
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
  frame->slots[11] /* total_variables */ = create_cell();
  frame->slots[12] /* other */ = create_cell();
  frame->slots[13] /* total_definitions */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 833: $$total_functions 0
  ((CELL *)frame->slots[0])->contents /* total_functions */ = number__0;
  // 834: $$total_polymorphic_functions 0
  ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */ = number__0;
  // 835: $$total_polymorphic_attributes 0
  ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */ = number__0;
  // 836: $$total_methods 0
  ((CELL *)frame->slots[3])->contents /* total_methods */ = number__0;
  // 837: $$total_inline_c_methods 0
  ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */ = number__0;
  // 838: $$total_inline_c_types 0
  ((CELL *)frame->slots[5])->contents /* total_inline_c_types */ = number__0;
  // 839: $$total_inline_c_objects 0
  ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */ = number__0;
  // 840: $$total_attributes 0
  ((CELL *)frame->slots[7])->contents /* total_attributes */ = number__0;
  // 841: $$total_inline_c_functions 0
  ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */ = number__0;
  // 842: $$total_unique_items 0
  ((CELL *)frame->slots[9])->contents /* total_unique_items */ = number__0;
  // 843: $$total_constants 0
  ((CELL *)frame->slots[10])->contents /* total_constants */ = number__0;
  // 844: $$total_variables 0
  ((CELL *)frame->slots[11])->contents /* total_variables */ = number__0;
  // 845: $$other 0
  ((CELL *)frame->slots[12])->contents /* other */ = number__0;
  // 847: ... : (_iname info)
  // 848:   case kind_of(info)
  // 849:     FUNCTION: inc &total_functions
  // 850:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 851:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 852:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 853:     INLINE_C_TYPE: inc &total_inline_c_types
  // 854:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 855:     UNIQUE_ITEM: inc &total_unique_items
  // 856:     CONSTANT: inc &total_constants
  // ...
  frame->slots[14] /* temp__1 */ = create_closure(entry__36_231, 2);
  // 847: for_each definitions: (_iname info)
  // 848:   case kind_of(info)
  // 849:     FUNCTION: inc &total_functions
  // 850:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 851:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 852:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 853:     INLINE_C_TYPE: inc &total_inline_c_types
  // 854:     INLINE_C_OBJECT: inc &total_inline_c_objects
  // 855:     UNIQUE_ITEM: inc &total_unique_items
  // 856:     CONSTANT: inc &total_constants
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[14] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_265;
}
static void entry__36_259(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_methods: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 862: ... inc &total_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_260;
}
static void cont__36_260(void) {
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
static void entry__36_261(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_methods: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_inline_c_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 863: ... inc &total_inline_c_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_262;
}
static void cont__36_262(void) {
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
static void entry__36_263(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 864: ... inc &total_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_264;
}
static void cont__36_264(void) {
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
static void entry__36_257(void) {
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
  // 861: ... kind_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_258;
}
static void cont__36_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 862: ... : inc &total_methods
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_259, 0);
  // 863: ... : inc &total_inline_c_methods
  frame->slots[7] /* temp__3 */ = create_closure(entry__36_261, 0);
  // 864: : inc &total_attributes
  frame->slots[8] /* temp__4 */ = create_closure(entry__36_263, 0);
  // 861: case kind_of(method_info)
  // 862:   FUNCTION: inc &total_methods
  // 863:   INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 864:   : inc &total_attributes
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
static void entry__36_255(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // info: 0
  // total_methods: 1
  // total_inline_c_methods: 2
  // total_attributes: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[12]; /* total_methods */
  frame->slots[2] = myself->closure.frame->slots[13]; /* total_inline_c_methods */
  frame->slots[3] = myself->closure.frame->slots[14]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 860: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__36_256;
}
static void cont__36_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 860: ... : (method_name method_info)
  // 861:   case kind_of(method_info)
  // 862:     FUNCTION: inc &total_methods
  // 863:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 864:     : inc &total_attributes
  frame->slots[5] /* temp__2 */ = create_closure(entry__36_257, 2);
  // 860: for_each methods_of(info): (method_name method_info)
  // 861:   case kind_of(method_info)
  // 862:     FUNCTION: inc &total_methods
  // 863:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 864:     : inc &total_attributes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_231(void) {
  allocate_initialized_frame_gc(15, 26);
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
  // total_variables: 10
  // other: 11
  // total_methods: 12
  // total_inline_c_methods: 13
  // total_attributes: 14
  frame->slots[2] = myself->closure.frame->slots[0]; /* total_functions */
  frame->slots[3] = myself->closure.frame->slots[1]; /* total_polymorphic_functions */
  frame->slots[4] = myself->closure.frame->slots[2]; /* total_polymorphic_attributes */
  frame->slots[5] = myself->closure.frame->slots[8]; /* total_inline_c_functions */
  frame->slots[6] = myself->closure.frame->slots[5]; /* total_inline_c_types */
  frame->slots[7] = myself->closure.frame->slots[6]; /* total_inline_c_objects */
  frame->slots[8] = myself->closure.frame->slots[9]; /* total_unique_items */
  frame->slots[9] = myself->closure.frame->slots[10]; /* total_constants */
  frame->slots[10] = myself->closure.frame->slots[11]; /* total_variables */
  frame->slots[11] = myself->closure.frame->slots[12]; /* other */
  frame->slots[12] = myself->closure.frame->slots[3]; /* total_methods */
  frame->slots[13] = myself->closure.frame->slots[4]; /* total_inline_c_methods */
  frame->slots[14] = myself->closure.frame->slots[7]; /* total_attributes */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 848: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_232;
}
static void cont__36_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__1 */ = arguments->slots[0];
  // 849: ... : inc &total_functions
  frame->slots[16] /* temp__2 */ = create_closure(entry__36_233, 0);
  // 850: ... : inc &total_polymorphic_functions
  frame->slots[17] /* temp__3 */ = create_closure(entry__36_235, 0);
  // 851: ... : inc &total_polymorphic_attributes
  frame->slots[18] /* temp__4 */ = create_closure(entry__36_237, 0);
  // 852: ... : inc &total_inline_c_functions
  frame->slots[19] /* temp__5 */ = create_closure(entry__36_239, 0);
  // 853: ... : inc &total_inline_c_types
  frame->slots[20] /* temp__6 */ = create_closure(entry__36_241, 0);
  // 854: ... : inc &total_inline_c_objects
  frame->slots[21] /* temp__7 */ = create_closure(entry__36_243, 0);
  // 855: ... : inc &total_unique_items
  frame->slots[22] /* temp__8 */ = create_closure(entry__36_245, 0);
  // 856: ... : inc &total_constants
  frame->slots[23] /* temp__9 */ = create_closure(entry__36_247, 0);
  // 857: ... : inc &total_variables
  frame->slots[24] /* temp__10 */ = create_closure(entry__36_249, 0);
  // 858: : inc &other
  frame->slots[25] /* temp__11 */ = create_closure(entry__36_251, 0);
  // 848: case kind_of(info)
  // 849:   FUNCTION: inc &total_functions
  // 850:   POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 851:   POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 852:   INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 853:   INLINE_C_TYPE: inc &total_inline_c_types
  // 854:   INLINE_C_OBJECT: inc &total_inline_c_objects
  // 855:   UNIQUE_ITEM: inc &total_unique_items
  // 856:   CONSTANT: inc &total_constants
  // 857:   VARIABLE: inc &total_variables
  // ...
  argument_count = 20;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = frame->slots[16] /* temp__2 */;
  arguments->slots[3] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[4] = frame->slots[17] /* temp__3 */;
  arguments->slots[5] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[6] = frame->slots[18] /* temp__4 */;
  arguments->slots[7] = var._INLINE_C_FUNCTION;
  arguments->slots[8] = frame->slots[19] /* temp__5 */;
  arguments->slots[9] = var._INLINE_C_TYPE;
  arguments->slots[10] = frame->slots[20] /* temp__6 */;
  arguments->slots[11] = var._INLINE_C_OBJECT;
  arguments->slots[12] = frame->slots[21] /* temp__7 */;
  arguments->slots[13] = var._UNIQUE_ITEM;
  arguments->slots[14] = frame->slots[22] /* temp__8 */;
  arguments->slots[15] = var._CONSTANT;
  arguments->slots[16] = frame->slots[23] /* temp__9 */;
  arguments->slots[17] = var._VARIABLE;
  arguments->slots[18] = frame->slots[24] /* temp__10 */;
  arguments->slots[19] = frame->slots[25] /* temp__11 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__36_253;
}
static void entry__36_233(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_functions: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 849: ... inc &total_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_234;
}
static void cont__36_234(void) {
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
static void entry__36_235(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_functions: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_polymorphic_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 850: ... inc &total_polymorphic_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_236;
}
static void cont__36_236(void) {
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
static void entry__36_237(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_polymorphic_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 851: ... inc &total_polymorphic_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_238;
}
static void cont__36_238(void) {
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
static void entry__36_239(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_functions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* total_inline_c_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 852: ... inc &total_inline_c_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_240;
}
static void cont__36_240(void) {
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
static void entry__36_241(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_types: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* total_inline_c_types */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 853: ... inc &total_inline_c_types
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_242;
}
static void cont__36_242(void) {
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
static void entry__36_243(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_objects: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* total_inline_c_objects */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 854: ... inc &total_inline_c_objects
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_244;
}
static void cont__36_244(void) {
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
static void entry__36_245(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_unique_items: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* total_unique_items */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 855: ... inc &total_unique_items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_246;
}
static void cont__36_246(void) {
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
static void entry__36_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_constants: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* total_constants */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 856: ... inc &total_constants
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_constants */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_248;
}
static void cont__36_248(void) {
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
static void entry__36_249(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_variables: 0
  frame->slots[0] = myself->closure.frame->slots[10]; /* total_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 857: ... inc &total_variables
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_variables */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_250;
}
static void cont__36_250(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_variables */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_251(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // other: 0
  frame->slots[0] = myself->closure.frame->slots[11]; /* other */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 858: ... inc &other
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* other */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__36_252;
}
static void cont__36_252(void) {
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
static void cont__36_253(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 859: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_254;
}
static void cont__36_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__1 */ = arguments->slots[0];
  // 859: ... :
  // 860:   for_each methods_of(info): (method_name method_info)
  // 861:     case kind_of(method_info)
  // 862:       FUNCTION: inc &total_methods
  // 863:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 864:       : inc &total_attributes
  frame->slots[16] /* temp__2 */ = create_closure(entry__36_255, 0);
  // 859: case kind_of(info) INLINE_C_TYPE:
  // 860:   for_each methods_of(info): (method_name method_info)
  // 861:     case kind_of(method_info)
  // 862:       FUNCTION: inc &total_methods
  // 863:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 864:       : inc &total_attributes
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__1 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  arguments->slots[2] = frame->slots[16] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_265(void) {
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
  frame->cont = cont__36_266;
}
static void cont__36_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__10 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[23] /* temp__10 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_267;
}
static void cont__36_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__9 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[22] /* temp__9 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_268;
}
static void cont__36_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__8 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[21] /* temp__8 */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_269;
}
static void cont__36_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__7 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__7 */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_270;
}
static void cont__36_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__6 */;
  arguments->slots[1] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_271;
}
static void cont__36_271(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__5 */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_272;
}
static void cont__36_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__4 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__4 */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_273;
}
static void cont__36_273(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_274;
}
static void cont__36_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_275;
}
static void cont__36_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 866: $total_definitions
  // 867:   +
  // 868:     total_functions
  // 869:     total_polymorphic_functions
  // 870:     total_polymorphic_attributes
  // 871:     total_methods
  // 872:     total_inline_c_methods
  // 873:     total_inline_c_types
  // 874:     total_inline_c_objects
  // 875:     total_attributes
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[11])->contents /* total_variables */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_276;
}
static void cont__36_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[13] /* total_definitions */, arguments->slots[0]);
  // 882: ... pad_left(total_definitions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* total_definitions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_277;
}
static void cont__36_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__2 */ = arguments->slots[0];
  // 884: ... pad_left(total_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_278;
}
static void cont__36_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__3 */ = arguments->slots[0];
  // 885: ... pad_left(total_polymorphic_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* total_polymorphic_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_279;
}
static void cont__36_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__4 */ = arguments->slots[0];
  // 886: ... pad_left(total_polymorphic_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_280;
}
static void cont__36_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__5 */ = arguments->slots[0];
  // 887: ... pad_left(total_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* total_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_281;
}
static void cont__36_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__6 */ = arguments->slots[0];
  // 888: ... pad_left(total_inline_c_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* total_inline_c_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_282;
}
static void cont__36_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__7 */ = arguments->slots[0];
  // 889: ... pad_left(total_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* total_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_283;
}
static void cont__36_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__8 */ = arguments->slots[0];
  // 890: ... pad_left(total_inline_c_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* total_inline_c_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_284;
}
static void cont__36_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__9 */ = arguments->slots[0];
  // 891: ... pad_left(total_inline_c_types 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* total_inline_c_types */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_285;
}
static void cont__36_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__10 */ = arguments->slots[0];
  // 892: ... pad_left(total_inline_c_objects 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* total_inline_c_objects */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_286;
}
static void cont__36_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__11 */ = arguments->slots[0];
  // 893: ... pad_left(total_unique_items 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* total_unique_items */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_287;
}
static void cont__36_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__12 */ = arguments->slots[0];
  // 894: ... pad_left(total_constants 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* total_constants */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_288;
}
static void cont__36_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__13 */ = arguments->slots[0];
  // 895: ... pad_left(total_variables 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* total_variables */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_289;
}
static void cont__36_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[27] /* temp__14 */ = arguments->slots[0];
  // 897: ... pad_left(other 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[12])->contents /* other */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__36_290;
}
static void cont__36_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[28] /* temp__15 */ = arguments->slots[0];
  // 881: ... "
  // 882:   total definitions:     @(pad_left(total_definitions 5))
  // 883:   
  // 884:   functions:             @(pad_left(total_functions 5))
  // 885:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 886:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 887:   method definitions:    @(pad_left(total_methods 5))
  // 888:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 889:   attribute definitions: @(pad_left(total_attributes 5))
  // 890:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 29;
  arguments = node_p;
  arguments->slots[0] = string__36_291;
  arguments->slots[1] = frame->slots[15] /* temp__2 */;
  arguments->slots[2] = string__36_292;
  arguments->slots[3] = frame->slots[16] /* temp__3 */;
  arguments->slots[4] = string__36_293;
  arguments->slots[5] = frame->slots[17] /* temp__4 */;
  arguments->slots[6] = string__36_294;
  arguments->slots[7] = frame->slots[18] /* temp__5 */;
  arguments->slots[8] = string__36_295;
  arguments->slots[9] = frame->slots[19] /* temp__6 */;
  arguments->slots[10] = string__36_296;
  arguments->slots[11] = frame->slots[20] /* temp__7 */;
  arguments->slots[12] = string__36_297;
  arguments->slots[13] = frame->slots[21] /* temp__8 */;
  arguments->slots[14] = string__36_298;
  arguments->slots[15] = frame->slots[22] /* temp__9 */;
  arguments->slots[16] = string__36_299;
  arguments->slots[17] = frame->slots[23] /* temp__10 */;
  arguments->slots[18] = string__36_300;
  arguments->slots[19] = frame->slots[24] /* temp__11 */;
  arguments->slots[20] = string__36_301;
  arguments->slots[21] = frame->slots[25] /* temp__12 */;
  arguments->slots[22] = string__36_302;
  arguments->slots[23] = frame->slots[26] /* temp__13 */;
  arguments->slots[24] = string__36_303;
  arguments->slots[25] = frame->slots[27] /* temp__14 */;
  arguments->slots[26] = string__36_304;
  arguments->slots[27] = frame->slots[28] /* temp__15 */;
  arguments->slots[28] = string__24_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_305;
}
static void cont__36_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 881: ewrite "
  // 882:   total definitions:     @(pad_left(total_definitions 5))
  // 883:   
  // 884:   functions:             @(pad_left(total_functions 5))
  // 885:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 886:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 887:   method definitions:    @(pad_left(total_methods 5))
  // 888:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 889:   attribute definitions: @(pad_left(total_attributes 5))
  // 890:   inline C functions:    @(pad_left(total_inline_c_functions 5))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_1_sim2c__extract_documentation(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 696: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__36_2;
}
static void cont__36_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 696: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__36_3;
}
static void cont__36_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 697: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__36_4;
}
static void cont__36_4(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 699: for_each definitions: (iname info)
  // 700:   $name name_of(info)
  // 701:   !short_descriptions(name) get_short_description(name info)
  // 702:   
  // 703:   if kind_of(info) == INLINE_C_TYPE:
  // 704:     $base base_of(info)
  // 705:     if base.is_defined: add_derived_type base iname
  // 706:     $$methods empty_key_order_table
  // 707:     for_each methods_of(info): ($method_name method_info)
  // 708:       unless method_name .contains. "::":
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__36_5;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_38;
}
static void entry__36_11(void) {
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
  // 704: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__36_12;
}
static void cont__36_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* base */, arguments->slots[0]);
  // 705: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_13;
}
static void cont__36_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 705: ... : add_derived_type base iname
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_14, 0);
  // 705: if base.is_defined: add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_15;
}
static void entry__36_14(void) {
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
  // 705: ... add_derived_type base iname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* iname */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: $$methods empty_key_order_table
  ((CELL *)frame->slots[4])->contents /* methods */ = get__empty_key_order_table();
  // 707: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__36_16;
}
static void cont__36_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 707: ... : ($method_name method_info)
  // 708:   unless method_name .contains. "::":
  // 709:     !method_name attribute_of(method_info).resolved_name
  // 710:   $sd_name string(name "/" method_name)
  // 711:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 712:   $oname
  // 713:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 714:   !definitions(oname).types_of(name) true
  // 715:   !methods(method_name) method_info
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_17, 2);
  // 707: for_each methods_of(info): ($method_name method_info)
  // 708:   unless method_name .contains. "::":
  // 709:     !method_name attribute_of(method_info).resolved_name
  // 710:   $sd_name string(name "/" method_name)
  // 711:   !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 712:   $oname
  // 713:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 714:   !definitions(oname).types_of(name) true
  // 715:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_35;
}
static void entry__36_17(void) {
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
  // 708: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__36_18;
}
static void cont__36_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 708: ... :
  // 709:   !method_name attribute_of(method_info).resolved_name
  frame->slots[7] /* temp__2 */ = create_closure(entry__36_19, 0);
  // 708: unless method_name .contains. "::":
  // 709:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__36_22;
}
static void entry__36_19(void) {
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
  // 709: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__36_20;
}
static void cont__36_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 709: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__36_21;
}
static void cont__36_21(void) {
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
static void cont__36_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 710: $sd_name string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__36_23;
  arguments->slots[2] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_24;
}
static void cont__36_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* sd_name */, arguments->slots[0]);
  // 711: !short_descriptions(sd_name) get_short_description(sd_name method_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__36_25;
}
static void cont__36_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 711: !short_descriptions(sd_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* sd_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__36_26;
}
static void cont__36_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 713: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__36_27;
}
static void cont__36_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 713: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_28;
}
static void cont__36_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 712: $oname
  // 713:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__36_29;
}
static void cont__36_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* oname */, arguments->slots[0]);
  // 714: !definitions(oname).types_of(name) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 714: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__36_30;
}
static void cont__36_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 714: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__36_31;
}
static void cont__36_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 714: !definitions(oname).types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[8] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__36_32;
}
static void cont__36_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 714: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[7] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[8] /* temp__3 */);
    frame->slots[7] /* temp__2 */ = temp;

  }
  // 714: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* oname */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__36_33;
}
static void cont__36_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 715: !methods(method_name) method_info
  frame->slots[6] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 715: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__36_34;
}
static void cont__36_34(void) {
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
static void cont__36_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 716: !definitions(iname).methods_of methods
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* methods */;
  // 716: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__36_36;
}
static void cont__36_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 716: !definitions(iname).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[5] /* temp__1 */);
    frame->slots[6] /* temp__2 */ = temp;

  }
  // 716: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__36_37;
}
static void cont__36_37(void) {
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
static void entry__36_5(void) {
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
  // 700: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__36_6;
}
static void cont__36_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 701: !short_descriptions(name) get_short_description(name info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._get_short_description;
  func = myself->type;
  frame->cont = cont__36_7;
}
static void cont__36_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 701: !short_descriptions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__36_8;
}
static void cont__36_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._short_descriptions = arguments->slots[0];
  // 703: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_9;
}
static void cont__36_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 703: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_10;
}
static void cont__36_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 703: ... :
  // 704:   $base base_of(info)
  // 705:   if base.is_defined: add_derived_type base iname
  // 706:   $$methods empty_key_order_table
  // 707:   for_each methods_of(info): ($method_name method_info)
  // 708:     unless method_name .contains. "::":
  // 709:       !method_name attribute_of(method_info).resolved_name
  // 710:     $sd_name string(name "/" method_name)
  // 711:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 712:     $oname
  // ...
  frame->slots[5] /* temp__3 */ = create_closure(entry__36_11, 0);
  // 703: if kind_of(info) == INLINE_C_TYPE:
  // 704:   $base base_of(info)
  // 705:   if base.is_defined: add_derived_type base iname
  // 706:   $$methods empty_key_order_table
  // 707:   for_each methods_of(info): ($method_name method_info)
  // 708:     unless method_name .contains. "::":
  // 709:       !method_name attribute_of(method_info).resolved_name
  // 710:     $sd_name string(name "/" method_name)
  // 711:     !short_descriptions(sd_name) get_short_description(sd_name method_info)
  // 712:     $oname
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
static void cont__36_38(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: create_page "html/type_index.html":
  // 719:   $print_type_info:
  // 720:     (
  // 721:       info
  // 722:       indent = 0
  // 723:     )
  // 724:     TR:
  // 725:       $qname name_of(info)
  // 726:       $remark_lines remark_lines_of(info)
  // 727:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_39;
  arguments->slots[1] = func__36_40;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__36_78;
}
static void entry__36_77(void) {
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
  // 741: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_70(void) {
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
  // 740: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_71;
}
static void cont__36_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 740: ... kind_of(info) == INLINE_C_TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._INLINE_C_TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_72;
}
static void cont__36_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 740: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__36_73, 0);
  // 740: ... kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__36_76;
}
static void entry__36_73(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 740: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__36_74;
}
static void cont__36_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 740: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__36_75;
}
static void cont__36_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 740: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 740: ... :
  // 741:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__36_77, 0);
  // 740: if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 741:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_69(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 739: ... : (_base info)
  // 740:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 741:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_70, 2);
  // 739: for_each definitions: (_base info)
  // 740:   if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 741:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_40(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 719: ... :
  // 720:   (
  // 721:     info
  // 722:     indent = 0
  // 723:   )
  // 724:   TR:
  // 725:     $qname name_of(info)
  // 726:     $remark_lines remark_lines_of(info)
  // 727:     if qname.is_defined:
  // 728:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_41_print_type_info, -1);
  // 719: $print_type_info:
  // 720:   (
  // 721:     info
  // 722:     indent = 0
  // 723:   )
  // 724:   TR:
  // 725:     $qname name_of(info)
  // 726:     $remark_lines remark_lines_of(info)
  // 727:     if qname.is_defined:
  // 728:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 736: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__36_67;
}
static void entry__36_64(void) {
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
  // 734: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__36_65;
}
static void cont__36_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 734: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__36_66;
}
static void cont__36_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 734: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_42(void) {
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
  // 725: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__36_43;
}
static void cont__36_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 726: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__36_44;
}
static void cont__36_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 727: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_45;
}
static void cont__36_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 727: ... :
  // 728:   TD:
  // 729:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_46, 0);
  // 727: if qname.is_defined:
  // 728:   TD:
  // 729:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_53;
}
static void entry__36_47(void) {
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
  // 729: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_8;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__36_48;
}
static void cont__36_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 729: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__36_49;
}
static void cont__36_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 730: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_50;
}
static void cont__36_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 730: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_51;
}
static void cont__36_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 730: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_52;
}
static void cont__36_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 730: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_46(void) {
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
  // 728: ... :
  // 729:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_47, 0);
  // 728: TD:
  // 729:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 731: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
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
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 731: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__36_55, 0);
  // 731: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__36_58;
}
static void entry__36_55(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_56;
}
static void cont__36_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 731: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__36_57;
}
static void cont__36_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 731: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 731: ... :
  // 732:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__36_59, 0);
  // 731: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 732:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_62;
}
static void entry__36_59(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 732: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__36_60;
}
static void cont__36_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 732: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__36_61;
}
static void cont__36_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 732: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_62(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 733: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__36_63;
}
static void cont__36_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 733: ... : (name)
  // 734:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__36_64, 1);
  // 733: for_each derived_types_of(info): (name)
  // 734:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_41_print_type_info(void) {
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
  // 724: ... :
  // 725:   $qname name_of(info)
  // 726:   $remark_lines remark_lines_of(info)
  // 727:   if qname.is_defined:
  // 728:     TD:
  // 729:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:       A "href" = "@(qname.mangled).html" qname
  // 731:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 732:     TD remark_lines.to_paragraphs(1)
  // 733:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_42, 0);
  // 724: TR:
  // 725:   $qname name_of(info)
  // 726:   $remark_lines remark_lines_of(info)
  // 727:   if qname.is_defined:
  // 728:     TD:
  // 729:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 730:       A "href" = "@(qname.mangled).html" qname
  // 731:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 732:     TD remark_lines.to_paragraphs(1)
  // 733:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 737: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_17;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_68;
}
static void cont__36_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: ... :
  // 739:   for_each definitions: (_base info)
  // 740:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 741:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_69, 0);
  // 738: TABLE:
  // 739:   for_each definitions: (_base info)
  // 740:     if kind_of(info) == INLINE_C_TYPE && base_of(info).is_undefined:
  // 741:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: create_page "html/symbol_index.html":
  // 744:   link_bar
  // 745:   H1 "id" = "index" "Symbol Index"
  // 746:   from_to
  // 747:     'a'
  // 748:     'z': (letter)
  // 749:       A "href" = "#@(letter)" letter.to_upper_case
  // 750:     :
  // 751:       TEXT " "
  // 752:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_79;
  arguments->slots[1] = func__36_80;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__36_169;
}
static void entry__36_155(void) {
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
  // 796: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_156;
  arguments->slots[1] = string__36_157;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_158;
}
static void cont__36_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 796: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__36_159;
}
static void cont__36_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 796: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_160;
}
static void cont__36_160(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 797: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_161, 0);
  // 797: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_166;
}
static void entry__36_161(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 797: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_162;
}
static void cont__36_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 797: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_163;
}
static void cont__36_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 797: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_164;
}
static void cont__36_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 797: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__26_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__36_165;
}
static void cont__36_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 797: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_166(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 798: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_352;
  arguments->slots[1] = string__36_167;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_168;
}
static void cont__36_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 798: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_154(void) {
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
  // 795: ... :
  // 796:   TD "align" = "right" name .until. "::"
  // 797:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 798:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_155, 0);
  // 795: TR:
  // 796:   TD "align" = "right" name .until. "::"
  // 797:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 798:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_96(void) {
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
  // 756: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__36_97;
}
static void cont__36_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 756: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__36_98;
}
static void cont__36_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 756: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__36_99;
}
static void cont__36_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 756: ... :
  // 757:   !letter iname(1)
  // 758:   TR:
  // 759:     TD "colspan" = 3:
  // 760:       H2 "id" = letter:
  // 761:         TEXT letter.to_upper_case
  // 762:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__36_100, 0);
  // 756: if iname(1) != letter:
  // 757:   !letter iname(1)
  // 758:   TR:
  // 759:     TD "colspan" = 3:
  // 760:       H2 "id" = letter:
  // 761:         TEXT letter.to_upper_case
  // 762:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_113;
}
static void entry__36_107(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 761: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__36_108;
}
static void cont__36_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 761: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__36_109;
}
static void cont__36_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 762: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__36_110;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_111;
}
static void cont__36_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 762: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__36_112;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_105(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_82;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_106;
}
static void cont__36_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 760: ... :
  // 761:   TEXT letter.to_upper_case
  // 762:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_107, 0);
  // 760: H2 "id" = letter:
  // 761:   TEXT letter.to_upper_case
  // 762:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_102(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 759: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_103;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_104;
}
static void cont__36_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 759: ... :
  // 760:   H2 "id" = letter:
  // 761:     TEXT letter.to_upper_case
  // 762:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__36_105, 0);
  // 759: TD "colspan" = 3:
  // 760:   H2 "id" = letter:
  // 761:     TEXT letter.to_upper_case
  // 762:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_100(void) {
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
  // 757: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__36_101;
}
static void cont__36_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 758: ... :
  // 759:   TD "colspan" = 3:
  // 760:     H2 "id" = letter:
  // 761:       TEXT letter.to_upper_case
  // 762:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_102, 0);
  // 758: TR:
  // 759:   TD "colspan" = 3:
  // 760:     H2 "id" = letter:
  // 761:       TEXT letter.to_upper_case
  // 762:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_113(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 764: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__36_114;
}
static void cont__36_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 765: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__36_115;
}
static void cont__36_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 766: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_116;
}
static void cont__36_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 766: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__36_117, 0);
  // 766: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__36_120;
}
static void entry__36_117(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 766: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__36_118;
}
static void cont__36_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 766: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__36_119;
}
static void cont__36_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 766: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 766: ... :
  // 767:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__36_121, 0);
  // 766: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 767:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_124;
}
static void entry__36_121(void) {
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
  // 767: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__36_122;
}
static void cont__36_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 767: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__36_123;
}
static void cont__36_123(void) {
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
static void cont__36_124(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 771: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_125;
}
static void cont__36_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 769: $kind_info
  // 770:   case
  // 771:     kind_of(info)
  // 772:     FUNCTION
  // 773:     -> "function"
  // 774:     INLINE_C_FUNCTION
  // 775:     -> "inline-C function"
  // 776:     POLYMORPHIC
  // 777:     -> "polymorphic function"
  // 778:     UNIQUE_ITEM
  // ...
  argument_count = 16;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__36_126;
  arguments->slots[3] = var._INLINE_C_FUNCTION;
  arguments->slots[4] = func__36_128;
  arguments->slots[5] = get__POLYMORPHIC();
  arguments->slots[6] = func__36_130;
  arguments->slots[7] = var._UNIQUE_ITEM;
  arguments->slots[8] = func__36_132;
  arguments->slots[9] = var._CONSTANT;
  arguments->slots[10] = func__36_134;
  arguments->slots[11] = var._INLINE_C_TYPE;
  arguments->slots[12] = func__36_136;
  arguments->slots[13] = var._INLINE_C_OBJECT;
  arguments->slots[14] = func__36_138;
  arguments->slots[15] = func__36_140;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__36_141;
}
static void entry__36_126(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 773: -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_127;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_128(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 775: -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_129;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_130(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 777: -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_131;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_132(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 779: -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_133;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_134(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 781: -> "constant"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_135;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_136(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 783: -> "inine-C type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_137;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_138(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: -> "inine-C object"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_139;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_140(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 786: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 788: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_142;
}
static void cont__36_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 788: ... :
  // 789:   if
  // 790:     remark.is_defined:
  // 791:       !remark string(remark " (" kind_info ")")
  // 792:     :
  // 793:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__36_143, 0);
  // 788: if kind_info.is_defined:
  // 789:   if
  // 790:     remark.is_defined:
  // 791:       !remark string(remark " (" kind_info ")")
  // 792:     :
  // 793:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__36_149;
}
static void entry__36_145(void) {
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
  // 791: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__36_146;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__34_100;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_147;
}
static void cont__36_147(void) {
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
static void entry__36_148(void) {
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
  // 793: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__36_143(void) {
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
  // 790: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_144;
}
static void cont__36_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 790: ... :
  // 791:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_145, 0);
  // 792: :
  // 793:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__36_148, 0);
  // 789: if
  // 790:   remark.is_defined:
  // 791:     !remark string(remark " (" kind_info ")")
  // 792:   :
  // 793:     !remark kind_info
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
static void cont__36_149(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 794: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_150;
}
static void cont__36_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 794: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__36_151, 0);
  // 794: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__36_153;
}
static void entry__36_151(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 794: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__36_152;
}
static void cont__36_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 794: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__36_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 794: ... :
  // 795:   TR:
  // 796:     TD "align" = "right" name .until. "::"
  // 797:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 798:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__36_154, 0);
  // 794: if remark.is_defined && name.is_defined:
  // 795:   TR:
  // 796:     TD "align" = "right" name .until. "::"
  // 797:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 798:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_95(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 754: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 755: ... : (iname info)
  // 756:   if iname(1) != letter:
  // 757:     !letter iname(1)
  // 758:     TR:
  // 759:       TD "colspan" = 3:
  // 760:         H2 "id" = letter:
  // 761:           TEXT letter.to_upper_case
  // 762:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 763:   $$remark undefined
  // 764:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_96, 2);
  // 755: for_each definitions: (iname info)
  // 756:   if iname(1) != letter:
  // 757:     !letter iname(1)
  // 758:     TR:
  // 759:       TD "colspan" = 3:
  // 760:         H2 "id" = letter:
  // 761:           TEXT letter.to_upper_case
  // 762:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 763:   $$remark undefined
  // 764:   $name name_of(info)
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
static void entry__36_80(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__36_81;
}
static void cont__36_81(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_82;
  arguments->slots[1] = string__36_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_84;
}
static void cont__36_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 745: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_22;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_85;
}
static void cont__36_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 746: from_to
  // 747:   'a'
  // 748:   'z': (letter)
  // 749:     A "href" = "#@(letter)" letter.to_upper_case
  // 750:   :
  // 751:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__36_86;
  arguments->slots[3] = func__36_91;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__36_93;
}
static void entry__36_86(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 749: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_87;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_88;
}
static void cont__36_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 749: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_89;
}
static void cont__36_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 749: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__36_90;
}
static void cont__36_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 749: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_91(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 751: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_92;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_93(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 752: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__36_94;
}
static void cont__36_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: TABLE:
  // 754:   $$letter undefined
  // 755:   for_each definitions: (iname info)
  // 756:     if iname(1) != letter:
  // 757:       !letter iname(1)
  // 758:       TR:
  // 759:         TD "colspan" = 3:
  // 760:           H2 "id" = letter:
  // 761:             TEXT letter.to_upper_case
  // 762:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_95;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_169(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 800: for_each definitions: (_iname info)
  // 801:   $name name_of(info)
  // 802:   create_info_page name info
  // 803:   case kind_of(info) INLINE_C_TYPE:
  // 804:     for_each methods_of(info): (method_name method_info)
  // 805:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__36_170;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_178;
}
static void entry__36_176(void) {
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
  // 805: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__36_23;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_177;
}
static void cont__36_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 805: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_174(void) {
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
  // 804: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__36_175;
}
static void cont__36_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 804: ... : (method_name method_info)
  // 805:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__36_176, 2);
  // 804: for_each methods_of(info): (method_name method_info)
  // 805:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_170(void) {
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
  // 801: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__36_171;
}
static void cont__36_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 802: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__36_172;
}
static void cont__36_172(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 803: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__36_173;
}
static void cont__36_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 803: ... :
  // 804:   for_each methods_of(info): (method_name method_info)
  // 805:     create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_174, 0);
  // 803: case kind_of(info) INLINE_C_TYPE:
  // 804:   for_each methods_of(info): (method_name method_info)
  // 805:     create_info_page string(name "/" method_name) method_info
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
static void cont__36_178(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 807: create_page "html/topic_index.html":
  // 808:   link_bar
  // 809:   H1 "id" = "index" "Topic Index"
  // 810:   TABLE:
  // 811:     for_each topics: (topic _references)
  // 812:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 813:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_179;
  arguments->slots[1] = func__36_180;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__36_193;
}
static void entry__36_191(void) {
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
  // 813: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_192;
}
static void cont__36_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 813: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_190(void) {
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
  // 813: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_191, 0);
  // 813: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_185(void) {
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
  // 812: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__36_186;
}
static void cont__36_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 812: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__34_338;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_187;
}
static void cont__36_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 812: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_188;
}
static void cont__36_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 812: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_189;
}
static void cont__36_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 813: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__36_190, 0);
  // 813: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_184(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 811: for_each topics: (topic _references)
  // 812:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 813:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__36_185;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_180(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 808: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__36_181;
}
static void cont__36_181(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 809: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_82;
  arguments->slots[1] = string__36_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_182;
}
static void cont__36_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 809: H1 "id" = "index" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_27;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_183;
}
static void cont__36_183(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 810: TABLE:
  // 811:   for_each topics: (topic _references)
  // 812:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 813:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_184;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_193(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 814: for_each topics: (topic references)
  // 815:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 816:   create_page "html/@(filename).html":
  // 817:     link_bar
  // 818:     H1 "id" = "index" topic
  // 819:     TABLE:
  // 820:       for_each references: (reference)
  // 821:         TR:
  // 822:           TD: A "href" = string(reference.mangled ".html") reference
  // 823:           TD "&nbsp;"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__36_194;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__36_213;
}
static void entry__36_205(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 822: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_206, 0);
  // 822: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_210;
}
static void entry__36_206(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 822: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__36_207;
}
static void cont__36_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 822: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__34_37;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__36_208;
}
static void cont__36_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 822: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_209;
}
static void cont__36_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 822: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_210(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 823: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_282;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__36_211;
}
static void cont__36_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 824: ... short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._short_descriptions;
  func = myself->type;
  frame->cont = cont__36_212;
}
static void cont__36_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 824: TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_204(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 821: ... :
  // 822:   TD: A "href" = string(reference.mangled ".html") reference
  // 823:   TD "&nbsp;"
  // 824:   TD short_descriptions(reference)
  frame->slots[1] /* temp__1 */ = create_closure(entry__36_205, 0);
  // 821: TR:
  // 822:   TD: A "href" = string(reference.mangled ".html") reference
  // 823:   TD "&nbsp;"
  // 824:   TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_203(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 820: for_each references: (reference)
  // 821:   TR:
  // 822:     TD: A "href" = string(reference.mangled ".html") reference
  // 823:     TD "&nbsp;"
  // 824:     TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__36_204;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_199(void) {
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
  // 817: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__36_200;
}
static void cont__36_200(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 818: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_82;
  arguments->slots[1] = string__36_83;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_201;
}
static void cont__36_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 818: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_202;
}
static void cont__36_202(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 819: ... :
  // 820:   for_each references: (reference)
  // 821:     TR:
  // 822:       TD: A "href" = string(reference.mangled ".html") reference
  // 823:       TD "&nbsp;"
  // 824:       TD short_descriptions(reference)
  frame->slots[2] /* temp__1 */ = create_closure(entry__36_203, 0);
  // 819: TABLE:
  // 820:   for_each references: (reference)
  // 821:     TR:
  // 822:       TD: A "href" = string(reference.mangled ".html") reference
  // 823:       TD "&nbsp;"
  // 824:       TD short_descriptions(reference)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_194(void) {
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
  // 815: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__36_195;
}
static void cont__36_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 815: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__34_338;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_196;
}
static void cont__36_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 815: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__36_197;
}
static void cont__36_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 816: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__34_36;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__34_37;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__36_198;
}
static void cont__36_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 816: ... :
  // 817:   link_bar
  // 818:   H1 "id" = "index" topic
  // 819:   TABLE:
  // 820:     for_each references: (reference)
  // 821:       TR:
  // 822:         TD: A "href" = string(reference.mangled ".html") reference
  // 823:         TD "&nbsp;"
  // 824:         TD short_descriptions(reference)
  frame->slots[4] /* temp__2 */ = create_closure(entry__36_199, 0);
  // 816: create_page "html/@(filename).html":
  // 817:   link_bar
  // 818:   H1 "id" = "index" topic
  // 819:   TABLE:
  // 820:     for_each references: (reference)
  // 821:       TR:
  // 822:         TD: A "href" = string(reference.mangled ".html") reference
  // 823:         TD "&nbsp;"
  // 824:         TD short_descriptions(reference)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_213(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 825: create_page "html/index.html":
  // 826:   H1 "Simplicity"
  // 827:   P: A "href" = "manual.html" "Manual"
  // 828:   P: A "href" = "type_index.html" "Type Index"
  // 829:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 830:   P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__36_214;
  arguments->slots[1] = func__36_215;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__36_229;
}
static void entry__36_227(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 830: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_228;
}
static void cont__36_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 830: ... A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__36_215(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 826: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__36_216;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__36_217;
}
static void cont__36_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 827: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_218;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__36_220;
}
static void entry__36_218(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 827: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_219;
}
static void cont__36_219(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 827: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_12;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_220(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 828: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_221;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__36_223;
}
static void entry__36_221(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 828: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_222;
}
static void cont__36_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 828: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_17;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_223(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 829: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_224;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__36_226;
}
static void entry__36_224(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 829: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_3;
  arguments->slots[1] = string__30_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__36_225;
}
static void cont__36_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 829: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_22;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_226(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 830: P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__36_227;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__36_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 832: if do_print_summary:
  // 833:   $$total_functions 0
  // 834:   $$total_polymorphic_functions 0
  // 835:   $$total_polymorphic_attributes 0
  // 836:   $$total_methods 0
  // 837:   $$total_inline_c_methods 0
  // 838:   $$total_inline_c_types 0
  // 839:   $$total_inline_c_objects 0
  // 840:   $$total_attributes 0
  // 841:   $$total_inline_c_functions 0
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_summary();
  arguments->slots[1] = func__36_230;
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
  var._BORING = collect_node(var._BORING);
  var._FUNCTION = collect_node(var._FUNCTION);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._POLYMORPHIC_ATTRIBUTE = collect_node(var._POLYMORPHIC_ATTRIBUTE);
  var._INLINE_C_TYPE = collect_node(var._INLINE_C_TYPE);
  var._INLINE_C_OBJECT = collect_node(var._INLINE_C_OBJECT);
  var._INLINE_C_FUNCTION = collect_node(var._INLINE_C_FUNCTION);
  var._UNIQUE_ITEM = collect_node(var._UNIQUE_ITEM);
  var._CONSTANT = collect_node(var._CONSTANT);
  var._VARIABLE = collect_node(var._VARIABLE);
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
  unique__BORING = register_unique_item("BORING");
  unique__FUNCTION = register_unique_item("FUNCTION");
  unique__POLYMORPHIC_FUNCTION = register_unique_item("POLYMORPHIC_FUNCTION");
  unique__POLYMORPHIC_ATTRIBUTE = register_unique_item("POLYMORPHIC_ATTRIBUTE");
  unique__INLINE_C_TYPE = register_unique_item("INLINE_C_TYPE");
  unique__INLINE_C_OBJECT = register_unique_item("INLINE_C_OBJECT");
  unique__INLINE_C_FUNCTION = register_unique_item("INLINE_C_FUNCTION");
  unique__UNIQUE_ITEM = register_unique_item("UNIQUE_ITEM");
  unique__CONSTANT = register_unique_item("CONSTANT");
  unique__VARIABLE = register_unique_item("VARIABLE");
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
  func__24_140 = create_function(entry__24_140, 0);
  func__24_141 = create_function(entry__24_141, 0);
  string__24_148 = from_latin_1_string("types::function", 15);
  func__24_167 = create_function(entry__24_167, 0);
  func__24_168 = create_function(entry__24_168, 0);
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
  string__34_9 = from_latin_1_string("types::", 7);
  string__34_14 = from_latin_1_string("std::", 5);
  string__34_27 = from_latin_1_string("The documentation for \042", 23);
  string__34_28 = from_latin_1_string("\042\012(defined in \042", 15);
  string__34_29 = from_latin_1_string("\042)\012references the undefined symbol \042", 36);
  string__34_30 = from_latin_1_string("\042!\012", 3);
  string__34_36 = from_latin_1_string("html/", 5);
  string__34_37 = from_latin_1_string(".html", 5);
  string__34_47 = from_latin_1_string("](", 2);
  string__34_48 = from_latin_1_string(".html)/[", 8);
  string__34_49 = from_latin_1_string(".html)", 6);
  string__34_62 = from_latin_1_string("Missing documentation for ", 26);
  string__34_63 = from_latin_1_string(" (defined in \042", 14);
  string__34_64 = from_latin_1_string("\042)!\012", 4);
  string__34_73 = from_latin_1_string("Parameter", 9);
  string__34_83 = from_latin_1_string(" (optional)", 11);
  string__34_90 = from_latin_1_string(" (zero or more arguments)", 25);
  string__34_99 = from_latin_1_string(" (optional; default value: ", 27);
  string__34_100 = from_latin_1_string(")", 1);
  string__34_109 = from_latin_1_string("Returns", 7);
  string__34_132 = from_latin_1_string("See also:", 9);
  string__34_162 = from_latin_1_string("Technical Details:", 18);
  string__34_180 = from_latin_1_string("[", 1);
  func__34_227 = create_function(entry__34_227, 0);
  func__34_231 = create_function(entry__34_231, 0);
  string__34_238 = from_latin_1_string("Parameters", 10);
  func__34_241 = create_function(entry__34_241, 1);
  func__34_251 = create_function(entry__34_251, 1);
  string__34_259 = from_latin_1_string("Description", 11);
  func__34_261 = create_function(entry__34_261, 1);
  string__34_265 = from_latin_1_string("Technical Details", 17);
  func__34_267 = create_function(entry__34_267, 1);
  string__34_271 = from_latin_1_string("See also", 8);
  string__34_282 = from_latin_1_string("&nbsp;", 6);
  string__34_289 = from_latin_1_string("Implemented by", 14);
  string__34_301 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__34_311 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__34_333 = from_latin_1_string("Topics", 6);
  string__34_338 = from_latin_1_string("_", 1);
  func__34_336 = create_function(entry__34_336, 1);
  string__34_352 = from_latin_1_string("class", 5);
  func__34_359 = create_function(entry__34_359, 1);
  string__34_361 = from_latin_1_string("**", 2);
  string__34_366 = from_latin_1_string("footer", 6);
  string__34_370 = from_latin_1_string("(defined in ", 12);
  string__34_371 = from_latin_1_string(")\012", 2);
  func__34_1_create_info_page = create_function(entry__34_1_create_info_page, 2);
  string__35_27 = from_latin_1_string("\012The short description for \042", 28);
  string__35_28 = from_latin_1_string("\042)\012is quite long:\012", 18);
  func__35_1_get_short_description = create_function(entry__35_1_get_short_description, 2);
  string__36_23 = from_latin_1_string("/", 1);
  func__36_5 = create_function(entry__36_5, 2);
  string__36_39 = from_latin_1_string("html/type_index.html", 20);
  func__36_40 = create_function(entry__36_40, 0);
  string__36_79 = from_latin_1_string("html/symbol_index.html", 22);
  string__36_82 = from_latin_1_string("id", 2);
  string__36_83 = from_latin_1_string("index", 5);
  string__36_87 = from_latin_1_string("#", 1);
  func__36_86 = create_function(entry__36_86, 1);
  string__36_92 = from_latin_1_string(" ", 1);
  func__36_91 = create_function(entry__36_91, 0);
  string__36_103 = from_latin_1_string("colspan", 7);
  string__36_110 = from_latin_1_string("#index", 6);
  string__36_112 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__36_127 = from_latin_1_string("function", 8);
  func__36_126 = create_function(entry__36_126, 0);
  string__36_129 = from_latin_1_string("inline-C function", 17);
  func__36_128 = create_function(entry__36_128, 0);
  string__36_131 = from_latin_1_string("polymorphic function", 20);
  func__36_130 = create_function(entry__36_130, 0);
  string__36_133 = from_latin_1_string("unique item", 11);
  func__36_132 = create_function(entry__36_132, 0);
  string__36_135 = from_latin_1_string("constant", 8);
  func__36_134 = create_function(entry__36_134, 0);
  string__36_137 = from_latin_1_string("inine-C type", 12);
  func__36_136 = create_function(entry__36_136, 0);
  string__36_139 = from_latin_1_string("inine-C object", 14);
  func__36_138 = create_function(entry__36_138, 0);
  func__36_140 = create_function(entry__36_140, 0);
  string__36_146 = from_latin_1_string(" (", 2);
  string__36_156 = from_latin_1_string("align", 5);
  string__36_157 = from_latin_1_string("right", 5);
  string__36_167 = from_latin_1_string("remark", 6);
  func__36_95 = create_function(entry__36_95, 0);
  func__36_80 = create_function(entry__36_80, 0);
  func__36_170 = create_function(entry__36_170, 2);
  string__36_179 = from_latin_1_string("html/topic_index.html", 21);
  func__36_185 = create_function(entry__36_185, 2);
  func__36_184 = create_function(entry__36_184, 0);
  func__36_180 = create_function(entry__36_180, 0);
  func__36_204 = create_function(entry__36_204, 1);
  func__36_194 = create_function(entry__36_194, 2);
  string__36_214 = from_latin_1_string("html/index.html", 15);
  string__36_216 = from_latin_1_string("Simplicity", 10);
  func__36_218 = create_function(entry__36_218, 0);
  func__36_221 = create_function(entry__36_221, 0);
  func__36_224 = create_function(entry__36_224, 0);
  func__36_227 = create_function(entry__36_227, 0);
  func__36_215 = create_function(entry__36_215, 0);
  string__36_291 = from_latin_1_string("total definitions:     ", 23);
  string__36_292 = from_latin_1_string("\012\012functions:             ", 25);
  string__36_293 = from_latin_1_string("\012polymorphic functions: ", 24);
  string__36_294 = from_latin_1_string("\012polymorphic attributes:", 24);
  string__36_295 = from_latin_1_string("\012method definitions:    ", 24);
  string__36_296 = from_latin_1_string("\012inline C methods:      ", 24);
  string__36_297 = from_latin_1_string("\012attribute definitions: ", 24);
  string__36_298 = from_latin_1_string("\012inline C functions:    ", 24);
  string__36_299 = from_latin_1_string("\012inline C types:        ", 24);
  string__36_300 = from_latin_1_string("\012inline C objects:      ", 24);
  string__36_301 = from_latin_1_string("\012unique items:          ", 24);
  string__36_302 = from_latin_1_string("\012other constants:       ", 24);
  string__36_303 = from_latin_1_string("\012variables:             ", 24);
  string__36_304 = from_latin_1_string("\012\012other:                 ", 25);
  func__36_230 = create_function(entry__36_230, 0);
  func__36_1_sim2c__extract_documentation = create_function(entry__36_1_sim2c__extract_documentation, 1);
  string__67_1 = from_latin_1_string("Topic", 5);
  string__68_1 = from_latin_1_string("Example", 7);
  string__68_2 = from_latin_1_string("Output", 6);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__extractor(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  assign_value(&var._BORING, unique__BORING);
  assign_value(&var._FUNCTION, unique__FUNCTION);
  assign_value(&var._POLYMORPHIC_FUNCTION, unique__POLYMORPHIC_FUNCTION);
  assign_value(&var._POLYMORPHIC_ATTRIBUTE, unique__POLYMORPHIC_ATTRIBUTE);
  assign_value(&var._INLINE_C_TYPE, unique__INLINE_C_TYPE);
  assign_value(&var._INLINE_C_OBJECT, unique__INLINE_C_OBJECT);
  assign_value(&var._INLINE_C_FUNCTION, unique__INLINE_C_FUNCTION);
  assign_value(&var._UNIQUE_ITEM, unique__UNIQUE_ITEM);
  assign_value(&var._CONSTANT, unique__CONSTANT);
  assign_value(&var._VARIABLE, unique__VARIABLE);
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
  use_read_only(NULL, "Error", &get__Error, &get_value_or_future__Error);
  use_read_only(NULL, "H1", &get__H1, &get_value_or_future__H1);
  use_read_only(NULL, "H2", &get__H2, &get_value_or_future__H2);
  use_read_only(NULL, "HEAD", &get__HEAD, &get_value_or_future__HEAD);
  use_read_only(NULL, "HTML", &get__HTML, &get_value_or_future__HTML);
  use_read_only(NULL, "METHOD_KIND", &get__METHOD_KIND, &get_value_or_future__METHOD_KIND);
  use_read_only(NULL, "MYSELF_PARAMETER", &get__MYSELF_PARAMETER, &get_value_or_future__MYSELF_PARAMETER);
  use_read_only(NULL, "NAME", &get__NAME, &get_value_or_future__NAME);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "P", &get__P, &get_value_or_future__P);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "PRE", &get__PRE, &get_value_or_future__PRE);
  use_read_only(NULL, "SORT", &get__SORT, &get_value_or_future__SORT);
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
  assign_variable(&var._create_info_page, &func__34_1_create_info_page);
  assign_variable(&var._get_short_description, &func__35_1_get_short_description);
  assign_variable(&var.sim2c__extract_documentation, &func__36_1_sim2c__extract_documentation);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
