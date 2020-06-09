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
IMPORT NODE *get_dynamic_cell(int id);
IMPORT void set_dynamic_cell(int id, NODE *node);
IMPORT void define_dynamic_cell(int id, NODE *node);
IMPORT NODE *get_dynamic_slot(int id);
IMPORT void define_dynamic_slot(int id, NODE *node);
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
IMPORT void set_module(const char *name);
IMPORT NODE *from_uint32(uint32_t val);
IMPORT void define_polymorphic_function(
  const char *namespace, const char *name, NODE_GETTER getter, int *id_p,
  NODE **var_p
);
IMPORT NODE *create_function(FUNC func, int par_count);
IMPORT NODE *from_latin_1_string(const char *str, long len);
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
static NODE_GETTER get__append;
static NODE_GETTER get_value_or_future__append;
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
static NODE_GETTER get__compiler__assigned_names;
static NODE_SETTER set__compiler__assigned_names;
static NODE_SETTER define__compiler__assigned_names;
static NODE_GETTER get__compiler__attribute_function_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_function_pair;
static NODE_GETTER get__compiler__attribute_value_pair;
static NODE_GETTER get_value_or_future__compiler__attribute_value_pair;
static NODE_GETTER get__compiler__body;
static NODE_GETTER get_value_or_future__compiler__body;
static NODE_GETTER get__compiler__c_code;
static NODE_GETTER get_value_or_future__compiler__c_code;
static NODE_GETTER get__compiler__call;
static NODE_GETTER get_value_or_future__compiler__call;
static NODE_GETTER get__compiler__define_dynamic_multi;
static NODE_GETTER get_value_or_future__compiler__define_dynamic_multi;
static NODE_GETTER get__compiler__define_dynamic_single;
static NODE_GETTER get_value_or_future__compiler__define_dynamic_single;
static NODE_GETTER get__compiler__define_static_multi;
static NODE_GETTER get_value_or_future__compiler__define_static_multi;
static NODE_GETTER get__compiler__define_static_single;
static NODE_GETTER get_value_or_future__compiler__define_static_single;
static NODE_GETTER get__compiler__defined_names;
static NODE_SETTER set__compiler__defined_names;
static NODE_SETTER define__compiler__defined_names;
static NODE_GETTER get__compiler__function_call;
static NODE_GETTER get_value_or_future__compiler__function_call;
static NODE_GETTER get__compiler__identifier;
static NODE_GETTER get_value_or_future__compiler__identifier;
static NODE_GETTER get__compiler__used_names;
static NODE_SETTER set__compiler__used_names;
static NODE_SETTER define__compiler__used_names;
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
static NODE_GETTER get__is_used_as_a_destination;
static NODE_GETTER get_value_or_future__is_used_as_a_destination;
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
static int poly_idx__parameter_kind_of;
static NODE_GETTER get__parameter_kind_of;
static int poly_idx__parameters_of;
static NODE_GETTER get__parameters_of;
static NODE_GETTER get__push;
static NODE_GETTER get_value_or_future__push;
static int poly_idx__result_count_of;
static NODE_GETTER get__result_count_of;
static NODE_GETTER get__show_compiler_debug_info;
static NODE_GETTER get_value_or_future__show_compiler_debug_info;
static int poly_idx__statements_of;
static NODE_GETTER get__statements_of;
static NODE_GETTER get__std__and;
static NODE_GETTER get_value_or_future__std__and;
static NODE_GETTER get__std__equal;
static NODE_GETTER get_value_or_future__std__equal;
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
static NODE_GETTER get__string;
static NODE_GETTER get_value_or_future__string;
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
  NODE *compiler__annotate_statement;
  NODE *compiler__annotate_expression;
  NODE *compiler__check_definitions;
} var;
static const char *var_names[] = {
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
static int dyna_idx__level;
static NODE *get__level(void) {
  return get_dynamic_slot(dyna_idx__level);
}
static void define__level(NODE *node) {
  define_dynamic_slot(dyna_idx__level, node);
}
static int poly_idx__compiler__annotate_statement;
static void type__compiler__annotate_statement(void);
static NODE *get__compiler__annotate_statement(void) {
  return var.compiler__annotate_statement;
}
static int poly_idx__compiler__annotate_expression;
static void type__compiler__annotate_expression(void);
static NODE *get__compiler__annotate_expression(void) {
  return var.compiler__annotate_expression;
}
static NODE *func__annotate_arguments;
static void entry__annotate_arguments(void);
static FRAME_INFO frame__annotate_arguments = {1, {"arguments"}};
static NODE *func__annotate_arguments_2;
static void entry__annotate_arguments_2(void);
static FRAME_INFO frame__annotate_arguments_2 = {1, {"argument"}};
static void cont__annotate_arguments_3(void);
static void cont__annotate_arguments_4(void);
static NODE *func__annotate_arguments_5;
static void entry__annotate_arguments_5(void);
static FRAME_INFO frame__annotate_arguments_5 = {0, {}};
static void cont__annotate_arguments_6(void);
static NODE *func__annotate_arguments_7;
static void entry__annotate_arguments_7(void);
static FRAME_INFO frame__annotate_arguments_7 = {2, {"argument", "destination"}};
static void cont__annotate_arguments_8(void);
static NODE *func__annotate_arguments_9;
static void entry__annotate_arguments_9(void);
static FRAME_INFO frame__annotate_arguments_9 = {2, {"destination", "name"}};
static NODE *func__annotate_arguments_10;
static void entry__annotate_arguments_10(void);
static FRAME_INFO frame__annotate_arguments_10 = {1, {"destination"}};
static void cont__annotate_arguments_11(void);
static NODE *func__annotate_arguments_12;
static void entry__annotate_arguments_12(void);
static FRAME_INFO frame__annotate_arguments_12 = {1, {"destination"}};
static void cont__annotate_arguments_13(void);
static NODE *func__annotate_arguments_14;
static void entry__annotate_arguments_14(void);
static FRAME_INFO frame__annotate_arguments_14 = {1, {"destination"}};
static void cont__annotate_arguments_15(void);
static void cont__annotate_arguments_16(void);
static NODE *func__annotate_arguments_17;
static void entry__annotate_arguments_17(void);
static FRAME_INFO frame__annotate_arguments_17 = {1, {"destination"}};
static void cont__annotate_arguments_18(void);
static void cont__annotate_arguments_19(void);
static void cont__annotate_arguments_20(void);
static void cont__annotate_arguments_21(void);
static void cont__annotate_arguments_22(void);
static void cont__annotate_arguments_23(void);
static NODE *func__types__grammar_node___annotate_statement;
static void entry__types__grammar_node___annotate_statement(void);
static FRAME_INFO frame__types__grammar_node___annotate_statement = {1, {"self"}};
static NODE *string__8a2e321e316b06ed;
static void cont__types__grammar_node___annotate_statement_3(void);
static NODE *func__types__grammar_node___annotate_expression;
static void entry__types__grammar_node___annotate_expression(void);
static FRAME_INFO frame__types__grammar_node___annotate_expression = {1, {"self"}};
static NODE *string__bce93a983bb5b33f;
static void cont__types__grammar_node___annotate_expression_3(void);
static NODE *func__compiler__check_definitions;
static void entry__compiler__check_definitions(void);
static FRAME_INFO frame__compiler__check_definitions = {2, {"defined_names", "used_names"}};
static NODE *func__compiler__check_definitions_2;
static void entry__compiler__check_definitions_2(void);
static FRAME_INFO frame__compiler__check_definitions_2 = {4, {"name", "info", "used_names", "identifier"}};
static void cont__compiler__check_definitions_3(void);
static void cont__compiler__check_definitions_4(void);
static void cont__compiler__check_definitions_5(void);
static NODE *func__compiler__check_definitions_6;
static void entry__compiler__check_definitions_6(void);
static FRAME_INFO frame__compiler__check_definitions_6 = {4, {"used_names", "name", "identifier", "info"}};
static void cont__compiler__check_definitions_7(void);
static void cont__compiler__check_definitions_8(void);
static NODE *func__compiler__check_definitions_9;
static void entry__compiler__check_definitions_9(void);
static FRAME_INFO frame__compiler__check_definitions_9 = {2, {"identifier", "name"}};
static void cont__compiler__check_definitions_10(void);
static NODE *func__compiler__check_definitions_11;
static void entry__compiler__check_definitions_11(void);
static FRAME_INFO frame__compiler__check_definitions_11 = {2, {"identifier", "name"}};
static NODE *string__1f20e521cf7a2a0e;
static NODE *string__e573d863c40ad98e;
static void cont__compiler__check_definitions_14(void);
static NODE *func__compiler__check_definitions_15;
static void entry__compiler__check_definitions_15(void);
static FRAME_INFO frame__compiler__check_definitions_15 = {3, {"info", "name", "identifier"}};
static void cont__compiler__check_definitions_16(void);
static NODE *func__compiler__check_definitions_17;
static void entry__compiler__check_definitions_17(void);
static FRAME_INFO frame__compiler__check_definitions_17 = {2, {"info", "name"}};
static void cont__compiler__check_definitions_18(void);
static void cont__compiler__check_definitions_19(void);
static void cont__compiler__check_definitions_20(void);
static NODE *func__compiler__check_definitions_21;
static void entry__compiler__check_definitions_21(void);
static FRAME_INFO frame__compiler__check_definitions_21 = {1, {"name"}};
static void cont__compiler__check_definitions_22(void);
static void cont__compiler__check_definitions_23(void);
static void cont__compiler__check_definitions_24(void);
static void cont__compiler__check_definitions_25(void);
static NODE *func__compiler__check_definitions_26;
static void entry__compiler__check_definitions_26(void);
static FRAME_INFO frame__compiler__check_definitions_26 = {2, {"identifier", "name"}};
static NODE *string__6ef85e6a0d2c67a5;
static void cont__compiler__check_definitions_28(void);
static void cont__compiler__check_definitions_29(void);
static NODE *func__compiler__check_definitions_30;
static void entry__compiler__check_definitions_30(void);
static FRAME_INFO frame__compiler__check_definitions_30 = {4, {"name", "info", "defined_names", "defined_name"}};
static void cont__compiler__check_definitions_31(void);
static void cont__compiler__check_definitions_32(void);
static NODE *func__compiler__check_definitions_33;
static void entry__compiler__check_definitions_33(void);
static FRAME_INFO frame__compiler__check_definitions_33 = {3, {"defined_name", "info", "name"}};
static NODE *func__compiler__check_definitions_34;
static void entry__compiler__check_definitions_34(void);
static FRAME_INFO frame__compiler__check_definitions_34 = {1, {"defined_name"}};
static void cont__compiler__check_definitions_35(void);
static void cont__compiler__check_definitions_36(void);
static void cont__compiler__check_definitions_37(void);
static NODE *func__compiler__check_definitions_38;
static void entry__compiler__check_definitions_38(void);
static FRAME_INFO frame__compiler__check_definitions_38 = {2, {"info", "name"}};
static void cont__compiler__check_definitions_39(void);
static NODE *string__fd0945f8c8a23329;
static NODE *string__27789aef2dccadff;
static void cont__compiler__check_definitions_42(void);
static NODE *get__compiler__check_definitions(void) {
  return var.compiler__check_definitions;
}
static NODE *func__compiler__body___annotate_expression;
static void entry__compiler__body___annotate_expression(void);
static FRAME_INFO frame__compiler__body___annotate_expression = {3, {"self", "locally_assigned_names", "outer_level"}};
static NODE *string__463aabf2a07456b1;
static void cont__compiler__body___annotate_expression_3(void);
static NODE *func__compiler__body__annotate_expression_4;
static void entry__compiler__body__annotate_expression_4(void);
static FRAME_INFO frame__compiler__body__annotate_expression_4 = {5, {"return__1", "outer_level", "self", "locally_assigned_names", "local_definitions"}};
static void cont__compiler__body__annotate_expression_5(void);
static void cont__compiler__body__annotate_expression_6(void);
static NODE *func__compiler__body__annotate_expression_7;
static void entry__compiler__body__annotate_expression_7(void);
static FRAME_INFO frame__compiler__body__annotate_expression_7 = {1, {"parameter"}};
static void cont__compiler__body__annotate_expression_8(void);
static void cont__compiler__body__annotate_expression_9(void);
static NODE *func__compiler__body__annotate_expression_10;
static void entry__compiler__body__annotate_expression_10(void);
static FRAME_INFO frame__compiler__body__annotate_expression_10 = {1, {"parameter"}};
static void cont__compiler__body__annotate_expression_11(void);
static void cont__compiler__body__annotate_expression_12(void);
static void cont__compiler__body__annotate_expression_13(void);
static NODE *func__compiler__body__annotate_expression_14;
static void entry__compiler__body__annotate_expression_14(void);
static FRAME_INFO frame__compiler__body__annotate_expression_14 = {1, {"parameter"}};
static void cont__compiler__body__annotate_expression_15(void);
static void cont__compiler__body__annotate_expression_16(void);
static void cont__compiler__body__annotate_expression_17(void);
static void cont__compiler__body__annotate_expression_18(void);
static void cont__compiler__body__annotate_expression_19(void);
static NODE *func__compiler__body__annotate_expression_20;
static void entry__compiler__body__annotate_expression_20(void);
static FRAME_INFO frame__compiler__body__annotate_expression_20 = {1, {"stmt"}};
static void cont__compiler__body__annotate_expression_21(void);
static void cont__compiler__body__annotate_expression_22(void);
static NODE *func__compiler__body__annotate_expression_23;
static void entry__compiler__body__annotate_expression_23(void);
static FRAME_INFO frame__compiler__body__annotate_expression_23 = {2, {"info", "local_definitions"}};
static void cont__compiler__body__annotate_expression_24(void);
static void cont__compiler__body__annotate_expression_25(void);
static NODE *func__compiler__body__annotate_expression_26;
static void entry__compiler__body__annotate_expression_26(void);
static FRAME_INFO frame__compiler__body__annotate_expression_26 = {4, {"info", "local_definitions", "ident", "name"}};
static void cont__compiler__body__annotate_expression_27(void);
static void cont__compiler__body__annotate_expression_28(void);
static void cont__compiler__body__annotate_expression_29(void);
static NODE *func__compiler__body__annotate_expression_30;
static void entry__compiler__body__annotate_expression_30(void);
static FRAME_INFO frame__compiler__body__annotate_expression_30 = {1, {"ident"}};
static void cont__compiler__body__annotate_expression_31(void);
static NODE *string__c9348eff105534ce;
static NODE *string__dcee629a9fc6e3f6;
static void cont__compiler__body__annotate_expression_34(void);
static void cont__compiler__body__annotate_expression_35(void);
static void cont__compiler__body__annotate_expression_36(void);
static void cont__compiler__body__annotate_expression_37(void);
static void cont__compiler__body__annotate_expression_38(void);
static NODE *func__compiler__body__annotate_expression_39;
static void entry__compiler__body__annotate_expression_39(void);
static FRAME_INFO frame__compiler__body__annotate_expression_39 = {2, {"ident", "name"}};
static NODE *string__e3b540e1e08e3bc7;
static NODE *string__578a5af303e9cc8;
static void cont__compiler__body__annotate_expression_42(void);
static void cont__compiler__body__annotate_expression_43(void);
static void cont__compiler__body__annotate_expression_44(void);
static void cont__compiler__body__annotate_expression_45(void);
static NODE *func__compiler__body__annotate_expression_46;
static void entry__compiler__body__annotate_expression_46(void);
static FRAME_INFO frame__compiler__body__annotate_expression_46 = {1, {"info"}};
static void cont__compiler__body__annotate_expression_47(void);
static void cont__compiler__body__annotate_expression_48(void);
static void cont__compiler__body__annotate_expression_49(void);
static void cont__compiler__body__annotate_expression_50(void);
static NODE *func__compiler__body__annotate_expression_51;
static void entry__compiler__body__annotate_expression_51(void);
static FRAME_INFO frame__compiler__body__annotate_expression_51 = {2, {"self", "parameters"}};
static void cont__compiler__body__annotate_expression_52(void);
static void cont__compiler__body__annotate_expression_53(void);
static NODE *func__compiler__body__annotate_expression_54;
static void entry__compiler__body__annotate_expression_54(void);
static FRAME_INFO frame__compiler__body__annotate_expression_54 = {1, {"parameters"}};
static void cont__compiler__body__annotate_expression_55(void);
static void cont__compiler__body__annotate_expression_56(void);
static void cont__compiler__body__annotate_expression_57(void);
static void cont__compiler__body__annotate_expression_58(void);
static void cont__compiler__body__annotate_expression_59(void);
static void cont__compiler__body__annotate_expression_60(void);
static NODE *func__compiler__body__annotate_expression_61;
static void entry__compiler__body__annotate_expression_61(void);
static FRAME_INFO frame__compiler__body__annotate_expression_61 = {2, {"self", "return"}};
static NODE *string__4a80ae5c052cc23f;
static void cont__compiler__body__annotate_expression_63(void);
static void cont__compiler__body__annotate_expression_64(void);
static void cont__compiler__body__annotate_expression_65(void);
static void cont__compiler__body__annotate_expression_66(void);
static void cont__compiler__body__annotate_expression_67(void);
static NODE *func__compiler__body__annotate_expression_68;
static void entry__compiler__body__annotate_expression_68(void);
static FRAME_INFO frame__compiler__body__annotate_expression_68 = {2, {"local_definitions", "locally_assigned_names"}};
static void cont__compiler__body__annotate_expression_69(void);
static void cont__compiler__body__annotate_expression_70(void);
static void cont__compiler__body___annotate_expression_71(void);
static void cont__compiler__body___annotate_expression_72(void);
static NODE *func__compiler__body__annotate_expression_73;
static void entry__compiler__body__annotate_expression_73(void);
static FRAME_INFO frame__compiler__body__annotate_expression_73 = {3, {"name", "info", "self"}};
static void cont__compiler__body__annotate_expression_74(void);
static void cont__compiler__body__annotate_expression_75(void);
static void cont__compiler__body__annotate_expression_76(void);
static NODE *func__compiler__body__annotate_expression_77;
static void entry__compiler__body__annotate_expression_77(void);
static FRAME_INFO frame__compiler__body__annotate_expression_77 = {3, {"name", "info", "updated_info"}};
static void cont__compiler__body__annotate_expression_78(void);
static void cont__compiler__body__annotate_expression_79(void);
static void cont__compiler__body__annotate_expression_80(void);
static NODE *func__compiler__body__annotate_expression_81;
static void entry__compiler__body__annotate_expression_81(void);
static FRAME_INFO frame__compiler__body__annotate_expression_81 = {2, {"name", "updated_info"}};
static void cont__compiler__body__annotate_expression_82(void);
static void cont__compiler__body___annotate_expression_83(void);
static NODE *func__compiler__body__annotate_expression_84;
static void entry__compiler__body__annotate_expression_84(void);
static FRAME_INFO frame__compiler__body__annotate_expression_84 = {1, {"locally_assigned_names"}};
static NODE *func__compiler__body__annotate_expression_85;
static void entry__compiler__body__annotate_expression_85(void);
static FRAME_INFO frame__compiler__body__annotate_expression_85 = {1, {"name"}};
static void cont__compiler__body__annotate_expression_86(void);
static void cont__compiler__body___annotate_expression_87(void);
static NODE *func__compiler__call___annotate_statement;
static void entry__compiler__call___annotate_statement(void);
static FRAME_INFO frame__compiler__call___annotate_statement = {1, {"self"}};
static void cont__compiler__call___annotate_statement_2(void);
static void cont__compiler__call___annotate_statement_3(void);
static void cont__compiler__call___annotate_statement_4(void);
static NODE *func__compiler__call__annotate_statement_5;
static void entry__compiler__call__annotate_statement_5(void);
static FRAME_INFO frame__compiler__call__annotate_statement_5 = {1, {"self"}};
static void cont__compiler__call__annotate_statement_6(void);
static void cont__compiler__call__annotate_statement_7(void);
static NODE *func__compiler__call__annotate_statement_8;
static void entry__compiler__call__annotate_statement_8(void);
static FRAME_INFO frame__compiler__call__annotate_statement_8 = {1, {"self"}};
static void cont__compiler__call__annotate_statement_9(void);
static void cont__compiler__call__annotate_statement_10(void);
static void cont__compiler__call__annotate_statement_11(void);
static void cont__compiler__call__annotate_statement_12(void);
static void cont__compiler__call__annotate_statement_13(void);
static NODE *func__compiler__call__annotate_statement_14;
static void entry__compiler__call__annotate_statement_14(void);
static FRAME_INFO frame__compiler__call__annotate_statement_14 = {1, {"self"}};
static void cont__compiler__call__annotate_statement_15(void);
static void cont__compiler__call__annotate_statement_16(void);
static void cont__compiler__call__annotate_statement_17(void);
static void cont__compiler__call__annotate_statement_18(void);
static void cont__compiler__call__annotate_statement_19(void);
static NODE *func__compiler__call__annotate_statement_20;
static void entry__compiler__call__annotate_statement_20(void);
static FRAME_INFO frame__compiler__call__annotate_statement_20 = {2, {"self", "destination"}};
static void cont__compiler__call__annotate_statement_21(void);
static void cont__compiler__call__annotate_statement_22(void);
static void cont__compiler__call__annotate_statement_23(void);
static NODE *func__compiler__call__annotate_statement_24;
static void entry__compiler__call__annotate_statement_24(void);
static FRAME_INFO frame__compiler__call__annotate_statement_24 = {3, {"self", "destination", "source"}};
static void cont__compiler__call__annotate_statement_25(void);
static void cont__compiler__call__annotate_statement_26(void);
static void cont__compiler__call__annotate_statement_27(void);
static NODE *func__compiler__call__annotate_statement_28;
static void entry__compiler__call__annotate_statement_28(void);
static FRAME_INFO frame__compiler__call__annotate_statement_28 = {1, {"source"}};
static void cont__compiler__call__annotate_statement_29(void);
static NODE *func__compiler__call__annotate_statement_30;
static void entry__compiler__call__annotate_statement_30(void);
static FRAME_INFO frame__compiler__call__annotate_statement_30 = {0, {}};
static void cont__compiler__call__annotate_statement_31(void);
static void cont__compiler__call__annotate_statement_32(void);
static NODE *func__compiler__call__annotate_statement_33;
static void entry__compiler__call__annotate_statement_33(void);
static FRAME_INFO frame__compiler__call__annotate_statement_33 = {1, {"source"}};
static void cont__compiler__call__annotate_statement_34(void);
static NODE *func__compiler__call__annotate_statement_35;
static void entry__compiler__call__annotate_statement_35(void);
static FRAME_INFO frame__compiler__call__annotate_statement_35 = {0, {}};
static void cont__compiler__call__annotate_statement_36(void);
static void cont__compiler__call__annotate_statement_37(void);
static void cont__compiler__call__annotate_statement_38(void);
static void cont__compiler__call__annotate_statement_39(void);
static NODE *func__compiler__call__annotate_statement_40;
static void entry__compiler__call__annotate_statement_40(void);
static FRAME_INFO frame__compiler__call__annotate_statement_40 = {3, {"destination", "self", "name"}};
static void cont__compiler__call__annotate_statement_41(void);
static void cont__compiler__call__annotate_statement_42(void);
static void cont__compiler__call__annotate_statement_43(void);
static void cont__compiler__call__annotate_statement_44(void);
static void cont__compiler__call__annotate_statement_45(void);
static NODE *func__compiler__call__annotate_statement_46;
static void entry__compiler__call__annotate_statement_46(void);
static FRAME_INFO frame__compiler__call__annotate_statement_46 = {3, {"destination", "name", "attribute"}};
static void cont__compiler__call__annotate_statement_47(void);
static void cont__compiler__call__annotate_statement_48(void);
static NODE *func__compiler__call__annotate_statement_49;
static void entry__compiler__call__annotate_statement_49(void);
static FRAME_INFO frame__compiler__call__annotate_statement_49 = {2, {"name", "attribute"}};
static void cont__compiler__call__annotate_statement_50(void);
static NODE *string__fa72f815cd16b93;
static void cont__compiler__call__annotate_statement_52(void);
static void cont__compiler__call__annotate_statement_53(void);
static NODE *func__compiler__call__annotate_statement_54;
static void entry__compiler__call__annotate_statement_54(void);
static FRAME_INFO frame__compiler__call__annotate_statement_54 = {1, {"name"}};
static NODE *string__4668ab89845667a5;
static void cont__compiler__call__annotate_statement_56(void);
static void cont__compiler__call__annotate_statement_57(void);
static void cont__compiler__call__annotate_statement_58(void);
static void cont__compiler__call__annotate_statement_59(void);
static void cont__compiler__call__annotate_statement_60(void);
static void cont__compiler__call__annotate_statement_61(void);
static void cont__compiler__call___annotate_statement_62(void);
static void cont__compiler__call___annotate_statement_63(void);
static void cont__compiler__call___annotate_statement_64(void);
static NODE *func__compiler__c_code___annotate_statement;
static void entry__compiler__c_code___annotate_statement(void);
static FRAME_INFO frame__compiler__c_code___annotate_statement = {1, {"self"}};
static NODE *string__1315a9c10d8edccd;
static void cont__compiler__c_code___annotate_statement_3(void);
static void cont__compiler__c_code___annotate_statement_4(void);
static NODE *string__2a0aef0b5de07d5c;
static NODE *string__4c1f570701a272a3;
static void cont__compiler__c_code___annotate_statement_7(void);
static NODE *func__compiler__c_code__annotate_statement_8;
static void entry__compiler__c_code__annotate_statement_8(void);
static FRAME_INFO frame__compiler__c_code__annotate_statement_8 = {1, {"self"}};
static void cont__compiler__c_code__annotate_statement_9(void);
static void cont__compiler__c_code___annotate_statement_10(void);
static void cont__compiler__c_code___annotate_statement_11(void);
static void cont__compiler__c_code___annotate_statement_12(void);
static NODE *func__compiler__c_code__annotate_statement_13;
static void entry__compiler__c_code__annotate_statement_13(void);
static FRAME_INFO frame__compiler__c_code__annotate_statement_13 = {1, {"self"}};
static void cont__compiler__c_code__annotate_statement_14(void);
static void cont__compiler__c_code__annotate_statement_15(void);
static void cont__compiler__c_code___annotate_statement_16(void);
static NODE *func__compiler__define_static_single___annotate_expression;
static void entry__compiler__define_static_single___annotate_expression(void);
static FRAME_INFO frame__compiler__define_static_single___annotate_expression = {1, {"self"}};
static NODE *string__da22f4fe83fda879;
static void cont__compiler__define_static_single___annotate_expression_3(void);
static void cont__compiler__define_static_single___annotate_expression_4(void);
static void cont__compiler__define_static_single___annotate_expression_5(void);
static NODE *func__compiler__define_static_single__annotate_expression_6;
static void entry__compiler__define_static_single__annotate_expression_6(void);
static FRAME_INFO frame__compiler__define_static_single__annotate_expression_6 = {1, {"self"}};
static void cont__compiler__define_static_single__annotate_expression_7(void);
static NODE *func__compiler__define_static_single__annotate_expression_8;
static void entry__compiler__define_static_single__annotate_expression_8(void);
static FRAME_INFO frame__compiler__define_static_single__annotate_expression_8 = {1, {"self"}};
static void cont__compiler__define_static_single__annotate_expression_9(void);
static void cont__compiler__define_static_single__annotate_expression_10(void);
static NODE *func__compiler__define_static_single__annotate_expression_11;
static void entry__compiler__define_static_single__annotate_expression_11(void);
static FRAME_INFO frame__compiler__define_static_single__annotate_expression_11 = {1, {"self"}};
static void cont__compiler__define_static_single__annotate_expression_12(void);
static void cont__compiler__define_static_single__annotate_expression_13(void);
static void cont__compiler__define_static_single__annotate_expression_14(void);
static void cont__compiler__define_static_single__annotate_expression_15(void);
static void cont__compiler__define_static_single__annotate_expression_16(void);
static void cont__compiler__define_static_single___annotate_expression_17(void);
static NODE *func__compiler__define_static_multi___annotate_expression;
static void entry__compiler__define_static_multi___annotate_expression(void);
static FRAME_INFO frame__compiler__define_static_multi___annotate_expression = {1, {"self"}};
static NODE *string__8d039bc45e06307a;
static void cont__compiler__define_static_multi___annotate_expression_3(void);
static void cont__compiler__define_static_multi___annotate_expression_4(void);
static NODE *func__compiler__define_dynamic_single___annotate_expression;
static void entry__compiler__define_dynamic_single___annotate_expression(void);
static FRAME_INFO frame__compiler__define_dynamic_single___annotate_expression = {1, {"self"}};
static NODE *string__ff383df04998a917;
static void cont__compiler__define_dynamic_single___annotate_expression_3(void);
static void cont__compiler__define_dynamic_single___annotate_expression_4(void);
static NODE *func__compiler__define_dynamic_multi___annotate_expression;
static void entry__compiler__define_dynamic_multi___annotate_expression(void);
static FRAME_INFO frame__compiler__define_dynamic_multi___annotate_expression = {1, {"self"}};
static NODE *string__2d2e5f670727e936;
static void cont__compiler__define_dynamic_multi___annotate_expression_3(void);
static void cont__compiler__define_dynamic_multi___annotate_expression_4(void);
static NODE *func__compiler__function_call___annotate_expression;
static void entry__compiler__function_call___annotate_expression(void);
static FRAME_INFO frame__compiler__function_call___annotate_expression = {1, {"self"}};
static NODE *string__e5094206a209984d;
static void cont__compiler__function_call___annotate_expression_3(void);
static void cont__compiler__function_call___annotate_expression_4(void);
static void cont__compiler__function_call___annotate_expression_5(void);
static NODE *func__compiler__function_call__annotate_expression_6;
static void entry__compiler__function_call__annotate_expression_6(void);
static FRAME_INFO frame__compiler__function_call__annotate_expression_6 = {1, {"self"}};
static void cont__compiler__function_call__annotate_expression_7(void);
static void cont__compiler__function_call__annotate_expression_8(void);
static void cont__compiler__function_call__annotate_expression_9(void);
static void cont__compiler__function_call__annotate_expression_10(void);
static void cont__compiler__function_call___annotate_expression_11(void);
static NODE *func__compiler__attribute_value_pair___annotate_expression;
static void entry__compiler__attribute_value_pair___annotate_expression(void);
static FRAME_INFO frame__compiler__attribute_value_pair___annotate_expression = {1, {"self"}};
static NODE *string__cdedef056fb3250d;
static void cont__compiler__attribute_value_pair___annotate_expression_3(void);
static void cont__compiler__attribute_value_pair___annotate_expression_4(void);
static void cont__compiler__attribute_value_pair___annotate_expression_5(void);
static void cont__compiler__attribute_value_pair___annotate_expression_6(void);
static void cont__compiler__attribute_value_pair___annotate_expression_7(void);
static NODE *func__compiler__attribute_function_pair___annotate_expression;
static void entry__compiler__attribute_function_pair___annotate_expression(void);
static FRAME_INFO frame__compiler__attribute_function_pair___annotate_expression = {1, {"self"}};
static NODE *string__9fe7729998bbff18;
static void cont__compiler__attribute_function_pair___annotate_expression_3(void);
static void cont__compiler__attribute_function_pair___annotate_expression_4(void);
static void cont__compiler__attribute_function_pair___annotate_expression_5(void);
static NODE *func__compiler__attribute_function_pair__annotate_expression_6;
static void entry__compiler__attribute_function_pair__annotate_expression_6(void);
static FRAME_INFO frame__compiler__attribute_function_pair__annotate_expression_6 = {1, {"self"}};
static void cont__compiler__attribute_function_pair__annotate_expression_7(void);
static void cont__compiler__attribute_function_pair__annotate_expression_8(void);
static void cont__compiler__attribute_function_pair___annotate_expression_9(void);
static void cont__compiler__attribute_function_pair___annotate_expression_10(void);
static void cont__compiler__attribute_function_pair___annotate_expression_11(void);
static NODE *func__compiler__identifier___annotate_expression;
static void entry__compiler__identifier___annotate_expression(void);
static FRAME_INFO frame__compiler__identifier___annotate_expression = {1, {"self"}};
static NODE *string__d4853f208c1cb4ea;
static void cont__compiler__identifier___annotate_expression_3(void);
static void cont__compiler__identifier___annotate_expression_4(void);
static NODE *func__compiler__identifier__annotate_expression_5;
static void entry__compiler__identifier__annotate_expression_5(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_5 = {4, {"self", "namespace", "name", "info"}};
static void cont__compiler__identifier__annotate_expression_6(void);
static void cont__compiler__identifier__annotate_expression_7(void);
static NODE *func__compiler__identifier__annotate_expression_8;
static void entry__compiler__identifier__annotate_expression_8(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_8 = {3, {"namespace", "self", "mapped_namespace"}};
static void cont__compiler__identifier__annotate_expression_9(void);
static void cont__compiler__identifier__annotate_expression_10(void);
static NODE *func__compiler__identifier__annotate_expression_11;
static void entry__compiler__identifier__annotate_expression_11(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_11 = {2, {"self", "mapped_namespace"}};
static void cont__compiler__identifier__annotate_expression_12(void);
static void cont__compiler__identifier__annotate_expression_13(void);
static void cont__compiler__identifier__annotate_expression_14(void);
static NODE *func__compiler__identifier__annotate_expression_15;
static void entry__compiler__identifier__annotate_expression_15(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_15 = {3, {"self", "info", "name"}};
static void cont__compiler__identifier__annotate_expression_16(void);
static NODE *func__compiler__identifier__annotate_expression_17;
static void entry__compiler__identifier__annotate_expression_17(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_17 = {3, {"info", "name", "self"}};
static void cont__compiler__identifier__annotate_expression_18(void);
static NODE *func__compiler__identifier__annotate_expression_19;
static void entry__compiler__identifier__annotate_expression_19(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_19 = {1, {"info"}};
static void cont__compiler__identifier__annotate_expression_20(void);
static void cont__compiler__identifier__annotate_expression_21(void);
static void cont__compiler__identifier__annotate_expression_22(void);
static NODE *func__compiler__identifier__annotate_expression_23;
static void entry__compiler__identifier__annotate_expression_23(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_23 = {2, {"name", "self"}};
static void cont__compiler__identifier__annotate_expression_24(void);
static NODE *func__compiler__identifier__annotate_expression_25;
static void entry__compiler__identifier__annotate_expression_25(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_25 = {3, {"info", "self", "name"}};
static void cont__compiler__identifier__annotate_expression_26(void);
static void cont__compiler__identifier__annotate_expression_27(void);
static NODE *func__compiler__identifier__annotate_expression_28;
static void entry__compiler__identifier__annotate_expression_28(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_28 = {2, {"self", "name"}};
static NODE *string__94ba0bbafc65551;
static NODE *string__578a5af303e9cc3;
static void cont__compiler__identifier__annotate_expression_31(void);
static NODE *func__compiler__identifier__annotate_expression_32;
static void entry__compiler__identifier__annotate_expression_32(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_32 = {3, {"self", "info", "name"}};
static void cont__compiler__identifier__annotate_expression_33(void);
static NODE *func__compiler__identifier__annotate_expression_34;
static void entry__compiler__identifier__annotate_expression_34(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_34 = {3, {"info", "name", "self"}};
static void cont__compiler__identifier__annotate_expression_35(void);
static NODE *func__compiler__identifier__annotate_expression_36;
static void entry__compiler__identifier__annotate_expression_36(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_36 = {1, {"info"}};
static void cont__compiler__identifier__annotate_expression_37(void);
static void cont__compiler__identifier__annotate_expression_38(void);
static void cont__compiler__identifier__annotate_expression_39(void);
static NODE *func__compiler__identifier__annotate_expression_40;
static void entry__compiler__identifier__annotate_expression_40(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_40 = {2, {"name", "self"}};
static void cont__compiler__identifier__annotate_expression_41(void);
static NODE *func__compiler__identifier__annotate_expression_42;
static void entry__compiler__identifier__annotate_expression_42(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_42 = {3, {"info", "self", "name"}};
static void cont__compiler__identifier__annotate_expression_43(void);
static void cont__compiler__identifier__annotate_expression_44(void);
static NODE *func__compiler__identifier__annotate_expression_45;
static void entry__compiler__identifier__annotate_expression_45(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_45 = {2, {"self", "name"}};
static void cont__compiler__identifier__annotate_expression_46(void);
static NODE *func__compiler__identifier__annotate_expression_47;
static void entry__compiler__identifier__annotate_expression_47(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_47 = {3, {"info", "name", "self"}};
static void cont__compiler__identifier__annotate_expression_48(void);
static NODE *func__compiler__identifier__annotate_expression_49;
static void entry__compiler__identifier__annotate_expression_49(void);
static FRAME_INFO frame__compiler__identifier__annotate_expression_49 = {2, {"name", "self"}};
static void cont__compiler__identifier__annotate_expression_50(void);
static void cont__compiler__identifier___annotate_expression_51(void);
void run__annotator(void);

static CONTINUATION_INFO continuation_info[] = {
  {type__compiler__annotate_statement, NULL, 34, 34, 2, 29},
  {type__compiler__annotate_expression, NULL, 35, 35, 2, 30},
  {run__annotator, NULL, 31, 31, 1, 28},
  {entry__annotate_arguments_5, NULL, 40, 40, 37, 53},
  {entry__annotate_arguments_14, NULL, 46, 46, 28, 52},
  {cont__annotate_arguments_15, &frame__annotate_arguments_14, 46, 46, 15, 55},
  {cont__annotate_arguments_16, &frame__annotate_arguments_14, 46, 46, 55, 55},
  {entry__annotate_arguments_17, NULL, 48, 48, 15, 50},
  {cont__annotate_arguments_18, &frame__annotate_arguments_17, 48, 48, 50, 50},
  {entry__annotate_arguments_12, NULL, 45, 45, 13, 46},
  {cont__annotate_arguments_13, &frame__annotate_arguments_12, 44, 48, 11, 51},
  {entry__annotate_arguments_10, NULL, 43, 43, 18, 47},
  {cont__annotate_arguments_11, &frame__annotate_arguments_10, 43, 48, 15, 52},
  {entry__annotate_arguments_9, NULL, 43, 48, 9, 52},
  {cont__annotate_arguments_19, &frame__annotate_arguments_9, 49, 49, 9, 42},
  {cont__annotate_arguments_20, &frame__annotate_arguments_9, 50, 50, 9, 29},
  {cont__annotate_arguments_21, &frame__annotate_arguments_9, 50, 50, 34, 34},
  {entry__annotate_arguments_7, NULL, 42, 42, 14, 40},
  {cont__annotate_arguments_8, &frame__annotate_arguments_7, 42, 50, 7, 34},
  {entry__annotate_arguments_2, NULL, 39, 39, 5, 33},
  {cont__annotate_arguments_3, &frame__annotate_arguments_2, 40, 40, 8, 32},
  {cont__annotate_arguments_4, &frame__annotate_arguments_2, 40, 40, 8, 53},
  {cont__annotate_arguments_6, &frame__annotate_arguments_2, 40, 50, 5, 35},
  {cont__annotate_arguments_22, &frame__annotate_arguments_2, },
  {entry__annotate_arguments, NULL, 38, 50, 3, 36},
  {cont__annotate_arguments_23, &frame__annotate_arguments, 50, 50, 37, 37},
  {entry__types__grammar_node___annotate_statement, NULL, 56, 56, 3, 47},
  {cont__types__grammar_node___annotate_statement_3, &frame__types__grammar_node___annotate_statement, },
  {entry__types__grammar_node___annotate_expression, NULL, 59, 59, 3, 48},
  {cont__types__grammar_node___annotate_expression_3, &frame__types__grammar_node___annotate_expression, },
  {entry__compiler__check_definitions_11, NULL, 73, 74, 32, 63},
  {cont__compiler__check_definitions_14, &frame__compiler__check_definitions_11, 73, 74, 13, 63},
  {entry__compiler__check_definitions_9, NULL, 72, 72, 18, 39},
  {cont__compiler__check_definitions_10, &frame__compiler__check_definitions_9, 72, 74, 11, 64},
  {entry__compiler__check_definitions_21, NULL, 80, 80, 19, 38},
  {cont__compiler__check_definitions_22, &frame__compiler__check_definitions_21, 80, 80, 15, 39},
  {cont__compiler__check_definitions_23, &frame__compiler__check_definitions_21, 80, 80, 15, 39},
  {entry__compiler__check_definitions_17, NULL, 79, 79, 15, 37},
  {cont__compiler__check_definitions_18, &frame__compiler__check_definitions_17, 79, 79, 15, 57},
  {cont__compiler__check_definitions_19, &frame__compiler__check_definitions_17, 79, 79, 15, 57},
  {cont__compiler__check_definitions_20, &frame__compiler__check_definitions_17, 80, 80, 15, 39},
  {cont__compiler__check_definitions_24, &frame__compiler__check_definitions_17, },
  {entry__compiler__check_definitions_26, NULL, 82, 84, 34, 50},
  {cont__compiler__check_definitions_28, &frame__compiler__check_definitions_26, 82, 84, 15, 50},
  {entry__compiler__check_definitions_15, NULL, 78, 78, 15, 47},
  {cont__compiler__check_definitions_16, &frame__compiler__check_definitions_15, },
  {cont__compiler__check_definitions_25, &frame__compiler__check_definitions_15, 76, 84, 11, 52},
  {entry__compiler__check_definitions_6, NULL, 71, 71, 9, 24},
  {cont__compiler__check_definitions_7, &frame__compiler__check_definitions_6, 71, 71, 9, 37},
  {cont__compiler__check_definitions_8, &frame__compiler__check_definitions_6, 70, 84, 7, 54},
  {entry__compiler__check_definitions_2, NULL, 68, 68, 5, 35},
  {cont__compiler__check_definitions_3, &frame__compiler__check_definitions_2, 69, 69, 12, 35},
  {cont__compiler__check_definitions_4, &frame__compiler__check_definitions_2, 69, 69, 12, 46},
  {cont__compiler__check_definitions_5, &frame__compiler__check_definitions_2, 69, 84, 5, 55},
  {entry__compiler__check_definitions_34, NULL, 88, 88, 31, 57},
  {cont__compiler__check_definitions_35, &frame__compiler__check_definitions_34, 88, 88, 31, 69},
  {cont__compiler__check_definitions_36, &frame__compiler__check_definitions_34, 88, 88, 31, 69},
  {entry__compiler__check_definitions_38, NULL, 89, 89, 17, 35},
  {cont__compiler__check_definitions_39, &frame__compiler__check_definitions_38, 89, 91, 37, 15},
  {cont__compiler__check_definitions_42, &frame__compiler__check_definitions_38, 89, 91, 9, 15},
  {entry__compiler__check_definitions_33, NULL, 88, 88, 10, 69},
  {cont__compiler__check_definitions_37, &frame__compiler__check_definitions_33, 88, 91, 7, 16},
  {entry__compiler__check_definitions_30, NULL, 86, 86, 5, 37},
  {cont__compiler__check_definitions_31, &frame__compiler__check_definitions_30, 87, 87, 8, 30},
  {cont__compiler__check_definitions_32, &frame__compiler__check_definitions_30, 87, 91, 5, 17},
  {entry__compiler__check_definitions, NULL, 67, 84, 3, 56},
  {cont__compiler__check_definitions_29, &frame__compiler__check_definitions, 85, 91, 3, 18},
  {entry__compiler__body__annotate_expression_10, NULL, 106, 106, 42, 68},
  {cont__compiler__body__annotate_expression_11, &frame__compiler__body__annotate_expression_10, 106, 106, 42, 79},
  {cont__compiler__body__annotate_expression_12, &frame__compiler__body__annotate_expression_10, 106, 106, 42, 79},
  {entry__compiler__body__annotate_expression_14, NULL, 108, 108, 32, 57},
  {cont__compiler__body__annotate_expression_15, &frame__compiler__body__annotate_expression_14, 108, 108, 11, 57},
  {cont__compiler__body__annotate_expression_16, &frame__compiler__body__annotate_expression_14, 108, 108, 57, 57},
  {entry__compiler__body__annotate_expression_7, NULL, 104, 104, 7, 35},
  {cont__compiler__body__annotate_expression_8, &frame__compiler__body__annotate_expression_7, 106, 106, 9, 37},
  {cont__compiler__body__annotate_expression_9, &frame__compiler__body__annotate_expression_7, 106, 106, 9, 79},
  {cont__compiler__body__annotate_expression_13, &frame__compiler__body__annotate_expression_7, 105, 108, 7, 58},
  {cont__compiler__body__annotate_expression_17, &frame__compiler__body__annotate_expression_7, },
  {entry__compiler__body__annotate_expression_20, NULL, 109, 109, 46, 69},
  {cont__compiler__body__annotate_expression_21, &frame__compiler__body__annotate_expression_20, 109, 109, 69, 69},
  {entry__compiler__body__annotate_expression_30, NULL, 117, 117, 56, 74},
  {cont__compiler__body__annotate_expression_31, &frame__compiler__body__annotate_expression_30, 116, 118, 31, 32},
  {cont__compiler__body__annotate_expression_34, &frame__compiler__body__annotate_expression_30, 116, 118, 13, 32},
  {entry__compiler__body__annotate_expression_39, NULL, 121, 123, 31, 16},
  {cont__compiler__body__annotate_expression_42, &frame__compiler__body__annotate_expression_39, 121, 123, 13, 16},
  {entry__compiler__body__annotate_expression_26, NULL, 114, 114, 11, 36},
  {cont__compiler__body__annotate_expression_27, &frame__compiler__body__annotate_expression_26, 115, 115, 14, 32},
  {cont__compiler__body__annotate_expression_28, &frame__compiler__body__annotate_expression_26, 115, 115, 14, 43},
  {cont__compiler__body__annotate_expression_29, &frame__compiler__body__annotate_expression_26, 115, 118, 11, 33},
  {cont__compiler__body__annotate_expression_35, &frame__compiler__body__annotate_expression_26, 119, 119, 11, 30},
  {cont__compiler__body__annotate_expression_36, &frame__compiler__body__annotate_expression_26, 120, 120, 14, 36},
  {cont__compiler__body__annotate_expression_37, &frame__compiler__body__annotate_expression_26, 120, 120, 14, 47},
  {cont__compiler__body__annotate_expression_38, &frame__compiler__body__annotate_expression_26, 120, 123, 11, 17},
  {cont__compiler__body__annotate_expression_43, &frame__compiler__body__annotate_expression_26, 124, 124, 11, 34},
  {cont__compiler__body__annotate_expression_44, &frame__compiler__body__annotate_expression_26, 124, 124, 39, 39},
  {entry__compiler__body__annotate_expression_46, NULL, 126, 126, 39, 57},
  {cont__compiler__body__annotate_expression_47, &frame__compiler__body__annotate_expression_46, 126, 126, 23, 58},
  {cont__compiler__body__annotate_expression_48, &frame__compiler__body__annotate_expression_46, 126, 126, 11, 59},
  {cont__compiler__body__annotate_expression_49, &frame__compiler__body__annotate_expression_46, 126, 126, 64, 64},
  {entry__compiler__body__annotate_expression_23, NULL, 112, 112, 12, 33},
  {cont__compiler__body__annotate_expression_24, &frame__compiler__body__annotate_expression_23, 113, 113, 9, 35},
  {cont__compiler__body__annotate_expression_25, &frame__compiler__body__annotate_expression_23, 125, 125, 9, 37},
  {cont__compiler__body__annotate_expression_45, &frame__compiler__body__annotate_expression_23, 112, 126, 7, 65},
  {entry__compiler__body__annotate_expression_54, NULL, 135, 135, 41, 41},
  {cont__compiler__body__annotate_expression_55, &frame__compiler__body__annotate_expression_54, 135, 135, 29, 42},
  {cont__compiler__body__annotate_expression_56, &frame__compiler__body__annotate_expression_54, 135, 135, 11, 43},
  {cont__compiler__body__annotate_expression_57, &frame__compiler__body__annotate_expression_54, 135, 135, 11, 69},
  {cont__compiler__body__annotate_expression_58, &frame__compiler__body__annotate_expression_54, 135, 135, 11, 69},
  {cont__compiler__body__annotate_expression_59, &frame__compiler__body__annotate_expression_54, 135, 135, 11, 69},
  {entry__compiler__body__annotate_expression_61, NULL, 137, 137, 39, 56},
  {cont__compiler__body__annotate_expression_63, &frame__compiler__body__annotate_expression_61, 138, 138, 11, 20},
  {cont__compiler__body__annotate_expression_64, &frame__compiler__body__annotate_expression_61, 140, 140, 14, 31},
  {cont__compiler__body__annotate_expression_65, &frame__compiler__body__annotate_expression_61, 139, 143, 11, 56},
  {cont__compiler__body__annotate_expression_66, &frame__compiler__body__annotate_expression_61, 143, 143, 57, 57},
  {entry__compiler__body__annotate_expression_51, NULL, 131, 131, 7, 37},
  {cont__compiler__body__annotate_expression_52, &frame__compiler__body__annotate_expression_51, 134, 134, 11, 29},
  {cont__compiler__body__annotate_expression_53, &frame__compiler__body__annotate_expression_51, 133, 135, 9, 69},
  {cont__compiler__body__annotate_expression_60, &frame__compiler__body__annotate_expression_51, 132, 143, 7, 58},
  {entry__compiler__body__annotate_expression_68, NULL, 145, 145, 7, 52},
  {cont__compiler__body__annotate_expression_69, &frame__compiler__body__annotate_expression_68, 146, 146, 44, 44},
  {entry__compiler__body__annotate_expression_4, NULL, 102, 102, 5, 24},
  {cont__compiler__body__annotate_expression_5, &frame__compiler__body__annotate_expression_4, 103, 103, 18, 35},
  {cont__compiler__body__annotate_expression_6, &frame__compiler__body__annotate_expression_4, 103, 108, 5, 59},
  {cont__compiler__body__annotate_expression_18, &frame__compiler__body__annotate_expression_4, 109, 109, 18, 35},
  {cont__compiler__body__annotate_expression_19, &frame__compiler__body__annotate_expression_4, 109, 109, 5, 69},
  {cont__compiler__body__annotate_expression_22, &frame__compiler__body__annotate_expression_4, 111, 126, 5, 66},
  {cont__compiler__body__annotate_expression_50, &frame__compiler__body__annotate_expression_4, 129, 143, 5, 59},
  {cont__compiler__body__annotate_expression_67, &frame__compiler__body__annotate_expression_4, 144, 146, 5, 44},
  {cont__compiler__body__annotate_expression_70, &frame__compiler__body__annotate_expression_4, 146, 146, 44, 44},
  {entry__compiler__body__annotate_expression_81, NULL, 150, 150, 35, 51},
  {cont__compiler__body__annotate_expression_82, &frame__compiler__body__annotate_expression_81, 150, 150, 64, 64},
  {entry__compiler__body__annotate_expression_77, NULL, 149, 149, 38, 53},
  {cont__compiler__body__annotate_expression_78, &frame__compiler__body__annotate_expression_77, 149, 149, 7, 59},
  {cont__compiler__body__annotate_expression_79, &frame__compiler__body__annotate_expression_77, 150, 150, 10, 32},
  {cont__compiler__body__annotate_expression_80, &frame__compiler__body__annotate_expression_77, 150, 150, 7, 64},
  {entry__compiler__body__annotate_expression_73, NULL, 148, 148, 12, 33},
  {cont__compiler__body__annotate_expression_74, &frame__compiler__body__annotate_expression_73, 148, 148, 12, 39},
  {cont__compiler__body__annotate_expression_75, &frame__compiler__body__annotate_expression_73, 148, 148, 12, 50},
  {cont__compiler__body__annotate_expression_76, &frame__compiler__body__annotate_expression_73, 148, 150, 5, 64},
  {entry__compiler__body__annotate_expression_85, NULL, 152, 152, 45, 65},
  {cont__compiler__body__annotate_expression_86, &frame__compiler__body__annotate_expression_85, 152, 152, 70, 70},
  {entry__compiler__body__annotate_expression_84, NULL, 152, 152, 5, 70},
  {entry__compiler__body___annotate_expression, NULL, 94, 94, 3, 42},
  {cont__compiler__body___annotate_expression_3, &frame__compiler__body___annotate_expression, 97, 146, 3, 45},
  {cont__compiler__body___annotate_expression_71, &frame__compiler__body___annotate_expression, 147, 147, 12, 30},
  {cont__compiler__body___annotate_expression_72, &frame__compiler__body___annotate_expression, 147, 150, 3, 65},
  {cont__compiler__body___annotate_expression_83, &frame__compiler__body___annotate_expression, 151, 152, 3, 70},
  {cont__compiler__body___annotate_expression_87, &frame__compiler__body___annotate_expression, },
  {entry__compiler__call__annotate_statement_8, NULL, 162, 162, 30, 49},
  {cont__compiler__call__annotate_statement_9, &frame__compiler__call__annotate_statement_8, 162, 162, 9, 49},
  {cont__compiler__call__annotate_statement_10, &frame__compiler__call__annotate_statement_8, 162, 162, 49, 49},
  {entry__compiler__call__annotate_statement_14, NULL, 164, 164, 30, 49},
  {cont__compiler__call__annotate_statement_15, &frame__compiler__call__annotate_statement_14, 164, 164, 9, 49},
  {cont__compiler__call__annotate_statement_16, &frame__compiler__call__annotate_statement_14, 164, 164, 49, 49},
  {entry__compiler__call__annotate_statement_5, NULL, 161, 161, 10, 30},
  {cont__compiler__call__annotate_statement_6, &frame__compiler__call__annotate_statement_5, 161, 161, 10, 41},
  {cont__compiler__call__annotate_statement_7, &frame__compiler__call__annotate_statement_5, 161, 162, 7, 49},
  {cont__compiler__call__annotate_statement_11, &frame__compiler__call__annotate_statement_5, 163, 163, 10, 30},
  {cont__compiler__call__annotate_statement_12, &frame__compiler__call__annotate_statement_5, 163, 163, 10, 41},
  {cont__compiler__call__annotate_statement_13, &frame__compiler__call__annotate_statement_5, 163, 164, 7, 49},
  {cont__compiler__call__annotate_statement_17, &frame__compiler__call__annotate_statement_5, 165, 165, 28, 42},
  {cont__compiler__call__annotate_statement_18, &frame__compiler__call__annotate_statement_5, 165, 165, 7, 42},
  {cont__compiler__call__annotate_statement_19, &frame__compiler__call__annotate_statement_5, 165, 165, 42, 42},
  {entry__compiler__call__annotate_statement_30, NULL, 173, 173, 33, 42},
  {cont__compiler__call__annotate_statement_31, &frame__compiler__call__annotate_statement_30, 173, 173, 33, 42},
  {entry__compiler__call__annotate_statement_35, NULL, 174, 174, 35, 44},
  {cont__compiler__call__annotate_statement_36, &frame__compiler__call__annotate_statement_35, 174, 174, 35, 44},
  {entry__compiler__call__annotate_statement_33, NULL, 174, 174, 13, 30},
  {cont__compiler__call__annotate_statement_34, &frame__compiler__call__annotate_statement_33, 174, 174, 13, 44},
  {cont__compiler__call__annotate_statement_37, &frame__compiler__call__annotate_statement_33, 174, 174, 13, 44},
  {entry__compiler__call__annotate_statement_28, NULL, 173, 173, 13, 28},
  {cont__compiler__call__annotate_statement_29, &frame__compiler__call__annotate_statement_28, 173, 173, 13, 42},
  {cont__compiler__call__annotate_statement_32, &frame__compiler__call__annotate_statement_28, 174, 174, 13, 44},
  {cont__compiler__call__annotate_statement_38, &frame__compiler__call__annotate_statement_28, },
  {entry__compiler__call__annotate_statement_49, NULL, 181, 181, 45, 70},
  {cont__compiler__call__annotate_statement_50, &frame__compiler__call__annotate_statement_49, 181, 181, 32, 71},
  {cont__compiler__call__annotate_statement_52, &frame__compiler__call__annotate_statement_49, 181, 181, 19, 71},
  {cont__compiler__call__annotate_statement_53, &frame__compiler__call__annotate_statement_49, 181, 181, 71, 71},
  {entry__compiler__call__annotate_statement_54, NULL, 183, 183, 32, 49},
  {cont__compiler__call__annotate_statement_56, &frame__compiler__call__annotate_statement_54, 183, 183, 19, 49},
  {cont__compiler__call__annotate_statement_57, &frame__compiler__call__annotate_statement_54, 183, 183, 49, 49},
  {entry__compiler__call__annotate_statement_46, NULL, 178, 178, 15, 50},
  {cont__compiler__call__annotate_statement_47, &frame__compiler__call__annotate_statement_46, 180, 180, 17, 36},
  {cont__compiler__call__annotate_statement_48, &frame__compiler__call__annotate_statement_46, 179, 183, 15, 50},
  {entry__compiler__call__annotate_statement_40, NULL, 176, 176, 36, 61},
  {cont__compiler__call__annotate_statement_41, &frame__compiler__call__annotate_statement_40, 176, 176, 13, 62},
  {cont__compiler__call__annotate_statement_42, &frame__compiler__call__annotate_statement_40, 177, 177, 16, 45},
  {cont__compiler__call__annotate_statement_43, &frame__compiler__call__annotate_statement_40, 177, 177, 16, 53},
  {cont__compiler__call__annotate_statement_44, &frame__compiler__call__annotate_statement_40, 177, 177, 16, 53},
  {cont__compiler__call__annotate_statement_45, &frame__compiler__call__annotate_statement_40, 177, 183, 13, 51},
  {cont__compiler__call__annotate_statement_58, &frame__compiler__call__annotate_statement_40, 184, 184, 14, 30},
  {cont__compiler__call__annotate_statement_59, &frame__compiler__call__annotate_statement_40, 184, 184, 14, 33},
  {cont__compiler__call__annotate_statement_60, &frame__compiler__call__annotate_statement_40, 184, 184, 13, 33},
  {cont__compiler__call__annotate_statement_61, &frame__compiler__call__annotate_statement_40, 184, 184, 46, 46},
  {entry__compiler__call__annotate_statement_24, NULL, 169, 169, 17, 34},
  {cont__compiler__call__annotate_statement_25, &frame__compiler__call__annotate_statement_24, 169, 169, 9, 37},
  {cont__compiler__call__annotate_statement_26, &frame__compiler__call__annotate_statement_24, 172, 172, 13, 44},
  {cont__compiler__call__annotate_statement_27, &frame__compiler__call__annotate_statement_24, },
  {cont__compiler__call__annotate_statement_39, &frame__compiler__call__annotate_statement_24, 170, 184, 9, 47},
  {entry__compiler__call__annotate_statement_20, NULL, 167, 167, 20, 37},
  {cont__compiler__call__annotate_statement_21, &frame__compiler__call__annotate_statement_20, 167, 167, 7, 40},
  {cont__compiler__call__annotate_statement_22, &frame__compiler__call__annotate_statement_20, 168, 168, 10, 36},
  {cont__compiler__call__annotate_statement_23, &frame__compiler__call__annotate_statement_20, 168, 184, 7, 48},
  {entry__compiler__call___annotate_statement, NULL, 158, 158, 3, 47},
  {cont__compiler__call___annotate_statement_2, &frame__compiler__call___annotate_statement, 160, 160, 5, 20},
  {cont__compiler__call___annotate_statement_3, &frame__compiler__call___annotate_statement, 160, 160, 5, 31},
  {cont__compiler__call___annotate_statement_4, &frame__compiler__call___annotate_statement, 159, 184, 3, 50},
  {cont__compiler__call___annotate_statement_62, &frame__compiler__call___annotate_statement, 185, 185, 23, 39},
  {cont__compiler__call___annotate_statement_63, &frame__compiler__call___annotate_statement, 185, 185, 3, 39},
  {cont__compiler__call___annotate_statement_64, &frame__compiler__call___annotate_statement, 185, 185, 39, 39},
  {entry__compiler__c_code__annotate_statement_8, NULL, 193, 195, 5, 79},
  {cont__compiler__c_code__annotate_statement_9, &frame__compiler__c_code__annotate_statement_8, 195, 195, 80, 80},
  {entry__compiler__c_code__annotate_statement_13, NULL, 196, 196, 53, 64},
  {cont__compiler__c_code__annotate_statement_14, &frame__compiler__c_code__annotate_statement_13, 196, 196, 32, 64},
  {cont__compiler__c_code__annotate_statement_15, &frame__compiler__c_code__annotate_statement_13, 196, 196, 64, 64},
  {entry__compiler__c_code___annotate_statement, NULL, 191, 191, 3, 44},
  {cont__compiler__c_code___annotate_statement_3, &frame__compiler__c_code___annotate_statement, 192, 192, 8, 20},
  {cont__compiler__c_code___annotate_statement_4, &frame__compiler__c_code___annotate_statement, 192, 192, 22, 37},
  {cont__compiler__c_code___annotate_statement_7, &frame__compiler__c_code___annotate_statement, 192, 195, 3, 80},
  {cont__compiler__c_code___annotate_statement_10, &frame__compiler__c_code___annotate_statement, 196, 196, 6, 18},
  {cont__compiler__c_code___annotate_statement_11, &frame__compiler__c_code___annotate_statement, 196, 196, 6, 29},
  {cont__compiler__c_code___annotate_statement_12, &frame__compiler__c_code___annotate_statement, 196, 196, 3, 64},
  {cont__compiler__c_code___annotate_statement_16, &frame__compiler__c_code___annotate_statement, },
  {entry__compiler__define_static_single__annotate_expression_6, NULL, 205, 205, 7, 30},
  {cont__compiler__define_static_single__annotate_expression_7, &frame__compiler__define_static_single__annotate_expression_6, 205, 205, 30, 30},
  {entry__compiler__define_static_single__annotate_expression_11, NULL, 207, 207, 62, 78},
  {cont__compiler__define_static_single__annotate_expression_12, &frame__compiler__define_static_single__annotate_expression_11, 207, 207, 41, 78},
  {cont__compiler__define_static_single__annotate_expression_13, &frame__compiler__define_static_single__annotate_expression_11, 207, 207, 78, 78},
  {entry__compiler__define_static_single__annotate_expression_8, NULL, 207, 207, 10, 27},
  {cont__compiler__define_static_single__annotate_expression_9, &frame__compiler__define_static_single__annotate_expression_8, 207, 207, 10, 38},
  {cont__compiler__define_static_single__annotate_expression_10, &frame__compiler__define_static_single__annotate_expression_8, 207, 207, 7, 78},
  {cont__compiler__define_static_single__annotate_expression_14, &frame__compiler__define_static_single__annotate_expression_8, 208, 208, 28, 45},
  {cont__compiler__define_static_single__annotate_expression_15, &frame__compiler__define_static_single__annotate_expression_8, 208, 208, 7, 45},
  {cont__compiler__define_static_single__annotate_expression_16, &frame__compiler__define_static_single__annotate_expression_8, 208, 208, 45, 45},
  {entry__compiler__define_static_single___annotate_expression, NULL, 202, 202, 3, 58},
  {cont__compiler__define_static_single___annotate_expression_3, &frame__compiler__define_static_single___annotate_expression, 204, 204, 5, 27},
  {cont__compiler__define_static_single___annotate_expression_4, &frame__compiler__define_static_single___annotate_expression, 204, 204, 5, 35},
  {cont__compiler__define_static_single___annotate_expression_5, &frame__compiler__define_static_single___annotate_expression, 203, 208, 3, 46},
  {cont__compiler__define_static_single___annotate_expression_17, &frame__compiler__define_static_single___annotate_expression, },
  {entry__compiler__define_static_multi___annotate_expression, NULL, 214, 214, 3, 57},
  {cont__compiler__define_static_multi___annotate_expression_3, &frame__compiler__define_static_multi___annotate_expression, 215, 215, 3, 26},
  {cont__compiler__define_static_multi___annotate_expression_4, &frame__compiler__define_static_multi___annotate_expression, 215, 215, 26, 26},
  {entry__compiler__define_dynamic_single___annotate_expression, NULL, 221, 221, 3, 59},
  {cont__compiler__define_dynamic_single___annotate_expression_3, &frame__compiler__define_dynamic_single___annotate_expression, 223, 223, 3, 26},
  {cont__compiler__define_dynamic_single___annotate_expression_4, &frame__compiler__define_dynamic_single___annotate_expression, 223, 223, 26, 26},
  {entry__compiler__define_dynamic_multi___annotate_expression, NULL, 229, 229, 3, 58},
  {cont__compiler__define_dynamic_multi___annotate_expression_3, &frame__compiler__define_dynamic_multi___annotate_expression, 231, 231, 3, 26},
  {cont__compiler__define_dynamic_multi___annotate_expression_4, &frame__compiler__define_dynamic_multi___annotate_expression, 231, 231, 26, 26},
  {entry__compiler__function_call__annotate_expression_6, NULL, 239, 239, 26, 40},
  {cont__compiler__function_call__annotate_expression_7, &frame__compiler__function_call__annotate_expression_6, 239, 239, 5, 40},
  {cont__compiler__function_call__annotate_expression_8, &frame__compiler__function_call__annotate_expression_6, 240, 240, 25, 41},
  {cont__compiler__function_call__annotate_expression_9, &frame__compiler__function_call__annotate_expression_6, 240, 240, 5, 41},
  {cont__compiler__function_call__annotate_expression_10, &frame__compiler__function_call__annotate_expression_6, 240, 240, 41, 41},
  {entry__compiler__function_call___annotate_expression, NULL, 237, 237, 3, 51},
  {cont__compiler__function_call___annotate_expression_3, &frame__compiler__function_call___annotate_expression, 238, 238, 6, 21},
  {cont__compiler__function_call___annotate_expression_4, &frame__compiler__function_call___annotate_expression, 238, 238, 6, 32},
  {cont__compiler__function_call___annotate_expression_5, &frame__compiler__function_call___annotate_expression, 238, 240, 3, 41},
  {cont__compiler__function_call___annotate_expression_11, &frame__compiler__function_call___annotate_expression, },
  {entry__compiler__attribute_value_pair___annotate_expression, NULL, 246, 246, 3, 58},
  {cont__compiler__attribute_value_pair___annotate_expression_3, &frame__compiler__attribute_value_pair___annotate_expression, 247, 247, 24, 41},
  {cont__compiler__attribute_value_pair___annotate_expression_4, &frame__compiler__attribute_value_pair___annotate_expression, 247, 247, 3, 41},
  {cont__compiler__attribute_value_pair___annotate_expression_5, &frame__compiler__attribute_value_pair___annotate_expression, 248, 248, 23, 39},
  {cont__compiler__attribute_value_pair___annotate_expression_6, &frame__compiler__attribute_value_pair___annotate_expression, 248, 248, 3, 39},
  {cont__compiler__attribute_value_pair___annotate_expression_7, &frame__compiler__attribute_value_pair___annotate_expression, 248, 248, 39, 39},
  {entry__compiler__attribute_function_pair__annotate_expression_6, NULL, 255, 255, 59, 76},
  {cont__compiler__attribute_function_pair__annotate_expression_7, &frame__compiler__attribute_function_pair__annotate_expression_6, 255, 255, 38, 76},
  {cont__compiler__attribute_function_pair__annotate_expression_8, &frame__compiler__attribute_function_pair__annotate_expression_6, 255, 255, 76, 76},
  {entry__compiler__attribute_function_pair___annotate_expression, NULL, 254, 254, 3, 61},
  {cont__compiler__attribute_function_pair___annotate_expression_3, &frame__compiler__attribute_function_pair___annotate_expression, 255, 255, 6, 24},
  {cont__compiler__attribute_function_pair___annotate_expression_4, &frame__compiler__attribute_function_pair___annotate_expression, 255, 255, 6, 35},
  {cont__compiler__attribute_function_pair___annotate_expression_5, &frame__compiler__attribute_function_pair___annotate_expression, 255, 255, 3, 76},
  {cont__compiler__attribute_function_pair___annotate_expression_9, &frame__compiler__attribute_function_pair___annotate_expression, 256, 256, 23, 39},
  {cont__compiler__attribute_function_pair___annotate_expression_10, &frame__compiler__attribute_function_pair___annotate_expression, 256, 256, 3, 39},
  {cont__compiler__attribute_function_pair___annotate_expression_11, &frame__compiler__attribute_function_pair___annotate_expression, 256, 256, 39, 39},
  {entry__compiler__identifier__annotate_expression_11, NULL, 267, 267, 73, 73},
  {entry__compiler__identifier__annotate_expression_8, NULL, 266, 266, 7, 53},
  {cont__compiler__identifier__annotate_expression_9, &frame__compiler__identifier__annotate_expression_8, 267, 267, 10, 36},
  {cont__compiler__identifier__annotate_expression_10, &frame__compiler__identifier__annotate_expression_8, 267, 267, 7, 73},
  {entry__compiler__identifier__annotate_expression_19, NULL, 273, 273, 32, 53},
  {cont__compiler__identifier__annotate_expression_20, &frame__compiler__identifier__annotate_expression_19, 273, 273, 32, 70},
  {cont__compiler__identifier__annotate_expression_21, &frame__compiler__identifier__annotate_expression_19, 273, 273, 32, 70},
  {entry__compiler__identifier__annotate_expression_23, NULL, 274, 274, 13, 29},
  {cont__compiler__identifier__annotate_expression_24, &frame__compiler__identifier__annotate_expression_23, 277, 277, 48, 48},
  {entry__compiler__identifier__annotate_expression_28, NULL, 280, 281, 32, 62},
  {cont__compiler__identifier__annotate_expression_31, &frame__compiler__identifier__annotate_expression_28, 280, 281, 15, 62},
  {entry__compiler__identifier__annotate_expression_25, NULL, 279, 279, 16, 37},
  {cont__compiler__identifier__annotate_expression_26, &frame__compiler__identifier__annotate_expression_25, 279, 279, 16, 52},
  {cont__compiler__identifier__annotate_expression_27, &frame__compiler__identifier__annotate_expression_25, 279, 281, 13, 63},
  {entry__compiler__identifier__annotate_expression_17, NULL, 273, 273, 11, 27},
  {cont__compiler__identifier__annotate_expression_18, &frame__compiler__identifier__annotate_expression_17, 273, 273, 11, 70},
  {cont__compiler__identifier__annotate_expression_22, &frame__compiler__identifier__annotate_expression_17, 272, 281, 9, 65},
  {entry__compiler__identifier__annotate_expression_15, NULL, 271, 271, 10, 38},
  {cont__compiler__identifier__annotate_expression_16, &frame__compiler__identifier__annotate_expression_15, 271, 281, 7, 66},
  {entry__compiler__identifier__annotate_expression_36, NULL, 284, 284, 32, 53},
  {cont__compiler__identifier__annotate_expression_37, &frame__compiler__identifier__annotate_expression_36, 284, 284, 32, 70},
  {cont__compiler__identifier__annotate_expression_38, &frame__compiler__identifier__annotate_expression_36, 284, 284, 32, 70},
  {entry__compiler__identifier__annotate_expression_40, NULL, 285, 285, 13, 29},
  {cont__compiler__identifier__annotate_expression_41, &frame__compiler__identifier__annotate_expression_40, 288, 288, 47, 47},
  {entry__compiler__identifier__annotate_expression_45, NULL, 291, 292, 32, 62},
  {cont__compiler__identifier__annotate_expression_46, &frame__compiler__identifier__annotate_expression_45, 291, 292, 15, 62},
  {entry__compiler__identifier__annotate_expression_42, NULL, 290, 290, 20, 41},
  {cont__compiler__identifier__annotate_expression_43, &frame__compiler__identifier__annotate_expression_42, 290, 290, 20, 56},
  {cont__compiler__identifier__annotate_expression_44, &frame__compiler__identifier__annotate_expression_42, 290, 292, 13, 63},
  {entry__compiler__identifier__annotate_expression_34, NULL, 284, 284, 11, 27},
  {cont__compiler__identifier__annotate_expression_35, &frame__compiler__identifier__annotate_expression_34, 284, 284, 11, 70},
  {cont__compiler__identifier__annotate_expression_39, &frame__compiler__identifier__annotate_expression_34, 283, 292, 9, 65},
  {entry__compiler__identifier__annotate_expression_32, NULL, 282, 282, 10, 47},
  {cont__compiler__identifier__annotate_expression_33, &frame__compiler__identifier__annotate_expression_32, 282, 292, 7, 66},
  {entry__compiler__identifier__annotate_expression_49, NULL, 295, 295, 11, 27},
  {cont__compiler__identifier__annotate_expression_50, &frame__compiler__identifier__annotate_expression_49, 298, 298, 47, 47},
  {entry__compiler__identifier__annotate_expression_47, NULL, 294, 294, 12, 28},
  {cont__compiler__identifier__annotate_expression_48, &frame__compiler__identifier__annotate_expression_47, 294, 298, 9, 47},
  {entry__compiler__identifier__annotate_expression_5, NULL, 264, 264, 5, 33},
  {cont__compiler__identifier__annotate_expression_6, &frame__compiler__identifier__annotate_expression_5, 265, 265, 8, 27},
  {cont__compiler__identifier__annotate_expression_7, &frame__compiler__identifier__annotate_expression_5, 265, 267, 5, 73},
  {cont__compiler__identifier__annotate_expression_12, &frame__compiler__identifier__annotate_expression_5, 268, 268, 5, 31},
  {cont__compiler__identifier__annotate_expression_13, &frame__compiler__identifier__annotate_expression_5, 269, 269, 5, 26},
  {cont__compiler__identifier__annotate_expression_14, &frame__compiler__identifier__annotate_expression_5, 270, 298, 5, 49},
  {entry__compiler__identifier___annotate_expression, NULL, 262, 262, 3, 54},
  {cont__compiler__identifier___annotate_expression_3, &frame__compiler__identifier___annotate_expression, 263, 263, 10, 35},
  {cont__compiler__identifier___annotate_expression_4, &frame__compiler__identifier___annotate_expression, 263, 298, 3, 50},
  {cont__compiler__identifier___annotate_expression_51, &frame__compiler__identifier___annotate_expression, }
};

union NODE {
  struct {
    FUNC type;
    ATTRIBUTES *attributes;
  };
  CONTINUATION continuation;
  CLOSURE closure;
};
static void type__compiler__annotate_statement(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__annotate_statement);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__annotate_statement, attr);
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
static void type__compiler__annotate_expression(void) {
  if (argument_count < 1) {
    too_few_arguments_error();
    return;
  }
  myself = get_attribute(arguments->slots[0], poly_idx__compiler__annotate_expression);
  if (CONTAINS_AN_ATTRIBUTE_VALUE(myself)) {
    if (argument_count != 1) {
      if (argument_count != 2) invalid_arguments_error();
      NODE *attr = arguments->slots[1];
      NODE *temp = clone_object_and_attributes(arguments->slots[0]);
      update_start_p = node_p;
      set_attribute_value(temp->attributes, poly_idx__compiler__annotate_expression, attr);
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
static NODE *number__1;
static NODE *number__2;

static const char *used_namespaces[] = {
  "std",
  "compiler",
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
static void entry__annotate_arguments(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // arguments: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* arguments */ = create_cell_with_contents(arguments->slots[0]);
  // 38: update_each &arguments: (&argument)
  // 39:   annotate_expression &argument
  // 40:   if argument.is_a_destination && do_print_warnings:
  // 41:     $$destination argument
  // 42:     unless destination.is_a_definition:
  // 43:       while -> destination.is_a_function_call:
  // 44:         if
  // 45:           destination.is_an_attribute_access:
  // 46:             !destination arguments_of(destination)(1)
  // 47:           :
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* arguments */;
  arguments->slots[1] = func__annotate_arguments_2;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__annotate_arguments_23;
}
static void entry__annotate_arguments_2(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // argument: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* argument */ = create_cell_with_contents(arguments->slots[0]);
  // 39: annotate_expression &argument
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__annotate_arguments_3;
}
static void cont__annotate_arguments_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[0])->contents /* argument */ = arguments->slots[0];
  // 40: ... argument.is_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* argument */;
  result_count = 1;
  myself = get__is_a_destination();
  func = myself->type;
  frame->cont = cont__annotate_arguments_4;
}
static void cont__annotate_arguments_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 40: ... argument.is_a_destination && do_print_warnings
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__annotate_arguments_5;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__annotate_arguments_6;
}
static void entry__annotate_arguments_5(void) {
  allocate_initialized_frame_gc(0, 0);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 40: ... do_print_warnings
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__annotate_arguments_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 40: ... :
  // 41:   $$destination argument
  // 42:   unless destination.is_a_definition:
  // 43:     while -> destination.is_a_function_call:
  // 44:       if
  // 45:         destination.is_an_attribute_access:
  // 46:           !destination arguments_of(destination)(1)
  // 47:         :
  // 48:           !destination functor_of(destination)
  // 49:     $name mangled_name_of(destination)
  // ...
  frame->slots[3] /* temp__3 */ = create_closure(entry__annotate_arguments_7, 0);
  // 40: if argument.is_a_destination && do_print_warnings:
  // 41:   $$destination argument
  // 42:   unless destination.is_a_definition:
  // 43:     while -> destination.is_a_function_call:
  // 44:       if
  // 45:         destination.is_an_attribute_access:
  // 46:           !destination arguments_of(destination)(1)
  // 47:         :
  // 48:           !destination functor_of(destination)
  // 49:     $name mangled_name_of(destination)
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__annotate_arguments_22;
}
static void entry__annotate_arguments_9(void) {
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
  // 43: ... -> destination.is_a_function_call:
  // 44:   if
  // 45:     destination.is_an_attribute_access:
  // 46:       !destination arguments_of(destination)(1)
  // 47:     :
  // 48:       !destination functor_of(destination)
  frame->slots[2] /* temp__1 */ = create_closure(entry__annotate_arguments_10, 0);
  // 43: while -> destination.is_a_function_call:
  // 44:   if
  // 45:     destination.is_an_attribute_access:
  // 46:       !destination arguments_of(destination)(1)
  // 47:     :
  // 48:       !destination functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__while();
  func = myself->type;
  frame->cont = cont__annotate_arguments_19;
}
static void entry__annotate_arguments_14(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 46: ... arguments_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__annotate_arguments_15;
}
static void cont__annotate_arguments_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 46: !destination arguments_of(destination)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[1] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__annotate_arguments_16;
}
static void cont__annotate_arguments_16(void) {
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
static void entry__annotate_arguments_17(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 48: !destination functor_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__annotate_arguments_18;
}
static void cont__annotate_arguments_18(void) {
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
static void entry__annotate_arguments_12(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 45: destination.is_an_attribute_access
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__is_an_attribute_access();
  func = myself->type;
  frame->cont = cont__annotate_arguments_13;
}
static void cont__annotate_arguments_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 45: ... :
  // 46:   !destination arguments_of(destination)(1)
  frame->slots[2] /* temp__2 */ = create_closure(entry__annotate_arguments_14, 0);
  // 47: :
  // 48:   !destination functor_of(destination)
  frame->slots[3] /* temp__3 */ = create_closure(entry__annotate_arguments_17, 0);
  // 44: if
  // 45:   destination.is_an_attribute_access:
  // 46:     !destination arguments_of(destination)(1)
  // 47:   :
  // 48:     !destination functor_of(destination)
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
static void entry__annotate_arguments_10(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // destination: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 43: ... destination.is_a_function_call
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__is_a_function_call();
  func = myself->type;
  frame->cont = cont__annotate_arguments_11;
}
static void cont__annotate_arguments_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 43: ... :
  // 44:   if
  // 45:     destination.is_an_attribute_access:
  // 46:       !destination arguments_of(destination)(1)
  // 47:     :
  // 48:       !destination functor_of(destination)
  frame->slots[2] /* temp__2 */ = create_closure(entry__annotate_arguments_12, 0);
  // 43: ... -> destination.is_a_function_call:
  // 44:   if
  // 45:     destination.is_an_attribute_access:
  // 46:       !destination arguments_of(destination)(1)
  // 47:     :
  // 48:       !destination functor_of(destination)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__annotate_arguments_19(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 49: $name mangled_name_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* destination */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__annotate_arguments_20;
}
static void cont__annotate_arguments_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* name */, arguments->slots[0]);
  // 50: !assigned_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__annotate_arguments_21;
}
static void cont__annotate_arguments_21(void) {
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
static void entry__annotate_arguments_7(void) {
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
  // 41: $$destination argument
  ((CELL *)frame->slots[1])->contents /* destination */ = ((CELL *)frame->slots[0])->contents /* argument */;
  // 42: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__annotate_arguments_8;
}
static void cont__annotate_arguments_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 42: ... :
  // 43:   while -> destination.is_a_function_call:
  // 44:     if
  // 45:       destination.is_an_attribute_access:
  // 46:         !destination arguments_of(destination)(1)
  // 47:       :
  // 48:         !destination functor_of(destination)
  // 49:   $name mangled_name_of(destination)
  // 50:   !assigned_names(name) true
  frame->slots[3] /* temp__2 */ = create_closure(entry__annotate_arguments_9, 0);
  // 42: unless destination.is_a_definition:
  // 43:   while -> destination.is_a_function_call:
  // 44:     if
  // 45:       destination.is_an_attribute_access:
  // 46:         !destination arguments_of(destination)(1)
  // 47:       :
  // 48:         !destination functor_of(destination)
  // 49:   $name mangled_name_of(destination)
  // 50:   !assigned_names(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__annotate_arguments_22(void) {
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
static void cont__annotate_arguments_23(void) {
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
static void entry__types__grammar_node___annotate_statement(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 56: show_compiler_debug_info "annotate statement"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8a2e321e316b06ed;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node___annotate_statement_3;
}
static void cont__types__grammar_node___annotate_statement_3(void) {
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
static void entry__types__grammar_node___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 59: show_compiler_debug_info "annotate expression"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__bce93a983bb5b33f;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__types__grammar_node___annotate_expression_3;
}
static void cont__types__grammar_node___annotate_expression_3(void) {
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
static void entry__compiler__check_definitions_38(void) {
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
  // 89: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_39;
}
static void cont__compiler__check_definitions_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 89: ... "
  // 90:   attempt to use the identifier "@(name)" that is marked as not being @
  // 91:   used@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__fd0945f8c8a23329;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__27789aef2dccadff;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_42;
}
static void cont__compiler__check_definitions_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 89: Warning identifier_of(info) "
  // 90:   attempt to use the identifier "@(name)" that is marked as not being @
  // 91:   used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_33(void) {
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
  // 88: ... identifier_of(defined_name).is_not_used
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__check_definitions_34, 0);
  // 88: ... do_print_warnings && identifier_of(defined_name).is_not_used
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_37;
}
static void entry__compiler__check_definitions_34(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // defined_name: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* defined_name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 88: ... identifier_of(defined_name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defined_name */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_35;
}
static void cont__compiler__check_definitions_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 88: ... identifier_of(defined_name).is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_36;
}
static void cont__compiler__check_definitions_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 88: ... identifier_of(defined_name).is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__check_definitions_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 88: ... :
  // 89:   Warning identifier_of(info) "
  // 90:     attempt to use the identifier "@(name)" that is marked as not being @
  // 91:     used@
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__check_definitions_38, 0);
  // 88: if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 89:   Warning identifier_of(info) "
  // 90:     attempt to use the identifier "@(name)" that is marked as not being @
  // 91:     used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_30(void) {
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
  // 86: $defined_name defined_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = frame->slots[2] /* defined_names */;
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_31;
}
static void cont__compiler__check_definitions_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* defined_name */, arguments->slots[0]);
  // 87: ... defined_name.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* defined_name */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_32;
}
static void cont__compiler__check_definitions_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 87: ... :
  // 88:   if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 89:     Warning identifier_of(info) "
  // 90:       attempt to use the identifier "@(name)" that is marked as not being @
  // 91:       used@
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__check_definitions_33, 0);
  // 87: if defined_name.is_defined:
  // 88:   if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 89:     Warning identifier_of(info) "
  // 90:       attempt to use the identifier "@(name)" that is marked as not being @
  // 91:       used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions(void) {
  allocate_initialized_frame_gc(2, 3);
  // slot allocations:
  // defined_names: 0
  // used_names: 1
  if (argument_count != 2) {
    invalid_arguments_error();
    return;
  }
  // 67: ... : (name info)
  // 68:   $identifier identifier_of(info)
  // 69:   unless namespace_of(identifier).is_defined:
  // 70:     if
  // 71:       used_names(name).is_undefined:
  // 72:         unless identifier.is_not_used:
  // 73:           Warning identifier "
  // 74:             the identifier "@(name)" is defined but not used@
  // 75:       :
  // 76:         if
  // ...
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__check_definitions_2, 2);
  // 67: for_each defined_names: (name info)
  // 68:   $identifier identifier_of(info)
  // 69:   unless namespace_of(identifier).is_defined:
  // 70:     if
  // 71:       used_names(name).is_undefined:
  // 72:         unless identifier.is_not_used:
  // 73:           Warning identifier "
  // 74:             the identifier "@(name)" is defined but not used@
  // 75:       :
  // 76:         if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* defined_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_29;
}
static void entry__compiler__check_definitions_26(void) {
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
  // 82: ... "
  // 83:   the identifier "@(name)" is defined as a read-write variable, @
  // 84:   but there is no actual assignment@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1f20e521cf7a2a0e;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__6ef85e6a0d2c67a5;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_28;
}
static void cont__compiler__check_definitions_28(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 82: Warning identifier "
  // 83:   the identifier "@(name)" is defined as a read-write variable, @
  // 84:   but there is no actual assignment@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_11(void) {
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
  // 73: ... "
  // 74:   the identifier "@(name)" is defined but not used@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__1f20e521cf7a2a0e;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__e573d863c40ad98e;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_14;
}
static void cont__compiler__check_definitions_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 73: Warning identifier "
  // 74:   the identifier "@(name)" is defined but not used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__Warning();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_9(void) {
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
  // 72: ... identifier.is_not_used
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* identifier */;
  result_count = 1;
  myself = get__is_not_used();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_10;
}
static void cont__compiler__check_definitions_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 72: ... :
  // 73:   Warning identifier "
  // 74:     the identifier "@(name)" is defined but not used@
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__check_definitions_11, 0);
  // 72: unless identifier.is_not_used:
  // 73:   Warning identifier "
  // 74:     the identifier "@(name)" is defined but not used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_15(void) {
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
  // 78: info.is_a_multi_assign_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_a_multi_assign_definition();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_16;
}
static void cont__compiler__check_definitions_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__check_definitions_17, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_25;
}
static void entry__compiler__check_definitions_17(void) {
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
  // 79: parameter_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__parameter_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_18;
}
static void cont__compiler__check_definitions_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 79: parameter_kind_of(info) != IN_OUT_PARAMETER
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__4 */;
  arguments->slots[1] = get__IN_OUT_PARAMETER();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_19;
}
static void cont__compiler__check_definitions_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__3 */ = arguments->slots[0];
  // 79: parameter_kind_of(info) != IN_OUT_PARAMETER
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__3 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_20;
}
static void cont__compiler__check_definitions_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 80: not(assigned_names(name))
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__check_definitions_21, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__2 */;
  arguments->slots[1] = frame->slots[6] /* temp__5 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_24;
}
static void entry__compiler__check_definitions_21(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 80: ... assigned_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_22;
}
static void cont__compiler__check_definitions_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 80: not(assigned_names(name))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__not();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_23;
}
static void cont__compiler__check_definitions_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 80: not(assigned_names(name))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__check_definitions_24(void) {
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
static void cont__compiler__check_definitions_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 81: :
  // 82:   Warning identifier "
  // 83:     the identifier "@(name)" is defined as a read-write variable, @
  // 84:     but there is no actual assignment@
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__check_definitions_26, 0);
  // 76: if
  // 77:   &&
  // 78:     info.is_a_multi_assign_definition
  // 79:     parameter_kind_of(info) != IN_OUT_PARAMETER
  // 80:     not(assigned_names(name))
  // 81:   :
  // 82:     Warning identifier "
  // 83:       the identifier "@(name)" is defined as a read-write variable, @
  // 84:       but there is no actual assignment@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__check_definitions_6(void) {
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
  // 71: used_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* name */;
  result_count = 1;
  myself = frame->slots[0] /* used_names */;
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_7;
}
static void cont__compiler__check_definitions_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 71: used_names(name).is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_8;
}
static void cont__compiler__check_definitions_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 71: ... :
  // 72:   unless identifier.is_not_used:
  // 73:     Warning identifier "
  // 74:       the identifier "@(name)" is defined but not used@
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__check_definitions_9, 0);
  // 75: :
  // 76:   if
  // 77:     &&
  // 78:       info.is_a_multi_assign_definition
  // 79:       parameter_kind_of(info) != IN_OUT_PARAMETER
  // 80:       not(assigned_names(name))
  // 81:     :
  // 82:       Warning identifier "
  // 83:         the identifier "@(name)" is defined as a read-write variable, @
  // 84:         but there is no actual assignment@
  frame->slots[7] /* temp__4 */ = create_closure(entry__compiler__check_definitions_15, 0);
  // 70: if
  // 71:   used_names(name).is_undefined:
  // 72:     unless identifier.is_not_used:
  // 73:       Warning identifier "
  // 74:         the identifier "@(name)" is defined but not used@
  // 75:   :
  // 76:     if
  // 77:       &&
  // 78:         info.is_a_multi_assign_definition
  // 79:         parameter_kind_of(info) != IN_OUT_PARAMETER
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
static void entry__compiler__check_definitions_2(void) {
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
  // 68: $identifier identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_3;
}
static void cont__compiler__check_definitions_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* identifier */, arguments->slots[0]);
  // 69: ... namespace_of(identifier)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* identifier */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_4;
}
static void cont__compiler__check_definitions_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__2 */ = arguments->slots[0];
  // 69: ... namespace_of(identifier).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__check_definitions_5;
}
static void cont__compiler__check_definitions_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 69: ... :
  // 70:   if
  // 71:     used_names(name).is_undefined:
  // 72:       unless identifier.is_not_used:
  // 73:         Warning identifier "
  // 74:           the identifier "@(name)" is defined but not used@
  // 75:     :
  // 76:       if
  // 77:         &&
  // 78:           info.is_a_multi_assign_definition
  // ...
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__check_definitions_6, 0);
  // 69: unless namespace_of(identifier).is_defined:
  // 70:   if
  // 71:     used_names(name).is_undefined:
  // 72:       unless identifier.is_not_used:
  // 73:         Warning identifier "
  // 74:           the identifier "@(name)" is defined but not used@
  // 75:     :
  // 76:       if
  // 77:         &&
  // 78:           info.is_a_multi_assign_definition
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
static void cont__compiler__check_definitions_29(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 85: ... : (name info)
  // 86:   $defined_name defined_names(name)
  // 87:   if defined_name.is_defined:
  // 88:     if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 89:       Warning identifier_of(info) "
  // 90:         attempt to use the identifier "@(name)" that is marked as not being @
  // 91:         used@
  frame->slots[2] /* temp__1 */ = create_closure(entry__compiler__check_definitions_30, 2);
  // 85: for_each used_names: (name info)
  // 86:   $defined_name defined_names(name)
  // 87:   if defined_name.is_defined:
  // 88:     if do_print_warnings && identifier_of(defined_name).is_not_used:
  // 89:       Warning identifier_of(info) "
  // 90:         attempt to use the identifier "@(name)" that is marked as not being @
  // 91:         used@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* used_names */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__body___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  // locally_assigned_names: 1
  // outer_level: 2
  frame->slots[1] /* locally_assigned_names */ = create_cell();
  // _define $outer_level level
  frame->slots[2] /* outer_level */ = get__level();
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 94: show_compiler_debug_info "annotate body"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__463aabf2a07456b1;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__body___annotate_expression_3;
}
static void cont__compiler__body___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 95: $$locally_assigned_names undefined
  ((CELL *)frame->slots[1])->contents /* locally_assigned_names */ = get__undefined();
  //  97: ... :
  //  98:   %%compiler::defined_names empty_list
  //  99:   %%compiler::used_names empty_insert_order_table
  // 100:   %%compiler::assigned_names empty_set
  // 101:   %%defines_dynamics false
  // 102:   %level outer_level+1
  // 103:   update_each &self.parameters_of: (&parameter)
  // 104:     push &defined_names parameter
  // 105:     if
  // 106:       parameter.is_an_optional_item && default_value_of(parameter).is_defined
  // ...
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__body__annotate_expression_4, 0);
  //  97: do:
  //  98:   %%compiler::defined_names empty_list
  //  99:   %%compiler::used_names empty_insert_order_table
  // 100:   %%compiler::assigned_names empty_set
  // 101:   %%defines_dynamics false
  // 102:   %level outer_level+1
  // 103:   update_each &self.parameters_of: (&parameter)
  // 104:     push &defined_names parameter
  // 105:     if
  // 106:       parameter.is_an_optional_item && default_value_of(parameter).is_defined
  // ...
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 0;
  myself = get__do();
  func = myself->type;
  frame->cont = cont__compiler__body___annotate_expression_71;
}
static void entry__compiler__body__annotate_expression_4(void) {
  allocate_initialized_frame_gc(4, 7);
  // slot allocations:
  // return__1: 0
  // outer_level: 1
  // self: 2
  // locally_assigned_names: 3
  // local_definitions: 4
  frame->slots[0] /* return__1 */ = create_continuation();
  frame->slots[1] = myself->closure.frame->slots[2]; /* outer_level */
  frame->slots[2] = myself->closure.frame->slots[0]; /* self */
  frame->slots[3] = myself->closure.frame->slots[1]; /* locally_assigned_names */
  define__compiler__defined_names(undefined);
  define__compiler__used_names(undefined);
  define__compiler__assigned_names(undefined);
  define__defines_dynamics(undefined);
  define__level(create_future());
  frame->slots[4] /* local_definitions */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 98: %%compiler::defined_names empty_list
  set__compiler__defined_names(get__empty_list());
  // 99: %%compiler::used_names empty_insert_order_table
  set__compiler__used_names(get__empty_insert_order_table());
  // 100: %%compiler::assigned_names empty_set
  set__compiler__assigned_names(get__empty_set());
  // 101: %%defines_dynamics false
  set__defines_dynamics(get__false());
  // 102: %level outer_level+1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* outer_level */;
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__plus();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_5;
}
static void cont__compiler__body__annotate_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(get__level(), arguments->slots[0]);
  // 103: ... self.parameters_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_6;
}
static void cont__compiler__body__annotate_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 103: update_each &self.parameters_of: (&parameter)
  // 104:   push &defined_names parameter
  // 105:   if
  // 106:     parameter.is_an_optional_item && default_value_of(parameter).is_defined
  // 107:     :
  // 108:       annotate_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__compiler__body__annotate_expression_7;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_18;
}
static void entry__compiler__body__annotate_expression_7(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_8;
}
static void cont__compiler__body__annotate_expression_8(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_9;
}
static void cont__compiler__body__annotate_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 106: ... default_value_of(parameter).is_defined
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__body__annotate_expression_10, 0);
  // 106: parameter.is_an_optional_item && default_value_of(parameter).is_defined
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_13;
}
static void entry__compiler__body__annotate_expression_10(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_11;
}
static void cont__compiler__body__annotate_expression_11(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_12;
}
static void cont__compiler__body__annotate_expression_12(void) {
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
static void cont__compiler__body__annotate_expression_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 107: :
  // 108:   annotate_expression &parameter.default_value_of
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__body__annotate_expression_14, 0);
  // 105: if
  // 106:   parameter.is_an_optional_item && default_value_of(parameter).is_defined
  // 107:   :
  // 108:     annotate_expression &parameter.default_value_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_17;
}
static void entry__compiler__body__annotate_expression_14(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // parameter: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* parameter */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 108: ... parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* parameter */;
  result_count = 1;
  myself = get__default_value_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_15;
}
static void cont__compiler__body__annotate_expression_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 108: annotate_expression &parameter.default_value_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_16;
}
static void cont__compiler__body__annotate_expression_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 108: ... &parameter.default_value_of
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
static void cont__compiler__body__annotate_expression_17(void) {
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
static void cont__compiler__body__annotate_expression_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 103: ... &self.parameters_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__parameters_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 109: ... self.statements_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[2])->contents /* self */;
  result_count = 1;
  myself = get__statements_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_19;
}
static void cont__compiler__body__annotate_expression_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__1 */ = arguments->slots[0];
  // 109: update_each &self.statements_of: (&stmt) annotate_statement &stmt
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__1 */;
  arguments->slots[1] = func__compiler__body__annotate_expression_20;
  result_count = 1;
  myself = get__update_each();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_22;
}
static void entry__compiler__body__annotate_expression_20(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // stmt: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* stmt */ = create_cell_with_contents(arguments->slots[0]);
  // 109: ... annotate_statement &stmt
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* stmt */;
  result_count = 1;
  myself = get__annotate_statement();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_21;
}
static void cont__compiler__body__annotate_expression_21(void) {
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
static void cont__compiler__body__annotate_expression_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[6] /* temp__2 */ = arguments->slots[0];
  // 109: ... &self.statements_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__statements_of, frame->slots[6] /* temp__2 */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 110: $$local_definitions empty_insert_order_table
  ((CELL *)frame->slots[4])->contents /* local_definitions */ = get__empty_insert_order_table();
  // 111: ... : (info)
  // 112:   case variable_kind_of(info)
  // 113:     STATIC_SINGLE, STATIC_MULTI:
  // 114:       $ident identifier_of(info)
  // 115:       if namespace_of(ident).is_defined:
  // 116:         SyntaxError ident "
  // 117:           attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:           in an inner scope@
  // 119:       $name name_of(ident)
  // 120:       if local_definitions(name).is_defined:
  // ...
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__body__annotate_expression_23, 1);
  // 111: for_each defined_names: (info)
  // 112:   case variable_kind_of(info)
  // 113:     STATIC_SINGLE, STATIC_MULTI:
  // 114:       $ident identifier_of(info)
  // 115:       if namespace_of(ident).is_defined:
  // 116:         SyntaxError ident "
  // 117:           attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:           in an inner scope@
  // 119:       $name name_of(ident)
  // 120:       if local_definitions(name).is_defined:
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_50;
}
static void entry__compiler__body__annotate_expression_46(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 126: ... identifier_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_47;
}
static void cont__compiler__body__annotate_expression_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 126: ... mangled_name_of(identifier_of(info))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_48;
}
static void cont__compiler__body__annotate_expression_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 126: !used_names(mangled_name_of(identifier_of(info)))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_49;
}
static void cont__compiler__body__annotate_expression_49(void) {
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
static void entry__compiler__body__annotate_expression_23(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // info: 0
  // local_definitions: 1
  frame->slots[1] = myself->closure.frame->slots[4]; /* local_definitions */
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 112: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_24;
}
static void cont__compiler__body__annotate_expression_24(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_25;
}
static void cont__compiler__body__annotate_expression_25(void) {
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
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__annotate_expression_26, 0);
  // 125: DYNAMIC_SINGLE, DYNAMIC_MULTI
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__DYNAMIC_SINGLE();
  arguments->slots[1] = get__DYNAMIC_MULTI();
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_45;
}
static void entry__compiler__body__annotate_expression_26(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_27;
}
static void cont__compiler__body__annotate_expression_27(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_28;
}
static void cont__compiler__body__annotate_expression_28(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_29;
}
static void cont__compiler__body__annotate_expression_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 115: ... :
  // 116:   SyntaxError ident "
  // 117:     attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:     in an inner scope@
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__body__annotate_expression_30, 0);
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
  frame->cont = cont__compiler__body__annotate_expression_35;
}
static void entry__compiler__body__annotate_expression_30(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_31;
}
static void cont__compiler__body__annotate_expression_31(void) {
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
  arguments->slots[0] = string__c9348eff105534ce;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = string__dcee629a9fc6e3f6;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_34;
}
static void cont__compiler__body__annotate_expression_34(void) {
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
static void cont__compiler__body__annotate_expression_35(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_36;
}
static void cont__compiler__body__annotate_expression_36(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_37;
}
static void cont__compiler__body__annotate_expression_37(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_38;
}
static void cont__compiler__body__annotate_expression_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 120: ... :
  // 121:   SyntaxError ident "
  // 122:     Attempt to define a variable twice within a single scope (@(name)@
  // 123:     )@
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__body__annotate_expression_39, 0);
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
  frame->cont = cont__compiler__body__annotate_expression_43;
}
static void entry__compiler__body__annotate_expression_39(void) {
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
  arguments->slots[0] = string__e3b540e1e08e3bc7;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc8;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_42;
}
static void cont__compiler__body__annotate_expression_42(void) {
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
static void cont__compiler__body__annotate_expression_43(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 124: !local_definitions(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* name */;
  arguments->slots[1] = frame->slots[0] /* info */;
  result_count = 1;
  myself = ((CELL *)frame->slots[1])->contents /* local_definitions */;
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_44;
}
static void cont__compiler__body__annotate_expression_44(void) {
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
static void cont__compiler__body__annotate_expression_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__4 */ = arguments->slots[0];
  // 125: ... :
  // 126:   !used_names(mangled_name_of(identifier_of(info))) info
  frame->slots[6] /* temp__5 */ = create_closure(entry__compiler__body__annotate_expression_46, 0);
  // 112: case variable_kind_of(info)
  // 113:   STATIC_SINGLE, STATIC_MULTI:
  // 114:     $ident identifier_of(info)
  // 115:     if namespace_of(ident).is_defined:
  // 116:       SyntaxError ident "
  // 117:         attempt to define a namespaced entity (@(full_name_of(ident))) @
  // 118:         in an inner scope@
  // 119:     $name name_of(ident)
  // 120:     if local_definitions(name).is_defined:
  // 121:       SyntaxError ident "
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
static void cont__compiler__body__annotate_expression_50(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 127: !self.defined_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defined_names_of, ((CELL *)frame->slots[4])->contents /* local_definitions */);
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 128: !self.used_names_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[2])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__used_names_of, get__used_names());
    ((CELL *)frame->slots[2])->contents /* self */ = temp;

  }
  // 129: ... :
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
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__body__annotate_expression_51, 0);
  // 129: if defines_dynamics:
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
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_67;
}
static void entry__compiler__body__annotate_expression_61(void) {
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
  arguments->slots[0] = string__4a80ae5c052cc23f;
  arguments->slots[1] = get__index();
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_63;
}
static void cont__compiler__body__annotate_expression_63(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_64;
}
static void cont__compiler__body__annotate_expression_64(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_65;
}
static void cont__compiler__body__annotate_expression_65(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
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
  frame->cont = cont__compiler__body__annotate_expression_66;
}
static void cont__compiler__body__annotate_expression_66(void) {
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
static void entry__compiler__body__annotate_expression_51(void) {
  allocate_initialized_frame_gc(1, 6);
  // slot allocations:
  // self: 0
  // parameters: 1
  frame->slots[0] = myself->closure.frame->slots[2]; /* self */
  frame->slots[1] /* parameters */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 130: !self.defines_a_dynamic
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__defines_a_dynamic, get__true());
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 131: $parameters parameters_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__parameters_of();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_52;
}
static void cont__compiler__body__annotate_expression_52(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_53;
}
static void cont__compiler__body__annotate_expression_53(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 135: parameter_kind_of(parameters(-1)) != CONTINUATION_PARAMETER
  frame->slots[4] /* temp__3 */ = create_closure(entry__compiler__body__annotate_expression_54, 0);
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
  frame->cont = cont__compiler__body__annotate_expression_60;
}
static void entry__compiler__body__annotate_expression_54(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_55;
}
static void cont__compiler__body__annotate_expression_55(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_56;
}
static void cont__compiler__body__annotate_expression_56(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_57;
}
static void cont__compiler__body__annotate_expression_57(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_58;
}
static void cont__compiler__body__annotate_expression_58(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_59;
}
static void cont__compiler__body__annotate_expression_59(void) {
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
static void cont__compiler__body__annotate_expression_60(void) {
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
  frame->slots[5] /* temp__4 */ = create_closure(entry__compiler__body__annotate_expression_61, 0);
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
static void cont__compiler__body__annotate_expression_67(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 144: ... :
  // 145:   check_definitions local_definitions used_names
  // 146:   !locally_assigned_names assigned_names
  frame->slots[5] /* temp__1 */ = create_closure(entry__compiler__body__annotate_expression_68, 0);
  // 144: if do_print_warnings:
  // 145:   check_definitions local_definitions used_names
  // 146:   !locally_assigned_names assigned_names
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[5] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_70;
}
static void entry__compiler__body__annotate_expression_68(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // local_definitions: 0
  // locally_assigned_names: 1
  frame->slots[0] = myself->closure.frame->slots[4]; /* local_definitions */
  frame->slots[1] = myself->closure.frame->slots[3]; /* locally_assigned_names */
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
  frame->cont = cont__compiler__body__annotate_expression_69;
}
static void cont__compiler__body__annotate_expression_69(void) {
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
static void cont__compiler__body__annotate_expression_70(void) {
  myself = frame->slots[0] /* return__1 */;
  func = myself->type;
  frame->cont = invalid_continuation;
}
static void cont__compiler__body___annotate_expression_71(void) {
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
  frame->cont = cont__compiler__body___annotate_expression_72;
}
static void cont__compiler__body___annotate_expression_72(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 147: ... : (name info)
  // 148:   unless defined_names_of(self)(name).is_defined:
  // 149:     $updated_info update_info(name used_names(name) info)
  // 150:     if updated_info.is_defined: !used_names(name) updated_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__annotate_expression_73, 2);
  // 147: for_each used_names_of(self): (name info)
  // 148:   unless defined_names_of(self)(name).is_defined:
  // 149:     $updated_info update_info(name used_names(name) info)
  // 150:     if updated_info.is_defined: !used_names(name) updated_info
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 0;
  myself = get__for_each();
  func = myself->type;
  frame->cont = cont__compiler__body___annotate_expression_83;
}
static void entry__compiler__body__annotate_expression_81(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // name: 0
  // updated_info: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* updated_info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 150: ... !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[1] /* updated_info */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_82;
}
static void cont__compiler__body__annotate_expression_82(void) {
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
static void entry__compiler__body__annotate_expression_77(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_78;
}
static void cont__compiler__body__annotate_expression_78(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_79;
}
static void cont__compiler__body__annotate_expression_79(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_80;
}
static void cont__compiler__body__annotate_expression_80(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 150: ... : !used_names(name) updated_info
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__body__annotate_expression_81, 0);
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
static void entry__compiler__body__annotate_expression_73(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_74;
}
static void cont__compiler__body__annotate_expression_74(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_75;
}
static void cont__compiler__body__annotate_expression_75(void) {
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
  frame->cont = cont__compiler__body__annotate_expression_76;
}
static void cont__compiler__body__annotate_expression_76(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 148: ... :
  // 149:   $updated_info update_info(name used_names(name) info)
  // 150:   if updated_info.is_defined: !used_names(name) updated_info
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__body__annotate_expression_77, 0);
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
static void cont__compiler__body___annotate_expression_83(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 151: ... :
  // 152:   for_each locally_assigned_names: (name) !assigned_names(name) true
  frame->slots[3] /* temp__1 */ = create_closure(entry__compiler__body__annotate_expression_84, 0);
  // 151: if do_print_warnings:
  // 152:   for_each locally_assigned_names: (name) !assigned_names(name) true
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__do_print_warnings();
  arguments->slots[1] = frame->slots[3] /* temp__1 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__body___annotate_expression_87;
}
static void entry__compiler__body__annotate_expression_85(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // name: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  // 152: ... !assigned_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = get__true();
  result_count = 1;
  myself = get__assigned_names();
  func = myself->type;
  frame->cont = cont__compiler__body__annotate_expression_86;
}
static void cont__compiler__body__annotate_expression_86(void) {
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
static void entry__compiler__body__annotate_expression_84(void) {
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
  arguments->slots[1] = func__compiler__body__annotate_expression_85;
  result_count = frame->caller_result_count;
  myself = get__for_each();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__body___annotate_expression_87(void) {
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
static void entry__compiler__call___annotate_statement(void) {
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
  arguments->slots[0] = string__8a2e321e316b06ed;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_2;
}
static void cont__compiler__call___annotate_statement_2(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 160: functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_3;
}
static void cont__compiler__call___annotate_statement_3(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 160: functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_4;
}
static void cont__compiler__call___annotate_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 160: ... :
  // 161:   if result_count_of(self).is_defined:
  // 162:     annotate_expression &self.result_count_of
  // 163:   if continuation_of(self).is_defined:
  // 164:     annotate_expression &self.continuation_of
  // 165:   annotate_expression &self.functor_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__annotate_statement_5, 0);
  // 166: :
  // 167:   $destination arguments_of(self)(1)
  // 168:   if destination.is_a_definition:
  // 169:     $source arguments_of(self)(2)
  // 170:     if
  // 171:       ||
  // 172:         source.is_a_unique_item_constant
  // 173:         source.is_a_body && level == 1
  // 174:         source.is_a_c_body && level == 1
  // 175:       :
  // ...
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__call__annotate_statement_20, 0);
  // 159: if
  // 160:   functor_of(self).is_defined:
  // 161:     if result_count_of(self).is_defined:
  // 162:       annotate_expression &self.result_count_of
  // 163:     if continuation_of(self).is_defined:
  // 164:       annotate_expression &self.continuation_of
  // 165:     annotate_expression &self.functor_of
  // 166:   :
  // 167:     $destination arguments_of(self)(1)
  // 168:     if destination.is_a_definition:
  // ...
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  arguments->slots[2] = frame->slots[4] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_62;
}
static void entry__compiler__call__annotate_statement_40(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // destination: 0
  // self: 1
  // name: 2
  frame->slots[0] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[0]; /* self */
  frame->slots[2] /* name */ = create_cell();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 176: ... identifier_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_41;
}
static void cont__compiler__call__annotate_statement_41(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 176: $$name mangled_name_of(identifier_of(destination))
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_42;
}
static void cont__compiler__call__annotate_statement_42(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  ((CELL *)frame->slots[2])->contents /* name */ = arguments->slots[0];
  // 177: ... attribute_kind_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_43;
}
static void cont__compiler__call__annotate_statement_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[5] /* temp__3 */ = arguments->slots[0];
  // 177: ... attribute_kind_of(destination) != NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[5] /* temp__3 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_44;
}
static void cont__compiler__call__annotate_statement_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 177: ... attribute_kind_of(destination) != NONE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = get__std__not();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_45;
}
static void cont__compiler__call__annotate_statement_45(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 177: ... :
  // 178:   $attribute attribute_of(destination)
  // 179:   if
  // 180:     attribute.is_defined:
  // 181:       append &name string("___" mangled_name_of(attribute))
  // 182:     :
  // 183:       append &name string("____type")
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__call__annotate_statement_46, 0);
  // 177: if attribute_kind_of(destination) != NONE:
  // 178:   $attribute attribute_of(destination)
  // 179:   if
  // 180:     attribute.is_defined:
  // 181:       append &name string("___" mangled_name_of(attribute))
  // 182:     :
  // 183:       append &name string("____type")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_58;
}
static void entry__compiler__call__annotate_statement_49(void) {
  allocate_initialized_frame_gc(2, 4);
  // slot allocations:
  // name: 0
  // attribute: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  frame->slots[1] = myself->closure.frame->slots[2]; /* attribute */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 181: ... mangled_name_of(attribute)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* attribute */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_50;
}
static void cont__compiler__call__annotate_statement_50(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__2 */ = arguments->slots[0];
  // 181: ... string("___" mangled_name_of(attribute))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__fa72f815cd16b93;
  arguments->slots[1] = frame->slots[3] /* temp__2 */;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_52;
}
static void cont__compiler__call__annotate_statement_52(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 181: append &name string("___" mangled_name_of(attribute))
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_53;
}
static void cont__compiler__call__annotate_statement_53(void) {
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
static void entry__compiler__call__annotate_statement_54(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // name: 0
  frame->slots[0] = myself->closure.frame->slots[1]; /* name */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 183: ... string("____type")
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__4668ab89845667a5;
  result_count = 1;
  myself = get__string();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_56;
}
static void cont__compiler__call__annotate_statement_56(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 183: append &name string("____type")
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* name */;
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__append();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_57;
}
static void cont__compiler__call__annotate_statement_57(void) {
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
static void entry__compiler__call__annotate_statement_46(void) {
  allocate_initialized_frame_gc(2, 6);
  // slot allocations:
  // destination: 0
  // name: 1
  // attribute: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* destination */
  frame->slots[1] = myself->closure.frame->slots[2]; /* name */
  frame->slots[2] /* attribute */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 178: $attribute attribute_of(destination)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* destination */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_47;
}
static void cont__compiler__call__annotate_statement_47(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* attribute */, arguments->slots[0]);
  // 180: attribute.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* attribute */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_48;
}
static void cont__compiler__call__annotate_statement_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 180: ... :
  // 181:   append &name string("___" mangled_name_of(attribute))
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__call__annotate_statement_49, 0);
  // 182: :
  // 183:   append &name string("____type")
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__annotate_statement_54, 0);
  // 179: if
  // 180:   attribute.is_defined:
  // 181:     append &name string("___" mangled_name_of(attribute))
  // 182:   :
  // 183:     append &name string("____type")
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
static void cont__compiler__call__annotate_statement_58(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 184: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[1])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_59;
}
static void cont__compiler__call__annotate_statement_59(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 184: ... self.arguments_of(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_60;
}
static void cont__compiler__call__annotate_statement_60(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 184: !self.arguments_of(2).name_of
  {
    NODE *temp = clone_object_and_attributes(frame->slots[4] /* temp__2 */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__name_of, ((CELL *)frame->slots[2])->contents /* name */);
    frame->slots[4] /* temp__2 */ = temp;

  }
  // 184: !self.arguments_of(2)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = number__2;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_61;
}
static void cont__compiler__call__annotate_statement_61(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 184: !self.arguments_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[1])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__arguments_of, frame->slots[3] /* temp__1 */);
    ((CELL *)frame->slots[1])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__call__annotate_statement_24(void) {
  allocate_initialized_frame_gc(2, 7);
  // slot allocations:
  // self: 0
  // destination: 1
  // source: 2
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] = myself->closure.frame->slots[1]; /* destination */
  frame->slots[2] /* source */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 169: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_25;
}
static void cont__compiler__call__annotate_statement_25(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 169: $source arguments_of(self)(2)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__2;
  result_count = 1;
  myself = frame->slots[3] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_26;
}
static void cont__compiler__call__annotate_statement_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* source */, arguments->slots[0]);
  // 172: source.is_a_unique_item_constant
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* source */;
  result_count = 1;
  myself = get__is_a_unique_item_constant();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_27;
}
static void cont__compiler__call__annotate_statement_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__call__annotate_statement_28, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_39;
}
static void entry__compiler__call__annotate_statement_28(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[2]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: source.is_a_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_body();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_29;
}
static void cont__compiler__call__annotate_statement_29(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__3 */ = arguments->slots[0];
  // 173: source.is_a_body && level == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__3 */;
  arguments->slots[1] = func__compiler__call__annotate_statement_30;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_32;
}
static void entry__compiler__call__annotate_statement_30(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 173: ... level == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__level();
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_31;
}
static void cont__compiler__call__annotate_statement_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 173: ... level == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__annotate_statement_32(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: source.is_a_c_body && level == 1
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__call__annotate_statement_33, 0);
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = frame->slots[4] /* temp__4 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_38;
}
static void entry__compiler__call__annotate_statement_33(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // source: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* source */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: source.is_a_c_body
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* source */;
  result_count = 1;
  myself = get__is_a_c_body();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_34;
}
static void cont__compiler__call__annotate_statement_34(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 174: source.is_a_c_body && level == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = func__compiler__call__annotate_statement_35;
  result_count = 1;
  myself = get__std__and();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_37;
}
static void entry__compiler__call__annotate_statement_35(void) {
  allocate_initialized_frame_gc(0, 1);
  // slot allocations:
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 174: ... level == 1
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__level();
  arguments->slots[1] = number__1;
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_36;
}
static void cont__compiler__call__annotate_statement_36(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[0] /* temp__1 */ = arguments->slots[0];
  // 174: ... level == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__annotate_statement_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 174: source.is_a_c_body && level == 1
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__call__annotate_statement_38(void) {
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
static void cont__compiler__call__annotate_statement_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 175: :
  // 176:   $$name mangled_name_of(identifier_of(destination))
  // 177:   if attribute_kind_of(destination) != NONE:
  // 178:     $attribute attribute_of(destination)
  // 179:     if
  // 180:       attribute.is_defined:
  // 181:         append &name string("___" mangled_name_of(attribute))
  // 182:       :
  // 183:         append &name string("____type")
  // 184:   !self.arguments_of(2).name_of name
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__call__annotate_statement_40, 0);
  // 170: if
  // 171:   ||
  // 172:     source.is_a_unique_item_constant
  // 173:     source.is_a_body && level == 1
  // 174:     source.is_a_c_body && level == 1
  // 175:   :
  // 176:     $$name mangled_name_of(identifier_of(destination))
  // 177:     if attribute_kind_of(destination) != NONE:
  // 178:       $attribute attribute_of(destination)
  // 179:       if
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[6] /* temp__4 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__call__annotate_statement_5(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 161: ... result_count_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_6;
}
static void cont__compiler__call__annotate_statement_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 161: ... result_count_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_7;
}
static void cont__compiler__call__annotate_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 161: ... :
  // 162:   annotate_expression &self.result_count_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__annotate_statement_8, 0);
  // 161: if result_count_of(self).is_defined:
  // 162:   annotate_expression &self.result_count_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_11;
}
static void entry__compiler__call__annotate_statement_8(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 162: ... self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__result_count_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_9;
}
static void cont__compiler__call__annotate_statement_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 162: annotate_expression &self.result_count_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_10;
}
static void cont__compiler__call__annotate_statement_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 162: ... &self.result_count_of
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
static void cont__compiler__call__annotate_statement_11(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 163: ... continuation_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_12;
}
static void cont__compiler__call__annotate_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 163: ... continuation_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_13;
}
static void cont__compiler__call__annotate_statement_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 163: ... :
  // 164:   annotate_expression &self.continuation_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__call__annotate_statement_14, 0);
  // 163: if continuation_of(self).is_defined:
  // 164:   annotate_expression &self.continuation_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_17;
}
static void entry__compiler__call__annotate_statement_14(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 164: ... self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__continuation_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_15;
}
static void cont__compiler__call__annotate_statement_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 164: annotate_expression &self.continuation_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_16;
}
static void cont__compiler__call__annotate_statement_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 164: ... &self.continuation_of
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
static void cont__compiler__call__annotate_statement_17(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 165: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_18;
}
static void cont__compiler__call__annotate_statement_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 165: annotate_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_19;
}
static void cont__compiler__call__annotate_statement_19(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 165: ... &self.functor_of
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
static void entry__compiler__call__annotate_statement_20(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  // destination: 1
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  frame->slots[1] /* destination */ = create_future();
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 167: ... arguments_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_21;
}
static void cont__compiler__call__annotate_statement_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 167: $destination arguments_of(self)(1)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = number__1;
  result_count = 1;
  myself = frame->slots[2] /* temp__1 */;
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_22;
}
static void cont__compiler__call__annotate_statement_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* destination */, arguments->slots[0]);
  // 168: ... destination.is_a_definition
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* destination */;
  result_count = 1;
  myself = get__is_a_definition();
  func = myself->type;
  frame->cont = cont__compiler__call__annotate_statement_23;
}
static void cont__compiler__call__annotate_statement_23(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 168: ... :
  // 169:   $source arguments_of(self)(2)
  // 170:   if
  // 171:     ||
  // 172:       source.is_a_unique_item_constant
  // 173:       source.is_a_body && level == 1
  // 174:       source.is_a_c_body && level == 1
  // 175:     :
  // 176:       $$name mangled_name_of(identifier_of(destination))
  // 177:       if attribute_kind_of(destination) != NONE:
  // ...
  frame->slots[3] /* temp__2 */ = create_closure(entry__compiler__call__annotate_statement_24, 0);
  // 168: if destination.is_a_definition:
  // 169:   $source arguments_of(self)(2)
  // 170:   if
  // 171:     ||
  // 172:       source.is_a_unique_item_constant
  // 173:       source.is_a_body && level == 1
  // 174:       source.is_a_c_body && level == 1
  // 175:     :
  // 176:       $$name mangled_name_of(identifier_of(destination))
  // 177:       if attribute_kind_of(destination) != NONE:
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
static void cont__compiler__call___annotate_statement_62(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 185: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_63;
}
static void cont__compiler__call___annotate_statement_63(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 185: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = func__annotate_arguments;
  func = myself->type;
  frame->cont = cont__compiler__call___annotate_statement_64;
}
static void cont__compiler__call___annotate_statement_64(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 185: ... &self.arguments_of
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
static void entry__compiler__c_code___annotate_statement(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 191: show_compiler_debug_info "annotate C-code"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__1315a9c10d8edccd;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_3;
}
static void cont__compiler__c_code___annotate_statement_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 192: ... kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__kind_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_4;
}
static void cont__compiler__c_code___annotate_statement_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 192: ... "type", "object"
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__2a0aef0b5de07d5c;
  arguments->slots[1] = string__4c1f570701a272a3;
  result_count = 1;
  myself = get__std__sequence();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_7;
}
static void cont__compiler__c_code___annotate_statement_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 192: ... :
  // 193:   push
  // 194:     &defined_names
  // 195:     self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__c_code__annotate_statement_8, 0);
  // 192: case kind_of(self) "type", "object":
  // 193:   push
  // 194:     &defined_names
  // 195:     self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[2] /* temp__2 */;
  arguments->slots[2] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__case();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_10;
}
static void entry__compiler__c_code__annotate_statement_8(void) {
  allocate_initialized_frame_gc(1, 2);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 195: self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    set_attribute_value(temp->attributes, poly_idx__is_a_single_assign_definition, get__true());
    frame->slots[1] /* temp__1 */ = temp;

  }
  // 193: push
  // 194:   &defined_names
  // 195:   self(.variable_kind_of STATIC_SINGLE .is_a_single_assign_definition true)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__c_code__annotate_statement_9;
}
static void cont__compiler__c_code__annotate_statement_9(void) {
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
static void cont__compiler__c_code___annotate_statement_10(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 196: ... base_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_11;
}
static void cont__compiler__c_code___annotate_statement_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 196: ... base_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_12;
}
static void cont__compiler__c_code___annotate_statement_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 196: ... : annotate_expression &self.base_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__c_code__annotate_statement_13, 0);
  // 196: if base_of(self).is_defined: annotate_expression &self.base_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__c_code___annotate_statement_16;
}
static void entry__compiler__c_code__annotate_statement_13(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 196: ... self.base_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__base_of();
  func = myself->type;
  frame->cont = cont__compiler__c_code__annotate_statement_14;
}
static void cont__compiler__c_code__annotate_statement_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 196: ... annotate_expression &self.base_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__c_code__annotate_statement_15;
}
static void cont__compiler__c_code__annotate_statement_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 196: ... &self.base_of
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
static void cont__compiler__c_code___annotate_statement_16(void) {
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
static void entry__compiler__define_static_single___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 5);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 202: show_compiler_debug_info "annotate define static single"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__da22f4fe83fda879;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single___annotate_expression_3;
}
static void cont__compiler__define_static_single___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 204: attribute_kind_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single___annotate_expression_4;
}
static void cont__compiler__define_static_single___annotate_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 204: attribute_kind_of(self) == NONE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__NONE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single___annotate_expression_5;
}
static void cont__compiler__define_static_single___annotate_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 204: ... :
  // 205:   push &defined_names self
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__define_static_single__annotate_expression_6, 0);
  // 206: :
  // 207:   if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  // 208:   annotate_expression &self.identifier_of
  frame->slots[4] /* temp__4 */ = create_closure(entry__compiler__define_static_single__annotate_expression_8, 0);
  // 203: if
  // 204:   attribute_kind_of(self) == NONE:
  // 205:     push &defined_names self
  // 206:   :
  // 207:     if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  // 208:     annotate_expression &self.identifier_of
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
  frame->cont = cont__compiler__define_static_single___annotate_expression_17;
}
static void entry__compiler__define_static_single__annotate_expression_6(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 205: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_7;
}
static void cont__compiler__define_static_single__annotate_expression_7(void) {
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
static void entry__compiler__define_static_single__annotate_expression_8(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... attribute_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_9;
}
static void cont__compiler__define_static_single__annotate_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 207: ... attribute_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_10;
}
static void cont__compiler__define_static_single__annotate_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 207: ... : annotate_expression &self.attribute_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__define_static_single__annotate_expression_11, 0);
  // 207: if attribute_of(self).is_defined: annotate_expression &self.attribute_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_14;
}
static void entry__compiler__define_static_single__annotate_expression_11(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 207: ... self.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__attribute_of();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_12;
}
static void cont__compiler__define_static_single__annotate_expression_12(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 207: ... annotate_expression &self.attribute_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_13;
}
static void cont__compiler__define_static_single__annotate_expression_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 207: ... &self.attribute_of
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
static void cont__compiler__define_static_single__annotate_expression_14(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 208: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_15;
}
static void cont__compiler__define_static_single__annotate_expression_15(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 208: annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__define_static_single__annotate_expression_16;
}
static void cont__compiler__define_static_single__annotate_expression_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 208: ... &self.identifier_of
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
static void cont__compiler__define_static_single___annotate_expression_17(void) {
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
static void entry__compiler__define_static_multi___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 214: show_compiler_debug_info "annotate define static multi"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__8d039bc45e06307a;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__define_static_multi___annotate_expression_3;
}
static void cont__compiler__define_static_multi___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 215: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__define_static_multi___annotate_expression_4;
}
static void cont__compiler__define_static_multi___annotate_expression_4(void) {
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
static void entry__compiler__define_dynamic_single___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 221: show_compiler_debug_info "annotate define dynamic single"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__ff383df04998a917;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__define_dynamic_single___annotate_expression_3;
}
static void cont__compiler__define_dynamic_single___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 222: !defines_dynamics true
  set__defines_dynamics(get__true());
  // 223: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__define_dynamic_single___annotate_expression_4;
}
static void cont__compiler__define_dynamic_single___annotate_expression_4(void) {
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
static void entry__compiler__define_dynamic_multi___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 1);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 229: show_compiler_debug_info "annotate define dynamic multi"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__2d2e5f670727e936;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__define_dynamic_multi___annotate_expression_3;
}
static void cont__compiler__define_dynamic_multi___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 230: !defines_dynamics true
  set__defines_dynamics(get__true());
  // 231: push &defined_names self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = get__defined_names();
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__push();
  func = myself->type;
  frame->cont = cont__compiler__define_dynamic_multi___annotate_expression_4;
}
static void cont__compiler__define_dynamic_multi___annotate_expression_4(void) {
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
static void entry__compiler__function_call___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 237: show_compiler_debug_info "annotate function call"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__e5094206a209984d;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__function_call___annotate_expression_3;
}
static void cont__compiler__function_call___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 238: ... functor_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call___annotate_expression_4;
}
static void cont__compiler__function_call___annotate_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 238: ... functor_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__function_call___annotate_expression_5;
}
static void cont__compiler__function_call___annotate_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 238: ... :
  // 239:   annotate_expression &self.functor_of
  // 240:   annotate_arguments &self.arguments_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__function_call__annotate_expression_6, 0);
  // 238: if functor_of(self).is_defined:
  // 239:   annotate_expression &self.functor_of
  // 240:   annotate_arguments &self.arguments_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count =
    frame->caller_result_count >= 1 ?
    frame->caller_result_count-1 : -1;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__function_call___annotate_expression_11;
}
static void entry__compiler__function_call__annotate_expression_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 239: ... self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__functor_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__annotate_expression_7;
}
static void cont__compiler__function_call__annotate_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 239: annotate_expression &self.functor_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__function_call__annotate_expression_8;
}
static void cont__compiler__function_call__annotate_expression_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 239: ... &self.functor_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__functor_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 240: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__function_call__annotate_expression_9;
}
static void cont__compiler__function_call__annotate_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 240: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = func__annotate_arguments;
  func = myself->type;
  frame->cont = cont__compiler__function_call__annotate_expression_10;
}
static void cont__compiler__function_call__annotate_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 240: ... &self.arguments_of
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
static void cont__compiler__function_call___annotate_expression_11(void) {
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
static void entry__compiler__attribute_value_pair___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 246: show_compiler_debug_info "annotate attribute-value pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__cdedef056fb3250d;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair___annotate_expression_3;
}
static void cont__compiler__attribute_value_pair___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 247: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair___annotate_expression_4;
}
static void cont__compiler__attribute_value_pair___annotate_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 247: annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair___annotate_expression_5;
}
static void cont__compiler__attribute_value_pair___annotate_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 247: ... &self.identifier_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, frame->slots[2] /* temp__2 */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  // 248: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair___annotate_expression_6;
}
static void cont__compiler__attribute_value_pair___annotate_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 248: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = func__annotate_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_value_pair___annotate_expression_7;
}
static void cont__compiler__attribute_value_pair___annotate_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 248: ... &self.arguments_of
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
static void entry__compiler__attribute_function_pair___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 4);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 254: show_compiler_debug_info "annotate attribute-function pair"
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = string__9fe7729998bbff18;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_3;
}
static void cont__compiler__attribute_function_pair___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 255: ... identifier_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_4;
}
static void cont__compiler__attribute_function_pair___annotate_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 255: ... identifier_of(self).is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_5;
}
static void cont__compiler__attribute_function_pair___annotate_expression_5(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 255: ... : annotate_expression &self.identifier_of
  frame->slots[3] /* temp__3 */ = create_closure(entry__compiler__attribute_function_pair__annotate_expression_6, 0);
  // 255: if identifier_of(self).is_defined: annotate_expression &self.identifier_of
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  arguments->slots[1] = frame->slots[3] /* temp__3 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_9;
}
static void entry__compiler__attribute_function_pair__annotate_expression_6(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* self */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 255: ... self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__identifier_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__annotate_expression_7;
}
static void cont__compiler__attribute_function_pair__annotate_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 255: ... annotate_expression &self.identifier_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = get__annotate_expression();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair__annotate_expression_8;
}
static void cont__compiler__attribute_function_pair__annotate_expression_8(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 255: ... &self.identifier_of
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
static void cont__compiler__attribute_function_pair___annotate_expression_9(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 256: ... self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__arguments_of();
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_10;
}
static void cont__compiler__attribute_function_pair___annotate_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 256: annotate_arguments &self.arguments_of
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  result_count = 1;
  myself = func__annotate_arguments;
  func = myself->type;
  frame->cont = cont__compiler__attribute_function_pair___annotate_expression_11;
}
static void cont__compiler__attribute_function_pair___annotate_expression_11(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 256: ... &self.arguments_of
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
static void entry__compiler__identifier___annotate_expression(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // self: 0
  if (argument_count != 1) {
    invalid_arguments_error();
    return;
  }
  frame->slots[0] /* self */ = create_cell_with_contents(arguments->slots[0]);
  // 262: show_compiler_debug_info "annotate identifier " self
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = string__d4853f208c1cb4ea;
  arguments->slots[1] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 0;
  myself = get__show_compiler_debug_info();
  func = myself->type;
  frame->cont = cont__compiler__identifier___annotate_expression_3;
}
static void cont__compiler__identifier___annotate_expression_3(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 263: ... self.is_an_operator_symbol
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_an_operator_symbol();
  func = myself->type;
  frame->cont = cont__compiler__identifier___annotate_expression_4;
}
static void cont__compiler__identifier___annotate_expression_4(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 263: ... :
  // 264:   $namespace namespace_of(self)
  // 265:   if namespace.is_defined:
  // 266:     $mapped_namespace namespace_mappings(namespace)
  // 267:     if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  // 268:   $name mangled_name_of(self)
  // 269:   $info used_names(name)
  // 270:   cond
  // 271:     -> self.is_used_as_a_destination:
  // 272:       if
  // ...
  frame->slots[2] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_5, 0);
  // 263: unless self.is_an_operator_symbol:
  // 264:   $namespace namespace_of(self)
  // 265:   if namespace.is_defined:
  // 266:     $mapped_namespace namespace_mappings(namespace)
  // 267:     if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  // 268:   $name mangled_name_of(self)
  // 269:   $info used_names(name)
  // 270:   cond
  // 271:     -> self.is_used_as_a_destination:
  // 272:       if
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
  frame->cont = cont__compiler__identifier___annotate_expression_51;
}
static void entry__compiler__identifier__annotate_expression_49(void) {
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
  // 295: !used_names(name)
  // 296:   types::grammar_node
  // 297:     .identifier_of self
  // 298:     .variable_kind_of STATIC_SINGLE
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_SINGLE());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 295: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_50;
}
static void cont__compiler__identifier__annotate_expression_50(void) {
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
static void entry__compiler__identifier__annotate_expression_45(void) {
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
  // 291: ... "
  // 292:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__94ba0bbafc65551;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_46;
}
static void cont__compiler__identifier__annotate_expression_46(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 291: SyntaxError self "
  // 292:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__identifier__annotate_expression_40(void) {
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
  // 285: !used_names(name)
  // 286:   types::grammar_node
  // 287:     .identifier_of self
  // 288:     .variable_kind_of POLYMORPHIC
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__POLYMORPHIC());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 285: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_41;
}
static void cont__compiler__identifier__annotate_expression_41(void) {
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
static void entry__compiler__identifier__annotate_expression_42(void) {
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
  // 290: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_43;
}
static void cont__compiler__identifier__annotate_expression_43(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 290: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_44;
}
static void cont__compiler__identifier__annotate_expression_44(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 290: ... :
  // 291:   SyntaxError self "
  // 292:     Incompatible use of identifier "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__identifier__annotate_expression_45, 0);
  // 290: unless variable_kind_of(info) == POLYMORPHIC:
  // 291:   SyntaxError self "
  // 292:     Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__unless();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__identifier__annotate_expression_34(void) {
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
  // 284: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_35;
}
static void cont__compiler__identifier__annotate_expression_35(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 284: ... variable_kind_of(info) == STATIC_SINGLE
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__identifier__annotate_expression_36, 0);
  // 284: info.is_undefined || variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_39;
}
static void entry__compiler__identifier__annotate_expression_36(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
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
  frame->cont = cont__compiler__identifier__annotate_expression_37;
}
static void cont__compiler__identifier__annotate_expression_37(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 284: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_38;
}
static void cont__compiler__identifier__annotate_expression_38(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 284: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__identifier__annotate_expression_39(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 284: ... :
  // 285:   !used_names(name)
  // 286:     types::grammar_node
  // 287:       .identifier_of self
  // 288:       .variable_kind_of POLYMORPHIC
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__identifier__annotate_expression_40, 0);
  // 289: :
  // 290:   unless variable_kind_of(info) == POLYMORPHIC:
  // 291:     SyntaxError self "
  // 292:       Incompatible use of identifier "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__identifier__annotate_expression_42, 0);
  // 283: if
  // 284:   info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 285:     !used_names(name)
  // 286:       types::grammar_node
  // 287:         .identifier_of self
  // 288:         .variable_kind_of POLYMORPHIC
  // 289:   :
  // 290:     unless variable_kind_of(info) == POLYMORPHIC:
  // 291:       SyntaxError self "
  // 292:         Incompatible use of identifier "@(name)@quot;@
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
static void entry__compiler__identifier__annotate_expression_28(void) {
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
  // 280: ... "
  // 281:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 3;
  arguments = node_p;
  arguments->slots[0] = string__94ba0bbafc65551;
  arguments->slots[1] = frame->slots[1] /* name */;
  arguments->slots[2] = string__578a5af303e9cc3;
  result_count = 1;
  myself = get__std__string();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_31;
}
static void cont__compiler__identifier__annotate_expression_31(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__1 */ = arguments->slots[0];
  // 280: SyntaxError self "
  // 281:   Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = frame->caller_result_count;
  myself = get__SyntaxError();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__identifier__annotate_expression_23(void) {
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
  // 274: !used_names(name)
  // 275:   types::grammar_node
  // 276:     .identifier_of self
  // 277:     .variable_kind_of STATIC_MULTI
  {
    NODE *temp = clone_object_and_attributes(get__types__grammar_node());
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__identifier_of, ((CELL *)frame->slots[1])->contents /* self */);
    set_attribute_value(temp->attributes, poly_idx__variable_kind_of, get__STATIC_MULTI());
    frame->slots[2] /* temp__1 */ = temp;

  }
  // 274: !used_names(name)
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* name */;
  arguments->slots[1] = frame->slots[2] /* temp__1 */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_24;
}
static void cont__compiler__identifier__annotate_expression_24(void) {
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
static void entry__compiler__identifier__annotate_expression_25(void) {
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
  // 279: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_26;
}
static void cont__compiler__identifier__annotate_expression_26(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 279: ... variable_kind_of(info) == POLYMORPHIC
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = get__POLYMORPHIC();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_27;
}
static void cont__compiler__identifier__annotate_expression_27(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 279: ... :
  // 280:   SyntaxError self "
  // 281:     Incompatible use of identifier "@(name)@quot;@
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__identifier__annotate_expression_28, 0);
  // 279: if variable_kind_of(info) == POLYMORPHIC:
  // 280:   SyntaxError self "
  // 281:     Incompatible use of identifier "@(name)@quot;@
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__identifier__annotate_expression_17(void) {
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
  // 273: info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_18;
}
static void cont__compiler__identifier__annotate_expression_18(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__2 */ = arguments->slots[0];
  // 273: ... variable_kind_of(info) == STATIC_SINGLE
  frame->slots[5] /* temp__3 */ = create_closure(entry__compiler__identifier__annotate_expression_19, 0);
  // 273: info.is_undefined || variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__2 */;
  arguments->slots[1] = frame->slots[5] /* temp__3 */;
  result_count = 1;
  myself = get__std__or();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_22;
}
static void entry__compiler__identifier__annotate_expression_19(void) {
  allocate_initialized_frame_gc(1, 3);
  // slot allocations:
  // info: 0
  frame->slots[0] = myself->closure.frame->slots[0]; /* info */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 273: ... variable_kind_of(info)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__variable_kind_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_20;
}
static void cont__compiler__identifier__annotate_expression_20(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[2] /* temp__2 */ = arguments->slots[0];
  // 273: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* temp__2 */;
  arguments->slots[1] = get__STATIC_SINGLE();
  result_count = 1;
  myself = get__std__equal();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_21;
}
static void cont__compiler__identifier__annotate_expression_21(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[1] /* temp__1 */ = arguments->slots[0];
  // 273: ... variable_kind_of(info) == STATIC_SINGLE
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* temp__1 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void cont__compiler__identifier__annotate_expression_22(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 273: ... :
  // 274:   !used_names(name)
  // 275:     types::grammar_node
  // 276:       .identifier_of self
  // 277:       .variable_kind_of STATIC_MULTI
  frame->slots[6] /* temp__4 */ = create_closure(entry__compiler__identifier__annotate_expression_23, 0);
  // 278: :
  // 279:   if variable_kind_of(info) == POLYMORPHIC:
  // 280:     SyntaxError self "
  // 281:       Incompatible use of identifier "@(name)@quot;@
  frame->slots[7] /* temp__5 */ = create_closure(entry__compiler__identifier__annotate_expression_25, 0);
  // 272: if
  // 273:   info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 274:     !used_names(name)
  // 275:       types::grammar_node
  // 276:         .identifier_of self
  // 277:         .variable_kind_of STATIC_MULTI
  // 278:   :
  // 279:     if variable_kind_of(info) == POLYMORPHIC:
  // 280:       SyntaxError self "
  // 281:         Incompatible use of identifier "@(name)@quot;@
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
static void entry__compiler__identifier__annotate_expression_15(void) {
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
  // 271: ... self.is_used_as_a_destination
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_used_as_a_destination();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_16;
}
static void cont__compiler__identifier__annotate_expression_16(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 271: ... :
  // 272:   if
  // 273:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 274:       !used_names(name)
  // 275:         types::grammar_node
  // 276:           .identifier_of self
  // 277:           .variable_kind_of STATIC_MULTI
  // 278:     :
  // 279:       if variable_kind_of(info) == POLYMORPHIC:
  // 280:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_17, 0);
  // 271: -> self.is_used_as_a_destination:
  // 272:   if
  // 273:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 274:       !used_names(name)
  // 275:         types::grammar_node
  // 276:           .identifier_of self
  // 277:           .variable_kind_of STATIC_MULTI
  // 278:     :
  // 279:       if variable_kind_of(info) == POLYMORPHIC:
  // 280:         SyntaxError self "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__annotate_expression_32(void) {
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
  // 282: ... self.is_used_as_a_polymorphic_function
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__is_used_as_a_polymorphic_function();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_33;
}
static void cont__compiler__identifier__annotate_expression_33(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 282: ... :
  // 283:   if
  // 284:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 285:       !used_names(name)
  // 286:         types::grammar_node
  // 287:           .identifier_of self
  // 288:           .variable_kind_of POLYMORPHIC
  // 289:     :
  // 290:       unless variable_kind_of(info) == POLYMORPHIC:
  // 291:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_34, 0);
  // 282: -> self.is_used_as_a_polymorphic_function:
  // 283:   if
  // 284:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 285:       !used_names(name)
  // 286:         types::grammar_node
  // 287:           .identifier_of self
  // 288:           .variable_kind_of POLYMORPHIC
  // 289:     :
  // 290:       unless variable_kind_of(info) == POLYMORPHIC:
  // 291:         SyntaxError self "
  // ...
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__annotate_expression_47(void) {
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
  // 294: ... info.is_undefined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* info */;
  result_count = 1;
  myself = get__is_undefined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_48;
}
static void cont__compiler__identifier__annotate_expression_48(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 294: ... :
  // 295:   !used_names(name)
  // 296:     types::grammar_node
  // 297:       .identifier_of self
  // 298:       .variable_kind_of STATIC_SINGLE
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_49, 0);
  // 294: if info.is_undefined:
  // 295:   !used_names(name)
  // 296:     types::grammar_node
  // 297:       .identifier_of self
  // 298:       .variable_kind_of STATIC_SINGLE
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void entry__compiler__identifier__annotate_expression_5(void) {
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
  // 264: $namespace namespace_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__namespace_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_6;
}
static void cont__compiler__identifier__annotate_expression_6(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[1] /* namespace */, arguments->slots[0]);
  // 265: ... namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[1] /* namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_7;
}
static void cont__compiler__identifier__annotate_expression_7(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[4] /* temp__1 */ = arguments->slots[0];
  // 265: ... :
  // 266:   $mapped_namespace namespace_mappings(namespace)
  // 267:   if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_8, 0);
  // 265: if namespace.is_defined:
  // 266:   $mapped_namespace namespace_mappings(namespace)
  // 267:   if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[4] /* temp__1 */;
  arguments->slots[1] = frame->slots[5] /* temp__2 */;
  result_count = 0;
  myself = get__if();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_12;
}
static void entry__compiler__identifier__annotate_expression_11(void) {
  allocate_initialized_frame_gc(2, 2);
  // slot allocations:
  // self: 0
  // mapped_namespace: 1
  frame->slots[0] = myself->closure.frame->slots[1]; /* self */
  frame->slots[1] = myself->closure.frame->slots[2]; /* mapped_namespace */
  if (argument_count != 0) {
    invalid_arguments_error();
    return;
  }
  // 267: ... !self.namespace_of
  {
    NODE *temp = clone_object_and_attributes(((CELL *)frame->slots[0])->contents /* self */);
    update_start_p = node_p;
    set_attribute_value(temp->attributes, poly_idx__namespace_of, frame->slots[1] /* mapped_namespace */);
    ((CELL *)frame->slots[0])->contents /* self */ = temp;

  }
  argument_count = 0;
  arguments = node_p;
  frame = frame->caller_frame;
  func = frame->cont;
  frame->cont = invalid_continuation;
}
static void entry__compiler__identifier__annotate_expression_8(void) {
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
  // 266: $mapped_namespace namespace_mappings(namespace)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[0] /* namespace */;
  result_count = 1;
  myself = get__namespace_mappings();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_9;
}
static void cont__compiler__identifier__annotate_expression_9(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* mapped_namespace */, arguments->slots[0]);
  // 267: ... mapped_namespace.is_defined
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* mapped_namespace */;
  result_count = 1;
  myself = get__is_defined();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_10;
}
static void cont__compiler__identifier__annotate_expression_10(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  frame->slots[3] /* temp__1 */ = arguments->slots[0];
  // 267: ... : !self.namespace_of mapped_namespace
  frame->slots[4] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_11, 0);
  // 267: if mapped_namespace.is_defined: !self.namespace_of mapped_namespace
  argument_count = 2;
  arguments = node_p;
  arguments->slots[0] = frame->slots[3] /* temp__1 */;
  arguments->slots[1] = frame->slots[4] /* temp__2 */;
  result_count = frame->caller_result_count;
  myself = get__if();
  func = myself->type;
  frame = frame->caller_frame;
}
static void cont__compiler__identifier__annotate_expression_12(void) {
  if (argument_count != 0) {
    invalid_results_error();
    return;
  }
  // 268: $name mangled_name_of(self)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = ((CELL *)frame->slots[0])->contents /* self */;
  result_count = 1;
  myself = get__mangled_name_of();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_13;
}
static void cont__compiler__identifier__annotate_expression_13(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[2] /* name */, arguments->slots[0]);
  // 269: $info used_names(name)
  argument_count = 1;
  arguments = node_p;
  arguments->slots[0] = frame->slots[2] /* name */;
  result_count = 1;
  myself = get__used_names();
  func = myself->type;
  frame->cont = cont__compiler__identifier__annotate_expression_14;
}
static void cont__compiler__identifier__annotate_expression_14(void) {
  if (argument_count != 1) {
    invalid_results_error();
    return;
  }
  initialize_future(frame->slots[3] /* info */, arguments->slots[0]);
  // 271: -> self.is_used_as_a_destination:
  // 272:   if
  // 273:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 274:       !used_names(name)
  // 275:         types::grammar_node
  // 276:           .identifier_of self
  // 277:           .variable_kind_of STATIC_MULTI
  // 278:     :
  // 279:       if variable_kind_of(info) == POLYMORPHIC:
  // 280:         SyntaxError self "
  // ...
  frame->slots[4] /* temp__1 */ = create_closure(entry__compiler__identifier__annotate_expression_15, 0);
  // 282: -> self.is_used_as_a_polymorphic_function:
  // 283:   if
  // 284:     info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 285:       !used_names(name)
  // 286:         types::grammar_node
  // 287:           .identifier_of self
  // 288:           .variable_kind_of POLYMORPHIC
  // 289:     :
  // 290:       unless variable_kind_of(info) == POLYMORPHIC:
  // 291:         SyntaxError self "
  // ...
  frame->slots[5] /* temp__2 */ = create_closure(entry__compiler__identifier__annotate_expression_32, 0);
  // 293: :
  // 294:   if info.is_undefined:
  // 295:     !used_names(name)
  // 296:       types::grammar_node
  // 297:         .identifier_of self
  // 298:         .variable_kind_of STATIC_SINGLE
  frame->slots[6] /* temp__3 */ = create_closure(entry__compiler__identifier__annotate_expression_47, 0);
  // 270: cond
  // 271:   -> self.is_used_as_a_destination:
  // 272:     if
  // 273:       info.is_undefined || variable_kind_of(info) == STATIC_SINGLE:
  // 274:         !used_names(name)
  // 275:           types::grammar_node
  // 276:             .identifier_of self
  // 277:             .variable_kind_of STATIC_MULTI
  // 278:       :
  // 279:         if variable_kind_of(info) == POLYMORPHIC:
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
static void cont__compiler__identifier___annotate_expression_51(void) {
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
  var.compiler__annotate_statement = collect_node(var.compiler__annotate_statement);
  var.compiler__annotate_expression = collect_node(var.compiler__annotate_expression);
  var.compiler__check_definitions = collect_node(var.compiler__check_definitions);
}

static int already_run_phase_1 = false;

EXPORT void phase_1__annotator(void) {
  if (already_run_phase_1) return;
  already_run_phase_1 = true;
  register_module_info(&module_info);
}

static int already_run_phase_2 = false;

EXPORT void phase_2__annotator(void) {
  if (already_run_phase_2) return;
  already_run_phase_2 = true;
  set_module("annotator");
  number__1 = from_uint32(1U);
  number__2 = from_uint32(2U);
  define_polymorphic_function("compiler", "annotate_statement", get__compiler__annotate_statement, &poly_idx__compiler__annotate_statement, &var.compiler__annotate_statement);
  define_polymorphic_function("compiler", "annotate_expression", get__compiler__annotate_expression, &poly_idx__compiler__annotate_expression, &var.compiler__annotate_expression);
  func__annotate_arguments_5 = create_function(entry__annotate_arguments_5, 0);
  func__annotate_arguments_2 = create_function(entry__annotate_arguments_2, 1);
  func__annotate_arguments = create_function(entry__annotate_arguments, 1);
  string__8a2e321e316b06ed = from_latin_1_string("annotate statement", 18);
  func__types__grammar_node___annotate_statement = create_function(entry__types__grammar_node___annotate_statement, 1);
  string__bce93a983bb5b33f = from_latin_1_string("annotate expression", 19);
  func__types__grammar_node___annotate_expression = create_function(entry__types__grammar_node___annotate_expression, 1);
  string__1f20e521cf7a2a0e = from_latin_1_string("the identifier \042", 16);
  string__e573d863c40ad98e = from_latin_1_string("\042 is defined but not used", 25);
  string__6ef85e6a0d2c67a5 = from_latin_1_string("\042 is defined as a read-write variable, but there is no actual assignment", 72);
  string__fd0945f8c8a23329 = from_latin_1_string("attempt to use the identifier \042", 31);
  string__27789aef2dccadff = from_latin_1_string("\042 that is marked as not being used", 34);
  func__compiler__check_definitions = create_function(entry__compiler__check_definitions, 2);
  string__463aabf2a07456b1 = from_latin_1_string("annotate body", 13);
  func__compiler__body__annotate_expression_7 = create_function(entry__compiler__body__annotate_expression_7, 1);
  func__compiler__body__annotate_expression_20 = create_function(entry__compiler__body__annotate_expression_20, 1);
  string__c9348eff105534ce = from_latin_1_string("attempt to define a namespaced entity (", 39);
  string__dcee629a9fc6e3f6 = from_latin_1_string(") in an inner scope", 19);
  string__e3b540e1e08e3bc7 = from_latin_1_string("Attempt to define a variable twice within a single scope (", 58);
  string__578a5af303e9cc8 = from_latin_1_string(")", 1);
  string__4a80ae5c052cc23f = from_latin_1_string("return__", 8);
  func__compiler__body__annotate_expression_85 = create_function(entry__compiler__body__annotate_expression_85, 1);
  func__compiler__body___annotate_expression = create_function(entry__compiler__body___annotate_expression, 1);
  func__compiler__call__annotate_statement_30 = create_function(entry__compiler__call__annotate_statement_30, 0);
  func__compiler__call__annotate_statement_35 = create_function(entry__compiler__call__annotate_statement_35, 0);
  string__fa72f815cd16b93 = from_latin_1_string("___", 3);
  string__4668ab89845667a5 = from_latin_1_string("____type", 8);
  func__compiler__call___annotate_statement = create_function(entry__compiler__call___annotate_statement, 1);
  string__1315a9c10d8edccd = from_latin_1_string("annotate C-code", 15);
  string__2a0aef0b5de07d5c = from_latin_1_string("type", 4);
  string__4c1f570701a272a3 = from_latin_1_string("object", 6);
  func__compiler__c_code___annotate_statement = create_function(entry__compiler__c_code___annotate_statement, 1);
  string__da22f4fe83fda879 = from_latin_1_string("annotate define static single", 29);
  func__compiler__define_static_single___annotate_expression = create_function(entry__compiler__define_static_single___annotate_expression, 1);
  string__8d039bc45e06307a = from_latin_1_string("annotate define static multi", 28);
  func__compiler__define_static_multi___annotate_expression = create_function(entry__compiler__define_static_multi___annotate_expression, 1);
  string__ff383df04998a917 = from_latin_1_string("annotate define dynamic single", 30);
  func__compiler__define_dynamic_single___annotate_expression = create_function(entry__compiler__define_dynamic_single___annotate_expression, 1);
  string__2d2e5f670727e936 = from_latin_1_string("annotate define dynamic multi", 29);
  func__compiler__define_dynamic_multi___annotate_expression = create_function(entry__compiler__define_dynamic_multi___annotate_expression, 1);
  string__e5094206a209984d = from_latin_1_string("annotate function call", 22);
  func__compiler__function_call___annotate_expression = create_function(entry__compiler__function_call___annotate_expression, 1);
  string__cdedef056fb3250d = from_latin_1_string("annotate attribute-value pair", 29);
  func__compiler__attribute_value_pair___annotate_expression = create_function(entry__compiler__attribute_value_pair___annotate_expression, 1);
  string__9fe7729998bbff18 = from_latin_1_string("annotate attribute-function pair", 32);
  func__compiler__attribute_function_pair___annotate_expression = create_function(entry__compiler__attribute_function_pair___annotate_expression, 1);
  string__d4853f208c1cb4ea = from_latin_1_string("annotate identifier ", 20);
  string__94ba0bbafc65551 = from_latin_1_string("Incompatible use of identifier \042", 32);
  string__578a5af303e9cc3 = from_latin_1_string("\042", 1);
  func__compiler__identifier___annotate_expression = create_function(entry__compiler__identifier___annotate_expression, 1);
}

static int already_run_phase_3 = false;

EXPORT void phase_3__annotator(void) {
  if (already_run_phase_3) return;
  already_run_phase_3 = true;
  set_module("annotator");
  set_used_namespaces(used_namespaces);
  register_dynamic(&dyna_idx__defines_dynamics);
  define__defines_dynamics(undefined);
  register_dynamic(&dyna_idx__level);
  var.compiler__check_definitions = create_future();
  define_single_assign_static("compiler", "check_definitions", get__compiler__check_definitions, &var.compiler__check_definitions);
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
  use_read_only(NULL, "append", &get__append, &get_value_or_future__append);
  use_polymorphic_function(NULL, "arguments_of", &get__arguments_of, &poly_idx__arguments_of);
  use_read_write(NULL, "assigned_names", &get__assigned_names, &set__assigned_names);
  use_read_only(NULL, "attribute_kind_of", &get__attribute_kind_of, &get_value_or_future__attribute_kind_of);
  use_polymorphic_function(NULL, "attribute_of", &get__attribute_of, &poly_idx__attribute_of);
  use_polymorphic_function(NULL, "base_of", &get__base_of, &poly_idx__base_of);
  use_read_only(NULL, "case", &get__case, &get_value_or_future__case);
  use_read_only(NULL, "check_definitions", &get__check_definitions, &get_value_or_future__check_definitions);
  use_multi_assign_dynamic("compiler", "assigned_names", &get__compiler__assigned_names, &set__compiler__assigned_names, &define__compiler__assigned_names);
  use_read_only("compiler", "attribute_function_pair", &get__compiler__attribute_function_pair, &get_value_or_future__compiler__attribute_function_pair);
  use_read_only("compiler", "attribute_value_pair", &get__compiler__attribute_value_pair, &get_value_or_future__compiler__attribute_value_pair);
  use_read_only("compiler", "body", &get__compiler__body, &get_value_or_future__compiler__body);
  use_read_only("compiler", "c_code", &get__compiler__c_code, &get_value_or_future__compiler__c_code);
  use_read_only("compiler", "call", &get__compiler__call, &get_value_or_future__compiler__call);
  use_read_only("compiler", "define_dynamic_multi", &get__compiler__define_dynamic_multi, &get_value_or_future__compiler__define_dynamic_multi);
  use_read_only("compiler", "define_dynamic_single", &get__compiler__define_dynamic_single, &get_value_or_future__compiler__define_dynamic_single);
  use_read_only("compiler", "define_static_multi", &get__compiler__define_static_multi, &get_value_or_future__compiler__define_static_multi);
  use_read_only("compiler", "define_static_single", &get__compiler__define_static_single, &get_value_or_future__compiler__define_static_single);
  use_multi_assign_dynamic("compiler", "defined_names", &get__compiler__defined_names, &set__compiler__defined_names, &define__compiler__defined_names);
  use_read_only("compiler", "function_call", &get__compiler__function_call, &get_value_or_future__compiler__function_call);
  use_read_only("compiler", "identifier", &get__compiler__identifier, &get_value_or_future__compiler__identifier);
  use_multi_assign_dynamic("compiler", "used_names", &get__compiler__used_names, &set__compiler__used_names, &define__compiler__used_names);
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
  use_read_only(NULL, "is_an_attribute_access", &get__is_an_attribute_access, &get_value_or_future__is_an_attribute_access);
  use_read_only(NULL, "is_an_operator_symbol", &get__is_an_operator_symbol, &get_value_or_future__is_an_operator_symbol);
  use_read_only(NULL, "is_an_optional_item", &get__is_an_optional_item, &get_value_or_future__is_an_optional_item);
  use_read_only(NULL, "is_defined", &get__is_defined, &get_value_or_future__is_defined);
  use_read_only(NULL, "is_empty", &get__is_empty, &get_value_or_future__is_empty);
  use_read_only(NULL, "is_not_used", &get__is_not_used, &get_value_or_future__is_not_used);
  use_read_only(NULL, "is_undefined", &get__is_undefined, &get_value_or_future__is_undefined);
  use_read_only(NULL, "is_used_as_a_destination", &get__is_used_as_a_destination, &get_value_or_future__is_used_as_a_destination);
  use_read_only(NULL, "is_used_as_a_polymorphic_function", &get__is_used_as_a_polymorphic_function, &get_value_or_future__is_used_as_a_polymorphic_function);
  use_read_only(NULL, "kind_of", &get__kind_of, &get_value_or_future__kind_of);
  use_read_only(NULL, "mangled_name_of", &get__mangled_name_of, &get_value_or_future__mangled_name_of);
  use_polymorphic_function(NULL, "name_of", &get__name_of, &poly_idx__name_of);
  use_read_only(NULL, "namespace_mappings", &get__namespace_mappings, &get_value_or_future__namespace_mappings);
  use_polymorphic_function(NULL, "namespace_of", &get__namespace_of, &poly_idx__namespace_of);
  use_read_only(NULL, "not", &get__not, &get_value_or_future__not);
  use_polymorphic_function(NULL, "parameter_kind_of", &get__parameter_kind_of, &poly_idx__parameter_kind_of);
  use_polymorphic_function(NULL, "parameters_of", &get__parameters_of, &poly_idx__parameters_of);
  use_read_only(NULL, "push", &get__push, &get_value_or_future__push);
  use_polymorphic_function(NULL, "result_count_of", &get__result_count_of, &poly_idx__result_count_of);
  use_read_only(NULL, "show_compiler_debug_info", &get__show_compiler_debug_info, &get_value_or_future__show_compiler_debug_info);
  use_polymorphic_function(NULL, "statements_of", &get__statements_of, &poly_idx__statements_of);
  use_read_only("std", "and", &get__std__and, &get_value_or_future__std__and);
  use_read_only("std", "equal", &get__std__equal, &get_value_or_future__std__equal);
  use_read_only("std", "negate", &get__std__negate, &get_value_or_future__std__negate);
  use_read_only("std", "not", &get__std__not, &get_value_or_future__std__not);
  use_read_only("std", "or", &get__std__or, &get_value_or_future__std__or);
  use_read_only("std", "plus", &get__std__plus, &get_value_or_future__std__plus);
  use_read_only("std", "sequence", &get__std__sequence, &get_value_or_future__std__sequence);
  use_read_only("std", "string", &get__std__string, &get_value_or_future__std__string);
  use_read_only(NULL, "string", &get__string, &get_value_or_future__string);
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
  define_method("types", "grammar_node", poly_idx__annotate_statement, func__types__grammar_node___annotate_statement);
  define_method("types", "grammar_node", poly_idx__annotate_expression, func__types__grammar_node___annotate_expression);
  define_method("compiler", "body", poly_idx__annotate_expression, func__compiler__body___annotate_expression);
  define_method("compiler", "call", poly_idx__annotate_statement, func__compiler__call___annotate_statement);
  define_method("compiler", "c_code", poly_idx__annotate_statement, func__compiler__c_code___annotate_statement);
  define_method("compiler", "define_static_single", poly_idx__annotate_expression, func__compiler__define_static_single___annotate_expression);
  define_method("compiler", "define_static_multi", poly_idx__annotate_expression, func__compiler__define_static_multi___annotate_expression);
  define_method("compiler", "define_dynamic_single", poly_idx__annotate_expression, func__compiler__define_dynamic_single___annotate_expression);
  define_method("compiler", "define_dynamic_multi", poly_idx__annotate_expression, func__compiler__define_dynamic_multi___annotate_expression);
  define_method("compiler", "function_call", poly_idx__annotate_expression, func__compiler__function_call___annotate_expression);
  define_method("compiler", "attribute_value_pair", poly_idx__annotate_expression, func__compiler__attribute_value_pair___annotate_expression);
  define_method("compiler", "attribute_function_pair", poly_idx__annotate_expression, func__compiler__attribute_function_pair___annotate_expression);
  define_method("compiler", "identifier", poly_idx__annotate_expression, func__compiler__identifier___annotate_expression);
}

static int already_run_phase_5 = false;

EXPORT void phase_5__annotator(void) {
  if (already_run_phase_5) return;
  already_run_phase_5 = true;
  define__level(number__1);
  assign_value(&var.compiler__annotate_statement, create_function(type__compiler__annotate_statement, -1));
  assign_value(&var.compiler__annotate_expression, create_function(type__compiler__annotate_expression, -1));
  initialize_future(var.compiler__check_definitions, func__compiler__check_definitions);
}

static int already_run_phase_6 = false;

EXPORT void phase_6__annotator(void) {
  if (already_run_phase_6) return;
  already_run_phase_6 = true;
  register_collector(collect__annotator);
}
