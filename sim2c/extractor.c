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
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
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
  NODE *_INLINE_C_FUNCTION;
  NODE *_UNIQUE_ITEM;
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
  "INLINE_C_FUNCTION",
  "UNIQUE_ITEM",
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
static NODE *unique__9_1;
static NODE *unique__10_1;
static NODE *unique__11_1;
static NODE *unique__12_1;
static NODE *unique__13_1;
static NODE *func__16_1;
static void entry__16_1(void);
static FRAME_INFO frame__16_1 = {3, {"filename", "body", "page"}};
static NODE *func__16_2;
static void entry__16_2(void);
static FRAME_INFO frame__16_2 = {1, {"body"}};
static NODE *func__16_3;
static void entry__16_3(void);
static FRAME_INFO frame__16_3 = {1, {"body"}};
static NODE *func__16_4;
static void entry__16_4(void);
static FRAME_INFO frame__16_4 = {0, {}};
static NODE *string__16_5;
static void cont__16_6(void);
static void cont__16_7(void);
static NODE *func__18_1;
static void entry__18_1(void);
static FRAME_INFO frame__18_1 = {7, {"filename", "return__1", "buf", "fragments", "trees", "first_idx", "local_method_names"}};
static NODE *string__18_2;
static NODE *string__18_3;
static void cont__18_4(void);
static void cont__18_5(void);
static void cont__18_6(void);
static void cont__18_7(void);
static void cont__18_8(void);
static void cont__18_9(void);
static NODE *func__18_10;
static void entry__18_10(void);
static FRAME_INFO frame__18_10 = {0, {}};
static NODE *string__18_11;
static void cont__18_12(void);
static void cont__18_13(void);
static void cont__18_14(void);
static void cont__18_15(void);
static NODE *func__18_16;
static void entry__18_16(void);
static FRAME_INFO frame__18_16 = {0, {}};
static NODE *string__18_17;
static void cont__18_18(void);
static void cont__18_19(void);
static void cont__18_20(void);
static void cont__18_21(void);
static void cont__18_22(void);
static NODE *func__18_23;
static void entry__18_23(void);
static FRAME_INFO frame__18_23 = {0, {}};
static NODE *string__18_24;
static void cont__18_25(void);
static NODE *string__18_26;
static void cont__18_27(void);
static NODE *string__18_28;
static void cont__18_29(void);
static void cont__18_30(void);
static void cont__18_31(void);
static NODE *func__18_32;
static void entry__18_32(void);
static FRAME_INFO frame__18_32 = {1, {"fragment"}};
static void cont__18_33(void);
static void cont__18_34(void);
static NODE *func__18_35;
static void entry__18_35(void);
static FRAME_INFO frame__18_35 = {3, {"done", "fragments", "first_idx"}};
static NODE *func__18_36;
static void entry__18_36(void);
static FRAME_INFO frame__18_36 = {4, {"idx", "fragment", "first_idx", "done"}};
static void cont__18_37(void);
static void cont__18_38(void);
static NODE *func__18_39;
static void entry__18_39(void);
static FRAME_INFO frame__18_39 = {2, {"first_idx", "idx"}};
static void cont__18_40(void);
static NODE *func__18_41;
static void entry__18_41(void);
static FRAME_INFO frame__18_41 = {4, {"first_idx", "idx", "fragment", "tree"}};
static void cont__18_42(void);
static void cont__18_43(void);
static NODE *func__18_44;
static void entry__18_44(void);
static FRAME_INFO frame__18_44 = {1, {"done"}};
static void cont__18_45(void);
static void cont__18_46(void);
static void cont__18_47(void);
static void cont__18_48(void);
static NODE *func__18_49;
static void entry__18_49(void);
static FRAME_INFO frame__18_49 = {2, {"fragment", "trees"}};
static void cont__18_50(void);
static void cont__18_51(void);
static void cont__18_52(void);
static void cont__18_53(void);
static NODE *func__18_54;
static void entry__18_54(void);
static FRAME_INFO frame__18_54 = {0, {}};
static NODE *string__18_55;
static void cont__18_56(void);
static void cont__18_57(void);
static NODE *func__18_58;
static void entry__18_58(void);
static FRAME_INFO frame__18_58 = {2, {"statement", "local_method_names"}};
static NODE *func__18_59;
static void entry__18_59(void);
static FRAME_INFO frame__18_59 = {1, {"statement"}};
static void cont__18_60(void);
static NODE *func__18_61;
static void entry__18_61(void);
static FRAME_INFO frame__18_61 = {0, {}};
static NODE *func__18_62;
static void entry__18_62(void);
static FRAME_INFO frame__18_62 = {1, {"statement"}};
static void cont__18_63(void);
static NODE *func__18_64;
static void entry__18_64(void);
static FRAME_INFO frame__18_64 = {0, {}};
static NODE *func__18_65;
static void entry__18_65(void);
static FRAME_INFO frame__18_65 = {2, {"statement", "local_method_names"}};
static void cont__18_66(void);
static NODE *func__18_67;
static void entry__18_67(void);
static FRAME_INFO frame__18_67 = {3, {"statement", "local_method_names", "destination"}};
static void cont__18_68(void);
static void cont__18_69(void);
static void cont__18_70(void);
static NODE *func__18_71;
static void entry__18_71(void);
static FRAME_INFO frame__18_71 = {4, {"destination", "statement", "local_method_names", "identifier"}};
static void cont__18_72(void);
static void cont__18_73(void);
static void cont__18_74(void);
static NODE *func__18_75;
static void entry__18_75(void);
static FRAME_INFO frame__18_75 = {4, {"statement", "local_method_names", "destination", "source"}};
static void cont__18_76(void);
static void cont__18_77(void);
static void cont__18_78(void);
static NODE *func__18_79;
static void entry__18_79(void);
static FRAME_INFO frame__18_79 = {2, {"local_method_names", "destination"}};
static void cont__18_80(void);
static void cont__18_81(void);
static void cont__18_82(void);
static void cont__18_83(void);
static NODE *func__18_84;
static void entry__18_84(void);
static FRAME_INFO frame__18_84 = {4, {"statement", "break", "filename", "local_method_names"}};
static NODE *func__18_85;
static void entry__18_85(void);
static FRAME_INFO frame__18_85 = {1, {"statement"}};
static void cont__18_86(void);
static NODE *func__18_87;
static void entry__18_87(void);
static FRAME_INFO frame__18_87 = {0, {}};
static NODE *func__18_88;
static void entry__18_88(void);
static FRAME_INFO frame__18_88 = {2, {"statement", "filename"}};
static void cont__18_89(void);
static NODE *func__18_90;
static void entry__18_90(void);
static FRAME_INFO frame__18_90 = {2, {"statement", "filename"}};
static void cont__18_91(void);
static NODE *string__18_92;
static void cont__18_93(void);
static NODE *func__18_94;
static void entry__18_94(void);
static FRAME_INFO frame__18_94 = {4, {"statement", "filename", "identifier", "namespace"}};
static void cont__18_95(void);
static void cont__18_96(void);
static void cont__18_97(void);
static NODE *func__18_98;
static void entry__18_98(void);
static FRAME_INFO frame__18_98 = {6, {"identifier", "statement", "namespace", "filename", "name", "base"}};
static void cont__18_99(void);
static void cont__18_100(void);
static void cont__18_101(void);
static void cont__18_102(void);
static NODE *func__18_103;
static void entry__18_103(void);
static FRAME_INFO frame__18_103 = {1, {"base"}};
static void cont__18_104(void);
static NODE *func__18_105;
static void entry__18_105(void);
static FRAME_INFO frame__18_105 = {0, {}};
static void cont__18_106(void);
static void cont__18_107(void);
static void cont__18_108(void);
static void cont__18_109(void);
static NODE *func__18_110;
static void entry__18_110(void);
static FRAME_INFO frame__18_110 = {4, {"statement", "filename", "break", "local_method_names"}};
static void cont__18_111(void);
static NODE *func__18_112;
static void entry__18_112(void);
static FRAME_INFO frame__18_112 = {6, {"statement", "filename", "break", "local_method_names", "destination", "info"}};
static void cont__18_113(void);
static void cont__18_114(void);
static void cont__18_115(void);
static NODE *func__18_116;
static void entry__18_116(void);
static FRAME_INFO frame__18_116 = {7, {"destination", "info", "statement", "break", "local_method_names", "identifier", "namespace"}};
static void cont__18_117(void);
static void cont__18_118(void);
static void cont__18_119(void);
static NODE *func__18_120;
static void entry__18_120(void);
static FRAME_INFO frame__18_120 = {10, {"identifier", "namespace", "info", "statement", "break", "destination", "local_method_names", "name", "iname", "source"}};
static void cont__18_121(void);
static void cont__18_122(void);
static void cont__18_123(void);
static void cont__18_124(void);
static void cont__18_125(void);
static NODE *func__18_126;
static void entry__18_126(void);
static FRAME_INFO frame__18_126 = {7, {"source", "name", "namespace", "iname", "info", "statement", "break"}};
static void cont__18_127(void);
static NODE *func__18_128;
static void entry__18_128(void);
static FRAME_INFO frame__18_128 = {6, {"name", "namespace", "iname", "info", "statement", "break"}};
static void cont__18_129(void);
static void cont__18_130(void);
static void cont__18_131(void);
static NODE *func__18_132;
static void entry__18_132(void);
static FRAME_INFO frame__18_132 = {2, {"source", "info"}};
static void cont__18_133(void);
static NODE *func__18_134;
static void entry__18_134(void);
static FRAME_INFO frame__18_134 = {2, {"info", "source"}};
static NODE *string__18_135;
static void cont__18_136(void);
static void cont__18_137(void);
static NODE *func__18_138;
static void entry__18_138(void);
static FRAME_INFO frame__18_138 = {3, {"source", "info", "statement"}};
static void cont__18_139(void);
static NODE *func__18_140;
static void entry__18_140(void);
static FRAME_INFO frame__18_140 = {2, {"info", "statement"}};
static void cont__18_141(void);
static NODE *func__18_142;
static void entry__18_142(void);
static FRAME_INFO frame__18_142 = {3, {"source", "info", "statement"}};
static void cont__18_143(void);
static NODE *func__18_144;
static void entry__18_144(void);
static FRAME_INFO frame__18_144 = {3, {"source", "info", "statement"}};
static void cont__18_145(void);
static void cont__18_146(void);
static NODE *func__18_147;
static void entry__18_147(void);
static FRAME_INFO frame__18_147 = {3, {"info", "source", "statement"}};
static void cont__18_148(void);
static void cont__18_149(void);
static NODE *func__18_150;
static void entry__18_150(void);
static FRAME_INFO frame__18_150 = {5, {"source", "iname", "info", "statement", "break"}};
static void cont__18_151(void);
static NODE *func__18_152;
static void entry__18_152(void);
static FRAME_INFO frame__18_152 = {4, {"iname", "info", "statement", "break"}};
static void cont__18_153(void);
static void cont__18_154(void);
static void cont__18_155(void);
static void cont__18_156(void);
static NODE *func__18_157;
static void entry__18_157(void);
static FRAME_INFO frame__18_157 = {3, {"iname", "info", "previous_definition"}};
static void cont__18_158(void);
static void cont__18_159(void);
static NODE *func__18_160;
static void entry__18_160(void);
static FRAME_INFO frame__18_160 = {2, {"previous_definition", "info"}};
static void cont__18_161(void);
static void cont__18_162(void);
static NODE *func__18_163;
static void entry__18_163(void);
static FRAME_INFO frame__18_163 = {2, {"info", "previous_definition"}};
static void cont__18_164(void);
static void cont__18_165(void);
static void cont__18_166(void);
static void cont__18_167(void);
static void cont__18_168(void);
static void cont__18_169(void);
static NODE *func__18_170;
static void entry__18_170(void);
static FRAME_INFO frame__18_170 = {6, {"destination", "iname", "local_method_names", "info", "attr", "type"}};
static void cont__18_171(void);
static void cont__18_172(void);
static void cont__18_173(void);
static void cont__18_174(void);
static void cont__18_175(void);
static NODE *func__18_176;
static void entry__18_176(void);
static FRAME_INFO frame__18_176 = {5, {"attr", "local_method_names", "iname", "info", "attr_name"}};
static void cont__18_177(void);
static void cont__18_178(void);
static NODE *func__18_179;
static void entry__18_179(void);
static FRAME_INFO frame__18_179 = {5, {"attr", "iname", "attr_name", "info", "definition"}};
static void cont__18_180(void);
static void cont__18_181(void);
static NODE *func__18_182;
static void entry__18_182(void);
static FRAME_INFO frame__18_182 = {1, {"attr"}};
static void cont__18_183(void);
static void cont__18_184(void);
static void cont__18_185(void);
static void cont__18_186(void);
static void cont__18_187(void);
static void cont__18_188(void);
static void cont__18_189(void);
static void cont__18_190(void);
static NODE *func__19_1;
static void entry__19_1(void);
static FRAME_INFO frame__19_1 = {1, {"path"}};
static void cont__19_2(void);
static void cont__19_3(void);
static NODE *func__19_4;
static void entry__19_4(void);
static FRAME_INFO frame__19_4 = {2, {"entry", "name"}};
static void cont__19_5(void);
static NODE *func__19_6;
static void entry__19_6(void);
static FRAME_INFO frame__19_6 = {2, {"entry", "name"}};
static void cont__19_7(void);
static NODE *func__19_8;
static void entry__19_8(void);
static FRAME_INFO frame__19_8 = {1, {"name"}};
static NODE *func__19_9;
static void entry__19_9(void);
static FRAME_INFO frame__19_9 = {1, {"name"}};
static void cont__19_10(void);
static NODE *func__19_11;
static void entry__19_11(void);
static FRAME_INFO frame__19_11 = {1, {"name"}};
static NODE *func__20_1;
static void entry__20_1(void);
static FRAME_INFO frame__20_1 = {2, {"attr", "name"}};
static void cont__20_2(void);
static void cont__20_3(void);
static void cont__20_4(void);
static NODE *func__20_5;
static void entry__20_5(void);
static FRAME_INFO frame__20_5 = {1, {"attr"}};
static void cont__20_6(void);
static NODE *func__20_7;
static void entry__20_7(void);
static FRAME_INFO frame__20_7 = {3, {"attr", "name", "resolved_namespace"}};
static void cont__20_8(void);
static NODE *func__20_9;
static void entry__20_9(void);
static FRAME_INFO frame__20_9 = {3, {"namespace", "name", "resolved_namespace"}};
static void cont__20_10(void);
static NODE *func__20_11;
static void entry__20_11(void);
static FRAME_INFO frame__20_11 = {3, {"resolved_namespace", "name", "namespace"}};
static void cont__20_12(void);
static NODE *func__20_13;
static void entry__20_13(void);
static FRAME_INFO frame__20_13 = {1, {"name"}};
static NODE *string__20_14;
static NODE *string__20_15;
static void cont__20_16(void);
static void cont__20_17(void);
static void cont__20_18(void);
static void cont__20_19(void);
static NODE *func__20_20;
static void entry__20_20(void);
static FRAME_INFO frame__20_20 = {1, {"name"}};
static NODE *string__20_21;
static void cont__20_22(void);
static void cont__20_23(void);
static NODE *string__20_24;
static void cont__20_25(void);
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {4, {"base", "name", "ibase", "definition"}};
static void cont__21_2(void);
static void cont__21_3(void);
static void cont__21_4(void);
static void cont__21_5(void);
static void cont__21_6(void);
static NODE *func__21_7;
static void entry__21_7(void);
static FRAME_INFO frame__21_7 = {3, {"definition", "name", "ibase"}};
static void cont__21_8(void);
static void cont__21_9(void);
static void cont__21_10(void);
static void cont__21_11(void);
static NODE *func__21_12;
static void entry__21_12(void);
static FRAME_INFO frame__21_12 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__21_13(void);
static void cont__21_14(void);
static NODE *func__21_15;
static void entry__21_15(void);
static FRAME_INFO frame__21_15 = {2, {"base_of_base", "ibase"}};
static void cont__21_16(void);
static void cont__21_17(void);
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {1, {"name"}};
static void cont__22_2(void);
static NODE *string__22_3;
static void cont__22_4(void);
static void cont__22_5(void);
static NODE *func__23_1;
static void entry__23_1(void);
static FRAME_INFO frame__23_1 = {2, {"namespace", "name"}};
static void cont__23_2(void);
static void cont__23_3(void);
static void cont__23_4(void);
static NODE *func__24_1;
static void entry__24_1(void);
static FRAME_INFO frame__24_1 = {0, {}};
static NODE *func__24_2;
static void entry__24_2(void);
static FRAME_INFO frame__24_2 = {0, {}};
static NODE *string__24_3;
static NODE *string__24_4;
static void cont__24_5(void);
static NODE *string__24_6;
static void cont__24_7(void);
static NODE *string__24_8;
static void cont__24_9(void);
static NODE *string__24_10;
static void cont__24_11(void);
static NODE *string__24_12;
static void cont__24_13(void);
static void cont__24_14(void);
static NODE *string__24_15;
static void cont__24_16(void);
static NODE *string__24_17;
static void cont__24_18(void);
static void cont__24_19(void);
static NODE *string__24_20;
static void cont__24_21(void);
static NODE *string__24_22;
static void cont__24_23(void);
static void cont__24_24(void);
static NODE *string__24_25;
static void cont__24_26(void);
static NODE *string__24_27;
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {1, {"reference"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__25_4(void);
static void cont__25_5(void);
static void cont__25_6(void);
static NODE *func__25_7;
static void entry__25_7(void);
static FRAME_INFO frame__25_7 = {1, {"type_name"}};
static NODE *string__25_8;
static void cont__25_9(void);
static void cont__25_10(void);
static void cont__25_11(void);
static NODE *func__25_12;
static void entry__25_12(void);
static FRAME_INFO frame__25_12 = {1, {"method_name"}};
static NODE *string__25_13;
static void cont__25_14(void);
static void cont__25_15(void);
static void cont__25_16(void);
static NODE *func__25_17;
static void entry__25_17(void);
static FRAME_INFO frame__25_17 = {1, {"reference"}};
static void cont__25_18(void);
static NODE *func__25_19;
static void entry__25_19(void);
static FRAME_INFO frame__25_19 = {1, {"reference"}};
static void cont__25_20(void);
static void cont__25_21(void);
static NODE *func__28_1;
static void entry__28_1(void);
static FRAME_INFO frame__28_1 = {4, {"lines", "paragraphs", "text", "pre_mode"}};
static NODE *func__28_2;
static void entry__28_2(void);
static FRAME_INFO frame__28_2 = {4, {"line", "pre_mode", "text", "paragraphs"}};
static NODE *func__28_3;
static void entry__28_3(void);
static FRAME_INFO frame__28_3 = {3, {"line", "text", "paragraphs"}};
static void cont__28_4(void);
static NODE *func__28_5;
static void entry__28_5(void);
static FRAME_INFO frame__28_5 = {3, {"text", "paragraphs", "line"}};
static void cont__28_6(void);
static void cont__28_7(void);
static NODE *func__28_8;
static void entry__28_8(void);
static FRAME_INFO frame__28_8 = {2, {"text", "line"}};
static void cont__28_9(void);
static NODE *func__28_10;
static void entry__28_10(void);
static FRAME_INFO frame__28_10 = {4, {"line", "text", "paragraphs", "pre_mode"}};
static void cont__28_11(void);
static NODE *func__28_12;
static void entry__28_12(void);
static FRAME_INFO frame__28_12 = {2, {"text", "paragraphs"}};
static void cont__28_13(void);
static void cont__28_14(void);
static NODE *func__28_15;
static void entry__28_15(void);
static FRAME_INFO frame__28_15 = {2, {"paragraphs", "text"}};
static void cont__28_16(void);
static NODE *func__28_17;
static void entry__28_17(void);
static FRAME_INFO frame__28_17 = {3, {"text", "line", "pre_mode"}};
static void cont__28_18(void);
static NODE *func__28_19;
static void entry__28_19(void);
static FRAME_INFO frame__28_19 = {2, {"line", "pre_mode"}};
static void cont__28_20(void);
static NODE *func__28_21;
static void entry__28_21(void);
static FRAME_INFO frame__28_21 = {1, {"pre_mode"}};
static NODE *func__28_22;
static void entry__28_22(void);
static FRAME_INFO frame__28_22 = {1, {"text"}};
static void cont__28_23(void);
static void cont__28_24(void);
static void cont__28_25(void);
static void cont__28_26(void);
static void cont__28_27(void);
static void cont__28_28(void);
static void cont__28_29(void);
static NODE *func__28_30;
static void entry__28_30(void);
static FRAME_INFO frame__28_30 = {2, {"paragraphs", "text"}};
static void cont__28_31(void);
static void cont__28_32(void);
static NODE *func__29_1;
static void entry__29_1(void);
static FRAME_INFO frame__29_1 = {2, {"function_name", "info"}};
static void cont__29_2(void);
static NODE *func__29_3;
static void entry__29_3(void);
static FRAME_INFO frame__29_3 = {2, {"function_name", "info"}};
static void cont__29_4(void);
static NODE *string__29_5;
static NODE *string__29_6;
static void cont__29_7(void);
static NODE *func__29_8;
static void entry__29_8(void);
static FRAME_INFO frame__29_8 = {11, {"function_name", "info", "short_description", "parameters", "return_values", "descriptions", "technical_details", "references", "examples", "remark_lines", "function_basename"}};
static void cont__29_9(void);
static void cont__29_10(void);
static NODE *func__29_11;
static void entry__29_11(void);
static FRAME_INFO frame__29_11 = {3, {"function_name", "type", "method"}};
static void cont__29_12(void);
static void cont__29_13(void);
static void cont__29_14(void);
static void cont__29_15(void);
static NODE *string__29_16;
static NODE *string__29_17;
static NODE *string__29_18;
static void cont__29_19(void);
static NODE *func__29_20;
static void entry__29_20(void);
static FRAME_INFO frame__29_20 = {1, {"function_name"}};
static void cont__29_21(void);
static void cont__29_22(void);
static void cont__29_23(void);
static NODE *func__29_24;
static void entry__29_24(void);
static FRAME_INFO frame__29_24 = {10, {"remark_lines", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions", "paragraphs"}};
static void cont__29_25(void);
static NODE *func__29_26;
static void entry__29_26(void);
static FRAME_INFO frame__29_26 = {9, {"paragraph", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions"}};
static NODE *func__29_27;
static void entry__29_27(void);
static FRAME_INFO frame__29_27 = {2, {"paragraph", "parameters"}};
static void cont__29_28(void);
static NODE *string__29_29;
static void cont__29_30(void);
static void cont__29_31(void);
static NODE *func__29_32;
static void entry__29_32(void);
static FRAME_INFO frame__29_32 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__29_33(void);
static NODE *func__29_34;
static void entry__29_34(void);
static FRAME_INFO frame__29_34 = {1, {"parameter"}};
static void cont__29_35(void);
static NODE *func__29_36;
static void entry__29_36(void);
static FRAME_INFO frame__29_36 = {1, {"parameter"}};
static void cont__29_37(void);
static void cont__29_38(void);
static NODE *string__29_39;
static void cont__29_40(void);
static NODE *func__29_41;
static void entry__29_41(void);
static FRAME_INFO frame__29_41 = {1, {"parameter"}};
static void cont__29_42(void);
static NODE *func__29_43;
static void entry__29_43(void);
static FRAME_INFO frame__29_43 = {1, {"parameter"}};
static void cont__29_44(void);
static void cont__29_45(void);
static NODE *string__29_46;
static void cont__29_47(void);
static NODE *func__29_48;
static void entry__29_48(void);
static FRAME_INFO frame__29_48 = {1, {"parameter"}};
static void cont__29_49(void);
static NODE *func__29_50;
static void entry__29_50(void);
static FRAME_INFO frame__29_50 = {1, {"parameter"}};
static void cont__29_51(void);
static void cont__29_52(void);
static void cont__29_53(void);
static void cont__29_54(void);
static NODE *string__29_55;
static NODE *string__29_56;
static void cont__29_57(void);
static void cont__29_58(void);
static void cont__29_59(void);
static void cont__29_60(void);
static void cont__29_61(void);
static void cont__29_62(void);
static NODE *func__29_63;
static void entry__29_63(void);
static FRAME_INFO frame__29_63 = {2, {"paragraph", "return_values"}};
static void cont__29_64(void);
static NODE *string__29_65;
static void cont__29_66(void);
static void cont__29_67(void);
static NODE *func__29_68;
static void entry__29_68(void);
static FRAME_INFO frame__29_68 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__29_69(void);
static NODE *func__29_70;
static void entry__29_70(void);
static FRAME_INFO frame__29_70 = {1, {"return_value"}};
static void cont__29_71(void);
static NODE *func__29_72;
static void entry__29_72(void);
static FRAME_INFO frame__29_72 = {1, {"return_value"}};
static void cont__29_73(void);
static void cont__29_74(void);
static void cont__29_75(void);
static NODE *func__29_76;
static void entry__29_76(void);
static FRAME_INFO frame__29_76 = {1, {"return_value"}};
static void cont__29_77(void);
static NODE *func__29_78;
static void entry__29_78(void);
static FRAME_INFO frame__29_78 = {1, {"return_value"}};
static void cont__29_79(void);
static void cont__29_80(void);
static void cont__29_81(void);
static void cont__29_82(void);
static void cont__29_83(void);
static void cont__29_84(void);
static void cont__29_85(void);
static void cont__29_86(void);
static NODE *func__29_87;
static void entry__29_87(void);
static FRAME_INFO frame__29_87 = {2, {"paragraph", "references"}};
static NODE *string__29_88;
static void cont__29_89(void);
static NODE *func__29_90;
static void entry__29_90(void);
static FRAME_INFO frame__29_90 = {2, {"paragraph", "references"}};
static void cont__29_91(void);
static void cont__29_92(void);
static NODE *func__29_93;
static void entry__29_93(void);
static FRAME_INFO frame__29_93 = {2, {"reference", "references"}};
static void cont__29_94(void);
static void cont__29_95(void);
static NODE *func__29_96;
static void entry__29_96(void);
static FRAME_INFO frame__29_96 = {2, {"paragraph", "function_name"}};
static void cont__29_97(void);
static NODE *func__29_98;
static void entry__29_98(void);
static FRAME_INFO frame__29_98 = {2, {"paragraph", "function_name"}};
static void cont__29_99(void);
static void cont__29_100(void);
static NODE *func__29_101;
static void entry__29_101(void);
static FRAME_INFO frame__29_101 = {3, {"topic", "function_name", "topic_contents"}};
static void cont__29_102(void);
static void cont__29_103(void);
static void cont__29_104(void);
static void cont__29_105(void);
static void cont__29_106(void);
static NODE *func__29_107;
static void entry__29_107(void);
static FRAME_INFO frame__29_107 = {2, {"paragraph", "examples"}};
static void cont__29_108(void);
static NODE *func__29_109;
static void entry__29_109(void);
static FRAME_INFO frame__29_109 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__29_110(void);
static void cont__29_111(void);
static void cont__29_112(void);
static void cont__29_113(void);
static void cont__29_114(void);
static void cont__29_115(void);
static NODE *func__29_116;
static void entry__29_116(void);
static FRAME_INFO frame__29_116 = {2, {"paragraph", "technical_details"}};
static NODE *string__29_117;
static void cont__29_118(void);
static NODE *func__29_119;
static void entry__29_119(void);
static FRAME_INFO frame__29_119 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__29_120(void);
static void cont__29_121(void);
static void cont__29_122(void);
static NODE *func__29_123;
static void entry__29_123(void);
static FRAME_INFO frame__29_123 = {1, {"technical_details"}};
static NODE *func__29_124;
static void entry__29_124(void);
static FRAME_INFO frame__29_124 = {2, {"technical_details", "detail"}};
static void cont__29_125(void);
static NODE *func__29_126;
static void entry__29_126(void);
static FRAME_INFO frame__29_126 = {4, {"paragraph", "short_description", "technical_details", "descriptions"}};
static void cont__29_127(void);
static void cont__29_128(void);
static void cont__29_129(void);
static NODE *func__29_130;
static void entry__29_130(void);
static FRAME_INFO frame__29_130 = {1, {"reference"}};
static void cont__29_131(void);
static void cont__29_132(void);
static void cont__29_133(void);
static void cont__29_134(void);
static NODE *string__29_135;
static void cont__29_136(void);
static void cont__29_137(void);
static void cont__29_138(void);
static void cont__29_139(void);
static NODE *func__29_140;
static void entry__29_140(void);
static FRAME_INFO frame__29_140 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__29_141(void);
static NODE *func__29_142;
static void entry__29_142(void);
static FRAME_INFO frame__29_142 = {2, {"technical_details", "paragraph"}};
static void cont__29_143(void);
static NODE *func__29_144;
static void entry__29_144(void);
static FRAME_INFO frame__29_144 = {2, {"descriptions", "paragraph"}};
static void cont__29_145(void);
static NODE *func__29_146;
static void entry__29_146(void);
static FRAME_INFO frame__29_146 = {2, {"short_description", "paragraph"}};
static void cont__29_147(void);
static void cont__29_148(void);
static void cont__29_149(void);
static NODE *func__29_150;
static void entry__29_150(void);
static FRAME_INFO frame__29_150 = {2, {"info", "parameters"}};
static void cont__29_151(void);
static NODE *func__29_152;
static void entry__29_152(void);
static FRAME_INFO frame__29_152 = {2, {"parameter", "parameters"}};
static void cont__29_153(void);
static void cont__29_154(void);
static NODE *func__29_155;
static void entry__29_155(void);
static FRAME_INFO frame__29_155 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__29_156(void);
static void cont__29_157(void);
static void cont__29_158(void);
static NODE *func__29_159;
static void entry__29_159(void);
static FRAME_INFO frame__29_159 = {2, {"parameter", "name"}};
static void cont__29_160(void);
static NODE *func__29_161;
static void entry__29_161(void);
static FRAME_INFO frame__29_161 = {2, {"parameter", "name"}};
static void cont__29_162(void);
static void cont__29_163(void);
static NODE *func__29_164;
static void entry__29_164(void);
static FRAME_INFO frame__29_164 = {2, {"name", "parameter"}};
static void cont__29_165(void);
static void cont__29_166(void);
static void cont__29_167(void);
static NODE *func__29_168;
static void entry__29_168(void);
static FRAME_INFO frame__29_168 = {1, {"name"}};
static void cont__29_169(void);
static NODE *func__29_170;
static void entry__29_170(void);
static FRAME_INFO frame__29_170 = {2, {"parameter", "name"}};
static void cont__29_171(void);
static NODE *func__29_172;
static void entry__29_172(void);
static FRAME_INFO frame__29_172 = {1, {"name"}};
static void cont__29_173(void);
static void cont__29_174(void);
static void cont__29_175(void);
static void cont__29_176(void);
static void cont__29_177(void);
static NODE *func__29_178;
static void entry__29_178(void);
static FRAME_INFO frame__29_178 = {1, {"parameter"}};
static void cont__29_179(void);
static void cont__29_180(void);
static void cont__29_181(void);
static NODE *func__29_182;
static void entry__29_182(void);
static FRAME_INFO frame__29_182 = {0, {}};
static void cont__29_183(void);
static void cont__29_184(void);
static void cont__29_185(void);
static NODE *func__29_186;
static void entry__29_186(void);
static FRAME_INFO frame__29_186 = {0, {}};
static void cont__29_187(void);
static void cont__29_188(void);
static NODE *func__29_189;
static void entry__29_189(void);
static FRAME_INFO frame__29_189 = {1, {"short_description"}};
static void cont__29_190(void);
static void cont__29_191(void);
static NODE *func__29_192;
static void entry__29_192(void);
static FRAME_INFO frame__29_192 = {1, {"parameters"}};
static NODE *string__29_193;
static void cont__29_194(void);
static NODE *func__29_195;
static void entry__29_195(void);
static FRAME_INFO frame__29_195 = {1, {"parameters"}};
static NODE *func__29_196;
static void entry__29_196(void);
static FRAME_INFO frame__29_196 = {1, {"parameter"}};
static void cont__29_197(void);
static void cont__29_198(void);
static NODE *func__29_199;
static void entry__29_199(void);
static FRAME_INFO frame__29_199 = {1, {"parameter"}};
static void cont__29_200(void);
static void cont__29_201(void);
static void cont__29_202(void);
static NODE *func__29_203;
static void entry__29_203(void);
static FRAME_INFO frame__29_203 = {1, {"return_values"}};
static void cont__29_204(void);
static NODE *func__29_205;
static void entry__29_205(void);
static FRAME_INFO frame__29_205 = {1, {"return_values"}};
static NODE *func__29_206;
static void entry__29_206(void);
static FRAME_INFO frame__29_206 = {1, {"return_value"}};
static void cont__29_207(void);
static void cont__29_208(void);
static NODE *func__29_209;
static void entry__29_209(void);
static FRAME_INFO frame__29_209 = {1, {"return_value"}};
static void cont__29_210(void);
static void cont__29_211(void);
static void cont__29_212(void);
static NODE *func__29_213;
static void entry__29_213(void);
static FRAME_INFO frame__29_213 = {1, {"descriptions"}};
static NODE *string__29_214;
static void cont__29_215(void);
static NODE *func__29_216;
static void entry__29_216(void);
static FRAME_INFO frame__29_216 = {1, {"description"}};
static void cont__29_217(void);
static void cont__29_218(void);
static NODE *func__29_219;
static void entry__29_219(void);
static FRAME_INFO frame__29_219 = {1, {"technical_details"}};
static NODE *string__29_220;
static void cont__29_221(void);
static NODE *func__29_222;
static void entry__29_222(void);
static FRAME_INFO frame__29_222 = {1, {"detail"}};
static void cont__29_223(void);
static void cont__29_224(void);
static NODE *func__29_225;
static void entry__29_225(void);
static FRAME_INFO frame__29_225 = {1, {"references"}};
static NODE *string__29_226;
static void cont__29_227(void);
static NODE *func__29_228;
static void entry__29_228(void);
static FRAME_INFO frame__29_228 = {1, {"references"}};
static NODE *func__29_229;
static void entry__29_229(void);
static FRAME_INFO frame__29_229 = {1, {"reference"}};
static void cont__29_230(void);
static void cont__29_231(void);
static void cont__29_232(void);
static void cont__29_233(void);
static void cont__29_234(void);
static void cont__29_235(void);
static void cont__29_236(void);
static void cont__29_237(void);
static NODE *func__29_238;
static void entry__29_238(void);
static FRAME_INFO frame__29_238 = {2, {"info", "function_name"}};
static NODE *string__29_239;
static void cont__29_240(void);
static NODE *func__29_241;
static void entry__29_241(void);
static FRAME_INFO frame__29_241 = {2, {"info", "function_name"}};
static void cont__29_242(void);
static NODE *func__29_243;
static void entry__29_243(void);
static FRAME_INFO frame__29_243 = {3, {"name", "function_name", "method"}};
static void cont__29_244(void);
static NODE *func__29_245;
static void entry__29_245(void);
static FRAME_INFO frame__29_245 = {2, {"name", "method"}};
static NODE *func__29_246;
static void entry__29_246(void);
static FRAME_INFO frame__29_246 = {1, {"name"}};
static void cont__29_247(void);
static void cont__29_248(void);
static void cont__29_249(void);
static void cont__29_250(void);
static NODE *string__29_251;
static void cont__29_252(void);
static NODE *func__29_253;
static void entry__29_253(void);
static FRAME_INFO frame__29_253 = {1, {"method"}};
static void cont__29_254(void);
static void cont__29_255(void);
static void cont__29_256(void);
static void cont__29_257(void);
static void cont__29_258(void);
static void cont__29_259(void);
static NODE *func__29_260;
static void entry__29_260(void);
static FRAME_INFO frame__29_260 = {2, {"info", "function_name"}};
static NODE *string__29_261;
static void cont__29_262(void);
static NODE *func__29_263;
static void entry__29_263(void);
static FRAME_INFO frame__29_263 = {2, {"info", "function_name"}};
static void cont__29_264(void);
static NODE *func__29_265;
static void entry__29_265(void);
static FRAME_INFO frame__29_265 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__29_266;
static void entry__29_266(void);
static FRAME_INFO frame__29_266 = {2, {"method_name", "function_name"}};
static NODE *func__29_267;
static void entry__29_267(void);
static FRAME_INFO frame__29_267 = {1, {"method_name"}};
static void cont__29_268(void);
static void cont__29_269(void);
static void cont__29_270(void);
static void cont__29_271(void);
static NODE *string__29_272;
static void cont__29_273(void);
static NODE *func__29_274;
static void entry__29_274(void);
static FRAME_INFO frame__29_274 = {2, {"function_name", "method_name"}};
static void cont__29_275(void);
static void cont__29_276(void);
static void cont__29_277(void);
static void cont__29_278(void);
static void cont__29_279(void);
static void cont__29_280(void);
static void cont__29_281(void);
static NODE *func__29_282;
static void entry__29_282(void);
static FRAME_INFO frame__29_282 = {4, {"example", "function_basename", "title", "text"}};
static void cont__29_283(void);
static void cont__29_284(void);
static void cont__29_285(void);
static void cont__29_286(void);
static void cont__29_287(void);
static NODE *string__29_288;
static void cont__29_289(void);
static NODE *func__29_290;
static void entry__29_290(void);
static FRAME_INFO frame__29_290 = {2, {"text", "function_basename"}};
static void cont__29_291(void);
static void cont__29_292(void);
static void cont__29_293(void);
static void cont__29_294(void);
static NODE *func__29_295;
static void entry__29_295(void);
static FRAME_INFO frame__29_295 = {1, {"string_literal"}};
static void cont__29_296(void);
static NODE *string__29_297;
static void cont__29_298(void);
static void cont__29_299(void);
static void cont__29_300(void);
static void cont__29_301(void);
static NODE *string__29_302;
static void cont__29_303(void);
static void cont__29_304(void);
static void cont__29_305(void);
static NODE *string__29_306;
static NODE *string__29_307;
static void cont__29_308(void);
static NODE *func__30_1;
static void entry__30_1(void);
static FRAME_INFO frame__30_1 = {2, {"path", "return__1"}};
static NODE *func__30_2;
static void entry__30_2(void);
static FRAME_INFO frame__30_2 = {3, {"text", "tag", "arg_str"}};
static NODE *string__30_3;
static void cont__30_4(void);
static NODE *func__30_5;
static void entry__30_5(void);
static FRAME_INFO frame__30_5 = {1, {"text"}};
static NODE *string__30_6;
static void cont__30_7(void);
static NODE *func__30_8;
static void entry__30_8(void);
static FRAME_INFO frame__30_8 = {2, {"capture", "reference"}};
static void cont__30_9(void);
static void cont__30_10(void);
static void cont__30_11(void);
static void cont__30_12(void);
static NODE *string__30_13;
static NODE *string__30_14;
static NODE *string__30_15;
static void cont__30_16(void);
static void cont__30_17(void);
static void cont__30_18(void);
static void cont__30_19(void);
static void cont__30_20(void);
static void cont__30_21(void);
static void cont__30_22(void);
static NODE *func__30_23;
static void entry__30_23(void);
static FRAME_INFO frame__30_23 = {2, {"name", "info"}};
static void cont__30_24(void);
static void cont__30_25(void);
static NODE *func__30_26;
static void entry__30_26(void);
static FRAME_INFO frame__30_26 = {4, {"info", "name", "base", "methods"}};
static void cont__30_27(void);
static void cont__30_28(void);
static NODE *func__30_29;
static void entry__30_29(void);
static FRAME_INFO frame__30_29 = {2, {"base", "name"}};
static void cont__30_30(void);
static void cont__30_31(void);
static NODE *func__30_32;
static void entry__30_32(void);
static FRAME_INFO frame__30_32 = {4, {"method_name", "method_info", "info", "methods"}};
static void cont__30_33(void);
static NODE *func__30_34;
static void entry__30_34(void);
static FRAME_INFO frame__30_34 = {2, {"method_name", "method_info"}};
static void cont__30_35(void);
static void cont__30_36(void);
static void cont__30_37(void);
static void cont__30_38(void);
static void cont__30_39(void);
static NODE *func__30_40;
static void entry__30_40(void);
static FRAME_INFO frame__30_40 = {3, {"method_name", "info", "oname"}};
static void cont__30_41(void);
static void cont__30_42(void);
static void cont__30_43(void);
static void cont__30_44(void);
static void cont__30_45(void);
static void cont__30_46(void);
static void cont__30_47(void);
static void cont__30_48(void);
static void cont__30_49(void);
static void cont__30_50(void);
static void cont__30_51(void);
static void cont__30_52(void);
static void cont__30_53(void);
static void cont__30_54(void);
static NODE *string__30_55;
static NODE *func__30_56;
static void entry__30_56(void);
static FRAME_INFO frame__30_56 = {1, {"print_type_info"}};
static NODE *func__30_57;
static void entry__30_57(void);
static FRAME_INFO frame__30_57 = {3, {"info", "indent", "print_type_info"}};
static NODE *func__30_58;
static void entry__30_58(void);
static FRAME_INFO frame__30_58 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__30_59(void);
static void cont__30_60(void);
static void cont__30_61(void);
static NODE *func__30_62;
static void entry__30_62(void);
static FRAME_INFO frame__30_62 = {2, {"indent", "qname"}};
static NODE *func__30_63;
static void entry__30_63(void);
static FRAME_INFO frame__30_63 = {2, {"indent", "qname"}};
static void cont__30_64(void);
static void cont__30_65(void);
static void cont__30_66(void);
static void cont__30_67(void);
static void cont__30_68(void);
static void cont__30_69(void);
static void cont__30_70(void);
static NODE *func__30_71;
static void entry__30_71(void);
static FRAME_INFO frame__30_71 = {1, {"remark_lines"}};
static void cont__30_72(void);
static void cont__30_73(void);
static void cont__30_74(void);
static NODE *func__30_75;
static void entry__30_75(void);
static FRAME_INFO frame__30_75 = {1, {"remark_lines"}};
static void cont__30_76(void);
static void cont__30_77(void);
static void cont__30_78(void);
static void cont__30_79(void);
static NODE *func__30_80;
static void entry__30_80(void);
static FRAME_INFO frame__30_80 = {3, {"name", "print_type_info", "indent"}};
static void cont__30_81(void);
static void cont__30_82(void);
static void cont__30_83(void);
static void cont__30_84(void);
static NODE *func__30_85;
static void entry__30_85(void);
static FRAME_INFO frame__30_85 = {1, {"print_type_info"}};
static NODE *func__30_86;
static void entry__30_86(void);
static FRAME_INFO frame__30_86 = {3, {"base", "info", "print_type_info"}};
static void cont__30_87(void);
static void cont__30_88(void);
static NODE *func__30_89;
static void entry__30_89(void);
static FRAME_INFO frame__30_89 = {1, {"info"}};
static void cont__30_90(void);
static void cont__30_91(void);
static void cont__30_92(void);
static NODE *func__30_93;
static void entry__30_93(void);
static FRAME_INFO frame__30_93 = {2, {"print_type_info", "info"}};
static void cont__30_94(void);
static NODE *string__30_95;
static NODE *func__30_96;
static void entry__30_96(void);
static FRAME_INFO frame__30_96 = {0, {}};
static void cont__30_97(void);
static NODE *string__30_98;
static NODE *string__30_99;
static void cont__30_100(void);
static void cont__30_101(void);
static NODE *func__30_102;
static void entry__30_102(void);
static FRAME_INFO frame__30_102 = {1, {"letter"}};
static NODE *string__30_103;
static void cont__30_104(void);
static void cont__30_105(void);
static void cont__30_106(void);
static NODE *func__30_107;
static void entry__30_107(void);
static FRAME_INFO frame__30_107 = {0, {}};
static NODE *string__30_108;
static void cont__30_109(void);
static void cont__30_110(void);
static NODE *func__30_111;
static void entry__30_111(void);
static FRAME_INFO frame__30_111 = {1, {"letter"}};
static NODE *func__30_112;
static void entry__30_112(void);
static FRAME_INFO frame__30_112 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__30_113(void);
static void cont__30_114(void);
static void cont__30_115(void);
static NODE *func__30_116;
static void entry__30_116(void);
static FRAME_INFO frame__30_116 = {2, {"letter", "iname"}};
static void cont__30_117(void);
static NODE *func__30_118;
static void entry__30_118(void);
static FRAME_INFO frame__30_118 = {1, {"letter"}};
static NODE *string__30_119;
static void cont__30_120(void);
static NODE *func__30_121;
static void entry__30_121(void);
static FRAME_INFO frame__30_121 = {1, {"letter"}};
static void cont__30_122(void);
static NODE *func__30_123;
static void entry__30_123(void);
static FRAME_INFO frame__30_123 = {1, {"letter"}};
static void cont__30_124(void);
static void cont__30_125(void);
static NODE *string__30_126;
static void cont__30_127(void);
static NODE *string__30_128;
static void cont__30_129(void);
static void cont__30_130(void);
static void cont__30_131(void);
static void cont__30_132(void);
static NODE *func__30_133;
static void entry__30_133(void);
static FRAME_INFO frame__30_133 = {1, {"remark_lines"}};
static void cont__30_134(void);
static void cont__30_135(void);
static void cont__30_136(void);
static NODE *func__30_137;
static void entry__30_137(void);
static FRAME_INFO frame__30_137 = {2, {"remark", "remark_lines"}};
static void cont__30_138(void);
static void cont__30_139(void);
static void cont__30_140(void);
static void cont__30_141(void);
static NODE *func__30_142;
static void entry__30_142(void);
static FRAME_INFO frame__30_142 = {0, {}};
static NODE *string__30_143;
static NODE *func__30_144;
static void entry__30_144(void);
static FRAME_INFO frame__30_144 = {0, {}};
static NODE *string__30_145;
static NODE *func__30_146;
static void entry__30_146(void);
static FRAME_INFO frame__30_146 = {0, {}};
static NODE *string__30_147;
static NODE *func__30_148;
static void entry__30_148(void);
static FRAME_INFO frame__30_148 = {0, {}};
static NODE *string__30_149;
static NODE *func__30_150;
static void entry__30_150(void);
static FRAME_INFO frame__30_150 = {0, {}};
static NODE *func__30_151;
static void entry__30_151(void);
static FRAME_INFO frame__30_151 = {0, {}};
static void cont__30_152(void);
static void cont__30_153(void);
static NODE *func__30_154;
static void entry__30_154(void);
static FRAME_INFO frame__30_154 = {2, {"remark", "kind_info"}};
static void cont__30_155(void);
static NODE *func__30_156;
static void entry__30_156(void);
static FRAME_INFO frame__30_156 = {2, {"remark", "kind_info"}};
static NODE *string__30_157;
static void cont__30_158(void);
static NODE *func__30_159;
static void entry__30_159(void);
static FRAME_INFO frame__30_159 = {2, {"remark", "kind_info"}};
static void cont__30_160(void);
static void cont__30_161(void);
static NODE *func__30_162;
static void entry__30_162(void);
static FRAME_INFO frame__30_162 = {1, {"name"}};
static void cont__30_163(void);
static void cont__30_164(void);
static NODE *func__30_165;
static void entry__30_165(void);
static FRAME_INFO frame__30_165 = {2, {"name", "remark"}};
static NODE *func__30_166;
static void entry__30_166(void);
static FRAME_INFO frame__30_166 = {2, {"name", "remark"}};
static NODE *string__30_167;
static NODE *string__30_168;
static void cont__30_169(void);
static void cont__30_170(void);
static void cont__30_171(void);
static NODE *func__30_172;
static void entry__30_172(void);
static FRAME_INFO frame__30_172 = {1, {"name"}};
static void cont__30_173(void);
static void cont__30_174(void);
static void cont__30_175(void);
static void cont__30_176(void);
static void cont__30_177(void);
static NODE *string__30_178;
static void cont__30_179(void);
static void cont__30_180(void);
static NODE *func__30_181;
static void entry__30_181(void);
static FRAME_INFO frame__30_181 = {3, {"iname", "info", "name"}};
static void cont__30_182(void);
static void cont__30_183(void);
static NODE *func__30_184;
static void entry__30_184(void);
static FRAME_INFO frame__30_184 = {2, {"name", "info"}};
static void cont__30_185(void);
static void cont__30_186(void);
static NODE *func__30_187;
static void entry__30_187(void);
static FRAME_INFO frame__30_187 = {2, {"info", "name"}};
static void cont__30_188(void);
static NODE *func__30_189;
static void entry__30_189(void);
static FRAME_INFO frame__30_189 = {3, {"method_name", "method_info", "name"}};
static NODE *string__30_190;
static void cont__30_191(void);
static void cont__30_192(void);
static NODE *string__30_193;
static NODE *func__30_194;
static void entry__30_194(void);
static FRAME_INFO frame__30_194 = {0, {}};
static void cont__30_195(void);
static void cont__30_196(void);
static void cont__30_197(void);
static NODE *func__30_198;
static void entry__30_198(void);
static FRAME_INFO frame__30_198 = {0, {}};
static NODE *func__30_199;
static void entry__30_199(void);
static FRAME_INFO frame__30_199 = {3, {"topic", "references", "filename"}};
static void cont__30_200(void);
static NODE *string__30_201;
static void cont__30_202(void);
static void cont__30_203(void);
static void cont__30_204(void);
static NODE *func__30_205;
static void entry__30_205(void);
static FRAME_INFO frame__30_205 = {2, {"filename", "topic"}};
static NODE *func__30_206;
static void entry__30_206(void);
static FRAME_INFO frame__30_206 = {2, {"filename", "topic"}};
static void cont__30_207(void);
static void cont__30_208(void);
static NODE *func__30_209;
static void entry__30_209(void);
static FRAME_INFO frame__30_209 = {3, {"topic", "references", "filename"}};
static void cont__30_210(void);
static void cont__30_211(void);
static void cont__30_212(void);
static void cont__30_213(void);
static NODE *func__30_214;
static void entry__30_214(void);
static FRAME_INFO frame__30_214 = {2, {"topic", "references"}};
static void cont__30_215(void);
static void cont__30_216(void);
static void cont__30_217(void);
static NODE *func__30_218;
static void entry__30_218(void);
static FRAME_INFO frame__30_218 = {1, {"references"}};
static NODE *func__30_219;
static void entry__30_219(void);
static FRAME_INFO frame__30_219 = {1, {"reference"}};
static NODE *func__30_220;
static void entry__30_220(void);
static FRAME_INFO frame__30_220 = {1, {"reference"}};
static NODE *func__30_221;
static void entry__30_221(void);
static FRAME_INFO frame__30_221 = {1, {"reference"}};
static void cont__30_222(void);
static void cont__30_223(void);
static void cont__30_224(void);
static void cont__30_225(void);
static NODE *string__30_226;
static NODE *func__30_227;
static void entry__30_227(void);
static FRAME_INFO frame__30_227 = {0, {}};
static NODE *string__30_228;
static void cont__30_229(void);
static NODE *func__30_230;
static void entry__30_230(void);
static FRAME_INFO frame__30_230 = {0, {}};
static void cont__30_231(void);
static void cont__30_232(void);
static NODE *func__30_233;
static void entry__30_233(void);
static FRAME_INFO frame__30_233 = {0, {}};
static void cont__30_234(void);
static void cont__30_235(void);
static NODE *func__30_236;
static void entry__30_236(void);
static FRAME_INFO frame__30_236 = {0, {}};
static void cont__30_237(void);
static void cont__30_238(void);
static NODE *func__30_239;
static void entry__30_239(void);
static FRAME_INFO frame__30_239 = {0, {}};
static void cont__30_240(void);
static void cont__30_241(void);
static NODE *get__sim2c__extract_documentation(void) {
  return var.sim2c__extract_documentation;
}
static void cont__36_1(void);
static void cont__44_1(void);
static void cont__44_2(void);
static void cont__44_3(void);
static void cont__44_4(void);
static void cont__44_5(void);
static void cont__44_6(void);
static void cont__44_7(void);
static NODE *string__56_1;
static NODE *string__56_2;
static void cont__56_3(void);
static void cont__56_4(void);
static NODE *string__57_1;
static NODE *string__57_2;
static void cont__57_3(void);
static void cont__57_4(void);
static void cont__57_5(void);
static void cont__57_6(void);
static void cont__57_7(void);
void run__extractor(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__filename_of, NULL, 30, 30, 2, 12},
  {type__used_namespaces_of, NULL, 31, 31, 2, 19},
  {type__derived_types_of, NULL, 32, 32, 2, 17},
  {type__methods_of, NULL, 33, 33, 2, 11},
  {type__types_of, NULL, 34, 34, 2, 9},
  {run__extractor, NULL, 36, 37, 1, 68},
  {cont__36_1, NULL, 53, 53, 15, 55},
  {cont__44_1, NULL, 53, 53, 7, 56},
  {cont__44_2, NULL, 54, 54, 12, 31},
  {cont__44_3, NULL, 54, 54, 12, 46},
  {cont__44_4, NULL, 54, 54, 7, 47},
  {cont__44_5, NULL, 52, 54, 5, 46},
  {cont__44_6, NULL, 48, 54, 1, 49},
  {cont__44_7, NULL, 357, 357, 8, 28},
  {cont__56_3, NULL, 357, 357, 1, 33},
  {cont__56_4, NULL, 358, 358, 10, 32},
  {cont__57_3, NULL, 358, 358, 40, 59},
  {cont__57_4, NULL, 358, 358, 40, 74},
  {cont__57_5, NULL, 358, 358, 35, 75},
  {cont__57_6, NULL, 358, 358, 1, 80},
  {cont__57_7, NULL, },
  {entry__16_4, NULL, 64, 142, 9, 11},
  {entry__16_3, NULL, 63, 142, 7, 12},
  {cont__16_6, &frame__16_3, 143, 143, 7, 15},
  {entry__16_2, NULL, 62, 143, 5, 15},
  {entry__16_1, NULL, 61, 143, 3, 16},
  {cont__16_7, &frame__16_1, 144, 144, 3, 20},
  {entry__18_10, NULL, 159, 159, 27, 52},
  {entry__18_16, NULL, 160, 160, 21, 63},
  {entry__18_23, NULL, 161, 161, 26, 71},
  {entry__18_32, NULL, 175, 175, 39, 56},
  {cont__18_33, &frame__18_32, 175, 175, 56, 56},
  {entry__18_39, NULL, 183, 183, 11, 42},
  {cont__18_40, &frame__18_39, 183, 183, 42, 42},
  {entry__18_41, NULL, 185, 185, 11, 26},
  {cont__18_42, &frame__18_41, 186, 186, 11, 48},
  {cont__18_43, &frame__18_41, 186, 186, 48, 48},
  {entry__18_44, NULL, 188, 188, 11, 14},
  {entry__18_36, NULL, 181, 181, 9, 27},
  {cont__18_37, &frame__18_36, 181, 181, 9, 30},
  {cont__18_38, &frame__18_36, 180, 188, 7, 15},
  {entry__18_35, NULL, 179, 188, 5, 16},
  {cont__18_45, &frame__18_35, 188, 188, 16, 16},
  {entry__18_49, NULL, 190, 190, 46, 70},
  {cont__18_50, &frame__18_49, 190, 190, 34, 70},
  {cont__18_51, &frame__18_49, 190, 190, 70, 70},
  {entry__18_54, NULL, 191, 191, 32, 54},
  {cont__18_56, &frame__18_54, 191, 191, 59, 59},
  {entry__18_61, NULL, 194, 194, 37, 40},
  {entry__18_59, NULL, 194, 194, 14, 34},
  {cont__18_60, &frame__18_59, 194, 194, 11, 40},
  {entry__18_64, NULL, 194, 194, 68, 71},
  {entry__18_62, NULL, 194, 194, 47, 65},
  {cont__18_63, &frame__18_62, 194, 194, 44, 71},
  {entry__18_79, NULL, 201, 201, 41, 66},
  {cont__18_80, &frame__18_79, 201, 201, 33, 67},
  {cont__18_81, &frame__18_79, 201, 201, 13, 68},
  {cont__18_82, &frame__18_79, 201, 201, 73, 73},
  {entry__18_75, NULL, 199, 199, 19, 41},
  {cont__18_76, &frame__18_75, 199, 199, 11, 44},
  {cont__18_77, &frame__18_75, 200, 200, 14, 54},
  {cont__18_78, &frame__18_75, 200, 201, 11, 73},
  {entry__18_71, NULL, 197, 197, 9, 46},
  {cont__18_72, &frame__18_71, 198, 198, 16, 39},
  {cont__18_73, &frame__18_71, 198, 198, 16, 50},
  {cont__18_74, &frame__18_71, 198, 201, 9, 74},
  {entry__18_67, NULL, 195, 195, 20, 49},
  {cont__18_68, &frame__18_67, 195, 195, 7, 52},
  {cont__18_69, &frame__18_67, 196, 196, 10, 36},
  {cont__18_70, &frame__18_67, 196, 201, 7, 75},
  {entry__18_65, NULL, 194, 194, 77, 102},
  {cont__18_66, &frame__18_65, 194, 201, 74, 76},
  {entry__18_58, NULL, 194, 201, 5, 76},
  {entry__18_87, NULL, 208, 208, 33, 36},
  {entry__18_85, NULL, 208, 208, 10, 30},
  {cont__18_86, &frame__18_85, 208, 208, 7, 36},
  {entry__18_103, NULL, 220, 220, 49, 62},
  {cont__18_104, &frame__18_103, 220, 220, 46, 62},
  {entry__18_105, NULL, 220, 220, 65, 76},
  {entry__18_98, NULL, 214, 214, 13, 37},
  {cont__18_99, &frame__18_98, 215, 215, 13, 36},
  {cont__18_100, &frame__18_98, 219, 219, 26, 45},
  {cont__18_101, &frame__18_98, 220, 220, 29, 43},
  {cont__18_102, &frame__18_98, 220, 220, 26, 77},
  {cont__18_106, &frame__18_98, 221, 221, 34, 59},
  {cont__18_107, &frame__18_98, 216, 216, 26, 53},
  {cont__18_108, &frame__18_98, 216, 216, 13, 54},
  {cont__18_109, &frame__18_98, 222, 222, 39, 39},
  {entry__18_94, NULL, 211, 211, 11, 46},
  {cont__18_95, &frame__18_94, 212, 212, 11, 45},
  {cont__18_96, &frame__18_94, 213, 213, 14, 33},
  {cont__18_97, &frame__18_94, 213, 222, 11, 39},
  {entry__18_90, NULL, 210, 210, 12, 29},
  {cont__18_91, &frame__18_90, 210, 210, 12, 39},
  {cont__18_93, &frame__18_90, 210, 222, 9, 40},
  {entry__18_88, NULL, 209, 209, 10, 28},
  {cont__18_89, &frame__18_88, 209, 222, 7, 41},
  {entry__18_128, NULL, 236, 236, 17, 54},
  {cont__18_129, &frame__18_128, 240, 240, 38, 63},
  {cont__18_130, &frame__18_128, 237, 237, 17, 35},
  {cont__18_131, &frame__18_128, 241, 241, 17, 21},
  {entry__18_126, NULL, 235, 235, 18, 58},
  {cont__18_127, &frame__18_126, 235, 241, 15, 21},
  {entry__18_134, NULL, 245, 245, 17, 57},
  {cont__18_136, &frame__18_134, 246, 246, 17, 61},
  {cont__18_137, &frame__18_134, 246, 246, 61, 61},
  {entry__18_132, NULL, 242, 242, 18, 33},
  {cont__18_133, &frame__18_132, 242, 246, 15, 61},
  {entry__18_140, NULL, 249, 249, 17, 64},
  {cont__18_141, &frame__18_140, 249, 249, 64, 64},
  {entry__18_138, NULL, 247, 247, 18, 35},
  {cont__18_139, &frame__18_138, 247, 249, 15, 64},
  {entry__18_147, NULL, 253, 253, 30, 45},
  {cont__18_148, &frame__18_147, 254, 254, 38, 63},
  {cont__18_149, &frame__18_147, 254, 254, 64, 64},
  {entry__18_144, NULL, 251, 251, 20, 39},
  {cont__18_145, &frame__18_144, 251, 251, 20, 50},
  {cont__18_146, &frame__18_144, 251, 254, 17, 64},
  {entry__18_142, NULL, 250, 250, 18, 40},
  {cont__18_143, &frame__18_142, 250, 254, 15, 65},
  {entry__18_152, NULL, 259, 259, 38, 63},
  {cont__18_153, &frame__18_152, 256, 256, 17, 35},
  {cont__18_154, &frame__18_152, 260, 260, 17, 21},
  {entry__18_150, NULL, 255, 255, 18, 37},
  {cont__18_151, &frame__18_150, 255, 260, 15, 21},
  {entry__18_163, NULL, 267, 267, 21, 64},
  {cont__18_164, &frame__18_163, 268, 268, 21, 80},
  {cont__18_165, &frame__18_163, 269, 269, 21, 68},
  {cont__18_166, &frame__18_163, 269, 269, 68, 68},
  {entry__18_160, NULL, 266, 266, 22, 49},
  {cont__18_161, &frame__18_160, 266, 266, 22, 57},
  {cont__18_162, &frame__18_160, 266, 269, 19, 68},
  {entry__18_157, NULL, 264, 264, 17, 55},
  {cont__18_158, &frame__18_157, 265, 265, 20, 49},
  {cont__18_159, &frame__18_157, 265, 269, 17, 69},
  {cont__18_167, &frame__18_157, 270, 270, 17, 35},
  {cont__18_168, &frame__18_157, 270, 270, 40, 40},
  {entry__18_182, NULL, 282, 282, 62, 62},
  {entry__18_179, NULL, 281, 281, 28, 45},
  {cont__18_180, &frame__18_179, 281, 281, 28, 56},
  {cont__18_181, &frame__18_179, 281, 282, 21, 62},
  {cont__18_183, &frame__18_179, 283, 283, 48, 65},
  {cont__18_184, &frame__18_179, 283, 283, 21, 78},
  {cont__18_185, &frame__18_179, 285, 285, 22, 42},
  {cont__18_186, &frame__18_179, 285, 285, 21, 53},
  {cont__18_187, &frame__18_179, 286, 286, 21, 39},
  {cont__18_188, &frame__18_179, 286, 286, 50, 50},
  {entry__18_176, NULL, 279, 279, 19, 43},
  {cont__18_177, &frame__18_176, 280, 280, 26, 54},
  {cont__18_178, &frame__18_176, 280, 286, 19, 50},
  {entry__18_170, NULL, 272, 272, 17, 48},
  {cont__18_171, &frame__18_170, 275, 275, 33, 50},
  {cont__18_172, &frame__18_170, 275, 275, 19, 63},
  {cont__18_173, &frame__18_170, 277, 277, 17, 35},
  {cont__18_174, &frame__18_170, 278, 278, 20, 34},
  {cont__18_175, &frame__18_170, 278, 286, 17, 51},
  {entry__18_120, NULL, 230, 230, 13, 37},
  {cont__18_121, &frame__18_120, 231, 231, 13, 47},
  {cont__18_122, &frame__18_120, 232, 232, 13, 46},
  {cont__18_123, &frame__18_120, 233, 233, 21, 43},
  {cont__18_124, &frame__18_120, 233, 233, 13, 46},
  {cont__18_125, &frame__18_120, 234, 260, 13, 22},
  {cont__18_155, &frame__18_120, 262, 262, 15, 44},
  {cont__18_156, &frame__18_120, 271, 271, 15, 41},
  {cont__18_169, &frame__18_120, 261, 286, 13, 53},
  {entry__18_116, NULL, 227, 227, 11, 48},
  {cont__18_117, &frame__18_116, 228, 228, 11, 45},
  {cont__18_118, &frame__18_116, 229, 229, 14, 33},
  {cont__18_119, &frame__18_116, 229, 286, 11, 54},
  {entry__18_112, NULL, 224, 224, 22, 51},
  {cont__18_113, &frame__18_112, 224, 224, 22, 54},
  {cont__18_114, &frame__18_112, 226, 226, 12, 38},
  {cont__18_115, &frame__18_112, 226, 286, 9, 55},
  {entry__18_110, NULL, 223, 223, 10, 35},
  {cont__18_111, &frame__18_110, 223, 286, 7, 56},
  {entry__18_84, NULL, 207, 286, 5, 57},
  {cont__18_189, &frame__18_84, 286, 286, 57, 57},
  {entry__18_1, NULL, 157, 157, 10, 56},
  {cont__18_4, &frame__18_1, 157, 157, 3, 56},
  {cont__18_5, &frame__18_1, 158, 158, 8, 21},
  {cont__18_6, &frame__18_1, 158, 158, 3, 31},
  {cont__18_7, &frame__18_1, 159, 159, 6, 19},
  {cont__18_8, &frame__18_1, 159, 159, 6, 24},
  {cont__18_9, &frame__18_1, 159, 159, 3, 52},
  {cont__18_12, &frame__18_1, 160, 160, 6, 11},
  {cont__18_13, &frame__18_1, 160, 160, 6, 18},
  {cont__18_14, &frame__18_1, 160, 160, 6, 18},
  {cont__18_15, &frame__18_1, 160, 160, 3, 63},
  {cont__18_18, &frame__18_1, 161, 161, 11, 11},
  {cont__18_19, &frame__18_1, 161, 161, 6, 12},
  {cont__18_20, &frame__18_1, 161, 161, 6, 23},
  {cont__18_21, &frame__18_1, 161, 161, 6, 23},
  {cont__18_22, &frame__18_1, 161, 161, 3, 71},
  {cont__18_25, &frame__18_1, 164, 164, 17, 48},
  {cont__18_27, &frame__18_1, 164, 164, 50, 59},
  {cont__18_29, &frame__18_1, 163, 165, 3, 69},
  {cont__18_30, &frame__18_1, 174, 174, 3, 37},
  {cont__18_31, &frame__18_1, 175, 175, 3, 56},
  {cont__18_34, &frame__18_1, 178, 188, 3, 17},
  {cont__18_46, &frame__18_1, 189, 189, 31, 31},
  {cont__18_47, &frame__18_1, 189, 189, 3, 31},
  {cont__18_48, &frame__18_1, 190, 190, 3, 70},
  {cont__18_52, &frame__18_1, 191, 191, 6, 29},
  {cont__18_53, &frame__18_1, 191, 191, 3, 59},
  {cont__18_57, &frame__18_1, 193, 201, 3, 77},
  {cont__18_83, &frame__18_1, 202, 286, 3, 58},
  {cont__18_190, &frame__18_1, 286, 286, 58, 58},
  {entry__19_8, NULL, 292, 292, 32, 72},
  {entry__19_6, NULL, 292, 292, 10, 29},
  {cont__19_7, &frame__19_6, 292, 292, 7, 72},
  {entry__19_11, NULL, 293, 293, 36, 71},
  {entry__19_9, NULL, 293, 293, 10, 33},
  {cont__19_10, &frame__19_9, 293, 293, 7, 71},
  {entry__19_4, NULL, 290, 290, 5, 28},
  {cont__19_5, &frame__19_4, 291, 293, 5, 71},
  {entry__19_1, NULL, 289, 289, 22, 27},
  {cont__19_2, &frame__19_1, 289, 289, 12, 33},
  {cont__19_3, &frame__19_1, 289, 293, 3, 72},
  {entry__20_5, NULL, 297, 297, 40, 53},
  {cont__20_6, &frame__20_5, 297, 297, 37, 53},
  {entry__20_13, NULL, 302, 303, 17, 64},
  {cont__20_16, &frame__20_13, 302, 303, 11, 64},
  {entry__20_11, NULL, 301, 301, 12, 40},
  {cont__20_12, &frame__20_11, 301, 303, 9, 65},
  {cont__20_17, &frame__20_11, 304, 304, 37, 37},
  {entry__20_9, NULL, 300, 300, 10, 46},
  {cont__20_10, &frame__20_9, 300, 304, 7, 37},
  {entry__20_20, NULL, 306, 307, 13, 51},
  {cont__20_22, &frame__20_20, 306, 307, 7, 51},
  {entry__20_7, NULL, 299, 299, 14, 37},
  {cont__20_8, &frame__20_7, 299, 304, 5, 38},
  {cont__20_18, &frame__20_7, 305, 305, 12, 40},
  {cont__20_19, &frame__20_7, 305, 307, 5, 52},
  {cont__20_23, &frame__20_7, 308, 308, 8, 43},
  {cont__20_25, &frame__20_7, 308, 308, 5, 43},
  {entry__20_1, NULL, 296, 296, 3, 21},
  {cont__20_2, &frame__20_1, 297, 297, 6, 23},
  {cont__20_3, &frame__20_1, 297, 297, 6, 34},
  {cont__20_4, &frame__20_1, 297, 308, 3, 43},
  {entry__21_15, NULL, 318, 318, 35, 69},
  {entry__21_12, NULL, 317, 317, 7, 39},
  {cont__21_13, &frame__21_12, 318, 318, 10, 32},
  {cont__21_14, &frame__21_12, 318, 318, 7, 69},
  {entry__21_7, NULL, 314, 314, 6, 32},
  {cont__21_8, &frame__21_7, 314, 314, 5, 38},
  {cont__21_9, &frame__21_7, 315, 315, 12, 30},
  {cont__21_10, &frame__21_7, 315, 315, 12, 38},
  {cont__21_11, &frame__21_7, 315, 318, 5, 69},
  {cont__21_16, &frame__21_7, 319, 319, 5, 23},
  {cont__21_17, &frame__21_7, 319, 319, 34, 34},
  {entry__21_1, NULL, 311, 311, 23, 40},
  {cont__21_2, &frame__21_1, 311, 311, 42, 59},
  {cont__21_3, &frame__21_1, 311, 311, 3, 60},
  {cont__21_4, &frame__21_1, 312, 312, 3, 33},
  {cont__21_5, &frame__21_1, 313, 313, 6, 26},
  {cont__21_6, &frame__21_1, 313, 319, 3, 34},
  {entry__22_1, NULL, 321, 321, 38, 48},
  {cont__22_2, &frame__22_1, 321, 321, 50, 60},
  {cont__22_4, &frame__22_1, 321, 321, 21, 61},
  {cont__22_5, &frame__22_1, 321, 321, 18, 61},
  {entry__23_1, NULL, 326, 326, 7, 24},
  {cont__23_2, &frame__23_1, 328, 328, 7, 29},
  {cont__23_3, &frame__23_1, 325, 332, 5, 14},
  {cont__23_4, &frame__23_1, 324, 332, 3, 16},
  {entry__24_2, NULL, 336, 336, 7, 27},
  {cont__24_5, &frame__24_2, 336, 336, 5, 34},
  {cont__24_7, &frame__24_2, 337, 337, 5, 29},
  {cont__24_9, &frame__24_2, 338, 338, 7, 28},
  {cont__24_11, &frame__24_2, 338, 338, 5, 37},
  {cont__24_13, &frame__24_2, 339, 339, 5, 29},
  {cont__24_14, &frame__24_2, 340, 340, 7, 32},
  {cont__24_16, &frame__24_2, 340, 340, 5, 45},
  {cont__24_18, &frame__24_2, 341, 341, 5, 29},
  {cont__24_19, &frame__24_2, 342, 342, 7, 34},
  {cont__24_21, &frame__24_2, 342, 342, 5, 49},
  {cont__24_23, &frame__24_2, 343, 343, 5, 29},
  {cont__24_24, &frame__24_2, 344, 344, 7, 33},
  {cont__24_26, &frame__24_2, 344, 344, 5, 47},
  {entry__24_1, NULL, 335, 344, 3, 47},
  {entry__25_7, NULL, 351, 351, 41, 67},
  {cont__25_9, &frame__25_7, 351, 351, 67, 67},
  {entry__25_12, NULL, 352, 352, 43, 69},
  {cont__25_14, &frame__25_12, 352, 352, 69, 69},
  {entry__25_3, NULL, 349, 349, 7, 40},
  {cont__25_4, &frame__25_3, 350, 350, 7, 42},
  {cont__25_5, &frame__25_3, 351, 351, 14, 38},
  {cont__25_6, &frame__25_3, 351, 351, 7, 67},
  {cont__25_10, &frame__25_3, 352, 352, 14, 40},
  {cont__25_11, &frame__25_3, 352, 352, 7, 69},
  {cont__25_15, &frame__25_3, 353, 353, 7, 50},
  {cont__25_16, &frame__25_3, 353, 353, 50, 50},
  {entry__25_19, NULL, 355, 355, 41, 65},
  {cont__25_20, &frame__25_19, 355, 355, 65, 65},
  {entry__25_17, NULL, 355, 355, 14, 38},
  {cont__25_18, &frame__25_17, 355, 355, 7, 65},
  {entry__25_1, NULL, 348, 348, 5, 28},
  {cont__25_2, &frame__25_1, 347, 355, 3, 66},
  {cont__25_21, &frame__25_1, },
  {entry__28_5, NULL, 369, 369, 13, 22},
  {cont__28_6, &frame__28_5, 370, 370, 13, 33},
  {cont__28_7, &frame__28_5, 371, 371, 22, 22},
  {entry__28_8, NULL, 373, 373, 13, 33},
  {cont__28_9, &frame__28_8, 373, 373, 33, 33},
  {entry__28_3, NULL, 368, 368, 11, 35},
  {cont__28_4, &frame__28_3, 367, 373, 9, 34},
  {entry__28_15, NULL, 378, 378, 15, 35},
  {cont__28_16, &frame__28_15, 379, 379, 22, 22},
  {entry__28_12, NULL, 377, 377, 16, 25},
  {cont__28_13, &frame__28_12, 377, 377, 16, 25},
  {cont__28_14, &frame__28_12, 377, 379, 13, 22},
  {entry__28_21, NULL, 383, 383, 60, 60},
  {entry__28_19, NULL, 383, 383, 20, 44},
  {cont__28_20, &frame__28_19, 383, 383, 17, 60},
  {entry__28_22, NULL, 385, 385, 17, 30},
  {cont__28_23, &frame__28_22, 385, 385, 30, 30},
  {entry__28_17, NULL, 382, 382, 15, 24},
  {cont__28_18, &frame__28_17, 381, 385, 13, 31},
  {cont__28_24, &frame__28_17, 386, 386, 26, 34},
  {cont__28_25, &frame__28_17, 386, 386, 13, 34},
  {cont__28_26, &frame__28_17, 386, 386, 34, 34},
  {entry__28_10, NULL, 376, 376, 11, 20},
  {cont__28_11, &frame__28_10, 375, 386, 9, 35},
  {entry__28_2, NULL, 365, 386, 5, 37},
  {entry__28_30, NULL, 387, 387, 18, 38},
  {cont__28_31, &frame__28_30, 387, 387, 38, 38},
  {entry__28_1, NULL, 364, 386, 3, 38},
  {cont__28_27, &frame__28_1, 387, 387, 6, 15},
  {cont__28_28, &frame__28_1, 387, 387, 6, 15},
  {cont__28_29, &frame__28_1, 387, 387, 3, 38},
  {cont__28_32, &frame__28_1, 388, 388, 3, 15},
  {entry__29_11, NULL, 396, 396, 11, 42},
  {cont__29_12, &frame__29_11, 397, 397, 11, 44},
  {cont__29_13, &frame__29_11, 403, 403, 15, 26},
  {cont__29_14, &frame__29_11, 407, 407, 15, 28},
  {cont__29_15, &frame__29_11, 399, 408, 13, 21},
  {cont__29_19, &frame__29_11, 398, 408, 11, 23},
  {entry__29_20, NULL, 410, 410, 11, 26},
  {entry__29_36, NULL, 436, 436, 58, 58},
  {cont__29_37, &frame__29_36, 436, 436, 39, 59},
  {cont__29_38, &frame__29_36, 436, 436, 21, 74},
  {cont__29_40, &frame__29_36, 436, 436, 74, 74},
  {entry__29_34, NULL, 435, 435, 22, 47},
  {cont__29_35, &frame__29_34, 435, 436, 19, 74},
  {entry__29_43, NULL, 439, 439, 49, 49},
  {cont__29_44, &frame__29_43, 439, 439, 30, 50},
  {cont__29_45, &frame__29_43, 438, 439, 21, 79},
  {cont__29_47, &frame__29_43, 439, 439, 80, 80},
  {entry__29_41, NULL, 437, 437, 22, 47},
  {cont__29_42, &frame__29_41, 437, 439, 19, 80},
  {entry__29_50, NULL, 443, 443, 26, 47},
  {cont__29_51, &frame__29_50, 443, 443, 26, 53},
  {cont__29_52, &frame__29_50, 445, 445, 26, 47},
  {cont__29_53, &frame__29_50, 445, 445, 26, 53},
  {cont__29_54, &frame__29_50, 441, 446, 21, 28},
  {cont__29_57, &frame__29_50, 446, 446, 29, 29},
  {entry__29_48, NULL, 440, 440, 22, 45},
  {cont__29_49, &frame__29_48, 440, 446, 19, 29},
  {entry__29_32, NULL, 433, 433, 17, 68},
  {cont__29_33, &frame__29_32, 434, 446, 17, 30},
  {cont__29_58, &frame__29_32, 447, 447, 31, 52},
  {cont__29_59, &frame__29_32, 447, 447, 17, 58},
  {cont__29_60, &frame__29_32, 448, 448, 34, 56},
  {cont__29_61, &frame__29_32, 448, 448, 17, 56},
  {cont__29_62, &frame__29_32, 448, 448, 56, 56},
  {entry__29_27, NULL, 430, 430, 19, 53},
  {cont__29_28, &frame__29_27, 426, 431, 17, 20},
  {cont__29_30, &frame__29_27, 424, 431, 15, 21},
  {cont__29_31, &frame__29_27, 423, 448, 13, 57},
  {entry__29_72, NULL, 462, 462, 64, 64},
  {cont__29_73, &frame__29_72, 462, 462, 42, 65},
  {cont__29_74, &frame__29_72, 462, 462, 21, 80},
  {cont__29_75, &frame__29_72, 462, 462, 80, 80},
  {entry__29_70, NULL, 461, 461, 22, 50},
  {cont__29_71, &frame__29_70, 461, 462, 19, 80},
  {entry__29_78, NULL, 466, 466, 47, 47},
  {cont__29_79, &frame__29_78, 466, 466, 25, 48},
  {cont__29_80, &frame__29_78, 464, 467, 21, 52},
  {cont__29_81, &frame__29_78, 467, 467, 53, 53},
  {entry__29_76, NULL, 463, 463, 22, 50},
  {cont__29_77, &frame__29_76, 463, 467, 19, 53},
  {entry__29_68, NULL, 459, 459, 17, 71},
  {cont__29_69, &frame__29_68, 460, 467, 17, 54},
  {cont__29_82, &frame__29_68, 468, 468, 31, 52},
  {cont__29_83, &frame__29_68, 468, 468, 17, 58},
  {cont__29_84, &frame__29_68, 469, 469, 37, 62},
  {cont__29_85, &frame__29_68, 469, 469, 17, 62},
  {cont__29_86, &frame__29_68, 469, 469, 62, 62},
  {entry__29_63, NULL, 456, 456, 19, 53},
  {cont__29_64, &frame__29_63, 452, 457, 17, 20},
  {cont__29_66, &frame__29_63, 450, 457, 15, 21},
  {cont__29_67, &frame__29_63, 449, 469, 13, 63},
  {entry__29_93, NULL, 472, 472, 34, 47},
  {cont__29_94, &frame__29_93, 472, 472, 17, 47},
  {cont__29_95, &frame__29_93, 472, 472, 47, 47},
  {entry__29_90, NULL, 471, 471, 30, 51},
  {cont__29_91, &frame__29_90, 471, 471, 24, 56},
  {cont__29_92, &frame__29_90, 471, 472, 15, 47},
  {entry__29_87, NULL, 470, 470, 16, 49},
  {cont__29_89, &frame__29_87, 470, 472, 13, 48},
  {entry__29_101, NULL, 475, 475, 17, 27},
  {cont__29_102, &frame__29_101, 478, 478, 33, 45},
  {cont__29_103, &frame__29_101, 477, 478, 17, 66},
  {cont__29_104, &frame__29_101, 480, 480, 17, 46},
  {cont__29_105, &frame__29_101, 481, 481, 17, 30},
  {cont__29_106, &frame__29_101, 481, 481, 45, 45},
  {entry__29_98, NULL, 474, 474, 30, 51},
  {cont__29_99, &frame__29_98, 474, 474, 24, 56},
  {cont__29_100, &frame__29_98, 474, 481, 15, 45},
  {entry__29_96, NULL, 473, 473, 16, 43},
  {cont__29_97, &frame__29_96, 473, 481, 13, 46},
  {entry__29_109, NULL, 483, 483, 23, 44},
  {cont__29_110, &frame__29_109, 483, 483, 15, 50},
  {cont__29_111, &frame__29_109, 484, 484, 22, 43},
  {cont__29_112, &frame__29_109, 484, 484, 15, 49},
  {cont__29_113, &frame__29_109, 485, 485, 30, 41},
  {cont__29_114, &frame__29_109, 485, 485, 15, 41},
  {cont__29_115, &frame__29_109, 485, 485, 41, 41},
  {entry__29_107, NULL, 482, 482, 16, 45},
  {cont__29_108, &frame__29_107, 482, 485, 13, 41},
  {entry__29_123, NULL, 490, 490, 47, 47},
  {entry__29_124, NULL, 492, 492, 19, 49},
  {cont__29_125, &frame__29_124, 492, 492, 49, 49},
  {entry__29_119, NULL, 487, 487, 24, 45},
  {cont__29_120, &frame__29_119, 487, 487, 15, 51},
  {cont__29_121, &frame__29_119, 489, 489, 17, 28},
  {cont__29_122, &frame__29_119, 488, 492, 15, 50},
  {entry__29_116, NULL, 486, 486, 16, 58},
  {cont__29_118, &frame__29_116, 486, 492, 13, 51},
  {entry__29_130, NULL, 499, 499, 41, 41},
  {cont__29_131, &frame__29_130, 499, 499, 21, 41},
  {cont__29_132, &frame__29_130, 500, 500, 21, 48},
  {cont__29_133, &frame__29_130, 501, 501, 42, 58},
  {cont__29_134, &frame__29_130, 501, 501, 24, 66},
  {cont__29_136, &frame__29_130, 501, 501, 21, 66},
  {entry__29_142, NULL, 506, 506, 23, 55},
  {cont__29_143, &frame__29_142, 506, 506, 55, 55},
  {entry__29_144, NULL, 508, 508, 23, 50},
  {cont__29_145, &frame__29_144, 508, 508, 50, 50},
  {entry__29_140, NULL, 505, 505, 21, 48},
  {cont__29_141, &frame__29_140, 504, 508, 19, 51},
  {entry__29_146, NULL, 510, 510, 46, 46},
  {entry__29_126, NULL, 497, 497, 39, 47},
  {cont__29_127, &frame__29_126, 497, 497, 30, 48},
  {cont__29_128, &frame__29_126, 497, 497, 19, 53},
  {cont__29_129, &frame__29_126, 496, 501, 17, 66},
  {cont__29_137, &frame__29_126, 494, 501, 15, 68},
  {cont__29_138, &frame__29_126, 503, 503, 17, 44},
  {cont__29_139, &frame__29_126, 502, 510, 15, 47},
  {entry__29_26, NULL, 422, 510, 11, 49},
  {entry__29_24, NULL, 420, 420, 9, 46},
  {cont__29_25, &frame__29_24, 421, 510, 9, 50},
  {entry__29_164, NULL, 526, 526, 25, 51},
  {cont__29_165, &frame__29_164, 526, 526, 25, 61},
  {cont__29_166, &frame__29_164, 523, 527, 23, 27},
  {cont__29_167, &frame__29_164, 527, 527, 28, 28},
  {entry__29_168, NULL, 529, 529, 23, 48},
  {cont__29_169, &frame__29_168, 529, 529, 48, 48},
  {entry__29_161, NULL, 522, 522, 21, 47},
  {cont__29_162, &frame__29_161, 522, 522, 21, 58},
  {cont__29_163, &frame__29_161, 521, 529, 19, 49},
  {entry__29_159, NULL, 520, 520, 20, 48},
  {cont__29_160, &frame__29_159, 520, 529, 17, 50},
  {entry__29_172, NULL, 531, 531, 19, 58},
  {cont__29_173, &frame__29_172, 531, 531, 58, 58},
  {entry__29_170, NULL, 530, 530, 20, 48},
  {cont__29_171, &frame__29_170, 530, 531, 17, 58},
  {entry__29_178, NULL, 536, 536, 22, 47},
  {cont__29_179, &frame__29_178, 536, 536, 22, 61},
  {cont__29_180, &frame__29_178, 536, 536, 22, 64},
  {cont__29_181, &frame__29_178, 536, 536, 19, 64},
  {entry__29_182, NULL, 537, 537, 19, 23},
  {entry__29_155, NULL, 518, 518, 30, 53},
  {cont__29_156, &frame__29_155, 518, 518, 22, 54},
  {cont__29_157, &frame__29_155, 518, 518, 15, 75},
  {cont__29_158, &frame__29_155, 519, 531, 15, 59},
  {cont__29_174, &frame__29_155, 535, 535, 23, 48},
  {cont__29_175, &frame__29_155, 535, 535, 23, 57},
  {cont__29_176, &frame__29_155, 535, 535, 19, 58},
  {cont__29_177, &frame__29_155, 533, 537, 15, 24},
  {cont__29_183, &frame__29_155, 539, 539, 32, 49},
  {cont__29_184, &frame__29_155, 539, 539, 15, 49},
  {cont__29_185, &frame__29_155, 539, 539, 49, 49},
  {entry__29_186, NULL, 516, 516, 15, 18},
  {entry__29_152, NULL, 514, 514, 13, 40},
  {cont__29_153, &frame__29_152, 515, 515, 13, 52},
  {cont__29_154, &frame__29_152, 513, 539, 11, 50},
  {entry__29_150, NULL, 512, 512, 18, 36},
  {cont__29_151, &frame__29_150, 512, 539, 9, 51},
  {entry__29_189, NULL, 540, 540, 40, 58},
  {entry__29_199, NULL, 546, 546, 19, 42},
  {cont__29_200, &frame__29_199, 546, 546, 17, 42},
  {entry__29_196, NULL, 545, 545, 16, 32},
  {cont__29_197, &frame__29_196, 545, 545, 13, 32},
  {cont__29_198, &frame__29_196, 546, 546, 13, 42},
  {entry__29_195, NULL, 544, 546, 11, 42},
  {entry__29_192, NULL, 542, 542, 9, 23},
  {cont__29_194, &frame__29_192, 543, 546, 9, 43},
  {entry__29_209, NULL, 552, 552, 19, 45},
  {cont__29_210, &frame__29_209, 552, 552, 17, 45},
  {entry__29_206, NULL, 551, 551, 16, 35},
  {cont__29_207, &frame__29_206, 551, 551, 13, 35},
  {cont__29_208, &frame__29_206, 552, 552, 13, 45},
  {entry__29_205, NULL, 550, 552, 11, 45},
  {entry__29_203, NULL, 548, 548, 9, 20},
  {cont__29_204, &frame__29_203, 549, 552, 9, 46},
  {entry__29_216, NULL, 555, 555, 46, 58},
  {entry__29_213, NULL, 554, 554, 9, 24},
  {cont__29_215, &frame__29_213, 555, 555, 9, 58},
  {entry__29_222, NULL, 558, 558, 46, 53},
  {entry__29_219, NULL, 557, 557, 9, 30},
  {cont__29_221, &frame__29_219, 558, 558, 9, 53},
  {entry__29_229, NULL, 563, 563, 13, 40},
  {cont__29_230, &frame__29_229, 564, 564, 27, 43},
  {cont__29_231, &frame__29_229, 564, 564, 24, 50},
  {cont__29_232, &frame__29_229, 564, 564, 15, 50},
  {cont__29_233, &frame__29_229, 564, 564, 13, 60},
  {cont__29_234, &frame__29_229, 565, 565, 13, 14},
  {entry__29_228, NULL, 562, 565, 11, 14},
  {entry__29_225, NULL, 560, 560, 9, 21},
  {cont__29_227, &frame__29_225, 561, 565, 9, 15},
  {entry__29_246, NULL, 572, 572, 33, 44},
  {cont__29_247, &frame__29_246, 572, 572, 30, 51},
  {cont__29_248, &frame__29_246, 572, 572, 21, 51},
  {cont__29_249, &frame__29_246, 572, 572, 19, 56},
  {entry__29_253, NULL, 574, 574, 33, 46},
  {cont__29_254, &frame__29_253, 574, 574, 30, 53},
  {cont__29_255, &frame__29_253, 574, 574, 21, 53},
  {cont__29_256, &frame__29_253, 574, 574, 19, 60},
  {entry__29_245, NULL, 572, 572, 15, 56},
  {cont__29_250, &frame__29_245, 573, 573, 15, 33},
  {cont__29_252, &frame__29_245, 574, 574, 15, 60},
  {entry__29_243, NULL, 570, 570, 13, 50},
  {cont__29_244, &frame__29_243, 571, 574, 13, 60},
  {entry__29_241, NULL, 569, 569, 20, 33},
  {cont__29_242, &frame__29_241, 569, 574, 11, 61},
  {entry__29_238, NULL, 567, 567, 9, 27},
  {cont__29_240, &frame__29_238, 568, 574, 9, 62},
  {entry__29_267, NULL, 580, 580, 33, 51},
  {cont__29_268, &frame__29_267, 580, 580, 30, 58},
  {cont__29_269, &frame__29_267, 580, 580, 21, 58},
  {cont__29_270, &frame__29_267, 580, 580, 19, 70},
  {entry__29_274, NULL, 586, 586, 24, 44},
  {cont__29_275, &frame__29_274, 586, 586, 51, 69},
  {cont__29_276, &frame__29_274, 586, 586, 21, 76},
  {cont__29_277, &frame__29_274, 584, 586, 19, 75},
  {cont__29_278, &frame__29_274, 583, 589, 17, 29},
  {entry__29_266, NULL, 580, 580, 15, 70},
  {cont__29_271, &frame__29_266, 581, 581, 15, 25},
  {cont__29_273, &frame__29_266, 582, 589, 15, 30},
  {entry__29_265, NULL, 579, 589, 13, 31},
  {entry__29_263, NULL, 578, 578, 20, 35},
  {cont__29_264, &frame__29_263, 578, 589, 11, 32},
  {entry__29_260, NULL, 576, 576, 9, 44},
  {cont__29_262, &frame__29_260, 577, 589, 9, 33},
  {entry__29_295, NULL, 608, 608, 19, 35},
  {entry__29_290, NULL, 605, 605, 24, 48},
  {cont__29_291, &frame__29_290, 605, 605, 24, 63},
  {cont__29_292, &frame__29_290, 605, 605, 19, 64},
  {cont__29_293, &frame__29_290, 603, 606, 17, 25},
  {cont__29_294, &frame__29_290, 602, 608, 15, 35},
  {cont__29_296, &frame__29_290, 609, 609, 35, 69},
  {cont__29_298, &frame__29_290, 609, 609, 15, 69},
  {cont__29_299, &frame__29_290, 600, 609, 13, 68},
  {cont__29_300, &frame__29_290, 599, 609, 11, 70},
  {entry__29_282, NULL, 595, 595, 9, 30},
  {cont__29_283, &frame__29_282, 596, 596, 9, 36},
  {cont__29_284, &frame__29_282, 597, 597, 9, 16},
  {cont__29_285, &frame__29_282, 598, 598, 45, 56},
  {cont__29_286, &frame__29_282, 598, 598, 23, 56},
  {cont__29_287, &frame__29_282, 598, 598, 13, 56},
  {cont__29_289, &frame__29_282, 598, 609, 9, 71},
  {entry__29_8, NULL, 393, 393, 7, 14},
  {cont__29_9, &frame__29_8, 395, 395, 9, 36},
  {cont__29_10, &frame__29_8, 394, 410, 7, 27},
  {cont__29_21, &frame__29_8, 418, 418, 7, 41},
  {cont__29_22, &frame__29_8, 419, 419, 10, 32},
  {cont__29_23, &frame__29_8, 419, 510, 7, 51},
  {cont__29_147, &frame__29_8, 511, 511, 10, 22},
  {cont__29_148, &frame__29_8, 511, 511, 10, 34},
  {cont__29_149, &frame__29_8, 511, 539, 7, 52},
  {cont__29_187, &frame__29_8, 540, 540, 10, 37},
  {cont__29_188, &frame__29_8, 540, 540, 7, 58},
  {cont__29_190, &frame__29_8, 541, 541, 14, 32},
  {cont__29_191, &frame__29_8, 541, 546, 7, 44},
  {cont__29_201, &frame__29_8, 547, 547, 14, 35},
  {cont__29_202, &frame__29_8, 547, 552, 7, 47},
  {cont__29_211, &frame__29_8, 553, 553, 14, 34},
  {cont__29_212, &frame__29_8, 553, 555, 7, 58},
  {cont__29_217, &frame__29_8, 556, 556, 10, 37},
  {cont__29_218, &frame__29_8, 556, 558, 7, 53},
  {cont__29_223, &frame__29_8, 559, 559, 14, 32},
  {cont__29_224, &frame__29_8, 559, 565, 7, 16},
  {cont__29_235, &frame__29_8, 566, 566, 14, 27},
  {cont__29_236, &frame__29_8, 566, 566, 14, 36},
  {cont__29_237, &frame__29_8, 566, 574, 7, 63},
  {cont__29_257, &frame__29_8, 575, 575, 10, 22},
  {cont__29_258, &frame__29_8, 575, 575, 10, 30},
  {cont__29_259, &frame__29_8, 575, 589, 7, 34},
  {cont__29_279, &frame__29_8, 592, 592, 9, 42},
  {cont__29_280, &frame__29_8, 591, 592, 7, 64},
  {cont__29_281, &frame__29_8, 594, 609, 7, 72},
  {cont__29_301, &frame__29_8, 611, 611, 9, 26},
  {cont__29_303, &frame__29_8, 612, 612, 24, 40},
  {cont__29_304, &frame__29_8, 612, 612, 24, 69},
  {cont__29_305, &frame__29_8, 612, 612, 9, 76},
  {cont__29_308, &frame__29_8, 610, 612, 7, 76},
  {entry__29_3, NULL, 392, 392, 25, 45},
  {cont__29_4, &frame__29_3, 392, 392, 17, 52},
  {cont__29_7, &frame__29_3, 392, 612, 5, 77},
  {entry__29_1, NULL, 391, 391, 6, 29},
  {cont__29_2, &frame__29_1, 391, 612, 3, 78},
  {entry__30_8, NULL, 622, 622, 59, 59},
  {cont__30_9, &frame__30_8, 622, 622, 42, 60},
  {cont__30_10, &frame__30_8, 622, 622, 13, 61},
  {cont__30_11, &frame__30_8, 624, 624, 26, 42},
  {cont__30_12, &frame__30_8, 623, 624, 16, 67},
  {cont__30_16, &frame__30_8, 623, 624, 13, 67},
  {entry__30_5, NULL, 620, 620, 11, 39},
  {cont__30_7, &frame__30_5, 619, 624, 9, 68},
  {cont__30_17, &frame__30_5, 617, 624, 7, 70},
  {cont__30_18, &frame__30_5, 624, 624, 71, 71},
  {entry__30_2, NULL, 616, 616, 8, 17},
  {cont__30_4, &frame__30_2, 616, 624, 5, 71},
  {cont__30_19, &frame__30_2, 625, 625, 5, 13},
  {entry__30_29, NULL, 632, 632, 27, 52},
  {entry__30_34, NULL, 636, 636, 24, 48},
  {cont__30_35, &frame__30_34, 636, 636, 11, 62},
  {cont__30_36, &frame__30_34, 636, 636, 62, 62},
  {entry__30_40, NULL, 639, 639, 26, 50},
  {cont__30_41, &frame__30_40, 639, 639, 52, 76},
  {cont__30_42, &frame__30_40, 638, 639, 11, 77},
  {cont__30_43, &frame__30_40, 641, 641, 12, 29},
  {cont__30_44, &frame__30_40, 641, 641, 12, 38},
  {cont__30_45, &frame__30_40, 641, 641, 40, 52},
  {cont__30_46, &frame__30_40, 641, 641, 11, 53},
  {cont__30_47, &frame__30_40, 641, 641, 11, 29},
  {cont__30_48, &frame__30_40, 641, 641, 58, 58},
  {entry__30_32, NULL, 635, 635, 16, 42},
  {cont__30_33, &frame__30_32, 635, 636, 9, 62},
  {cont__30_37, &frame__30_32, 637, 637, 12, 24},
  {cont__30_38, &frame__30_32, 637, 637, 12, 35},
  {cont__30_39, &frame__30_32, 637, 641, 9, 58},
  {cont__30_49, &frame__30_32, 642, 642, 9, 29},
  {cont__30_50, &frame__30_32, 642, 642, 41, 41},
  {entry__30_26, NULL, 631, 631, 7, 25},
  {cont__30_27, &frame__30_26, 632, 632, 10, 24},
  {cont__30_28, &frame__30_26, 632, 632, 7, 52},
  {cont__30_30, &frame__30_26, 634, 634, 16, 31},
  {cont__30_31, &frame__30_26, 634, 642, 7, 41},
  {cont__30_51, &frame__30_26, 643, 643, 8, 24},
  {cont__30_52, &frame__30_26, 643, 643, 7, 24},
  {cont__30_53, &frame__30_26, 643, 643, 43, 43},
  {entry__30_23, NULL, 630, 630, 8, 20},
  {cont__30_24, &frame__30_23, 630, 630, 8, 28},
  {cont__30_25, &frame__30_23, 630, 643, 5, 43},
  {entry__30_63, NULL, 655, 655, 18, 50},
  {cont__30_64, &frame__30_63, 655, 655, 13, 50},
  {cont__30_65, &frame__30_63, 656, 656, 27, 39},
  {cont__30_66, &frame__30_63, 656, 656, 24, 46},
  {cont__30_67, &frame__30_63, 656, 656, 15, 46},
  {cont__30_68, &frame__30_63, 656, 656, 13, 52},
  {entry__30_62, NULL, 654, 656, 11, 52},
  {entry__30_71, NULL, 657, 657, 43, 63},
  {cont__30_72, &frame__30_71, 657, 657, 39, 64},
  {cont__30_73, &frame__30_71, 657, 657, 39, 64},
  {entry__30_75, NULL, 658, 658, 14, 39},
  {cont__30_76, &frame__30_75, 658, 658, 14, 42},
  {cont__30_77, &frame__30_75, 658, 658, 11, 42},
  {entry__30_80, NULL, 660, 660, 27, 43},
  {cont__30_81, &frame__30_80, 660, 660, 45, 52},
  {cont__30_82, &frame__30_80, 660, 660, 11, 52},
  {entry__30_58, NULL, 651, 651, 9, 28},
  {cont__30_59, &frame__30_58, 652, 652, 9, 43},
  {cont__30_60, &frame__30_58, 653, 653, 12, 27},
  {cont__30_61, &frame__30_58, 653, 656, 9, 53},
  {cont__30_69, &frame__30_58, 657, 657, 12, 34},
  {cont__30_70, &frame__30_58, 657, 657, 12, 64},
  {cont__30_74, &frame__30_58, 657, 658, 9, 42},
  {cont__30_78, &frame__30_58, 659, 659, 18, 39},
  {cont__30_79, &frame__30_58, 659, 660, 9, 52},
  {entry__30_57, NULL, 650, 660, 7, 53},
  {entry__30_89, NULL, 666, 666, 37, 49},
  {cont__30_90, &frame__30_89, 666, 666, 37, 62},
  {cont__30_91, &frame__30_89, 666, 666, 37, 62},
  {entry__30_93, NULL, 667, 667, 11, 30},
  {entry__30_86, NULL, 666, 666, 12, 24},
  {cont__30_87, &frame__30_86, 666, 666, 12, 32},
  {cont__30_88, &frame__30_86, 666, 666, 12, 62},
  {cont__30_92, &frame__30_86, 666, 667, 9, 30},
  {entry__30_85, NULL, 665, 667, 7, 31},
  {entry__30_56, NULL, 662, 662, 5, 12},
  {cont__30_83, &frame__30_56, 663, 663, 5, 19},
  {cont__30_84, &frame__30_56, 664, 667, 5, 32},
  {entry__30_102, NULL, 674, 674, 20, 31},
  {cont__30_104, &frame__30_102, 674, 674, 11, 31},
  {cont__30_105, &frame__30_102, 674, 674, 33, 52},
  {cont__30_106, &frame__30_102, 674, 674, 9, 52},
  {entry__30_107, NULL, 676, 676, 9, 16},
  {entry__30_123, NULL, 686, 686, 22, 41},
  {cont__30_124, &frame__30_123, 686, 686, 17, 41},
  {cont__30_125, &frame__30_123, 687, 687, 19, 35},
  {cont__30_127, &frame__30_123, 687, 687, 17, 66},
  {entry__30_121, NULL, 685, 685, 18, 30},
  {cont__30_122, &frame__30_121, 685, 687, 15, 66},
  {entry__30_118, NULL, 684, 684, 16, 28},
  {cont__30_120, &frame__30_118, 684, 687, 13, 67},
  {entry__30_116, NULL, 682, 682, 11, 26},
  {cont__30_117, &frame__30_116, 683, 687, 11, 68},
  {entry__30_133, NULL, 691, 691, 43, 63},
  {cont__30_134, &frame__30_133, 691, 691, 39, 64},
  {cont__30_135, &frame__30_133, 691, 691, 39, 64},
  {entry__30_137, NULL, 692, 692, 19, 44},
  {cont__30_138, &frame__30_137, 692, 692, 11, 47},
  {cont__30_139, &frame__30_137, 692, 692, 47, 47},
  {entry__30_142, NULL, 698, 698, 13, 25},
  {entry__30_144, NULL, 700, 700, 13, 34},
  {entry__30_146, NULL, 702, 702, 13, 37},
  {entry__30_148, NULL, 704, 704, 13, 28},
  {entry__30_150, NULL, 706, 706, 13, 21},
  {entry__30_151, NULL, 707, 707, 13, 24},
  {entry__30_156, NULL, 712, 712, 15, 55},
  {cont__30_158, &frame__30_156, 712, 712, 55, 55},
  {entry__30_159, NULL, 714, 714, 31, 31},
  {entry__30_154, NULL, 711, 711, 13, 29},
  {cont__30_155, &frame__30_154, 710, 714, 11, 32},
  {entry__30_162, NULL, 715, 715, 33, 47},
  {cont__30_163, &frame__30_162, 715, 715, 33, 47},
  {entry__30_172, NULL, 718, 718, 31, 42},
  {cont__30_173, &frame__30_172, 718, 718, 28, 49},
  {cont__30_174, &frame__30_172, 718, 718, 19, 49},
  {cont__30_175, &frame__30_172, 718, 718, 51, 68},
  {cont__30_176, &frame__30_172, 718, 718, 17, 68},
  {entry__30_166, NULL, 717, 717, 16, 32},
  {cont__30_169, &frame__30_166, 717, 717, 34, 50},
  {cont__30_170, &frame__30_166, 717, 717, 13, 50},
  {cont__30_171, &frame__30_166, 718, 718, 13, 68},
  {cont__30_177, &frame__30_166, 719, 719, 16, 33},
  {cont__30_179, &frame__30_166, 719, 719, 13, 40},
  {entry__30_165, NULL, 716, 719, 11, 40},
  {entry__30_112, NULL, 681, 681, 12, 19},
  {cont__30_113, &frame__30_112, 681, 681, 12, 29},
  {cont__30_114, &frame__30_112, 681, 681, 12, 29},
  {cont__30_115, &frame__30_112, 681, 687, 9, 69},
  {cont__30_129, &frame__30_112, 689, 689, 9, 27},
  {cont__30_130, &frame__30_112, 690, 690, 9, 43},
  {cont__30_131, &frame__30_112, 691, 691, 12, 34},
  {cont__30_132, &frame__30_112, 691, 691, 12, 64},
  {cont__30_136, &frame__30_112, 691, 692, 9, 47},
  {cont__30_140, &frame__30_112, 696, 696, 13, 25},
  {cont__30_141, &frame__30_112, 694, 707, 9, 25},
  {cont__30_152, &frame__30_112, 709, 709, 12, 31},
  {cont__30_153, &frame__30_112, 709, 714, 9, 33},
  {cont__30_160, &frame__30_112, 715, 715, 12, 28},
  {cont__30_161, &frame__30_112, 715, 715, 12, 47},
  {cont__30_164, &frame__30_112, 715, 719, 9, 41},
  {entry__30_111, NULL, 680, 719, 7, 42},
  {entry__30_96, NULL, 669, 669, 5, 12},
  {cont__30_97, &frame__30_96, 670, 670, 8, 21},
  {cont__30_100, &frame__30_96, 670, 670, 5, 36},
  {cont__30_101, &frame__30_96, 671, 676, 5, 17},
  {cont__30_109, &frame__30_96, 677, 677, 5, 6},
  {cont__30_110, &frame__30_96, 678, 719, 5, 43},
  {entry__30_189, NULL, 726, 726, 28, 55},
  {cont__30_191, &frame__30_189, 726, 726, 11, 67},
  {entry__30_187, NULL, 725, 725, 18, 33},
  {cont__30_188, &frame__30_187, 725, 726, 9, 67},
  {entry__30_184, NULL, 723, 723, 7, 32},
  {cont__30_185, &frame__30_184, 724, 724, 12, 24},
  {cont__30_186, &frame__30_184, 724, 726, 7, 68},
  {entry__30_181, NULL, 721, 721, 5, 23},
  {cont__30_182, &frame__30_181, 722, 722, 8, 22},
  {cont__30_183, &frame__30_181, 722, 726, 5, 69},
  {entry__30_206, NULL, 733, 733, 19, 35},
  {cont__30_207, &frame__30_206, 733, 733, 17, 41},
  {entry__30_205, NULL, 733, 733, 13, 41},
  {entry__30_199, NULL, 732, 732, 38, 56},
  {cont__30_200, &frame__30_199, 732, 732, 58, 66},
  {cont__30_202, &frame__30_199, 732, 732, 26, 67},
  {cont__30_203, &frame__30_199, 732, 732, 9, 76},
  {cont__30_204, &frame__30_199, 733, 733, 9, 41},
  {entry__30_198, NULL, 731, 733, 7, 41},
  {entry__30_194, NULL, 728, 728, 5, 12},
  {cont__30_195, &frame__30_194, 729, 729, 8, 21},
  {cont__30_196, &frame__30_194, 729, 729, 5, 35},
  {cont__30_197, &frame__30_194, 730, 733, 5, 42},
  {entry__30_221, NULL, 741, 741, 37, 53},
  {cont__30_222, &frame__30_221, 741, 741, 30, 62},
  {cont__30_223, &frame__30_221, 741, 741, 21, 62},
  {cont__30_224, &frame__30_221, 741, 741, 19, 72},
  {entry__30_220, NULL, 741, 741, 15, 72},
  {entry__30_219, NULL, 741, 741, 11, 72},
  {entry__30_218, NULL, 740, 741, 9, 72},
  {entry__30_214, NULL, 737, 737, 7, 14},
  {cont__30_215, &frame__30_214, 738, 738, 10, 23},
  {cont__30_216, &frame__30_214, 738, 738, 7, 29},
  {cont__30_217, &frame__30_214, 739, 741, 7, 73},
  {entry__30_209, NULL, 735, 735, 27, 45},
  {cont__30_210, &frame__30_209, 735, 735, 47, 55},
  {cont__30_211, &frame__30_209, 735, 735, 5, 56},
  {cont__30_212, &frame__30_209, 736, 736, 17, 39},
  {cont__30_213, &frame__30_209, 736, 741, 5, 74},
  {entry__30_230, NULL, 744, 744, 10, 31},
  {cont__30_231, &frame__30_230, 744, 744, 8, 40},
  {entry__30_233, NULL, 745, 745, 10, 35},
  {cont__30_234, &frame__30_233, 745, 745, 8, 48},
  {entry__30_236, NULL, 746, 746, 10, 37},
  {cont__30_237, &frame__30_236, 746, 746, 8, 52},
  {entry__30_239, NULL, 747, 747, 10, 36},
  {cont__30_240, &frame__30_239, 747, 747, 8, 50},
  {entry__30_227, NULL, 743, 743, 5, 19},
  {cont__30_229, &frame__30_227, 744, 744, 5, 40},
  {cont__30_232, &frame__30_227, 745, 745, 5, 48},
  {cont__30_235, &frame__30_227, 746, 746, 5, 52},
  {cont__30_238, &frame__30_227, 747, 747, 5, 50},
  {entry__30_1, NULL, 627, 627, 42, 42},
  {cont__30_20, &frame__30_1, 627, 627, 3, 43},
  {cont__30_21, &frame__30_1, 628, 628, 3, 43},
  {cont__30_22, &frame__30_1, 629, 643, 3, 44},
  {cont__30_54, &frame__30_1, 644, 667, 3, 33},
  {cont__30_94, &frame__30_1, 668, 719, 3, 44},
  {cont__30_180, &frame__30_1, 720, 726, 3, 70},
  {cont__30_192, &frame__30_1, 727, 733, 3, 43},
  {cont__30_208, &frame__30_1, 734, 741, 3, 75},
  {cont__30_225, &frame__30_1, 742, 747, 3, 50},
  {cont__30_241, &frame__30_1, 747, 747, 50, 50}
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
  frame->cont = cont__36_1;
}
static void cont__36_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 39: $$definitions empty_key_order_table
  var._definitions = get__empty_key_order_table();
  // 40: $$topics empty_key_order_table
  var._topics = get__empty_key_order_table();
  // 53: ... sim2c::WHITESPACE, '=', sim2c::WHITESPACE
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = get__sim2c__WHITESPACE();
  arguments->slots[1] = character__61;
  arguments->slots[2] = get__sim2c__WHITESPACE();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__44_1;
}
static void cont__44_1(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 53: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__44_2;
}
static void cont__44_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 54: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__44_3;
}
static void cont__44_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__6 */ = arguments->slots[0];
  // 54: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__44_4;
}
static void cont__44_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__5 */ = arguments->slots[0];
  // 54: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__44_5;
}
static void cont__44_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 52: sequence
  // 53:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 54:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__4 */;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__44_6;
}
static void cont__44_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 48: $PARAMETER_COUNT_OR_MYSELF
  // 49:   alt
  // 50:     '*'
  // 51:     '?'
  // 52:     sequence
  // 53:       alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 54:       many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__42;
  arguments->slots[1] = character__63;
  arguments->slots[2] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__44_7;
}
static void cont__44_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._PARAMETER_COUNT_OR_MYSELF, arguments->slots[0]);
  // 56: $$path_prefix undefined
  var._path_prefix = get__undefined();
  // 146: types::object $symbol_info
  // 147:   .kind_of BORING
  // 148:   .name_of undefined
  // 149:   .base_of undefined
  // 150:   .parameters_of undefined
  // 151:   .remark_lines_of undefined
  // 152:   .derived_types_of empty_key_order_set
  // 153:   .methods_of empty_key_order_table
  // 154:   .types_of empty_key_order_set
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
  // 357: ... alt("Topics" "Topic")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__56_1;
  arguments->slots[1] = string__56_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__56_3;
}
static void cont__56_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 357: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = character__58;
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
  initialize_future(var._TOPIC, arguments->slots[0]);
  // 358: ... alt("Example" "Output")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__57_1;
  arguments->slots[1] = string__57_2;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__57_3;
}
static void cont__57_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 358: ... not_followed_by(':')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__58;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__57_4;
}
static void cont__57_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__4 */ = arguments->slots[0];
  // 358: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__4 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__57_5;
}
static void cont__57_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__3 */ = arguments->slots[0];
  // 358: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__3 */;
  result_count = 1;
  myself = get__some();
  func = myself->type;
  frame->cont = cont__57_6;
}
static void cont__57_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__2 */ = arguments->slots[0];
  // 358: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* temp__2 */;
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__57_7;
}
static void cont__57_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(var._EXAMPLE, arguments->slots[0]);
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_1(void) {
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
  // 61: ... :
  // 62:   HTML:
  // 63:     HEAD:
  // 64:       STYLE "
  // 65:         body {
  // 66:           background-color: white;
  // 67:           font-family: Times New Roman, Times;
  // 68:           font-size: 12pt;
  // 69:           color: #222;
  // 70:         }
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__16_2, 0);
  // 61: collect_output $page:
  // 62:   HTML:
  // 63:     HEAD:
  // 64:       STYLE "
  // 65:         body {
  // 66:           background-color: white;
  // 67:           font-family: Times New Roman, Times;
  // 68:           font-size: 12pt;
  // 69:           color: #222;
  // 70:         }
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__collect_output();
  func = myself->type;
  frame->cont = cont__16_7;
}
static void entry__16_3(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 63: HEAD:
  // 64:   STYLE "
  // 65:     body {
  // 66:       background-color: white;
  // 67:       font-family: Times New Roman, Times;
  // 68:       font-size: 12pt;
  // 69:       color: #222;
  // 70:     }
  // 71:     h1 {
  // 72:       font-family: Arial, Helvetica;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__16_4;
  result_count = 0;
  myself = get__HEAD();
  func = myself->type;
  frame->cont = cont__16_6;
}
static void entry__16_4(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 64: STYLE "
  // 65:   body {
  // 66:     background-color: white;
  // 67:     font-family: Times New Roman, Times;
  // 68:     font-size: 12pt;
  // 69:     color: #222;
  // 70:   }
  // 71:   h1 {
  // 72:     font-family: Arial, Helvetica;
  // 73:     font-size: 20pt;
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__16_5;
  result_count = frame->caller_result_count;
  myself = get__STYLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_6(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 143: BODY body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* body */;
  result_count = frame->caller_result_count;
  myself = get__BODY();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__16_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // body: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* body */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 62: ... :
  // 63:   HEAD:
  // 64:     STYLE "
  // 65:       body {
  // 66:         background-color: white;
  // 67:         font-family: Times New Roman, Times;
  // 68:         font-size: 12pt;
  // 69:         color: #222;
  // 70:       }
  // 71:       h1 {
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__16_3, 0);
  // 62: HTML:
  // 63:   HEAD:
  // 64:     STYLE "
  // 65:       body {
  // 66:         background-color: white;
  // 67:         font-family: Times New Roman, Times;
  // 68:         font-size: 12pt;
  // 69:         color: #222;
  // 70:       }
  // 71:       h1 {
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__HTML();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* page */, arguments->slots[0]);
  // 144: save filename page
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = frame->slots[2] /* page */;
  result_count = frame->caller_result_count;
  myself = get__save();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_1(void) {
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
  // 157: ... "extracting documentation from @(filename)@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__18_2;
  arguments->slots[1] = frame->slots[0] /* filename */;
  arguments->slots[2] = string__18_3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 157: ewrite "extracting documentation from @(filename)@nl;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__ewrite();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 158: ... load(filename)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__load();
  func = myself->type;
  frame->cont = cont__18_6;
}
static void cont__18_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 158: $buf load(filename).from_utf8
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__from_utf8();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* buf */, arguments->slots[0]);
  // 159: ... length_of(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__length_of();
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 159: ... length_of(buf) == 0
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = number__0;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_9;
}
static void cont__18_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 159: if length_of(buf) == 0: Error "Empty source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__18_10;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_12;
}
static void entry__18_10(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 159: ... Error "Empty source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__18_11;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 160: ... buf(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__18_13;
}
static void cont__18_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 160: ... buf(1) <= ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__less();
  func = myself->type;
  frame->cont = cont__18_14;
}
static void cont__18_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 160: ... buf(1) <= ' '
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__18_15;
}
static void cont__18_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 160: if buf(1) <= ' ': Error "Whitespace at start of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__18_16;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_18;
}
static void entry__18_16(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 160: ... Error "Whitespace at start of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__18_17;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 161: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__18_19;
}
static void cont__18_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__4 */ = arguments->slots[0];
  // 161: ... buf(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[10] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[2] /* buf */;
  func = myself->type;
  frame->cont = cont__18_20;
}
static void cont__18_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 161: ... buf(-1) != newline
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = get__newline();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_21;
}
static void cont__18_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 161: ... buf(-1) != newline
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__18_22;
}
static void cont__18_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 161: if buf(-1) != newline: Error "Missing newline at end of source text!"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__18_23;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_25;
}
static void entry__18_23(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 161: ... Error "Missing newline at end of source text!"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__18_24;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_25(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 164: ... filename .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* filename */;
  arguments->slots[1] = string__18_26;
  result_count = 1;
  myself = get__without_suffix();
  func = myself->type;
  frame->cont = cont__18_27;
}
static void cont__18_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 164: ... '/' = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__18_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__18_29;
}
static void cont__18_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 163: %sim2c::module_name
  // 164:   replace_all(filename .without_suffix. ".sim" '/' = "__")
  // 165:     #filename .without_prefix. main_prefix .without_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__18_30;
}
static void cont__18_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__sim2c__module_name(), arguments->slots[0]);
  // 167: %%sim2c::required_modules empty_insert_order_table
  set__sim2c__required_modules(get__empty_insert_order_table());
  // 168: %%sim2c::used_namespaces empty_insert_order_set
  set__sim2c__used_namespaces(get__empty_insert_order_set());
  // 169: %%sim2c::defined_namespaces empty_insert_order_set
  set__sim2c__defined_namespaces(get__empty_insert_order_set());
  // 170: %%sim2c::namespace_mappings empty_insert_order_table
  set__sim2c__namespace_mappings(get__empty_insert_order_table());
  // 171: %%sim2c::included_files empty_insert_order_set
  set__sim2c__included_files(get__empty_insert_order_set());
  // 172: %%sim2c::linked_libraries empty_insert_order_set
  set__sim2c__linked_libraries(get__empty_insert_order_set());
  // 173: %%sim2c::enumeration_count 0
  set__sim2c__enumeration_count(number__0);
  // 174: $$fragments cut_into_fragments(buf)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* buf */;
  result_count = 1;
  myself = get__cut_into_fragments();
  func = myself->type;
  frame->cont = cont__18_31;
}
static void cont__18_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 175: update_each &fragments: (&fragment) tokenize &fragment
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = func__18_32;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__18_34;
}
static void entry__18_32(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // fragment: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* fragment */ = create_cell_with_contents(arguments->slots[0]);
  // 175: ... tokenize &fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* fragment */;
  result_count = 1;
  myself = get__tokenize();
  func = myself->type;
  frame->cont = cont__18_33;
}
static void cont__18_33(void) {
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
static void cont__18_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 176: $$trees empty_list
  ((CELL *)frame->slots[4])->contents /* trees */ = get__empty_list();
  // 177: $$first_idx 1
  ((CELL *)frame->slots[5])->contents /* first_idx */ = number__1;
  // 178: ... : (-> done)
  // 179:   for_each fragments: (idx fragment)
  // 180:     case
  // 181:       source_of(fragment)(1)
  // 182:       '#':
  // 183:         !first_idx idx+1 # ignore remark
  // 184:       '<':
  // 185:         !first_idx idx+1
  // 186:         parse_meta_instruction $_tree fragment
  // 187:       :
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__18_35, 0);
  // 178: do: (-> done)
  // 179:   for_each fragments: (idx fragment)
  // 180:     case
  // 181:       source_of(fragment)(1)
  // 182:       '#':
  // 183:         !first_idx idx+1 # ignore remark
  // 184:       '<':
  // 185:         !first_idx idx+1
  // 186:         parse_meta_instruction $_tree fragment
  // 187:       :
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__18_46;
}
static void entry__18_35(void) {
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
  // 179: ... : (idx fragment)
  // 180:   case
  // 181:     source_of(fragment)(1)
  // 182:     '#':
  // 183:       !first_idx idx+1 # ignore remark
  // 184:     '<':
  // 185:       !first_idx idx+1
  // 186:       parse_meta_instruction $_tree fragment
  // 187:     :
  // 188:       done
  frame->slots[3] /* temp__1 */ = create_closure(entry__18_36, 2);
  // 179: for_each fragments: (idx fragment)
  // 180:   case
  // 181:     source_of(fragment)(1)
  // 182:     '#':
  // 183:       !first_idx idx+1 # ignore remark
  // 184:     '<':
  // 185:       !first_idx idx+1
  // 186:       parse_meta_instruction $_tree fragment
  // 187:     :
  // 188:       done
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* fragments */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__18_45;
}
static void entry__18_39(void) {
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
  // 183: !first_idx idx+1 # ignore remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_40;
}
static void cont__18_40(void) {
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
static void entry__18_41(void) {
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
  // 185: !first_idx idx+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* idx */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__18_42;
}
static void cont__18_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* first_idx */ = arguments->slots[0];
  // 186: parse_meta_instruction $_tree fragment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* fragment */;
  result_count = 1;
  myself = get__parse_meta_instruction();
  func = myself->type;
  frame->cont = cont__18_43;
}
static void cont__18_43(void) {
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
static void entry__18_44(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // done: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* done */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 188: done
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_36(void) {
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
  // 181: source_of(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* fragment */;
  result_count = 1;
  myself = get__source_of();
  func = myself->type;
  frame->cont = cont__18_37;
}
static void cont__18_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 181: source_of(fragment)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__18_38;
}
static void cont__18_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 182: ... :
  // 183:   !first_idx idx+1 # ignore remark
  frame->slots[6] /* temp__3 */ = create_closure(entry__18_39, 0);
  // 184: ... :
  // 185:   !first_idx idx+1
  // 186:   parse_meta_instruction $_tree fragment
  frame->slots[7] /* temp__4 */ = create_closure(entry__18_41, 0);
  // 187: :
  // 188:   done
  frame->slots[8] /* temp__5 */ = create_closure(entry__18_44, 0);
  // 180: case
  // 181:   source_of(fragment)(1)
  // 182:   '#':
  // 183:     !first_idx idx+1 # ignore remark
  // 184:   '<':
  // 185:     !first_idx idx+1
  // 186:     parse_meta_instruction $_tree fragment
  // 187:   :
  // 188:     done
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
static void cont__18_45(void) {
  myself = frame->slots[0] /* done */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__18_46(void) {
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
  frame->cont = cont__18_47;
}
static void cont__18_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 189: range &fragments first_idx -1
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = ((CELL *)frame->slots[5])->contents /* first_idx */;
  arguments->slots[2] = frame->slots[7] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__18_48;
}
static void cont__18_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* fragments */ = arguments->slots[0];
  // 190: ... : (fragment) push &trees parse_statement(fragment)
  frame->slots[7] /* temp__1 */ = create_closure(entry__18_49, 1);
  // 190: for_each fragments: (fragment) push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* fragments */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__18_52;
}
static void entry__18_49(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // fragment: 0
  // trees: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* trees */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 190: ... parse_statement(fragment)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* fragment */;
  result_count = 1;
  myself = get__parse_statement();
  func = myself->type;
  frame->cont = cont__18_50;
}
static void cont__18_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 190: ... push &trees parse_statement(fragment)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* trees */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__18_51;
}
static void cont__18_51(void) {
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
static void cont__18_52(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 191: ... used_namespaces.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__used_namespaces();
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__18_53;
}
static void cont__18_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 191: if used_namespaces.is_empty: !used_namespaces("std") true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = func__18_54;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_57;
}
static void entry__18_54(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 191: ... !used_namespaces("std") true
  frame->slots[0] /* temp__1 */ = get__true();
  // 191: ... !used_namespaces("std")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__18_55;
  arguments->slots[1] = frame->slots[0] /* temp__1 */;
  result_count = 1;
  myself = get__used_namespaces();
  func = myself->type;
  frame->cont = cont__18_56;
}
static void cont__18_56(void) {
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
static void cont__18_57(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 192: $$local_method_names empty_set
  ((CELL *)frame->slots[6])->contents /* local_method_names */ = get__empty_set();
  // 193: ... : (statement)
  // 194:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 195:     $destination output_arguments_of(statement)(1)
  // 196:     if destination.is_a_definition:
  // 197:       $identifier identifier_of(destination)
  // 198:       unless namespace_of(identifier).is_defined:
  // 199:         $source arguments_of(statement)(1)
  // 200:         if source.is_a_polymorphic_function_constant:
  // 201:           !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[7] /* temp__1 */ = create_closure(entry__18_58, 1);
  // 193: for_each trees: (statement)
  // 194:   cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 195:     $destination output_arguments_of(statement)(1)
  // 196:     if destination.is_a_definition:
  // 197:       $identifier identifier_of(destination)
  // 198:       unless namespace_of(identifier).is_defined:
  // 199:         $source arguments_of(statement)(1)
  // 200:         if source.is_a_polymorphic_function_constant:
  // 201:           !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__18_83;
}
static void entry__18_79(void) {
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
  // 201: !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 201: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_80;
}
static void cont__18_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 201: ... name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__18_81;
}
static void cont__18_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 201: !local_method_names(name_of(identifier_of(destination)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[0])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__18_82;
}
static void cont__18_82(void) {
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
static void entry__18_75(void) {
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
  // 199: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__18_76;
}
static void cont__18_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 199: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__18_77;
}
static void cont__18_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* source */, arguments->slots[0]);
  // 200: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__18_78;
}
static void cont__18_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 200: ... :
  // 201:   !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[5] /* temp__2 */ = create_closure(entry__18_79, 0);
  // 200: if source.is_a_polymorphic_function_constant:
  // 201:   !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_71(void) {
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
  // 197: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_72;
}
static void cont__18_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 198: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__18_73;
}
static void cont__18_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 198: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_74;
}
static void cont__18_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 198: ... :
  // 199:   $source arguments_of(statement)(1)
  // 200:   if source.is_a_polymorphic_function_constant:
  // 201:     !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__18_75, 0);
  // 198: unless namespace_of(identifier).is_defined:
  // 199:   $source arguments_of(statement)(1)
  // 200:   if source.is_a_polymorphic_function_constant:
  // 201:     !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_67(void) {
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
  // 195: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__18_68;
}
static void cont__18_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 195: $destination output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__18_69;
}
static void cont__18_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* destination */, arguments->slots[0]);
  // 196: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__18_70;
}
static void cont__18_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 196: ... :
  // 197:   $identifier identifier_of(destination)
  // 198:   unless namespace_of(identifier).is_defined:
  // 199:     $source arguments_of(statement)(1)
  // 200:     if source.is_a_polymorphic_function_constant:
  // 201:       !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_71, 0);
  // 196: if destination.is_a_definition:
  // 197:   $identifier identifier_of(destination)
  // 198:   unless namespace_of(identifier).is_defined:
  // 199:     $source arguments_of(statement)(1)
  // 200:     if source.is_a_polymorphic_function_constant:
  // 201:       !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_64(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_61(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_59(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__18_60;
}
static void cont__18_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 194: ... -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_61;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_62(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 194: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__18_63;
}
static void cont__18_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 194: ... -> statement.is_c_code: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_64;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_65(void) {
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
  // 194: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__18_66;
}
static void cont__18_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 194: ... :
  // 195:   $destination output_arguments_of(statement)(1)
  // 196:   if destination.is_a_definition:
  // 197:     $identifier identifier_of(destination)
  // 198:     unless namespace_of(identifier).is_defined:
  // 199:       $source arguments_of(statement)(1)
  // 200:       if source.is_a_polymorphic_function_constant:
  // 201:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__18_67, 0);
  // 194: ... -> statement.is_an_assignment:
  // 195:   $destination output_arguments_of(statement)(1)
  // 196:   if destination.is_a_definition:
  // 197:     $identifier identifier_of(destination)
  // 198:     unless namespace_of(identifier).is_defined:
  // 199:       $source arguments_of(statement)(1)
  // 200:       if source.is_a_polymorphic_function_constant:
  // 201:         !local_method_names(name_of(identifier_of(destination))) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_58(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // statement: 0
  // local_method_names: 1
  frame->slots[1] = myself->closure.frame->slots[6]; /* local_method_names */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 194: ... -> statement.is_a_remark: pass
  frame->slots[2] /* temp__1 */ = create_closure(entry__18_59, 0);
  // 194: ... -> statement.is_c_code: pass
  frame->slots[3] /* temp__2 */ = create_closure(entry__18_62, 0);
  // 194: ... -> statement.is_an_assignment:
  // 195:   $destination output_arguments_of(statement)(1)
  // 196:   if destination.is_a_definition:
  // 197:     $identifier identifier_of(destination)
  // 198:     unless namespace_of(identifier).is_defined:
  // 199:       $source arguments_of(statement)(1)
  // 200:       if source.is_a_polymorphic_function_constant:
  // 201:         !local_method_names(name_of(identifier_of(destination))) true
  frame->slots[4] /* temp__3 */ = create_closure(entry__18_65, 0);
  // 194: cond (-> statement.is_a_remark: pass) (-> statement.is_c_code: pass) -> statement.is_an_assignment:
  // 195:   $destination output_arguments_of(statement)(1)
  // 196:   if destination.is_a_definition:
  // 197:     $identifier identifier_of(destination)
  // 198:     unless namespace_of(identifier).is_defined:
  // 199:       $source arguments_of(statement)(1)
  // 200:       if source.is_a_polymorphic_function_constant:
  // 201:         !local_method_names(name_of(identifier_of(destination))) true
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
static void cont__18_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 202: ... :
  // 203:   (
  // 204:     statement
  // 205:     -> break
  // 206:   )
  // 207:   cond
  // 208:     -> statement.is_a_remark: pass
  // 209:     -> statement.is_c_code:
  // 210:       if kind_of(statement) == "type":
  // 211:         $identifier identifier_of(statement)
  // ...
  frame->slots[7] /* temp__1 */ = create_closure(entry__18_84, 1);
  // 202: for_each trees:
  // 203:   (
  // 204:     statement
  // 205:     -> break
  // 206:   )
  // 207:   cond
  // 208:     -> statement.is_a_remark: pass
  // 209:     -> statement.is_c_code:
  // 210:       if kind_of(statement) == "type":
  // 211:         $identifier identifier_of(statement)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* trees */;
  arguments->slots[1] = frame->slots[7] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__18_190;
}
static void entry__18_84(void) {
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
  // 208: -> statement.is_a_remark: pass
  frame->slots[4] /* temp__1 */ = create_closure(entry__18_85, 0);
  // 209: -> statement.is_c_code:
  // 210:   if kind_of(statement) == "type":
  // 211:     $identifier identifier_of(statement)
  // 212:     $namespace namespace_of(identifier)
  // 213:     if namespace.is_defined:
  // 214:       $name name_of(identifier)
  // 215:       $base base_of(statement)
  // 216:       !definitions(ordered_name(namespace name))
  // 217:         symbol_info
  // 218:           .kind_of TYPE
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__18_88, 0);
  // 223: -> statement.is_an_assignment:
  // 224:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 225:   $$info symbol_info(.filename_of filename)
  // 226:   if destination.is_a_definition:
  // 227:     $identifier identifier_of(destination)
  // 228:     $namespace namespace_of(identifier)
  // 229:     if namespace.is_defined:
  // 230:       $name name_of(identifier)
  // 231:       $iname ordered_name(namespace name)
  // 232:       !info.name_of identifier.to_string
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__18_110, 0);
  // 207: cond
  // 208:   -> statement.is_a_remark: pass
  // 209:   -> statement.is_c_code:
  // 210:     if kind_of(statement) == "type":
  // 211:       $identifier identifier_of(statement)
  // 212:       $namespace namespace_of(identifier)
  // 213:       if namespace.is_defined:
  // 214:         $name name_of(identifier)
  // 215:         $base base_of(statement)
  // 216:         !definitions(ordered_name(namespace name))
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__18_189;
}
static void entry__18_179(void) {
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
  // 281: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__18_180;
}
static void cont__18_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 281: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_181;
}
static void cont__18_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 281: ... :
  // 282:   !attr.used_namespaces_of used_namespaces
  frame->slots[7] /* temp__3 */ = create_closure(entry__18_182, 0);
  // 281: unless namespace_of(attr).is_defined:
  // 282:   !attr.used_namespaces_of used_namespaces
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__18_183;
}
static void entry__18_182(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 282: !attr.used_namespaces_of used_namespaces
  frame->slots[1] /* temp__1 */ = get__used_namespaces();
  // 282: !attr.used_namespaces_of
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
static void cont__18_183(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 283: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_184;
}
static void cont__18_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 283: $$definition default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__18_185;
}
static void cont__18_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* definition */ = arguments->slots[0];
  // 284: !definition.kind_of TYPE
  frame->slots[5] /* temp__1 */ = var._TYPE;
  // 284: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[5] /* temp__1 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 285: !definition.methods_of(attr_name) info(.attribute_of attr)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, ((CELL *)frame->slots[0])->contents /* attr */);
    frame->slots[5] /* temp__1 */ = temp;

  }
  // 285: ... definition.methods_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__18_186;
}
static void cont__18_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 285: !definition.methods_of(attr_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attr_name */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[6] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__18_187;
}
static void cont__18_187(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 285: !definition.methods_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[4])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[4])->contents /* definition */ = temp;

  }
  // 286: !definitions(iname) definition
  frame->slots[5] /* temp__1 */ = ((CELL *)frame->slots[4])->contents /* definition */;
  // 286: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_188;
}
static void cont__18_188(void) {
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
static void entry__18_176(void) {
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
  // 279: $attr_name attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__18_177;
}
static void cont__18_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* attr_name */, arguments->slots[0]);
  // 280: ... local_method_names(attr_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* attr_name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_method_names */;
  func = myself->type;
  frame->cont = cont__18_178;
}
static void cont__18_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 280: ... :
  // 281:   unless namespace_of(attr).is_defined:
  // 282:     !attr.used_namespaces_of used_namespaces
  // 283:   $$definition default_value(definitions(iname) symbol_info)
  // 284:   !definition.kind_of TYPE
  // 285:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 286:   !definitions(iname) definition
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_179, 0);
  // 280: unless local_method_names(attr_name):
  // 281:   unless namespace_of(attr).is_defined:
  // 282:     !attr.used_namespaces_of used_namespaces
  // 283:   $$definition default_value(definitions(iname) symbol_info)
  // 284:   !definition.kind_of TYPE
  // 285:   !definition.methods_of(attr_name) info(.attribute_of attr)
  // 286:   !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_170(void) {
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
  // 272: $$attr attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__18_171;
}
static void cont__18_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[4])->contents /* attr */ = arguments->slots[0];
  // 275: ... definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_172;
}
static void cont__18_172(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 275: default_value(definitions(iname) symbol_info)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__2 */;
  arguments->slots[1] = var._symbol_info;
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__18_173;
}
static void cont__18_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 274: $type
  // 275:   default_value(definitions(iname) symbol_info)(.kind_of TYPE)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._TYPE);
    initialize_future(frame->slots[5] /* type */, temp);

  }
  // 277: !definitions(iname) type
  frame->slots[6] /* temp__1 */ = frame->slots[5] /* type */;
  // 277: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* iname */;
  arguments->slots[1] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_174;
}
static void cont__18_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 278: ... attr.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* attr */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_175;
}
static void cont__18_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 278: ... :
  // 279:   $attr_name attr.to_string
  // 280:   unless local_method_names(attr_name):
  // 281:     unless namespace_of(attr).is_defined:
  // 282:       !attr.used_namespaces_of used_namespaces
  // 283:     $$definition default_value(definitions(iname) symbol_info)
  // 284:     !definition.kind_of TYPE
  // 285:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 286:     !definitions(iname) definition
  frame->slots[7] /* temp__2 */ = create_closure(entry__18_176, 0);
  // 278: if attr.is_defined:
  // 279:   $attr_name attr.to_string
  // 280:   unless local_method_names(attr_name):
  // 281:     unless namespace_of(attr).is_defined:
  // 282:       !attr.used_namespaces_of used_namespaces
  // 283:     $$definition default_value(definitions(iname) symbol_info)
  // 284:     !definition.kind_of TYPE
  // 285:     !definition.methods_of(attr_name) info(.attribute_of attr)
  // 286:     !definitions(iname) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_120(void) {
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
  // 230: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__18_121;
}
static void cont__18_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[7] /* name */, arguments->slots[0]);
  // 231: $iname ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  arguments->slots[1] = frame->slots[7] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__18_122;
}
static void cont__18_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[8] /* iname */, arguments->slots[0]);
  // 232: !info.name_of identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__18_123;
}
static void cont__18_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 232: !info.name_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[10] /* temp__1 */);
    ((CELL *)frame->slots[2])->contents /* info */ = temp;

  }
  // 233: ... arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* statement */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__18_124;
}
static void cont__18_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 233: $source arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__18_125;
}
static void cont__18_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* source */, arguments->slots[0]);
  // 235: -> source.is_a_polymorphic_function_constant:
  // 236:   !polymorphic_functions(name namespace) true
  // 237:   !definitions(iname)
  // 238:     info
  // 239:       .kind_of POLYMORPHIC
  // 240:       .remark_lines_of remark_lines_of(statement)
  // 241:   break
  frame->slots[10] /* temp__1 */ = create_closure(entry__18_126, 0);
  // 242: -> source.is_a_body:
  // 243:   !info.base_of "types::function"
  // 244:   !info.kind_of FUNCTION
  // 245:   !info.parameters_of parameters_of(source)
  // 246:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[11] /* temp__2 */ = create_closure(entry__18_132, 0);
  // 247: -> source.is_a_c_body:
  // 248:   !info.kind_of INLINE_C_FUNCTION
  // 249:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[12] /* temp__3 */ = create_closure(entry__18_138, 0);
  // 250: -> source.is_an_identifier:
  // 251:   if namespace_of(source).is_defined:
  // 252:     !info
  // 253:       .base_of source.to_string
  // 254:       .remark_lines_of remark_lines_of(statement)
  frame->slots[13] /* temp__4 */ = create_closure(entry__18_142, 0);
  // 255: -> source.is_a_constant:
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of UNIQUE_ITEM
  // 259:       .remark_lines_of remark_lines_of(statement)
  // 260:   break
  frame->slots[14] /* temp__5 */ = create_closure(entry__18_150, 0);
  // 234: cond
  // 235:   -> source.is_a_polymorphic_function_constant:
  // 236:     !polymorphic_functions(name namespace) true
  // 237:     !definitions(iname)
  // 238:       info
  // 239:         .kind_of POLYMORPHIC
  // 240:         .remark_lines_of remark_lines_of(statement)
  // 241:     break
  // 242:   -> source.is_a_body:
  // 243:     !info.base_of "types::function"
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
  frame->cont = cont__18_155;
}
static void entry__18_152(void) {
  allocate_initialized_frame_gc(4, 6);
  // slot allocations:
  // iname: 0
  // info: 1
  // statement: 2
  // break: 3
  frame->slots[0] = myself->closure.frame->slots[1]; /* iname */
  frame->slots[1] = myself->closure.frame->slots[2]; /* info */
  frame->slots[2] = myself->closure.frame->slots[3]; /* statement */
  frame->slots[3] = myself->closure.frame->slots[4]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 259: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_153;
}
static void cont__18_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 256: !definitions(iname)
  // 257:   info
  // 258:     .kind_of UNIQUE_ITEM
  // 259:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, var._UNIQUE_ITEM);
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[4] /* temp__1 */);
    frame->slots[5] /* temp__2 */ = temp;

  }
  // 256: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_154;
}
static void cont__18_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 260: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[3] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_147(void) {
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
  // 253: ... source.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__18_148;
}
static void cont__18_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 254: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_149;
}
static void cont__18_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 252: !info
  // 253:   .base_of source.to_string
  // 254:   .remark_lines_of remark_lines_of(statement)
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
static void entry__18_144(void) {
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
  // 251: ... namespace_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__18_145;
}
static void cont__18_145(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 251: ... namespace_of(source).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_146;
}
static void cont__18_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 251: ... :
  // 252:   !info
  // 253:     .base_of source.to_string
  // 254:     .remark_lines_of remark_lines_of(statement)
  frame->slots[5] /* temp__3 */ = create_closure(entry__18_147, 0);
  // 251: if namespace_of(source).is_defined:
  // 252:   !info
  // 253:     .base_of source.to_string
  // 254:     .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_140(void) {
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
  // 248: !info.kind_of INLINE_C_FUNCTION
  frame->slots[2] /* temp__1 */ = var._INLINE_C_FUNCTION;
  // 248: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 249: !info.remark_lines_of remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_141;
}
static void cont__18_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 249: !info.remark_lines_of
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
static void entry__18_134(void) {
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
  // 243: !info.base_of "types::function"
  frame->slots[2] /* temp__1 */ = string__18_135;
  // 243: !info.base_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 244: !info.kind_of FUNCTION
  frame->slots[2] /* temp__1 */ = var._FUNCTION;
  // 244: !info.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 245: !info.parameters_of parameters_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__18_136;
}
static void cont__18_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 245: !info.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 246: !info.remark_lines_of remark_lines_of(source)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* source */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_137;
}
static void cont__18_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 246: !info.remark_lines_of
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
static void entry__18_128(void) {
  allocate_initialized_frame_gc(6, 8);
  // slot allocations:
  // name: 0
  // namespace: 1
  // iname: 2
  // info: 3
  // statement: 4
  // break: 5
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* namespace */
  frame->slots[2] = myself->closure.frame->slots[3]; /* iname */
  frame->slots[3] = myself->closure.frame->slots[4]; /* info */
  frame->slots[4] = myself->closure.frame->slots[5]; /* statement */
  frame->slots[5] = myself->closure.frame->slots[6]; /* break */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 236: !polymorphic_functions(name namespace) true
  frame->slots[6] /* temp__1 */ = get__true();
  // 236: !polymorphic_functions(name namespace)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* namespace */;
  arguments->slots[2] = frame->slots[6] /* temp__1 */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__18_129;
}
static void cont__18_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._polymorphic_functions = arguments->slots[0];
  // 240: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_130;
}
static void cont__18_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 237: !definitions(iname)
  // 238:   info
  // 239:     .kind_of POLYMORPHIC
  // 240:     .remark_lines_of remark_lines_of(statement)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[3])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, get__POLYMORPHIC());
    set_attribute_value(temp->attributes, poly_idx__remark_lines_of, frame->slots[6] /* temp__1 */);
    frame->slots[7] /* temp__2 */ = temp;

  }
  // 237: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* iname */;
  arguments->slots[1] = frame->slots[7] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_131;
}
static void cont__18_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._definitions = arguments->slots[0];
  // 241: break
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = frame->slots[5] /* break */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_126(void) {
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
  // 235: ... source.is_a_polymorphic_function_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_polymorphic_function_constant();
  func = myself->type;
  frame->cont = cont__18_127;
}
static void cont__18_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 235: ... :
  // 236:   !polymorphic_functions(name namespace) true
  // 237:   !definitions(iname)
  // 238:     info
  // 239:       .kind_of POLYMORPHIC
  // 240:       .remark_lines_of remark_lines_of(statement)
  // 241:   break
  frame->slots[8] /* temp__2 */ = create_closure(entry__18_128, 0);
  // 235: -> source.is_a_polymorphic_function_constant:
  // 236:   !polymorphic_functions(name namespace) true
  // 237:   !definitions(iname)
  // 238:     info
  // 239:       .kind_of POLYMORPHIC
  // 240:       .remark_lines_of remark_lines_of(statement)
  // 241:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_132(void) {
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
  // 242: ... source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__18_133;
}
static void cont__18_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 242: ... :
  // 243:   !info.base_of "types::function"
  // 244:   !info.kind_of FUNCTION
  // 245:   !info.parameters_of parameters_of(source)
  // 246:   !info.remark_lines_of remark_lines_of(source)
  frame->slots[3] /* temp__2 */ = create_closure(entry__18_134, 0);
  // 242: -> source.is_a_body:
  // 243:   !info.base_of "types::function"
  // 244:   !info.kind_of FUNCTION
  // 245:   !info.parameters_of parameters_of(source)
  // 246:   !info.remark_lines_of remark_lines_of(source)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_138(void) {
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
  // 247: ... source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__18_139;
}
static void cont__18_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 247: ... :
  // 248:   !info.kind_of INLINE_C_FUNCTION
  // 249:   !info.remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_140, 0);
  // 247: -> source.is_a_c_body:
  // 248:   !info.kind_of INLINE_C_FUNCTION
  // 249:   !info.remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_142(void) {
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
  // 250: ... source.is_an_identifier
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_an_identifier();
  func = myself->type;
  frame->cont = cont__18_143;
}
static void cont__18_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 250: ... :
  // 251:   if namespace_of(source).is_defined:
  // 252:     !info
  // 253:       .base_of source.to_string
  // 254:       .remark_lines_of remark_lines_of(statement)
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_144, 0);
  // 250: -> source.is_an_identifier:
  // 251:   if namespace_of(source).is_defined:
  // 252:     !info
  // 253:       .base_of source.to_string
  // 254:       .remark_lines_of remark_lines_of(statement)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_150(void) {
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
  // 255: ... source.is_a_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_constant();
  func = myself->type;
  frame->cont = cont__18_151;
}
static void cont__18_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 255: ... :
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of UNIQUE_ITEM
  // 259:       .remark_lines_of remark_lines_of(statement)
  // 260:   break
  frame->slots[6] /* temp__2 */ = create_closure(entry__18_152, 0);
  // 255: -> source.is_a_constant:
  // 256:   !definitions(iname)
  // 257:     info
  // 258:       .kind_of UNIQUE_ITEM
  // 259:       .remark_lines_of remark_lines_of(statement)
  // 260:   break
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_155(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 262: attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__18_156;
}
static void cont__18_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__1 */ = arguments->slots[0];
  // 263: ... :
  // 264:   $previous_definition definitions(iname)
  // 265:   if previous_definition.is_defined:
  // 266:     if kind_of(previous_definition) == TYPE:
  // 267:       !info.types_of types_of(previous_definition)
  // 268:       !info.derived_types_of derived_types_of(previous_definition)
  // 269:       !info.methods_of methods_of(previous_definition)
  // 270:   !definitions(iname) info
  frame->slots[11] /* temp__2 */ = create_closure(entry__18_157, 0);
  // 271: ATTRIBUTE_KIND, METHOD_KIND
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__ATTRIBUTE_KIND();
  arguments->slots[1] = get__METHOD_KIND();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__18_169;
}
static void entry__18_157(void) {
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
  // 264: $previous_definition definitions(iname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_158;
}
static void cont__18_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* previous_definition */, arguments->slots[0]);
  // 265: ... previous_definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* previous_definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_159;
}
static void cont__18_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   if kind_of(previous_definition) == TYPE:
  // 267:     !info.types_of types_of(previous_definition)
  // 268:     !info.derived_types_of derived_types_of(previous_definition)
  // 269:     !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__2 */ = create_closure(entry__18_160, 0);
  // 265: if previous_definition.is_defined:
  // 266:   if kind_of(previous_definition) == TYPE:
  // 267:     !info.types_of types_of(previous_definition)
  // 268:     !info.derived_types_of derived_types_of(previous_definition)
  // 269:     !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_167;
}
static void entry__18_163(void) {
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
  // 267: !info.types_of types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__18_164;
}
static void cont__18_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 267: !info.types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 268: !info.derived_types_of derived_types_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__18_165;
}
static void cont__18_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 268: !info.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* info */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* info */ = temp;

  }
  // 269: !info.methods_of methods_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* previous_definition */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__18_166;
}
static void cont__18_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 269: !info.methods_of
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
static void entry__18_160(void) {
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
  // 266: ... kind_of(previous_definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* previous_definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__18_161;
}
static void cont__18_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 266: ... kind_of(previous_definition) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_162;
}
static void cont__18_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 266: ... :
  // 267:   !info.types_of types_of(previous_definition)
  // 268:   !info.derived_types_of derived_types_of(previous_definition)
  // 269:   !info.methods_of methods_of(previous_definition)
  frame->slots[4] /* temp__3 */ = create_closure(entry__18_163, 0);
  // 266: if kind_of(previous_definition) == TYPE:
  // 267:   !info.types_of types_of(previous_definition)
  // 268:   !info.derived_types_of derived_types_of(previous_definition)
  // 269:   !info.methods_of methods_of(previous_definition)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__18_167(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 270: !definitions(iname) info
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[1])->contents /* info */;
  // 270: !definitions(iname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* iname */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_168;
}
static void cont__18_168(void) {
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
static void cont__18_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__3 */ = arguments->slots[0];
  // 271: ... :
  // 272:   $$attr attribute_of(destination)
  // 273:   
  // 274:   $type
  // 275:     default_value(definitions(iname) symbol_info)(.kind_of TYPE)
  // 276:   
  // 277:   !definitions(iname) type
  // 278:   if attr.is_defined:
  // 279:     $attr_name attr.to_string
  // 280:     unless local_method_names(attr_name):
  // ...
  frame->slots[13] /* temp__4 */ = create_closure(entry__18_170, 0);
  // 261: case
  // 262:   attribute_kind_of(destination)
  // 263:   NONE:
  // 264:     $previous_definition definitions(iname)
  // 265:     if previous_definition.is_defined:
  // 266:       if kind_of(previous_definition) == TYPE:
  // 267:         !info.types_of types_of(previous_definition)
  // 268:         !info.derived_types_of derived_types_of(previous_definition)
  // 269:         !info.methods_of methods_of(previous_definition)
  // 270:     !definitions(iname) info
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
static void entry__18_116(void) {
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
  // 227: $identifier identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_117;
}
static void cont__18_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* identifier */, arguments->slots[0]);
  // 228: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__18_118;
}
static void cont__18_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* namespace */, arguments->slots[0]);
  // 229: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_119;
}
static void cont__18_119(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 229: ... :
  // 230:   $name name_of(identifier)
  // 231:   $iname ordered_name(namespace name)
  // 232:   !info.name_of identifier.to_string
  // 233:   $source arguments_of(statement)(1)
  // 234:   cond
  // 235:     -> source.is_a_polymorphic_function_constant:
  // 236:       !polymorphic_functions(name namespace) true
  // 237:       !definitions(iname)
  // 238:         info
  // ...
  frame->slots[8] /* temp__2 */ = create_closure(entry__18_120, 0);
  // 229: if namespace.is_defined:
  // 230:   $name name_of(identifier)
  // 231:   $iname ordered_name(namespace name)
  // 232:   !info.name_of identifier.to_string
  // 233:   $source arguments_of(statement)(1)
  // 234:   cond
  // 235:     -> source.is_a_polymorphic_function_constant:
  // 236:       !polymorphic_functions(name namespace) true
  // 237:       !definitions(iname)
  // 238:         info
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
static void entry__18_112(void) {
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
  // 224: ... output_arguments_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__18_113;
}
static void cont__18_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 224: ... output_arguments_of(statement)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[7] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__18_114;
}
static void cont__18_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 224: $destination output_arguments_of(statement)(1)(.base_of undefined)
  {
    NODE *temp = clone_object_and_attributes(frame->slots[6] /* temp__1 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, get__undefined());
    initialize_future(frame->slots[4] /* destination */, temp);

  }
  // 225: $$info symbol_info(.filename_of filename)
  {
    NODE *temp = clone_object_and_attributes(var._symbol_info);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__filename_of, frame->slots[1] /* filename */);
    ((CELL *)frame->slots[5])->contents /* info */ = temp;

  }
  // 226: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__18_115;
}
static void cont__18_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 226: ... :
  // 227:   $identifier identifier_of(destination)
  // 228:   $namespace namespace_of(identifier)
  // 229:   if namespace.is_defined:
  // 230:     $name name_of(identifier)
  // 231:     $iname ordered_name(namespace name)
  // 232:     !info.name_of identifier.to_string
  // 233:     $source arguments_of(statement)(1)
  // 234:     cond
  // 235:       -> source.is_a_polymorphic_function_constant:
  // ...
  frame->slots[7] /* temp__2 */ = create_closure(entry__18_116, 0);
  // 226: if destination.is_a_definition:
  // 227:   $identifier identifier_of(destination)
  // 228:   $namespace namespace_of(identifier)
  // 229:   if namespace.is_defined:
  // 230:     $name name_of(identifier)
  // 231:     $iname ordered_name(namespace name)
  // 232:     !info.name_of identifier.to_string
  // 233:     $source arguments_of(statement)(1)
  // 234:     cond
  // 235:       -> source.is_a_polymorphic_function_constant:
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
static void entry__18_98(void) {
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
  // 214: $name name_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__18_99;
}
static void cont__18_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 215: $base base_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__18_100;
}
static void cont__18_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* base */, arguments->slots[0]);
  // 219: ... identifier.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__18_101;
}
static void cont__18_101(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__1 */ = arguments->slots[0];
  // 220: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_102;
}
static void cont__18_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__3 */ = arguments->slots[0];
  // 220: ... -> base.to_string
  frame->slots[9] /* temp__4 */ = create_closure(entry__18_103, 0);
  // 220: ... if(base.is_defined (-> base.to_string) -> undefined)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__3 */;
  arguments->slots[1] = frame->slots[9] /* temp__4 */;
  arguments->slots[2] = func__18_105;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_106;
}
static void entry__18_103(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // base: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* base */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: ... base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__18_104;
}
static void cont__18_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 220: ... -> base.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_105(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 220: ... -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__2 */ = arguments->slots[0];
  // 221: ... remark_lines_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* statement */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__18_107;
}
static void cont__18_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__5 */ = arguments->slots[0];
  // 216: !definitions(ordered_name(namespace name))
  // 217:   symbol_info
  // 218:     .kind_of TYPE
  // 219:     .name_of identifier.to_string
  // 220:     .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 221:     .remark_lines_of remark_lines_of(statement)
  // 222:     .filename_of filename
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
  // 216: ... ordered_name(namespace name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* namespace */;
  arguments->slots[1] = frame->slots[4] /* name */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__18_108;
}
static void cont__18_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__7 */ = arguments->slots[0];
  // 216: !definitions(ordered_name(namespace name))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__7 */;
  arguments->slots[1] = frame->slots[11] /* temp__6 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__18_109;
}
static void cont__18_109(void) {
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
static void entry__18_94(void) {
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
  // 211: $identifier identifier_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_95;
}
static void cont__18_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* identifier */, arguments->slots[0]);
  // 212: $namespace namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__18_96;
}
static void cont__18_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* namespace */, arguments->slots[0]);
  // 213: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_97;
}
static void cont__18_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 213: ... :
  // 214:   $name name_of(identifier)
  // 215:   $base base_of(statement)
  // 216:   !definitions(ordered_name(namespace name))
  // 217:     symbol_info
  // 218:       .kind_of TYPE
  // 219:       .name_of identifier.to_string
  // 220:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 221:       .remark_lines_of remark_lines_of(statement)
  // 222:       .filename_of filename
  frame->slots[5] /* temp__2 */ = create_closure(entry__18_98, 0);
  // 213: if namespace.is_defined:
  // 214:   $name name_of(identifier)
  // 215:   $base base_of(statement)
  // 216:   !definitions(ordered_name(namespace name))
  // 217:     symbol_info
  // 218:       .kind_of TYPE
  // 219:       .name_of identifier.to_string
  // 220:       .base_of if(base.is_defined (-> base.to_string) -> undefined)
  // 221:       .remark_lines_of remark_lines_of(statement)
  // 222:       .filename_of filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_90(void) {
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
  // 210: ... kind_of(statement)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__18_91;
}
static void cont__18_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 210: ... kind_of(statement) == "type"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = string__18_92;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__18_93;
}
static void cont__18_93(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 210: ... :
  // 211:   $identifier identifier_of(statement)
  // 212:   $namespace namespace_of(identifier)
  // 213:   if namespace.is_defined:
  // 214:     $name name_of(identifier)
  // 215:     $base base_of(statement)
  // 216:     !definitions(ordered_name(namespace name))
  // 217:       symbol_info
  // 218:         .kind_of TYPE
  // 219:         .name_of identifier.to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__18_94, 0);
  // 210: if kind_of(statement) == "type":
  // 211:   $identifier identifier_of(statement)
  // 212:   $namespace namespace_of(identifier)
  // 213:   if namespace.is_defined:
  // 214:     $name name_of(identifier)
  // 215:     $base base_of(statement)
  // 216:     !definitions(ordered_name(namespace name))
  // 217:       symbol_info
  // 218:         .kind_of TYPE
  // 219:         .name_of identifier.to_string
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
static void entry__18_87(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: ... pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__18_85(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // statement: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* statement */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 208: ... statement.is_a_remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_a_remark();
  func = myself->type;
  frame->cont = cont__18_86;
}
static void cont__18_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 208: -> statement.is_a_remark: pass
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__18_87;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_88(void) {
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
  // 209: ... statement.is_c_code
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_c_code();
  func = myself->type;
  frame->cont = cont__18_89;
}
static void cont__18_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 209: ... :
  // 210:   if kind_of(statement) == "type":
  // 211:     $identifier identifier_of(statement)
  // 212:     $namespace namespace_of(identifier)
  // 213:     if namespace.is_defined:
  // 214:       $name name_of(identifier)
  // 215:       $base base_of(statement)
  // 216:       !definitions(ordered_name(namespace name))
  // 217:         symbol_info
  // 218:           .kind_of TYPE
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__18_90, 0);
  // 209: -> statement.is_c_code:
  // 210:   if kind_of(statement) == "type":
  // 211:     $identifier identifier_of(statement)
  // 212:     $namespace namespace_of(identifier)
  // 213:     if namespace.is_defined:
  // 214:       $name name_of(identifier)
  // 215:       $base base_of(statement)
  // 216:       !definitions(ordered_name(namespace name))
  // 217:         symbol_info
  // 218:           .kind_of TYPE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_110(void) {
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
  // 223: ... statement.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* statement */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__18_111;
}
static void cont__18_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 223: ... :
  // 224:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 225:   $$info symbol_info(.filename_of filename)
  // 226:   if destination.is_a_definition:
  // 227:     $identifier identifier_of(destination)
  // 228:     $namespace namespace_of(identifier)
  // 229:     if namespace.is_defined:
  // 230:       $name name_of(identifier)
  // 231:       $iname ordered_name(namespace name)
  // 232:       !info.name_of identifier.to_string
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__18_112, 0);
  // 223: -> statement.is_an_assignment:
  // 224:   $destination output_arguments_of(statement)(1)(.base_of undefined)
  // 225:   $$info symbol_info(.filename_of filename)
  // 226:   if destination.is_a_definition:
  // 227:     $identifier identifier_of(destination)
  // 228:     $namespace namespace_of(identifier)
  // 229:     if namespace.is_defined:
  // 230:       $name name_of(identifier)
  // 231:       $iname ordered_name(namespace name)
  // 232:       !info.name_of identifier.to_string
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_189(void) {
  myself = frame->slots[1] /* break */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__18_190(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void entry__19_11(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 293: ... extract_documentation_from_file name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_file;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 292: ... extract_documentation_from_directory name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_6(void) {
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
  // 292: ... entry.is_a_directory
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__is_a_directory();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 292: ... : extract_documentation_from_directory name
  frame->slots[3] /* temp__2 */ = create_closure(entry__19_8, 0);
  // 292: -> entry.is_a_directory: extract_documentation_from_directory name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 293: ... name .has_suffix. ".sim"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__18_26;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__19_10;
}
static void cont__19_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 293: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__19_11, 0);
  // 293: -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // entry: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 290: $name fullname_of(entry)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* entry */;
  result_count = 1;
  myself = get__fullname_of();
  func = myself->type;
  frame->cont = cont__19_5;
}
static void cont__19_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 292: -> entry.is_a_directory: extract_documentation_from_directory name
  frame->slots[2] /* temp__1 */ = create_closure(entry__19_6, 0);
  // 293: -> name .has_suffix. ".sim": extract_documentation_from_file name
  frame->slots[3] /* temp__2 */ = create_closure(entry__19_9, 0);
  // 291: cond
  // 292:   -> entry.is_a_directory: extract_documentation_from_directory name
  // 293:   -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 289: ... --SORT
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__SORT();
  arguments->slots[1] = get__std__true();
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__19_2;
}
static void cont__19_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 289: ... directory(--SORT path)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[0] /* path */;
  result_count = 1;
  myself = get__directory();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 289: for_each directory(--SORT path): (entry)
  // 290:   $name fullname_of(entry)
  // 291:   cond
  // 292:     -> entry.is_a_directory: extract_documentation_from_directory name
  // 293:     -> name .has_suffix. ".sim": extract_documentation_from_file name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = func__19_4;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__20_5(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // attr: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* attr */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 297: ... attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__20_6;
}
static void cont__20_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 297: ... -> attr.to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_7(void) {
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
  // 298: $$resolved_namespace undefined
  ((CELL *)frame->slots[2])->contents /* resolved_namespace */ = get__undefined();
  // 299: ... used_namespaces_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = var._used_namespaces_of;
  func = myself->type;
  frame->cont = cont__20_8;
}
static void cont__20_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 299: ... : (namespace)
  // 300:   if polymorphic_functions(name namespace):
  // 301:     if resolved_namespace.is_defined:
  // 302:       Error "
  // 303:         The attribute "@(name)" cannot be uniquely resolved!
  // 304:     !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_9, 1);
  // 299: for_each used_namespaces_of(attr): (namespace)
  // 300:   if polymorphic_functions(name namespace):
  // 301:     if resolved_namespace.is_defined:
  // 302:       Error "
  // 303:         The attribute "@(name)" cannot be uniquely resolved!
  // 304:     !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__20_18;
}
static void entry__20_11(void) {
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
  // 301: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_12;
}
static void cont__20_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 301: ... :
  // 302:   Error "
  // 303:     The attribute "@(name)" cannot be uniquely resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_13, 0);
  // 301: if resolved_namespace.is_defined:
  // 302:   Error "
  // 303:     The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__20_17;
}
static void entry__20_13(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 302: ... "
  // 303:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__20_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__20_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__20_16;
}
static void cont__20_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 302: Error "
  // 303:   The attribute "@(name)" cannot be uniquely resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 304: !resolved_namespace namespace
  ((CELL *)frame->slots[0])->contents /* resolved_namespace */ = frame->slots[2] /* namespace */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_9(void) {
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
  // 300: ... polymorphic_functions(name namespace)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = var._polymorphic_functions;
  func = myself->type;
  frame->cont = cont__20_10;
}
static void cont__20_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 300: ... :
  // 301:   if resolved_namespace.is_defined:
  // 302:     Error "
  // 303:       The attribute "@(name)" cannot be uniquely resolved!
  // 304:   !resolved_namespace namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_11, 0);
  // 300: if polymorphic_functions(name namespace):
  // 301:   if resolved_namespace.is_defined:
  // 302:     Error "
  // 303:       The attribute "@(name)" cannot be uniquely resolved!
  // 304:   !resolved_namespace namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 305: ... resolved_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_19;
}
static void cont__20_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 305: ... :
  // 306:   Error "
  // 307:     The attribute "@(name)" cannot be resolved!
  frame->slots[4] /* temp__2 */ = create_closure(entry__20_20, 0);
  // 305: unless resolved_namespace.is_defined:
  // 306:   Error "
  // 307:     The attribute "@(name)" cannot be resolved!
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__20_23;
}
static void entry__20_20(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 306: ... "
  // 307:   The attribute "@(name)" cannot be resolved!
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__20_14;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__20_21;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__20_22;
}
static void cont__20_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 306: Error "
  // 307:   The attribute "@(name)" cannot be resolved!
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Error();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__20_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__20_24;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__20_25;
}
static void cont__20_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 308: -> string(resolved_namespace "::" name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__20_1(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // attr: 0
  // name: 1
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 296: $name name_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__20_2;
}
static void cont__20_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 297: ... namespace_of(attr)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* attr */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__20_3;
}
static void cont__20_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 297: ... namespace_of(attr).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__20_4;
}
static void cont__20_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 297: ... -> attr.to_string
  frame->slots[4] /* temp__3 */ = create_closure(entry__20_5, 0);
  // 297: ... :
  // 298:   $$resolved_namespace undefined
  // 299:   for_each used_namespaces_of(attr): (namespace)
  // 300:     if polymorphic_functions(name namespace):
  // 301:       if resolved_namespace.is_defined:
  // 302:         Error "
  // 303:           The attribute "@(name)" cannot be uniquely resolved!
  // 304:       !resolved_namespace namespace
  // 305:   unless resolved_namespace.is_defined:
  // 306:     Error "
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__20_7, 0);
  // 297: if namespace_of(attr).is_defined (-> attr.to_string):
  // 298:   $$resolved_namespace undefined
  // 299:   for_each used_namespaces_of(attr): (namespace)
  // 300:     if polymorphic_functions(name namespace):
  // 301:       if resolved_namespace.is_defined:
  // 302:         Error "
  // 303:           The attribute "@(name)" cannot be uniquely resolved!
  // 304:       !resolved_namespace namespace
  // 305:   unless resolved_namespace.is_defined:
  // 306:     Error "
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
static void entry__21_7(void) {
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
  // 314: !definition.derived_types_of(name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 314: ... definition.derived_types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__21_8;
}
static void cont__21_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 314: !definition.derived_types_of(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__21_9;
}
static void cont__21_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 314: !definition.derived_types_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__derived_types_of, frame->slots[4] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 315: ... kind_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__21_10;
}
static void cont__21_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 315: ... kind_of(definition) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__21_11;
}
static void cont__21_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   !definition.kind_of TYPE
  // 317:   $base_of_base base_of(definition)
  // 318:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_12, 0);
  // 315: unless kind_of(definition) == TYPE:
  // 316:   !definition.kind_of TYPE
  // 317:   $base_of_base base_of(definition)
  // 318:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__21_16;
}
static void entry__21_15(void) {
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
  // 318: ... add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base_of_base */;
  arguments->slots[1] = frame->slots[1] /* ibase */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__21_12(void) {
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
  // 316: !definition.kind_of TYPE
  frame->slots[3] /* temp__1 */ = var._TYPE;
  // 316: !definition.kind_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* definition */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__kind_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* definition */ = temp;

  }
  // 317: $base_of_base base_of(definition)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* definition */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__21_13;
}
static void cont__21_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base_of_base */, arguments->slots[0]);
  // 318: ... base_of_base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base_of_base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_14;
}
static void cont__21_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 318: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__21_15, 0);
  // 318: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__21_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 319: !definitions(ibase) definition
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[0])->contents /* definition */;
  // 319: !definitions(ibase)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__21_17;
}
static void cont__21_17(void) {
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
static void entry__21_1(void) {
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
  // 311: ... base .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__21_2;
}
static void cont__21_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 311: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__21_3;
}
static void cont__21_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 311: $ibase ordered_name(base .before. "::" base .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__21_4;
}
static void cont__21_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ibase */, arguments->slots[0]);
  // 312: $$definition definitions(ibase)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ibase */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[3])->contents /* definition */ = arguments->slots[0];
  // 313: ... definition.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* definition */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__21_6;
}
static void cont__21_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 313: ... :
  // 314:   !definition.derived_types_of(name) true
  // 315:   unless kind_of(definition) == TYPE:
  // 316:     !definition.kind_of TYPE
  // 317:     $base_of_base base_of(definition)
  // 318:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 319:   !definitions(ibase) definition
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_7, 0);
  // 313: if definition.is_defined:
  // 314:   !definition.derived_types_of(name) true
  // 315:   unless kind_of(definition) == TYPE:
  // 316:     !definition.kind_of TYPE
  // 317:     $base_of_base base_of(definition)
  // 318:     if base_of_base.is_defined: add_derived_type base_of_base ibase
  // 319:   !definitions(ibase) definition
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__22_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 321: ... "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__20_24;
  arguments->slots[1] = string__18_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__22_2;
}
static void cont__22_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 321: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__22_3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__22_4;
}
static void cont__22_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 321: ... replace_all(name "::" = "__" '/' = "___")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__22_5;
}
static void cont__22_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 321: ... -> replace_all(name "::" = "__" '/' = "___")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__23_1(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // name: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 326: name.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__23_2;
}
static void cont__23_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 328: namespace.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__23_3;
}
static void cont__23_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 325: string
  // 326:   name.to_lower_case
  // 327:   '/'
  // 328:   namespace.to_lower_case
  // 329:   '/'
  // 330:   name
  // 331:   '/'
  // 332:   namespace
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
  frame->cont = cont__23_4;
}
static void cont__23_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 324: ->
  // 325:   string
  // 326:     name.to_lower_case
  // 327:     '/'
  // 328:     namespace.to_lower_case
  // 329:     '/'
  // 330:     name
  // 331:     '/'
  // 332:     namespace
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__24_2(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 336: ... "href" = "index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_4;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_5;
}
static void cont__24_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 336: A "href" = "index.html" "Home"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_6;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_7;
}
static void cont__24_7(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_9;
}
static void cont__24_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 338: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_11;
}
static void cont__24_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 338: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_12;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_13;
}
static void cont__24_13(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 339: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_14;
}
static void cont__24_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 340: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void cont__24_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 340: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_17;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_18;
}
static void cont__24_18(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 341: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_19;
}
static void cont__24_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 342: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_21;
}
static void cont__24_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 342: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_22;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void cont__24_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 343: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_8;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_24;
}
static void cont__24_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 344: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_26;
}
static void cont__24_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 344: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__24_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 335: P:
  // 336:   A "href" = "index.html" "Home"
  // 337:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 338:   A "href" = "manual.html" "Manual"
  // 339:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 340:   A "href" = "type_index.html" "Type Index"
  // 341:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 342:   A "href" = "symbol_index.html" "Symbol Index"
  // 343:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 344:   A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__24_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__25_1(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 348: reference .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_2;
}
static void cont__25_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 348: ... :
  // 349:   $$type_name reference .before. '/'
  // 350:   $$method_name reference .behind. '/'
  // 351:   unless type_name .contains. "::": append "types::" &type_name
  // 352:   unless method_name .contains. "::": append "std::" &method_name
  // 353:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 354: :
  // 355:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__25_17, 0);
  // 347: if
  // 348:   reference .contains. '/':
  // 349:     $$type_name reference .before. '/'
  // 350:     $$method_name reference .behind. '/'
  // 351:     unless type_name .contains. "::": append "types::" &type_name
  // 352:     unless method_name .contains. "::": append "std::" &method_name
  // 353:     !reference string(type_name '/' method_name)
  // 354:   :
  // 355:     unless reference .contains. "::": append "std::" &reference
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
  frame->cont = cont__25_21;
}
static void entry__25_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_20;
}
static void cont__25_20(void) {
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
static void entry__25_3(void) {
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
  // 349: $$type_name reference .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__25_4;
}
static void cont__25_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* type_name */ = arguments->slots[0];
  // 350: $$method_name reference .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__25_5;
}
static void cont__25_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* method_name */ = arguments->slots[0];
  // 351: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_6;
}
static void cont__25_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 351: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_7, 0);
  // 351: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void entry__25_7(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 351: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_8;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_9;
}
static void cont__25_9(void) {
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
static void cont__25_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 352: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void cont__25_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 352: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_12, 0);
  // 352: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_15;
}
static void entry__25_12(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 352: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_13;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_14;
}
static void cont__25_14(void) {
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
static void cont__25_15(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 353: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__25_16;
}
static void cont__25_16(void) {
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
static void entry__25_17(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 355: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_18;
}
static void cont__25_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 355: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_19, 0);
  // 355: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__25_21(void) {
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
static void entry__28_1(void) {
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
  // 361: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 362: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 363: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 364: ... : (line)
  // 365:   if
  // 366:     pre_mode:
  // 367:       if
  // 368:         line .has_prefix. EXAMPLE:
  // 369:           trim &text
  // 370:           push &paragraphs text
  // 371:           !text line
  // 372:         :
  // 373:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__28_2, 1);
  // 364: for_each lines: (line)
  // 365:   if
  // 366:     pre_mode:
  // 367:       if
  // 368:         line .has_prefix. EXAMPLE:
  // 369:           trim &text
  // 370:           push &paragraphs text
  // 371:           !text line
  // 372:         :
  // 373:           writeln_to &text line
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* lines */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__28_27;
}
static void entry__28_15(void) {
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
  // 378: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_16;
}
static void cont__28_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraphs */ = arguments->slots[0];
  // 379: !text ""
  ((CELL *)frame->slots[1])->contents /* text */ = empty_string;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_12(void) {
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
  // 377: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_13;
}
static void cont__28_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 377: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__28_14;
}
static void cont__28_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 377: ... :
  // 378:   push &paragraphs text
  // 379:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__28_15, 0);
  // 377: if text != "":
  // 378:   push &paragraphs text
  // 379:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_17(void) {
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
  // 382: text == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_18;
}
static void cont__28_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 382: ... :
  // 383:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__28_19, 0);
  // 384: :
  // 385:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_22, 0);
  // 381: if
  // 382:   text == "":
  // 383:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 384:   :
  // 385:     push &text ' '
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_24;
}
static void entry__28_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // pre_mode: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* pre_mode */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 383: ... !pre_mode true
  ((CELL *)frame->slots[0])->contents /* pre_mode */ = get__true();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_19(void) {
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
  // 383: ... line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__28_20;
}
static void cont__28_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 383: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__28_21, 0);
  // 383: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__28_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 385: push &text ' '
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = character__32;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_23;
}
static void cont__28_23(void) {
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
static void cont__28_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 386: ... line.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__28_25;
}
static void cont__28_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 386: append &text line.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__28_26;
}
static void cont__28_26(void) {
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
static void entry__28_5(void) {
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
  // 369: trim &text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__28_6;
}
static void cont__28_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* text */ = arguments->slots[0];
  // 370: push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_7;
}
static void cont__28_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = arguments->slots[0];
  // 371: !text line
  ((CELL *)frame->slots[0])->contents /* text */ = frame->slots[2] /* line */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__28_8(void) {
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
  // 373: writeln_to &text line
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* line */;
  result_count = 1;
  myself = get__writeln_to();
  func = myself->type;
  frame->cont = cont__28_9;
}
static void cont__28_9(void) {
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
static void entry__28_3(void) {
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
  // 368: line .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__28_4;
}
static void cont__28_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 368: ... :
  // 369:   trim &text
  // 370:   push &paragraphs text
  // 371:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__28_5, 0);
  // 372: :
  // 373:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_8, 0);
  // 367: if
  // 368:   line .has_prefix. EXAMPLE:
  // 369:     trim &text
  // 370:     push &paragraphs text
  // 371:     !text line
  // 372:   :
  // 373:     writeln_to &text line
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
static void entry__28_10(void) {
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
  // 376: line == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* line */;
  arguments->slots[1] = empty_string;
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
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 376: ... :
  // 377:   if text != "":
  // 378:     push &paragraphs text
  // 379:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_12, 0);
  // 380: :
  // 381:   if
  // 382:     text == "":
  // 383:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 384:     :
  // 385:       push &text ' '
  // 386:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_17, 0);
  // 375: if
  // 376:   line == "":
  // 377:     if text != "":
  // 378:       push &paragraphs text
  // 379:       !text ""
  // 380:   :
  // 381:     if
  // 382:       text == "":
  // 383:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 384:       :
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
static void entry__28_2(void) {
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
  // 366: ... :
  // 367:   if
  // 368:     line .has_prefix. EXAMPLE:
  // 369:       trim &text
  // 370:       push &paragraphs text
  // 371:       !text line
  // 372:     :
  // 373:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__28_3, 0);
  // 374: :
  // 375:   if
  // 376:     line == "":
  // 377:       if text != "":
  // 378:         push &paragraphs text
  // 379:         !text ""
  // 380:     :
  // 381:       if
  // 382:         text == "":
  // 383:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_10, 0);
  // 365: if
  // 366:   pre_mode:
  // 367:     if
  // 368:       line .has_prefix. EXAMPLE:
  // 369:         trim &text
  // 370:         push &paragraphs text
  // 371:         !text line
  // 372:       :
  // 373:         writeln_to &text line
  // 374:   :
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
static void cont__28_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 387: ... text != ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* text */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__28_28;
}
static void cont__28_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 387: ... text != ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__28_29;
}
static void cont__28_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 387: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_30, 0);
  // 387: if text != "": push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__28_32;
}
static void entry__28_30(void) {
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
  // 387: ... push &paragraphs text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraphs */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* text */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__28_31;
}
static void cont__28_31(void) {
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
static void cont__28_32(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 388: -> paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* paragraphs */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_8(void) {
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
  // 393: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__29_9;
}
static void cont__29_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 395: function_name .contains. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_10;
}
static void cont__29_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 395: ... :
  // 396:   $type function_name .before. '/'
  // 397:   $method function_name .behind. '/'
  // 398:   H1
  // 399:     string
  // 400:       '['
  // 401:       type
  // 402:       "]("
  // 403:       type.mangled
  // 404:       ".html)/["
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_11, 0);
  // 409: :
  // 410:   H1 function_name
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_20, 0);
  // 394: if
  // 395:   function_name .contains. '/':
  // 396:     $type function_name .before. '/'
  // 397:     $method function_name .behind. '/'
  // 398:     H1
  // 399:       string
  // 400:         '['
  // 401:         type
  // 402:         "]("
  // 403:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_21;
}
static void entry__29_11(void) {
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
  // 396: $type function_name .before. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_12;
}
static void cont__29_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* type */, arguments->slots[0]);
  // 397: $method function_name .behind. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_13;
}
static void cont__29_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 403: type.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* type */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_14;
}
static void cont__29_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 407: method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_15;
}
static void cont__29_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 399: string
  // 400:   '['
  // 401:   type
  // 402:   "]("
  // 403:   type.mangled
  // 404:   ".html)/["
  // 405:   method
  // 406:   "]("
  // 407:   method.mangled
  // 408:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__29_16;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__29_17;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__29_16;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__29_18;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_19;
}
static void cont__29_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 398: H1
  // 399:   string
  // 400:     '['
  // 401:     type
  // 402:     "]("
  // 403:     type.mangled
  // 404:     ".html)/["
  // 405:     method
  // 406:     "]("
  // 407:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // function_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 410: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 411: $$short_description undefined
  ((CELL *)frame->slots[2])->contents /* short_description */ = get__undefined();
  // 412: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 413: $$return_values empty_list
  ((CELL *)frame->slots[4])->contents /* return_values */ = get__empty_list();
  // 414: $$descriptions empty_list
  ((CELL *)frame->slots[5])->contents /* descriptions */ = get__empty_list();
  // 415: $$technical_details undefined
  ((CELL *)frame->slots[6])->contents /* technical_details */ = get__undefined();
  // 416: $$references empty_list
  ((CELL *)frame->slots[7])->contents /* references */ = get__empty_list();
  // 417: $$examples empty_list
  ((CELL *)frame->slots[8])->contents /* examples */ = get__empty_list();
  // 418: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_22;
}
static void cont__29_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* remark_lines */, arguments->slots[0]);
  // 419: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_23;
}
static void cont__29_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 419: ... :
  // 420:   $paragraphs remark_lines.to_paragraphs
  // 421:   for_each paragraphs: ($paragraph)
  // 422:     cond
  // 423:       ->
  // 424:         has_prefix
  // 425:           paragraph
  // 426:           sequence
  // 427:             "Parameter"
  // 428:             sim2c::WHITESPACE
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_24, 0);
  // 419: if remark_lines.is_defined:
  // 420:   $paragraphs remark_lines.to_paragraphs
  // 421:   for_each paragraphs: ($paragraph)
  // 422:     cond
  // 423:       ->
  // 424:         has_prefix
  // 425:           paragraph
  // 426:           sequence
  // 427:             "Parameter"
  // 428:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_147;
}
static void entry__29_142(void) {
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
  // 506: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_143;
}
static void cont__29_143(void) {
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
static void entry__29_144(void) {
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
  // 508: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_145;
}
static void cont__29_145(void) {
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
static void entry__29_140(void) {
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
  // 505: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_141;
}
static void cont__29_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 505: ... :
  // 506:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_142, 0);
  // 507: :
  // 508:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_144, 0);
  // 504: if
  // 505:   technical_details.is_defined:
  // 506:     push &technical_details paragraph
  // 507:   :
  // 508:     push &descriptions paragraph
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
static void entry__29_146(void) {
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
  // 510: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_123(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 490: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_124(void) {
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
  // 492: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__29_125;
}
static void cont__29_125(void) {
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
static void entry__29_119(void) {
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
  // 487: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_120;
}
static void cont__29_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 487: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_121;
}
static void cont__29_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 489: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_122;
}
static void cont__29_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 489: ... :
  // 490:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_123, 0);
  // 491: :
  // 492:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_124, 0);
  // 488: if
  // 489:   detail == "":
  // 490:     !technical_details empty_list
  // 491:   :
  // 492:     !technical_details list(detail)
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
static void entry__29_109(void) {
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
  // 483: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_110;
}
static void cont__29_110(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 483: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_111;
}
static void cont__29_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 484: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_112;
}
static void cont__29_112(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 484: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_113;
}
static void cont__29_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 485: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_114;
}
static void cont__29_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 485: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_115;
}
static void cont__29_115(void) {
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
static void entry__29_101(void) {
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
  // 475: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_102;
}
static void cont__29_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 478: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__29_103;
}
static void cont__29_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 477: $$topic_contents
  // 478:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__29_104;
}
static void cont__29_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 480: !topic_contents(function_name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 480: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__29_105;
}
static void cont__29_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 481: !topics(topic) topic_contents
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  // 481: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__29_106;
}
static void cont__29_106(void) {
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
static void entry__29_98(void) {
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
  // 474: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_99;
}
static void cont__29_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 474: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__29_100;
}
static void cont__29_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 474: ... : ($topic)
  // 475:   trim &topic
  // 476:   
  // 477:   $$topic_contents
  // 478:     default_value(topics(topic) empty_key_order_set)
  // 479:   
  // 480:   !topic_contents(function_name) true
  // 481:   !topics(topic) topic_contents
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_101, 1);
  // 474: for_each split(paragraph .behind. ':' ','): ($topic)
  // 475:   trim &topic
  // 476:   
  // 477:   $$topic_contents
  // 478:     default_value(topics(topic) empty_key_order_set)
  // 479:   
  // 480:   !topic_contents(function_name) true
  // 481:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_93(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 472: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_94;
}
static void cont__29_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 472: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_95;
}
static void cont__29_95(void) {
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
static void entry__29_90(void) {
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
  // 471: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_91;
}
static void cont__29_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 471: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__29_92;
}
static void cont__29_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 471: ... : (reference)
  // 472:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_93, 1);
  // 471: for_each split(paragraph .behind. ':' ','): (reference)
  // 472:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_68(void) {
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
  // 459: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__29_69;
}
static void cont__29_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 461: -> return_value .has_suffix. '?':
  // 462:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_70, 0);
  // 463: -> return_value .has_suffix. '*':
  // 464:   !return_value
  // 465:     string
  // 466:       range(return_value 1 -2)
  // 467:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_76, 0);
  // 460: cond
  // 461:   -> return_value .has_suffix. '?':
  // 462:     !return_value string(range(return_value 1 -2) " (optional)")
  // 463:   -> return_value .has_suffix. '*':
  // 464:     !return_value
  // 465:       string
  // 466:         range(return_value 1 -2)
  // 467:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_82;
}
static void entry__29_78(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 466: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_79;
}
static void cont__29_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 466: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_80;
}
static void cont__29_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 464: !return_value
  // 465:   string
  // 466:     range(return_value 1 -2)
  // 467:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_46;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_81;
}
static void cont__29_81(void) {
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
static void entry__29_72(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 462: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_73;
}
static void cont__29_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 462: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_74;
}
static void cont__29_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 462: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_39;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_75;
}
static void cont__29_75(void) {
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
static void entry__29_70(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 461: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_71;
}
static void cont__29_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 461: ... :
  // 462:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_72, 0);
  // 461: -> return_value .has_suffix. '?':
  // 462:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_76(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 463: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_77;
}
static void cont__29_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 463: ... :
  // 464:   !return_value
  // 465:     string
  // 466:       range(return_value 1 -2)
  // 467:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_78, 0);
  // 463: -> return_value .has_suffix. '*':
  // 464:   !return_value
  // 465:     string
  // 466:       range(return_value 1 -2)
  // 467:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_82(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 468: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_83;
}
static void cont__29_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 468: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_84;
}
static void cont__29_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 469: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_85;
}
static void cont__29_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 469: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_86;
}
static void cont__29_86(void) {
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
static void entry__29_32(void) {
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
  // 433: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__29_33;
}
static void cont__29_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 435: -> parameter .has_suffix. '?':
  // 436:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_34, 0);
  // 437: -> parameter .has_suffix. '*':
  // 438:   !parameter
  // 439:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_41, 0);
  // 440: -> parameter .contains. '=':
  // 441:   !parameter
  // 442:     string
  // 443:       (parameter .before. '=').trim
  // 444:       " (optional; default value: "
  // 445:       (parameter .behind. '=').trim
  // 446:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__29_48, 0);
  // 434: cond
  // 435:   -> parameter .has_suffix. '?':
  // 436:     !parameter string(range(parameter 1 -2) " (optional)")
  // 437:   -> parameter .has_suffix. '*':
  // 438:     !parameter
  // 439:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 440:   -> parameter .contains. '=':
  // 441:     !parameter
  // 442:       string
  // 443:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_58;
}
static void entry__29_50(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 443: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_51;
}
static void cont__29_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 443: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_52;
}
static void cont__29_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 445: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_53;
}
static void cont__29_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 445: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_54;
}
static void cont__29_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 441: !parameter
  // 442:   string
  // 443:     (parameter .before. '=').trim
  // 444:     " (optional; default value: "
  // 445:     (parameter .behind. '=').trim
  // 446:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_55;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__29_56;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_57;
}
static void cont__29_57(void) {
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
static void entry__29_43(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 439: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_44;
}
static void cont__29_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 439: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_45;
}
static void cont__29_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 438: !parameter
  // 439:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_46;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_47;
}
static void cont__29_47(void) {
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
static void entry__29_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_37;
}
static void cont__29_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 436: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_38;
}
static void cont__29_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 436: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_39;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_40;
}
static void cont__29_40(void) {
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
static void entry__29_34(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 435: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_35;
}
static void cont__29_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 435: ... :
  // 436:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_36, 0);
  // 435: -> parameter .has_suffix. '?':
  // 436:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_41(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 437: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_42;
}
static void cont__29_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 437: ... :
  // 438:   !parameter
  // 439:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_43, 0);
  // 437: -> parameter .has_suffix. '*':
  // 438:   !parameter
  // 439:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_48(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 440: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_49;
}
static void cont__29_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 440: ... :
  // 441:   !parameter
  // 442:     string
  // 443:       (parameter .before. '=').trim
  // 444:       " (optional; default value: "
  // 445:       (parameter .behind. '=').trim
  // 446:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_50, 0);
  // 440: -> parameter .contains. '=':
  // 441:   !parameter
  // 442:     string
  // 443:       (parameter .before. '=').trim
  // 444:       " (optional; default value: "
  // 445:       (parameter .behind. '=').trim
  // 446:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 447: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_59;
}
static void cont__29_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 447: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_60;
}
static void cont__29_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 448: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_61;
}
static void cont__29_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 448: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_62;
}
static void cont__29_62(void) {
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
static void entry__29_27(void) {
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
  // 430: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_28;
}
static void cont__29_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 426: sequence
  // 427:   "Parameter"
  // 428:   sim2c::WHITESPACE
  // 429:   NAME
  // 430:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 431:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_29;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_30;
}
static void cont__29_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 424: has_prefix
  // 425:   paragraph
  // 426:   sequence
  // 427:     "Parameter"
  // 428:     sim2c::WHITESPACE
  // 429:     NAME
  // 430:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 431:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_31;
}
static void cont__29_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 432: :
  // 433:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 434:   cond
  // 435:     -> parameter .has_suffix. '?':
  // 436:       !parameter string(range(parameter 1 -2) " (optional)")
  // 437:     -> parameter .has_suffix. '*':
  // 438:       !parameter
  // 439:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 440:     -> parameter .contains. '=':
  // 441:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_32, 0);
  // 423: ->
  // 424:   has_prefix
  // 425:     paragraph
  // 426:     sequence
  // 427:       "Parameter"
  // 428:       sim2c::WHITESPACE
  // 429:       NAME
  // 430:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 431:       ':'
  // 432:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_63(void) {
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
  // 456: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_64;
}
static void cont__29_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 452: sequence
  // 453:   "Returns"
  // 454:   sim2c::WHITESPACE
  // 455:   NAME
  // 456:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 457:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_65;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_66;
}
static void cont__29_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 450: has_prefix
  // 451:   paragraph
  // 452:   sequence
  // 453:     "Returns"
  // 454:     sim2c::WHITESPACE
  // 455:     NAME
  // 456:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 457:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_67;
}
static void cont__29_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 458: :
  // 459:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 460:   cond
  // 461:     -> return_value .has_suffix. '?':
  // 462:       !return_value string(range(return_value 1 -2) " (optional)")
  // 463:     -> return_value .has_suffix. '*':
  // 464:       !return_value
  // 465:         string
  // 466:           range(return_value 1 -2)
  // 467:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_68, 0);
  // 449: ->
  // 450:   has_prefix
  // 451:     paragraph
  // 452:     sequence
  // 453:       "Returns"
  // 454:       sim2c::WHITESPACE
  // 455:       NAME
  // 456:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 457:       ':'
  // 458:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_87(void) {
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
  // 470: ... paragraph .has_prefix. "See Also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__29_88;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_89;
}
static void cont__29_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 470: ... :
  // 471:   for_each split(paragraph .behind. ':' ','): (reference)
  // 472:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_90, 0);
  // 470: -> paragraph .has_prefix. "See Also:":
  // 471:   for_each split(paragraph .behind. ':' ','): (reference)
  // 472:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_96(void) {
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
  // 473: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_97;
}
static void cont__29_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 473: ... :
  // 474:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 475:     trim &topic
  // 476:     
  // 477:     $$topic_contents
  // 478:       default_value(topics(topic) empty_key_order_set)
  // 479:     
  // 480:     !topic_contents(function_name) true
  // 481:     !topics(topic) topic_contents
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_98, 0);
  // 473: -> paragraph .has_prefix. TOPIC:
  // 474:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 475:     trim &topic
  // 476:     
  // 477:     $$topic_contents
  // 478:       default_value(topics(topic) empty_key_order_set)
  // 479:     
  // 480:     !topic_contents(function_name) true
  // 481:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_107(void) {
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
  // 482: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_108;
}
static void cont__29_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 482: ... :
  // 483:   $title (paragraph .before. ':').trim
  // 484:   $text (paragraph .behind. ':').trim
  // 485:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_109, 0);
  // 482: -> paragraph .has_prefix. EXAMPLE:
  // 483:   $title (paragraph .before. ':').trim
  // 484:   $text (paragraph .behind. ':').trim
  // 485:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_116(void) {
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
  // 486: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__29_117;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_118;
}
static void cont__29_118(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 486: ... :
  // 487:   $detail (paragraph .behind. ':').trim
  // 488:   if
  // 489:     detail == "":
  // 490:       !technical_details empty_list
  // 491:     :
  // 492:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_119, 0);
  // 486: -> paragraph .has_prefix. "Technical Details:":
  // 487:   $detail (paragraph .behind. ':').trim
  // 488:   if
  // 489:     detail == "":
  // 490:       !technical_details empty_list
  // 491:     :
  // 492:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_126(void) {
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
  // 497: ... '/', NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_127;
}
static void cont__29_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 497: ... optional('/', NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_128;
}
static void cont__29_128(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 497: '<', NAME, optional('/', NAME), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_129;
}
static void cont__29_129(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 496: =
  // 497:   '<', NAME, optional('/', NAME), '>'
  // 498:   : ($reference)
  // 499:     range &reference 2 -2
  // 500:     resolve_reference &reference
  // 501:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = func__29_130;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_137;
}
static void entry__29_130(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 499: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_131;
}
static void cont__29_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 499: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_132;
}
static void cont__29_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 500: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__29_133;
}
static void cont__29_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 501: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_134;
}
static void cont__29_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 501: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_135;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__29_16;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__29_18;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_136;
}
static void cont__29_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 501: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 494: replace_all
  // 495:   &paragraph
  // 496:   =
  // 497:     '<', NAME, optional('/', NAME), '>'
  // 498:     : ($reference)
  // 499:       range &reference 2 -2
  // 500:       resolve_reference &reference
  // 501:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__29_138;
}
static void cont__29_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 503: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_139;
}
static void cont__29_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 503: ... :
  // 504:   if
  // 505:     technical_details.is_defined:
  // 506:       push &technical_details paragraph
  // 507:     :
  // 508:       push &descriptions paragraph
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_140, 0);
  // 509: :
  // 510:   !short_description paragraph
  frame->slots[6] /* temp__3 */ = create_closure(entry__29_146, 0);
  // 502: if
  // 503:   short_description.is_defined:
  // 504:     if
  // 505:       technical_details.is_defined:
  // 506:         push &technical_details paragraph
  // 507:       :
  // 508:         push &descriptions paragraph
  // 509:   :
  // 510:     !short_description paragraph
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
static void entry__29_26(void) {
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
  // 423: ->
  // 424:   has_prefix
  // 425:     paragraph
  // 426:     sequence
  // 427:       "Parameter"
  // 428:       sim2c::WHITESPACE
  // 429:       NAME
  // 430:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 431:       ':'
  // 432:   :
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__29_27, 0);
  // 449: ->
  // 450:   has_prefix
  // 451:     paragraph
  // 452:     sequence
  // 453:       "Returns"
  // 454:       sim2c::WHITESPACE
  // 455:       NAME
  // 456:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 457:       ':'
  // 458:   :
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__29_63, 0);
  // 470: -> paragraph .has_prefix. "See Also:":
  // 471:   for_each split(paragraph .behind. ':' ','): (reference)
  // 472:     push &references reference.trim
  frame->slots[11] /* temp__3 */ = create_closure(entry__29_87, 0);
  // 473: -> paragraph .has_prefix. TOPIC:
  // 474:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 475:     trim &topic
  // 476:     
  // 477:     $$topic_contents
  // 478:       default_value(topics(topic) empty_key_order_set)
  // 479:     
  // 480:     !topic_contents(function_name) true
  // 481:     !topics(topic) topic_contents
  frame->slots[12] /* temp__4 */ = create_closure(entry__29_96, 0);
  // 482: -> paragraph .has_prefix. EXAMPLE:
  // 483:   $title (paragraph .before. ':').trim
  // 484:   $text (paragraph .behind. ':').trim
  // 485:   push &examples title = text
  frame->slots[13] /* temp__5 */ = create_closure(entry__29_107, 0);
  // 486: -> paragraph .has_prefix. "Technical Details:":
  // 487:   $detail (paragraph .behind. ':').trim
  // 488:   if
  // 489:     detail == "":
  // 490:       !technical_details empty_list
  // 491:     :
  // 492:       !technical_details list(detail)
  frame->slots[14] /* temp__6 */ = create_closure(entry__29_116, 0);
  // 493: :
  // 494:   replace_all
  // 495:     &paragraph
  // 496:     =
  // 497:       '<', NAME, optional('/', NAME), '>'
  // 498:       : ($reference)
  // 499:         range &reference 2 -2
  // 500:         resolve_reference &reference
  // 501:         -> "[@(reference)](@(reference.mangled).html)"
  // 502:   if
  // ...
  frame->slots[15] /* temp__7 */ = create_closure(entry__29_126, 0);
  // 422: cond
  // 423:   ->
  // 424:     has_prefix
  // 425:       paragraph
  // 426:       sequence
  // 427:         "Parameter"
  // 428:         sim2c::WHITESPACE
  // 429:         NAME
  // 430:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 431:         ':'
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
static void entry__29_24(void) {
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
  // 420: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__29_25;
}
static void cont__29_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* paragraphs */, arguments->slots[0]);
  // 421: ... : ($paragraph)
  // 422:   cond
  // 423:     ->
  // 424:       has_prefix
  // 425:         paragraph
  // 426:         sequence
  // 427:           "Parameter"
  // 428:           sim2c::WHITESPACE
  // 429:           NAME
  // 430:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[10] /* temp__1 */ = create_closure(entry__29_26, 1);
  // 421: for_each paragraphs: ($paragraph)
  // 422:   cond
  // 423:     ->
  // 424:       has_prefix
  // 425:         paragraph
  // 426:         sequence
  // 427:           "Parameter"
  // 428:           sim2c::WHITESPACE
  // 429:           NAME
  // 430:           optional(PARAMETER_COUNT_OR_MYSELF)
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
static void cont__29_147(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 511: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__29_148;
}
static void cont__29_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 511: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_149;
}
static void cont__29_149(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 511: ... :
  // 512:   for_each parameters_of(info): (parameter)
  // 513:     case
  // 514:       parameter_kind_of(parameter)
  // 515:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 516:         pass
  // 517:       :
  // 518:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:         cond
  // 520:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_150, 0);
  // 511: if kind_of(info) == FUNCTION:
  // 512:   for_each parameters_of(info): (parameter)
  // 513:     case
  // 514:       parameter_kind_of(parameter)
  // 515:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 516:         pass
  // 517:       :
  // 518:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:         cond
  // 520:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_187;
}
static void entry__29_155(void) {
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
  // 518: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__29_156;
}
static void cont__29_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 518: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__29_157;
}
static void cont__29_157(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 518: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__29_158;
}
static void cont__29_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 520: -> parameter.is_an_optional_item:
  // 521:   if
  // 522:     default_value_of(parameter).is_defined:
  // 523:       write_to
  // 524:         &name
  // 525:         " (optional; default value: "
  // 526:         default_value_of(parameter).to_string
  // 527:         ")"
  // 528:     :
  // 529:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_159, 0);
  // 530: -> parameter.is_an_expanded_item:
  // 531:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_170, 0);
  // 519: cond
  // 520:   -> parameter.is_an_optional_item:
  // 521:     if
  // 522:       default_value_of(parameter).is_defined:
  // 523:         write_to
  // 524:           &name
  // 525:           " (optional; default value: "
  // 526:           default_value_of(parameter).to_string
  // 527:           ")"
  // 528:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_174;
}
static void entry__29_172(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 531: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_46;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_173;
}
static void cont__29_173(void) {
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
static void entry__29_164(void) {
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
  // 526: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__29_165;
}
static void cont__29_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 526: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__29_166;
}
static void cont__29_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 523: write_to
  // 524:   &name
  // 525:   " (optional; default value: "
  // 526:   default_value_of(parameter).to_string
  // 527:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_55;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__29_56;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__29_167;
}
static void cont__29_167(void) {
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
static void entry__29_168(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 529: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_39;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_169;
}
static void cont__29_169(void) {
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
static void entry__29_161(void) {
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
  // 522: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__29_162;
}
static void cont__29_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 522: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_163;
}
static void cont__29_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 522: ... :
  // 523:   write_to
  // 524:     &name
  // 525:     " (optional; default value: "
  // 526:     default_value_of(parameter).to_string
  // 527:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_164, 0);
  // 528: :
  // 529:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_168, 0);
  // 521: if
  // 522:   default_value_of(parameter).is_defined:
  // 523:     write_to
  // 524:       &name
  // 525:       " (optional; default value: "
  // 526:       default_value_of(parameter).to_string
  // 527:       ")"
  // 528:   :
  // 529:     append &name " (optional)"
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
static void entry__29_159(void) {
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
  // 520: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__29_160;
}
static void cont__29_160(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 520: ... :
  // 521:   if
  // 522:     default_value_of(parameter).is_defined:
  // 523:       write_to
  // 524:         &name
  // 525:         " (optional; default value: "
  // 526:         default_value_of(parameter).to_string
  // 527:         ")"
  // 528:     :
  // 529:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_161, 0);
  // 520: -> parameter.is_an_optional_item:
  // 521:   if
  // 522:     default_value_of(parameter).is_defined:
  // 523:       write_to
  // 524:         &name
  // 525:         " (optional; default value: "
  // 526:         default_value_of(parameter).to_string
  // 527:         ")"
  // 528:     :
  // 529:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_170(void) {
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
  // 530: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__29_171;
}
static void cont__29_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 530: ... :
  // 531:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_172, 0);
  // 530: -> parameter.is_an_expanded_item:
  // 531:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_174(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 535: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_175;
}
static void cont__29_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 535: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_176;
}
static void cont__29_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 535: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__29_177;
}
static void cont__29_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 536: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__29_178, 0);
  // 533: $description
  // 534:   if
  // 535:     not(remark_lines_of(parameter).is_empty)
  // 536:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 537:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__29_182;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_183;
}
static void entry__29_178(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 536: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_179;
}
static void cont__29_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 536: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__29_180;
}
static void cont__29_180(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 536: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__29_181;
}
static void cont__29_181(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 536: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_182(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 539: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_184;
}
static void cont__29_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 539: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_185;
}
static void cont__29_185(void) {
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
static void entry__29_186(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 516: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_152(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 514: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__29_153;
}
static void cont__29_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 515: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_154;
}
static void cont__29_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 517: :
  // 518:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:   cond
  // 520:     -> parameter.is_an_optional_item:
  // 521:       if
  // 522:         default_value_of(parameter).is_defined:
  // 523:           write_to
  // 524:             &name
  // 525:             " (optional; default value: "
  // 526:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_155, 0);
  // 513: case
  // 514:   parameter_kind_of(parameter)
  // 515:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 516:     pass
  // 517:   :
  // 518:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:     cond
  // 520:       -> parameter.is_an_optional_item:
  // 521:         if
  // 522:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__29_186;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_150(void) {
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
  // 512: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__29_151;
}
static void cont__29_151(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 512: ... : (parameter)
  // 513:   case
  // 514:     parameter_kind_of(parameter)
  // 515:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 516:       pass
  // 517:     :
  // 518:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:       cond
  // 520:         -> parameter.is_an_optional_item:
  // 521:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_152, 1);
  // 512: for_each parameters_of(info): (parameter)
  // 513:   case
  // 514:     parameter_kind_of(parameter)
  // 515:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 516:       pass
  // 517:     :
  // 518:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 519:       cond
  // 520:         -> parameter.is_an_optional_item:
  // 521:           if
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
static void cont__29_187(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 540: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_188;
}
static void cont__29_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 540: ... : P short_description
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_189, 0);
  // 540: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_190;
}
static void entry__29_189(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 540: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_190(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 541: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_191;
}
static void cont__29_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 541: ... :
  // 542:   H2 "Parameters"
  // 543:   DL:
  // 544:     for_each parameters: (parameter)
  // 545:       DT key_of(parameter)
  // 546:       DD: P std::value_of(parameter)
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_192, 0);
  // 541: unless parameters.is_empty:
  // 542:   H2 "Parameters"
  // 543:   DL:
  // 544:     for_each parameters: (parameter)
  // 545:       DT key_of(parameter)
  // 546:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_201;
}
static void entry__29_199(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 546: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_200;
}
static void cont__29_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 546: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_196(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 545: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_197;
}
static void cont__29_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 545: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__29_198;
}
static void cont__29_198(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 546: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_199, 0);
  // 546: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_195(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 544: for_each parameters: (parameter)
  // 545:   DT key_of(parameter)
  // 546:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__29_196;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_192(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 542: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_193;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_194;
}
static void cont__29_194(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 543: ... :
  // 544:   for_each parameters: (parameter)
  // 545:     DT key_of(parameter)
  // 546:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_195, 0);
  // 543: DL:
  // 544:   for_each parameters: (parameter)
  // 545:     DT key_of(parameter)
  // 546:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_201(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 547: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_202;
}
static void cont__29_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 547: ... :
  // 548:   H2 "Returns"
  // 549:   DL:
  // 550:     for_each return_values: (return_value)
  // 551:       DT key_of(return_value)
  // 552:       DD: P std::value_of(return_value)
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_203, 0);
  // 547: unless return_values.is_empty:
  // 548:   H2 "Returns"
  // 549:   DL:
  // 550:     for_each return_values: (return_value)
  // 551:       DT key_of(return_value)
  // 552:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_211;
}
static void entry__29_209(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 552: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_210;
}
static void cont__29_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 552: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_206(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 551: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_207;
}
static void cont__29_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 551: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__29_208;
}
static void cont__29_208(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 552: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_209, 0);
  // 552: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_205(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 550: for_each return_values: (return_value)
  // 551:   DT key_of(return_value)
  // 552:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__29_206;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_203(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 548: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_65;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_204;
}
static void cont__29_204(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 549: ... :
  // 550:   for_each return_values: (return_value)
  // 551:     DT key_of(return_value)
  // 552:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_205, 0);
  // 549: DL:
  // 550:   for_each return_values: (return_value)
  // 551:     DT key_of(return_value)
  // 552:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 553: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_212;
}
static void cont__29_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 553: ... :
  // 554:   H2 "Description"
  // 555:   for_each descriptions: (description) P description
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_213, 0);
  // 553: unless descriptions.is_empty:
  // 554:   H2 "Description"
  // 555:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_217;
}
static void entry__29_216(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 555: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_213(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 554: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_214;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_215;
}
static void cont__29_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 555: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__29_216;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 556: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_218;
}
static void cont__29_218(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 556: ... :
  // 557:   H2 "Technical Details"
  // 558:   for_each technical_details: (detail) P detail
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_219, 0);
  // 556: if technical_details.is_defined:
  // 557:   H2 "Technical Details"
  // 558:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_223;
}
static void entry__29_222(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 558: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_219(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 557: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_220;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_221;
}
static void cont__29_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 558: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__29_222;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_223(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 559: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_224;
}
static void cont__29_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 559: ... :
  // 560:   H2 "See Also"
  // 561:   P:
  // 562:     for_each references: ($reference)
  // 563:       resolve_reference &reference
  // 564:       A "href" = "@(reference.mangled).html" reference
  // 565:       BR
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_225, 0);
  // 559: unless references.is_empty:
  // 560:   H2 "See Also"
  // 561:   P:
  // 562:     for_each references: ($reference)
  // 563:       resolve_reference &reference
  // 564:       A "href" = "@(reference.mangled).html" reference
  // 565:       BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_235;
}
static void entry__29_229(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 563: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__29_230;
}
static void cont__29_230(void) {
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
  frame->cont = cont__29_231;
}
static void cont__29_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 564: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_232;
}
static void cont__29_232(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 564: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_233;
}
static void cont__29_233(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 564: A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__29_234;
}
static void cont__29_234(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 565: BR
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__BR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_228(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 562: for_each references: ($reference)
  // 563:   resolve_reference &reference
  // 564:   A "href" = "@(reference.mangled).html" reference
  // 565:   BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = func__29_229;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_225(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 560: H2 "See Also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_226;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_227;
}
static void cont__29_227(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: ... :
  // 562:   for_each references: ($reference)
  // 563:     resolve_reference &reference
  // 564:     A "href" = "@(reference.mangled).html" reference
  // 565:     BR
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_228, 0);
  // 561: P:
  // 562:   for_each references: ($reference)
  // 563:     resolve_reference &reference
  // 564:     A "href" = "@(reference.mangled).html" reference
  // 565:     BR
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 566: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__29_236;
}
static void cont__29_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 566: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_237;
}
static void cont__29_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 566: ... :
  // 567:   H2 "Implemented by"
  // 568:   TABLE:
  // 569:     for_each types_of(info): (name)
  // 570:       $method string(name '/' function_name)
  // 571:       TR:
  // 572:         TD: A "href" = "@(name.mangled).html" name
  // 573:         TD "&nbsp;as&nbsp;"
  // 574:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_238, 0);
  // 566: unless types_of(info).is_empty:
  // 567:   H2 "Implemented by"
  // 568:   TABLE:
  // 569:     for_each types_of(info): (name)
  // 570:       $method string(name '/' function_name)
  // 571:       TR:
  // 572:         TD: A "href" = "@(name.mangled).html" name
  // 573:         TD "&nbsp;as&nbsp;"
  // 574:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_257;
}
static void entry__29_253(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 574: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_254;
}
static void cont__29_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 574: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_255;
}
static void cont__29_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 574: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_256;
}
static void cont__29_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 574: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_245(void) {
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
  // 572: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_246, 0);
  // 572: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_250;
}
static void entry__29_246(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 572: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_247;
}
static void cont__29_247(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 572: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_248;
}
static void cont__29_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 572: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_249;
}
static void cont__29_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 572: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_250(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 573: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_251;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_252;
}
static void cont__29_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_253, 0);
  // 574: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_243(void) {
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
  // 570: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_244;
}
static void cont__29_244(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 571: ... :
  // 572:   TD: A "href" = "@(name.mangled).html" name
  // 573:   TD "&nbsp;as&nbsp;"
  // 574:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_245, 0);
  // 571: TR:
  // 572:   TD: A "href" = "@(name.mangled).html" name
  // 573:   TD "&nbsp;as&nbsp;"
  // 574:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_241(void) {
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
  // 569: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__29_242;
}
static void cont__29_242(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 569: ... : (name)
  // 570:   $method string(name '/' function_name)
  // 571:   TR:
  // 572:     TD: A "href" = "@(name.mangled).html" name
  // 573:     TD "&nbsp;as&nbsp;"
  // 574:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_243, 1);
  // 569: for_each types_of(info): (name)
  // 570:   $method string(name '/' function_name)
  // 571:   TR:
  // 572:     TD: A "href" = "@(name.mangled).html" name
  // 573:     TD "&nbsp;as&nbsp;"
  // 574:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_238(void) {
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
  // 567: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_239;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_240;
}
static void cont__29_240(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 568: ... :
  // 569:   for_each types_of(info): (name)
  // 570:     $method string(name '/' function_name)
  // 571:     TR:
  // 572:       TD: A "href" = "@(name.mangled).html" name
  // 573:       TD "&nbsp;as&nbsp;"
  // 574:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_241, 0);
  // 568: TABLE:
  // 569:   for_each types_of(info): (name)
  // 570:     $method string(name '/' function_name)
  // 571:     TR:
  // 572:       TD: A "href" = "@(name.mangled).html" name
  // 573:       TD "&nbsp;as&nbsp;"
  // 574:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_257(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 575: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__29_258;
}
static void cont__29_258(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 575: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_259;
}
static void cont__29_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 575: ... :
  // 576:   H2 "Supported Polymorphic Functions"
  // 577:   TABLE:
  // 578:     for_each methods_of(info): (method_name _method_info)
  // 579:       TR:
  // 580:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:         TD "&nbsp;"
  // 582:         TD:
  // 583:           A
  // 584:             =
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_260, 0);
  // 575: if kind_of(info) == TYPE:
  // 576:   H2 "Supported Polymorphic Functions"
  // 577:   TABLE:
  // 578:     for_each methods_of(info): (method_name _method_info)
  // 579:       TR:
  // 580:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:         TD "&nbsp;"
  // 582:         TD:
  // 583:           A
  // 584:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_279;
}
static void entry__29_274(void) {
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
  // 586: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_275;
}
static void cont__29_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 586: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_276;
}
static void cont__29_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 586: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__22_3;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_277;
}
static void cont__29_277(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 584: =
  // 585:   "href"
  // 586:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_278;
}
static void cont__29_278(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 583: A
  // 584:   =
  // 585:     "href"
  // 586:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:   function_name
  // 588:   '/'
  // 589:   method_name
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
static void entry__29_266(void) {
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
  // 580: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_267, 0);
  // 580: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_271;
}
static void entry__29_267(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 580: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_268;
}
static void cont__29_268(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 580: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_269;
}
static void cont__29_269(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 580: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_270;
}
static void cont__29_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 580: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_271(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 581: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_272;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_273;
}
static void cont__29_273(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 582: ... :
  // 583:   A
  // 584:     =
  // 585:       "href"
  // 586:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:     function_name
  // 588:     '/'
  // 589:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_274, 0);
  // 582: TD:
  // 583:   A
  // 584:     =
  // 585:       "href"
  // 586:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:     function_name
  // 588:     '/'
  // 589:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_265(void) {
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
  // 579: ... :
  // 580:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:   TD "&nbsp;"
  // 582:   TD:
  // 583:     A
  // 584:       =
  // 585:         "href"
  // 586:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:       function_name
  // 588:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_266, 0);
  // 579: TR:
  // 580:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:   TD "&nbsp;"
  // 582:   TD:
  // 583:     A
  // 584:       =
  // 585:         "href"
  // 586:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:       function_name
  // 588:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_263(void) {
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
  // 578: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__29_264;
}
static void cont__29_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 578: ... : (method_name _method_info)
  // 579:   TR:
  // 580:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:     TD "&nbsp;"
  // 582:     TD:
  // 583:       A
  // 584:         =
  // 585:           "href"
  // 586:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_265, 2);
  // 578: for_each methods_of(info): (method_name _method_info)
  // 579:   TR:
  // 580:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:     TD "&nbsp;"
  // 582:     TD:
  // 583:       A
  // 584:         =
  // 585:           "href"
  // 586:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 587:         function_name
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
static void entry__29_260(void) {
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
  // 576: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_261;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_262;
}
static void cont__29_262(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 577: ... :
  // 578:   for_each methods_of(info): (method_name _method_info)
  // 579:     TR:
  // 580:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:       TD "&nbsp;"
  // 582:       TD:
  // 583:         A
  // 584:           =
  // 585:             "href"
  // 586:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_263, 0);
  // 577: TABLE:
  // 578:   for_each methods_of(info): (method_name _method_info)
  // 579:     TR:
  // 580:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 581:       TD "&nbsp;"
  // 582:       TD:
  // 583:         A
  // 584:           =
  // 585:             "href"
  // 586:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__29_279(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 592: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__29_280;
}
static void cont__29_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 591: $function_basename
  // 592:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__29_281;
}
static void cont__29_281(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* function_basename */, arguments->slots[0]);
  // 594: ... : (example)
  // 595:   $title key_of(example)
  // 596:   $text std::value_of(example)
  // 597:   H2 title
  // 598:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 599:     PRE
  // 600:       replace_all
  // 601:         text
  // 602:         =
  // 603:           sequence
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__29_282, 1);
  // 594: for_each examples: (example)
  // 595:   $title key_of(example)
  // 596:   $text std::value_of(example)
  // 597:   H2 title
  // 598:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 599:     PRE
  // 600:       replace_all
  // 601:         text
  // 602:         =
  // 603:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* examples */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__29_301;
}
static void entry__29_290(void) {
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
  // 605: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__29_291;
}
static void cont__29_291(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 605: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_292;
}
static void cont__29_292(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 605: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__29_293;
}
static void cont__29_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 603: sequence
  // 604:   '@quot;'
  // 605:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_294;
}
static void cont__29_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 602: =
  // 603:   sequence
  // 604:     '@quot;'
  // 605:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:     '@quot;'
  // 607:   : (string_literal)
  // 608:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__29_295;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_296;
}
static void entry__29_295(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 608: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_296(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 609: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_297;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__29_297;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_298;
}
static void cont__29_298(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 609: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_299;
}
static void cont__29_299(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 600: replace_all
  // 601:   text
  // 602:   =
  // 603:     sequence
  // 604:       '@quot;'
  // 605:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:       '@quot;'
  // 607:     : (string_literal)
  // 608:       -> string_literal
  // 609:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__29_300;
}
static void cont__29_300(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 599: PRE
  // 600:   replace_all
  // 601:     text
  // 602:     =
  // 603:       sequence
  // 604:         '@quot;'
  // 605:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:         '@quot;'
  // 607:       : (string_literal)
  // 608:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_282(void) {
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
  // 595: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_283;
}
static void cont__29_283(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 596: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_284;
}
static void cont__29_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 597: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_285;
}
static void cont__29_285(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 598: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__29_286;
}
static void cont__29_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 598: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__29_287;
}
static void cont__29_287(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 598: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_288;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_289;
}
static void cont__29_289(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 598: ... :
  // 599:   PRE
  // 600:     replace_all
  // 601:       text
  // 602:       =
  // 603:         sequence
  // 604:           '@quot;'
  // 605:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:           '@quot;'
  // 607:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__29_290, 0);
  // 598: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 599:   PRE
  // 600:     replace_all
  // 601:       text
  // 602:       =
  // 603:         sequence
  // 604:           '@quot;'
  // 605:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 606:           '@quot;'
  // 607:         : (string_literal)
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
static void cont__29_301(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 611: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_288;
  arguments->slots[1] = string__29_302;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_303;
}
static void cont__29_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 612: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__29_304;
}
static void cont__29_304(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__4 */ = arguments->slots[0];
  // 612: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__29_305;
}
static void cont__29_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 612: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_306;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = string__29_307;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_308;
}
static void cont__29_308(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 610: DIV
  // 611:   "class" = "footer"
  // 612:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__29_3(void) {
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
  // 392: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_4;
}
static void cont__29_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 392: ... "html/@(function_name.mangled).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_5;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_7;
}
static void cont__29_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 392: ... :
  // 393:   link_bar
  // 394:   if
  // 395:     function_name .contains. '/':
  // 396:       $type function_name .before. '/'
  // 397:       $method function_name .behind. '/'
  // 398:       H1
  // 399:         string
  // 400:           '['
  // 401:           type
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_8, 0);
  // 392: create_page "html/@(function_name.mangled).html":
  // 393:   link_bar
  // 394:   if
  // 395:     function_name .contains. '/':
  // 396:       $type function_name .before. '/'
  // 397:       $method function_name .behind. '/'
  // 398:       H1
  // 399:         string
  // 400:           '['
  // 401:           type
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
static void entry__29_1(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // function_name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 391: ... function_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_2;
}
static void cont__29_2(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 391: ... :
  // 392:   create_page "html/@(function_name.mangled).html":
  // 393:     link_bar
  // 394:     if
  // 395:       function_name .contains. '/':
  // 396:         $type function_name .before. '/'
  // 397:         $method function_name .behind. '/'
  // 398:         H1
  // 399:           string
  // 400:             '['
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_3, 0);
  // 391: if function_name.is_defined:
  // 392:   create_page "html/@(function_name.mangled).html":
  // 393:     link_bar
  // 394:     if
  // 395:       function_name .contains. '/':
  // 396:         $type function_name .before. '/'
  // 397:         $method function_name .behind. '/'
  // 398:         H1
  // 399:           string
  // 400:             '['
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
static void entry__30_1(void) {
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
  define__html__encode(func__30_2);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 627: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__30_20;
}
static void entry__30_2(void) {
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
  // 616: ... tag == "p"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* tag */;
  arguments->slots[1] = string__30_3;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_4;
}
static void cont__30_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 616: ... :
  // 617:   replace_all
  // 618:     &text
  // 619:     =
  // 620:       "&lt;", NAME, "::", NAME, '>'
  // 621:       : (capture)
  // 622:         $reference resolve_reference(range(capture 5 -2))
  // 623:         -> "
  // 624:           <a href="@(reference.mangled).html">@(reference)</a>@
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 616: if tag == "p":
  // 617:   replace_all
  // 618:     &text
  // 619:     =
  // 620:       "&lt;", NAME, "::", NAME, '>'
  // 621:       : (capture)
  // 622:         $reference resolve_reference(range(capture 5 -2))
  // 623:         -> "
  // 624:           <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_19;
}
static void entry__30_5(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // text: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* text */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 620: "&lt;", NAME, "::", NAME, '>'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__30_6;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = string__20_24;
  arguments->slots[3] = get__NAME();
  arguments->slots[4] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__30_7;
}
static void cont__30_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 619: =
  // 620:   "&lt;", NAME, "::", NAME, '>'
  // 621:   : (capture)
  // 622:     $reference resolve_reference(range(capture 5 -2))
  // 623:     -> "
  // 624:       <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__30_8;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_17;
}
static void entry__30_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // capture: 0
  // reference: 1
  frame->slots[1] /* reference */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 622: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__30_9;
}
static void cont__30_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 622: ... range(capture 5 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* capture */;
  arguments->slots[1] = number__5;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__30_10;
}
static void cont__30_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 622: $reference resolve_reference(range(capture 5 -2))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__30_11;
}
static void cont__30_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* reference */, arguments->slots[0]);
  // 624: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_12;
}
static void cont__30_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 623: ... "
  // 624:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__30_13;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__30_14;
  arguments->slots[3] = frame->slots[1] /* reference */;
  arguments->slots[4] = string__30_15;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_16;
}
static void cont__30_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 623: -> "
  // 624:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 617: replace_all
  // 618:   &text
  // 619:   =
  // 620:     "&lt;", NAME, "::", NAME, '>'
  // 621:     : (capture)
  // 622:       $reference resolve_reference(range(capture 5 -2))
  // 623:       -> "
  // 624:         <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_18;
}
static void cont__30_18(void) {
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
static void cont__30_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 625: emit text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 627: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__30_21;
}
static void cont__30_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 628: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__30_22;
}
static void cont__30_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 629: for_each definitions: (name info)
  // 630:   if kind_of(info) == TYPE:
  // 631:     $base base_of(info)
  // 632:     if base.is_defined: add_derived_type base name
  // 633:     $$methods empty_key_order_table
  // 634:     for_each methods_of(info): ($method_name method_info)
  // 635:       unless method_name .contains. "::":
  // 636:         !method_name attribute_of(method_info).resolved_name
  // 637:       if name_of(info).is_defined:
  // 638:         $oname
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__30_23;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_54;
}
static void entry__30_26(void) {
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
  // 631: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__30_27;
}
static void cont__30_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base */, arguments->slots[0]);
  // 632: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_28;
}
static void cont__30_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 632: ... : add_derived_type base name
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_29, 0);
  // 632: if base.is_defined: add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_30;
}
static void entry__30_29(void) {
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
  // 632: ... add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 633: $$methods empty_key_order_table
  ((CELL *)frame->slots[3])->contents /* methods */ = get__empty_key_order_table();
  // 634: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__30_31;
}
static void cont__30_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 634: ... : ($method_name method_info)
  // 635:   unless method_name .contains. "::":
  // 636:     !method_name attribute_of(method_info).resolved_name
  // 637:   if name_of(info).is_defined:
  // 638:     $oname
  // 639:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 640:     
  // 641:     !definitions(oname).types_of(name_of(info)) true
  // 642:   !methods(method_name) method_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_32, 2);
  // 634: for_each methods_of(info): ($method_name method_info)
  // 635:   unless method_name .contains. "::":
  // 636:     !method_name attribute_of(method_info).resolved_name
  // 637:   if name_of(info).is_defined:
  // 638:     $oname
  // 639:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 640:     
  // 641:     !definitions(oname).types_of(name_of(info)) true
  // 642:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_51;
}
static void entry__30_32(void) {
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
  // 635: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__30_33;
}
static void cont__30_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 635: ... :
  // 636:   !method_name attribute_of(method_info).resolved_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_34, 0);
  // 635: unless method_name .contains. "::":
  // 636:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__30_37;
}
static void entry__30_34(void) {
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
  // 636: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__30_35;
}
static void cont__30_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 636: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__30_36;
}
static void cont__30_36(void) {
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
static void cont__30_37(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_38;
}
static void cont__30_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 637: ... name_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_39;
}
static void cont__30_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 637: ... :
  // 638:   $oname
  // 639:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 640:   
  // 641:   !definitions(oname).types_of(name_of(info)) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__30_40, 0);
  // 637: if name_of(info).is_defined:
  // 638:   $oname
  // 639:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 640:   
  // 641:   !definitions(oname).types_of(name_of(info)) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_49;
}
static void entry__30_40(void) {
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
  // 639: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__30_41;
}
static void cont__30_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 639: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__30_42;
}
static void cont__30_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 638: $oname
  // 639:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__30_43;
}
static void cont__30_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* oname */, arguments->slots[0]);
  // 641: !definitions(oname).types_of(name_of(info)) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 641: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_44;
}
static void cont__30_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 641: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__30_45;
}
static void cont__30_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 641: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_46;
}
static void cont__30_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 641: !definitions(oname).types_of(name_of(info))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__30_47;
}
static void cont__30_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 641: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[5] /* temp__3 */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 641: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_48;
}
static void cont__30_48(void) {
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
static void cont__30_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 642: !methods(method_name) method_info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 642: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__30_50;
}
static void cont__30_50(void) {
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
static void cont__30_51(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 643: !definitions(name).methods_of methods
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* methods */;
  // 643: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_52;
}
static void cont__30_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 643: !definitions(name).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[4] /* temp__1 */);
    frame->slots[5] /* temp__2 */ = temp;

  }
  // 643: !definitions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_53;
}
static void cont__30_53(void) {
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
static void entry__30_23(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 630: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_24;
}
static void cont__30_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 630: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_25;
}
static void cont__30_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 630: ... :
  // 631:   $base base_of(info)
  // 632:   if base.is_defined: add_derived_type base name
  // 633:   $$methods empty_key_order_table
  // 634:   for_each methods_of(info): ($method_name method_info)
  // 635:     unless method_name .contains. "::":
  // 636:       !method_name attribute_of(method_info).resolved_name
  // 637:     if name_of(info).is_defined:
  // 638:       $oname
  // 639:         ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_26, 0);
  // 630: if kind_of(info) == TYPE:
  // 631:   $base base_of(info)
  // 632:   if base.is_defined: add_derived_type base name
  // 633:   $$methods empty_key_order_table
  // 634:   for_each methods_of(info): ($method_name method_info)
  // 635:     unless method_name .contains. "::":
  // 636:       !method_name attribute_of(method_info).resolved_name
  // 637:     if name_of(info).is_defined:
  // 638:       $oname
  // 639:         ordered_name(method_name .before. "::" method_name .behind. "::")
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
static void cont__30_54(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 644: create_page "html/type_index.html":
  // 645:   $print_type_info:
  // 646:     (
  // 647:       info
  // 648:       indent = 0
  // 649:     )
  // 650:     TR:
  // 651:       $qname name_of(info)
  // 652:       $remark_lines remark_lines_of(info)
  // 653:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_55;
  arguments->slots[1] = func__30_56;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_94;
}
static void entry__30_93(void) {
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
  // 667: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_86(void) {
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
  // 666: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_87;
}
static void cont__30_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 666: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_88;
}
static void cont__30_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 666: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__30_89, 0);
  // 666: ... kind_of(info) == TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_92;
}
static void entry__30_89(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 666: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__30_90;
}
static void cont__30_90(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 666: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__30_91;
}
static void cont__30_91(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 666: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 666: ... :
  // 667:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__30_93, 0);
  // 666: if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 667:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_85(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 665: ... : (_base info)
  // 666:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 667:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_86, 2);
  // 665: for_each definitions: (_base info)
  // 666:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 667:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_56(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 645: ... :
  // 646:   (
  // 647:     info
  // 648:     indent = 0
  // 649:   )
  // 650:   TR:
  // 651:     $qname name_of(info)
  // 652:     $remark_lines remark_lines_of(info)
  // 653:     if qname.is_defined:
  // 654:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_57, -1);
  // 645: $print_type_info:
  // 646:   (
  // 647:     info
  // 648:     indent = 0
  // 649:   )
  // 650:   TR:
  // 651:     $qname name_of(info)
  // 652:     $remark_lines remark_lines_of(info)
  // 653:     if qname.is_defined:
  // 654:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 662: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_83;
}
static void entry__30_80(void) {
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
  // 660: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_81;
}
static void cont__30_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 660: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__30_82;
}
static void cont__30_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 660: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_58(void) {
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
  // 651: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_59;
}
static void cont__30_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 652: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__30_60;
}
static void cont__30_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 653: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_61;
}
static void cont__30_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 653: ... :
  // 654:   TD:
  // 655:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__30_62, 0);
  // 653: if qname.is_defined:
  // 654:   TD:
  // 655:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_69;
}
static void entry__30_63(void) {
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
  // 655: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_8;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__30_64;
}
static void cont__30_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 655: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_65;
}
static void cont__30_65(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 656: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_66;
}
static void cont__30_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 656: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_67;
}
static void cont__30_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 656: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_68;
}
static void cont__30_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 656: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_62(void) {
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
  // 654: ... :
  // 655:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_63, 0);
  // 654: TD:
  // 655:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_69(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_70;
}
static void cont__30_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 657: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__30_71, 0);
  // 657: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_74;
}
static void entry__30_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 657: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__30_72;
}
static void cont__30_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 657: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__30_73;
}
static void cont__30_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 657: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 657: ... :
  // 658:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__30_75, 0);
  // 657: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 658:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_78;
}
static void entry__30_75(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 658: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__30_76;
}
static void cont__30_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 658: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__30_77;
}
static void cont__30_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 658: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_78(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 659: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__30_79;
}
static void cont__30_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 659: ... : (name)
  // 660:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__30_80, 1);
  // 659: for_each derived_types_of(info): (name)
  // 660:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_57(void) {
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
  // 650: ... :
  // 651:   $qname name_of(info)
  // 652:   $remark_lines remark_lines_of(info)
  // 653:   if qname.is_defined:
  // 654:     TD:
  // 655:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:       A "href" = "@(qname.mangled).html" qname
  // 657:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 658:     TD remark_lines.to_paragraphs(1)
  // 659:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__30_58, 0);
  // 650: TR:
  // 651:   $qname name_of(info)
  // 652:   $remark_lines remark_lines_of(info)
  // 653:   if qname.is_defined:
  // 654:     TD:
  // 655:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 656:       A "href" = "@(qname.mangled).html" qname
  // 657:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 658:     TD remark_lines.to_paragraphs(1)
  // 659:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_17;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_84;
}
static void cont__30_84(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: ... :
  // 665:   for_each definitions: (_base info)
  // 666:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 667:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_85, 0);
  // 664: TABLE:
  // 665:   for_each definitions: (_base info)
  // 666:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 667:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_94(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 668: create_page "html/symbol_index.html":
  // 669:   link_bar
  // 670:   H1 "id" = "index" "Symbol Index"
  // 671:   from_to
  // 672:     'a'
  // 673:     'z': (letter)
  // 674:       A "href" = "#@(letter)" letter.to_upper_case
  // 675:     :
  // 676:       TEXT " "
  // 677:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_95;
  arguments->slots[1] = func__30_96;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_180;
}
static void entry__30_166(void) {
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
  // 717: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_167;
  arguments->slots[1] = string__30_168;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_169;
}
static void cont__30_169(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 717: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__30_170;
}
static void cont__30_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 717: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__30_171;
}
static void cont__30_171(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 718: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_172, 0);
  // 718: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__30_177;
}
static void entry__30_172(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 718: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_173;
}
static void cont__30_173(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 718: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_174;
}
static void cont__30_174(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 718: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_175;
}
static void cont__30_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 718: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__20_24;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__30_176;
}
static void cont__30_176(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 718: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_177(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 719: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_288;
  arguments->slots[1] = string__30_178;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_179;
}
static void cont__30_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 719: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_165(void) {
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
  // 716: ... :
  // 717:   TD "align" = "right" name .until. "::"
  // 718:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 719:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_166, 0);
  // 716: TR:
  // 717:   TD "align" = "right" name .until. "::"
  // 718:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 719:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_112(void) {
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
  // 681: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__30_113;
}
static void cont__30_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 681: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_114;
}
static void cont__30_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 681: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__30_115;
}
static void cont__30_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 681: ... :
  // 682:   !letter iname(1)
  // 683:   TR:
  // 684:     TD "colspan" = 3:
  // 685:       H2 "id" = letter:
  // 686:         TEXT letter.to_upper_case
  // 687:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_116, 0);
  // 681: if iname(1) != letter:
  // 682:   !letter iname(1)
  // 683:   TR:
  // 684:     TD "colspan" = 3:
  // 685:       H2 "id" = letter:
  // 686:         TEXT letter.to_upper_case
  // 687:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_129;
}
static void entry__30_123(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 686: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__30_124;
}
static void cont__30_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 686: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_125;
}
static void cont__30_125(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 687: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__30_126;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_127;
}
static void cont__30_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 687: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__30_128;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_121(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 685: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_98;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_122;
}
static void cont__30_122(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 685: ... :
  // 686:   TEXT letter.to_upper_case
  // 687:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__30_123, 0);
  // 685: H2 "id" = letter:
  // 686:   TEXT letter.to_upper_case
  // 687:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_118(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_119;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_120;
}
static void cont__30_120(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 684: ... :
  // 685:   H2 "id" = letter:
  // 686:     TEXT letter.to_upper_case
  // 687:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__30_121, 0);
  // 684: TD "colspan" = 3:
  // 685:   H2 "id" = letter:
  // 686:     TEXT letter.to_upper_case
  // 687:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_116(void) {
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
  // 682: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__30_117;
}
static void cont__30_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 683: ... :
  // 684:   TD "colspan" = 3:
  // 685:     H2 "id" = letter:
  // 686:       TEXT letter.to_upper_case
  // 687:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_118, 0);
  // 683: TR:
  // 684:   TD "colspan" = 3:
  // 685:     H2 "id" = letter:
  // 686:       TEXT letter.to_upper_case
  // 687:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_129(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 688: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 689: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_130;
}
static void cont__30_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 690: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__30_131;
}
static void cont__30_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 691: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_132;
}
static void cont__30_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 691: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__30_133, 0);
  // 691: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_136;
}
static void entry__30_133(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__30_134;
}
static void cont__30_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 691: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__30_135;
}
static void cont__30_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 691: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 691: ... :
  // 692:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_137, 0);
  // 691: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 692:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_140;
}
static void entry__30_137(void) {
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
  // 692: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__30_138;
}
static void cont__30_138(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 692: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__30_139;
}
static void cont__30_139(void) {
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
static void cont__30_140(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 696: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_141;
}
static void cont__30_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 694: $kind_info
  // 695:   case
  // 696:     kind_of(info)
  // 697:     FUNCTION
  // 698:     -> "function"
  // 699:     INLINE_C_FUNCTION
  // 700:     -> "inline-C function"
  // 701:     POLYMORPHIC
  // 702:     -> "polymorphic function"
  // 703:     UNIQUE_ITEM
  // ...
  argument_count = 12;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__30_142;
  arguments->slots[3] = var._INLINE_C_FUNCTION;
  arguments->slots[4] = func__30_144;
  arguments->slots[5] = get__POLYMORPHIC();
  arguments->slots[6] = func__30_146;
  arguments->slots[7] = var._UNIQUE_ITEM;
  arguments->slots[8] = func__30_148;
  arguments->slots[9] = var._TYPE;
  arguments->slots[10] = func__30_150;
  arguments->slots[11] = func__30_151;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__30_152;
}
static void entry__30_142(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 698: -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_143;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_144(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_145;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_146(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 702: -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_147;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_148(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 704: -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_149;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_150(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 706: -> "type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__18_92;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_151(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 707: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_152(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 709: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_153;
}
static void cont__30_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 709: ... :
  // 710:   if
  // 711:     remark.is_defined:
  // 712:       !remark string(remark " (" kind_info ")")
  // 713:     :
  // 714:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__30_154, 0);
  // 709: if kind_info.is_defined:
  // 710:   if
  // 711:     remark.is_defined:
  // 712:       !remark string(remark " (" kind_info ")")
  // 713:     :
  // 714:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_160;
}
static void entry__30_156(void) {
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
  // 712: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__30_157;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__29_56;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_158;
}
static void cont__30_158(void) {
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
static void entry__30_159(void) {
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
  // 714: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_154(void) {
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
  // 711: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_155;
}
static void cont__30_155(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 711: ... :
  // 712:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_156, 0);
  // 713: :
  // 714:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_159, 0);
  // 710: if
  // 711:   remark.is_defined:
  // 712:     !remark string(remark " (" kind_info ")")
  // 713:   :
  // 714:     !remark kind_info
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
static void cont__30_160(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 715: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_161;
}
static void cont__30_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 715: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__30_162, 0);
  // 715: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_164;
}
static void entry__30_162(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 715: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_163;
}
static void cont__30_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 715: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_164(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 715: ... :
  // 716:   TR:
  // 717:     TD "align" = "right" name .until. "::"
  // 718:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 719:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_165, 0);
  // 715: if remark.is_defined && name.is_defined:
  // 716:   TR:
  // 717:     TD "align" = "right" name .until. "::"
  // 718:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 719:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_111(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 679: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 680: ... : (iname info)
  // 681:   if iname(1) != letter:
  // 682:     !letter iname(1)
  // 683:     TR:
  // 684:       TD "colspan" = 3:
  // 685:         H2 "id" = letter:
  // 686:           TEXT letter.to_upper_case
  // 687:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 688:   $$remark undefined
  // 689:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_112, 2);
  // 680: for_each definitions: (iname info)
  // 681:   if iname(1) != letter:
  // 682:     !letter iname(1)
  // 683:     TR:
  // 684:       TD "colspan" = 3:
  // 685:         H2 "id" = letter:
  // 686:           TEXT letter.to_upper_case
  // 687:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 688:   $$remark undefined
  // 689:   $name name_of(info)
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
static void entry__30_96(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_97;
}
static void cont__30_97(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 670: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_98;
  arguments->slots[1] = string__30_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_100;
}
static void cont__30_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 670: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_22;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_101;
}
static void cont__30_101(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 671: from_to
  // 672:   'a'
  // 673:   'z': (letter)
  // 674:     A "href" = "#@(letter)" letter.to_upper_case
  // 675:   :
  // 676:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__30_102;
  arguments->slots[3] = func__30_107;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__30_109;
}
static void entry__30_102(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 674: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_103;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_104;
}
static void cont__30_104(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 674: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_105;
}
static void cont__30_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 674: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__30_106;
}
static void cont__30_106(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 674: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_107(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 676: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_108;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_109(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 677: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__30_110;
}
static void cont__30_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 678: TABLE:
  // 679:   $$letter undefined
  // 680:   for_each definitions: (iname info)
  // 681:     if iname(1) != letter:
  // 682:       !letter iname(1)
  // 683:       TR:
  // 684:         TD "colspan" = 3:
  // 685:           H2 "id" = letter:
  // 686:             TEXT letter.to_upper_case
  // 687:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_111;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_180(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 720: for_each definitions: (_iname info)
  // 721:   $name name_of(info)
  // 722:   if name.is_defined:
  // 723:     create_info_page name info
  // 724:     case kind_of(info) TYPE:
  // 725:       for_each methods_of(info): (method_name method_info)
  // 726:         create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__30_181;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_192;
}
static void entry__30_189(void) {
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
  // 726: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__30_190;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_191;
}
static void cont__30_191(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 726: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_187(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 725: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__30_188;
}
static void cont__30_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 725: ... : (method_name method_info)
  // 726:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_189, 2);
  // 725: for_each methods_of(info): (method_name method_info)
  // 726:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_184(void) {
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
  // 723: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__30_185;
}
static void cont__30_185(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 724: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_186;
}
static void cont__30_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 724: ... :
  // 725:   for_each methods_of(info): (method_name method_info)
  // 726:     create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_187, 0);
  // 724: case kind_of(info) TYPE:
  // 725:   for_each methods_of(info): (method_name method_info)
  // 726:     create_info_page string(name "/" method_name) method_info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = var._TYPE;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_181(void) {
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
  // 721: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_182;
}
static void cont__30_182(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 722: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_183;
}
static void cont__30_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 722: ... :
  // 723:   create_info_page name info
  // 724:   case kind_of(info) TYPE:
  // 725:     for_each methods_of(info): (method_name method_info)
  // 726:       create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_184, 0);
  // 722: if name.is_defined:
  // 723:   create_info_page name info
  // 724:   case kind_of(info) TYPE:
  // 725:     for_each methods_of(info): (method_name method_info)
  // 726:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_192(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 727: create_page "html/topic_index.html":
  // 728:   link_bar
  // 729:   H1 "id" = "index" "Topic Index"
  // 730:   TABLE:
  // 731:     for_each topics: (topic _references)
  // 732:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 733:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_193;
  arguments->slots[1] = func__30_194;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_208;
}
static void entry__30_206(void) {
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
  // 733: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[0] /* filename */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_207;
}
static void cont__30_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 733: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_205(void) {
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
  // 733: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_206, 0);
  // 733: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_199(void) {
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
  // 732: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_200;
}
static void cont__30_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 732: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__30_201;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_202;
}
static void cont__30_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 732: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_203;
}
static void cont__30_203(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 732: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_204;
}
static void cont__30_204(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 733: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__30_205, 0);
  // 733: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_198(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 731: for_each topics: (topic _references)
  // 732:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 733:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__30_199;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_194(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 728: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_195;
}
static void cont__30_195(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 729: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_98;
  arguments->slots[1] = string__30_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_196;
}
static void cont__30_196(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 729: H1 "id" = "index" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_27;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_197;
}
static void cont__30_197(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 730: TABLE:
  // 731:   for_each topics: (topic _references)
  // 732:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 733:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_198;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_208(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 734: for_each topics: (topic references)
  // 735:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 736:   create_page "html/@(filename).html":
  // 737:     link_bar
  // 738:     H1 "id" = "index" topic
  // 739:     TABLE:
  // 740:       for_each references: (reference)
  // 741:         TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__30_209;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_225;
}
static void entry__30_221(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 741: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_222;
}
static void cont__30_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 741: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_6;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_223;
}
static void cont__30_223(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 741: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_224;
}
static void cont__30_224(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 741: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_220(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 741: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_221, 0);
  // 741: ... TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_219(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 741: ... : TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_220, 0);
  // 741: TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_218(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 740: for_each references: (reference)
  // 741:   TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__30_219;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_214(void) {
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
  // 737: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_215;
}
static void cont__30_215(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_98;
  arguments->slots[1] = string__30_99;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_216;
}
static void cont__30_216(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 738: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_217;
}
static void cont__30_217(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 739: ... :
  // 740:   for_each references: (reference)
  // 741:     TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_218, 0);
  // 739: TABLE:
  // 740:   for_each references: (reference)
  // 741:     TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_209(void) {
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
  // 735: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_210;
}
static void cont__30_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 735: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__30_201;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_211;
}
static void cont__30_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 735: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_212;
}
static void cont__30_212(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 736: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_5;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__29_6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_213;
}
static void cont__30_213(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 736: ... :
  // 737:   link_bar
  // 738:   H1 "id" = "index" topic
  // 739:   TABLE:
  // 740:     for_each references: (reference)
  // 741:       TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_214, 0);
  // 736: create_page "html/@(filename).html":
  // 737:   link_bar
  // 738:   H1 "id" = "index" topic
  // 739:   TABLE:
  // 740:     for_each references: (reference)
  // 741:       TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 742: create_page "html/index.html":
  // 743:   H1 "Simplicity"
  // 744:   P: A "href" = "manual.html" "Manual"
  // 745:   P: A "href" = "type_index.html" "Type Index"
  // 746:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 747:   P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_226;
  arguments->slots[1] = func__30_227;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_241;
}
static void entry__30_239(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 747: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_25;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_240;
}
static void cont__30_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 747: ... A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_27;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__30_227(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 743: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_228;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_229;
}
static void cont__30_229(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 744: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_230;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_232;
}
static void entry__30_230(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 744: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_10;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_231;
}
static void cont__30_231(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 744: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_12;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 745: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_233;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_235;
}
static void entry__30_233(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 745: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_15;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_234;
}
static void cont__30_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 745: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_17;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_235(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 746: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_236;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_238;
}
static void entry__30_236(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 746: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_3;
  arguments->slots[1] = string__24_20;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_237;
}
static void cont__30_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 746: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_22;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_238(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 747: P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_239;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__30_241(void) {
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
  unique__9_1 = collect_node(unique__9_1);
  var._TYPE = collect_node(var._TYPE);
  unique__10_1 = collect_node(unique__10_1);
  var._FUNCTION = collect_node(var._FUNCTION);
  unique__11_1 = collect_node(unique__11_1);
  var._INLINE_C_FUNCTION = collect_node(var._INLINE_C_FUNCTION);
  unique__12_1 = collect_node(unique__12_1);
  var._UNIQUE_ITEM = collect_node(var._UNIQUE_ITEM);
  unique__13_1 = collect_node(unique__13_1);
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
  string__16_5 = from_latin_1_string("body {\012  background-color: white;\012  font-family: Times New Roman, Times;\012  font-size: 12pt;\012  color: #222;\012}\012h1 {\012  font-family: Arial, Helvetica;\012  font-size: 20pt;\012  color: #333;\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012h2 {\012  font-family: Arial, Helvetica;\012  font-size: 16pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 5pt;\012}\012h3 {\012  font-family: Arial, Helvetica;\012  font-size: 14pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 3pt;\012}\012h4 {\012  font-family: Arial, Helvetica;\012  font-size: 13pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 2pt;\012}\012dt {\012  font-style: italic;\012  margin-bottom: 4pt;\012}\012dd {\012  padding-left: 0pt;\012  margin-left: 16pt;\012  margin-top: 0pt;\012  margin-bottom: 0pt;\012}\012p {\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012a {\012  text-decoration: none;\012}\012div.Example {\012  background-color: #ffc;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.Output {\012  background-color: #cff;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.footer {\012  padding-top: 10pt;\012  font-size: 10pt;\012}\012pre {\012  font-family: Courier New, Courier;\012  font-size: 12pt;\012  padding-top: 0pt;\012  padding-bottom: 0pt;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012td.remark {\012  padding-left: 10pt;\012}\012", 1234);
  func__16_4 = create_function(entry__16_4, 0);
  func__16_1 = create_function(entry__16_1, 2);
  string__18_2 = from_latin_1_string("extracting documentation from ", 30);
  string__18_3 = from_latin_1_string("\012", 1);
  string__18_11 = from_latin_1_string("Empty source text!", 18);
  func__18_10 = create_function(entry__18_10, 0);
  string__18_17 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__18_16 = create_function(entry__18_16, 0);
  string__18_24 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__18_23 = create_function(entry__18_23, 0);
  string__18_26 = from_latin_1_string(".sim", 4);
  string__18_28 = from_latin_1_string("__", 2);
  func__18_32 = create_function(entry__18_32, 1);
  string__18_55 = from_latin_1_string("std", 3);
  func__18_54 = create_function(entry__18_54, 0);
  func__18_61 = create_function(entry__18_61, 0);
  func__18_64 = create_function(entry__18_64, 0);
  func__18_87 = create_function(entry__18_87, 0);
  string__18_92 = from_latin_1_string("type", 4);
  func__18_105 = create_function(entry__18_105, 0);
  string__18_135 = from_latin_1_string("types::function", 15);
  func__18_1 = create_function(entry__18_1, 1);
  func__19_4 = create_function(entry__19_4, 1);
  func__19_1 = create_function(entry__19_1, 1);
  string__20_14 = from_latin_1_string("The attribute \042", 15);
  string__20_15 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__20_21 = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__20_24 = from_latin_1_string("::", 2);
  func__20_1 = create_function(entry__20_1, 1);
  func__21_1 = create_function(entry__21_1, 2);
  string__22_3 = from_latin_1_string("___", 3);
  func__22_1 = create_function(entry__22_1, 1);
  func__23_1 = create_function(entry__23_1, 2);
  string__24_3 = from_latin_1_string("href", 4);
  string__24_4 = from_latin_1_string("index.html", 10);
  string__24_6 = from_latin_1_string("Home", 4);
  string__24_8 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__24_10 = from_latin_1_string("manual.html", 11);
  string__24_12 = from_latin_1_string("Manual", 6);
  string__24_15 = from_latin_1_string("type_index.html", 15);
  string__24_17 = from_latin_1_string("Type Index", 10);
  string__24_20 = from_latin_1_string("symbol_index.html", 17);
  string__24_22 = from_latin_1_string("Symbol Index", 12);
  string__24_25 = from_latin_1_string("topic_index.html", 16);
  string__24_27 = from_latin_1_string("Topic Index", 11);
  func__24_2 = create_function(entry__24_2, 0);
  func__24_1 = create_function(entry__24_1, 0);
  string__25_8 = from_latin_1_string("types::", 7);
  string__25_13 = from_latin_1_string("std::", 5);
  func__25_1 = create_function(entry__25_1, 1);
  func__28_1 = create_function(entry__28_1, 1);
  string__29_5 = from_latin_1_string("html/", 5);
  string__29_6 = from_latin_1_string(".html", 5);
  string__29_16 = from_latin_1_string("](", 2);
  string__29_17 = from_latin_1_string(".html)/[", 8);
  string__29_18 = from_latin_1_string(".html)", 6);
  string__29_29 = from_latin_1_string("Parameter", 9);
  string__29_39 = from_latin_1_string(" (optional)", 11);
  string__29_46 = from_latin_1_string(" (zero or more arguments)", 25);
  string__29_55 = from_latin_1_string(" (optional; default value: ", 27);
  string__29_56 = from_latin_1_string(")", 1);
  string__29_65 = from_latin_1_string("Returns", 7);
  string__29_88 = from_latin_1_string("See Also:", 9);
  string__29_117 = from_latin_1_string("Technical Details:", 18);
  string__29_135 = from_latin_1_string("[", 1);
  func__29_130 = create_function(entry__29_130, 1);
  func__29_182 = create_function(entry__29_182, 0);
  func__29_186 = create_function(entry__29_186, 0);
  string__29_193 = from_latin_1_string("Parameters", 10);
  func__29_196 = create_function(entry__29_196, 1);
  func__29_206 = create_function(entry__29_206, 1);
  string__29_214 = from_latin_1_string("Description", 11);
  func__29_216 = create_function(entry__29_216, 1);
  string__29_220 = from_latin_1_string("Technical Details", 17);
  func__29_222 = create_function(entry__29_222, 1);
  string__29_226 = from_latin_1_string("See Also", 8);
  func__29_229 = create_function(entry__29_229, 1);
  string__29_239 = from_latin_1_string("Implemented by", 14);
  string__29_251 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__29_261 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__29_272 = from_latin_1_string("&nbsp;", 6);
  string__29_288 = from_latin_1_string("class", 5);
  func__29_295 = create_function(entry__29_295, 1);
  string__29_297 = from_latin_1_string("**", 2);
  string__29_302 = from_latin_1_string("footer", 6);
  string__29_306 = from_latin_1_string("(defined in ", 12);
  string__29_307 = from_latin_1_string(")\012", 2);
  func__29_1 = create_function(entry__29_1, 2);
  string__30_3 = from_latin_1_string("p", 1);
  string__30_6 = from_latin_1_string("&lt;", 4);
  string__30_13 = from_latin_1_string("<a href=\042", 9);
  string__30_14 = from_latin_1_string(".html\042>", 7);
  string__30_15 = from_latin_1_string("</a>", 4);
  func__30_8 = create_function(entry__30_8, 1);
  func__30_2 = create_function(entry__30_2, 3);
  func__30_23 = create_function(entry__30_23, 2);
  string__30_55 = from_latin_1_string("html/type_index.html", 20);
  func__30_56 = create_function(entry__30_56, 0);
  string__30_95 = from_latin_1_string("html/symbol_index.html", 22);
  string__30_98 = from_latin_1_string("id", 2);
  string__30_99 = from_latin_1_string("index", 5);
  string__30_103 = from_latin_1_string("#", 1);
  func__30_102 = create_function(entry__30_102, 1);
  string__30_108 = from_latin_1_string(" ", 1);
  func__30_107 = create_function(entry__30_107, 0);
  string__30_119 = from_latin_1_string("colspan", 7);
  string__30_126 = from_latin_1_string("#index", 6);
  string__30_128 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__30_143 = from_latin_1_string("function", 8);
  func__30_142 = create_function(entry__30_142, 0);
  string__30_145 = from_latin_1_string("inline-C function", 17);
  func__30_144 = create_function(entry__30_144, 0);
  string__30_147 = from_latin_1_string("polymorphic function", 20);
  func__30_146 = create_function(entry__30_146, 0);
  string__30_149 = from_latin_1_string("unique item", 11);
  func__30_148 = create_function(entry__30_148, 0);
  func__30_150 = create_function(entry__30_150, 0);
  func__30_151 = create_function(entry__30_151, 0);
  string__30_157 = from_latin_1_string(" (", 2);
  string__30_167 = from_latin_1_string("align", 5);
  string__30_168 = from_latin_1_string("right", 5);
  string__30_178 = from_latin_1_string("remark", 6);
  func__30_111 = create_function(entry__30_111, 0);
  func__30_96 = create_function(entry__30_96, 0);
  string__30_190 = from_latin_1_string("/", 1);
  func__30_181 = create_function(entry__30_181, 2);
  string__30_193 = from_latin_1_string("html/topic_index.html", 21);
  string__30_201 = from_latin_1_string("_", 1);
  func__30_199 = create_function(entry__30_199, 2);
  func__30_198 = create_function(entry__30_198, 0);
  func__30_194 = create_function(entry__30_194, 0);
  func__30_219 = create_function(entry__30_219, 1);
  func__30_209 = create_function(entry__30_209, 2);
  string__30_226 = from_latin_1_string("html/index.html", 15);
  string__30_228 = from_latin_1_string("Simplicity", 10);
  func__30_230 = create_function(entry__30_230, 0);
  func__30_233 = create_function(entry__30_233, 0);
  func__30_236 = create_function(entry__30_236, 0);
  func__30_239 = create_function(entry__30_239, 0);
  func__30_227 = create_function(entry__30_227, 0);
  func__30_1 = create_function(entry__30_1, 1);
  string__56_1 = from_latin_1_string("Topics", 6);
  string__56_2 = from_latin_1_string("Topic", 5);
  string__57_1 = from_latin_1_string("Example", 7);
  string__57_2 = from_latin_1_string("Output", 6);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__extractor(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  unique__9_1 = register_unique_item("BORING");
  assign_value(&var._BORING, unique__9_1);
  unique__10_1 = register_unique_item("TYPE");
  assign_value(&var._TYPE, unique__10_1);
  unique__11_1 = register_unique_item("FUNCTION");
  assign_value(&var._FUNCTION, unique__11_1);
  unique__12_1 = register_unique_item("INLINE_C_FUNCTION");
  assign_value(&var._INLINE_C_FUNCTION, unique__12_1);
  unique__13_1 = register_unique_item("UNIQUE_ITEM");
  assign_value(&var._UNIQUE_ITEM, unique__13_1);
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
  use_read_only(NULL, "dup", &get__dup, &get_value_or_future__dup);
  use_read_only(NULL, "emit", &get__emit, &get_value_or_future__emit);
  use_read_only(NULL, "empty_insert_order_set", &get__empty_insert_order_set, &get_value_or_future__empty_insert_order_set);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_key_order_set", &get__empty_key_order_set, &get_value_or_future__empty_key_order_set);
  use_read_only(NULL, "empty_key_order_table", &get__empty_key_order_table, &get_value_or_future__empty_key_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "ewrite", &get__ewrite, &get_value_or_future__ewrite);
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
  use_read_only(NULL, "is_a_body", &get__is_a_body, &get_value_or_future__is_a_body);
  use_read_only(NULL, "is_a_c_body", &get__is_a_c_body, &get_value_or_future__is_a_c_body);
  use_read_only(NULL, "is_a_constant", &get__is_a_constant, &get_value_or_future__is_a_constant);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_read_only(NULL, "is_a_directory", &get__is_a_directory, &get_value_or_future__is_a_directory);
  use_read_only(NULL, "is_a_polymorphic_function_constant", &get__is_a_polymorphic_function_constant, &get_value_or_future__is_a_polymorphic_function_constant);
  use_read_only(NULL, "is_a_remark", &get__is_a_remark, &get_value_or_future__is_a_remark);
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
  assign_variable(&var._create_page, &func__16_1);
  assign_variable(&var._extract_documentation_from_file, &func__18_1);
  assign_variable(&var._extract_documentation_from_directory, &func__19_1);
  assign_variable(&var._resolved_name, &func__20_1);
  assign_variable(&var._add_derived_type, &func__21_1);
  assign_variable(&var._mangled, &func__22_1);
  assign_variable(&var._ordered_name, &func__23_1);
  assign_variable(&var._link_bar, &func__24_1);
  assign_variable(&var._resolve_reference, &func__25_1);
  assign_variable(&var._to_paragraphs, &func__28_1);
  assign_variable(&var._create_info_page, &func__29_1);
  assign_variable(&var.sim2c__extract_documentation, &func__30_1);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__extractor(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__extractor);
}
