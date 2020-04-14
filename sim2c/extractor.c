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
IMPORT void use_single_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *definer
);
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
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
static NODE_GETTER get__do_print_summary;
static NODE_GETTER get_value_or_future__do_print_summary;
static NODE_GETTER get__do_print_warnings;
static NODE_GETTER get_value_or_future__do_print_warnings;
static NODE_GETTER get__dup;
static NODE_GETTER get_value_or_future__dup;
static NODE_GETTER get__emit;
static NODE_GETTER get_value_or_future__emit;
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
static NODE_GETTER get__ewrite;
static NODE_GETTER get_value_or_future__ewrite;
static NODE_GETTER get__ewriteln;
static NODE_GETTER get_value_or_future__ewriteln;
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
static NODE_GETTER get__html__encode;
static NODE_SETTER define__html__encode;
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
  NODE *_topics;
  NODE *_BORING;
  NODE *_TYPE;
  NODE *_FUNCTION;
  NODE *_POLYMORPHIC_FUNCTION;
  NODE *_POLYMORPHIC_ATTRIBUTE;
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
  NODE *_resolve_reference;
  NODE *_TOPIC;
  NODE *_EXAMPLE;
  NODE *_to_paragraphs;
  NODE *_create_info_page;
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
  "topics",
  "BORING",
  "TYPE",
  "FUNCTION",
  "POLYMORPHIC_FUNCTION",
  "POLYMORPHIC_ATTRIBUTE",
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
  "resolve_reference",
  "TOPIC",
  "EXAMPLE",
  "to_paragraphs",
  "create_info_page"
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
static NODE *unique__TYPE;
static NODE *unique__FUNCTION;
static NODE *unique__POLYMORPHIC_FUNCTION;
static NODE *unique__POLYMORPHIC_ATTRIBUTE;
static NODE *unique__INLINE_C_FUNCTION;
static NODE *unique__UNIQUE_ITEM;
static NODE *unique__CONSTANT;
static NODE *unique__VARIABLE;
static NODE *func__20_1_create_page;
static void entry__20_1_create_page(void);
static FRAME_INFO frame__20_1_create_page = {3, {"filename", "body", "page"}};
static NODE *func__20_2;
static void entry__20_2(void);
static FRAME_INFO frame__20_2 = {1, {"body"}};
static NODE *func__20_3;
static void entry__20_3(void);
static FRAME_INFO frame__20_3 = {1, {"body"}};
static NODE *func__20_4;
static void entry__20_4(void);
static FRAME_INFO frame__20_4 = {0, {}};
static NODE *string__20_5;
static void cont__20_6(void);
static void cont__20_7(void);
static NODE *func__22_1_extract_documentation_from_file;
static void entry__22_1_extract_documentation_from_file(void);
static FRAME_INFO frame__22_1_extract_documentation_from_file = {7, {"filename", "return__1", "buf", "fragments", "trees", "first_idx", "local_method_names"}};
static NODE *string__22_2;
static NODE *string__22_3;
static void cont__22_4(void);
static void cont__22_5(void);
static void cont__22_6(void);
static void cont__22_7(void);
static void cont__22_8(void);
static void cont__22_9(void);
static NODE *func__22_10;
static void entry__22_10(void);
static FRAME_INFO frame__22_10 = {0, {}};
static NODE *string__22_11;
static void cont__22_12(void);
static void cont__22_13(void);
static void cont__22_14(void);
static void cont__22_15(void);
static NODE *func__22_16;
static void entry__22_16(void);
static FRAME_INFO frame__22_16 = {0, {}};
static NODE *string__22_17;
static void cont__22_18(void);
static void cont__22_19(void);
static void cont__22_20(void);
static void cont__22_21(void);
static void cont__22_22(void);
static NODE *func__22_23;
static void entry__22_23(void);
static FRAME_INFO frame__22_23 = {0, {}};
static NODE *string__22_24;
static void cont__22_25(void);
static NODE *string__22_26;
static void cont__22_27(void);
static NODE *string__22_28;
static void cont__22_29(void);
static void cont__22_30(void);
static void cont__22_31(void);
static NODE *func__22_32;
static void entry__22_32(void);
static FRAME_INFO frame__22_32 = {1, {"fragment"}};
static void cont__22_33(void);
static void cont__22_34(void);
static NODE *func__22_35;
static void entry__22_35(void);
static FRAME_INFO frame__22_35 = {3, {"done", "fragments", "first_idx"}};
static NODE *func__22_36;
static void entry__22_36(void);
static FRAME_INFO frame__22_36 = {4, {"idx", "fragment", "first_idx", "done"}};
static void cont__22_37(void);
static void cont__22_38(void);
static NODE *func__22_39;
static void entry__22_39(void);
static FRAME_INFO frame__22_39 = {2, {"first_idx", "idx"}};
static void cont__22_40(void);
static NODE *func__22_41;
static void entry__22_41(void);
static FRAME_INFO frame__22_41 = {4, {"first_idx", "idx", "fragment", "tree"}};
static void cont__22_42(void);
static void cont__22_43(void);
static NODE *func__22_44;
static void entry__22_44(void);
static FRAME_INFO frame__22_44 = {1, {"done"}};
static void cont__22_45(void);
static void cont__22_46(void);
static void cont__22_47(void);
static void cont__22_48(void);
static NODE *func__22_49;
static void entry__22_49(void);
static FRAME_INFO frame__22_49 = {2, {"fragment", "trees"}};
static void cont__22_50(void);
static void cont__22_51(void);
static void cont__22_52(void);
static void cont__22_53(void);
static NODE *func__22_54;
static void entry__22_54(void);
static FRAME_INFO frame__22_54 = {0, {}};
static NODE *string__22_55;
static void cont__22_56(void);
static void cont__22_57(void);
static NODE *func__22_58;
static void entry__22_58(void);
static FRAME_INFO frame__22_58 = {2, {"statement", "local_method_names"}};
static NODE *func__22_59;
static void entry__22_59(void);
static FRAME_INFO frame__22_59 = {1, {"statement"}};
static void cont__22_60(void);
static NODE *func__22_61;
static void entry__22_61(void);
static FRAME_INFO frame__22_61 = {0, {}};
static NODE *func__22_62;
static void entry__22_62(void);
static FRAME_INFO frame__22_62 = {1, {"statement"}};
static void cont__22_63(void);
static NODE *func__22_64;
static void entry__22_64(void);
static FRAME_INFO frame__22_64 = {0, {}};
static NODE *func__22_65;
static void entry__22_65(void);
static FRAME_INFO frame__22_65 = {2, {"statement", "local_method_names"}};
static void cont__22_66(void);
static NODE *func__22_67;
static void entry__22_67(void);
static FRAME_INFO frame__22_67 = {3, {"statement", "local_method_names", "destination"}};
static void cont__22_68(void);
static void cont__22_69(void);
static void cont__22_70(void);
static NODE *func__22_71;
static void entry__22_71(void);
static FRAME_INFO frame__22_71 = {4, {"destination", "statement", "local_method_names", "identifier"}};
static void cont__22_72(void);
static void cont__22_73(void);
static void cont__22_74(void);
static NODE *func__22_75;
static void entry__22_75(void);
static FRAME_INFO frame__22_75 = {4, {"statement", "local_method_names", "destination", "source"}};
static void cont__22_76(void);
static void cont__22_77(void);
static void cont__22_78(void);
static NODE *func__22_79;
static void entry__22_79(void);
static FRAME_INFO frame__22_79 = {2, {"local_method_names", "destination"}};
static void cont__22_80(void);
static void cont__22_81(void);
static void cont__22_82(void);
static void cont__22_83(void);
static NODE *func__22_84;
static void entry__22_84(void);
static FRAME_INFO frame__22_84 = {4, {"statement", "break", "filename", "local_method_names"}};
static NODE *func__22_85;
static void entry__22_85(void);
static FRAME_INFO frame__22_85 = {1, {"statement"}};
static void cont__22_86(void);
static NODE *func__22_87;
static void entry__22_87(void);
static FRAME_INFO frame__22_87 = {0, {}};
static NODE *func__22_88;
static void entry__22_88(void);
static FRAME_INFO frame__22_88 = {2, {"statement", "filename"}};
static void cont__22_89(void);
static NODE *func__22_90;
static void entry__22_90(void);
static FRAME_INFO frame__22_90 = {2, {"statement", "filename"}};
static void cont__22_91(void);
static NODE *string__22_92;
static void cont__22_93(void);
static NODE *func__22_94;
static void entry__22_94(void);
static FRAME_INFO frame__22_94 = {4, {"statement", "filename", "identifier", "namespace"}};
static void cont__22_95(void);
static void cont__22_96(void);
static void cont__22_97(void);
static NODE *func__22_98;
static void entry__22_98(void);
static FRAME_INFO frame__22_98 = {6, {"identifier", "statement", "namespace", "filename", "name", "base"}};
static void cont__22_99(void);
static void cont__22_100(void);
static void cont__22_101(void);
static void cont__22_102(void);
static NODE *func__22_103;
static void entry__22_103(void);
static FRAME_INFO frame__22_103 = {1, {"base"}};
static void cont__22_104(void);
static NODE *func__22_105;
static void entry__22_105(void);
static FRAME_INFO frame__22_105 = {0, {}};
static void cont__22_106(void);
static void cont__22_107(void);
static void cont__22_108(void);
static void cont__22_109(void);
static NODE *func__22_110;
static void entry__22_110(void);
static FRAME_INFO frame__22_110 = {4, {"statement", "filename", "break", "local_method_names"}};
static void cont__22_111(void);
static NODE *func__22_112;
static void entry__22_112(void);
static FRAME_INFO frame__22_112 = {6, {"statement", "filename", "break", "local_method_names", "destination", "info"}};
static void cont__22_113(void);
static void cont__22_114(void);
static void cont__22_115(void);
static NODE *func__22_116;
static void entry__22_116(void);
static FRAME_INFO frame__22_116 = {7, {"destination", "info", "statement", "break", "local_method_names", "identifier", "namespace"}};
static void cont__22_117(void);
static void cont__22_118(void);
static void cont__22_119(void);
static NODE *func__22_120;
static void entry__22_120(void);
static FRAME_INFO frame__22_120 = {10, {"identifier", "namespace", "info", "statement", "break", "destination", "local_method_names", "name", "iname", "source"}};
static void cont__22_121(void);
static void cont__22_122(void);
static void cont__22_123(void);
static void cont__22_124(void);
static void cont__22_125(void);
static NODE *func__22_126;
static void entry__22_126(void);
static FRAME_INFO frame__22_126 = {7, {"source", "name", "namespace", "iname", "info", "statement", "break"}};
static void cont__22_127(void);
static NODE *func__22_128;
static void entry__22_128(void);
static FRAME_INFO frame__22_128 = {7, {"name", "namespace", "iname", "info", "source", "statement", "break"}};
static void cont__22_129(void);
static void cont__22_130(void);
static NODE *func__22_131;
static void entry__22_131(void);
static FRAME_INFO frame__22_131 = {0, {}};
static NODE *func__22_132;
static void entry__22_132(void);
static FRAME_INFO frame__22_132 = {0, {}};
static void cont__22_133(void);
static void cont__22_134(void);
static void cont__22_135(void);
static NODE *func__22_136;
static void entry__22_136(void);
static FRAME_INFO frame__22_136 = {2, {"source", "info"}};
static void cont__22_137(void);
static NODE *func__22_138;
static void entry__22_138(void);
static FRAME_INFO frame__22_138 = {2, {"info", "source"}};
static NODE *string__22_139;
static void cont__22_140(void);
static void cont__22_141(void);
static NODE *func__22_142;
static void entry__22_142(void);
static FRAME_INFO frame__22_142 = {3, {"source", "info", "statement"}};
static void cont__22_143(void);
static NODE *func__22_144;
static void entry__22_144(void);
static FRAME_INFO frame__22_144 = {2, {"info", "statement"}};
static void cont__22_145(void);
static NODE *func__22_146;
static void entry__22_146(void);
static FRAME_INFO frame__22_146 = {3, {"source", "info", "statement"}};
static void cont__22_147(void);
static NODE *func__22_148;
static void entry__22_148(void);
static FRAME_INFO frame__22_148 = {3, {"source", "info", "statement"}};
static void cont__22_149(void);
static void cont__22_150(void);
static NODE *func__22_151;
static void entry__22_151(void);
static FRAME_INFO frame__22_151 = {3, {"info", "source", "statement"}};
static void cont__22_152(void);
static void cont__22_153(void);
static NODE *func__22_154;
static void entry__22_154(void);
static FRAME_INFO frame__22_154 = {5, {"source", "iname", "info", "statement", "break"}};
static void cont__22_155(void);
static NODE *func__22_156;
static void entry__22_156(void);
static FRAME_INFO frame__22_156 = {5, {"iname", "info", "source", "statement", "break"}};
static void cont__22_157(void);
static NODE *func__22_158;
static void entry__22_158(void);
static FRAME_INFO frame__22_158 = {0, {}};
static NODE *func__22_159;
static void entry__22_159(void);
static FRAME_INFO frame__22_159 = {0, {}};
static void cont__22_160(void);
static void cont__22_161(void);
static void cont__22_162(void);
static void cont__22_163(void);
static void cont__22_164(void);
static NODE *func__22_165;
static void entry__22_165(void);
static FRAME_INFO frame__22_165 = {3, {"iname", "info", "previous_definition"}};
static void cont__22_166(void);
static void cont__22_167(void);
static NODE *func__22_168;
static void entry__22_168(void);
static FRAME_INFO frame__22_168 = {2, {"previous_definition", "info"}};
static void cont__22_169(void);
static void cont__22_170(void);
static NODE *func__22_171;
static void entry__22_171(void);
static FRAME_INFO frame__22_171 = {2, {"info", "previous_definition"}};
static void cont__22_172(void);
static void cont__22_173(void);
static void cont__22_174(void);
static void cont__22_175(void);
static void cont__22_176(void);
static void cont__22_177(void);
static NODE *func__22_178;
static void entry__22_178(void);
static FRAME_INFO frame__22_178 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__22_179(void);
static void cont__22_180(void);
static void cont__22_181(void);
static void cont__22_182(void);
static void cont__22_183(void);
static NODE *func__22_184;
static void entry__22_184(void);
static FRAME_INFO frame__22_184 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__22_185(void);
static void cont__22_186(void);
static NODE *func__22_187;
static void entry__22_187(void);
static FRAME_INFO frame__22_187 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__22_188(void);
static void cont__22_189(void);
static NODE *func__22_190;
static void entry__22_190(void);
static FRAME_INFO frame__22_190 = {1, {"attr"}};
static void cont__22_191(void);
static void cont__22_192(void);
static void cont__22_193(void);
static void cont__22_194(void);
static void cont__22_195(void);
static void cont__22_196(void);
static void cont__22_197(void);
static void cont__22_198(void);
static NODE *func__23_1_extract_documentation_from_directory;
static void entry__23_1_extract_documentation_from_directory(void);
static FRAME_INFO frame__23_1_extract_documentation_from_directory = {1, {"path"}};
static void cont__23_2(void);
static void cont__23_3(void);
static NODE *func__23_4;
static void entry__23_4(void);
static FRAME_INFO frame__23_4 = {2, {"entry", "name"}};
static void cont__23_5(void);
static NODE *func__23_6;
static void entry__23_6(void);
static FRAME_INFO frame__23_6 = {2, {"entry", "name"}};
static void cont__23_7(void);
static NODE *func__23_8;
static void entry__23_8(void);
static FRAME_INFO frame__23_8 = {1, {"name"}};
static NODE *func__23_9;
static void entry__23_9(void);
static FRAME_INFO frame__23_9 = {1, {"name"}};
static void cont__23_10(void);
static NODE *func__23_11;
static void entry__23_11(void);
static FRAME_INFO frame__23_11 = {1, {"name"}};
static NODE *func__24_1_resolved_name;
static void entry__24_1_resolved_name(void);
static FRAME_INFO frame__24_1_resolved_name = {2, {"attr", "name"}};
static void cont__24_2(void);
static void cont__24_3(void);
static void cont__24_4(void);
static NODE *func__24_5;
static void entry__24_5(void);
static FRAME_INFO frame__24_5 = {1, {"attr"}};
static void cont__24_6(void);
static NODE *func__24_7;
static void entry__24_7(void);
static FRAME_INFO frame__24_7 = {3, {"attr", "name", "resolved_namespace"}};
static void cont__24_8(void);
static NODE *func__24_9;
static void entry__24_9(void);
static FRAME_INFO frame__24_9 = {3, {"namespace", "name", "resolved_namespace"}};
static void cont__24_10(void);
static NODE *func__24_11;
static void entry__24_11(void);
static FRAME_INFO frame__24_11 = {3, {"resolved_namespace", "name", "namespace"}};
static void cont__24_12(void);
static NODE *func__24_13;
static void entry__24_13(void);
static FRAME_INFO frame__24_13 = {1, {"name"}};
static NODE *string__24_14;
static NODE *string__24_15;
static void cont__24_16(void);
static void cont__24_17(void);
static void cont__24_18(void);
static void cont__24_19(void);
static NODE *func__24_20;
static void entry__24_20(void);
static FRAME_INFO frame__24_20 = {1, {"name"}};
static NODE *string__24_21;
static void cont__24_22(void);
static void cont__24_23(void);
static NODE *string__24_24;
static void cont__24_25(void);
static NODE *func__25_1_add_derived_type;
static void entry__25_1_add_derived_type(void);
static FRAME_INFO frame__25_1_add_derived_type = {4, {"base", "name", "ibase", "definition"}};
static void cont__25_2(void);
static void cont__25_3(void);
static void cont__25_4(void);
static void cont__25_5(void);
static void cont__25_6(void);
static NODE *func__25_7;
static void entry__25_7(void);
static FRAME_INFO frame__25_7 = {3, {"definition", "name", "ibase"}};
static void cont__25_8(void);
static void cont__25_9(void);
static void cont__25_10(void);
static void cont__25_11(void);
static NODE *func__25_12;
static void entry__25_12(void);
static FRAME_INFO frame__25_12 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__25_13(void);
static void cont__25_14(void);
static NODE *func__25_15;
static void entry__25_15(void);
static FRAME_INFO frame__25_15 = {2, {"base_of_base", "ibase"}};
static void cont__25_16(void);
static void cont__25_17(void);
static NODE *func__26_1_mangled;
static void entry__26_1_mangled(void);
static FRAME_INFO frame__26_1_mangled = {1, {"name"}};
static void cont__26_2(void);
static NODE *string__26_3;
static void cont__26_4(void);
static void cont__26_5(void);
static NODE *func__27_1_ordered_name;
static void entry__27_1_ordered_name(void);
static FRAME_INFO frame__27_1_ordered_name = {2, {"namespace", "name"}};
static void cont__27_2(void);
static void cont__27_3(void);
static void cont__27_4(void);
static NODE *func__28_1_link_bar;
static void entry__28_1_link_bar(void);
static FRAME_INFO frame__28_1_link_bar = {0, {}};
static NODE *func__28_2;
static void entry__28_2(void);
static FRAME_INFO frame__28_2 = {0, {}};
static NODE *string__28_3;
static NODE *string__28_4;
static void cont__28_5(void);
static NODE *string__28_6;
static void cont__28_7(void);
static NODE *string__28_8;
static void cont__28_9(void);
static NODE *string__28_10;
static void cont__28_11(void);
static NODE *string__28_12;
static void cont__28_13(void);
static void cont__28_14(void);
static NODE *string__28_15;
static void cont__28_16(void);
static NODE *string__28_17;
static void cont__28_18(void);
static void cont__28_19(void);
static NODE *string__28_20;
static void cont__28_21(void);
static NODE *string__28_22;
static void cont__28_23(void);
static void cont__28_24(void);
static NODE *string__28_25;
static void cont__28_26(void);
static NODE *string__28_27;
static NODE *func__29_1_resolve_reference;
static void entry__29_1_resolve_reference(void);
static FRAME_INFO frame__29_1_resolve_reference = {1, {"reference"}};
static void cont__29_2(void);
static NODE *func__29_3;
static void entry__29_3(void);
static FRAME_INFO frame__29_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__29_4(void);
static void cont__29_5(void);
static void cont__29_6(void);
static NODE *func__29_7;
static void entry__29_7(void);
static FRAME_INFO frame__29_7 = {1, {"type_name"}};
static NODE *string__29_8;
static void cont__29_9(void);
static void cont__29_10(void);
static void cont__29_11(void);
static NODE *func__29_12;
static void entry__29_12(void);
static FRAME_INFO frame__29_12 = {1, {"method_name"}};
static NODE *string__29_13;
static void cont__29_14(void);
static void cont__29_15(void);
static void cont__29_16(void);
static NODE *func__29_17;
static void entry__29_17(void);
static FRAME_INFO frame__29_17 = {1, {"reference"}};
static void cont__29_18(void);
static NODE *func__29_19;
static void entry__29_19(void);
static FRAME_INFO frame__29_19 = {1, {"reference"}};
static void cont__29_20(void);
static void cont__29_21(void);
static NODE *func__32_1_to_paragraphs;
static void entry__32_1_to_paragraphs(void);
static FRAME_INFO frame__32_1_to_paragraphs = {4, {"lines", "paragraphs", "text", "pre_mode"}};
static NODE *func__32_2;
static void entry__32_2(void);
static FRAME_INFO frame__32_2 = {4, {"line", "pre_mode", "text", "paragraphs"}};
static NODE *func__32_3;
static void entry__32_3(void);
static FRAME_INFO frame__32_3 = {3, {"line", "text", "paragraphs"}};
static void cont__32_4(void);
static NODE *func__32_5;
static void entry__32_5(void);
static FRAME_INFO frame__32_5 = {3, {"text", "paragraphs", "line"}};
static void cont__32_6(void);
static void cont__32_7(void);
static NODE *func__32_8;
static void entry__32_8(void);
static FRAME_INFO frame__32_8 = {2, {"text", "line"}};
static void cont__32_9(void);
static NODE *func__32_10;
static void entry__32_10(void);
static FRAME_INFO frame__32_10 = {4, {"line", "text", "paragraphs", "pre_mode"}};
static void cont__32_11(void);
static NODE *func__32_12;
static void entry__32_12(void);
static FRAME_INFO frame__32_12 = {2, {"text", "paragraphs"}};
static void cont__32_13(void);
static void cont__32_14(void);
static NODE *func__32_15;
static void entry__32_15(void);
static FRAME_INFO frame__32_15 = {2, {"paragraphs", "text"}};
static void cont__32_16(void);
static NODE *func__32_17;
static void entry__32_17(void);
static FRAME_INFO frame__32_17 = {3, {"text", "line", "pre_mode"}};
static void cont__32_18(void);
static NODE *func__32_19;
static void entry__32_19(void);
static FRAME_INFO frame__32_19 = {2, {"line", "pre_mode"}};
static void cont__32_20(void);
static NODE *func__32_21;
static void entry__32_21(void);
static FRAME_INFO frame__32_21 = {1, {"pre_mode"}};
static NODE *func__32_22;
static void entry__32_22(void);
static FRAME_INFO frame__32_22 = {1, {"text"}};
static void cont__32_23(void);
static void cont__32_24(void);
static void cont__32_25(void);
static void cont__32_26(void);
static void cont__32_27(void);
static void cont__32_28(void);
static void cont__32_29(void);
static NODE *func__32_30;
static void entry__32_30(void);
static FRAME_INFO frame__32_30 = {2, {"paragraphs", "text"}};
static void cont__32_31(void);
static void cont__32_32(void);
static NODE *func__33_1_create_info_page;
static void entry__33_1_create_info_page(void);
static FRAME_INFO frame__33_1_create_info_page = {2, {"function_name", "info"}};
static void cont__33_2(void);
static NODE *func__33_3;
static void entry__33_3(void);
static FRAME_INFO frame__33_3 = {2, {"function_name", "info"}};
static void cont__33_4(void);
static NODE *string__33_5;
static NODE *string__33_6;
static void cont__33_7(void);
static NODE *func__33_8;
static void entry__33_8(void);
static FRAME_INFO frame__33_8 = {11, {"function_name", "info", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "examples", "remark_lines", "function_basename"}};
static void cont__33_9(void);
static void cont__33_10(void);
static NODE *func__33_11;
static void entry__33_11(void);
static FRAME_INFO frame__33_11 = {3, {"function_name", "type", "method"}};
static void cont__33_12(void);
static void cont__33_13(void);
static void cont__33_14(void);
static void cont__33_15(void);
static NODE *string__33_16;
static NODE *string__33_17;
static NODE *string__33_18;
static void cont__33_19(void);
static NODE *func__33_20;
static void entry__33_20(void);
static FRAME_INFO frame__33_20 = {1, {"function_name"}};
static void cont__33_21(void);
static void cont__33_22(void);
static NODE *func__33_23;
static void entry__33_23(void);
static FRAME_INFO frame__33_23 = {1, {"remark_lines"}};
static void cont__33_24(void);
static NODE *func__33_25;
static void entry__33_25(void);
static FRAME_INFO frame__33_25 = {1, {"remark_lines"}};
static void cont__33_26(void);
static void cont__33_27(void);
static void cont__33_28(void);
static NODE *func__33_29;
static void entry__33_29(void);
static FRAME_INFO frame__33_29 = {1, {"function_name"}};
static NODE *string__33_30;
static NODE *string__33_31;
static void cont__33_32(void);
static void cont__33_33(void);
static void cont__33_34(void);
static NODE *func__33_35;
static void entry__33_35(void);
static FRAME_INFO frame__33_35 = {10, {"remark_lines", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions", "paragraphs"}};
static void cont__33_36(void);
static NODE *func__33_37;
static void entry__33_37(void);
static FRAME_INFO frame__33_37 = {9, {"paragraph", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions"}};
static NODE *func__33_38;
static void entry__33_38(void);
static FRAME_INFO frame__33_38 = {2, {"paragraph", "parameters"}};
static void cont__33_39(void);
static NODE *string__33_40;
static void cont__33_41(void);
static void cont__33_42(void);
static NODE *func__33_43;
static void entry__33_43(void);
static FRAME_INFO frame__33_43 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__33_44(void);
static NODE *func__33_45;
static void entry__33_45(void);
static FRAME_INFO frame__33_45 = {1, {"parameter"}};
static void cont__33_46(void);
static NODE *func__33_47;
static void entry__33_47(void);
static FRAME_INFO frame__33_47 = {1, {"parameter"}};
static void cont__33_48(void);
static void cont__33_49(void);
static NODE *string__33_50;
static void cont__33_51(void);
static NODE *func__33_52;
static void entry__33_52(void);
static FRAME_INFO frame__33_52 = {1, {"parameter"}};
static void cont__33_53(void);
static NODE *func__33_54;
static void entry__33_54(void);
static FRAME_INFO frame__33_54 = {1, {"parameter"}};
static void cont__33_55(void);
static void cont__33_56(void);
static NODE *string__33_57;
static void cont__33_58(void);
static NODE *func__33_59;
static void entry__33_59(void);
static FRAME_INFO frame__33_59 = {1, {"parameter"}};
static void cont__33_60(void);
static NODE *func__33_61;
static void entry__33_61(void);
static FRAME_INFO frame__33_61 = {1, {"parameter"}};
static void cont__33_62(void);
static void cont__33_63(void);
static void cont__33_64(void);
static void cont__33_65(void);
static NODE *string__33_66;
static NODE *string__33_67;
static void cont__33_68(void);
static void cont__33_69(void);
static void cont__33_70(void);
static void cont__33_71(void);
static void cont__33_72(void);
static void cont__33_73(void);
static NODE *func__33_74;
static void entry__33_74(void);
static FRAME_INFO frame__33_74 = {2, {"paragraph", "return_values"}};
static void cont__33_75(void);
static NODE *string__33_76;
static void cont__33_77(void);
static void cont__33_78(void);
static NODE *func__33_79;
static void entry__33_79(void);
static FRAME_INFO frame__33_79 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__33_80(void);
static NODE *func__33_81;
static void entry__33_81(void);
static FRAME_INFO frame__33_81 = {1, {"return_value"}};
static void cont__33_82(void);
static NODE *func__33_83;
static void entry__33_83(void);
static FRAME_INFO frame__33_83 = {1, {"return_value"}};
static void cont__33_84(void);
static void cont__33_85(void);
static void cont__33_86(void);
static NODE *func__33_87;
static void entry__33_87(void);
static FRAME_INFO frame__33_87 = {1, {"return_value"}};
static void cont__33_88(void);
static NODE *func__33_89;
static void entry__33_89(void);
static FRAME_INFO frame__33_89 = {1, {"return_value"}};
static void cont__33_90(void);
static void cont__33_91(void);
static void cont__33_92(void);
static void cont__33_93(void);
static void cont__33_94(void);
static void cont__33_95(void);
static void cont__33_96(void);
static void cont__33_97(void);
static NODE *func__33_98;
static void entry__33_98(void);
static FRAME_INFO frame__33_98 = {2, {"paragraph", "references"}};
static NODE *string__33_99;
static void cont__33_100(void);
static NODE *func__33_101;
static void entry__33_101(void);
static FRAME_INFO frame__33_101 = {2, {"paragraph", "references"}};
static void cont__33_102(void);
static void cont__33_103(void);
static NODE *func__33_104;
static void entry__33_104(void);
static FRAME_INFO frame__33_104 = {2, {"reference", "references"}};
static void cont__33_105(void);
static void cont__33_106(void);
static NODE *func__33_107;
static void entry__33_107(void);
static FRAME_INFO frame__33_107 = {2, {"paragraph", "function_name"}};
static void cont__33_108(void);
static NODE *func__33_109;
static void entry__33_109(void);
static FRAME_INFO frame__33_109 = {2, {"paragraph", "function_name"}};
static void cont__33_110(void);
static void cont__33_111(void);
static NODE *func__33_112;
static void entry__33_112(void);
static FRAME_INFO frame__33_112 = {3, {"topic", "function_name", "topic_contents"}};
static void cont__33_113(void);
static void cont__33_114(void);
static void cont__33_115(void);
static void cont__33_116(void);
static void cont__33_117(void);
static NODE *func__33_118;
static void entry__33_118(void);
static FRAME_INFO frame__33_118 = {2, {"paragraph", "examples"}};
static void cont__33_119(void);
static NODE *func__33_120;
static void entry__33_120(void);
static FRAME_INFO frame__33_120 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__33_121(void);
static void cont__33_122(void);
static void cont__33_123(void);
static void cont__33_124(void);
static void cont__33_125(void);
static void cont__33_126(void);
static NODE *func__33_127;
static void entry__33_127(void);
static FRAME_INFO frame__33_127 = {2, {"paragraph", "technical_details"}};
static NODE *string__33_128;
static void cont__33_129(void);
static NODE *func__33_130;
static void entry__33_130(void);
static FRAME_INFO frame__33_130 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__33_131(void);
static void cont__33_132(void);
static void cont__33_133(void);
static NODE *func__33_134;
static void entry__33_134(void);
static FRAME_INFO frame__33_134 = {1, {"technical_details"}};
static NODE *func__33_135;
static void entry__33_135(void);
static FRAME_INFO frame__33_135 = {2, {"technical_details", "detail"}};
static void cont__33_136(void);
static NODE *func__33_137;
static void entry__33_137(void);
static FRAME_INFO frame__33_137 = {4, {"paragraph", "short_description", "technical_details", "descriptions"}};
static void cont__33_138(void);
static void cont__33_139(void);
static void cont__33_140(void);
static NODE *func__33_141;
static void entry__33_141(void);
static FRAME_INFO frame__33_141 = {1, {"reference"}};
static void cont__33_142(void);
static void cont__33_143(void);
static void cont__33_144(void);
static void cont__33_145(void);
static NODE *string__33_146;
static void cont__33_147(void);
static void cont__33_148(void);
static void cont__33_149(void);
static void cont__33_150(void);
static NODE *func__33_151;
static void entry__33_151(void);
static FRAME_INFO frame__33_151 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__33_152(void);
static NODE *func__33_153;
static void entry__33_153(void);
static FRAME_INFO frame__33_153 = {2, {"technical_details", "paragraph"}};
static void cont__33_154(void);
static NODE *func__33_155;
static void entry__33_155(void);
static FRAME_INFO frame__33_155 = {2, {"descriptions", "paragraph"}};
static void cont__33_156(void);
static NODE *func__33_157;
static void entry__33_157(void);
static FRAME_INFO frame__33_157 = {2, {"short_description", "paragraph"}};
static void cont__33_158(void);
static void cont__33_159(void);
static void cont__33_160(void);
static NODE *func__33_161;
static void entry__33_161(void);
static FRAME_INFO frame__33_161 = {2, {"info", "parameters"}};
static void cont__33_162(void);
static NODE *func__33_163;
static void entry__33_163(void);
static FRAME_INFO frame__33_163 = {2, {"parameter", "parameters"}};
static void cont__33_164(void);
static void cont__33_165(void);
static NODE *func__33_166;
static void entry__33_166(void);
static FRAME_INFO frame__33_166 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__33_167(void);
static void cont__33_168(void);
static void cont__33_169(void);
static NODE *func__33_170;
static void entry__33_170(void);
static FRAME_INFO frame__33_170 = {2, {"parameter", "name"}};
static void cont__33_171(void);
static NODE *func__33_172;
static void entry__33_172(void);
static FRAME_INFO frame__33_172 = {2, {"parameter", "name"}};
static void cont__33_173(void);
static void cont__33_174(void);
static NODE *func__33_175;
static void entry__33_175(void);
static FRAME_INFO frame__33_175 = {2, {"name", "parameter"}};
static void cont__33_176(void);
static void cont__33_177(void);
static void cont__33_178(void);
static NODE *func__33_179;
static void entry__33_179(void);
static FRAME_INFO frame__33_179 = {1, {"name"}};
static void cont__33_180(void);
static NODE *func__33_181;
static void entry__33_181(void);
static FRAME_INFO frame__33_181 = {2, {"parameter", "name"}};
static void cont__33_182(void);
static NODE *func__33_183;
static void entry__33_183(void);
static FRAME_INFO frame__33_183 = {1, {"name"}};
static void cont__33_184(void);
static void cont__33_185(void);
static void cont__33_186(void);
static void cont__33_187(void);
static void cont__33_188(void);
static NODE *func__33_189;
static void entry__33_189(void);
static FRAME_INFO frame__33_189 = {1, {"parameter"}};
static void cont__33_190(void);
static void cont__33_191(void);
static void cont__33_192(void);
static NODE *func__33_193;
static void entry__33_193(void);
static FRAME_INFO frame__33_193 = {0, {}};
static void cont__33_194(void);
static void cont__33_195(void);
static void cont__33_196(void);
static NODE *func__33_197;
static void entry__33_197(void);
static FRAME_INFO frame__33_197 = {0, {}};
static void cont__33_198(void);
static void cont__33_199(void);
static NODE *func__33_200;
static void entry__33_200(void);
static FRAME_INFO frame__33_200 = {1, {"short_description"}};
static void cont__33_201(void);
static void cont__33_202(void);
static NODE *func__33_203;
static void entry__33_203(void);
static FRAME_INFO frame__33_203 = {1, {"parameters"}};
static NODE *string__33_204;
static void cont__33_205(void);
static NODE *func__33_206;
static void entry__33_206(void);
static FRAME_INFO frame__33_206 = {1, {"parameters"}};
static NODE *func__33_207;
static void entry__33_207(void);
static FRAME_INFO frame__33_207 = {1, {"parameter"}};
static void cont__33_208(void);
static void cont__33_209(void);
static NODE *func__33_210;
static void entry__33_210(void);
static FRAME_INFO frame__33_210 = {1, {"parameter"}};
static void cont__33_211(void);
static void cont__33_212(void);
static void cont__33_213(void);
static NODE *func__33_214;
static void entry__33_214(void);
static FRAME_INFO frame__33_214 = {1, {"return_values"}};
static void cont__33_215(void);
static NODE *func__33_216;
static void entry__33_216(void);
static FRAME_INFO frame__33_216 = {1, {"return_values"}};
static NODE *func__33_217;
static void entry__33_217(void);
static FRAME_INFO frame__33_217 = {1, {"return_value"}};
static void cont__33_218(void);
static void cont__33_219(void);
static NODE *func__33_220;
static void entry__33_220(void);
static FRAME_INFO frame__33_220 = {1, {"return_value"}};
static void cont__33_221(void);
static void cont__33_222(void);
static void cont__33_223(void);
static NODE *func__33_224;
static void entry__33_224(void);
static FRAME_INFO frame__33_224 = {1, {"descriptions"}};
static NODE *string__33_225;
static void cont__33_226(void);
static NODE *func__33_227;
static void entry__33_227(void);
static FRAME_INFO frame__33_227 = {1, {"description"}};
static void cont__33_228(void);
static void cont__33_229(void);
static NODE *func__33_230;
static void entry__33_230(void);
static FRAME_INFO frame__33_230 = {1, {"technical_details"}};
static NODE *string__33_231;
static void cont__33_232(void);
static NODE *func__33_233;
static void entry__33_233(void);
static FRAME_INFO frame__33_233 = {1, {"detail"}};
static void cont__33_234(void);
static void cont__33_235(void);
static NODE *func__33_236;
static void entry__33_236(void);
static FRAME_INFO frame__33_236 = {1, {"references"}};
static NODE *string__33_237;
static void cont__33_238(void);
static NODE *func__33_239;
static void entry__33_239(void);
static FRAME_INFO frame__33_239 = {1, {"references"}};
static NODE *func__33_240;
static void entry__33_240(void);
static FRAME_INFO frame__33_240 = {1, {"reference"}};
static void cont__33_241(void);
static void cont__33_242(void);
static void cont__33_243(void);
static void cont__33_244(void);
static void cont__33_245(void);
static void cont__33_246(void);
static void cont__33_247(void);
static void cont__33_248(void);
static NODE *func__33_249;
static void entry__33_249(void);
static FRAME_INFO frame__33_249 = {2, {"info", "function_name"}};
static NODE *string__33_250;
static void cont__33_251(void);
static NODE *func__33_252;
static void entry__33_252(void);
static FRAME_INFO frame__33_252 = {2, {"info", "function_name"}};
static void cont__33_253(void);
static NODE *func__33_254;
static void entry__33_254(void);
static FRAME_INFO frame__33_254 = {3, {"name", "function_name", "method"}};
static void cont__33_255(void);
static NODE *func__33_256;
static void entry__33_256(void);
static FRAME_INFO frame__33_256 = {2, {"name", "method"}};
static NODE *func__33_257;
static void entry__33_257(void);
static FRAME_INFO frame__33_257 = {1, {"name"}};
static void cont__33_258(void);
static void cont__33_259(void);
static void cont__33_260(void);
static void cont__33_261(void);
static NODE *string__33_262;
static void cont__33_263(void);
static NODE *func__33_264;
static void entry__33_264(void);
static FRAME_INFO frame__33_264 = {1, {"method"}};
static void cont__33_265(void);
static void cont__33_266(void);
static void cont__33_267(void);
static void cont__33_268(void);
static void cont__33_269(void);
static void cont__33_270(void);
static NODE *func__33_271;
static void entry__33_271(void);
static FRAME_INFO frame__33_271 = {2, {"info", "function_name"}};
static NODE *string__33_272;
static void cont__33_273(void);
static NODE *func__33_274;
static void entry__33_274(void);
static FRAME_INFO frame__33_274 = {2, {"info", "function_name"}};
static void cont__33_275(void);
static NODE *func__33_276;
static void entry__33_276(void);
static FRAME_INFO frame__33_276 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__33_277;
static void entry__33_277(void);
static FRAME_INFO frame__33_277 = {2, {"method_name", "function_name"}};
static NODE *func__33_278;
static void entry__33_278(void);
static FRAME_INFO frame__33_278 = {1, {"method_name"}};
static void cont__33_279(void);
static void cont__33_280(void);
static void cont__33_281(void);
static void cont__33_282(void);
static NODE *string__33_283;
static void cont__33_284(void);
static NODE *func__33_285;
static void entry__33_285(void);
static FRAME_INFO frame__33_285 = {2, {"function_name", "method_name"}};
static void cont__33_286(void);
static void cont__33_287(void);
static void cont__33_288(void);
static void cont__33_289(void);
static void cont__33_290(void);
static void cont__33_291(void);
static void cont__33_292(void);
static NODE *func__33_293;
static void entry__33_293(void);
static FRAME_INFO frame__33_293 = {4, {"example", "function_basename", "title", "text"}};
static void cont__33_294(void);
static void cont__33_295(void);
static void cont__33_296(void);
static void cont__33_297(void);
static void cont__33_298(void);
static NODE *string__33_299;
static void cont__33_300(void);
static NODE *func__33_301;
static void entry__33_301(void);
static FRAME_INFO frame__33_301 = {2, {"text", "function_basename"}};
static void cont__33_302(void);
static void cont__33_303(void);
static void cont__33_304(void);
static void cont__33_305(void);
static NODE *func__33_306;
static void entry__33_306(void);
static FRAME_INFO frame__33_306 = {1, {"string_literal"}};
static void cont__33_307(void);
static NODE *string__33_308;
static void cont__33_309(void);
static void cont__33_310(void);
static void cont__33_311(void);
static void cont__33_312(void);
static NODE *string__33_313;
static void cont__33_314(void);
static void cont__33_315(void);
static void cont__33_316(void);
static NODE *string__33_317;
static NODE *string__33_318;
static void cont__33_319(void);
static NODE *func__34_1_sim2c__extract_documentation;
static void entry__34_1_sim2c__extract_documentation(void);
static FRAME_INFO frame__34_1_sim2c__extract_documentation = {2, {"path", "return__1"}};
static NODE *func__34_2_html__encode;
static void entry__34_2_html__encode(void);
static FRAME_INFO frame__34_2_html__encode = {3, {"text", "tag", "arg_str"}};
static NODE *string__34_3;
static void cont__34_4(void);
static NODE *func__34_5;
static void entry__34_5(void);
static FRAME_INFO frame__34_5 = {1, {"text"}};
static NODE *string__34_6;
static void cont__34_7(void);
static NODE *func__34_8;
static void entry__34_8(void);
static FRAME_INFO frame__34_8 = {2, {"capture", "reference"}};
static void cont__34_9(void);
static void cont__34_10(void);
static void cont__34_11(void);
static void cont__34_12(void);
static NODE *string__34_13;
static NODE *string__34_14;
static NODE *string__34_15;
static void cont__34_16(void);
static void cont__34_17(void);
static void cont__34_18(void);
static void cont__34_19(void);
static void cont__34_20(void);
static void cont__34_21(void);
static void cont__34_22(void);
static NODE *func__34_23;
static void entry__34_23(void);
static FRAME_INFO frame__34_23 = {2, {"name", "info"}};
static void cont__34_24(void);
static void cont__34_25(void);
static NODE *func__34_26;
static void entry__34_26(void);
static FRAME_INFO frame__34_26 = {4, {"info", "name", "base", "methods"}};
static void cont__34_27(void);
static void cont__34_28(void);
static NODE *func__34_29;
static void entry__34_29(void);
static FRAME_INFO frame__34_29 = {2, {"base", "name"}};
static void cont__34_30(void);
static void cont__34_31(void);
static NODE *func__34_32;
static void entry__34_32(void);
static FRAME_INFO frame__34_32 = {4, {"method_name", "method_info", "info", "methods"}};
static void cont__34_33(void);
static NODE *func__34_34;
static void entry__34_34(void);
static FRAME_INFO frame__34_34 = {2, {"method_name", "method_info"}};
static void cont__34_35(void);
static void cont__34_36(void);
static void cont__34_37(void);
static void cont__34_38(void);
static void cont__34_39(void);
static NODE *func__34_40;
static void entry__34_40(void);
static FRAME_INFO frame__34_40 = {3, {"method_name", "info", "oname"}};
static void cont__34_41(void);
static void cont__34_42(void);
static void cont__34_43(void);
static void cont__34_44(void);
static void cont__34_45(void);
static void cont__34_46(void);
static void cont__34_47(void);
static void cont__34_48(void);
static void cont__34_49(void);
static void cont__34_50(void);
static void cont__34_51(void);
static void cont__34_52(void);
static void cont__34_53(void);
static void cont__34_54(void);
static NODE *string__34_55;
static NODE *func__34_56;
static void entry__34_56(void);
static FRAME_INFO frame__34_56 = {1, {"print_type_info"}};
static NODE *func__34_57_print_type_info;
static void entry__34_57_print_type_info(void);
static FRAME_INFO frame__34_57_print_type_info = {3, {"info", "indent", "print_type_info"}};
static NODE *func__34_58;
static void entry__34_58(void);
static FRAME_INFO frame__34_58 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__34_59(void);
static void cont__34_60(void);
static void cont__34_61(void);
static NODE *func__34_62;
static void entry__34_62(void);
static FRAME_INFO frame__34_62 = {2, {"indent", "qname"}};
static NODE *func__34_63;
static void entry__34_63(void);
static FRAME_INFO frame__34_63 = {2, {"indent", "qname"}};
static void cont__34_64(void);
static void cont__34_65(void);
static void cont__34_66(void);
static void cont__34_67(void);
static void cont__34_68(void);
static void cont__34_69(void);
static void cont__34_70(void);
static NODE *func__34_71;
static void entry__34_71(void);
static FRAME_INFO frame__34_71 = {1, {"remark_lines"}};
static void cont__34_72(void);
static void cont__34_73(void);
static void cont__34_74(void);
static NODE *func__34_75;
static void entry__34_75(void);
static FRAME_INFO frame__34_75 = {1, {"remark_lines"}};
static void cont__34_76(void);
static void cont__34_77(void);
static void cont__34_78(void);
static void cont__34_79(void);
static NODE *func__34_80;
static void entry__34_80(void);
static FRAME_INFO frame__34_80 = {3, {"name", "print_type_info", "indent"}};
static void cont__34_81(void);
static void cont__34_82(void);
static void cont__34_83(void);
static void cont__34_84(void);
static NODE *func__34_85;
static void entry__34_85(void);
static FRAME_INFO frame__34_85 = {1, {"print_type_info"}};
static NODE *func__34_86;
static void entry__34_86(void);
static FRAME_INFO frame__34_86 = {3, {"base", "info", "print_type_info"}};
static void cont__34_87(void);
static void cont__34_88(void);
static NODE *func__34_89;
static void entry__34_89(void);
static FRAME_INFO frame__34_89 = {1, {"info"}};
static void cont__34_90(void);
static void cont__34_91(void);
static void cont__34_92(void);
static NODE *func__34_93;
static void entry__34_93(void);
static FRAME_INFO frame__34_93 = {2, {"print_type_info", "info"}};
static void cont__34_94(void);
static NODE *string__34_95;
static NODE *func__34_96;
static void entry__34_96(void);
static FRAME_INFO frame__34_96 = {0, {}};
static void cont__34_97(void);
static NODE *string__34_98;
static NODE *string__34_99;
static void cont__34_100(void);
static void cont__34_101(void);
static NODE *func__34_102;
static void entry__34_102(void);
static FRAME_INFO frame__34_102 = {1, {"letter"}};
static NODE *string__34_103;
static void cont__34_104(void);
static void cont__34_105(void);
static void cont__34_106(void);
static NODE *func__34_107;
static void entry__34_107(void);
static FRAME_INFO frame__34_107 = {0, {}};
static NODE *string__34_108;
static void cont__34_109(void);
static void cont__34_110(void);
static NODE *func__34_111;
static void entry__34_111(void);
static FRAME_INFO frame__34_111 = {1, {"letter"}};
static NODE *func__34_112;
static void entry__34_112(void);
static FRAME_INFO frame__34_112 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__34_113(void);
static void cont__34_114(void);
static void cont__34_115(void);
static NODE *func__34_116;
static void entry__34_116(void);
static FRAME_INFO frame__34_116 = {2, {"letter", "iname"}};
static void cont__34_117(void);
static NODE *func__34_118;
static void entry__34_118(void);
static FRAME_INFO frame__34_118 = {1, {"letter"}};
static NODE *string__34_119;
static void cont__34_120(void);
static NODE *func__34_121;
static void entry__34_121(void);
static FRAME_INFO frame__34_121 = {1, {"letter"}};
static void cont__34_122(void);
static NODE *func__34_123;
static void entry__34_123(void);
static FRAME_INFO frame__34_123 = {1, {"letter"}};
static void cont__34_124(void);
static void cont__34_125(void);
static NODE *string__34_126;
static void cont__34_127(void);
static NODE *string__34_128;
static void cont__34_129(void);
static void cont__34_130(void);
static void cont__34_131(void);
static void cont__34_132(void);
static NODE *func__34_133;
static void entry__34_133(void);
static FRAME_INFO frame__34_133 = {1, {"remark_lines"}};
static void cont__34_134(void);
static void cont__34_135(void);
static void cont__34_136(void);
static NODE *func__34_137;
static void entry__34_137(void);
static FRAME_INFO frame__34_137 = {2, {"remark", "remark_lines"}};
static void cont__34_138(void);
static void cont__34_139(void);
static void cont__34_140(void);
static void cont__34_141(void);
static NODE *func__34_142;
static void entry__34_142(void);
static FRAME_INFO frame__34_142 = {0, {}};
static NODE *string__34_143;
static NODE *func__34_144;
static void entry__34_144(void);
static FRAME_INFO frame__34_144 = {0, {}};
static NODE *string__34_145;
static NODE *func__34_146;
static void entry__34_146(void);
static FRAME_INFO frame__34_146 = {0, {}};
static NODE *string__34_147;
static NODE *func__34_148;
static void entry__34_148(void);
static FRAME_INFO frame__34_148 = {0, {}};
static NODE *string__34_149;
static NODE *func__34_150;
static void entry__34_150(void);
static FRAME_INFO frame__34_150 = {0, {}};
static NODE *string__34_151;
static NODE *func__34_152;
static void entry__34_152(void);
static FRAME_INFO frame__34_152 = {0, {}};
static NODE *func__34_153;
static void entry__34_153(void);
static FRAME_INFO frame__34_153 = {0, {}};
static void cont__34_154(void);
static void cont__34_155(void);
static NODE *func__34_156;
static void entry__34_156(void);
static FRAME_INFO frame__34_156 = {2, {"remark", "kind_info"}};
static void cont__34_157(void);
static NODE *func__34_158;
static void entry__34_158(void);
static FRAME_INFO frame__34_158 = {2, {"remark", "kind_info"}};
static NODE *string__34_159;
static void cont__34_160(void);
static NODE *func__34_161;
static void entry__34_161(void);
static FRAME_INFO frame__34_161 = {2, {"remark", "kind_info"}};
static void cont__34_162(void);
static void cont__34_163(void);
static NODE *func__34_164;
static void entry__34_164(void);
static FRAME_INFO frame__34_164 = {1, {"name"}};
static void cont__34_165(void);
static void cont__34_166(void);
static NODE *func__34_167;
static void entry__34_167(void);
static FRAME_INFO frame__34_167 = {2, {"name", "remark"}};
static NODE *func__34_168;
static void entry__34_168(void);
static FRAME_INFO frame__34_168 = {2, {"name", "remark"}};
static NODE *string__34_169;
static NODE *string__34_170;
static void cont__34_171(void);
static void cont__34_172(void);
static void cont__34_173(void);
static NODE *func__34_174;
static void entry__34_174(void);
static FRAME_INFO frame__34_174 = {1, {"name"}};
static void cont__34_175(void);
static void cont__34_176(void);
static void cont__34_177(void);
static void cont__34_178(void);
static void cont__34_179(void);
static NODE *string__34_180;
static void cont__34_181(void);
static void cont__34_182(void);
static NODE *func__34_183;
static void entry__34_183(void);
static FRAME_INFO frame__34_183 = {3, {"iname", "info", "name"}};
static void cont__34_184(void);
static void cont__34_185(void);
static void cont__34_186(void);
static NODE *func__34_187;
static void entry__34_187(void);
static FRAME_INFO frame__34_187 = {2, {"info", "name"}};
static void cont__34_188(void);
static NODE *func__34_189;
static void entry__34_189(void);
static FRAME_INFO frame__34_189 = {3, {"method_name", "method_info", "name"}};
static NODE *string__34_190;
static void cont__34_191(void);
static void cont__34_192(void);
static NODE *string__34_193;
static NODE *func__34_194;
static void entry__34_194(void);
static FRAME_INFO frame__34_194 = {0, {}};
static void cont__34_195(void);
static void cont__34_196(void);
static void cont__34_197(void);
static NODE *func__34_198;
static void entry__34_198(void);
static FRAME_INFO frame__34_198 = {0, {}};
static NODE *func__34_199;
static void entry__34_199(void);
static FRAME_INFO frame__34_199 = {3, {"topic", "references", "filename"}};
static void cont__34_200(void);
static NODE *string__34_201;
static void cont__34_202(void);
static void cont__34_203(void);
static void cont__34_204(void);
static NODE *func__34_205;
static void entry__34_205(void);
static FRAME_INFO frame__34_205 = {2, {"filename", "topic"}};
static NODE *func__34_206;
static void entry__34_206(void);
static FRAME_INFO frame__34_206 = {2, {"filename", "topic"}};
static void cont__34_207(void);
static void cont__34_208(void);
static NODE *func__34_209;
static void entry__34_209(void);
static FRAME_INFO frame__34_209 = {3, {"topic", "references", "filename"}};
static void cont__34_210(void);
static void cont__34_211(void);
static void cont__34_212(void);
static void cont__34_213(void);
static NODE *func__34_214;
static void entry__34_214(void);
static FRAME_INFO frame__34_214 = {2, {"topic", "references"}};
static void cont__34_215(void);
static void cont__34_216(void);
static void cont__34_217(void);
static NODE *func__34_218;
static void entry__34_218(void);
static FRAME_INFO frame__34_218 = {1, {"references"}};
static NODE *func__34_219;
static void entry__34_219(void);
static FRAME_INFO frame__34_219 = {1, {"reference"}};
static NODE *func__34_220;
static void entry__34_220(void);
static FRAME_INFO frame__34_220 = {1, {"reference"}};
static NODE *func__34_221;
static void entry__34_221(void);
static FRAME_INFO frame__34_221 = {1, {"reference"}};
static void cont__34_222(void);
static void cont__34_223(void);
static void cont__34_224(void);
static void cont__34_225(void);
static NODE *string__34_226;
static NODE *func__34_227;
static void entry__34_227(void);
static FRAME_INFO frame__34_227 = {0, {}};
static NODE *string__34_228;
static void cont__34_229(void);
static NODE *func__34_230;
static void entry__34_230(void);
static FRAME_INFO frame__34_230 = {0, {}};
static void cont__34_231(void);
static void cont__34_232(void);
static NODE *func__34_233;
static void entry__34_233(void);
static FRAME_INFO frame__34_233 = {0, {}};
static void cont__34_234(void);
static void cont__34_235(void);
static NODE *func__34_236;
static void entry__34_236(void);
static FRAME_INFO frame__34_236 = {0, {}};
static void cont__34_237(void);
static void cont__34_238(void);
static NODE *func__34_239;
static void entry__34_239(void);
static FRAME_INFO frame__34_239 = {0, {}};
static void cont__34_240(void);
static void cont__34_241(void);
static NODE *func__34_242;
static void entry__34_242(void);
static FRAME_INFO frame__34_242 = {13, {"total_types", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_methods", "total_inline_c_methods", "total_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "total_variables", "other", "total_definitions"}};
static NODE *func__34_243;
static void entry__34_243(void);
static FRAME_INFO frame__34_243 = {14, {"iname", "info", "total_types", "total_functions", "total_polymorphic_functions", "total_polymorphic_attributes", "total_inline_c_functions", "total_unique_items", "total_constants", "total_variables", "other", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__34_244(void);
static NODE *func__34_245;
static void entry__34_245(void);
static FRAME_INFO frame__34_245 = {1, {"total_types"}};
static void cont__34_246(void);
static NODE *func__34_247;
static void entry__34_247(void);
static FRAME_INFO frame__34_247 = {1, {"total_functions"}};
static void cont__34_248(void);
static NODE *func__34_249;
static void entry__34_249(void);
static FRAME_INFO frame__34_249 = {1, {"total_polymorphic_functions"}};
static void cont__34_250(void);
static NODE *func__34_251;
static void entry__34_251(void);
static FRAME_INFO frame__34_251 = {1, {"total_polymorphic_attributes"}};
static void cont__34_252(void);
static NODE *func__34_253;
static void entry__34_253(void);
static FRAME_INFO frame__34_253 = {1, {"total_inline_c_functions"}};
static void cont__34_254(void);
static NODE *func__34_255;
static void entry__34_255(void);
static FRAME_INFO frame__34_255 = {1, {"total_unique_items"}};
static void cont__34_256(void);
static NODE *func__34_257;
static void entry__34_257(void);
static FRAME_INFO frame__34_257 = {1, {"total_constants"}};
static void cont__34_258(void);
static NODE *func__34_259;
static void entry__34_259(void);
static FRAME_INFO frame__34_259 = {1, {"total_variables"}};
static void cont__34_260(void);
static NODE *func__34_261;
static void entry__34_261(void);
static FRAME_INFO frame__34_261 = {1, {"other"}};
static void cont__34_262(void);
static void cont__34_263(void);
static void cont__34_264(void);
static NODE *func__34_265;
static void entry__34_265(void);
static FRAME_INFO frame__34_265 = {4, {"info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__34_266(void);
static NODE *func__34_267;
static void entry__34_267(void);
static FRAME_INFO frame__34_267 = {5, {"method_name", "method_info", "total_methods", "total_inline_c_methods", "total_attributes"}};
static void cont__34_268(void);
static NODE *func__34_269;
static void entry__34_269(void);
static FRAME_INFO frame__34_269 = {1, {"total_methods"}};
static void cont__34_270(void);
static NODE *func__34_271;
static void entry__34_271(void);
static FRAME_INFO frame__34_271 = {1, {"total_inline_c_methods"}};
static void cont__34_272(void);
static NODE *func__34_273;
static void entry__34_273(void);
static FRAME_INFO frame__34_273 = {1, {"total_attributes"}};
static void cont__34_274(void);
static void cont__34_275(void);
static void cont__34_276(void);
static void cont__34_277(void);
static void cont__34_278(void);
static void cont__34_279(void);
static void cont__34_280(void);
static void cont__34_281(void);
static void cont__34_282(void);
static void cont__34_283(void);
static void cont__34_284(void);
static void cont__34_285(void);
static void cont__34_286(void);
static void cont__34_287(void);
static void cont__34_288(void);
static void cont__34_289(void);
static void cont__34_290(void);
static void cont__34_291(void);
static void cont__34_292(void);
static void cont__34_293(void);
static void cont__34_294(void);
static void cont__34_295(void);
static void cont__34_296(void);
static void cont__34_297(void);
static void cont__34_298(void);
static NODE *string__34_299;
static NODE *string__34_300;
static NODE *string__34_301;
static NODE *string__34_302;
static NODE *string__34_303;
static NODE *string__34_304;
static NODE *string__34_305;
static NODE *string__34_306;
static NODE *string__34_307;
static NODE *string__34_308;
static NODE *string__34_309;
static NODE *string__34_310;
static NODE *string__34_311;
static void cont__34_312(void);
static void cont__34_313(void);
static NODE *get__sim2c__extract_documentation(void) {
  return var.sim2c__extract_documentation;
}
static void cont__40_1(void);
static void cont__52_1(void);
static void cont__52_2(void);
static void cont__52_3(void);
static void cont__52_4(void);
static void cont__52_5(void);
static void cont__52_6(void);
static void cont__52_7(void);
static NODE *string__64_1;
static NODE *string__64_2;
static void cont__64_3(void);
static void cont__64_4(void);
static NODE *string__65_1;
static NODE *string__65_2;
static void cont__65_3(void);
static void cont__65_4(void);
static void cont__65_5(void);
static void cont__65_6(void);
static void cont__65_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__40_1, NULL, 57, 57, 15, 55},
  {cont__52_1, NULL, 57, 57, 7, 56},
  {cont__52_2, NULL, 58, 58, 12, 31},
  {cont__52_3, NULL, 58, 58, 12, 46},
  {cont__52_4, NULL, 58, 58, 7, 47},
  {cont__52_5, NULL, 56, 58, 5, 46},
  {cont__52_6, NULL, 52, 58, 1, 49},
  {cont__52_7, NULL, 369, 369, 8, 28},
  {cont__64_3, NULL, 369, 369, 1, 33},
  {cont__64_4, NULL, 370, 370, 10, 32},
  {cont__65_3, NULL, 370, 370, 40, 59},
  {cont__65_4, NULL, 370, 370, 40, 74},
  {cont__65_5, NULL, 370, 370, 35, 75},
  {cont__65_6, NULL, 370, 370, 1, 80},
  {cont__65_7, NULL, },
  {entry__20_4, NULL, 68, 146, 9, 11},
  {entry__20_3, NULL, 67, 146, 7, 12},
  {cont__20_6, &frame__20_3, 147, 147, 7, 15},
  {entry__20_2, NULL, 66, 147, 5, 15},
  {entry__20_1_create_page, NULL, 65, 147, 3, 16},
  {cont__20_7, &frame__20_1_create_page, 148, 148, 3, 20},
  {entry__22_10, NULL, 163, 163, 27, 52},
  {entry__22_16, NULL, 164, 164, 21, 63},
  {entry__22_23, NULL, 165, 165, 26, 71},
  {entry__22_32, NULL, 179, 179, 39, 56},
  {cont__22_33, &frame__22_32, 179, 179, 56, 56},
  {entry__22_39, NULL, 187, 187, 11, 42},
  {cont__22_40, &frame__22_39, 187, 187, 42, 42},
  {entry__22_41, NULL, 189, 189, 11, 26},
  {cont__22_42, &frame__22_41, 190, 190, 11, 48},
  {cont__22_43, &frame__22_41, 190, 190, 48, 48},
  {entry__22_44, NULL, 192, 192, 11, 14},
  {entry__22_36, NULL, 185, 185, 9, 27},
  {cont__22_37, &frame__22_36, 185, 185, 9, 30},
  {cont__22_38, &frame__22_36, 184, 192, 7, 15},
  {entry__22_35, NULL, 183, 192, 5, 16},
  {cont__22_45, &frame__22_35, 192, 192, 16, 16},
  {entry__22_49, NULL, 194, 194, 46, 70},
  {cont__22_50, &frame__22_49, 194, 194, 34, 70},
  {cont__22_51, &frame__22_49, 194, 194, 70, 70},
  {entry__22_54, NULL, 195, 195, 32, 54},
  {cont__22_56, &frame__22_54, 195, 195, 59, 59},
  {entry__22_61, NULL, 198, 198, 37, 40},
  {entry__22_59, NULL, 198, 198, 14, 34},
  {cont__22_60, &frame__22_59, 198, 198, 11, 40},
  {entry__22_64, NULL, 198, 198, 68, 71},
  {entry__22_62, NULL, 198, 198, 47, 65},
  {cont__22_63, &frame__22_62, 198, 198, 44, 71},
  {entry__22_79, NULL, 205, 205, 41, 66},
  {cont__22_80, &frame__22_79, 205, 205, 33, 67},
  {cont__22_81, &frame__22_79, 205, 205, 13, 68},
  {cont__22_82, &frame__22_79, 205, 205, 73, 73},
  {entry__22_75, NULL, 203, 203, 19, 41},
  {cont__22_76, &frame__22_75, 203, 203, 11, 44},
  {cont__22_77, &frame__22_75, 204, 204, 14, 54},
  {cont__22_78, &frame__22_75, 204, 205, 11, 73},
  {entry__22_71, NULL, 201, 201, 9, 46},
  {cont__22_72, &frame__22_71, 202, 202, 16, 39},
  {cont__22_73, &frame__22_71, 202, 202, 16, 50},
  {cont__22_74, &frame__22_71, 202, 205, 9, 74},
  {entry__22_67, NULL, 199, 199, 20, 49},
  {cont__22_68, &frame__22_67, 199, 199, 7, 52},
  {cont__22_69, &frame__22_67, 200, 200, 10, 36},
  {cont__22_70, &frame__22_67, 200, 205, 7, 75},
  {entry__22_65, NULL, 198, 198, 77, 102},
  {cont__22_66, &frame__22_65, 198, 205, 74, 76},
  {entry__22_58, NULL, 198, 205, 5, 76},
  {entry__22_87, NULL, 212, 212, 33, 36},
  {entry__22_85, NULL, 212, 212, 10, 30},
  {cont__22_86, &frame__22_85, 212, 212, 7, 36},
  {entry__22_103, NULL, 224, 224, 49, 62},
  {cont__22_104, &frame__22_103, 224, 224, 46, 62},
  {entry__22_105, NULL, 224, 224, 65, 76},
  {entry__22_98, NULL, 218, 218, 13, 37},
  {cont__22_99, &frame__22_98, 219, 219, 13, 36},
  {cont__22_100, &frame__22_98, 223, 223, 26, 45},
  {cont__22_101, &frame__22_98, 224, 224, 29, 43},
  {cont__22_102, &frame__22_98, 224, 224, 26, 77},
  {cont__22_106, &frame__22_98, 225, 225, 34, 59},
  {cont__22_107, &frame__22_98, 220, 220, 26, 53},
  {cont__22_108, &frame__22_98, 220, 220, 13, 54},
  {cont__22_109, &frame__22_98, 226, 226, 39, 39},
  {entry__22_94, NULL, 215, 215, 11, 46},
  {cont__22_95, &frame__22_94, 216, 216, 11, 45},
  {cont__22_96, &frame__22_94, 217, 217, 14, 33},
  {cont__22_97, &frame__22_94, 217, 226, 11, 39},
  {entry__22_90, NULL, 214, 214, 12, 29},
  {cont__22_91, &frame__22_90, 214, 214, 12, 39},
  {cont__22_93, &frame__22_90, 214, 226, 9, 40},
  {entry__22_88, NULL, 213, 213, 10, 28},
  {cont__22_89, &frame__22_88, 213, 226, 7, 41},
  {entry__22_131, NULL, 246, 246, 25, 48},
  {entry__22_132, NULL, 247, 247, 25, 47},
  {entry__22_128, NULL, 240, 240, 17, 54},
  {cont__22_129, &frame__22_128, 245, 245, 25, 42},
  {cont__22_130, &frame__22_128, 244, 247, 23, 46},
  {cont__22_133, &frame__22_128, 248, 248, 38, 63},
  {cont__22_134, &frame__22_128, 241, 241, 17, 35},
  {cont__22_135, &frame__22_128, 249, 249, 17, 21},
  {entry__22_126, NULL, 239, 239, 18, 58},
  {cont__22_127, &frame__22_126, 239, 249, 15, 21},
  {entry__22_138, NULL, 253, 253, 17, 57},
  {cont__22_140, &frame__22_138, 254, 254, 17, 61},
  {cont__22_141, &frame__22_138, 254, 254, 61, 61},
  {entry__22_136, NULL, 250, 250, 18, 33},
  {cont__22_137, &frame__22_136, 250, 254, 15, 61},
  {entry__22_144, NULL, 257, 257, 17, 64},
  {cont__22_145, &frame__22_144, 257, 257, 64, 64},
  {entry__22_142, NULL, 255, 255, 18, 35},
  {cont__22_143, &frame__22_142, 255, 257, 15, 64},
  {entry__22_151, NULL, 261, 261, 30, 45},
  {cont__22_152, &frame__22_151, 262, 262, 38, 63},
  {cont__22_153, &frame__22_151, 262, 262, 64, 64},
  {entry__22_148, NULL, 259, 259, 20, 39},
  {cont__22_149, &frame__22_148, 259, 259, 20, 50},
  {cont__22_150, &frame__22_148, 259, 262, 17, 64},
  {entry__22_146, NULL, 258, 258, 18, 40},
  {cont__22_147, &frame__22_146, 258, 262, 15, 65},
  {entry__22_158, NULL, 269, 269, 25, 38},
  {entry__22_159, NULL, 270, 270, 25, 35},
  {entry__22_156, NULL, 268, 268, 25, 56},
  {cont__22_157, &frame__22_156, 267, 270, 23, 34},
  {cont__22_160, &frame__22_156, 271, 271, 38, 63},
  {cont__22_161, &frame__22_156, 264, 264, 17, 35},
  {cont__22_162, &frame__22_156, 272, 272, 17, 21},
  {entry__22_154, NULL, 263, 263, 18, 37},
  {cont__22_155, &frame__22_154, 263, 272, 15, 21},
  {entry__22_171, NULL, 279, 279, 21, 64},
  {cont__22_172, &frame__22_171, 280, 280, 21, 80},
  {cont__22_173, &frame__22_171, 281, 281, 21, 68},
  {cont__22_174, &frame__22_171, 281, 281, 68, 68},
  {entry__22_168, NULL, 278, 278, 22, 49},
  {cont__22_169, &frame__22_168, 278, 278, 22, 57},
  {cont__22_170, &frame__22_168, 278, 281, 19, 68},
  {entry__22_165, NULL, 276, 276, 17, 55},
  {cont__22_166, &frame__22_165, 277, 277, 20, 49},
  {cont__22_167, &frame__22_165, 277, 281, 17, 69},
  {cont__22_175, &frame__22_165, 282, 282, 17, 35},
  {cont__22_176, &frame__22_165, 282, 282, 40, 40},
  {entry__22_190, NULL, 294, 294, 62, 62},
  {entry__22_187, NULL, 293, 293, 28, 45},
  {cont__22_188, &frame__22_187, 293, 293, 28, 56},
  {cont__22_189, &frame__22_187, 293, 294, 21, 62},
  {cont__22_191, &frame__22_187, 295, 295, 48, 65},
  {cont__22_192, &frame__22_187, 295, 295, 21, 78},
  {cont__22_193, &frame__22_187, 297, 297, 22, 42},
  {cont__22_194, &frame__22_187, 297, 297, 21, 53},
  {cont__22_195, &frame__22_187, 298, 298, 21, 39},
  {cont__22_196, &frame__22_187, 298, 298, 50, 50},
  {entry__22_184, NULL, 291, 291, 19, 43},
  {cont__22_185, &frame__22_184, 292, 292, 26, 54},
  {cont__22_186, &frame__22_184, 292, 298, 19, 50},
  {entry__22_178, NULL, 284, 284, 17, 48},
  {cont__22_179, &frame__22_178, 287, 287, 33, 50},
  {cont__22_180, &frame__22_178, 287, 287, 19, 63},
  {cont__22_181, &frame__22_178, 289, 289, 17, 35},
  {cont__22_182, &frame__22_178, 290, 290, 20, 34},
  {cont__22_183, &frame__22_178, 290, 298, 17, 51},
  {entry__22_120, NULL, 234, 234, 13, 37},
  {cont__22_121, &frame__22_120, 235, 235, 13, 47},
  {cont__22_122, &frame__22_120, 236, 236, 13, 46},
  {cont__22_123, &frame__22_120, 237, 237, 21, 43},
  {cont__22_124, &frame__22_120, 237, 237, 13, 46},
  {cont__22_125, &frame__22_120, 238, 272, 13, 22},
  {cont__22_163, &frame__22_120, 274, 274, 15, 44},
  {cont__22_164, &frame__22_120, 283, 283, 15, 41},
  {cont__22_177, &frame__22_120, 273, 298, 13, 53},
  {entry__22_116, NULL, 231, 231, 11, 48},
  {cont__22_117, &frame__22_116, 232, 232, 11, 45},
  {cont__22_118, &frame__22_116, 233, 233, 14, 33},
  {cont__22_119, &frame__22_116, 233, 298, 11, 54},
  {entry__22_112, NULL, 228, 228, 22, 51},
  {cont__22_113, &frame__22_112, 228, 228, 22, 54},
  {cont__22_114, &frame__22_112, 230, 230, 12, 38},
  {cont__22_115, &frame__22_112, 230, 298, 9, 55},
  {entry__22_110, NULL, 227, 227, 10, 35},
  {cont__22_111, &frame__22_110, 227, 298, 7, 56},
  {entry__22_84, NULL, 211, 298, 5, 57},
  {cont__22_197, &frame__22_84, 298, 298, 57, 57},
  {entry__22_1_extract_documentation_from_file, NULL, 161, 161, 10, 56},
  {cont__22_4, &frame__22_1_extract_documentation_from_file, 161, 161, 3, 56},
  {cont__22_5, &frame__22_1_extract_documentation_from_file, 162, 162, 8, 21},
  {cont__22_6, &frame__22_1_extract_documentation_from_file, 162, 162, 3, 31},
  {cont__22_7, &frame__22_1_extract_documentation_from_file, 163, 163, 6, 19},
  {cont__22_8, &frame__22_1_extract_documentation_from_file, 163, 163, 6, 24},
  {cont__22_9, &frame__22_1_extract_documentation_from_file, 163, 163, 3, 52},
  {cont__22_12, &frame__22_1_extract_documentation_from_file, 164, 164, 6, 11},
  {cont__22_13, &frame__22_1_extract_documentation_from_file, 164, 164, 6, 18},
  {cont__22_14, &frame__22_1_extract_documentation_from_file, 164, 164, 6, 18},
  {cont__22_15, &frame__22_1_extract_documentation_from_file, 164, 164, 3, 63},
  {cont__22_18, &frame__22_1_extract_documentation_from_file, 165, 165, 11, 11},
  {cont__22_19, &frame__22_1_extract_documentation_from_file, 165, 165, 6, 12},
  {cont__22_20, &frame__22_1_extract_documentation_from_file, 165, 165, 6, 23},
  {cont__22_21, &frame__22_1_extract_documentation_from_file, 165, 165, 6, 23},
  {cont__22_22, &frame__22_1_extract_documentation_from_file, 165, 165, 3, 71},
  {cont__22_25, &frame__22_1_extract_documentation_from_file, 168, 168, 17, 48},
  {cont__22_27, &frame__22_1_extract_documentation_from_file, 168, 168, 50, 59},
  {cont__22_29, &frame__22_1_extract_documentation_from_file, 167, 169, 3, 69},
  {cont__22_30, &frame__22_1_extract_documentation_from_file, 178, 178, 3, 37},
  {cont__22_31, &frame__22_1_extract_documentation_from_file, 179, 179, 3, 56},
  {cont__22_34, &frame__22_1_extract_documentation_from_file, 182, 192, 3, 17},
  {cont__22_46, &frame__22_1_extract_documentation_from_file, 193, 193, 31, 31},
  {cont__22_47, &frame__22_1_extract_documentation_from_file, 193, 193, 3, 31},
  {cont__22_48, &frame__22_1_extract_documentation_from_file, 194, 194, 3, 70},
  {cont__22_52, &frame__22_1_extract_documentation_from_file, 195, 195, 6, 29},
  {cont__22_53, &frame__22_1_extract_documentation_from_file, 195, 195, 3, 59},
  {cont__22_57, &frame__22_1_extract_documentation_from_file, 197, 205, 3, 77},
  {cont__22_83, &frame__22_1_extract_documentation_from_file, 206, 298, 3, 58},
  {cont__22_198, &frame__22_1_extract_documentation_from_file, 298, 298, 58, 58},
  {entry__23_8, NULL, 304, 304, 32, 72},
  {entry__23_6, NULL, 304, 304, 10, 29},
  {cont__23_7, &frame__23_6, 304, 304, 7, 72},
  {entry__23_11, NULL, 305, 305, 36, 71},
  {entry__23_9, NULL, 305, 305, 10, 33},
  {cont__23_10, &frame__23_9, 305, 305, 7, 71},
  {entry__23_4, NULL, 302, 302, 5, 28},
  {cont__23_5, &frame__23_4, 303, 305, 5, 71},
  {entry__23_1_extract_documentation_from_directory, NULL, 301, 301, 22, 27},
  {cont__23_2, &frame__23_1_extract_documentation_from_directory, 301, 301, 12, 33},
  {cont__23_3, &frame__23_1_extract_documentation_from_directory, 301, 305, 3, 72},
  {entry__24_5, NULL, 309, 309, 40, 53},
  {cont__24_6, &frame__24_5, 309, 309, 37, 53},
  {entry__24_13, NULL, 314, 315, 17, 64},
  {cont__24_16, &frame__24_13, 314, 315, 11, 64},
  {entry__24_11, NULL, 313, 313, 12, 40},
  {cont__24_12, &frame__24_11, 313, 315, 9, 65},
  {cont__24_17, &frame__24_11, 316, 316, 37, 37},
  {entry__24_9, NULL, 312, 312, 10, 46},
  {cont__24_10, &frame__24_9, 312, 316, 7, 37},
  {entry__24_20, NULL, 318, 319, 13, 51},
  {cont__24_22, &frame__24_20, 318, 319, 7, 51},
  {entry__24_7, NULL, 311, 311, 14, 37},
  {cont__24_8, &frame__24_7, 311, 316, 5, 38},
  {cont__24_18, &frame__24_7, 317, 317, 12, 40},
  {cont__24_19, &frame__24_7, 317, 319, 5, 52},
  {cont__24_23, &frame__24_7, 320, 320, 8, 43},
  {cont__24_25, &frame__24_7, 320, 320, 5, 43},
  {entry__24_1_resolved_name, NULL, 308, 308, 3, 21},
  {cont__24_2, &frame__24_1_resolved_name, 309, 309, 6, 23},
  {cont__24_3, &frame__24_1_resolved_name, 309, 309, 6, 34},
  {cont__24_4, &frame__24_1_resolved_name, 309, 320, 3, 43},
  {entry__25_15, NULL, 330, 330, 35, 69},
  {entry__25_12, NULL, 329, 329, 7, 39},
  {cont__25_13, &frame__25_12, 330, 330, 10, 32},
  {cont__25_14, &frame__25_12, 330, 330, 7, 69},
  {entry__25_7, NULL, 326, 326, 6, 32},
  {cont__25_8, &frame__25_7, 326, 326, 5, 38},
  {cont__25_9, &frame__25_7, 327, 327, 12, 30},
  {cont__25_10, &frame__25_7, 327, 327, 12, 38},
  {cont__25_11, &frame__25_7, 327, 330, 5, 69},
  {cont__25_16, &frame__25_7, 331, 331, 5, 23},
  {cont__25_17, &frame__25_7, 331, 331, 34, 34},
  {entry__25_1_add_derived_type, NULL, 323, 323, 23, 40},
  {cont__25_2, &frame__25_1_add_derived_type, 323, 323, 42, 59},
  {cont__25_3, &frame__25_1_add_derived_type, 323, 323, 3, 60},
  {cont__25_4, &frame__25_1_add_derived_type, 324, 324, 3, 33},
  {cont__25_5, &frame__25_1_add_derived_type, 325, 325, 6, 26},
  {cont__25_6, &frame__25_1_add_derived_type, 325, 331, 3, 34},
  {entry__26_1_mangled, NULL, 333, 333, 38, 48},
  {cont__26_2, &frame__26_1_mangled, 333, 333, 50, 60},
  {cont__26_4, &frame__26_1_mangled, 333, 333, 21, 61},
  {cont__26_5, &frame__26_1_mangled, 333, 333, 18, 61},
  {entry__27_1_ordered_name, NULL, 338, 338, 7, 24},
  {cont__27_2, &frame__27_1_ordered_name, 340, 340, 7, 29},
  {cont__27_3, &frame__27_1_ordered_name, 337, 344, 5, 14},
  {cont__27_4, &frame__27_1_ordered_name, 336, 344, 3, 16},
  {entry__28_2, NULL, 348, 348, 7, 27},
  {cont__28_5, &frame__28_2, 348, 348, 5, 34},
  {cont__28_7, &frame__28_2, 349, 349, 5, 29},
  {cont__28_9, &frame__28_2, 350, 350, 7, 28},
  {cont__28_11, &frame__28_2, 350, 350, 5, 37},
  {cont__28_13, &frame__28_2, 351, 351, 5, 29},
  {cont__28_14, &frame__28_2, 352, 352, 7, 32},
  {cont__28_16, &frame__28_2, 352, 352, 5, 45},
  {cont__28_18, &frame__28_2, 353, 353, 5, 29},
  {cont__28_19, &frame__28_2, 354, 354, 7, 34},
  {cont__28_21, &frame__28_2, 354, 354, 5, 49},
  {cont__28_23, &frame__28_2, 355, 355, 5, 29},
  {cont__28_24, &frame__28_2, 356, 356, 7, 33},
  {cont__28_26, &frame__28_2, 356, 356, 5, 47},
  {entry__28_1_link_bar, NULL, 347, 356, 3, 47},
  {entry__29_7, NULL, 363, 363, 41, 67},
  {cont__29_9, &frame__29_7, 363, 363, 67, 67},
  {entry__29_12, NULL, 364, 364, 43, 69},
  {cont__29_14, &frame__29_12, 364, 364, 69, 69},
  {entry__29_3, NULL, 361, 361, 7, 40},
  {cont__29_4, &frame__29_3, 362, 362, 7, 42},
  {cont__29_5, &frame__29_3, 363, 363, 14, 38},
  {cont__29_6, &frame__29_3, 363, 363, 7, 67},
  {cont__29_10, &frame__29_3, 364, 364, 14, 40},
  {cont__29_11, &frame__29_3, 364, 364, 7, 69},
  {cont__29_15, &frame__29_3, 365, 365, 7, 50},
  {cont__29_16, &frame__29_3, 365, 365, 50, 50},
  {entry__29_19, NULL, 367, 367, 41, 65},
  {cont__29_20, &frame__29_19, 367, 367, 65, 65},
  {entry__29_17, NULL, 367, 367, 14, 38},
  {cont__29_18, &frame__29_17, 367, 367, 7, 65},
  {entry__29_1_resolve_reference, NULL, 360, 360, 5, 28},
  {cont__29_2, &frame__29_1_resolve_reference, 359, 367, 3, 66},
  {cont__29_21, &frame__29_1_resolve_reference, },
  {entry__32_5, NULL, 381, 381, 13, 22},
  {cont__32_6, &frame__32_5, 382, 382, 13, 33},
  {cont__32_7, &frame__32_5, 383, 383, 22, 22},
  {entry__32_8, NULL, 385, 385, 13, 33},
  {cont__32_9, &frame__32_8, 385, 385, 33, 33},
  {entry__32_3, NULL, 380, 380, 11, 35},
  {cont__32_4, &frame__32_3, 379, 385, 9, 34},
  {entry__32_15, NULL, 390, 390, 15, 35},
  {cont__32_16, &frame__32_15, 391, 391, 22, 22},
  {entry__32_12, NULL, 389, 389, 16, 25},
  {cont__32_13, &frame__32_12, 389, 389, 16, 25},
  {cont__32_14, &frame__32_12, 389, 391, 13, 22},
  {entry__32_21, NULL, 395, 395, 60, 60},
  {entry__32_19, NULL, 395, 395, 20, 44},
  {cont__32_20, &frame__32_19, 395, 395, 17, 60},
  {entry__32_22, NULL, 397, 397, 17, 30},
  {cont__32_23, &frame__32_22, 397, 397, 30, 30},
  {entry__32_17, NULL, 394, 394, 15, 24},
  {cont__32_18, &frame__32_17, 393, 397, 13, 31},
  {cont__32_24, &frame__32_17, 398, 398, 26, 34},
  {cont__32_25, &frame__32_17, 398, 398, 13, 34},
  {cont__32_26, &frame__32_17, 398, 398, 34, 34},
  {entry__32_10, NULL, 388, 388, 11, 20},
  {cont__32_11, &frame__32_10, 387, 398, 9, 35},
  {entry__32_2, NULL, 377, 398, 5, 37},
  {entry__32_30, NULL, 399, 399, 18, 38},
  {cont__32_31, &frame__32_30, 399, 399, 38, 38},
  {entry__32_1_to_paragraphs, NULL, 376, 398, 3, 38},
  {cont__32_27, &frame__32_1_to_paragraphs, 399, 399, 6, 15},
  {cont__32_28, &frame__32_1_to_paragraphs, 399, 399, 6, 15},
  {cont__32_29, &frame__32_1_to_paragraphs, 399, 399, 3, 38},
  {cont__32_32, &frame__32_1_to_paragraphs, 400, 400, 3, 15},
  {entry__33_11, NULL, 408, 408, 11, 42},
  {cont__33_12, &frame__33_11, 409, 409, 11, 44},
  {cont__33_13, &frame__33_11, 415, 415, 15, 26},
  {cont__33_14, &frame__33_11, 419, 419, 15, 28},
  {cont__33_15, &frame__33_11, 411, 420, 13, 21},
  {cont__33_19, &frame__33_11, 410, 420, 11, 23},
  {entry__33_20, NULL, 422, 422, 11, 26},
  {entry__33_25, NULL, 434, 434, 40, 60},
  {cont__33_26, &frame__33_25, 434, 434, 40, 60},
  {entry__33_23, NULL, 434, 434, 11, 35},
  {cont__33_24, &frame__33_23, 434, 434, 11, 60},
  {cont__33_27, &frame__33_23, 434, 434, 11, 60},
  {entry__33_29, NULL, 436, 436, 20, 64},
  {cont__33_32, &frame__33_29, 436, 436, 11, 64},
  {entry__33_47, NULL, 454, 454, 58, 58},
  {cont__33_48, &frame__33_47, 454, 454, 39, 59},
  {cont__33_49, &frame__33_47, 454, 454, 21, 74},
  {cont__33_51, &frame__33_47, 454, 454, 74, 74},
  {entry__33_45, NULL, 453, 453, 22, 47},
  {cont__33_46, &frame__33_45, 453, 454, 19, 74},
  {entry__33_54, NULL, 457, 457, 49, 49},
  {cont__33_55, &frame__33_54, 457, 457, 30, 50},
  {cont__33_56, &frame__33_54, 456, 457, 21, 79},
  {cont__33_58, &frame__33_54, 457, 457, 80, 80},
  {entry__33_52, NULL, 455, 455, 22, 47},
  {cont__33_53, &frame__33_52, 455, 457, 19, 80},
  {entry__33_61, NULL, 461, 461, 26, 47},
  {cont__33_62, &frame__33_61, 461, 461, 26, 53},
  {cont__33_63, &frame__33_61, 463, 463, 26, 47},
  {cont__33_64, &frame__33_61, 463, 463, 26, 53},
  {cont__33_65, &frame__33_61, 459, 464, 21, 28},
  {cont__33_68, &frame__33_61, 464, 464, 29, 29},
  {entry__33_59, NULL, 458, 458, 22, 45},
  {cont__33_60, &frame__33_59, 458, 464, 19, 29},
  {entry__33_43, NULL, 451, 451, 17, 68},
  {cont__33_44, &frame__33_43, 452, 464, 17, 30},
  {cont__33_69, &frame__33_43, 465, 465, 31, 52},
  {cont__33_70, &frame__33_43, 465, 465, 17, 58},
  {cont__33_71, &frame__33_43, 466, 466, 34, 56},
  {cont__33_72, &frame__33_43, 466, 466, 17, 56},
  {cont__33_73, &frame__33_43, 466, 466, 56, 56},
  {entry__33_38, NULL, 448, 448, 19, 53},
  {cont__33_39, &frame__33_38, 444, 449, 17, 20},
  {cont__33_41, &frame__33_38, 442, 449, 15, 21},
  {cont__33_42, &frame__33_38, 441, 466, 13, 57},
  {entry__33_83, NULL, 480, 480, 64, 64},
  {cont__33_84, &frame__33_83, 480, 480, 42, 65},
  {cont__33_85, &frame__33_83, 480, 480, 21, 80},
  {cont__33_86, &frame__33_83, 480, 480, 80, 80},
  {entry__33_81, NULL, 479, 479, 22, 50},
  {cont__33_82, &frame__33_81, 479, 480, 19, 80},
  {entry__33_89, NULL, 484, 484, 47, 47},
  {cont__33_90, &frame__33_89, 484, 484, 25, 48},
  {cont__33_91, &frame__33_89, 482, 485, 21, 52},
  {cont__33_92, &frame__33_89, 485, 485, 53, 53},
  {entry__33_87, NULL, 481, 481, 22, 50},
  {cont__33_88, &frame__33_87, 481, 485, 19, 53},
  {entry__33_79, NULL, 477, 477, 17, 71},
  {cont__33_80, &frame__33_79, 478, 485, 17, 54},
  {cont__33_93, &frame__33_79, 486, 486, 31, 52},
  {cont__33_94, &frame__33_79, 486, 486, 17, 58},
  {cont__33_95, &frame__33_79, 487, 487, 37, 62},
  {cont__33_96, &frame__33_79, 487, 487, 17, 62},
  {cont__33_97, &frame__33_79, 487, 487, 62, 62},
  {entry__33_74, NULL, 474, 474, 19, 53},
  {cont__33_75, &frame__33_74, 470, 475, 17, 20},
  {cont__33_77, &frame__33_74, 468, 475, 15, 21},
  {cont__33_78, &frame__33_74, 467, 487, 13, 63},
  {entry__33_104, NULL, 490, 490, 34, 47},
  {cont__33_105, &frame__33_104, 490, 490, 17, 47},
  {cont__33_106, &frame__33_104, 490, 490, 47, 47},
  {entry__33_101, NULL, 489, 489, 30, 51},
  {cont__33_102, &frame__33_101, 489, 489, 24, 56},
  {cont__33_103, &frame__33_101, 489, 490, 15, 47},
  {entry__33_98, NULL, 488, 488, 16, 49},
  {cont__33_100, &frame__33_98, 488, 490, 13, 48},
  {entry__33_112, NULL, 493, 493, 17, 27},
  {cont__33_113, &frame__33_112, 496, 496, 33, 45},
  {cont__33_114, &frame__33_112, 495, 496, 17, 66},
  {cont__33_115, &frame__33_112, 498, 498, 17, 46},
  {cont__33_116, &frame__33_112, 499, 499, 17, 30},
  {cont__33_117, &frame__33_112, 499, 499, 45, 45},
  {entry__33_109, NULL, 492, 492, 30, 51},
  {cont__33_110, &frame__33_109, 492, 492, 24, 56},
  {cont__33_111, &frame__33_109, 492, 499, 15, 45},
  {entry__33_107, NULL, 491, 491, 16, 43},
  {cont__33_108, &frame__33_107, 491, 499, 13, 46},
  {entry__33_120, NULL, 501, 501, 23, 44},
  {cont__33_121, &frame__33_120, 501, 501, 15, 50},
  {cont__33_122, &frame__33_120, 502, 502, 22, 43},
  {cont__33_123, &frame__33_120, 502, 502, 15, 49},
  {cont__33_124, &frame__33_120, 503, 503, 30, 41},
  {cont__33_125, &frame__33_120, 503, 503, 15, 41},
  {cont__33_126, &frame__33_120, 503, 503, 41, 41},
  {entry__33_118, NULL, 500, 500, 16, 45},
  {cont__33_119, &frame__33_118, 500, 503, 13, 41},
  {entry__33_134, NULL, 508, 508, 47, 47},
  {entry__33_135, NULL, 510, 510, 19, 49},
  {cont__33_136, &frame__33_135, 510, 510, 49, 49},
  {entry__33_130, NULL, 505, 505, 24, 45},
  {cont__33_131, &frame__33_130, 505, 505, 15, 51},
  {cont__33_132, &frame__33_130, 507, 507, 17, 28},
  {cont__33_133, &frame__33_130, 506, 510, 15, 50},
  {entry__33_127, NULL, 504, 504, 16, 58},
  {cont__33_129, &frame__33_127, 504, 510, 13, 51},
  {entry__33_141, NULL, 517, 517, 41, 41},
  {cont__33_142, &frame__33_141, 517, 517, 21, 41},
  {cont__33_143, &frame__33_141, 518, 518, 21, 48},
  {cont__33_144, &frame__33_141, 519, 519, 42, 58},
  {cont__33_145, &frame__33_141, 519, 519, 24, 66},
  {cont__33_147, &frame__33_141, 519, 519, 21, 66},
  {entry__33_153, NULL, 524, 524, 23, 55},
  {cont__33_154, &frame__33_153, 524, 524, 55, 55},
  {entry__33_155, NULL, 526, 526, 23, 50},
  {cont__33_156, &frame__33_155, 526, 526, 50, 50},
  {entry__33_151, NULL, 523, 523, 21, 48},
  {cont__33_152, &frame__33_151, 522, 526, 19, 51},
  {entry__33_157, NULL, 528, 528, 46, 46},
  {entry__33_137, NULL, 515, 515, 39, 47},
  {cont__33_138, &frame__33_137, 515, 515, 30, 48},
  {cont__33_139, &frame__33_137, 515, 515, 19, 53},
  {cont__33_140, &frame__33_137, 514, 519, 17, 66},
  {cont__33_148, &frame__33_137, 512, 519, 15, 68},
  {cont__33_149, &frame__33_137, 521, 521, 17, 44},
  {cont__33_150, &frame__33_137, 520, 528, 15, 47},
  {entry__33_37, NULL, 440, 528, 11, 49},
  {entry__33_35, NULL, 438, 438, 9, 46},
  {cont__33_36, &frame__33_35, 439, 528, 9, 50},
  {entry__33_175, NULL, 544, 544, 25, 51},
  {cont__33_176, &frame__33_175, 544, 544, 25, 61},
  {cont__33_177, &frame__33_175, 541, 545, 23, 27},
  {cont__33_178, &frame__33_175, 545, 545, 28, 28},
  {entry__33_179, NULL, 547, 547, 23, 48},
  {cont__33_180, &frame__33_179, 547, 547, 48, 48},
  {entry__33_172, NULL, 540, 540, 21, 47},
  {cont__33_173, &frame__33_172, 540, 540, 21, 58},
  {cont__33_174, &frame__33_172, 539, 547, 19, 49},
  {entry__33_170, NULL, 538, 538, 20, 48},
  {cont__33_171, &frame__33_170, 538, 547, 17, 50},
  {entry__33_183, NULL, 549, 549, 19, 58},
  {cont__33_184, &frame__33_183, 549, 549, 58, 58},
  {entry__33_181, NULL, 548, 548, 20, 48},
  {cont__33_182, &frame__33_181, 548, 549, 17, 58},
  {entry__33_189, NULL, 554, 554, 22, 47},
  {cont__33_190, &frame__33_189, 554, 554, 22, 61},
  {cont__33_191, &frame__33_189, 554, 554, 22, 64},
  {cont__33_192, &frame__33_189, 554, 554, 19, 64},
  {entry__33_193, NULL, 555, 555, 19, 23},
  {entry__33_166, NULL, 536, 536, 30, 53},
  {cont__33_167, &frame__33_166, 536, 536, 22, 54},
  {cont__33_168, &frame__33_166, 536, 536, 15, 75},
  {cont__33_169, &frame__33_166, 537, 549, 15, 59},
  {cont__33_185, &frame__33_166, 553, 553, 23, 48},
  {cont__33_186, &frame__33_166, 553, 553, 23, 57},
  {cont__33_187, &frame__33_166, 553, 553, 19, 58},
  {cont__33_188, &frame__33_166, 551, 555, 15, 24},
  {cont__33_194, &frame__33_166, 557, 557, 32, 49},
  {cont__33_195, &frame__33_166, 557, 557, 15, 49},
  {cont__33_196, &frame__33_166, 557, 557, 49, 49},
  {entry__33_197, NULL, 534, 534, 15, 18},
  {entry__33_163, NULL, 532, 532, 13, 40},
  {cont__33_164, &frame__33_163, 533, 533, 13, 52},
  {cont__33_165, &frame__33_163, 531, 557, 11, 50},
  {entry__33_161, NULL, 530, 530, 18, 36},
  {cont__33_162, &frame__33_161, 530, 557, 9, 51},
  {entry__33_200, NULL, 558, 558, 40, 58},
  {entry__33_210, NULL, 564, 564, 19, 42},
  {cont__33_211, &frame__33_210, 564, 564, 17, 42},
  {entry__33_207, NULL, 563, 563, 16, 32},
  {cont__33_208, &frame__33_207, 563, 563, 13, 32},
  {cont__33_209, &frame__33_207, 564, 564, 13, 42},
  {entry__33_206, NULL, 562, 564, 11, 42},
  {entry__33_203, NULL, 560, 560, 9, 23},
  {cont__33_205, &frame__33_203, 561, 564, 9, 43},
  {entry__33_220, NULL, 570, 570, 19, 45},
  {cont__33_221, &frame__33_220, 570, 570, 17, 45},
  {entry__33_217, NULL, 569, 569, 16, 35},
  {cont__33_218, &frame__33_217, 569, 569, 13, 35},
  {cont__33_219, &frame__33_217, 570, 570, 13, 45},
  {entry__33_216, NULL, 568, 570, 11, 45},
  {entry__33_214, NULL, 566, 566, 9, 20},
  {cont__33_215, &frame__33_214, 567, 570, 9, 46},
  {entry__33_227, NULL, 573, 573, 46, 58},
  {entry__33_224, NULL, 572, 572, 9, 24},
  {cont__33_226, &frame__33_224, 573, 573, 9, 58},
  {entry__33_233, NULL, 576, 576, 46, 53},
  {entry__33_230, NULL, 575, 575, 9, 30},
  {cont__33_232, &frame__33_230, 576, 576, 9, 53},
  {entry__33_240, NULL, 581, 581, 13, 40},
  {cont__33_241, &frame__33_240, 582, 582, 27, 43},
  {cont__33_242, &frame__33_240, 582, 582, 24, 50},
  {cont__33_243, &frame__33_240, 582, 582, 15, 50},
  {cont__33_244, &frame__33_240, 582, 582, 13, 60},
  {cont__33_245, &frame__33_240, 583, 583, 13, 14},
  {entry__33_239, NULL, 580, 583, 11, 14},
  {entry__33_236, NULL, 578, 578, 9, 21},
  {cont__33_238, &frame__33_236, 579, 583, 9, 15},
  {entry__33_257, NULL, 590, 590, 33, 44},
  {cont__33_258, &frame__33_257, 590, 590, 30, 51},
  {cont__33_259, &frame__33_257, 590, 590, 21, 51},
  {cont__33_260, &frame__33_257, 590, 590, 19, 56},
  {entry__33_264, NULL, 592, 592, 33, 46},
  {cont__33_265, &frame__33_264, 592, 592, 30, 53},
  {cont__33_266, &frame__33_264, 592, 592, 21, 53},
  {cont__33_267, &frame__33_264, 592, 592, 19, 60},
  {entry__33_256, NULL, 590, 590, 15, 56},
  {cont__33_261, &frame__33_256, 591, 591, 15, 33},
  {cont__33_263, &frame__33_256, 592, 592, 15, 60},
  {entry__33_254, NULL, 588, 588, 13, 50},
  {cont__33_255, &frame__33_254, 589, 592, 13, 60},
  {entry__33_252, NULL, 587, 587, 20, 33},
  {cont__33_253, &frame__33_252, 587, 592, 11, 61},
  {entry__33_249, NULL, 585, 585, 9, 27},
  {cont__33_251, &frame__33_249, 586, 592, 9, 62},
  {entry__33_278, NULL, 598, 598, 33, 51},
  {cont__33_279, &frame__33_278, 598, 598, 30, 58},
  {cont__33_280, &frame__33_278, 598, 598, 21, 58},
  {cont__33_281, &frame__33_278, 598, 598, 19, 70},
  {entry__33_285, NULL, 604, 604, 24, 44},
  {cont__33_286, &frame__33_285, 604, 604, 51, 69},
  {cont__33_287, &frame__33_285, 604, 604, 21, 76},
  {cont__33_288, &frame__33_285, 602, 604, 19, 75},
  {cont__33_289, &frame__33_285, 601, 607, 17, 29},
  {entry__33_277, NULL, 598, 598, 15, 70},
  {cont__33_282, &frame__33_277, 599, 599, 15, 25},
  {cont__33_284, &frame__33_277, 600, 607, 15, 30},
  {entry__33_276, NULL, 597, 607, 13, 31},
  {entry__33_274, NULL, 596, 596, 20, 35},
  {cont__33_275, &frame__33_274, 596, 607, 11, 32},
  {entry__33_271, NULL, 594, 594, 9, 44},
  {cont__33_273, &frame__33_271, 595, 607, 9, 33},
  {entry__33_306, NULL, 626, 626, 19, 35},
  {entry__33_301, NULL, 623, 623, 24, 48},
  {cont__33_302, &frame__33_301, 623, 623, 24, 63},
  {cont__33_303, &frame__33_301, 623, 623, 19, 64},
  {cont__33_304, &frame__33_301, 621, 624, 17, 25},
  {cont__33_305, &frame__33_301, 620, 626, 15, 35},
  {cont__33_307, &frame__33_301, 627, 627, 35, 69},
  {cont__33_309, &frame__33_301, 627, 627, 15, 69},
  {cont__33_310, &frame__33_301, 618, 627, 13, 68},
  {cont__33_311, &frame__33_301, 617, 627, 11, 70},
  {entry__33_293, NULL, 613, 613, 9, 30},
  {cont__33_294, &frame__33_293, 614, 614, 9, 36},
  {cont__33_295, &frame__33_293, 615, 615, 9, 16},
  {cont__33_296, &frame__33_293, 616, 616, 45, 56},
  {cont__33_297, &frame__33_293, 616, 616, 23, 56},
  {cont__33_298, &frame__33_293, 616, 616, 13, 56},
  {cont__33_300, &frame__33_293, 616, 627, 9, 71},
  {entry__33_8, NULL, 405, 405, 7, 14},
  {cont__33_9, &frame__33_8, 407, 407, 9, 36},
  {cont__33_10, &frame__33_8, 406, 422, 7, 27},
  {cont__33_21, &frame__33_8, 430, 430, 7, 41},
  {cont__33_22, &frame__33_8, 432, 434, 9, 59},
  {cont__33_28, &frame__33_8, 431, 436, 7, 65},
  {cont__33_33, &frame__33_8, 437, 437, 10, 32},
  {cont__33_34, &frame__33_8, 437, 528, 7, 51},
  {cont__33_158, &frame__33_8, 529, 529, 10, 22},
  {cont__33_159, &frame__33_8, 529, 529, 10, 34},
  {cont__33_160, &frame__33_8, 529, 557, 7, 52},
  {cont__33_198, &frame__33_8, 558, 558, 10, 37},
  {cont__33_199, &frame__33_8, 558, 558, 7, 58},
  {cont__33_201, &frame__33_8, 559, 559, 14, 32},
  {cont__33_202, &frame__33_8, 559, 564, 7, 44},
  {cont__33_212, &frame__33_8, 565, 565, 14, 35},
  {cont__33_213, &frame__33_8, 565, 570, 7, 47},
  {cont__33_222, &frame__33_8, 571, 571, 14, 34},
  {cont__33_223, &frame__33_8, 571, 573, 7, 58},
  {cont__33_228, &frame__33_8, 574, 574, 10, 37},
  {cont__33_229, &frame__33_8, 574, 576, 7, 53},
  {cont__33_234, &frame__33_8, 577, 577, 14, 32},
  {cont__33_235, &frame__33_8, 577, 583, 7, 16},
  {cont__33_246, &frame__33_8, 584, 584, 14, 27},
  {cont__33_247, &frame__33_8, 584, 584, 14, 36},
  {cont__33_248, &frame__33_8, 584, 592, 7, 63},
  {cont__33_268, &frame__33_8, 593, 593, 10, 22},
  {cont__33_269, &frame__33_8, 593, 593, 10, 30},
  {cont__33_270, &frame__33_8, 593, 607, 7, 34},
  {cont__33_290, &frame__33_8, 610, 610, 9, 42},
  {cont__33_291, &frame__33_8, 609, 610, 7, 64},
  {cont__33_292, &frame__33_8, 612, 627, 7, 72},
  {cont__33_312, &frame__33_8, 629, 629, 9, 26},
  {cont__33_314, &frame__33_8, 630, 630, 24, 40},
  {cont__33_315, &frame__33_8, 630, 630, 24, 69},
  {cont__33_316, &frame__33_8, 630, 630, 9, 76},
  {cont__33_319, &frame__33_8, 628, 630, 7, 76},
  {entry__33_3, NULL, 404, 404, 25, 45},
  {cont__33_4, &frame__33_3, 404, 404, 17, 52},
  {cont__33_7, &frame__33_3, 404, 630, 5, 77},
  {entry__33_1_create_info_page, NULL, 403, 403, 6, 29},
  {cont__33_2, &frame__33_1_create_info_page, 403, 630, 3, 78},
  {entry__34_8, NULL, 640, 640, 59, 59},
  {cont__34_9, &frame__34_8, 640, 640, 42, 60},
  {cont__34_10, &frame__34_8, 640, 640, 13, 61},
  {cont__34_11, &frame__34_8, 642, 642, 26, 42},
  {cont__34_12, &frame__34_8, 641, 642, 16, 67},
  {cont__34_16, &frame__34_8, 641, 642, 13, 67},
  {entry__34_5, NULL, 638, 638, 11, 39},
  {cont__34_7, &frame__34_5, 637, 642, 9, 68},
  {cont__34_17, &frame__34_5, 635, 642, 7, 70},
  {cont__34_18, &frame__34_5, 642, 642, 71, 71},
  {entry__34_2_html__encode, NULL, 634, 634, 8, 17},
  {cont__34_4, &frame__34_2_html__encode, 634, 642, 5, 71},
  {cont__34_19, &frame__34_2_html__encode, 643, 643, 5, 13},
  {entry__34_29, NULL, 650, 650, 27, 52},
  {entry__34_34, NULL, 654, 654, 24, 48},
  {cont__34_35, &frame__34_34, 654, 654, 11, 62},
  {cont__34_36, &frame__34_34, 654, 654, 62, 62},
  {entry__34_40, NULL, 657, 657, 26, 50},
  {cont__34_41, &frame__34_40, 657, 657, 52, 76},
  {cont__34_42, &frame__34_40, 656, 657, 11, 77},
  {cont__34_43, &frame__34_40, 659, 659, 12, 29},
  {cont__34_44, &frame__34_40, 659, 659, 12, 38},
  {cont__34_45, &frame__34_40, 659, 659, 40, 52},
  {cont__34_46, &frame__34_40, 659, 659, 11, 53},
  {cont__34_47, &frame__34_40, 659, 659, 11, 29},
  {cont__34_48, &frame__34_40, 659, 659, 58, 58},
  {entry__34_32, NULL, 653, 653, 16, 42},
  {cont__34_33, &frame__34_32, 653, 654, 9, 62},
  {cont__34_37, &frame__34_32, 655, 655, 12, 24},
  {cont__34_38, &frame__34_32, 655, 655, 12, 35},
  {cont__34_39, &frame__34_32, 655, 659, 9, 58},
  {cont__34_49, &frame__34_32, 660, 660, 9, 29},
  {cont__34_50, &frame__34_32, 660, 660, 41, 41},
  {entry__34_26, NULL, 649, 649, 7, 25},
  {cont__34_27, &frame__34_26, 650, 650, 10, 24},
  {cont__34_28, &frame__34_26, 650, 650, 7, 52},
  {cont__34_30, &frame__34_26, 652, 652, 16, 31},
  {cont__34_31, &frame__34_26, 652, 660, 7, 41},
  {cont__34_51, &frame__34_26, 661, 661, 8, 24},
  {cont__34_52, &frame__34_26, 661, 661, 7, 24},
  {cont__34_53, &frame__34_26, 661, 661, 43, 43},
  {entry__34_23, NULL, 648, 648, 8, 20},
  {cont__34_24, &frame__34_23, 648, 648, 8, 28},
  {cont__34_25, &frame__34_23, 648, 661, 5, 43},
  {entry__34_63, NULL, 673, 673, 18, 50},
  {cont__34_64, &frame__34_63, 673, 673, 13, 50},
  {cont__34_65, &frame__34_63, 674, 674, 27, 39},
  {cont__34_66, &frame__34_63, 674, 674, 24, 46},
  {cont__34_67, &frame__34_63, 674, 674, 15, 46},
  {cont__34_68, &frame__34_63, 674, 674, 13, 52},
  {entry__34_62, NULL, 672, 674, 11, 52},
  {entry__34_71, NULL, 675, 675, 43, 63},
  {cont__34_72, &frame__34_71, 675, 675, 39, 64},
  {cont__34_73, &frame__34_71, 675, 675, 39, 64},
  {entry__34_75, NULL, 676, 676, 14, 39},
  {cont__34_76, &frame__34_75, 676, 676, 14, 42},
  {cont__34_77, &frame__34_75, 676, 676, 11, 42},
  {entry__34_80, NULL, 678, 678, 27, 43},
  {cont__34_81, &frame__34_80, 678, 678, 45, 52},
  {cont__34_82, &frame__34_80, 678, 678, 11, 52},
  {entry__34_58, NULL, 669, 669, 9, 28},
  {cont__34_59, &frame__34_58, 670, 670, 9, 43},
  {cont__34_60, &frame__34_58, 671, 671, 12, 27},
  {cont__34_61, &frame__34_58, 671, 674, 9, 53},
  {cont__34_69, &frame__34_58, 675, 675, 12, 34},
  {cont__34_70, &frame__34_58, 675, 675, 12, 64},
  {cont__34_74, &frame__34_58, 675, 676, 9, 42},
  {cont__34_78, &frame__34_58, 677, 677, 18, 39},
  {cont__34_79, &frame__34_58, 677, 678, 9, 52},
  {entry__34_57_print_type_info, NULL, 668, 678, 7, 53},
  {entry__34_89, NULL, 684, 684, 37, 49},
  {cont__34_90, &frame__34_89, 684, 684, 37, 62},
  {cont__34_91, &frame__34_89, 684, 684, 37, 62},
  {entry__34_93, NULL, 685, 685, 11, 30},
  {entry__34_86, NULL, 684, 684, 12, 24},
  {cont__34_87, &frame__34_86, 684, 684, 12, 32},
  {cont__34_88, &frame__34_86, 684, 684, 12, 62},
  {cont__34_92, &frame__34_86, 684, 685, 9, 30},
  {entry__34_85, NULL, 683, 685, 7, 31},
  {entry__34_56, NULL, 680, 680, 5, 12},
  {cont__34_83, &frame__34_56, 681, 681, 5, 19},
  {cont__34_84, &frame__34_56, 682, 685, 5, 32},
  {entry__34_102, NULL, 692, 692, 20, 31},
  {cont__34_104, &frame__34_102, 692, 692, 11, 31},
  {cont__34_105, &frame__34_102, 692, 692, 33, 52},
  {cont__34_106, &frame__34_102, 692, 692, 9, 52},
  {entry__34_107, NULL, 694, 694, 9, 16},
  {entry__34_123, NULL, 704, 704, 22, 41},
  {cont__34_124, &frame__34_123, 704, 704, 17, 41},
  {cont__34_125, &frame__34_123, 705, 705, 19, 35},
  {cont__34_127, &frame__34_123, 705, 705, 17, 66},
  {entry__34_121, NULL, 703, 703, 18, 30},
  {cont__34_122, &frame__34_121, 703, 705, 15, 66},
  {entry__34_118, NULL, 702, 702, 16, 28},
  {cont__34_120, &frame__34_118, 702, 705, 13, 67},
  {entry__34_116, NULL, 700, 700, 11, 26},
  {cont__34_117, &frame__34_116, 701, 705, 11, 68},
  {entry__34_133, NULL, 709, 709, 43, 63},
  {cont__34_134, &frame__34_133, 709, 709, 39, 64},
  {cont__34_135, &frame__34_133, 709, 709, 39, 64},
  {entry__34_137, NULL, 710, 710, 19, 44},
  {cont__34_138, &frame__34_137, 710, 710, 11, 47},
  {cont__34_139, &frame__34_137, 710, 710, 47, 47},
  {entry__34_142, NULL, 716, 716, 13, 25},
  {entry__34_144, NULL, 718, 718, 13, 34},
  {entry__34_146, NULL, 720, 720, 13, 37},
  {entry__34_148, NULL, 722, 722, 13, 28},
  {entry__34_150, NULL, 724, 724, 13, 25},
  {entry__34_152, NULL, 726, 726, 13, 21},
  {entry__34_153, NULL, 727, 727, 13, 24},
  {entry__34_158, NULL, 732, 732, 15, 55},
  {cont__34_160, &frame__34_158, 732, 732, 55, 55},
  {entry__34_161, NULL, 734, 734, 31, 31},
  {entry__34_156, NULL, 731, 731, 13, 29},
  {cont__34_157, &frame__34_156, 730, 734, 11, 32},
  {entry__34_164, NULL, 735, 735, 33, 47},
  {cont__34_165, &frame__34_164, 735, 735, 33, 47},
  {entry__34_174, NULL, 738, 738, 31, 42},
  {cont__34_175, &frame__34_174, 738, 738, 28, 49},
  {cont__34_176, &frame__34_174, 738, 738, 19, 49},
  {cont__34_177, &frame__34_174, 738, 738, 51, 68},
  {cont__34_178, &frame__34_174, 738, 738, 17, 68},
  {entry__34_168, NULL, 737, 737, 16, 32},
  {cont__34_171, &frame__34_168, 737, 737, 34, 50},
  {cont__34_172, &frame__34_168, 737, 737, 13, 50},
  {cont__34_173, &frame__34_168, 738, 738, 13, 68},
  {cont__34_179, &frame__34_168, 739, 739, 16, 33},
  {cont__34_181, &frame__34_168, 739, 739, 13, 40},
  {entry__34_167, NULL, 736, 739, 11, 40},
  {entry__34_112, NULL, 699, 699, 12, 19},
  {cont__34_113, &frame__34_112, 699, 699, 12, 29},
  {cont__34_114, &frame__34_112, 699, 699, 12, 29},
  {cont__34_115, &frame__34_112, 699, 705, 9, 69},
  {cont__34_129, &frame__34_112, 707, 707, 9, 27},
  {cont__34_130, &frame__34_112, 708, 708, 9, 43},
  {cont__34_131, &frame__34_112, 709, 709, 12, 34},
  {cont__34_132, &frame__34_112, 709, 709, 12, 64},
  {cont__34_136, &frame__34_112, 709, 710, 9, 47},
  {cont__34_140, &frame__34_112, 714, 714, 13, 25},
  {cont__34_141, &frame__34_112, 712, 727, 9, 25},
  {cont__34_154, &frame__34_112, 729, 729, 12, 31},
  {cont__34_155, &frame__34_112, 729, 734, 9, 33},
  {cont__34_162, &frame__34_112, 735, 735, 12, 28},
  {cont__34_163, &frame__34_112, 735, 735, 12, 47},
  {cont__34_166, &frame__34_112, 735, 739, 9, 41},
  {entry__34_111, NULL, 698, 739, 7, 42},
  {entry__34_96, NULL, 687, 687, 5, 12},
  {cont__34_97, &frame__34_96, 688, 688, 8, 21},
  {cont__34_100, &frame__34_96, 688, 688, 5, 36},
  {cont__34_101, &frame__34_96, 689, 694, 5, 17},
  {cont__34_109, &frame__34_96, 695, 695, 5, 6},
  {cont__34_110, &frame__34_96, 696, 739, 5, 43},
  {entry__34_189, NULL, 745, 745, 26, 53},
  {cont__34_191, &frame__34_189, 745, 745, 9, 65},
  {entry__34_187, NULL, 744, 744, 16, 31},
  {cont__34_188, &frame__34_187, 744, 745, 7, 65},
  {entry__34_183, NULL, 741, 741, 5, 23},
  {cont__34_184, &frame__34_183, 742, 742, 5, 30},
  {cont__34_185, &frame__34_183, 743, 743, 10, 22},
  {cont__34_186, &frame__34_183, 743, 745, 5, 66},
  {entry__34_206, NULL, 752, 752, 19, 35},
  {cont__34_207, &frame__34_206, 752, 752, 17, 41},
  {entry__34_205, NULL, 752, 752, 13, 41},
  {entry__34_199, NULL, 751, 751, 38, 56},
  {cont__34_200, &frame__34_199, 751, 751, 58, 66},
  {cont__34_202, &frame__34_199, 751, 751, 26, 67},
  {cont__34_203, &frame__34_199, 751, 751, 9, 76},
  {cont__34_204, &frame__34_199, 752, 752, 9, 41},
  {entry__34_198, NULL, 750, 752, 7, 41},
  {entry__34_194, NULL, 747, 747, 5, 12},
  {cont__34_195, &frame__34_194, 748, 748, 8, 21},
  {cont__34_196, &frame__34_194, 748, 748, 5, 35},
  {cont__34_197, &frame__34_194, 749, 752, 5, 42},
  {entry__34_221, NULL, 760, 760, 37, 53},
  {cont__34_222, &frame__34_221, 760, 760, 30, 62},
  {cont__34_223, &frame__34_221, 760, 760, 21, 62},
  {cont__34_224, &frame__34_221, 760, 760, 19, 72},
  {entry__34_220, NULL, 760, 760, 15, 72},
  {entry__34_219, NULL, 760, 760, 11, 72},
  {entry__34_218, NULL, 759, 760, 9, 72},
  {entry__34_214, NULL, 756, 756, 7, 14},
  {cont__34_215, &frame__34_214, 757, 757, 10, 23},
  {cont__34_216, &frame__34_214, 757, 757, 7, 29},
  {cont__34_217, &frame__34_214, 758, 760, 7, 73},
  {entry__34_209, NULL, 754, 754, 27, 45},
  {cont__34_210, &frame__34_209, 754, 754, 47, 55},
  {cont__34_211, &frame__34_209, 754, 754, 5, 56},
  {cont__34_212, &frame__34_209, 755, 755, 17, 39},
  {cont__34_213, &frame__34_209, 755, 760, 5, 74},
  {entry__34_230, NULL, 763, 763, 10, 31},
  {cont__34_231, &frame__34_230, 763, 763, 8, 40},
  {entry__34_233, NULL, 764, 764, 10, 35},
  {cont__34_234, &frame__34_233, 764, 764, 8, 48},
  {entry__34_236, NULL, 765, 765, 10, 37},
  {cont__34_237, &frame__34_236, 765, 765, 8, 52},
  {entry__34_239, NULL, 766, 766, 10, 36},
  {cont__34_240, &frame__34_239, 766, 766, 8, 50},
  {entry__34_227, NULL, 762, 762, 5, 19},
  {cont__34_229, &frame__34_227, 763, 763, 5, 40},
  {cont__34_232, &frame__34_227, 764, 764, 5, 48},
  {cont__34_235, &frame__34_227, 765, 765, 5, 52},
  {cont__34_238, &frame__34_227, 766, 766, 5, 50},
  {entry__34_245, NULL, 784, 784, 15, 30},
  {cont__34_246, &frame__34_245, 784, 784, 30, 30},
  {entry__34_247, NULL, 785, 785, 19, 38},
  {cont__34_248, &frame__34_247, 785, 785, 38, 38},
  {entry__34_249, NULL, 786, 786, 31, 62},
  {cont__34_250, &frame__34_249, 786, 786, 62, 62},
  {entry__34_251, NULL, 787, 787, 32, 64},
  {cont__34_252, &frame__34_251, 787, 787, 64, 64},
  {entry__34_253, NULL, 788, 788, 28, 56},
  {cont__34_254, &frame__34_253, 788, 788, 56, 56},
  {entry__34_255, NULL, 789, 789, 22, 44},
  {cont__34_256, &frame__34_255, 789, 789, 44, 44},
  {entry__34_257, NULL, 790, 790, 19, 38},
  {cont__34_258, &frame__34_257, 790, 790, 38, 38},
  {entry__34_259, NULL, 791, 791, 19, 38},
  {cont__34_260, &frame__34_259, 791, 791, 38, 38},
  {entry__34_261, NULL, 792, 792, 11, 20},
  {cont__34_262, &frame__34_261, 792, 792, 20, 20},
  {entry__34_269, NULL, 796, 796, 23, 40},
  {cont__34_270, &frame__34_269, 796, 796, 40, 40},
  {entry__34_271, NULL, 797, 797, 32, 58},
  {cont__34_272, &frame__34_271, 797, 797, 58, 58},
  {entry__34_273, NULL, 798, 798, 15, 35},
  {cont__34_274, &frame__34_273, 798, 798, 35, 35},
  {entry__34_267, NULL, 795, 795, 16, 35},
  {cont__34_268, &frame__34_267, 795, 798, 11, 35},
  {entry__34_265, NULL, 794, 794, 18, 33},
  {cont__34_266, &frame__34_265, 794, 798, 9, 36},
  {entry__34_243, NULL, 783, 783, 12, 24},
  {cont__34_244, &frame__34_243, 783, 792, 7, 20},
  {cont__34_263, &frame__34_243, 793, 793, 12, 24},
  {cont__34_264, &frame__34_243, 793, 798, 7, 37},
  {entry__34_242, NULL, 782, 798, 5, 38},
  {cont__34_275, &frame__34_242, },
  {cont__34_276, &frame__34_242, },
  {cont__34_277, &frame__34_242, },
  {cont__34_278, &frame__34_242, },
  {cont__34_279, &frame__34_242, },
  {cont__34_280, &frame__34_242, },
  {cont__34_281, &frame__34_242, },
  {cont__34_282, &frame__34_242, },
  {cont__34_283, &frame__34_242, },
  {cont__34_284, &frame__34_242, 800, 812, 5, 24},
  {cont__34_285, &frame__34_242, 815, 815, 32, 60},
  {cont__34_286, &frame__34_242, 817, 817, 32, 54},
  {cont__34_287, &frame__34_242, 818, 818, 32, 58},
  {cont__34_288, &frame__34_242, 819, 819, 32, 70},
  {cont__34_289, &frame__34_242, 820, 820, 32, 71},
  {cont__34_290, &frame__34_242, 821, 821, 32, 56},
  {cont__34_291, &frame__34_242, 822, 822, 32, 65},
  {cont__34_292, &frame__34_242, 823, 823, 32, 59},
  {cont__34_293, &frame__34_242, 824, 824, 32, 67},
  {cont__34_294, &frame__34_242, 825, 825, 32, 61},
  {cont__34_295, &frame__34_242, 826, 826, 32, 58},
  {cont__34_296, &frame__34_242, 827, 827, 32, 58},
  {cont__34_297, &frame__34_242, 829, 829, 32, 48},
  {cont__34_298, &frame__34_242, 814, 829, 12, 49},
  {cont__34_312, &frame__34_242, 814, 829, 5, 49},
  {entry__34_1_sim2c__extract_documentation, NULL, 645, 645, 42, 42},
  {cont__34_20, &frame__34_1_sim2c__extract_documentation, 645, 645, 3, 43},
  {cont__34_21, &frame__34_1_sim2c__extract_documentation, 646, 646, 3, 43},
  {cont__34_22, &frame__34_1_sim2c__extract_documentation, 647, 661, 3, 44},
  {cont__34_54, &frame__34_1_sim2c__extract_documentation, 662, 685, 3, 33},
  {cont__34_94, &frame__34_1_sim2c__extract_documentation, 686, 739, 3, 44},
  {cont__34_182, &frame__34_1_sim2c__extract_documentation, 740, 745, 3, 67},
  {cont__34_192, &frame__34_1_sim2c__extract_documentation, 746, 752, 3, 43},
  {cont__34_208, &frame__34_1_sim2c__extract_documentation, 753, 760, 3, 75},
  {cont__34_225, &frame__34_1_sim2c__extract_documentation, 761, 766, 3, 50},
  {cont__34_241, &frame__34_1_sim2c__extract_documentation, 768, 829, 3, 50},
  {cont__34_313, &frame__34_1_sim2c__extract_documentation, 829, 829, 50, 50}
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
  frame->cont = cont__40_1;
}
static void cont__40_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 39: $$definitions empty_key_order_table
  var._definitions = get__empty_key_order_table();
  // 40: $$topics empty_key_order_table
  var._topics = get__empty_key_order_table();
  // 57: ... sim2c::WHITESPACE, '=', sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__sim2c__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__sim2c__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__52_1;
}
static void cont__52_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 57: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__52_2;
}
static void cont__52_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 58: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__52_3;
}
static void cont__52_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 58: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__52_4;
}
static void cont__52_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 58: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__52_5;
}
static void cont__52_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 56: sequence
  // 57:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 58:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__52_6;
}
static void cont__52_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 52: $PARAMETER_COUNT_OR_MYSELF
  // 53:   alt
  // 54:     '*'
  // 55:     '?'
  // 56:     sequence
  // 57:       alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 58:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__52_7;
}
static void cont__52_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 60: $$path_prefix undefined
  var._path_prefix = get__undefined();
  // 150: types::object $symbol_info
  // 151:   .kind_of BORING
  // 152:   .name_of undefined
  // 153:   .base_of undefined
  // 154:   .parameters_of undefined
  // 155:   .remark_lines_of undefined
  // 156:   .derived_types_of empty_key_order_set
  // 157:   .methods_of empty_key_order_table
  // 158:   .types_of empty_key_order_set
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
  // 369: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__64_1;
  arguments->slots[1] = string__64_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__64_3;
}
static void cont__64_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 369: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__64_4;
}
static void cont__64_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 370: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__65_1;
  arguments->slots[1] = string__65_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__65_3;
}
static void cont__65_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 370: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__65_4;
}
static void cont__65_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 370: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__65_5;
}
static void cont__65_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 370: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__65_6;
}
static void cont__65_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 370: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__65_7;
}
static void cont__65_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXAMPLE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1_create_page(void) {
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
  // 65: ... :
  // 66:   HTML:
  // 67:     HEAD:
  // 68:       STYLE "
  // 69:         body {
  // 70:           background-color: white;
  // 71:           font-family: Times New Roman, Times;
  // 72:           font-size: 12pt;
  // 73:           color: #222;
  // 74:         }
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__20_2, 0);
  // 65: collect_output $page:
  // 66:   HTML:
  // 67:     HEAD:
  // 68:       STYLE "
  // 69:         body {
  // 70:           background-color: white;
  // 71:           font-family: Times New Roman, Times;
  // 72:           font-size: 12pt;
  // 73:           color: #222;
  // 74:         }
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__20_7;
}
static void entry__20_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 67: HEAD:
  // 68:   STYLE "
  // 69:     body {
  // 70:       background-color: white;
  // 71:       font-family: Times New Roman, Times;
  // 72:       font-size: 12pt;
  // 73:       color: #222;
  // 74:     }
  // 75:     h1 {
  // 76:       font-family: Arial, Helvetica;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__20_4;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__20_6;
}
static void entry__20_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 68: STYLE "
  // 69:   body {
  // 70:     background-color: white;
  // 71:     font-family: Times New Roman, Times;
  // 72:     font-size: 12pt;
  // 73:     color: #222;
  // 74:   }
  // 75:   h1 {
  // 76:     font-family: Arial, Helvetica;
  // 77:     font-size: 20pt;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__20_5;
  result_count = frame->caller_result_count;
  myself = get__STYLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 147: BODY body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__BODY();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 66: ... :
  // 67:   HEAD:
  // 68:     STYLE "
  // 69:       body {
  // 70:         background-color: white;
  // 71:         font-family: Times New Roman, Times;
  // 72:         font-size: 12pt;
  // 73:         color: #222;
  // 74:       }
  // 75:       h1 {
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__20_3, 0);
  // 66: HTML:
  // 67:   HEAD:
  // 68:     STYLE "
  // 69:       body {
  // 70:         background-color: white;
  // 71:         font-family: Times New Roman, Times;
  // 72:         font-size: 12pt;
  // 73:         color: #222;
  // 74:       }
  // 75:       h1 {
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* page */, arguments->slots[0]);
  // 148: save filename page
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[2] /* page */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_1_extract_documentation_from_file(void) {
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
  // 161: ... "extracting documentation from @(filename)@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__22_2;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__22_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 161: ewrite "extracting documentation from @(filename)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 162: ... load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 162: $buf load(filename).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* buf */, arguments->slots[0]);
  // 163: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__22_8;
}
static void cont__22_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 163: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_9;
}
static void cont__22_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 163: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__22_10;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_12;
}
static void entry__22_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__22_11;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 164: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__22_13;
}
static void cont__22_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 164: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__22_14;
}
static void cont__22_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 164: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_15;
}
static void cont__22_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 164: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__22_16;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_18;
}
static void entry__22_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 164: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__22_17;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 165: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__22_19;
}
static void cont__22_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 165: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__22_20;
}
static void cont__22_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 165: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_21;
}
static void cont__22_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 165: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__22_22;
}
static void cont__22_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 165: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__22_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_25;
}
static void entry__22_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 165: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__22_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 168: ... filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__22_26;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__22_27;
}
static void cont__22_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 168: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__22_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__22_29;
}
static void cont__22_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 167: %sim2c::module_name
  // 168:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 169:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__22_30;
}
static void cont__22_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 171: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 172: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 173: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 174: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 175: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 176: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 177: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 178: $$fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__22_31;
}
static void cont__22_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 179: update_each &fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = func__22_32;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__22_34;
}
static void entry__22_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 179: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__22_33;
}
static void cont__22_33(void) {
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
static void cont__22_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 180: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 181: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 182: ... : (-> done)
  // 183:   for_each fragments: (idx fragment)
  // 184:     case
  // 185:       source_of(fragment)(1)
  // 186:       '#':
  // 187:         !first_idx idx+1 # ignore remark
  // 188:       '<':
  // 189:         !first_idx idx+1
  // 190:         parse_meta_instruction $_tree fragment
  // 191:       :
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__22_35, 0);
  // 182: do: (-> done)
  // 183:   for_each fragments: (idx fragment)
  // 184:     case
  // 185:       source_of(fragment)(1)
  // 186:       '#':
  // 187:         !first_idx idx+1 # ignore remark
  // 188:       '<':
  // 189:         !first_idx idx+1
  // 190:         parse_meta_instruction $_tree fragment
  // 191:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__22_46;
}
static void entry__22_35(void) {
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
  // 183: ... : (idx fragment)
  // 184:   case
  // 185:     source_of(fragment)(1)
  // 186:     '#':
  // 187:       !first_idx idx+1 # ignore remark
  // 188:     '<':
  // 189:       !first_idx idx+1
  // 190:       parse_meta_instruction $_tree fragment
  // 191:     :
  // 192:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__22_36, 2);
  // 183: for_each fragments: (idx fragment)
  // 184:   case
  // 185:     source_of(fragment)(1)
  // 186:     '#':
  // 187:       !first_idx idx+1 # ignore remark
  // 188:     '<':
  // 189:       !first_idx idx+1
  // 190:       parse_meta_instruction $_tree fragment
  // 191:     :
  // 192:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__22_45;
}
static void entry__22_39(void) {
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
  // 187: !first_idx idx+1 # ignore remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__22_40;
}
static void cont__22_40(void) {
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
static void entry__22_41(void) {
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
  // 189: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__22_42;
}
static void cont__22_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 190: parse_meta_instruction $_tree fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__22_43;
}
static void cont__22_43(void) {
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
static void entry__22_44(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 192: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_36(void) {
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
  // 185: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__22_37;
}
static void cont__22_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 185: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__22_38;
}
static void cont__22_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 186: ... :
  // 187:   !first_idx idx+1 # ignore remark
  frame->slots[6] /* temp__3 */ = create_closure(entry__22_39, 0);
  // 188: ... :
  // 189:   !first_idx idx+1
  // 190:   parse_meta_instruction $_tree fragment
  frame->slots[7] /* temp__4 */ = create_closure(entry__22_41, 0);
  // 191: :
  // 192:   done
  frame->slots[8] /* temp__5 */ = create_closure(entry__22_44, 0);
  // 184: case
  // 185:   source_of(fragment)(1)
  // 186:   '#':
  // 187:     !first_idx idx+1 # ignore remark
  // 188:   '<':
  // 189:     !first_idx idx+1
  // 190:     parse_meta_instruction $_tree fragment
  // 191:   :
  // 192:     done
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
static void cont__22_45(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__22_46(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 193: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__22_47;
}
static void cont__22_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 193: range &fragments first_idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__22_48;
}
static void cont__22_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 194: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__22_49, 1);
  // 194: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__22_52;
}
static void entry__22_49(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 194: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__22_50;
}
static void cont__22_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 194: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__22_51;
}
static void cont__22_51(void) {
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
static void cont__22_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 195: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__22_53;
}
static void cont__22_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 195: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__22_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_57;
}
static void entry__22_54(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 195: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__22_55;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__22_56;
}
static void cont__22_56(void) {
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
static void cont__22_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 196: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 197: ... : (statement)
  // 198:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 199:     $destination output_arguments_of(statement)(1)
  // 200:     if destination.is_a_definition:
  // 201:       $identifier identifier_of(destination)
  // 202:       unless namespace_of(identifier).is_defined:
  // 203:         $source arguments_of(statement)(1)
  // 204:         if source.is_a_polymorphic_function_constant:
  // 205:           !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[7] /* temp__1 */ = create_closure(entry__22_58, 1);
  // 197: for_each trees: (statement)
  // 198:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 199:     $destination output_arguments_of(statement)(1)
  // 200:     if destination.is_a_definition:
  // 201:       $identifier identifier_of(destination)
  // 202:       unless namespace_of(identifier).is_defined:
  // 203:         $source arguments_of(statement)(1)
  // 204:         if source.is_a_polymorphic_function_constant:
  // 205:           !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__22_83;
}
static void entry__22_79(void) {
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
  // 205: !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 205: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__22_80;
}
static void cont__22_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 205: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__22_81;
}
static void cont__22_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 205: !local_method_names(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__22_82;
}
static void cont__22_82(void) {
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
static void entry__22_75(void) {
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
  // 203: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__22_76;
}
static void cont__22_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 203: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__22_77;
}
static void cont__22_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 204: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__22_78;
}
static void cont__22_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 204: ... :
  // 205:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__22_79, 0);
  // 204: if source.is_a_polymorphic_function_constant:
  // 205:   !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_71(void) {
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
  // 201: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__22_72;
}
static void cont__22_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 202: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__22_73;
}
static void cont__22_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 202: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_74;
}
static void cont__22_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 202: ... :
  // 203:   $source arguments_of(statement)(1)
  // 204:   if source.is_a_polymorphic_function_constant:
  // 205:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__22_75, 0);
  // 202: unless namespace_of(identifier).is_defined:
  // 203:   $source arguments_of(statement)(1)
  // 204:   if source.is_a_polymorphic_function_constant:
  // 205:     !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_67(void) {
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
  // 199: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__22_68;
}
static void cont__22_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 199: $destination output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__22_69;
}
static void cont__22_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 200: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__22_70;
}
static void cont__22_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 200: ... :
  // 201:   $identifier identifier_of(destination)
  // 202:   unless namespace_of(identifier).is_defined:
  // 203:     $source arguments_of(statement)(1)
  // 204:     if source.is_a_polymorphic_function_constant:
  // 205:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_71, 0);
  // 200: if destination.is_a_definition:
  // 201:   $identifier identifier_of(destination)
  // 202:   unless namespace_of(identifier).is_defined:
  // 203:     $source arguments_of(statement)(1)
  // 204:     if source.is_a_polymorphic_function_constant:
  // 205:       !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_64(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_61(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__22_60;
}
static void cont__22_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 198: ... -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__22_61;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_62(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 198: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__22_63;
}
static void cont__22_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 198: ... -> statement.is_c_code: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__22_64;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_65(void) {
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
  // 198: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__22_66;
}
static void cont__22_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   $destination output_arguments_of(statement)(1)
  // 200:   if destination.is_a_definition:
  // 201:     $identifier identifier_of(destination)
  // 202:     unless namespace_of(identifier).is_defined:
  // 203:       $source arguments_of(statement)(1)
  // 204:       if source.is_a_polymorphic_function_constant:
  // 205:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__22_67, 0);
  // 198: ... -> statement.is_an_assignment:
  // 199:   $destination output_arguments_of(statement)(1)
  // 200:   if destination.is_a_definition:
  // 201:     $identifier identifier_of(destination)
  // 202:     unless namespace_of(identifier).is_defined:
  // 203:       $source arguments_of(statement)(1)
  // 204:       if source.is_a_polymorphic_function_constant:
  // 205:         !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_58(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 198: ... -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__22_59, 0);
  // 198: ... -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__22_62, 0);
  // 198: ... -> statement.is_an_assignment:
  // 199:   $destination output_arguments_of(statement)(1)
  // 200:   if destination.is_a_definition:
  // 201:     $identifier identifier_of(destination)
  // 202:     unless namespace_of(identifier).is_defined:
  // 203:       $source arguments_of(statement)(1)
  // 204:       if source.is_a_polymorphic_function_constant:
  // 205:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__22_65, 0);
  // 198: cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 199:   $destination output_arguments_of(statement)(1)
  // 200:   if destination.is_a_definition:
  // 201:     $identifier identifier_of(destination)
  // 202:     unless namespace_of(identifier).is_defined:
  // 203:       $source arguments_of(statement)(1)
  // 204:       if source.is_a_polymorphic_function_constant:
  // 205:         !local_method_names(name_of(identifier_of(destination))) true
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
static void cont__22_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 206: ... :
  // 207:   (
  // 208:     statement
  // 209:     -> break
  // 210:   )
  // 211:   cond
  // 212:     -> statement.is_a_remark: pass
  // 213:     -> statement.is_c_code:
  // 214:       if kind_of(statement) == "type":
  // 215:         $identifier identifier_of(statement)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__22_84, 1);
  // 206: for_each trees:
  // 207:   (
  // 208:     statement
  // 209:     -> break
  // 210:   )
  // 211:   cond
  // 212:     -> statement.is_a_remark: pass
  // 213:     -> statement.is_c_code:
  // 214:       if kind_of(statement) == "type":
  // 215:         $identifier identifier_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__22_198;
}
static void entry__22_84(void) {
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
  // 212: -> statement.is_a_remark: pass
  frame->slots[4] /* temp__1 */ = create_closure(entry__22_85, 0);
  // 213: -> statement.is_c_code:
  // 214:   if kind_of(statement) == "type":
  // 215:     $identifier identifier_of(statement)
  // 216:     $namespace namespace_of(identifier)
  // 217:     if namespace.is_defined:
  // 218:       $name name_of(identifier)
  // 219:       $base base_of(statement)
  // 220:       !definitions(ordered_name(namespace name))
  // 221:         symbol_info
  // 222:           .kind_of TYPE
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__22_88, 0);
  // 227: -> statement.is_an_assignment:
  // 228:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 229:   $$info symbol_info(.filename_of filename)
  // 230:   if destination.is_a_definition:
  // 231:     $identifier identifier_of(destination)
  // 232:     $namespace namespace_of(identifier)
  // 233:     if namespace.is_defined:
  // 234:       $name name_of(identifier)
  // 235:       $iname ordered_name(namespace name)
  // 236:       !info.name_of identifier.to_string
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__22_110, 0);
  // 211: cond
  // 212:   -> statement.is_a_remark: pass
  // 213:   -> statement.is_c_code:
  // 214:     if kind_of(statement) == "type":
  // 215:       $identifier identifier_of(statement)
  // 216:       $namespace namespace_of(identifier)
  // 217:       if namespace.is_defined:
  // 218:         $name name_of(identifier)
  // 219:         $base base_of(statement)
  // 220:         !definitions(ordered_name(namespace name))
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__22_197;
}
static void entry__22_187(void) {
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
  // 293: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__22_188;
}
static void cont__22_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 293: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_189;
}
static void cont__22_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 293: ... :
  // 294:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__22_190, 0);
  // 293: unless namespace_of(attr).is_defined:
  // 294:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__22_191;
}
static void entry__22_190(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 294: !attr.used_namespaces_of used_namespaces
  frame->slots[1] /* temp__1 */ = get__used_namespaces();
  // 294: !attr.used_namespaces_of
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
static void cont__22_191(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 295: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_192;
}
static void cont__22_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 295: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__22_193;
}
static void cont__22_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 296: !definition.kind_of TYPE
  frame->slots[5] /* temp__1 */ = var._TYPE;
  // 296: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 297: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 297: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__22_194;
}
static void cont__22_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 297: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__22_195;
}
static void cont__22_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 297: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 298: !definitions(iname) definition
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* definition */;
  // 298: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_196;
}
static void cont__22_196(void) {
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
static void entry__22_184(void) {
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
  // 291: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__22_185;
}
static void cont__22_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 292: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__22_186;
}
static void cont__22_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 292: ... :
  // 293:   unless namespace_of(attr).is_defined:
  // 294:     !attr.used_namespaces_of used_namespaces
  // 295:   $$definition default_value(definitions(iname) symbol_info)
  // 296:   !definition.kind_of TYPE
  // 297:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 298:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__22_187, 0);
  // 292: unless local_method_names(attr_name):
  // 293:   unless namespace_of(attr).is_defined:
  // 294:     !attr.used_namespaces_of used_namespaces
  // 295:   $$definition default_value(definitions(iname) symbol_info)
  // 296:   !definition.kind_of TYPE
  // 297:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 298:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_178(void) {
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
  // 284: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__22_179;
}
static void cont__22_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 287: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_180;
}
static void cont__22_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 287: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__22_181;
}
static void cont__22_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 286: $type
  // 287:   default_value(definitions(iname) symbol_info)(.kind_of TYPE)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 289: !definitions(iname) type
  frame->slots[6] /* temp__1 */ = frame->slots[5] /* type */;
  // 289: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_182;
}
static void cont__22_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 290: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_183;
}
static void cont__22_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 290: ... :
  // 291:   $attr_name attr.to_string
  // 292:   unless local_method_names(attr_name):
  // 293:     unless namespace_of(attr).is_defined:
  // 294:       !attr.used_namespaces_of used_namespaces
  // 295:     $$definition default_value(definitions(iname) symbol_info)
  // 296:     !definition.kind_of TYPE
  // 297:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 298:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__22_184, 0);
  // 290: if attr.is_defined:
  // 291:   $attr_name attr.to_string
  // 292:   unless local_method_names(attr_name):
  // 293:     unless namespace_of(attr).is_defined:
  // 294:       !attr.used_namespaces_of used_namespaces
  // 295:     $$definition default_value(definitions(iname) symbol_info)
  // 296:     !definition.kind_of TYPE
  // 297:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 298:     !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_120(void) {
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
  // 234: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__22_121;
}
static void cont__22_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* name */, arguments->slots[0]);
  // 235: $iname ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[7] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__22_122;
}
static void cont__22_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* iname */, arguments->slots[0]);
  // 236: !info.name_of identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__22_123;
}
static void cont__22_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 236: !info.name_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[10] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 237: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__22_124;
}
static void cont__22_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 237: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__22_125;
}
static void cont__22_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* source */, arguments->slots[0]);
  // 239: -> source.is_a_polymorphic_function_constant:
  // 240:   !polymorphic_functions(name namespace) true
  // 241:   !definitions(iname)
  // 242:     info
  // 243:       .kind_of
  // 244:         if
  // 245:           source.is_a_setter
  // 246:           -> POLYMORPHIC_ATTRIBUTE
  // 247:           -> POLYMORPHIC_FUNCTION
  // 248:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[10] /* temp__1 */ = create_closure(entry__22_126, 0);
  // 250: -> source.is_a_body:
  // 251:   !info.base_of "types::function"
  // 252:   !info.kind_of FUNCTION
  // 253:   !info.parameters_of parameters_of(source)
  // 254:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[11] /* temp__2 */ = create_closure(entry__22_136, 0);
  // 255: -> source.is_a_c_body:
  // 256:   !info.kind_of INLINE_C_FUNCTION
  // 257:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[12] /* temp__3 */ = create_closure(entry__22_142, 0);
  // 258: -> source.is_an_identifier:
  // 259:   if namespace_of(source).is_defined:
  // 260:     !info
  // 261:       .base_of source.to_string
  // 262:       .remark_lines_of remark_lines_of(statement)
  frame->slots[13] /* temp__4 */ = create_closure(entry__22_146, 0);
  // 263: -> source.is_a_constant:
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_unique_item_constant
  // 269:           -> UNIQUE_ITEM
  // 270:           -> CONSTANT
  // 271:       .remark_lines_of remark_lines_of(statement)
  // 272:   break
  frame->slots[14] /* temp__5 */ = create_closure(entry__22_154, 0);
  // 238: cond
  // 239:   -> source.is_a_polymorphic_function_constant:
  // 240:     !polymorphic_functions(name namespace) true
  // 241:     !definitions(iname)
  // 242:       info
  // 243:         .kind_of
  // 244:           if
  // 245:             source.is_a_setter
  // 246:             -> POLYMORPHIC_ATTRIBUTE
  // 247:             -> POLYMORPHIC_FUNCTION
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
  frame->cont = cont__22_163;
}
static void entry__22_156(void) {
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
  // 268: source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__22_157;
}
static void cont__22_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 267: if
  // 268:   source.is_a_unique_item_constant
  // 269:   -> UNIQUE_ITEM
  // 270:   -> CONSTANT
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = func__22_158;
  arguments->slots[2] = func__22_159;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_160;
}
static void entry__22_158(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 269: -> UNIQUE_ITEM
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._UNIQUE_ITEM;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_159(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 270: -> CONSTANT
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._CONSTANT;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 271: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_161;
}
static void cont__22_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__3 */ = arguments->slots[0];
  // 264: !definitions(iname)
  // 265:   info
  // 266:     .kind_of
  // 267:       if
  // 268:         source.is_a_unique_item_constant
  // 269:         -> UNIQUE_ITEM
  // 270:         -> CONSTANT
  // 271:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[7] /* temp__3 */);
    frame->slots[8] /* temp__4 */ = temp;

  }
  // 264: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_162;
}
static void cont__22_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 272: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[4] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_151(void) {
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
  // 261: ... source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__22_152;
}
static void cont__22_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 262: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_153;
}
static void cont__22_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 260: !info
  // 261:   .base_of source.to_string
  // 262:   .remark_lines_of remark_lines_of(statement)
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
static void entry__22_148(void) {
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
  // 259: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__22_149;
}
static void cont__22_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 259: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_150;
}
static void cont__22_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 259: ... :
  // 260:   !info
  // 261:     .base_of source.to_string
  // 262:     .remark_lines_of remark_lines_of(statement)
  frame->slots[5] /* temp__3 */ = create_closure(entry__22_151, 0);
  // 259: if namespace_of(source).is_defined:
  // 260:   !info
  // 261:     .base_of source.to_string
  // 262:     .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_144(void) {
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
  // 256: !info.kind_of INLINE_C_FUNCTION
  frame->slots[2] /* temp__1 */ = var._INLINE_C_FUNCTION;
  // 256: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 257: !info.remark_lines_of remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_145;
}
static void cont__22_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 257: !info.remark_lines_of
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
static void entry__22_138(void) {
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
  // 251: !info.base_of "types::function"
  frame->slots[2] /* temp__1 */ = string__22_139;
  // 251: !info.base_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 252: !info.kind_of FUNCTION
  frame->slots[2] /* temp__1 */ = var._FUNCTION;
  // 252: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 253: !info.parameters_of parameters_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__22_140;
}
static void cont__22_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 253: !info.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 254: !info.remark_lines_of remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_141;
}
static void cont__22_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 254: !info.remark_lines_of
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
static void entry__22_128(void) {
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
  // 240: !polymorphic_functions(name namespace) true
  frame->slots[7] /* temp__1 */ = get__true();
  // 240: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__22_129;
}
static void cont__22_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 245: source.is_a_setter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* source */;
  result_count = 1;
  myself = get__is_a_setter();
  func = myself->type;
  frame->cont = cont__22_130;
}
static void cont__22_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 244: if
  // 245:   source.is_a_setter
  // 246:   -> POLYMORPHIC_ATTRIBUTE
  // 247:   -> POLYMORPHIC_FUNCTION
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = func__22_131;
  arguments->slots[2] = func__22_132;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_133;
}
static void entry__22_131(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 246: -> POLYMORPHIC_ATTRIBUTE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_ATTRIBUTE;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_132(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 247: -> POLYMORPHIC_FUNCTION
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._POLYMORPHIC_FUNCTION;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 248: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_134;
}
static void cont__22_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 241: !definitions(iname)
  // 242:   info
  // 243:     .kind_of
  // 244:       if
  // 245:         source.is_a_setter
  // 246:         -> POLYMORPHIC_ATTRIBUTE
  // 247:         -> POLYMORPHIC_FUNCTION
  // 248:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[7] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[9] /* temp__3 */);
    frame->slots[10] /* temp__4 */ = temp;

  }
  // 241: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_135;
}
static void cont__22_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 249: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[6] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_126(void) {
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
  // 239: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__22_127;
}
static void cont__22_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 239: ... :
  // 240:   !polymorphic_functions(name namespace) true
  // 241:   !definitions(iname)
  // 242:     info
  // 243:       .kind_of
  // 244:         if
  // 245:           source.is_a_setter
  // 246:           -> POLYMORPHIC_ATTRIBUTE
  // 247:           -> POLYMORPHIC_FUNCTION
  // 248:       .remark_lines_of remark_lines_of(statement)
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__22_128, 0);
  // 239: -> source.is_a_polymorphic_function_constant:
  // 240:   !polymorphic_functions(name namespace) true
  // 241:   !definitions(iname)
  // 242:     info
  // 243:       .kind_of
  // 244:         if
  // 245:           source.is_a_setter
  // 246:           -> POLYMORPHIC_ATTRIBUTE
  // 247:           -> POLYMORPHIC_FUNCTION
  // 248:       .remark_lines_of remark_lines_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_136(void) {
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
  // 250: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__22_137;
}
static void cont__22_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 250: ... :
  // 251:   !info.base_of "types::function"
  // 252:   !info.kind_of FUNCTION
  // 253:   !info.parameters_of parameters_of(source)
  // 254:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[3] /* temp__2 */ = create_closure(entry__22_138, 0);
  // 250: -> source.is_a_body:
  // 251:   !info.base_of "types::function"
  // 252:   !info.kind_of FUNCTION
  // 253:   !info.parameters_of parameters_of(source)
  // 254:   !info.remark_lines_of remark_lines_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_142(void) {
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
  // 255: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__22_143;
}
static void cont__22_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 255: ... :
  // 256:   !info.kind_of INLINE_C_FUNCTION
  // 257:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_144, 0);
  // 255: -> source.is_a_c_body:
  // 256:   !info.kind_of INLINE_C_FUNCTION
  // 257:   !info.remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_146(void) {
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
  // 258: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__22_147;
}
static void cont__22_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 258: ... :
  // 259:   if namespace_of(source).is_defined:
  // 260:     !info
  // 261:       .base_of source.to_string
  // 262:       .remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_148, 0);
  // 258: -> source.is_an_identifier:
  // 259:   if namespace_of(source).is_defined:
  // 260:     !info
  // 261:       .base_of source.to_string
  // 262:       .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_154(void) {
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
  // 263: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__22_155;
}
static void cont__22_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 263: ... :
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_unique_item_constant
  // 269:           -> UNIQUE_ITEM
  // 270:           -> CONSTANT
  // 271:       .remark_lines_of remark_lines_of(statement)
  // 272:   break
  frame->slots[6] /* temp__2 */ = create_closure(entry__22_156, 0);
  // 263: -> source.is_a_constant:
  // 264:   !definitions(iname)
  // 265:     info
  // 266:       .kind_of
  // 267:         if
  // 268:           source.is_a_unique_item_constant
  // 269:           -> UNIQUE_ITEM
  // 270:           -> CONSTANT
  // 271:       .remark_lines_of remark_lines_of(statement)
  // 272:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_163(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 274: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__22_164;
}
static void cont__22_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 275: ... :
  // 276:   $previous_definition definitions(iname)
  // 277:   if previous_definition.is_defined:
  // 278:     if kind_of(previous_definition) == TYPE:
  // 279:       !info.types_of types_of(previous_definition)
  // 280:       !info.derived_types_of derived_types_of(previous_definition)
  // 281:       !info.methods_of methods_of(previous_definition)
  // 282:   !definitions(iname) info
  frame->slots[11] /* temp__2 */ = create_closure(entry__22_165, 0);
  // 283: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__22_177;
}
static void entry__22_165(void) {
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
  // 276: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_166;
}
static void cont__22_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 277: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_167;
}
static void cont__22_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 277: ... :
  // 278:   if kind_of(previous_definition) == TYPE:
  // 279:     !info.types_of types_of(previous_definition)
  // 280:     !info.derived_types_of derived_types_of(previous_definition)
  // 281:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__22_168, 0);
  // 277: if previous_definition.is_defined:
  // 278:   if kind_of(previous_definition) == TYPE:
  // 279:     !info.types_of types_of(previous_definition)
  // 280:     !info.derived_types_of derived_types_of(previous_definition)
  // 281:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_175;
}
static void entry__22_171(void) {
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
  // 279: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__22_172;
}
static void cont__22_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 279: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 280: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__22_173;
}
static void cont__22_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 280: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 281: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__22_174;
}
static void cont__22_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 281: !info.methods_of
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
static void entry__22_168(void) {
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
  // 278: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__22_169;
}
static void cont__22_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 278: ... kind_of(previous_definition) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_170;
}
static void cont__22_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 278: ... :
  // 279:   !info.types_of types_of(previous_definition)
  // 280:   !info.derived_types_of derived_types_of(previous_definition)
  // 281:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__22_171, 0);
  // 278: if kind_of(previous_definition) == TYPE:
  // 279:   !info.types_of types_of(previous_definition)
  // 280:   !info.derived_types_of derived_types_of(previous_definition)
  // 281:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__22_175(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 282: !definitions(iname) info
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* info */;
  // 282: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_176;
}
static void cont__22_176(void) {
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
static void cont__22_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 283: ... :
  // 284:   $$attr attribute_of(destination)
  // 285:   
  // 286:   $type
  // 287:     default_value(definitions(iname) symbol_info)(.kind_of TYPE)
  // 288:   
  // 289:   !definitions(iname) type
  // 290:   if attr.is_defined:
  // 291:     $attr_name attr.to_string
  // 292:     unless local_method_names(attr_name):
  // ...
  frame->slots[13] /* temp__4 */ = create_closure(entry__22_178, 0);
  // 273: case
  // 274:   attribute_kind_of(destination)
  // 275:   NONE:
  // 276:     $previous_definition definitions(iname)
  // 277:     if previous_definition.is_defined:
  // 278:       if kind_of(previous_definition) == TYPE:
  // 279:         !info.types_of types_of(previous_definition)
  // 280:         !info.derived_types_of derived_types_of(previous_definition)
  // 281:         !info.methods_of methods_of(previous_definition)
  // 282:     !definitions(iname) info
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
static void entry__22_116(void) {
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
  // 231: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__22_117;
}
static void cont__22_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* identifier */, arguments->slots[0]);
  // 232: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__22_118;
}
static void cont__22_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* namespace */, arguments->slots[0]);
  // 233: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_119;
}
static void cont__22_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 233: ... :
  // 234:   $name name_of(identifier)
  // 235:   $iname ordered_name(namespace name)
  // 236:   !info.name_of identifier.to_string
  // 237:   $source arguments_of(statement)(1)
  // 238:   cond
  // 239:     -> source.is_a_polymorphic_function_constant:
  // 240:       !polymorphic_functions(name namespace) true
  // 241:       !definitions(iname)
  // 242:         info
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__22_120, 0);
  // 233: if namespace.is_defined:
  // 234:   $name name_of(identifier)
  // 235:   $iname ordered_name(namespace name)
  // 236:   !info.name_of identifier.to_string
  // 237:   $source arguments_of(statement)(1)
  // 238:   cond
  // 239:     -> source.is_a_polymorphic_function_constant:
  // 240:       !polymorphic_functions(name namespace) true
  // 241:       !definitions(iname)
  // 242:         info
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
static void entry__22_112(void) {
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
  // 228: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__22_113;
}
static void cont__22_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 228: ... output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__22_114;
}
static void cont__22_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 228: $destination output_arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 229: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 230: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__22_115;
}
static void cont__22_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 230: ... :
  // 231:   $identifier identifier_of(destination)
  // 232:   $namespace namespace_of(identifier)
  // 233:   if namespace.is_defined:
  // 234:     $name name_of(identifier)
  // 235:     $iname ordered_name(namespace name)
  // 236:     !info.name_of identifier.to_string
  // 237:     $source arguments_of(statement)(1)
  // 238:     cond
  // 239:       -> source.is_a_polymorphic_function_constant:
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__22_116, 0);
  // 230: if destination.is_a_definition:
  // 231:   $identifier identifier_of(destination)
  // 232:   $namespace namespace_of(identifier)
  // 233:   if namespace.is_defined:
  // 234:     $name name_of(identifier)
  // 235:     $iname ordered_name(namespace name)
  // 236:     !info.name_of identifier.to_string
  // 237:     $source arguments_of(statement)(1)
  // 238:     cond
  // 239:       -> source.is_a_polymorphic_function_constant:
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
static void entry__22_98(void) {
  allocate_initialized_frame_gc(4, 13);
  // slot allocations:
  // identifier: 0
  // statement: 1
  // namespace: 2
  // filename: 3
  // name: 4
  // base: 5
  frame->slots[0] = myself->closure.frame->slots[2]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[2] = myself->closure.frame->slots[3]; /* namespace */
  frame->slots[3] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[4] /* name */ = create_future();
  frame->slots[5] /* base */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 218: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__22_99;
}
static void cont__22_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 219: $base base_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__22_100;
}
static void cont__22_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* base */, arguments->slots[0]);
  // 223: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__22_101;
}
static void cont__22_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 224: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_102;
}
static void cont__22_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 224: ... -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__22_103, 0);
  // 224: ... if(base.is_defined (-> base.to_string) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = func__22_105;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__22_106;
}
static void entry__22_103(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* base */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__22_104;
}
static void cont__22_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 224: ... -> base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_105(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 224: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 225: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__22_107;
}
static void cont__22_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 220: !definitions(ordered_name(namespace name))
  // 221:   symbol_info
  // 222:     .kind_of TYPE
  // 223:     .name_of identifier.to_string
  // 224:     .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 225:     .remark_lines_of remark_lines_of(statement)
  // 226:     .filename_of filename
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._TYPE);
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[6] /* temp__1 */);
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[7] /* temp__2 */);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[10] /* temp__5 */);
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[3] /* filename */);
    frame->slots[11] /* temp__6 */ = temp;

  }
  // 220: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[4] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__22_108;
}
static void cont__22_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 220: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[11] /* temp__6 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__22_109;
}
static void cont__22_109(void) {
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
static void entry__22_94(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // statement: 0
  // filename: 1
  // identifier: 2
  // namespace: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filename */
  frame->slots[2] /* identifier */ = create_future();
  frame->slots[3] /* namespace */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 215: $identifier identifier_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__22_95;
}
static void cont__22_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 216: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__22_96;
}
static void cont__22_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 217: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__22_97;
}
static void cont__22_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 217: ... :
  // 218:   $name name_of(identifier)
  // 219:   $base base_of(statement)
  // 220:   !definitions(ordered_name(namespace name))
  // 221:     symbol_info
  // 222:       .kind_of TYPE
  // 223:       .name_of identifier.to_string
  // 224:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 225:       .remark_lines_of remark_lines_of(statement)
  // 226:       .filename_of filename
  frame->slots[5] /* temp__2 */ = create_closure(entry__22_98, 0);
  // 217: if namespace.is_defined:
  // 218:   $name name_of(identifier)
  // 219:   $base base_of(statement)
  // 220:   !definitions(ordered_name(namespace name))
  // 221:     symbol_info
  // 222:       .kind_of TYPE
  // 223:       .name_of identifier.to_string
  // 224:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 225:       .remark_lines_of remark_lines_of(statement)
  // 226:       .filename_of filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_90(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // filename: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  frame->slots[1] = myself->closure.frame->slots[1]; /* filename */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 214: ... kind_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__22_91;
}
static void cont__22_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 214: ... kind_of(statement) == "type"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = string__22_92;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__22_93;
}
static void cont__22_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 214: ... :
  // 215:   $identifier identifier_of(statement)
  // 216:   $namespace namespace_of(identifier)
  // 217:   if namespace.is_defined:
  // 218:     $name name_of(identifier)
  // 219:     $base base_of(statement)
  // 220:     !definitions(ordered_name(namespace name))
  // 221:       symbol_info
  // 222:         .kind_of TYPE
  // 223:         .name_of identifier.to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__22_94, 0);
  // 214: if kind_of(statement) == "type":
  // 215:   $identifier identifier_of(statement)
  // 216:   $namespace namespace_of(identifier)
  // 217:   if namespace.is_defined:
  // 218:     $name name_of(identifier)
  // 219:     $base base_of(statement)
  // 220:     !definitions(ordered_name(namespace name))
  // 221:       symbol_info
  // 222:         .kind_of TYPE
  // 223:         .name_of identifier.to_string
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_87(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_85(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 212: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__22_86;
}
static void cont__22_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 212: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__22_87;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_88(void) {
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
  // 213: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__22_89;
}
static void cont__22_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   if kind_of(statement) == "type":
  // 215:     $identifier identifier_of(statement)
  // 216:     $namespace namespace_of(identifier)
  // 217:     if namespace.is_defined:
  // 218:       $name name_of(identifier)
  // 219:       $base base_of(statement)
  // 220:       !definitions(ordered_name(namespace name))
  // 221:         symbol_info
  // 222:           .kind_of TYPE
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__22_90, 0);
  // 213: -> statement.is_c_code:
  // 214:   if kind_of(statement) == "type":
  // 215:     $identifier identifier_of(statement)
  // 216:     $namespace namespace_of(identifier)
  // 217:     if namespace.is_defined:
  // 218:       $name name_of(identifier)
  // 219:       $base base_of(statement)
  // 220:       !definitions(ordered_name(namespace name))
  // 221:         symbol_info
  // 222:           .kind_of TYPE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__22_110(void) {
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
  // 227: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__22_111;
}
static void cont__22_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 227: ... :
  // 228:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 229:   $$info symbol_info(.filename_of filename)
  // 230:   if destination.is_a_definition:
  // 231:     $identifier identifier_of(destination)
  // 232:     $namespace namespace_of(identifier)
  // 233:     if namespace.is_defined:
  // 234:       $name name_of(identifier)
  // 235:       $iname ordered_name(namespace name)
  // 236:       !info.name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__22_112, 0);
  // 227: -> statement.is_an_assignment:
  // 228:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 229:   $$info symbol_info(.filename_of filename)
  // 230:   if destination.is_a_definition:
  // 231:     $identifier identifier_of(destination)
  // 232:     $namespace namespace_of(identifier)
  // 233:     if namespace.is_defined:
  // 234:       $name name_of(identifier)
  // 235:       $iname ordered_name(namespace name)
  // 236:       !info.name_of identifier.to_string
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__22_197(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__22_198(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__23_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: ... extract_documentation_from_file name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 304: ... extract_documentation_from_directory name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_6(void) {
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
  // 304: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__23_7;
}
static void cont__23_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 304: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__23_8, 0);
  // 304: -> entry.is_a_directory: extract_documentation_from_directory name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 305: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__22_26;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__23_10;
}
static void cont__23_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 305: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__23_11, 0);
  // 305: -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 302: $name fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__23_5;
}
static void cont__23_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 304: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__23_6, 0);
  // 305: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__23_9, 0);
  // 303: cond
  // 304:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 305:   -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__23_1_extract_documentation_from_directory(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 301: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 301: ... directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 301: for_each directory(--SORT path): (entry)
  // 302:   $name fullname_of(entry)
  // 303:   cond
  // 304:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 305:     -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__23_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 309: ... attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__24_6;
}
static void cont__24_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 309: ... -> attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_7(void) {
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
  // 310: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 311: ... used_namespaces_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = var._used_namespaces_of;
  func = myself->type;
  frame->cont = cont__24_8;
}
static void cont__24_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 311: ... : (namespace)
  // 312:   if polymorphic_functions(name namespace):
  // 313:     if resolved_namespace.is_defined:
  // 314:       Error "
  // 315:         The attribute "@(name)" cannot be uniquely resolved!
  // 316:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_9, 1);
  // 311: for_each used_namespaces_of(attr): (namespace)
  // 312:   if polymorphic_functions(name namespace):
  // 313:     if resolved_namespace.is_defined:
  // 314:       Error "
  // 315:         The attribute "@(name)" cannot be uniquely resolved!
  // 316:     !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__24_18;
}
static void entry__24_11(void) {
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
  // 313: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_12;
}
static void cont__24_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 313: ... :
  // 314:   Error "
  // 315:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_13, 0);
  // 313: if resolved_namespace.is_defined:
  // 314:   Error "
  // 315:     The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__24_17;
}
static void entry__24_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 314: ... "
  // 315:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__24_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__24_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void cont__24_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 314: Error "
  // 315:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 316: !resolved_namespace namespace
  ((CELL *)frame->slots[0])->contents /* resolved_namespace */ = frame->slots[2] /* namespace */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_9(void) {
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
  // 312: ... polymorphic_functions(name namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__24_10;
}
static void cont__24_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 312: ... :
  // 313:   if resolved_namespace.is_defined:
  // 314:     Error "
  // 315:       The attribute "@(name)" cannot be uniquely resolved!
  // 316:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_11, 0);
  // 312: if polymorphic_functions(name namespace):
  // 313:   if resolved_namespace.is_defined:
  // 314:     Error "
  // 315:       The attribute "@(name)" cannot be uniquely resolved!
  // 316:   !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 317: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_19;
}
static void cont__24_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 317: ... :
  // 318:   Error "
  // 319:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__24_20, 0);
  // 317: unless resolved_namespace.is_defined:
  // 318:   Error "
  // 319:     The attribute "@(name)" cannot be resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void entry__24_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 318: ... "
  // 319:   The attribute "@(name)" cannot be resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__24_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__24_21;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__24_22;
}
static void cont__24_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 318: Error "
  // 319:   The attribute "@(name)" cannot be resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__24_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 320: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__24_24;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__24_25;
}
static void cont__24_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 320: -> string(resolved_namespace "::" name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_1_resolved_name(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // attr: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 308: $name name_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__24_2;
}
static void cont__24_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 309: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__24_3;
}
static void cont__24_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 309: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__24_4;
}
static void cont__24_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 309: ... -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__24_5, 0);
  // 309: ... :
  // 310:   $$resolved_namespace undefined
  // 311:   for_each used_namespaces_of(attr): (namespace)
  // 312:     if polymorphic_functions(name namespace):
  // 313:       if resolved_namespace.is_defined:
  // 314:         Error "
  // 315:           The attribute "@(name)" cannot be uniquely resolved!
  // 316:       !resolved_namespace namespace
  // 317:   unless resolved_namespace.is_defined:
  // 318:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__24_7, 0);
  // 309: if namespace_of(attr).is_defined (-> attr.to_string):
  // 310:   $$resolved_namespace undefined
  // 311:   for_each used_namespaces_of(attr): (namespace)
  // 312:     if polymorphic_functions(name namespace):
  // 313:       if resolved_namespace.is_defined:
  // 314:         Error "
  // 315:           The attribute "@(name)" cannot be uniquely resolved!
  // 316:       !resolved_namespace namespace
  // 317:   unless resolved_namespace.is_defined:
  // 318:     Error "
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
static void entry__25_7(void) {
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
  // 326: !definition.derived_types_of(name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 326: ... definition.derived_types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__25_8;
}
static void cont__25_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 326: !definition.derived_types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__25_9;
}
static void cont__25_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 326: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 327: ... kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void cont__25_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 327: ... kind_of(definition) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void cont__25_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 327: ... :
  // 328:   !definition.kind_of TYPE
  // 329:   $base_of_base base_of(definition)
  // 330:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__25_12, 0);
  // 327: unless kind_of(definition) == TYPE:
  // 328:   !definition.kind_of TYPE
  // 329:   $base_of_base base_of(definition)
  // 330:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_16;
}
static void entry__25_15(void) {
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
  // 330: ... add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base_of_base */;
  arguments->slots[1] = frame->slots[1] /* ibase */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_12(void) {
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
  // 328: !definition.kind_of TYPE
  frame->slots[3] /* temp__1 */ = var._TYPE;
  // 328: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 329: $base_of_base base_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base_of_base */, arguments->slots[0]);
  // 330: ... base_of_base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base_of_base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 330: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_15, 0);
  // 330: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 331: !definitions(ibase) definition
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* definition */;
  // 331: !definitions(ibase)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_17;
}
static void cont__25_17(void) {
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
static void entry__25_1_add_derived_type(void) {
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
  // 323: ... base .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 323: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__25_3;
}
static void cont__25_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 323: $ibase ordered_name(base .before. "::" base .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ibase */, arguments->slots[0]);
  // 324: $$definition definitions(ibase)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* definition */ = arguments->slots[0];
  // 325: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__25_6;
}
static void cont__25_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 325: ... :
  // 326:   !definition.derived_types_of(name) true
  // 327:   unless kind_of(definition) == TYPE:
  // 328:     !definition.kind_of TYPE
  // 329:     $base_of_base base_of(definition)
  // 330:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 331:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__25_7, 0);
  // 325: if definition.is_defined:
  // 326:   !definition.derived_types_of(name) true
  // 327:   unless kind_of(definition) == TYPE:
  // 328:     !definition.kind_of TYPE
  // 329:     $base_of_base base_of(definition)
  // 330:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 331:   !definitions(ibase) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__26_1_mangled(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 333: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_24;
  arguments->slots[1] = string__22_28;
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
  // 333: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__26_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__26_4;
}
static void cont__26_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 333: ... replace_all(name "::" = "__" '/' = "___")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__26_5;
}
static void cont__26_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 333: ... -> replace_all(name "::" = "__" '/' = "___")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__27_1_ordered_name(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 338: name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__27_2;
}
static void cont__27_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 340: namespace.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__27_3;
}
static void cont__27_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 337: string
  // 338:   name.to_lower_case
  // 339:   '/'
  // 340:   namespace.to_lower_case
  // 341:   '/'
  // 342:   name
  // 343:   '/'
  // 344:   namespace
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
  frame->cont = cont__27_4;
}
static void cont__27_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 336: ->
  // 337:   string
  // 338:     name.to_lower_case
  // 339:     '/'
  // 340:     namespace.to_lower_case
  // 341:     '/'
  // 342:     name
  // 343:     '/'
  // 344:     namespace
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: ... "href" = "index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_5;
}
static void cont__28_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 348: A "href" = "index.html" "Home"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_6;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__28_7;
}
static void cont__28_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 349: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__28_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 350: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_11;
}
static void cont__28_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 350: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_12;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void cont__28_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 351: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__28_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__28_14;
}
static void cont__28_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_16;
}
static void cont__28_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 352: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_17;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__28_18;
}
static void cont__28_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__28_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__28_19;
}
static void cont__28_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 354: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_21;
}
static void cont__28_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 354: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_22;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__28_23;
}
static void cont__28_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 355: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__28_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__28_24;
}
static void cont__28_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 356: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__28_26;
}
static void cont__28_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 356: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_1_link_bar(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 347: P:
  // 348:   A "href" = "index.html" "Home"
  // 349:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 350:   A "href" = "manual.html" "Manual"
  // 351:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 352:   A "href" = "type_index.html" "Type Index"
  // 353:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 354:   A "href" = "symbol_index.html" "Symbol Index"
  // 355:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 356:   A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__28_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_1_resolve_reference(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 360: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 360: ... :
  // 361:   $$type_name reference .before. '/'
  // 362:   $$method_name reference .behind. '/'
  // 363:   unless type_name .contains. "::": append "types::" &type_name
  // 364:   unless method_name .contains. "::": append "std::" &method_name
  // 365:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_3, 0);
  // 366: :
  // 367:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__29_17, 0);
  // 359: if
  // 360:   reference .contains. '/':
  // 361:     $$type_name reference .before. '/'
  // 362:     $$method_name reference .behind. '/'
  // 363:     unless type_name .contains. "::": append "types::" &type_name
  // 364:     unless method_name .contains. "::": append "std::" &method_name
  // 365:     !reference string(type_name '/' method_name)
  // 366:   :
  // 367:     unless reference .contains. "::": append "std::" &reference
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
  frame->cont = cont__29_21;
}
static void entry__29_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_20;
}
static void cont__29_20(void) {
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
static void entry__29_3(void) {
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
  // 361: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 362: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_5;
}
static void cont__29_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 363: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_6;
}
static void cont__29_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 363: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_7, 0);
  // 363: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_10;
}
static void entry__29_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 363: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_8;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_9;
}
static void cont__29_9(void) {
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
static void cont__29_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 364: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_11;
}
static void cont__29_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 364: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_12, 0);
  // 364: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_15;
}
static void entry__29_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 364: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_14;
}
static void cont__29_14(void) {
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
static void cont__29_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 365: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_16;
}
static void cont__29_16(void) {
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
static void entry__29_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 367: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_18;
}
static void cont__29_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 367: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_19, 0);
  // 367: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_21(void) {
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
static void entry__32_1_to_paragraphs(void) {
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
  // 373: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 374: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 375: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 376: ... : (line)
  // 377:   if
  // 378:     pre_mode:
  // 379:       if
  // 380:         line .has_prefix. EXAMPLE:
  // 381:           trim &text
  // 382:           push &paragraphs text
  // 383:           !text line
  // 384:         :
  // 385:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__32_2, 1);
  // 376: for_each lines: (line)
  // 377:   if
  // 378:     pre_mode:
  // 379:       if
  // 380:         line .has_prefix. EXAMPLE:
  // 381:           trim &text
  // 382:           push &paragraphs text
  // 383:           !text line
  // 384:         :
  // 385:           writeln_to &text line
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__32_27;
}
static void entry__32_15(void) {
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
  // 390: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__32_16;
}
static void cont__32_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  // 391: !text ""
  ((CELL *)frame->slots[1])->contents /* text */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_12(void) {
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
  // 389: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_13;
}
static void cont__32_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 389: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__32_14;
}
static void cont__32_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 389: ... :
  // 390:   push &paragraphs text
  // 391:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__32_15, 0);
  // 389: if text != "":
  // 390:   push &paragraphs text
  // 391:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_17(void) {
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
  // 394: text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_18;
}
static void cont__32_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 394: ... :
  // 395:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__32_19, 0);
  // 396: :
  // 397:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__32_22, 0);
  // 393: if
  // 394:   text == "":
  // 395:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 396:   :
  // 397:     push &text ' '
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_24;
}
static void entry__32_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pre_mode: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 395: ... !pre_mode true
  ((CELL *)frame->slots[0])->contents /* pre_mode */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_19(void) {
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
  // 395: ... line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__32_20;
}
static void cont__32_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 395: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__32_21, 0);
  // 395: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__32_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 397: push &text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__32_23;
}
static void cont__32_23(void) {
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
static void cont__32_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 398: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__32_25;
}
static void cont__32_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 398: append &text line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__32_26;
}
static void cont__32_26(void) {
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
static void entry__32_5(void) {
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
  // 381: trim &text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__32_6;
}
static void cont__32_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 382: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__32_7;
}
static void cont__32_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = arguments->slots[0];
  // 383: !text line
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[2] /* line */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__32_8(void) {
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
  // 385: writeln_to &text line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__32_9;
}
static void cont__32_9(void) {
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
static void entry__32_3(void) {
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
  // 380: line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__32_4;
}
static void cont__32_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 380: ... :
  // 381:   trim &text
  // 382:   push &paragraphs text
  // 383:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__32_5, 0);
  // 384: :
  // 385:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__32_8, 0);
  // 379: if
  // 380:   line .has_prefix. EXAMPLE:
  // 381:     trim &text
  // 382:     push &paragraphs text
  // 383:     !text line
  // 384:   :
  // 385:     writeln_to &text line
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
static void entry__32_10(void) {
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
  // 388: line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_11;
}
static void cont__32_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 388: ... :
  // 389:   if text != "":
  // 390:     push &paragraphs text
  // 391:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__32_12, 0);
  // 392: :
  // 393:   if
  // 394:     text == "":
  // 395:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 396:     :
  // 397:       push &text ' '
  // 398:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__32_17, 0);
  // 387: if
  // 388:   line == "":
  // 389:     if text != "":
  // 390:       push &paragraphs text
  // 391:       !text ""
  // 392:   :
  // 393:     if
  // 394:       text == "":
  // 395:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 396:       :
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
static void entry__32_2(void) {
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
  // 378: ... :
  // 379:   if
  // 380:     line .has_prefix. EXAMPLE:
  // 381:       trim &text
  // 382:       push &paragraphs text
  // 383:       !text line
  // 384:     :
  // 385:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__32_3, 0);
  // 386: :
  // 387:   if
  // 388:     line == "":
  // 389:       if text != "":
  // 390:         push &paragraphs text
  // 391:         !text ""
  // 392:     :
  // 393:       if
  // 394:         text == "":
  // 395:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__32_10, 0);
  // 377: if
  // 378:   pre_mode:
  // 379:     if
  // 380:       line .has_prefix. EXAMPLE:
  // 381:         trim &text
  // 382:         push &paragraphs text
  // 383:         !text line
  // 384:       :
  // 385:         writeln_to &text line
  // 386:   :
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
static void cont__32_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 399: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__32_28;
}
static void cont__32_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 399: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__32_29;
}
static void cont__32_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 399: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__32_30, 0);
  // 399: if text != "": push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__32_32;
}
static void entry__32_30(void) {
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
  // 399: ... push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__32_31;
}
static void cont__32_31(void) {
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
static void cont__32_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 400: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_8(void) {
  allocate_initialized_frame_gc(2, 15);
  // slot allocations:
  // function_name: 0
  // info: 1
  // short_description: 2
  // parameters: 3
  // return_values: 4
  // descriptions: 5
  // technical_details: 6
  // references: 7
  // examples: 8
  // remark_lines: 9
  // function_basename: 10
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] /* short_description */ = create_cell();
  frame->slots[3] /* parameters */ = create_cell();
  frame->slots[4] /* return_values */ = create_cell();
  frame->slots[5] /* descriptions */ = create_cell();
  frame->slots[6] /* technical_details */ = create_cell();
  frame->slots[7] /* references */ = create_cell();
  frame->slots[8] /* examples */ = create_cell();
  frame->slots[9] /* remark_lines */ = create_future();
  frame->slots[10] /* function_basename */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 405: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__33_9;
}
static void cont__33_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 407: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__33_10;
}
static void cont__33_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 407: ... :
  // 408:   $type function_name .before. '/'
  // 409:   $method function_name .behind. '/'
  // 410:   H1
  // 411:     string
  // 412:       '['
  // 413:       type
  // 414:       "]("
  // 415:       type.mangled
  // 416:       ".html)/["
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_11, 0);
  // 421: :
  // 422:   H1 function_name
  frame->slots[13] /* temp__3 */ = create_closure(entry__33_20, 0);
  // 406: if
  // 407:   function_name .contains. '/':
  // 408:     $type function_name .before. '/'
  // 409:     $method function_name .behind. '/'
  // 410:     H1
  // 411:       string
  // 412:         '['
  // 413:         type
  // 414:         "]("
  // 415:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_21;
}
static void entry__33_11(void) {
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
  // 408: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__33_12;
}
static void cont__33_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 409: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_13;
}
static void cont__33_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 415: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_14;
}
static void cont__33_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 419: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_15;
}
static void cont__33_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 411: string
  // 412:   '['
  // 413:   type
  // 414:   "]("
  // 415:   type.mangled
  // 416:   ".html)/["
  // 417:   method
  // 418:   "]("
  // 419:   method.mangled
  // 420:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__33_16;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__33_17;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__33_16;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__33_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_19;
}
static void cont__33_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 410: H1
  // 411:   string
  // 412:     '['
  // 413:     type
  // 414:     "]("
  // 415:     type.mangled
  // 416:     ".html)/["
  // 417:     method
  // 418:     "]("
  // 419:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // function_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 422: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 423: $$short_description undefined
  ((CELL *)frame->slots[2])->contents /* short_description */ = get__undefined();
  // 424: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 425: $$return_values empty_list
  ((CELL *)frame->slots[4])->contents /* return_values */ = get__empty_list();
  // 426: $$descriptions empty_list
  ((CELL *)frame->slots[5])->contents /* descriptions */ = get__empty_list();
  // 427: $$technical_details undefined
  ((CELL *)frame->slots[6])->contents /* technical_details */ = get__undefined();
  // 428: $$references empty_list
  ((CELL *)frame->slots[7])->contents /* references */ = get__empty_list();
  // 429: $$examples empty_list
  ((CELL *)frame->slots[8])->contents /* examples */ = get__empty_list();
  // 430: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__33_22;
}
static void cont__33_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* remark_lines */, arguments->slots[0]);
  // 434: remark_lines.is_undefined || remark_lines.is_empty
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_23, 0);
  // 432: &&
  // 433:   do_print_warnings
  // 434:   remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__33_28;
}
static void entry__33_23(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: remark_lines.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__33_24;
}
static void cont__33_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 434: ... remark_lines.is_empty
  frame->slots[3] /* temp__3 */ = create_closure(entry__33_25, 0);
  // 434: remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__33_27;
}
static void entry__33_25(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 434: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_26;
}
static void cont__33_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 434: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 434: remark_lines.is_undefined || remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 435: :
  // 436:   ewriteln "Missing documentation for @(function_name)!"
  frame->slots[13] /* temp__3 */ = create_closure(entry__33_29, 0);
  // 431: if
  // 432:   &&
  // 433:     do_print_warnings
  // 434:     remark_lines.is_undefined || remark_lines.is_empty
  // 435:   :
  // 436:     ewriteln "Missing documentation for @(function_name)!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_33;
}
static void entry__33_29(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // function_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: ... "Missing documentation for @(function_name)!"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33_30;
  arguments->slots[1] = frame->slots[0] /* function_name */;
  arguments->slots[2] = string__33_31;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_32;
}
static void cont__33_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 436: ewriteln "Missing documentation for @(function_name)!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewriteln();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_33(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 437: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_34;
}
static void cont__33_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 437: ... :
  // 438:   $paragraphs remark_lines.to_paragraphs
  // 439:   for_each paragraphs: ($paragraph)
  // 440:     cond
  // 441:       ->
  // 442:         has_prefix
  // 443:           paragraph
  // 444:           sequence
  // 445:             "Parameter"
  // 446:             sim2c::WHITESPACE
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_35, 0);
  // 437: if remark_lines.is_defined:
  // 438:   $paragraphs remark_lines.to_paragraphs
  // 439:   for_each paragraphs: ($paragraph)
  // 440:     cond
  // 441:       ->
  // 442:         has_prefix
  // 443:           paragraph
  // 444:           sequence
  // 445:             "Parameter"
  // 446:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_158;
}
static void entry__33_153(void) {
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
  // 524: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_154;
}
static void cont__33_154(void) {
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
static void entry__33_155(void) {
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
  // 526: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_156;
}
static void cont__33_156(void) {
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
static void entry__33_151(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // technical_details: 0
  // paragraph: 1
  // descriptions: 2
  frame->slots[0] = myself->closure.frame->slots[2]; /* technical_details */
  frame->slots[1] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[2] = myself->closure.frame->slots[3]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 523: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_152;
}
static void cont__33_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 523: ... :
  // 524:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_153, 0);
  // 525: :
  // 526:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_155, 0);
  // 522: if
  // 523:   technical_details.is_defined:
  // 524:     push &technical_details paragraph
  // 525:   :
  // 526:     push &descriptions paragraph
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
static void entry__33_157(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // short_description: 0
  // paragraph: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* short_description */
  frame->slots[1] = myself->closure.frame->slots[0]; /* paragraph */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 528: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_134(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 508: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_135(void) {
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
  // 510: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__33_136;
}
static void cont__33_136(void) {
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
static void entry__33_130(void) {
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
  // 505: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_131;
}
static void cont__33_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 505: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_132;
}
static void cont__33_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 507: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_133;
}
static void cont__33_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 507: ... :
  // 508:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__33_134, 0);
  // 509: :
  // 510:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__33_135, 0);
  // 506: if
  // 507:   detail == "":
  // 508:     !technical_details empty_list
  // 509:   :
  // 510:     !technical_details list(detail)
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
static void entry__33_120(void) {
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
  // 501: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__33_121;
}
static void cont__33_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 501: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_122;
}
static void cont__33_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 502: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_123;
}
static void cont__33_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 502: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_124;
}
static void cont__33_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 503: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_125;
}
static void cont__33_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 503: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_126;
}
static void cont__33_126(void) {
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
static void entry__33_112(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // topic: 0
  // function_name: 1
  // topic_contents: 2
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_name */
  frame->slots[2] /* topic_contents */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* topic */ = create_cell_with_contents(arguments->slots[0]);
  // 493: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_113;
}
static void cont__33_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 496: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__33_114;
}
static void cont__33_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 495: $$topic_contents
  // 496:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__33_115;
}
static void cont__33_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 498: !topic_contents(function_name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 498: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__33_116;
}
static void cont__33_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 499: !topics(topic) topic_contents
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  // 499: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__33_117;
}
static void cont__33_117(void) {
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
static void entry__33_109(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // paragraph: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[1]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 492: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_110;
}
static void cont__33_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 492: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__33_111;
}
static void cont__33_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 492: ... : ($topic)
  // 493:   trim &topic
  // 494:   
  // 495:   $$topic_contents
  // 496:     default_value(topics(topic) empty_key_order_set)
  // 497:   
  // 498:   !topic_contents(function_name) true
  // 499:   !topics(topic) topic_contents
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_112, 1);
  // 492: for_each split(paragraph .behind. ':' ','): ($topic)
  // 493:   trim &topic
  // 494:   
  // 495:   $$topic_contents
  // 496:     default_value(topics(topic) empty_key_order_set)
  // 497:   
  // 498:   !topic_contents(function_name) true
  // 499:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_104(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 490: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_105;
}
static void cont__33_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 490: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_106;
}
static void cont__33_106(void) {
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
static void entry__33_101(void) {
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
  // 489: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_102;
}
static void cont__33_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 489: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__33_103;
}
static void cont__33_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 489: ... : (reference)
  // 490:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_104, 1);
  // 489: for_each split(paragraph .behind. ':' ','): (reference)
  // 490:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_79(void) {
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
  // 477: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__33_80;
}
static void cont__33_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 479: -> return_value .has_suffix. '?':
  // 480:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_81, 0);
  // 481: -> return_value .has_suffix. '*':
  // 482:   !return_value
  // 483:     string
  // 484:       range(return_value 1 -2)
  // 485:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_87, 0);
  // 478: cond
  // 479:   -> return_value .has_suffix. '?':
  // 480:     !return_value string(range(return_value 1 -2) " (optional)")
  // 481:   -> return_value .has_suffix. '*':
  // 482:     !return_value
  // 483:       string
  // 484:         range(return_value 1 -2)
  // 485:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__33_93;
}
static void entry__33_89(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 484: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__33_90;
}
static void cont__33_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 484: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_91;
}
static void cont__33_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 482: !return_value
  // 483:   string
  // 484:     range(return_value 1 -2)
  // 485:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__33_57;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_92;
}
static void cont__33_92(void) {
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
static void entry__33_83(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 480: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__33_84;
}
static void cont__33_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 480: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_85;
}
static void cont__33_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 480: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__33_50;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_86;
}
static void cont__33_86(void) {
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
static void entry__33_81(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 479: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__33_82;
}
static void cont__33_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 479: ... :
  // 480:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__33_83, 0);
  // 479: -> return_value .has_suffix. '?':
  // 480:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_87(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 481: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__33_88;
}
static void cont__33_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 481: ... :
  // 482:   !return_value
  // 483:     string
  // 484:       range(return_value 1 -2)
  // 485:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__33_89, 0);
  // 481: -> return_value .has_suffix. '*':
  // 482:   !return_value
  // 483:     string
  // 484:       range(return_value 1 -2)
  // 485:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_93(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 486: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_94;
}
static void cont__33_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 486: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_95;
}
static void cont__33_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 487: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_96;
}
static void cont__33_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 487: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_97;
}
static void cont__33_97(void) {
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
static void entry__33_43(void) {
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
  // 451: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__33_44;
}
static void cont__33_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 453: -> parameter .has_suffix. '?':
  // 454:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_45, 0);
  // 455: -> parameter .has_suffix. '*':
  // 456:   !parameter
  // 457:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_52, 0);
  // 458: -> parameter .contains. '=':
  // 459:   !parameter
  // 460:     string
  // 461:       (parameter .before. '=').trim
  // 462:       " (optional; default value: "
  // 463:       (parameter .behind. '=').trim
  // 464:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_59, 0);
  // 452: cond
  // 453:   -> parameter .has_suffix. '?':
  // 454:     !parameter string(range(parameter 1 -2) " (optional)")
  // 455:   -> parameter .has_suffix. '*':
  // 456:     !parameter
  // 457:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 458:   -> parameter .contains. '=':
  // 459:     !parameter
  // 460:       string
  // 461:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__33_69;
}
static void entry__33_61(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 461: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__33_62;
}
static void cont__33_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 461: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_63;
}
static void cont__33_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 463: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_64;
}
static void cont__33_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 463: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_65;
}
static void cont__33_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 459: !parameter
  // 460:   string
  // 461:     (parameter .before. '=').trim
  // 462:     " (optional; default value: "
  // 463:     (parameter .behind. '=').trim
  // 464:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__33_66;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__33_67;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_68;
}
static void cont__33_68(void) {
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
static void entry__33_54(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 457: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__33_55;
}
static void cont__33_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 457: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_56;
}
static void cont__33_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 456: !parameter
  // 457:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__33_57;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_58;
}
static void cont__33_58(void) {
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
static void entry__33_47(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 454: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__33_48;
}
static void cont__33_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 454: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_49;
}
static void cont__33_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 454: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__33_50;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_51;
}
static void cont__33_51(void) {
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
static void entry__33_45(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 453: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__33_46;
}
static void cont__33_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 453: ... :
  // 454:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__33_47, 0);
  // 453: -> parameter .has_suffix. '?':
  // 454:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_52(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 455: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__33_53;
}
static void cont__33_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 455: ... :
  // 456:   !parameter
  // 457:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__33_54, 0);
  // 455: -> parameter .has_suffix. '*':
  // 456:   !parameter
  // 457:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_59(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 458: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__33_60;
}
static void cont__33_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 458: ... :
  // 459:   !parameter
  // 460:     string
  // 461:       (parameter .before. '=').trim
  // 462:       " (optional; default value: "
  // 463:       (parameter .behind. '=').trim
  // 464:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__33_61, 0);
  // 458: -> parameter .contains. '=':
  // 459:   !parameter
  // 460:     string
  // 461:       (parameter .before. '=').trim
  // 462:       " (optional; default value: "
  // 463:       (parameter .behind. '=').trim
  // 464:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 465: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__33_70;
}
static void cont__33_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 465: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__33_71;
}
static void cont__33_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 466: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_72;
}
static void cont__33_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 466: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_73;
}
static void cont__33_73(void) {
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
static void entry__33_38(void) {
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
  // 448: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__33_39;
}
static void cont__33_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 444: sequence
  // 445:   "Parameter"
  // 446:   sim2c::WHITESPACE
  // 447:   NAME
  // 448:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 449:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__33_40;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__33_41;
}
static void cont__33_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 442: has_prefix
  // 443:   paragraph
  // 444:   sequence
  // 445:     "Parameter"
  // 446:     sim2c::WHITESPACE
  // 447:     NAME
  // 448:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 449:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_42;
}
static void cont__33_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 450: :
  // 451:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 452:   cond
  // 453:     -> parameter .has_suffix. '?':
  // 454:       !parameter string(range(parameter 1 -2) " (optional)")
  // 455:     -> parameter .has_suffix. '*':
  // 456:       !parameter
  // 457:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 458:     -> parameter .contains. '=':
  // 459:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__33_43, 0);
  // 441: ->
  // 442:   has_prefix
  // 443:     paragraph
  // 444:     sequence
  // 445:       "Parameter"
  // 446:       sim2c::WHITESPACE
  // 447:       NAME
  // 448:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 449:       ':'
  // 450:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_74(void) {
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
  // 474: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__33_75;
}
static void cont__33_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 470: sequence
  // 471:   "Returns"
  // 472:   sim2c::WHITESPACE
  // 473:   NAME
  // 474:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 475:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__33_76;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__33_77;
}
static void cont__33_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 468: has_prefix
  // 469:   paragraph
  // 470:   sequence
  // 471:     "Returns"
  // 472:     sim2c::WHITESPACE
  // 473:     NAME
  // 474:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 475:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_78;
}
static void cont__33_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 476: :
  // 477:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 478:   cond
  // 479:     -> return_value .has_suffix. '?':
  // 480:       !return_value string(range(return_value 1 -2) " (optional)")
  // 481:     -> return_value .has_suffix. '*':
  // 482:       !return_value
  // 483:         string
  // 484:           range(return_value 1 -2)
  // 485:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__33_79, 0);
  // 467: ->
  // 468:   has_prefix
  // 469:     paragraph
  // 470:     sequence
  // 471:       "Returns"
  // 472:       sim2c::WHITESPACE
  // 473:       NAME
  // 474:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 475:       ':'
  // 476:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_98(void) {
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
  // 488: ... paragraph .has_prefix. "See also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__33_99;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_100;
}
static void cont__33_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 488: ... :
  // 489:   for_each split(paragraph .behind. ':' ','): (reference)
  // 490:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_101, 0);
  // 488: -> paragraph .has_prefix. "See also:":
  // 489:   for_each split(paragraph .behind. ':' ','): (reference)
  // 490:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_107(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // function_name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[4]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 491: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_108;
}
static void cont__33_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 491: ... :
  // 492:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 493:     trim &topic
  // 494:     
  // 495:     $$topic_contents
  // 496:       default_value(topics(topic) empty_key_order_set)
  // 497:     
  // 498:     !topic_contents(function_name) true
  // 499:     !topics(topic) topic_contents
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_109, 0);
  // 491: -> paragraph .has_prefix. TOPIC:
  // 492:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 493:     trim &topic
  // 494:     
  // 495:     $$topic_contents
  // 496:       default_value(topics(topic) empty_key_order_set)
  // 497:     
  // 498:     !topic_contents(function_name) true
  // 499:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_118(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // examples: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[5]; /* examples */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 500: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_119;
}
static void cont__33_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 500: ... :
  // 501:   $title (paragraph .before. ':').trim
  // 502:   $text (paragraph .behind. ':').trim
  // 503:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_120, 0);
  // 500: -> paragraph .has_prefix. EXAMPLE:
  // 501:   $title (paragraph .before. ':').trim
  // 502:   $text (paragraph .behind. ':').trim
  // 503:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_127(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // paragraph: 0
  // technical_details: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[6]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 504: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__33_128;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__33_129;
}
static void cont__33_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 504: ... :
  // 505:   $detail (paragraph .behind. ':').trim
  // 506:   if
  // 507:     detail == "":
  // 508:       !technical_details empty_list
  // 509:     :
  // 510:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_130, 0);
  // 504: -> paragraph .has_prefix. "Technical Details:":
  // 505:   $detail (paragraph .behind. ':').trim
  // 506:   if
  // 507:     detail == "":
  // 508:       !technical_details empty_list
  // 509:     :
  // 510:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_137(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // paragraph: 0
  // short_description: 1
  // technical_details: 2
  // descriptions: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* paragraph */
  frame->slots[1] = myself->closure.frame->slots[7]; /* short_description */
  frame->slots[2] = myself->closure.frame->slots[6]; /* technical_details */
  frame->slots[3] = myself->closure.frame->slots[8]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 515: ... '/', NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__33_138;
}
static void cont__33_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 515: ... optional('/', NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__33_139;
}
static void cont__33_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 515: '<', NAME, optional('/', NAME), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__33_140;
}
static void cont__33_140(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 514: =
  // 515:   '<', NAME, optional('/', NAME), '>'
  // 516:   : ($reference)
  // 517:     range &reference 2 -2
  // 518:     resolve_reference &reference
  // 519:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = func__33_141;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_148;
}
static void entry__33_141(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 517: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__33_142;
}
static void cont__33_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 517: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__33_143;
}
static void cont__33_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 518: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__33_144;
}
static void cont__33_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 519: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_145;
}
static void cont__33_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 519: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__33_146;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__33_16;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__33_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_147;
}
static void cont__33_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 519: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 512: replace_all
  // 513:   &paragraph
  // 514:   =
  // 515:     '<', NAME, optional('/', NAME), '>'
  // 516:     : ($reference)
  // 517:       range &reference 2 -2
  // 518:       resolve_reference &reference
  // 519:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__33_149;
}
static void cont__33_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 521: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_150;
}
static void cont__33_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 521: ... :
  // 522:   if
  // 523:     technical_details.is_defined:
  // 524:       push &technical_details paragraph
  // 525:     :
  // 526:       push &descriptions paragraph
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_151, 0);
  // 527: :
  // 528:   !short_description paragraph
  frame->slots[6] /* temp__3 */ = create_closure(entry__33_157, 0);
  // 520: if
  // 521:   short_description.is_defined:
  // 522:     if
  // 523:       technical_details.is_defined:
  // 524:         push &technical_details paragraph
  // 525:       :
  // 526:         push &descriptions paragraph
  // 527:   :
  // 528:     !short_description paragraph
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
static void entry__33_37(void) {
  allocate_initialized_frame_gc(9, 16);
  // slot allocations:
  // paragraph: 0
  // parameters: 1
  // return_values: 2
  // references: 3
  // function_name: 4
  // examples: 5
  // technical_details: 6
  // short_description: 7
  // descriptions: 8
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[2]; /* return_values */
  frame->slots[3] = myself->closure.frame->slots[3]; /* references */
  frame->slots[4] = myself->closure.frame->slots[4]; /* function_name */
  frame->slots[5] = myself->closure.frame->slots[5]; /* examples */
  frame->slots[6] = myself->closure.frame->slots[6]; /* technical_details */
  frame->slots[7] = myself->closure.frame->slots[7]; /* short_description */
  frame->slots[8] = myself->closure.frame->slots[8]; /* descriptions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* paragraph */ = create_cell_with_contents(arguments->slots[0]);
  // 441: ->
  // 442:   has_prefix
  // 443:     paragraph
  // 444:     sequence
  // 445:       "Parameter"
  // 446:       sim2c::WHITESPACE
  // 447:       NAME
  // 448:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 449:       ':'
  // 450:   :
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__33_38, 0);
  // 467: ->
  // 468:   has_prefix
  // 469:     paragraph
  // 470:     sequence
  // 471:       "Returns"
  // 472:       sim2c::WHITESPACE
  // 473:       NAME
  // 474:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 475:       ':'
  // 476:   :
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__33_74, 0);
  // 488: -> paragraph .has_prefix. "See also:":
  // 489:   for_each split(paragraph .behind. ':' ','): (reference)
  // 490:     push &references reference.trim
  frame->slots[11] /* temp__3 */ = create_closure(entry__33_98, 0);
  // 491: -> paragraph .has_prefix. TOPIC:
  // 492:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 493:     trim &topic
  // 494:     
  // 495:     $$topic_contents
  // 496:       default_value(topics(topic) empty_key_order_set)
  // 497:     
  // 498:     !topic_contents(function_name) true
  // 499:     !topics(topic) topic_contents
  frame->slots[12] /* temp__4 */ = create_closure(entry__33_107, 0);
  // 500: -> paragraph .has_prefix. EXAMPLE:
  // 501:   $title (paragraph .before. ':').trim
  // 502:   $text (paragraph .behind. ':').trim
  // 503:   push &examples title = text
  frame->slots[13] /* temp__5 */ = create_closure(entry__33_118, 0);
  // 504: -> paragraph .has_prefix. "Technical Details:":
  // 505:   $detail (paragraph .behind. ':').trim
  // 506:   if
  // 507:     detail == "":
  // 508:       !technical_details empty_list
  // 509:     :
  // 510:       !technical_details list(detail)
  frame->slots[14] /* temp__6 */ = create_closure(entry__33_127, 0);
  // 511: :
  // 512:   replace_all
  // 513:     &paragraph
  // 514:     =
  // 515:       '<', NAME, optional('/', NAME), '>'
  // 516:       : ($reference)
  // 517:         range &reference 2 -2
  // 518:         resolve_reference &reference
  // 519:         -> "[@(reference)](@(reference.mangled).html)"
  // 520:   if
  // ...
  frame->slots[15] /* temp__7 */ = create_closure(entry__33_137, 0);
  // 440: cond
  // 441:   ->
  // 442:     has_prefix
  // 443:       paragraph
  // 444:       sequence
  // 445:         "Parameter"
  // 446:         sim2c::WHITESPACE
  // 447:         NAME
  // 448:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 449:         ':'
  // ...
  argument_count = 7;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__2 */;
  arguments->slots[2] = frame->slots[11] /* temp__3 */;
  arguments->slots[3] = frame->slots[12] /* temp__4 */;
  arguments->slots[4] = frame->slots[13] /* temp__5 */;
  arguments->slots[5] = frame->slots[14] /* temp__6 */;
  arguments->slots[6] = frame->slots[15] /* temp__7 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_35(void) {
  allocate_initialized_frame_gc(9, 11);
  // slot allocations:
  // remark_lines: 0
  // parameters: 1
  // return_values: 2
  // references: 3
  // function_name: 4
  // examples: 5
  // technical_details: 6
  // short_description: 7
  // descriptions: 8
  // paragraphs: 9
  frame->slots[0] = myself->closure.frame->slots[9]; /* remark_lines */
  frame->slots[1] = myself->closure.frame->slots[3]; /* parameters */
  frame->slots[2] = myself->closure.frame->slots[4]; /* return_values */
  frame->slots[3] = myself->closure.frame->slots[7]; /* references */
  frame->slots[4] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[5] = myself->closure.frame->slots[8]; /* examples */
  frame->slots[6] = myself->closure.frame->slots[6]; /* technical_details */
  frame->slots[7] = myself->closure.frame->slots[2]; /* short_description */
  frame->slots[8] = myself->closure.frame->slots[5]; /* descriptions */
  frame->slots[9] /* paragraphs */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 438: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__33_36;
}
static void cont__33_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* paragraphs */, arguments->slots[0]);
  // 439: ... : ($paragraph)
  // 440:   cond
  // 441:     ->
  // 442:       has_prefix
  // 443:         paragraph
  // 444:         sequence
  // 445:           "Parameter"
  // 446:           sim2c::WHITESPACE
  // 447:           NAME
  // 448:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[10] /* temp__1 */ = create_closure(entry__33_37, 1);
  // 439: for_each paragraphs: ($paragraph)
  // 440:   cond
  // 441:     ->
  // 442:       has_prefix
  // 443:         paragraph
  // 444:         sequence
  // 445:           "Parameter"
  // 446:           sim2c::WHITESPACE
  // 447:           NAME
  // 448:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* paragraphs */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_158(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 529: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__33_159;
}
static void cont__33_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 529: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_160;
}
static void cont__33_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 529: ... :
  // 530:   for_each parameters_of(info): (parameter)
  // 531:     case
  // 532:       parameter_kind_of(parameter)
  // 533:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 534:         pass
  // 535:       :
  // 536:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:         cond
  // 538:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__33_161, 0);
  // 529: if kind_of(info) == FUNCTION:
  // 530:   for_each parameters_of(info): (parameter)
  // 531:     case
  // 532:       parameter_kind_of(parameter)
  // 533:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 534:         pass
  // 535:       :
  // 536:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:         cond
  // 538:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_198;
}
static void entry__33_166(void) {
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
  // 536: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__33_167;
}
static void cont__33_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 536: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__33_168;
}
static void cont__33_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 536: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__33_169;
}
static void cont__33_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 538: -> parameter.is_an_optional_item:
  // 539:   if
  // 540:     default_value_of(parameter).is_defined:
  // 541:       write_to
  // 542:         &name
  // 543:         " (optional; default value: "
  // 544:         default_value_of(parameter).to_string
  // 545:         ")"
  // 546:     :
  // 547:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__33_170, 0);
  // 548: -> parameter.is_an_expanded_item:
  // 549:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__33_181, 0);
  // 537: cond
  // 538:   -> parameter.is_an_optional_item:
  // 539:     if
  // 540:       default_value_of(parameter).is_defined:
  // 541:         write_to
  // 542:           &name
  // 543:           " (optional; default value: "
  // 544:           default_value_of(parameter).to_string
  // 545:           ")"
  // 546:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__33_185;
}
static void entry__33_183(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 549: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__33_57;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__33_184;
}
static void cont__33_184(void) {
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
static void entry__33_175(void) {
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
  // 544: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__33_176;
}
static void cont__33_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 544: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__33_177;
}
static void cont__33_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 541: write_to
  // 542:   &name
  // 543:   " (optional; default value: "
  // 544:   default_value_of(parameter).to_string
  // 545:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__33_66;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__33_67;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__33_178;
}
static void cont__33_178(void) {
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
static void entry__33_179(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__33_50;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__33_180;
}
static void cont__33_180(void) {
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
static void entry__33_172(void) {
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
  // 540: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__33_173;
}
static void cont__33_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 540: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_174;
}
static void cont__33_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 540: ... :
  // 541:   write_to
  // 542:     &name
  // 543:     " (optional; default value: "
  // 544:     default_value_of(parameter).to_string
  // 545:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_175, 0);
  // 546: :
  // 547:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__33_179, 0);
  // 539: if
  // 540:   default_value_of(parameter).is_defined:
  // 541:     write_to
  // 542:       &name
  // 543:       " (optional; default value: "
  // 544:       default_value_of(parameter).to_string
  // 545:       ")"
  // 546:   :
  // 547:     append &name " (optional)"
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
static void entry__33_170(void) {
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
  // 538: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__33_171;
}
static void cont__33_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 538: ... :
  // 539:   if
  // 540:     default_value_of(parameter).is_defined:
  // 541:       write_to
  // 542:         &name
  // 543:         " (optional; default value: "
  // 544:         default_value_of(parameter).to_string
  // 545:         ")"
  // 546:     :
  // 547:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_172, 0);
  // 538: -> parameter.is_an_optional_item:
  // 539:   if
  // 540:     default_value_of(parameter).is_defined:
  // 541:       write_to
  // 542:         &name
  // 543:         " (optional; default value: "
  // 544:         default_value_of(parameter).to_string
  // 545:         ")"
  // 546:     :
  // 547:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_181(void) {
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
  // 548: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__33_182;
}
static void cont__33_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 548: ... :
  // 549:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_183, 0);
  // 548: -> parameter.is_an_expanded_item:
  // 549:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 553: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__33_186;
}
static void cont__33_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 553: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_187;
}
static void cont__33_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 553: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__33_188;
}
static void cont__33_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 554: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__33_189, 0);
  // 551: $description
  // 552:   if
  // 553:     not(remark_lines_of(parameter).is_empty)
  // 554:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 555:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__33_193;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_194;
}
static void entry__33_189(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 554: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__33_190;
}
static void cont__33_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 554: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__33_191;
}
static void cont__33_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 554: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__33_192;
}
static void cont__33_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 554: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__33_193(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 557: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_195;
}
static void cont__33_195(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 557: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__33_196;
}
static void cont__33_196(void) {
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
static void entry__33_197(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 534: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_163(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 532: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__33_164;
}
static void cont__33_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 533: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__33_165;
}
static void cont__33_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 535: :
  // 536:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:   cond
  // 538:     -> parameter.is_an_optional_item:
  // 539:       if
  // 540:         default_value_of(parameter).is_defined:
  // 541:           write_to
  // 542:             &name
  // 543:             " (optional; default value: "
  // 544:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_166, 0);
  // 531: case
  // 532:   parameter_kind_of(parameter)
  // 533:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 534:     pass
  // 535:   :
  // 536:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:     cond
  // 538:       -> parameter.is_an_optional_item:
  // 539:         if
  // 540:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__33_197;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_161(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // parameters: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[3]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 530: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__33_162;
}
static void cont__33_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 530: ... : (parameter)
  // 531:   case
  // 532:     parameter_kind_of(parameter)
  // 533:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 534:       pass
  // 535:     :
  // 536:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:       cond
  // 538:         -> parameter.is_an_optional_item:
  // 539:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_163, 1);
  // 530: for_each parameters_of(info): (parameter)
  // 531:   case
  // 532:     parameter_kind_of(parameter)
  // 533:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 534:       pass
  // 535:     :
  // 536:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 537:       cond
  // 538:         -> parameter.is_an_optional_item:
  // 539:           if
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
static void cont__33_198(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 558: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_199;
}
static void cont__33_199(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 558: ... : P short_description
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_200, 0);
  // 558: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_201;
}
static void entry__33_200(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 558: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_201(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 559: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_202;
}
static void cont__33_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 559: ... :
  // 560:   H2 "Parameters"
  // 561:   DL:
  // 562:     for_each parameters: (parameter)
  // 563:       DT key_of(parameter)
  // 564:       DD: P std::value_of(parameter)
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_203, 0);
  // 559: unless parameters.is_empty:
  // 560:   H2 "Parameters"
  // 561:   DL:
  // 562:     for_each parameters: (parameter)
  // 563:       DT key_of(parameter)
  // 564:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__33_212;
}
static void entry__33_210(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 564: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__33_211;
}
static void cont__33_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 564: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_207(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 563: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__33_208;
}
static void cont__33_208(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 563: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__33_209;
}
static void cont__33_209(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 564: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__33_210, 0);
  // 564: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_206(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: for_each parameters: (parameter)
  // 563:   DT key_of(parameter)
  // 564:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__33_207;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_203(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 560: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_204;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_205;
}
static void cont__33_205(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: ... :
  // 562:   for_each parameters: (parameter)
  // 563:     DT key_of(parameter)
  // 564:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__33_206, 0);
  // 561: DL:
  // 562:   for_each parameters: (parameter)
  // 563:     DT key_of(parameter)
  // 564:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_212(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 565: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_213;
}
static void cont__33_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 565: ... :
  // 566:   H2 "Returns"
  // 567:   DL:
  // 568:     for_each return_values: (return_value)
  // 569:       DT key_of(return_value)
  // 570:       DD: P std::value_of(return_value)
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_214, 0);
  // 565: unless return_values.is_empty:
  // 566:   H2 "Returns"
  // 567:   DL:
  // 568:     for_each return_values: (return_value)
  // 569:       DT key_of(return_value)
  // 570:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__33_222;
}
static void entry__33_220(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 570: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__33_221;
}
static void cont__33_221(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 570: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_217(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 569: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__33_218;
}
static void cont__33_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 569: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__33_219;
}
static void cont__33_219(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 570: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__33_220, 0);
  // 570: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_216(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 568: for_each return_values: (return_value)
  // 569:   DT key_of(return_value)
  // 570:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__33_217;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_214(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 566: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_76;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_215;
}
static void cont__33_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 567: ... :
  // 568:   for_each return_values: (return_value)
  // 569:     DT key_of(return_value)
  // 570:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__33_216, 0);
  // 567: DL:
  // 568:   for_each return_values: (return_value)
  // 569:     DT key_of(return_value)
  // 570:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_222(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 571: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_223;
}
static void cont__33_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 571: ... :
  // 572:   H2 "Description"
  // 573:   for_each descriptions: (description) P description
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_224, 0);
  // 571: unless descriptions.is_empty:
  // 572:   H2 "Description"
  // 573:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__33_228;
}
static void entry__33_227(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 573: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_224(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 572: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_225;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_226;
}
static void cont__33_226(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 573: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__33_227;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_228(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_229;
}
static void cont__33_229(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 574: ... :
  // 575:   H2 "Technical Details"
  // 576:   for_each technical_details: (detail) P detail
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_230, 0);
  // 574: if technical_details.is_defined:
  // 575:   H2 "Technical Details"
  // 576:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_234;
}
static void entry__33_233(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 576: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_230(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 575: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_231;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_232;
}
static void cont__33_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 576: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__33_233;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_234(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 577: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_235;
}
static void cont__33_235(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 577: ... :
  // 578:   H2 "See also"
  // 579:   P:
  // 580:     for_each references: ($reference)
  // 581:       resolve_reference &reference
  // 582:       A "href" = "@(reference.mangled).html" reference
  // 583:       BR
  frame->slots[12] /* temp__2 */ = create_closure(entry__33_236, 0);
  // 577: unless references.is_empty:
  // 578:   H2 "See also"
  // 579:   P:
  // 580:     for_each references: ($reference)
  // 581:       resolve_reference &reference
  // 582:       A "href" = "@(reference.mangled).html" reference
  // 583:       BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__33_246;
}
static void entry__33_240(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 581: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__33_241;
}
static void cont__33_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 582: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_242;
}
static void cont__33_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 582: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_243;
}
static void cont__33_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 582: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_244;
}
static void cont__33_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 582: A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__33_245;
}
static void cont__33_245(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 583: BR
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__BR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_239(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: for_each references: ($reference)
  // 581:   resolve_reference &reference
  // 582:   A "href" = "@(reference.mangled).html" reference
  // 583:   BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = func__33_240;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_236(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 578: H2 "See also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_237;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_238;
}
static void cont__33_238(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 579: ... :
  // 580:   for_each references: ($reference)
  // 581:     resolve_reference &reference
  // 582:     A "href" = "@(reference.mangled).html" reference
  // 583:     BR
  frame->slots[1] /* temp__1 */ = create_closure(entry__33_239, 0);
  // 579: P:
  // 580:   for_each references: ($reference)
  // 581:     resolve_reference &reference
  // 582:     A "href" = "@(reference.mangled).html" reference
  // 583:     BR
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 584: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__33_247;
}
static void cont__33_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 584: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__33_248;
}
static void cont__33_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 584: ... :
  // 585:   H2 "Implemented by"
  // 586:   TABLE:
  // 587:     for_each types_of(info): (name)
  // 588:       $method string(name '/' function_name)
  // 589:       TR:
  // 590:         TD: A "href" = "@(name.mangled).html" name
  // 591:         TD "&nbsp;as&nbsp;"
  // 592:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[13] /* temp__3 */ = create_closure(entry__33_249, 0);
  // 584: unless types_of(info).is_empty:
  // 585:   H2 "Implemented by"
  // 586:   TABLE:
  // 587:     for_each types_of(info): (name)
  // 588:       $method string(name '/' function_name)
  // 589:       TR:
  // 590:         TD: A "href" = "@(name.mangled).html" name
  // 591:         TD "&nbsp;as&nbsp;"
  // 592:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__33_268;
}
static void entry__33_264(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 592: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_265;
}
static void cont__33_265(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 592: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_266;
}
static void cont__33_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 592: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_267;
}
static void cont__33_267(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 592: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_256(void) {
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
  // 590: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_257, 0);
  // 590: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__33_261;
}
static void entry__33_257(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 590: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_258;
}
static void cont__33_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 590: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_259;
}
static void cont__33_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 590: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_260;
}
static void cont__33_260(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 590: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_261(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 591: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_262;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__33_263;
}
static void cont__33_263(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 592: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_264, 0);
  // 592: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_254(void) {
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
  // 588: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_255;
}
static void cont__33_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 589: ... :
  // 590:   TD: A "href" = "@(name.mangled).html" name
  // 591:   TD "&nbsp;as&nbsp;"
  // 592:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__33_256, 0);
  // 589: TR:
  // 590:   TD: A "href" = "@(name.mangled).html" name
  // 591:   TD "&nbsp;as&nbsp;"
  // 592:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_252(void) {
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
  // 587: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__33_253;
}
static void cont__33_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 587: ... : (name)
  // 588:   $method string(name '/' function_name)
  // 589:   TR:
  // 590:     TD: A "href" = "@(name.mangled).html" name
  // 591:     TD "&nbsp;as&nbsp;"
  // 592:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_254, 1);
  // 587: for_each types_of(info): (name)
  // 588:   $method string(name '/' function_name)
  // 589:   TR:
  // 590:     TD: A "href" = "@(name.mangled).html" name
  // 591:     TD "&nbsp;as&nbsp;"
  // 592:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_249(void) {
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
  // 585: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_250;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_251;
}
static void cont__33_251(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 586: ... :
  // 587:   for_each types_of(info): (name)
  // 588:     $method string(name '/' function_name)
  // 589:     TR:
  // 590:       TD: A "href" = "@(name.mangled).html" name
  // 591:       TD "&nbsp;as&nbsp;"
  // 592:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_252, 0);
  // 586: TABLE:
  // 587:   for_each types_of(info): (name)
  // 588:     $method string(name '/' function_name)
  // 589:     TR:
  // 590:       TD: A "href" = "@(name.mangled).html" name
  // 591:       TD "&nbsp;as&nbsp;"
  // 592:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_268(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 593: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__33_269;
}
static void cont__33_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 593: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__33_270;
}
static void cont__33_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 593: ... :
  // 594:   H2 "Supported Polymorphic Functions"
  // 595:   TABLE:
  // 596:     for_each methods_of(info): (method_name _method_info)
  // 597:       TR:
  // 598:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:         TD "&nbsp;"
  // 600:         TD:
  // 601:           A
  // 602:             =
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__33_271, 0);
  // 593: if kind_of(info) == TYPE:
  // 594:   H2 "Supported Polymorphic Functions"
  // 595:   TABLE:
  // 596:     for_each methods_of(info): (method_name _method_info)
  // 597:       TR:
  // 598:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:         TD "&nbsp;"
  // 600:         TD:
  // 601:           A
  // 602:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__33_290;
}
static void entry__33_285(void) {
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
  // 604: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_286;
}
static void cont__33_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 604: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_287;
}
static void cont__33_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 604: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__26_3;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_288;
}
static void cont__33_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 602: =
  // 603:   "href"
  // 604:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_289;
}
static void cont__33_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 601: A
  // 602:   =
  // 603:     "href"
  // 604:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:   function_name
  // 606:   '/'
  // 607:   method_name
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
static void entry__33_277(void) {
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
  // 598: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_278, 0);
  // 598: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__33_282;
}
static void entry__33_278(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 598: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_279;
}
static void cont__33_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 598: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_280;
}
static void cont__33_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 598: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_281;
}
static void cont__33_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 598: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_282(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 599: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_283;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__33_284;
}
static void cont__33_284(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 600: ... :
  // 601:   A
  // 602:     =
  // 603:       "href"
  // 604:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:     function_name
  // 606:     '/'
  // 607:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_285, 0);
  // 600: TD:
  // 601:   A
  // 602:     =
  // 603:       "href"
  // 604:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:     function_name
  // 606:     '/'
  // 607:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_276(void) {
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
  // 597: ... :
  // 598:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:   TD "&nbsp;"
  // 600:   TD:
  // 601:     A
  // 602:       =
  // 603:         "href"
  // 604:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:       function_name
  // 606:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__33_277, 0);
  // 597: TR:
  // 598:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:   TD "&nbsp;"
  // 600:   TD:
  // 601:     A
  // 602:       =
  // 603:         "href"
  // 604:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:       function_name
  // 606:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_274(void) {
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
  // 596: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__33_275;
}
static void cont__33_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 596: ... : (method_name _method_info)
  // 597:   TR:
  // 598:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:     TD "&nbsp;"
  // 600:     TD:
  // 601:       A
  // 602:         =
  // 603:           "href"
  // 604:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_276, 2);
  // 596: for_each methods_of(info): (method_name _method_info)
  // 597:   TR:
  // 598:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:     TD "&nbsp;"
  // 600:     TD:
  // 601:       A
  // 602:         =
  // 603:           "href"
  // 604:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 605:         function_name
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
static void entry__33_271(void) {
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
  // 594: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__33_272;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_273;
}
static void cont__33_273(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 595: ... :
  // 596:   for_each methods_of(info): (method_name _method_info)
  // 597:     TR:
  // 598:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:       TD "&nbsp;"
  // 600:       TD:
  // 601:         A
  // 602:           =
  // 603:             "href"
  // 604:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__33_274, 0);
  // 595: TABLE:
  // 596:   for_each methods_of(info): (method_name _method_info)
  // 597:     TR:
  // 598:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 599:       TD "&nbsp;"
  // 600:       TD:
  // 601:         A
  // 602:           =
  // 603:             "href"
  // 604:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__33_290(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 610: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__33_291;
}
static void cont__33_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 609: $function_basename
  // 610:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__33_292;
}
static void cont__33_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* function_basename */, arguments->slots[0]);
  // 612: ... : (example)
  // 613:   $title key_of(example)
  // 614:   $text std::value_of(example)
  // 615:   H2 title
  // 616:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 617:     PRE
  // 618:       replace_all
  // 619:         text
  // 620:         =
  // 621:           sequence
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__33_293, 1);
  // 612: for_each examples: (example)
  // 613:   $title key_of(example)
  // 614:   $text std::value_of(example)
  // 615:   H2 title
  // 616:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 617:     PRE
  // 618:       replace_all
  // 619:         text
  // 620:         =
  // 621:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* examples */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__33_312;
}
static void entry__33_301(void) {
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
  // 623: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__33_302;
}
static void cont__33_302(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 623: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__33_303;
}
static void cont__33_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 623: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__33_304;
}
static void cont__33_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 621: sequence
  // 622:   '@quot;'
  // 623:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__33_305;
}
static void cont__33_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 620: =
  // 621:   sequence
  // 622:     '@quot;'
  // 623:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:     '@quot;'
  // 625:   : (string_literal)
  // 626:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__33_306;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_307;
}
static void entry__33_306(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 626: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__33_307(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 627: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33_308;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__33_308;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__33_309;
}
static void cont__33_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 627: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_310;
}
static void cont__33_310(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 618: replace_all
  // 619:   text
  // 620:   =
  // 621:     sequence
  // 622:       '@quot;'
  // 623:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:       '@quot;'
  // 625:     : (string_literal)
  // 626:       -> string_literal
  // 627:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__33_311;
}
static void cont__33_311(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 617: PRE
  // 618:   replace_all
  // 619:     text
  // 620:     =
  // 621:       sequence
  // 622:         '@quot;'
  // 623:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:         '@quot;'
  // 625:       : (string_literal)
  // 626:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_293(void) {
  allocate_initialized_frame_gc(2, 8);
  // slot allocations:
  // example: 0
  // function_basename: 1
  // title: 2
  // text: 3
  frame->slots[1] = myself->closure.frame->slots[10]; /* function_basename */
  frame->slots[2] /* title */ = create_future();
  frame->slots[3] /* text */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 613: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__33_294;
}
static void cont__33_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 614: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__33_295;
}
static void cont__33_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 615: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__33_296;
}
static void cont__33_296(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 616: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__33_297;
}
static void cont__33_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 616: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__33_298;
}
static void cont__33_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 616: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__33_299;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_300;
}
static void cont__33_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   PRE
  // 618:     replace_all
  // 619:       text
  // 620:       =
  // 621:         sequence
  // 622:           '@quot;'
  // 623:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:           '@quot;'
  // 625:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__33_301, 0);
  // 616: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 617:   PRE
  // 618:     replace_all
  // 619:       text
  // 620:       =
  // 621:         sequence
  // 622:           '@quot;'
  // 623:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 624:           '@quot;'
  // 625:         : (string_literal)
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
static void cont__33_312(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__33_299;
  arguments->slots[1] = string__33_313;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__33_314;
}
static void cont__33_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 630: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__33_315;
}
static void cont__33_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__4 */ = arguments->slots[0];
  // 630: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__33_316;
}
static void cont__33_316(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 630: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33_317;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = string__33_318;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_319;
}
static void cont__33_319(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 628: DIV
  // 629:   "class" = "footer"
  // 630:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_3(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // function_name: 0
  // info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 404: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__33_4;
}
static void cont__33_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 404: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33_5;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__33_7;
}
static void cont__33_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 404: ... :
  // 405:   link_bar
  // 406:   if
  // 407:     function_name .contains. '/':
  // 408:       $type function_name .before. '/'
  // 409:       $method function_name .behind. '/'
  // 410:       H1
  // 411:         string
  // 412:           '['
  // 413:           type
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__33_8, 0);
  // 404: create_page "html/@(function_name.mangled).html":
  // 405:   link_bar
  // 406:   if
  // 407:     function_name .contains. '/':
  // 408:       $type function_name .before. '/'
  // 409:       $method function_name .behind. '/'
  // 410:       H1
  // 411:         string
  // 412:           '['
  // 413:           type
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__33_1_create_info_page(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // function_name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 403: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__33_2;
}
static void cont__33_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 403: ... :
  // 404:   create_page "html/@(function_name.mangled).html":
  // 405:     link_bar
  // 406:     if
  // 407:       function_name .contains. '/':
  // 408:         $type function_name .before. '/'
  // 409:         $method function_name .behind. '/'
  // 410:         H1
  // 411:           string
  // 412:             '['
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__33_3, 0);
  // 403: if function_name.is_defined:
  // 404:   create_page "html/@(function_name.mangled).html":
  // 405:     link_bar
  // 406:     if
  // 407:       function_name .contains. '/':
  // 408:         $type function_name .before. '/'
  // 409:         $method function_name .behind. '/'
  // 410:         H1
  // 411:           string
  // 412:             '['
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_1_sim2c__extract_documentation(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // return__1: 1
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %html::encode 
  // : ($text tag _arg_str)
  //   std::equal temp__1 tag "p"
  // 
  //   temp__2:
  //     std::sequence temp__2 "&lt;" NAME "::" NAME '>'
  //     std::key_value_pair temp__1 temp__2: (capture)
  //       std::negate temp__2 2
  //       range temp__1 capture 5 temp__2
  //       resolve_reference temp__1 $reference
  //       mangled temp__2 reference
  //       std::string
  //         temp__1
  //         "
  //           <a href="@
  //         temp__2
  //         "
  //           .html">@
  //         reference
  //         "</a>"
  //       -> temp__1
  //     replace_all &text temp__1
  // 
  //   if temp__1 temp__2
  //   emit text
  define__html__encode(func__34_2_html__encode);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 645: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_20;
}
static void entry__34_2_html__encode(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // text: 0
  // tag: 1
  // arg_str: 2
  if (argument_count != 3) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* text */ = create_cell_with_contents(arguments->slots[0]);
  // 634: ... tag == "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* tag */;
  arguments->slots[1] = string__34_3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_4;
}
static void cont__34_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 634: ... :
  // 635:   replace_all
  // 636:     &text
  // 637:     =
  // 638:       "&lt;", NAME, "::", NAME, '>'
  // 639:       : (capture)
  // 640:         $reference resolve_reference(range(capture 5 -2))
  // 641:         -> "
  // 642:           <a href="@(reference.mangled).html">@(reference)</a>@
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_5, 0);
  // 634: if tag == "p":
  // 635:   replace_all
  // 636:     &text
  // 637:     =
  // 638:       "&lt;", NAME, "::", NAME, '>'
  // 639:       : (capture)
  // 640:         $reference resolve_reference(range(capture 5 -2))
  // 641:         -> "
  // 642:           <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_19;
}
static void entry__34_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: "&lt;", NAME, "::", NAME, '>'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_6;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = string__24_24;
  arguments->slots[3] = get__NAME();
  arguments->slots[4] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__34_7;
}
static void cont__34_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 637: =
  // 638:   "&lt;", NAME, "::", NAME, '>'
  // 639:   : (capture)
  // 640:     $reference resolve_reference(range(capture 5 -2))
  // 641:     -> "
  // 642:       <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__34_8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_17;
}
static void entry__34_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // capture: 0
  // reference: 1
  frame->slots[1] /* reference */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 640: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__34_9;
}
static void cont__34_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 640: ... range(capture 5 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* capture */;
  arguments->slots[1] = number__5;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__34_10;
}
static void cont__34_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 640: $reference resolve_reference(range(capture 5 -2))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__34_11;
}
static void cont__34_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* reference */, arguments->slots[0]);
  // 642: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_12;
}
static void cont__34_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 641: ... "
  // 642:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__34_13;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__34_14;
  arguments->slots[3] = frame->slots[1] /* reference */;
  arguments->slots[4] = string__34_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_16;
}
static void cont__34_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 641: -> "
  // 642:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 635: replace_all
  // 636:   &text
  // 637:   =
  // 638:     "&lt;", NAME, "::", NAME, '>'
  // 639:     : (capture)
  // 640:       $reference resolve_reference(range(capture 5 -2))
  // 641:       -> "
  // 642:         <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_18;
}
static void cont__34_18(void) {
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
static void cont__34_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: emit text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 645: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__34_21;
}
static void cont__34_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 646: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__34_22;
}
static void cont__34_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 647: for_each definitions: (name info)
  // 648:   if kind_of(info) == TYPE:
  // 649:     $base base_of(info)
  // 650:     if base.is_defined: add_derived_type base name
  // 651:     $$methods empty_key_order_table
  // 652:     for_each methods_of(info): ($method_name method_info)
  // 653:       unless method_name .contains. "::":
  // 654:         !method_name attribute_of(method_info).resolved_name
  // 655:       if name_of(info).is_defined:
  // 656:         $oname
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__34_23;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_54;
}
static void entry__34_26(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // info: 0
  // name: 1
  // base: 2
  // methods: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] /* base */ = create_future();
  frame->slots[3] /* methods */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 649: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__34_27;
}
static void cont__34_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base */, arguments->slots[0]);
  // 650: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_28;
}
static void cont__34_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 650: ... : add_derived_type base name
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_29, 0);
  // 650: if base.is_defined: add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_30;
}
static void entry__34_29(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // base: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* base */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: ... add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 651: $$methods empty_key_order_table
  ((CELL *)frame->slots[3])->contents /* methods */ = get__empty_key_order_table();
  // 652: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__34_31;
}
static void cont__34_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 652: ... : ($method_name method_info)
  // 653:   unless method_name .contains. "::":
  // 654:     !method_name attribute_of(method_info).resolved_name
  // 655:   if name_of(info).is_defined:
  // 656:     $oname
  // 657:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 658:     
  // 659:     !definitions(oname).types_of(name_of(info)) true
  // 660:   !methods(method_name) method_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_32, 2);
  // 652: for_each methods_of(info): ($method_name method_info)
  // 653:   unless method_name .contains. "::":
  // 654:     !method_name attribute_of(method_info).resolved_name
  // 655:   if name_of(info).is_defined:
  // 656:     $oname
  // 657:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 658:     
  // 659:     !definitions(oname).types_of(name_of(info)) true
  // 660:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_51;
}
static void entry__34_32(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // method_name: 0
  // method_info: 1
  // info: 2
  // methods: 3
  frame->slots[2] = myself->closure.frame->slots[0]; /* info */
  frame->slots[3] = myself->closure.frame->slots[3]; /* methods */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* method_name */ = create_cell_with_contents(arguments->slots[0]);
  // 653: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__34_33;
}
static void cont__34_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 653: ... :
  // 654:   !method_name attribute_of(method_info).resolved_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_34, 0);
  // 653: unless method_name .contains. "::":
  // 654:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__34_37;
}
static void entry__34_34(void) {
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
  // 654: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__34_35;
}
static void cont__34_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 654: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__34_36;
}
static void cont__34_36(void) {
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
static void cont__34_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 655: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_38;
}
static void cont__34_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 655: ... name_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_39;
}
static void cont__34_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 655: ... :
  // 656:   $oname
  // 657:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 658:   
  // 659:   !definitions(oname).types_of(name_of(info)) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__34_40, 0);
  // 655: if name_of(info).is_defined:
  // 656:   $oname
  // 657:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 658:   
  // 659:   !definitions(oname).types_of(name_of(info)) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_49;
}
static void entry__34_40(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // method_name: 0
  // info: 1
  // oname: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] /* oname */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__34_41;
}
static void cont__34_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 657: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_42;
}
static void cont__34_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 656: $oname
  // 657:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__34_43;
}
static void cont__34_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* oname */, arguments->slots[0]);
  // 659: !definitions(oname).types_of(name_of(info)) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 659: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__34_44;
}
static void cont__34_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 659: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__34_45;
}
static void cont__34_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 659: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_46;
}
static void cont__34_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 659: !definitions(oname).types_of(name_of(info))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__34_47;
}
static void cont__34_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 659: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[5] /* temp__3 */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 659: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__34_48;
}
static void cont__34_48(void) {
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
static void cont__34_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 660: !methods(method_name) method_info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 660: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__34_50;
}
static void cont__34_50(void) {
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
static void cont__34_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: !definitions(name).methods_of methods
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* methods */;
  // 661: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__34_52;
}
static void cont__34_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 661: !definitions(name).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[4] /* temp__1 */);
    frame->slots[5] /* temp__2 */ = temp;

  }
  // 661: !definitions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__34_53;
}
static void cont__34_53(void) {
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
static void entry__34_23(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 648: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_24;
}
static void cont__34_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 648: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_25;
}
static void cont__34_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 648: ... :
  // 649:   $base base_of(info)
  // 650:   if base.is_defined: add_derived_type base name
  // 651:   $$methods empty_key_order_table
  // 652:   for_each methods_of(info): ($method_name method_info)
  // 653:     unless method_name .contains. "::":
  // 654:       !method_name attribute_of(method_info).resolved_name
  // 655:     if name_of(info).is_defined:
  // 656:       $oname
  // 657:         ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_26, 0);
  // 648: if kind_of(info) == TYPE:
  // 649:   $base base_of(info)
  // 650:   if base.is_defined: add_derived_type base name
  // 651:   $$methods empty_key_order_table
  // 652:   for_each methods_of(info): ($method_name method_info)
  // 653:     unless method_name .contains. "::":
  // 654:       !method_name attribute_of(method_info).resolved_name
  // 655:     if name_of(info).is_defined:
  // 656:       $oname
  // 657:         ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 662: create_page "html/type_index.html":
  // 663:   $print_type_info:
  // 664:     (
  // 665:       info
  // 666:       indent = 0
  // 667:     )
  // 668:     TR:
  // 669:       $qname name_of(info)
  // 670:       $remark_lines remark_lines_of(info)
  // 671:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_55;
  arguments->slots[1] = func__34_56;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__34_94;
}
static void entry__34_93(void) {
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
  // 685: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_86(void) {
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
  // 684: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_87;
}
static void cont__34_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 684: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_88;
}
static void cont__34_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 684: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__34_89, 0);
  // 684: ... kind_of(info) == TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_92;
}
static void entry__34_89(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__34_90;
}
static void cont__34_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 684: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__34_91;
}
static void cont__34_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 684: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 684: ... :
  // 685:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__34_93, 0);
  // 684: if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 685:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_85(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 683: ... : (_base info)
  // 684:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 685:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_86, 2);
  // 683: for_each definitions: (_base info)
  // 684:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 685:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_56(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 663: ... :
  // 664:   (
  // 665:     info
  // 666:     indent = 0
  // 667:   )
  // 668:   TR:
  // 669:     $qname name_of(info)
  // 670:     $remark_lines remark_lines_of(info)
  // 671:     if qname.is_defined:
  // 672:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_57_print_type_info, -1);
  // 663: $print_type_info:
  // 664:   (
  // 665:     info
  // 666:     indent = 0
  // 667:   )
  // 668:   TR:
  // 669:     $qname name_of(info)
  // 670:     $remark_lines remark_lines_of(info)
  // 671:     if qname.is_defined:
  // 672:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 680: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__34_83;
}
static void entry__34_80(void) {
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
  // 678: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__34_81;
}
static void cont__34_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 678: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_82;
}
static void cont__34_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 678: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_58(void) {
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
  // 669: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_59;
}
static void cont__34_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 670: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__34_60;
}
static void cont__34_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 671: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_61;
}
static void cont__34_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 671: ... :
  // 672:   TD:
  // 673:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__34_62, 0);
  // 671: if qname.is_defined:
  // 672:   TD:
  // 673:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_69;
}
static void entry__34_63(void) {
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
  // 673: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_8;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__34_64;
}
static void cont__34_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 673: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__34_65;
}
static void cont__34_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 674: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_66;
}
static void cont__34_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 674: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_67;
}
static void cont__34_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 674: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_68;
}
static void cont__34_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 674: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_62(void) {
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
  // 672: ... :
  // 673:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_63, 0);
  // 672: TD:
  // 673:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 675: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_70;
}
static void cont__34_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 675: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_71, 0);
  // 675: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_74;
}
static void entry__34_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 675: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_72;
}
static void cont__34_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 675: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__34_73;
}
static void cont__34_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 675: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 675: ... :
  // 676:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_75, 0);
  // 675: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 676:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_78;
}
static void entry__34_75(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 676: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__34_76;
}
static void cont__34_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 676: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__34_77;
}
static void cont__34_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 676: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__34_79;
}
static void cont__34_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 677: ... : (name)
  // 678:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__34_80, 1);
  // 677: for_each derived_types_of(info): (name)
  // 678:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_57_print_type_info(void) {
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
  // 668: ... :
  // 669:   $qname name_of(info)
  // 670:   $remark_lines remark_lines_of(info)
  // 671:   if qname.is_defined:
  // 672:     TD:
  // 673:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:       A "href" = "@(qname.mangled).html" qname
  // 675:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 676:     TD remark_lines.to_paragraphs(1)
  // 677:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__34_58, 0);
  // 668: TR:
  // 669:   $qname name_of(info)
  // 670:   $remark_lines remark_lines_of(info)
  // 671:   if qname.is_defined:
  // 672:     TD:
  // 673:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 674:       A "href" = "@(qname.mangled).html" qname
  // 675:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 676:     TD remark_lines.to_paragraphs(1)
  // 677:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 681: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__28_17;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__34_84;
}
static void cont__34_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 682: ... :
  // 683:   for_each definitions: (_base info)
  // 684:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 685:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_85, 0);
  // 682: TABLE:
  // 683:   for_each definitions: (_base info)
  // 684:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 685:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 686: create_page "html/symbol_index.html":
  // 687:   link_bar
  // 688:   H1 "id" = "index" "Symbol Index"
  // 689:   from_to
  // 690:     'a'
  // 691:     'z': (letter)
  // 692:       A "href" = "#@(letter)" letter.to_upper_case
  // 693:     :
  // 694:       TEXT " "
  // 695:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_95;
  arguments->slots[1] = func__34_96;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__34_182;
}
static void entry__34_168(void) {
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
  // 737: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_169;
  arguments->slots[1] = string__34_170;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_171;
}
static void cont__34_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 737: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__34_172;
}
static void cont__34_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 737: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_173;
}
static void cont__34_173(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_174, 0);
  // 738: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__34_179;
}
static void entry__34_174(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 738: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_175;
}
static void cont__34_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 738: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_176;
}
static void cont__34_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 738: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_177;
}
static void cont__34_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 738: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__24_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__34_178;
}
static void cont__34_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 738: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_179(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 739: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__33_299;
  arguments->slots[1] = string__34_180;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_181;
}
static void cont__34_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 739: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_167(void) {
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
  // 736: ... :
  // 737:   TD "align" = "right" name .until. "::"
  // 738:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 739:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_168, 0);
  // 736: TR:
  // 737:   TD "align" = "right" name .until. "::"
  // 738:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 739:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_112(void) {
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
  // 699: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__34_113;
}
static void cont__34_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 699: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__34_114;
}
static void cont__34_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 699: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__34_115;
}
static void cont__34_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 699: ... :
  // 700:   !letter iname(1)
  // 701:   TR:
  // 702:     TD "colspan" = 3:
  // 703:       H2 "id" = letter:
  // 704:         TEXT letter.to_upper_case
  // 705:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__34_116, 0);
  // 699: if iname(1) != letter:
  // 700:   !letter iname(1)
  // 701:   TR:
  // 702:     TD "colspan" = 3:
  // 703:       H2 "id" = letter:
  // 704:         TEXT letter.to_upper_case
  // 705:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_129;
}
static void entry__34_123(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__34_124;
}
static void cont__34_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 704: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__34_125;
}
static void cont__34_125(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 705: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__34_126;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_127;
}
static void cont__34_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 705: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__34_128;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_121(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 703: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_98;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_122;
}
static void cont__34_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 703: ... :
  // 704:   TEXT letter.to_upper_case
  // 705:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_123, 0);
  // 703: H2 "id" = letter:
  // 704:   TEXT letter.to_upper_case
  // 705:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_118(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_119;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_120;
}
static void cont__34_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 702: ... :
  // 703:   H2 "id" = letter:
  // 704:     TEXT letter.to_upper_case
  // 705:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__34_121, 0);
  // 702: TD "colspan" = 3:
  // 703:   H2 "id" = letter:
  // 704:     TEXT letter.to_upper_case
  // 705:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_116(void) {
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
  // 700: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__34_117;
}
static void cont__34_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 701: ... :
  // 702:   TD "colspan" = 3:
  // 703:     H2 "id" = letter:
  // 704:       TEXT letter.to_upper_case
  // 705:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_118, 0);
  // 701: TR:
  // 702:   TD "colspan" = 3:
  // 703:     H2 "id" = letter:
  // 704:       TEXT letter.to_upper_case
  // 705:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 706: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 707: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_130;
}
static void cont__34_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 708: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__34_131;
}
static void cont__34_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 709: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_132;
}
static void cont__34_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 709: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__34_133, 0);
  // 709: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_136;
}
static void entry__34_133(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 709: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__34_134;
}
static void cont__34_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 709: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__34_135;
}
static void cont__34_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 709: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 709: ... :
  // 710:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__34_137, 0);
  // 709: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 710:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_140;
}
static void entry__34_137(void) {
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
  // 710: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__34_138;
}
static void cont__34_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 710: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__34_139;
}
static void cont__34_139(void) {
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
static void cont__34_140(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 714: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_141;
}
static void cont__34_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 712: $kind_info
  // 713:   case
  // 714:     kind_of(info)
  // 715:     FUNCTION
  // 716:     -> "function"
  // 717:     INLINE_C_FUNCTION
  // 718:     -> "inline-C function"
  // 719:     POLYMORPHIC
  // 720:     -> "polymorphic function"
  // 721:     UNIQUE_ITEM
  // ...
  argument_count = 14;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__34_142;
  arguments->slots[3] = var._INLINE_C_FUNCTION;
  arguments->slots[4] = func__34_144;
  arguments->slots[5] = get__POLYMORPHIC();
  arguments->slots[6] = func__34_146;
  arguments->slots[7] = var._UNIQUE_ITEM;
  arguments->slots[8] = func__34_148;
  arguments->slots[9] = var._CONSTANT;
  arguments->slots[10] = func__34_150;
  arguments->slots[11] = var._TYPE;
  arguments->slots[12] = func__34_152;
  arguments->slots[13] = func__34_153;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__34_154;
}
static void entry__34_142(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 716: -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_143;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_144(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 718: -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_145;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_146(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 720: -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_147;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_148(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 722: -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_149;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_150(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 724: -> "constant"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_151;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_152(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 726: -> "type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__22_92;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_153(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 727: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 729: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_155;
}
static void cont__34_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 729: ... :
  // 730:   if
  // 731:     remark.is_defined:
  // 732:       !remark string(remark " (" kind_info ")")
  // 733:     :
  // 734:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__34_156, 0);
  // 729: if kind_info.is_defined:
  // 730:   if
  // 731:     remark.is_defined:
  // 732:       !remark string(remark " (" kind_info ")")
  // 733:     :
  // 734:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_162;
}
static void entry__34_158(void) {
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
  // 732: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__34_159;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__33_67;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_160;
}
static void cont__34_160(void) {
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
static void entry__34_161(void) {
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
  // 734: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_156(void) {
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
  // 731: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_157;
}
static void cont__34_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 731: ... :
  // 732:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_158, 0);
  // 733: :
  // 734:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__34_161, 0);
  // 730: if
  // 731:   remark.is_defined:
  // 732:     !remark string(remark " (" kind_info ")")
  // 733:   :
  // 734:     !remark kind_info
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
static void cont__34_162(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 735: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_163;
}
static void cont__34_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 735: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__34_164, 0);
  // 735: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__34_166;
}
static void entry__34_164(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 735: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__34_165;
}
static void cont__34_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 735: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__34_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 735: ... :
  // 736:   TR:
  // 737:     TD "align" = "right" name .until. "::"
  // 738:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 739:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__34_167, 0);
  // 735: if remark.is_defined && name.is_defined:
  // 736:   TR:
  // 737:     TD "align" = "right" name .until. "::"
  // 738:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 739:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_111(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 698: ... : (iname info)
  // 699:   if iname(1) != letter:
  // 700:     !letter iname(1)
  // 701:     TR:
  // 702:       TD "colspan" = 3:
  // 703:         H2 "id" = letter:
  // 704:           TEXT letter.to_upper_case
  // 705:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 706:   $$remark undefined
  // 707:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_112, 2);
  // 698: for_each definitions: (iname info)
  // 699:   if iname(1) != letter:
  // 700:     !letter iname(1)
  // 701:     TR:
  // 702:       TD "colspan" = 3:
  // 703:         H2 "id" = letter:
  // 704:           TEXT letter.to_upper_case
  // 705:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 706:   $$remark undefined
  // 707:   $name name_of(info)
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
static void entry__34_96(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 687: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__34_97;
}
static void cont__34_97(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 688: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_98;
  arguments->slots[1] = string__34_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_100;
}
static void cont__34_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 688: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_22;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__34_101;
}
static void cont__34_101(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 689: from_to
  // 690:   'a'
  // 691:   'z': (letter)
  // 692:     A "href" = "#@(letter)" letter.to_upper_case
  // 693:   :
  // 694:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__34_102;
  arguments->slots[3] = func__34_107;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__34_109;
}
static void entry__34_102(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 692: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_103;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_104;
}
static void cont__34_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 692: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
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
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 692: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__34_106;
}
static void cont__34_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 692: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_107(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 694: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_108;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 695: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__34_110;
}
static void cont__34_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 696: TABLE:
  // 697:   $$letter undefined
  // 698:   for_each definitions: (iname info)
  // 699:     if iname(1) != letter:
  // 700:       !letter iname(1)
  // 701:       TR:
  // 702:         TD "colspan" = 3:
  // 703:           H2 "id" = letter:
  // 704:             TEXT letter.to_upper_case
  // 705:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_111;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_182(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: for_each definitions: (_iname info)
  // 741:   $name name_of(info)
  // 742:   create_info_page name info
  // 743:   case kind_of(info) TYPE:
  // 744:     for_each methods_of(info): (method_name method_info)
  // 745:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__34_183;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_192;
}
static void entry__34_189(void) {
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
  // 745: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__34_190;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_191;
}
static void cont__34_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 745: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_187(void) {
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
  // 744: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__34_188;
}
static void cont__34_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 744: ... : (method_name method_info)
  // 745:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__34_189, 2);
  // 744: for_each methods_of(info): (method_name method_info)
  // 745:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_183(void) {
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
  // 741: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__34_184;
}
static void cont__34_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 742: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__34_185;
}
static void cont__34_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 743: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_186;
}
static void cont__34_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 743: ... :
  // 744:   for_each methods_of(info): (method_name method_info)
  // 745:     create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_187, 0);
  // 743: case kind_of(info) TYPE:
  // 744:   for_each methods_of(info): (method_name method_info)
  // 745:     create_info_page string(name "/" method_name) method_info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = var._TYPE;
  arguments->slots[2] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_192(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 746: create_page "html/topic_index.html":
  // 747:   link_bar
  // 748:   H1 "id" = "index" "Topic Index"
  // 749:   TABLE:
  // 750:     for_each topics: (topic _references)
  // 751:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 752:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_193;
  arguments->slots[1] = func__34_194;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__34_208;
}
static void entry__34_206(void) {
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
  // 752: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_207;
}
static void cont__34_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 752: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_205(void) {
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
  // 752: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_206, 0);
  // 752: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_199(void) {
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
  // 751: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__34_200;
}
static void cont__34_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 751: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__34_201;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_202;
}
static void cont__34_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 751: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_203;
}
static void cont__34_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 751: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_204;
}
static void cont__34_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 752: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__34_205, 0);
  // 752: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_198(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 750: for_each topics: (topic _references)
  // 751:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 752:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__34_199;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_194(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 747: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__34_195;
}
static void cont__34_195(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 748: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_98;
  arguments->slots[1] = string__34_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_196;
}
static void cont__34_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 748: H1 "id" = "index" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_27;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__34_197;
}
static void cont__34_197(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 749: TABLE:
  // 750:   for_each topics: (topic _references)
  // 751:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 752:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_198;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_208(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 753: for_each topics: (topic references)
  // 754:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 755:   create_page "html/@(filename).html":
  // 756:     link_bar
  // 757:     H1 "id" = "index" topic
  // 758:     TABLE:
  // 759:       for_each references: (reference)
  // 760:         TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__34_209;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_225;
}
static void entry__34_221(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__34_222;
}
static void cont__34_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 760: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__33_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__34_223;
}
static void cont__34_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 760: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_224;
}
static void cont__34_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 760: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_220(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 760: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_221, 0);
  // 760: ... TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_219(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 760: ... : TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__34_220, 0);
  // 760: TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_218(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 759: for_each references: (reference)
  // 760:   TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__34_219;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_214(void) {
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
  // 756: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__34_215;
}
static void cont__34_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 757: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_98;
  arguments->slots[1] = string__34_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_216;
}
static void cont__34_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 757: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__34_217;
}
static void cont__34_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 758: ... :
  // 759:   for_each references: (reference)
  // 760:     TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[2] /* temp__1 */ = create_closure(entry__34_218, 0);
  // 758: TABLE:
  // 759:   for_each references: (reference)
  // 760:     TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_209(void) {
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
  // 754: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__34_210;
}
static void cont__34_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 754: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__34_201;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_211;
}
static void cont__34_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 754: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__34_212;
}
static void cont__34_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 755: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__33_5;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__33_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_213;
}
static void cont__34_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 755: ... :
  // 756:   link_bar
  // 757:   H1 "id" = "index" topic
  // 758:   TABLE:
  // 759:     for_each references: (reference)
  // 760:       TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[4] /* temp__2 */ = create_closure(entry__34_214, 0);
  // 755: create_page "html/@(filename).html":
  // 756:   link_bar
  // 757:   H1 "id" = "index" topic
  // 758:   TABLE:
  // 759:     for_each references: (reference)
  // 760:       TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 761: create_page "html/index.html":
  // 762:   H1 "Simplicity"
  // 763:   P: A "href" = "manual.html" "Manual"
  // 764:   P: A "href" = "type_index.html" "Type Index"
  // 765:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 766:   P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__34_226;
  arguments->slots[1] = func__34_227;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__34_241;
}
static void entry__34_239(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 766: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_240;
}
static void cont__34_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 766: ... A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_227(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 762: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__34_228;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__34_229;
}
static void cont__34_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 763: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_230;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__34_232;
}
static void entry__34_230(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 763: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_231;
}
static void cont__34_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 763: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_12;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 764: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_233;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__34_235;
}
static void entry__34_233(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 764: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_234;
}
static void cont__34_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 764: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_17;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 765: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_236;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__34_238;
}
static void entry__34_236(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 765: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__28_3;
  arguments->slots[1] = string__28_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__34_237;
}
static void cont__34_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 765: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__28_22;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_238(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 766: P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__34_239;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_241(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 768: if do_print_summary:
  // 769:   $$total_types 0
  // 770:   $$total_functions 0
  // 771:   $$total_polymorphic_functions 0
  // 772:   $$total_polymorphic_attributes 0
  // 773:   $$total_methods 0
  // 774:   $$total_inline_c_methods 0
  // 775:   $$total_attributes 0
  // 776:   $$total_inline_c_functions 0
  // 777:   $$total_unique_items 0
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_summary();
  arguments->slots[1] = func__34_242;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__34_313;
}
static void entry__34_242(void) {
  allocate_initialized_frame_gc(0, 27);
  // slot allocations:
  // total_types: 0
  // total_functions: 1
  // total_polymorphic_functions: 2
  // total_polymorphic_attributes: 3
  // total_methods: 4
  // total_inline_c_methods: 5
  // total_attributes: 6
  // total_inline_c_functions: 7
  // total_unique_items: 8
  // total_constants: 9
  // total_variables: 10
  // other: 11
  // total_definitions: 12
  frame->slots[0] /* total_types */ = create_cell();
  frame->slots[1] /* total_functions */ = create_cell();
  frame->slots[2] /* total_polymorphic_functions */ = create_cell();
  frame->slots[3] /* total_polymorphic_attributes */ = create_cell();
  frame->slots[4] /* total_methods */ = create_cell();
  frame->slots[5] /* total_inline_c_methods */ = create_cell();
  frame->slots[6] /* total_attributes */ = create_cell();
  frame->slots[7] /* total_inline_c_functions */ = create_cell();
  frame->slots[8] /* total_unique_items */ = create_cell();
  frame->slots[9] /* total_constants */ = create_cell();
  frame->slots[10] /* total_variables */ = create_cell();
  frame->slots[11] /* other */ = create_cell();
  frame->slots[12] /* total_definitions */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 769: $$total_types 0
  ((CELL *)frame->slots[0])->contents /* total_types */ = number__0;
  // 770: $$total_functions 0
  ((CELL *)frame->slots[1])->contents /* total_functions */ = number__0;
  // 771: $$total_polymorphic_functions 0
  ((CELL *)frame->slots[2])->contents /* total_polymorphic_functions */ = number__0;
  // 772: $$total_polymorphic_attributes 0
  ((CELL *)frame->slots[3])->contents /* total_polymorphic_attributes */ = number__0;
  // 773: $$total_methods 0
  ((CELL *)frame->slots[4])->contents /* total_methods */ = number__0;
  // 774: $$total_inline_c_methods 0
  ((CELL *)frame->slots[5])->contents /* total_inline_c_methods */ = number__0;
  // 775: $$total_attributes 0
  ((CELL *)frame->slots[6])->contents /* total_attributes */ = number__0;
  // 776: $$total_inline_c_functions 0
  ((CELL *)frame->slots[7])->contents /* total_inline_c_functions */ = number__0;
  // 777: $$total_unique_items 0
  ((CELL *)frame->slots[8])->contents /* total_unique_items */ = number__0;
  // 778: $$total_constants 0
  ((CELL *)frame->slots[9])->contents /* total_constants */ = number__0;
  // 779: $$total_variables 0
  ((CELL *)frame->slots[10])->contents /* total_variables */ = number__0;
  // 780: $$other 0
  ((CELL *)frame->slots[11])->contents /* other */ = number__0;
  // 782: ... : (_iname info)
  // 783:   case kind_of(info)
  // 784:     TYPE: inc &total_types
  // 785:     FUNCTION: inc &total_functions
  // 786:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 787:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 788:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 789:     UNIQUE_ITEM: inc &total_unique_items
  // 790:     CONSTANT: inc &total_constants
  // 791:     VARIABLE: inc &total_variables
  // ...
  frame->slots[13] /* temp__1 */ = create_closure(entry__34_243, 2);
  // 782: for_each definitions: (_iname info)
  // 783:   case kind_of(info)
  // 784:     TYPE: inc &total_types
  // 785:     FUNCTION: inc &total_functions
  // 786:     POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 787:     POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 788:     INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 789:     UNIQUE_ITEM: inc &total_unique_items
  // 790:     CONSTANT: inc &total_constants
  // 791:     VARIABLE: inc &total_variables
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[13] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__34_275;
}
static void entry__34_269(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_methods: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 796: ... inc &total_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_270;
}
static void cont__34_270(void) {
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
static void entry__34_271(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_methods: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_inline_c_methods */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 797: ... inc &total_inline_c_methods
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_272;
}
static void cont__34_272(void) {
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
static void entry__34_273(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 798: ... inc &total_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_274;
}
static void cont__34_274(void) {
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
static void entry__34_267(void) {
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
  // 795: ... kind_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_268;
}
static void cont__34_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 796: ... : inc &total_methods
  frame->slots[6] /* temp__2 */ = create_closure(entry__34_269, 0);
  // 797: ... : inc &total_inline_c_methods
  frame->slots[7] /* temp__3 */ = create_closure(entry__34_271, 0);
  // 798: : inc &total_attributes
  frame->slots[8] /* temp__4 */ = create_closure(entry__34_273, 0);
  // 795: case kind_of(method_info)
  // 796:   FUNCTION: inc &total_methods
  // 797:   INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 798:   : inc &total_attributes
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
static void entry__34_265(void) {
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
  // 794: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__34_266;
}
static void cont__34_266(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 794: ... : (method_name method_info)
  // 795:   case kind_of(method_info)
  // 796:     FUNCTION: inc &total_methods
  // 797:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 798:     : inc &total_attributes
  frame->slots[5] /* temp__2 */ = create_closure(entry__34_267, 2);
  // 794: for_each methods_of(info): (method_name method_info)
  // 795:   case kind_of(method_info)
  // 796:     FUNCTION: inc &total_methods
  // 797:     INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 798:     : inc &total_attributes
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__34_243(void) {
  allocate_initialized_frame_gc(14, 24);
  // slot allocations:
  // iname: 0
  // info: 1
  // total_types: 2
  // total_functions: 3
  // total_polymorphic_functions: 4
  // total_polymorphic_attributes: 5
  // total_inline_c_functions: 6
  // total_unique_items: 7
  // total_constants: 8
  // total_variables: 9
  // other: 10
  // total_methods: 11
  // total_inline_c_methods: 12
  // total_attributes: 13
  frame->slots[2] = myself->closure.frame->slots[0]; /* total_types */
  frame->slots[3] = myself->closure.frame->slots[1]; /* total_functions */
  frame->slots[4] = myself->closure.frame->slots[2]; /* total_polymorphic_functions */
  frame->slots[5] = myself->closure.frame->slots[3]; /* total_polymorphic_attributes */
  frame->slots[6] = myself->closure.frame->slots[7]; /* total_inline_c_functions */
  frame->slots[7] = myself->closure.frame->slots[8]; /* total_unique_items */
  frame->slots[8] = myself->closure.frame->slots[9]; /* total_constants */
  frame->slots[9] = myself->closure.frame->slots[10]; /* total_variables */
  frame->slots[10] = myself->closure.frame->slots[11]; /* other */
  frame->slots[11] = myself->closure.frame->slots[4]; /* total_methods */
  frame->slots[12] = myself->closure.frame->slots[5]; /* total_inline_c_methods */
  frame->slots[13] = myself->closure.frame->slots[6]; /* total_attributes */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 783: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_244;
}
static void cont__34_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 784: ... : inc &total_types
  frame->slots[15] /* temp__2 */ = create_closure(entry__34_245, 0);
  // 785: ... : inc &total_functions
  frame->slots[16] /* temp__3 */ = create_closure(entry__34_247, 0);
  // 786: ... : inc &total_polymorphic_functions
  frame->slots[17] /* temp__4 */ = create_closure(entry__34_249, 0);
  // 787: ... : inc &total_polymorphic_attributes
  frame->slots[18] /* temp__5 */ = create_closure(entry__34_251, 0);
  // 788: ... : inc &total_inline_c_functions
  frame->slots[19] /* temp__6 */ = create_closure(entry__34_253, 0);
  // 789: ... : inc &total_unique_items
  frame->slots[20] /* temp__7 */ = create_closure(entry__34_255, 0);
  // 790: ... : inc &total_constants
  frame->slots[21] /* temp__8 */ = create_closure(entry__34_257, 0);
  // 791: ... : inc &total_variables
  frame->slots[22] /* temp__9 */ = create_closure(entry__34_259, 0);
  // 792: : inc &other
  frame->slots[23] /* temp__10 */ = create_closure(entry__34_261, 0);
  // 783: case kind_of(info)
  // 784:   TYPE: inc &total_types
  // 785:   FUNCTION: inc &total_functions
  // 786:   POLYMORPHIC_FUNCTION: inc &total_polymorphic_functions
  // 787:   POLYMORPHIC_ATTRIBUTE: inc &total_polymorphic_attributes
  // 788:   INLINE_C_FUNCTION: inc &total_inline_c_functions
  // 789:   UNIQUE_ITEM: inc &total_unique_items
  // 790:   CONSTANT: inc &total_constants
  // 791:   VARIABLE: inc &total_variables
  // 792:   : inc &other
  argument_count = 18;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  arguments->slots[1] = var._TYPE;
  arguments->slots[2] = frame->slots[15] /* temp__2 */;
  arguments->slots[3] = var._FUNCTION;
  arguments->slots[4] = frame->slots[16] /* temp__3 */;
  arguments->slots[5] = var._POLYMORPHIC_FUNCTION;
  arguments->slots[6] = frame->slots[17] /* temp__4 */;
  arguments->slots[7] = var._POLYMORPHIC_ATTRIBUTE;
  arguments->slots[8] = frame->slots[18] /* temp__5 */;
  arguments->slots[9] = var._INLINE_C_FUNCTION;
  arguments->slots[10] = frame->slots[19] /* temp__6 */;
  arguments->slots[11] = var._UNIQUE_ITEM;
  arguments->slots[12] = frame->slots[20] /* temp__7 */;
  arguments->slots[13] = var._CONSTANT;
  arguments->slots[14] = frame->slots[21] /* temp__8 */;
  arguments->slots[15] = var._VARIABLE;
  arguments->slots[16] = frame->slots[22] /* temp__9 */;
  arguments->slots[17] = frame->slots[23] /* temp__10 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__34_263;
}
static void entry__34_245(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_types: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* total_types */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 784: ... inc &total_types
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_types */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_246;
}
static void cont__34_246(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* total_types */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__34_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_functions: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* total_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 785: ... inc &total_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_248;
}
static void cont__34_248(void) {
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
static void entry__34_249(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_functions: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* total_polymorphic_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 786: ... inc &total_polymorphic_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_250;
}
static void cont__34_250(void) {
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
static void entry__34_251(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_polymorphic_attributes: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* total_polymorphic_attributes */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 787: ... inc &total_polymorphic_attributes
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_252;
}
static void cont__34_252(void) {
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
static void entry__34_253(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_inline_c_functions: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* total_inline_c_functions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 788: ... inc &total_inline_c_functions
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_254;
}
static void cont__34_254(void) {
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
static void entry__34_255(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_unique_items: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* total_unique_items */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 789: ... inc &total_unique_items
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_256;
}
static void cont__34_256(void) {
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
static void entry__34_257(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_constants: 0
  frame->slots[0] = myself->closure.frame->slots[8]; /* total_constants */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 790: ... inc &total_constants
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_constants */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_258;
}
static void cont__34_258(void) {
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
static void entry__34_259(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // total_variables: 0
  frame->slots[0] = myself->closure.frame->slots[9]; /* total_variables */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 791: ... inc &total_variables
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_variables */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_260;
}
static void cont__34_260(void) {
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
static void entry__34_261(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // other: 0
  frame->slots[0] = myself->closure.frame->slots[10]; /* other */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 792: ... inc &other
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* other */;
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__34_262;
}
static void cont__34_262(void) {
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
static void cont__34_263(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 793: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__34_264;
}
static void cont__34_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__1 */ = arguments->slots[0];
  // 793: ... :
  // 794:   for_each methods_of(info): (method_name method_info)
  // 795:     case kind_of(method_info)
  // 796:       FUNCTION: inc &total_methods
  // 797:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 798:       : inc &total_attributes
  frame->slots[15] /* temp__2 */ = create_closure(entry__34_265, 0);
  // 793: case kind_of(info) TYPE:
  // 794:   for_each methods_of(info): (method_name method_info)
  // 795:     case kind_of(method_info)
  // 796:       FUNCTION: inc &total_methods
  // 797:       INLINE_C_FUNCTION: inc &total_inline_c_methods
  // 798:       : inc &total_attributes
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__1 */;
  arguments->slots[1] = var._TYPE;
  arguments->slots[2] = frame->slots[15] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_275(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_types */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* total_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_276;
}
static void cont__34_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[21] /* temp__9 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_277;
}
static void cont__34_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[20] /* temp__8 */;
  arguments->slots[1] = ((CELL *)frame->slots[3])->contents /* total_polymorphic_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_278;
}
static void cont__34_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[19] /* temp__7 */;
  arguments->slots[1] = ((CELL *)frame->slots[4])->contents /* total_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_279;
}
static void cont__34_279(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[18] /* temp__6 */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* total_inline_c_methods */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_280;
}
static void cont__34_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[17] /* temp__5 */;
  arguments->slots[1] = ((CELL *)frame->slots[6])->contents /* total_attributes */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_281;
}
static void cont__34_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[16] /* temp__4 */;
  arguments->slots[1] = ((CELL *)frame->slots[7])->contents /* total_inline_c_functions */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_282;
}
static void cont__34_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[15] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[8])->contents /* total_unique_items */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_283;
}
static void cont__34_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__2 */;
  arguments->slots[1] = ((CELL *)frame->slots[9])->contents /* total_constants */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_284;
}
static void cont__34_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 800: $total_definitions
  // 801:   +
  // 802:     total_types
  // 803:     total_functions
  // 804:     total_polymorphic_functions
  // 805:     total_polymorphic_attributes
  // 806:     total_methods
  // 807:     total_inline_c_methods
  // 808:     total_attributes
  // 809:     total_inline_c_functions
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[10])->contents /* total_variables */;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__34_285;
}
static void cont__34_285(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[12] /* total_definitions */, arguments->slots[0]);
  // 815: ... pad_left(total_definitions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* total_definitions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_286;
}
static void cont__34_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__2 */ = arguments->slots[0];
  // 817: ... pad_left(total_types 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* total_types */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_287;
}
static void cont__34_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[15] /* temp__3 */ = arguments->slots[0];
  // 818: ... pad_left(total_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* total_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_288;
}
static void cont__34_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[16] /* temp__4 */ = arguments->slots[0];
  // 819: ... pad_left(total_polymorphic_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* total_polymorphic_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_289;
}
static void cont__34_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[17] /* temp__5 */ = arguments->slots[0];
  // 820: ... pad_left(total_polymorphic_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* total_polymorphic_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_290;
}
static void cont__34_290(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[18] /* temp__6 */ = arguments->slots[0];
  // 821: ... pad_left(total_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* total_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_291;
}
static void cont__34_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[19] /* temp__7 */ = arguments->slots[0];
  // 822: ... pad_left(total_inline_c_methods 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* total_inline_c_methods */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_292;
}
static void cont__34_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[20] /* temp__8 */ = arguments->slots[0];
  // 823: ... pad_left(total_attributes 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* total_attributes */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_293;
}
static void cont__34_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[21] /* temp__9 */ = arguments->slots[0];
  // 824: ... pad_left(total_inline_c_functions 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* total_inline_c_functions */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_294;
}
static void cont__34_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[22] /* temp__10 */ = arguments->slots[0];
  // 825: ... pad_left(total_unique_items 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* total_unique_items */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_295;
}
static void cont__34_295(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[23] /* temp__11 */ = arguments->slots[0];
  // 826: ... pad_left(total_constants 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[9])->contents /* total_constants */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_296;
}
static void cont__34_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[24] /* temp__12 */ = arguments->slots[0];
  // 827: ... pad_left(total_variables 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[10])->contents /* total_variables */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_297;
}
static void cont__34_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[25] /* temp__13 */ = arguments->slots[0];
  // 829: ... pad_left(other 5)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[11])->contents /* other */;
  arguments->slots[1] = number__5;
  result_count = 1;
  myself = get__pad_left();
  func = myself->type;
  frame->cont = cont__34_298;
}
static void cont__34_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[26] /* temp__14 */ = arguments->slots[0];
  // 814: ... "
  // 815:   total definitions:     @(pad_left(total_definitions 5))
  // 816:   
  // 817:   types:                 @(pad_left(total_types 5))
  // 818:   functions:             @(pad_left(total_functions 5))
  // 819:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 820:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 821:   method definitions:    @(pad_left(total_methods 5))
  // 822:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 823:   attribute definitions: @(pad_left(total_attributes 5))
  // ...
  argument_count = 27;
  arguments = node_p;
  arguments->slots[0] = string__34_299;
  arguments->slots[1] = frame->slots[14] /* temp__2 */;
  arguments->slots[2] = string__34_300;
  arguments->slots[3] = frame->slots[15] /* temp__3 */;
  arguments->slots[4] = string__34_301;
  arguments->slots[5] = frame->slots[16] /* temp__4 */;
  arguments->slots[6] = string__34_302;
  arguments->slots[7] = frame->slots[17] /* temp__5 */;
  arguments->slots[8] = string__34_303;
  arguments->slots[9] = frame->slots[18] /* temp__6 */;
  arguments->slots[10] = string__34_304;
  arguments->slots[11] = frame->slots[19] /* temp__7 */;
  arguments->slots[12] = string__34_305;
  arguments->slots[13] = frame->slots[20] /* temp__8 */;
  arguments->slots[14] = string__34_306;
  arguments->slots[15] = frame->slots[21] /* temp__9 */;
  arguments->slots[16] = string__34_307;
  arguments->slots[17] = frame->slots[22] /* temp__10 */;
  arguments->slots[18] = string__34_308;
  arguments->slots[19] = frame->slots[23] /* temp__11 */;
  arguments->slots[20] = string__34_309;
  arguments->slots[21] = frame->slots[24] /* temp__12 */;
  arguments->slots[22] = string__34_310;
  arguments->slots[23] = frame->slots[25] /* temp__13 */;
  arguments->slots[24] = string__34_311;
  arguments->slots[25] = frame->slots[26] /* temp__14 */;
  arguments->slots[26] = string__22_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__34_312;
}
static void cont__34_312(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__1 */ = arguments->slots[0];
  // 814: ewrite "
  // 815:   total definitions:     @(pad_left(total_definitions 5))
  // 816:   
  // 817:   types:                 @(pad_left(total_types 5))
  // 818:   functions:             @(pad_left(total_functions 5))
  // 819:   polymorphic functions: @(pad_left(total_polymorphic_functions 5))
  // 820:   polymorphic attributes:@(pad_left(total_polymorphic_attributes 5))
  // 821:   method definitions:    @(pad_left(total_methods 5))
  // 822:   inline C methods:      @(pad_left(total_inline_c_methods 5))
  // 823:   attribute definitions: @(pad_left(total_attributes 5))
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[13] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__ewrite();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__34_313(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__extractor(void) {
  var._filename_of = collect_node(var._filename_of);
  var._used_namespaces_of = collect_node(var._used_namespaces_of);
  var._derived_types_of = collect_node(var._derived_types_of);
  var._methods_of = collect_node(var._methods_of);
  var._types_of = collect_node(var._types_of);
  var._polymorphic_functions = collect_node(var._polymorphic_functions);
  var._definitions = collect_node(var._definitions);
  var._topics = collect_node(var._topics);
  var._BORING = collect_node(var._BORING);
  var._TYPE = collect_node(var._TYPE);
  var._FUNCTION = collect_node(var._FUNCTION);
  var._POLYMORPHIC_FUNCTION = collect_node(var._POLYMORPHIC_FUNCTION);
  var._POLYMORPHIC_ATTRIBUTE = collect_node(var._POLYMORPHIC_ATTRIBUTE);
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
  var._resolve_reference = collect_node(var._resolve_reference);
  var._TOPIC = collect_node(var._TOPIC);
  var._EXAMPLE = collect_node(var._EXAMPLE);
  var._to_paragraphs = collect_node(var._to_paragraphs);
  var._create_info_page = collect_node(var._create_info_page);
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
  unique__TYPE = register_unique_item("TYPE");
  unique__FUNCTION = register_unique_item("FUNCTION");
  unique__POLYMORPHIC_FUNCTION = register_unique_item("POLYMORPHIC_FUNCTION");
  unique__POLYMORPHIC_ATTRIBUTE = register_unique_item("POLYMORPHIC_ATTRIBUTE");
  unique__INLINE_C_FUNCTION = register_unique_item("INLINE_C_FUNCTION");
  unique__UNIQUE_ITEM = register_unique_item("UNIQUE_ITEM");
  unique__CONSTANT = register_unique_item("CONSTANT");
  unique__VARIABLE = register_unique_item("VARIABLE");
  string__20_5 = from_latin_1_string("body {\012  background-color: white;\012  font-family: Times New Roman, Times;\012  font-size: 12pt;\012  color: #222;\012}\012h1 {\012  font-family: Arial, Helvetica;\012  font-size: 20pt;\012  color: #333;\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012h2 {\012  font-family: Arial, Helvetica;\012  font-size: 16pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 5pt;\012}\012h3 {\012  font-family: Arial, Helvetica;\012  font-size: 14pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 3pt;\012}\012h4 {\012  font-family: Arial, Helvetica;\012  font-size: 13pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 2pt;\012}\012dt {\012  font-style: italic;\012  margin-bottom: 4pt;\012}\012dd {\012  padding-left: 0pt;\012  margin-left: 16pt;\012  margin-top: 0pt;\012  margin-bottom: 0pt;\012}\012p {\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012a {\012  text-decoration: none;\012}\012div.Example {\012  background-color: #ffc;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.Output {\012  background-color: #cff;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.footer {\012  padding-top: 10pt;\012  font-size: 10pt;\012}\012pre {\012  font-family: Courier New, Courier;\012  font-size: 12pt;\012  padding-top: 0pt;\012  padding-bottom: 0pt;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012td.remark {\012  padding-left: 10pt;\012}\012", 1234);
  func__20_4 = create_function(entry__20_4, 0);
  func__20_1_create_page = create_function(entry__20_1_create_page, 2);
  string__22_2 = from_latin_1_string("extracting documentation from ", 30);
  string__22_3 = from_latin_1_string("\012", 1);
  string__22_11 = from_latin_1_string("Empty source text!", 18);
  func__22_10 = create_function(entry__22_10, 0);
  string__22_17 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__22_16 = create_function(entry__22_16, 0);
  string__22_24 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__22_23 = create_function(entry__22_23, 0);
  string__22_26 = from_latin_1_string(".sim", 4);
  string__22_28 = from_latin_1_string("__", 2);
  func__22_32 = create_function(entry__22_32, 1);
  string__22_55 = from_latin_1_string("std", 3);
  func__22_54 = create_function(entry__22_54, 0);
  func__22_61 = create_function(entry__22_61, 0);
  func__22_64 = create_function(entry__22_64, 0);
  func__22_87 = create_function(entry__22_87, 0);
  string__22_92 = from_latin_1_string("type", 4);
  func__22_105 = create_function(entry__22_105, 0);
  func__22_131 = create_function(entry__22_131, 0);
  func__22_132 = create_function(entry__22_132, 0);
  string__22_139 = from_latin_1_string("types::function", 15);
  func__22_158 = create_function(entry__22_158, 0);
  func__22_159 = create_function(entry__22_159, 0);
  func__22_1_extract_documentation_from_file = create_function(entry__22_1_extract_documentation_from_file, 1);
  func__23_4 = create_function(entry__23_4, 1);
  func__23_1_extract_documentation_from_directory = create_function(entry__23_1_extract_documentation_from_directory, 1);
  string__24_14 = from_latin_1_string("The attribute \042", 15);
  string__24_15 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__24_21 = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__24_24 = from_latin_1_string("::", 2);
  func__24_1_resolved_name = create_function(entry__24_1_resolved_name, 1);
  func__25_1_add_derived_type = create_function(entry__25_1_add_derived_type, 2);
  string__26_3 = from_latin_1_string("___", 3);
  func__26_1_mangled = create_function(entry__26_1_mangled, 1);
  func__27_1_ordered_name = create_function(entry__27_1_ordered_name, 2);
  string__28_3 = from_latin_1_string("href", 4);
  string__28_4 = from_latin_1_string("index.html", 10);
  string__28_6 = from_latin_1_string("Home", 4);
  string__28_8 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__28_10 = from_latin_1_string("manual.html", 11);
  string__28_12 = from_latin_1_string("Manual", 6);
  string__28_15 = from_latin_1_string("type_index.html", 15);
  string__28_17 = from_latin_1_string("Type Index", 10);
  string__28_20 = from_latin_1_string("symbol_index.html", 17);
  string__28_22 = from_latin_1_string("Symbol Index", 12);
  string__28_25 = from_latin_1_string("topic_index.html", 16);
  string__28_27 = from_latin_1_string("Topic Index", 11);
  func__28_2 = create_function(entry__28_2, 0);
  func__28_1_link_bar = create_function(entry__28_1_link_bar, 0);
  string__29_8 = from_latin_1_string("types::", 7);
  string__29_13 = from_latin_1_string("std::", 5);
  func__29_1_resolve_reference = create_function(entry__29_1_resolve_reference, 1);
  func__32_1_to_paragraphs = create_function(entry__32_1_to_paragraphs, 1);
  string__33_5 = from_latin_1_string("html/", 5);
  string__33_6 = from_latin_1_string(".html", 5);
  string__33_16 = from_latin_1_string("](", 2);
  string__33_17 = from_latin_1_string(".html)/[", 8);
  string__33_18 = from_latin_1_string(".html)", 6);
  string__33_30 = from_latin_1_string("Missing documentation for ", 26);
  string__33_31 = from_latin_1_string("!", 1);
  string__33_40 = from_latin_1_string("Parameter", 9);
  string__33_50 = from_latin_1_string(" (optional)", 11);
  string__33_57 = from_latin_1_string(" (zero or more arguments)", 25);
  string__33_66 = from_latin_1_string(" (optional; default value: ", 27);
  string__33_67 = from_latin_1_string(")", 1);
  string__33_76 = from_latin_1_string("Returns", 7);
  string__33_99 = from_latin_1_string("See also:", 9);
  string__33_128 = from_latin_1_string("Technical Details:", 18);
  string__33_146 = from_latin_1_string("[", 1);
  func__33_141 = create_function(entry__33_141, 1);
  func__33_193 = create_function(entry__33_193, 0);
  func__33_197 = create_function(entry__33_197, 0);
  string__33_204 = from_latin_1_string("Parameters", 10);
  func__33_207 = create_function(entry__33_207, 1);
  func__33_217 = create_function(entry__33_217, 1);
  string__33_225 = from_latin_1_string("Description", 11);
  func__33_227 = create_function(entry__33_227, 1);
  string__33_231 = from_latin_1_string("Technical Details", 17);
  func__33_233 = create_function(entry__33_233, 1);
  string__33_237 = from_latin_1_string("See also", 8);
  func__33_240 = create_function(entry__33_240, 1);
  string__33_250 = from_latin_1_string("Implemented by", 14);
  string__33_262 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__33_272 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__33_283 = from_latin_1_string("&nbsp;", 6);
  string__33_299 = from_latin_1_string("class", 5);
  func__33_306 = create_function(entry__33_306, 1);
  string__33_308 = from_latin_1_string("**", 2);
  string__33_313 = from_latin_1_string("footer", 6);
  string__33_317 = from_latin_1_string("(defined in ", 12);
  string__33_318 = from_latin_1_string(")\012", 2);
  func__33_1_create_info_page = create_function(entry__33_1_create_info_page, 2);
  string__34_3 = from_latin_1_string("p", 1);
  string__34_6 = from_latin_1_string("&lt;", 4);
  string__34_13 = from_latin_1_string("<a href=\042", 9);
  string__34_14 = from_latin_1_string(".html\042>", 7);
  string__34_15 = from_latin_1_string("</a>", 4);
  func__34_8 = create_function(entry__34_8, 1);
  func__34_2_html__encode = create_function(entry__34_2_html__encode, 3);
  func__34_23 = create_function(entry__34_23, 2);
  string__34_55 = from_latin_1_string("html/type_index.html", 20);
  func__34_56 = create_function(entry__34_56, 0);
  string__34_95 = from_latin_1_string("html/symbol_index.html", 22);
  string__34_98 = from_latin_1_string("id", 2);
  string__34_99 = from_latin_1_string("index", 5);
  string__34_103 = from_latin_1_string("#", 1);
  func__34_102 = create_function(entry__34_102, 1);
  string__34_108 = from_latin_1_string(" ", 1);
  func__34_107 = create_function(entry__34_107, 0);
  string__34_119 = from_latin_1_string("colspan", 7);
  string__34_126 = from_latin_1_string("#index", 6);
  string__34_128 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__34_143 = from_latin_1_string("function", 8);
  func__34_142 = create_function(entry__34_142, 0);
  string__34_145 = from_latin_1_string("inline-C function", 17);
  func__34_144 = create_function(entry__34_144, 0);
  string__34_147 = from_latin_1_string("polymorphic function", 20);
  func__34_146 = create_function(entry__34_146, 0);
  string__34_149 = from_latin_1_string("unique item", 11);
  func__34_148 = create_function(entry__34_148, 0);
  string__34_151 = from_latin_1_string("constant", 8);
  func__34_150 = create_function(entry__34_150, 0);
  func__34_152 = create_function(entry__34_152, 0);
  func__34_153 = create_function(entry__34_153, 0);
  string__34_159 = from_latin_1_string(" (", 2);
  string__34_169 = from_latin_1_string("align", 5);
  string__34_170 = from_latin_1_string("right", 5);
  string__34_180 = from_latin_1_string("remark", 6);
  func__34_111 = create_function(entry__34_111, 0);
  func__34_96 = create_function(entry__34_96, 0);
  string__34_190 = from_latin_1_string("/", 1);
  func__34_183 = create_function(entry__34_183, 2);
  string__34_193 = from_latin_1_string("html/topic_index.html", 21);
  string__34_201 = from_latin_1_string("_", 1);
  func__34_199 = create_function(entry__34_199, 2);
  func__34_198 = create_function(entry__34_198, 0);
  func__34_194 = create_function(entry__34_194, 0);
  func__34_219 = create_function(entry__34_219, 1);
  func__34_209 = create_function(entry__34_209, 2);
  string__34_226 = from_latin_1_string("html/index.html", 15);
  string__34_228 = from_latin_1_string("Simplicity", 10);
  func__34_230 = create_function(entry__34_230, 0);
  func__34_233 = create_function(entry__34_233, 0);
  func__34_236 = create_function(entry__34_236, 0);
  func__34_239 = create_function(entry__34_239, 0);
  func__34_227 = create_function(entry__34_227, 0);
  string__34_299 = from_latin_1_string("total definitions:     ", 23);
  string__34_300 = from_latin_1_string("\012\012types:                 ", 25);
  string__34_301 = from_latin_1_string("\012functions:             ", 24);
  string__34_302 = from_latin_1_string("\012polymorphic functions: ", 24);
  string__34_303 = from_latin_1_string("\012polymorphic attributes:", 24);
  string__34_304 = from_latin_1_string("\012method definitions:    ", 24);
  string__34_305 = from_latin_1_string("\012inline C methods:      ", 24);
  string__34_306 = from_latin_1_string("\012attribute definitions: ", 24);
  string__34_307 = from_latin_1_string("\012inline C functions:    ", 24);
  string__34_308 = from_latin_1_string("\012unique items:          ", 24);
  string__34_309 = from_latin_1_string("\012other constants:       ", 24);
  string__34_310 = from_latin_1_string("\012variables:             ", 24);
  string__34_311 = from_latin_1_string("\012\012other:                 ", 25);
  func__34_242 = create_function(entry__34_242, 0);
  func__34_1_sim2c__extract_documentation = create_function(entry__34_1_sim2c__extract_documentation, 1);
  string__64_1 = from_latin_1_string("Topics", 6);
  string__64_2 = from_latin_1_string("Topic", 5);
  string__65_1 = from_latin_1_string("Example", 7);
  string__65_2 = from_latin_1_string("Output", 6);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__extractor(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  assign_value(&var._BORING, unique__BORING);
  assign_value(&var._TYPE, unique__TYPE);
  assign_value(&var._FUNCTION, unique__FUNCTION);
  assign_value(&var._POLYMORPHIC_FUNCTION, unique__POLYMORPHIC_FUNCTION);
  assign_value(&var._POLYMORPHIC_ATTRIBUTE, unique__POLYMORPHIC_ATTRIBUTE);
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
  use_read_only(NULL, "do_print_summary", &get__do_print_summary, &get_value_or_future__do_print_summary);
  use_read_only(NULL, "do_print_warnings", &get__do_print_warnings, &get_value_or_future__do_print_warnings);
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "emit", &get__emit, &get_value_or_future__emit);
  use_read_only(NULL, "empty_insert_order_set", &get__empty_insert_order_set, &get_value_or_future__empty_insert_order_set);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_key_order_set", &get__empty_key_order_set, &get_value_or_future__empty_key_order_set);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
  use_read_only(NULL, "ewriteln", &get__ewriteln, &get_value_or_future__ewriteln);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "from_to", &get__from_to, &get_value_or_future__from_to);
  use_read_only(NULL, "from_utf8", &get__from_utf8, &get_value_or_future__from_utf8);
  use_read_only(NULL, "fullname_of", &get__fullname_of, &get_value_or_future__fullname_of);
  use_read_only(NULL, "has_prefix", &get__has_prefix, &get_value_or_future__has_prefix);
  use_read_only(NULL, "has_suffix", &get__has_suffix, &get_value_or_future__has_suffix);
  use_single_assign_dynamic("html", "encode", &get__html__encode, &define__html__encode);
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
  assign_variable(&var._create_page, &func__20_1_create_page);
  assign_variable(&var._extract_documentation_from_file, &func__22_1_extract_documentation_from_file);
  assign_variable(&var._extract_documentation_from_directory, &func__23_1_extract_documentation_from_directory);
  assign_variable(&var._resolved_name, &func__24_1_resolved_name);
  assign_variable(&var._add_derived_type, &func__25_1_add_derived_type);
  assign_variable(&var._mangled, &func__26_1_mangled);
  assign_variable(&var._ordered_name, &func__27_1_ordered_name);
  assign_variable(&var._link_bar, &func__28_1_link_bar);
  assign_variable(&var._resolve_reference, &func__29_1_resolve_reference);
  assign_variable(&var._to_paragraphs, &func__32_1_to_paragraphs);
  assign_variable(&var._create_info_page, &func__33_1_create_info_page);
  assign_variable(&var.sim2c__extract_documentation, &func__34_1_sim2c__extract_documentation);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
