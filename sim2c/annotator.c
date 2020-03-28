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
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
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
REGISTER NODE *myself ASM("r13");
IMPORT NODE *get_attribute(NODE *node, int idx);
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
IMPORT NODE *undefined;
IMPORT NODE *create_cell_with_contents(NODE *contents);
typedef struct CELL {
  FUNC type;
  struct ATTRIBUTES *attributes;
  NODE *contents;
} CELL;
IMPORT int result_count;
IMPORT void invalid_results_error(void);
IMPORT NODE *create_closure(FUNC type, int par_count);
IMPORT NODE *create_future(void);
IMPORT void initialize_future(NODE *var, NODE *val);
IMPORT NODE *create_cell(void);
IMPORT NODE *create_continuation(void);
IMPORT NODE *collect_node(NODE *node);
IMPORT void register_module_info(MODULE_INFO *info);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *from_uchar32(unsigned int chr);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
IMPORT void set_module(const char *name);
IMPORT void set_used_namespaces(const char **namespaces);
IMPORT void register_dynamic(int *id_p);
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
IMPORT void use_read_write(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter
);
IMPORT void use_multi_assign_dynamic(
  const char *namespace, const char *name,
  NODE_GETTER *getter, NODE_SETTER *setter, NODE_SETTER *definer
);
IMPORT void define_method(
  const char *namespace, const char *name,
  int id, NODE *method
);
IMPORT void assign_value(NODE **dest, NODE *val);
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
static NODE_GETTER get__CONTINUATION_PARAMETER;
static NODE_GETTER get_value_or_future__CONTINUATION_PARAMETER;
static NODE_GETTER get__DYNAMIC_MULTI;
static NODE_GETTER get_value_or_future__DYNAMIC_MULTI;
static NODE_GETTER get__DYNAMIC_SINGLE;
static NODE_GETTER get_value_or_future__DYNAMIC_SINGLE;
static NODE_GETTER get__IN_OUT_PARAMETER;
static NODE_GETTER get_value_or_future__IN_OUT_PARAMETER;
static NODE_GETTER get__NONE;
static NODE_GETTER get_value_or_future__NONE;
static NODE_GETTER get__POLYMORPHIC;
static NODE_GETTER get_value_or_future__POLYMORPHIC;
static NODE_GETTER get__STATIC_MULTI;
static NODE_GETTER get_value_or_future__STATIC_MULTI;
static NODE_GETTER get__STATIC_SINGLE;
static NODE_GETTER get_value_or_future__STATIC_SINGLE;
static NODE_GETTER get__SyntaxError;
static NODE_GETTER get_value_or_future__SyntaxError;
static NODE_GETTER get__Warning;
static NODE_GETTER get_value_or_future__Warning;
static int poly_idx__annotate_expression;
static NODE_GETTER get__annotate_expression;
static int poly_idx__annotate_statement;
static NODE_GETTER get__annotate_statement;
static int poly_idx__arguments_of;
static NODE_GETTER get__arguments_of;
static NODE_GETTER get__assigned_names;
static NODE_SETTER set__assigned_names;
static NODE_GETTER get__attribute_kind_of;
static NODE_GETTER get_value_or_future__attribute_kind_of;
static int poly_idx__attribute_of;
static NODE_GETTER get__attribute_of;
static int poly_idx__base_of;
static NODE_GETTER get__base_of;
static NODE_GETTER get__case;
static NODE_GETTER get_value_or_future__case;
static NODE_GETTER get__check_definitions;
static NODE_GETTER get_value_or_future__check_definitions;
static NODE_GETTER get__cond;
static NODE_GETTER get_value_or_future__cond;
static int poly_idx__continuation_of;
static NODE_GETTER get__continuation_of;
static int poly_idx__default_value_of;
static NODE_GETTER get__default_value_of;
static NODE_GETTER get__define_static_single;
static NODE_GETTER get_value_or_future__define_static_single;
static NODE_GETTER get__defined_names;
static NODE_SETTER set__defined_names;
static int poly_idx__defined_names_of;
static NODE_GETTER get__defined_names_of;
static int poly_idx__defines_a_dynamic;
static NODE_GETTER get__defines_a_dynamic;
static NODE_GETTER get__do;
static NODE_GETTER get_value_or_future__do;
static NODE_GETTER get__do_print_warnings;
static NODE_GETTER get_value_or_future__do_print_warnings;
static NODE_GETTER get__empty_insert_order_table;
static NODE_GETTER get_value_or_future__empty_insert_order_table;
static NODE_GETTER get__empty_list;
static NODE_GETTER get_value_or_future__empty_list;
static NODE_GETTER get__empty_set;
static NODE_GETTER get_value_or_future__empty_set;
static NODE_GETTER get__false;
static NODE_GETTER get_value_or_future__false;
static NODE_GETTER get__for_each;
static NODE_GETTER get_value_or_future__for_each;
static NODE_GETTER get__full_name_of;
static NODE_GETTER get_value_or_future__full_name_of;
static int poly_idx__functor_of;
static NODE_GETTER get__functor_of;
static NODE_GETTER get__identifier;
static NODE_GETTER get_value_or_future__identifier;
static int poly_idx__identifier_of;
static NODE_GETTER get__identifier_of;
static NODE_GETTER get__if;
static NODE_GETTER get_value_or_future__if;
static NODE_GETTER get__inc;
static NODE_GETTER get_value_or_future__inc;
static NODE_GETTER get__index;
static NODE_SETTER set__index;
static NODE_GETTER get__is_a_body;
static NODE_GETTER get_value_or_future__is_a_body;
static NODE_GETTER get__is_a_c_body;
static NODE_GETTER get_value_or_future__is_a_c_body;
static NODE_GETTER get__is_a_definition;
static NODE_GETTER get_value_or_future__is_a_definition;
static NODE_GETTER get__is_a_destination;
static NODE_GETTER get_value_or_future__is_a_destination;
static NODE_GETTER get__is_a_function_call;
static NODE_GETTER get_value_or_future__is_a_function_call;
static NODE_GETTER get__is_a_multi_assign_definition;
static NODE_GETTER get_value_or_future__is_a_multi_assign_definition;
static int poly_idx__is_a_single_assign_definition;
static NODE_GETTER get__is_a_single_assign_definition;
static NODE_GETTER get__is_a_unique_item_constant;
static NODE_GETTER get_value_or_future__is_a_unique_item_constant;
static NODE_GETTER get__is_an_assignment;
static NODE_GETTER get_value_or_future__is_an_assignment;
static NODE_GETTER get__is_an_attribute_access;
static NODE_GETTER get_value_or_future__is_an_attribute_access;
static NODE_GETTER get__is_an_operator_symbol;
static NODE_GETTER get_value_or_future__is_an_operator_symbol;
static NODE_GETTER get__is_an_optional_item;
static NODE_GETTER get_value_or_future__is_an_optional_item;
static NODE_GETTER get__is_defined;
static NODE_GETTER get_value_or_future__is_defined;
static NODE_GETTER get__is_empty;
static NODE_GETTER get_value_or_future__is_empty;
static NODE_GETTER get__is_not_used;
static NODE_GETTER get_value_or_future__is_not_used;
static NODE_GETTER get__is_undefined;
static NODE_GETTER get_value_or_future__is_undefined;
static NODE_GETTER get__is_used_as_a_polymorphic_function;
static NODE_GETTER get_value_or_future__is_used_as_a_polymorphic_function;
static NODE_GETTER get__kind_of;
static NODE_GETTER get_value_or_future__kind_of;
static NODE_GETTER get__mangled_name_of;
static NODE_GETTER get_value_or_future__mangled_name_of;
static int poly_idx__name_of;
static NODE_GETTER get__name_of;
static NODE_GETTER get__namespace_mappings;
static NODE_GETTER get_value_or_future__namespace_mappings;
static int poly_idx__namespace_of;
static NODE_GETTER get__namespace_of;
static NODE_GETTER get__not;
static NODE_GETTER get_value_or_future__not;
static int poly_idx__output_arguments_of;
static NODE_GETTER get__output_arguments_of;
static int poly_idx__parameter_kind_of;
static NODE_GETTER get__parameter_kind_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static NODE_GETTER get__range;
static NODE_GETTER get_value_or_future__range;
static NODE_GETTER get__replace_all;
static NODE_GETTER get_value_or_future__replace_all;
static int poly_idx__result_count_of;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static NODE_GETTER get__sim2c__assigned_names;
static NODE_SETTER set__sim2c__assigned_names;
static NODE_SETTER define__sim2c__assigned_names;
static NODE_GETTER get__sim2c__attribute_function_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_function_pair;
static NODE_GETTER get__sim2c__attribute_value_pair;
static NODE_GETTER get_value_or_future__sim2c__attribute_value_pair;
static NODE_GETTER get__sim2c__body;
static NODE_GETTER get_value_or_future__sim2c__body;
static NODE_GETTER get__sim2c__c_code;
static NODE_GETTER get_value_or_future__sim2c__c_code;
static NODE_GETTER get__sim2c__call;
static NODE_GETTER get_value_or_future__sim2c__call;
static NODE_GETTER get__sim2c__define_dynamic_multi;
static NODE_GETTER get_value_or_future__sim2c__define_dynamic_multi;
static NODE_GETTER get__sim2c__define_dynamic_single;
static NODE_GETTER get_value_or_future__sim2c__define_dynamic_single;
static NODE_GETTER get__sim2c__define_static_multi;
static NODE_GETTER get_value_or_future__sim2c__define_static_multi;
static NODE_GETTER get__sim2c__define_static_single;
static NODE_GETTER get_value_or_future__sim2c__define_static_single;
static NODE_GETTER get__sim2c__defined_names;
static NODE_SETTER set__sim2c__defined_names;
static NODE_SETTER define__sim2c__defined_names;
static NODE_GETTER get__sim2c__function_call;
static NODE_GETTER get_value_or_future__sim2c__function_call;
static NODE_GETTER get__sim2c__identifier;
static NODE_GETTER get_value_or_future__sim2c__identifier;
static NODE_GETTER get__sim2c__used_names;
static NODE_SETTER set__sim2c__used_names;
static NODE_SETTER define__sim2c__used_names;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
static NODE_GETTER get__std__key_value_pair;
static NODE_GETTER get_value_or_future__std__key_value_pair;
static NODE_GETTER get__std__negate;
static NODE_GETTER get_value_or_future__std__negate;
static NODE_GETTER get__std__not;
static NODE_GETTER get_value_or_future__std__not;
static NODE_GETTER get__std__or;
static NODE_GETTER get_value_or_future__std__or;
static NODE_GETTER get__std__sequence;
static NODE_GETTER get_value_or_future__std__sequence;
static NODE_GETTER get__std__string;
static NODE_GETTER get_value_or_future__std__string;
static NODE_GETTER get__to_string;
static NODE_GETTER get_value_or_future__to_string;
static NODE_GETTER get__true;
static NODE_GETTER get_value_or_future__true;
static NODE_GETTER get__types__grammar_node;
static NODE_GETTER get_value_or_future__types__grammar_node;
static NODE_GETTER get__undefined;
static NODE_GETTER get_value_or_future__undefined;
static NODE_GETTER get__unless;
static NODE_GETTER get_value_or_future__unless;
static NODE_GETTER get__update_each;
static NODE_GETTER get_value_or_future__update_each;
static NODE_GETTER get__update_info;
static NODE_GETTER get_value_or_future__update_info;
static NODE_GETTER get__used_names;
static NODE_SETTER set__used_names;
static int poly_idx__used_names_of;
static NODE_GETTER get__used_names_of;
static int poly_idx__variable_kind_of;
static NODE_GETTER get__variable_kind_of;
static NODE_GETTER get__while;
static NODE_GETTER get_value_or_future__while;
static struct {
  NODE *_annotate_output_arguments;
  NODE *_annotate_arguments;
  NODE *sim2c__annotate_statement;
  NODE *sim2c__annotate_expression;
  NODE *sim2c__check_definitions;
} var;
static const char *var_names[] = {
  "annotate_output_arguments",
  "annotate_arguments"
};
static int dyna_idx__defines_dynamics;
static NODE *get__defines_dynamics(void) {
  return get_dynamic_cell(dyna_idx__defines_dynamics);
}
static void set__defines_dynamics(NODE *node) {
  set_dynamic_cell(dyna_idx__defines_dynamics, node);
}
static void define__defines_dynamics(NODE *node) {
  define_dynamic_cell(dyna_idx__defines_dynamics, node);
}
static int poly_idx__sim2c__annotate_statement;
static void type__sim2c__annotate_statement(void);
static NODE *get__sim2c__annotate_statement(void) {
  return var.sim2c__annotate_statement;
}
static int poly_idx__sim2c__annotate_expression;
static void type__sim2c__annotate_expression(void);
static NODE *get__sim2c__annotate_expression(void) {
  return var.sim2c__annotate_expression;
}
static NODE *func__4_1_annotate_output_arguments;
static void entry__4_1_annotate_output_arguments(void);
static FRAME_INFO frame__4_1_annotate_output_arguments = {1, {"arguments"}};
static NODE *func__4_2;
static void entry__4_2(void);
static FRAME_INFO frame__4_2 = {1, {"argument"}};
static void cont__4_3(void);
static NODE *func__4_4;
static void entry__4_4(void);
static FRAME_INFO frame__4_4 = {2, {"argument", "destination"}};
static void cont__4_5(void);
static NODE *func__4_6;
static void entry__4_6(void);
static FRAME_INFO frame__4_6 = {2, {"destination", "name"}};
static NODE *func__4_7;
static void entry__4_7(void);
static FRAME_INFO frame__4_7 = {1, {"destination"}};
static void cont__4_8(void);
static NODE *func__4_9;
static void entry__4_9(void);
static FRAME_INFO frame__4_9 = {1, {"destination"}};
static void cont__4_10(void);
static NODE *func__4_11;
static void entry__4_11(void);
static FRAME_INFO frame__4_11 = {1, {"destination"}};
static void cont__4_12(void);
static void cont__4_13(void);
static NODE *func__4_14;
static void entry__4_14(void);
static FRAME_INFO frame__4_14 = {1, {"destination"}};
static void cont__4_15(void);
static void cont__4_16(void);
static void cont__4_17(void);
static void cont__4_18(void);
static void cont__4_19(void);
static void cont__4_20(void);
static NODE *func__5_1_annotate_arguments;
static void entry__5_1_annotate_arguments(void);
static FRAME_INFO frame__5_1_annotate_arguments = {1, {"arguments"}};
static NODE *func__5_2;
static void entry__5_2(void);
static FRAME_INFO frame__5_2 = {1, {"argument"}};
static void cont__5_3(void);
static void cont__5_4(void);
static NODE *func__6_1_types__grammar_node_annotate_statement;
static void entry__6_1_types__grammar_node_annotate_statement(void);
static FRAME_INFO frame__6_1_types__grammar_node_annotate_statement = {1, {"self"}};
static NODE *string__6_2;
static void cont__6_3(void);
static NODE *func__7_1_types__grammar_node_annotate_expression;
static void entry__7_1_types__grammar_node_annotate_expression(void);
static FRAME_INFO frame__7_1_types__grammar_node_annotate_expression = {1, {"self"}};
static NODE *string__7_2;
static void cont__7_3(void);
static NODE *func__8_1_sim2c__check_definitions;
static void entry__8_1_sim2c__check_definitions(void);
static FRAME_INFO frame__8_1_sim2c__check_definitions = {2, {"defined_names", "used_names"}};
static NODE *func__8_2;
static void entry__8_2(void);
static FRAME_INFO frame__8_2 = {4, {"name", "info", "used_names", "identifier"}};
static void cont__8_3(void);
static void cont__8_4(void);
static void cont__8_5(void);
static NODE *func__8_6;
static void entry__8_6(void);
static FRAME_INFO frame__8_6 = {4, {"used_names", "name", "identifier", "info"}};
static void cont__8_7(void);
static void cont__8_8(void);
static NODE *func__8_9;
static void entry__8_9(void);
static FRAME_INFO frame__8_9 = {2, {"identifier", "name"}};
static void cont__8_10(void);
static NODE *func__8_11;
static void entry__8_11(void);
static FRAME_INFO frame__8_11 = {2, {"identifier", "name"}};
static NODE *string__8_12;
static NODE *string__8_13;
static void cont__8_14(void);
static NODE *func__8_15;
static void entry__8_15(void);
static FRAME_INFO frame__8_15 = {3, {"info", "name", "identifier"}};
static void cont__8_16(void);
static NODE *func__8_17;
static void entry__8_17(void);
static FRAME_INFO frame__8_17 = {2, {"info", "name"}};
static void cont__8_18(void);
static void cont__8_19(void);
static void cont__8_20(void);
static NODE *func__8_21;
static void entry__8_21(void);
static FRAME_INFO frame__8_21 = {1, {"name"}};
static void cont__8_22(void);
static void cont__8_23(void);
static void cont__8_24(void);
static void cont__8_25(void);
static NODE *func__8_26;
static void entry__8_26(void);
static FRAME_INFO frame__8_26 = {2, {"identifier", "name"}};
static NODE *string__8_27;
static void cont__8_28(void);
static void cont__8_29(void);
static NODE *func__8_30;
static void entry__8_30(void);
static FRAME_INFO frame__8_30 = {4, {"name", "info", "defined_names", "defined_name"}};
static void cont__8_31(void);
static void cont__8_32(void);
static NODE *func__8_33;
static void entry__8_33(void);
static FRAME_INFO frame__8_33 = {3, {"defined_name", "info", "name"}};
static NODE *func__8_34;
static void entry__8_34(void);
static FRAME_INFO frame__8_34 = {1, {"defined_name"}};
static void cont__8_35(void);
static void cont__8_36(void);
static void cont__8_37(void);
static NODE *func__8_38;
static void entry__8_38(void);
static FRAME_INFO frame__8_38 = {2, {"info", "name"}};
static void cont__8_39(void);
static NODE *string__8_40;
static NODE *string__8_41;
static void cont__8_42(void);
static NODE *get__sim2c__check_definitions(void) {
  return var.sim2c__check_definitions;
}
static NODE *func__9_1_sim2c__body_annotate_expression;
static void entry__9_1_sim2c__body_annotate_expression(void);
static FRAME_INFO frame__9_1_sim2c__body_annotate_expression = {2, {"self", "locally_assigned_names"}};
static NODE *string__9_2;
static void cont__9_3(void);
static NODE *func__9_4;
static void entry__9_4(void);
static FRAME_INFO frame__9_4 = {4, {"return__1", "self", "locally_assigned_names", "local_definitions"}};
static void cont__9_5(void);
static NODE *func__9_6;
static void entry__9_6(void);
static FRAME_INFO frame__9_6 = {1, {"parameter"}};
static void cont__9_7(void);
static void cont__9_8(void);
static NODE *func__9_9;
static void entry__9_9(void);
static FRAME_INFO frame__9_9 = {1, {"parameter"}};
static void cont__9_10(void);
static void cont__9_11(void);
static void cont__9_12(void);
static NODE *func__9_13;
static void entry__9_13(void);
static FRAME_INFO frame__9_13 = {1, {"parameter"}};
static void cont__9_14(void);
static void cont__9_15(void);
static void cont__9_16(void);
static void cont__9_17(void);
static void cont__9_18(void);
static NODE *func__9_19;
static void entry__9_19(void);
static FRAME_INFO frame__9_19 = {1, {"stmt"}};
static void cont__9_20(void);
static void cont__9_21(void);
static NODE *func__9_22;
static void entry__9_22(void);
static FRAME_INFO frame__9_22 = {2, {"info", "local_definitions"}};
static void cont__9_23(void);
static void cont__9_24(void);
static NODE *func__9_25;
static void entry__9_25(void);
static FRAME_INFO frame__9_25 = {4, {"info", "local_definitions", "ident", "name"}};
static void cont__9_26(void);
static void cont__9_27(void);
static void cont__9_28(void);
static NODE *func__9_29;
static void entry__9_29(void);
static FRAME_INFO frame__9_29 = {1, {"ident"}};
static void cont__9_30(void);
static NODE *string__9_31;
static NODE *string__9_32;
static void cont__9_33(void);
static void cont__9_34(void);
static void cont__9_35(void);
static void cont__9_36(void);
static void cont__9_37(void);
static NODE *func__9_38;
static void entry__9_38(void);
static FRAME_INFO frame__9_38 = {2, {"ident", "name"}};
static NODE *string__9_39;
static NODE *string__9_40;
static void cont__9_41(void);
static void cont__9_42(void);
static void cont__9_43(void);
static void cont__9_44(void);
static NODE *func__9_45;
static void entry__9_45(void);
static FRAME_INFO frame__9_45 = {1, {"info"}};
static void cont__9_46(void);
static void cont__9_47(void);
static void cont__9_48(void);
static void cont__9_49(void);
static NODE *func__9_50;
static void entry__9_50(void);
static FRAME_INFO frame__9_50 = {2, {"self", "parameters"}};
static void cont__9_51(void);
static void cont__9_52(void);
static NODE *func__9_53;
static void entry__9_53(void);
static FRAME_INFO frame__9_53 = {1, {"parameters"}};
static void cont__9_54(void);
static void cont__9_55(void);
static void cont__9_56(void);
static void cont__9_57(void);
static void cont__9_58(void);
static void cont__9_59(void);
static NODE *func__9_60;
static void entry__9_60(void);
static FRAME_INFO frame__9_60 = {2, {"self", "return"}};
static NODE *string__9_61;
static void cont__9_62(void);
static void cont__9_63(void);
static void cont__9_64(void);
static void cont__9_65(void);
static void cont__9_66(void);
static NODE *func__9_67;
static void entry__9_67(void);
static FRAME_INFO frame__9_67 = {2, {"local_definitions", "locally_assigned_names"}};
static void cont__9_68(void);
static void cont__9_69(void);
static void cont__9_70(void);
static void cont__9_71(void);
static NODE *func__9_72;
static void entry__9_72(void);
static FRAME_INFO frame__9_72 = {3, {"name", "info", "self"}};
static void cont__9_73(void);
static void cont__9_74(void);
static void cont__9_75(void);
static NODE *func__9_76;
static void entry__9_76(void);
static FRAME_INFO frame__9_76 = {3, {"name", "info", "updated_info"}};
static void cont__9_77(void);
static void cont__9_78(void);
static void cont__9_79(void);
static NODE *func__9_80;
static void entry__9_80(void);
static FRAME_INFO frame__9_80 = {2, {"name", "updated_info"}};
static void cont__9_81(void);
static void cont__9_82(void);
static NODE *func__9_83;
static void entry__9_83(void);
static FRAME_INFO frame__9_83 = {1, {"locally_assigned_names"}};
static NODE *func__9_84;
static void entry__9_84(void);
static FRAME_INFO frame__9_84 = {1, {"name"}};
static void cont__9_85(void);
static void cont__9_86(void);
static NODE *func__10_1_sim2c__call_annotate_statement;
static void entry__10_1_sim2c__call_annotate_statement(void);
static FRAME_INFO frame__10_1_sim2c__call_annotate_statement = {1, {"self"}};
static void cont__10_2(void);
static void cont__10_3(void);
static NODE *func__10_4;
static void entry__10_4(void);
static FRAME_INFO frame__10_4 = {1, {"self"}};
static void cont__10_5(void);
static void cont__10_6(void);
static void cont__10_7(void);
static NODE *func__10_8;
static void entry__10_8(void);
static FRAME_INFO frame__10_8 = {1, {"self"}};
static void cont__10_9(void);
static void cont__10_10(void);
static void cont__10_11(void);
static void cont__10_12(void);
static NODE *func__10_13;
static void entry__10_13(void);
static FRAME_INFO frame__10_13 = {1, {"self"}};
static void cont__10_14(void);
static void cont__10_15(void);
static void cont__10_16(void);
static void cont__10_17(void);
static void cont__10_18(void);
static NODE *func__10_19;
static void entry__10_19(void);
static FRAME_INFO frame__10_19 = {1, {"self"}};
static void cont__10_20(void);
static void cont__10_21(void);
static void cont__10_22(void);
static void cont__10_23(void);
static void cont__10_24(void);
static NODE *string__10_25;
static NODE *string__10_26;
static void cont__10_27(void);
static NODE *string__10_28;
static void cont__10_29(void);
static void cont__10_30(void);
static void cont__10_31(void);
static void cont__10_32(void);
static void cont__10_33(void);
static void cont__10_34(void);
static void cont__10_35(void);
static void cont__10_36(void);
static void cont__10_37(void);
static NODE *func__10_38;
static void entry__10_38(void);
static FRAME_INFO frame__10_38 = {1, {"self"}};
static void cont__10_39(void);
static void cont__10_40(void);
static NODE *func__10_41;
static void entry__10_41(void);
static FRAME_INFO frame__10_41 = {1, {"self"}};
static void cont__10_42(void);
static void cont__10_43(void);
static void cont__10_44(void);
static void cont__10_45(void);
static void cont__10_46(void);
static NODE *func__10_47;
static void entry__10_47(void);
static FRAME_INFO frame__10_47 = {1, {"self"}};
static void cont__10_48(void);
static void cont__10_49(void);
static void cont__10_50(void);
static void cont__10_51(void);
static void cont__10_52(void);
static NODE *func__10_53;
static void entry__10_53(void);
static FRAME_INFO frame__10_53 = {1, {"self"}};
static void cont__10_54(void);
static void cont__10_55(void);
static NODE *func__10_56;
static void entry__10_56(void);
static FRAME_INFO frame__10_56 = {2, {"self", "destination"}};
static void cont__10_57(void);
static void cont__10_58(void);
static void cont__10_59(void);
static NODE *func__10_60;
static void entry__10_60(void);
static FRAME_INFO frame__10_60 = {1, {"self"}};
static void cont__10_61(void);
static void cont__10_62(void);
static void cont__10_63(void);
static void cont__10_64(void);
static NODE *func__10_65;
static void entry__10_65(void);
static FRAME_INFO frame__10_65 = {2, {"self", "destination"}};
static void cont__10_66(void);
static void cont__10_67(void);
static void cont__10_68(void);
static void cont__10_69(void);
static void cont__10_70(void);
static void cont__10_71(void);
static void cont__10_72(void);
static void cont__10_73(void);
static void cont__10_74(void);
static void cont__10_75(void);
static NODE *func__11_1_sim2c__c_code_annotate_statement;
static void entry__11_1_sim2c__c_code_annotate_statement(void);
static FRAME_INFO frame__11_1_sim2c__c_code_annotate_statement = {1, {"self"}};
static NODE *string__11_2;
static void cont__11_3(void);
static void cont__11_4(void);
static NODE *string__11_5;
static NODE *string__11_6;
static void cont__11_7(void);
static NODE *func__11_8;
static void entry__11_8(void);
static FRAME_INFO frame__11_8 = {1, {"self"}};
static void cont__11_9(void);
static void cont__11_10(void);
static void cont__11_11(void);
static void cont__11_12(void);
static NODE *func__11_13;
static void entry__11_13(void);
static FRAME_INFO frame__11_13 = {1, {"self"}};
static void cont__11_14(void);
static void cont__11_15(void);
static void cont__11_16(void);
static NODE *func__12_1_sim2c__define_static_single_annotate_expression;
static void entry__12_1_sim2c__define_static_single_annotate_expression(void);
static FRAME_INFO frame__12_1_sim2c__define_static_single_annotate_expression = {1, {"self"}};
static NODE *string__12_2;
static void cont__12_3(void);
static void cont__12_4(void);
static void cont__12_5(void);
static NODE *func__12_6;
static void entry__12_6(void);
static FRAME_INFO frame__12_6 = {1, {"self"}};
static void cont__12_7(void);
static NODE *func__12_8;
static void entry__12_8(void);
static FRAME_INFO frame__12_8 = {1, {"self"}};
static void cont__12_9(void);
static void cont__12_10(void);
static NODE *func__12_11;
static void entry__12_11(void);
static FRAME_INFO frame__12_11 = {1, {"self"}};
static void cont__12_12(void);
static void cont__12_13(void);
static void cont__12_14(void);
static void cont__12_15(void);
static void cont__12_16(void);
static void cont__12_17(void);
static NODE *func__13_1_sim2c__define_static_multi_annotate_expression;
static void entry__13_1_sim2c__define_static_multi_annotate_expression(void);
static FRAME_INFO frame__13_1_sim2c__define_static_multi_annotate_expression = {1, {"self"}};
static NODE *string__13_2;
static void cont__13_3(void);
static void cont__13_4(void);
static NODE *func__14_1_sim2c__define_dynamic_single_annotate_expression;
static void entry__14_1_sim2c__define_dynamic_single_annotate_expression(void);
static FRAME_INFO frame__14_1_sim2c__define_dynamic_single_annotate_expression = {1, {"self"}};
static NODE *string__14_2;
static void cont__14_3(void);
static void cont__14_4(void);
static NODE *func__15_1_sim2c__define_dynamic_multi_annotate_expression;
static void entry__15_1_sim2c__define_dynamic_multi_annotate_expression(void);
static FRAME_INFO frame__15_1_sim2c__define_dynamic_multi_annotate_expression = {1, {"self"}};
static NODE *string__15_2;
static void cont__15_3(void);
static void cont__15_4(void);
static NODE *func__16_1_sim2c__function_call_annotate_expression;
static void entry__16_1_sim2c__function_call_annotate_expression(void);
static FRAME_INFO frame__16_1_sim2c__function_call_annotate_expression = {1, {"self"}};
static NODE *string__16_2;
static void cont__16_3(void);
static void cont__16_4(void);
static void cont__16_5(void);
static NODE *func__16_6;
static void entry__16_6(void);
static FRAME_INFO frame__16_6 = {1, {"self"}};
static void cont__16_7(void);
static void cont__16_8(void);
static void cont__16_9(void);
static void cont__16_10(void);
static void cont__16_11(void);
static void cont__16_12(void);
static void cont__16_13(void);
static NODE *func__17_1_sim2c__attribute_value_pair_annotate_expression;
static void entry__17_1_sim2c__attribute_value_pair_annotate_expression(void);
static FRAME_INFO frame__17_1_sim2c__attribute_value_pair_annotate_expression = {1, {"self"}};
static NODE *string__17_2;
static void cont__17_3(void);
static void cont__17_4(void);
static void cont__17_5(void);
static void cont__17_6(void);
static void cont__17_7(void);
static NODE *func__18_1_sim2c__attribute_function_pair_annotate_expression;
static void entry__18_1_sim2c__attribute_function_pair_annotate_expression(void);
static FRAME_INFO frame__18_1_sim2c__attribute_function_pair_annotate_expression = {1, {"self"}};
static NODE *string__18_2;
static void cont__18_3(void);
static void cont__18_4(void);
static void cont__18_5(void);
static NODE *func__18_6;
static void entry__18_6(void);
static FRAME_INFO frame__18_6 = {1, {"self"}};
static void cont__18_7(void);
static void cont__18_8(void);
static void cont__18_9(void);
static void cont__18_10(void);
static void cont__18_11(void);
static NODE *func__19_1_sim2c__identifier_annotate_expression;
static void entry__19_1_sim2c__identifier_annotate_expression(void);
static FRAME_INFO frame__19_1_sim2c__identifier_annotate_expression = {1, {"self"}};
static NODE *string__19_2;
static void cont__19_3(void);
static void cont__19_4(void);
static NODE *func__19_5;
static void entry__19_5(void);
static FRAME_INFO frame__19_5 = {4, {"self", "namespace", "name", "info"}};
static void cont__19_6(void);
static void cont__19_7(void);
static NODE *func__19_8;
static void entry__19_8(void);
static FRAME_INFO frame__19_8 = {3, {"namespace", "self", "mapped_namespace"}};
static void cont__19_9(void);
static void cont__19_10(void);
static NODE *func__19_11;
static void entry__19_11(void);
static FRAME_INFO frame__19_11 = {2, {"self", "mapped_namespace"}};
static void cont__19_12(void);
static void cont__19_13(void);
static void cont__19_14(void);
static NODE *func__19_15;
static void entry__19_15(void);
static FRAME_INFO frame__19_15 = {3, {"self", "info", "name"}};
static void cont__19_16(void);
static NODE *func__19_17;
static void entry__19_17(void);
static FRAME_INFO frame__19_17 = {3, {"info", "name", "self"}};
static void cont__19_18(void);
static NODE *func__19_19;
static void entry__19_19(void);
static FRAME_INFO frame__19_19 = {1, {"info"}};
static void cont__19_20(void);
static void cont__19_21(void);
static void cont__19_22(void);
static NODE *func__19_23;
static void entry__19_23(void);
static FRAME_INFO frame__19_23 = {2, {"name", "self"}};
static void cont__19_24(void);
static NODE *func__19_25;
static void entry__19_25(void);
static FRAME_INFO frame__19_25 = {3, {"info", "self", "name"}};
static void cont__19_26(void);
static void cont__19_27(void);
static NODE *func__19_28;
static void entry__19_28(void);
static FRAME_INFO frame__19_28 = {2, {"self", "name"}};
static NODE *string__19_29;
static NODE *string__19_30;
static void cont__19_31(void);
static NODE *func__19_32;
static void entry__19_32(void);
static FRAME_INFO frame__19_32 = {3, {"self", "info", "name"}};
static void cont__19_33(void);
static NODE *func__19_34;
static void entry__19_34(void);
static FRAME_INFO frame__19_34 = {3, {"info", "name", "self"}};
static void cont__19_35(void);
static NODE *func__19_36;
static void entry__19_36(void);
static FRAME_INFO frame__19_36 = {1, {"info"}};
static void cont__19_37(void);
static void cont__19_38(void);
static void cont__19_39(void);
static NODE *func__19_40;
static void entry__19_40(void);
static FRAME_INFO frame__19_40 = {2, {"name", "self"}};
static void cont__19_41(void);
static NODE *func__19_42;
static void entry__19_42(void);
static FRAME_INFO frame__19_42 = {3, {"info", "self", "name"}};
static void cont__19_43(void);
static void cont__19_44(void);
static NODE *func__19_45;
static void entry__19_45(void);
static FRAME_INFO frame__19_45 = {2, {"self", "name"}};
static void cont__19_46(void);
static NODE *func__19_47;
static void entry__19_47(void);
static FRAME_INFO frame__19_47 = {3, {"info", "name", "self"}};
static void cont__19_48(void);
static NODE *func__19_49;
static void entry__19_49(void);
static FRAME_INFO frame__19_49 = {2, {"name", "self"}};
static void cont__19_50(void);
static void cont__19_51(void);
void run__annotator(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__sim2c__annotate_statement, NULL, 33, 33, 2, 26},
  {type__sim2c__annotate_expression, NULL, 34, 34, 2, 27},
  {run__annotator, NULL, 31, 31, 1, 28},
  {entry__4_11, NULL, 45, 45, 28, 52},
  {cont__4_12, &frame__4_11, 45, 45, 15, 55},
  {cont__4_13, &frame__4_11, 45, 45, 55, 55},
  {entry__4_14, NULL, 47, 47, 15, 50},
  {cont__4_15, &frame__4_14, 47, 47, 50, 50},
  {entry__4_9, NULL, 44, 44, 13, 46},
  {cont__4_10, &frame__4_9, 43, 47, 11, 51},
  {entry__4_7, NULL, 42, 42, 18, 47},
  {cont__4_8, &frame__4_7, 42, 47, 15, 52},
  {entry__4_6, NULL, 42, 47, 9, 52},
  {cont__4_16, &frame__4_6, 48, 48, 9, 42},
  {cont__4_17, &frame__4_6, 49, 49, 9, 29},
  {cont__4_18, &frame__4_6, 49, 49, 34, 34},
  {entry__4_4, NULL, 41, 41, 14, 40},
  {cont__4_5, &frame__4_4, 41, 49, 7, 34},
  {entry__4_2, NULL, 38, 38, 5, 33},
  {cont__4_3, &frame__4_2, 39, 49, 5, 35},
  {cont__4_19, &frame__4_2, },
  {entry__4_1_annotate_output_arguments, NULL, 37, 49, 3, 36},
  {cont__4_20, &frame__4_1_annotate_output_arguments, 49, 49, 37, 37},
  {entry__5_2, NULL, 52, 52, 39, 67},
  {cont__5_3, &frame__5_2, 52, 52, 67, 67},
  {entry__5_1_annotate_arguments, NULL, 52, 52, 3, 67},
  {cont__5_4, &frame__5_1_annotate_arguments, 52, 52, 67, 67},
  {entry__6_1_types__grammar_node_annotate_statement, NULL, 58, 58, 3, 47},
  {cont__6_3, &frame__6_1_types__grammar_node_annotate_statement, },
  {entry__7_1_types__grammar_node_annotate_expression, NULL, 61, 61, 3, 48},
  {cont__7_3, &frame__7_1_types__grammar_node_annotate_expression, },
  {entry__8_11, NULL, 75, 76, 32, 63},
  {cont__8_14, &frame__8_11, 75, 76, 13, 63},
  {entry__8_9, NULL, 74, 74, 18, 39},
  {cont__8_10, &frame__8_9, 74, 76, 11, 64},
  {entry__8_21, NULL, 82, 82, 19, 38},
  {cont__8_22, &frame__8_21, 82, 82, 15, 39},
  {cont__8_23, &frame__8_21, 82, 82, 15, 39},
  {entry__8_17, NULL, 81, 81, 15, 37},
  {cont__8_18, &frame__8_17, 81, 81, 15, 57},
  {cont__8_19, &frame__8_17, 81, 81, 15, 57},
  {cont__8_20, &frame__8_17, 82, 82, 15, 39},
  {cont__8_24, &frame__8_17, },
  {entry__8_26, NULL, 84, 86, 34, 50},
  {cont__8_28, &frame__8_26, 84, 86, 15, 50},
  {entry__8_15, NULL, 80, 80, 15, 47},
  {cont__8_16, &frame__8_15, },
  {cont__8_25, &frame__8_15, 78, 86, 11, 52},
  {entry__8_6, NULL, 73, 73, 9, 24},
  {cont__8_7, &frame__8_6, 73, 73, 9, 37},
  {cont__8_8, &frame__8_6, 72, 86, 7, 54},
  {entry__8_2, NULL, 70, 70, 5, 35},
  {cont__8_3, &frame__8_2, 71, 71, 12, 35},
  {cont__8_4, &frame__8_2, 71, 71, 12, 46},
  {cont__8_5, &frame__8_2, 71, 86, 5, 55},
  {entry__8_34, NULL, 90, 90, 31, 57},
  {cont__8_35, &frame__8_34, 90, 90, 31, 69},
  {cont__8_36, &frame__8_34, 90, 90, 31, 69},
  {entry__8_38, NULL, 91, 91, 17, 35},
  {cont__8_39, &frame__8_38, 91, 93, 37, 15},
  {cont__8_42, &frame__8_38, 91, 93, 9, 15},
  {entry__8_33, NULL, 90, 90, 10, 69},
  {cont__8_37, &frame__8_33, 90, 93, 7, 16},
  {entry__8_30, NULL, 88, 88, 5, 37},
  {cont__8_31, &frame__8_30, 89, 89, 8, 30},
  {cont__8_32, &frame__8_30, 89, 93, 5, 17},
  {entry__8_1_sim2c__check_definitions, NULL, 69, 86, 3, 56},
  {cont__8_29, &frame__8_1_sim2c__check_definitions, 87, 93, 3, 18},
  {entry__9_9, NULL, 106, 106, 42, 68},
  {cont__9_10, &frame__9_9, 106, 106, 42, 79},
  {cont__9_11, &frame__9_9, 106, 106, 42, 79},
  {entry__9_13, NULL, 107, 107, 32, 57},
  {cont__9_14, &frame__9_13, 107, 107, 11, 57},
  {cont__9_15, &frame__9_13, 107, 107, 57, 57},
  {entry__9_6, NULL, 104, 104, 7, 35},
  {cont__9_7, &frame__9_6, 106, 106, 9, 37},
  {cont__9_8, &frame__9_6, 106, 106, 9, 79},
  {cont__9_12, &frame__9_6, 105, 107, 7, 58},
  {cont__9_16, &frame__9_6, },
  {entry__9_19, NULL, 108, 108, 46, 69},
  {cont__9_20, &frame__9_19, 108, 108, 69, 69},
  {entry__9_29, NULL, 117, 117, 56, 74},
  {cont__9_30, &frame__9_29, 116, 118, 31, 32},
  {cont__9_33, &frame__9_29, 116, 118, 13, 32},
  {entry__9_38, NULL, 121, 123, 31, 16},
  {cont__9_41, &frame__9_38, 121, 123, 13, 16},
  {entry__9_25, NULL, 114, 114, 11, 36},
  {cont__9_26, &frame__9_25, 115, 115, 14, 32},
  {cont__9_27, &frame__9_25, 115, 115, 14, 43},
  {cont__9_28, &frame__9_25, 115, 118, 11, 33},
  {cont__9_34, &frame__9_25, 119, 119, 11, 30},
  {cont__9_35, &frame__9_25, 120, 120, 14, 36},
  {cont__9_36, &frame__9_25, 120, 120, 14, 47},
  {cont__9_37, &frame__9_25, 120, 123, 11, 17},
  {cont__9_42, &frame__9_25, 124, 124, 11, 34},
  {cont__9_43, &frame__9_25, 124, 124, 39, 39},
  {entry__9_45, NULL, 126, 126, 39, 57},
  {cont__9_46, &frame__9_45, 126, 126, 23, 58},
  {cont__9_47, &frame__9_45, 126, 126, 11, 59},
  {cont__9_48, &frame__9_45, 126, 126, 64, 64},
  {entry__9_22, NULL, 112, 112, 9, 30},
  {cont__9_23, &frame__9_22, 113, 113, 9, 35},
  {cont__9_24, &frame__9_22, 125, 125, 9, 37},
  {cont__9_44, &frame__9_22, 111, 126, 7, 65},
  {entry__9_53, NULL, 135, 135, 41, 41},
  {cont__9_54, &frame__9_53, 135, 135, 29, 42},
  {cont__9_55, &frame__9_53, 135, 135, 11, 43},
  {cont__9_56, &frame__9_53, 135, 135, 11, 69},
  {cont__9_57, &frame__9_53, 135, 135, 11, 69},
  {cont__9_58, &frame__9_53, 135, 135, 11, 69},
  {entry__9_60, NULL, 137, 137, 39, 56},
  {cont__9_62, &frame__9_60, 138, 138, 11, 20},
  {cont__9_63, &frame__9_60, 140, 140, 14, 31},
  {cont__9_64, &frame__9_60, 139, 143, 11, 56},
  {cont__9_65, &frame__9_60, 143, 143, 57, 57},
  {entry__9_50, NULL, 131, 131, 7, 37},
  {cont__9_51, &frame__9_50, 134, 134, 11, 29},
  {cont__9_52, &frame__9_50, 133, 135, 9, 68},
  {cont__9_59, &frame__9_50, 132, 143, 7, 58},
  {entry__9_67, NULL, 145, 145, 7, 52},
  {cont__9_68, &frame__9_67, 146, 146, 44, 44},
  {entry__9_4, NULL, 103, 103, 18, 35},
  {cont__9_5, &frame__9_4, 103, 107, 5, 59},
  {cont__9_17, &frame__9_4, 108, 108, 18, 35},
  {cont__9_18, &frame__9_4, 108, 108, 5, 69},
  {cont__9_21, &frame__9_4, 110, 126, 5, 66},
  {cont__9_49, &frame__9_4, 129, 143, 5, 59},
  {cont__9_66, &frame__9_4, 144, 146, 5, 44},
  {cont__9_69, &frame__9_4, 146, 146, 44, 44},
  {entry__9_80, NULL, 150, 150, 35, 51},
  {cont__9_81, &frame__9_80, 150, 150, 64, 64},
  {entry__9_76, NULL, 149, 149, 38, 53},
  {cont__9_77, &frame__9_76, 149, 149, 7, 59},
  {cont__9_78, &frame__9_76, 150, 150, 10, 32},
  {cont__9_79, &frame__9_76, 150, 150, 7, 64},
  {entry__9_72, NULL, 148, 148, 12, 33},
  {cont__9_73, &frame__9_72, 148, 148, 12, 39},
  {cont__9_74, &frame__9_72, 148, 148, 12, 50},
  {cont__9_75, &frame__9_72, 148, 150, 5, 64},
  {entry__9_84, NULL, 152, 152, 45, 65},
  {cont__9_85, &frame__9_84, 152, 152, 70, 70},
  {entry__9_83, NULL, 152, 152, 5, 70},
  {entry__9_1_sim2c__body_annotate_expression, NULL, 96, 96, 3, 42},
  {cont__9_3, &frame__9_1_sim2c__body_annotate_expression, 98, 146, 3, 45},
  {cont__9_70, &frame__9_1_sim2c__body_annotate_expression, 147, 147, 12, 30},
  {cont__9_71, &frame__9_1_sim2c__body_annotate_expression, 147, 150, 3, 65},
  {cont__9_82, &frame__9_1_sim2c__body_annotate_expression, 151, 152, 3, 70},
  {cont__9_86, &frame__9_1_sim2c__body_annotate_expression, },
  {entry__10_8, NULL, 162, 162, 42, 59},
  {cont__10_9, &frame__10_8, 162, 162, 42, 62},
  {cont__10_10, &frame__10_8, 162, 162, 42, 74},
  {cont__10_11, &frame__10_8, 162, 162, 42, 74},
  {entry__10_13, NULL, 163, 163, 7, 31},
  {cont__10_14, &frame__10_13, 163, 163, 7, 34},
  {cont__10_15, &frame__10_13, 163, 163, 7, 64},
  {cont__10_16, &frame__10_13, 163, 163, 7, 64},
  {entry__10_4, NULL, 162, 162, 7, 24},
  {cont__10_5, &frame__10_4, 162, 162, 7, 27},
  {cont__10_6, &frame__10_4, 162, 162, 7, 37},
  {cont__10_7, &frame__10_4, 162, 162, 7, 74},
  {cont__10_12, &frame__10_4, 163, 163, 7, 64},
  {cont__10_17, &frame__10_4, },
  {entry__10_19, NULL, 167, 167, 17, 41},
  {cont__10_20, &frame__10_19, 167, 167, 17, 44},
  {cont__10_21, &frame__10_19, 167, 167, 17, 54},
  {cont__10_22, &frame__10_19, 167, 167, 59, 59},
  {cont__10_23, &frame__10_19, 167, 167, 11, 60},
  {cont__10_24, &frame__10_19, 168, 168, 11, 21},
  {cont__10_27, &frame__10_19, 169, 169, 11, 19},
  {cont__10_29, &frame__10_19, 170, 170, 11, 19},
  {cont__10_30, &frame__10_19, 165, 170, 7, 20},
  {cont__10_31, &frame__10_19, 165, 165, 8, 24},
  {cont__10_32, &frame__10_19, 165, 165, 8, 27},
  {cont__10_33, &frame__10_19, 165, 165, 7, 27},
  {cont__10_34, &frame__10_19, 170, 170, 21, 21},
  {entry__10_41, NULL, 174, 174, 30, 49},
  {cont__10_42, &frame__10_41, 174, 174, 9, 49},
  {cont__10_43, &frame__10_41, 174, 174, 49, 49},
  {entry__10_47, NULL, 176, 176, 30, 49},
  {cont__10_48, &frame__10_47, 176, 176, 9, 49},
  {cont__10_49, &frame__10_47, 176, 176, 49, 49},
  {entry__10_38, NULL, 173, 173, 10, 30},
  {cont__10_39, &frame__10_38, 173, 173, 10, 41},
  {cont__10_40, &frame__10_38, 173, 174, 7, 49},
  {cont__10_44, &frame__10_38, 175, 175, 10, 30},
  {cont__10_45, &frame__10_38, 175, 175, 10, 41},
  {cont__10_46, &frame__10_38, 175, 176, 7, 49},
  {cont__10_50, &frame__10_38, 177, 177, 28, 42},
  {cont__10_51, &frame__10_38, 177, 177, 7, 42},
  {cont__10_52, &frame__10_38, 177, 177, 42, 42},
  {entry__10_60, NULL, 184, 184, 13, 30},
  {cont__10_61, &frame__10_60, 184, 184, 13, 33},
  {cont__10_62, &frame__10_60, 184, 184, 13, 59},
  {cont__10_63, &frame__10_60, 184, 184, 13, 59},
  {entry__10_65, NULL, 187, 187, 31, 56},
  {cont__10_66, &frame__10_65, 186, 187, 13, 57},
  {cont__10_67, &frame__10_65, 186, 186, 14, 30},
  {cont__10_68, &frame__10_65, 186, 186, 14, 33},
  {cont__10_69, &frame__10_65, 186, 186, 13, 33},
  {cont__10_70, &frame__10_65, 187, 187, 58, 58},
  {entry__10_56, NULL, 180, 180, 22, 46},
  {cont__10_57, &frame__10_56, 180, 180, 9, 49},
  {cont__10_58, &frame__10_56, 183, 183, 13, 39},
  {cont__10_59, &frame__10_56, 182, 184, 11, 58},
  {cont__10_64, &frame__10_56, 181, 187, 9, 59},
  {entry__10_53, NULL, 179, 179, 14, 38},
  {cont__10_54, &frame__10_53, 179, 179, 14, 47},
  {cont__10_55, &frame__10_53, 179, 187, 7, 60},
  {entry__10_1_sim2c__call_annotate_statement, NULL, 158, 158, 3, 47},
  {cont__10_2, &frame__10_1_sim2c__call_annotate_statement, 161, 161, 7, 27},
  {cont__10_3, &frame__10_1_sim2c__call_annotate_statement, },
  {cont__10_18, &frame__10_1_sim2c__call_annotate_statement, 159, 170, 3, 22},
  {cont__10_35, &frame__10_1_sim2c__call_annotate_statement, 172, 172, 5, 20},
  {cont__10_36, &frame__10_1_sim2c__call_annotate_statement, 172, 172, 5, 31},
  {cont__10_37, &frame__10_1_sim2c__call_annotate_statement, 171, 187, 3, 62},
  {cont__10_71, &frame__10_1_sim2c__call_annotate_statement, 188, 188, 30, 53},
  {cont__10_72, &frame__10_1_sim2c__call_annotate_statement, 188, 188, 3, 53},
  {cont__10_73, &frame__10_1_sim2c__call_annotate_statement, 189, 189, 23, 39},
  {cont__10_74, &frame__10_1_sim2c__call_annotate_statement, 189, 189, 3, 39},
  {cont__10_75, &frame__10_1_sim2c__call_annotate_statement, 189, 189, 39, 39},
  {entry__11_8, NULL, 197, 199, 5, 79},
  {cont__11_9, &frame__11_8, 199, 199, 80, 80},
  {entry__11_13, NULL, 200, 200, 53, 64},
  {cont__11_14, &frame__11_13, 200, 200, 32, 64},
  {cont__11_15, &frame__11_13, 200, 200, 64, 64},
  {entry__11_1_sim2c__c_code_annotate_statement, NULL, 195, 195, 3, 44},
  {cont__11_3, &frame__11_1_sim2c__c_code_annotate_statement, 196, 196, 8, 20},
  {cont__11_4, &frame__11_1_sim2c__c_code_annotate_statement, 196, 196, 22, 37},
  {cont__11_7, &frame__11_1_sim2c__c_code_annotate_statement, 196, 199, 3, 80},
  {cont__11_10, &frame__11_1_sim2c__c_code_annotate_statement, 200, 200, 6, 18},
  {cont__11_11, &frame__11_1_sim2c__c_code_annotate_statement, 200, 200, 6, 29},
  {cont__11_12, &frame__11_1_sim2c__c_code_annotate_statement, 200, 200, 3, 64},
  {cont__11_16, &frame__11_1_sim2c__c_code_annotate_statement, },
  {entry__12_6, NULL, 209, 209, 7, 30},
  {cont__12_7, &frame__12_6, 209, 209, 30, 30},
  {entry__12_11, NULL, 211, 211, 62, 78},
  {cont__12_12, &frame__12_11, 211, 211, 41, 78},
  {cont__12_13, &frame__12_11, 211, 211, 78, 78},
  {entry__12_8, NULL, 211, 211, 10, 27},
  {cont__12_9, &frame__12_8, 211, 211, 10, 38},
  {cont__12_10, &frame__12_8, 211, 211, 7, 78},
  {cont__12_14, &frame__12_8, 212, 212, 28, 45},
  {cont__12_15, &frame__12_8, 212, 212, 7, 45},
  {cont__12_16, &frame__12_8, 212, 212, 45, 45},
  {entry__12_1_sim2c__define_static_single_annotate_expression, NULL, 206, 206, 3, 58},
  {cont__12_3, &frame__12_1_sim2c__define_static_single_annotate_expression, 208, 208, 5, 27},
  {cont__12_4, &frame__12_1_sim2c__define_static_single_annotate_expression, 208, 208, 5, 35},
  {cont__12_5, &frame__12_1_sim2c__define_static_single_annotate_expression, 207, 212, 3, 46},
  {cont__12_17, &frame__12_1_sim2c__define_static_single_annotate_expression, },
  {entry__13_1_sim2c__define_static_multi_annotate_expression, NULL, 218, 218, 3, 57},
  {cont__13_3, &frame__13_1_sim2c__define_static_multi_annotate_expression, 219, 219, 3, 26},
  {cont__13_4, &frame__13_1_sim2c__define_static_multi_annotate_expression, 219, 219, 26, 26},
  {entry__14_1_sim2c__define_dynamic_single_annotate_expression, NULL, 225, 225, 3, 59},
  {cont__14_3, &frame__14_1_sim2c__define_dynamic_single_annotate_expression, 227, 227, 3, 26},
  {cont__14_4, &frame__14_1_sim2c__define_dynamic_single_annotate_expression, 227, 227, 26, 26},
  {entry__15_1_sim2c__define_dynamic_multi_annotate_expression, NULL, 233, 233, 3, 58},
  {cont__15_3, &frame__15_1_sim2c__define_dynamic_multi_annotate_expression, 235, 235, 3, 26},
  {cont__15_4, &frame__15_1_sim2c__define_dynamic_multi_annotate_expression, 235, 235, 26, 26},
  {entry__16_6, NULL, 243, 243, 26, 40},
  {cont__16_7, &frame__16_6, 243, 243, 5, 40},
  {cont__16_8, &frame__16_6, 244, 244, 32, 55},
  {cont__16_9, &frame__16_6, 244, 244, 5, 55},
  {cont__16_10, &frame__16_6, 245, 245, 25, 41},
  {cont__16_11, &frame__16_6, 245, 245, 5, 41},
  {cont__16_12, &frame__16_6, 245, 245, 41, 41},
  {entry__16_1_sim2c__function_call_annotate_expression, NULL, 241, 241, 3, 51},
  {cont__16_3, &frame__16_1_sim2c__function_call_annotate_expression, 242, 242, 6, 21},
  {cont__16_4, &frame__16_1_sim2c__function_call_annotate_expression, 242, 242, 6, 32},
  {cont__16_5, &frame__16_1_sim2c__function_call_annotate_expression, 242, 245, 3, 41},
  {cont__16_13, &frame__16_1_sim2c__function_call_annotate_expression, },
  {entry__17_1_sim2c__attribute_value_pair_annotate_expression, NULL, 251, 251, 3, 58},
  {cont__17_3, &frame__17_1_sim2c__attribute_value_pair_annotate_expression, 252, 252, 24, 41},
  {cont__17_4, &frame__17_1_sim2c__attribute_value_pair_annotate_expression, 252, 252, 3, 41},
  {cont__17_5, &frame__17_1_sim2c__attribute_value_pair_annotate_expression, 253, 253, 23, 39},
  {cont__17_6, &frame__17_1_sim2c__attribute_value_pair_annotate_expression, 253, 253, 3, 39},
  {cont__17_7, &frame__17_1_sim2c__attribute_value_pair_annotate_expression, 253, 253, 39, 39},
  {entry__18_6, NULL, 260, 260, 59, 76},
  {cont__18_7, &frame__18_6, 260, 260, 38, 76},
  {cont__18_8, &frame__18_6, 260, 260, 76, 76},
  {entry__18_1_sim2c__attribute_function_pair_annotate_expression, NULL, 259, 259, 3, 61},
  {cont__18_3, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 260, 260, 6, 24},
  {cont__18_4, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 260, 260, 6, 35},
  {cont__18_5, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 260, 260, 3, 76},
  {cont__18_9, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 261, 261, 23, 39},
  {cont__18_10, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 261, 261, 3, 39},
  {cont__18_11, &frame__18_1_sim2c__attribute_function_pair_annotate_expression, 261, 261, 39, 39},
  {entry__19_11, NULL, 272, 272, 73, 73},
  {entry__19_8, NULL, 271, 271, 7, 53},
  {cont__19_9, &frame__19_8, 272, 272, 10, 36},
  {cont__19_10, &frame__19_8, 272, 272, 7, 73},
  {entry__19_19, NULL, 278, 278, 32, 53},
  {cont__19_20, &frame__19_19, 278, 278, 32, 70},
  {cont__19_21, &frame__19_19, 278, 278, 32, 70},
  {entry__19_23, NULL, 279, 279, 13, 29},
  {cont__19_24, &frame__19_23, 282, 282, 48, 48},
  {entry__19_28, NULL, 285, 286, 32, 62},
  {cont__19_31, &frame__19_28, 285, 286, 15, 62},
  {entry__19_25, NULL, 284, 284, 16, 37},
  {cont__19_26, &frame__19_25, 284, 284, 16, 52},
  {cont__19_27, &frame__19_25, 284, 286, 13, 63},
  {entry__19_17, NULL, 278, 278, 11, 27},
  {cont__19_18, &frame__19_17, 278, 278, 11, 70},
  {cont__19_22, &frame__19_17, 277, 286, 9, 65},
  {entry__19_15, NULL, 276, 276, 10, 30},
  {cont__19_16, &frame__19_15, 276, 286, 7, 66},
  {entry__19_36, NULL, 289, 289, 32, 53},
  {cont__19_37, &frame__19_36, 289, 289, 32, 70},
  {cont__19_38, &frame__19_36, 289, 289, 32, 70},
  {entry__19_40, NULL, 290, 290, 13, 29},
  {cont__19_41, &frame__19_40, 293, 293, 47, 47},
  {entry__19_45, NULL, 296, 297, 32, 62},
  {cont__19_46, &frame__19_45, 296, 297, 15, 62},
  {entry__19_42, NULL, 295, 295, 20, 41},
  {cont__19_43, &frame__19_42, 295, 295, 20, 56},
  {cont__19_44, &frame__19_42, 295, 297, 13, 63},
  {entry__19_34, NULL, 289, 289, 11, 27},
  {cont__19_35, &frame__19_34, 289, 289, 11, 70},
  {cont__19_39, &frame__19_34, 288, 297, 9, 65},
  {entry__19_32, NULL, 287, 287, 10, 47},
  {cont__19_33, &frame__19_32, 287, 297, 7, 66},
  {entry__19_49, NULL, 300, 300, 11, 27},
  {cont__19_50, &frame__19_49, 303, 303, 47, 47},
  {entry__19_47, NULL, 299, 299, 12, 28},
  {cont__19_48, &frame__19_47, 299, 303, 9, 47},
  {entry__19_5, NULL, 269, 269, 5, 33},
  {cont__19_6, &frame__19_5, 270, 270, 8, 27},
  {cont__19_7, &frame__19_5, 270, 272, 5, 73},
  {cont__19_12, &frame__19_5, 273, 273, 5, 31},
  {cont__19_13, &frame__19_5, 274, 274, 5, 26},
  {cont__19_14, &frame__19_5, 275, 303, 5, 49},
  {entry__19_1_sim2c__identifier_annotate_expression, NULL, 267, 267, 3, 54},
  {cont__19_3, &frame__19_1_sim2c__identifier_annotate_expression, 268, 268, 10, 35},
  {cont__19_4, &frame__19_1_sim2c__identifier_annotate_expression, 268, 303, 3, 50},
  {cont__19_51, &frame__19_1_sim2c__identifier_annotate_expression, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__sim2c__annotate_statement(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__annotate_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__annotate_statement, attr);
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
static void type__sim2c__annotate_expression(void) {
  myself = get_attribute(arguments->slots[0], poly_idx__sim2c__annotate_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__sim2c__annotate_expression, attr);
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
static NODE *character__47;
static NODE *number__1;
static NODE *character__46;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  "sim2c",
  "node",
  NULL
};

static MODULE_INFO module_info = {
  NULL,
  "annotator",
  continuation_info,
  sizeof(continuation_info)/sizeof(CONTINUATION_INFO),
  (NODE **)&var,
  var_names,
  sizeof(var_names)/sizeof(const char *),
  used_namespaces,
  {DEBUG_FILENAME("annotator.sim")}
};

/******
C O D E
******/

static int already_run = false;

EXPORT void run__annotator(void) {
  if (already_run) {
    func = frame->cont;
    frame->cont = invalid_continuation;
    return;
  }
  already_run = true;
  allocate_initialized_frame_gc(0, 0);
  // 31: %%defines_dynamics undefined
  set__defines_dynamics(get__undefined());
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_1_annotate_output_arguments(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* arguments */ = create_cell_with_contents(arguments->slots[0]);
  // 37: update_each &arguments: (&argument)
  // 38:   annotate_expression &argument
  // 39:   if do_print_warnings:
  // 40:     $$destination argument
  // 41:     unless destination.is_a_definition:
  // 42:       while -> destination.is_a_function_call:
  // 43:         if
  // 44:           destination.is_an_attribute_access:
  // 45:             !destination arguments_of(destination)(1)
  // 46:           :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = func__4_2;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__4_20;
}
static void entry__4_2(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 38: annotate_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__4_3;
}
static void cont__4_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 39: ... :
  // 40:   $$destination argument
  // 41:   unless destination.is_a_definition:
  // 42:     while -> destination.is_a_function_call:
  // 43:       if
  // 44:         destination.is_an_attribute_access:
  // 45:           !destination arguments_of(destination)(1)
  // 46:         :
  // 47:           !destination functor_of(destination)
  // 48:     $name mangled_name_of(destination)
  // ...
  frame->slots[1] /* temp__1 */ = create_closure(entry__4_4, 0);
  // 39: if do_print_warnings:
  // 40:   $$destination argument
  // 41:   unless destination.is_a_definition:
  // 42:     while -> destination.is_a_function_call:
  // 43:       if
  // 44:         destination.is_an_attribute_access:
  // 45:           !destination arguments_of(destination)(1)
  // 46:         :
  // 47:           !destination functor_of(destination)
  // 48:     $name mangled_name_of(destination)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__4_19;
}
static void entry__4_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // destination: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 42: ... -> destination.is_a_function_call:
  // 43:   if
  // 44:     destination.is_an_attribute_access:
  // 45:       !destination arguments_of(destination)(1)
  // 46:     :
  // 47:       !destination functor_of(destination)
  frame->slots[2] /* temp__1 */ = create_closure(entry__4_7, 0);
  // 42: while -> destination.is_a_function_call:
  // 43:   if
  // 44:     destination.is_an_attribute_access:
  // 45:       !destination arguments_of(destination)(1)
  // 46:     :
  // 47:       !destination functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__4_16;
}
static void entry__4_11(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: ... arguments_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__4_12;
}
static void cont__4_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 45: !destination arguments_of(destination)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__4_13;
}
static void cont__4_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* destination */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_14(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 47: !destination functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__4_15;
}
static void cont__4_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* destination */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_9(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 44: destination.is_an_attribute_access
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__is_an_attribute_access();
  func = myself->type;
  frame->cont = cont__4_10;
}
static void cont__4_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 44: ... :
  // 45:   !destination arguments_of(destination)(1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__4_11, 0);
  // 46: :
  // 47:   !destination functor_of(destination)
  frame->slots[3] /* temp__3 */ = create_closure(entry__4_14, 0);
  // 43: if
  // 44:   destination.is_an_attribute_access:
  // 45:     !destination arguments_of(destination)(1)
  // 46:   :
  // 47:     !destination functor_of(destination)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__4_7(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 42: ... destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__4_8;
}
static void cont__4_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 42: ... :
  // 43:   if
  // 44:     destination.is_an_attribute_access:
  // 45:       !destination arguments_of(destination)(1)
  // 46:     :
  // 47:       !destination functor_of(destination)
  frame->slots[2] /* temp__2 */ = create_closure(entry__4_9, 0);
  // 42: ... -> destination.is_a_function_call:
  // 43:   if
  // 44:     destination.is_an_attribute_access:
  // 45:       !destination arguments_of(destination)(1)
  // 46:     :
  // 47:       !destination functor_of(destination)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__4_16(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 48: $name mangled_name_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__4_17;
}
static void cont__4_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 49: !assigned_names(name) true
  frame->slots[2] /* temp__1 */ = get__true();
  // 49: !assigned_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__4_18;
}
static void cont__4_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__assigned_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__4_4(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* argument */
  frame->slots[1] /* destination */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 40: $$destination argument
  ((CELL *)frame->slots[1])->contents /* destination */ = ((CELL *)frame->slots[0])->contents /* argument */;
  // 41: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__4_5;
}
static void cont__4_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 41: ... :
  // 42:   while -> destination.is_a_function_call:
  // 43:     if
  // 44:       destination.is_an_attribute_access:
  // 45:         !destination arguments_of(destination)(1)
  // 46:       :
  // 47:         !destination functor_of(destination)
  // 48:   $name mangled_name_of(destination)
  // 49:   !assigned_names(name) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__4_6, 0);
  // 41: unless destination.is_a_definition:
  // 42:   while -> destination.is_a_function_call:
  // 43:     if
  // 44:       destination.is_an_attribute_access:
  // 45:         !destination arguments_of(destination)(1)
  // 46:       :
  // 47:         !destination functor_of(destination)
  // 48:   $name mangled_name_of(destination)
  // 49:   !assigned_names(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__4_19(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__4_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__5_1_annotate_arguments(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* arguments */ = create_cell_with_contents(arguments->slots[0]);
  // 52: update_each &arguments: (&argument) annotate_expression &argument
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = func__5_2;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__5_4;
}
static void entry__5_2(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 52: ... annotate_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__5_3;
}
static void cont__5_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__5_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* arguments */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__6_1_types__grammar_node_annotate_statement(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 58: show_compiler_debug_info "annotate statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6_2;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__6_3;
}
static void cont__6_3(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__7_1_types__grammar_node_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 61: show_compiler_debug_info "annotate expression"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__7_2;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__7_3;
}
static void cont__7_3(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__8_38(void) {
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
  // 91: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__8_39;
}
static void cont__8_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 91: ... "
  // 92:   attempt to use the identifier "@(name)" that is marked as not being @
  // 93:   used@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8_40;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__8_41;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_42;
}
static void cont__8_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 91: Warning identifier_of(info) "
  // 92:   attempt to use the identifier "@(name)" that is marked as not being @
  // 93:   used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_33(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // defined_name: 0
  // info: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* defined_name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] = myself->closure.frame->slots[0]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... identifier_of(defined_name).is_not_used
  frame->slots[4] /* temp__2 */ = create_closure(entry__8_34, 0);
  // 90: ... do_print_warnings && identifier_of(defined_name).is_not_used
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__8_37;
}
static void entry__8_34(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // defined_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* defined_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 90: ... identifier_of(defined_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defined_name */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__8_35;
}
static void cont__8_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 90: ... identifier_of(defined_name).is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__8_36;
}
static void cont__8_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 90: ... identifier_of(defined_name).is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 90: ... :
  // 91:   Warning identifier_of(info) "
  // 92:     attempt to use the identifier "@(name)" that is marked as not being @
  // 93:     used@
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_38, 0);
  // 90: if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 91:   Warning identifier_of(info) "
  // 92:     attempt to use the identifier "@(name)" that is marked as not being @
  // 93:     used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_30(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // name: 0
  // info: 1
  // defined_names: 2
  // defined_name: 3
  frame->slots[2] = myself->closure.frame->slots[0]; /* defined_names */
  frame->slots[3] /* defined_name */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 88: $defined_name defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* defined_names */;
  func = myself->type;
  frame->cont = cont__8_31;
}
static void cont__8_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* defined_name */, arguments->slots[0]);
  // 89: ... defined_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* defined_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_32;
}
static void cont__8_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 89: ... :
  // 90:   if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 91:     Warning identifier_of(info) "
  // 92:       attempt to use the identifier "@(name)" that is marked as not being @
  // 93:       used@
  frame->slots[5] /* temp__2 */ = create_closure(entry__8_33, 0);
  // 89: if defined_name.is_defined:
  // 90:   if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 91:     Warning identifier_of(info) "
  // 92:       attempt to use the identifier "@(name)" that is marked as not being @
  // 93:       used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_1_sim2c__check_definitions(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defined_names: 0
  // used_names: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 69: ... : (name info)
  // 70:   $identifier identifier_of(info)
  // 71:   unless namespace_of(identifier).is_defined:
  // 72:     if
  // 73:       used_names(name).is_undefined:
  // 74:         unless identifier.is_not_used:
  // 75:           Warning identifier "
  // 76:             the identifier "@(name)" is defined but not used@
  // 77:       :
  // 78:         if
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__8_2, 2);
  // 69: for_each defined_names: (name info)
  // 70:   $identifier identifier_of(info)
  // 71:   unless namespace_of(identifier).is_defined:
  // 72:     if
  // 73:       used_names(name).is_undefined:
  // 74:         unless identifier.is_not_used:
  // 75:           Warning identifier "
  // 76:             the identifier "@(name)" is defined but not used@
  // 77:       :
  // 78:         if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defined_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__8_29;
}
static void entry__8_26(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // identifier: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 84: ... "
  // 85:   the identifier "@(name)" is defined as a read-write variable, @
  // 86:   but there is no actual assignment@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8_12;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__8_27;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_28;
}
static void cont__8_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 84: Warning identifier "
  // 85:   the identifier "@(name)" is defined as a read-write variable, @
  // 86:   but there is no actual assignment@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_11(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // identifier: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 75: ... "
  // 76:   the identifier "@(name)" is defined but not used@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__8_12;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__8_13;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__8_14;
}
static void cont__8_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 75: Warning identifier "
  // 76:   the identifier "@(name)" is defined but not used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_9(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // identifier: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* identifier */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 74: ... identifier.is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__8_10;
}
static void cont__8_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 74: ... :
  // 75:   Warning identifier "
  // 76:     the identifier "@(name)" is defined but not used@
  frame->slots[3] /* temp__2 */ = create_closure(entry__8_11, 0);
  // 74: unless identifier.is_not_used:
  // 75:   Warning identifier "
  // 76:     the identifier "@(name)" is defined but not used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_15(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // info: 0
  // name: 1
  // identifier: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  frame->slots[2] = myself->closure.frame->slots[2]; /* identifier */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 80: info.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_a_multi_assign_definition();
  func = myself->type;
  frame->cont = cont__8_16;
}
static void cont__8_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__8_17, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__8_25;
}
static void entry__8_17(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // info: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 81: parameter_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__8_18;
}
static void cont__8_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 81: parameter_kind_of(info) != IN_OUT_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = get__IN_OUT_PARAMETER();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__8_19;
}
static void cont__8_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 81: parameter_kind_of(info) != IN_OUT_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__8_20;
}
static void cont__8_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 82: not(assigned_names(name))
  frame->slots[6] /* temp__5 */ = create_closure(entry__8_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__8_24;
}
static void entry__8_21(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 82: ... assigned_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__8_22;
}
static void cont__8_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 82: not(assigned_names(name))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__8_23;
}
static void cont__8_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 82: not(assigned_names(name))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__8_24(void) {
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
static void cont__8_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 83: :
  // 84:   Warning identifier "
  // 85:     the identifier "@(name)" is defined as a read-write variable, @
  // 86:     but there is no actual assignment@
  frame->slots[6] /* temp__4 */ = create_closure(entry__8_26, 0);
  // 78: if
  // 79:   &&
  // 80:     info.is_a_multi_assign_definition
  // 81:     parameter_kind_of(info) != IN_OUT_PARAMETER
  // 82:     not(assigned_names(name))
  // 83:   :
  // 84:     Warning identifier "
  // 85:       the identifier "@(name)" is defined as a read-write variable, @
  // 86:       but there is no actual assignment@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_6(void) {
  allocate_initialized_frame_gc(4, 8);
  // slot allocations:
  // used_names: 0
  // name: 1
  // identifier: 2
  // info: 3
  frame->slots[0] = myself->closure.frame->slots[2]; /* used_names */
  frame->slots[1] = myself->closure.frame->slots[0]; /* name */
  frame->slots[2] = myself->closure.frame->slots[3]; /* identifier */
  frame->slots[3] = myself->closure.frame->slots[1]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 73: used_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = frame->slots[0] /* used_names */;
  func = myself->type;
  frame->cont = cont__8_7;
}
static void cont__8_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 73: used_names(name).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__8_8;
}
static void cont__8_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 73: ... :
  // 74:   unless identifier.is_not_used:
  // 75:     Warning identifier "
  // 76:       the identifier "@(name)" is defined but not used@
  frame->slots[6] /* temp__3 */ = create_closure(entry__8_9, 0);
  // 77: :
  // 78:   if
  // 79:     &&
  // 80:       info.is_a_multi_assign_definition
  // 81:       parameter_kind_of(info) != IN_OUT_PARAMETER
  // 82:       not(assigned_names(name))
  // 83:     :
  // 84:       Warning identifier "
  // 85:         the identifier "@(name)" is defined as a read-write variable, @
  // 86:         but there is no actual assignment@
  frame->slots[7] /* temp__4 */ = create_closure(entry__8_15, 0);
  // 72: if
  // 73:   used_names(name).is_undefined:
  // 74:     unless identifier.is_not_used:
  // 75:       Warning identifier "
  // 76:         the identifier "@(name)" is defined but not used@
  // 77:   :
  // 78:     if
  // 79:       &&
  // 80:         info.is_a_multi_assign_definition
  // 81:         parameter_kind_of(info) != IN_OUT_PARAMETER
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  arguments->slots[2] = frame->slots[7] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__8_2(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // used_names: 2
  // identifier: 3
  frame->slots[2] = myself->closure.frame->slots[1]; /* used_names */
  frame->slots[3] /* identifier */ = create_future();
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 70: $identifier identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__8_3;
}
static void cont__8_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 71: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__8_4;
}
static void cont__8_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 71: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__8_5;
}
static void cont__8_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 71: ... :
  // 72:   if
  // 73:     used_names(name).is_undefined:
  // 74:       unless identifier.is_not_used:
  // 75:         Warning identifier "
  // 76:           the identifier "@(name)" is defined but not used@
  // 77:     :
  // 78:       if
  // 79:         &&
  // 80:           info.is_a_multi_assign_definition
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__8_6, 0);
  // 71: unless namespace_of(identifier).is_defined:
  // 72:   if
  // 73:     used_names(name).is_undefined:
  // 74:       unless identifier.is_not_used:
  // 75:         Warning identifier "
  // 76:           the identifier "@(name)" is defined but not used@
  // 77:     :
  // 78:       if
  // 79:         &&
  // 80:           info.is_a_multi_assign_definition
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__8_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 87: ... : (name info)
  // 88:   $defined_name defined_names(name)
  // 89:   if defined_name.is_defined:
  // 90:     if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 91:       Warning identifier_of(info) "
  // 92:         attempt to use the identifier "@(name)" that is marked as not being @
  // 93:         used@
  frame->slots[2] /* temp__1 */ = create_closure(entry__8_30, 2);
  // 87: for_each used_names: (name info)
  // 88:   $defined_name defined_names(name)
  // 89:   if defined_name.is_defined:
  // 90:     if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 91:       Warning identifier_of(info) "
  // 92:         attempt to use the identifier "@(name)" that is marked as not being @
  // 93:         used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_1_sim2c__body_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  // locally_assigned_names: 1
  frame->slots[1] /* locally_assigned_names */ = create_cell();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 96: show_compiler_debug_info "annotate body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__9_3;
}
static void cont__9_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 97: $$locally_assigned_names undefined
  ((CELL *)frame->slots[1])->contents /* locally_assigned_names */ = get__undefined();
  //  98: ... :
  //  99:   %%sim2c::defined_names empty_list
  // 100:   %%sim2c::used_names empty_insert_order_table
  // 101:   %%sim2c::assigned_names empty_set
  // 102:   %%defines_dynamics false
  // 103:   update_each &self.parameters_of: (&parameter)
  // 104:     push &defined_names parameter
  // 105:     if
  // 106:       parameter.is_an_optional_item && default_value_of(parameter).is_defined:
  // 107:         annotate_expression &parameter.default_value_of
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__9_4, 0);
  //  98: do:
  //  99:   %%sim2c::defined_names empty_list
  // 100:   %%sim2c::used_names empty_insert_order_table
  // 101:   %%sim2c::assigned_names empty_set
  // 102:   %%defines_dynamics false
  // 103:   update_each &self.parameters_of: (&parameter)
  // 104:     push &defined_names parameter
  // 105:     if
  // 106:       parameter.is_an_optional_item && default_value_of(parameter).is_defined:
  // 107:         annotate_expression &parameter.default_value_of
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__9_70;
}
static void entry__9_4(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // return__1: 0
  // self: 1
  // locally_assigned_names: 2
  // local_definitions: 3
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* locally_assigned_names */
  define__sim2c__defined_names(undefined);
  define__sim2c__used_names(undefined);
  define__sim2c__assigned_names(undefined);
  define__defines_dynamics(undefined);
  frame->slots[3] /* local_definitions */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 99: %%sim2c::defined_names empty_list
  set__sim2c__defined_names(get__empty_list());
  // 100: %%sim2c::used_names empty_insert_order_table
  set__sim2c__used_names(get__empty_insert_order_table());
  // 101: %%sim2c::assigned_names empty_set
  set__sim2c__assigned_names(get__empty_set());
  // 102: %%defines_dynamics false
  set__defines_dynamics(get__false());
  // 103: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__9_5;
}
static void cont__9_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 103: update_each &self.parameters_of: (&parameter)
  // 104:   push &defined_names parameter
  // 105:   if
  // 106:     parameter.is_an_optional_item && default_value_of(parameter).is_defined:
  // 107:       annotate_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__9_6;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__9_17;
}
static void entry__9_6(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // parameter: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* parameter */ = create_cell_with_contents(arguments->slots[0]);
  // 104: push &defined_names parameter
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_7;
}
static void cont__9_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  // 106: parameter.is_an_optional_item
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__is_an_optional_item();
  func = myself->type;
  frame->cont = cont__9_8;
}
static void cont__9_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 106: ... default_value_of(parameter).is_defined
  frame->slots[3] /* temp__3 */ = create_closure(entry__9_9, 0);
  // 106: parameter.is_an_optional_item && default_value_of(parameter).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__9_12;
}
static void entry__9_9(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 106: ... default_value_of(parameter)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__9_10;
}
static void cont__9_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 106: ... default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_11;
}
static void cont__9_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 106: ... default_value_of(parameter).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 106: ... :
  // 107:   annotate_expression &parameter.default_value_of
  frame->slots[4] /* temp__4 */ = create_closure(entry__9_13, 0);
  // 105: if
  // 106:   parameter.is_an_optional_item && default_value_of(parameter).is_defined:
  // 107:     annotate_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_16;
}
static void entry__9_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 107: ... parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__9_14;
}
static void cont__9_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 107: annotate_expression &parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__9_15;
}
static void cont__9_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 107: ... &parameter.default_value_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* parameter */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__default_value_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* parameter */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_16(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_17(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 103: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 108: ... self.statements_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__9_18;
}
static void cont__9_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 108: update_each &self.statements_of: (&stmt) annotate_statement &stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = func__9_19;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__9_21;
}
static void entry__9_19(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* stmt */ = create_cell_with_contents(arguments->slots[0]);
  // 108: ... annotate_statement &stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* stmt */;
  result_count = 1;
  myself = get__annotate_statement();
  func = myself->type;
  frame->cont = cont__9_20;
}
static void cont__9_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* stmt */ = arguments->slots[0];
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* stmt */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 108: ... &self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[5] /* temp__2 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 109: $$local_definitions empty_insert_order_table
  ((CELL *)frame->slots[3])->contents /* local_definitions */ = get__empty_insert_order_table();
  // 110: ... : (info)
  // 111:   case
  // 112:     variable_kind_of(info)
  // 113:     STATIC_SINGLE, STATIC_MULTI:
  // 114:       $ident identifier_of(info)
  // 115:       if namespace_of(ident).is_defined:
  // 116:         SyntaxError ident "
  // 117:           attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:           in an inner scope@
  // 119:       $name name_of(ident)
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__9_22, 1);
  // 110: for_each defined_names: (info)
  // 111:   case
  // 112:     variable_kind_of(info)
  // 113:     STATIC_SINGLE, STATIC_MULTI:
  // 114:       $ident identifier_of(info)
  // 115:       if namespace_of(ident).is_defined:
  // 116:         SyntaxError ident "
  // 117:           attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:           in an inner scope@
  // 119:       $name name_of(ident)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__9_49;
}
static void entry__9_45(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: !used_names(mangled_name_of(identifier_of(info))) info
  frame->slots[1] /* temp__1 */ = frame->slots[0] /* info */;
  // 126: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__9_46;
}
static void cont__9_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 126: ... mangled_name_of(identifier_of(info))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__9_47;
}
static void cont__9_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 126: !used_names(mangled_name_of(identifier_of(info)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__9_48;
}
static void cont__9_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_22(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // info: 0
  // local_definitions: 1
  frame->slots[1] = myself->closure.frame->slots[3]; /* local_definitions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 112: variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__9_23;
}
static void cont__9_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 113: STATIC_SINGLE, STATIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__STATIC_SINGLE();
  arguments->slots[1] = get__STATIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__9_24;
}
static void cont__9_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 113: ... :
  // 114:   $ident identifier_of(info)
  // 115:   if namespace_of(ident).is_defined:
  // 116:     SyntaxError ident "
  // 117:       attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:       in an inner scope@
  // 119:   $name name_of(ident)
  // 120:   if local_definitions(name).is_defined:
  // 121:     SyntaxError ident "
  // 122:       Attempt to define a variable twice within a single scope (@(name)@
  // ...
  frame->slots[4] /* temp__3 */ = create_closure(entry__9_25, 0);
  // 125: DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__9_44;
}
static void entry__9_25(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // info: 0
  // local_definitions: 1
  // ident: 2
  // name: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[1]; /* local_definitions */
  frame->slots[2] /* ident */ = create_future();
  frame->slots[3] /* name */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 114: $ident identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__9_26;
}
static void cont__9_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* ident */, arguments->slots[0]);
  // 115: ... namespace_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ident */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__9_27;
}
static void cont__9_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 115: ... namespace_of(ident).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_28;
}
static void cont__9_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 115: ... :
  // 116:   SyntaxError ident "
  // 117:     attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:     in an inner scope@
  frame->slots[6] /* temp__3 */ = create_closure(entry__9_29, 0);
  // 115: if namespace_of(ident).is_defined:
  // 116:   SyntaxError ident "
  // 117:     attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:     in an inner scope@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_34;
}
static void entry__9_29(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // ident: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* ident */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 117: ... full_name_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  result_count = 1;
  myself = get__full_name_of();
  func = myself->type;
  frame->cont = cont__9_30;
}
static void cont__9_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 116: ... "
  // 117:   attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:   in an inner scope@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9_31;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__9_32;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__9_33;
}
static void cont__9_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 116: SyntaxError ident "
  // 117:   attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:   in an inner scope@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_34(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 119: $name name_of(ident)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* ident */;
  result_count = 1;
  myself = get__name_of();
  func = myself->type;
  frame->cont = cont__9_35;
}
static void cont__9_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* name */, arguments->slots[0]);
  // 120: ... local_definitions(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* name */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_definitions */;
  func = myself->type;
  frame->cont = cont__9_36;
}
static void cont__9_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 120: ... local_definitions(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_37;
}
static void cont__9_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 120: ... :
  // 121:   SyntaxError ident "
  // 122:     Attempt to define a variable twice within a single scope (@(name)@
  // 123:     )@
  frame->slots[6] /* temp__3 */ = create_closure(entry__9_38, 0);
  // 120: if local_definitions(name).is_defined:
  // 121:   SyntaxError ident "
  // 122:     Attempt to define a variable twice within a single scope (@(name)@
  // 123:     )@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_42;
}
static void entry__9_38(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // ident: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* ident */
  frame->slots[1] = myself->closure.frame->slots[3]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 121: ... "
  // 122:   Attempt to define a variable twice within a single scope (@(name)@
  // 123:   )@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__9_39;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__9_40;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__9_41;
}
static void cont__9_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 121: SyntaxError ident "
  // 122:   Attempt to define a variable twice within a single scope (@(name)@
  // 123:   )@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* ident */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_42(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 124: !local_definitions(name) info
  frame->slots[4] /* temp__1 */ = frame->slots[0] /* info */;
  // 124: !local_definitions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* name */;
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_definitions */;
  func = myself->type;
  frame->cont = cont__9_43;
}
static void cont__9_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[1])->contents /* local_definitions */ = arguments->slots[0];
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 125: ... :
  // 126:   !used_names(mangled_name_of(identifier_of(info))) info
  frame->slots[6] /* temp__5 */ = create_closure(entry__9_45, 0);
  // 111: case
  // 112:   variable_kind_of(info)
  // 113:   STATIC_SINGLE, STATIC_MULTI:
  // 114:     $ident identifier_of(info)
  // 115:     if namespace_of(ident).is_defined:
  // 116:       SyntaxError ident "
  // 117:         attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:         in an inner scope@
  // 119:     $name name_of(ident)
  // 120:     if local_definitions(name).is_defined:
  // ...
  argument_count = 5;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  arguments->slots[2] = frame->slots[4] /* temp__3 */;
  arguments->slots[3] = frame->slots[5] /* temp__4 */;
  arguments->slots[4] = frame->slots[6] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__case();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_49(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 127: !self.defined_names_of local_definitions
  frame->slots[4] /* temp__1 */ = ((CELL *)frame->slots[3])->contents /* local_definitions */;
  // 127: !self.defined_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defined_names_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 128: !self.used_names_of used_names
  frame->slots[4] /* temp__1 */ = get__used_names();
  // 128: !self.used_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_names_of, frame->slots[4] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  // 129: ... : # then add a continuation parameter if not present
  // 130:   !self.defines_a_dynamic true
  // 131:   $parameters parameters_of(self)
  // 132:   if
  // 133:     ||
  // 134:       parameters.is_empty
  // 135:       parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  // 136:     :
  // 137:       $return identifier(.name_of "return__@(index)")
  // 138:       inc &index
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__9_50, 0);
  // 129: if defines_dynamics: # then add a continuation parameter if not present
  // 130:   !self.defines_a_dynamic true
  // 131:   $parameters parameters_of(self)
  // 132:   if
  // 133:     ||
  // 134:       parameters.is_empty
  // 135:       parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  // 136:     :
  // 137:       $return identifier(.name_of "return__@(index)")
  // 138:       inc &index
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defines_dynamics();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_66;
}
static void entry__9_60(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // return: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* return */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 137: ... "return__@(index)"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__9_61;
  arguments->slots[1] = get__index();
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__9_62;
}
static void cont__9_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 137: $return identifier(.name_of "return__@(index)")
  {
    NODE *temp = clone_object_and_attributes(get__identifier());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[2] /* temp__1 */);
    initialize_future(frame->slots[1] /* return */, temp);

  }
  // 138: inc &index
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__index();
  result_count = 1;
  myself = get__inc();
  func = myself->type;
  frame->cont = cont__9_63;
}
static void cont__9_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__index(arguments->slots[0]);
  // 140: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__9_64;
}
static void cont__9_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 141: define_static_single
  // 142:   .identifier_of return
  // 143:   .parameter_kind_of CONTINUATION_PARAMETER
  {
    NODE *temp = clone_object_and_attributes(get__define_static_single());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[1] /* return */);
    set_attribute_value(temp->attributes, poly_idx__parameter_kind_of, get__CONTINUATION_PARAMETER());
    frame->slots[3] /* temp__2 */ = temp;

  }
  // 139: push
  // 140:   &self.parameters_of
  // 141:   define_static_single
  // 142:     .identifier_of return
  // 143:     .parameter_kind_of CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__9_65;
}
static void cont__9_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 140: &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_50(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // parameters: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] /* parameters */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: !self.defines_a_dynamic true
  frame->slots[2] /* temp__1 */ = get__true();
  // 130: !self.defines_a_dynamic
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defines_a_dynamic, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 131: $parameters parameters_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__9_51;
}
static void cont__9_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* parameters */, arguments->slots[0]);
  // 134: parameters.is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* parameters */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__9_52;
}
static void cont__9_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  frame->slots[4] /* temp__3 */ = create_closure(entry__9_53, 0);
  // 133: ||
  // 134:   parameters.is_empty
  // 135:   parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__9_59;
}
static void entry__9_53(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // parameters: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* parameters */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 135: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__9_54;
}
static void cont__9_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 135: ... parameters(-1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = frame->slots[0] /* parameters */;
  func = myself->type;
  frame->cont = cont__9_55;
}
static void cont__9_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__9_56;
}
static void cont__9_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = get__CONTINUATION_PARAMETER();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__9_57;
}
static void cont__9_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__9_58;
}
static void cont__9_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 136: :
  // 137:   $return identifier(.name_of "return__@(index)")
  // 138:   inc &index
  // 139:   push
  // 140:     &self.parameters_of
  // 141:     define_static_single
  // 142:       .identifier_of return
  // 143:       .parameter_kind_of CONTINUATION_PARAMETER
  frame->slots[5] /* temp__4 */ = create_closure(entry__9_60, 0);
  // 132: if
  // 133:   ||
  // 134:     parameters.is_empty
  // 135:     parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  // 136:   :
  // 137:     $return identifier(.name_of "return__@(index)")
  // 138:     inc &index
  // 139:     push
  // 140:       &self.parameters_of
  // 141:       define_static_single
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_66(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: ... :
  // 145:   check_definitions local_definitions used_names
  // 146:   !locally_assigned_names assigned_names
  frame->slots[4] /* temp__1 */ = create_closure(entry__9_67, 0);
  // 144: if do_print_warnings:
  // 145:   check_definitions local_definitions used_names
  // 146:   !locally_assigned_names assigned_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[4] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_69;
}
static void entry__9_67(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // local_definitions: 0
  // locally_assigned_names: 1
  frame->slots[0] = myself->closure.frame->slots[3]; /* local_definitions */
  frame->slots[1] = myself->closure.frame->slots[2]; /* locally_assigned_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 145: check_definitions local_definitions used_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* local_definitions */;
  arguments->slots[1] = get__used_names();
  result_count = 0;
  myself = get__check_definitions();
  func = myself->type;
  frame->cont = cont__9_68;
}
static void cont__9_68(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 146: !locally_assigned_names assigned_names
  ((CELL *)frame->slots[1])->contents /* locally_assigned_names */ = get__assigned_names();
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__9_69(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__9_70(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 147: ... used_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__used_names_of();
  func = myself->type;
  frame->cont = cont__9_71;
}
static void cont__9_71(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 147: ... : (name info)
  // 148:   unless defined_names_of(self)(name).is_defined:
  // 149:     $updated_info update_info(name used_names(name) info)
  // 150:     if updated_info.is_defined: !used_names(name) updated_info
  frame->slots[3] /* temp__2 */ = create_closure(entry__9_72, 2);
  // 147: for_each used_names_of(self): (name info)
  // 148:   unless defined_names_of(self)(name).is_defined:
  // 149:     $updated_info update_info(name used_names(name) info)
  // 150:     if updated_info.is_defined: !used_names(name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__9_82;
}
static void entry__9_80(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // updated_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* updated_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... !used_names(name) updated_info
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* updated_info */;
  // 150: ... !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__9_81;
}
static void cont__9_81(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_76(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // name: 0
  // info: 1
  // updated_info: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[1]; /* info */
  frame->slots[2] /* updated_info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 149: ... used_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__9_77;
}
static void cont__9_77(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 149: $updated_info update_info(name used_names(name) info)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  arguments->slots[2] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__update_info();
  func = myself->type;
  frame->cont = cont__9_78;
}
static void cont__9_78(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* updated_info */, arguments->slots[0]);
  // 150: ... updated_info.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* updated_info */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_79;
}
static void cont__9_79(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 150: ... : !used_names(name) updated_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__9_80, 0);
  // 150: if updated_info.is_defined: !used_names(name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__9_72(void) {
  allocate_initialized_frame_gc(3, 7);
  // slot allocations:
  // name: 0
  // info: 1
  // self: 2
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 148: ... defined_names_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__defined_names_of();
  func = myself->type;
  frame->cont = cont__9_73;
}
static void cont__9_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 148: ... defined_names_of(self)(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[5] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__9_74;
}
static void cont__9_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 148: ... defined_names_of(self)(name).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__9_75;
}
static void cont__9_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 148: ... :
  // 149:   $updated_info update_info(name used_names(name) info)
  // 150:   if updated_info.is_defined: !used_names(name) updated_info
  frame->slots[6] /* temp__4 */ = create_closure(entry__9_76, 0);
  // 148: unless defined_names_of(self)(name).is_defined:
  // 149:   $updated_info update_info(name used_names(name) info)
  // 150:   if updated_info.is_defined: !used_names(name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_82(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 151: ... :
  // 152:   for_each locally_assigned_names: (name) !assigned_names(name) true
  frame->slots[2] /* temp__1 */ = create_closure(entry__9_83, 0);
  // 151: if do_print_warnings:
  // 152:   for_each locally_assigned_names: (name) !assigned_names(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__9_86;
}
static void entry__9_84(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 152: ... !assigned_names(name) true
  frame->slots[1] /* temp__1 */ = get__true();
  // 152: ... !assigned_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__9_85;
}
static void cont__9_85(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__assigned_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__9_83(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // locally_assigned_names: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* locally_assigned_names */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 152: for_each locally_assigned_names: (name) !assigned_names(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* locally_assigned_names */;
  arguments->slots[1] = func__9_84;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__9_86(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_1_sim2c__call_annotate_statement(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 158: show_compiler_debug_info "annotate statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__6_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__10_2;
}
static void cont__10_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 161: self.is_an_assignment
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_assignment();
  func = myself->type;
  frame->cont = cont__10_3;
}
static void cont__10_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  frame->slots[3] /* temp__3 */ = create_closure(entry__10_4, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_18;
}
static void entry__10_4(void) {
  allocate_initialized_frame_gc(1, 8);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_5;
}
static void cont__10_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 162: arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[5] /* temp__5 */;
  func = myself->type;
  frame->cont = cont__10_6;
}
static void cont__10_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 162: arguments_of(self)(1).is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__10_7;
}
static void cont__10_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 162: ... arguments_of(self)(1).is_a_c_body
  frame->slots[6] /* temp__6 */ = create_closure(entry__10_8, 0);
  // 162: arguments_of(self)(1).is_a_body || arguments_of(self)(1).is_a_c_body
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__10_12;
}
static void entry__10_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_9;
}
static void cont__10_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 162: ... arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_10;
}
static void cont__10_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 162: ... arguments_of(self)(1).is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__10_11;
}
static void cont__10_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 162: ... arguments_of(self)(1).is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: output_arguments_of(self)(1).is_a_single_assign_definition
  frame->slots[7] /* temp__7 */ = create_closure(entry__10_13, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[7] /* temp__7 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_17;
}
static void entry__10_13(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 163: output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_14;
}
static void cont__10_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 163: output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_15;
}
static void cont__10_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: output_arguments_of(self)(1).is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_single_assign_definition();
  func = myself->type;
  frame->cont = cont__10_16;
}
static void cont__10_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: output_arguments_of(self)(1).is_a_single_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_17(void) {
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
static void cont__10_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 164: :
  // 165:   !self.arguments_of(1).name_of
  // 166:     replace_all
  // 167:       range(output_arguments_of(self)(1).to_string 2 -1)
  // 168:       "::" = "__"
  // 169:       '/' = "_"
  // 170:       '.' = "_"
  frame->slots[4] /* temp__4 */ = create_closure(entry__10_19, 0);
  // 159: if
  // 160:   &&
  // 161:     self.is_an_assignment
  // 162:     arguments_of(self)(1).is_a_body || arguments_of(self)(1).is_a_c_body
  // 163:     output_arguments_of(self)(1).is_a_single_assign_definition
  // 164:   :
  // 165:     !self.arguments_of(1).name_of
  // 166:       replace_all
  // 167:         range(output_arguments_of(self)(1).to_string 2 -1)
  // 168:         "::" = "__"
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_35;
}
static void entry__10_19(void) {
  allocate_initialized_frame_gc(1, 12);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_20;
}
static void cont__10_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__4 */ = arguments->slots[0];
  // 167: ... output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__4 */;
  func = myself->type;
  frame->cont = cont__10_21;
}
static void cont__10_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 167: ... output_arguments_of(self)(1).to_string
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__to_string();
  func = myself->type;
  frame->cont = cont__10_22;
}
static void cont__10_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 167: ... 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = get__std__negate();
  func = myself->type;
  frame->cont = cont__10_23;
}
static void cont__10_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__5 */ = arguments->slots[0];
  // 167: range(output_arguments_of(self)(1).to_string 2 -1)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = number__2;
  arguments->slots[2] = frame->slots[5] /* temp__5 */;
  result_count = 1;
  myself = get__range();
  func = myself->type;
  frame->cont = cont__10_24;
}
static void cont__10_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 168: "::" = "__"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__10_25;
  arguments->slots[1] = string__10_26;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_27;
}
static void cont__10_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__6 */ = arguments->slots[0];
  // 169: '/' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__47;
  arguments->slots[1] = string__10_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_29;
}
static void cont__10_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[7] /* temp__7 */ = arguments->slots[0];
  // 170: '.' = "_"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = character__46;
  arguments->slots[1] = string__10_28;
  result_count = 1;
  myself = get__std__key_value_pair();
  func = myself->type;
  frame->cont = cont__10_30;
}
static void cont__10_30(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[8] /* temp__8 */ = arguments->slots[0];
  // 165: !self.arguments_of(1).name_of
  // 166:   replace_all
  // 167:     range(output_arguments_of(self)(1).to_string 2 -1)
  // 168:     "::" = "__"
  // 169:     '/' = "_"
  // 170:     '.' = "_"
  argument_count = 4;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__6 */;
  arguments->slots[2] = frame->slots[7] /* temp__7 */;
  arguments->slots[3] = frame->slots[8] /* temp__8 */;
  result_count = 1;
  myself = get__replace_all();
  func = myself->type;
  frame->cont = cont__10_31;
}
static void cont__10_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[9] /* temp__9 */ = arguments->slots[0];
  // 165: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_32;
}
static void cont__10_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__10 */ = arguments->slots[0];
  // 165: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[10] /* temp__10 */;
  func = myself->type;
  frame->cont = cont__10_33;
}
static void cont__10_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[11] /* temp__11 */ = arguments->slots[0];
  // 165: !self.arguments_of(1).name_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[11] /* temp__11 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[9] /* temp__9 */);
    frame->slots[11] /* temp__11 */ = temp;

  }
  // 165: !self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[11] /* temp__11 */;
  result_count = 1;
  myself = frame->slots[10] /* temp__10 */;
  func = myself->type;
  frame->cont = cont__10_34;
}
static void cont__10_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[10] /* temp__10 */ = arguments->slots[0];
  // 165: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[10] /* temp__10 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_35(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 172: functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__10_36;
}
static void cont__10_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 172: functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_37;
}
static void cont__10_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 172: ... :
  // 173:   if result_count_of(self).is_defined:
  // 174:     annotate_expression &self.result_count_of
  // 175:   if continuation_of(self).is_defined:
  // 176:     annotate_expression &self.continuation_of
  // 177:   annotate_expression &self.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__10_38, 0);
  // 178: :
  // 179:   unless output_arguments_of(self).is_empty:
  // 180:     $destination output_arguments_of(self)(1)
  // 181:     if
  // 182:       &&
  // 183:         destination.is_a_definition
  // 184:         arguments_of(self)(1).is_a_unique_item_constant
  // 185:       :
  // 186:         !self.arguments_of(1).name_of
  // 187:           mangled_name_of(identifier_of(destination))
  frame->slots[4] /* temp__4 */ = create_closure(entry__10_53, 0);
  // 171: if
  // 172:   functor_of(self).is_defined:
  // 173:     if result_count_of(self).is_defined:
  // 174:       annotate_expression &self.result_count_of
  // 175:     if continuation_of(self).is_defined:
  // 176:       annotate_expression &self.continuation_of
  // 177:     annotate_expression &self.functor_of
  // 178:   :
  // 179:     unless output_arguments_of(self).is_empty:
  // 180:       $destination output_arguments_of(self)(1)
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_71;
}
static void entry__10_65(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // self: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 187: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__10_66;
}
static void cont__10_66(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 186: !self.arguments_of(1).name_of
  // 187:   mangled_name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__10_67;
}
static void cont__10_67(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 186: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_68;
}
static void cont__10_68(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 186: ... self.arguments_of(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_69;
}
static void cont__10_69(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 186: !self.arguments_of(1).name_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[5] /* temp__4 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, frame->slots[3] /* temp__2 */);
    frame->slots[5] /* temp__4 */ = temp;

  }
  // 186: !self.arguments_of(1)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__1;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = 1;
  myself = frame->slots[4] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_70;
}
static void cont__10_70(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 186: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[4] /* temp__3 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_56(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 180: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_57;
}
static void cont__10_57(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 180: $destination output_arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__10_58;
}
static void cont__10_58(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* destination */, arguments->slots[0]);
  // 183: destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__10_59;
}
static void cont__10_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 184: arguments_of(self)(1).is_a_unique_item_constant
  frame->slots[4] /* temp__3 */ = create_closure(entry__10_60, 0);
  // 182: &&
  // 183:   destination.is_a_definition
  // 184:   arguments_of(self)(1).is_a_unique_item_constant
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__10_64;
}
static void entry__10_60(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 184: arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_61;
}
static void cont__10_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 184: arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[3] /* temp__3 */;
  func = myself->type;
  frame->cont = cont__10_62;
}
static void cont__10_62(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 184: arguments_of(self)(1).is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__10_63;
}
static void cont__10_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 184: arguments_of(self)(1).is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 185: :
  // 186:   !self.arguments_of(1).name_of
  // 187:     mangled_name_of(identifier_of(destination))
  frame->slots[5] /* temp__4 */ = create_closure(entry__10_65, 0);
  // 181: if
  // 182:   &&
  // 183:     destination.is_a_definition
  // 184:     arguments_of(self)(1).is_a_unique_item_constant
  // 185:   :
  // 186:     !self.arguments_of(1).name_of
  // 187:       mangled_name_of(identifier_of(destination))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__10_38(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__10_39;
}
static void cont__10_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 173: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_40;
}
static void cont__10_40(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 173: ... :
  // 174:   annotate_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__10_41, 0);
  // 173: if result_count_of(self).is_defined:
  // 174:   annotate_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_44;
}
static void entry__10_41(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__10_42;
}
static void cont__10_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: annotate_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__10_43;
}
static void cont__10_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: ... &self.result_count_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__result_count_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_44(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 175: ... continuation_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__10_45;
}
static void cont__10_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 175: ... continuation_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__10_46;
}
static void cont__10_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 175: ... :
  // 176:   annotate_expression &self.continuation_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__10_47, 0);
  // 175: if continuation_of(self).is_defined:
  // 176:   annotate_expression &self.continuation_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__10_50;
}
static void entry__10_47(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__10_48;
}
static void cont__10_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 176: annotate_expression &self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__10_49;
}
static void cont__10_49(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 176: ... &self.continuation_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__continuation_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__10_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 177: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__10_51;
}
static void cont__10_51(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 177: annotate_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__10_52;
}
static void cont__10_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 177: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__10_53(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 179: ... output_arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_54;
}
static void cont__10_54(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 179: ... output_arguments_of(self).is_empty
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_empty();
  func = myself->type;
  frame->cont = cont__10_55;
}
static void cont__10_55(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 179: ... :
  // 180:   $destination output_arguments_of(self)(1)
  // 181:   if
  // 182:     &&
  // 183:       destination.is_a_definition
  // 184:       arguments_of(self)(1).is_a_unique_item_constant
  // 185:     :
  // 186:       !self.arguments_of(1).name_of
  // 187:         mangled_name_of(identifier_of(destination))
  frame->slots[3] /* temp__3 */ = create_closure(entry__10_56, 0);
  // 179: unless output_arguments_of(self).is_empty:
  // 180:   $destination output_arguments_of(self)(1)
  // 181:   if
  // 182:     &&
  // 183:       destination.is_a_definition
  // 184:       arguments_of(self)(1).is_a_unique_item_constant
  // 185:     :
  // 186:       !self.arguments_of(1).name_of
  // 187:         mangled_name_of(identifier_of(destination))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__10_71(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 188: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__10_72;
}
static void cont__10_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 188: annotate_output_arguments &self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_output_arguments;
  func = myself->type;
  frame->cont = cont__10_73;
}
static void cont__10_73(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 188: ... &self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 189: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__10_74;
}
static void cont__10_74(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 189: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_arguments;
  func = myself->type;
  frame->cont = cont__10_75;
}
static void cont__10_75(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 189: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__11_1_sim2c__c_code_annotate_statement(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 195: show_compiler_debug_info "annotate C-code"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__11_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__11_3;
}
static void cont__11_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 196: ... kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__11_4;
}
static void cont__11_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 196: ... "type", "object"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__11_5;
  arguments->slots[1] = string__11_6;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__11_7;
}
static void cont__11_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 196: ... :
  // 197:   push
  // 198:     &defined_names
  // 199:     self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  frame->slots[3] /* temp__3 */ = create_closure(entry__11_8, 0);
  // 196: case kind_of(self) "type", "object":
  // 197:   push
  // 198:     &defined_names
  // 199:     self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__11_10;
}
static void entry__11_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 199: self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    set_attribute_value(temp->attributes, poly_idx__is_a_single_assign_definition, get__true());
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 197: push
  // 198:   &defined_names
  // 199:   self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__11_9;
}
static void cont__11_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 200: ... base_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__11_11;
}
static void cont__11_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 200: ... base_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__11_12;
}
static void cont__11_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 200: ... : annotate_expression &self.base_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__11_13, 0);
  // 200: if base_of(self).is_defined: annotate_expression &self.base_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__11_16;
}
static void entry__11_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 200: ... self.base_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__11_14;
}
static void cont__11_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 200: ... annotate_expression &self.base_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__11_15;
}
static void cont__11_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 200: ... &self.base_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__base_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__11_16(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_1_sim2c__define_static_single_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 206: show_compiler_debug_info "annotate define static single"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__12_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__12_3;
}
static void cont__12_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 208: attribute_kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__12_4;
}
static void cont__12_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 208: attribute_kind_of(self) == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__12_5;
}
static void cont__12_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 208: ... :
  // 209:   push &defined_names self
  frame->slots[3] /* temp__3 */ = create_closure(entry__12_6, 0);
  // 210: :
  // 211:   if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  // 212:   annotate_expression &self.identifier_of
  frame->slots[4] /* temp__4 */ = create_closure(entry__12_8, 0);
  // 207: if
  // 208:   attribute_kind_of(self) == NONE:
  // 209:     push &defined_names self
  // 210:   :
  // 211:     if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  // 212:     annotate_expression &self.identifier_of
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_17;
}
static void entry__12_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 209: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__12_7;
}
static void cont__12_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__12_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: ... attribute_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__12_9;
}
static void cont__12_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 211: ... attribute_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__12_10;
}
static void cont__12_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: ... : annotate_expression &self.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__12_11, 0);
  // 211: if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__12_14;
}
static void entry__12_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 211: ... self.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__12_12;
}
static void cont__12_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 211: ... annotate_expression &self.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__12_13;
}
static void cont__12_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 211: ... &self.attribute_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__attribute_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__12_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 212: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__12_15;
}
static void cont__12_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 212: annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__12_16;
}
static void cont__12_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 212: ... &self.identifier_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__12_17(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__13_1_sim2c__define_static_multi_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 218: show_compiler_debug_info "annotate define static multi"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__13_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__13_3;
}
static void cont__13_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 219: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__13_4;
}
static void cont__13_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__14_1_sim2c__define_dynamic_single_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 225: show_compiler_debug_info "annotate define dynamic single"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__14_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__14_3;
}
static void cont__14_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 226: !defines_dynamics true
  set__defines_dynamics(get__true());
  // 227: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__14_4;
}
static void cont__14_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__15_1_sim2c__define_dynamic_multi_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 233: show_compiler_debug_info "annotate define dynamic multi"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__15_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__15_3;
}
static void cont__15_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 234: !defines_dynamics true
  set__defines_dynamics(get__true());
  // 235: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__15_4;
}
static void cont__15_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__defined_names(arguments->slots[0]);
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__16_1_sim2c__function_call_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 241: show_compiler_debug_info "annotate function call"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__16_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__16_3;
}
static void cont__16_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 242: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__16_4;
}
static void cont__16_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 242: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__16_5;
}
static void cont__16_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 242: ... :
  // 243:   annotate_expression &self.functor_of
  // 244:   annotate_output_arguments &self.output_arguments_of
  // 245:   annotate_arguments &self.arguments_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__16_6, 0);
  // 242: if functor_of(self).is_defined:
  // 243:   annotate_expression &self.functor_of
  // 244:   annotate_output_arguments &self.output_arguments_of
  // 245:   annotate_arguments &self.arguments_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__16_13;
}
static void entry__16_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 243: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__16_7;
}
static void cont__16_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 243: annotate_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__16_8;
}
static void cont__16_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 243: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 244: ... self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__output_arguments_of();
  func = myself->type;
  frame->cont = cont__16_9;
}
static void cont__16_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 244: annotate_output_arguments &self.output_arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_output_arguments;
  func = myself->type;
  frame->cont = cont__16_10;
}
static void cont__16_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 244: ... &self.output_arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__output_arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 245: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__16_11;
}
static void cont__16_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 245: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_arguments;
  func = myself->type;
  frame->cont = cont__16_12;
}
static void cont__16_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 245: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__16_13(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__17_1_sim2c__attribute_value_pair_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 251: show_compiler_debug_info "annotate attribute-value pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__17_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__17_3;
}
static void cont__17_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 252: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__17_4;
}
static void cont__17_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 252: annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__17_5;
}
static void cont__17_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 252: ... &self.identifier_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 253: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__17_6;
}
static void cont__17_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 253: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_arguments;
  func = myself->type;
  frame->cont = cont__17_7;
}
static void cont__17_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 253: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__18_1_sim2c__attribute_function_pair_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 259: show_compiler_debug_info "annotate attribute-function pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__18_2;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__18_3;
}
static void cont__18_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 260: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_4;
}
static void cont__18_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 260: ... identifier_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__18_5;
}
static void cont__18_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 260: ... : annotate_expression &self.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__18_6, 0);
  // 260: if identifier_of(self).is_defined: annotate_expression &self.identifier_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__18_9;
}
static void entry__18_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 260: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__18_7;
}
static void cont__18_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 260: ... annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__18_8;
}
static void cont__18_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 260: ... &self.identifier_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__18_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 261: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__18_10;
}
static void cont__18_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 261: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = var._annotate_arguments;
  func = myself->type;
  frame->cont = cont__18_11;
}
static void cont__18_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 261: ... &self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_1_sim2c__identifier_annotate_expression(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 267: show_compiler_debug_info "annotate identifier " self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__19_2;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__19_3;
}
static void cont__19_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 268: ... self.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__19_4;
}
static void cont__19_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 268: ... :
  // 269:   $namespace namespace_of(self)
  // 270:   if namespace.is_defined:
  // 271:     $mapped_namespace namespace_mappings(namespace)
  // 272:     if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  // 273:   $name mangled_name_of(self)
  // 274:   $info used_names(name)
  // 275:   cond
  // 276:     -> self.is_a_destination:
  // 277:       if
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__19_5, 0);
  // 268: unless self.is_an_operator_symbol:
  // 269:   $namespace namespace_of(self)
  // 270:   if namespace.is_defined:
  // 271:     $mapped_namespace namespace_mappings(namespace)
  // 272:     if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  // 273:   $name mangled_name_of(self)
  // 274:   $info used_names(name)
  // 275:   cond
  // 276:     -> self.is_a_destination:
  // 277:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__unless();
  func = myself->type;
  frame->cont = cont__19_51;
}
static void entry__19_49(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 300: !used_names(name)
  // 301:   types::grammar_node
  // 302:     .identifier_of self
  // 303:     .variable_kind_of STATIC_SINGLE
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 300: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__19_50;
}
static void cont__19_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_45(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 296: ... "
  // 297:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__19_29;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__19_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__19_46;
}
static void cont__19_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 296: SyntaxError self "
  // 297:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_40(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 290: !used_names(name)
  // 291:   types::grammar_node
  // 292:     .identifier_of self
  // 293:     .variable_kind_of POLYMORPHIC
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__POLYMORPHIC());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 290: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__19_41;
}
static void cont__19_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_42(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // info: 0
  // self: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 295: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__19_43;
}
static void cont__19_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 295: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_44;
}
static void cont__19_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 295: ... :
  // 296:   SyntaxError self "
  // 297:     Incompatible use of identifier "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__19_45, 0);
  // 295: unless variable_kind_of(info) == POLYMORPHIC:
  // 296:   SyntaxError self "
  // 297:     Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_34(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // info: 0
  // name: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__19_35;
}
static void cont__19_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 289: ... variable_kind_of(info) == STATIC_SINGLE
  frame->slots[5] /* temp__3 */ = create_closure(entry__19_36, 0);
  // 289: info.is_undefined || variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__19_39;
}
static void entry__19_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 289: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__19_37;
}
static void cont__19_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 289: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_38;
}
static void cont__19_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 289: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 289: ... :
  // 290:   !used_names(name)
  // 291:     types::grammar_node
  // 292:       .identifier_of self
  // 293:       .variable_kind_of POLYMORPHIC
  frame->slots[6] /* temp__4 */ = create_closure(entry__19_40, 0);
  // 294: :
  // 295:   unless variable_kind_of(info) == POLYMORPHIC:
  // 296:     SyntaxError self "
  // 297:       Incompatible use of identifier "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__19_42, 0);
  // 288: if
  // 289:   info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 290:     !used_names(name)
  // 291:       types::grammar_node
  // 292:         .identifier_of self
  // 293:         .variable_kind_of POLYMORPHIC
  // 294:   :
  // 295:     unless variable_kind_of(info) == POLYMORPHIC:
  // 296:       SyntaxError self "
  // 297:         Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_28(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // name: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 285: ... "
  // 286:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__19_29;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__19_30;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__19_31;
}
static void cont__19_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 285: SyntaxError self "
  // 286:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_23(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // name: 0
  // self: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 279: !used_names(name)
  // 280:   types::grammar_node
  // 281:     .identifier_of self
  // 282:     .variable_kind_of STATIC_MULTI
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_MULTI());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 279: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__19_24;
}
static void cont__19_24(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  set__used_names(arguments->slots[0]);
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_25(void) {
  allocate_initialized_frame_gc(3, 6);
  // slot allocations:
  // info: 0
  // self: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* self */
  frame->slots[2] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 284: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__19_26;
}
static void cont__19_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 284: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_27;
}
static void cont__19_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 284: ... :
  // 285:   SyntaxError self "
  // 286:     Incompatible use of identifier "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__19_28, 0);
  // 284: if variable_kind_of(info) == POLYMORPHIC:
  // 285:   SyntaxError self "
  // 286:     Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_17(void) {
  allocate_initialized_frame_gc(3, 8);
  // slot allocations:
  // info: 0
  // name: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__19_18;
}
static void cont__19_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 278: ... variable_kind_of(info) == STATIC_SINGLE
  frame->slots[5] /* temp__3 */ = create_closure(entry__19_19, 0);
  // 278: info.is_undefined || variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__19_22;
}
static void entry__19_19(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 278: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__19_20;
}
static void cont__19_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 278: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__19_21;
}
static void cont__19_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 278: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__19_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 278: ... :
  // 279:   !used_names(name)
  // 280:     types::grammar_node
  // 281:       .identifier_of self
  // 282:       .variable_kind_of STATIC_MULTI
  frame->slots[6] /* temp__4 */ = create_closure(entry__19_23, 0);
  // 283: :
  // 284:   if variable_kind_of(info) == POLYMORPHIC:
  // 285:     SyntaxError self "
  // 286:       Incompatible use of identifier "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__19_25, 0);
  // 277: if
  // 278:   info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 279:     !used_names(name)
  // 280:       types::grammar_node
  // 281:         .identifier_of self
  // 282:         .variable_kind_of STATIC_MULTI
  // 283:   :
  // 284:     if variable_kind_of(info) == POLYMORPHIC:
  // 285:       SyntaxError self "
  // 286:         Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  arguments->slots[2] = frame->slots[7] /* temp__5 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_15(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // info: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 276: ... self.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__19_16;
}
static void cont__19_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 276: ... :
  // 277:   if
  // 278:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 279:       !used_names(name)
  // 280:         types::grammar_node
  // 281:           .identifier_of self
  // 282:           .variable_kind_of STATIC_MULTI
  // 283:     :
  // 284:       if variable_kind_of(info) == POLYMORPHIC:
  // 285:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__19_17, 0);
  // 276: -> self.is_a_destination:
  // 277:   if
  // 278:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 279:       !used_names(name)
  // 280:         types::grammar_node
  // 281:           .identifier_of self
  // 282:           .variable_kind_of STATIC_MULTI
  // 283:     :
  // 284:       if variable_kind_of(info) == POLYMORPHIC:
  // 285:         SyntaxError self "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_32(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // self: 0
  // info: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[3]; /* info */
  frame->slots[2] = myself->closure.frame->slots[2]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 287: ... self.is_used_as_a_polymorphic_function
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_used_as_a_polymorphic_function();
  func = myself->type;
  frame->cont = cont__19_33;
}
static void cont__19_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 287: ... :
  // 288:   if
  // 289:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 290:       !used_names(name)
  // 291:         types::grammar_node
  // 292:           .identifier_of self
  // 293:           .variable_kind_of POLYMORPHIC
  // 294:     :
  // 295:       unless variable_kind_of(info) == POLYMORPHIC:
  // 296:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__19_34, 0);
  // 287: -> self.is_used_as_a_polymorphic_function:
  // 288:   if
  // 289:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 290:       !used_names(name)
  // 291:         types::grammar_node
  // 292:           .identifier_of self
  // 293:           .variable_kind_of POLYMORPHIC
  // 294:     :
  // 295:       unless variable_kind_of(info) == POLYMORPHIC:
  // 296:         SyntaxError self "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_47(void) {
  allocate_initialized_frame_gc(3, 5);
  // slot allocations:
  // info: 0
  // name: 1
  // self: 2
  frame->slots[0] = myself->closure.frame->slots[3]; /* info */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 299: ... info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__19_48;
}
static void cont__19_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 299: ... :
  // 300:   !used_names(name)
  // 301:     types::grammar_node
  // 302:       .identifier_of self
  // 303:       .variable_kind_of STATIC_SINGLE
  frame->slots[4] /* temp__2 */ = create_closure(entry__19_49, 0);
  // 299: if info.is_undefined:
  // 300:   !used_names(name)
  // 301:     types::grammar_node
  // 302:       .identifier_of self
  // 303:       .variable_kind_of STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__19_5(void) {
  allocate_initialized_frame_gc(1, 7);
  // slot allocations:
  // self: 0
  // namespace: 1
  // name: 2
  // info: 3
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* namespace */ = create_future();
  frame->slots[2] /* name */ = create_future();
  frame->slots[3] /* info */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 269: $namespace namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__19_6;
}
static void cont__19_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* namespace */, arguments->slots[0]);
  // 270: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__19_7;
}
static void cont__19_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 270: ... :
  // 271:   $mapped_namespace namespace_mappings(namespace)
  // 272:   if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_8, 0);
  // 270: if namespace.is_defined:
  // 271:   $mapped_namespace namespace_mappings(namespace)
  // 272:   if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__19_12;
}
static void entry__19_11(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // self: 0
  // mapped_namespace: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* mapped_namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 272: ... !self.namespace_of mapped_namespace
  frame->slots[2] /* temp__1 */ = frame->slots[1] /* mapped_namespace */;
  // 272: ... !self.namespace_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, frame->slots[2] /* temp__1 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__19_8(void) {
  allocate_initialized_frame_gc(2, 5);
  // slot allocations:
  // namespace: 0
  // self: 1
  // mapped_namespace: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* namespace */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] /* mapped_namespace */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 271: $mapped_namespace namespace_mappings(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__19_9;
}
static void cont__19_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mapped_namespace */, arguments->slots[0]);
  // 272: ... mapped_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mapped_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__19_10;
}
static void cont__19_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 272: ... : !self.namespace_of mapped_namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__19_11, 0);
  // 272: if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 273: $name mangled_name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__19_13;
}
static void cont__19_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 274: $info used_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__19_14;
}
static void cont__19_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 276: -> self.is_a_destination:
  // 277:   if
  // 278:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 279:       !used_names(name)
  // 280:         types::grammar_node
  // 281:           .identifier_of self
  // 282:           .variable_kind_of STATIC_MULTI
  // 283:     :
  // 284:       if variable_kind_of(info) == POLYMORPHIC:
  // 285:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__19_15, 0);
  // 287: -> self.is_used_as_a_polymorphic_function:
  // 288:   if
  // 289:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 290:       !used_names(name)
  // 291:         types::grammar_node
  // 292:           .identifier_of self
  // 293:           .variable_kind_of POLYMORPHIC
  // 294:     :
  // 295:       unless variable_kind_of(info) == POLYMORPHIC:
  // 296:         SyntaxError self "
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__19_32, 0);
  // 298: :
  // 299:   if info.is_undefined:
  // 300:     !used_names(name)
  // 301:       types::grammar_node
  // 302:         .identifier_of self
  // 303:         .variable_kind_of STATIC_SINGLE
  frame->slots[6] /* temp__3 */ = create_closure(entry__19_47, 0);
  // 275: cond
  // 276:   -> self.is_a_destination:
  // 277:     if
  // 278:       info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 279:         !used_names(name)
  // 280:           types::grammar_node
  // 281:             .identifier_of self
  // 282:             .variable_kind_of STATIC_MULTI
  // 283:       :
  // 284:         if variable_kind_of(info) == POLYMORPHIC:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  arguments->slots[2] = frame->slots[6] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__cond();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__19_51(void) {
  int i = argument_count;
  while (--i >= 0) {
    arguments->slots[i+1] = arguments->slots[i];
  }
  argument_count += 1;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
