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
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT NODE *register_unique_item(const char *name);
IMPORT void assign_value(NODE **dest, NODE *val);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
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

#define ENCODE_ADDRESS(addr) ((void *)(FIRST_INVALID_ADDRESS|(uintptr_t)(addr) >> 2))
#define DECODE_ADDRESS(addr) ((void *)((uintptr_t)(addr) << 2))
#define IS_AN_INVALID_ADDRESS(addr) ((void *)(addr) >= (void *)FIRST_INVALID_ADDRESS)

#define IS_COLLECTED(addr) (((void *)(addr)) >= coll_node_buf && ((void *)(addr)) < coll_node_buf_end)
#define IS_OLD(addr) false
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
static NODE *temp__1;
static NODE *temp__2;
static NODE *temp__3;
static NODE *temp__4;
static NODE *temp__5;
static NODE *temp__6;
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
static NODE *string__19_10;
static void cont__19_11(void);
static NODE *func__19_12;
static void entry__19_12(void);
static FRAME_INFO frame__19_12 = {1, {"name"}};
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
static NODE *string__20_22;
static void cont__20_23(void);
static void cont__20_24(void);
static NODE *string__20_25;
static void cont__20_26(void);
static NODE *func__21_1;
static void entry__21_1(void);
static FRAME_INFO frame__21_1 = {4, {"base", "name", "ibase", "definition"}};
static NODE *string__21_2;
static void cont__21_3(void);
static NODE *string__21_4;
static void cont__21_5(void);
static void cont__21_6(void);
static void cont__21_7(void);
static void cont__21_8(void);
static NODE *func__21_9;
static void entry__21_9(void);
static FRAME_INFO frame__21_9 = {3, {"definition", "name", "ibase"}};
static void cont__21_10(void);
static void cont__21_11(void);
static void cont__21_12(void);
static void cont__21_13(void);
static NODE *func__21_14;
static void entry__21_14(void);
static FRAME_INFO frame__21_14 = {3, {"definition", "ibase", "base_of_base"}};
static void cont__21_15(void);
static void cont__21_16(void);
static NODE *func__21_17;
static void entry__21_17(void);
static FRAME_INFO frame__21_17 = {2, {"base_of_base", "ibase"}};
static void cont__21_18(void);
static void cont__21_19(void);
static NODE *func__22_1;
static void entry__22_1(void);
static FRAME_INFO frame__22_1 = {1, {"name"}};
static NODE *string__22_2;
static NODE *string__22_3;
static void cont__22_4(void);
static NODE *string__22_5;
static void cont__22_6(void);
static void cont__22_7(void);
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
static NODE *string__24_11;
static void cont__24_12(void);
static NODE *string__24_13;
static void cont__24_14(void);
static NODE *string__24_15;
static void cont__24_16(void);
static NODE *string__24_17;
static NODE *string__24_18;
static void cont__24_19(void);
static NODE *string__24_20;
static void cont__24_21(void);
static NODE *string__24_22;
static void cont__24_23(void);
static NODE *string__24_24;
static NODE *string__24_25;
static void cont__24_26(void);
static NODE *string__24_27;
static void cont__24_28(void);
static NODE *string__24_29;
static void cont__24_30(void);
static NODE *string__24_31;
static NODE *string__24_32;
static void cont__24_33(void);
static NODE *string__24_34;
static NODE *func__25_1;
static void entry__25_1(void);
static FRAME_INFO frame__25_1 = {1, {"reference"}};
static void cont__25_2(void);
static NODE *func__25_3;
static void entry__25_3(void);
static FRAME_INFO frame__25_3 = {3, {"reference", "type_name", "method_name"}};
static void cont__25_4(void);
static void cont__25_5(void);
static NODE *string__25_6;
static void cont__25_7(void);
static NODE *func__25_8;
static void entry__25_8(void);
static FRAME_INFO frame__25_8 = {1, {"type_name"}};
static NODE *string__25_9;
static void cont__25_10(void);
static void cont__25_11(void);
static NODE *string__25_12;
static void cont__25_13(void);
static NODE *func__25_14;
static void entry__25_14(void);
static FRAME_INFO frame__25_14 = {1, {"method_name"}};
static NODE *string__25_15;
static void cont__25_16(void);
static void cont__25_17(void);
static void cont__25_18(void);
static NODE *func__25_19;
static void entry__25_19(void);
static FRAME_INFO frame__25_19 = {1, {"reference"}};
static NODE *string__25_20;
static void cont__25_21(void);
static NODE *func__25_22;
static void entry__25_22(void);
static FRAME_INFO frame__25_22 = {1, {"reference"}};
static NODE *string__25_23;
static void cont__25_24(void);
static void cont__25_25(void);
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
static NODE *string__29_19;
static void cont__29_20(void);
static NODE *func__29_21;
static void entry__29_21(void);
static FRAME_INFO frame__29_21 = {1, {"function_name"}};
static void cont__29_22(void);
static void cont__29_23(void);
static void cont__29_24(void);
static NODE *func__29_25;
static void entry__29_25(void);
static FRAME_INFO frame__29_25 = {10, {"remark_lines", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions", "paragraphs"}};
static void cont__29_26(void);
static NODE *func__29_27;
static void entry__29_27(void);
static FRAME_INFO frame__29_27 = {9, {"paragraph", "parameters", "return_values", "references", "function_name", "examples", "technical_details", "short_description", "descriptions"}};
static NODE *func__29_28;
static void entry__29_28(void);
static FRAME_INFO frame__29_28 = {2, {"paragraph", "parameters"}};
static void cont__29_29(void);
static NODE *string__29_30;
static void cont__29_31(void);
static void cont__29_32(void);
static NODE *func__29_33;
static void entry__29_33(void);
static FRAME_INFO frame__29_33 = {4, {"paragraph", "parameters", "parameter", "description"}};
static void cont__29_34(void);
static NODE *func__29_35;
static void entry__29_35(void);
static FRAME_INFO frame__29_35 = {1, {"parameter"}};
static void cont__29_36(void);
static NODE *func__29_37;
static void entry__29_37(void);
static FRAME_INFO frame__29_37 = {1, {"parameter"}};
static void cont__29_38(void);
static void cont__29_39(void);
static NODE *string__29_40;
static void cont__29_41(void);
static NODE *func__29_42;
static void entry__29_42(void);
static FRAME_INFO frame__29_42 = {1, {"parameter"}};
static void cont__29_43(void);
static NODE *func__29_44;
static void entry__29_44(void);
static FRAME_INFO frame__29_44 = {1, {"parameter"}};
static void cont__29_45(void);
static void cont__29_46(void);
static NODE *string__29_47;
static void cont__29_48(void);
static NODE *func__29_49;
static void entry__29_49(void);
static FRAME_INFO frame__29_49 = {1, {"parameter"}};
static void cont__29_50(void);
static NODE *func__29_51;
static void entry__29_51(void);
static FRAME_INFO frame__29_51 = {1, {"parameter"}};
static void cont__29_52(void);
static void cont__29_53(void);
static void cont__29_54(void);
static void cont__29_55(void);
static NODE *string__29_56;
static NODE *string__29_57;
static void cont__29_58(void);
static void cont__29_59(void);
static void cont__29_60(void);
static void cont__29_61(void);
static void cont__29_62(void);
static void cont__29_63(void);
static NODE *func__29_64;
static void entry__29_64(void);
static FRAME_INFO frame__29_64 = {2, {"paragraph", "return_values"}};
static void cont__29_65(void);
static NODE *string__29_66;
static void cont__29_67(void);
static void cont__29_68(void);
static NODE *func__29_69;
static void entry__29_69(void);
static FRAME_INFO frame__29_69 = {4, {"paragraph", "return_values", "return_value", "description"}};
static void cont__29_70(void);
static NODE *func__29_71;
static void entry__29_71(void);
static FRAME_INFO frame__29_71 = {1, {"return_value"}};
static void cont__29_72(void);
static NODE *func__29_73;
static void entry__29_73(void);
static FRAME_INFO frame__29_73 = {1, {"return_value"}};
static void cont__29_74(void);
static void cont__29_75(void);
static NODE *string__29_76;
static void cont__29_77(void);
static NODE *func__29_78;
static void entry__29_78(void);
static FRAME_INFO frame__29_78 = {1, {"return_value"}};
static void cont__29_79(void);
static NODE *func__29_80;
static void entry__29_80(void);
static FRAME_INFO frame__29_80 = {1, {"return_value"}};
static void cont__29_81(void);
static void cont__29_82(void);
static NODE *string__29_83;
static void cont__29_84(void);
static void cont__29_85(void);
static void cont__29_86(void);
static void cont__29_87(void);
static void cont__29_88(void);
static void cont__29_89(void);
static NODE *func__29_90;
static void entry__29_90(void);
static FRAME_INFO frame__29_90 = {2, {"paragraph", "references"}};
static NODE *string__29_91;
static void cont__29_92(void);
static NODE *func__29_93;
static void entry__29_93(void);
static FRAME_INFO frame__29_93 = {2, {"paragraph", "references"}};
static void cont__29_94(void);
static void cont__29_95(void);
static NODE *func__29_96;
static void entry__29_96(void);
static FRAME_INFO frame__29_96 = {2, {"reference", "references"}};
static void cont__29_97(void);
static void cont__29_98(void);
static NODE *func__29_99;
static void entry__29_99(void);
static FRAME_INFO frame__29_99 = {2, {"paragraph", "function_name"}};
static void cont__29_100(void);
static NODE *func__29_101;
static void entry__29_101(void);
static FRAME_INFO frame__29_101 = {2, {"paragraph", "function_name"}};
static void cont__29_102(void);
static void cont__29_103(void);
static NODE *func__29_104;
static void entry__29_104(void);
static FRAME_INFO frame__29_104 = {3, {"topic", "function_name", "topic_contents"}};
static void cont__29_105(void);
static void cont__29_106(void);
static void cont__29_107(void);
static void cont__29_108(void);
static void cont__29_109(void);
static NODE *func__29_110;
static void entry__29_110(void);
static FRAME_INFO frame__29_110 = {2, {"paragraph", "examples"}};
static void cont__29_111(void);
static NODE *func__29_112;
static void entry__29_112(void);
static FRAME_INFO frame__29_112 = {4, {"paragraph", "examples", "title", "text"}};
static void cont__29_113(void);
static void cont__29_114(void);
static void cont__29_115(void);
static void cont__29_116(void);
static void cont__29_117(void);
static void cont__29_118(void);
static NODE *func__29_119;
static void entry__29_119(void);
static FRAME_INFO frame__29_119 = {2, {"paragraph", "technical_details"}};
static NODE *string__29_120;
static void cont__29_121(void);
static NODE *func__29_122;
static void entry__29_122(void);
static FRAME_INFO frame__29_122 = {3, {"paragraph", "technical_details", "detail"}};
static void cont__29_123(void);
static void cont__29_124(void);
static void cont__29_125(void);
static NODE *func__29_126;
static void entry__29_126(void);
static FRAME_INFO frame__29_126 = {1, {"technical_details"}};
static NODE *func__29_127;
static void entry__29_127(void);
static FRAME_INFO frame__29_127 = {2, {"technical_details", "detail"}};
static void cont__29_128(void);
static NODE *func__29_129;
static void entry__29_129(void);
static FRAME_INFO frame__29_129 = {4, {"paragraph", "short_description", "technical_details", "descriptions"}};
static void cont__29_130(void);
static void cont__29_131(void);
static void cont__29_132(void);
static NODE *func__29_133;
static void entry__29_133(void);
static FRAME_INFO frame__29_133 = {1, {"reference"}};
static void cont__29_134(void);
static void cont__29_135(void);
static void cont__29_136(void);
static void cont__29_137(void);
static NODE *string__29_138;
static NODE *string__29_139;
static NODE *string__29_140;
static void cont__29_141(void);
static void cont__29_142(void);
static void cont__29_143(void);
static void cont__29_144(void);
static NODE *func__29_145;
static void entry__29_145(void);
static FRAME_INFO frame__29_145 = {3, {"technical_details", "paragraph", "descriptions"}};
static void cont__29_146(void);
static NODE *func__29_147;
static void entry__29_147(void);
static FRAME_INFO frame__29_147 = {2, {"technical_details", "paragraph"}};
static void cont__29_148(void);
static NODE *func__29_149;
static void entry__29_149(void);
static FRAME_INFO frame__29_149 = {2, {"descriptions", "paragraph"}};
static void cont__29_150(void);
static NODE *func__29_151;
static void entry__29_151(void);
static FRAME_INFO frame__29_151 = {2, {"short_description", "paragraph"}};
static void cont__29_152(void);
static void cont__29_153(void);
static void cont__29_154(void);
static NODE *func__29_155;
static void entry__29_155(void);
static FRAME_INFO frame__29_155 = {2, {"info", "parameters"}};
static void cont__29_156(void);
static NODE *func__29_157;
static void entry__29_157(void);
static FRAME_INFO frame__29_157 = {2, {"parameter", "parameters"}};
static void cont__29_158(void);
static void cont__29_159(void);
static NODE *func__29_160;
static void entry__29_160(void);
static FRAME_INFO frame__29_160 = {4, {"parameter", "parameters", "name", "description"}};
static void cont__29_161(void);
static void cont__29_162(void);
static void cont__29_163(void);
static NODE *func__29_164;
static void entry__29_164(void);
static FRAME_INFO frame__29_164 = {2, {"parameter", "name"}};
static void cont__29_165(void);
static NODE *func__29_166;
static void entry__29_166(void);
static FRAME_INFO frame__29_166 = {2, {"parameter", "name"}};
static void cont__29_167(void);
static void cont__29_168(void);
static NODE *func__29_169;
static void entry__29_169(void);
static FRAME_INFO frame__29_169 = {2, {"name", "parameter"}};
static void cont__29_170(void);
static void cont__29_171(void);
static NODE *string__29_172;
static NODE *string__29_173;
static void cont__29_174(void);
static NODE *func__29_175;
static void entry__29_175(void);
static FRAME_INFO frame__29_175 = {1, {"name"}};
static NODE *string__29_176;
static void cont__29_177(void);
static NODE *func__29_178;
static void entry__29_178(void);
static FRAME_INFO frame__29_178 = {2, {"parameter", "name"}};
static void cont__29_179(void);
static NODE *func__29_180;
static void entry__29_180(void);
static FRAME_INFO frame__29_180 = {1, {"name"}};
static NODE *string__29_181;
static void cont__29_182(void);
static void cont__29_183(void);
static void cont__29_184(void);
static void cont__29_185(void);
static void cont__29_186(void);
static NODE *func__29_187;
static void entry__29_187(void);
static FRAME_INFO frame__29_187 = {1, {"parameter"}};
static void cont__29_188(void);
static void cont__29_189(void);
static void cont__29_190(void);
static NODE *func__29_191;
static void entry__29_191(void);
static FRAME_INFO frame__29_191 = {0, {}};
static void cont__29_192(void);
static void cont__29_193(void);
static void cont__29_194(void);
static NODE *func__29_195;
static void entry__29_195(void);
static FRAME_INFO frame__29_195 = {0, {}};
static void cont__29_196(void);
static void cont__29_197(void);
static NODE *func__29_198;
static void entry__29_198(void);
static FRAME_INFO frame__29_198 = {1, {"short_description"}};
static void cont__29_199(void);
static void cont__29_200(void);
static NODE *func__29_201;
static void entry__29_201(void);
static FRAME_INFO frame__29_201 = {1, {"parameters"}};
static NODE *string__29_202;
static void cont__29_203(void);
static NODE *func__29_204;
static void entry__29_204(void);
static FRAME_INFO frame__29_204 = {1, {"parameters"}};
static NODE *func__29_205;
static void entry__29_205(void);
static FRAME_INFO frame__29_205 = {1, {"parameter"}};
static void cont__29_206(void);
static void cont__29_207(void);
static NODE *func__29_208;
static void entry__29_208(void);
static FRAME_INFO frame__29_208 = {1, {"parameter"}};
static void cont__29_209(void);
static void cont__29_210(void);
static void cont__29_211(void);
static NODE *func__29_212;
static void entry__29_212(void);
static FRAME_INFO frame__29_212 = {1, {"return_values"}};
static NODE *string__29_213;
static void cont__29_214(void);
static NODE *func__29_215;
static void entry__29_215(void);
static FRAME_INFO frame__29_215 = {1, {"return_values"}};
static NODE *func__29_216;
static void entry__29_216(void);
static FRAME_INFO frame__29_216 = {1, {"return_value"}};
static void cont__29_217(void);
static void cont__29_218(void);
static NODE *func__29_219;
static void entry__29_219(void);
static FRAME_INFO frame__29_219 = {1, {"return_value"}};
static void cont__29_220(void);
static void cont__29_221(void);
static void cont__29_222(void);
static NODE *func__29_223;
static void entry__29_223(void);
static FRAME_INFO frame__29_223 = {1, {"descriptions"}};
static NODE *string__29_224;
static void cont__29_225(void);
static NODE *func__29_226;
static void entry__29_226(void);
static FRAME_INFO frame__29_226 = {1, {"description"}};
static void cont__29_227(void);
static void cont__29_228(void);
static NODE *func__29_229;
static void entry__29_229(void);
static FRAME_INFO frame__29_229 = {1, {"technical_details"}};
static NODE *string__29_230;
static void cont__29_231(void);
static NODE *func__29_232;
static void entry__29_232(void);
static FRAME_INFO frame__29_232 = {1, {"detail"}};
static void cont__29_233(void);
static void cont__29_234(void);
static NODE *func__29_235;
static void entry__29_235(void);
static FRAME_INFO frame__29_235 = {1, {"references"}};
static NODE *string__29_236;
static void cont__29_237(void);
static NODE *func__29_238;
static void entry__29_238(void);
static FRAME_INFO frame__29_238 = {1, {"references"}};
static NODE *func__29_239;
static void entry__29_239(void);
static FRAME_INFO frame__29_239 = {1, {"reference"}};
static void cont__29_240(void);
static void cont__29_241(void);
static NODE *string__29_242;
static void cont__29_243(void);
static NODE *string__29_244;
static void cont__29_245(void);
static void cont__29_246(void);
static void cont__29_247(void);
static void cont__29_248(void);
static void cont__29_249(void);
static NODE *func__29_250;
static void entry__29_250(void);
static FRAME_INFO frame__29_250 = {2, {"info", "function_name"}};
static NODE *string__29_251;
static void cont__29_252(void);
static NODE *func__29_253;
static void entry__29_253(void);
static FRAME_INFO frame__29_253 = {2, {"info", "function_name"}};
static void cont__29_254(void);
static NODE *func__29_255;
static void entry__29_255(void);
static FRAME_INFO frame__29_255 = {3, {"name", "function_name", "method"}};
static void cont__29_256(void);
static NODE *func__29_257;
static void entry__29_257(void);
static FRAME_INFO frame__29_257 = {2, {"name", "method"}};
static NODE *func__29_258;
static void entry__29_258(void);
static FRAME_INFO frame__29_258 = {1, {"name"}};
static void cont__29_259(void);
static NODE *string__29_260;
static void cont__29_261(void);
static NODE *string__29_262;
static void cont__29_263(void);
static void cont__29_264(void);
static NODE *string__29_265;
static void cont__29_266(void);
static NODE *func__29_267;
static void entry__29_267(void);
static FRAME_INFO frame__29_267 = {1, {"method"}};
static void cont__29_268(void);
static NODE *string__29_269;
static void cont__29_270(void);
static NODE *string__29_271;
static void cont__29_272(void);
static void cont__29_273(void);
static void cont__29_274(void);
static void cont__29_275(void);
static NODE *func__29_276;
static void entry__29_276(void);
static FRAME_INFO frame__29_276 = {2, {"info", "function_name"}};
static NODE *string__29_277;
static void cont__29_278(void);
static NODE *func__29_279;
static void entry__29_279(void);
static FRAME_INFO frame__29_279 = {2, {"info", "function_name"}};
static void cont__29_280(void);
static NODE *func__29_281;
static void entry__29_281(void);
static FRAME_INFO frame__29_281 = {3, {"method_name", "method_info", "function_name"}};
static NODE *func__29_282;
static void entry__29_282(void);
static FRAME_INFO frame__29_282 = {2, {"method_name", "function_name"}};
static NODE *func__29_283;
static void entry__29_283(void);
static FRAME_INFO frame__29_283 = {1, {"method_name"}};
static void cont__29_284(void);
static NODE *string__29_285;
static void cont__29_286(void);
static NODE *string__29_287;
static void cont__29_288(void);
static void cont__29_289(void);
static NODE *string__29_290;
static void cont__29_291(void);
static NODE *func__29_292;
static void entry__29_292(void);
static FRAME_INFO frame__29_292 = {2, {"function_name", "method_name"}};
static void cont__29_293(void);
static void cont__29_294(void);
static NODE *string__29_295;
static NODE *string__29_296;
static void cont__29_297(void);
static NODE *string__29_298;
static void cont__29_299(void);
static void cont__29_300(void);
static void cont__29_301(void);
static NODE *string__29_302;
static void cont__29_303(void);
static NODE *func__29_304;
static void entry__29_304(void);
static FRAME_INFO frame__29_304 = {4, {"example", "function_basename", "title", "text"}};
static void cont__29_305(void);
static void cont__29_306(void);
static void cont__29_307(void);
static void cont__29_308(void);
static void cont__29_309(void);
static NODE *string__29_310;
static void cont__29_311(void);
static NODE *func__29_312;
static void entry__29_312(void);
static FRAME_INFO frame__29_312 = {2, {"text", "function_basename"}};
static void cont__29_313(void);
static void cont__29_314(void);
static void cont__29_315(void);
static void cont__29_316(void);
static NODE *func__29_317;
static void entry__29_317(void);
static FRAME_INFO frame__29_317 = {1, {"string_literal"}};
static void cont__29_318(void);
static NODE *string__29_319;
static NODE *string__29_320;
static void cont__29_321(void);
static void cont__29_322(void);
static void cont__29_323(void);
static void cont__29_324(void);
static NODE *string__29_325;
static NODE *string__29_326;
static void cont__29_327(void);
static void cont__29_328(void);
static void cont__29_329(void);
static NODE *string__29_330;
static NODE *string__29_331;
static void cont__29_332(void);
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
static NODE *string__30_7;
static void cont__30_8(void);
static NODE *func__30_9;
static void entry__30_9(void);
static FRAME_INFO frame__30_9 = {2, {"capture", "reference"}};
static void cont__30_10(void);
static void cont__30_11(void);
static void cont__30_12(void);
static void cont__30_13(void);
static NODE *string__30_14;
static NODE *string__30_15;
static NODE *string__30_16;
static void cont__30_17(void);
static void cont__30_18(void);
static void cont__30_19(void);
static void cont__30_20(void);
static void cont__30_21(void);
static void cont__30_22(void);
static void cont__30_23(void);
static NODE *func__30_24;
static void entry__30_24(void);
static FRAME_INFO frame__30_24 = {2, {"name", "info"}};
static void cont__30_25(void);
static void cont__30_26(void);
static NODE *func__30_27;
static void entry__30_27(void);
static FRAME_INFO frame__30_27 = {4, {"info", "name", "base", "methods"}};
static void cont__30_28(void);
static void cont__30_29(void);
static NODE *func__30_30;
static void entry__30_30(void);
static FRAME_INFO frame__30_30 = {2, {"base", "name"}};
static void cont__30_31(void);
static void cont__30_32(void);
static NODE *func__30_33;
static void entry__30_33(void);
static FRAME_INFO frame__30_33 = {4, {"method_name", "method_info", "info", "methods"}};
static NODE *string__30_34;
static void cont__30_35(void);
static NODE *func__30_36;
static void entry__30_36(void);
static FRAME_INFO frame__30_36 = {2, {"method_name", "method_info"}};
static void cont__30_37(void);
static void cont__30_38(void);
static void cont__30_39(void);
static void cont__30_40(void);
static void cont__30_41(void);
static NODE *func__30_42;
static void entry__30_42(void);
static FRAME_INFO frame__30_42 = {3, {"method_name", "info", "oname"}};
static NODE *string__30_43;
static void cont__30_44(void);
static NODE *string__30_45;
static void cont__30_46(void);
static void cont__30_47(void);
static void cont__30_48(void);
static void cont__30_49(void);
static void cont__30_50(void);
static void cont__30_51(void);
static void cont__30_52(void);
static void cont__30_53(void);
static void cont__30_54(void);
static void cont__30_55(void);
static void cont__30_56(void);
static void cont__30_57(void);
static void cont__30_58(void);
static NODE *string__30_59;
static NODE *func__30_60;
static void entry__30_60(void);
static FRAME_INFO frame__30_60 = {1, {"print_type_info"}};
static NODE *func__30_61;
static void entry__30_61(void);
static FRAME_INFO frame__30_61 = {3, {"info", "indent", "print_type_info"}};
static NODE *func__30_62;
static void entry__30_62(void);
static FRAME_INFO frame__30_62 = {5, {"info", "indent", "print_type_info", "qname", "remark_lines"}};
static void cont__30_63(void);
static void cont__30_64(void);
static void cont__30_65(void);
static NODE *func__30_66;
static void entry__30_66(void);
static FRAME_INFO frame__30_66 = {2, {"indent", "qname"}};
static NODE *func__30_67;
static void entry__30_67(void);
static FRAME_INFO frame__30_67 = {2, {"indent", "qname"}};
static NODE *string__30_68;
static void cont__30_69(void);
static void cont__30_70(void);
static void cont__30_71(void);
static NODE *string__30_72;
static void cont__30_73(void);
static NODE *string__30_74;
static void cont__30_75(void);
static void cont__30_76(void);
static void cont__30_77(void);
static NODE *func__30_78;
static void entry__30_78(void);
static FRAME_INFO frame__30_78 = {1, {"remark_lines"}};
static void cont__30_79(void);
static void cont__30_80(void);
static void cont__30_81(void);
static NODE *func__30_82;
static void entry__30_82(void);
static FRAME_INFO frame__30_82 = {1, {"remark_lines"}};
static void cont__30_83(void);
static void cont__30_84(void);
static void cont__30_85(void);
static void cont__30_86(void);
static NODE *func__30_87;
static void entry__30_87(void);
static FRAME_INFO frame__30_87 = {3, {"name", "print_type_info", "indent"}};
static void cont__30_88(void);
static void cont__30_89(void);
static void cont__30_90(void);
static NODE *string__30_91;
static void cont__30_92(void);
static NODE *func__30_93;
static void entry__30_93(void);
static FRAME_INFO frame__30_93 = {1, {"print_type_info"}};
static NODE *func__30_94;
static void entry__30_94(void);
static FRAME_INFO frame__30_94 = {3, {"base", "info", "print_type_info"}};
static void cont__30_95(void);
static void cont__30_96(void);
static NODE *func__30_97;
static void entry__30_97(void);
static FRAME_INFO frame__30_97 = {1, {"info"}};
static void cont__30_98(void);
static void cont__30_99(void);
static void cont__30_100(void);
static NODE *func__30_101;
static void entry__30_101(void);
static FRAME_INFO frame__30_101 = {2, {"print_type_info", "info"}};
static void cont__30_102(void);
static NODE *string__30_103;
static NODE *func__30_104;
static void entry__30_104(void);
static FRAME_INFO frame__30_104 = {0, {}};
static void cont__30_105(void);
static NODE *string__30_106;
static NODE *string__30_107;
static void cont__30_108(void);
static NODE *string__30_109;
static void cont__30_110(void);
static NODE *func__30_111;
static void entry__30_111(void);
static FRAME_INFO frame__30_111 = {1, {"letter"}};
static NODE *string__30_112;
static void cont__30_113(void);
static NODE *string__30_114;
static void cont__30_115(void);
static void cont__30_116(void);
static NODE *func__30_117;
static void entry__30_117(void);
static FRAME_INFO frame__30_117 = {0, {}};
static NODE *string__30_118;
static void cont__30_119(void);
static void cont__30_120(void);
static NODE *func__30_121;
static void entry__30_121(void);
static FRAME_INFO frame__30_121 = {1, {"letter"}};
static NODE *func__30_122;
static void entry__30_122(void);
static FRAME_INFO frame__30_122 = {7, {"iname", "info", "letter", "remark", "name", "remark_lines", "kind_info"}};
static void cont__30_123(void);
static void cont__30_124(void);
static void cont__30_125(void);
static NODE *func__30_126;
static void entry__30_126(void);
static FRAME_INFO frame__30_126 = {2, {"letter", "iname"}};
static void cont__30_127(void);
static NODE *func__30_128;
static void entry__30_128(void);
static FRAME_INFO frame__30_128 = {1, {"letter"}};
static NODE *string__30_129;
static void cont__30_130(void);
static NODE *func__30_131;
static void entry__30_131(void);
static FRAME_INFO frame__30_131 = {1, {"letter"}};
static NODE *string__30_132;
static void cont__30_133(void);
static NODE *func__30_134;
static void entry__30_134(void);
static FRAME_INFO frame__30_134 = {1, {"letter"}};
static void cont__30_135(void);
static void cont__30_136(void);
static NODE *string__30_137;
static NODE *string__30_138;
static void cont__30_139(void);
static NODE *string__30_140;
static void cont__30_141(void);
static void cont__30_142(void);
static void cont__30_143(void);
static void cont__30_144(void);
static NODE *func__30_145;
static void entry__30_145(void);
static FRAME_INFO frame__30_145 = {1, {"remark_lines"}};
static void cont__30_146(void);
static void cont__30_147(void);
static void cont__30_148(void);
static NODE *func__30_149;
static void entry__30_149(void);
static FRAME_INFO frame__30_149 = {2, {"remark", "remark_lines"}};
static void cont__30_150(void);
static void cont__30_151(void);
static void cont__30_152(void);
static void cont__30_153(void);
static NODE *func__30_154;
static void entry__30_154(void);
static FRAME_INFO frame__30_154 = {0, {}};
static NODE *string__30_155;
static NODE *func__30_156;
static void entry__30_156(void);
static FRAME_INFO frame__30_156 = {0, {}};
static NODE *string__30_157;
static NODE *func__30_158;
static void entry__30_158(void);
static FRAME_INFO frame__30_158 = {0, {}};
static NODE *string__30_159;
static NODE *func__30_160;
static void entry__30_160(void);
static FRAME_INFO frame__30_160 = {0, {}};
static NODE *string__30_161;
static NODE *func__30_162;
static void entry__30_162(void);
static FRAME_INFO frame__30_162 = {0, {}};
static NODE *string__30_163;
static NODE *func__30_164;
static void entry__30_164(void);
static FRAME_INFO frame__30_164 = {0, {}};
static void cont__30_165(void);
static void cont__30_166(void);
static NODE *func__30_167;
static void entry__30_167(void);
static FRAME_INFO frame__30_167 = {2, {"remark", "kind_info"}};
static void cont__30_168(void);
static NODE *func__30_169;
static void entry__30_169(void);
static FRAME_INFO frame__30_169 = {2, {"remark", "kind_info"}};
static NODE *string__30_170;
static NODE *string__30_171;
static void cont__30_172(void);
static NODE *func__30_173;
static void entry__30_173(void);
static FRAME_INFO frame__30_173 = {2, {"remark", "kind_info"}};
static void cont__30_174(void);
static void cont__30_175(void);
static NODE *func__30_176;
static void entry__30_176(void);
static FRAME_INFO frame__30_176 = {1, {"name"}};
static void cont__30_177(void);
static void cont__30_178(void);
static NODE *func__30_179;
static void entry__30_179(void);
static FRAME_INFO frame__30_179 = {2, {"name", "remark"}};
static NODE *func__30_180;
static void entry__30_180(void);
static FRAME_INFO frame__30_180 = {2, {"name", "remark"}};
static NODE *string__30_181;
static NODE *string__30_182;
static void cont__30_183(void);
static NODE *string__30_184;
static void cont__30_185(void);
static void cont__30_186(void);
static NODE *func__30_187;
static void entry__30_187(void);
static FRAME_INFO frame__30_187 = {1, {"name"}};
static void cont__30_188(void);
static NODE *string__30_189;
static void cont__30_190(void);
static NODE *string__30_191;
static void cont__30_192(void);
static NODE *string__30_193;
static void cont__30_194(void);
static void cont__30_195(void);
static NODE *string__30_196;
static NODE *string__30_197;
static void cont__30_198(void);
static void cont__30_199(void);
static NODE *func__30_200;
static void entry__30_200(void);
static FRAME_INFO frame__30_200 = {3, {"iname", "info", "name"}};
static void cont__30_201(void);
static void cont__30_202(void);
static NODE *func__30_203;
static void entry__30_203(void);
static FRAME_INFO frame__30_203 = {2, {"name", "info"}};
static void cont__30_204(void);
static void cont__30_205(void);
static NODE *func__30_206;
static void entry__30_206(void);
static FRAME_INFO frame__30_206 = {2, {"info", "name"}};
static void cont__30_207(void);
static NODE *func__30_208;
static void entry__30_208(void);
static FRAME_INFO frame__30_208 = {3, {"method_name", "method_info", "name"}};
static NODE *string__30_209;
static void cont__30_210(void);
static void cont__30_211(void);
static NODE *string__30_212;
static NODE *func__30_213;
static void entry__30_213(void);
static FRAME_INFO frame__30_213 = {0, {}};
static void cont__30_214(void);
static NODE *string__30_215;
static NODE *string__30_216;
static void cont__30_217(void);
static NODE *string__30_218;
static void cont__30_219(void);
static NODE *func__30_220;
static void entry__30_220(void);
static FRAME_INFO frame__30_220 = {0, {}};
static NODE *func__30_221;
static void entry__30_221(void);
static FRAME_INFO frame__30_221 = {3, {"topic", "references", "filename"}};
static void cont__30_222(void);
static NODE *string__30_223;
static void cont__30_224(void);
static void cont__30_225(void);
static NODE *string__30_226;
static void cont__30_227(void);
static NODE *func__30_228;
static void entry__30_228(void);
static FRAME_INFO frame__30_228 = {2, {"filename", "topic"}};
static NODE *func__30_229;
static void entry__30_229(void);
static FRAME_INFO frame__30_229 = {2, {"filename", "topic"}};
static NODE *string__30_230;
static void cont__30_231(void);
static void cont__30_232(void);
static NODE *func__30_233;
static void entry__30_233(void);
static FRAME_INFO frame__30_233 = {3, {"topic", "references", "filename"}};
static void cont__30_234(void);
static NODE *string__30_235;
static void cont__30_236(void);
static void cont__30_237(void);
static NODE *string__30_238;
static NODE *string__30_239;
static void cont__30_240(void);
static NODE *func__30_241;
static void entry__30_241(void);
static FRAME_INFO frame__30_241 = {2, {"topic", "references"}};
static void cont__30_242(void);
static NODE *string__30_243;
static NODE *string__30_244;
static void cont__30_245(void);
static void cont__30_246(void);
static NODE *func__30_247;
static void entry__30_247(void);
static FRAME_INFO frame__30_247 = {1, {"references"}};
static NODE *func__30_248;
static void entry__30_248(void);
static FRAME_INFO frame__30_248 = {1, {"reference"}};
static NODE *func__30_249;
static void entry__30_249(void);
static FRAME_INFO frame__30_249 = {1, {"reference"}};
static NODE *func__30_250;
static void entry__30_250(void);
static FRAME_INFO frame__30_250 = {1, {"reference"}};
static void cont__30_251(void);
static NODE *string__30_252;
static void cont__30_253(void);
static NODE *string__30_254;
static void cont__30_255(void);
static void cont__30_256(void);
static NODE *string__30_257;
static NODE *func__30_258;
static void entry__30_258(void);
static FRAME_INFO frame__30_258 = {0, {}};
static NODE *string__30_259;
static void cont__30_260(void);
static NODE *func__30_261;
static void entry__30_261(void);
static FRAME_INFO frame__30_261 = {0, {}};
static NODE *string__30_262;
static NODE *string__30_263;
static void cont__30_264(void);
static NODE *string__30_265;
static void cont__30_266(void);
static NODE *func__30_267;
static void entry__30_267(void);
static FRAME_INFO frame__30_267 = {0, {}};
static NODE *string__30_268;
static NODE *string__30_269;
static void cont__30_270(void);
static NODE *string__30_271;
static void cont__30_272(void);
static NODE *func__30_273;
static void entry__30_273(void);
static FRAME_INFO frame__30_273 = {0, {}};
static NODE *string__30_274;
static NODE *string__30_275;
static void cont__30_276(void);
static NODE *string__30_277;
static void cont__30_278(void);
static NODE *func__30_279;
static void entry__30_279(void);
static FRAME_INFO frame__30_279 = {0, {}};
static NODE *string__30_280;
static NODE *string__30_281;
static void cont__30_282(void);
static NODE *string__30_283;
static void cont__30_284(void);
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
  {cont__44_7, NULL, 350, 350, 8, 28},
  {cont__56_3, NULL, 350, 350, 1, 33},
  {cont__56_4, NULL, 351, 351, 10, 32},
  {cont__57_3, NULL, 351, 351, 40, 59},
  {cont__57_4, NULL, 351, 351, 40, 74},
  {cont__57_5, NULL, 351, 351, 35, 75},
  {cont__57_6, NULL, 351, 351, 1, 80},
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
  {entry__19_12, NULL, 293, 293, 36, 71},
  {entry__19_9, NULL, 293, 293, 10, 33},
  {cont__19_11, &frame__19_9, 293, 293, 7, 71},
  {entry__19_4, NULL, 290, 290, 5, 28},
  {cont__19_5, &frame__19_4, 291, 293, 5, 71},
  {entry__19_1, NULL, 289, 289, 22, 56},
  {cont__19_2, &frame__19_1, 289, 289, 12, 62},
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
  {cont__20_23, &frame__20_20, 306, 307, 7, 51},
  {entry__20_7, NULL, 299, 299, 14, 37},
  {cont__20_8, &frame__20_7, 299, 304, 5, 38},
  {cont__20_18, &frame__20_7, 305, 305, 12, 40},
  {cont__20_19, &frame__20_7, 305, 307, 5, 52},
  {cont__20_24, &frame__20_7, 308, 308, 8, 43},
  {cont__20_26, &frame__20_7, 308, 308, 5, 43},
  {entry__20_1, NULL, 296, 296, 3, 21},
  {cont__20_2, &frame__20_1, 297, 297, 6, 23},
  {cont__20_3, &frame__20_1, 297, 297, 6, 34},
  {cont__20_4, &frame__20_1, 297, 308, 3, 43},
  {entry__21_17, NULL, 318, 318, 35, 69},
  {entry__21_14, NULL, 317, 317, 7, 39},
  {cont__21_15, &frame__21_14, 318, 318, 10, 32},
  {cont__21_16, &frame__21_14, 318, 318, 7, 69},
  {entry__21_9, NULL, 314, 314, 6, 32},
  {cont__21_10, &frame__21_9, 314, 314, 5, 38},
  {cont__21_11, &frame__21_9, 315, 315, 12, 30},
  {cont__21_12, &frame__21_9, 315, 315, 12, 38},
  {cont__21_13, &frame__21_9, 315, 318, 5, 69},
  {cont__21_18, &frame__21_9, 319, 319, 5, 23},
  {cont__21_19, &frame__21_9, 319, 319, 34, 34},
  {entry__21_1, NULL, 311, 311, 23, 40},
  {cont__21_3, &frame__21_1, 311, 311, 42, 59},
  {cont__21_5, &frame__21_1, 311, 311, 3, 60},
  {cont__21_6, &frame__21_1, 312, 312, 3, 33},
  {cont__21_7, &frame__21_1, 313, 313, 6, 26},
  {cont__21_8, &frame__21_1, 313, 319, 3, 34},
  {entry__22_1, NULL, 321, 321, 38, 48},
  {cont__22_4, &frame__22_1, 321, 321, 50, 60},
  {cont__22_6, &frame__22_1, 321, 321, 21, 61},
  {cont__22_7, &frame__22_1, 321, 321, 18, 61},
  {entry__23_1, NULL, 325, 325, 12, 29},
  {cont__23_2, &frame__23_1, 325, 325, 35, 57},
  {cont__23_3, &frame__23_1, 325, 325, 5, 81},
  {cont__23_4, &frame__23_1, 324, 325, 3, 81},
  {entry__24_2, NULL, 329, 329, 7, 27},
  {cont__24_5, &frame__24_2, 329, 329, 5, 34},
  {cont__24_7, &frame__24_2, 330, 330, 5, 29},
  {cont__24_9, &frame__24_2, 331, 331, 7, 28},
  {cont__24_12, &frame__24_2, 331, 331, 5, 37},
  {cont__24_14, &frame__24_2, 332, 332, 5, 29},
  {cont__24_16, &frame__24_2, 333, 333, 7, 32},
  {cont__24_19, &frame__24_2, 333, 333, 5, 45},
  {cont__24_21, &frame__24_2, 334, 334, 5, 29},
  {cont__24_23, &frame__24_2, 335, 335, 7, 34},
  {cont__24_26, &frame__24_2, 335, 335, 5, 49},
  {cont__24_28, &frame__24_2, 336, 336, 5, 29},
  {cont__24_30, &frame__24_2, 337, 337, 7, 33},
  {cont__24_33, &frame__24_2, 337, 337, 5, 47},
  {entry__24_1, NULL, 328, 337, 3, 47},
  {entry__25_8, NULL, 344, 344, 41, 67},
  {cont__25_10, &frame__25_8, 344, 344, 67, 67},
  {entry__25_14, NULL, 345, 345, 43, 69},
  {cont__25_16, &frame__25_14, 345, 345, 69, 69},
  {entry__25_3, NULL, 342, 342, 7, 40},
  {cont__25_4, &frame__25_3, 343, 343, 7, 42},
  {cont__25_5, &frame__25_3, 344, 344, 14, 38},
  {cont__25_7, &frame__25_3, 344, 344, 7, 67},
  {cont__25_11, &frame__25_3, 345, 345, 14, 40},
  {cont__25_13, &frame__25_3, 345, 345, 7, 69},
  {cont__25_17, &frame__25_3, 346, 346, 7, 50},
  {cont__25_18, &frame__25_3, 346, 346, 50, 50},
  {entry__25_22, NULL, 348, 348, 41, 65},
  {cont__25_24, &frame__25_22, 348, 348, 65, 65},
  {entry__25_19, NULL, 348, 348, 14, 38},
  {cont__25_21, &frame__25_19, 348, 348, 7, 65},
  {entry__25_1, NULL, 341, 341, 5, 28},
  {cont__25_2, &frame__25_1, 340, 348, 3, 66},
  {cont__25_25, &frame__25_1, },
  {entry__28_5, NULL, 362, 362, 13, 22},
  {cont__28_6, &frame__28_5, 363, 363, 13, 33},
  {cont__28_7, &frame__28_5, 364, 364, 22, 22},
  {entry__28_8, NULL, 366, 366, 13, 33},
  {cont__28_9, &frame__28_8, 366, 366, 33, 33},
  {entry__28_3, NULL, 361, 361, 11, 35},
  {cont__28_4, &frame__28_3, 360, 366, 9, 34},
  {entry__28_15, NULL, 371, 371, 15, 35},
  {cont__28_16, &frame__28_15, 372, 372, 22, 22},
  {entry__28_12, NULL, 370, 370, 16, 25},
  {cont__28_13, &frame__28_12, 370, 370, 16, 25},
  {cont__28_14, &frame__28_12, 370, 372, 13, 22},
  {entry__28_21, NULL, 376, 376, 60, 60},
  {entry__28_19, NULL, 376, 376, 20, 44},
  {cont__28_20, &frame__28_19, 376, 376, 17, 60},
  {entry__28_22, NULL, 378, 378, 17, 30},
  {cont__28_23, &frame__28_22, 378, 378, 30, 30},
  {entry__28_17, NULL, 375, 375, 15, 24},
  {cont__28_18, &frame__28_17, 374, 378, 13, 31},
  {cont__28_24, &frame__28_17, 379, 379, 26, 34},
  {cont__28_25, &frame__28_17, 379, 379, 13, 34},
  {cont__28_26, &frame__28_17, 379, 379, 34, 34},
  {entry__28_10, NULL, 369, 369, 11, 20},
  {cont__28_11, &frame__28_10, 368, 379, 9, 35},
  {entry__28_2, NULL, 358, 379, 5, 37},
  {entry__28_30, NULL, 380, 380, 18, 38},
  {cont__28_31, &frame__28_30, 380, 380, 38, 38},
  {entry__28_1, NULL, 357, 379, 3, 38},
  {cont__28_27, &frame__28_1, 380, 380, 6, 15},
  {cont__28_28, &frame__28_1, 380, 380, 6, 15},
  {cont__28_29, &frame__28_1, 380, 380, 3, 38},
  {cont__28_32, &frame__28_1, 381, 381, 3, 15},
  {entry__29_11, NULL, 389, 389, 11, 42},
  {cont__29_12, &frame__29_11, 390, 390, 11, 44},
  {cont__29_13, &frame__29_11, 396, 396, 15, 26},
  {cont__29_14, &frame__29_11, 400, 400, 15, 28},
  {cont__29_15, &frame__29_11, 392, 401, 13, 21},
  {cont__29_20, &frame__29_11, 391, 401, 11, 23},
  {entry__29_21, NULL, 403, 403, 11, 26},
  {entry__29_37, NULL, 429, 429, 58, 58},
  {cont__29_38, &frame__29_37, 429, 429, 39, 59},
  {cont__29_39, &frame__29_37, 429, 429, 21, 74},
  {cont__29_41, &frame__29_37, 429, 429, 74, 74},
  {entry__29_35, NULL, 428, 428, 22, 47},
  {cont__29_36, &frame__29_35, 428, 429, 19, 74},
  {entry__29_44, NULL, 432, 432, 49, 49},
  {cont__29_45, &frame__29_44, 432, 432, 30, 50},
  {cont__29_46, &frame__29_44, 431, 432, 21, 79},
  {cont__29_48, &frame__29_44, 432, 432, 80, 80},
  {entry__29_42, NULL, 430, 430, 22, 47},
  {cont__29_43, &frame__29_42, 430, 432, 19, 80},
  {entry__29_51, NULL, 436, 436, 26, 47},
  {cont__29_52, &frame__29_51, 436, 436, 26, 53},
  {cont__29_53, &frame__29_51, 438, 438, 26, 47},
  {cont__29_54, &frame__29_51, 438, 438, 26, 53},
  {cont__29_55, &frame__29_51, 434, 439, 21, 28},
  {cont__29_58, &frame__29_51, 439, 439, 29, 29},
  {entry__29_49, NULL, 433, 433, 22, 45},
  {cont__29_50, &frame__29_49, 433, 439, 19, 29},
  {entry__29_33, NULL, 426, 426, 17, 68},
  {cont__29_34, &frame__29_33, 427, 439, 17, 30},
  {cont__29_59, &frame__29_33, 440, 440, 31, 52},
  {cont__29_60, &frame__29_33, 440, 440, 17, 58},
  {cont__29_61, &frame__29_33, 441, 441, 34, 56},
  {cont__29_62, &frame__29_33, 441, 441, 17, 56},
  {cont__29_63, &frame__29_33, 441, 441, 56, 56},
  {entry__29_28, NULL, 423, 423, 19, 53},
  {cont__29_29, &frame__29_28, 419, 424, 17, 20},
  {cont__29_31, &frame__29_28, 417, 424, 15, 21},
  {cont__29_32, &frame__29_28, 416, 441, 13, 57},
  {entry__29_73, NULL, 455, 455, 64, 64},
  {cont__29_74, &frame__29_73, 455, 455, 42, 65},
  {cont__29_75, &frame__29_73, 455, 455, 21, 80},
  {cont__29_77, &frame__29_73, 455, 455, 80, 80},
  {entry__29_71, NULL, 454, 454, 22, 50},
  {cont__29_72, &frame__29_71, 454, 455, 19, 80},
  {entry__29_80, NULL, 459, 459, 47, 47},
  {cont__29_81, &frame__29_80, 459, 459, 25, 48},
  {cont__29_82, &frame__29_80, 457, 460, 21, 52},
  {cont__29_84, &frame__29_80, 460, 460, 53, 53},
  {entry__29_78, NULL, 456, 456, 22, 50},
  {cont__29_79, &frame__29_78, 456, 460, 19, 53},
  {entry__29_69, NULL, 452, 452, 17, 71},
  {cont__29_70, &frame__29_69, 453, 460, 17, 54},
  {cont__29_85, &frame__29_69, 461, 461, 31, 52},
  {cont__29_86, &frame__29_69, 461, 461, 17, 58},
  {cont__29_87, &frame__29_69, 462, 462, 37, 62},
  {cont__29_88, &frame__29_69, 462, 462, 17, 62},
  {cont__29_89, &frame__29_69, 462, 462, 62, 62},
  {entry__29_64, NULL, 449, 449, 19, 53},
  {cont__29_65, &frame__29_64, 445, 450, 17, 20},
  {cont__29_67, &frame__29_64, 443, 450, 15, 21},
  {cont__29_68, &frame__29_64, 442, 462, 13, 63},
  {entry__29_96, NULL, 465, 465, 34, 47},
  {cont__29_97, &frame__29_96, 465, 465, 17, 47},
  {cont__29_98, &frame__29_96, 465, 465, 47, 47},
  {entry__29_93, NULL, 464, 464, 30, 51},
  {cont__29_94, &frame__29_93, 464, 464, 24, 56},
  {cont__29_95, &frame__29_93, 464, 465, 15, 47},
  {entry__29_90, NULL, 463, 463, 16, 49},
  {cont__29_92, &frame__29_90, 463, 465, 13, 48},
  {entry__29_104, NULL, 468, 468, 17, 27},
  {cont__29_105, &frame__29_104, 471, 471, 33, 45},
  {cont__29_106, &frame__29_104, 470, 471, 17, 66},
  {cont__29_107, &frame__29_104, 473, 473, 17, 46},
  {cont__29_108, &frame__29_104, 474, 474, 17, 30},
  {cont__29_109, &frame__29_104, 474, 474, 45, 45},
  {entry__29_101, NULL, 467, 467, 30, 51},
  {cont__29_102, &frame__29_101, 467, 467, 24, 56},
  {cont__29_103, &frame__29_101, 467, 474, 15, 45},
  {entry__29_99, NULL, 466, 466, 16, 43},
  {cont__29_100, &frame__29_99, 466, 474, 13, 46},
  {entry__29_112, NULL, 476, 476, 23, 44},
  {cont__29_113, &frame__29_112, 476, 476, 15, 50},
  {cont__29_114, &frame__29_112, 477, 477, 22, 43},
  {cont__29_115, &frame__29_112, 477, 477, 15, 49},
  {cont__29_116, &frame__29_112, 478, 478, 30, 41},
  {cont__29_117, &frame__29_112, 478, 478, 15, 41},
  {cont__29_118, &frame__29_112, 478, 478, 41, 41},
  {entry__29_110, NULL, 475, 475, 16, 45},
  {cont__29_111, &frame__29_110, 475, 478, 13, 41},
  {entry__29_126, NULL, 483, 483, 47, 47},
  {entry__29_127, NULL, 485, 485, 19, 49},
  {cont__29_128, &frame__29_127, 485, 485, 49, 49},
  {entry__29_122, NULL, 480, 480, 24, 45},
  {cont__29_123, &frame__29_122, 480, 480, 15, 51},
  {cont__29_124, &frame__29_122, 482, 482, 17, 28},
  {cont__29_125, &frame__29_122, 481, 485, 15, 50},
  {entry__29_119, NULL, 479, 479, 16, 58},
  {cont__29_121, &frame__29_119, 479, 485, 13, 51},
  {entry__29_133, NULL, 492, 492, 41, 41},
  {cont__29_134, &frame__29_133, 492, 492, 21, 41},
  {cont__29_135, &frame__29_133, 493, 493, 21, 48},
  {cont__29_136, &frame__29_133, 494, 494, 42, 58},
  {cont__29_137, &frame__29_133, 494, 494, 24, 66},
  {cont__29_141, &frame__29_133, 494, 494, 21, 66},
  {entry__29_147, NULL, 499, 499, 23, 55},
  {cont__29_148, &frame__29_147, 499, 499, 55, 55},
  {entry__29_149, NULL, 501, 501, 23, 50},
  {cont__29_150, &frame__29_149, 501, 501, 50, 50},
  {entry__29_145, NULL, 498, 498, 21, 48},
  {cont__29_146, &frame__29_145, 497, 501, 19, 51},
  {entry__29_151, NULL, 503, 503, 46, 46},
  {entry__29_129, NULL, 490, 490, 39, 47},
  {cont__29_130, &frame__29_129, 490, 490, 30, 48},
  {cont__29_131, &frame__29_129, 490, 490, 19, 53},
  {cont__29_132, &frame__29_129, 489, 494, 17, 66},
  {cont__29_142, &frame__29_129, 487, 494, 15, 68},
  {cont__29_143, &frame__29_129, 496, 496, 17, 44},
  {cont__29_144, &frame__29_129, 495, 503, 15, 47},
  {entry__29_27, NULL, 415, 503, 11, 49},
  {entry__29_25, NULL, 413, 413, 9, 46},
  {cont__29_26, &frame__29_25, 414, 503, 9, 50},
  {entry__29_169, NULL, 519, 519, 25, 51},
  {cont__29_170, &frame__29_169, 519, 519, 25, 61},
  {cont__29_171, &frame__29_169, 516, 520, 23, 27},
  {cont__29_174, &frame__29_169, 520, 520, 28, 28},
  {entry__29_175, NULL, 522, 522, 23, 48},
  {cont__29_177, &frame__29_175, 522, 522, 48, 48},
  {entry__29_166, NULL, 515, 515, 21, 47},
  {cont__29_167, &frame__29_166, 515, 515, 21, 58},
  {cont__29_168, &frame__29_166, 514, 522, 19, 49},
  {entry__29_164, NULL, 513, 513, 20, 48},
  {cont__29_165, &frame__29_164, 513, 522, 17, 50},
  {entry__29_180, NULL, 524, 524, 19, 58},
  {cont__29_182, &frame__29_180, 524, 524, 58, 58},
  {entry__29_178, NULL, 523, 523, 20, 48},
  {cont__29_179, &frame__29_178, 523, 524, 17, 58},
  {entry__29_187, NULL, 529, 529, 22, 47},
  {cont__29_188, &frame__29_187, 529, 529, 22, 61},
  {cont__29_189, &frame__29_187, 529, 529, 22, 64},
  {cont__29_190, &frame__29_187, 529, 529, 19, 64},
  {entry__29_191, NULL, 530, 530, 19, 23},
  {entry__29_160, NULL, 511, 511, 30, 53},
  {cont__29_161, &frame__29_160, 511, 511, 22, 54},
  {cont__29_162, &frame__29_160, 511, 511, 15, 75},
  {cont__29_163, &frame__29_160, 512, 524, 15, 59},
  {cont__29_183, &frame__29_160, 528, 528, 23, 48},
  {cont__29_184, &frame__29_160, 528, 528, 23, 57},
  {cont__29_185, &frame__29_160, 528, 528, 19, 58},
  {cont__29_186, &frame__29_160, 526, 530, 15, 24},
  {cont__29_192, &frame__29_160, 532, 532, 32, 49},
  {cont__29_193, &frame__29_160, 532, 532, 15, 49},
  {cont__29_194, &frame__29_160, 532, 532, 49, 49},
  {entry__29_195, NULL, 509, 509, 15, 18},
  {entry__29_157, NULL, 507, 507, 13, 40},
  {cont__29_158, &frame__29_157, 508, 508, 13, 52},
  {cont__29_159, &frame__29_157, 506, 532, 11, 50},
  {entry__29_155, NULL, 505, 505, 18, 36},
  {cont__29_156, &frame__29_155, 505, 532, 9, 51},
  {entry__29_198, NULL, 533, 533, 40, 58},
  {entry__29_208, NULL, 539, 539, 19, 42},
  {cont__29_209, &frame__29_208, 539, 539, 17, 42},
  {entry__29_205, NULL, 538, 538, 16, 32},
  {cont__29_206, &frame__29_205, 538, 538, 13, 32},
  {cont__29_207, &frame__29_205, 539, 539, 13, 42},
  {entry__29_204, NULL, 537, 539, 11, 42},
  {entry__29_201, NULL, 535, 535, 9, 23},
  {cont__29_203, &frame__29_201, 536, 539, 9, 43},
  {entry__29_219, NULL, 545, 545, 19, 45},
  {cont__29_220, &frame__29_219, 545, 545, 17, 45},
  {entry__29_216, NULL, 544, 544, 16, 35},
  {cont__29_217, &frame__29_216, 544, 544, 13, 35},
  {cont__29_218, &frame__29_216, 545, 545, 13, 45},
  {entry__29_215, NULL, 543, 545, 11, 45},
  {entry__29_212, NULL, 541, 541, 9, 20},
  {cont__29_214, &frame__29_212, 542, 545, 9, 46},
  {entry__29_226, NULL, 548, 548, 46, 58},
  {entry__29_223, NULL, 547, 547, 9, 24},
  {cont__29_225, &frame__29_223, 548, 548, 9, 58},
  {entry__29_232, NULL, 551, 551, 46, 53},
  {entry__29_229, NULL, 550, 550, 9, 30},
  {cont__29_231, &frame__29_229, 551, 551, 9, 53},
  {entry__29_239, NULL, 556, 556, 13, 40},
  {cont__29_240, &frame__29_239, 557, 557, 27, 43},
  {cont__29_241, &frame__29_239, 557, 557, 24, 50},
  {cont__29_243, &frame__29_239, 557, 557, 15, 50},
  {cont__29_245, &frame__29_239, 557, 557, 13, 60},
  {cont__29_246, &frame__29_239, 558, 558, 13, 14},
  {entry__29_238, NULL, 555, 558, 11, 14},
  {entry__29_235, NULL, 553, 553, 9, 21},
  {cont__29_237, &frame__29_235, 554, 558, 9, 15},
  {entry__29_258, NULL, 565, 565, 33, 44},
  {cont__29_259, &frame__29_258, 565, 565, 30, 51},
  {cont__29_261, &frame__29_258, 565, 565, 21, 51},
  {cont__29_263, &frame__29_258, 565, 565, 19, 56},
  {entry__29_267, NULL, 567, 567, 33, 46},
  {cont__29_268, &frame__29_267, 567, 567, 30, 53},
  {cont__29_270, &frame__29_267, 567, 567, 21, 53},
  {cont__29_272, &frame__29_267, 567, 567, 19, 60},
  {entry__29_257, NULL, 565, 565, 15, 56},
  {cont__29_264, &frame__29_257, 566, 566, 15, 33},
  {cont__29_266, &frame__29_257, 567, 567, 15, 60},
  {entry__29_255, NULL, 563, 563, 13, 50},
  {cont__29_256, &frame__29_255, 564, 567, 13, 60},
  {entry__29_253, NULL, 562, 562, 20, 33},
  {cont__29_254, &frame__29_253, 562, 567, 11, 61},
  {entry__29_250, NULL, 560, 560, 9, 27},
  {cont__29_252, &frame__29_250, 561, 567, 9, 62},
  {entry__29_283, NULL, 573, 573, 33, 51},
  {cont__29_284, &frame__29_283, 573, 573, 30, 58},
  {cont__29_286, &frame__29_283, 573, 573, 21, 58},
  {cont__29_288, &frame__29_283, 573, 573, 19, 70},
  {entry__29_292, NULL, 579, 579, 24, 44},
  {cont__29_293, &frame__29_292, 579, 579, 51, 69},
  {cont__29_294, &frame__29_292, 579, 579, 21, 76},
  {cont__29_297, &frame__29_292, 577, 579, 19, 75},
  {cont__29_299, &frame__29_292, 576, 582, 17, 29},
  {entry__29_282, NULL, 573, 573, 15, 70},
  {cont__29_289, &frame__29_282, 574, 574, 15, 25},
  {cont__29_291, &frame__29_282, 575, 582, 15, 30},
  {entry__29_281, NULL, 572, 582, 13, 31},
  {entry__29_279, NULL, 571, 571, 20, 35},
  {cont__29_280, &frame__29_279, 571, 582, 11, 32},
  {entry__29_276, NULL, 569, 569, 9, 44},
  {cont__29_278, &frame__29_276, 570, 582, 9, 33},
  {entry__29_317, NULL, 601, 601, 19, 35},
  {entry__29_312, NULL, 598, 598, 24, 48},
  {cont__29_313, &frame__29_312, 598, 598, 24, 63},
  {cont__29_314, &frame__29_312, 598, 598, 19, 64},
  {cont__29_315, &frame__29_312, 596, 599, 17, 25},
  {cont__29_316, &frame__29_312, 595, 601, 15, 35},
  {cont__29_318, &frame__29_312, 602, 602, 35, 69},
  {cont__29_321, &frame__29_312, 602, 602, 15, 69},
  {cont__29_322, &frame__29_312, 593, 602, 13, 68},
  {cont__29_323, &frame__29_312, 592, 602, 11, 70},
  {entry__29_304, NULL, 588, 588, 9, 30},
  {cont__29_305, &frame__29_304, 589, 589, 9, 36},
  {cont__29_306, &frame__29_304, 590, 590, 9, 16},
  {cont__29_307, &frame__29_304, 591, 591, 45, 56},
  {cont__29_308, &frame__29_304, 591, 591, 23, 56},
  {cont__29_309, &frame__29_304, 591, 591, 13, 56},
  {cont__29_311, &frame__29_304, 591, 602, 9, 71},
  {entry__29_8, NULL, 386, 386, 7, 14},
  {cont__29_9, &frame__29_8, 388, 388, 9, 36},
  {cont__29_10, &frame__29_8, 387, 403, 7, 27},
  {cont__29_22, &frame__29_8, 411, 411, 7, 41},
  {cont__29_23, &frame__29_8, 412, 412, 10, 32},
  {cont__29_24, &frame__29_8, 412, 503, 7, 51},
  {cont__29_152, &frame__29_8, 504, 504, 10, 22},
  {cont__29_153, &frame__29_8, 504, 504, 10, 34},
  {cont__29_154, &frame__29_8, 504, 532, 7, 52},
  {cont__29_196, &frame__29_8, 533, 533, 10, 37},
  {cont__29_197, &frame__29_8, 533, 533, 7, 58},
  {cont__29_199, &frame__29_8, 534, 534, 14, 32},
  {cont__29_200, &frame__29_8, 534, 539, 7, 44},
  {cont__29_210, &frame__29_8, 540, 540, 14, 35},
  {cont__29_211, &frame__29_8, 540, 545, 7, 47},
  {cont__29_221, &frame__29_8, 546, 546, 14, 34},
  {cont__29_222, &frame__29_8, 546, 548, 7, 58},
  {cont__29_227, &frame__29_8, 549, 549, 10, 37},
  {cont__29_228, &frame__29_8, 549, 551, 7, 53},
  {cont__29_233, &frame__29_8, 552, 552, 14, 32},
  {cont__29_234, &frame__29_8, 552, 558, 7, 16},
  {cont__29_247, &frame__29_8, 559, 559, 14, 27},
  {cont__29_248, &frame__29_8, 559, 559, 14, 36},
  {cont__29_249, &frame__29_8, 559, 567, 7, 63},
  {cont__29_273, &frame__29_8, 568, 568, 10, 22},
  {cont__29_274, &frame__29_8, 568, 568, 10, 30},
  {cont__29_275, &frame__29_8, 568, 582, 7, 34},
  {cont__29_300, &frame__29_8, 585, 585, 9, 42},
  {cont__29_301, &frame__29_8, 584, 585, 7, 64},
  {cont__29_303, &frame__29_8, 587, 602, 7, 72},
  {cont__29_324, &frame__29_8, 604, 604, 9, 26},
  {cont__29_327, &frame__29_8, 605, 605, 24, 40},
  {cont__29_328, &frame__29_8, 605, 605, 24, 69},
  {cont__29_329, &frame__29_8, 605, 605, 9, 76},
  {cont__29_332, &frame__29_8, 603, 605, 7, 76},
  {entry__29_3, NULL, 385, 385, 25, 45},
  {cont__29_4, &frame__29_3, 385, 385, 17, 52},
  {cont__29_7, &frame__29_3, 385, 605, 5, 77},
  {entry__29_1, NULL, 384, 384, 6, 29},
  {cont__29_2, &frame__29_1, 384, 605, 3, 78},
  {entry__30_9, NULL, 615, 615, 59, 59},
  {cont__30_10, &frame__30_9, 615, 615, 42, 60},
  {cont__30_11, &frame__30_9, 615, 615, 13, 61},
  {cont__30_12, &frame__30_9, 617, 617, 26, 42},
  {cont__30_13, &frame__30_9, 616, 617, 16, 67},
  {cont__30_17, &frame__30_9, 616, 617, 13, 67},
  {entry__30_5, NULL, 613, 613, 11, 39},
  {cont__30_8, &frame__30_5, 612, 617, 9, 68},
  {cont__30_18, &frame__30_5, 610, 617, 7, 70},
  {cont__30_19, &frame__30_5, 617, 617, 71, 71},
  {entry__30_2, NULL, 609, 609, 8, 17},
  {cont__30_4, &frame__30_2, 609, 617, 5, 71},
  {cont__30_20, &frame__30_2, 618, 618, 5, 13},
  {entry__30_30, NULL, 625, 625, 27, 52},
  {entry__30_36, NULL, 629, 629, 24, 48},
  {cont__30_37, &frame__30_36, 629, 629, 11, 62},
  {cont__30_38, &frame__30_36, 629, 629, 62, 62},
  {entry__30_42, NULL, 632, 632, 26, 50},
  {cont__30_44, &frame__30_42, 632, 632, 52, 76},
  {cont__30_46, &frame__30_42, 631, 632, 11, 77},
  {cont__30_47, &frame__30_42, 634, 634, 12, 29},
  {cont__30_48, &frame__30_42, 634, 634, 12, 38},
  {cont__30_49, &frame__30_42, 634, 634, 40, 52},
  {cont__30_50, &frame__30_42, 634, 634, 11, 53},
  {cont__30_51, &frame__30_42, 634, 634, 11, 29},
  {cont__30_52, &frame__30_42, 634, 634, 58, 58},
  {entry__30_33, NULL, 628, 628, 16, 42},
  {cont__30_35, &frame__30_33, 628, 629, 9, 62},
  {cont__30_39, &frame__30_33, 630, 630, 12, 24},
  {cont__30_40, &frame__30_33, 630, 630, 12, 35},
  {cont__30_41, &frame__30_33, 630, 634, 9, 58},
  {cont__30_53, &frame__30_33, 635, 635, 9, 29},
  {cont__30_54, &frame__30_33, 635, 635, 41, 41},
  {entry__30_27, NULL, 624, 624, 7, 25},
  {cont__30_28, &frame__30_27, 625, 625, 10, 24},
  {cont__30_29, &frame__30_27, 625, 625, 7, 52},
  {cont__30_31, &frame__30_27, 627, 627, 16, 31},
  {cont__30_32, &frame__30_27, 627, 635, 7, 41},
  {cont__30_55, &frame__30_27, 636, 636, 8, 24},
  {cont__30_56, &frame__30_27, 636, 636, 7, 24},
  {cont__30_57, &frame__30_27, 636, 636, 43, 43},
  {entry__30_24, NULL, 623, 623, 8, 20},
  {cont__30_25, &frame__30_24, 623, 623, 8, 28},
  {cont__30_26, &frame__30_24, 623, 636, 5, 43},
  {entry__30_67, NULL, 648, 648, 18, 50},
  {cont__30_69, &frame__30_67, 648, 648, 13, 50},
  {cont__30_70, &frame__30_67, 649, 649, 27, 39},
  {cont__30_71, &frame__30_67, 649, 649, 24, 46},
  {cont__30_73, &frame__30_67, 649, 649, 15, 46},
  {cont__30_75, &frame__30_67, 649, 649, 13, 52},
  {entry__30_66, NULL, 647, 649, 11, 52},
  {entry__30_78, NULL, 650, 650, 43, 63},
  {cont__30_79, &frame__30_78, 650, 650, 39, 64},
  {cont__30_80, &frame__30_78, 650, 650, 39, 64},
  {entry__30_82, NULL, 651, 651, 14, 39},
  {cont__30_83, &frame__30_82, 651, 651, 14, 42},
  {cont__30_84, &frame__30_82, 651, 651, 11, 42},
  {entry__30_87, NULL, 653, 653, 27, 43},
  {cont__30_88, &frame__30_87, 653, 653, 45, 52},
  {cont__30_89, &frame__30_87, 653, 653, 11, 52},
  {entry__30_62, NULL, 644, 644, 9, 28},
  {cont__30_63, &frame__30_62, 645, 645, 9, 43},
  {cont__30_64, &frame__30_62, 646, 646, 12, 27},
  {cont__30_65, &frame__30_62, 646, 649, 9, 53},
  {cont__30_76, &frame__30_62, 650, 650, 12, 34},
  {cont__30_77, &frame__30_62, 650, 650, 12, 64},
  {cont__30_81, &frame__30_62, 650, 651, 9, 42},
  {cont__30_85, &frame__30_62, 652, 652, 18, 39},
  {cont__30_86, &frame__30_62, 652, 653, 9, 52},
  {entry__30_61, NULL, 643, 653, 7, 53},
  {entry__30_97, NULL, 659, 659, 37, 49},
  {cont__30_98, &frame__30_97, 659, 659, 37, 62},
  {cont__30_99, &frame__30_97, 659, 659, 37, 62},
  {entry__30_101, NULL, 660, 660, 11, 30},
  {entry__30_94, NULL, 659, 659, 12, 24},
  {cont__30_95, &frame__30_94, 659, 659, 12, 32},
  {cont__30_96, &frame__30_94, 659, 659, 12, 62},
  {cont__30_100, &frame__30_94, 659, 660, 9, 30},
  {entry__30_93, NULL, 658, 660, 7, 31},
  {entry__30_60, NULL, 655, 655, 5, 12},
  {cont__30_90, &frame__30_60, 656, 656, 5, 19},
  {cont__30_92, &frame__30_60, 657, 660, 5, 32},
  {entry__30_111, NULL, 667, 667, 20, 31},
  {cont__30_113, &frame__30_111, 667, 667, 11, 31},
  {cont__30_115, &frame__30_111, 667, 667, 33, 52},
  {cont__30_116, &frame__30_111, 667, 667, 9, 52},
  {entry__30_117, NULL, 669, 669, 9, 16},
  {entry__30_134, NULL, 679, 679, 22, 41},
  {cont__30_135, &frame__30_134, 679, 679, 17, 41},
  {cont__30_136, &frame__30_134, 680, 680, 19, 35},
  {cont__30_139, &frame__30_134, 680, 680, 17, 66},
  {entry__30_131, NULL, 678, 678, 18, 30},
  {cont__30_133, &frame__30_131, 678, 680, 15, 66},
  {entry__30_128, NULL, 677, 677, 16, 28},
  {cont__30_130, &frame__30_128, 677, 680, 13, 67},
  {entry__30_126, NULL, 675, 675, 11, 26},
  {cont__30_127, &frame__30_126, 676, 680, 11, 68},
  {entry__30_145, NULL, 684, 684, 43, 63},
  {cont__30_146, &frame__30_145, 684, 684, 39, 64},
  {cont__30_147, &frame__30_145, 684, 684, 39, 64},
  {entry__30_149, NULL, 685, 685, 19, 44},
  {cont__30_150, &frame__30_149, 685, 685, 11, 47},
  {cont__30_151, &frame__30_149, 685, 685, 47, 47},
  {entry__30_154, NULL, 691, 691, 13, 25},
  {entry__30_156, NULL, 693, 693, 13, 34},
  {entry__30_158, NULL, 695, 695, 13, 37},
  {entry__30_160, NULL, 697, 697, 13, 28},
  {entry__30_162, NULL, 699, 699, 13, 21},
  {entry__30_164, NULL, 700, 700, 13, 24},
  {entry__30_169, NULL, 705, 705, 15, 55},
  {cont__30_172, &frame__30_169, 705, 705, 55, 55},
  {entry__30_173, NULL, 707, 707, 31, 31},
  {entry__30_167, NULL, 704, 704, 13, 29},
  {cont__30_168, &frame__30_167, 703, 707, 11, 32},
  {entry__30_176, NULL, 708, 708, 33, 47},
  {cont__30_177, &frame__30_176, 708, 708, 33, 47},
  {entry__30_187, NULL, 711, 711, 31, 42},
  {cont__30_188, &frame__30_187, 711, 711, 28, 49},
  {cont__30_190, &frame__30_187, 711, 711, 19, 49},
  {cont__30_192, &frame__30_187, 711, 711, 51, 68},
  {cont__30_194, &frame__30_187, 711, 711, 17, 68},
  {entry__30_180, NULL, 710, 710, 16, 32},
  {cont__30_183, &frame__30_180, 710, 710, 34, 50},
  {cont__30_185, &frame__30_180, 710, 710, 13, 50},
  {cont__30_186, &frame__30_180, 711, 711, 13, 68},
  {cont__30_195, &frame__30_180, 712, 712, 16, 33},
  {cont__30_198, &frame__30_180, 712, 712, 13, 40},
  {entry__30_179, NULL, 709, 712, 11, 40},
  {entry__30_122, NULL, 674, 674, 12, 19},
  {cont__30_123, &frame__30_122, 674, 674, 12, 29},
  {cont__30_124, &frame__30_122, 674, 674, 12, 29},
  {cont__30_125, &frame__30_122, 674, 680, 9, 69},
  {cont__30_141, &frame__30_122, 682, 682, 9, 27},
  {cont__30_142, &frame__30_122, 683, 683, 9, 43},
  {cont__30_143, &frame__30_122, 684, 684, 12, 34},
  {cont__30_144, &frame__30_122, 684, 684, 12, 64},
  {cont__30_148, &frame__30_122, 684, 685, 9, 47},
  {cont__30_152, &frame__30_122, 689, 689, 13, 25},
  {cont__30_153, &frame__30_122, 687, 700, 9, 25},
  {cont__30_165, &frame__30_122, 702, 702, 12, 31},
  {cont__30_166, &frame__30_122, 702, 707, 9, 33},
  {cont__30_174, &frame__30_122, 708, 708, 12, 28},
  {cont__30_175, &frame__30_122, 708, 708, 12, 47},
  {cont__30_178, &frame__30_122, 708, 712, 9, 41},
  {entry__30_121, NULL, 673, 712, 7, 42},
  {entry__30_104, NULL, 662, 662, 5, 12},
  {cont__30_105, &frame__30_104, 663, 663, 8, 21},
  {cont__30_108, &frame__30_104, 663, 663, 5, 36},
  {cont__30_110, &frame__30_104, 664, 669, 5, 17},
  {cont__30_119, &frame__30_104, 670, 670, 5, 6},
  {cont__30_120, &frame__30_104, 671, 712, 5, 43},
  {entry__30_208, NULL, 719, 719, 28, 55},
  {cont__30_210, &frame__30_208, 719, 719, 11, 67},
  {entry__30_206, NULL, 718, 718, 18, 33},
  {cont__30_207, &frame__30_206, 718, 719, 9, 67},
  {entry__30_203, NULL, 716, 716, 7, 32},
  {cont__30_204, &frame__30_203, 717, 717, 12, 24},
  {cont__30_205, &frame__30_203, 717, 719, 7, 68},
  {entry__30_200, NULL, 714, 714, 5, 23},
  {cont__30_201, &frame__30_200, 715, 715, 8, 22},
  {cont__30_202, &frame__30_200, 715, 719, 5, 69},
  {entry__30_229, NULL, 726, 726, 19, 35},
  {cont__30_231, &frame__30_229, 726, 726, 17, 41},
  {entry__30_228, NULL, 726, 726, 13, 41},
  {entry__30_221, NULL, 725, 725, 38, 56},
  {cont__30_222, &frame__30_221, 725, 725, 58, 66},
  {cont__30_224, &frame__30_221, 725, 725, 26, 67},
  {cont__30_225, &frame__30_221, 725, 725, 9, 76},
  {cont__30_227, &frame__30_221, 726, 726, 9, 41},
  {entry__30_220, NULL, 724, 726, 7, 41},
  {entry__30_213, NULL, 721, 721, 5, 12},
  {cont__30_214, &frame__30_213, 722, 722, 8, 21},
  {cont__30_217, &frame__30_213, 722, 722, 5, 35},
  {cont__30_219, &frame__30_213, 723, 726, 5, 42},
  {entry__30_250, NULL, 734, 734, 37, 53},
  {cont__30_251, &frame__30_250, 734, 734, 30, 62},
  {cont__30_253, &frame__30_250, 734, 734, 21, 62},
  {cont__30_255, &frame__30_250, 734, 734, 19, 72},
  {entry__30_249, NULL, 734, 734, 15, 72},
  {entry__30_248, NULL, 734, 734, 11, 72},
  {entry__30_247, NULL, 733, 734, 9, 72},
  {entry__30_241, NULL, 730, 730, 7, 14},
  {cont__30_242, &frame__30_241, 731, 731, 10, 23},
  {cont__30_245, &frame__30_241, 731, 731, 7, 29},
  {cont__30_246, &frame__30_241, 732, 734, 7, 73},
  {entry__30_233, NULL, 728, 728, 27, 45},
  {cont__30_234, &frame__30_233, 728, 728, 47, 55},
  {cont__30_236, &frame__30_233, 728, 728, 5, 56},
  {cont__30_237, &frame__30_233, 729, 729, 17, 39},
  {cont__30_240, &frame__30_233, 729, 734, 5, 74},
  {entry__30_261, NULL, 737, 737, 10, 31},
  {cont__30_264, &frame__30_261, 737, 737, 8, 40},
  {entry__30_267, NULL, 738, 738, 10, 35},
  {cont__30_270, &frame__30_267, 738, 738, 8, 48},
  {entry__30_273, NULL, 739, 739, 10, 37},
  {cont__30_276, &frame__30_273, 739, 739, 8, 52},
  {entry__30_279, NULL, 740, 740, 10, 36},
  {cont__30_282, &frame__30_279, 740, 740, 8, 50},
  {entry__30_258, NULL, 736, 736, 5, 19},
  {cont__30_260, &frame__30_258, 737, 737, 5, 40},
  {cont__30_266, &frame__30_258, 738, 738, 5, 48},
  {cont__30_272, &frame__30_258, 739, 739, 5, 52},
  {cont__30_278, &frame__30_258, 740, 740, 5, 50},
  {entry__30_1, NULL, 620, 620, 42, 42},
  {cont__30_21, &frame__30_1, 620, 620, 3, 43},
  {cont__30_22, &frame__30_1, 621, 621, 3, 43},
  {cont__30_23, &frame__30_1, 622, 636, 3, 44},
  {cont__30_58, &frame__30_1, 637, 660, 3, 33},
  {cont__30_102, &frame__30_1, 661, 712, 3, 44},
  {cont__30_199, &frame__30_1, 713, 719, 3, 70},
  {cont__30_211, &frame__30_1, 720, 726, 3, 43},
  {cont__30_232, &frame__30_1, 727, 734, 3, 75},
  {cont__30_256, &frame__30_1, 735, 740, 3, 50},
  {cont__30_284, &frame__30_1, 740, 740, 50, 50}
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
  allocate_initialized_frame_gc(0, 0);
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
  temp__3 = arguments->slots[0];
  // 53: alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__61;
  arguments->slots[1] = temp__3;
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
  temp__2 = arguments->slots[0];
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
  temp__6 = arguments->slots[0];
  // 54: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__6;
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
  temp__5 = arguments->slots[0];
  // 54: many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__5;
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
  temp__4 = arguments->slots[0];
  // 52: sequence
  // 53:   alt('=' sim2c::WHITESPACE, '=', sim2c::WHITESPACE)
  // 54:   many(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__2;
  arguments->slots[1] = temp__4;
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
  temp__1 = arguments->slots[0];
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
  arguments->slots[2] = temp__1;
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
  // 350: ... alt("Topics" "Topic")
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
  temp__1 = arguments->slots[0];
  // 350: $TOPIC alt("Topics" "Topic"), ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__1;
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
  // 351: ... alt("Example" "Output")
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
  temp__1 = arguments->slots[0];
  // 351: ... not_followed_by(':')
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
  temp__4 = arguments->slots[0];
  // 351: ... not_followed_by(':'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = temp__4;
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
  temp__3 = arguments->slots[0];
  // 351: ... some(not_followed_by(':'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = temp__3;
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
  temp__2 = arguments->slots[0];
  // 351: $EXAMPLE alt("Example" "Output"), some(not_followed_by(':'), ANY_CHARACTER), ':'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = temp__1;
  arguments->slots[1] = temp__2;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
static void entry__19_12(void) {
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  arguments->slots[1] = string__19_10;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__19_11;
}
static void cont__19_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 293: ... : extract_documentation_from_file name
  frame->slots[2] /* temp__2 */ = create_closure(entry__19_12, 0);
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
  frame->cont = frame->cont;
}
static void entry__19_1(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // path: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 289: ... std::key_value_pair(SORT std::true)
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
  // 289: ... directory(std::key_value_pair(SORT std::true) path)
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
  // 289: for_each directory(std::key_value_pair(SORT std::true) path): (entry)
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = frame->cont;
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
  frame->cont = cont__20_24;
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
  arguments->slots[0] = string__20_21;
  arguments->slots[1] = frame->slots[0] /* name */;
  arguments->slots[2] = string__20_22;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__20_23;
}
static void cont__20_23(void) {
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
  frame->cont = frame->cont;
}
static void cont__20_24(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 308: ... string(resolved_namespace "::" name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* resolved_namespace */;
  arguments->slots[1] = string__20_25;
  arguments->slots[2] = frame->slots[1] /* name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__20_26;
}
static void cont__20_26(void) {
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
  frame->cont = frame->cont;
}
static void entry__21_9(void) {
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
  frame->cont = cont__21_10;
}
static void cont__21_10(void) {
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
  frame->cont = cont__21_11;
}
static void cont__21_11(void) {
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
  frame->cont = cont__21_12;
}
static void cont__21_12(void) {
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
  frame->cont = cont__21_13;
}
static void cont__21_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 315: ... :
  // 316:   !definition.kind_of TYPE
  // 317:   $base_of_base base_of(definition)
  // 318:   if base_of_base.is_defined: add_derived_type base_of_base ibase
  frame->slots[5] /* temp__3 */ = create_closure(entry__21_14, 0);
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
  frame->cont = cont__21_18;
}
static void entry__21_17(void) {
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
  frame->cont = frame->cont;
}
static void entry__21_14(void) {
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
  frame->cont = cont__21_15;
}
static void cont__21_15(void) {
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
  frame->cont = cont__21_16;
}
static void cont__21_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 318: ... : add_derived_type base_of_base ibase
  frame->slots[4] /* temp__2 */ = create_closure(entry__21_17, 0);
  // 318: if base_of_base.is_defined: add_derived_type base_of_base ibase
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__21_18(void) {
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
  frame->cont = cont__21_19;
}
static void cont__21_19(void) {
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
  arguments->slots[1] = string__21_2;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__21_3;
}
static void cont__21_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 311: ... base .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = string__21_4;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__21_5;
}
static void cont__21_5(void) {
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
  frame->cont = cont__21_6;
}
static void cont__21_6(void) {
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
  frame->cont = cont__21_7;
}
static void cont__21_7(void) {
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
  frame->cont = cont__21_8;
}
static void cont__21_8(void) {
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
  frame->slots[5] /* temp__2 */ = create_closure(entry__21_9, 0);
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
  frame->cont = frame->cont;
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
  arguments->slots[0] = string__22_2;
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
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 321: ... '/' = "___"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__22_5;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__22_6;
}
static void cont__22_6(void) {
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
  frame->cont = cont__22_7;
}
static void cont__22_7(void) {
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
  // 325: ... name.to_lower_case
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
  // 325: ... namespace.to_lower_case
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
  // 325: string(name.to_lower_case '/' namespace.to_lower_case '/' name '/' namespace)
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
  // 325:   string(name.to_lower_case '/' namespace.to_lower_case '/' name '/' namespace)
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
  // 329: ... "href" = "index.html"
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
  // 329: A "href" = "index.html" "Home"
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
  // 330: TEXT "&nbsp;&nbsp;&nbsp;"
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
  // 331: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_10;
  arguments->slots[1] = string__24_11;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_12;
}
static void cont__24_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 331: A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_13;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_14;
}
static void cont__24_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 332: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_15;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_16;
}
static void cont__24_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 333: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_17;
  arguments->slots[1] = string__24_18;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_19;
}
static void cont__24_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 333: A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_20;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_21;
}
static void cont__24_21(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 334: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_22;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_23;
}
static void cont__24_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 335: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_24;
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
  // 335: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_27;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__24_28;
}
static void cont__24_28(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 336: TEXT "&nbsp;&nbsp;&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__24_29;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__24_30;
}
static void cont__24_30(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 337: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__24_31;
  arguments->slots[1] = string__24_32;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__24_33;
}
static void cont__24_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 337: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__24_34;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__24_1(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 328: P:
  // 329:   A "href" = "index.html" "Home"
  // 330:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 331:   A "href" = "manual.html" "Manual"
  // 332:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 333:   A "href" = "type_index.html" "Type Index"
  // 334:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 335:   A "href" = "symbol_index.html" "Symbol Index"
  // 336:   TEXT "&nbsp;&nbsp;&nbsp;"
  // 337:   A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__24_2;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 341: reference .contains. '/'
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
  // 341: ... :
  // 342:   $$type_name reference .before. '/'
  // 343:   $$method_name reference .behind. '/'
  // 344:   unless type_name .contains. "::": append "types::" &type_name
  // 345:   unless method_name .contains. "::": append "std::" &method_name
  // 346:   !reference string(type_name '/' method_name)
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_3, 0);
  // 347: :
  // 348:   unless reference .contains. "::": append "std::" &reference
  frame->slots[3] /* temp__3 */ = create_closure(entry__25_19, 0);
  // 340: if
  // 341:   reference .contains. '/':
  // 342:     $$type_name reference .before. '/'
  // 343:     $$method_name reference .behind. '/'
  // 344:     unless type_name .contains. "::": append "types::" &type_name
  // 345:     unless method_name .contains. "::": append "std::" &method_name
  // 346:     !reference string(type_name '/' method_name)
  // 347:   :
  // 348:     unless reference .contains. "::": append "std::" &reference
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
  frame->cont = cont__25_25;
}
static void entry__25_22(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: ... append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_23;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_24;
}
static void cont__25_24(void) {
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
  // 342: $$type_name reference .before. '/'
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
  // 343: $$method_name reference .behind. '/'
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
  // 344: ... type_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = string__25_6;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_7;
}
static void cont__25_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 344: ... : append "types::" &type_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_8, 0);
  // 344: unless type_name .contains. "::": append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_11;
}
static void entry__25_8(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // type_name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* type_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 344: ... append "types::" &type_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_9;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* type_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_10;
}
static void cont__25_10(void) {
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
static void cont__25_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 345: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* method_name */;
  arguments->slots[1] = string__25_12;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_13;
}
static void cont__25_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 345: ... : append "std::" &method_name
  frame->slots[4] /* temp__2 */ = create_closure(entry__25_14, 0);
  // 345: unless method_name .contains. "::": append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__25_17;
}
static void entry__25_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 345: ... append "std::" &method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__25_15;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* method_name */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__25_16;
}
static void cont__25_16(void) {
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
static void cont__25_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 346: !reference string(type_name '/' method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* type_name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = ((CELL *)frame->slots[2])->contents /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__25_18;
}
static void cont__25_18(void) {
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
static void entry__25_19(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 348: ... reference .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = string__25_20;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__25_21;
}
static void cont__25_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 348: ... : append "std::" &reference
  frame->slots[2] /* temp__2 */ = create_closure(entry__25_22, 0);
  // 348: unless reference .contains. "::": append "std::" &reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__25_25(void) {
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
  // 354: $$paragraphs empty_list
  ((CELL *)frame->slots[1])->contents /* paragraphs */ = get__empty_list();
  // 355: $$text ""
  ((CELL *)frame->slots[2])->contents /* text */ = empty_string;
  // 356: $$pre_mode false
  ((CELL *)frame->slots[3])->contents /* pre_mode */ = get__false();
  // 357: ... : (line)
  // 358:   if
  // 359:     pre_mode:
  // 360:       if
  // 361:         line .has_prefix. EXAMPLE:
  // 362:           trim &text
  // 363:           push &paragraphs text
  // 364:           !text line
  // 365:         :
  // 366:           writeln_to &text line
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__28_2, 1);
  // 357: for_each lines: (line)
  // 358:   if
  // 359:     pre_mode:
  // 360:       if
  // 361:         line .has_prefix. EXAMPLE:
  // 362:           trim &text
  // 363:           push &paragraphs text
  // 364:           !text line
  // 365:         :
  // 366:           writeln_to &text line
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
  // 371: push &paragraphs text
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
  // 372: !text ""
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
  // 370: ... text != ""
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
  // 370: ... text != ""
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
  // 370: ... :
  // 371:   push &paragraphs text
  // 372:   !text ""
  frame->slots[4] /* temp__3 */ = create_closure(entry__28_15, 0);
  // 370: if text != "":
  // 371:   push &paragraphs text
  // 372:   !text ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 375: text == ""
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
  // 375: ... :
  // 376:   if line .has_prefix. EXAMPLE: !pre_mode true
  frame->slots[4] /* temp__2 */ = create_closure(entry__28_19, 0);
  // 377: :
  // 378:   push &text ' '
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_22, 0);
  // 374: if
  // 375:   text == "":
  // 376:     if line .has_prefix. EXAMPLE: !pre_mode true
  // 377:   :
  // 378:     push &text ' '
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
  // 376: ... !pre_mode true
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
  // 376: ... line .has_prefix. EXAMPLE
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
  // 376: ... : !pre_mode true
  frame->slots[3] /* temp__2 */ = create_closure(entry__28_21, 0);
  // 376: if line .has_prefix. EXAMPLE: !pre_mode true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 378: push &text ' '
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
  // 379: ... line.trim
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
  // 379: append &text line.trim
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
  // 362: trim &text
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
  // 363: push &paragraphs text
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
  // 364: !text line
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
  // 366: writeln_to &text line
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
  // 361: line .has_prefix. EXAMPLE
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
  // 361: ... :
  // 362:   trim &text
  // 363:   push &paragraphs text
  // 364:   !text line
  frame->slots[4] /* temp__2 */ = create_closure(entry__28_5, 0);
  // 365: :
  // 366:   writeln_to &text line
  frame->slots[5] /* temp__3 */ = create_closure(entry__28_8, 0);
  // 360: if
  // 361:   line .has_prefix. EXAMPLE:
  // 362:     trim &text
  // 363:     push &paragraphs text
  // 364:     !text line
  // 365:   :
  // 366:     writeln_to &text line
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 369: line == ""
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
  // 369: ... :
  // 370:   if text != "":
  // 371:     push &paragraphs text
  // 372:     !text ""
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_12, 0);
  // 373: :
  // 374:   if
  // 375:     text == "":
  // 376:       if line .has_prefix. EXAMPLE: !pre_mode true
  // 377:     :
  // 378:       push &text ' '
  // 379:   append &text line.trim
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_17, 0);
  // 368: if
  // 369:   line == "":
  // 370:     if text != "":
  // 371:       push &paragraphs text
  // 372:       !text ""
  // 373:   :
  // 374:     if
  // 375:       text == "":
  // 376:         if line .has_prefix. EXAMPLE: !pre_mode true
  // 377:       :
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
  frame->cont = frame->cont;
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
  // 359: ... :
  // 360:   if
  // 361:     line .has_prefix. EXAMPLE:
  // 362:       trim &text
  // 363:       push &paragraphs text
  // 364:       !text line
  // 365:     :
  // 366:       writeln_to &text line
  frame->slots[4] /* temp__1 */ = create_closure(entry__28_3, 0);
  // 367: :
  // 368:   if
  // 369:     line == "":
  // 370:       if text != "":
  // 371:         push &paragraphs text
  // 372:         !text ""
  // 373:     :
  // 374:       if
  // 375:         text == "":
  // 376:           if line .has_prefix. EXAMPLE: !pre_mode true
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__28_10, 0);
  // 358: if
  // 359:   pre_mode:
  // 360:     if
  // 361:       line .has_prefix. EXAMPLE:
  // 362:         trim &text
  // 363:         push &paragraphs text
  // 364:         !text line
  // 365:       :
  // 366:         writeln_to &text line
  // 367:   :
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
  frame->cont = frame->cont;
}
static void cont__28_27(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 380: ... text != ""
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
  // 380: ... text != ""
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
  // 380: ... : push &paragraphs text
  frame->slots[6] /* temp__3 */ = create_closure(entry__28_30, 0);
  // 380: if text != "": push &paragraphs text
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
  // 380: ... push &paragraphs text
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
  // 381: -> paragraphs
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
  // 386: link_bar
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
  // 388: function_name .contains. '/'
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
  // 388: ... :
  // 389:   $type function_name .before. '/'
  // 390:   $method function_name .behind. '/'
  // 391:   H1
  // 392:     string
  // 393:       '['
  // 394:       type
  // 395:       "]("
  // 396:       type.mangled
  // 397:       ".html)/["
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_11, 0);
  // 402: :
  // 403:   H1 function_name
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_21, 0);
  // 387: if
  // 388:   function_name .contains. '/':
  // 389:     $type function_name .before. '/'
  // 390:     $method function_name .behind. '/'
  // 391:     H1
  // 392:       string
  // 393:         '['
  // 394:         type
  // 395:         "]("
  // 396:         type.mangled
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  arguments->slots[2] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_22;
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
  // 389: $type function_name .before. '/'
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
  // 390: $method function_name .behind. '/'
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
  // 396: type.mangled
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
  // 400: method.mangled
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
  // 392: string
  // 393:   '['
  // 394:   type
  // 395:   "]("
  // 396:   type.mangled
  // 397:   ".html)/["
  // 398:   method
  // 399:   "]("
  // 400:   method.mangled
  // 401:   ".html)"
  argument_count = 9;
  arguments = node_p;
  arguments->slots[0] = character__91;
  arguments->slots[1] = frame->slots[1] /* type */;
  arguments->slots[2] = string__29_16;
  arguments->slots[3] = frame->slots[4] /* temp__2 */;
  arguments->slots[4] = string__29_17;
  arguments->slots[5] = frame->slots[2] /* method */;
  arguments->slots[6] = string__29_18;
  arguments->slots[7] = frame->slots[5] /* temp__3 */;
  arguments->slots[8] = string__29_19;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_20;
}
static void cont__29_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 391: H1
  // 392:   string
  // 393:     '['
  // 394:     type
  // 395:     "]("
  // 396:     type.mangled
  // 397:     ".html)/["
  // 398:     method
  // 399:     "]("
  // 400:     method.mangled
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_21(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // function_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* function_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 403: H1 function_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = frame->caller_result_count;
  myself = get__H1();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_22(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 404: $$short_description undefined
  ((CELL *)frame->slots[2])->contents /* short_description */ = get__undefined();
  // 405: $$parameters empty_list
  ((CELL *)frame->slots[3])->contents /* parameters */ = get__empty_list();
  // 406: $$return_values empty_list
  ((CELL *)frame->slots[4])->contents /* return_values */ = get__empty_list();
  // 407: $$descriptions empty_list
  ((CELL *)frame->slots[5])->contents /* descriptions */ = get__empty_list();
  // 408: $$technical_details undefined
  ((CELL *)frame->slots[6])->contents /* technical_details */ = get__undefined();
  // 409: $$references empty_list
  ((CELL *)frame->slots[7])->contents /* references */ = get__empty_list();
  // 410: $$examples empty_list
  ((CELL *)frame->slots[8])->contents /* examples */ = get__empty_list();
  // 411: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_23;
}
static void cont__29_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* remark_lines */, arguments->slots[0]);
  // 412: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_24;
}
static void cont__29_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 412: ... :
  // 413:   $paragraphs remark_lines.to_paragraphs
  // 414:   for_each paragraphs: ($paragraph)
  // 415:     cond
  // 416:       ->
  // 417:         has_prefix
  // 418:           paragraph
  // 419:           sequence
  // 420:             "Parameter"
  // 421:             sim2c::WHITESPACE
  // ...
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_25, 0);
  // 412: if remark_lines.is_defined:
  // 413:   $paragraphs remark_lines.to_paragraphs
  // 414:   for_each paragraphs: ($paragraph)
  // 415:     cond
  // 416:       ->
  // 417:         has_prefix
  // 418:           paragraph
  // 419:           sequence
  // 420:             "Parameter"
  // 421:             sim2c::WHITESPACE
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_152;
}
static void entry__29_147(void) {
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
  // 499: push &technical_details paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_148;
}
static void cont__29_148(void) {
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
static void entry__29_149(void) {
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
  // 501: push &descriptions paragraph
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* paragraph */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_150;
}
static void cont__29_150(void) {
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
static void entry__29_145(void) {
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
  // 498: technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_146;
}
static void cont__29_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 498: ... :
  // 499:   push &technical_details paragraph
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_147, 0);
  // 500: :
  // 501:   push &descriptions paragraph
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_149, 0);
  // 497: if
  // 498:   technical_details.is_defined:
  // 499:     push &technical_details paragraph
  // 500:   :
  // 501:     push &descriptions paragraph
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_151(void) {
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
  // 503: !short_description paragraph
  ((CELL *)frame->slots[0])->contents /* short_description */ = ((CELL *)frame->slots[1])->contents /* paragraph */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_126(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 483: !technical_details empty_list
  ((CELL *)frame->slots[0])->contents /* technical_details */ = get__empty_list();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_127(void) {
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
  // 485: !technical_details list(detail)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* detail */;
  result_count = 1;
  myself = get__list();
  func = myself->type;
  frame->cont = cont__29_128;
}
static void cont__29_128(void) {
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
static void entry__29_122(void) {
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
  // 480: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_123;
}
static void cont__29_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 480: $detail (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_124;
}
static void cont__29_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* detail */, arguments->slots[0]);
  // 482: detail == ""
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* detail */;
  arguments->slots[1] = empty_string;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_125;
}
static void cont__29_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 482: ... :
  // 483:   !technical_details empty_list
  frame->slots[4] /* temp__2 */ = create_closure(entry__29_126, 0);
  // 484: :
  // 485:   !technical_details list(detail)
  frame->slots[5] /* temp__3 */ = create_closure(entry__29_127, 0);
  // 481: if
  // 482:   detail == "":
  // 483:     !technical_details empty_list
  // 484:   :
  // 485:     !technical_details list(detail)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  arguments->slots[2] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_112(void) {
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
  // 476: ... paragraph .before. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_113;
}
static void cont__29_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 476: $title (paragraph .before. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_114;
}
static void cont__29_114(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 477: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_115;
}
static void cont__29_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 477: $text (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_116;
}
static void cont__29_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 478: ... title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[3] /* text */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_117;
}
static void cont__29_117(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 478: push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* examples */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_118;
}
static void cont__29_118(void) {
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
static void entry__29_104(void) {
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
  // 468: trim &topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_105;
}
static void cont__29_105(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* topic */ = arguments->slots[0];
  // 471: ... topics(topic)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
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
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 470: $$topic_contents
  // 471:   default_value(topics(topic) empty_key_order_set)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = get__empty_key_order_set();
  result_count = 1;
  myself = get__default_value();
  func = myself->type;
  frame->cont = cont__29_107;
}
static void cont__29_107(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 473: !topic_contents(function_name) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 473: !topic_contents(function_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  func = myself->type;
  frame->cont = cont__29_108;
}
static void cont__29_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* topic_contents */ = arguments->slots[0];
  // 474: !topics(topic) topic_contents
  frame->slots[3] /* temp__1 */ = ((CELL *)frame->slots[2])->contents /* topic_contents */;
  // 474: !topics(topic)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* topic */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = var._topics;
  func = myself->type;
  frame->cont = cont__29_109;
}
static void cont__29_109(void) {
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
static void entry__29_101(void) {
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
  // 467: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_102;
}
static void cont__29_102(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 467: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__29_103;
}
static void cont__29_103(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 467: ... : ($topic)
  // 468:   trim &topic
  // 469:   
  // 470:   $$topic_contents
  // 471:     default_value(topics(topic) empty_key_order_set)
  // 472:   
  // 473:   !topic_contents(function_name) true
  // 474:   !topics(topic) topic_contents
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_104, 1);
  // 467: for_each split(paragraph .behind. ':' ','): ($topic)
  // 468:   trim &topic
  // 469:   
  // 470:   $$topic_contents
  // 471:     default_value(topics(topic) empty_key_order_set)
  // 472:   
  // 473:   !topic_contents(function_name) true
  // 474:   !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_96(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // reference: 0
  // references: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 465: ... reference.trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_97;
}
static void cont__29_97(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 465: push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* references */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_98;
}
static void cont__29_98(void) {
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
static void entry__29_93(void) {
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
  // 464: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_94;
}
static void cont__29_94(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 464: ... split(paragraph .behind. ':' ',')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = character__44;
  result_count = 1;
  myself = get__split();
  func = myself->type;
  frame->cont = cont__29_95;
}
static void cont__29_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 464: ... : (reference)
  // 465:   push &references reference.trim
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_96, 1);
  // 464: for_each split(paragraph .behind. ':' ','): (reference)
  // 465:   push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_69(void) {
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
  // 452: $$return_value between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__29_70;
}
static void cont__29_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* return_value */ = arguments->slots[0];
  // 454: -> return_value .has_suffix. '?':
  // 455:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_71, 0);
  // 456: -> return_value .has_suffix. '*':
  // 457:   !return_value
  // 458:     string
  // 459:       range(return_value 1 -2)
  // 460:       " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_78, 0);
  // 453: cond
  // 454:   -> return_value .has_suffix. '?':
  // 455:     !return_value string(range(return_value 1 -2) " (optional)")
  // 456:   -> return_value .has_suffix. '*':
  // 457:     !return_value
  // 458:       string
  // 459:         range(return_value 1 -2)
  // 460:         " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_85;
}
static void entry__29_80(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 459: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_81;
}
static void cont__29_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 459: range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_82;
}
static void cont__29_82(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 457: !return_value
  // 458:   string
  // 459:     range(return_value 1 -2)
  // 460:     " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_83;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_84;
}
static void cont__29_84(void) {
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
static void entry__29_73(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 455: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_74;
}
static void cont__29_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 455: ... range(return_value 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_75;
}
static void cont__29_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 455: !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_76;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_77;
}
static void cont__29_77(void) {
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
static void entry__29_71(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 454: ... return_value .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_72;
}
static void cont__29_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 454: ... :
  // 455:   !return_value string(range(return_value 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_73, 0);
  // 454: -> return_value .has_suffix. '?':
  // 455:   !return_value string(range(return_value 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_78(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 456: ... return_value .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_value */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_79;
}
static void cont__29_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 456: ... :
  // 457:   !return_value
  // 458:     string
  // 459:       range(return_value 1 -2)
  // 460:       " (zero or more arguments)"
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_80, 0);
  // 456: -> return_value .has_suffix. '*':
  // 457:   !return_value
  // 458:     string
  // 459:       range(return_value 1 -2)
  // 460:       " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 461: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_86;
}
static void cont__29_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 461: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_87;
}
static void cont__29_87(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 462: ... return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* return_value */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_88;
}
static void cont__29_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 462: push &return_values return_value = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* return_values */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_89;
}
static void cont__29_89(void) {
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
static void entry__29_33(void) {
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
  // 426: $$parameter between(paragraph sim2c::WHITESPACE ':')
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = character__58;
  result_count = 1;
  myself = get__between();
  func = myself->type;
  frame->cont = cont__29_34;
}
static void cont__29_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* parameter */ = arguments->slots[0];
  // 428: -> parameter .has_suffix. '?':
  // 429:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_35, 0);
  // 430: -> parameter .has_suffix. '*':
  // 431:   !parameter
  // 432:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_42, 0);
  // 433: -> parameter .contains. '=':
  // 434:   !parameter
  // 435:     string
  // 436:       (parameter .before. '=').trim
  // 437:       " (optional; default value: "
  // 438:       (parameter .behind. '=').trim
  // 439:       ")"
  frame->slots[6] /* temp__3 */ = create_closure(entry__29_49, 0);
  // 427: cond
  // 428:   -> parameter .has_suffix. '?':
  // 429:     !parameter string(range(parameter 1 -2) " (optional)")
  // 430:   -> parameter .has_suffix. '*':
  // 431:     !parameter
  // 432:       string(range(parameter 1 -2) " (zero or more arguments)")
  // 433:   -> parameter .contains. '=':
  // 434:     !parameter
  // 435:       string
  // 436:         (parameter .before. '=').trim
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_59;
}
static void entry__29_51(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 436: ... parameter .before. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__29_52;
}
static void cont__29_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 436: ... parameter .before. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_53;
}
static void cont__29_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 438: ... parameter .behind. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_54;
}
static void cont__29_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 438: ... parameter .behind. '=').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_55;
}
static void cont__29_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 434: !parameter
  // 435:   string
  // 436:     (parameter .before. '=').trim
  // 437:     " (optional; default value: "
  // 438:     (parameter .behind. '=').trim
  // 439:     ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_56;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  arguments->slots[3] = string__29_57;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_58;
}
static void cont__29_58(void) {
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
static void entry__29_44(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 432: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_45;
}
static void cont__29_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 432: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_46;
}
static void cont__29_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 431: !parameter
  // 432:   string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_47;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_48;
}
static void cont__29_48(void) {
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
static void entry__29_37(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 429: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_38;
}
static void cont__29_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 429: ... range(parameter 1 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = number__1;
  arguments->slots[2] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_39;
}
static void cont__29_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 429: !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__29_40;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_41;
}
static void cont__29_41(void) {
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
static void entry__29_35(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 428: ... parameter .has_suffix. '?'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__63;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_36;
}
static void cont__29_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 428: ... :
  // 429:   !parameter string(range(parameter 1 -2) " (optional)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_37, 0);
  // 428: -> parameter .has_suffix. '?':
  // 429:   !parameter string(range(parameter 1 -2) " (optional)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_42(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 430: ... parameter .has_suffix. '*'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__42;
  result_count = 1;
  myself = get__has_suffix();
  func = myself->type;
  frame->cont = cont__29_43;
}
static void cont__29_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 430: ... :
  // 431:   !parameter
  // 432:     string(range(parameter 1 -2) " (zero or more arguments)")
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_44, 0);
  // 430: -> parameter .has_suffix. '*':
  // 431:   !parameter
  // 432:     string(range(parameter 1 -2) " (zero or more arguments)")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_49(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 433: ... parameter .contains. '='
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  arguments->slots[1] = character__61;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__29_50;
}
static void cont__29_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 433: ... :
  // 434:   !parameter
  // 435:     string
  // 436:       (parameter .before. '=').trim
  // 437:       " (optional; default value: "
  // 438:       (parameter .behind. '=').trim
  // 439:       ")"
  frame->slots[2] /* temp__2 */ = create_closure(entry__29_51, 0);
  // 433: -> parameter .contains. '=':
  // 434:   !parameter
  // 435:     string
  // 436:       (parameter .before. '=').trim
  // 437:       " (optional; default value: "
  // 438:       (parameter .behind. '=').trim
  // 439:       ")"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_59(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 440: ... paragraph .behind. ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__29_60;
}
static void cont__29_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 440: $description (paragraph .behind. ':').trim
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__trim();
  func = myself->type;
  frame->cont = cont__29_61;
}
static void cont__29_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 441: ... parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* parameter */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_62;
}
static void cont__29_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 441: push &parameters parameter = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_63;
}
static void cont__29_63(void) {
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
static void entry__29_28(void) {
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
  // 423: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_29;
}
static void cont__29_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 419: sequence
  // 420:   "Parameter"
  // 421:   sim2c::WHITESPACE
  // 422:   NAME
  // 423:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 424:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_30;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_31;
}
static void cont__29_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 417: has_prefix
  // 418:   paragraph
  // 419:   sequence
  // 420:     "Parameter"
  // 421:     sim2c::WHITESPACE
  // 422:     NAME
  // 423:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 424:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_32;
}
static void cont__29_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 425: :
  // 426:   $$parameter between(paragraph sim2c::WHITESPACE ':')
  // 427:   cond
  // 428:     -> parameter .has_suffix. '?':
  // 429:       !parameter string(range(parameter 1 -2) " (optional)")
  // 430:     -> parameter .has_suffix. '*':
  // 431:       !parameter
  // 432:         string(range(parameter 1 -2) " (zero or more arguments)")
  // 433:     -> parameter .contains. '=':
  // 434:       !parameter
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_33, 0);
  // 416: ->
  // 417:   has_prefix
  // 418:     paragraph
  // 419:     sequence
  // 420:       "Parameter"
  // 421:       sim2c::WHITESPACE
  // 422:       NAME
  // 423:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 424:       ':'
  // 425:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_64(void) {
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
  // 449: optional(PARAMETER_COUNT_OR_MYSELF)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = var._PARAMETER_COUNT_OR_MYSELF;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_65;
}
static void cont__29_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 445: sequence
  // 446:   "Returns"
  // 447:   sim2c::WHITESPACE
  // 448:   NAME
  // 449:   optional(PARAMETER_COUNT_OR_MYSELF)
  // 450:   ':'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_66;
  arguments->slots[1] = get__sim2c__WHITESPACE();
  arguments->slots[2] = get__NAME();
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  arguments->slots[4] = character__58;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_67;
}
static void cont__29_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 443: has_prefix
  // 444:   paragraph
  // 445:   sequence
  // 446:     "Returns"
  // 447:     sim2c::WHITESPACE
  // 448:     NAME
  // 449:     optional(PARAMETER_COUNT_OR_MYSELF)
  // 450:     ':'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_68;
}
static void cont__29_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 451: :
  // 452:   $$return_value between(paragraph sim2c::WHITESPACE ':')
  // 453:   cond
  // 454:     -> return_value .has_suffix. '?':
  // 455:       !return_value string(range(return_value 1 -2) " (optional)")
  // 456:     -> return_value .has_suffix. '*':
  // 457:       !return_value
  // 458:         string
  // 459:           range(return_value 1 -2)
  // 460:           " (zero or more arguments)"
  // ...
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_69, 0);
  // 442: ->
  // 443:   has_prefix
  // 444:     paragraph
  // 445:     sequence
  // 446:       "Returns"
  // 447:       sim2c::WHITESPACE
  // 448:       NAME
  // 449:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 450:       ':'
  // 451:   :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_90(void) {
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
  // 463: ... paragraph .has_prefix. "See Also:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__29_91;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_92;
}
static void cont__29_92(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 463: ... :
  // 464:   for_each split(paragraph .behind. ':' ','): (reference)
  // 465:     push &references reference.trim
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_93, 0);
  // 463: -> paragraph .has_prefix. "See Also:":
  // 464:   for_each split(paragraph .behind. ':' ','): (reference)
  // 465:     push &references reference.trim
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_99(void) {
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
  // 466: ... paragraph .has_prefix. TOPIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._TOPIC;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_100;
}
static void cont__29_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 466: ... :
  // 467:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 468:     trim &topic
  // 469:     
  // 470:     $$topic_contents
  // 471:       default_value(topics(topic) empty_key_order_set)
  // 472:     
  // 473:     !topic_contents(function_name) true
  // 474:     !topics(topic) topic_contents
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_101, 0);
  // 466: -> paragraph .has_prefix. TOPIC:
  // 467:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 468:     trim &topic
  // 469:     
  // 470:     $$topic_contents
  // 471:       default_value(topics(topic) empty_key_order_set)
  // 472:     
  // 473:     !topic_contents(function_name) true
  // 474:     !topics(topic) topic_contents
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_110(void) {
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
  // 475: ... paragraph .has_prefix. EXAMPLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = var._EXAMPLE;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_111;
}
static void cont__29_111(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 475: ... :
  // 476:   $title (paragraph .before. ':').trim
  // 477:   $text (paragraph .behind. ':').trim
  // 478:   push &examples title = text
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_112, 0);
  // 475: -> paragraph .has_prefix. EXAMPLE:
  // 476:   $title (paragraph .before. ':').trim
  // 477:   $text (paragraph .behind. ':').trim
  // 478:   push &examples title = text
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_119(void) {
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
  // 479: ... paragraph .has_prefix. "Technical Details:"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = string__29_120;
  result_count = 1;
  myself = get__has_prefix();
  func = myself->type;
  frame->cont = cont__29_121;
}
static void cont__29_121(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 479: ... :
  // 480:   $detail (paragraph .behind. ':').trim
  // 481:   if
  // 482:     detail == "":
  // 483:       !technical_details empty_list
  // 484:     :
  // 485:       !technical_details list(detail)
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_122, 0);
  // 479: -> paragraph .has_prefix. "Technical Details:":
  // 480:   $detail (paragraph .behind. ':').trim
  // 481:   if
  // 482:     detail == "":
  // 483:       !technical_details empty_list
  // 484:     :
  // 485:       !technical_details list(detail)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_129(void) {
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
  // 490: ... '/', NAME
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = get__NAME();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_130;
}
static void cont__29_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__4 */ = arguments->slots[0];
  // 490: ... optional('/', NAME)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__4 */;
  result_count = 1;
  myself = get__optional();
  func = myself->type;
  frame->cont = cont__29_131;
}
static void cont__29_131(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 490: '<', NAME, optional('/', NAME), '>'
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__60;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  arguments->slots[3] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_132;
}
static void cont__29_132(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 489: =
  // 490:   '<', NAME, optional('/', NAME), '>'
  // 491:   : ($reference)
  // 492:     range &reference 2 -2
  // 493:     resolve_reference &reference
  // 494:     -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  arguments->slots[1] = func__29_133;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_142;
}
static void entry__29_133(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 492: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__29_134;
}
static void cont__29_134(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 492: range &reference 2 -2
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__29_135;
}
static void cont__29_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 493: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__29_136;
}
static void cont__29_136(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 494: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_137;
}
static void cont__29_137(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 494: ... "[@(reference)](@(reference.mangled).html)"
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__29_138;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  arguments->slots[2] = string__29_139;
  arguments->slots[3] = frame->slots[2] /* temp__2 */;
  arguments->slots[4] = string__29_140;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_141;
}
static void cont__29_141(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 494: -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 487: replace_all
  // 488:   &paragraph
  // 489:   =
  // 490:     '<', NAME, optional('/', NAME), '>'
  // 491:     : ($reference)
  // 492:       range &reference 2 -2
  // 493:       resolve_reference &reference
  // 494:       -> "[@(reference)](@(reference.mangled).html)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* paragraph */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__29_143;
}
static void cont__29_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* paragraph */ = arguments->slots[0];
  // 496: short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_144;
}
static void cont__29_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 496: ... :
  // 497:   if
  // 498:     technical_details.is_defined:
  // 499:       push &technical_details paragraph
  // 500:     :
  // 501:       push &descriptions paragraph
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_145, 0);
  // 502: :
  // 503:   !short_description paragraph
  frame->slots[6] /* temp__3 */ = create_closure(entry__29_151, 0);
  // 495: if
  // 496:   short_description.is_defined:
  // 497:     if
  // 498:       technical_details.is_defined:
  // 499:         push &technical_details paragraph
  // 500:       :
  // 501:         push &descriptions paragraph
  // 502:   :
  // 503:     !short_description paragraph
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_27(void) {
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
  // 416: ->
  // 417:   has_prefix
  // 418:     paragraph
  // 419:     sequence
  // 420:       "Parameter"
  // 421:       sim2c::WHITESPACE
  // 422:       NAME
  // 423:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 424:       ':'
  // 425:   :
  // ...
  frame->slots[9] /* temp__1 */ = create_closure(entry__29_28, 0);
  // 442: ->
  // 443:   has_prefix
  // 444:     paragraph
  // 445:     sequence
  // 446:       "Returns"
  // 447:       sim2c::WHITESPACE
  // 448:       NAME
  // 449:       optional(PARAMETER_COUNT_OR_MYSELF)
  // 450:       ':'
  // 451:   :
  // ...
  frame->slots[10] /* temp__2 */ = create_closure(entry__29_64, 0);
  // 463: -> paragraph .has_prefix. "See Also:":
  // 464:   for_each split(paragraph .behind. ':' ','): (reference)
  // 465:     push &references reference.trim
  frame->slots[11] /* temp__3 */ = create_closure(entry__29_90, 0);
  // 466: -> paragraph .has_prefix. TOPIC:
  // 467:   for_each split(paragraph .behind. ':' ','): ($topic)
  // 468:     trim &topic
  // 469:     
  // 470:     $$topic_contents
  // 471:       default_value(topics(topic) empty_key_order_set)
  // 472:     
  // 473:     !topic_contents(function_name) true
  // 474:     !topics(topic) topic_contents
  frame->slots[12] /* temp__4 */ = create_closure(entry__29_99, 0);
  // 475: -> paragraph .has_prefix. EXAMPLE:
  // 476:   $title (paragraph .before. ':').trim
  // 477:   $text (paragraph .behind. ':').trim
  // 478:   push &examples title = text
  frame->slots[13] /* temp__5 */ = create_closure(entry__29_110, 0);
  // 479: -> paragraph .has_prefix. "Technical Details:":
  // 480:   $detail (paragraph .behind. ':').trim
  // 481:   if
  // 482:     detail == "":
  // 483:       !technical_details empty_list
  // 484:     :
  // 485:       !technical_details list(detail)
  frame->slots[14] /* temp__6 */ = create_closure(entry__29_119, 0);
  // 486: :
  // 487:   replace_all
  // 488:     &paragraph
  // 489:     =
  // 490:       '<', NAME, optional('/', NAME), '>'
  // 491:       : ($reference)
  // 492:         range &reference 2 -2
  // 493:         resolve_reference &reference
  // 494:         -> "[@(reference)](@(reference.mangled).html)"
  // 495:   if
  // ...
  frame->slots[15] /* temp__7 */ = create_closure(entry__29_129, 0);
  // 415: cond
  // 416:   ->
  // 417:     has_prefix
  // 418:       paragraph
  // 419:       sequence
  // 420:         "Parameter"
  // 421:         sim2c::WHITESPACE
  // 422:         NAME
  // 423:         optional(PARAMETER_COUNT_OR_MYSELF)
  // 424:         ':'
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
  frame->cont = frame->cont;
}
static void entry__29_25(void) {
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
  // 413: $paragraphs remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__29_26;
}
static void cont__29_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[9] /* paragraphs */, arguments->slots[0]);
  // 414: ... : ($paragraph)
  // 415:   cond
  // 416:     ->
  // 417:       has_prefix
  // 418:         paragraph
  // 419:         sequence
  // 420:           "Parameter"
  // 421:           sim2c::WHITESPACE
  // 422:           NAME
  // 423:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  frame->slots[10] /* temp__1 */ = create_closure(entry__29_27, 1);
  // 414: for_each paragraphs: ($paragraph)
  // 415:   cond
  // 416:     ->
  // 417:       has_prefix
  // 418:         paragraph
  // 419:         sequence
  // 420:           "Parameter"
  // 421:           sim2c::WHITESPACE
  // 422:           NAME
  // 423:           optional(PARAMETER_COUNT_OR_MYSELF)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* paragraphs */;
  arguments->slots[1] = frame->slots[10] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_152(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 504: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__29_153;
}
static void cont__29_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 504: ... kind_of(info) == FUNCTION
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._FUNCTION;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_154;
}
static void cont__29_154(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 504: ... :
  // 505:   for_each parameters_of(info): (parameter)
  // 506:     case
  // 507:       parameter_kind_of(parameter)
  // 508:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 509:         pass
  // 510:       :
  // 511:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:         cond
  // 513:           -> parameter.is_an_optional_item:
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_155, 0);
  // 504: if kind_of(info) == FUNCTION:
  // 505:   for_each parameters_of(info): (parameter)
  // 506:     case
  // 507:       parameter_kind_of(parameter)
  // 508:       MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 509:         pass
  // 510:       :
  // 511:         $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:         cond
  // 513:           -> parameter.is_an_optional_item:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_196;
}
static void entry__29_160(void) {
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
  // 511: ... identifier_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__29_161;
}
static void cont__29_161(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 511: ... name_of(identifier_of(parameter))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__29_162;
}
static void cont__29_162(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 511: $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = character__36;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__29_163;
}
static void cont__29_163(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 513: -> parameter.is_an_optional_item:
  // 514:   if
  // 515:     default_value_of(parameter).is_defined:
  // 516:       write_to
  // 517:         &name
  // 518:         " (optional; default value: "
  // 519:         default_value_of(parameter).to_string
  // 520:         ")"
  // 521:     :
  // 522:       append &name " (optional)"
  frame->slots[4] /* temp__1 */ = create_closure(entry__29_164, 0);
  // 523: -> parameter.is_an_expanded_item:
  // 524:   append &name " (zero or more arguments)"
  frame->slots[5] /* temp__2 */ = create_closure(entry__29_178, 0);
  // 512: cond
  // 513:   -> parameter.is_an_optional_item:
  // 514:     if
  // 515:       default_value_of(parameter).is_defined:
  // 516:         write_to
  // 517:           &name
  // 518:           " (optional; default value: "
  // 519:           default_value_of(parameter).to_string
  // 520:           ")"
  // 521:       :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__cond();
  func = myself->type;
  frame->cont = cont__29_183;
}
static void entry__29_180(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 524: append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_181;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_182;
}
static void cont__29_182(void) {
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
static void entry__29_169(void) {
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
  // 519: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__29_170;
}
static void cont__29_170(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 519: default_value_of(parameter).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__29_171;
}
static void cont__29_171(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 516: write_to
  // 517:   &name
  // 518:   " (optional; default value: "
  // 519:   default_value_of(parameter).to_string
  // 520:   ")"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_172;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  arguments->slots[3] = string__29_173;
  result_count = 1;
  myself = get__write_to();
  func = myself->type;
  frame->cont = cont__29_174;
}
static void cont__29_174(void) {
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
static void entry__29_175(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 522: append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = string__29_176;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__29_177;
}
static void cont__29_177(void) {
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
static void entry__29_166(void) {
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
  // 515: default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__29_167;
}
static void cont__29_167(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 515: default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_168;
}
static void cont__29_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 515: ... :
  // 516:   write_to
  // 517:     &name
  // 518:     " (optional; default value: "
  // 519:     default_value_of(parameter).to_string
  // 520:     ")"
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_169, 0);
  // 521: :
  // 522:   append &name " (optional)"
  frame->slots[5] /* temp__4 */ = create_closure(entry__29_175, 0);
  // 514: if
  // 515:   default_value_of(parameter).is_defined:
  // 516:     write_to
  // 517:       &name
  // 518:       " (optional; default value: "
  // 519:       default_value_of(parameter).to_string
  // 520:       ")"
  // 521:   :
  // 522:     append &name " (optional)"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_164(void) {
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
  // 513: ... parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__29_165;
}
static void cont__29_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 513: ... :
  // 514:   if
  // 515:     default_value_of(parameter).is_defined:
  // 516:       write_to
  // 517:         &name
  // 518:         " (optional; default value: "
  // 519:         default_value_of(parameter).to_string
  // 520:         ")"
  // 521:     :
  // 522:       append &name " (optional)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_166, 0);
  // 513: -> parameter.is_an_optional_item:
  // 514:   if
  // 515:     default_value_of(parameter).is_defined:
  // 516:       write_to
  // 517:         &name
  // 518:         " (optional; default value: "
  // 519:         default_value_of(parameter).to_string
  // 520:         ")"
  // 521:     :
  // 522:       append &name " (optional)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_178(void) {
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
  // 523: ... parameter.is_an_expanded_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__is_an_expanded_item();
  func = myself->type;
  frame->cont = cont__29_179;
}
static void cont__29_179(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 523: ... :
  // 524:   append &name " (zero or more arguments)"
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_180, 0);
  // 523: -> parameter.is_an_expanded_item:
  // 524:   append &name " (zero or more arguments)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_183(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 528: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_184;
}
static void cont__29_184(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 528: ... remark_lines_of(parameter).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_185;
}
static void cont__29_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 528: not(remark_lines_of(parameter).is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__29_186;
}
static void cont__29_186(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 529: -> remark_lines_of(parameter).to_paragraphs(1)
  frame->slots[7] /* temp__4 */ = create_closure(entry__29_187, 0);
  // 526: $description
  // 527:   if
  // 528:     not(remark_lines_of(parameter).is_empty)
  // 529:     -> remark_lines_of(parameter).to_paragraphs(1)
  // 530:     -> ""
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  arguments->slots[2] = func__29_191;
  result_count = 1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_192;
}
static void entry__29_187(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 529: ... remark_lines_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__29_188;
}
static void cont__29_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 529: ... remark_lines_of(parameter).to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__29_189;
}
static void cont__29_189(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 529: ... remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__29_190;
}
static void cont__29_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 529: -> remark_lines_of(parameter).to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__29_191(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 530: -> ""
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = empty_string;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* description */, arguments->slots[0]);
  // 532: ... name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* name */;
  arguments->slots[1] = frame->slots[3] /* description */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_193;
}
static void cont__29_193(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 532: push &parameters name = description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* parameters */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__29_194;
}
static void cont__29_194(void) {
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
static void entry__29_195(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 509: pass
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__pass();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_157(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // parameter: 0
  // parameters: 1
  frame->slots[1] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 507: parameter_kind_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__29_158;
}
static void cont__29_158(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 508: MYSELF_PARAMETER, CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__MYSELF_PARAMETER();
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_159;
}
static void cont__29_159(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 510: :
  // 511:   $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:   cond
  // 513:     -> parameter.is_an_optional_item:
  // 514:       if
  // 515:         default_value_of(parameter).is_defined:
  // 516:           write_to
  // 517:             &name
  // 518:             " (optional; default value: "
  // 519:             default_value_of(parameter).to_string
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_160, 0);
  // 506: case
  // 507:   parameter_kind_of(parameter)
  // 508:   MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 509:     pass
  // 510:   :
  // 511:     $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:     cond
  // 513:       -> parameter.is_an_optional_item:
  // 514:         if
  // 515:           default_value_of(parameter).is_defined:
  // ...
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = func__29_195;
  arguments->slots[3] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_155(void) {
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
  // 505: ... parameters_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__29_156;
}
static void cont__29_156(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 505: ... : (parameter)
  // 506:   case
  // 507:     parameter_kind_of(parameter)
  // 508:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 509:       pass
  // 510:     :
  // 511:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:       cond
  // 513:         -> parameter.is_an_optional_item:
  // 514:           if
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_157, 1);
  // 505: for_each parameters_of(info): (parameter)
  // 506:   case
  // 507:     parameter_kind_of(parameter)
  // 508:     MYSELF_PARAMETER, CONTINUATION_PARAMETER:
  // 509:       pass
  // 510:     :
  // 511:       $$name name_of(identifier_of(parameter)) .without_prefix. '$'
  // 512:       cond
  // 513:         -> parameter.is_an_optional_item:
  // 514:           if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_196(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 533: ... short_description.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* short_description */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_197;
}
static void cont__29_197(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 533: ... : P short_description
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_198, 0);
  // 533: if short_description.is_defined: P short_description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_199;
}
static void entry__29_198(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // short_description: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* short_description */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 533: ... P short_description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* short_description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_199(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 534: ... parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_200;
}
static void cont__29_200(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 534: ... :
  // 535:   H2 "Parameters"
  // 536:   DL:
  // 537:     for_each parameters: (parameter)
  // 538:       DT key_of(parameter)
  // 539:       DD: P std::value_of(parameter)
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_201, 0);
  // 534: unless parameters.is_empty:
  // 535:   H2 "Parameters"
  // 536:   DL:
  // 537:     for_each parameters: (parameter)
  // 538:       DT key_of(parameter)
  // 539:       DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_210;
}
static void entry__29_208(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 539: ... std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_209;
}
static void cont__29_209(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 539: ... P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_205(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 538: ... key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* parameter */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_206;
}
static void cont__29_206(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 538: DT key_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__29_207;
}
static void cont__29_207(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 539: ... : P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_208, 0);
  // 539: DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_204(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 537: for_each parameters: (parameter)
  // 538:   DT key_of(parameter)
  // 539:   DD: P std::value_of(parameter)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameters */;
  arguments->slots[1] = func__29_205;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_201(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[3]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 535: H2 "Parameters"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_202;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_203;
}
static void cont__29_203(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 536: ... :
  // 537:   for_each parameters: (parameter)
  // 538:     DT key_of(parameter)
  // 539:     DD: P std::value_of(parameter)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_204, 0);
  // 536: DL:
  // 537:   for_each parameters: (parameter)
  // 538:     DT key_of(parameter)
  // 539:     DD: P std::value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_210(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 540: ... return_values.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[4])->contents /* return_values */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_211;
}
static void cont__29_211(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 540: ... :
  // 541:   H2 "Returns"
  // 542:   DL:
  // 543:     for_each return_values: (return_value)
  // 544:       DT key_of(return_value)
  // 545:       DD: P std::value_of(return_value)
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_212, 0);
  // 540: unless return_values.is_empty:
  // 541:   H2 "Returns"
  // 542:   DL:
  // 543:     for_each return_values: (return_value)
  // 544:       DT key_of(return_value)
  // 545:       DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_221;
}
static void entry__29_219(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_value */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 545: ... std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_220;
}
static void cont__29_220(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 545: ... P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_216(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_value: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 544: ... key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* return_value */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_217;
}
static void cont__29_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 544: DT key_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__DT();
  func = myself->type;
  frame->cont = cont__29_218;
}
static void cont__29_218(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 545: ... : P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_219, 0);
  // 545: DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_215(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 543: for_each return_values: (return_value)
  // 544:   DT key_of(return_value)
  // 545:   DD: P std::value_of(return_value)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* return_values */;
  arguments->slots[1] = func__29_216;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_212(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // return_values: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* return_values */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 541: H2 "Returns"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_213;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_214;
}
static void cont__29_214(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 542: ... :
  // 543:   for_each return_values: (return_value)
  // 544:     DT key_of(return_value)
  // 545:     DD: P std::value_of(return_value)
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_215, 0);
  // 542: DL:
  // 543:   for_each return_values: (return_value)
  // 544:     DT key_of(return_value)
  // 545:     DD: P std::value_of(return_value)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__DL();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_221(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 546: ... descriptions.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[5])->contents /* descriptions */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_222;
}
static void cont__29_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 546: ... :
  // 547:   H2 "Description"
  // 548:   for_each descriptions: (description) P description
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_223, 0);
  // 546: unless descriptions.is_empty:
  // 547:   H2 "Description"
  // 548:   for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_227;
}
static void entry__29_226(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // description: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 548: ... P description
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* description */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_223(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // descriptions: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* descriptions */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 547: H2 "Description"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_224;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_225;
}
static void cont__29_225(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 548: for_each descriptions: (description) P description
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* descriptions */;
  arguments->slots[1] = func__29_226;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_227(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 549: ... technical_details.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[6])->contents /* technical_details */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__29_228;
}
static void cont__29_228(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 549: ... :
  // 550:   H2 "Technical Details"
  // 551:   for_each technical_details: (detail) P detail
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_229, 0);
  // 549: if technical_details.is_defined:
  // 550:   H2 "Technical Details"
  // 551:   for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_233;
}
static void entry__29_232(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // detail: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 551: ... P detail
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* detail */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_229(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // technical_details: 0
  frame->slots[0] = myself->closure.frame->slots[6]; /* technical_details */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 550: H2 "Technical Details"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_230;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_231;
}
static void cont__29_231(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 551: for_each technical_details: (detail) P detail
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* technical_details */;
  arguments->slots[1] = func__29_232;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_233(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 552: ... references.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[7])->contents /* references */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_234;
}
static void cont__29_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 552: ... :
  // 553:   H2 "See Also"
  // 554:   P:
  // 555:     for_each references: ($reference)
  // 556:       resolve_reference &reference
  // 557:       A "href" = "@(reference.mangled).html" reference
  // 558:       BR
  frame->slots[12] /* temp__2 */ = create_closure(entry__29_235, 0);
  // 552: unless references.is_empty:
  // 553:   H2 "See Also"
  // 554:   P:
  // 555:     for_each references: ($reference)
  // 556:       resolve_reference &reference
  // 557:       A "href" = "@(reference.mangled).html" reference
  // 558:       BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_247;
}
static void entry__29_239(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* reference */ = create_cell_with_contents(arguments->slots[0]);
  // 556: resolve_reference &reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__29_240;
}
static void cont__29_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* reference */ = arguments->slots[0];
  // 557: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_241;
}
static void cont__29_241(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 557: ... "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_242;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_243;
}
static void cont__29_243(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 557: ... "href" = "@(reference.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_244;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_245;
}
static void cont__29_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 557: A "href" = "@(reference.mangled).html" reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* reference */;
  result_count = 0;
  myself = get__A();
  func = myself->type;
  frame->cont = cont__29_246;
}
static void cont__29_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 558: BR
  argument_count = 0;
  arguments = node_p;
  result_count = frame->caller_result_count;
  myself = get__BR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_238(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 555: for_each references: ($reference)
  // 556:   resolve_reference &reference
  // 557:   A "href" = "@(reference.mangled).html" reference
  // 558:   BR
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* references */;
  arguments->slots[1] = func__29_239;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_235(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[7]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 553: H2 "See Also"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_236;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_237;
}
static void cont__29_237(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 554: ... :
  // 555:   for_each references: ($reference)
  // 556:     resolve_reference &reference
  // 557:     A "href" = "@(reference.mangled).html" reference
  // 558:     BR
  frame->slots[1] /* temp__1 */ = create_closure(entry__29_238, 0);
  // 554: P:
  // 555:   for_each references: ($reference)
  // 556:     resolve_reference &reference
  // 557:     A "href" = "@(reference.mangled).html" reference
  // 558:     BR
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_247(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 559: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__29_248;
}
static void cont__29_248(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 559: ... types_of(info).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__29_249;
}
static void cont__29_249(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 559: ... :
  // 560:   H2 "Implemented by"
  // 561:   TABLE:
  // 562:     for_each types_of(info): (name)
  // 563:       $method string(name '/' function_name)
  // 564:       TR:
  // 565:         TD: A "href" = "@(name.mangled).html" name
  // 566:         TD "&nbsp;as&nbsp;"
  // 567:         TD: A "href" = "@(method.mangled).html" method
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_250, 0);
  // 559: unless types_of(info).is_empty:
  // 560:   H2 "Implemented by"
  // 561:   TABLE:
  // 562:     for_each types_of(info): (name)
  // 563:       $method string(name '/' function_name)
  // 564:       TR:
  // 565:         TD: A "href" = "@(name.mangled).html" name
  // 566:         TD "&nbsp;as&nbsp;"
  // 567:         TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__29_273;
}
static void entry__29_267(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* method */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 567: ... method.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method */;
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
  // 567: ... "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_269;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_270;
}
static void cont__29_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 567: ... "href" = "@(method.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_271;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_272;
}
static void cont__29_272(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 567: ... A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_257(void) {
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
  // 565: ... : A "href" = "@(name.mangled).html" name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_258, 0);
  // 565: TD: A "href" = "@(name.mangled).html" name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_264;
}
static void entry__29_258(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 565: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_259;
}
static void cont__29_259(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 565: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_260;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_261;
}
static void cont__29_261(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 565: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_262;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_263;
}
static void cont__29_263(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 565: ... A "href" = "@(name.mangled).html" name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_264(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 566: TD "&nbsp;as&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_265;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_266;
}
static void cont__29_266(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 567: ... : A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_267, 0);
  // 567: TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_255(void) {
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
  // 563: $method string(name '/' function_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[1] /* function_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_256;
}
static void cont__29_256(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* method */, arguments->slots[0]);
  // 564: ... :
  // 565:   TD: A "href" = "@(name.mangled).html" name
  // 566:   TD "&nbsp;as&nbsp;"
  // 567:   TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_257, 0);
  // 564: TR:
  // 565:   TD: A "href" = "@(name.mangled).html" name
  // 566:   TD "&nbsp;as&nbsp;"
  // 567:   TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_253(void) {
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
  // 562: ... types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__29_254;
}
static void cont__29_254(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 562: ... : (name)
  // 563:   $method string(name '/' function_name)
  // 564:   TR:
  // 565:     TD: A "href" = "@(name.mangled).html" name
  // 566:     TD "&nbsp;as&nbsp;"
  // 567:     TD: A "href" = "@(method.mangled).html" method
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_255, 1);
  // 562: for_each types_of(info): (name)
  // 563:   $method string(name '/' function_name)
  // 564:   TR:
  // 565:     TD: A "href" = "@(name.mangled).html" name
  // 566:     TD "&nbsp;as&nbsp;"
  // 567:     TD: A "href" = "@(method.mangled).html" method
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_250(void) {
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
  // 560: H2 "Implemented by"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_251;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_252;
}
static void cont__29_252(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 561: ... :
  // 562:   for_each types_of(info): (name)
  // 563:     $method string(name '/' function_name)
  // 564:     TR:
  // 565:       TD: A "href" = "@(name.mangled).html" name
  // 566:       TD "&nbsp;as&nbsp;"
  // 567:       TD: A "href" = "@(method.mangled).html" method
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_253, 0);
  // 561: TABLE:
  // 562:   for_each types_of(info): (name)
  // 563:     $method string(name '/' function_name)
  // 564:     TR:
  // 565:       TD: A "href" = "@(name.mangled).html" name
  // 566:       TD "&nbsp;as&nbsp;"
  // 567:       TD: A "href" = "@(method.mangled).html" method
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_273(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 568: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__29_274;
}
static void cont__29_274(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 568: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[12] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__29_275;
}
static void cont__29_275(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 568: ... :
  // 569:   H2 "Supported Polymorphic Functions"
  // 570:   TABLE:
  // 571:     for_each methods_of(info): (method_name _method_info)
  // 572:       TR:
  // 573:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:         TD "&nbsp;"
  // 575:         TD:
  // 576:           A
  // 577:             =
  // ...
  frame->slots[13] /* temp__3 */ = create_closure(entry__29_276, 0);
  // 568: if kind_of(info) == TYPE:
  // 569:   H2 "Supported Polymorphic Functions"
  // 570:   TABLE:
  // 571:     for_each methods_of(info): (method_name _method_info)
  // 572:       TR:
  // 573:         TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:         TD "&nbsp;"
  // 575:         TD:
  // 576:           A
  // 577:             =
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__29_300;
}
static void entry__29_292(void) {
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
  // 579: ... function_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_293;
}
static void cont__29_293(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 579: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_294;
}
static void cont__29_294(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 579: "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__29_295;
  arguments->slots[2] = frame->slots[5] /* temp__4 */;
  arguments->slots[3] = string__29_296;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_297;
}
static void cont__29_297(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 577: =
  // 578:   "href"
  // 579:   "@(function_name.mangled)___@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_298;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 576: A
  // 577:   =
  // 578:     "href"
  // 579:     "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:   function_name
  // 581:   '/'
  // 582:   method_name
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
  frame->cont = frame->cont;
}
static void entry__29_282(void) {
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
  // 573: ... : A "href" = "@(method_name.mangled).html" method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_283, 0);
  // 573: TD: A "href" = "@(method_name.mangled).html" method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_289;
}
static void entry__29_283(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // method_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* method_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 573: ... method_name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__29_284;
}
static void cont__29_284(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 573: ... "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__29_285;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_286;
}
static void cont__29_286(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 573: ... "href" = "@(method_name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_287;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_288;
}
static void cont__29_288(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 573: ... A "href" = "@(method_name.mangled).html" method_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* method_name */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_289(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 574: TD "&nbsp;"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_290;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__29_291;
}
static void cont__29_291(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 575: ... :
  // 576:   A
  // 577:     =
  // 578:       "href"
  // 579:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:     function_name
  // 581:     '/'
  // 582:     method_name
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_292, 0);
  // 575: TD:
  // 576:   A
  // 577:     =
  // 578:       "href"
  // 579:       "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:     function_name
  // 581:     '/'
  // 582:     method_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_281(void) {
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
  // 572: ... :
  // 573:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:   TD "&nbsp;"
  // 575:   TD:
  // 576:     A
  // 577:       =
  // 578:         "href"
  // 579:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:       function_name
  // 581:       '/'
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__29_282, 0);
  // 572: TR:
  // 573:   TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:   TD "&nbsp;"
  // 575:   TD:
  // 576:     A
  // 577:       =
  // 578:         "href"
  // 579:         "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:       function_name
  // 581:       '/'
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_279(void) {
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
  // 571: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__29_280;
}
static void cont__29_280(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 571: ... : (method_name _method_info)
  // 572:   TR:
  // 573:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:     TD "&nbsp;"
  // 575:     TD:
  // 576:       A
  // 577:         =
  // 578:           "href"
  // 579:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:         function_name
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_281, 2);
  // 571: for_each methods_of(info): (method_name _method_info)
  // 572:   TR:
  // 573:     TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:     TD "&nbsp;"
  // 575:     TD:
  // 576:       A
  // 577:         =
  // 578:           "href"
  // 579:           "@(function_name.mangled)___@(method_name.mangled).html"
  // 580:         function_name
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_276(void) {
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
  // 569: H2 "Supported Polymorphic Functions"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__29_277;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_278;
}
static void cont__29_278(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 570: ... :
  // 571:   for_each methods_of(info): (method_name _method_info)
  // 572:     TR:
  // 573:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:       TD "&nbsp;"
  // 575:       TD:
  // 576:         A
  // 577:           =
  // 578:             "href"
  // 579:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__29_279, 0);
  // 570: TABLE:
  // 571:   for_each methods_of(info): (method_name _method_info)
  // 572:     TR:
  // 573:       TD: A "href" = "@(method_name.mangled).html" method_name
  // 574:       TD "&nbsp;"
  // 575:       TD:
  // 576:         A
  // 577:           =
  // 578:             "href"
  // 579:             "@(function_name.mangled)___@(method_name.mangled).html"
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_300(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 585: function_name .truncate_until. '/'
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* function_name */;
  arguments->slots[1] = character__47;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__29_301;
}
static void cont__29_301(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 584: $function_basename
  // 585:   function_name .truncate_until. '/' .truncate_until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = string__29_302;
  result_count = 1;
  myself = get__truncate_until();
  func = myself->type;
  frame->cont = cont__29_303;
}
static void cont__29_303(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[10] /* function_basename */, arguments->slots[0]);
  // 587: ... : (example)
  // 588:   $title key_of(example)
  // 589:   $text std::value_of(example)
  // 590:   H2 title
  // 591:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 592:     PRE
  // 593:       replace_all
  // 594:         text
  // 595:         =
  // 596:           sequence
  // ...
  frame->slots[11] /* temp__1 */ = create_closure(entry__29_304, 1);
  // 587: for_each examples: (example)
  // 588:   $title key_of(example)
  // 589:   $text std::value_of(example)
  // 590:   H2 title
  // 591:   DIV "class" = title .truncate_from. alt(' ' ':'):
  // 592:     PRE
  // 593:       replace_all
  // 594:         text
  // 595:         =
  // 596:           sequence
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[8])->contents /* examples */;
  arguments->slots[1] = frame->slots[11] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__29_324;
}
static void entry__29_312(void) {
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
  // 598: ... not_followed_by('@quot;')
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = character__34;
  result_count = 1;
  myself = get__not_followed_by();
  func = myself->type;
  frame->cont = cont__29_313;
}
static void cont__29_313(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__6 */ = arguments->slots[0];
  // 598: ... not_followed_by('@quot;'), ANY_CHARACTER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__6 */;
  arguments->slots[1] = get__ANY_CHARACTER();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__29_314;
}
static void cont__29_314(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__5 */ = arguments->slots[0];
  // 598: many(not_followed_by('@quot;'), ANY_CHARACTER)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__many();
  func = myself->type;
  frame->cont = cont__29_315;
}
static void cont__29_315(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 596: sequence
  // 597:   '@quot;'
  // 598:   many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:   '@quot;'
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = character__34;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  arguments->slots[2] = character__34;
  result_count = 1;
  myself = get__sequence();
  func = myself->type;
  frame->cont = cont__29_316;
}
static void cont__29_316(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 595: =
  // 596:   sequence
  // 597:     '@quot;'
  // 598:     many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:     '@quot;'
  // 600:   : (string_literal)
  // 601:     -> string_literal
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = func__29_317;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_318;
}
static void entry__29_317(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // string_literal: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 601: -> string_literal
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* string_literal */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__29_318(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 602: ... string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_319;
  arguments->slots[1] = frame->slots[1] /* function_basename */;
  arguments->slots[2] = string__29_320;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__29_321;
}
static void cont__29_321(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__8 */ = arguments->slots[0];
  // 602: function_basename = string("**" function_basename "**")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* function_basename */;
  arguments->slots[1] = frame->slots[9] /* temp__8 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_322;
}
static void cont__29_322(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__7 */ = arguments->slots[0];
  // 593: replace_all
  // 594:   text
  // 595:   =
  // 596:     sequence
  // 597:       '@quot;'
  // 598:       many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:       '@quot;'
  // 600:     : (string_literal)
  // 601:       -> string_literal
  // 602:   function_basename = string("**" function_basename "**")
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* text */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[8] /* temp__7 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__29_323;
}
static void cont__29_323(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 592: PRE
  // 593:   replace_all
  // 594:     text
  // 595:     =
  // 596:       sequence
  // 597:         '@quot;'
  // 598:         many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:         '@quot;'
  // 600:       : (string_literal)
  // 601:         -> string_literal
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__PRE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__29_304(void) {
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
  // 588: $title key_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__key_of();
  func = myself->type;
  frame->cont = cont__29_305;
}
static void cont__29_305(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* title */, arguments->slots[0]);
  // 589: $text std::value_of(example)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* example */;
  result_count = 1;
  myself = get__std__value_of();
  func = myself->type;
  frame->cont = cont__29_306;
}
static void cont__29_306(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* text */, arguments->slots[0]);
  // 590: H2 title
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  result_count = 0;
  myself = get__H2();
  func = myself->type;
  frame->cont = cont__29_307;
}
static void cont__29_307(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 591: ... alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = character__58;
  result_count = 1;
  myself = get__alt();
  func = myself->type;
  frame->cont = cont__29_308;
}
static void cont__29_308(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__3 */ = arguments->slots[0];
  // 591: ... title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* title */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 1;
  myself = get__truncate_from();
  func = myself->type;
  frame->cont = cont__29_309;
}
static void cont__29_309(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 591: ... "class" = title .truncate_from. alt(' ' ':')
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_310;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_311;
}
static void cont__29_311(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 591: ... :
  // 592:   PRE
  // 593:     replace_all
  // 594:       text
  // 595:       =
  // 596:         sequence
  // 597:           '@quot;'
  // 598:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:           '@quot;'
  // 600:         : (string_literal)
  // ...
  frame->slots[7] /* temp__4 */ = create_closure(entry__29_312, 0);
  // 591: DIV "class" = title .truncate_from. alt(' ' ':'):
  // 592:   PRE
  // 593:     replace_all
  // 594:       text
  // 595:       =
  // 596:         sequence
  // 597:           '@quot;'
  // 598:           many(not_followed_by('@quot;'), ANY_CHARACTER)
  // 599:           '@quot;'
  // 600:         : (string_literal)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__29_324(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 604: "class" = "footer"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__29_325;
  arguments->slots[1] = string__29_326;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__29_327;
}
static void cont__29_327(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__1 */ = arguments->slots[0];
  // 605: ... filename_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = var._filename_of;
  func = myself->type;
  frame->cont = cont__29_328;
}
static void cont__29_328(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[14] /* temp__4 */ = arguments->slots[0];
  // 605: ... filename_of(info) .without_prefix. path_prefix
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[14] /* temp__4 */;
  arguments->slots[1] = var._path_prefix;
  result_count = 1;
  myself = get__without_prefix();
  func = myself->type;
  frame->cont = cont__29_329;
}
static void cont__29_329(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[13] /* temp__3 */ = arguments->slots[0];
  // 605: "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__29_330;
  arguments->slots[1] = frame->slots[13] /* temp__3 */;
  arguments->slots[2] = string__29_331;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__29_332;
}
static void cont__29_332(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[12] /* temp__2 */ = arguments->slots[0];
  // 603: DIV
  // 604:   "class" = "footer"
  // 605:   "(defined in @(filename_of(info) .without_prefix. path_prefix))@nl;"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[11] /* temp__1 */;
  arguments->slots[1] = frame->slots[12] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__DIV();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 385: ... function_name.mangled
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
  // 385: ... "html/@(function_name.mangled).html"
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
  // 385: ... :
  // 386:   link_bar
  // 387:   if
  // 388:     function_name .contains. '/':
  // 389:       $type function_name .before. '/'
  // 390:       $method function_name .behind. '/'
  // 391:       H1
  // 392:         string
  // 393:           '['
  // 394:           type
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__29_8, 0);
  // 385: create_page "html/@(function_name.mangled).html":
  // 386:   link_bar
  // 387:   if
  // 388:     function_name .contains. '/':
  // 389:       $type function_name .before. '/'
  // 390:       $method function_name .behind. '/'
  // 391:       H1
  // 392:         string
  // 393:           '['
  // 394:           type
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
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
  // 384: ... function_name.is_defined
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
  // 384: ... :
  // 385:   create_page "html/@(function_name.mangled).html":
  // 386:     link_bar
  // 387:     if
  // 388:       function_name .contains. '/':
  // 389:         $type function_name .before. '/'
  // 390:         $method function_name .behind. '/'
  // 391:         H1
  // 392:           string
  // 393:             '['
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__29_3, 0);
  // 384: if function_name.is_defined:
  // 385:   create_page "html/@(function_name.mangled).html":
  // 386:     link_bar
  // 387:     if
  // 388:       function_name .contains. '/':
  // 389:         $type function_name .before. '/'
  // 390:         $method function_name .behind. '/'
  // 391:         H1
  // 392:           string
  // 393:             '['
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_1(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // path: 0
  // return__1: 1
  frame->slots[1] /* return__1 */ = create_continuation();
  // _define %html::encode 
  // : ($text tag _arg_str)
  // std::equal temp__1 tag "p"
  // 
  // temp__2:
  // std::sequence temp__2 "&lt;" NAME "::" NAME '>'
  // std::key_value_pair temp__1 temp__2: (capture)
  // std::negate temp__2 2
  // range temp__1 capture 5 temp__2
  // resolve_reference temp__1 $reference
  // mangled temp__2 reference
  // std::string
  // temp__1
  // "
  // <a href="@
  // temp__2
  // "
  // .html">@
  // reference
  // "</a>"
  // -> temp__1
  // replace_all &text temp__1
  // 
  // if temp__1 temp__2
  // emit text
  define__html__encode(func__30_2);
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 620: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__30_21;
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
  // 609: ... tag == "p"
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
  // 609: ... :
  // 610:   replace_all
  // 611:     &text
  // 612:     =
  // 613:       "&lt;", NAME, "::", NAME, '>'
  // 614:       : (capture)
  // 615:         $reference resolve_reference(range(capture 5 -2))
  // 616:         -> "
  // 617:           <a href="@(reference.mangled).html">@(reference)</a>@
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_5, 0);
  // 609: if tag == "p":
  // 610:   replace_all
  // 611:     &text
  // 612:     =
  // 613:       "&lt;", NAME, "::", NAME, '>'
  // 614:       : (capture)
  // 615:         $reference resolve_reference(range(capture 5 -2))
  // 616:         -> "
  // 617:           <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_20;
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
  // 613: "&lt;", NAME, "::", NAME, '>'
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__30_6;
  arguments->slots[1] = get__NAME();
  arguments->slots[2] = string__30_7;
  arguments->slots[3] = get__NAME();
  arguments->slots[4] = character__62;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__30_8;
}
static void cont__30_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 612: =
  // 613:   "&lt;", NAME, "::", NAME, '>'
  // 614:   : (capture)
  // 615:     $reference resolve_reference(range(capture 5 -2))
  // 616:     -> "
  // 617:       <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__30_9;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_18;
}
static void entry__30_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // capture: 0
  // reference: 1
  frame->slots[1] /* reference */ = create_future();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 615: ... 2
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__30_10;
}
static void cont__30_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 615: ... range(capture 5 -2)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* capture */;
  arguments->slots[1] = number__5;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__30_11;
}
static void cont__30_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 615: $reference resolve_reference(range(capture 5 -2))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolve_reference;
  func = myself->type;
  frame->cont = cont__30_12;
}
static void cont__30_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* reference */, arguments->slots[0]);
  // 617: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_13;
}
static void cont__30_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 616: ... "
  // 617:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = string__30_14;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = string__30_15;
  arguments->slots[3] = frame->slots[1] /* reference */;
  arguments->slots[4] = string__30_16;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_17;
}
static void cont__30_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 616: -> "
  // 617:   <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 610: replace_all
  // 611:   &text
  // 612:   =
  // 613:     "&lt;", NAME, "::", NAME, '>'
  // 614:     : (capture)
  // 615:       $reference resolve_reference(range(capture 5 -2))
  // 616:       -> "
  // 617:         <a href="@(reference.mangled).html">@(reference)</a>@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_19;
}
static void cont__30_19(void) {
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
static void cont__30_20(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 618: emit text
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* text */;
  result_count = frame->caller_result_count;
  myself = get__emit();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 620: !path_prefix truncate_behind(path '/' -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  arguments->slots[1] = character__47;
  arguments->slots[2] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__truncate_behind();
  func = myself->type;
  frame->cont = cont__30_22;
}
static void cont__30_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  var._path_prefix = arguments->slots[0];
  // 621: extract_documentation_from_directory path
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* path */;
  result_count = 0;
  myself = var._extract_documentation_from_directory;
  func = myself->type;
  frame->cont = cont__30_23;
}
static void cont__30_23(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 622: for_each definitions: (name info)
  // 623:   if kind_of(info) == TYPE:
  // 624:     $base base_of(info)
  // 625:     if base.is_defined: add_derived_type base name
  // 626:     $$methods empty_key_order_table
  // 627:     for_each methods_of(info): ($method_name method_info)
  // 628:       unless method_name .contains. "::":
  // 629:         !method_name attribute_of(method_info).resolved_name
  // 630:       if name_of(info).is_defined:
  // 631:         $oname
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__30_24;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_58;
}
static void entry__30_27(void) {
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
  // 624: $base base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__30_28;
}
static void cont__30_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* base */, arguments->slots[0]);
  // 625: ... base.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* base */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_29;
}
static void cont__30_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 625: ... : add_derived_type base name
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_30, 0);
  // 625: if base.is_defined: add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_31;
}
static void entry__30_30(void) {
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
  // 625: ... add_derived_type base name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* base */;
  arguments->slots[1] = frame->slots[1] /* name */;
  result_count = frame->caller_result_count;
  myself = var._add_derived_type;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_31(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 626: $$methods empty_key_order_table
  ((CELL *)frame->slots[3])->contents /* methods */ = get__empty_key_order_table();
  // 627: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__30_32;
}
static void cont__30_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 627: ... : ($method_name method_info)
  // 628:   unless method_name .contains. "::":
  // 629:     !method_name attribute_of(method_info).resolved_name
  // 630:   if name_of(info).is_defined:
  // 631:     $oname
  // 632:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 633:     
  // 634:     !definitions(oname).types_of(name_of(info)) true
  // 635:   !methods(method_name) method_info
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_33, 2);
  // 627: for_each methods_of(info): ($method_name method_info)
  // 628:   unless method_name .contains. "::":
  // 629:     !method_name attribute_of(method_info).resolved_name
  // 630:   if name_of(info).is_defined:
  // 631:     $oname
  // 632:       ordered_name(method_name .before. "::" method_name .behind. "::")
  // 633:     
  // 634:     !definitions(oname).types_of(name_of(info)) true
  // 635:   !methods(method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_55;
}
static void entry__30_33(void) {
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
  // 628: ... method_name .contains. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__30_34;
  result_count = 1;
  myself = get__contains();
  func = myself->type;
  frame->cont = cont__30_35;
}
static void cont__30_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 628: ... :
  // 629:   !method_name attribute_of(method_info).resolved_name
  frame->slots[5] /* temp__2 */ = create_closure(entry__30_36, 0);
  // 628: unless method_name .contains. "::":
  // 629:   !method_name attribute_of(method_info).resolved_name
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__30_39;
}
static void entry__30_36(void) {
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
  // 629: ... attribute_of(method_info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* method_info */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__30_37;
}
static void cont__30_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 629: !method_name attribute_of(method_info).resolved_name
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = var._resolved_name;
  func = myself->type;
  frame->cont = cont__30_38;
}
static void cont__30_38(void) {
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
static void cont__30_39(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 630: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_40;
}
static void cont__30_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 630: ... name_of(info).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_41;
}
static void cont__30_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 630: ... :
  // 631:   $oname
  // 632:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 633:   
  // 634:   !definitions(oname).types_of(name_of(info)) true
  frame->slots[6] /* temp__3 */ = create_closure(entry__30_42, 0);
  // 630: if name_of(info).is_defined:
  // 631:   $oname
  // 632:     ordered_name(method_name .before. "::" method_name .behind. "::")
  // 633:   
  // 634:   !definitions(oname).types_of(name_of(info)) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_53;
}
static void entry__30_42(void) {
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
  // 632: ... method_name .before. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__30_43;
  result_count = 1;
  myself = get__before();
  func = myself->type;
  frame->cont = cont__30_44;
}
static void cont__30_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 632: ... method_name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = string__30_45;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__30_46;
}
static void cont__30_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 631: $oname
  // 632:   ordered_name(method_name .before. "::" method_name .behind. "::")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._ordered_name;
  func = myself->type;
  frame->cont = cont__30_47;
}
static void cont__30_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* oname */, arguments->slots[0]);
  // 634: !definitions(oname).types_of(name_of(info)) true
  frame->slots[3] /* temp__1 */ = get__true();
  // 634: ... definitions(oname)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
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
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 634: ... definitions(oname).types_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = var._types_of;
  func = myself->type;
  frame->cont = cont__30_49;
}
static void cont__30_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 634: ... name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_50;
}
static void cont__30_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__4 */ = arguments->slots[0];
  // 634: !definitions(oname).types_of(name_of(info))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__4 */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__30_51;
}
static void cont__30_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 634: !definitions(oname).types_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__types_of, frame->slots[5] /* temp__3 */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 634: !definitions(oname)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* oname */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
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
  var._definitions = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_53(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 635: !methods(method_name) method_info
  frame->slots[4] /* temp__1 */ = frame->slots[1] /* method_info */;
  // 635: !methods(method_name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* method_name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[3])->contents /* methods */;
  func = myself->type;
  frame->cont = cont__30_54;
}
static void cont__30_54(void) {
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
static void cont__30_55(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 636: !definitions(name).methods_of methods
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* methods */;
  // 636: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_56;
}
static void cont__30_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 636: !definitions(name).methods_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__methods_of, frame->slots[4] /* temp__1 */);
    frame->slots[5] /* temp__2 */ = temp;

  }
  // 636: !definitions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_57;
}
static void cont__30_57(void) {
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
static void entry__30_24(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 623: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_25;
}
static void cont__30_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 623: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_26;
}
static void cont__30_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 623: ... :
  // 624:   $base base_of(info)
  // 625:   if base.is_defined: add_derived_type base name
  // 626:   $$methods empty_key_order_table
  // 627:   for_each methods_of(info): ($method_name method_info)
  // 628:     unless method_name .contains. "::":
  // 629:       !method_name attribute_of(method_info).resolved_name
  // 630:     if name_of(info).is_defined:
  // 631:       $oname
  // 632:         ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_27, 0);
  // 623: if kind_of(info) == TYPE:
  // 624:   $base base_of(info)
  // 625:   if base.is_defined: add_derived_type base name
  // 626:   $$methods empty_key_order_table
  // 627:   for_each methods_of(info): ($method_name method_info)
  // 628:     unless method_name .contains. "::":
  // 629:       !method_name attribute_of(method_info).resolved_name
  // 630:     if name_of(info).is_defined:
  // 631:       $oname
  // 632:         ordered_name(method_name .before. "::" method_name .behind. "::")
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 637: create_page "html/type_index.html":
  // 638:   $print_type_info:
  // 639:     (
  // 640:       info
  // 641:       indent = 0
  // 642:     )
  // 643:     TR:
  // 644:       $qname name_of(info)
  // 645:       $remark_lines remark_lines_of(info)
  // 646:       if qname.is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_59;
  arguments->slots[1] = func__30_60;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_102;
}
static void entry__30_101(void) {
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
  // 660: print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = frame->caller_result_count;
  myself = frame->slots[0] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_94(void) {
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
  // 659: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_95;
}
static void cont__30_95(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 659: ... kind_of(info) == TYPE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = var._TYPE;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_96;
}
static void cont__30_96(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 659: ... base_of(info).is_undefined
  frame->slots[6] /* temp__4 */ = create_closure(entry__30_97, 0);
  // 659: ... kind_of(info) == TYPE && base_of(info).is_undefined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_100;
}
static void entry__30_97(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 659: ... base_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__30_98;
}
static void cont__30_98(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 659: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__30_99;
}
static void cont__30_99(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 659: ... base_of(info).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_100(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 659: ... :
  // 660:   print_type_info info
  frame->slots[7] /* temp__5 */ = create_closure(entry__30_101, 0);
  // 659: if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 660:   print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_93(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* print_type_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 658: ... : (_base info)
  // 659:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 660:     print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_94, 2);
  // 658: for_each definitions: (_base info)
  // 659:   if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 660:     print_type_info info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_60(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // print_type_info: 0
  frame->slots[0] /* print_type_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 638: ... :
  // 639:   (
  // 640:     info
  // 641:     indent = 0
  // 642:   )
  // 643:   TR:
  // 644:     $qname name_of(info)
  // 645:     $remark_lines remark_lines_of(info)
  // 646:     if qname.is_defined:
  // 647:       TD:
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_61, -1);
  // 638: $print_type_info:
  // 639:   (
  // 640:     info
  // 641:     indent = 0
  // 642:   )
  // 643:   TR:
  // 644:     $qname name_of(info)
  // 645:     $remark_lines remark_lines_of(info)
  // 646:     if qname.is_defined:
  // 647:       TD:
  // ...
  initialize_future(frame->slots[0] /* print_type_info */, frame->slots[1] /* temp__1 */);
  // 655: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_90;
}
static void entry__30_87(void) {
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
  // 653: ... definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._definitions;
  func = myself->type;
  frame->cont = cont__30_88;
}
static void cont__30_88(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 653: ... indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* indent */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__30_89;
}
static void cont__30_89(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 653: print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = frame->slots[1] /* print_type_info */;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_62(void) {
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
  // 644: $qname name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_63;
}
static void cont__30_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* qname */, arguments->slots[0]);
  // 645: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__30_64;
}
static void cont__30_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* remark_lines */, arguments->slots[0]);
  // 646: ... qname.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* qname */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_65;
}
static void cont__30_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 646: ... :
  // 647:   TD:
  // 648:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:     A "href" = "@(qname.mangled).html" qname
  frame->slots[6] /* temp__2 */ = create_closure(entry__30_66, 0);
  // 646: if qname.is_defined:
  // 647:   TD:
  // 648:     TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:     A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_76;
}
static void entry__30_67(void) {
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
  // 648: ... "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_68;
  arguments->slots[1] = frame->slots[0] /* indent */;
  result_count = 1;
  myself = get__dup();
  func = myself->type;
  frame->cont = cont__30_69;
}
static void cont__30_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 648: TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_70;
}
static void cont__30_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 649: ... qname.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* qname */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_71;
}
static void cont__30_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 649: ... "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  arguments->slots[1] = string__30_72;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_73;
}
static void cont__30_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 649: ... "href" = "@(qname.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_74;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_75;
}
static void cont__30_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 649: A "href" = "@(qname.mangled).html" qname
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* qname */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_66(void) {
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
  // 647: ... :
  // 648:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:   A "href" = "@(qname.mangled).html" qname
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_67, 0);
  // 647: TD:
  // 648:   TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:   A "href" = "@(qname.mangled).html" qname
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_76(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 650: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_77;
}
static void cont__30_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 650: ... not(remark_lines.is_empty)
  frame->slots[7] /* temp__3 */ = create_closure(entry__30_78, 0);
  // 650: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_81;
}
static void entry__30_78(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 650: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__30_79;
}
static void cont__30_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 650: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__30_80;
}
static void cont__30_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 650: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 650: ... :
  // 651:   TD remark_lines.to_paragraphs(1)
  frame->slots[8] /* temp__4 */ = create_closure(entry__30_82, 0);
  // 650: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 651:   TD remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_85;
}
static void entry__30_82(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 651: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__30_83;
}
static void cont__30_83(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 651: ... remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__2 */;
  func = myself->type;
  frame->cont = cont__30_84;
}
static void cont__30_84(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 651: TD remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_85(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 652: ... derived_types_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._derived_types_of;
  func = myself->type;
  frame->cont = cont__30_86;
}
static void cont__30_86(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 652: ... : (name)
  // 653:   print_type_info definitions(name) indent+1
  frame->slots[6] /* temp__2 */ = create_closure(entry__30_87, 1);
  // 652: for_each derived_types_of(info): (name)
  // 653:   print_type_info definitions(name) indent+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_61(void) {
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
  // 643: ... :
  // 644:   $qname name_of(info)
  // 645:   $remark_lines remark_lines_of(info)
  // 646:   if qname.is_defined:
  // 647:     TD:
  // 648:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:       A "href" = "@(qname.mangled).html" qname
  // 650:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 651:     TD remark_lines.to_paragraphs(1)
  // 652:   for_each derived_types_of(info): (name)
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__30_62, 0);
  // 643: TR:
  // 644:   $qname name_of(info)
  // 645:   $remark_lines remark_lines_of(info)
  // 646:   if qname.is_defined:
  // 647:     TD:
  // 648:       TEXT "&nbsp;&nbsp;&nbsp;" .dup. indent
  // 649:       A "href" = "@(qname.mangled).html" qname
  // 650:   if remark_lines.is_defined && not(remark_lines.is_empty):
  // 651:     TD remark_lines.to_paragraphs(1)
  // 652:   for_each derived_types_of(info): (name)
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_90(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 656: H1 "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_91;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_92;
}
static void cont__30_92(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 657: ... :
  // 658:   for_each definitions: (_base info)
  // 659:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 660:       print_type_info info
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_93, 0);
  // 657: TABLE:
  // 658:   for_each definitions: (_base info)
  // 659:     if kind_of(info) == TYPE && base_of(info).is_undefined:
  // 660:       print_type_info info
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_102(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 661: create_page "html/symbol_index.html":
  // 662:   link_bar
  // 663:   H1 "id" = "index" "Symbol Index"
  // 664:   from_to
  // 665:     'a'
  // 666:     'z': (letter)
  // 667:       A "href" = "#@(letter)" letter.to_upper_case
  // 668:     :
  // 669:       TEXT " "
  // 670:   BR
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_103;
  arguments->slots[1] = func__30_104;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_199;
}
static void entry__30_180(void) {
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
  // 710: ... "align" = "right"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_181;
  arguments->slots[1] = string__30_182;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_183;
}
static void cont__30_183(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 710: ... name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__30_184;
  result_count = 1;
  myself = get__until();
  func = myself->type;
  frame->cont = cont__30_185;
}
static void cont__30_185(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 710: TD "align" = "right" name .until. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__30_186;
}
static void cont__30_186(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 711: ... : A "href" = "@(name.mangled).html" name .behind. "::"
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_187, 0);
  // 711: TD: A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__TD();
  func = myself->type;
  frame->cont = cont__30_195;
}
static void entry__30_187(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 711: ... name.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_188;
}
static void cont__30_188(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 711: ... "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__30_189;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_190;
}
static void cont__30_190(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 711: ... "href" = "@(name.mangled).html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_191;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_192;
}
static void cont__30_192(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 711: ... name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = string__30_193;
  result_count = 1;
  myself = get__behind();
  func = myself->type;
  frame->cont = cont__30_194;
}
static void cont__30_194(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 711: ... A "href" = "@(name.mangled).html" name .behind. "::"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_195(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 712: ... "class" = "remark"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_196;
  arguments->slots[1] = string__30_197;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_198;
}
static void cont__30_198(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 712: TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = ((CELL *)frame->slots[1])->contents /* remark */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_179(void) {
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
  // 709: ... :
  // 710:   TD "align" = "right" name .until. "::"
  // 711:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 712:   TD "class" = "remark" remark
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_180, 0);
  // 709: TR:
  // 710:   TD "align" = "right" name .until. "::"
  // 711:   TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 712:   TD "class" = "remark" remark
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_122(void) {
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
  // 674: ... iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[0] /* iname */;
  func = myself->type;
  frame->cont = cont__30_123;
}
static void cont__30_123(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__3 */ = arguments->slots[0];
  // 674: ... iname(1) != letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[9] /* temp__3 */;
  arguments->slots[1] = ((CELL *)frame->slots[2])->contents /* letter */;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__30_124;
}
static void cont__30_124(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 674: ... iname(1) != letter
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__30_125;
}
static void cont__30_125(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 674: ... :
  // 675:   !letter iname(1)
  // 676:   TR:
  // 677:     TD "colspan" = 3:
  // 678:       H2 "id" = letter:
  // 679:         TEXT letter.to_upper_case
  // 680:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_126, 0);
  // 674: if iname(1) != letter:
  // 675:   !letter iname(1)
  // 676:   TR:
  // 677:     TD "colspan" = 3:
  // 678:       H2 "id" = letter:
  // 679:         TEXT letter.to_upper_case
  // 680:         A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_141;
}
static void entry__30_134(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 679: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__30_135;
}
static void cont__30_135(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 679: TEXT letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 0;
  myself = get__TEXT();
  func = myself->type;
  frame->cont = cont__30_136;
}
static void cont__30_136(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 680: ... "href" = "#index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_137;
  arguments->slots[1] = string__30_138;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_139;
}
static void cont__30_139(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 680: A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = string__30_140;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_131(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 678: ... "id" = letter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_132;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* letter */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_133;
}
static void cont__30_133(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 678: ... :
  // 679:   TEXT letter.to_upper_case
  // 680:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__30_134, 0);
  // 678: H2 "id" = letter:
  // 679:   TEXT letter.to_upper_case
  // 680:   A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__H2();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_128(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // letter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* letter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 677: ... "colspan" = 3
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_129;
  arguments->slots[1] = number__3;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_130;
}
static void cont__30_130(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 677: ... :
  // 678:   H2 "id" = letter:
  // 679:     TEXT letter.to_upper_case
  // 680:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__2 */ = create_closure(entry__30_131, 0);
  // 677: TD "colspan" = 3:
  // 678:   H2 "id" = letter:
  // 679:     TEXT letter.to_upper_case
  // 680:     A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_126(void) {
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
  // 675: !letter iname(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* iname */;
  func = myself->type;
  frame->cont = cont__30_127;
}
static void cont__30_127(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* letter */ = arguments->slots[0];
  // 676: ... :
  // 677:   TD "colspan" = 3:
  // 678:     H2 "id" = letter:
  // 679:       TEXT letter.to_upper_case
  // 680:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_128, 0);
  // 676: TR:
  // 677:   TD "colspan" = 3:
  // 678:     H2 "id" = letter:
  // 679:       TEXT letter.to_upper_case
  // 680:       A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_141(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 681: $$remark undefined
  ((CELL *)frame->slots[3])->contents /* remark */ = get__undefined();
  // 682: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_142;
}
static void cont__30_142(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[4] /* name */, arguments->slots[0]);
  // 683: $remark_lines remark_lines_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__remark_lines_of();
  func = myself->type;
  frame->cont = cont__30_143;
}
static void cont__30_143(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[5] /* remark_lines */, arguments->slots[0]);
  // 684: ... remark_lines.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* remark_lines */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_144;
}
static void cont__30_144(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 684: ... not(remark_lines.is_empty)
  frame->slots[9] /* temp__3 */ = create_closure(entry__30_145, 0);
  // 684: ... remark_lines.is_defined && not(remark_lines.is_empty)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_148;
}
static void entry__30_145(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // remark_lines: 0
  frame->slots[0] = myself->closure.frame->slots[5]; /* remark_lines */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 684: ... remark_lines.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* remark_lines */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__30_146;
}
static void cont__30_146(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 684: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__30_147;
}
static void cont__30_147(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 684: ... not(remark_lines.is_empty)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_148(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 684: ... :
  // 685:   !remark remark_lines.to_paragraphs(1)
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_149, 0);
  // 684: if remark_lines.is_defined && not(remark_lines.is_empty):
  // 685:   !remark remark_lines.to_paragraphs(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_152;
}
static void entry__30_149(void) {
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
  // 685: ... remark_lines.to_paragraphs
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* remark_lines */;
  result_count = 1;
  myself = var._to_paragraphs;
  func = myself->type;
  frame->cont = cont__30_150;
}
static void cont__30_150(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 685: !remark remark_lines.to_paragraphs(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__30_151;
}
static void cont__30_151(void) {
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
static void cont__30_152(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 689: kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_153;
}
static void cont__30_153(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 687: $kind_info
  // 688:   case
  // 689:     kind_of(info)
  // 690:     FUNCTION
  // 691:     -> "function"
  // 692:     INLINE_C_FUNCTION
  // 693:     -> "inline-C function"
  // 694:     POLYMORPHIC
  // 695:     -> "polymorphic function"
  // 696:     UNIQUE_ITEM
  // ...
  argument_count = 12;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = var._FUNCTION;
  arguments->slots[2] = func__30_154;
  arguments->slots[3] = var._INLINE_C_FUNCTION;
  arguments->slots[4] = func__30_156;
  arguments->slots[5] = get__POLYMORPHIC();
  arguments->slots[6] = func__30_158;
  arguments->slots[7] = var._UNIQUE_ITEM;
  arguments->slots[8] = func__30_160;
  arguments->slots[9] = var._TYPE;
  arguments->slots[10] = func__30_162;
  arguments->slots[11] = func__30_164;
  result_count = 1;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__30_165;
}
static void entry__30_154(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 691: -> "function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_155;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_156(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 693: -> "inline-C function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_157;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_158(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 695: -> "polymorphic function"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_159;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_160(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 697: -> "unique item"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_161;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_162(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 699: -> "type"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_163;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_164(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 700: -> undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__undefined();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_165(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[6] /* kind_info */, arguments->slots[0]);
  // 702: ... kind_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[6] /* kind_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_166;
}
static void cont__30_166(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 702: ... :
  // 703:   if
  // 704:     remark.is_defined:
  // 705:       !remark string(remark " (" kind_info ")")
  // 706:     :
  // 707:       !remark kind_info
  frame->slots[8] /* temp__2 */ = create_closure(entry__30_167, 0);
  // 702: if kind_info.is_defined:
  // 703:   if
  // 704:     remark.is_defined:
  // 705:       !remark string(remark " (" kind_info ")")
  // 706:     :
  // 707:       !remark kind_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[8] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__30_174;
}
static void entry__30_169(void) {
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
  // 705: !remark string(remark " (" kind_info ")")
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  arguments->slots[1] = string__30_170;
  arguments->slots[2] = frame->slots[1] /* kind_info */;
  arguments->slots[3] = string__30_171;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_172;
}
static void cont__30_172(void) {
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
static void entry__30_173(void) {
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
  // 707: !remark kind_info
  ((CELL *)frame->slots[0])->contents /* remark */ = frame->slots[1] /* kind_info */;
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__30_167(void) {
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
  // 704: remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_168;
}
static void cont__30_168(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 704: ... :
  // 705:   !remark string(remark " (" kind_info ")")
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_169, 0);
  // 706: :
  // 707:   !remark kind_info
  frame->slots[4] /* temp__3 */ = create_closure(entry__30_173, 0);
  // 703: if
  // 704:   remark.is_defined:
  // 705:     !remark string(remark " (" kind_info ")")
  // 706:   :
  // 707:     !remark kind_info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_174(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 708: ... remark.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[3])->contents /* remark */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_175;
}
static void cont__30_175(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__2 */ = arguments->slots[0];
  // 708: ... name.is_defined
  frame->slots[9] /* temp__3 */ = create_closure(entry__30_176, 0);
  // 708: ... remark.is_defined && name.is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[8] /* temp__2 */;
  arguments->slots[1] = frame->slots[9] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__30_178;
}
static void entry__30_176(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[4]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 708: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_177;
}
static void cont__30_177(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 708: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__30_178(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__1 */ = arguments->slots[0];
  // 708: ... :
  // 709:   TR:
  // 710:     TD "align" = "right" name .until. "::"
  // 711:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 712:     TD "class" = "remark" remark
  frame->slots[10] /* temp__4 */ = create_closure(entry__30_179, 0);
  // 708: if remark.is_defined && name.is_defined:
  // 709:   TR:
  // 710:     TD "align" = "right" name .until. "::"
  // 711:     TD: A "href" = "@(name.mangled).html" name .behind. "::"
  // 712:     TD "class" = "remark" remark
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[7] /* temp__1 */;
  arguments->slots[1] = frame->slots[10] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_121(void) {
  allocate_initialized_frame_gc(0, 2);
  // slot allocations:
  // letter: 0
  frame->slots[0] /* letter */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 672: $$letter undefined
  ((CELL *)frame->slots[0])->contents /* letter */ = get__undefined();
  // 673: ... : (iname info)
  // 674:   if iname(1) != letter:
  // 675:     !letter iname(1)
  // 676:     TR:
  // 677:       TD "colspan" = 3:
  // 678:         H2 "id" = letter:
  // 679:           TEXT letter.to_upper_case
  // 680:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 681:   $$remark undefined
  // 682:   $name name_of(info)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_122, 2);
  // 673: for_each definitions: (iname info)
  // 674:   if iname(1) != letter:
  // 675:     !letter iname(1)
  // 676:     TR:
  // 677:       TD "colspan" = 3:
  // 678:         H2 "id" = letter:
  // 679:           TEXT letter.to_upper_case
  // 680:           A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // 681:   $$remark undefined
  // 682:   $name name_of(info)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_104(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 662: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_105;
}
static void cont__30_105(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 663: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_106;
  arguments->slots[1] = string__30_107;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_108;
}
static void cont__30_108(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 663: H1 "id" = "index" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_109;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_110;
}
static void cont__30_110(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 664: from_to
  // 665:   'a'
  // 666:   'z': (letter)
  // 667:     A "href" = "#@(letter)" letter.to_upper_case
  // 668:   :
  // 669:     TEXT " "
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = character__97;
  arguments->slots[1] = character__122;
  arguments->slots[2] = func__30_111;
  arguments->slots[3] = func__30_117;
  result_count = 0;
  myself = get__from_to();
  func = myself->type;
  frame->cont = cont__30_119;
}
static void entry__30_111(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // letter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 667: ... "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_112;
  arguments->slots[1] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_113;
}
static void cont__30_113(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 667: ... "href" = "#@(letter)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_114;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_115;
}
static void cont__30_115(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 667: ... letter.to_upper_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* letter */;
  result_count = 1;
  myself = get__to_upper_case();
  func = myself->type;
  frame->cont = cont__30_116;
}
static void cont__30_116(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 667: A "href" = "#@(letter)" letter.to_upper_case
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_117(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 669: TEXT " "
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_118;
  result_count = frame->caller_result_count;
  myself = get__TEXT();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_119(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 670: BR
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = get__BR();
  func = myself->type;
  frame->cont = cont__30_120;
}
static void cont__30_120(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 671: TABLE:
  // 672:   $$letter undefined
  // 673:   for_each definitions: (iname info)
  // 674:     if iname(1) != letter:
  // 675:       !letter iname(1)
  // 676:       TR:
  // 677:         TD "colspan" = 3:
  // 678:           H2 "id" = letter:
  // 679:             TEXT letter.to_upper_case
  // 680:             A "href" = "#index" "&nbsp;&#x2302;" # home symbol
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_121;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_199(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 713: for_each definitions: (_iname info)
  // 714:   $name name_of(info)
  // 715:   if name.is_defined:
  // 716:     create_info_page name info
  // 717:     case kind_of(info) TYPE:
  // 718:       for_each methods_of(info): (method_name method_info)
  // 719:         create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._definitions;
  arguments->slots[1] = func__30_200;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_211;
}
static void entry__30_208(void) {
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
  // 719: ... string(name "/" method_name)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  arguments->slots[1] = string__30_209;
  arguments->slots[2] = frame->slots[0] /* method_name */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_210;
}
static void cont__30_210(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 719: create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* method_info */;
  result_count = frame->caller_result_count;
  myself = var._create_info_page;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_206(void) {
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
  // 718: ... methods_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = var._methods_of;
  func = myself->type;
  frame->cont = cont__30_207;
}
static void cont__30_207(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 718: ... : (method_name method_info)
  // 719:   create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_208, 2);
  // 718: for_each methods_of(info): (method_name method_info)
  // 719:   create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_203(void) {
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
  // 716: create_info_page name info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* info */;
  result_count = 0;
  myself = var._create_info_page;
  func = myself->type;
  frame->cont = cont__30_204;
}
static void cont__30_204(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 717: ... kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__30_205;
}
static void cont__30_205(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 717: ... :
  // 718:   for_each methods_of(info): (method_name method_info)
  // 719:     create_info_page string(name "/" method_name) method_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__30_206, 0);
  // 717: case kind_of(info) TYPE:
  // 718:   for_each methods_of(info): (method_name method_info)
  // 719:     create_info_page string(name "/" method_name) method_info
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = var._TYPE;
  arguments->slots[2] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_200(void) {
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
  // 714: $name name_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__30_201;
}
static void cont__30_201(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 715: ... name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__30_202;
}
static void cont__30_202(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 715: ... :
  // 716:   create_info_page name info
  // 717:   case kind_of(info) TYPE:
  // 718:     for_each methods_of(info): (method_name method_info)
  // 719:       create_info_page string(name "/" method_name) method_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_203, 0);
  // 715: if name.is_defined:
  // 716:   create_info_page name info
  // 717:   case kind_of(info) TYPE:
  // 718:     for_each methods_of(info): (method_name method_info)
  // 719:       create_info_page string(name "/" method_name) method_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_211(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 720: create_page "html/topic_index.html":
  // 721:   link_bar
  // 722:   H1 "id" = "index" "Topic Index"
  // 723:   TABLE:
  // 724:     for_each topics: (topic _references)
  // 725:       $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 726:       TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_212;
  arguments->slots[1] = func__30_213;
  result_count = 0;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_232;
}
static void entry__30_229(void) {
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
  // 726: ... "href" = filename
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_230;
  arguments->slots[1] = frame->slots[0] /* filename */;
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
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 726: ... A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[1] /* topic */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_228(void) {
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
  // 726: ... : A "href" = filename topic
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_229, 0);
  // 726: ... TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_221(void) {
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
  // 725: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_222;
}
static void cont__30_222(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 725: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__30_223;
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
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 725: ... replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_225;
}
static void cont__30_225(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 725: $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = string__30_226;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_227;
}
static void cont__30_227(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 726: ... : TD: A "href" = filename topic
  frame->slots[3] /* temp__1 */ = create_closure(entry__30_228, 0);
  // 726: TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_220(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 724: for_each topics: (topic _references)
  // 725:   $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 726:   TR: TD: A "href" = filename topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__30_221;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_213(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 721: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_214;
}
static void cont__30_214(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 722: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_215;
  arguments->slots[1] = string__30_216;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_217;
}
static void cont__30_217(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 722: H1 "id" = "index" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_218;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_219;
}
static void cont__30_219(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 723: TABLE:
  // 724:   for_each topics: (topic _references)
  // 725:     $filename string(replace_all(topic.to_lower_case ' ' = "_") ".html")
  // 726:     TR: TD: A "href" = filename topic
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_220;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_232(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 727: for_each topics: (topic references)
  // 728:   $filename replace_all(topic.to_lower_case ' ' = "_")
  // 729:   create_page "html/@(filename).html":
  // 730:     link_bar
  // 731:     H1 "id" = "index" topic
  // 732:     TABLE:
  // 733:       for_each references: (reference)
  // 734:         TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = var._topics;
  arguments->slots[1] = func__30_233;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__30_256;
}
static void entry__30_250(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 734: ... reference.mangled
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* reference */;
  result_count = 1;
  myself = var._mangled;
  func = myself->type;
  frame->cont = cont__30_251;
}
static void cont__30_251(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 734: ... string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = string__30_252;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__30_253;
}
static void cont__30_253(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 734: ... "href" = string(reference.mangled ".html")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_254;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_255;
}
static void cont__30_255(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 734: ... A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* reference */;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_249(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* reference */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 734: ... : A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_250, 0);
  // 734: ... TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TD();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_248(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // reference: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 734: ... : TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[1] /* temp__1 */ = create_closure(entry__30_249, 0);
  // 734: TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TR();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_247(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // references: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* references */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 733: for_each references: (reference)
  // 734:   TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* references */;
  arguments->slots[1] = func__30_248;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_241(void) {
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
  // 730: link_bar
  argument_count = 0;
  arguments = node_p;
  result_count = 0;
  myself = var._link_bar;
  func = myself->type;
  frame->cont = cont__30_242;
}
static void cont__30_242(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 731: ... "id" = "index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_243;
  arguments->slots[1] = string__30_244;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_245;
}
static void cont__30_245(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 731: H1 "id" = "index" topic
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* topic */;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_246;
}
static void cont__30_246(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 732: ... :
  // 733:   for_each references: (reference)
  // 734:     TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[2] /* temp__1 */ = create_closure(entry__30_247, 0);
  // 732: TABLE:
  // 733:   for_each references: (reference)
  // 734:     TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__TABLE();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_233(void) {
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
  // 728: ... topic.to_lower_case
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* topic */;
  result_count = 1;
  myself = get__to_lower_case();
  func = myself->type;
  frame->cont = cont__30_234;
}
static void cont__30_234(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 728: ... ' ' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__32;
  arguments->slots[1] = string__30_235;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_236;
}
static void cont__30_236(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 728: $filename replace_all(topic.to_lower_case ' ' = "_")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__30_237;
}
static void cont__30_237(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* filename */, arguments->slots[0]);
  // 729: ... "html/@(filename).html"
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__30_238;
  arguments->slots[1] = frame->slots[2] /* filename */;
  arguments->slots[2] = string__30_239;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__30_240;
}
static void cont__30_240(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 729: ... :
  // 730:   link_bar
  // 731:   H1 "id" = "index" topic
  // 732:   TABLE:
  // 733:     for_each references: (reference)
  // 734:       TR: TD: A "href" = string(reference.mangled ".html") reference
  frame->slots[4] /* temp__2 */ = create_closure(entry__30_241, 0);
  // 729: create_page "html/@(filename).html":
  // 730:   link_bar
  // 731:   H1 "id" = "index" topic
  // 732:   TABLE:
  // 733:     for_each references: (reference)
  // 734:       TR: TD: A "href" = string(reference.mangled ".html") reference
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_256(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 735: create_page "html/index.html":
  // 736:   H1 "Simplicity"
  // 737:   P: A "href" = "manual.html" "Manual"
  // 738:   P: A "href" = "type_index.html" "Type Index"
  // 739:   P: A "href" = "symbol_index.html" "Symbol Index"
  // 740:   P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_257;
  arguments->slots[1] = func__30_258;
  result_count = frame->caller_result_count;
  myself = var._create_page;
  func = myself->type;
  frame->cont = cont__30_284;
}
static void entry__30_279(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 740: ... "href" = "topic_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_280;
  arguments->slots[1] = string__30_281;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_282;
}
static void cont__30_282(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 740: ... A "href" = "topic_index.html" "Topic Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_283;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void entry__30_258(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 736: H1 "Simplicity"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__30_259;
  result_count = 0;
  myself = get__H1();
  func = myself->type;
  frame->cont = cont__30_260;
}
static void cont__30_260(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 737: P: A "href" = "manual.html" "Manual"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_261;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_266;
}
static void entry__30_261(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 737: ... "href" = "manual.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_262;
  arguments->slots[1] = string__30_263;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_264;
}
static void cont__30_264(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 737: ... A "href" = "manual.html" "Manual"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_265;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_266(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 738: P: A "href" = "type_index.html" "Type Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_267;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_272;
}
static void entry__30_267(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 738: ... "href" = "type_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_268;
  arguments->slots[1] = string__30_269;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_270;
}
static void cont__30_270(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 738: ... A "href" = "type_index.html" "Type Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_271;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_272(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 739: P: A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_273;
  result_count = 0;
  myself = get__P();
  func = myself->type;
  frame->cont = cont__30_278;
}
static void entry__30_273(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 739: ... "href" = "symbol_index.html"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__30_274;
  arguments->slots[1] = string__30_275;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__30_276;
}
static void cont__30_276(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 739: ... A "href" = "symbol_index.html" "Symbol Index"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  arguments->slots[1] = string__30_277;
  result_count = frame->caller_result_count;
  myself = get__A();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_278(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 740: P: A "href" = "topic_index.html" "Topic Index"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = func__30_279;
  result_count = frame->caller_result_count;
  myself = get__P();
  func = myself->type;
  frame = frame->caller_frame;
  frame->cont = frame->cont;
}
static void cont__30_284(void) {
  myself = frame->slots[1] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
EXPORT void collect__extractor(void) {
  temp__1 = collect_node(temp__1);
  temp__2 = collect_node(temp__2);
  temp__3 = collect_node(temp__3);
  temp__4 = collect_node(temp__4);
  temp__5 = collect_node(temp__5);
  temp__6 = collect_node(temp__6);
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
  string__16_5 = collect_node(string__16_5);
  func__16_4 = collect_node(func__16_4);
  func__16_1 = collect_node(func__16_1);
  var._symbol_info = collect_node(var._symbol_info);
  var._extract_documentation_from_file = collect_node(var._extract_documentation_from_file);
  string__18_2 = collect_node(string__18_2);
  string__18_3 = collect_node(string__18_3);
  string__18_11 = collect_node(string__18_11);
  func__18_10 = collect_node(func__18_10);
  string__18_17 = collect_node(string__18_17);
  func__18_16 = collect_node(func__18_16);
  string__18_24 = collect_node(string__18_24);
  func__18_23 = collect_node(func__18_23);
  string__18_26 = collect_node(string__18_26);
  string__18_28 = collect_node(string__18_28);
  func__18_32 = collect_node(func__18_32);
  string__18_55 = collect_node(string__18_55);
  func__18_54 = collect_node(func__18_54);
  func__18_61 = collect_node(func__18_61);
  func__18_64 = collect_node(func__18_64);
  func__18_87 = collect_node(func__18_87);
  string__18_92 = collect_node(string__18_92);
  func__18_105 = collect_node(func__18_105);
  string__18_135 = collect_node(string__18_135);
  func__18_1 = collect_node(func__18_1);
  var._extract_documentation_from_directory = collect_node(var._extract_documentation_from_directory);
  string__19_10 = collect_node(string__19_10);
  func__19_4 = collect_node(func__19_4);
  func__19_1 = collect_node(func__19_1);
  var._resolved_name = collect_node(var._resolved_name);
  string__20_14 = collect_node(string__20_14);
  string__20_15 = collect_node(string__20_15);
  string__20_21 = collect_node(string__20_21);
  string__20_22 = collect_node(string__20_22);
  string__20_25 = collect_node(string__20_25);
  func__20_1 = collect_node(func__20_1);
  var._add_derived_type = collect_node(var._add_derived_type);
  string__21_2 = collect_node(string__21_2);
  string__21_4 = collect_node(string__21_4);
  func__21_1 = collect_node(func__21_1);
  var._mangled = collect_node(var._mangled);
  string__22_2 = collect_node(string__22_2);
  string__22_3 = collect_node(string__22_3);
  string__22_5 = collect_node(string__22_5);
  func__22_1 = collect_node(func__22_1);
  var._ordered_name = collect_node(var._ordered_name);
  func__23_1 = collect_node(func__23_1);
  var._link_bar = collect_node(var._link_bar);
  string__24_3 = collect_node(string__24_3);
  string__24_4 = collect_node(string__24_4);
  string__24_6 = collect_node(string__24_6);
  string__24_8 = collect_node(string__24_8);
  string__24_10 = collect_node(string__24_10);
  string__24_11 = collect_node(string__24_11);
  string__24_13 = collect_node(string__24_13);
  string__24_15 = collect_node(string__24_15);
  string__24_17 = collect_node(string__24_17);
  string__24_18 = collect_node(string__24_18);
  string__24_20 = collect_node(string__24_20);
  string__24_22 = collect_node(string__24_22);
  string__24_24 = collect_node(string__24_24);
  string__24_25 = collect_node(string__24_25);
  string__24_27 = collect_node(string__24_27);
  string__24_29 = collect_node(string__24_29);
  string__24_31 = collect_node(string__24_31);
  string__24_32 = collect_node(string__24_32);
  string__24_34 = collect_node(string__24_34);
  func__24_2 = collect_node(func__24_2);
  func__24_1 = collect_node(func__24_1);
  var._resolve_reference = collect_node(var._resolve_reference);
  string__25_6 = collect_node(string__25_6);
  string__25_9 = collect_node(string__25_9);
  string__25_12 = collect_node(string__25_12);
  string__25_15 = collect_node(string__25_15);
  string__25_20 = collect_node(string__25_20);
  string__25_23 = collect_node(string__25_23);
  func__25_1 = collect_node(func__25_1);
  var._TOPIC = collect_node(var._TOPIC);
  var._EXAMPLE = collect_node(var._EXAMPLE);
  var._to_paragraphs = collect_node(var._to_paragraphs);
  func__28_1 = collect_node(func__28_1);
  var._create_info_page = collect_node(var._create_info_page);
  string__29_5 = collect_node(string__29_5);
  string__29_6 = collect_node(string__29_6);
  string__29_16 = collect_node(string__29_16);
  string__29_17 = collect_node(string__29_17);
  string__29_18 = collect_node(string__29_18);
  string__29_19 = collect_node(string__29_19);
  string__29_30 = collect_node(string__29_30);
  string__29_40 = collect_node(string__29_40);
  string__29_47 = collect_node(string__29_47);
  string__29_56 = collect_node(string__29_56);
  string__29_57 = collect_node(string__29_57);
  string__29_66 = collect_node(string__29_66);
  string__29_76 = collect_node(string__29_76);
  string__29_83 = collect_node(string__29_83);
  string__29_91 = collect_node(string__29_91);
  string__29_120 = collect_node(string__29_120);
  string__29_138 = collect_node(string__29_138);
  string__29_139 = collect_node(string__29_139);
  string__29_140 = collect_node(string__29_140);
  func__29_133 = collect_node(func__29_133);
  string__29_172 = collect_node(string__29_172);
  string__29_173 = collect_node(string__29_173);
  string__29_176 = collect_node(string__29_176);
  string__29_181 = collect_node(string__29_181);
  func__29_191 = collect_node(func__29_191);
  func__29_195 = collect_node(func__29_195);
  string__29_202 = collect_node(string__29_202);
  func__29_205 = collect_node(func__29_205);
  string__29_213 = collect_node(string__29_213);
  func__29_216 = collect_node(func__29_216);
  string__29_224 = collect_node(string__29_224);
  func__29_226 = collect_node(func__29_226);
  string__29_230 = collect_node(string__29_230);
  func__29_232 = collect_node(func__29_232);
  string__29_236 = collect_node(string__29_236);
  string__29_242 = collect_node(string__29_242);
  string__29_244 = collect_node(string__29_244);
  func__29_239 = collect_node(func__29_239);
  string__29_251 = collect_node(string__29_251);
  string__29_260 = collect_node(string__29_260);
  string__29_262 = collect_node(string__29_262);
  string__29_265 = collect_node(string__29_265);
  string__29_269 = collect_node(string__29_269);
  string__29_271 = collect_node(string__29_271);
  string__29_277 = collect_node(string__29_277);
  string__29_285 = collect_node(string__29_285);
  string__29_287 = collect_node(string__29_287);
  string__29_290 = collect_node(string__29_290);
  string__29_295 = collect_node(string__29_295);
  string__29_296 = collect_node(string__29_296);
  string__29_298 = collect_node(string__29_298);
  string__29_302 = collect_node(string__29_302);
  string__29_310 = collect_node(string__29_310);
  func__29_317 = collect_node(func__29_317);
  string__29_319 = collect_node(string__29_319);
  string__29_320 = collect_node(string__29_320);
  string__29_325 = collect_node(string__29_325);
  string__29_326 = collect_node(string__29_326);
  string__29_330 = collect_node(string__29_330);
  string__29_331 = collect_node(string__29_331);
  func__29_1 = collect_node(func__29_1);
  var.sim2c__extract_documentation = collect_node(var.sim2c__extract_documentation);
  string__30_3 = collect_node(string__30_3);
  string__30_6 = collect_node(string__30_6);
  string__30_7 = collect_node(string__30_7);
  string__30_14 = collect_node(string__30_14);
  string__30_15 = collect_node(string__30_15);
  string__30_16 = collect_node(string__30_16);
  func__30_9 = collect_node(func__30_9);
  func__30_2 = collect_node(func__30_2);
  string__30_34 = collect_node(string__30_34);
  string__30_43 = collect_node(string__30_43);
  string__30_45 = collect_node(string__30_45);
  func__30_24 = collect_node(func__30_24);
  string__30_59 = collect_node(string__30_59);
  string__30_68 = collect_node(string__30_68);
  string__30_72 = collect_node(string__30_72);
  string__30_74 = collect_node(string__30_74);
  string__30_91 = collect_node(string__30_91);
  func__30_60 = collect_node(func__30_60);
  string__30_103 = collect_node(string__30_103);
  string__30_106 = collect_node(string__30_106);
  string__30_107 = collect_node(string__30_107);
  string__30_109 = collect_node(string__30_109);
  string__30_112 = collect_node(string__30_112);
  string__30_114 = collect_node(string__30_114);
  func__30_111 = collect_node(func__30_111);
  string__30_118 = collect_node(string__30_118);
  func__30_117 = collect_node(func__30_117);
  string__30_129 = collect_node(string__30_129);
  string__30_132 = collect_node(string__30_132);
  string__30_137 = collect_node(string__30_137);
  string__30_138 = collect_node(string__30_138);
  string__30_140 = collect_node(string__30_140);
  string__30_155 = collect_node(string__30_155);
  func__30_154 = collect_node(func__30_154);
  string__30_157 = collect_node(string__30_157);
  func__30_156 = collect_node(func__30_156);
  string__30_159 = collect_node(string__30_159);
  func__30_158 = collect_node(func__30_158);
  string__30_161 = collect_node(string__30_161);
  func__30_160 = collect_node(func__30_160);
  string__30_163 = collect_node(string__30_163);
  func__30_162 = collect_node(func__30_162);
  func__30_164 = collect_node(func__30_164);
  string__30_170 = collect_node(string__30_170);
  string__30_171 = collect_node(string__30_171);
  string__30_181 = collect_node(string__30_181);
  string__30_182 = collect_node(string__30_182);
  string__30_184 = collect_node(string__30_184);
  string__30_189 = collect_node(string__30_189);
  string__30_191 = collect_node(string__30_191);
  string__30_193 = collect_node(string__30_193);
  string__30_196 = collect_node(string__30_196);
  string__30_197 = collect_node(string__30_197);
  func__30_121 = collect_node(func__30_121);
  func__30_104 = collect_node(func__30_104);
  string__30_209 = collect_node(string__30_209);
  func__30_200 = collect_node(func__30_200);
  string__30_212 = collect_node(string__30_212);
  string__30_215 = collect_node(string__30_215);
  string__30_216 = collect_node(string__30_216);
  string__30_218 = collect_node(string__30_218);
  string__30_223 = collect_node(string__30_223);
  string__30_226 = collect_node(string__30_226);
  string__30_230 = collect_node(string__30_230);
  func__30_221 = collect_node(func__30_221);
  func__30_220 = collect_node(func__30_220);
  func__30_213 = collect_node(func__30_213);
  string__30_235 = collect_node(string__30_235);
  string__30_238 = collect_node(string__30_238);
  string__30_239 = collect_node(string__30_239);
  string__30_243 = collect_node(string__30_243);
  string__30_244 = collect_node(string__30_244);
  string__30_252 = collect_node(string__30_252);
  string__30_254 = collect_node(string__30_254);
  func__30_248 = collect_node(func__30_248);
  func__30_233 = collect_node(func__30_233);
  string__30_257 = collect_node(string__30_257);
  string__30_259 = collect_node(string__30_259);
  string__30_262 = collect_node(string__30_262);
  string__30_263 = collect_node(string__30_263);
  string__30_265 = collect_node(string__30_265);
  func__30_261 = collect_node(func__30_261);
  string__30_268 = collect_node(string__30_268);
  string__30_269 = collect_node(string__30_269);
  string__30_271 = collect_node(string__30_271);
  func__30_267 = collect_node(func__30_267);
  string__30_274 = collect_node(string__30_274);
  string__30_275 = collect_node(string__30_275);
  string__30_277 = collect_node(string__30_277);
  func__30_273 = collect_node(func__30_273);
  string__30_280 = collect_node(string__30_280);
  string__30_281 = collect_node(string__30_281);
  string__30_283 = collect_node(string__30_283);
  func__30_279 = collect_node(func__30_279);
  func__30_258 = collect_node(func__30_258);
  func__30_1 = collect_node(func__30_1);
  string__56_1 = collect_node(string__56_1);
  string__56_2 = collect_node(string__56_2);
  string__57_1 = collect_node(string__57_1);
  string__57_2 = collect_node(string__57_2);
  character__35 = collect_node(character__35);
  character__122 = collect_node(character__122);
  character__47 = collect_node(character__47);
  character__63 = collect_node(character__63);
  character__44 = collect_node(character__44);
  character__58 = collect_node(character__58);
  number__0 = collect_node(number__0);
  number__3 = collect_node(number__3);
  character__60 = collect_node(character__60);
  character__34 = collect_node(character__34);
  number__5 = collect_node(number__5);
  character__36 = collect_node(character__36);
  character__91 = collect_node(character__91);
  character__32 = collect_node(character__32);
  character__61 = collect_node(character__61);
  character__97 = collect_node(character__97);
  number__1 = collect_node(number__1);
  number__2 = collect_node(number__2);
  character__42 = collect_node(character__42);
  character__62 = collect_node(character__62);
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
  set_module("extractor");
  set_used_namespaces(used_namespaces);
  character__35 = create_future();
  character__122 = create_future();
  character__47 = create_future();
  character__63 = create_future();
  character__44 = create_future();
  character__58 = create_future();
  number__0 = create_future();
  number__3 = create_future();
  character__60 = create_future();
  character__34 = create_future();
  number__5 = create_future();
  character__36 = create_future();
  character__91 = create_future();
  character__32 = create_future();
  character__61 = create_future();
  character__97 = create_future();
  number__1 = create_future();
  number__2 = create_future();
  character__42 = create_future();
  character__62 = create_future();
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
  string__16_5 = from_latin_1_string("body {\012  background-color: white;\012  font-family: Times New Roman, Times;\012  font-size: 12pt;\012  color: #222;\012}\012h1 {\012  font-family: Arial, Helvetica;\012  font-size: 20pt;\012  color: #333;\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012h2 {\012  font-family: Arial, Helvetica;\012  font-size: 16pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 5pt;\012}\012h3 {\012  font-family: Arial, Helvetica;\012  font-size: 14pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 3pt;\012}\012h4 {\012  font-family: Arial, Helvetica;\012  font-size: 13pt;\012  color: #222;\012  margin-top: 0pt;\012  margin-bottom: 2pt;\012}\012dt {\012  font-style: italic;\012  margin-bottom: 4pt;\012}\012dd {\012  padding-left: 0pt;\012  margin-left: 16pt;\012  margin-top: 0pt;\012  margin-bottom: 0pt;\012}\012p {\012  margin-top: 0pt;\012  margin-bottom: 8pt;\012}\012a {\012  text-decoration: none;\012}\012div.Example {\012  background-color: #ffc;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.Output {\012  background-color: #cff;\012  border: solid 1pt;\012  margin-top: 6pt;\012  margin-bottom: 8pt;\012}\012div.footer {\012  padding-top: 10pt;\012  font-size: 10pt;\012}\012pre {\012  font-family: Courier New, Courier;\012  font-size: 12pt;\012  padding-top: 0pt;\012  padding-bottom: 0pt;\012  margin-top: 2pt;\012  margin-bottom: 2pt;\012}\012td.remark {\012  padding-left: 10pt;\012}\012", 1234);
  func__16_4 = create_future();
  func__16_1 = create_future();
  var._symbol_info = create_future();
  string__18_2 = from_latin_1_string("extracting documentation from ", 30);
  string__18_3 = from_latin_1_string("\012", 1);
  string__18_11 = from_latin_1_string("Empty source text!", 18);
  func__18_10 = create_future();
  string__18_17 = from_latin_1_string("Whitespace at start of source text!", 35);
  func__18_16 = create_future();
  string__18_24 = from_latin_1_string("Missing newline at end of source text!", 38);
  func__18_23 = create_future();
  string__18_26 = from_latin_1_string(".sim", 4);
  string__18_28 = from_latin_1_string("__", 2);
  func__18_32 = create_future();
  string__18_55 = from_latin_1_string("std", 3);
  func__18_54 = create_future();
  func__18_61 = create_future();
  func__18_64 = create_future();
  func__18_87 = create_future();
  string__18_92 = from_latin_1_string("type", 4);
  func__18_105 = create_future();
  string__18_135 = from_latin_1_string("types::function", 15);
  func__18_1 = create_future();
  string__19_10 = from_latin_1_string(".sim", 4);
  func__19_4 = create_future();
  func__19_1 = create_future();
  string__20_14 = from_latin_1_string("The attribute \042", 15);
  string__20_15 = from_latin_1_string("\042 cannot be uniquely resolved!\012", 31);
  string__20_21 = from_latin_1_string("The attribute \042", 15);
  string__20_22 = from_latin_1_string("\042 cannot be resolved!\012", 22);
  string__20_25 = from_latin_1_string("::", 2);
  func__20_1 = create_future();
  string__21_2 = from_latin_1_string("::", 2);
  string__21_4 = from_latin_1_string("::", 2);
  func__21_1 = create_future();
  string__22_2 = from_latin_1_string("::", 2);
  string__22_3 = from_latin_1_string("__", 2);
  string__22_5 = from_latin_1_string("___", 3);
  func__22_1 = create_future();
  func__23_1 = create_future();
  string__24_3 = from_latin_1_string("href", 4);
  string__24_4 = from_latin_1_string("index.html", 10);
  string__24_6 = from_latin_1_string("Home", 4);
  string__24_8 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__24_10 = from_latin_1_string("href", 4);
  string__24_11 = from_latin_1_string("manual.html", 11);
  string__24_13 = from_latin_1_string("Manual", 6);
  string__24_15 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__24_17 = from_latin_1_string("href", 4);
  string__24_18 = from_latin_1_string("type_index.html", 15);
  string__24_20 = from_latin_1_string("Type Index", 10);
  string__24_22 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__24_24 = from_latin_1_string("href", 4);
  string__24_25 = from_latin_1_string("symbol_index.html", 17);
  string__24_27 = from_latin_1_string("Symbol Index", 12);
  string__24_29 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__24_31 = from_latin_1_string("href", 4);
  string__24_32 = from_latin_1_string("topic_index.html", 16);
  string__24_34 = from_latin_1_string("Topic Index", 11);
  func__24_2 = create_future();
  func__24_1 = create_future();
  string__25_6 = from_latin_1_string("::", 2);
  string__25_9 = from_latin_1_string("types::", 7);
  string__25_12 = from_latin_1_string("::", 2);
  string__25_15 = from_latin_1_string("std::", 5);
  string__25_20 = from_latin_1_string("::", 2);
  string__25_23 = from_latin_1_string("std::", 5);
  func__25_1 = create_future();
  var._TOPIC = create_future();
  var._EXAMPLE = create_future();
  func__28_1 = create_future();
  string__29_5 = from_latin_1_string("html/", 5);
  string__29_6 = from_latin_1_string(".html", 5);
  string__29_16 = from_latin_1_string("](", 2);
  string__29_17 = from_latin_1_string(".html)/[", 8);
  string__29_18 = from_latin_1_string("](", 2);
  string__29_19 = from_latin_1_string(".html)", 6);
  string__29_30 = from_latin_1_string("Parameter", 9);
  string__29_40 = from_latin_1_string(" (optional)", 11);
  string__29_47 = from_latin_1_string(" (zero or more arguments)", 25);
  string__29_56 = from_latin_1_string(" (optional; default value: ", 27);
  string__29_57 = from_latin_1_string(")", 1);
  string__29_66 = from_latin_1_string("Returns", 7);
  string__29_76 = from_latin_1_string(" (optional)", 11);
  string__29_83 = from_latin_1_string(" (zero or more arguments)", 25);
  string__29_91 = from_latin_1_string("See Also:", 9);
  string__29_120 = from_latin_1_string("Technical Details:", 18);
  string__29_138 = from_latin_1_string("[", 1);
  string__29_139 = from_latin_1_string("](", 2);
  string__29_140 = from_latin_1_string(".html)", 6);
  func__29_133 = create_future();
  string__29_172 = from_latin_1_string(" (optional; default value: ", 27);
  string__29_173 = from_latin_1_string(")", 1);
  string__29_176 = from_latin_1_string(" (optional)", 11);
  string__29_181 = from_latin_1_string(" (zero or more arguments)", 25);
  func__29_191 = create_future();
  func__29_195 = create_future();
  string__29_202 = from_latin_1_string("Parameters", 10);
  func__29_205 = create_future();
  string__29_213 = from_latin_1_string("Returns", 7);
  func__29_216 = create_future();
  string__29_224 = from_latin_1_string("Description", 11);
  func__29_226 = create_future();
  string__29_230 = from_latin_1_string("Technical Details", 17);
  func__29_232 = create_future();
  string__29_236 = from_latin_1_string("See Also", 8);
  string__29_242 = from_latin_1_string(".html", 5);
  string__29_244 = from_latin_1_string("href", 4);
  func__29_239 = create_future();
  string__29_251 = from_latin_1_string("Implemented by", 14);
  string__29_260 = from_latin_1_string(".html", 5);
  string__29_262 = from_latin_1_string("href", 4);
  string__29_265 = from_latin_1_string("&nbsp;as&nbsp;", 14);
  string__29_269 = from_latin_1_string(".html", 5);
  string__29_271 = from_latin_1_string("href", 4);
  string__29_277 = from_latin_1_string("Supported Polymorphic Functions", 31);
  string__29_285 = from_latin_1_string(".html", 5);
  string__29_287 = from_latin_1_string("href", 4);
  string__29_290 = from_latin_1_string("&nbsp;", 6);
  string__29_295 = from_latin_1_string("___", 3);
  string__29_296 = from_latin_1_string(".html", 5);
  string__29_298 = from_latin_1_string("href", 4);
  string__29_302 = from_latin_1_string("::", 2);
  string__29_310 = from_latin_1_string("class", 5);
  func__29_317 = create_future();
  string__29_319 = from_latin_1_string("**", 2);
  string__29_320 = from_latin_1_string("**", 2);
  string__29_325 = from_latin_1_string("class", 5);
  string__29_326 = from_latin_1_string("footer", 6);
  string__29_330 = from_latin_1_string("(defined in ", 12);
  string__29_331 = from_latin_1_string(")\012", 2);
  func__29_1 = create_future();
  string__30_3 = from_latin_1_string("p", 1);
  string__30_6 = from_latin_1_string("&lt;", 4);
  string__30_7 = from_latin_1_string("::", 2);
  string__30_14 = from_latin_1_string("<a href=\042", 9);
  string__30_15 = from_latin_1_string(".html\042>", 7);
  string__30_16 = from_latin_1_string("</a>", 4);
  func__30_9 = create_future();
  func__30_2 = create_future();
  string__30_34 = from_latin_1_string("::", 2);
  string__30_43 = from_latin_1_string("::", 2);
  string__30_45 = from_latin_1_string("::", 2);
  func__30_24 = create_future();
  string__30_59 = from_latin_1_string("html/type_index.html", 20);
  string__30_68 = from_latin_1_string("&nbsp;&nbsp;&nbsp;", 18);
  string__30_72 = from_latin_1_string(".html", 5);
  string__30_74 = from_latin_1_string("href", 4);
  string__30_91 = from_latin_1_string("Type Index", 10);
  func__30_60 = create_future();
  string__30_103 = from_latin_1_string("html/symbol_index.html", 22);
  string__30_106 = from_latin_1_string("id", 2);
  string__30_107 = from_latin_1_string("index", 5);
  string__30_109 = from_latin_1_string("Symbol Index", 12);
  string__30_112 = from_latin_1_string("#", 1);
  string__30_114 = from_latin_1_string("href", 4);
  func__30_111 = create_future();
  string__30_118 = from_latin_1_string(" ", 1);
  func__30_117 = create_future();
  string__30_129 = from_latin_1_string("colspan", 7);
  string__30_132 = from_latin_1_string("id", 2);
  string__30_137 = from_latin_1_string("href", 4);
  string__30_138 = from_latin_1_string("#index", 6);
  string__30_140 = from_latin_1_string("&nbsp;&#x2302;", 14);
  string__30_155 = from_latin_1_string("function", 8);
  func__30_154 = create_future();
  string__30_157 = from_latin_1_string("inline-C function", 17);
  func__30_156 = create_future();
  string__30_159 = from_latin_1_string("polymorphic function", 20);
  func__30_158 = create_future();
  string__30_161 = from_latin_1_string("unique item", 11);
  func__30_160 = create_future();
  string__30_163 = from_latin_1_string("type", 4);
  func__30_162 = create_future();
  func__30_164 = create_future();
  string__30_170 = from_latin_1_string(" (", 2);
  string__30_171 = from_latin_1_string(")", 1);
  string__30_181 = from_latin_1_string("align", 5);
  string__30_182 = from_latin_1_string("right", 5);
  string__30_184 = from_latin_1_string("::", 2);
  string__30_189 = from_latin_1_string(".html", 5);
  string__30_191 = from_latin_1_string("href", 4);
  string__30_193 = from_latin_1_string("::", 2);
  string__30_196 = from_latin_1_string("class", 5);
  string__30_197 = from_latin_1_string("remark", 6);
  func__30_121 = create_future();
  func__30_104 = create_future();
  string__30_209 = from_latin_1_string("/", 1);
  func__30_200 = create_future();
  string__30_212 = from_latin_1_string("html/topic_index.html", 21);
  string__30_215 = from_latin_1_string("id", 2);
  string__30_216 = from_latin_1_string("index", 5);
  string__30_218 = from_latin_1_string("Topic Index", 11);
  string__30_223 = from_latin_1_string("_", 1);
  string__30_226 = from_latin_1_string(".html", 5);
  string__30_230 = from_latin_1_string("href", 4);
  func__30_221 = create_future();
  func__30_220 = create_future();
  func__30_213 = create_future();
  string__30_235 = from_latin_1_string("_", 1);
  string__30_238 = from_latin_1_string("html/", 5);
  string__30_239 = from_latin_1_string(".html", 5);
  string__30_243 = from_latin_1_string("id", 2);
  string__30_244 = from_latin_1_string("index", 5);
  string__30_252 = from_latin_1_string(".html", 5);
  string__30_254 = from_latin_1_string("href", 4);
  func__30_248 = create_future();
  func__30_233 = create_future();
  string__30_257 = from_latin_1_string("html/index.html", 15);
  string__30_259 = from_latin_1_string("Simplicity", 10);
  string__30_262 = from_latin_1_string("href", 4);
  string__30_263 = from_latin_1_string("manual.html", 11);
  string__30_265 = from_latin_1_string("Manual", 6);
  func__30_261 = create_future();
  string__30_268 = from_latin_1_string("href", 4);
  string__30_269 = from_latin_1_string("type_index.html", 15);
  string__30_271 = from_latin_1_string("Type Index", 10);
  func__30_267 = create_future();
  string__30_274 = from_latin_1_string("href", 4);
  string__30_275 = from_latin_1_string("symbol_index.html", 17);
  string__30_277 = from_latin_1_string("Symbol Index", 12);
  func__30_273 = create_future();
  string__30_280 = from_latin_1_string("href", 4);
  string__30_281 = from_latin_1_string("topic_index.html", 16);
  string__30_283 = from_latin_1_string("Topic Index", 11);
  func__30_279 = create_future();
  func__30_258 = create_future();
  func__30_1 = create_future();
  define_single_assign_static("sim2c", "extract_documentation", get__sim2c__extract_documentation, &var.sim2c__extract_documentation);
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

static int already_run_phase_4 = false;

EXPORT void phase_4__extractor(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  assign_value(&character__35, from_uchar32(35));
  assign_value(&character__122, from_uchar32(122));
  assign_value(&character__47, from_uchar32(47));
  assign_value(&character__63, from_uchar32(63));
  assign_value(&character__44, from_uchar32(44));
  assign_value(&character__58, from_uchar32(58));
  assign_value(&number__0, from_uint32(0U));
  assign_value(&number__3, from_uint32(3U));
  assign_value(&character__60, from_uchar32(60));
  assign_value(&character__34, from_uchar32(34));
  assign_value(&number__5, from_uint32(5U));
  assign_value(&character__36, from_uchar32(36));
  assign_value(&character__91, from_uchar32(91));
  assign_value(&character__32, from_uchar32(32));
  assign_value(&character__61, from_uchar32(61));
  assign_value(&character__97, from_uchar32(97));
  assign_value(&number__1, from_uint32(1U));
  assign_value(&number__2, from_uint32(2U));
  assign_value(&character__42, from_uchar32(42));
  assign_value(&character__62, from_uchar32(62));
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

static int already_run_phase_5 = false;

EXPORT void phase_5__extractor(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&func__16_4, create_function(entry__16_4, 0));
  assign_value(&func__16_1, create_function(entry__16_1, 2));
  assign_value(&func__18_10, create_function(entry__18_10, 0));
  assign_value(&func__18_16, create_function(entry__18_16, 0));
  assign_value(&func__18_23, create_function(entry__18_23, 0));
  assign_value(&func__18_32, create_function(entry__18_32, 1));
  assign_value(&func__18_54, create_function(entry__18_54, 0));
  assign_value(&func__18_61, create_function(entry__18_61, 0));
  assign_value(&func__18_64, create_function(entry__18_64, 0));
  assign_value(&func__18_87, create_function(entry__18_87, 0));
  assign_value(&func__18_105, create_function(entry__18_105, 0));
  assign_value(&func__18_1, create_function(entry__18_1, 1));
  assign_value(&func__19_4, create_function(entry__19_4, 1));
  assign_value(&func__19_1, create_function(entry__19_1, 1));
  assign_value(&func__20_1, create_function(entry__20_1, 1));
  assign_value(&func__21_1, create_function(entry__21_1, 2));
  assign_value(&func__22_1, create_function(entry__22_1, 1));
  assign_value(&func__23_1, create_function(entry__23_1, 2));
  assign_value(&func__24_2, create_function(entry__24_2, 0));
  assign_value(&func__24_1, create_function(entry__24_1, 0));
  assign_value(&func__25_1, create_function(entry__25_1, 1));
  assign_value(&func__28_1, create_function(entry__28_1, 1));
  assign_value(&func__29_133, create_function(entry__29_133, 1));
  assign_value(&func__29_191, create_function(entry__29_191, 0));
  assign_value(&func__29_195, create_function(entry__29_195, 0));
  assign_value(&func__29_205, create_function(entry__29_205, 1));
  assign_value(&func__29_216, create_function(entry__29_216, 1));
  assign_value(&func__29_226, create_function(entry__29_226, 1));
  assign_value(&func__29_232, create_function(entry__29_232, 1));
  assign_value(&func__29_239, create_function(entry__29_239, 1));
  assign_value(&func__29_317, create_function(entry__29_317, 1));
  assign_value(&func__29_1, create_function(entry__29_1, 2));
  assign_value(&func__30_9, create_function(entry__30_9, 1));
  assign_value(&func__30_2, create_function(entry__30_2, 3));
  assign_value(&func__30_24, create_function(entry__30_24, 2));
  assign_value(&func__30_60, create_function(entry__30_60, 0));
  assign_value(&func__30_111, create_function(entry__30_111, 1));
  assign_value(&func__30_117, create_function(entry__30_117, 0));
  assign_value(&func__30_154, create_function(entry__30_154, 0));
  assign_value(&func__30_156, create_function(entry__30_156, 0));
  assign_value(&func__30_158, create_function(entry__30_158, 0));
  assign_value(&func__30_160, create_function(entry__30_160, 0));
  assign_value(&func__30_162, create_function(entry__30_162, 0));
  assign_value(&func__30_164, create_function(entry__30_164, 0));
  assign_value(&func__30_121, create_function(entry__30_121, 0));
  assign_value(&func__30_104, create_function(entry__30_104, 0));
  assign_value(&func__30_200, create_function(entry__30_200, 2));
  assign_value(&func__30_221, create_function(entry__30_221, 2));
  assign_value(&func__30_220, create_function(entry__30_220, 0));
  assign_value(&func__30_213, create_function(entry__30_213, 0));
  assign_value(&func__30_248, create_function(entry__30_248, 1));
  assign_value(&func__30_233, create_function(entry__30_233, 2));
  assign_value(&func__30_261, create_function(entry__30_261, 0));
  assign_value(&func__30_267, create_function(entry__30_267, 0));
  assign_value(&func__30_273, create_function(entry__30_273, 0));
  assign_value(&func__30_279, create_function(entry__30_279, 0));
  assign_value(&func__30_258, create_function(entry__30_258, 0));
  assign_value(&func__30_1, create_function(entry__30_1, 1));
  register_collector(collect__extractor);
}