EXPORT void collect__annotator(void) {
  var.sim2c__annotate_statement = collect_node(var.sim2c__annotate_statement);
  var.sim2c__annotate_expression = collect_node(var.sim2c__annotate_expression);
  var._annotate_output_arguments = collect_node(var._annotate_output_arguments);
  var._annotate_arguments = collect_node(var._annotate_arguments);
  var.sim2c__check_definitions = collect_node(var.sim2c__check_definitions);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__annotator(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
  define_polymorphic_function("sim2c", "annotate_statement", get__sim2c__annotate_statement, &poly_idx__sim2c__annotate_statement, &var.sim2c__annotate_statement);
  define_polymorphic_function("sim2c", "annotate_expression", get__sim2c__annotate_expression, &poly_idx__sim2c__annotate_expression, &var.sim2c__annotate_expression);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__annotator(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  character__47 = from_uchar32(47);
  number__1 = from_uint32(1U);
  character__46 = from_uchar32(46);
  number__2 = from_uint32(2U);
  func__4_2 = create_function(entry__4_2, 1);
  func__4_1_annotate_output_arguments = create_function(entry__4_1_annotate_output_arguments, 1);
  func__5_2 = create_function(entry__5_2, 1);
  func__5_1_annotate_arguments = create_function(entry__5_1_annotate_arguments, 1);
  string__6_2 = from_latin_1_string("annotate statement", 18);
  func__6_1_types__grammar_node_annotate_statement = create_function(entry__6_1_types__grammar_node_annotate_statement, 1);
  string__7_2 = from_latin_1_string("annotate expression", 19);
  func__7_1_types__grammar_node_annotate_expression = create_function(entry__7_1_types__grammar_node_annotate_expression, 1);
  string__8_12 = from_latin_1_string("the identifier \042", 16);
  string__8_13 = from_latin_1_string("\042 is defined but not used", 25);
  string__8_27 = from_latin_1_string("\042 is defined as a read-write variable, but there is no actual assignment", 72);
  string__8_40 = from_latin_1_string("attempt to use the identifier \042", 31);
  string__8_41 = from_latin_1_string("\042 that is marked as not being used", 34);
  func__8_1_sim2c__check_definitions = create_function(entry__8_1_sim2c__check_definitions, 2);
  string__9_2 = from_latin_1_string("annotate body", 13);
  func__9_6 = create_function(entry__9_6, 1);
  func__9_19 = create_function(entry__9_19, 1);
  string__9_31 = from_latin_1_string("attempt to define a namespaced entity (", 39);
  string__9_32 = from_latin_1_string(") in an inner scope", 19);
  string__9_39 = from_latin_1_string("Attempt to define a variable twice within a single scope (", 58);
  string__9_40 = from_latin_1_string(")", 1);
  string__9_61 = from_latin_1_string("return__", 8);
  func__9_84 = create_function(entry__9_84, 1);
  func__9_1_sim2c__body_annotate_expression = create_function(entry__9_1_sim2c__body_annotate_expression, 1);
  string__10_25 = from_latin_1_string("::", 2);
  string__10_26 = from_latin_1_string("__", 2);
  string__10_28 = from_latin_1_string("_", 1);
  func__10_1_sim2c__call_annotate_statement = create_function(entry__10_1_sim2c__call_annotate_statement, 1);
  string__11_2 = from_latin_1_string("annotate C-code", 15);
  string__11_5 = from_latin_1_string("type", 4);
  string__11_6 = from_latin_1_string("object", 6);
  func__11_1_sim2c__c_code_annotate_statement = create_function(entry__11_1_sim2c__c_code_annotate_statement, 1);
  string__12_2 = from_latin_1_string("annotate define static single", 29);
  func__12_1_sim2c__define_static_single_annotate_expression = create_function(entry__12_1_sim2c__define_static_single_annotate_expression, 1);
  string__13_2 = from_latin_1_string("annotate define static multi", 28);
  func__13_1_sim2c__define_static_multi_annotate_expression = create_function(entry__13_1_sim2c__define_static_multi_annotate_expression, 1);
  string__14_2 = from_latin_1_string("annotate define dynamic single", 30);
  func__14_1_sim2c__define_dynamic_single_annotate_expression = create_function(entry__14_1_sim2c__define_dynamic_single_annotate_expression, 1);
  string__15_2 = from_latin_1_string("annotate define dynamic multi", 29);
  func__15_1_sim2c__define_dynamic_multi_annotate_expression = create_function(entry__15_1_sim2c__define_dynamic_multi_annotate_expression, 1);
  string__16_2 = from_latin_1_string("annotate function call", 22);
  func__16_1_sim2c__function_call_annotate_expression = create_function(entry__16_1_sim2c__function_call_annotate_expression, 1);
  string__17_2 = from_latin_1_string("annotate attribute-value pair", 29);
  func__17_1_sim2c__attribute_value_pair_annotate_expression = create_function(entry__17_1_sim2c__attribute_value_pair_annotate_expression, 1);
  string__18_2 = from_latin_1_string("annotate attribute-function pair", 32);
  func__18_1_sim2c__attribute_function_pair_annotate_expression = create_function(entry__18_1_sim2c__attribute_function_pair_annotate_expression, 1);
  string__19_2 = from_latin_1_string("annotate identifier ", 20);
  string__19_29 = from_latin_1_string("Incompatible use of identifier \042", 32);
  string__19_30 = from_latin_1_string("\042", 1);
  func__19_1_sim2c__identifier_annotate_expression = create_function(entry__19_1_sim2c__identifier_annotate_expression, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__annotator(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("annotator");
  set_used_namespaces(used_namespaces);
  register_dynamic(&dyna_idx__defines_dynamics);
  define__defines_dynamics(undefined);
  define_single_assign_static("sim2c", "check_definitions", get__sim2c__check_definitions, &var.sim2c__check_definitions);
}

static int already_run_phase_4 = false;

EXPORT void phase_4__annotator(void) {
  if (already_run_phase_4) return;
  already_run_phase_4 = true;
  set_module("annotator");
  set_used_namespaces(used_namespaces);
  use_read_only(NULL, "CONTINUATION_PARAMETER", &get__CONTINUATION_PARAMETER, &get_value_or_future__CONTINUATION_PARAMETER);
  use_read_only(NULL, "DYNAMIC_MULTI", &get__DYNAMIC_MULTI, &get_value_or_future__DYNAMIC_MULTI);
  use_read_only(NULL, "DYNAMIC_SINGLE", &get__DYNAMIC_SINGLE, &get_value_or_future__DYNAMIC_SINGLE);
  use_read_only(NULL, "IN_OUT_PARAMETER", &get__IN_OUT_PARAMETER, &get_value_or_future__IN_OUT_PARAMETER);
  use_read_only(NULL, "NONE", &get__NONE, &get_value_or_future__NONE);
  use_read_only(NULL, "POLYMORPHIC", &get__POLYMORPHIC, &get_value_or_future__POLYMORPHIC);
  use_read_only(NULL, "STATIC_MULTI", &get__STATIC_MULTI, &get_value_or_future__STATIC_MULTI);
  use_read_only(NULL, "STATIC_SINGLE", &get__STATIC_SINGLE, &get_value_or_future__STATIC_SINGLE);
  use_read_only(NULL, "SyntaxError", &get__SyntaxError, &get_value_or_future__SyntaxError);
  use_read_only(NULL, "Warning", &get__Warning, &get_value_or_future__Warning);
  use_polymorphic_function(NULL, "annotate_expression", &get__annotate_expression, &poly_idx__annotate_expression);
  use_polymorphic_function(NULL, "annotate_statement", &get__annotate_statement, &poly_idx__annotate_statement);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_write(NULL, "assigned_names", &get__assigned_names, &set__assigned_names);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_polymorphic_function(NULL, "attribute_of", &get__attribute_of, &poly_idx__attribute_of);
  use_polymorphic_function(NULL, "base_of", &get__base_of, &poly_idx__base_of);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "check_definitions", &get__check_definitions, &get_value_or_future__check_definitions);
  use_read_only(NULL, "cond", &get__cond, &get_value_or_future__cond);
  use_polymorphic_function(NULL, "continuation_of", &get__continuation_of, &poly_idx__continuation_of);
  use_polymorphic_function(NULL, "default_value_of", &get__default_value_of, &poly_idx__default_value_of);
  use_read_only(NULL, "define_static_single", &get__define_static_single, &get_value_or_future__define_static_single);
  use_read_write(NULL, "defined_names", &get__defined_names, &set__defined_names);
  use_polymorphic_function(NULL, "defined_names_of", &get__defined_names_of, &poly_idx__defined_names_of);
  use_polymorphic_function(NULL, "defines_a_dynamic", &get__defines_a_dynamic, &poly_idx__defines_a_dynamic);
  use_read_only(NULL, "do", &get__do, &get_value_or_future__do);
  use_read_only(NULL, "do_print_warnings", &get__do_print_warnings, &get_value_or_future__do_print_warnings);
  use_read_only(NULL, "empty_insert_order_table", &get__empty_insert_order_table, &get_value_or_future__empty_insert_order_table);
  use_read_only(NULL, "empty_list", &get__empty_list, &get_value_or_future__empty_list);
  use_read_only(NULL, "empty_set", &get__empty_set, &get_value_or_future__empty_set);
  use_read_only(NULL, "false", &get__false, &get_value_or_future__false);
  use_read_only(NULL, "for_each", &get__for_each, &get_value_or_future__for_each);
  use_read_only(NULL, "full_name_of", &get__full_name_of, &get_value_or_future__full_name_of);
  use_polymorphic_function(NULL, "functor_of", &get__functor_of, &poly_idx__functor_of);
  use_read_only(NULL, "identifier", &get__identifier, &get_value_or_future__identifier);
  use_polymorphic_function(NULL, "identifier_of", &get__identifier_of, &poly_idx__identifier_of);
  use_read_only(NULL, "if", &get__if, &get_value_or_future__if);
  use_read_only(NULL, "inc", &get__inc, &get_value_or_future__inc);
  use_read_write(NULL, "index", &get__index, &set__index);
  use_read_only(NULL, "is_a_body", &get__is_a_body, &get_value_or_future__is_a_body);
  use_read_only(NULL, "is_a_c_body", &get__is_a_c_body, &get_value_or_future__is_a_c_body);
  use_read_only(NULL, "is_a_definition", &get__is_a_definition, &get_value_or_future__is_a_definition);
  use_read_only(NULL, "is_a_destination", &get__is_a_destination, &get_value_or_future__is_a_destination);
  use_read_only(NULL, "is_a_function_call", &get__is_a_function_call, &get_value_or_future__is_a_function_call);
  use_read_only(NULL, "is_a_multi_assign_definition", &get__is_a_multi_assign_definition, &get_value_or_future__is_a_multi_assign_definition);
  use_polymorphic_function(NULL, "is_a_single_assign_definition", &get__is_a_single_assign_definition, &poly_idx__is_a_single_assign_definition);
  use_read_only(NULL, "is_a_unique_item_constant", &get__is_a_unique_item_constant, &get_value_or_future__is_a_unique_item_constant);
  use_read_only(NULL, "is_an_assignment", &get__is_an_assignment, &get_value_or_future__is_an_assignment);
  use_read_only(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &get_value_or_future__is_an_attribute_access);
  use_read_only(NULL, "is_an_operator_symbol", &get__is_an_operator_symbol, &get_value_or_future__is_an_operator_symbol);
  use_read_only(NULL, "is_an_optional_item", &get__is_an_optional_item, &get_value_or_future__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_not_used", &get__is_not_used, &get_value_or_future__is_not_used);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "is_used_as_a_polymorphic_function", &get__is_used_as_a_polymorphic_function, &get_value_or_future__is_used_as_a_polymorphic_function);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "mangled_name_of", &get__mangled_name_of, &get_value_or_future__mangled_name_of);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_read_only(NULL, "namespace_mappings", &get__namespace_mappings, &get_value_or_future__namespace_mappings);
  use_polymorphic_function(NULL, "namespace_of", &get__namespace_of, &poly_idx__namespace_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_polymorphic_function(NULL, "output_arguments_of", &get__output_arguments_of, &poly_idx__output_arguments_of);
  use_polymorphic_function(NULL, "parameter_kind_of", &get__parameter_kind_of, &poly_idx__parameter_kind_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_read_only(NULL, "range", &get__range, &get_value_or_future__range);
  use_read_only(NULL, "replace_all", &get__replace_all, &get_value_or_future__replace_all);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_multi_assign_dynamic("sim2c", "assigned_names", &get__sim2c__assigned_names, &set__sim2c__assigned_names, &define__sim2c__assigned_names);
  use_read_only("sim2c", "attribute_function_pair", &get__sim2c__attribute_function_pair, &get_value_or_future__sim2c__attribute_function_pair);
  use_read_only("sim2c", "attribute_value_pair", &get__sim2c__attribute_value_pair, &get_value_or_future__sim2c__attribute_value_pair);
  use_read_only("sim2c", "body", &get__sim2c__body, &get_value_or_future__sim2c__body);
  use_read_only("sim2c", "c_code", &get__sim2c__c_code, &get_value_or_future__sim2c__c_code);
  use_read_only("sim2c", "call", &get__sim2c__call, &get_value_or_future__sim2c__call);
  use_read_only("sim2c", "define_dynamic_multi", &get__sim2c__define_dynamic_multi, &get_value_or_future__sim2c__define_dynamic_multi);
  use_read_only("sim2c", "define_dynamic_single", &get__sim2c__define_dynamic_single, &get_value_or_future__sim2c__define_dynamic_single);
  use_read_only("sim2c", "define_static_multi", &get__sim2c__define_static_multi, &get_value_or_future__sim2c__define_static_multi);
  use_read_only("sim2c", "define_static_single", &get__sim2c__define_static_single, &get_value_or_future__sim2c__define_static_single);
  use_multi_assign_dynamic("sim2c", "defined_names", &get__sim2c__defined_names, &set__sim2c__defined_names, &define__sim2c__defined_names);
  use_read_only("sim2c", "function_call", &get__sim2c__function_call, &get_value_or_future__sim2c__function_call);
  use_read_only("sim2c", "identifier", &get__sim2c__identifier, &get_value_or_future__sim2c__identifier);
  use_multi_assign_dynamic("sim2c", "used_names", &get__sim2c__used_names, &set__sim2c__used_names, &define__sim2c__used_names);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "key_value_pair", &get__std__key_value_pair, &get_value_or_future__std__key_value_pair);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only(NULL, "to_string", &get__to_string, &get_value_or_future__to_string);
  use_read_only(NULL, "true", &get__true, &get_value_or_future__true);
  use_read_only("types", "grammar_node", &get__types__grammar_node, &get_value_or_future__types__grammar_node);
  use_read_only(NULL, "undefined", &get__undefined, &get_value_or_future__undefined);
  use_read_only(NULL, "unless", &get__unless, &get_value_or_future__unless);
  use_read_only(NULL, "update_each", &get__update_each, &get_value_or_future__update_each);
  use_read_only(NULL, "update_info", &get__update_info, &get_value_or_future__update_info);
  use_read_write(NULL, "used_names", &get__used_names, &set__used_names);
  use_polymorphic_function(NULL, "used_names_of", &get__used_names_of, &poly_idx__used_names_of);
  use_polymorphic_function(NULL, "variable_kind_of", &get__variable_kind_of, &poly_idx__variable_kind_of);
  use_read_only(NULL, "while", &get__while, &get_value_or_future__while);
  define_method("types", "grammar_node", poly_idx__annotate_statement, func__6_1_types__grammar_node_annotate_statement);
  define_method("types", "grammar_node", poly_idx__annotate_expression, func__7_1_types__grammar_node_annotate_expression);
  define_method("sim2c", "body", poly_idx__annotate_expression, func__9_1_sim2c__body_annotate_expression);
  define_method("sim2c", "call", poly_idx__annotate_statement, func__10_1_sim2c__call_annotate_statement);
  define_method("sim2c", "c_code", poly_idx__annotate_statement, func__11_1_sim2c__c_code_annotate_statement);
  define_method("sim2c", "define_static_single", poly_idx__annotate_expression, func__12_1_sim2c__define_static_single_annotate_expression);
  define_method("sim2c", "define_static_multi", poly_idx__annotate_expression, func__13_1_sim2c__define_static_multi_annotate_expression);
  define_method("sim2c", "define_dynamic_single", poly_idx__annotate_expression, func__14_1_sim2c__define_dynamic_single_annotate_expression);
  define_method("sim2c", "define_dynamic_multi", poly_idx__annotate_expression, func__15_1_sim2c__define_dynamic_multi_annotate_expression);
  define_method("sim2c", "function_call", poly_idx__annotate_expression, func__16_1_sim2c__function_call_annotate_expression);
  define_method("sim2c", "attribute_value_pair", poly_idx__annotate_expression, func__17_1_sim2c__attribute_value_pair_annotate_expression);
  define_method("sim2c", "attribute_function_pair", poly_idx__annotate_expression, func__18_1_sim2c__attribute_function_pair_annotate_expression);
  define_method("sim2c", "identifier", poly_idx__annotate_expression, func__19_1_sim2c__identifier_annotate_expression);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__annotator(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  assign_value(&var.sim2c__annotate_statement, create_function(type__sim2c__annotate_statement, -1));
  assign_value(&var.sim2c__annotate_expression, create_function(type__sim2c__annotate_expression, -1));
  assign_variable(&var._annotate_output_arguments, &func__4_1_annotate_output_arguments);
  assign_variable(&var._annotate_arguments, &func__5_1_annotate_arguments);
  assign_variable(&var.sim2c__check_definitions, &func__8_1_sim2c__check_definitions);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__annotator(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__annotator);
}
